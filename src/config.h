#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace config_namespace
{

static json get_config()
{
    std::ifstream file("/home/vlad/Projects/Game/config/config.json"); // TODO: make relative path
    if (!file.is_open())
    {
        std::cerr << "Failed to open config.json file" << std::endl;
        return 1;
    }

    json config;
    file >> config;

    return config;
}

inline json config = get_config(); // TODO: check that config opened

inline uint32_t lives = config["rules"]["lives"];
inline uint32_t base_points_for_kill = config["rules"]["base_points_for_kill"];
inline uint32_t max_enemies = config["rules"]["max_enemies"];
inline std::string enemy_symbol = config["pawns_symbols"]["enemy_symbol"];
inline std::string player_symbol = config["pawns_symbols"]["player_symbol"];
inline std::string bullet_symbol = config["pawns_symbols"]["bullet_symbol"];
inline uint32_t enemies_start_speed = config["rules"]["enemies_start_speed"];

} // namespace config_namespace
