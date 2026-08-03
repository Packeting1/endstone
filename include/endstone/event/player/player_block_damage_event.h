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

#include <optional>
#include <utility>

#include "endstone/block/block_face.h"
#include "endstone/event/cancellable.h"
#include "endstone/event/player/player_event.h"
#include "endstone/inventory/item_stack.h"
#include "endstone/util/vector.h"

namespace endstone {

/**
 * @brief Called when a player starts, continues, aborts, predicts, stops, or creatively destroys a block.
 */
class PlayerBlockDamageEvent final : public Cancellable<PlayerEvent> {
public:
    ENDSTONE_EVENT(PlayerBlockDamageEvent)

    enum class Action {
        Start,
        Abort,
        Stop,
        Continue,
        Predict,
        Creative,
    };

    PlayerBlockDamageEvent(Player &player, Action action, std::optional<ItemStack> item, Block *block,
                           std::optional<BlockFace> block_face, std::optional<Vector> position)
        : Cancellable(player), action_(action), item_(std::move(item)), block_(block), block_face_(block_face),
          position_(std::move(position))
    {
    }

    [[nodiscard]] Action getAction() const { return action_; }
    [[nodiscard]] bool hasItem() const { return item_.has_value(); }
    [[nodiscard]] const std::optional<ItemStack> &getItem() const { return item_; }
    [[nodiscard]] bool hasBlock() const { return block_ != nullptr; }
    [[nodiscard]] Block *getBlock() const { return block_; }
    [[nodiscard]] std::optional<BlockFace> getBlockFace() const { return block_face_; }
    [[nodiscard]] std::optional<Vector> getPosition() const { return position_; }

private:
    Action action_;
    std::optional<ItemStack> item_;
    Block *block_;
    std::optional<BlockFace> block_face_;
    std::optional<Vector> position_;
};

}  // namespace endstone
