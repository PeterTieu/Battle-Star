#include "splashkit.h"
#include "menu.h"
#include "button.h"
#include "battlestar.h"
#include <vector>
#include <algorithm>
#include "settings.h"
#include "button.h"
#include "player.h"

using namespace std;

//Load the Settings Screen
settings_data load_settings_data(menu_data &menu)
{
    settings_data settings;                                                                         //Declare the Settings
    button_data background_1_button, background_2_button, background_3_button, background_4_button; //Declare the Buttons to select the Background Kind
    button_data skin_1_button, skin_2_button, skin_3_button, skin_4_button;                         //Delcare the Buttons to select the Ship Kind
    button_data back_button;                                                                        //Declare the "Back to Main Menu" Button

    settings.settings_screen_background = load_background(BACKGROUND_SETTINGS_SCREEN); //Load the Background for the Settings Screen
    settings.button_pointer = 0;                                                       //Initilias the Button Pointer to 0

    background_1_button = new_settings_screen_button(BUTTON_BACKGROUND_1_UNSELECTED, 225, screen_height() * 0.35); //Create a Button for Background #1
    background_2_button = new_settings_screen_button(BUTTON_BACKGROUND_2_UNSELECTED, 375, screen_height() * 0.35); //Create a Button for Background #2
    background_3_button = new_settings_screen_button(BUTTON_BACKGROUND_3_UNSELECTED, 525, screen_height() * 0.35); //Create a Button for Background #3
    background_4_button = new_settings_screen_button(BUTTON_BACKGROUND_4_UNSELECTED, 675, screen_height() * 0.35); //Create a Button for Background #4
    skin_1_button = new_settings_screen_button(BUTTON_SHIP_1_UNSELECTED, 225, screen_height() * 0.65);             //Create a Button for Ship #1
    skin_2_button = new_settings_screen_button(BUTTON_SHIP_2_UNSELECTED, 375, screen_height() * 0.65);             //Create a Button for Ship #2
    skin_3_button = new_settings_screen_button(BUTTON_SHIP_3_UNSELECTED, 525, screen_height() * 0.65);             //Create a Button for Ship #3
    skin_4_button = new_settings_screen_button(BUTTON_SHIP_4_UNSELECTED, 675, screen_height() * 0.65);             //Create a Button for Ship #4
    back_button = new_settings_screen_button(BUTTON_BACK_TO_MAIN_MENU_UNSELECTED, 415, screen_height() * 0.9);     //Create a Button for "Back to Main Menu"

    settings.buttons.push_back(background_1_button); //Add the Background #1 Button to the Buttons vector
    settings.buttons.push_back(background_2_button); //Add the Background #2 Button to the Buttons vector
    settings.buttons.push_back(background_3_button); //Add the Background #3 Button to the Buttons vector
    settings.buttons.push_back(background_4_button); //Add the Background #4 Button to the Buttons vector
    settings.buttons.push_back(skin_1_button);       //Add the Ship #1 Button to the Buttons vector
    settings.buttons.push_back(skin_2_button);       //Add the Ship #2 Button to the Buttons vector
    settings.buttons.push_back(skin_3_button);       //Add the Ship #3 Button to the Buttons vector
    settings.buttons.push_back(skin_4_button);       //Add the Ship #4 Button to the Buttons vector
    settings.buttons.push_back(back_button);         //Add the "Back to Menu" Button to the Buttons vector

    //Iterate over the Background Chosen vector
    for (int i = 0; i < NUM_BACKGROUND_KIND_BUTTONS_IN_SETTINGS_SCREEN; i++)
    {
        settings.background_chosen[i] = false; //Initialise to the vector of Background chosen to false
    }

    //Iterate over the Ship Chosen vector
    for (int i = 0; i < NUM_SHIP_KIND_BUTTONS_IN_SETTINGS_SCREEN; i++)
    {
        settings.ship_chosen[i] = false; //Initialise to the vector of Ship Chosen to false
    }

    //Set the element in the Background Chosen vector to true, according to the current Game Background
    switch (menu.game_background.kind)
    {
    case BACKGROUND_NEBULA:
        settings.background_chosen[0] = true;
        break;
    case BACKGROUND_ABYSS:
        settings.background_chosen[1] = true;
        break;
    case BACKGROUND_CLOUDS:
        settings.background_chosen[2] = true;
        break;
    default:
        settings.background_chosen[3] = true;
        break;
    }

    //Set the element in the Player Chosen vector to true, according to the current Game Background
    switch (menu.player.kind)
    {
    case SKIN1:
        settings.ship_chosen[0] = true;
        break;
    case SKIN2:
        settings.ship_chosen[1] = true;
        break;
    case SKIN3:
        settings.ship_chosen[2] = true;
        break;
    case SKIN4:
        settings.ship_chosen[3] = true;
        break;
    }

    return settings; //Return Settings
}

//Switch the Button indexed by the value of Button Pointer from "unselected" state to "selected" state
void button_switch_to_selected(settings_data &settings, int button_index)
{
    sprite_show_layer(settings.buttons[button_index].button_sprite, static_cast<int>(1)); //Show the "selected" layer
    sprite_hide_layer(settings.buttons[button_index].button_sprite, static_cast<int>(0)); //Hide the "unselected" layer
}

//Switch the Buttonindexed by the value of the Button Pointer from "selected" state to "unselectd" state
void button_switch_to_unselected(settings_data &settings, int button_index)
{
    sprite_show_layer(settings.buttons[button_index].button_sprite, static_cast<int>(0)); //Show the "unselected" layer
    sprite_hide_layer(settings.buttons[button_index].button_sprite, static_cast<int>(1)); //Hide the "selected" layer
}

//Toggle the Button indexed by the Button Pointer to the "selected" state, and toggle all other buttons to the "unselected" state
void toggle_to_next_settings_button(settings_data &settings)
{
    //Iterate over all the Buttons vector
    for (int i = 0; i < settings.buttons.size(); i++)
    {
        //If the index of the Button matches the value of the Button Pointer
        if (settings.button_pointer == i)
        {
            button_switch_to_selected(settings, i); //Switch the Button from "unselected" state to "selected" state
        }
        else //If the index of the Button does not matche the value of the Button Pointer
        {
            button_switch_to_unselected(settings, i); //Switch the Button from "selected" state to "unselectd" state
        }
    }

    //Set boundaries of the Button Pointer
    if (settings.button_pointer == NUM_BUTTONS_IN_SETTINGS_MENU - 1)
    {
        settings.button_pointer = -1;
    }
}

//Toggle the Background Chosen at the passed index to true, and toggle all the other Background Chosen to false
void toggle_background_choosen(settings_data &settings, int index_to_toggle)
{
    //Iterate over all the Background Chosen
    for (int i = 0; i < NUM_BACKGROUND_KIND_BUTTONS_IN_SETTINGS_SCREEN; i++)
    {
        settings.background_chosen[i] = false;              //Set the Background Chosen to false
        settings.background_chosen[index_to_toggle] = true; //Set the Background Chosen at the index to true
    }
}

//Toggle the Ship Chosen at the passed index to true, and toggle all the other Ship Chosen to false
void toggle_ship_choosen(settings_data &settings, int index_to_toggle)
{
    for (int i = 0; i < NUM_SHIP_KIND_BUTTONS_IN_SETTINGS_SCREEN; i++)
    {
        settings.ship_chosen[i] = false;              //Set the Ship Chosen to false
        settings.ship_chosen[index_to_toggle] = true; //Set the Ship Chosen at the index to true
    }
}

//Handle inputs for the Settings Screen
bool handle_settings_screen_input(menu_data &menu, settings_data &settings)
{
    bool is_settings_screen_running = true; //Flag to indicate if the Settings Screen is Running

    //If the 'right' key or 'down' key is pressed
    if (key_typed(RIGHT_KEY) || key_typed(DOWN_KEY))
    {
        toggle_to_next_settings_button(settings); //Toggle the Button indexed by the Button Pointer to the "selected" state, and toggle all other buttons to the "unselected" state
        settings.button_pointer++;                //Increment the Button Pointer
    }

    //If the 'Space' key is typed
    if (key_typed(SPACE_KEY))
    {
        //Execute according to the value of the Button Pointer
        switch (settings.button_pointer)
        {
        case (1):                                          //Background #1
            menu.game_background.kind = BACKGROUND_NEBULA; //Set the Game Background Kind to Nebula
            toggle_background_choosen(settings, 0);        //Toggle the Background Chosen at index 0 to true, and all others to false
            break;
        case (2):                                         //Background #2
            menu.game_background.kind = BACKGROUND_ABYSS; //Set the Game Background Kind to Abyss
            toggle_background_choosen(settings, 1);       //Toggle the Background Chosen at index 1 to true, and all others to false
            break;
        case (3):                                          //Background #3
            menu.game_background.kind = BACKGROUND_CLOUDS; //Set the Game Background Kind to Clouds
            toggle_background_choosen(settings, 2);        //Toggle the Background Chosen at index 2 to true, and all others to false
            break;
        case (4):                                       //Background #4
            menu.game_background.kind = BACKGROUND_SEA; //Set the Game Background Kind to Sea
            toggle_background_choosen(settings, 3);     //Toggle the Background Chosen at index 3 to true, and all others to false
            break;
        case (5):                             //Ship #1
            menu.player.kind = SKIN1;         //Set the Game Ship Kind to Skin 1
            toggle_ship_choosen(settings, 0); //Toggle the Ship Chosen at index 0 to true, and all others to false
            break;
        case (6):                             //Ship #2
            menu.player.kind = SKIN2;         //Set the Game Ship Kind to Skin 2
            toggle_ship_choosen(settings, 1); //Toggle the Ship Chosen at index 1 to true, and all others to false
            break;

        case (7):                             //Ship #3
            menu.player.kind = SKIN3;         //Set the Game Ship Kind to Skin 3
            toggle_ship_choosen(settings, 2); //Toggle the Ship Chosen at index 2 to true, and all others to false
            break;
        case (8):                             //Ship #4
            menu.player.kind = SKIN4;         //Set the Game Ship Kind to Skin 4
            toggle_ship_choosen(settings, 3); //Toggle the Ship Chosen at index 3 to true, and all others to false
            break;

        case (0):                               //Back to Main Menu
            is_settings_screen_running = false; //Set the Settings Screen Running flag to false
            break;
        }
    }

    return is_settings_screen_running; //Return the Settings Screen flag
}

//Update the Settings Screen
void update_settings_screen(settings_data &settings)
{
    update_background(settings.settings_screen_background); //Update the Background

    //Iterate over all the Buttons in the Settings Screen
    for (int i = 0; i < settings.buttons.size(); i++)
    {
        update_button(settings.buttons[i]); //Update all the Buttons
    }
}

//Draw the Settings Screen
void draw_settings_screen(settings_data &settings)
{
    draw_background(settings.settings_screen_background); //Draw the Background

    draw_text("SETTINGS", COLOR_BLUE_VIOLET, load_font("ZebulonBold", "ZebulonBold"), 55, screen_width() / 2 - 200, screen_height() * 0.05);  //Draw the Settings Screen heading
    draw_text("Pick Map", COLOR_YELLOW_GREEN, load_font("ZebulonBold", "ZebulonBold"), 30, screen_width() / 2 - 100, screen_height() * 0.27); //Draw the propmt to Pick a Map (Background)

    //Iterate over all the Buttons in Settings
    for (int i = 0; i < settings.buttons.size(); i++)
    {
        draw_button(settings.buttons[i]); //Draw the Button
    }

    draw_text("Pick Ship", COLOR_YELLOW_GREEN, load_font("ZebulonBold", "ZebulonBold"), 30, screen_width() / 2 - 110, screen_height() * 0.57); //Draw the prompt to Pick a Ship

    //Iterate over all the elements of the Ship Chosen vector
    for (int i = 0; i < NUM_SHIP_KIND_BUTTONS_IN_SETTINGS_SCREEN; i++)
    {
        //If the element at index i of the Ship Chosen vector is true
        if (settings.ship_chosen[i] == true)
        {
            double x_coord_ship_button = sprite_x(settings.buttons[NUM_BACKGROUND_KIND_BUTTONS_IN_SETTINGS_SCREEN + i].button_sprite); //Obtain the x-coordinate of the Button to select the Ship Kind
            double y_coord_ship_button = sprite_y(settings.buttons[NUM_BACKGROUND_KIND_BUTTONS_IN_SETTINGS_SCREEN + i].button_sprite); //Obtain the y-coordinate of the Button to select the Ship Kind

            bitmap red_check_mark = bitmap_named("red_check_mark");                //Obtain the bitmap for the check mark
            draw_bitmap(red_check_mark, x_coord_ship_button, y_coord_ship_button); //Draw the bitmap for the check mark
        }
    }

    //Iterate over all the elements of the Background Chosen vector
    for (int i = 0; i < NUM_BACKGROUND_KIND_BUTTONS_IN_SETTINGS_SCREEN; i++)
    {
        //If the element at index i of the Background Chosen vector is true
        if (settings.background_chosen[i] == true)
        {
            double x_coord_background_button = sprite_x(settings.buttons[i].button_sprite); //Obtain the x-coordinate of the Button to select the Background Kind
            double y_coord_background_button = sprite_y(settings.buttons[i].button_sprite); //Obtain the y-coordinate of the Button to select the Background Kind

            bitmap red_check_mark = bitmap_named("red_check_mark");                             //Obtain the bitmap for the check mark
            draw_bitmap(red_check_mark, x_coord_background_button, y_coord_background_button);  //Draw the bitmap for the check mark
        }
    }

    draw_text("BACK", COLOR_PURPLE, load_font("ZebulonBold", "ZebulonBold"), 30, sprite_x(settings.buttons[8].button_sprite) + 40,
    sprite_y(settings.buttons[8].button_sprite) + 3); //Draw the label for the "Back to Main Menu" Button
}
