

# File cauldron\_level\_change\_event.h

[**File List**](files.md) **>** [**block**](dir_992e9ad7dc69726476903ba283e33c71.md) **>** [**cauldron\_level\_change\_event.h**](cauldron__level__change__event_8h.md)

[Go to the documentation of this file](cauldron__level__change__event_8h.md)


```C++
#pragma once

#include <memory>
#include <utility>

#include "endstone/actor/actor.h"
#include "endstone/block/block_state.h"
#include "endstone/event/block/block_event.h"
#include "endstone/event/cancellable.h"
#include "endstone/util/pointers.h"

namespace endstone {

class CauldronLevelChangeEvent final : public Cancellable<BlockEvent> {
public:
    ENDSTONE_EVENT(CauldronLevelChangeEvent);

    enum class ChangeReason {
        BucketFill,
        BucketEmpty,
        BottleFill,
        BottleEmpty,
        BannerWash,
        ArmorWash,
        ShulkerWash,
        Extinguish,
        Evaporate,
        NaturalFill,
        Unknown,
    };

    CauldronLevelChangeEvent(std::unique_ptr<Block> block, Nullable<Actor> entity, ChangeReason reason,
                             std::unique_ptr<BlockState> new_state)
        : Cancellable(std::move(block)), entity_(std::move(entity)), reason_(reason), new_state_(std::move(new_state))
    {
    }

    [[nodiscard]] const Nullable<Actor> &getEntity() const { return entity_; }

    [[nodiscard]] ChangeReason getReason() const { return reason_; }

    [[nodiscard]] BlockState &getNewState() const { return *new_state_; }

private:
    Nullable<Actor> entity_;
    ChangeReason reason_;
    std::unique_ptr<BlockState> new_state_;
};

}  // namespace endstone
```


