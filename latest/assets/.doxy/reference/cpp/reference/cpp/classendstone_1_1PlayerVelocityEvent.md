

# Class endstone::PlayerVelocityEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerVelocityEvent**](classendstone_1_1PlayerVelocityEvent.md)



_Represents an event that is called when the velocity of a player changes._ 

* `#include <endstone/event/player/player_velocity_event.h>`



Inherits the following classes: [endstone::PlayerEvent](classendstone_1_1PlayerEvent.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**PlayerVelocityEvent**](classendstone_1_1PlayerVelocityEvent.md)) <br> |
|   | [**PlayerVelocityEvent**](#function-playervelocityevent) ([**Player**](classendstone_1_1Player.md) & player, [**Vector**](classendstone_1_1Vector.md) velocity) <br> |
|  [**Vector**](classendstone_1_1Vector.md) | [**getVelocity**](#function-getvelocity) () const<br>_Gets the velocity vector that will be sent to the player._  |
|  [**void**](classendstone_1_1Identifier.md) | [**setVelocity**](#function-setvelocity) ([**Vector**](classendstone_1_1Vector.md) velocity) <br>_Sets the velocity vector that will be sent to the player._  |


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




### function ENDSTONE\_EVENT 

```C++
endstone::PlayerVelocityEvent::ENDSTONE_EVENT (
    PlayerVelocityEvent
) 
```




<hr>



### function PlayerVelocityEvent 

```C++
inline explicit endstone::PlayerVelocityEvent::PlayerVelocityEvent (
    Player & player,
    Vector velocity
) 
```




<hr>



### function getVelocity 

_Gets the velocity vector that will be sent to the player._ 
```C++
inline Vector endstone::PlayerVelocityEvent::getVelocity () const
```





**Note:**

This method returns a copy; changes must be applied via [**setVelocity()**](classendstone_1_1PlayerVelocityEvent.md#function-setvelocity).




**Returns:**

the velocity vector 





        

<hr>



### function setVelocity 

_Sets the velocity vector that will be sent to the player._ 
```C++
inline void endstone::PlayerVelocityEvent::setVelocity (
    Vector velocity
) 
```





**Parameters:**


* `velocity` The velocity vector. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_velocity_event.h`

