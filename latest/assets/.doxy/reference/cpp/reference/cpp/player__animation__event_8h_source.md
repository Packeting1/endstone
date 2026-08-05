

# File player\_animation\_event.h

[**File List**](files.md) **>** [**endstone**](dir_6cf277b678674f97c7a2b6b3b2447b33.md) **>** [**event**](dir_f1d783c0ad83ee143d16e768ebca51c8.md) **>** [**player**](dir_7c05c37b25e9c9eccd9c63c2d313ba28.md) **>** [**player\_animation\_event.h**](player__animation__event_8h.md)

[Go to the documentation of this file](player__animation__event_8h.md)


```C++
// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.

#pragma once

#include "endstone/event/cancellable.h"
#include "endstone/event/player/player_event.h"

namespace endstone {

enum class PlayerAnimationType {
    ArmSwing,
    OffArmSwing,
};

class PlayerAnimationEvent final : public Cancellable<PlayerEvent> {
public:
    ENDSTONE_EVENT(PlayerAnimationEvent);

    PlayerAnimationEvent(Player &player, PlayerAnimationType animation_type)
        : Cancellable(player), animation_type_(animation_type)
    {
    }

    [[nodiscard]] PlayerAnimationType getAnimationType() const { return animation_type_; }

private:
    PlayerAnimationType animation_type_;
};

}  // namespace endstone
```


