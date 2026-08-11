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

#include <cstdint>
#include <memory>
#include <optional>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include "bedrock/bedrock.h"
#include "bedrock/world/containers/container_enum.h"
#include "bedrock/world/inventory/network/item_stack_net_result.h"
#include "bedrock/world/inventory/network/item_stack_request_action.h"
#include "bedrock/world/inventory/network/item_stack_request_action_type.h"
#include "bedrock/world/level/block/actor/block_actor.h"
#include "endstone/core/inventory/inventory.h"
#include "endstone/core/inventory/inventory_view.h"
#include "endstone/core/inventory/item_stack.h"
#include "endstone/core/player.h"
#include "endstone/core/server.h"
#include "endstone/event/inventory/inventory_click_event.h"
#include "endstone/runtime/hook.h"

namespace {

using endstone::InventoryAction;
using endstone::InventoryView;
using endstone::SlotType;
using endstone::core::EndstoneInventoryView;
using endstone::core::EndstonePlayer;

bool isPlayerContainer(ContainerEnumName name);
SlotType getTopSlotType(ContainerEnumName name);

Container *getOpenContainer(Player &player, const EndstonePlayer::OpenContainer &open_container)
{
#ifdef _WIN32
    if (const auto *entity_id = std::get_if<ActorUniqueID>(&open_container.owner)) {
        using Resolver = Container *(*)(Player &, const ActorUniqueID &);
        constexpr auto symbol = "LevelContainerManagerModel::_getRawContainerForEntity";
        const auto resolver = endstone::detail::fp_cast(
            static_cast<Resolver>(nullptr),
            static_cast<char *>(endstone::runtime::get_executable_base()) + endstone::runtime::get_symbol(symbol));
        return resolver(player, *entity_id);
    }

    const auto &position = std::get<BlockPos>(open_container.owner);
    const auto *block_actor = player.getDimensionBlockSource().getBlockEntity(position);
    if (block_actor == nullptr) {
        return nullptr;
    }

    using Resolver = Container *(*)(Player &, BlockActorType, const BlockPos &);
    constexpr auto symbol = "LevelContainerManagerModel::_getRawContainerForBlock";
    const auto resolver = endstone::detail::fp_cast(
        static_cast<Resolver>(nullptr),
        static_cast<char *>(endstone::runtime::get_executable_base()) + endstone::runtime::get_symbol(symbol));
    return resolver(player, block_actor->getType(), position);
#else
    using Resolver = Container *(*)(ContainerManagerModel *);
    constexpr auto symbol = "_ZN26LevelContainerManagerModel16_getRawContainerEv";
    const auto resolver = endstone::detail::fp_cast(
        static_cast<Resolver>(nullptr),
        static_cast<char *>(endstone::runtime::get_executable_base()) + endstone::runtime::get_symbol(symbol));
    auto *manager = player.getContainerManager();
    return manager ? resolver(manager) : nullptr;
#endif
}

struct ViewContext {
    std::shared_ptr<EndstoneInventoryView> view;
    int top_slot_count;
};

ViewContext makeView(Player &player, const std::shared_ptr<EndstonePlayer> &endstone_player,
                     const ItemStackRequestActionTransferBase *request_action = nullptr)
{
    auto bottom = endstone::NotNull<endstone::Inventory>{
        std::shared_ptr<endstone::Inventory>{endstone_player, &endstone_player->getInventory()}};
    auto top = bottom;
    const auto &open_container = endstone_player->getOpenContainer();
    auto top_slot_count = 0;
    if (open_container) {
        auto *container = getOpenContainer(player, *open_container);
        if (container == nullptr) {
            return {};
        }
        top = endstone::NotNull<endstone::Inventory>{std::make_shared<endstone::core::EndstoneInventory>(*container)};
        top_slot_count = top->getSize();
    }

    std::vector<SlotType> top_slot_types(top_slot_count, SlotType::Container);
    if (request_action != nullptr) {
        const auto add_slot_type = [&](const ItemStackRequestSlotInfo &slot) {
            const auto &container = slot.container_name_;
            const auto index = slot.slot_;
            if (!isPlayerContainer(container.name) && index < top_slot_count) {
                top_slot_types[index] = getTopSlotType(container.name);
            }
        };
        add_slot_type(request_action->source_);
        add_slot_type(request_action->destination_);
    }
    return {std::make_shared<EndstoneInventoryView>(endstone_player, top, bottom, open_container, top_slot_count,
                                                    std::move(top_slot_types)),
            top_slot_count};
}

bool isPlayerContainer(ContainerEnumName name)
{
    switch (name) {
    case ContainerEnumName::HotbarContainer:
    case ContainerEnumName::InventoryContainer:
    case ContainerEnumName::CombinedHotbarAndInventoryContainer:
    case ContainerEnumName::ArmorContainer:
    case ContainerEnumName::OffhandContainer:
    case ContainerEnumName::CursorContainer:
        return true;
    default:
        return false;
    }
}

SlotType getTopSlotType(ContainerEnumName name)
{
    switch (name) {
    case ContainerEnumName::AnvilResultPreviewContainer:
    case ContainerEnumName::SmithingTableResultPreviewContainer:
    case ContainerEnumName::CraftingOutputPreviewContainer:
    case ContainerEnumName::FurnaceResultContainer:
    case ContainerEnumName::BrewingStandResultContainer:
    case ContainerEnumName::TradeResultPreviewContainer:
    case ContainerEnumName::Trade2ResultPreviewContainer:
    case ContainerEnumName::LoomResultPreviewContainer:
    case ContainerEnumName::GrindstoneResultPreviewContainer:
    case ContainerEnumName::StonecutterResultPreviewContainer:
    case ContainerEnumName::CartographyResultPreviewContainer:
    case ContainerEnumName::CreatedOutputContainer:
    case ContainerEnumName::CompoundCreatorOutputPreview:
    case ContainerEnumName::ElementConstructorOutputPreview:
    case ContainerEnumName::MaterialReducerOutput:
        return SlotType::Result;
    case ContainerEnumName::FurnaceFuelContainer:
    case ContainerEnumName::BrewingStandFuelContainer:
        return SlotType::Fuel;
    case ContainerEnumName::AnvilInputContainer:
    case ContainerEnumName::AnvilMaterialContainer:
    case ContainerEnumName::SmithingTableInputContainer:
    case ContainerEnumName::SmithingTableMaterialContainer:
    case ContainerEnumName::SmithingTableTemplateContainer:
    case ContainerEnumName::CraftingInputContainer:
    case ContainerEnumName::RecipeConstructionContainer:
    case ContainerEnumName::RecipeNatureContainer:
    case ContainerEnumName::RecipeItemsContainer:
    case ContainerEnumName::RecipeEquipmentContainer:
    case ContainerEnumName::EnchantingInputContainer:
    case ContainerEnumName::EnchantingMaterialContainer:
    case ContainerEnumName::FurnaceIngredientContainer:
    case ContainerEnumName::BlastFurnaceIngredientContainer:
    case ContainerEnumName::SmokerIngredientContainer:
    case ContainerEnumName::TradeIngredient1Container:
    case ContainerEnumName::TradeIngredient2Container:
    case ContainerEnumName::Trade2Ingredient1Container:
    case ContainerEnumName::Trade2Ingredient2Container:
    case ContainerEnumName::GrindstoneInputContainer:
    case ContainerEnumName::GrindstoneAdditionalContainer:
    case ContainerEnumName::StonecutterInputContainer:
    case ContainerEnumName::CartographyInputContainer:
    case ContainerEnumName::CartographyAdditionalContainer:
    case ContainerEnumName::LoomInputContainer:
    case ContainerEnumName::LoomDyeContainer:
    case ContainerEnumName::LoomMaterialContainer:
    case ContainerEnumName::CompoundCreatorInput:
    case ContainerEnumName::MaterialReducerInput:
    case ContainerEnumName::LabTableInput:
        return SlotType::Crafting;
    default:
        return SlotType::Container;
    }
}

struct SlotInfo {
    int raw_slot;
    SlotType slot_type;
};

SlotInfo getSlotInfo(const FullContainerName &container, int slot, int top_slot_count)
{
    switch (container.name) {
    case ContainerEnumName::CursorContainer:
        return {InventoryView::OUTSIDE, SlotType::Outside};
    case ContainerEnumName::HotbarContainer:
        return {top_slot_count + slot, SlotType::Quickbar};
    case ContainerEnumName::InventoryContainer:
        return {top_slot_count + 9 + slot, SlotType::Container};
    case ContainerEnumName::CombinedHotbarAndInventoryContainer:
        return {top_slot_count + slot, slot < 9 ? SlotType::Quickbar : SlotType::Container};
    case ContainerEnumName::ArmorContainer:
        return {top_slot_count + 36 + slot, SlotType::Armor};
    case ContainerEnumName::OffhandContainer:
        return {top_slot_count + 40, SlotType::Container};
    default:
        return {slot, getTopSlotType(container.name)};
    }
}

bool isCursorContainer(const FullContainerName &container)
{
    return container.name == ContainerEnumName::CursorContainer;
}

bool isSameContainer(const FullContainerName &left, const FullContainerName &right)
{
    return left.name == right.name && left.dynamic_id == right.dynamic_id;
}

bool isDirectTransfer(ItemStackRequestActionType type, const FullContainerName &source, int source_slot,
                      const FullContainerName &destination, int destination_slot)
{
    return (type == ItemStackRequestActionType::Take || type == ItemStackRequestActionType::Place) &&
           !isCursorContainer(source) && !isCursorContainer(destination) &&
           (!isSameContainer(source, destination) || source_slot != destination_slot);
}

struct DirectTransferState {
    FullContainerName source;
    int source_slot;
    std::optional<endstone::ItemStack> item;
};

std::unordered_map<ItemStackRequestActionHandler *, DirectTransferState> direct_transfer_states;

std::optional<endstone::ItemStack> getSlotItem(const EndstoneInventoryView &view, const SlotInfo &slot)
{
    return slot.slot_type == SlotType::Outside ? view.getCursor() : view.getItem(slot.raw_slot);
}

InventoryAction getTransferAction(ItemStackRequestActionType type, const std::optional<endstone::ItemStack> &current,
                                  const std::optional<endstone::ItemStack> &cursor, std::uint8_t amount,
                                  const FullContainerName &source, int source_slot, const FullContainerName &destination,
                                  int destination_slot)
{
    if (isDirectTransfer(type, source, source_slot, destination, destination_slot)) {
        return InventoryAction::MoveToOtherInventory;
    }

    switch (type) {
    case ItemStackRequestActionType::Take:
        if (amount == 0) {
            return InventoryAction::Nothing;
        }
        if (!current) {
            return InventoryAction::Nothing;
        }
        if (amount >= current->getAmount()) {
            return InventoryAction::PickupAll;
        }
        if (amount == 1) {
            return InventoryAction::PickupOne;
        }
        if (amount == (current->getAmount() + 1) / 2) {
            return InventoryAction::PickupHalf;
        }
        return InventoryAction::PickupSome;
    case ItemStackRequestActionType::Place:
        if (amount == 0) {
            return InventoryAction::Nothing;
        }
        if (!cursor) {
            return InventoryAction::Nothing;
        }
        if (amount >= cursor->getAmount()) {
            return InventoryAction::PlaceAll;
        }
        if (amount == 1) {
            return InventoryAction::PlaceOne;
        }
        return InventoryAction::PlaceSome;
    case ItemStackRequestActionType::Swap:
        if (source.name == ContainerEnumName::CursorContainer ||
            destination.name == ContainerEnumName::CursorContainer) {
            return InventoryAction::SwapWithCursor;
        }
        if (source.name == ContainerEnumName::HotbarContainer ||
            destination.name == ContainerEnumName::HotbarContainer ||
            source.name == ContainerEnumName::OffhandContainer ||
            destination.name == ContainerEnumName::OffhandContainer) {
            return InventoryAction::HotbarSwap;
        }
        return InventoryAction::Unknown;
    default:
        return InventoryAction::Unknown;
    }
}

template <typename CallOriginal>
ItemStackNetResult dispatchRemove(ItemStackRequestActionHandler &handler,
                                  const ItemStackRequestActionTransferBase &request_action, ::ItemStack &removed_item,
                                  int remove_type, CallOriginal &&call_original)
{
    if (remove_type < 0 || remove_type > 3) {
        return call_original();
    }

    auto endstone_player = handler.getPlayer().getEndstoneActorPtr<EndstonePlayer>();
    auto context = makeView(handler.getPlayer(), endstone_player, &request_action);
    if (!context.view) {
        return call_original();
    }

    const auto slot =
        getSlotInfo(request_action.source_.container_name_, request_action.source_.slot_, context.top_slot_count);
    const auto current_item = getSlotItem(*context.view, slot);
    auto action = InventoryAction::Unknown;
    if (remove_type <= 1) {
        const auto amount = request_action.amount_ != 0 ? request_action.amount_ : removed_item.getCount();
        const auto all = current_item && amount >= current_item->getAmount();
        if (slot.slot_type == SlotType::Outside) {
            action = all ? InventoryAction::DropAllCursor : InventoryAction::DropOneCursor;
        }
        else {
            action = all ? InventoryAction::DropAllSlot : InventoryAction::DropOneSlot;
        }
    }

    std::optional<endstone::ItemStack> outside_item;
    if (slot.slot_type == SlotType::Outside) {
        outside_item = current_item;
    }
    endstone::InventoryClickEvent event{endstone::NotNull<endstone::InventoryView>{context.view},
                                        slot.slot_type,
                                        slot.raw_slot,
                                        action,
                                        -1,
                                        std::move(outside_item)};
    endstone::core::EndstoneServer::getInstance().getPluginManager().callEvent(event);
    if (event.isCancelled()) {
        return ItemStackNetResult::Error;
    }
    return call_original();
}

}  // namespace

ItemStackNetResult ItemStackRequestActionHandler::_handleTransfer(
    const ItemStackRequestActionTransferBase &request_action, bool is_src_hint_slot, bool is_dst_hint_slot,
    bool is_swap)
{
    constexpr auto symbol = __FUNCDNAME__;
    const auto call_original = [&] {
        return ENDSTONE_HOOK_CALL_ORIGINAL_NAME(&ItemStackRequestActionHandler::_handleTransfer, symbol, this,
                                                request_action, is_src_hint_slot, is_dst_hint_slot, is_swap);
    };

    const auto type = request_action.type_;
    if (type != ItemStackRequestActionType::Take && type != ItemStackRequestActionType::Place &&
        type != ItemStackRequestActionType::Swap) {
        return call_original();
    }

    auto endstone_player = getPlayer().getEndstoneActorPtr<EndstonePlayer>();
    auto context = makeView(getPlayer(), endstone_player, &request_action);
    if (!context.view) {
        return call_original();
    }

    const auto source =
        getSlotInfo(request_action.source_.container_name_, request_action.source_.slot_, context.top_slot_count);
    const auto destination = getSlotInfo(request_action.destination_.container_name_, request_action.destination_.slot_,
                                         context.top_slot_count);
    const auto clicked = isCursorContainer(request_action.source_.container_name_) ? destination : source;
    const auto current_item = getSlotItem(*context.view, clicked);
    const auto cursor = context.view->getCursor();
    const auto action =
        getTransferAction(type, current_item, cursor, request_action.amount_, request_action.source_.container_name_,
                          request_action.source_.slot_, request_action.destination_.container_name_,
                          request_action.destination_.slot_);
    const auto direct_transfer = isDirectTransfer(type, request_action.source_.container_name_,
                                                  request_action.source_.slot_,
                                                  request_action.destination_.container_name_,
                                                  request_action.destination_.slot_);
    if (direct_transfer) {
        const auto state = direct_transfer_states.find(this);
        const auto repeated = state != direct_transfer_states.end() &&
                              isSameContainer(state->second.source, request_action.source_.container_name_) &&
                              state->second.source_slot == request_action.source_.slot_ &&
                              (!state->second.item || !current_item || state->second.item == current_item);
        if (repeated) {
            return call_original();
        }
        direct_transfer_states.insert_or_assign(this,
                                                DirectTransferState{request_action.source_.container_name_,
                                                                    request_action.source_.slot_, current_item});
    }
    else {
        direct_transfer_states.erase(this);
    }

    endstone::InventoryClickEvent event{endstone::NotNull<endstone::InventoryView>{context.view},
                                        clicked.slot_type,
                                        clicked.raw_slot,
                                        action,
                                        -1,
                                        current_item};
    endstone::core::EndstoneServer::getInstance().getPluginManager().callEvent(event);
    if (event.isCancelled()) {
        direct_transfer_states.erase(this);
        return ItemStackNetResult::Error;
    }
    return call_original();
}

extern "C" ENDSTONE_HOOK ItemStackNetResult endstone_inventory_remove(
    ItemStackRequestActionHandler *handler, const ItemStackRequestActionTransferBase &request_action,
    ::ItemStack &removed_item, int remove_type)
{
    const auto call_original = [&] {
        return ENDSTONE_HOOK_CALL_ORIGINAL_NAME(&endstone_inventory_remove, "endstone_inventory_remove", handler,
                                                request_action, removed_item, remove_type);
    };
    return dispatchRemove(*handler, request_action, removed_item, remove_type, call_original);
}
