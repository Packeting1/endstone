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
#include <utility>

#include "endstone/event/inventory/inventory_action.h"
#include "endstone/event/inventory/inventory_interact_event.h"
#include "endstone/event/inventory/slot_type.h"
#include "endstone/inventory/item_stack.h"

namespace endstone {

/** Called when a player clicks in an inventory. */
class InventoryClickEvent final : public InventoryInteractEvent {
public:
    ENDSTONE_EVENT(InventoryClickEvent)

    InventoryClickEvent(const NotNull<InventoryView> &view, SlotType slot_type, int raw_slot, InventoryAction action,
                        int hotbar_button = -1,
                        std::optional<ItemStack> current_item = std::nullopt)
        : InventoryInteractEvent(view),
          slot_type_(slot_type),
          raw_slot_(raw_slot),
          action_(action),
          hotbar_button_(hotbar_button),
          current_item_(std::move(current_item))
    {
    }

    /** Gets the type of the clicked slot. */
    [[nodiscard]] SlotType getSlotType() const { return slot_type_; }

    /** Gets the item currently held on the cursor. */
    [[nodiscard]] std::optional<ItemStack> getCursor() const { return getView()->getCursor(); }

    /** Gets the item currently in the clicked slot. */
    [[nodiscard]] std::optional<ItemStack> getCurrentItem() const
    {
        if (slot_type_ == SlotType::Outside || current_item_) {
            return current_item_;
        }
        return getView()->getItem(raw_slot_);
    }

    /** Sets the item currently held on the cursor. */
    void setCursor(std::optional<ItemStack> item) { getView()->setCursor(std::move(item)); }

    /** Sets the item currently in the clicked slot. */
    void setCurrentItem(std::optional<ItemStack> item)
    {
        current_item_ = item;
        if (slot_type_ == SlotType::Outside) {
            return;
        }
        getView()->setItem(raw_slot_, std::move(item));
    }

    /** Gets the inventory corresponding to the clicked slot, or `nullptr` if outside. */
    [[nodiscard]] Inventory *getClickedInventory() const { return getView()->getInventory(raw_slot_); }

    /** Gets the slot index in its corresponding inventory. */
    [[nodiscard]] int getSlot() const { return getView()->convertSlot(raw_slot_); }

    /** Gets the raw slot index in this view. */
    [[nodiscard]] int getRawSlot() const { return raw_slot_; }

    /** Gets the hotbar key index, or -1 when this is not a number-key click. */
    [[nodiscard]] int getHotbarButton() const { return hotbar_button_; }

    /** Gets the estimated inventory operation. */
    [[nodiscard]] InventoryAction getAction() const { return action_; }

private:
    SlotType slot_type_;
    int raw_slot_;
    InventoryAction action_;
    int hotbar_button_;
    std::optional<ItemStack> current_item_;
};

}  // namespace endstone
