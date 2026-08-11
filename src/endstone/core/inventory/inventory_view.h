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
#include <vector>

#include "endstone/core/inventory/inventory.h"
#include "endstone/core/player.h"
#include "endstone/inventory/inventory_view.h"
#include "endstone/util/pointers.h"

namespace endstone::core {

class EndstoneInventoryView final : public InventoryView {
public:
    EndstoneInventoryView(NotNull<Player> player, NotNull<Inventory> top, NotNull<Inventory> bottom,
                          std::optional<EndstonePlayer::OpenContainer> open_container,
                          int top_slot_count = -1, std::vector<SlotType> top_slot_types = {})
        : player_(std::move(player)), top_(std::move(top)), bottom_(std::move(bottom)),
          open_container_(std::move(open_container)),
          top_slot_count_(top_slot_count < 0 ? top_->getSize() : top_slot_count),
          top_slot_types_(std::move(top_slot_types))
    {
    }

    [[nodiscard]] Inventory &getTopInventory() const override { return *top_; }
    [[nodiscard]] Inventory &getBottomInventory() const override { return *bottom_; }
    [[nodiscard]] const NotNull<Player> &getPlayer() const override { return player_; }
    void setItem(int raw_slot, std::optional<ItemStack> item) override;
    [[nodiscard]] std::optional<ItemStack> getItem(int raw_slot) const override;
    void setCursor(std::optional<ItemStack> item) override;
    [[nodiscard]] std::optional<ItemStack> getCursor() const override;
    [[nodiscard]] Inventory *getInventory(int raw_slot) const override;
    [[nodiscard]] int convertSlot(int raw_slot) const override;
    [[nodiscard]] SlotType getSlotType(int raw_slot) const override;
    [[nodiscard]] int countSlots() const override;
    [[nodiscard]] std::vector<NotNull<Player>> getViewers() const override;

private:
    [[nodiscard]] int getBottomSize() const;
    [[nodiscard]] std::optional<ItemStack> getBottomItem(int slot) const;
    void setBottomItem(int slot, std::optional<ItemStack> item);

    NotNull<Player> player_;
    NotNull<Inventory> top_;
    NotNull<Inventory> bottom_;
    std::optional<EndstonePlayer::OpenContainer> open_container_;
    int top_slot_count_;
    std::vector<SlotType> top_slot_types_;
};

}  // namespace endstone::core
