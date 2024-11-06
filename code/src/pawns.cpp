#include "pawns.h"
#include "config.h"
#include "timer.h"
#include <cstdlib>
#include <ncurses.h>

void entity::draw() const
{
    mvprintw(y, x, "%s", symbol.c_str());
}

player::player(int start_x, int start_y)
    : entity(start_x, start_y)
{
    symbol = config::player_symbol;
}

void player::move_left()
{
    if (x > 0)
    {
        --x;
    }
}

void player::move_right()
{
    if (x < COLS - 1)
    {
        ++x;
    }
}

enemy::enemy(int start_x, int start_y)
    : entity(start_x, start_y)
{
    symbol = config::enemy_symbol;
    speed = config::enemies_start_speed;
}

void enemy::update()
{
    float current_time =
        static_cast<float>(elapsed_timer::get_instance().get_elapsed_time_milliseconds());
    if ((current_time - elapsed_time_from_last_movement) / elapsed_timer::milliseconds_in_second >= speed)
    {
        elapsed_time_from_last_movement =
            elapsed_timer::get_instance().get_elapsed_time_milliseconds();

        ++y;
    }
}

bullet::bullet(int start_x, int start_y)
    : entity(start_x, start_y)
{
    symbol = config::bullet_symbol;
    speed = config::bullets_start_speed;
}

void bullet::update()
{
    float current_time =
        static_cast<float>(elapsed_timer::get_instance().get_elapsed_time_milliseconds());
    if ((current_time - elapsed_time_from_last_movement) / elapsed_timer::milliseconds_in_second >=
        speed)
    {
        elapsed_time_from_last_movement =
            elapsed_timer::get_instance().get_elapsed_time_milliseconds();

        --y;
    }
}
