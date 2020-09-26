#include "splashkit.h"
#include "battlestar.h"
#include "player.h"
#include "enemy.h"
#include "asteroid.h"
#include "item.h"
#include "halo.h"
#include "background.h"
#include "menu.h"
#include <cmath>

//============================== LOAD RESOURCES ========================================================================
//Load and play the Theme Song
void load_and_play_them_song()
{
    load_music("theme_song", "theme_song.wav"); //Load the theme song
    play_music("theme_song");                   //Play the theme song
    set_music_volume(0.4);                      //Set the volume of the theme song to 40%
}

//Load all images and sounds from the Resources folder
void load_resources()
{
    load_resource_bundle("game_bundle", "battlestar.txt");
    load_and_play_them_song();
}

//============================== NEW GAME ==============================================================================

//Create a new Game
game_data new_game(background_kind background_kind, player_kind ship_kind)
{
    game_data game; //Declare variable of type game_data

    //Initialise variables
    game.is_game_over = false;                  //Initialise the Game Over Flag to false
    game.is_game_over_effects_executed = false; //Initialise the Game Over Effects Executed Flag to false

    game.background = load_background(background_kind); //Load the background
    game.player = new_player(ship_kind);                //Create a new Player

    //Create and initialise the Game's Random Events Timer to manage random events
    game.game_timer = create_timer("Random events timer"); //Create the Random Events timer
    start_timer(game.game_timer);                          //Start the timer

    //Create and initialise the Player's Beam Timer to manage the Beam Shooting Cooldown
    game.game_timer = create_timer("Player Beam cooldown timer"); //Create the Player Beam timer
    start_timer("Player Beam cooldown timer");                    //Start the timer

    //Create and initialise the Player's Halo Timer to manage the Star Mode Effect
    game.game_timer = create_timer("Player Star Mode timer"); //Create the Player Star Mode timer
    game.player.is_star_mode = false;                         //Start the timer

    return game;
}

//============================== LOAD RANDOM EVENTS ==============================================================================

//Define the randomness of an Enemy spawning
void random_enemy_spawning(game_data &game, int time_division)
{
    int modulus_remainder = 20; //Modulus remainder

    //Control the frequency of enemies spawning
    if (!game.is_game_over_effects_executed) //If the Game Over Effects have not been executed yet
    {
        //If the remainder of the Random Events timer is between zero and the modulus remainder
        if (timer_ticks("Random events timer") % time_division >= 0 && timer_ticks("Random events timer") % time_division <= modulus_remainder)
        {
            double enemy_spawn_coordinate_x = rnd(0, screen_width() - 40); //Spawn the enemy at a random x-coordinate at the top of the screen
            game.enemies.push_back(new_enemy(enemy_spawn_coordinate_x));   //Add the enemy to the Enemies vector
        }
    }
}

//Define the randomness of an Enemy Beam being fired from an Enemy
void random_enemy_shooting(game_data &game)
{
    int time_division = 500;    //INCREASE to REDUCE frequency of random events
    int modulus_remainder = 15; //REDUCE to REDUCE frequency of random events

    //If there are Enemies
    if (!game.enemies.empty())
    {
        //Sift over each of the Enemies
        for (int i = 0; i < game.enemies.size(); i++)
        {
            //If the Enemy is in the view of the camera (i.e. they are on screen)
            if (sprite_y(game.enemies[i].enemy_sprite) >= camera_y() - sprite_height(game.enemies[i].enemy_sprite))
            {
                //If the remainder of the Random Events timer is between zero and the modulus remainer
                if (timer_ticks("Random events timer") % time_division > 0 && timer_ticks("Random events timer") % time_division <= modulus_remainder)
                {
                    double random = rnd(1, 1000); //Obtain a random number between 1 and 1000

                    //If the random number is less than 150
                    if (random < 150)
                    {
                        point_2d sprite_center = center_point(game.enemies[i].enemy_sprite);    //Obtain the center point of the Enemy
                        game.enemy_beams.push_back(new_beam(sprite_center, BEAM_ENEMY_ORIGIN)); //Create an Enemy Beam starting at the center Point of the Enemy
                                                                                                //and add it to the Enemy Beams vector
                        play_sound_effect("enemy_beam_laser_sound_effect");                     //Play a sound effect
                    }
                }
            }
        }
    }
}

//Define the randomness of an Asteroid appearing
void random_asteroid_spawning(game_data &game)
{
    int time_division = 3500;   //INCREASE to REDUCE frequency of random events
    int modulus_remainder = 10; //REDUCE to REDUCE frequency of random events

    //Control the frequency of an Asteroid appearing
    if (timer_ticks("Random events timer") % time_division >= 0 && timer_ticks("Random events timer") % time_division <= modulus_remainder)
    {
        // point_2d player_sprite_center = center_point(game.player.player_sprite); //Obtain the center point of the Player

        double asteroid_spawn_coordinate_x = rnd(0, screen_width() - 40);                                                                              //Obtain a random x-coordinate within the horizontal confines of the screen
        game.asteroids.push_back(new_asteroid(asteroid_spawn_coordinate_x, sprite_x(game.player.player_sprite), sprite_x(game.player.player_sprite))); //Create an Asteroid and add it
                                                                                                                                                       //to the Asteroids vector
    }
}

//Define the randomness of an Item apeparing
void random_item_spawning(game_data &game)
{
    int time_division = 1500;   //INCREASE to REDUCE frequency of random events
    int modulus_remainder = 10; //REDUCE to REDUCE frequency of random events

    //Control the frequency of an Item appearing
    if (timer_ticks("Random events timer") % time_division >= 0 && timer_ticks("Random events timer") % time_division <= modulus_remainder)
    {
        game.items.push_back(new_item()); //Create an Asteroid and add it to the Items vector
    }
}

//Define the Levels based on the Scores
//For each level, increase the frequency of Enemy spawning by decreasing the "time division" value
void define_levels(game_data &game)
{
    //Level 1
    if (game.player.score >= 0 && game.player.score < 300)
    {
        game.player.level = 1;
        random_enemy_spawning(game, 2100);
    }
    //Level 2
    else if (game.player.score >= 300 && game.player.score < 600)
    {
        game.player.level = 2;
        random_enemy_spawning(game, 2050);
    }
    //Level 3
    else if (game.player.score >= 600 && game.player.score < 900)
    {
        game.player.level = 3;
        random_enemy_spawning(game, 2000);
    }
    //Level 4
    else if (game.player.score >= 900 && game.player.score < 1200)
    {
        game.player.level = 4;
        random_enemy_spawning(game, 1950);
    }
    //Level 5
    else if (game.player.score >= 1200 && game.player.score < 1500)
    {
        game.player.level = 5;
        random_enemy_spawning(game, 1900);
    }
    //Level 6
    else if (game.player.score >= 1500 && game.player.score < 1800)
    {
        game.player.level = 6;
        random_enemy_spawning(game, 1850);
    }
    //Level 7
    else if (game.player.score >= 1800 && game.player.score < 2100)
    {
        game.player.level = 7;
        random_enemy_spawning(game, 1800);
    }
    //Level 8
    else if (game.player.score >= 2100 && game.player.score < 2400)
    {
        game.player.level = 8;
        random_enemy_spawning(game, 1750);
    }
    //Level 9
    else if (game.player.score >= 2400)
    {
        game.player.level = 9;
        random_enemy_spawning(game, 1700);
    }
}

//Load Random Events
void load_random_events(game_data &game)
{
    //If the Game Over Effects have been executed
    if (!game.is_game_over_effects_executed)
    {
        random_enemy_shooting(game);    //Define the randomness of an Enemy Beam being fired from an Enemy
        random_asteroid_spawning(game); //Define the randomness of an Asteroid appearing
        random_item_spawning(game);     //Define the randomness of an Item apeparing
        define_levels(game);            //Define the Levels based on the Scores
    }
}

//============================== HANDLE INPUT ==============================================================================

//Handle the player/user inputs
bool handle_game_input(game_data &game)
{
    bool is_game_running = true;

    //If the Game Over Effects have not been executed
    if (!game.is_game_over_effects_executed)
    {

        //Set the horizontal and vertical velocities of the player to zero
        sprite_set_dx(game.player.player_sprite, 0);
        sprite_set_dy(game.player.player_sprite, 0);

        point_2d sprite_center = center_point(game.player.player_sprite); //Obtain the center point of the Player
        double bottom_edge = camera_y() + screen_height() - 90;           //Find the World y-coordinate of the bottom fo the camera

        //Handle movement - rotating left/right/up/down

        //If the Left key is pressed down
        if (key_down(LEFT_KEY))
        {
            sprite_set_dx(game.player.player_sprite, -PLAYER_SPEED_HORIZONTAL); //Move Player left
        }

        //If the Right key is pressed down
        if (key_down(RIGHT_KEY))
        {
            sprite_set_dx(game.player.player_sprite, PLAYER_SPEED_HORIZONTAL); //Move Player right
        }

        //If the Up key is pressed down
        if (key_down(UP_KEY))
        {
            sprite_set_dy(game.player.player_sprite, -PLAYER_SPEED_VERTICAL); //Move Player Up
        }

        //If the Down key is pressed down
        if (key_down(DOWN_KEY))
        {
            sprite_set_dy(game.player.player_sprite, PLAYER_SPEED_VERTICAL); //Move Player Down

            //If the Player is at the bottom of the camera's boundary
            if (sprite_center.y >= bottom_edge + 50)
            {
                sprite_set_dy(game.player.player_sprite, 0); //Set the player's vertical velocity to zero so they can't move down
            }
        }

        //If the Player Beam Cooldown timer has reached a benchmark value (i.e the player can shoot again)
        if (timer_ticks("Player Beam cooldown timer") > BEAM_SHOOT_COOLDOWN_TIME)
        {
            //If the Space key is typed
            if (key_typed(SPACE_KEY))
            {
                game.player.ammo -= 1;                                            //Decrement the Ammo by 1
                point_2d sprite_center = center_point(game.player.player_sprite); //Obtaint the center point of the Player

                //If the Ammo amount is greater than or equal to zero
                if (game.player.ammo >= 0)
                {
                    game.player_beams.push_back(new_beam(sprite_center, BEAM_PLAYER_ORIGIN)); //Create a Player Beam and shoot it upwards
                    play_sound_effect("beam_laser_sound_effect");                             //Play a sound effect
                    reset_timer("Player Beam cooldown timer");                                //Reset the Player Beam cooldown timer
                }
                else
                {
                    play_sound_effect("no_ammo_sound_effect");
                }
            }
        }
    }

    //If the 'Q' key is typed - i.e. user has requested to quit the Game
    if (key_typed(Q_KEY))
    {
        //Clear all the vectors holding data for the Game
        game.background.background_sprites.clear(); //Clear the Background Sprites vector
        game.enemies.clear();                       //Clear the Enemies vector
        game.asteroids.clear();                     //Clear the Asteroids vector
        game.items.clear();                         //Clear the Items vector
        game.player_beams.clear();                  //Clear the Player Beams vector
        game.enemy_beams.clear();                   //Clear the Enemy Beams vector

        //Re-assign Game flag
        game.is_game_over = true;                  //Set the Game Over flag to true
        game.is_game_over_effects_executed = true; //Set the Game Over Effects Executed flag to true
        is_game_running = false;                   //Set the Game Running flag to false

        //======================= ADD DATA TO THE HISCORES DATABASE =======================
        database hiscores_db;   //Declare Hiscores database variable
        query_result query_res; //Declare Query Result variable to query the SQLite Database

        hiscores_db = open_database(database_name, database_name);                      //Create/open the SQLiteDatabase to store the Hiscores data
        query_res = run_sql(hiscores_db, "select * from " + database_table_name + ";"); //Run an SQL command to open the Hiscores table from the database

        //If the database has existing rows, i.e. has existing data
        if (has_row(query_res))
        {
            run_sql(hiscores_db, "INSERT INTO hiscores VALUES (" + to_string(game.player.score) + ");"); //Run SQL command to insert the Game Score to the "Hiscores" table of the Hiscores database
        }
        else //If the database has no existing rows, i.e. has no existing data
        {
            hiscores_db = open_database(database_name, database_name);                                                      //Creates/opens the SQLiteDatabase to store the Hiscores data
            run_sql(hiscores_db, "CREATE TABLE " + database_table_name + " (score INTEGER PRIMARY KEY);");                  //Run SQL command to create a table named "hiscores" in the database
            run_sql(hiscores_db, "INSERT INTO " + database_table_name + " VALUES (" + to_string(game.player.score) + ");"); //Run SQL command to insert the Game Score to the "Hiscores" table of the Hiscores database
        }

        free_all_query_results();   //Free all Query Results
        free_database(hiscores_db); //Free the database
    }

    return is_game_running; //Return the Game Running Flag
}

//============================== UPDATE GAME ==============================================================================

//Delete an Enemy at a specific index from the Enemies vector
void delete_enemy_index_from_vector(game_data &game, int index_to_delete)
{
    //Sift through all the Enemies
    if (index_to_delete >= 0 and index_to_delete < game.enemies.size())
    {
        int last_idx;                                           //Declare last index
        last_idx = game.enemies.size() - 1;                     //Obtain the last index of the Enemies vector
        game.enemies[index_to_delete] = game.enemies[last_idx]; //Assign the Enemy at the current index (i.e. Enemy to delete) to the last index
        game.enemies.pop_back();                                //Remove the Enemy to delete, that is now in the last index of the vector
    }
}

//Delete a Player Beam at a specific index from the Player Beams vector
void delete_player_beam_index_from_vector(game_data &game, int index_to_delete)
{
    //Sift through all the Player Beam in the Player Beams vector
    if (index_to_delete >= 0 and index_to_delete < game.player_beams.size())
    {
        int last_idx;                                                     //Declare last index
        last_idx = game.player_beams.size() - 1;                          //Obtain the last index of the Player Beams vector
        game.player_beams[index_to_delete] = game.player_beams[last_idx]; //Assign the Player Beam at the current index (i.e. Player Beam to delete) to the last index
        game.player_beams.pop_back();                                     //Remove the Player Beam to delete, that is now in the last index of the vector
    }
}

//Delete an Enemy Beam at a specific index from the Enemy Beams vector
void delete_enemy_beam_index_from_vector(game_data &game, int index_to_delete)
{
    //Sift through all the Knights in the Kingdom
    if (index_to_delete >= 0 and index_to_delete < game.enemy_beams.size())
    {
        int last_idx;                                                   //Declare last index
        last_idx = game.enemy_beams.size() - 1;                         //Obtain the last index of the Enemy Beams vector
        game.enemy_beams[index_to_delete] = game.enemy_beams[last_idx]; //Assign the Enemy Beam at the current index (i.e. Enemy Beam to delete) to the last index
        game.enemy_beams.pop_back();                                    //Remove the Enemy Beam to delete, that is now in the last index of the vector
    }
}

//Delete an Asteroid at a specific index from the Asteroids vector
void delete_asteroid_index_from_vector(game_data &game, int index_to_delete)
{
    //Sift through all the Knights in the Kingdom
    if (index_to_delete >= 0 and index_to_delete < game.asteroids.size())
    {
        int last_idx;                                               //Declare last index
        last_idx = game.asteroids.size() - 1;                       //Obtain the last index of the Asteroids vector
        game.asteroids[index_to_delete] = game.asteroids[last_idx]; //Assign the Asteroid at the current index (i.e. Asteroid to delete) to the last index
        game.asteroids.pop_back();                                  //Remove the Asteroid to delete, that is now in the last index of the vector
    }
}

//Delete an Asteroid at a specific index from the Asteroids vector
void delete_item_index_from_vector(game_data &game, int index_to_delete)
{
    //Sift through all the Knights in the Kingdom
    if (index_to_delete >= 0 and index_to_delete < game.items.size())
    {
        int last_idx;                                       //Declare last index
        last_idx = game.items.size() - 1;                   //Obtain the last index of the Asteroids vector
        game.items[index_to_delete] = game.items[last_idx]; //Assign the Knight at the current index (i.e. Knight to delete) to the last index
        game.items.pop_back();                              //Remove the Knight to delete, that is now in the last index of the vector
    }
}

//Define the effects of an Item on the Player's HP, Ammo and Score
void player_effects(player_data &player, double hp_effect, double ammo_effect, double score_effect)
{
    player.hp += hp_effect;       //Increase HP by the specified amount
    player.ammo += ammo_effect;   //Increase Ammo by the specified amount
    player.score += score_effect; //Increase Score by the specified amount
}

//------------------------------ DEFINE EFFECTS OF COLLISIONS -------------------------------------------------------------

//Define what happens when a Player Beam collides into an Enemy
void collision_player_beam_on_enemy(game_data &game)
{
    //Sift through all the current Enemies
    for (int j = 0; j < game.enemies.size(); j++)
    {
        //Sift through all the current Beams
        for (int i = 0; i < game.player_beams.size(); i++)
        {
            //If the Player Beam collides into an Enemy
            if (sprite_collision(game.player_beams[i].beam_sprite, game.enemies[j].enemy_sprite))
            {
                player_effects(game.player, 0, 0, 4);              //Increase the Score
                play_sound_effect("enemy_destroyed_sound_effect"); //Play a sound effect
                delete_enemy_index_from_vector(game, j);           //Remove the Enemy that was collised by the Beam
                delete_player_beam_index_from_vector(game, i);     //Remove the Beam that collied the Enemy
            }
        }
    }
}

//Define what happens when an Enemy Beam collides into the Player
void collision_enemy_beam_on_player(game_data &game)
{
    //Sift through all the current Beams
    for (int i = 0; i < game.enemy_beams.size(); i++)
    {
        //If the Enemy Beam collides into the Player
        if (sprite_collision(game.enemy_beams[i].beam_sprite, game.player.player_sprite))
        {
            play_sound_effect("enemy_destroyed_sound_effect"); //Play sound effect
            delete_enemy_beam_index_from_vector(game, i);      //Remove the Beam that collided the Player

            //If the Star Mode is not on
            if (!game.player.is_star_mode)
            {
                game.player.hp -= 0.04; //Reduce the HP
            }
        }
    }
}

//Define what happens when an Enemy collides into the Player
void collision_enemy_on_player(game_data &game)
{
    //Sift through all the current Enemies
    for (int i = 0; i < game.enemies.size(); i++)
    {
        //If the Enemy collides into the Player
        if (sprite_collision(game.enemies[i].enemy_sprite, game.player.player_sprite))
        {
            play_sound_effect("enemy_destroyed_sound_effect"); //Play sound effect
            delete_enemy_index_from_vector(game, i);           //Remove the Enemy that collided the Player

            //If the Star Mode is not on
            if (!game.player.is_star_mode)
            {
                game.player.hp -= 0.07; //Reduce the HP
                // game.player.hp -= 0.5;
            }
        }
    }
}

//Define what happens when an Asteroid collides into the Player
void collision_asteroid_on_player(game_data &game)
{
    //Sift through all the current Asteroids
    for (int i = 0; i < game.asteroids.size(); i++)
    {
        //If the Asteroid collides into the Player
        if (sprite_collision(game.asteroids[i].asteroid_sprite, game.player.player_sprite))
        {
            play_sound_effect("enemy_destroyed_sound_effect"); //Play sound effect
            delete_asteroid_index_from_vector(game, i);        //Remove the Asteroid that collided the Player

            //If the Star Mode is not on
            if (!game.player.is_star_mode)
            {
                game.player.hp -= 0.09; //Reduce the HP
            }
        }
    }
}

//Define what happens when an Asteroid collides into an Enemy
void collision_asteroid_on_enemy(game_data &game)
{
    //Sift through all the current Asteroids
    for (int j = 0; j < game.asteroids.size(); j++)
    {
        //Sift through all the current Enemies
        for (int i = 0; i < game.enemies.size(); i++)
        {
            //If the specified Asteroid collides into the Player
            if (sprite_collision(game.asteroids[j].asteroid_sprite, game.enemies[i].enemy_sprite))
            {
                play_sound_effect("enemy_destroyed_sound_effect"); //Play sound effect
                delete_enemy_index_from_vector(game, i);           //Remove the Asteroid that collided the Enemy
            }
        }
    }
}

//Define what happens when a Player Beam collides into an Asteroid
void collision_player_beam_on_asteroid(game_data &game)
{
    //Sift through all the current Asteroids
    for (int j = 0; j < game.asteroids.size(); j++)
    {
        //Sift through all the current Player Beams
        for (int i = 0; i < game.player_beams.size(); i++)
        {
            //If the specified Asteroid collides into the specified Player Beam
            if (sprite_collision(game.asteroids[j].asteroid_sprite, game.player_beams[i].beam_sprite))
            {
                player_effects(game.player, 0, 0, 6);              //Increase the Score
                play_sound_effect("enemy_destroyed_sound_effect"); //Play sound effect
                delete_asteroid_index_from_vector(game, j);        //Remove the Asteroid that was collided by the Player Beam
                delete_player_beam_index_from_vector(game, i);     //Remove the Player that collided the Asteroid
                game.player.hp -= 0.06;
            }
        }
    }
}

//Define what happens when an Enemy Beam collides into an Asteroid
void collision_enemy_beam_on_asteroid(game_data &game)
{
    //Sift through all the current Asteroids
    for (int j = 0; j < game.asteroids.size(); j++)
    {
        //Sift through all the current Enemy Beams
        for (int i = 0; i < game.enemy_beams.size(); i++)
        {
            //If the specified Asteroid collides into the specified Enemy Beam
            if (sprite_collision(game.asteroids[j].asteroid_sprite, game.enemy_beams[i].beam_sprite))
            {
                play_sound_effect("enemy_destroyed_sound_effect"); //Play sound effect
                delete_enemy_beam_index_from_vector(game, i);      //Remove the Enemy Beam that collided into  the Asteroid
                delete_asteroid_index_from_vector(game, j);        //Remove the Asteroid that was collided by the Enemy Beam
            }
        }
    }
}

//Define what happens when an Enemy Beam collides into a Player Beam
void collision_enemy_beam_on_player_beam(game_data &game)
{
    //Sift through all the current Player Beams
    for (int j = 0; j < game.player_beams.size(); j++)
    {
        //Sift through all the current Enemy Beams
        for (int i = 0; i < game.enemy_beams.size(); i++)
        {
            //If the specified Asteroid collides into the specified Enemy Beam
            if (sprite_collision(game.player_beams[j].beam_sprite, game.enemy_beams[i].beam_sprite))
            {
                delete_enemy_beam_index_from_vector(game, i);  //Remove the Enemy Beam that collided into Player Beam
                delete_player_beam_index_from_vector(game, j); //Remove the Player Beam that collided into the Enemy Beam
            }
        }
    }
}

//Define what happens when the Player collides into an Item
void collision_player_on_item(game_data &game)
{
    //Sift through all the current Items
    for (int i = 0; i < game.items.size(); i++)
    {
        //If the Player collides into the Item
        if (sprite_collision(game.items[i].item_sprite, game.player.player_sprite))
        {
            //Find an enumerated match for the collided Item
            switch (game.items[i].kind)
            {
            case (MEDPACK):                                          //MedPack item
                player_effects(game.player, 0.12, 0, 13);            //Increase the HP and Score
                play_sound_effect("medpack_collision_sound_effect"); //Play sound effect
                break;
            case (DIAMOND):                                          //Diamond item
                player_effects(game.player, 0, 0, 37);               //Increase the Score
                play_sound_effect("diamond_collision_sound_effect"); //Play sound effect
                break;
            case (AMMO):                                          //Ammo item
                player_effects(game.player, 0, 24, 6);            //Increase the Ammo and Score
                play_sound_effect("ammo_collision_sound_effect"); //Play sound effect
                break;
            case (STAR):                                          //Star item
                player_effects(game.player, 0.07, 0, 19);         //Increase the HP and Score
                game.player.is_star_mode = true;                  //Set the Star Mode as true -
                                                                  //the HP is now immune/unaffected by the Player's collisios to all Enemies, Enemy Beams and Asteroids
                game.halo = new_halo(game.player);                //Create a Halo surrounding the Player to indicate that the Star Mode is one for the Player
                start_timer("Player Star Mode timer");            //Start the Timer
                play_sound_effect("star_collision_sound_effect"); //Play sound effect
                break;
            }

            delete_item_index_from_vector(game, i); //Remove the Item that was collided by the Player
        }
    }
}

//Check for all collisions across the Player, Player Beams, Enemies, Enemy Beams, Asteroids and Items
void check_collisions(game_data &game)
{
    collision_player_beam_on_enemy(game);
    collision_enemy_beam_on_player(game);
    collision_enemy_on_player(game);
    collision_asteroid_on_player(game);
    collision_asteroid_on_enemy(game);
    collision_player_beam_on_asteroid(game);
    collision_enemy_beam_on_asteroid(game);
    collision_enemy_beam_on_player_beam(game);
    collision_player_on_item(game);
}

//------------------------------ REMOVE IRRELEVANT SPRITES ----------------------------------------------------------------

//Remove the Player Beam that has left the scope of vision of the camera so as to save on computational upkeep
//of having to maintain the existence of the Player Beam in the Player Beams vector
void remove_irrelevant_player_beam(game_data &game)
{
    //Sift through all the current Player Beams
    for (int i = 0; i < game.player_beams.size(); i++)
    {
        point_2d beam_sprite_center = center_point(game.player_beams[i].beam_sprite); //Obtain the centre point of the Player Beam

        //If the Beam has left the top of the camera
        if (beam_sprite_center.y < camera_y() - 50)
        {
            delete_player_beam_index_from_vector(game, i); ///Remove the Player Beam
        }
    }
}

//Remove the Enemy Beam that has left the scope of vision of the camera so as to save on computational upkeep
//of having to maintain the existence of the Enemy Beam in the Enemy Beams vector
void remove_irrelevant_enemy_beam(game_data &game)
{
    //Sift through all the current Enemy Beams
    for (int i = 0; i < game.enemy_beams.size(); i++)
    {
        point_2d beam_sprite_center = center_point(game.enemy_beams[i].beam_sprite); //Obtain the centre point of the Enemy Beam

        //If the Beam has left the bottom of the camera
        if (beam_sprite_center.y > camera_y() + screen_height() + 50)
        {
            delete_enemy_beam_index_from_vector(game, i); ///Remove the Enemy Beam
        }
    }
}

//Remove the Enemy that has left the scope of vision of the camera so as to save on computational upkeep
//of having to maintain the existence of the Enemy in the Enemies vector
void remove_irrelevant_enemy(game_data &game)
{
    //Sift through all the current Enemies
    for (int i = 0; i < game.enemies.size(); i++)
    {
        point_2d enemy_sprite_center = center_point(game.enemies[i].enemy_sprite); //Obtain the centre point of the Enemy

        //If the Enemy has left the bottom of the camera
        if (enemy_sprite_center.y > camera_y() + screen_height() + 50)
        {
            delete_enemy_index_from_vector(game, i); ///Remove the Enemy Beam
            game.player.hp -= 0.04;                  //Reduce the HP as punishment for failing to destroy the Enemy before they reach the bottom of the screen
        }
    }
}

//Remove the Asteroid that has left the scope of vision of the camera so as to save on computational upkeep
//of having to maintain the existence of the Asteroid in the Asteroids vector
void remove_irrelevant_asteroid(game_data &game)
{
    //Sift through all the Asteroids available
    for (int i = 0; i < game.asteroids.size(); i++)
    {
        point_2d asteroid_sprite_centre = center_point(game.asteroids[i].asteroid_sprite); //Obtain the centre point of the Asteroid

        //If the Asteroid has left the bottom of the camera
        if (asteroid_sprite_centre.y > camera_y() + screen_height() + 50)
        {
            delete_asteroid_index_from_vector(game, i); ///Remove the Asteroid
        }
        //If the Asteroid has left the left of the camera
        if (asteroid_sprite_centre.x > camera_x() + screen_width() + 100)
        {
            delete_asteroid_index_from_vector(game, i); ///Remove the Asteroid
        }
        //If the Asteroid has left the right of the camera
        if (asteroid_sprite_centre.x < camera_x() - 50)
        {
            delete_asteroid_index_from_vector(game, i); ///Remove the Asteroid
        }
    }
}

//Remove the Item that has left the scope of vision of the camera so as to save on computational upkeep
//of having to maintain the existence of the Item in the Items vector
void remove_irrelevant_item(game_data &game)
{
    //Sift through all the Items available
    for (int i = 0; i < game.items.size(); i++)
    {
        point_2d item_sprite_centre = center_point(game.items[i].item_sprite); //Obtain the centre point of the Item

        //If the Item has left the bottom of the camera
        if (item_sprite_centre.y > camera_y() + screen_height() + 100)
        {
            delete_item_index_from_vector(game, i); //Remove the Item
        }
        //If the Beam has left the left of the camera
        if (item_sprite_centre.x < camera_x() - 100)
        {
            delete_item_index_from_vector(game, i); //Remove the Item
        }
        //If the Item has left the right of the camera
        if (item_sprite_centre.x > camera_x() + screen_width() + 100)
        {
            delete_item_index_from_vector(game, i); //Remove the Item
        }
    }
}

//Remove any sprites that have left the screen so as to save up on computational upkeep of having to maintain the existence of that sprite
void remove_irrelevant_sprites(game_data &game)
{
    remove_irrelevant_player_beam(game);
    remove_irrelevant_enemy_beam(game);
    remove_irrelevant_enemy(game);
    remove_irrelevant_asteroid(game);
    remove_irrelevant_item(game);
}

//------------------------------ DEFINE LIMITS ----------------------------------------------------------------------------

//Define the limits of the HP
void define_hp_limits(player_data &player)
{
    //Define the maximum value of the HP as 1
    if (player.hp >= 1)
    {
        player.hp = 1;
    }
    //Define the minimum value of the HP as zero
    else if (player.hp <= 0)
    {
        player.hp = 0;
    }
}

//Define the limits of the Ammo
void define_ammo_limits(player_data &player)
{
    //Define the minimum value of the Ammo as zero
    if (player.ammo <= 0)
    {
        player.ammo = 0;
    }
}

//Define the limit of the Mana
void define_mana_limits(player_data &player)
{
    //Set the maximum of the Mana Bar to 1
    if (player.mana >= 1)
    {
        player.mana = 1;
    }
}

//------------------------------ STOP MOTIONS -----------------------------------------------------------------------------

//Stop the motion of all Enemies
void stop_all_enemies(game_data &game)
{
    //Sift through all the current Enemies
    for (int i = 0; i < game.enemies.size(); i++)
    {
        sprite_set_speed(game.enemies[i].enemy_sprite, 0); //Set the speed of the Enemy to zero
    }
}

//Stop the motion of all Enemy Beams
void stop_all_enemy_beams(game_data &game)
{
    //Sift through all the current Enemy Beams
    for (int i = 0; i < game.enemy_beams.size(); i++)
    {
        sprite_set_speed(game.enemy_beams[i].beam_sprite, 0); //Set the speed of the Enemy Beam to zero
    }
}

//Stop the motion of all Player Beams
void stop_all_player_beams(game_data &game)
{
    //Sift through all the current Player Beams
    for (int i = 0; i < game.player_beams.size(); i++)
    {
        sprite_set_speed(game.player_beams[i].beam_sprite, 0); //Set the speed of the Player Beam to zero
    }
}

//Stop the motion of all Asteroids
void stop_all_asteroids(game_data &game)
{
    //Sift through all the current Asteroids
    for (int i = 0; i < game.asteroids.size(); i++)
    {
        sprite_set_speed(game.asteroids[i].asteroid_sprite, 0); //Set the speed of the Asteroid Beam to zero
    }
}

//Stop the motion of all Items
void stop_all_items(game_data &game)
{
    //Sift through all the current Items
    for (int i = 0; i < game.items.size(); i++)
    {
        sprite_set_speed(game.items[i].item_sprite, 0); //Set the speed of the Item Beam to zero
    }
}

//Stop the motion of the Background looping
void stop_background_movement(game_data &game)
{
    sprite_set_speed(game.background.background_sprites[0], 0); //Stop the motion of the first Background
    sprite_set_speed(game.background.background_sprites[1], 0); //Stop the motion of the first Background
}

//Define what happens when the HP reaches zero
void define_game_over_effects(game_data &game)
{
    //If the HP is lower than or equal to zero
    if (game.player.hp <= 0)
    {
        game.is_game_over = true; //Set the Game Over Flag to true

        //If the Game Over Flag is true and the Game Over Effects hav enot been Executed yet
        if (game.is_game_over && !game.is_game_over_effects_executed)
        {
            play_sound_effect("game_over_sound_effect"); //Play sound effect

            sprite_set_speed(game.player.player_sprite, 0); //Set the speed of the Player to zero
            stop_all_enemies(game);                         //Stop the motion of all Enemies
            stop_all_enemy_beams(game);                     //Stop the motion of all Enemy Beams
            stop_all_player_beams(game);                    //Stop the motion of all Player Beams
            stop_all_asteroids(game);                       //Stop the motion of all Asteroids
            stop_all_items(game);                           //Stop the motion of all Items

            game.is_game_over_effects_executed = true; //Set the Game Over Effects Executed Flag to true

            //======================= ADD DATA TO THE HISCORES DATABASE =======================
            database hiscores_db;   //Declare Hiscores database variable
            query_result query_res; //Declare Query Result variable to query the SQLite Database

            hiscores_db = open_database(database_name, database_name);                      //Create/open the SQLiteDatabase to store the Hiscores data
            query_res = run_sql(hiscores_db, "select * from " + database_table_name + ";"); //Run an SQL command to open the Hiscores table from the database

            //If the database has existing rows, i.e. has existing data
            if (has_row(query_res))
            {
                run_sql(hiscores_db, "INSERT INTO hiscores VALUES (" + to_string(game.player.score) + ");"); //Run SQL command to insert the Game Score to the "Hiscores" table of the Hiscores database
            }
            else //If the database has no existing rows, i.e. has no existing data
            {
                hiscores_db = open_database(database_name, database_name);                                                      //Creates/opens the SQLiteDatabase to store the Hiscores data
                run_sql(hiscores_db, "CREATE TABLE " + database_table_name + " (score INTEGER PRIMARY KEY);");                  //Run SQL command to create a table named "hiscores" in the database
                run_sql(hiscores_db, "INSERT INTO " + database_table_name + " VALUES (" + to_string(game.player.score) + ");"); //Run SQL command to insert the Game Score to the "Hiscores" table of the Hiscores database
            }

            free_all_query_results();   //Free all Query Results
            free_database(hiscores_db); //Free the database
        }

        //If Game Over is reached
        if (game.is_game_over)
        {
            stop_background_movement(game); //Stop the motion of the Background looping
        }
    }
}

//------------------------------ UPDATE SPRITES ---------------------------------------------------------------------------

//Update all the Enemies
void update_enemies(game_data &game)
{
    //If there are Enemies
    if (!game.enemies.empty())
    {
        check_collisions(game); //Check for collisions

        //Sift through all current Enemies
        for (int i = 0; i < game.enemies.size(); i++)
        {
            update_enemy(game.enemies[i]); //Update the Enemy
        }

        //Sift through all current Enemy Beams
        for (int i = 0; i < game.enemy_beams.size(); i++)
        {
            update_beam(game.enemy_beams[i]); //Update the Enemy Beam
        }
    }
}

//Update all the Player Beams
void update_player_beams(game_data &game)
{
    //If there are Player Beams
    if (!game.player_beams.empty())
    {
        check_collisions(game); //Check for collisions

        //Sift through all current Beams
        for (int i = 0; i < game.player_beams.size(); i++)
        {
            update_beam(game.player_beams[i]); //Update the Beam
        }
    }
}

//Update all the Enemy Beams
void update_enemy_beams(game_data &game)
{
    //If there are Enemy Beams
    if (!game.enemy_beams.empty())
    {
        check_collisions(game); //Check for collisions
    }
}

//Update all the Asteroids
void update_asteroids(game_data &game)
{
    //If there are Asteroids
    if (!game.asteroids.empty())
    {
        check_collisions(game); //Check for collisions

        //Sift through all Asteroids
        for (int i = 0; i < game.asteroids.size(); i++)
        {
            update_asteroid(game.asteroids[i]); //Update the Asteroid
        }
    }
}

//Update all the Items
void update_items(game_data &game)
{
    //Update Items if there are any
    if (!game.items.empty())
    {
        check_collisions(game); //Check for collisions

        //Sift through all Items
        for (int i = 0; i < game.items.size(); i++)
        {
            update_item(game.items[i]); //Update the Item
        }
    }
}

//Update the Star Mode
void define_star_mode_effects(game_data &game)
{
    //If Star Mode is active
    if (game.player.is_star_mode)
    {
        update_halo(game.halo); //Update the Halo surrounding the Player

        //If the timer for the Star Mode exceeds 8000ms
        if (timer_ticks("Player Star Mode timer") >= 8000)
        {
            stop_timer("Player Star Mode timer"); //Stop the Star Mode timer
            game.player.is_star_mode = false;     //Inactivate Star Mode
            free_sprite(game.halo.halo_sprite);   //Remove the Halo
        }
    }
}

//Update the Theme Song in the background
void update_music(game_data &game)
{
    //If the theme song in the background has finished playing
    if (!music_playing())
    {
        play_music("theme_song"); //Play the theme song again
    }
}

//------------------------------ UPDATE THE HUD ---------------------------------------------------------------------------
void update_game(game_data &game)
{
    //Perform updates
    update_background(game.background); //Update the Background
    update_player(game.player);         //Update the Player
    update_enemies(game);               //Update Enemies
    update_player_beams(game);          //Update Player Beams
    update_enemy_beams(game);           //Update Enemy Beams
    update_asteroids(game);             //Update Asteroids
    update_items(game);                 //Update Items
    update_music(game);                 //Update Music

    remove_irrelevant_sprites(game); //Remove any sprites that have left the screen

    //Perform definitions
    define_hp_limits(game.player);   //Define the limits of the HP
    define_ammo_limits(game.player); //Define the limits of the Ammo
    define_star_mode_effects(game);  //Define the effects of the Star Mode
    define_game_over_effects(game);  //Define the effects of Game Over
}

//============================== DRAW GAME ==============================================================================

//------------------------------ DRAW THE HUD ---------------------------------------------------------------------------
//Obtain the Mana Bar percentage
double get_mana_pct(game_data &game)
{
    //Declare variables
    double time_elapsed_since_zero; //Time elapsed (ms) since the Mana Bar is zero
    double mana_percentage;         //Mana Bar percentage

    if (game.player.ammo > 0)
    {
        time_elapsed_since_zero = timer_ticks("Player Beam cooldown timer");  //Obtain time elapsed (ms) since the Mana Bar is zero
        mana_percentage = time_elapsed_since_zero / BEAM_SHOOT_COOLDOWN_TIME; //Mana Bar percentage
    }
    else
    {
        mana_percentage = 0;
    }

    return mana_percentage;
}

//Draw Ammo Information
void draw_ammo_information(game_data &game)
{
    //Draw Ammo Information
    draw_text("AMMO:", COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, screen_width() * 0.82, screen_height() * 0.83, option_to_screen());
    draw_text(to_string(game.player.ammo), COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, screen_width() * 0.92, screen_height() * 0.83, option_to_screen());
}

//Draw Mana Bar
void draw_mana_bar(game_data &game)
{
    game.player.mana = get_mana_pct(game); ///Obtain the Mana Bar percentage
    define_mana_limits(game.player);       //Define the limits of the Mana

    //Draw Mana Bar
    draw_bitmap("mana_bar_empty", screen_width() * 0.75, screen_height() * 0.87, option_to_screen());
    draw_bitmap("mana_bar_full", screen_width() * 0.75, screen_height() * 0.87, option_part_bmp(0, -3, bitmap_width("mana_bar_empty") * game.player.mana, bitmap_height("mana_bar_empty"), option_to_screen()));
}

//Draw HP Bar
void draw_hp_bar(game_data &game)
{
    //Draw HP Bar
    draw_bitmap("hp_bar_empty", screen_width() * 0.75, screen_height() * 0.922, option_to_screen());
    draw_bitmap("hp_bar_full", screen_width() * 0.75, screen_height() * 0.92, option_part_bmp(0, -3, bitmap_width("hp_bar_empty") * game.player.hp, bitmap_height("hp_bar_empty"), option_to_screen()));
}

//Draw Score Information
void draw_score_information(game_data &game)
{
    //Draw Score Information
    draw_text("SCORE:", COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, screen_width() * 0.80, screen_height() * 0.03, option_to_screen());
    draw_text(to_string(game.player.score), COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, screen_width() * 0.90, screen_height() * 0.03, option_to_screen());
}

//Draw Level Information
void draw_level_information(game_data &game)
{
    //Draw Level Information
    draw_text("LEVEL:", COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, screen_width() * 0.02, screen_height() * 0.03, option_to_screen());
    draw_text(to_string(game.player.level), COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, screen_width() * 0.13, screen_height() * 0.03, option_to_screen());
}

//Draw HP Information
void draw_hp_information(game_data &game)
{
    draw_text(to_string(int(game.player.hp * 100)), COLOR_BLACK, load_font("pcsenior", "pcsenior"), 10, screen_width() * 0.82, screen_height() * 0.933, option_to_screen());
    draw_text("/", COLOR_BLACK, load_font("pcsenior", "pcsenior"), 10, screen_width() * 0.855, screen_height() * 0.933, option_to_screen());
    draw_text("100", COLOR_BLACK, load_font("pcsenior", "pcsenior"), 10, screen_width() * 0.87, screen_height() * 0.933, option_to_screen());
}

//Draw Game Over
void draw_game_over(game_data &game)
{
    if (game.is_game_over_effects_executed)
    {
        draw_text("GAME OVER !", COLOR_WHITE, load_font("pcsenior", "pcsenior"), 28, screen_width() * 0.35, screen_height() * 0.4, option_to_screen());
    }
}

//Create the Heads-Up Display (HUD)
void draw_hud(game_data &game)
{
    draw_ammo_information(game);  //Draw Ammo Information
    draw_mana_bar(game);          //Draw Mana Bar
    draw_hp_bar(game);            //Draw HP Bar
    draw_score_information(game); //Draw Score Information
    draw_level_information(game); //Draw Level Information
    draw_hp_information(game);    //Draw HP Information
    draw_game_over(game);         //Draw Game Over

    //Draw Ammo Information
    draw_text("AMMO:", COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, screen_width() * 0.82, screen_height() * 0.83, option_to_screen());
    draw_text(to_string(game.player.ammo), COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, screen_width() * 0.92, screen_height() * 0.83, option_to_screen());

    draw_text("'Q' to Quit", COLOR_YELLOW, load_font("pcsenior", "pcsenior"), 16, screen_width() * 0.02, screen_height() * 0.95, option_to_screen());
}

//------------------------------ DRAW THE SPRITES ---------------------------------------------------------------------------

//Draw the Items
void draw_items(game_data &game)
{
    //Draw Items if there are any
    if (!game.items.empty())
    {
        //Sift through all Items
        for (int i = 0; i < game.items.size(); i++)
        {
            draw_item(game.items[i]); //Draw Item
        }
    }
}

//Draw the Player Beams
void draw_player_beams(game_data &game)
{
    //Draw Player Beams if there is any
    if (!game.player_beams.empty())
    {
        //Sift through all Player Beams
        for (int i = 0; i < game.player_beams.size(); i++)
        {
            draw_beam(game.player_beams[i]); //Draw Player Beam
        }
    }
}

//Draw the Enemies
void draw_enemies(game_data &game)
{
    //Draw Enemies if there are any
    if (!game.enemies.empty())
    {
        //Sift through all Enemies
        for (int i = 0; i < game.enemies.size(); i++)
        {
            draw_enemy(game.enemies[i]); //Draw the Enemy
        }
    }
}

//Draw the Enemy Beams
void draw_enemy_beams(game_data &game)
{
    //Draw Enemy Beams if there are any
    if (!game.enemy_beams.empty())
    {
        //Sift through all Enemy Beams
        for (int i = 0; i < game.enemy_beams.size(); i++)
        {
            draw_beam(game.enemy_beams[i]); //Draw Enemy Beam
        }
    }
}

//Draw the Asteroids
void draw_asteroids(game_data &game)
{
    //Draw Asteroids if there are any
    if (!game.asteroids.empty())
    {
        //Sift through all Asteroid
        for (int i = 0; i < game.asteroids.size(); i++)
        {
            draw_asteroid(game.asteroids[i]); //Draw the Asteroid
        }
    }
}

//Draw the Halo
void draw_halo(game_data &game)
{
    //IF the Star Mode is activated
    if (game.player.is_star_mode)
    {
        //If the Star Mode has been activated and less than 5000ms has elapsed
        if (timer_ticks("Player Star Mode timer") < 5000)
        {
            draw_halo(game.halo, game.player); //Draw the Halo
        }
        //If the Star Mode has been activated and more than 5000ms has elpased
        else if (timer_ticks("Player Star Mode timer") >= 5000 && timer_ticks("Player Star Mode timer") % 2)
        {
            draw_halo(game.halo, game.player); //Draw the Halo
        }
    }
}

//------------------------------ DRAW THE GAME ----------------------------------------------------------------------------
void draw_game(game_data &game)
{
    draw_background(game.background); //Draw the Background
    draw_player(game.player);         //Draw the Player
    draw_enemies(game);               //Draw the Enemies
    draw_enemy_beams(game);           //Draw the Enemhy Beams
    draw_asteroids(game);             //Draw the Asteroids
    draw_items(game);                 //Draw the Items
    draw_player_beams(game);          //Draw the Player Beams
    draw_halo(game);                  //Draw the Halo
    draw_hud(game);                   //Draw the HUD
}