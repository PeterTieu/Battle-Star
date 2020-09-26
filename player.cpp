#include "player.h"
#include "splashkit.h"

//Obtain the Player bitmap corresponding to the enumerated kind
bitmap player_bitmap(player_kind kind)
{
    switch (kind)
    {
    case SKIN1:
        return bitmap_named("skin1");
    case SKIN2:
        return bitmap_named("skin2");
    case SKIN3:
        return bitmap_named("skin3");
    default:
        return bitmap_named("skin4");
    }
}

//Create the Player
player_data new_player(player_kind ship_kind)
{
    //Declare variables
    player_data result; //Player
    int x_coordinate;   //World x-coordinate of the Player
    int y_coordinate;   //World y-coordinate of the Player

    bitmap default_bitmap = player_bitmap(ship_kind); //Declare and assign default bitmap for Ship Kind

    //Declare and initialise Player struct fields at the start of the game
    result.level = 1;   //Level at 1
    result.hp = 1;      //HP at 100%
    result.score = 0;   //Score at 0
    result.ammo = 18;   //Ammo at 18
    result.mana = 0;    //Mana at 0
    result.level = 1;   //Level at 1

    result.player_sprite = create_sprite(default_bitmap); //Obtain the bitmapof the Player

    //Define x- and y- coordinates to spawn the Player
    x_coordinate = (screen_width() - sprite_width(result.player_sprite)) / 2; //Obtain center x-coordinate of the screen
    y_coordinate = (screen_height() - sprite_height(result.player_sprite)) / 2; //Obtain the center y-coordiante of the screen
    sprite_set_x(result.player_sprite, x_coordinate); //Position the Player in the center x-coordinate of the screen
    sprite_set_y(result.player_sprite, y_coordinate); //Position the Player in the center y-coordinate of the screen

    return result;
}

//Update the player
void update_player(player_data &player_to_update)
{
    update_sprite(player_to_update.player_sprite); //Update the Item

    double top_edge = camera_y() + SCREEN_BORDER_TOP; //Obtain the World y-coordinate of the top of the screen

    point_2d sprite_center = center_point(player_to_update.player_sprite); //Get the center of the Player

    //If the position of the Player is above the top of the screen
    if (sprite_center.y < top_edge)
    {
        move_camera_by(0, sprite_center.y - top_edge); //Move the camera up to the point where the player is 'just' below the top of the screen
    }

    //Add boundaries to the right/left side of the screen so the that Player is not about to leave from these sides
    if (sprite_center.x < camera_x()) //If the Player tries to leave through the left of the screen
    {
        sprite_set_x(player_to_update.player_sprite, 0); //Reposition the Player to the left edge of the screen
    }
    else if (sprite_center.x > camera_x() + screen_width()) //If the Player tries to leave through the right of the screen
    {
        sprite_set_x(player_to_update.player_sprite, screen_width()-sprite_width(player_to_update.player_sprite)); //Reposition the Player to the
                                                                                                                    //right edge of the screen
    }
}

//Draw the Player
void draw_player(const player_data &player_to_draw)
{
    draw_sprite(player_to_draw.player_sprite); //Draw the Player
}
