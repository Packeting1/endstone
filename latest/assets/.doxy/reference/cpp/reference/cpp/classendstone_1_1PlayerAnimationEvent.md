

# Class endstone::PlayerAnimationEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerAnimationEvent**](classendstone_1_1PlayerAnimationEvent.md)



_Represents an event that is called when a player performs an animation._ 

* `#include <endstone/event/player/player_animation_event.h>`



Inherits the following classes: [endstone::Cancellable](classendstone_1_1Cancellable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**PlayerAnimationEvent**](classendstone_1_1PlayerAnimationEvent.md)) <br> |
|   | [**PlayerAnimationEvent**](#function-playeranimationevent) ([**Player**](classendstone_1_1Player.md) & player, [**PlayerAnimationType**](namespaceendstone.md#enum-playeranimationtype) animation\_type) <br> |
|  [**PlayerAnimationType**](namespaceendstone.md#enum-playeranimationtype) | [**getAnimationType**](#function-getanimationtype) () const<br>_Gets the type of animation performed by the player._  |


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
















































































## Public Functions Documentation




### function ENDSTONE\_EVENT 

```C++
endstone::PlayerAnimationEvent::ENDSTONE_EVENT (
    PlayerAnimationEvent
) 
```




<hr>



### function PlayerAnimationEvent 

```C++
inline endstone::PlayerAnimationEvent::PlayerAnimationEvent (
    Player & player,
    PlayerAnimationType animation_type
) 
```




<hr>



### function getAnimationType 

_Gets the type of animation performed by the player._ 
```C++
inline PlayerAnimationType endstone::PlayerAnimationEvent::getAnimationType () const
```





**Returns:**

the animation type 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_animation_event.h`

