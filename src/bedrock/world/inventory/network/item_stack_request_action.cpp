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

#include "bedrock/world/inventory/network/item_stack_request_action.h"

// Endstone: local vtable placeholders for synthetic request actions.
const ItemStackRequestActionCraftBase *ItemStackRequestAction::getCraftAction() const
{
    return nullptr;
}

int ItemStackRequestAction::getFilteredStringIndex() const
{
    return -1;
}

void ItemStackRequestAction::postLoadItems_DEPRECATEDASKTYLAING(BlockPalette &, bool) {}

const ItemStackRequestActionCraftBase *ItemStackRequestActionCraftBase::getCraftAction() const
{
    return this;
}

void ItemStackRequestActionCraftBase::postLoadItems_DEPRECATEDASKTYLAING(BlockPalette &, bool) {}

void ItemStackRequestActionCraftRecipe::_write(BinaryStream &) const {}

Bedrock::Result<void> ItemStackRequestActionCraftRecipe::_read(ReadOnlyBinaryStream &)
{
    return {};
}

void ItemStackRequestActionCraftRecipeAuto::_write(BinaryStream &) const {}

Bedrock::Result<void> ItemStackRequestActionCraftRecipeAuto::_read(ReadOnlyBinaryStream &)
{
    return {};
}

void ItemStackRequestActionTransferBase::_write(BinaryStream &) const {}

Bedrock::Result<void> ItemStackRequestActionTransferBase::_read(ReadOnlyBinaryStream &)
{
    return {};
}
