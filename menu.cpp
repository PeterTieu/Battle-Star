#include "splashkit.h"
#include "menu.h"
#include "button.h"
#include "battlestar.h"
#include <vector>
#include "hiscores.h"
#include "settings.h"
#include "player.h"

using namespace std;

//Start the Game
void start_game(menu_data &menu, game_data game)
{
    //While the flag indicating the Game is Running is true and user has not requested to quit the program
    while (menu.is_game_running && !quit_requested())
    {
        process_events(); //Allow SplashKit to react to user interactions

        load_random_events(game); //Load random aspects of the game, including:
                                  //   1:Asteroids appearance
                                  //   2:Items appearance
                                  //   3:Enemies appearance
                                  //   4:Enemies firing of Beams

        menu.is_game_running = handle_game_input(game); //Handle the keyboard inputs from the user

        clear_screen(COLOR_BLACK); //Clear the screen to a black color

        update_game(game); //Update the game, inclouding:
                           //   1:Player
                           //   2:Enemies
                           //   3:Player Beams
                           //   4:Enemy Beams
                           //   5:Asteroids
                           //   6:Items
                           //   7:Music
                           //   8:Limits of the HP, Ammo
                           //   9:All sprites that have left the screen
                           //  10:Star Mode
                           //  11:Game Over Effects

        draw_game(game); //Draw the game

        refresh_screen(60); //Refresh the screen at 60 fps
    }
}

//Open the Hiscores Screen
void open_hiscores_screen(menu_data &menu, hiscores_data &hiscores)
{
    //While the flag indicatig the Hiscores Screen is Running is true and the user has not requested to quit the program
    while (menu.is_hiscores_screen_running && !quit_requested())
    {
        process_events(); //Allow SplashKit to react to user interactions
        menu.is_hiscores_screen_running = handle_hiscores_screen_input(hiscores); //Handle the keyboard inputs from the user
        clear_screen(COLOR_BLACK); //Clear the screen to a black color
        update_hiscores_screen(hiscores);
        draw_hiscores_screen(hiscores);
        refresh_screen(60); //Refresh the screen at 60 fps
    }
}

//Open the Settings Screen
void open_settings_screen(menu_data &menu, settings_data &settings)
{
    while (menu.is_settings_screen_running && !quit_requested())
    {
        process_events(); //Allow SplashKit to react to user interactions
        menu.is_settings_screen_running = handle_settings_screen_input(menu, settings); //Handle the keyboard inputs from the user
        clear_screen(COLOR_BLACK); //Clear the screen to a black color
        update_settings_screen(settings);
        draw_settings_screen(settings);
        refresh_screen(60); //Refresh the screen at 60 fps
    }
}

//Quit the Game
void quit_game(menu_data &menu)
{
    menu.program_quit_requested = true; //Set the Program Quit Requested flag to true
}

//Create a new Menu
menu_data new_menu()
{
    menu_data menu; //Declare a Menu
    button_data button_start_game, button_hiscores, button_settings, button_quit_game; //Declare all the buttons for the Main Menu

    //Initialise the fields
    menu.button_pointer = 0;                 //Initialise the Button Pointer to 0
    menu.up_key_typed = false;               //Intialise the Up Key Typed flag to false
    menu.down_key_typed = false;             //Intialise the Up Key Typed flag to false
    menu.program_quit_requested = false;     //Initialise the Program Quit Requested flag to false
    menu.is_game_running = false;            //Initialise the Game Is Running flag to false
    menu.is_hiscores_screen_running = false; //Initialise the Hiscores Screen Running flag to false
    menu.is_settings_screen_running = false; //Initialise the Settings Screen Running flag to false

    menu.menu_background = load_background(BACKGROUND_MENU); //Load the background

    menu.player.kind = SKIN1; //Initialise the player kind to the SKIN1
    menu.game_background.kind = BACKGROUND_NEBULA; //Initialise the backgorund kind to BACKGROUND_NEBULA

    //Create the Buttons for the Main Menu and set them to the "unselected" state
    button_start_game = new_main_menu_button(BUTTON_START_GAME_UNSELECTED, screen_height()*0.4); //Start Game Button
    button_hiscores = new_main_menu_button(BUTTON_HISCORES_UNSELECTED, screen_height()*0.55);    //Hiscores Button
    button_settings = new_main_menu_button(BUTTON_SETTINGS_UNSELECTED, screen_height()*0.70);    //Settings Button
    button_quit_game = new_main_menu_button(BUTTON_QUIT_GAME_UNSELECTED, screen_height()*0.85);  //Quit Button

    //Add the Buttons to the Buttons vector of Menu
    menu.buttons.push_back(button_start_game); //Start Game Button
    menu.buttons.push_back(button_hiscores);   //Hiscores Button
    menu.buttons.push_back(button_settings);   //Settings Button
    menu.buttons.push_back(button_quit_game);  //Quit Button

    return menu; //Return Menu
}

//Switch the Button indexed by the value of the Button Pointer from "unselected" state to "selected" state
void button_switch_to_selected(menu_data &menu, int button_index)
{
    sprite_show_layer(menu.buttons[button_index].button_sprite, static_cast<int>(1)); //Show the "selected" layer
    sprite_hide_layer(menu.buttons[button_index].button_sprite, static_cast<int>(0)); //Hide the "unselected" layer
}

//Switch the Button indexed by the value of the Button Pointer from "selected" state to "unselectd" state
void button_switch_to_unselected(menu_data &menu, int button_index)
{
    sprite_show_layer(menu.buttons[button_index].button_sprite, static_cast<int>(0)); //Show the "unselected" layer
    sprite_hide_layer(menu.buttons[button_index].button_sprite, static_cast<int>(1)); //Hide the "selected" layer
}

//Toggle the Button indexed by the Button Pointer to the "selected" state, and toggle all other buttons to the "unselected" state
void toggle_button(menu_data &menu)
{

    //Iterate over all the Buttons vector
    for (int i = 0; i < menu.buttons.size(); i++)
    {
        //If the index of the Button matches the value of the Button Pointer
        if (menu.button_pointer == i)
        {
            button_switch_to_selected(menu, i); //Switch the Button from "unselected" state to "selected" state
        }
        else //If the index of the Button does not matche the value of the Button Pointer
        {
            button_switch_to_unselected(menu, i); //Switch the Button from "selected" state to "unselectd" state
        }
    }

    //Set boundaries of the Button Pointer
    if (menu.button_pointer == NUM_BUTTONS_IN_MAIN_MENU - 1 && menu.down_key_typed == true)
    {
        menu.button_pointer = -1;
    }

    if (menu.button_pointer == 0 && menu.up_key_typed == true)
    {
        menu.button_pointer = NUM_BUTTONS_IN_MAIN_MENU;
    }
}

//Handle Input for the Main Menu
void handle_menu_input(menu_data &menu)
{
    game_data game;             //Declare the Game
    hiscores_data hiscores;     //Declare Hiscores
    settings_data settings;     //Declare Settings

    //If the 'down' key is typed
    if (key_typed(DOWN_KEY))
    {
        menu.down_key_typed = true; //Set the Down Key Typed flag to true
        menu.up_key_typed = false; //Set the Up Key Typed flag to false

        toggle_button(menu); //Toggle the Button indexed by the Button Pointer to the "selected" state, and toggle all other buttons to the "unselected" state
        menu.button_pointer++; //Increment the Button Pointer
    }

    //If the 'up' key is typed
    if (key_typed(UP_KEY))
    {
        menu.up_key_typed = true; //Set the Up Key Typed flag to true
        menu.down_key_typed = false; //Set the Down Key Typed flag to false

        toggle_button(menu); //Toggle the Button indexed by the Button Pointer to the "selected" state, and toggle all other buttons to the "unselected" state
        menu.button_pointer--; //Increment the Button Pointer
    }

    //If the 'space' key is typed and the Down Key Typed flag is true
    if (key_typed(SPACE_KEY) && menu.down_key_typed)
    {
        //Execute according to the value of the Button Pointer
        switch (menu.button_pointer)
        {
        case (1): //Start Game
            menu.is_game_running = true;
            game = new_game(menu.game_background.kind, menu.player.kind); //Create a new Game
            start_game(menu, game);
            break;
        case (2): //Open Hiscores Screen
            menu.is_hiscores_screen_running = true;
            hiscores = load_hiscores_data();
            open_hiscores_screen(menu, hiscores);
            break;
        case (3): //Open Settings Screen
            menu.is_settings_screen_running = true;
            settings = load_settings_data(menu);
            open_settings_screen(menu, settings);
            break;
        case (0): //Quit Program
            menu.is_game_running = false;
            quit_game(menu);
            break;
        }
    }

    //If the 'space' key is typed and the Up Key Typed flag is true
    if (key_typed(SPACE_KEY) && menu.up_key_typed)
    {
        //Execute according to the value of the Button Pointer
        switch (menu.button_pointer)
        {
        case (3): //Start Game
            menu.is_game_running = true;
            game = new_game(menu.game_background.kind, menu.player.kind); //Create a new Game
            start_game(menu, game);
            break;
        case (0): //Open Hiscores Screen
            menu.is_hiscores_screen_running = true;
            hiscores = load_hiscores_data();
            open_hiscores_screen(menu, hiscores);
            break;
        case (1): //Open Settings Screen
            menu.is_settings_screen_running = true;
            settings = load_settings_data(menu);
            open_settings_screen(menu, settings);
            break;
        case (2): //Quit Program
            menu.is_game_running = false;
            quit_game(menu);
            break;
        }
    }
}

//Replay the Theme Song in the background after it finishes playing
void update_music()
{
    //If the theme song in the background has finished playing
    if (!music_playing())
    {
        play_music("theme_song"); //Play the theme song again
    }
}

//Update Main Menu
void update_menu(menu_data &menu)
{
    set_camera_x(0); //Re-initialise the World x-coordinate - in case the player has moved in the World if the game has been played
    set_camera_y(0); //Re-initialise the World y-coordinate - in case the player has moved in the World if the game has been played

    update_background(menu.menu_background); //Update the Background

    //Iterate through all the Buttons
    for (int i = 0; i < menu.buttons.size(); i++)
    {
        draw_button(menu.buttons[i]); //Draw the Button
    }

    update_music(); //Replay the Theme Song in the background after it finishes playing
}

//Draw the Main Menu
void draw_menu(menu_data &menu)
{
    bitmap play_icon, hiscores_icon, settings_icon, quit_icon; //Declare all the bitmaps of the icons for the Buttons

    draw_background(menu.menu_background); //Draw the Background

    draw_text("Battle", COLOR_GOLD, load_font("Sawah", "Sawah"), 52, screen_width()/2-285, screen_height()*0.07); //Draw the Gane title #1
    draw_text("Star", COLOR_WHITE, load_font("Sawah", "Sawah"), 52, screen_width()/2-190, screen_height()*0.17); //Draw the GAme title #2

    //Iterate through all the Buttons
    for (int i = 0; i < menu.buttons.size(); i++)
    {
        draw_button(menu.buttons[i]); //Draw the Button
    }

    //Load all the bitmaps fo the icons for the Buttons
    play_icon = bitmap_named("icon_play");          //Play icon
    hiscores_icon = bitmap_named("icon_hiscores");  //Hiscores icon
    settings_icon = bitmap_named("icon_settings");  //Settings icon
    quit_icon = bitmap_named("icon_quit");          //Quit icon

    //Draw the PLay Button annotations
    draw_bitmap(play_icon, sprite_x(menu.buttons[0].button_sprite), sprite_y(menu.buttons[0].button_sprite)-2); //Draw Play icon
    draw_text("Play", COLOR_PURPLE, load_font("ZebulonBold", "ZebulonBold"), 30, sprite_x(menu.buttons[0].button_sprite)+50, sprite_y(menu.buttons[0].button_sprite)+5); //Draw Play label

    //Draw the Hiscores Button annotations
    draw_bitmap(hiscores_icon, sprite_x(menu.buttons[1].button_sprite)+4, sprite_y(menu.buttons[1].button_sprite)+4); //Draw Hiscores icon
    draw_text("Hiscores", COLOR_PURPLE, load_font("ZebulonBold", "ZebulonBold"), 20, sprite_x(menu.buttons[1].button_sprite)+50, sprite_y(menu.buttons[1].button_sprite)+12); //Draw Hiscores label

    //Draw the Settings Button annotations
    draw_bitmap(settings_icon, sprite_x(menu.buttons[2].button_sprite)+4, sprite_y(menu.buttons[2].button_sprite)+4); //Draw the Settings icon
    draw_text("Settings", COLOR_PURPLE, load_font("ZebulonBold", "ZebulonBold"), 20, sprite_x(menu.buttons[2].button_sprite)+50, sprite_y(menu.buttons[2].button_sprite)+12); //Draw the Settings label

    //Draw the Quit Button annoations
    draw_bitmap(quit_icon, sprite_x(menu.buttons[3].button_sprite)+3, sprite_y(menu.buttons[3].button_sprite)+4); //Draw the Quit icon
    draw_text("Quit", COLOR_PURPLE, load_font("ZebulonBold", "ZebulonBold"), 30, sprite_x(menu.buttons[3].button_sprite)+50, sprite_y(menu.buttons[3].button_sprite)+5); //Draw the Quit label
}