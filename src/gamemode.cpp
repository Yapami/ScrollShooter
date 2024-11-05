#include "gamemode.h"
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

    start_time = clock();
    timeElapsed = 0;

    lives = config_namespace::lives; // TODO: Maybe remake it
    score = 0;

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
    timeout(Timeout); // TODO: maybe should be deleted

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
    mvprintw(0, COLS - 10, "Time: %d", timeElapsed);
}

void scroll_shooter::update_all()
{
    for (auto it = enemies.begin(); it != enemies.end();)
    {
        it->update();
        if (it->y >= LINES - 1)
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

    clock_t currentTime = clock();
    if ((currentTime - start_time) / 100000 /*CLOCKS_PER_SEC*/ >= 1) // TODO: make it normal
    {
        timeElapsed++;
        start_time = currentTime;
    }
}

void scroll_shooter::spawn_enemy()
{
    if (enemies.size() < max_enemies && is_spawn_of_enemy_available())
    {
        enemies.emplace_back(Enemy(rand() % COLS, 0)); // TODO: figure out how emplace_back works
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
        bullets.emplace_back(player->x, (player->y) - 1);
        break;
    case 'q':
        endwin();
        exit(0);
    }
}

void scroll_shooter::print_final_text()
{
    clear();
    mvprintw(LINES / 2, COLS / 2 - 5, "GAME OVER!");
    mvprintw(LINES / 2 + 1, COLS / 2 - 5, "Score: %d", score);
    mvprintw(LINES / 2 + 2, COLS / 2 - 5, "Time: %ld", start_time);
    mvprintw(LINES / 2 + 5, COLS / 2 - 5, "Press any key to restart");
    mvprintw(LINES / 2 + 6, COLS / 2 - 5, "Press 'q' to quit");
    mvprintw(LINES / 2 + 7, COLS / 2 - 5, "Press 'r' to restart");
    refresh();
}

bool scroll_shooter::is_spawn_of_enemy_available()
{
    static clock_t currentTime = clock();

    clock_t t = clock();

    double d = ((static_cast<double>(t) - static_cast<double>(currentTime)) / 100000.0);

    if (d >= 0.7) // TODO: remake to config
    {
        currentTime = clock();
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
    lives = config_namespace::lives;
    points_for_kill = config_namespace::base_points_for_kill;
    max_enemies = config_namespace::max_enemies;

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
        print_final_text();
    } while (is_game_finish());

    endwin();
}
