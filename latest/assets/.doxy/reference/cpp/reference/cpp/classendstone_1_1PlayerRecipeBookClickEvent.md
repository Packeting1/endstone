

# Class endstone::PlayerRecipeBookClickEvent



[**ClassList**](annotated.md) **>** [**endstone**](namespaceendstone.md) **>** [**PlayerRecipeBookClickEvent**](classendstone_1_1PlayerRecipeBookClickEvent.md)



_Represents an event that is called when a player clicks a recipe in the recipe book._ 

* `#include <endstone/event/player/player_recipe_book_click_event.h>`



Inherits the following classes: [endstone::PlayerEvent](classendstone_1_1PlayerEvent.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ENDSTONE\_EVENT**](#function-endstone_event) ([**PlayerRecipeBookClickEvent**](classendstone_1_1PlayerRecipeBookClickEvent.md)) <br> |
|   | [**PlayerRecipeBookClickEvent**](#function-playerrecipebookclickevent) ([**Player**](classendstone_1_1Player.md) & player, [**Recipe**](classendstone_1_1Recipe.md) & recipe, [**bool**](classendstone_1_1Identifier.md) shift\_click) <br> |
|  [**Recipe**](classendstone_1_1Recipe.md) & | [**getOriginalRecipe**](#function-getoriginalrecipe) () const<br>_Gets the recipe originally selected by the player._  |
|  [**Recipe**](classendstone_1_1Recipe.md) & | [**getRecipe**](#function-getrecipe) () const<br>_Gets the recipe that will be used for crafting._  |
|  [**bool**](classendstone_1_1Identifier.md) | [**isShiftClick**](#function-isshiftclick) () const<br>_Gets whether the player requested crafting as many copies as possible._  |
|  [**void**](classendstone_1_1Identifier.md) | [**setRecipe**](#function-setrecipe) ([**Recipe**](classendstone_1_1Recipe.md) & recipe) <br>_Sets the recipe that will be used for crafting._  |
|  [**void**](classendstone_1_1Identifier.md) | [**setShiftClick**](#function-setshiftclick) ([**bool**](classendstone_1_1Identifier.md) shift\_click) <br>_Sets whether the player requests crafting as many copies as possible._  |


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
endstone::PlayerRecipeBookClickEvent::ENDSTONE_EVENT (
    PlayerRecipeBookClickEvent
) 
```




<hr>



### function PlayerRecipeBookClickEvent 

```C++
inline endstone::PlayerRecipeBookClickEvent::PlayerRecipeBookClickEvent (
    Player & player,
    Recipe & recipe,
    bool shift_click
) 
```




<hr>



### function getOriginalRecipe 

_Gets the recipe originally selected by the player._ 
```C++
inline Recipe & endstone::PlayerRecipeBookClickEvent::getOriginalRecipe () const
```





**Returns:**

the originally selected recipe 





        

<hr>



### function getRecipe 

_Gets the recipe that will be used for crafting._ 
```C++
inline Recipe & endstone::PlayerRecipeBookClickEvent::getRecipe () const
```





**Returns:**

the recipe that will be used 





        

<hr>



### function isShiftClick 

_Gets whether the player requested crafting as many copies as possible._ 
```C++
inline bool endstone::PlayerRecipeBookClickEvent::isShiftClick () const
```





**Returns:**

true if the player requested shift-click crafting 





        

<hr>



### function setRecipe 

_Sets the recipe that will be used for crafting._ 
```C++
inline void endstone::PlayerRecipeBookClickEvent::setRecipe (
    Recipe & recipe
) 
```





**Parameters:**


* `recipe` the recipe to use 




        

<hr>



### function setShiftClick 

_Sets whether the player requests crafting as many copies as possible._ 
```C++
inline void endstone::PlayerRecipeBookClickEvent::setShiftClick (
    bool shift_click
) 
```





**Parameters:**


* `shift_click` true to request shift-click crafting 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/endstone/event/player/player_recipe_book_click_event.h`

