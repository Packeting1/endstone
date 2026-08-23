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

#include "endstone/core/message.h"

#include <utility>

#include "bedrock/locale/i18n.h"
#include "endstone/core/server.h"
#include "endstone/variant.h"

namespace endstone::core {

Message EndstoneMessage::applyConfiguredMessages(Message message)
{
    if (const auto *translatable = std::get_if<Translatable>(&message);
        translatable && translatable->getText() == "commands.generic.error.permissions") {
        const auto configured =
            EndstoneServer::getInstance().getConfig().getString("paper.global.messages.no-permission", "");
        if (!configured.empty()) {
            return configured;
        }
    }
    return message;
}

std::string EndstoneMessage::toString(Message message)
{
    return std::visit(overloaded{[](const std::string &string) { return string; },
                                 [](const Translatable &tr) {
                                     return getI18n().get(tr.getText(), tr.getParameters(), nullptr);
                                 }},
                      applyConfiguredMessages(std::move(message)));
}

Translatable EndstoneMessage::toTranslatable(Message message)
{
    return std::visit(overloaded{[](const std::string &string) { return Translatable{string, {}}; },
                                 [](const Translatable &tr) {
                                     return tr;
                                 }},
                      applyConfiguredMessages(std::move(message)));
}

}  // namespace endstone::core
