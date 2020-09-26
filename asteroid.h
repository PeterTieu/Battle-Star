#ifndef BATTLESTAR_ASTEROID
#define BATTLESTAR_ASTEROID

#include "splashkit.h"

//Enumerate Asteroid kinds
enum asteroid_kind
{
    ASTEROID_ROUND,
    ASTEROID_OVAL

};

//Define Asteroid struct
struct asteroid_data
{
    sprite asteroid_sprite; //Asteroid sprite
    asteroid_kind kind; //Asteroid kind
};

//Declare Asteroid procedures and functions
asteroid_data new_asteroid(double x_coordinate_starting, double x_coordinate_player, double y_coordinate_player); ////Create a new Asteroid
void draw_asteroid(const asteroid_data &asteroid_to_draw); //Draw the Asteroid
void update_asteroid(asteroid_data &asteroid_to_update); //Update the Asteroid

#endif