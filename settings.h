#ifndef BATTLESTAR_SETTINGS_DATA
#define BATTLESTAR_SETTINGS_DATA

#include "splashkit.h"
#include "button.h"
#include "battlestar.h"
#include <vector>
#include "battlestar.h"
#include "menu.h"
#include "hiscore_cell.h"
#include "player.h"
#include "background.h"

#define NUM_BUTTONS_IN_SETTINGS_MENU 9                      //Define the total number of Buttons in the Settings Screen
#define NUM_BACKGROUND_KIND_BUTTONS_IN_SETTINGS_SCREEN 4    //Define the number of 'Background Kind' Buttons in Settings Screen
#define NUM_SHIP_KIND_BUTTONS_IN_SETTINGS_SCREEN 4          //Define the number of 'Ship Kind' Buttons in the Settings Screen

//Define the Settings struct
struct settings_data
{
    vector<button_data> buttons;                                    //Vector of Buttons
    int button_pointer;                                             //Button Pointer
    bool background_chosen[NUM_BUTTONS_IN_SETTINGS_MENU];           //Flag to indicate a Background Kind is selected for the Game
    bool ship_chosen[NUM_SHIP_KIND_BUTTONS_IN_SETTINGS_SCREEN];     //Flag to indicate the Ship Kind selected for the Game
    background_data settings_screen_background;                     //Background of the Settings Screen
};

settings_data load_settings_data(menu_data &menu);                              //Load the Settings Screen
bool handle_settings_screen_input(menu_data &menu, settings_data &settings);    //Handle inputs for the Settings Screen
void update_settings_screen(settings_data &settings);                           //Update the Settings Screen
void draw_settings_screen(settings_data &settings);                             //Draw the Settings Screen


#endif