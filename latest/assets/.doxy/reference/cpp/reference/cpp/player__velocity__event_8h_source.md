

# File player\_velocity\_event.h

[**File List**](files.md) **>** [**endstone**](dir_6cf277b678674f97c7a2b6b3b2447b33.md) **>** [**event**](dir_f1d783c0ad83ee143d16e768ebca51c8.md) **>** [**player**](dir_7c05c37b25e9c9eccd9c63c2d313ba28.md) **>** [**player\_velocity\_event.h**](player__velocity__event_8h.md)

[Go to the documentation of this file](player__velocity__event_8h.md)


```C++
// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.

#pragma once

#include "endstone/event/player/player_event.h"
#include "endstone/util/vector.h"

namespace endstone {

class PlayerVelocityEvent final : public PlayerEvent {
public:
    ENDSTONE_EVENT(PlayerVelocityEvent);

    explicit PlayerVelocityEvent(Player &player, Vector velocity) : PlayerEvent(player), velocity_(velocity) {}

    [[nodiscard]] Vector getVelocity() const { return velocity_; }

    void setVelocity(Vector velocity) { velocity_ = velocity; }

private:
    Vector velocity_;
};

}  // namespace endstone
```


