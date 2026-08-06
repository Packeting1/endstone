// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include <utility>

#include "endstone/event/cancellable.h"
#include "endstone/event/player/player_event.h"
#include "endstone/inventory/equipment_slot.h"
#include "endstone/inventory/item_stack.h"

namespace endstone {

class Actor;

/**
 * Called when a player shears an entity.
 */
class PlayerShearEntityEvent final : public Cancellable<PlayerEvent> {
public:
    ENDSTONE_EVENT(PlayerShearEntityEvent);

    /**
     * Constructs a player shear entity event.
     *
     * @param player player who sheared the entity
     * @param entity entity that was sheared
     * @param hand hand used to shear the entity
     * @param item item used to shear the entity
     */
    PlayerShearEntityEvent(Player &player, Actor &entity, EquipmentSlot hand, ItemStack item)
        : Cancellable(player), entity_(entity), hand_(hand), item_(std::move(item))
    {
    }

    /**
     * Gets the entity that was sheared.
     *
     * @return entity that was sheared
     */
    [[nodiscard]] Actor &getEntity() const { return entity_; }

    /**
     * Gets the hand used to shear the entity.
     *
     * @return hand used to shear the entity
     */
    [[nodiscard]] EquipmentSlot getHand() const { return hand_; }

    /**
     * Gets the item used to shear the entity.
     *
     * @return item used to shear the entity
     */
    [[nodiscard]] const ItemStack &getItem() const { return item_; }

private:
    Actor &entity_;
    EquipmentSlot hand_;
    ItemStack item_;
};

}  // namespace endstone
