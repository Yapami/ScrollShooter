#include "pawns.h"
#include "config.h"
#include "timer.h"
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
    x = std::max(0, x - 1);
}

void player::move_right()
{
    x = std::min(COLS - 1, x + 1);
}

enemy::enemy(int start_x, int start_y)
    : npc_entity(start_x, start_y)
{
    symbol = config::enemy_symbol;
    speed = config::enemies_start_speed;
}

void enemy::move()
{
    ++y;
}

bullet::bullet(int start_x, int start_y)
    : npc_entity(start_x, start_y)
{
    symbol = config::bullet_symbol;
    speed = config::bullets_start_speed;
}

void bullet::move()
{
    --y;
}

void npc_entity::update()
{
    if (timer == nullptr)
    {
        return;
    }

    float current_time = static_cast<float>(timer->get_elapsed_time_milliseconds());
    if ((current_time - elapsed_time_from_last_movement) / elapsed_timer::milliseconds_in_second >=
        speed)
    {
        elapsed_time_from_last_movement = timer->get_elapsed_time_milliseconds();

        move();
    }
}
