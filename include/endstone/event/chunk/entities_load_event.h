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

#include <vector>

#include "endstone/actor/actor.h"
#include "endstone/event/chunk/chunk_event.h"

namespace endstone {

/**
 * Called when entities are loaded into a chunk.
 */
class EntitiesLoadEvent : public ChunkEvent {
public:
    ENDSTONE_EVENT(EntitiesLoadEvent);

    /**
     * Creates an entities load event.
     *
     * @param chunk The chunk containing the loaded entities.
     * @param entities The loaded entities.
     */
    EntitiesLoadEvent(Chunk &chunk, const std::vector<NotNull<Actor>> &entities)
        : ChunkEvent(chunk), entities_(entities) {}
    ~EntitiesLoadEvent() override = default;

    /**
     * Gets the entities that were loaded.
     *
     * @return A read-only collection of loaded entities.
     */
    [[nodiscard]] const std::vector<NotNull<Actor>> &getEntities() const { return entities_; }

private:
    std::vector<NotNull<Actor>> entities_;
};

}
