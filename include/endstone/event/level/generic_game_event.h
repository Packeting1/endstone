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

#include <string>
#include <utility>

#include "endstone/actor/actor.h"
#include "endstone/event/cancellable.h"
#include "endstone/event/level/level_event.h"
#include "endstone/level/dimension.h"
#include "endstone/level/location.h"

namespace endstone {

/**
 * Represents a generic game event.
 *
 * The event carries the identifier, location, optional actor, and radius associated with the event.
 */
class GenericGameEvent : public Cancellable<LevelEvent> {
public:
    ENDSTONE_EVENT(GenericGameEvent);

    /**
     * Constructs a generic game event.
     *
     * @param event Identifier of the event.
     * @param location Location where the event occurred.
     * @param actor Actor associated with the event, or `nullptr` if there is none.
     * @param radius Radius associated with the event.
     */
    GenericGameEvent(std::string event, Location location, const Nullable<Actor> &actor, int radius)
        : Cancellable(location.getDimension().value().getLevel()),
          event_(std::move(event)),
          location_(std::move(location)),
          actor_(actor),
          radius_(radius)
    {
    }

    ~GenericGameEvent() override = default;

    /**
     * Gets the identifier of the event.
     *
     * @return Identifier of the event.
     */
    [[nodiscard]] const std::string &getEvent() const { return event_; }

    /**
     * Gets the location where the event occurred.
     *
     * @return Location where the event occurred.
     */
    [[nodiscard]] const Location &getLocation() const { return location_; }

    /**
     * Gets the actor associated with the event.
     *
     * @return Actor associated with the event, or `nullptr` if there is none.
     */
    [[nodiscard]] const Nullable<Actor> &getActor() const { return actor_; }

    /**
     * Gets the radius associated with the event.
     *
     * @return Radius associated with the event.
     */
    [[nodiscard]] int getRadius() const { return radius_; }

private:
    std::string event_;
    Location location_;
    Nullable<Actor> actor_;
    int radius_;
};

}  // namespace endstone
