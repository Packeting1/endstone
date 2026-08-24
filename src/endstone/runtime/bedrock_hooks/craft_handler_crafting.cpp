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

#include "bedrock/world/inventory/network/crafting/craft_handler_crafting.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "bedrock/world/actor/player/player.h"
#include "bedrock/world/inventory/network/crafting/item_stack_request_action_craft.h"
#include "bedrock/world/inventory/network/crafting/item_stack_request_action_craft_handler.h"
#include "bedrock/world/item/crafting/recipes.h"
#include "bedrock/world/level/level.h"
#include "endstone/core/inventory/item_stack.h"
#include "endstone/core/player.h"
#include "endstone/core/server.h"
#include "endstone/event/player/player_craft_item_event.h"
#include "endstone/runtime/hook.h"

struct RecipeSpamState {
    bool initialized = false;
    std::uint64_t last_tick = 0;
    std::int64_t count = 0;
};

static std::mutex recipe_spam_mutex;
static std::unordered_map<std::uint64_t, RecipeSpamState> recipe_spam_states;

static bool allowRecipe(const endstone::core::EndstoneServer &server, Player &player)
{
    const auto increment = server.getConfig().getInt("paper.global.spam-limiter.recipe-spam-increment", 1);
    const auto threshold = server.getConfig().getInt("paper.global.spam-limiter.recipe-spam-limit", 20);
    if (increment <= 0 || threshold <= 0) {
        return true;
    }

    const auto tick = player.getLevel().getCurrentServerTick().tick_id;
    std::lock_guard lock(recipe_spam_mutex);
    auto &state = recipe_spam_states[player.getRuntimeID().raw_id];
    if (!state.initialized || tick < state.last_tick) {
        state.initialized = true;
        state.last_tick = tick;
        state.count = 0;
    }
    else if (tick > state.last_tick) {
        const auto decay = std::min<std::uint64_t>(tick - state.last_tick, static_cast<std::uint64_t>(state.count));
        state.count -= static_cast<std::int64_t>(decay);
        state.last_tick = tick;
    }

    state.count += increment;
    return state.count < threshold;
}

ItemStackNetResult CraftHandlerCrafting::_handleCraftAction(const ItemStackRequestActionCraftBase &request_action)
{
    const auto &server = endstone::core::EndstoneServer::getInstance();
    const auto action_type = request_action.getActionType();
    if ((action_type == ItemStackRequestActionType::CraftRecipe ||
         action_type == ItemStackRequestActionType::CraftRecipeAuto) &&
        !allowRecipe(server, player_)) {
        player_.getEndstoneActor<endstone::core::EndstonePlayer>()->kick("disconnect.spam");
        return ItemStackNetResult::ActionRequestNotAllowed;
    }
    if (!server.getEndstonePluginManager().isEventRegistered<endstone::PlayerCraftItemEvent>()) {
        return ENDSTONE_HOOK_CALL_ORIGINAL(&CraftHandlerCrafting::_handleCraftAction, this, request_action);
    }

    std::vector<endstone::ItemStack> ingredients;
    const Recipe *recipe = nullptr;

    switch (request_action.getActionType()) {
    case ItemStackRequestActionType::CraftRecipe: {
        const auto &net_id = static_cast<const ItemStackRequestActionCraftRecipe &>(request_action).getRecipeNetId();
        recipe = player_.getLevel().getRecipes().getRecipeByNetId(net_id);
        if (recipe == nullptr) {
            break;
        }

        const auto first_slot = 28 + workbench_ * 4;
        const auto slot_count = workbench_ * 5 + 4;
        const auto &player_ui = player_.getPlayerUIContainer();
        for (auto i = 0; i < slot_count; ++i) {
            const auto &item = player_ui.getItem(first_slot + i);
            if (!item.isNull()) {
                ingredients.push_back(endstone::core::EndstoneItemStack::fromMinecraft(item));
            }
        }
        break;
    }
    case ItemStackRequestActionType::CraftRecipeAuto: {
        const auto &net_id =
            static_cast<const ItemStackRequestActionCraftRecipeAuto &>(request_action).getRecipeNetId();
        recipe = player_.getLevel().getRecipes().getRecipeByNetId(net_id);
        if (recipe == nullptr) {
            break;
        }

        for (auto y = 0; y < recipe->getHeight(); ++y) {
            for (auto x = 0; x < recipe->getWidth(); ++x) {
                const auto &ingredient = recipe->getIngredient(x, y);
                const auto *item = ingredient.getItem();
                if (item == nullptr || ingredient.getStackSize() == 0) {
                    continue;
                }
                ingredients.push_back(endstone::core::EndstoneItemStack::fromMinecraft(
                    ItemStack(*item, ingredient.getStackSize(), ingredient.getAuxValue())));
            }
        }
        break;
    }
    default:
        break;
    }

    if (recipe == nullptr) {
        return ENDSTONE_HOOK_CALL_ORIGINAL(&CraftHandlerCrafting::_handleCraftAction, this, request_action);
    }

    std::vector<endstone::ItemStack> results;
    results.reserve(recipe->getResultItems().size());
    for (const auto &result : recipe->getResultItems()) {
        results.push_back(endstone::core::EndstoneItemStack::fromMinecraft(ItemStack(result)));
    }

    endstone::PlayerCraftItemEvent e{player_.getEndstoneActor<endstone::core::EndstonePlayer>(), std::move(ingredients),
                                     results, request_action.getNumCrafts()};
    server.getPluginManager().callEvent(e);
    if (e.isCancelled()) {
        return ItemStackNetResult::ActionRequestNotAllowed;
    }
    const_cast<ItemStackRequestActionCraftBase &>(request_action)
        .setNumCrafts(static_cast<std::uint8_t>(std::clamp(e.getRepetitions(), 0, 255)));

    const auto result = ENDSTONE_HOOK_CALL_ORIGINAL(&CraftHandlerCrafting::_handleCraftAction, this, request_action);
    if (result == ItemStackNetResult::Success && e.getResults() != results) {
        auto &craft_results = craft_request_handler_.getCraftResults();
        const auto replaced = std::min(e.getResults().size(), craft_results.size());
        for (std::size_t i = 0; i < replaced; ++i) {
            craft_results[i].first = ItemInstance(endstone::core::EndstoneItemStack::toMinecraft(e.getResults()[i]));
        }
    }
    return result;
}
