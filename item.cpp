#include "item.h"
#include "splashkit.h"

//Obtain the Item bitmap corresponding to the enumerated kind
bitmap item_bitmap(item_kind kind)
{
    switch (kind)
    {
        case (MEDPACK):
        return bitmap_named("medpack");
        break;

        case (DIAMOND):
        return bitmap_named("diamond");
        break;

        case (AMMO):
        return bitmap_named("ammo");
        break;

        default:
        return bitmap_named("star");
    }
}

//Set the World x- and y- coordinates of the Item
void sprite_set_position(sprite &item_sprite, double coord_x, double coord_y)
{
    sprite_set_x(item_sprite, coord_x); //Set the x-coordinate of the Item
    sprite_set_y(item_sprite, coord_y); //Set the y-coordinate of the Item
}

//Set the angle of the Item
void sprite_set_random_angle(sprite &item_sprite, int min_degree, int max_degree)
{
    double random_angle; //Declare the angle variable

    random_angle = rnd(min_degree, max_degree); //Obtain randomn angle between the specified minimum and maximum
    sprite_set_rotation(item_sprite, random_angle); //Set the angle of the Item
}

//Create a new Item
item_data new_item()
{
    //Declare variables
    item_data result;
    double rand_coord_x;
    double rand_coord_y;

    result.kind = static_cast<item_kind>(rnd(4));       //Obtain a random Item Kind
    bitmap default_bitmap = item_bitmap(result.kind);   //Obtain a bitmap of the Item Kind
    result.item_sprite = create_sprite(default_bitmap); //Create the Item

    result.origin = static_cast<originating_side>(rnd(3)); //Obtain a random side in which the Item is to originate from (e.g. top, left or right of screen)

    //Define motion of the Item based on where it originates from
    switch(result.origin)
    {
        case(TOP_OF_SCREEN): //Top of screen
            rand_coord_x = rnd(0, screen_width()); //Obtain random x-coordinate
            sprite_set_position(result.item_sprite, rand_coord_x, camera_y() - sprite_height(result.item_sprite)); //Set the starting position of the Item
            sprite_set_random_angle(result.item_sprite, -90, 90); //Set the angle of motion of the Item
            break;
        case(LEFT_OF_SCREEN): //Left of screen
            rand_coord_y = rnd(camera_y(), camera_y() + screen_height()); //Obtain random xycoordinate
            sprite_set_position(result.item_sprite, 0 - sprite_width(result.item_sprite), rand_coord_y); //Set the starting position of the Item
            sprite_set_random_angle(result.item_sprite, -180, 0); //Set the angle of motion of the Item
            break;
        default: //Right of screen
            rand_coord_y = rnd(camera_y(), camera_y() + screen_height()); //Obtain random xycoordinate
            sprite_set_position(result.item_sprite, camera_x() + screen_width(), rand_coord_y); //Set the starting position of the Item
            sprite_set_random_angle(result.item_sprite, 0, 180); //Set the angle of motion of the Item
            break;
    }

    sprite_set_dy(result.item_sprite, rnd()*5); //Set the vertical velocity of the Item

    return result;
}

//Draw the Item
void draw_item(const item_data &item_to_draw)
{
    draw_sprite(item_to_draw.item_sprite); //Draw the Item
}

//Update the Item
void update_item(item_data &item_to_update)
{
    update_sprite(item_to_update.item_sprite); //Update the Item
}