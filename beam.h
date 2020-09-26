#ifndef BATTLESTAR_BACKGROUND_BEAM
#define BATTLESTAR_BACKGROUND_BEAM

#include "splashkit.h"

#define BEAM_SPEED -9 //Define Beam Speed

//Define enumeration of Beam Kind
enum beam_kind
{
    LASER_BLUE, //Player Beam kind
    LASER_RED   //Enemy Beam kind
};

//Define enumeration of Beam Kind
enum beam_origin
{
    BEAM_PLAYER_ORIGIN, //Player Beam Origin
    BEAM_ENEMY_ORIGIN   //Enemy Beam Origin
};

//Define Beam
struct beam_data
{
    sprite beam_sprite; //Beam
    beam_kind kind;     //Beam Kind
};

//Define procedures and functions
beam_data new_beam(point_2d starting_point, beam_origin origin);
void update_beam(beam_data &beam_to_update); //Update the Player Beam
void draw_beam(const beam_data &beam_to_draw); //Draw the Beam

#endif