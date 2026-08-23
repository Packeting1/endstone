// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "bedrock/network/packet.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <variant>

#include "bedrock/entity/components/user_entity_identifier_component.h"
#include "bedrock/network/net_event_callback.h"
#include "bedrock/network/network_identifier.h"
#include "bedrock/network/packet/book_edit_packet.h"
#include "bedrock/network/packet/correct_player_move_prediction_packet.h"
#include "bedrock/network/packet/emote_packet.h"
#include "bedrock/network/packet/mob_equipment_packet.h"
#include "bedrock/network/packet/player_action_packet.h"
#include "bedrock/network/packet/player_auth_input_packet.h"
#include "bedrock/network/packet/player_skin_packet.h"
#include "bedrock/network/packet/set_local_player_as_initialized_packet.h"
#include "bedrock/network/packet/set_player_inventory_options_packet.h"
#include "bedrock/network/server_network_handler.h"
#include "bedrock/server/server_instance.h"
#include "bedrock/world/actor/provider/actor_offset.h"
#include "bedrock/world/level/block_source.h"
#include "bedrock/world/phys/aabb.h"
#include "endstone/block/block.h"
#include "endstone/color_format.h"
#include "endstone/core/entity/components/flag_components.h"
#include "endstone/core/inventory/item_factory.h"
#include "endstone/core/player.h"
#include "endstone/core/server.h"
#include "endstone/core/skin.h"
#include "endstone/event/actor/actor_toggle_glide_event.h"
#include "endstone/event/actor/actor_toggle_swim_event.h"
#include "endstone/event/player/player_edit_book_event.h"
#include "endstone/event/player/player_emote_event.h"
#include "endstone/event/player/player_input_event.h"
#include "endstone/event/player/player_interact_event.h"
#include "endstone/event/player/player_item_held_event.h"
#include "endstone/event/player/player_jump_event.h"
#include "endstone/event/player/player_move_event.h"
#include "endstone/event/player/player_recipe_book_settings_change_event.h"
#include "endstone/event/player/player_skin_change_event.h"
#include "endstone/event/player/player_toggle_crawl_event.h"
#include "endstone/event/player/player_toggle_flight_event.h"
#include "endstone/event/player/player_toggle_sneak_event.h"
#include "endstone/event/player/player_toggle_sprint_event.h"
#include "endstone/inventory/item_stack.h"
#include "endstone/inventory/meta/book_meta.h"
#include "endstone/runtime/hook.h"
#include "endstone/variant.h"

namespace endstone::core {

namespace {

struct PacketRateWindow {
    std::chrono::steady_clock::time_point started = std::chrono::steady_clock::now();
    double packets = 0.0;
};

struct IncomingSpamWindow {
    std::chrono::steady_clock::time_point last_packet = std::chrono::steady_clock::time_point{};
    std::uint32_t limited_packets = 0;
};

std::mutex packet_rate_mutex;
std::unordered_map<std::string, PacketRateWindow> packet_rate_windows;
std::unordered_map<std::string, IncomingSpamWindow> incoming_spam_windows;

bool allowIncomingPacket(const EndstoneServer &server, const NetworkIdentifier &network_id, const Packet &packet)
{
    const auto &config = server.getConfig();
    const auto now = std::chrono::steady_clock::now();
    const auto incoming_packet_threshold = config.getInt("paper.global.spam-limiter.incoming-packet-threshold", -1);
    if (incoming_packet_threshold >= 0) {
        auto spam_key = network_id.getAddress();
        spam_key.append(1, '\x1f');
        spam_key.append(std::to_string(static_cast<int>(packet.getSenderSubId())));
        bool ignored = false;
        {
            std::lock_guard lock(packet_rate_mutex);
            auto &window = incoming_spam_windows[spam_key];
            const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - window.last_packet);
            if (window.last_packet != std::chrono::steady_clock::time_point{} &&
                elapsed.count() < incoming_packet_threshold) {
                ignored = window.limited_packets++ >= 8;
            }
            else {
                window.last_packet = now;
                window.limited_packets = 0;
            }
        }
        if (ignored) {
            return false;
        }
    }

    const auto all_packets_prefix = std::string_view{"paper.global.packet-limiter.all-packets."};
    const auto packet_override_prefix =
        std::string{"paper.global.packet-limiter.overrides."} + std::string{packet.getName()} + ".";
    const auto has_packet_override = config.has(packet_override_prefix + "interval") ||
                                     config.has(packet_override_prefix + "max-packet-rate") ||
                                     config.has(packet_override_prefix + "action");
    const auto prefix = has_packet_override ? std::string_view{packet_override_prefix} : all_packets_prefix;
    const auto interval = config.getDouble(std::string{prefix} + "interval", 7.0);
    const auto limit = config.getDouble(std::string{prefix} + "max-packet-rate", 500.0);
    if (interval <= 0.0 || limit <= 0.0) {
        return true;
    }

    auto key = network_id.getAddress();
    if (has_packet_override) {
        key.append(1, '\x1f');
        key.append(packet.getName());
    }
    bool exceeded = false;
    {
        std::lock_guard lock(packet_rate_mutex);
        auto &window = packet_rate_windows[key];
        if (std::chrono::duration<double>(now - window.started).count() >= interval) {
            window = PacketRateWindow{now, 0.0};
        }
        exceeded = ++window.packets > limit;
    }
    if (!exceeded) {
        return true;
    }

    if (config.getString(std::string{prefix} + "action", "KICK") == "KICK") {
        const auto message =
            config.getString("paper.global.packet-limiter.kick-message", "<red><lang:disconnect.exceeded_packet_rate>");
        server.getServer().getMinecraft()->getServerNetworkHandler()->disconnect(network_id, packet.getSenderSubId(),
                                                                                 message);
    }
    return false;
}

std::size_t utf8CharacterCount(std::string_view value)
{
    std::size_t result = 0;
    for (const auto byte : value) {
        if ((static_cast<unsigned char>(byte) & 0xc0U) != 0x80U) {
            ++result;
        }
    }
    return result;
}

}  // namespace

class EndstonePacketHandler {
public:
    EndstonePacketHandler(const NetworkIdentifier &network_id, NetEventCallback &callback,
                          const IPacketHandlerDispatcher &original, std::shared_ptr<Packet> &packet)
        : network_id_(network_id), callback_(callback), original_(original), packet_(packet)
    {
    }

    template <typename T>
    void handle(T &packet);

private:
    ServerPlayer *getPlayer()
    {
        if (player_ == nullptr) {
            auto &network_handler = static_cast<ServerNetworkHandler &>(callback_);
            player_ = network_handler.getServerPlayer(network_id_, packet_->getSenderSubId());
        }
        return player_;
    }

    void handle() const { original_.handle(network_id_, callback_, packet_); }

    const NetworkIdentifier &network_id_;
    NetEventCallback &callback_;
    const IPacketHandlerDispatcher &original_;
    std::shared_ptr<Packet> &packet_;
    ServerPlayer *player_ = nullptr;
};

template <>
void EndstonePacketHandler::handle(MobEquipmentPacket &packet)
{
    const auto *player = getPlayer();
    if (player == nullptr) {
        return;
    }
    const auto endstone_player = player->getEndstoneActor<EndstonePlayer>();
    const auto from_slot = endstone_player->getInventory().getHeldItemSlot();
    const auto to_slot = packet.payload.selected_slot;
    if (from_slot == to_slot) {
        handle();
        return;
    }
    PlayerItemHeldEvent e(endstone_player, from_slot, to_slot);
    endstone_player->getServer().getPluginManager().callEvent(e);
    if (e.isCancelled()) {
        endstone_player->getInventory().setHeldItemSlot(from_slot);
        return;
    }
    handle();
}

template <>
void EndstonePacketHandler::handle(BookEditPacket &packet)
{
    constexpr auto writable_book = ItemTypeId::minecraft("writable_book");
    constexpr auto written_book = ItemTypeId::minecraft("written_book");
    constexpr int max_page_count = 50;
    constexpr std::int64_t default_page_length = 16384;
    constexpr std::int64_t default_author_length = 8192;
    constexpr std::int64_t default_title_length = 8192;

    const auto &config = EndstoneServer::getInstance().getConfig();
    const auto configured_page_length = config.getInt("paper.global.item-validation.book.page", default_page_length);
    const auto page_length_limit = configured_page_length > 0 ? static_cast<std::size_t>(configured_page_length)
                                                              : static_cast<std::size_t>(default_page_length);
    const auto configured_page_size = config.getInt("paper.global.item-validation.book-size.page-max", -1);
    const auto page_size_limit = configured_page_size > 0 ? static_cast<std::size_t>(configured_page_size) : 0;
    const auto configured_author_length =
        config.getInt("paper.global.item-validation.book.author", default_author_length);
    const auto author_length_limit = configured_author_length > 0 ? static_cast<std::size_t>(configured_author_length)
                                                                  : static_cast<std::size_t>(default_author_length);
    const auto configured_title_length = config.getInt("paper.global.item-validation.book.title", default_title_length);
    const auto title_length_limit = configured_title_length > 0 ? static_cast<std::size_t>(configured_title_length)
                                                                : static_cast<std::size_t>(default_title_length);
    const auto page_exceeds_limits = [page_length_limit, page_size_limit](std::string_view page) {
        return utf8CharacterCount(page) > page_length_limit || (page_size_limit != 0 && page.size() > page_size_limit);
    };
    const auto resolve_selectors = config.getBool("paper.global.item-validation.resolve-selectors-in-books", false);
    (void)resolve_selectors;

    const auto book_exceeds_total_limit = [configured_page_size, &config](const std::vector<std::string> &pages) {
        if (configured_page_size <= 0) {
            return false;
        }
        const auto multiplier =
            std::clamp(config.getDouble("paper.global.item-validation.book-size.total-multiplier", 0.98), 0.3, 1.0);
        std::size_t byte_total = 0;
        double byte_allowed = static_cast<double>(configured_page_size);
        for (const auto &page : pages) {
            byte_total += page.size();
            const auto character_count = utf8CharacterCount(page);
            const auto page_multiplier = std::clamp(static_cast<double>(character_count) / 255.0, 0.1, 1.0);
            byte_allowed += static_cast<double>(configured_page_size) * page_multiplier * multiplier;
            const auto multibyte_characters =
                static_cast<std::size_t>(std::count_if(page.begin(), page.end(), [](const char byte) {
                    const auto value = static_cast<unsigned char>(byte);
                    return value > 127U && (value & 0xc0U) != 0x80U;
                }));
            if (multibyte_characters > 1) {
                byte_allowed -= static_cast<double>(multibyte_characters);
            }
        }
        return static_cast<double>(byte_total) > byte_allowed;
    };

    const auto text_exceeds_limit = [](std::string_view text, std::size_t limit) {
        return utf8CharacterCount(text) > limit;
    };

    const auto *player = getPlayer();
    if (player == nullptr) {
        return;
    }
    const auto endstone_player = player->getEndstoneActor<EndstonePlayer>();
    auto &inventory = endstone_player->getInventory();
    const auto slot = packet.payload.book_slot;
    if (slot < 0 || slot >= inventory.getSize()) {
        handle();
        return;
    }

    const auto item = inventory.getItem(slot);
    if (!item || item->getType().getId() != writable_book) {
        handle();
        return;
    }

    auto &item_factory = EndstoneItemFactory::instance();
    const auto meta = item->getItemMeta();
    const auto previous_book_meta = item_factory.asMetaFor(meta.get().get(), written_book).as<BookMeta>();
    const auto new_book_meta = item_factory.asMetaFor(meta.get().get(), written_book).as<BookMeta>();
    if (!previous_book_meta || !new_book_meta) {
        handle();
        return;
    }

    bool invalid_action = false;
    std::visit(overloaded{
                   [&](const BookEditAction::ReplacePage &action) {
                       if (action.page_index < 0 || action.page_index >= max_page_count ||
                           page_exceeds_limits(action.page_text)) {
                           invalid_action = true;
                           return;
                       }
                       auto pages = new_book_meta->getPages();
                       if (action.page_index >= static_cast<int>(pages.size())) {
                           pages.resize(action.page_index);
                           pages.emplace_back(action.page_text);
                       }
                       else {
                           pages[action.page_index] = action.page_text;
                       }
                       new_book_meta->setPages(std::move(pages));
                   },
                   [&](const BookEditAction::AddPage &action) {
                       if (action.page_index < 0 || action.page_index >= max_page_count ||
                           page_exceeds_limits(action.page_text)) {
                           invalid_action = true;
                           return;
                       }
                       auto pages = new_book_meta->getPages();
                       if (static_cast<int>(pages.size()) >= max_page_count) {
                           return;
                       }
                       if (action.page_index >= static_cast<int>(pages.size())) {
                           pages.resize(action.page_index);
                           pages.emplace_back(action.page_text);
                       }
                       else {
                           pages.insert(pages.begin() + action.page_index, action.page_text);
                       }
                       new_book_meta->setPages(std::move(pages));
                   },
                   [&](const BookEditAction::DeletePage &action) {
                       auto pages = new_book_meta->getPages();
                       if (action.page_index >= 0 && action.page_index < static_cast<int>(pages.size())) {
                           pages.erase(pages.begin() + action.page_index);
                           new_book_meta->setPages(std::move(pages));
                       }
                   },
                   [&](const BookEditAction::SwapPages &action) {
                       auto pages = new_book_meta->getPages();
                       if (action.page_index >= 0 && action.page_index < static_cast<int>(pages.size()) &&
                           action.swap_with_index >= 0 && action.swap_with_index < static_cast<int>(pages.size())) {
                           std::swap(pages[action.page_index], pages[action.swap_with_index]);
                           new_book_meta->setPages(std::move(pages));
                       }
                   },
                   [&](const BookEditAction::Finalize &action) {
                       if (text_exceeds_limit(action.title, title_length_limit) ||
                           text_exceeds_limit(action.author, author_length_limit)) {
                           invalid_action = true;
                           return;
                       }
                       new_book_meta->setTitle(action.title);
                       new_book_meta->setAuthor(action.author);
                       new_book_meta->setGeneration(BookMeta::Generation::Original);
                   },
               },
               packet.payload.operation);
    if (!invalid_action && book_exceeds_total_limit(new_book_meta->getPages())) {
        invalid_action = true;
    }
    if (invalid_action) {
        return;
    }
    const auto is_signing = std::holds_alternative<BookEditAction::Finalize>(packet.payload.operation);

    PlayerEditBookEvent e{endstone_player, slot, previous_book_meta, new_book_meta, is_signing};
    endstone_player->getServer().getPluginManager().callEvent(e);
    if (e.isCancelled()) {
        return;
    }

    if (e.isSigning() != is_signing) {
        auto edited_item = *item;
        edited_item.setType(e.isSigning() ? written_book : writable_book);
        if (edited_item.setItemMeta(e.getNewBookMeta().get().get())) {
            inventory.setItem(slot, std::move(edited_item));
        }
        return;
    }

    const auto meta_changed = !item_factory.equals(e.getNewBookMeta().get().get(), new_book_meta.get().get());

    handle();

    if (!meta_changed) {
        return;
    }
    auto edited_item = inventory.getItem(slot);
    if (edited_item && edited_item->setItemMeta(e.getNewBookMeta().get().get())) {
        inventory.setItem(slot, std::move(edited_item));
    }
}

template <>
void EndstonePacketHandler::handle(PlayerSkinPacket &packet)
{
    auto *player = getPlayer();
    if (player == nullptr) {
        return;
    }
    if (player->getPersistentComponent<UserEntityIdentifierComponent>()->getClientUUID() == packet.payload.uuid) {
        const auto endstone_player = player->getEndstoneActor<EndstonePlayer>();
        auto &server = static_cast<EndstoneServer &>(endstone_player->getServer());
        Message skin_change_message = Translatable(ColorFormat::Yellow + (packet.payload.skin.getIsPersona()
                                                                              ? "%multiplayer.player.changeToPersona"
                                                                              : "%multiplayer.player.changeToSkin"),
                                                   {endstone_player->getName()});
        PlayerSkinChangeEvent e{endstone_player, EndstoneSkin::fromMinecraft(packet.payload.skin), skin_change_message};
        server.getPluginManager().callEvent(e);
        if (e.isCancelled()) {
            auto new_packet = MinecraftPackets::createPacket(MinecraftPacketIds::PlayerSkin);
            auto &new_pk = static_cast<PlayerSkinPacket &>(*new_packet);
            new_pk.payload.uuid = packet.payload.uuid;
            new_pk.payload.skin = player->getSkin();
            new_pk.payload.localized_new_skin_name = packet.payload.localized_old_skin_name;
            new_pk.payload.localized_old_skin_name = packet.payload.localized_new_skin_name;
            player->sendNetworkPacket(new_pk);
            return;
        }

        skin_change_message = e.getSkinChangeMessage().value_or("");
        if (server.isServerTextEnabled(ServerTextEvent::PlayerChangedSkin) &&
            (!std::holds_alternative<std::string>(skin_change_message) ||
             !std::get<std::string>(skin_change_message).empty())) {
            server.broadcastMessage(skin_change_message);
        }
    }
    handle();
}

template <>
void EndstonePacketHandler::handle(SetLocalPlayerAsInitializedPacket & /*packet*/)
{
    const auto *player = getPlayer();
    if (player == nullptr) {
        return;
    }
    player->getEndstoneActor<EndstonePlayer>()->doFirstSpawn();
    handle();
}

template <>
void EndstonePacketHandler::handle(EmotePacket &packet)
{
    const auto *player = getPlayer();
    if (player == nullptr) {
        return;
    }
    if (packet.isServerSide()) {
        handle();
        return;
    }
    const auto endstone_player = player->getEndstoneActor<EndstonePlayer>();
    PlayerEmoteEvent e(endstone_player, packet.payload.piece_id, packet.isEmoteChatMuted());
    endstone_player->getServer().getPluginManager().callEvent(e);
    if (e.isCancelled()) {
        return;
    }
    if (e.isMuted()) {
        packet.payload.flags |= static_cast<uint8_t>(EmotePacket::Flags::MUTE_EMOTE_CHAT);
    }
    else {
        packet.payload.flags &= ~static_cast<uint8_t>(EmotePacket::Flags::MUTE_EMOTE_CHAT);
    }
    handle();
}

template <>
void EndstonePacketHandler::handle(SetPlayerInventoryOptionsPacket &packet)
{
    const auto *player = getPlayer();
    if (player == nullptr) {
        return;
    }
    const auto endstone_player = player->getEndstoneActor<EndstonePlayer>();
    const auto &options = packet.payload.inventory_options;
    const EndstonePlayer::RecipeBookSettings settings{
        .filtering = options.filtering,
        .inventory_layout = static_cast<int>(options.layout_inv),
        .crafting_layout = static_cast<int>(options.layout_craft),
    };
    const auto settings_changed =
        !endstone_player->last_recipe_book_settings_ || *endstone_player->last_recipe_book_settings_ != settings;
    endstone_player->last_recipe_book_settings_ = settings;
    if (!settings_changed) {
        handle();
        return;
    }

    const auto is_open =
        options.layout_inv == InventoryLayout::Default || options.layout_inv == InventoryLayout::RecipeBookOnly ||
        options.layout_craft == InventoryLayout::Default || options.layout_craft == InventoryLayout::RecipeBookOnly;

    PlayerRecipeBookSettingsChangeEvent e{
        endstone_player,
        PlayerRecipeBookSettingsChangeEvent::RecipeBookType::Crafting,
        is_open,
        options.filtering,
    };
    endstone_player->getServer().getPluginManager().callEvent(e);
    handle();
}

template <>
void EndstonePacketHandler::handle(PlayerAuthInputPacket &packet)
{
    auto *player = getPlayer();
    if (player == nullptr) {
        return;
    }
    const auto endstone_player = player->getEndstoneActor<EndstonePlayer>();
    auto &plugin_manager = endstone_player->getServer().getPluginManager();

    const Input player_input{
        packet.getInput(PlayerAuthInputPacket::InputData::Up),
        packet.getInput(PlayerAuthInputPacket::InputData::Down),
        packet.getInput(PlayerAuthInputPacket::InputData::Left),
        packet.getInput(PlayerAuthInputPacket::InputData::Right),
        packet.getInput(PlayerAuthInputPacket::InputData::Jumping),
        packet.getInput(PlayerAuthInputPacket::InputData::Sneaking),
        packet.getInput(PlayerAuthInputPacket::InputData::Sprinting),
    };
    const bool input_changed = endstone_player->last_input_ != player_input;
    endstone_player->last_input_ = player_input;

    if (packet.getInput(PlayerAuthInputPacket::InputData::StartSprinting) && !player->isSprinting()) {
        PlayerToggleSprintEvent e(endstone_player, true);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StopSprinting) && player->isSprinting()) {
        PlayerToggleSprintEvent e(endstone_player, false);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StartSneaking) && !player->isSneaking()) {
        PlayerToggleSneakEvent e(endstone_player, true);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StopSneaking) && player->isSneaking()) {
        PlayerToggleSneakEvent e(endstone_player, false);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::MissedSwing)) {
        PlayerInteractEvent e{
            endstone_player,
            PlayerInteractEvent::Action::LeftClickAir,
            endstone_player->getInventory().getItemInMainHand(),
            nullptr,
            BlockFace::South,
            std::nullopt,
        };
        plugin_manager.callEvent(e);
        if (e.isCancelled()) {
            packet.setInput(PlayerAuthInputPacket::InputData::MissedSwing, false);
        }
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StartSwimming) && !player->isSwimming()) {
        ActorToggleSwimEvent e(endstone_player, true);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StopSwimming) && player->isSwimming()) {
        ActorToggleSwimEvent e(endstone_player, false);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StartGliding) && !player->isGliding()) {
        ActorToggleGlideEvent e(endstone_player, true);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StopGliding) && player->isGliding()) {
        ActorToggleGlideEvent e(endstone_player, false);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StartCrawling) && !player->isCrawling()) {
        PlayerToggleCrawlEvent e(endstone_player, true);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StopCrawling) && player->isCrawling()) {
        PlayerToggleCrawlEvent e(endstone_player, false);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StartFlying) && endstone_player->getAllowFlight() &&
        !player->isFlying()) {
        PlayerToggleFlightEvent e(endstone_player, true);
        plugin_manager.callEvent(e);
    }
    if (packet.getInput(PlayerAuthInputPacket::InputData::StopFlying) && endstone_player->getAllowFlight() &&
        player->isFlying()) {
        PlayerToggleFlightEvent e(endstone_player, false);
        plugin_manager.callEvent(e);
    }
    if (input_changed) {
        PlayerInputEvent e(endstone_player, player_input);
        plugin_manager.callEvent(e);
    }

    auto &block_source = player->getDimension().getBlockSourceFromMainChunkSource();
    const auto prevent_unloaded_chunk_movement = EndstoneServer::getInstance().getConfig().getBool(
        "paper.world_defaults.chunks.prevent-moving-into-unloaded-chunks", false);

    auto &actions = packet.payload.player_block_actions.actions_;
    for (auto it = actions.begin(); it != actions.end();) {
        const auto &action = *it;
        if (prevent_unloaded_chunk_movement && !block_source.hasChunk(ChunkPos(action.pos), false)) {
            it = actions.erase(it);
            continue;
        }
        if (action.player_action_type == PlayerActionType::StartDestroyBlock) {
            const auto item = endstone_player->getInventory().getItemInMainHand();
            const auto block = endstone_player->getDimension()->getBlockAt(action.pos.x, action.pos.y, action.pos.z);
            PlayerInteractEvent e{
                endstone_player,
                PlayerInteractEvent::Action::LeftClickBlock,
                item,
                block,
                static_cast<BlockFace>(action.facing),
                Vector{action.pos.x, action.pos.y, action.pos.z},
            };
            plugin_manager.callEvent(e);
            if (e.isCancelled()) {
                it = actions.erase(it);
                continue;
            }
        }
        ++it;
    }

    const auto pos = player->getPosition();
    const auto rot = player->getRotation();
    const auto &input = packet.payload;
    const auto delta = input.pos - pos;
    const auto delta_angle = input.rot - rot;
    const auto on_ground = player->isOnGround();

    if (prevent_unloaded_chunk_movement && (delta.x != 0.0F || delta.z != 0.0F)) {
        const auto &aabb = player->getAABB();
        const AABB moved_aabb{aabb.min.x + delta.x, aabb.min.y + delta.y, aabb.min.z + delta.z,
                              aabb.max.x + delta.x, aabb.max.y + delta.y, aabb.max.z + delta.z};
        if (!block_source.hasChunksAt(moved_aabb, false)) {
            auto correction = MinecraftPackets::createPacket(MinecraftPacketIds::CorrectPlayerMovePredictionPacket);
            auto &payload = static_cast<CorrectPlayerMovePredictionPacket &>(*correction).payload;
            payload.pos = pos;
            payload.pos_delta = Vec3::ZERO;
            payload.vehicle_rotation = Vec2::ZERO;
            payload.vehicle_angular_velocity = std::nullopt;
            payload.tick = input.client_tick;
            payload.on_ground = on_ground;
            payload.prediction_type = RewindType::Player;
            player->sendNetworkPacket(*correction);
            return;
        }
    }

    const Location from = endstone_player->getLocation();
    const auto height_offset = ActorOffset::getHeightOffset(player->getEntity());
    const Location to{endstone_player->getDimension(),
                      input.pos.x,
                      input.pos.y - height_offset,
                      input.pos.z,
                      input.rot.x,
                      input.rot.y};

    if (packet.getInput(PlayerAuthInputPacket::InputData::Jumping) && on_ground && delta.y > 0.0F) {
        PlayerJumpEvent e{endstone_player, from, to};
        plugin_manager.callEvent(e);
        if (e.isCancelled()) {
            player->addOrRemoveComponent<InternalTeleportFlagComponent>(true);
            endstone_player->teleport(from);
            return;
        }
    }

    // Prevent intensive event calls on tiny movement using the thresholds from Spigot
    if (delta.lengthSquared() > 1.0F / 256 || delta_angle.lengthSquared() > 10.0F) {
        PlayerMoveEvent e{endstone_player, from, to};
        plugin_manager.callEvent(e);
        if (e.isCancelled()) {
            if (delta_angle.lengthSquared() > 0.0F) {
                player->addOrRemoveComponent<InternalTeleportFlagComponent>(true);
                endstone_player->teleport(from);
            }
            else {
                auto correction = MinecraftPackets::createPacket(MinecraftPacketIds::CorrectPlayerMovePredictionPacket);
                auto &payload = static_cast<CorrectPlayerMovePredictionPacket &>(*correction).payload;
                payload.pos = pos;
                payload.pos_delta = Vec3::ZERO;
                payload.vehicle_rotation = Vec2::ZERO;
                payload.vehicle_angular_velocity = std::nullopt;
                payload.tick = input.client_tick;
                payload.on_ground = on_ground;
                payload.prediction_type = RewindType::Player;
                player->sendNetworkPacket(*correction);
            }
            return;
        }
        if (to != e.getTo()) {
            player->addOrRemoveComponent<InternalTeleportFlagComponent>(true);
            endstone_player->teleport(e.getTo());
            return;
        }
    }
    handle();
}

namespace {

class EndstonePacketRateLimitDispatcher : public IPacketHandlerDispatcher {
public:
    static void set(const IPacketHandlerDispatcher **handler)
    {
        if (*handler == nullptr) {
            return;
        }
        const auto *original = *handler;
        static std::mutex dispatchers_mutex;
        static std::unordered_map<const IPacketHandlerDispatcher *, std::unique_ptr<EndstonePacketRateLimitDispatcher>>
            dispatchers;
        std::lock_guard lock(dispatchers_mutex);
        auto [it, inserted] = dispatchers.try_emplace(original);
        if (inserted) {
            it->second =
                std::unique_ptr<EndstonePacketRateLimitDispatcher>(new EndstonePacketRateLimitDispatcher{*original});
        }
        *handler = it->second.get();
    }

    void handle(const NetworkIdentifier &network_id, NetEventCallback &callback,
                std::shared_ptr<Packet> &packet) const override
    {
        if (allowIncomingPacket(EndstoneServer::getInstance(), network_id, *packet)) {
            original_.handle(network_id, callback, packet);
        }
    }

private:
    explicit EndstonePacketRateLimitDispatcher(const IPacketHandlerDispatcher &original) : original_(original) {}

    const IPacketHandlerDispatcher &original_;
};

template <typename T>
class EndstonePacketHandlerDispatcher : public IPacketHandlerDispatcher {
public:
    static void set(const IPacketHandlerDispatcher **handler)
    {
        if (*handler == nullptr) {
            return;
        }
        static EndstonePacketHandlerDispatcher dispatcher{**handler};
        *handler = &dispatcher;
    }

    void handle(const NetworkIdentifier &network_id, NetEventCallback &callback,
                std::shared_ptr<Packet> &packet) const override
    {
        if (!allowIncomingPacket(EndstoneServer::getInstance(), network_id, *packet)) {
            return;
        }
        EndstonePacketHandler handler{network_id, callback, original_, packet};
        handler.handle(static_cast<T &>(*packet));
    }

private:
    explicit EndstonePacketHandlerDispatcher(const IPacketHandlerDispatcher &original) : original_(original) {}

    const IPacketHandlerDispatcher &original_;
};
}  // namespace

}  // namespace endstone::core

std::shared_ptr<Packet> MinecraftPackets::createPacket(MinecraftPacketIds id)
{
    using endstone::core::EndstonePacketHandlerDispatcher;
    using endstone::core::EndstonePacketRateLimitDispatcher;
    auto packet = ENDSTONE_HOOK_CALL_ORIGINAL(&MinecraftPackets::createPacket, id);
    switch (id) {
    case MinecraftPacketIds::PlayerEquipment: {
        using Dispatcher = EndstonePacketHandlerDispatcher<MobEquipmentPacket>;
        Dispatcher::set(&packet->handler_);
        break;
    }
    case MinecraftPacketIds::BookEdit: {
        using Dispatcher = EndstonePacketHandlerDispatcher<BookEditPacket>;
        Dispatcher::set(&packet->handler_);
        break;
    }
    case MinecraftPacketIds::PlayerSkin: {
        using Dispatcher = EndstonePacketHandlerDispatcher<PlayerSkinPacket>;
        Dispatcher::set(&packet->handler_);
        break;
    }
    case MinecraftPacketIds::SetLocalPlayerAsInit: {
        using Dispatcher = EndstonePacketHandlerDispatcher<SetLocalPlayerAsInitializedPacket>;
        Dispatcher::set(&packet->handler_);
        break;
    }
    case MinecraftPacketIds::PlayerAuthInputPacket: {
        using Dispatcher = EndstonePacketHandlerDispatcher<PlayerAuthInputPacket>;
        Dispatcher::set(&packet->handler_);
        break;
    }
    case MinecraftPacketIds::Emote: {
        using Dispatcher = EndstonePacketHandlerDispatcher<EmotePacket>;
        Dispatcher::set(&packet->handler_);
        break;
    }
    case MinecraftPacketIds::SetPlayerInventoryOptions: {
        using Dispatcher = EndstonePacketHandlerDispatcher<SetPlayerInventoryOptionsPacket>;
        Dispatcher::set(&packet->handler_);
        break;
    }
    default:
        EndstonePacketRateLimitDispatcher::set(&packet->handler_);
        break;
    }
    return packet;
}
