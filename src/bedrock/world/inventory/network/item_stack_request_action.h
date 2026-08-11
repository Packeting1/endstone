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

#include <cstdint>
#include <vector>

#include "bedrock/bedrock.h"
#include "bedrock/platform/result.h"
#include "bedrock/world/containers/container_enum.h"
#include "bedrock/world/inventory/network/item_stack_net_id_variant.h"
#include "bedrock/world/inventory/network/item_stack_net_result.h"
#include "bedrock/world/inventory/network/item_stack_request_action_type.h"
#include "bedrock/world/item/crafting/recipe.h"

class BinaryStream;
class BlockPalette;
class ItemStackRequestActionCraftBase;
class ItemStackRequestActionHandler;
class ItemStackNetManagerServer;
class Player;
class ReadOnlyBinaryStream;

struct ItemStackRequestSlotInfo {
    FullContainerName container_name_;
    std::uint8_t slot_;
    ItemStackNetIdVariant net_id_;
};
BEDROCK_STATIC_ASSERT_SIZE(ItemStackRequestSlotInfo, 40, 40);

class ItemStackRequestAction {
public:
    virtual ~ItemStackRequestAction() = default;

    virtual const ItemStackRequestActionCraftBase *getCraftAction() const;
    virtual int getFilteredStringIndex() const;
    virtual void postLoadItems_DEPRECATEDASKTYLAING(BlockPalette &, bool);
    virtual void _write(BinaryStream &) const = 0;
    virtual Bedrock::Result<void> _read(ReadOnlyBinaryStream &) = 0;

    // Endstone: private -> public
    ItemStackRequestActionType type_;
};
BEDROCK_STATIC_ASSERT_SIZE(ItemStackRequestAction, 16, 16);

class ItemStackRequestActionCraftBase : public ItemStackRequestAction {
public:
    const ItemStackRequestActionCraftBase *getCraftAction() const override;
    void postLoadItems_DEPRECATEDASKTYLAING(BlockPalette &, bool) override;

    // Endstone: private -> public
    std::uint8_t craft_count_;
};
BEDROCK_STATIC_ASSERT_SIZE(ItemStackRequestActionCraftBase, 24, 16);

class ItemStackRequestActionCraftRecipe : public ItemStackRequestActionCraftBase {
public:
    void _write(BinaryStream &) const override;
    Bedrock::Result<void> _read(ReadOnlyBinaryStream &) override;

    // Endstone: private -> public
    RecipeNetId recipe_net_id_;
};
BEDROCK_STATIC_ASSERT_SIZE(ItemStackRequestActionCraftRecipe, 32, 16);

class ItemStackRequestActionCraftRecipeAuto : public ItemStackRequestActionCraftRecipe {
public:
    void _write(BinaryStream &) const override;
    Bedrock::Result<void> _read(ReadOnlyBinaryStream &) override;

    // Endstone: private -> public
    std::vector<RecipeIngredient> ingredients_;

    // Endstone: private -> public
    std::uint8_t ingredient_count_;
};
BEDROCK_STATIC_ASSERT_SIZE(ItemStackRequestActionCraftRecipeAuto, 64, 48);

class ItemStackRequestActionTransferBase : public ItemStackRequestAction {
public:
    bool is_dst_serialized_;
    bool is_amount_serialized_;
    std::uint8_t amount_;
    ItemStackRequestSlotInfo source_;
    ItemStackRequestSlotInfo destination_;

    void _write(BinaryStream &) const override;
    Bedrock::Result<void> _read(ReadOnlyBinaryStream &) override;
};
BEDROCK_STATIC_ASSERT_SIZE(ItemStackRequestActionTransferBase, 104, 96);

class ItemStackRequestActionCraftHandler {
public:
    ItemStackRequestActionCraftHandler(ItemStackRequestActionHandler &, Player &);
    virtual ~ItemStackRequestActionCraftHandler() = default;

    ENDSTONE_HOOK ItemStackNetResult handleCraftAction(const ItemStackRequestActionCraftBase &);

    // Endstone
    [[nodiscard]] Player &getPlayer() const { return player_; }

private:
    ItemStackRequestActionHandler &action_handler_;
    Player &player_;
};
BEDROCK_STATIC_ASSERT_SIZE(ItemStackRequestActionCraftHandler, 24, 24);

class ItemStackRequestActionHandler {
public:
    ItemStackRequestActionHandler(ItemStackNetManagerServer &, Player &);
    ENDSTONE_HOOK ItemStackNetResult _handleTransfer(const ItemStackRequestActionTransferBase &, bool, bool, bool);

    // Endstone
    [[nodiscard]] Player &getPlayer() const { return player_; }

private:
    Player &player_;
};
