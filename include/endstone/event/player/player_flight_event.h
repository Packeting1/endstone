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

#include "endstone/event/player/player_event.h"

namespace endstone {

/**
 * Called when a player starts or stops flying.
 */
class PlayerFlightEvent final : public PlayerEvent {
public:
    ENDSTONE_EVENT(PlayerFlightEvent)

    explicit PlayerFlightEvent(Player &player, bool flying) : PlayerEvent(player), flying_(flying) {}

    /**
     * Gets whether the player is flying.
     *
     * @return true when starting to fly, false when stopping
     */
    [[nodiscard]] bool isFlying() const { return flying_; }

private:
    bool flying_;
};

}  // namespace endstone
