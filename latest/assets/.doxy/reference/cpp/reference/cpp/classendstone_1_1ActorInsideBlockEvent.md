

# Class endstone::ActorInsideBlockEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**ActorInsideBlockEvent**](classendstone_1_1ActorInsideBlockEvent.md)



_Called when an_ [_**Actor**_](classendstone_1_1Actor.md) _is inside a supported block._[More...](#detailed-description)

* `#include <endstone/event/actor/actor_inside_block_event.h>`



Inherits the following classes: [endstone::Cancellable](classendstone_1_1Cancellable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ActorInsideBlockEvent**](#function-actorinsideblockevent) ([**const**](classendstone_1_1Identifier.md) [**NotNull**](classendstone_1_1NotNull.md)&lt; [**Actor**](classendstone_1_1Actor.md) &gt; & actor, std::unique\_ptr&lt; [**Block**](classendstone_1_1Block.md) &gt; block) <br> |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**ActorInsideBlockEvent**](classendstone_1_1ActorInsideBlockEvent.md)) <br> |
|  [**Block**](classendstone_1_1Block.md) & | [**getBlock**](#function-getblock) () const<br>_Gets the block involved in this event._  |
|   | [**~ActorInsideBlockEvent**](#function-actorinsideblockevent) () override<br> |


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


Endstone currently fires this event for non-empty water, lava, and powder snow cauldrons.


If this event is cancelled, the block will not affect the [**Actor**](classendstone_1_1Actor.md). 


    
## Public Functions Documentation




### function ActorInsideBlockEvent 

```C++
inline endstone::ActorInsideBlockEvent::ActorInsideBlockEvent (
    const  NotNull < Actor > & actor,
    std::unique_ptr< Block > block
) 
```




<hr>



### function ENDSTONE\_EVENT 

```C++
endstone::ActorInsideBlockEvent::ENDSTONE_EVENT (
    ActorInsideBlockEvent
) 
```




<hr>



### function getBlock 

_Gets the block involved in this event._ 
```C++
inline Block & endstone::ActorInsideBlockEvent::getBlock () const
```





**Returns:**

the block containing the [**Actor**](classendstone_1_1Actor.md) 





        

<hr>



### function ~ActorInsideBlockEvent 

```C++
endstone::ActorInsideBlockEvent::~ActorInsideBlockEvent () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/actor/actor_inside_block_event.h`

