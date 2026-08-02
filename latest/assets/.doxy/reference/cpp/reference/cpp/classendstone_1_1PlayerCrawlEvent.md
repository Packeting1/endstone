

# Class endstone::PlayerCrawlEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerCrawlEvent**](classendstone_1_1PlayerCrawlEvent.md)



_Called when a player starts or stops crawling._ 

* `#include <endstone/event/player/player_crawl_event.h>`



Inherits the following classes: [endstone::PlayerEvent](classendstone_1_1PlayerEvent.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PlayerCrawlEvent**](#function-playercrawlevent) ([**Player**](classendstone_1_1Player.md) & player, [**bool**](classendstone_1_1Identifier.md) crawling) <br> |
|  [**bool**](classendstone_1_1Identifier.md) | [**isCrawling**](#function-iscrawling) () const<br>_Gets whether the player is crawling._  |


## Public Functions inherited from endstone::PlayerEvent

See [endstone::PlayerEvent](classendstone_1_1PlayerEvent.md)

| Type | Name |
| ---: | :--- |
|   | [**PlayerEvent**](classendstone_1_1PlayerEvent.md#function-playerevent) ([**Player**](classendstone_1_1Player.md) & player) <br> |
|  [**Player**](classendstone_1_1Player.md) & | [**getPlayer**](classendstone_1_1PlayerEvent.md#function-getplayer) () const<br>_Returns the player involved in this event._  |
|   | [**~PlayerEvent**](classendstone_1_1PlayerEvent.md#function-playerevent) () override<br> |


## Public Functions inherited from endstone::Event

See [endstone::Event](classendstone_1_1Event.md)

| Type | Name |
| ---: | :--- |
|   | [**Event**](classendstone_1_1Event.md#function-event-13) ([**bool**](classendstone_1_1Identifier.md) async=[**false**](classendstone_1_1Identifier.md)) <br> |
|   | [**Event**](classendstone_1_1Event.md#function-event-23) ([**const**](classendstone_1_1Identifier.md) [**Event**](classendstone_1_1Event.md) &) = delete<br> |
|   | [**Event**](classendstone_1_1Event.md#function-event-33) ([**Event**](classendstone_1_1Event.md) &&) = default<br> |
| virtual std::string | [**getEventName**](classendstone_1_1Event.md#function-geteventname) () const = 0<br>_Gets a user-friendly identifier for this event._  |
|  [**bool**](classendstone_1_1Identifier.md) | [**isAsynchronous**](classendstone_1_1Event.md#function-isasynchronous) () const<br>_Any custom event that should not by synchronized with other events must use the specific constructor._  |
|  [**Event**](classendstone_1_1Event.md) & | [**operator=**](classendstone_1_1Event.md#function-operator) ([**const**](classendstone_1_1Identifier.md) [**Event**](classendstone_1_1Event.md) &) = delete<br> |
|  [**Event**](classendstone_1_1Event.md) & | [**operator=**](classendstone_1_1Event.md#function-operator_1) ([**Event**](classendstone_1_1Event.md) &&) = default<br> |
| virtual  | [**~Event**](classendstone_1_1Event.md#function-event) () = default<br> |






















## Protected Attributes inherited from endstone::PlayerEvent

See [endstone::PlayerEvent](classendstone_1_1PlayerEvent.md)

| Type | Name |
| ---: | :--- |
|  std::reference\_wrapper&lt; [**Player**](classendstone_1_1Player.md) &gt; | [**player\_**](classendstone_1_1PlayerEvent.md#variable-player_)  <br> |


























































## Public Functions Documentation




### function PlayerCrawlEvent 

```C++
inline explicit endstone::PlayerCrawlEvent::PlayerCrawlEvent (
    Player & player,
    bool crawling
) 
```




<hr>



### function isCrawling 

_Gets whether the player is crawling._ 
```C++
inline bool endstone::PlayerCrawlEvent::isCrawling () const
```





**Returns:**

true when starting to crawl, false when stopping 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_crawl_event.h`

