

# Class endstone::LevelLoadEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**LevelLoadEvent**](classendstone_1_1LevelLoadEvent.md)



_Called when a level is loaded._ 

* `#include <endstone/event/level/level_load_event.h>`



Inherits the following classes: [endstone::LevelEvent](classendstone_1_1LevelEvent.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**LevelLoadEvent**](classendstone_1_1LevelLoadEvent.md)) <br> |
|   | [**LevelLoadEvent**](#function-levelloadevent) ([**Level**](classendstone_1_1Level.md) & level) <br> |
|   | [**~LevelLoadEvent**](#function-levelloadevent) () override<br> |


## Public Functions inherited from endstone::LevelEvent

See [endstone::LevelEvent](classendstone_1_1LevelEvent.md)

| Type | Name |
| ---: | :--- |
|   | [**LevelEvent**](classendstone_1_1LevelEvent.md#function-levelevent) ([**Level**](classendstone_1_1Level.md) & level) <br> |
|  [**Level**](classendstone_1_1Level.md) & | [**getLevel**](classendstone_1_1LevelEvent.md#function-getlevel) () const<br>_Gets the level primarily involved with this event._  |


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
















































































## Public Functions Documentation




### function ENDSTONE\_EVENT 

```C++
endstone::LevelLoadEvent::ENDSTONE_EVENT (
    LevelLoadEvent
) 
```




<hr>



### function LevelLoadEvent 

```C++
inline explicit endstone::LevelLoadEvent::LevelLoadEvent (
    Level & level
) 
```




<hr>



### function ~LevelLoadEvent 

```C++
endstone::LevelLoadEvent::~LevelLoadEvent () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/level/level_load_event.h`

