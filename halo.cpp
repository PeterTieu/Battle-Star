#include "halo.h"
#include "player.h"
#include "splashkit.h"

//Create a new Halo based on where the Player is
halo_data new_halo(player_data &player)
{
    halo_data result; //Declare a Halo

    bitmap halo_bitmap = bitmap_named("halo"); //Obtain the Halo bitmap
    result.halo_sprite = create_sprite(halo_bitmap); //Create a Halo

    //Position the Halo in the specified x- and y- coordinates
    sprite_set_x(result.halo_sprite, sprite_x(player.player_sprite)-14); //Set the World x-coordinate of the Halo based on the Player's
    sprite_set_y(result.halo_sprite, sprite_y(player.player_sprite)-20); //Set the World y-coordinate of the Halo based on the Player's

    return result;
}

//Draw the Halo
void draw_halo(const halo_data &halo_to_draw, player_data &player)
{
    sprite_set_x(halo_to_draw.halo_sprite, sprite_x(player.player_sprite)-14); //Set the Halo at the new the World x-coordinate
    sprite_set_y(halo_to_draw.halo_sprite, sprite_y(player.player_sprite)-20); //Set the Halo at the new the World y-coordinate
    draw_sprite(halo_to_draw.halo_sprite); //Draw the Halo
}

//Update the Halo
void update_halo(halo_data &halo_to_update)
{
    update_sprite(halo_to_update.halo_sprite); //Update the Halo
}