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

#include <memory>
#include <utility>
#include <vector>

#include "endstone/block/block_state.h"
#include "endstone/event/cancellable.h"
#include "endstone/event/level/level_event.h"
#include "endstone/util/pointers.h"

namespace endstone {

class Actor;

/**
 * Called when a portal is created.
 *
 * If a PortalCreateEvent is cancelled, the portal will not be created.
 */
class PortalCreateEvent : public Cancellable<LevelEvent> {
    using BlockList = std::vector<std::unique_ptr<BlockState>>;

public:
    /**
     * Specifies the reason that a portal was created.
     */
    enum class CreateReason {
        /** A portal was created by fire. */
        Fire,
        /** A portal was created by another portal. */
        NetherPair,
        /** An end platform was created. */
        EndPlatform,
        /** A portal was created by a custom source. */
        Custom,
    };

    ENDSTONE_EVENT(PortalCreateEvent);

    PortalCreateEvent(BlockList blocks, Level &level, const Nullable<Actor> &entity, CreateReason reason)
        : Cancellable(level), blocks_(std::move(blocks)), entity_(entity), reason_(reason)
    {
    }
    ~PortalCreateEvent() override = default;

    /**
     * Gets the blocks involved in the portal creation.
     *
     * @return The block states that will be used to create the portal.
     */
    [[nodiscard]] const BlockList &getBlocks() const { return blocks_; }

    /**
     * Gets the blocks involved in the portal creation.
     *
     * @return The block states that will be used to create the portal.
     */
    [[nodiscard]] BlockList &getBlocks() { return blocks_; }

    /**
     * Gets the Actor involved in creating the portal.
     *
     * @return The Actor involved in the portal creation, or an empty handle if no Actor was involved.
     */
    [[nodiscard]] const Nullable<Actor> &getEntity() const { return entity_; }

    /**
     * Gets the reason for the portal creation.
     *
     * @return The reason the portal was created.
     */
    [[nodiscard]] CreateReason getReason() const { return reason_; }

private:
    BlockList blocks_;
    Nullable<Actor> entity_;
    CreateReason reason_;
};

}  // namespace endstone
