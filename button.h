#ifndef BATTLESTAR_BUTTON_DATA
#define BATTLESTAR_BUTTON_DATA

#include "splashkit.h"

//Define Button Kinds
enum button_kind
{
    //Main Menu Buttons
        //Unselected
   BUTTON_START_GAME_UNSELECTED,
   BUTTON_HISCORES_UNSELECTED,
   BUTTON_SETTINGS_UNSELECTED,
   BUTTON_QUIT_GAME_UNSELECTED,
        //Selected
   BUTTON_START_GAME_SELECTED,
   BUTTON_HISCORES_SELECTED,
   BUTTON_SETTINGS_SELECTED,
   BUTTON_QUIT_GAME_SELECTED,

    //Hiscores Screen Buttons
        //Unselected
   BUTTON_BACK_TO_MAIN_MENU_UNSELECTED,
   BUTTON_CLEAR_HISCORES_UNSELECTED,
        //Selected
   BUTTON_BACK_TO_MAIN_MENU_SELECTED,
   BUTTON_CLEAR_HISCORES_SELECTED,

    //Settings Screen Buttons
        //Unselected
   BUTTON_BACKGROUND_1_UNSELECTED,
   BUTTON_BACKGROUND_2_UNSELECTED,
   BUTTON_BACKGROUND_3_UNSELECTED,
   BUTTON_BACKGROUND_4_UNSELECTED,
   BUTTON_SHIP_1_UNSELECTED,
   BUTTON_SHIP_2_UNSELECTED,
   BUTTON_SHIP_3_UNSELECTED,
   BUTTON_SHIP_4_UNSELECTED,
        //Selected
   BUTTON_BACKGROUND_1_SELECTED,
   BUTTON_BACKGROUND_2_SELECTED,
   BUTTON_BACKGROUND_3_SELECTED,
   BUTTON_BACKGROUND_4_SELECTED,
   BUTTON_SHIP_1_SELECTED,
   BUTTON_SHIP_2_SELECTED,
   BUTTON_SHIP_3_SELECTED,
   BUTTON_SHIP_4_SELECTED
};

//Define Button struct
struct button_data
{
    sprite button_sprite; //Button Sprite
    button_kind kind; //Button Kind
};

button_data new_main_menu_button(button_kind kind, double y_pos);                       //Create a new Main Menu Button depending on the passed kind and x-position
button_data new_hiscores_screen_button(button_kind kind, double y_pos);                 //Create a new Hiscore Screen Button depending on the passed kind and x-position
button_data new_settings_screen_button(button_kind kind, double x_pos, double y_pos);   //Create a new Settings Screen Button depending on the passed kind and x-position
void update_button(button_data &button);                                                //Update the Button
void draw_button(button_data &button);                                                  //Draw the Button


#endif