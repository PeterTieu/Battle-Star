#include "splashkit.h"
#include "menu.h"
#include "button.h"
#include "battlestar.h"
#include <vector>
#include "hiscore_cell.h"

using namespace std;

hiscore_cell_data new_hiscore_cell(int placing, int score, double x_pos, double y_pos)
{
    hiscore_cell_data hiscore_cell;

    hiscore_cell.placing = placing;
    hiscore_cell.score = score;

    hiscore_cell.x_pos = x_pos;
    hiscore_cell.y_pos = y_pos;


    return hiscore_cell;
}

void update_hiscore_cell(hiscore_cell_data &hiscore_cell)
{
    // update_sprite(hiscore_cell.hiscore_cell_placing_sprite);
    // update_sprite(hiscore_cell.hiscore_cell_score_sprite);


    // draw_text(to_string(hiscore_cell.placing), COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, hiscore_cell.x_pos, hiscore_cell.y_pos, option_to_screen());
    // draw_text(to_string(hiscore_cell.score), COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, hiscore_cell.x_pos, hiscore_cell.y_pos+100, option_to_screen());

}

void draw_hiscore_cell(hiscore_cell_data &hiscore_cell)
{
    bitmap hiscore_cell_placing_bitmap;
    bitmap hiscore_cell_score_bitmap;
    // draw_sprite(hiscore_cell.hiscore_cell_placing_sprite);
    // draw_sprite(hiscore_cell.hiscore_cell_score_sprite);

    hiscore_cell_placing_bitmap = bitmap_named("hiscore_cell_placing");
    hiscore_cell_score_bitmap = bitmap_named("hiscore_cell_score");

    draw_bitmap(hiscore_cell_placing_bitmap, hiscore_cell.x_pos, hiscore_cell.y_pos);
    draw_bitmap(hiscore_cell_score_bitmap, hiscore_cell.x_pos+50, hiscore_cell.y_pos);


    draw_text(to_string(hiscore_cell.placing), COLOR_BLACK, load_font("pcsenior", "pcsenior"), 16, hiscore_cell.x_pos+10, hiscore_cell.y_pos+15, option_to_screen());
    draw_text(to_string(hiscore_cell.score), COLOR_WHITE, load_font("pcsenior", "pcsenior"), 16, hiscore_cell.x_pos+100, hiscore_cell.y_pos+15, option_to_screen());

}
