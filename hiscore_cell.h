#ifndef BATTLESTAR_HISCORE_CELL_DATA
#define BATTLESTAR_HISCORE_CELL_DATA

#include "splashkit.h"
#include "button.h"
#include "battlestar.h"
#include <vector>
#include "battlestar.h"
#include "menu.h"

#define NUM_SPRITES_IN_CELL 2


struct hiscore_cell_data
{
    int placing;
    int score;
    double x_pos;
    double y_pos;
};

hiscore_cell_data new_hiscore_cell(int placing, int score, double x_pos, double y_pos);
void update_hiscore_cell(hiscore_cell_data &hiscore_cell);
void draw_hiscore_cell(hiscore_cell_data &hiscore_cell);


#endif