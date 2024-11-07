cmake_minimum_required(VERSION 3.10)

project(ScrollShooter LANGUAGES CXX)

set(SOURCES
    code/src/main.cpp
    code/src/scrollshooter.cpp
    code/src/pawns.cpp
)

add_executable(ScrollShooter ${SOURCES})

find_package(Curses REQUIRED)
target_link_libraries(ScrollShooter PRIVATE ${CURSES_LIBRARIES})

find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(ScrollShooter PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(ScrollShooter PRIVATE 
    ${CURSES_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/code/include
    ${CMAKE_CURRENT_SOURCE_DIR}/code/libraries
)