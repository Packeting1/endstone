

# Class endstone::PlayerSetSpawnEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerSetSpawnEvent**](classendstone_1_1PlayerSetSpawnEvent.md)



_Called when a player's spawn is set, either by themselves or otherwise._ [More...](#detailed-description)

* `#include <endstone/event/player/player_set_spawn_event.h>`



Inherits the following classes: [endstone::Cancellable](classendstone_1_1Cancellable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**PlayerSetSpawnEvent**](classendstone_1_1PlayerSetSpawnEvent.md)) <br> |
|   | [**PlayerSetSpawnEvent**](#function-playersetspawnevent) ([**const**](classendstone_1_1Identifier.md) [**NotNull**](classendstone_1_1NotNull.md)&lt; [**Player**](classendstone_1_1Player.md) &gt; & player, [**Location**](classendstone_1_1Location.md) location) <br> |
|  [**const**](classendstone_1_1Identifier.md) [**Location**](classendstone_1_1Location.md) & | [**getLocation**](#function-getlocation) () const<br>_Gets the spawn location._  |
|  [**void**](classendstone_1_1Identifier.md) | [**setLocation**](#function-setlocation) ([**const**](classendstone_1_1Identifier.md) [**Location**](classendstone_1_1Location.md) & location) <br>_Sets the spawn location._  |


## Public Functions inherited from endstone::Cancellable

See [endstone::Cancellable](classendstone_1_1Cancellable.md)

| Type | Name |
| ---: | :--- |
| virtual [**void**](classendstone_1_1Identifier.md) | [**cancel**](classendstone_1_1Cancellable.md#function-cancel) () <br>_Cancel this event._  |
| virtual [**bool**](classendstone_1_1Identifier.md) | [**isCancelled**](classendstone_1_1Cancellable.md#function-iscancelled) () override const<br>_Gets the cancellation state of this event._  |
| virtual [**void**](classendstone_1_1Identifier.md) | [**setCancelled**](classendstone_1_1Cancellable.md#function-setcancelled) ([**bool**](classendstone_1_1Identifier.md) cancel) override<br>_Sets the cancellation state of this event._  |


## Public Functions inherited from endstone::ICancellable

See [endstone::ICancellable](classendstone_1_1ICancellable.md)

| Type | Name |
| ---: | :--- |
| virtual [**void**](classendstone_1_1Identifier.md) | [**cancel**](classendstone_1_1ICancellable.md#function-cancel) () = 0<br>_Cancels this event._  |
| virtual [**bool**](classendstone_1_1Identifier.md) | [**isCancelled**](classendstone_1_1ICancellable.md#function-iscancelled) () const = 0<br>_Gets the cancellation state of this event._  |
| virtual [**void**](classendstone_1_1Identifier.md) | [**setCancelled**](classendstone_1_1ICancellable.md#function-setcancelled) ([**bool**](classendstone_1_1Identifier.md) cancel) = 0<br>_Sets the cancellation state of this event._  |
| virtual  | [**~ICancellable**](classendstone_1_1ICancellable.md#function-icancellable) () = default<br> |
















































































## Detailed Description


Cancelling this event prevents the spawn change on supported native paths. 


    
## Public Functions Documentation




### function ENDSTONE\_EVENT 

```C++
endstone::PlayerSetSpawnEvent::ENDSTONE_EVENT (
    PlayerSetSpawnEvent
) 
```




<hr>



### function PlayerSetSpawnEvent 

```C++
inline endstone::PlayerSetSpawnEvent::PlayerSetSpawnEvent (
    const  NotNull < Player > & player,
    Location location
) 
```




<hr>



### function getLocation 

_Gets the spawn location._ 
```C++
inline const  Location & endstone::PlayerSetSpawnEvent::getLocation () const
```




<hr>



### function setLocation 

_Sets the spawn location._ 
```C++
inline void endstone::PlayerSetSpawnEvent::setLocation (
    const  Location & location
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_set_spawn_event.h`

