#ifndef BATTLESTAR_MENU_DATA
#define BATTLESTAR_MENU_DATA

#include "splashkit.h"
#include "button.h"
#include "battlestar.h"
#include <vector>
#include "battlestar.h"
#include "background.h"
#include "player.h"

#define NUM_BUTTONS_IN_MAIN_MENU 4                    //Number of Buttons in the Main Menu
#define NUM_BUTTONS_IN_HISCORES_SCREEN 2              //Number of Buttons in the Hiscores Screen
const string database_name = "battlestar_database";   //Name of the Hiscores SQLite Database
const string database_table_name = "hiscores";        //Name of the Hiscores table in the SQLite Database

//Define Menu struct
struct menu_data
{
   vector<button_data> buttons;     //Vector of Buttons
   int button_pointer;              //Point of Buttons to point to buttons
   bool down_key_typed;             //Flag to indicate if 'down key' is typed
   bool up_key_typed;               //Flag to indicate if 'up key' is typed
   bool program_quit_requested;     //Flag to indicate if the Program Quit Request has been made
   bool is_game_running;            //Flag to indicate if the Game is Running
   bool is_hiscores_screen_running; //Flag to indicate if the Hiscores Screen is Running
   bool is_settings_screen_running; //Flag to indicate if the Settings Screen is Running
   background_data menu_background; //Background for the Main Menu
   background_data game_background; //Background for the Game
   player_data player;              //Player data
};

void load_resources();
menu_data new_menu();                     //Create a new Menu
void open_hiscores_screen();              //Open the Hiscores Screen
void open_settings_screen();              //Open the Settings Scren
void handle_menu_input(menu_data &menu);  //Handle Input for the Main Menu
void update_menu(menu_data &menu);        //Update Main Menu
void draw_menu(menu_data &menu);          //Draw the Main Menu


#endif