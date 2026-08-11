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

#pragma once

#include <optional>
#include <vector>

#include "endstone/event/inventory/slot_type.h"
#include "endstone/inventory/item_stack.h"
#include "endstone/util/pointers.h"

namespace endstone {

class Inventory;
class Player;

/**
 * Represents a player's view of an open container screen.
 */
class InventoryView {
public:
    static constexpr int OUTSIDE = -999;

    virtual ~InventoryView() = default;

    /**
     * Gets the upper inventory involved in this view.
     *
     * @return the upper inventory
     */
    [[nodiscard]] virtual Inventory &getTopInventory() const = 0;

    /**
     * Gets the lower inventory involved in this view.
     *
     * @return the lower inventory
     */
    [[nodiscard]] virtual Inventory &getBottomInventory() const = 0;

    /**
     * Gets the player viewing the inventory.
     *
     * @return the viewing player
     */
    [[nodiscard]] virtual const NotNull<Player> &getPlayer() const = 0;

    /** Sets one item in this view by its raw slot index. */
    virtual void setItem(int raw_slot, std::optional<ItemStack> item) = 0;

    /** Gets one item in this view by its raw slot index. */
    [[nodiscard]] virtual std::optional<ItemStack> getItem(int raw_slot) const = 0;

    /** Sets the item held on the viewing player's cursor. */
    virtual void setCursor(std::optional<ItemStack> item) = 0;

    /** Gets the item held on the viewing player's cursor. */
    [[nodiscard]] virtual std::optional<ItemStack> getCursor() const = 0;

    /** Gets the inventory corresponding to a raw slot index, or `nullptr` if outside. */
    [[nodiscard]] virtual Inventory *getInventory(int raw_slot) const = 0;

    /** Converts a raw slot index to its local inventory slot index. */
    [[nodiscard]] virtual int convertSlot(int raw_slot) const = 0;

    /** Gets the logical type of a raw slot. */
    [[nodiscard]] virtual SlotType getSlotType(int raw_slot) const = 0;

    /** Gets the total number of slots in this view. */
    [[nodiscard]] virtual int countSlots() const = 0;

    /**
     * Gets the players viewing this inventory.
     *
     * @return the viewers
     */
    [[nodiscard]] virtual std::vector<NotNull<Player>> getViewers() const = 0;
};

}  // namespace endstone
