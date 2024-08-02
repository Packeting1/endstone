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

#include "endstone/detail/block/block.h"

namespace endstone::detail {
EndstoneBlock::EndstoneBlock(BlockSource &block_source, BlockPos block_pos)
    : block_source_(block_source), block_pos_(block_pos)
{
}

std::unique_ptr<BlockData> EndstoneBlock::getData()
{
    // TODO(block): implement me
    return nullptr;
}

std::unique_ptr<EndstoneBlock> EndstoneBlock::at(BlockSource &block_source, BlockPos block_pos)
{
    return std::make_unique<EndstoneBlock>(block_source, block_pos);
}

}  // namespace endstone::detail
