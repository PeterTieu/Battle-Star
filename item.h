#ifndef BATTLESTAR_ITEM
#define BATTLESTAR_ITEM

#include "splashkit.h"

//Define enumeration of Item Kind
enum item_kind
{
    MEDPACK, //Increases HP
    DIAMOND, //Increases Score
    AMMO,    //Increases Ammunition
    STAR     //Gives shield for 15 seconds

};

//Define enumeration of the Origin Kind
enum originating_side
{
    TOP_OF_SCREEN,  //Origin of the Item at the TOP of the screen
    LEFT_OF_SCREEN, //Origin of the Item at the LEFT of the screen
    RIGHT_OF_SCREEN //Origin of the Item at the ROGJT of the screen
};

//Define Item
struct item_data
{
    sprite item_sprite;
    item_kind kind;
    originating_side origin;
};

//Define procedures and functions
item_data new_item(); ////Create a new Item
void draw_item(const item_data &item_to_draw); //Draw the Item
void update_item(item_data &item_to_update); //Update the Item

#endif