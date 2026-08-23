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

#include "bedrock/entity/utilities/pushable_by_entity_utility.h"

#include <cstdint>
#include <unordered_map>

#include "bedrock/world/actor/actor.h"
#include "bedrock/world/level/level.h"
#include "endstone/core/plugin/plugin_manager.h"
#include "endstone/core/server.h"
#include "endstone/event/actor/actor_collide_with_actor_event.h"
#include "endstone/runtime/hook.h"

namespace {

struct CollisionCount {
    std::int64_t count = 0;
};

std::uint64_t collision_tick = 0;
std::unordered_map<std::uint64_t, CollisionCount> collision_counts;

bool allowEntityCollision(const endstone::core::EndstoneServer &server, Actor &owner)
{
    const auto max_collisions = server.getConfig().getInt("paper.world_defaults.collisions.max-entity-collisions", 8);
    if (max_collisions <= 0) {
        return true;
    }

    const auto tick_id = owner.getLevel().getCurrentServerTick().tick_id;
    if (tick_id != collision_tick) {
        collision_tick = tick_id;
        collision_counts.clear();
    }

    auto &count = collision_counts[owner.getRuntimeID().raw_id];
    if (count.count >= max_collisions) {
        return false;
    }
    ++count.count;
    return true;
}

}  // namespace

void PushableByEntityUtility::push(Actor &owner, Actor &other, bool push_self_only)
{
    const auto &server = endstone::core::EndstoneServer::getInstance();
    if (server.getEndstonePluginManager().isEventRegistered<endstone::ActorCollideWithActorEvent>()) {
        endstone::ActorCollideWithActorEvent event{owner.getEndstoneActor<endstone::Actor>(),
                                                   other.getEndstoneActor<endstone::Actor>()};
        server.getPluginManager().callEvent(event);
        if (event.isCancelled()) {
            return;
        }
    }

    const auto only_players_collide =
        server.getConfig().getBool("paper.world_defaults.collisions.only-players-collide", false);
    const auto allow_vehicle_collisions =
        server.getConfig().getBool("paper.world_defaults.collisions.allow-vehicle-collisions", true);
    if (only_players_collide && !owner.isPlayer() && !other.isPlayer() &&
        (!allow_vehicle_collisions || (!owner.isVehicle() && !other.isVehicle()))) {
        return;
    }
    const auto enable_player_collisions =
        server.getConfig().getBool("paper.global.collisions.enable-player-collisions", true);
    if (!enable_player_collisions && owner.isPlayer() && other.isPlayer()) {
        return;
    }
    if (!allowEntityCollision(server, owner)) {
        return;
    }

    ENDSTONE_HOOK_CALL_ORIGINAL(&PushableByEntityUtility::push, owner, other, push_self_only);
}
