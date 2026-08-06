

# File player\_shear\_entity\_event.h

[**File List**](files.md) **>** [**endstone**](dir_6cf277b678674f97c7a2b6b3b2447b33.md) **>** [**event**](dir_f1d783c0ad83ee143d16e768ebca51c8.md) **>** [**player**](dir_7c05c37b25e9c9eccd9c63c2d313ba28.md) **>** [**player\_shear\_entity\_event.h**](player__shear__entity__event_8h.md)

[Go to the documentation of this file](player__shear__entity__event_8h.md)


```C++
// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include <utility>

#include "endstone/actor/actor.h"
#include "endstone/event/cancellable.h"
#include "endstone/event/player/player_event.h"
#include "endstone/inventory/equipment_slot.h"
#include "endstone/inventory/item_stack.h"

namespace endstone {

class PlayerShearEntityEvent final : public Cancellable<PlayerEvent> {
public:
    ENDSTONE_EVENT(PlayerShearEntityEvent);

    PlayerShearEntityEvent(Player &player, Actor &entity, EquipmentSlot hand, ItemStack item)
        : Cancellable(player), entity_(entity), hand_(hand), item_(std::move(item))
    {
    }

    [[nodiscard]] Actor &getEntity() const { return entity_; }

    [[nodiscard]] EquipmentSlot getHand() const { return hand_; }

    [[nodiscard]] const ItemStack &getItem() const { return item_; }

private:
    Actor &entity_;
    EquipmentSlot hand_;
    ItemStack item_;
};

}  // namespace endstone
```


