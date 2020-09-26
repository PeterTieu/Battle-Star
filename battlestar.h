#ifndef BATTLESTAR
#define BATTLESTAR

#include "splashkit.h"
#include <vector>
#include "player.h"
#include "enemy.h"
#include "asteroid.h"
#include "item.h"
#include "beam.h"
#include "halo.h"
#include "background.h"

//Define constants
#define PLAYER_SPEED_HORIZONTAL 8       //Player horizontal speed when left/right keeys are pressed
#define PLAYER_SPEED_VERTICAL 6         //Player vertical speed when up/down keys are pressed
#define BEAM_SHOOT_COOLDOWN_TIME 250    //Cooldown time in ms between each Player Beam being fired

using namespace std;

//Define Game struct
struct game_data
{
    player_data player;                 //Player
    vector<enemy_data> enemies;         //Enemies
    vector<asteroid_data> asteroids;    //Asteroids
    vector<item_data> items;            //Items
    vector<beam_data> player_beams;     //Player Beams
    vector<beam_data> enemy_beams;      //Enemy Beams
    background_data background;         //Background
    halo_data halo;                     //Halo
    timer game_timer;                   //Game Timer
    bool is_game_over;                  //Game Over Flag - to flag when Game Over has been reached (i.e. HP = 0)
    bool is_game_over_effects_executed; //Game Over Effects Executed Flag - to flag when effects of Game Over have been executed
};

//Define procedures and functions
void load_resources();                      //Load the resources
game_data new_game(background_kind background_kind, player_kind ship_kind);  //Create a New Game - loads the Background, creates a Player and the Game Timers
void load_random_events(game_data &game);   //Load Random Events for Enemies firing, Asteroids appearance and Items Appearance
bool handle_game_input(game_data &game);    //Handle to user inputs
void update_game(game_data &game);          //Update the Game
void draw_game(game_data &game);            //Draw the Game

#endif