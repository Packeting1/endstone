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
#include "endstone/event/event.h"
#include "endstone/event/cancellable.h"
#include "endstone/level/location.h"
#include "endstone/player.h"
#include "endstone/util/pointers.h"

namespace endstone {

/**
 * Represents the type of tree that will grow.
 */
enum class TreeType {
    /** A regular tree. */
    Tree,
    /** A large tree. */
    BigTree,
    /** A redwood tree. */
    Redwood,
    /** A tall redwood tree. */
    TallRedwood,
    /** A birch tree. */
    Birch,
    /** A jungle tree. */
    Jungle,
    /** A small jungle tree. */
    SmallJungle,
    /** A jungle tree with cocoa pods. */
    CocoaTree,
    /** A jungle bush. */
    JungleBush,
    /** A red mushroom. */
    RedMushroom,
    /** A brown mushroom. */
    BrownMushroom,
    /** A swamp tree. */
    Swamp,
    /** An acacia tree. */
    Acacia,
    /** A dark oak tree. */
    DarkOak,
    /** A mega redwood tree. */
    MegaRedwood,
    /** A mega pine tree. */
    MegaPine,
    /** A tall mangrove tree. */
    TallMangrove,
    /** A cherry tree. */
    Cherry,
    /** A pale oak tree. */
    PaleOak
};

/**
 * Called when a tree or other structure grows.
 *
 * If a Structure Grow event is cancelled, the structure will not grow.
 */
class StructureGrowEvent final : public Cancellable<Event> {
    using BlockStateList = std::vector<std::unique_ptr<BlockState>>;

public:
    ENDSTONE_EVENT(StructureGrowEvent);

    explicit StructureGrowEvent(Location location, TreeType species, bool from_bonemeal,
                                const Nullable<Player> &player, BlockStateList blocks)
        : Cancellable(), location_(std::move(location)), species_(species), from_bonemeal_(from_bonemeal), player_(player),
          blocks_(std::move(blocks))
    {
    }

    ~StructureGrowEvent() override = default;

    /**
     * Gets the location where the structure will be generated.
     *
     * @return The location where the structure will be generated.
     */
    [[nodiscard]] const Location &getLocation() const { return location_; }

    /**
     * Gets the type of tree that will grow.
     *
     * @return The tree type.
     */
    [[nodiscard]] TreeType getSpecies() const { return species_; }

    /**
     * Gets whether this structure growth was caused by bonemeal.
     *
     * @return `true` if bonemeal caused the growth, otherwise `false`.
     */
    [[nodiscard]] bool isFromBonemeal() const { return from_bonemeal_; }

    /**
     * Gets the player who caused the structure to grow.
     *
     * @return The player, or an empty value if no player caused the growth.
     */
    [[nodiscard]] const Nullable<Player> &getPlayer() const { return player_; }

    /**
     * Gets the block states that will be changed by this event.
     *
     * @return The block states that will be changed.
     */
    [[nodiscard]] const BlockStateList &getBlocks() const { return blocks_; }

    /**
     * Gets the block states that will be changed by this event.
     *
     * @return The block states that will be changed.
     */
    [[nodiscard]] BlockStateList &getBlocks() { return blocks_; }

private:
    Location location_;
    TreeType species_;
    bool from_bonemeal_;
    Nullable<Player> player_;
    BlockStateList blocks_;
};

}  // namespace endstone
