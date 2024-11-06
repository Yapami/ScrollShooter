#include "scrollshooter.h"
#include "config.h"
#include "pawns.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

void scroll_shooter::set_start_values()
{
    enemies.clear();
    bullets.clear();

    elapsed_timer::get_instance().refresh_timer();

    lives = config::lives;
    score = 0;

    elapsed_time_from_last_enemy_spawn = 0;

    if (player != nullptr)
    {
        delete player;
    }

    player = new Player(COLS / 2, LINES - 2);
}

void scroll_shooter::init_game()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(timeout);

    set_start_values();
}

void scroll_shooter::draw_all()
{
    player->draw();
    for (Enemy& enemy : enemies)
    {
        enemy.draw();
    }

    for (Bullet& bullet : bullets)
    {
        bullet.draw();
    }

    mvprintw(1, 0, "Lives: %d", lives);
    mvprintw(0, 0, "Score: %d", score);
    mvprintw(0, COLS - 10, "Time: %d", elapsed_timer::get_instance().get_elapsed_time_seconds());
}

void scroll_shooter::update_all()
{
    for (auto it = enemies.begin(); it != enemies.end();)
    {
        it->update();
        if (it->y >= LINES - 2)
        {
            --lives;
            it = enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = bullets.begin(); it != bullets.end();)
    {
        it->update();
        if (it->y >= LINES)
        {
            it = bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto bullet_it = bullets.begin(); bullet_it != bullets.end();)
    {
        bool hit = false;
        for (auto enemy_it = enemies.begin(); enemy_it != enemies.end();)
        {
            if (bullet_it->x == enemy_it->x && bullet_it->y == enemy_it->y)
            {
                enemy_it = enemies.erase(enemy_it);
                hit = true;
                increase_score(points_for_kill);
                break;
            }
            else
            {
                ++enemy_it;
            }
        }

        if (hit)
        {
            bullet_it = bullets.erase(bullet_it);
        }
        else
        {
            ++bullet_it;
        }
    }

    elapsed_timer::get_instance().update_timer();
}

void scroll_shooter::spawn_enemy()
{
    if (is_spawn_of_enemy_available())
    {
        enemies.emplace_back(Enemy(rand() % COLS, 0));
    }
}

void scroll_shooter::handle_input()
{
    int ch = getch();
    switch (ch)
    {
    case KEY_LEFT:
        player->move_left();
        break;
    case KEY_RIGHT:
        player->move_right();
        break;
    case ' ':
        bullets.emplace_back(player->x, (player->y));
        break;
    case 'q':
        endwin();
        exit(0);
    }
}

void scroll_shooter::show_finish_screen() const
{
    const std::string game_over_str = "GAME OVER!";
    const std::string score_str = "Score: " + std::to_string(score);
    const std::string time_str =
        "Time: " + std::to_string(elapsed_timer::get_instance().get_elapsed_time_seconds());
    const std::string quit_str = "Press 'q' to quit";
    const std::string restart = "Press 'r' to restart";

    clear();
    mvprintw(LINES / 2 - 4, COLS / 2 - game_over_str.size() / 2, "%s", game_over_str.c_str());
    mvprintw(LINES / 2 - 4 + 1, COLS / 2 - score_str.size() / 2, "%s", score_str.c_str());
    mvprintw(LINES / 2 - 4 + 2, COLS / 2 - time_str.size() / 2, "%s", time_str.c_str());
    mvprintw(LINES / 2 - 4 + 5, COLS / 2 - quit_str.size() / 2, "%s", quit_str.c_str());
    mvprintw(LINES / 2 - 4 + 6, COLS / 2 - restart.size() / 2, "%s", restart.c_str());
    refresh();
}

bool scroll_shooter::is_spawn_of_enemy_available()
{
    if (enemies.size() >= max_enemies)
    {
        return false;
    }

    float current_time =
        static_cast<float>(elapsed_timer::get_instance().get_elapsed_time_milliseconds());

    if ((current_time - elapsed_time_from_last_enemy_spawn) / 1000.0 >=
        config::enemies_spawn_frequency)
    {
        elapsed_time_from_last_enemy_spawn =
            elapsed_timer::get_instance().get_elapsed_time_milliseconds();
        return true;
    }

    return false;
}

bool scroll_shooter::is_game_finish()
{
    timeout(-1);
    while (true)
    {
        char ch = getch();
        switch (ch)
        {
        case 'q':
            return false;
        case 'r':
            return true;
        }
    }
}

bool scroll_shooter::is_player_alive()
{
    return lives > 0;
}

void scroll_shooter::game_loop()
{
    while (true)
    {
        clear();
        update_all();
        draw_all();
        handle_input();
        spawn_enemy();
        refresh();

        if (is_player_alive() == false)
        {
            break;
        }
    }
}

void scroll_shooter::increase_score(uint16_t count)
{
    score += count;
}

scroll_shooter::scroll_shooter()
{
    points_for_kill = config::base_points_for_kill;
    max_enemies = config::max_enemies;

    srand(time(0));
}

scroll_shooter::~scroll_shooter()
{
    delete player;
}

void scroll_shooter::start_game()
{
    do
    {
        init_game();
        game_loop();
        show_finish_screen();
    } while (is_game_finish());

    endwin();
}
