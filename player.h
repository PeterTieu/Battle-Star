#ifndef BATTLESTAR_PLAYER_DATA
#define BATTLESTAR_PLAYER_DATA

#include "splashkit.h"

#define SCREEN_BORDER_TOP 480 //Define the co-ordinate distance from the top of the camera for which when the
                                //y-coordinate location of the player exceeds, the camera speeds its upwards movement

//Define enumeration of Player Kind
enum player_kind
{
    SKIN1, //Skin 1
    SKIN2, //Skin 2
    SKIN3, //Skin 3
    SKIN4  //Skin 4
};

//Define Player
struct player_data
{
    sprite player_sprite; //Player sprite
    player_kind kind;     //Player kind
    double hp;            //HP
    double mana;          //Mana - only able to fire Beams when 100% charged
    int score;            //Score
    int ammo;             //Ammo - for firing Beams
    int level;            //Level
    bool is_star_mode;    //Star Mode Flag
};

//Define procedures and functions
player_data new_player(player_kind ship_kind); //Create new Player
void update_player(player_data &player_to_update); //Update the Player
void draw_player(const player_data &player_to_draw); //Draw the Player

#endif