#pragma once

#include "pawns.h"
#include "timer.h"
#include <chrono>
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
    void show_finish_screen() const;
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
    float enemies_spawn_frequency;
    float elapsed_time_from_last_enemy_spawn = 0;

    const int timeout = 1;

    elapsed_timer& timer = elapsed_timer::get_instance();
};
