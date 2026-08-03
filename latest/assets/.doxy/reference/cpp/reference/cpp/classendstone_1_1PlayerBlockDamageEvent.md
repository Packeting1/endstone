

# Class endstone::PlayerBlockDamageEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerBlockDamageEvent**](classendstone_1_1PlayerBlockDamageEvent.md)



_Called when a player starts, continues, aborts, predicts, or stops damaging a block._ 

* `#include <endstone/event/player/player_block_damage_event.h>`



Inherits the following classes: [endstone::Cancellable](classendstone_1_1Cancellable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Action**](#enum-action)  <br> |




























































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PlayerBlockDamageEvent**](#function-playerblockdamageevent) ([**Player**](classendstone_1_1Player.md) & player, Action action, std::optional&lt; [**ItemStack**](classendstone_1_1ItemStack.md) &gt; item, [**Block**](classendstone_1_1Block.md) \* block, std::optional&lt; [**BlockFace**](namespaceendstone.md#enum-blockface) &gt; block\_face, std::optional&lt; [**Vector**](classendstone_1_1Vector.md) &gt; position) <br> |
|  Action | [**getAction**](#function-getaction) () const<br> |
|  [**Block**](classendstone_1_1Block.md) \* | [**getBlock**](#function-getblock) () const<br> |
|  std::optional&lt; [**BlockFace**](namespaceendstone.md#enum-blockface) &gt; | [**getBlockFace**](#function-getblockface) () const<br> |
|  [**const**](classendstone_1_1Identifier.md) std::optional&lt; [**ItemStack**](classendstone_1_1ItemStack.md) &gt; & | [**getItem**](#function-getitem) () const<br> |
|  std::optional&lt; [**Vector**](classendstone_1_1Vector.md) &gt; | [**getPosition**](#function-getposition) () const<br> |
|  [**bool**](classendstone_1_1Identifier.md) | [**hasBlock**](#function-hasblock) () const<br> |
|  [**bool**](classendstone_1_1Identifier.md) | [**hasItem**](#function-hasitem) () const<br> |


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
















































































## Public Types Documentation




### enum Action 

```C++
enum endstone::PlayerBlockDamageEvent::Action {
    Start,
    Abort,
    Stop,
    Continue,
    Predict
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
    std::optional< Vector > position
) 
```




<hr>



### function getAction 

```C++
inline Action endstone::PlayerBlockDamageEvent::getAction () const
```




<hr>



### function getBlock 

```C++
inline Block * endstone::PlayerBlockDamageEvent::getBlock () const
```




<hr>



### function getBlockFace 

```C++
inline std::optional< BlockFace > endstone::PlayerBlockDamageEvent::getBlockFace () const
```




<hr>



### function getItem 

```C++
inline const std::optional< ItemStack > & endstone::PlayerBlockDamageEvent::getItem () const
```




<hr>



### function getPosition 

```C++
inline std::optional< Vector > endstone::PlayerBlockDamageEvent::getPosition () const
```




<hr>



### function hasBlock 

```C++
inline bool endstone::PlayerBlockDamageEvent::hasBlock () const
```




<hr>



### function hasItem 

```C++
inline bool endstone::PlayerBlockDamageEvent::hasItem () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_block_damage_event.h`

