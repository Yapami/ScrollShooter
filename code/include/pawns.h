#pragma once

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

class enemy : public entity
{
public:
    enemy(int start_x, int start_y);

    void update() override;

private:
    float speed = 0.0;
    float elapsed_time_from_last_movement = 0.0;
};

class bullet : public entity
{
public:
    bullet(int start_x, int start_y);

    void update() override;

private:
    float speed = 0.0;
    float elapsed_time_from_last_movement = 0.0;
};