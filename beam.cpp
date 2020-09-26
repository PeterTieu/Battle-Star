#include "splashkit.h"
#include "battlestar.h"
#include "player.h"
#include "beam.h"

using namespace std;

//Obtain the Beam bitmap corresponding to the enumerated kind
bitmap beam_bitmap(beam_kind kind)
{
    switch (kind)
    {
    case LASER_BLUE:
        return bitmap_named("beam_laser_blue");
    default:
        return bitmap_named("beam_laser_red");
    }
}

//Create a new Player or Enemy Beam
beam_data new_beam(point_2d starting_point, beam_origin origin)
{
    //Declare variables
    beam_data beam; //Beam
    bitmap beam_bmp; //Bitmap of the Beam

    //Obtain the Beam Origin corresponding to the enumerated kind
    switch(origin)
    {
        case (BEAM_PLAYER_ORIGIN): //Player Origin
            beam_bmp = beam_bitmap(LASER_BLUE); //Obtain bitmap of the Player Beam
            break;
        case(BEAM_ENEMY_ORIGIN): //Enemy Origin
            beam_bmp = beam_bitmap(LASER_RED);   //Obtain bitmap of the Enemy Beam
            break;
    }

    beam.beam_sprite = create_sprite(beam_bmp);       //Create the sprite of the Beam
    sprite_set_x(beam.beam_sprite, starting_point.x-10); //Set the starting World x-coordinate to create the beam
    sprite_set_y(beam.beam_sprite, starting_point.y-35); //Set the starting World y-coordinate to create the beam

    sprite_set_dx(beam.beam_sprite, 0); //Set random movement velocities (incl. speed and direction) for the Power Up in the 2D plane

    //Obtain the Beam Origin corresponding to the enumerated kind
    switch(origin)
    {
        case (BEAM_PLAYER_ORIGIN): //Player Origin
            sprite_set_dy(beam.beam_sprite, BEAM_SPEED); //Set the vertical velocity of the Player Beam to the Beam Speed
            break;
        case(BEAM_ENEMY_ORIGIN): //Enemy Origin
            sprite_set_dy(beam.beam_sprite, - BEAM_SPEED); //Set the vertical velocity of the Player Beam to the negative of the Beam Speed
            break;
    }

    return beam;
}

//Update the Beam
void update_beam(beam_data &beam_to_update)
{
    update_sprite(beam_to_update.beam_sprite); // Apply movement based on the velocity of the Beam
}

//Draw the Background
void draw_beam(const beam_data &beam_to_draw)
{
    draw_sprite(beam_to_draw.beam_sprite); //Draw the Beam
}