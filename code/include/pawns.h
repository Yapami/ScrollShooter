#pragma once

#include "timer.h"
#include <string>

class entity
{
public:
    entity(int start_x, int start_y)
        : x(start_x)
        , y(start_y)
    {
    }

    virtual void update() = 0;
    void draw() const;

public:
    int x, y;

protected:
    std::string symbol;
};

class npc_entity : public entity
{
public:
    npc_entity(int start_x, int start_y)
        : entity(start_x, start_y)
        , timer(&elapsed_timer::get_instance())
    {
    }

    void update() override;

protected:
    virtual void move() = 0;

protected:
    float speed = 0.0;
    float last_movement_time = 0.0;

    elapsed_timer* timer;
};

class player : public entity
{
public:
    player(int start_x, int start_y);

    void update() override
    {
    }
    void move_left();
    void move_right();
};

class enemy : public npc_entity
{
public:
    enemy(int start_x, int start_y);

private:
    void move() override;
};

class bullet : public npc_entity
{
public:
    bullet(int start_x, int start_y);

private:
    void move() override;
};