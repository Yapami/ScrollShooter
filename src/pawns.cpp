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
    symbol = config_namespace::player_symbol;
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
    symbol = config_namespace::enemy_symbol;
    speed = config_namespace::enemies_start_speed;
}

void Enemy::update()
{
    ++t;
    if (t > speed)
    {
        t = 0;
        ++y;
    }
}

Bullet::Bullet(int start_x, int start_y)
    : Entity(start_x, start_y)
{
    symbol = config_namespace::bullet_symbol;
}

void Bullet::update()
{
    ++a;
    if (a > 75) // TODO: remake it to config
    {
        a = 0;
        --y;
    }
}
