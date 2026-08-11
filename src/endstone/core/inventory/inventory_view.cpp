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

#include "endstone/core/inventory/inventory_view.h"

#include "bedrock/world/inventory/filling_container.h"
#include "endstone/core/inventory/player_inventory.h"
#include "endstone/core/server.h"
#include "endstone/core/player.h"

namespace {

using endstone::Inventory;
using endstone::ItemStack;
using endstone::PlayerInventory;

std::optional<ItemStack> getPlayerInventoryItem(const PlayerInventory &inventory, int slot)
{
    switch (slot) {
    case 36:
        return inventory.getHelmet();
    case 37:
        return inventory.getChestplate();
    case 38:
        return inventory.getLeggings();
    case 39:
        return inventory.getBoots();
    case 40:
        return inventory.getItemInOffHand();
    default:
        return std::nullopt;
    }
}

void setPlayerInventoryItem(PlayerInventory &inventory, int slot, std::optional<ItemStack> item)
{
    switch (slot) {
    case 36:
        inventory.setHelmet(std::move(item));
        break;
    case 37:
        inventory.setChestplate(std::move(item));
        break;
    case 38:
        inventory.setLeggings(std::move(item));
        break;
    case 39:
        inventory.setBoots(std::move(item));
        break;
    case 40:
        inventory.setItemInOffHand(std::move(item));
        break;
    default:
        break;
    }
}

}  // namespace

namespace endstone::core {

void EndstoneInventoryView::setItem(int raw_slot, std::optional<ItemStack> item)
{
    if (raw_slot < 0 || raw_slot >= countSlots()) {
        return;
    }

    if (raw_slot < top_slot_count_) {
        top_->setItem(raw_slot, std::move(item));
        return;
    }

    setBottomItem(convertSlot(raw_slot), std::move(item));
}

std::optional<ItemStack> EndstoneInventoryView::getItem(int raw_slot) const
{
    if (raw_slot < 0 || raw_slot >= countSlots()) {
        return std::nullopt;
    }

    if (raw_slot < top_slot_count_) {
        return top_->getItem(raw_slot);
    }

    return getBottomItem(convertSlot(raw_slot));
}

void EndstoneInventoryView::setCursor(std::optional<ItemStack> item)
{
    auto &player = static_cast<EndstonePlayer &>(*player_);
    const auto cursor_item = item.has_value() ? EndstoneItemStack::toMinecraft(*item) : ::ItemStack::EMPTY_ITEM;
    player.getHandle().getPlayerUIContainer().setItemWithForceBalance(0, cursor_item, true);
}

std::optional<ItemStack> EndstoneInventoryView::getCursor() const
{
    const auto &player = static_cast<const EndstonePlayer &>(*player_);
    const auto &cursor_item = player.getHandle().getPlayerUIContainer().getItem(0);
    if (cursor_item.isNull()) {
        return std::nullopt;
    }
    return EndstoneItemStack::fromMinecraft(cursor_item);
}

Inventory *EndstoneInventoryView::getInventory(int raw_slot) const
{
    if (raw_slot < 0 || raw_slot >= countSlots()) {
        return nullptr;
    }
    if (raw_slot < top_slot_count_) {
        return top_.get().get();
    }
    return bottom_.get().get();
}

int EndstoneInventoryView::convertSlot(int raw_slot) const
{
    if (raw_slot == InventoryView::OUTSIDE || raw_slot < 0) {
        return InventoryView::OUTSIDE;
    }
    return raw_slot < top_slot_count_ ? raw_slot : raw_slot - top_slot_count_;
}

SlotType EndstoneInventoryView::getSlotType(int raw_slot) const
{
    if (raw_slot == InventoryView::OUTSIDE || raw_slot < 0) {
        return SlotType::Outside;
    }
    if (raw_slot >= countSlots()) {
        return SlotType::Container;
    }
    if (raw_slot < top_slot_count_) {
        return raw_slot < static_cast<int>(top_slot_types_.size()) ? top_slot_types_[raw_slot] : SlotType::Container;
    }

    const auto slot = convertSlot(raw_slot);
    if (slot < FillingContainer::HOTBAR_SIZE) {
        return SlotType::Quickbar;
    }
    if (slot >= 36 && slot < 40) {
        return SlotType::Armor;
    }
    return SlotType::Container;
}

int EndstoneInventoryView::countSlots() const
{
    return top_slot_count_ + getBottomSize();
}

int EndstoneInventoryView::getBottomSize() const
{
    return dynamic_cast<const PlayerInventory *>(&*bottom_) ? 41 : bottom_->getSize();
}

std::optional<ItemStack> EndstoneInventoryView::getBottomItem(int slot) const
{
    if (slot < 0 || slot >= getBottomSize()) {
        return std::nullopt;
    }
    if (slot < bottom_->getSize()) {
        return bottom_->getItem(slot);
    }

    const auto *player_inventory = dynamic_cast<const PlayerInventory *>(&*bottom_);
    return player_inventory ? getPlayerInventoryItem(*player_inventory, slot) : std::nullopt;
}

void EndstoneInventoryView::setBottomItem(int slot, std::optional<ItemStack> item)
{
    if (slot < 0 || slot >= getBottomSize()) {
        return;
    }
    if (slot < bottom_->getSize()) {
        bottom_->setItem(slot, std::move(item));
        return;
    }

    if (auto *player_inventory = dynamic_cast<PlayerInventory *>(&*bottom_)) {
        setPlayerInventoryItem(*player_inventory, slot, std::move(item));
    }
}

std::vector<NotNull<Player>> EndstoneInventoryView::getViewers() const
{
    if (!open_container_) {
        return {player_};
    }

    std::vector<NotNull<Player>> viewers;
    for (const auto &viewer : EndstoneServer::getInstance().getOnlinePlayers()) {
        const auto &player = static_cast<const EndstonePlayer &>(*viewer);
        if (player.getOpenContainer() == open_container_) {
            viewers.push_back(viewer);
        }
    }
    return viewers;
}

}  // namespace endstone::core
