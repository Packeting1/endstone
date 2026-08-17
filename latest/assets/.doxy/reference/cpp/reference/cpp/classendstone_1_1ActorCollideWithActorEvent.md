

# Class endstone::ActorCollideWithActorEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**ActorCollideWithActorEvent**](classendstone_1_1ActorCollideWithActorEvent.md)



_Called when two Actors collide with each other._ [More...](#detailed-description)

* `#include <endstone/event/actor/actor_collide_with_actor_event.h>`



Inherits the following classes: [endstone::Cancellable](classendstone_1_1Cancellable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ActorCollideWithActorEvent**](#function-actorcollidewithactorevent) ([**const**](classendstone_1_1Identifier.md) [**NotNull**](classendstone_1_1NotNull.md)&lt; [**Actor**](classendstone_1_1Actor.md) &gt; & actor1, [**const**](classendstone_1_1Identifier.md) [**NotNull**](classendstone_1_1NotNull.md)&lt; [**Actor**](classendstone_1_1Actor.md) &gt; & actor2) <br> |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**ActorCollideWithActorEvent**](classendstone_1_1ActorCollideWithActorEvent.md)) <br> |
|  std::vector&lt; [**NotNull**](classendstone_1_1NotNull.md)&lt; [**Actor**](classendstone_1_1Actor.md) &gt; &gt; | [**getActors**](#function-getactors) () const<br>_Returns the Actors involved in this event._  |
|   | [**~ActorCollideWithActorEvent**](#function-actorcollidewithactorevent) () override<br> |


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


If this event is cancelled, the Actors will not be pushed away from each other. 


    
## Public Functions Documentation




### function ActorCollideWithActorEvent 

```C++
inline endstone::ActorCollideWithActorEvent::ActorCollideWithActorEvent (
    const  NotNull < Actor > & actor1,
    const  NotNull < Actor > & actor2
) 
```




<hr>



### function ENDSTONE\_EVENT 

```C++
endstone::ActorCollideWithActorEvent::ENDSTONE_EVENT (
    ActorCollideWithActorEvent
) 
```




<hr>



### function getActors 

_Returns the Actors involved in this event._ 
```C++
inline std::vector< NotNull < Actor > > endstone::ActorCollideWithActorEvent::getActors () const
```





**Returns:**

Actors that are involved in this event 





        

<hr>



### function ~ActorCollideWithActorEvent 

```C++
endstone::ActorCollideWithActorEvent::~ActorCollideWithActorEvent () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/actor/actor_collide_with_actor_event.h`

