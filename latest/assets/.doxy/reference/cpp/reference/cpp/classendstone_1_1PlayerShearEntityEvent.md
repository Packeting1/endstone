

# Class endstone::PlayerShearEntityEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerShearEntityEvent**](classendstone_1_1PlayerShearEntityEvent.md)



_Called when a player shears an entity._ 

* `#include <endstone/event/player/player_shear_entity_event.h>`



Inherits the following classes: [endstone::Cancellable](classendstone_1_1Cancellable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**PlayerShearEntityEvent**](classendstone_1_1PlayerShearEntityEvent.md)) <br> |
|   | [**PlayerShearEntityEvent**](#function-playershearentityevent) ([**Player**](classendstone_1_1Player.md) & player, [**Actor**](classendstone_1_1Actor.md) & entity, [**EquipmentSlot**](namespaceendstone.md#enum-equipmentslot) hand, [**ItemStack**](classendstone_1_1ItemStack.md) item) <br>_Constructs a player shear entity event._  |
|  [**Actor**](classendstone_1_1Actor.md) & | [**getEntity**](#function-getentity) () const<br>_Gets the entity that was sheared._  |
|  [**EquipmentSlot**](namespaceendstone.md#enum-equipmentslot) | [**getHand**](#function-gethand) () const<br>_Gets the hand used to shear the entity._  |
|  [**const**](classendstone_1_1Identifier.md) [**ItemStack**](classendstone_1_1ItemStack.md) & | [**getItem**](#function-getitem) () const<br>_Gets the item used to shear the entity._  |


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
endstone::PlayerShearEntityEvent::ENDSTONE_EVENT (
    PlayerShearEntityEvent
) 
```




<hr>



### function PlayerShearEntityEvent 

_Constructs a player shear entity event._ 
```C++
inline endstone::PlayerShearEntityEvent::PlayerShearEntityEvent (
    Player & player,
    Actor & entity,
    EquipmentSlot hand,
    ItemStack item
) 
```





**Parameters:**


* `player` player who sheared the entity 
* `entity` entity that was sheared 
* `hand` hand used to shear the entity 
* `item` item used to shear the entity 




        

<hr>



### function getEntity 

_Gets the entity that was sheared._ 
```C++
inline Actor & endstone::PlayerShearEntityEvent::getEntity () const
```





**Returns:**

entity that was sheared 





        

<hr>



### function getHand 

_Gets the hand used to shear the entity._ 
```C++
inline EquipmentSlot endstone::PlayerShearEntityEvent::getHand () const
```





**Returns:**

hand used to shear the entity 





        

<hr>



### function getItem 

_Gets the item used to shear the entity._ 
```C++
inline const  ItemStack & endstone::PlayerShearEntityEvent::getItem () const
```





**Returns:**

item used to shear the entity 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_shear_entity_event.h`

