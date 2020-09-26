#ifndef BATTLESTAR_HALO
#define BATTLESTAR_HALO

#include "splashkit.h"
#include "player.h"

//Define enumeration of Halo Kind
struct halo_data
{
    sprite halo_sprite; //Halo sprite
};

//Define procedures and functions
halo_data new_halo(player_data &player);                            //Create a new Halo
void draw_halo(const halo_data &halo_to_draw, player_data &player); //Draw the Halo
void update_halo(halo_data &halo_to_update);                        //Update the Halo

#endif