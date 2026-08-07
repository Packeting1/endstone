

# File player\_recipe\_book\_click\_event.h

[**File List**](files.md) **>** [**endstone**](dir_6cf277b678674f97c7a2b6b3b2447b33.md) **>** [**event**](dir_f1d783c0ad83ee143d16e768ebca51c8.md) **>** [**player**](dir_7c05c37b25e9c9eccd9c63c2d313ba28.md) **>** [**player\_recipe\_book\_click\_event.h**](player__recipe__book__click__event_8h.md)

[Go to the documentation of this file](player__recipe__book__click__event_8h.md)


```C++
// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "endstone/event/player/player_event.h"
#include "endstone/inventory/recipe.h"

namespace endstone {

class PlayerRecipeBookClickEvent final : public PlayerEvent {
public:
    ENDSTONE_EVENT(PlayerRecipeBookClickEvent);

    PlayerRecipeBookClickEvent(Player &player, Recipe &recipe, bool shift_click)
        : PlayerEvent(player), original_recipe_(recipe), recipe_(recipe), shift_click_(shift_click)
    {
    }

    [[nodiscard]] Recipe &getOriginalRecipe() const { return original_recipe_; }

    [[nodiscard]] Recipe &getRecipe() const { return recipe_; }

    void setRecipe(Recipe &recipe) { recipe_ = recipe; }

    [[nodiscard]] bool isShiftClick() const { return shift_click_; }

    void setShiftClick(bool shift_click) { shift_click_ = shift_click; }

private:
    Recipe &original_recipe_;
    Recipe &recipe_;
    bool shift_click_;
};

}  // namespace endstone
```


