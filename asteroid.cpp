#include "asteroid.h"
#include "splashkit.h"
#include <cmath>

//Obtain the Asteroid bitmap enumerated by the kind
bitmap asteroid_bitmap(asteroid_kind kind)
{
    switch (kind)
    {
        case (ASTEROID_ROUND):
        return bitmap_named("asteroid_round");

        default:
        return bitmap_named("asteroid_oval");
    }
}

//Create a new Asteroid
asteroid_data new_asteroid(double x_coordinate_starting, double x_coordinate_player, double y_coordinate_player)
{
    asteroid_data result; //Declare Asteroid struct variable
    double opposite, adjacent, ratio, radians, degrees; //Declare trigonometry variables

    result.kind = static_cast<asteroid_kind>(rnd(2)); //Obtain a random Asteroid Kind

    bitmap default_bitmap = asteroid_bitmap(result.kind); //Declare and assign default bitmap for the Asteroid Kind

    result.asteroid_sprite = create_sprite(default_bitmap); //Create Asteroid sprite

    //Perform trigonometry calculations to ain the Asteroid at the Player
    opposite = x_coordinate_player - x_coordinate_starting; //Obtain the Opposite value of the triangle
    adjacent = y_coordinate_player - 0; //Obtain the Adjacent value of the triangle

    ratio = opposite/adjacent; //Obtain the ratio between the Opposite and Adjacent of the triange
    radians = atan(ratio); //Inverse tan of ratio to obtain the angle in radians
    degrees = -radians * (180.0/3.142); //Covert the angle in radians to degrees

    sprite_set_rotation(result.asteroid_sprite, degrees); //Set the angle of the Asteroid, aimed at the direction of the Player

    //Position the Asteroid in the specified x- and y- coordinates
    sprite_set_x(result.asteroid_sprite, x_coordinate_starting);
    sprite_set_y(result.asteroid_sprite, camera_y() - sprite_height(result.asteroid_sprite));

    sprite_set_dy(result.asteroid_sprite, rnd()*6); //Randomise the vertical velocity of the Asteroid

    return result;
}

//Draw the Asteroid
void draw_asteroid(const asteroid_data &asteroid_to_draw)
{
    draw_sprite(asteroid_to_draw.asteroid_sprite);
}

//Update the Asteroid
void update_asteroid(asteroid_data &asteroid_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(asteroid_to_update.asteroid_sprite);
}