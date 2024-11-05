#pragma once

#include "pawns.h"
#include <vector>

class scroll_shooter
{
public:
    scroll_shooter();
    ~scroll_shooter();

    void start_game();

private:
    void game_loop();

    void init_game();
    void draw_all();
    void update_all();
    void spawn_enemy();
    void handle_input();

    void set_start_values();
    void print_final_text();
    void increase_score(uint16_t count);

    bool is_spawn_of_enemy_available();
    bool is_game_finish();
    bool is_player_alive();

private:
    Player* player = nullptr;

    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;

    int points_for_kill;
    int score = 0;
    int lives;

    int max_enemies;

    int timeElapsed = 0;
    clock_t start_time;

    const int Timeout = 1;
};
