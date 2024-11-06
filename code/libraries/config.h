#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace config
{
static json get_config()
{
    std::ifstream file("../config/config.json");
    if (!file.is_open())
    {
        std::cerr << "Error: Failed to open config.json file" << std::endl;
        std::exit(EXIT_FAILURE);
        return 1;
    }

    json config;
    file >> config;
    file.close();

    return config;
}

inline json config = get_config();

inline const uint32_t lives = config["rules"]["lives"];
inline const uint32_t base_points_for_kill = config["rules"]["base_points_for_kill"];
inline const uint32_t max_enemies = config["rules"]["max_enemies"];
inline const std::string enemy_symbol = config["pawns_symbols"]["enemy_symbol"];
inline const std::string player_symbol = config["pawns_symbols"]["player_symbol"];
inline const std::string bullet_symbol = config["pawns_symbols"]["bullet_symbol"];
inline const float enemies_start_speed = config["rules"]["enemies_start_speed"];
inline const float enemies_spawn_frequency = config["rules"]["enemies_spawn_frequency"];
inline const float bullets_start_speed = config["rules"]["bullets_speed"];
} // namespace config
