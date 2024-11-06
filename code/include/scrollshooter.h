#pragma once

#include "pawns.h"
#include <cstdint>
#include <memory>
#include <vector>

class scroll_shooter
{
public:
    scroll_shooter();
    ~scroll_shooter() = default;

    void start_game();

private:
    void game_loop();

    void init_ncurses();
    void init_game();

    void draw_all();
    void update_all();
    void spawn_enemy();
    void handle_input();

    void set_start_values();
    void show_finish_screen() const;
    void add_points_to_score(uint16_t count);

    bool is_spawn_of_enemy_available();
    bool is_game_finish() const;
    bool is_player_alive() const;

private:
    std::unique_ptr<player> main_player = nullptr;

    std::vector<enemy> enemies;
    std::vector<bullet> bullets;

    uint16_t points_for_kill = 0;
    uint32_t score = 0;
    uint32_t lives = 0;

    uint16_t max_enemies = 0;
    float elapsed_time_from_last_enemy_spawn = 0;

    const uint8_t timeout = 1;
};
