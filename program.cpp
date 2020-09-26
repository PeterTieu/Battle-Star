//By: Peter Tieu
//Link to GitHub: https://github.com/PeterTieu/Battle-Star
//Link to YouTube Gameplay: https://www.youtube.com/watch?v=b79-vNMa7Xs&feature=youtu.be

#include "splashkit.h"
#include "battlestar.h"
#include "player.h"
#include "enemy.h"
#include "asteroid.h"
#include "item.h"
#include "background.h"
#include "menu.h"

//Main execution function
int main()
{
    // game_data game; //Declare Game variable
    load_resources(); //Load all resources in the resource bundle
    open_window("Battle Star - TieuTech", 1000, 812); //Open the Window

    menu_data menu = new_menu();  //Create a new Main Menu

    //While the program quit request has not been made and the Menu Quit Requested flag is false
    while (!quit_requested() && !menu.program_quit_requested)
    {
        process_events();           //Allow SplashKit to react to user interactions
        clear_screen();             //Clear the screen
        draw_menu(menu);            //Draw the Main Menu
        handle_menu_input(menu);    //Shows the button the cursor is on
        clear_screen(COLOR_BLACK);  //Clear the screen to a black color
        update_menu(menu);          //Update the Main Menu
        draw_menu(menu);            //Draw the Main Menu
        refresh_screen(60);         //Refresh the screen at 60 fps
    }

    return 0;
}
