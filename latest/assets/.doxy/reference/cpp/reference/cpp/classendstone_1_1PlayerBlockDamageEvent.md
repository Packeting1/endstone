

# Class endstone::PlayerBlockDamageEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerBlockDamageEvent**](classendstone_1_1PlayerBlockDamageEvent.md)



_Called when a player starts, continues, aborts, predicts, stops, or creatively destroys a block._ [More...](#detailed-description)

* `#include <endstone/event/player/player_block_damage_event.h>`



Inherits the following classes: [endstone::Cancellable](classendstone_1_1Cancellable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Action**](#enum-action)  <br>_Represents the block damage action that triggered this event._  |




























































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PlayerBlockDamageEvent**](#function-playerblockdamageevent) ([**Player**](classendstone_1_1Player.md) & player, [**Action**](classendstone_1_1PlayerBlockDamageEvent.md#enum-action) action, std::optional&lt; [**ItemStack**](classendstone_1_1ItemStack.md) &gt; item, [**Block**](classendstone_1_1Block.md) \* block, std::optional&lt; [**BlockFace**](namespaceendstone.md#enum-blockface) &gt; block\_face, [**Vector**](classendstone_1_1Vector.md) position) <br> |
|  [**Action**](classendstone_1_1PlayerBlockDamageEvent.md#enum-action) | [**getAction**](#function-getaction) () const<br>_Gets the block damage action that triggered this event._  |
|  [**Block**](classendstone_1_1Block.md) \* | [**getBlock**](#function-getblock) () const<br>_Gets the block being damaged._  |
|  std::optional&lt; [**BlockFace**](namespaceendstone.md#enum-blockface) &gt; | [**getBlockFace**](#function-getblockface) () const<br>_Gets the face being damaged._  |
|  [**const**](classendstone_1_1Identifier.md) std::optional&lt; [**ItemStack**](classendstone_1_1ItemStack.md) &gt; & | [**getItem**](#function-getitem) () const<br>_Gets the item used to damage the block._  |
|  [**Vector**](classendstone_1_1Vector.md) | [**getPosition**](#function-getposition) () const<br>_Gets the block position._  |


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


Cancellation is honored for Start and Continue actions only. 


    
## Public Types Documentation




### enum Action 

_Represents the block damage action that triggered this event._ 
```C++
enum endstone::PlayerBlockDamageEvent::Action {
    Start,
    Abort,
    Stop,
    Continue,
    Predict,
    Creative
};
```




<hr>
## Public Functions Documentation




### function PlayerBlockDamageEvent 

```C++
inline endstone::PlayerBlockDamageEvent::PlayerBlockDamageEvent (
    Player & player,
    Action action,
    std::optional< ItemStack > item,
    Block * block,
    std::optional< BlockFace > block_face,
    Vector position
) 
```




<hr>



### function getAction 

_Gets the block damage action that triggered this event._ 
```C++
inline Action endstone::PlayerBlockDamageEvent::getAction () const
```





**Returns:**

the block damage action 





        

<hr>



### function getBlock 

_Gets the block being damaged._ 
```C++
inline Block * endstone::PlayerBlockDamageEvent::getBlock () const
```





**Returns:**

the block being damaged, or nullptr if unavailable 





        

<hr>



### function getBlockFace 

_Gets the face being damaged._ 
```C++
inline std::optional< BlockFace > endstone::PlayerBlockDamageEvent::getBlockFace () const
```





**Returns:**

the face being damaged, or std::nullopt if unavailable 





        

<hr>



### function getItem 

_Gets the item used to damage the block._ 
```C++
inline const std::optional< ItemStack > & endstone::PlayerBlockDamageEvent::getItem () const
```





**Returns:**

the item used to damage the block, or std::nullopt if unavailable 





        

<hr>



### function getPosition 

_Gets the block position._ 
```C++
inline Vector endstone::PlayerBlockDamageEvent::getPosition () const
```





**Returns:**

the block position 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_block_damage_event.h`

