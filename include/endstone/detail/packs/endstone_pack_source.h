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

#include "bedrock/resources/pack.h"
#include "bedrock/resources/pack_source.h"

namespace endstone::detail {

class EndstonePackSource : public PackSource {
public:
    explicit EndstonePackSource(::PackType pack_type);
    ~EndstonePackSource() override = default;
    void forEachPackConst(ConstPackCallback callback) const override;
    void forEachPack(PackCallback callback) override;
    [[nodiscard]] PackOrigin getPackOrigin() const override;
    [[nodiscard]] PackType getPackType() const override;
    PackSourceReport load(IPackManifestFactory &factory,
                          const Bedrock::NotNullNonOwnerPtr<const IContentKeyProvider> &) override;

private:
    ::PackType pack_type_;
    std::vector<std::unique_ptr<Pack>> packs_;
};

}  // namespace endstone::detail
