#include "enemy.h"
#include "splashkit.h"

//Obtain the Enemy bitmap corresponding to the enumerated kind
bitmap enemy_bitmap(enemy_kind kind)
{
    switch (kind)
    {
    case PAWN:
        return bitmap_named("pawn");
    case BISHOP:
        return bitmap_named("bishop");
    case KNIGHT:
        return bitmap_named("knight");
    default:
        return bitmap_named("rook");
    }
}

//Create a new Enemy
enemy_data new_enemy(double x)
{
    enemy_data result; //Declare Enemy

    result.kind = static_cast<enemy_kind>(rnd(6)); //Obtain a random Enemy Kind
    bitmap default_bitmap = enemy_bitmap(result.kind); //Declare and assign default bitmap for the Enemy Kind
    result.enemy_sprite = create_sprite(default_bitmap); //Create the Enemy sprite

    //Position the Enemy in the specified x- and y- coordinates
    sprite_set_x(result.enemy_sprite, x);
    sprite_set_y(result.enemy_sprite, camera_y() - sprite_height(result.enemy_sprite) - 800);

    //Set random movement velocities (incl. speed and direction) for the Power Up in the 2D plane
    sprite_set_dy(result.enemy_sprite, rnd()*3+0.3);

    return result;
}

//Draw the Enemy
void draw_enemy(const enemy_data &enemy_to_draw)
{
    draw_sprite(enemy_to_draw.enemy_sprite); //Draw the Enemy
}

//Update the Enemy
void update_enemy(enemy_data &enemy_to_update)
{
    update_sprite(enemy_to_update.enemy_sprite); //Update the Enemy
}