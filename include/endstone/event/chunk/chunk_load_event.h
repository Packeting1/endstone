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

#include "endstone/event/chunk/chunk_event.h"

namespace endstone {

/**
 * Called when a chunk is loaded.
 */
class ChunkLoadEvent : public ChunkEvent {
public:
    ENDSTONE_EVENT(ChunkLoadEvent);

    /**
     * Constructs a chunk load event for the given chunk.
     *
     * @param chunk The chunk that was loaded.
     * @param new_chunk Whether the chunk was newly created.
     */
    explicit ChunkLoadEvent(Chunk &chunk, bool new_chunk) : ChunkEvent(chunk), new_chunk_(new_chunk) {}

    /**
     * Gets whether this chunk was newly created.
     *
     * @return `true` if this chunk was newly created, otherwise `false`.
     */
    [[nodiscard]] bool isNewChunk() const { return new_chunk_; }

    ~ChunkLoadEvent() override = default;

private:
    bool new_chunk_;
};

}  // namespace endstone
