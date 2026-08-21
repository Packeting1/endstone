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

#include <utility>

#include "endstone/event/level/level_event.h"
#include "endstone/level/location.h"

namespace endstone {

/**
 * Called when the spawn location of a level changes.
 */
class SpawnChangeEvent : public LevelEvent {
public:
    ENDSTONE_EVENT(SpawnChangeEvent);

    SpawnChangeEvent(Level &level, Location previous_location)
        : LevelEvent(level), previous_location_(std::move(previous_location))
    {
    }

    /**
     * Gets the previous spawn location.
     *
     * @return the previous spawn location
     */
    [[nodiscard]] const Location &getPreviousLocation() const { return previous_location_; }

private:
    Location previous_location_;
};

}  // namespace endstone
