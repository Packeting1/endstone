

# Class endstone::PlayerBucketEntityEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerBucketEntityEvent**](classendstone_1_1PlayerBucketEntityEvent.md)



_Represents an event that is called when a player captures an entity with a bucket._ 

* `#include <endstone/event/player/player_bucket_entity_event.h>`



Inherits the following classes: [endstone::Cancellable](classendstone_1_1Cancellable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**PlayerBucketEntityEvent**](classendstone_1_1PlayerBucketEntityEvent.md)) <br> |
|   | [**PlayerBucketEntityEvent**](#function-playerbucketentityevent) ([**Player**](classendstone_1_1Player.md) & player, [**Actor**](classendstone_1_1Actor.md) & entity, [**ItemStack**](classendstone_1_1ItemStack.md) entity\_bucket, [**EquipmentSlot**](namespaceendstone.md#enum-equipmentslot) hand, [**ItemStack**](classendstone_1_1ItemStack.md) original\_bucket) <br> |
|  [**Actor**](classendstone_1_1Actor.md) & | [**getEntity**](#function-getentity) () const<br>_Gets the entity being captured._  |
|  [**const**](classendstone_1_1Identifier.md) [**ItemStack**](classendstone_1_1ItemStack.md) & | [**getEntityBucket**](#function-getentitybucket) () const<br>_Gets the bucket item that will contain the captured entity._  |
|  [**EquipmentSlot**](namespaceendstone.md#enum-equipmentslot) | [**getHand**](#function-gethand) () const<br>_Gets the hand used to capture the entity._  |
|  [**const**](classendstone_1_1Identifier.md) [**ItemStack**](classendstone_1_1ItemStack.md) & | [**getOriginalBucket**](#function-getoriginalbucket) () const<br>_Gets the bucket used to capture the entity._  |
|  [**void**](classendstone_1_1Identifier.md) | [**setEntityBucket**](#function-setentitybucket) ([**ItemStack**](classendstone_1_1ItemStack.md) entity\_bucket) <br>_Sets the bucket item that will contain the captured entity._  |


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
endstone::PlayerBucketEntityEvent::ENDSTONE_EVENT (
    PlayerBucketEntityEvent
) 
```




<hr>



### function PlayerBucketEntityEvent 

```C++
inline endstone::PlayerBucketEntityEvent::PlayerBucketEntityEvent (
    Player & player,
    Actor & entity,
    ItemStack entity_bucket,
    EquipmentSlot hand,
    ItemStack original_bucket
) 
```




<hr>



### function getEntity 

_Gets the entity being captured._ 
```C++
inline Actor & endstone::PlayerBucketEntityEvent::getEntity () const
```





**Returns:**

entity being captured 





        

<hr>



### function getEntityBucket 

_Gets the bucket item that will contain the captured entity._ 
```C++
inline const  ItemStack & endstone::PlayerBucketEntityEvent::getEntityBucket () const
```





**Returns:**

bucket item containing the captured entity 





        

<hr>



### function getHand 

_Gets the hand used to capture the entity._ 
```C++
inline EquipmentSlot endstone::PlayerBucketEntityEvent::getHand () const
```





**Returns:**

hand used to capture the entity 





        

<hr>



### function getOriginalBucket 

_Gets the bucket used to capture the entity._ 
```C++
inline const  ItemStack & endstone::PlayerBucketEntityEvent::getOriginalBucket () const
```





**Returns:**

bucket used to capture the entity 





        

<hr>



### function setEntityBucket 

_Sets the bucket item that will contain the captured entity._ 
```C++
inline void endstone::PlayerBucketEntityEvent::setEntityBucket (
    ItemStack entity_bucket
) 
```





**Parameters:**


* `entity_bucket` new entity bucket 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_bucket_entity_event.h`

