#pragma once

#include <ncurses.h>
#include <string>

class Entity
{
public:
    int x, y;

    Entity(int start_x, int start_y)
        : x(start_x)
        , y(start_y)
    {
    }

    virtual void update() = 0;
    void draw() const;

protected:
    std::string symbol;
};

class Player : public Entity
{
public:
    Player(int start_x, int start_y);

    void update() override
    {
    }
    void move_left();
    void move_right();
};

class Enemy : public Entity
{
public:
    Enemy(int start_x, int start_y);

    void update() override;

private:
    int speed;
    int t = 0;
};

class Bullet : public Entity
{
public:
    Bullet(int start_x, int start_y);

    void update() override;

private:
    int a = 0;
};