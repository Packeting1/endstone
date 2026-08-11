

# File player\_edit\_book\_event.h

[**File List**](files.md) **>** [**endstone**](dir_6cf277b678674f97c7a2b6b3b2447b33.md) **>** [**event**](dir_f1d783c0ad83ee143d16e768ebca51c8.md) **>** [**player**](dir_7c05c37b25e9c9eccd9c63c2d313ba28.md) **>** [**player\_edit\_book\_event.h**](player__edit__book__event_8h.md)

[Go to the documentation of this file](player__edit__book__event_8h.md)


```C++
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

#include <memory>
#include <stdexcept>

#include "endstone/event/cancellable.h"
#include "endstone/event/player/player_event.h"
#include "endstone/inventory/meta/book_meta.h"

namespace endstone {

class PlayerEditBookEvent final : public Cancellable<PlayerEvent> {
public:
    ENDSTONE_EVENT(PlayerEditBookEvent);

    PlayerEditBookEvent(Player &player, int slot, const BookMeta &previous_book_meta, const BookMeta &new_book_meta,
                        bool signing)
        : Cancellable(player), slot_(slot), previous_book_meta_(cloneBookMeta(previous_book_meta)),
          new_book_meta_(cloneBookMeta(new_book_meta)), signing_(signing)
    {
    }

    [[nodiscard]] int getSlot() const { return slot_; }

    [[nodiscard]] const BookMeta &getPreviousBookMeta() const { return *previous_book_meta_; }

    [[nodiscard]] BookMeta &getNewBookMeta() { return *new_book_meta_; }

    [[nodiscard]] const BookMeta &getNewBookMeta() const { return *new_book_meta_; }

    void setNewBookMeta(const BookMeta &new_book_meta) { new_book_meta_ = cloneBookMeta(new_book_meta); }

    [[nodiscard]] bool isSigning() const { return signing_; }

    void setSigning(bool signing) { signing_ = signing; }

private:
    [[nodiscard]] static std::unique_ptr<BookMeta> cloneBookMeta(const BookMeta &meta)
    {
        auto clone = meta.clone();
        auto *book_meta = clone->as<BookMeta>();
        if (book_meta == nullptr) {
            throw std::invalid_argument("Book metadata must implement BookMeta");
        }
        clone.release();
        return std::unique_ptr<BookMeta>(book_meta);
    }

    int slot_;
    std::unique_ptr<BookMeta> previous_book_meta_;
    std::unique_ptr<BookMeta> new_book_meta_;
    bool signing_;
};

}  // namespace endstone
```


