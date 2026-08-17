

# Class endstone::CauldronLevelChangeEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**CauldronLevelChangeEvent**](classendstone_1_1CauldronLevelChangeEvent.md)



_Called when a cauldron's level or contents change._ [More...](#detailed-description)

* `#include <endstone/event/block/cauldron_level_change_event.h>`



Inherits the following classes: [endstone::Cancellable](classendstone_1_1Cancellable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**ChangeReason**](#enum-changereason)  <br>_Describes what caused the cauldron to change._  |




























































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CauldronLevelChangeEvent**](#function-cauldronlevelchangeevent) (std::unique\_ptr&lt; [**Block**](classendstone_1_1Block.md) &gt; block, [**Nullable**](classendstone_1_1Nullable.md)&lt; [**Actor**](classendstone_1_1Actor.md) &gt; entity, [**ChangeReason**](classendstone_1_1CauldronLevelChangeEvent.md#enum-changereason) reason, std::unique\_ptr&lt; [**BlockState**](classendstone_1_1BlockState.md) &gt; new\_state) <br> |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**CauldronLevelChangeEvent**](classendstone_1_1CauldronLevelChangeEvent.md)) <br> |
|  [**const**](classendstone_1_1Identifier.md) [**Nullable**](classendstone_1_1Nullable.md)&lt; [**Actor**](classendstone_1_1Actor.md) &gt; & | [**getEntity**](#function-getentity) () const<br>_Gets the entity responsible for the change._  |
|  [**BlockState**](classendstone_1_1BlockState.md) & | [**getNewState**](#function-getnewstate) () const<br>_Gets the state that will replace the cauldron._  |
|  [**ChangeReason**](classendstone_1_1CauldronLevelChangeEvent.md#enum-changereason) | [**getReason**](#function-getreason) () const<br>_Gets the reason for the change._  |


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


If this event is cancelled, the cauldron will not change. 


    
## Public Types Documentation




### enum ChangeReason 

_Describes what caused the cauldron to change._ 
```C++
enum endstone::CauldronLevelChangeEvent::ChangeReason {
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
    Unknown
};
```




<hr>
## Public Functions Documentation




### function CauldronLevelChangeEvent 

```C++
inline endstone::CauldronLevelChangeEvent::CauldronLevelChangeEvent (
    std::unique_ptr< Block > block,
    Nullable < Actor > entity,
    ChangeReason reason,
    std::unique_ptr< BlockState > new_state
) 
```




<hr>



### function ENDSTONE\_EVENT 

```C++
endstone::CauldronLevelChangeEvent::ENDSTONE_EVENT (
    CauldronLevelChangeEvent
) 
```




<hr>



### function getEntity 

_Gets the entity responsible for the change._ 
```C++
inline const  Nullable < Actor > & endstone::CauldronLevelChangeEvent::getEntity () const
```





**Returns:**

the responsible entity, or nullptr if there is none 





        

<hr>



### function getNewState 

_Gets the state that will replace the cauldron._ 
```C++
inline BlockState & endstone::CauldronLevelChangeEvent::getNewState () const
```





**Returns:**

the new block state 





        

<hr>



### function getReason 

_Gets the reason for the change._ 
```C++
inline ChangeReason endstone::CauldronLevelChangeEvent::getReason () const
```





**Returns:**

the change reason 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/block/cauldron_level_change_event.h`

