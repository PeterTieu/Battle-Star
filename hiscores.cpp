#include "splashkit.h"
#include "menu.h"
#include "button.h"
#include "battlestar.h"
#include <vector>
#include "hiscores.h"
#include "hiscore_cell.h"
#include "background.h"
#include <algorithm>

using namespace std;

//Obtain the Hiscores from SQLite Database
vector<int> get_hiscores()
{
    vector<int> results;    //Declare vector to store Hiscores results
    database hiscores_db;   //Declare SQLite Database
    query_result query_res; //Declare Query Result for the SQLite Database
    int current_score;      //Declare variable to store the score at the cell pointed to by the Query Result

    hiscores_db = open_database("battlestar_database", "battlestar_database"); //Open/Create an SQLite Database for storing the Hiscores
    query_res = run_sql(hiscores_db, "select * from hiscores;");               //Run an SQL command to open the Hiscores table from the database

    //If the database has existing rows, i.e. has existing data
    if (has_row(query_res))
    {
        //While the database has rows
        while (has_row(query_res))
        {
            current_score = query_column_for_int(query_res, 0); //Get the score from current row on the first column
            results.push_back(current_score);                   //Add the current score to the Results vector
            get_next_row(query_res);                            //Point to the next row in the table
        }
    }
    else //If the database has no existing rows, i.e. has no data
    {
        hiscores_db = open_database("battlestar_database", "battlestar_database"); //Create an SQLite Database for storing the Hiscores
        run_sql(hiscores_db, "CREATE TABLE hiscores (id INTEGER PRIMARY KEY)");    //Run the SQL command to create a "hiscores" table in the database
                                                                                   //Make the first column a Primary Key and take data of type Integer
    }

    return results; //Return the vector of Hiscores
}

//Load all Hiscores data
hiscores_data load_hiscores_data()
{
    hiscores_data hiscores;                                      //Declare Hiscores variable
    hiscore_cell_data hiscore_cell;                              //Declare Hiscore Cell variable
    button_data clear_hiscores_button, back_to_main_menu_button; //Deckare Buttons for the Hiscores Screen

    hiscores.button_pointer = 0; //Initialise the Button Pointer to 0

    vector<int> hiscores_list = get_hiscores(); //Get all the Hiscores data and store it in the Hiscores vector
    int hiscore_cell_y = 150;                   //Declare and initialise the y-coordinate of the first Hiscore Cell sprite to 150
    int placing = 1;                            //Declare and initialise the placing of the first Hiscore cell to 1
    int score;                                  //Declare a score variable

    hiscores.hiscores_background = load_background(BACKGROUND_HISCORES_SCREEN); //Load the Background for the Hiscores Screen

    //If the size of the vector of Hiscores is less than or equal to 10
    if (hiscores_list.size() <= 10)
    {
        //Iterate over all the Hiscores in the vector of Hiscores
        for (int i = hiscores_list.size() - 1; i >= 0; i--)
        {
            score = hiscores_list[i]; //Obtain the Hiscore value

            hiscore_cell = new_hiscore_cell(placing, score, 400, hiscore_cell_y); //Create a Hiscore Cell to store the Hiscore value
            hiscores.hiscore_cells.push_back(hiscore_cell); //Add the Hiscore Cell to the vector of Hiscore Cells

            hiscore_cell_y += 50; //Increment the y-coordinate of the Hiscore Cell sprite by 50
            placing++; //Increment the placing
        }
    }
    else //If the size of the vector of the Hiscores is greater than 10 - take the top 10 Hiscores
    {
        //Iterate over the last 10 (i.e. top 10) Hiscores in the Hiscores vector
        for (int i = hiscores_list.size() - 1; i >= hiscores_list.size() - 10; i--)
        {
            score = hiscores_list[i]; //Obtain the Hiscore value

            hiscore_cell = new_hiscore_cell(placing, score, 400, hiscore_cell_y); //Create a Hiscore Cell to store the Hiscore value
            hiscores.hiscore_cells.push_back(hiscore_cell); //Add the Hiscore Cell to the vector of Hiscore Cells

            hiscore_cell_y += 50; //Increment the y-coordinate of the Hiscore Cell sprite by 50
            placing++; //Increment the placing
        }
    }

    clear_hiscores_button = new_hiscores_screen_button(BUTTON_CLEAR_HISCORES_UNSELECTED, screen_height() * 0.85); //Create the "Clear Hiscores" Button
    back_to_main_menu_button = new_hiscores_screen_button(BUTTON_BACK_TO_MAIN_MENU_UNSELECTED, screen_height() * 0.92); //Clear the "Back to Main Menu" Button

    hiscores.buttons.push_back(clear_hiscores_button); //Add the "Clear Hiscores" Button to the vector of Buttons
    hiscores.buttons.push_back(back_to_main_menu_button); //Add the "Back to Main Menu" Button to the vector of Buttons

    return hiscores; //Return the Hiscores
}

//Switch the Button indexed by the value of Button Pointer from "unselected" state to "selected" state
void button_switch_to_selected(hiscores_data &hiscores, int button_index)
{
    sprite_show_layer(hiscores.buttons[button_index].button_sprite, static_cast<int>(1)); //Show the "selected" layer
    sprite_hide_layer(hiscores.buttons[button_index].button_sprite, static_cast<int>(0)); //Hide the "unselected" layer
}

//Switch the Buttonindexed by the value of the Button Pointer from "selected" state to "unselectd" state
void button_switch_to_unselected(hiscores_data &hiscores, int button_index)
{
    sprite_show_layer(hiscores.buttons[button_index].button_sprite, static_cast<int>(0)); //Show the "unselected" layer
    sprite_hide_layer(hiscores.buttons[button_index].button_sprite, static_cast<int>(1));  //Hide the "selected" layer
}

//Toggle the Button indexed by the Button Pointer to the "selected" state, and toggle all other buttons to the "unselected" state
void toggle_to_next_hiscores_screen_button(hiscores_data &hiscores)
{
    //Iterate over all the Buttons vector
    for (int i = 0; i < hiscores.buttons.size(); i++)
    {
        //If the index of the Button matches the value of the Button Pointer
        if (hiscores.button_pointer == i)
        {
            button_switch_to_selected(hiscores, i);  //Switch the Button from "unselected" state to "selected" state
        }
        else //If the index of the Button does not matche the value of the Button Pointer
        {
            button_switch_to_unselected(hiscores, i); //Switch the Button from "selected" state to "unselectd" state
        }
    }

    //Set boundaries of the Button Pointer
    if (hiscores.button_pointer == NUM_BUTTONS_IN_HISCORES_SCREEN - 1)
    {
        hiscores.button_pointer = -1;
    }
}

//Handle Input for the Hiscores Screen
bool handle_hiscores_screen_input(hiscores_data &hiscores)
{
    bool is_hiscores_screen_running = true; //Declare and initialise the flag for the Hiscores Screen Running to true

    //If the 'down' key is pressed
    if (key_typed(DOWN_KEY))
    {
        toggle_to_next_hiscores_screen_button(hiscores); //Toggle the Button indexed by the Button Pointer to the "selected" state, and toggle all other buttons to the "unselected" state
        hiscores.button_pointer++; //Increment the Button Pointer
    }

    //If the 'down' key is pressed
    if (key_typed(SPACE_KEY))
    {
        database hiscores_db; //
        hiscores_db = open_database(database_name, database_name); //Creates/opens a database

        //Match the Button's index with the value of the Button Pointer
        switch (hiscores.button_pointer)
        {
        case (1): //Clear Hiscores Button
            run_sql(hiscores_db, "DROP TABLE " + database_table_name + ";"); //Run an SQL command to remove the Hiscores table in the database, i.e. clear all Hiscores in the database
            hiscores.hiscore_cells.clear(); //Remove all the elements of the Hiscore Cells vector
            break;
        case (0):
            is_hiscores_screen_running = false; //Set the Hiscores Screen Running flag to false
            break;
        }
    }

    return is_hiscores_screen_running; //Return the Hiscores Screen Running flag
}

//Update the Hiscores Screen
void update_hiscores_screen(hiscores_data &hiscores)
{
    update_background(hiscores.hiscores_background); //Update the Background

    //Iterate over all the Hiscore Cells
    for (int i = 0; i < hiscores.hiscore_cells.size(); i++)
    {
        update_hiscore_cell(hiscores.hiscore_cells[i]); //Update the Hiscore Cell
    }

    //Iterate over all the Hiscore Buttons
    for (int i = 0; i < hiscores.buttons.size(); i++)
    {
        update_button(hiscores.buttons[i]); //Update the Hiscore Button
    }
}

//Draw the Hiscores Screen
void draw_hiscores_screen(hiscores_data &hiscores)
{
    draw_background(hiscores.hiscores_background); //Draw the Background

    draw_text("HISCORES", COLOR_GREEN_YELLOW, load_font("ZebulonBold", "ZebulonBold"), 55, screen_width() / 2 - 150, screen_height() * 0.05); //Draw the Hiscores Screen heading

    //If there are no existing Hiscores
    if (hiscores.hiscore_cells.empty() || hiscores.hiscore_cells.size() == 0)
    {
        draw_text("ALL HISCORES", COLOR_LIGHT_BLUE, load_font("pcsenior", "pcsenior"), 40, 300, 280, option_to_screen()); //Display message to indicate all Hiscores have been cleared #1
        draw_text("CLEARED!", COLOR_LIGHT_BLUE, load_font("pcsenior", "pcsenior"), 40, 380, 340, option_to_screen()); //Display message to indicate all Hiscores have been cleared #2
    }
    else //If there are existing Hiscores
    {
        //Iterate over all the Hiscore Cells
        for (int i = 0; i < hiscores.hiscore_cells.size(); i++)
        {
            draw_hiscore_cell(hiscores.hiscore_cells[i]); //Draw the Hiscore Cell
        }
    }

    //Iterate over all the Hiscore Buttons
    for (int i = 0; i < hiscores.buttons.size(); i++)
    {
        draw_button(hiscores.buttons[i]); //Draw the Hiscore Button
    }

    draw_text("CLEAR", COLOR_PURPLE, load_font("ZebulonBold", "ZebulonBold"), 30,
              sprite_x(hiscores.buttons[0].button_sprite) + 25, sprite_y(hiscores.buttons[0].button_sprite) + 3); //Draw a label for the "Clear" Button

    draw_text("BACK", COLOR_PURPLE, load_font("ZebulonBold", "ZebulonBold"), 30,
              sprite_x(hiscores.buttons[1].button_sprite) + 40, sprite_y(hiscores.buttons[1].button_sprite) + 3); //Draw a label for the "Back" Button
}