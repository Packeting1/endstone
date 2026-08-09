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

#include <cstdint>

#include "bedrock/bedrock.h"
#include "bedrock/world/actor/actor.h"
#include "bedrock/world/actor/player/player.h"
#include "bedrock/world/item/item_stack.h"
#include "endstone/core/inventory/item_stack.h"
#include "endstone/core/player.h"
#include "endstone/core/server.h"
#include "endstone/event/player/player_bucket_entity_event.h"
#include "endstone/runtime/bedrock_hooks/actor_interaction.h"
#include "endstone/runtime/hook.h"

namespace {
bool callBucketEntityEvent(const endstone::runtime::ActorInteractionContext &interaction, ::ItemStack &entity_bucket)
{
    const auto &server = endstone::core::EndstoneServer::getInstance();
    auto &player = interaction.player->getEndstoneActor<endstone::core::EndstonePlayer>();
    endstone::PlayerBucketEntityEvent event{
        player,
        interaction.target->getEndstoneActor(),
        endstone::core::EndstoneItemStack::fromMinecraft(entity_bucket),
        endstone::EquipmentSlot::Hand,
        endstone::core::EndstoneItemStack::fromMinecraft(interaction.player->getCarriedItem()),
    };

    server.getPluginManager().callEvent(event);
    if (event.isCancelled()) {
        return false;
    }

    entity_bucket.setUserData(nullptr);
    entity_bucket = endstone::core::EndstoneItemStack::toMinecraft(event.getEntityBucket());
    return true;
}
}  // namespace

#ifdef _WIN32
extern "C" ENDSTONE_HOOK std::int64_t endstone_bucket_entity_use(
    std::int64_t item_stack, std::int64_t result, std::int64_t entity, int arg3, int arg4, int arg5, char arg6,
    std::int64_t arg7, std::int64_t arg8)
{
    const auto original = ENDSTONE_HOOK_CALL_ORIGINAL_NAME(&endstone_bucket_entity_use, "endstone_bucket_entity_use",
                                                            item_stack, result, entity, arg3, arg4, arg5, arg6, arg7,
                                                            arg8);
    const auto *interaction = endstone::runtime::getActorInteractionContext();
    if (interaction == nullptr || interaction->target != reinterpret_cast<::Actor *>(entity) || result == 0 ||
        (*reinterpret_cast<const unsigned char *>(result) & 1) == 0) {
        return original;
    }

    if (!callBucketEntityEvent(*interaction, *reinterpret_cast<::ItemStack *>(item_stack))) {
        *reinterpret_cast<unsigned char *>(result) = 0;
    }
    return original;
}
#else
extern "C" ENDSTONE_HOOK std::int64_t endstone_bucket_entity_use(
    std::int64_t item_stack, std::int64_t entity, int arg2, int arg3, int arg4, char arg5, std::int64_t arg6,
    std::int64_t arg7)
{
    const auto result = ENDSTONE_HOOK_CALL_ORIGINAL_NAME(&endstone_bucket_entity_use, "endstone_bucket_entity_use",
                                                         item_stack, entity, arg2, arg3, arg4, arg5, arg6, arg7);
    const auto *interaction = endstone::runtime::getActorInteractionContext();
    if (interaction == nullptr || interaction->target != reinterpret_cast<::Actor *>(entity) || (result & 1) == 0) {
        return result;
    }

    if (!callBucketEntityEvent(*interaction, *reinterpret_cast<::ItemStack *>(item_stack))) {
        return 0;
    }
    return result;
}
#endif
