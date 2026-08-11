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

namespace endstone {

/** Describes the client input that triggered an inventory click. */
enum class ClickType {
    Drop,
    ControlDrop,
    Creative,
    SwapOffhand,
    Unknown,
};

/** Returns whether the click type represents a keyboard action. */
constexpr bool isKeyboardClick(ClickType click)
{
    return click == ClickType::Drop || click == ClickType::ControlDrop || click == ClickType::SwapOffhand;
}

/** Returns whether the click type is restricted to creative inventory actions. */
constexpr bool isCreativeAction(ClickType click)
{
    return click == ClickType::Creative;
}

}  // namespace endstone
