#include "splashkit.h"
#include "button.h"

using namespace std;

//Return the bitmap of the Button's kind
bitmap button_bitmap(button_kind kind)
{
    //Match passed kind parameter with the right Button bitmap
    switch (kind)
    {
    case BUTTON_START_GAME_UNSELECTED:
        return bitmap_named("button_start_game_unselected");
        break;
    case BUTTON_HISCORES_UNSELECTED:
        return bitmap_named("button_hiscores_unselected");
        break;
    case BUTTON_SETTINGS_UNSELECTED:
        return bitmap_named("button_settings_unselected");
        break;
    case BUTTON_QUIT_GAME_UNSELECTED:
        return bitmap_named("button_quit_game_unselected");
        break;

    case BUTTON_START_GAME_SELECTED:
        return bitmap_named("button_start_game_selected");
        break;
    case BUTTON_HISCORES_SELECTED:
        return bitmap_named("button_hiscores_selected");
        break;
    case BUTTON_SETTINGS_SELECTED:
        return bitmap_named("button_settings_selected");
        break;
    case BUTTON_QUIT_GAME_SELECTED:
        return bitmap_named("button_quit_game_selected");
        break;

    case BUTTON_CLEAR_HISCORES_UNSELECTED:
        return bitmap_named("button_clear_hiscores_uns");
        break;
    case BUTTON_CLEAR_HISCORES_SELECTED:
        return bitmap_named("button_clear_hiscores_sel");
        break;

    case BUTTON_BACKGROUND_1_UNSELECTED:
        return bitmap_named("button_background_1_uns");
        break;
    case BUTTON_BACKGROUND_2_UNSELECTED:
        return bitmap_named("button_background_2_uns");
        break;
    case BUTTON_BACKGROUND_3_UNSELECTED:
        return bitmap_named("button_background_3_uns");
        break;
    case BUTTON_BACKGROUND_4_UNSELECTED:
        return bitmap_named("button_background_4_uns");
        break;
    case BUTTON_SHIP_1_UNSELECTED:
        return bitmap_named("button_ship_1_unselected");
        break;
    case BUTTON_SHIP_2_UNSELECTED:
        return bitmap_named("button_ship_2_unselected");
        break;
    case BUTTON_SHIP_3_UNSELECTED:
        return bitmap_named("button_ship_3_unselected");
        break;
    case BUTTON_SHIP_4_UNSELECTED:
        return bitmap_named("button_ship_4_unselected");
        break;

    case BUTTON_BACKGROUND_1_SELECTED:
        return bitmap_named("button_background_1_sel");
        break;
    case BUTTON_BACKGROUND_2_SELECTED:
        return bitmap_named("button_background_2_sel");
        break;
    case BUTTON_BACKGROUND_3_SELECTED:
        return bitmap_named("button_background_3_sel");
        break;
    case BUTTON_BACKGROUND_4_SELECTED:
        return bitmap_named("button_background_4_sel");
        break;
    case BUTTON_SHIP_1_SELECTED:
        return bitmap_named("button_ship_1_selected");
        break;
    case BUTTON_SHIP_2_SELECTED:
        return bitmap_named("button_ship_2_selected");
        break;
    case BUTTON_SHIP_3_SELECTED:
        return bitmap_named("button_ship_3_selected");
        break;
    case BUTTON_SHIP_4_SELECTED:
        return bitmap_named("button_ship_4_selected");
        break;

    case BUTTON_BACK_TO_MAIN_MENU_UNSELECTED:
        return bitmap_named("button_back_to_main_menu_uns");
        break;
    default:
        return bitmap_named("button_back_to_main_menu_sel");
        break;
    }
}

//Create a new Main Menu Button depending on the passed kind and x-position
button_data new_main_menu_button(button_kind kind, double y_pos)
{
    button_data button; //Declare Button
    bitmap bttn_bitmap; //Declare Button bitmap

    bttn_bitmap = button_bitmap(kind); //Obtain the Button bitmap
    button.button_sprite = create_sprite(bttn_bitmap); //Create the Button sprite

    //Match the passed Button Kind with the possible Button Kinds and add a "selected" layer and hide it
    switch (kind)
    {
    case (BUTTON_START_GAME_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_START_GAME_SELECTED), "button_start_game_selected");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_START_GAME_UNSELECTED;
        break;

    case (BUTTON_HISCORES_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_HISCORES_SELECTED), "button_hiscores_selected");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_HISCORES_UNSELECTED;
        break;

    case (BUTTON_SETTINGS_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_SETTINGS_SELECTED), "button_settings_selected");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_SETTINGS_UNSELECTED;
        break;

    default:
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_QUIT_GAME_SELECTED), "button_quit_game_selected");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_QUIT_GAME_UNSELECTED;
    }

    sprite_set_x(button.button_sprite, screen_width() / 2 - sprite_width(button.button_sprite) / 2); //Set the x-coordinate of the Button sprite
    sprite_set_y(button.button_sprite, y_pos); //Set the y-coordinate of the Button sprite

    return button; //Return the Button
}

//Create a new Hiscore Screen Button depending on the passed kind and x-position
button_data new_hiscores_screen_button(button_kind kind, double y_pos)
{
    button_data button; //Declare Button
    bitmap bttn_bitmap; //Declare Button bitmap

    bttn_bitmap = button_bitmap(kind); //Obtain the Button bitmap
    button.button_sprite = create_sprite(bttn_bitmap); //Create the Button sprite

    //Match the passed Button Kind with the possible Button Kinds and add a "selected" layer and hide it
    switch (kind)
    {
    case (BUTTON_CLEAR_HISCORES_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_CLEAR_HISCORES_SELECTED), "button_clear_hiscores_sel");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_CLEAR_HISCORES_UNSELECTED;
        break;

    default:
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_BACK_TO_MAIN_MENU_SELECTED), "button_back_to_main_menu_sel");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_BACK_TO_MAIN_MENU_UNSELECTED;
        break;
    }

    sprite_set_x(button.button_sprite, screen_width() / 2 - sprite_width(button.button_sprite) / 2); //Set the x-coordinate of the Button sprite
    sprite_set_y(button.button_sprite, y_pos); //Set the y-coordinate of the Button sprite

    return button; //Return the Button
}

//Create a new Settings Screen Button depending on the passed kind and x-position
button_data new_settings_screen_button(button_kind kind, double x_pos, double y_pos)
{
    button_data button; //Declare Button
    bitmap bttn_bitmap; //Declare Button bitmap

    bttn_bitmap = button_bitmap(kind); //Obtain the Button bitmap
    button.button_sprite = create_sprite(bttn_bitmap); //Create the Button sprite

    //Match the passed Button Kind with the possible Button Kinds and add a "selected" layer and hide it
    switch (kind)
    {
    case (BUTTON_BACKGROUND_1_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_BACKGROUND_1_SELECTED), "button_background_1_sel");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_BACKGROUND_1_UNSELECTED;
        break;

    case (BUTTON_BACKGROUND_2_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_BACKGROUND_2_SELECTED), "button_background_2_sel");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_BACKGROUND_2_UNSELECTED;
        break;

    case (BUTTON_BACKGROUND_3_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_BACKGROUND_3_SELECTED), "button_background_3_sel");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_BACKGROUND_3_UNSELECTED;
        break;

    case (BUTTON_BACKGROUND_4_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_BACKGROUND_4_SELECTED), "button_background_4_sel");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_BACKGROUND_4_UNSELECTED;
        break;

    case (BUTTON_SHIP_1_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_SHIP_1_SELECTED), "button_ship_1_selected");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_SHIP_1_UNSELECTED;
        break;

    case (BUTTON_SHIP_2_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_SHIP_2_SELECTED), "button_ship_2_selected");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_SHIP_2_UNSELECTED;
        break;

    case (BUTTON_SHIP_3_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_SHIP_3_SELECTED), "button_ship_3_selected");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_SHIP_3_UNSELECTED;
        break;

    case (BUTTON_SHIP_4_UNSELECTED):
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_SHIP_4_SELECTED), "button_ship_4_selected");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_SHIP_4_UNSELECTED;
        break;

    default:
        sprite_add_layer(button.button_sprite, button_bitmap(BUTTON_BACK_TO_MAIN_MENU_SELECTED), "button_back_to_main_menu_sel");
        sprite_hide_layer(button.button_sprite, 1);
        button.kind = BUTTON_BACK_TO_MAIN_MENU_UNSELECTED;
        break;
    }

    sprite_set_x(button.button_sprite, x_pos); //Set the x-coordinate of the Button sprite
    sprite_set_y(button.button_sprite, y_pos); //Set the y-coordinate of the Button sprite

    return button; //Return the Button
}

//Update the Button
void update_button(button_data &button)
{
    update_sprite(button.button_sprite);
}

//Draw the Button
void draw_button(button_data &button)
{
    draw_sprite(button.button_sprite);
}
