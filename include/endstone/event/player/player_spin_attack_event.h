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
 * @brief Called when a player starts or stops a spin attack.
 */
class PlayerSpinAttackEvent final : public PlayerEvent {
public:
    ENDSTONE_EVENT(PlayerSpinAttackEvent)

    explicit PlayerSpinAttackEvent(Player &player, bool spin_attacking)
        : PlayerEvent(player), spin_attacking_(spin_attacking)
    {
    }

    /**
     * @brief Gets whether the player is performing a spin attack.
     *
     * @return true when starting a spin attack, false when stopping
     */
    [[nodiscard]] bool isSpinAttacking() const { return spin_attacking_; }

private:
    bool spin_attacking_;
};

}  // namespace endstone
