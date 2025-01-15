

# Class endstone::PlayerGameModeChangeEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerGameModeChangeEvent**](classendstone_1_1PlayerGameModeChangeEvent.md)



_Called when the GameMode of the player is changed._ 

* `#include <endstone/event/player/player_game_mode_change_event.h>`



Inherits the following classes: [endstone::PlayerEvent](classendstone_1_1PlayerEvent.md)
































## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**const**](classendstone_1_1Vector.md) std::string | [**NAME**](#variable-name)   = = "PlayerGameModeChangeEvent"<br> |










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PlayerGameModeChangeEvent**](#function-playergamemodechangeevent) ([**Player**](classendstone_1_1Player.md) & player, GameMode new\_game\_mode) <br> |
| virtual std::string | [**getEventName**](#function-geteventname) () override const<br> |
|  GameMode | [**getNewGameMode**](#function-getnewgamemode) () const<br>_Gets the GameMode the player is switched to._  |
|   | [**~PlayerGameModeChangeEvent**](#function-playergamemodechangeevent) () override<br> |


## Public Functions inherited from endstone::PlayerEvent

See [endstone::PlayerEvent](classendstone_1_1PlayerEvent.md)

| Type | Name |
| ---: | :--- |
|   | [**PlayerEvent**](classendstone_1_1PlayerEvent.md#function-playerevent) ([**Player**](classendstone_1_1Player.md) & player) <br> |
|  [**Player**](classendstone_1_1Player.md) & | [**getPlayer**](classendstone_1_1PlayerEvent.md#function-getplayer) () const<br> |
|   | [**~PlayerEvent**](classendstone_1_1PlayerEvent.md#function-playerevent) () override<br> |


## Public Functions inherited from endstone::Event

See [endstone::Event](classendstone_1_1Event.md)

| Type | Name |
| ---: | :--- |
|   | [**Event**](classendstone_1_1Event.md#function-event-12) ([**bool**](classendstone_1_1Vector.md) async=[**false**](classendstone_1_1Vector.md)) <br> |
|   | [**Event**](classendstone_1_1Event.md#function-event-22) ([**const**](classendstone_1_1Vector.md) [**Event**](classendstone_1_1Event.md) &) = delete<br> |
| virtual std::string | [**getEventName**](classendstone_1_1Event.md#function-geteventname) () const = 0<br> |
|  [**bool**](classendstone_1_1Vector.md) | [**isAsynchronous**](classendstone_1_1Event.md#function-isasynchronous) () const<br> |
|  [**Event**](classendstone_1_1Event.md) & | [**operator=**](classendstone_1_1Event.md#function-operator) ([**const**](classendstone_1_1Vector.md) [**Event**](classendstone_1_1Event.md) &) = delete<br> |
| virtual  | [**~Event**](classendstone_1_1Event.md#function-event) () = default<br> |
















































































## Public Static Attributes Documentation




### variable NAME 

```C++
const std::string endstone::PlayerGameModeChangeEvent::NAME;
```




<hr>
## Public Functions Documentation




### function PlayerGameModeChangeEvent 

```C++
inline explicit endstone::PlayerGameModeChangeEvent::PlayerGameModeChangeEvent (
    Player & player,
    GameMode new_game_mode
) 
```




<hr>



### function getEventName 

```C++
inline virtual std::string endstone::PlayerGameModeChangeEvent::getEventName () override const
```



Gets a user-friendly identifier for this event.




**Returns:**

name of this event 





        
Implements [*endstone::Event::getEventName*](classendstone_1_1Event.md#function-geteventname)


<hr>



### function getNewGameMode 

_Gets the GameMode the player is switched to._ 
```C++
inline GameMode endstone::PlayerGameModeChangeEvent::getNewGameMode () const
```





**Returns:**

player's new GameMode 





        

<hr>



### function ~PlayerGameModeChangeEvent 

```C++
endstone::PlayerGameModeChangeEvent::~PlayerGameModeChangeEvent () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_game_mode_change_event.h`

