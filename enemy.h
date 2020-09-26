#ifndef BATTLESTAR_ENEMY
#define BATTLESTAR_ENEMY

#include "splashkit.h"

//Define enumeration of Enemy Kind
enum enemy_kind
{
    PAWN,
    KNIGHT,
    ROOK,
    BISHOP
};

//Define Enemy
struct enemy_data
{
    sprite enemy_sprite; //Enemy sprite
    enemy_kind kind;     //Enemy Kind
};

//Define procedures and functions
enemy_data new_enemy(double x);                   //Create a new Enemy
void draw_enemy(const enemy_data &enemy_to_draw); //Draw the Enemy
void update_enemy(enemy_data &enemy_to_update);   //Update the Enemy

#endif