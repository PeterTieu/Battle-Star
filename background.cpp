#include "splashkit.h"
#include "background.h"

using namespace std;

//Obtain the Background corresponding to the enumerated kind
bitmap background_bitmap(background_kind kind)
{
    switch (kind)
    {
    case BACKGROUND_MENU:
        return bitmap_named("background_menu");
    case BACKGROUND_HISCORES_SCREEN:
        return bitmap_named("background_hiscores_screen");
    case BACKGROUND_SETTINGS_SCREEN:
        return bitmap_named("background_settings_screen");
    case BACKGROUND_NEBULA:
        return bitmap_named("background_nebula");
    case BACKGROUND_CLOUDS:
        return bitmap_named("background_clouds");
    case BACKGROUND_ABYSS:
        return bitmap_named("background_abyss");
    default:
        return bitmap_named("background_sea");
    }
}

//Load the Background
background_data load_background(background_kind kind)
{
    //Declare variables
    background_data background;        //Backgrond entity
    bitmap space_background_bitmap;    //Background bitmap
    vector<sprite> background_sprites; //Background Sprite
    double top_edge_coordinate;        //World coordinate of the top edge of the window

    space_background_bitmap = background_bitmap(kind); //Declare and assign default bitmap for Background Kind

    //Add the two Background sprites to the vector of Background sprites
    background.background_sprites.push_back(create_sprite(space_background_bitmap));
    background.background_sprites.push_back(create_sprite(space_background_bitmap));

    top_edge_coordinate = camera_y(); //Obtain the dynamic World y-coordinate of the top edge of the window

    sprite_set_x(background.background_sprites[0], 0);                                     //Set the World x-coordinate of the first Background sprite
    sprite_set_y(background.background_sprites[0], 0);                                     //Set the World x-coordinate of the second Background sprite
    sprite_set_x(background.background_sprites[1], 0);                                     //Set the World x-coordinate of the second Background sprite
    sprite_set_y(background.background_sprites[1], top_edge_coordinate - screen_height()); //Set the World x-coordinate of the second Background sprite

    return background;
}

//Update the Background
void update_background(background_data &background_to_update)
{
    //Declare variables
    double top_edge_coordinate, bottom_edge_coordinate; //World y-coordintes of the top and bottom of the camera

    top_edge_coordinate = camera_y();                      //World y-coordinte of the top of the camera
    bottom_edge_coordinate = camera_y() + screen_height(); //World y-coordinte of the bottom of the camera

    //Sift through each of the (two) Background sprites in the Background Sprites vector
    for (int i = 0; i < background_to_update.background_sprites.size(); i++)
    {
        update_sprite(background_to_update.background_sprites[i]); //Update the sprite

        sprite_set_dy(background_to_update.background_sprites[i], BACKGROUND_SPEED); //Set the vertical velocity of the Background sprite (moving down)

        //If the sprite is below the bottom edge of th camera, then set the sprite to be (exactly) one screen height above the window
        if (sprite_y(background_to_update.background_sprites[i]) >= bottom_edge_coordinate)
        {
            sprite_set_x(background_to_update.background_sprites[i], 0); //Set the World x-coordinate of the sprite to zero
            sprite_set_y(background_to_update.background_sprites[i], top_edge_coordinate - screen_height()); //Set the World y-coordinate of the sprite to
                                                                                                                //(exactly) one screen height above the window
        }
    }
}

//Draw the Background
void draw_background(const background_data &background_to_draw)
{
    draw_sprite(background_to_draw.background_sprites[0]);
    draw_sprite(background_to_draw.background_sprites[1]);
}
