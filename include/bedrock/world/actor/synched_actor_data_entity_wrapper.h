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

#include "bedrock/entity/gamerefs_entity/gamerefs_entity.h"
#include "bedrock/gamerefs/weak_ref.h"

class SynchedActorDataEntityWrapper {
public:
    virtual ~SynchedActorDataEntityWrapper() = default;
    gsl::not_null<void *> data_;         // SynchedActorDataComponent
    gsl::not_null<void *> flag_data_;    // ActorDataFlagComponent
    gsl::not_null<void *> dirty_flags_;  // ActorDataDirtyFlagsComponent
    WeakRef<EntityContext> entity_context_;
};
// static_assert(sizeof(SynchedActorDataEntityWrapper) == 40);
