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

#include "endstone/runtime/bedrock_hooks/shear.h"

#include "bedrock/core/string/string_hash.h"
#include "bedrock/entity/components/actor_equipment_component.h"
#include "bedrock/world/actor/actor.h"
#include "bedrock/world/actor/actor_data_ids.h"
#include "bedrock/world/actor/player/player.h"
#include "bedrock/world/actor/provider/actor_riding.h"
#include "bedrock/world/item/item.h"
#include "bedrock/world/item/item_stack.h"
#include "endstone/core/inventory/item_stack.h"
#include "endstone/core/player.h"
#include "endstone/core/server.h"
#include "endstone/event/player/player_shear_entity_event.h"
#include "endstone/runtime/bedrock_hooks/actor_interaction.h"

namespace {
bool hasComponent(const ::Actor &actor, const char *name)
{
    return const_cast<::Actor &>(actor).hasComponent(HashedString(name));
}

const ::ItemStack *getBodyItem(const ::Actor &actor)
{
    const auto *equipment = actor.tryGetComponent<ActorEquipmentComponent>();
    if (!equipment || !equipment->armor) {
        return nullptr;
    }
    return &equipment->armor->getItem(static_cast<int>(ArmorSlot::Body));
}

bool isOwnedBy(const ::Actor &actor, const ::Player &player)
{
    const auto owner_id = static_cast<SynchedActorData::ID>(ActorDataIDs::OWNER);
    return actor.entity_data.hasData(owner_id) &&
           actor.entity_data.getInt64(owner_id) == player.getOrCreateUniqueID().raw_id;
}

bool isShearable(const ::Actor &actor, const ::Player &player)
{
    const auto &name = actor.getActorIdentifier().getCanonicalName();
    if (name == "minecraft:sheep") {
        return hasComponent(actor, "minecraft:is_dyeable") && !hasComponent(actor, "minecraft:is_baby");
    }
    if (name == "minecraft:mooshroom") {
        return !hasComponent(actor, "minecraft:transformation");
    }
    if (name == "minecraft:snow_golem" || name == "minecraft:bogged") {
        return !hasComponent(actor, "minecraft:is_sheared");
    }
    if (name == "minecraft:sulfur_cube") {
        return !player.isSneaking() && hasComponent(actor, "minecraft:environment_sensor");
    }
    if (name == "minecraft:wolf") {
        // Bedrock only allows the owner to remove equipped wolf armor while not sneaking.
        const auto *body_item = getBodyItem(actor);
        return !player.isSneaking() && hasComponent(actor, "minecraft:is_tamed") && isOwnedBy(actor, player) &&
               body_item && body_item->getItem() && body_item->getItem()->getFullItemName() == "minecraft:wolf_armor";
    }
    if (name == "minecraft:happy_ghast") {
        // Bedrock only allows removing a happy ghast's harness while not sneaking and without passengers.
        const auto *body_item = getBodyItem(actor);
        return !player.isSneaking() && ActorRiding::getPassengers(actor.getEntity()).empty() && body_item &&
               !body_item->isNull();
    }
    return false;
}

bool isShears(const ::ItemStack &item)
{
    return !item.isNull() && item.getItem() && item.getItem()->getFullItemName() == "minecraft:shears";
}
}  // namespace

namespace endstone::runtime {

bool fireShearEntityEvent(const ::Player &player, const ::Actor &target, const ::ItemStack &item)
{
    const auto *interaction = getActorInteractionContext();
    if (!interaction || interaction->player != &player || interaction->target != &target || !isShears(item) ||
        !isShearable(target, player)) {
        return true;
    }

    const auto &server = endstone::core::EndstoneServer::getInstance();
    endstone::PlayerShearEntityEvent event{
        player.getEndstoneActor<endstone::core::EndstonePlayer>(),
        target.getEndstoneActor(),
        getInteractionHand(player, item),
        endstone::core::EndstoneItemStack::fromMinecraft(item),
    };
    server.getPluginManager().callEvent(event);
    return !event.isCancelled();
}

}  // namespace endstone::runtime
