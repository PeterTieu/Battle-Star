#ifndef BATTLESTAR_BACKGROUND_DATA
#define BATTLESTAR_BACKGROUND_DATA

#include "splashkit.h"

#define BACKGROUND_SPEED 0.6

//Define Background Kinds
enum background_kind
{
    BACKGROUND_MENU,            //Main Menu
    BACKGROUND_HISCORES_SCREEN, //Hiscores
    BACKGROUND_SETTINGS_SCREEN, //Settings
    BACKGROUND_NEBULA,          //Nebula (Game Background)
    BACKGROUND_CLOUDS,          //Clouds (Game Background)
    BACKGROUND_ABYSS,           //Abyss (Game Background)
    BACKGROUND_SEA              //Sea (Game Background)
};

//Define Background struct
struct background_data
{
    vector<sprite> background_sprites; //Vector of Backgrounds - contains 2 Background sprites
                                        //Each loop, starting from 1 screen height above to the screen
                                        //then ending at the bottom of the screen
    background_kind kind; //Background kind
};

//Define procedures and functions
background_data load_background(background_kind background_kind); //Load the Background
void update_background(background_data &background_to_update); //Update the Background
void draw_background(const background_data &background_to_draw); //Draw the Background

#endif