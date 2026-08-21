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

#include <cstdint>

#include "endstone/event/cancellable.h"
#include "endstone/event/level/level_event.h"

namespace endstone {

/**
 * Represents an event that is fired when the clock of a level is advanced.
 *
 * The event may be cancelled to prevent the time skip from occurring.
 */
class ClockTimeSkipEvent : public Cancellable<LevelEvent> {
public:
    /**
     * Represents the reason for a level clock time skip.
     */
    enum class SkipReason {
        /**
         * The time skip was initiated by a command.
         */
        Command,
        /**
         * The time skip was initiated by a custom source.
         */
        Custom,
        /**
         * The time skip was initiated because of the normal night skip.
         */
        NightSkip
    };

    /**
     * Constructs a clock time skip event.
     *
     * @param level the level whose clock will be advanced
     * @param reason the reason for the time skip
     * @param skip_amount the signed amount of time to skip
     */
    explicit ClockTimeSkipEvent(Level &level, SkipReason reason, std::int64_t skip_amount)
        : Cancellable(level), reason_(reason), skip_amount_(skip_amount) {}

    ENDSTONE_EVENT(ClockTimeSkipEvent)

    /**
     * Gets the reason for the time skip.
     *
     * @return the immutable reason for the time skip
     */
    [[nodiscard]] SkipReason getSkipReason() const { return reason_; }

    /**
     * Gets the amount of time to skip.
     *
     * Negative values move the level clock backwards.
     *
     * @return the signed amount of time to skip
     */
    [[nodiscard]] std::int64_t getSkipAmount() const { return skip_amount_; }

    /**
     * Sets the amount of time to skip.
     *
     * Negative values move the level clock backwards.
     *
     * @param skip_amount the signed amount of time to skip
     */
    void setSkipAmount(std::int64_t skip_amount) { skip_amount_ = skip_amount; }

private:
    const SkipReason reason_;
    std::int64_t skip_amount_;
};

}  // namespace endstone
