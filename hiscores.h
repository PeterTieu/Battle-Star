#ifndef BATTLESTAR_HISCORES_DATA
#define BATTLESTAR_HISCORS_DATA

#include "splashkit.h"
#include "button.h"
#include "battlestar.h"
#include <vector>
#include "battlestar.h"
#include "menu.h"
#include "hiscore_cell.h"

#define NUM_BUTTONS_IN_HISCORES_MENU 2

//Define Hiscores struct
struct hiscores_data
{
    vector<button_data> buttons;             //Vector of Buttons
    vector<hiscore_cell_data> hiscore_cells; //Vector of Hiscores
    int button_pointer;                      //Button Pointer for indexing the Buttons
    background_data hiscores_background;     //Background
};

hiscores_data load_hiscores_data();                             //Load all Hiscores data
bool handle_hiscores_screen_input(hiscores_data &hiscores);     //Handle Input for the Hiscores Screen
void update_hiscores_screen(hiscores_data &hiscores);           //Update the Hiscores Screen
void draw_hiscores_screen(hiscores_data &hiscores);             //Draw the Hiscores Screen


#endif