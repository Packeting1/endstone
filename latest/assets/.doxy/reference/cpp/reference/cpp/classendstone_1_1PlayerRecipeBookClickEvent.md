

# Class endstone::PlayerRecipeBookClickEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerRecipeBookClickEvent**](classendstone_1_1PlayerRecipeBookClickEvent.md)



_Represents an event that is called when a player clicks a recipe in the recipe book._ 

* `#include <endstone/event/player/player_recipe_book_click_event.h>`



Inherits the following classes: [endstone::Cancellable](classendstone_1_1Cancellable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**PlayerRecipeBookClickEvent**](classendstone_1_1PlayerRecipeBookClickEvent.md)) <br> |
|   | [**PlayerRecipeBookClickEvent**](#function-playerrecipebookclickevent) ([**const**](classendstone_1_1Identifier.md) [**NotNull**](classendstone_1_1NotNull.md)&lt; [**Player**](classendstone_1_1Player.md) &gt; & player, std::string recipe, [**bool**](classendstone_1_1Identifier.md) make\_all) <br> |
|  [**const**](classendstone_1_1Identifier.md) std::string & | [**getRecipe**](#function-getrecipe) () const<br>_Gets the recipe identifier clicked by the player._  |
|  [**bool**](classendstone_1_1Identifier.md) | [**isMakeAll**](#function-ismakeall) () const<br>_Gets whether the player requested crafting as many copies as possible._  |
|  [**void**](classendstone_1_1Identifier.md) | [**setMakeAll**](#function-setmakeall) ([**bool**](classendstone_1_1Identifier.md) make\_all) <br>_Sets whether the player requests crafting as many copies as possible._  |


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
endstone::PlayerRecipeBookClickEvent::ENDSTONE_EVENT (
    PlayerRecipeBookClickEvent
) 
```




<hr>



### function PlayerRecipeBookClickEvent 

```C++
inline endstone::PlayerRecipeBookClickEvent::PlayerRecipeBookClickEvent (
    const  NotNull < Player > & player,
    std::string recipe,
    bool make_all
) 
```




<hr>



### function getRecipe 

_Gets the recipe identifier clicked by the player._ 
```C++
inline const std::string & endstone::PlayerRecipeBookClickEvent::getRecipe () const
```





**Returns:**

the recipe identifier 





        

<hr>



### function isMakeAll 

_Gets whether the player requested crafting as many copies as possible._ 
```C++
inline bool endstone::PlayerRecipeBookClickEvent::isMakeAll () const
```





**Returns:**

true if the player requested crafting all possible copies 





        

<hr>



### function setMakeAll 

_Sets whether the player requests crafting as many copies as possible._ 
```C++
inline void endstone::PlayerRecipeBookClickEvent::setMakeAll (
    bool make_all
) 
```





**Parameters:**


* `make_all` true to request crafting all possible copies 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_recipe_book_click_event.h`

