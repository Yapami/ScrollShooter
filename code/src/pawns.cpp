#include "pawns.h"
#include "config.h"
#include <cstdlib>

void Entity::draw() const
{
    mvprintw(y, x, "%s", symbol.c_str());
}

Player::Player(int start_x, int start_y)
    : Entity(start_x, start_y)
{
    symbol = config::player_symbol;
}

void Player::move_left()
{
    if (x > 0)
    {
        --x;
    }
}

void Player::move_right()
{
    if (x < COLS - 1)
    {
        ++x;
    }
}

Enemy::Enemy(int start_x, int start_y)
    : Entity(start_x, start_y)
{
    symbol = config::enemy_symbol;
    speed = config::enemies_start_speed;
}

void Enemy::update()
{
    float current_time =
        static_cast<float>(elapsed_timer::get_instance().get_elapsed_time_milliseconds());
    if ((current_time - elapsed_time_from_last_movement) / 1000.0 >= speed)
    {
        elapsed_time_from_last_movement =
            elapsed_timer::get_instance().get_elapsed_time_milliseconds();
            
        ++y;
    }
}

Bullet::Bullet(int start_x, int start_y)
    : Entity(start_x, start_y)
{
    symbol = config::bullet_symbol;
    speed = config::bullets_start_speed;
}

void Bullet::update()
{
    float current_time =
        static_cast<float>(elapsed_timer::get_instance().get_elapsed_time_milliseconds());
    if ((current_time - elapsed_time_from_last_movement) / 1000.0 >= speed)
    {
        elapsed_time_from_last_movement =
            elapsed_timer::get_instance().get_elapsed_time_milliseconds();

        --y;
    }
}
