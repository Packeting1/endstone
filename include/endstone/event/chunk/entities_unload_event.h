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
 * Called when entities are unloaded from a chunk.
 */
class EntitiesUnloadEvent : public ChunkEvent {
public:
    ENDSTONE_EVENT(EntitiesUnloadEvent);

    /**
     * Creates an event for entities being unloaded from a chunk.
     *
     * @param chunk Chunk from which the entities are being unloaded
     * @param entities Entities being unloaded
     */
    explicit EntitiesUnloadEvent(Chunk &chunk, const std::vector<Actor *> &entities)
        : ChunkEvent(chunk), entities_(entities) {}
    ~EntitiesUnloadEvent() override = default;

    /**
     * Gets the entities being unloaded.
     *
     * @return Read-only collection of entities being unloaded
     */
    [[nodiscard]] const std::vector<Actor *> &getEntities() const { return entities_; }

private:
    std::vector<Actor *> entities_;
};

}
