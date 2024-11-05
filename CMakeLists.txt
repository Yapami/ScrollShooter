# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(ScrollShooter)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем список исходных файлов
set(SOURCES
    src/main.cpp
    src/gamemode.cpp
    src/pawns.cpp
)

set(HEADERS
    src/gamemode.h
    src/pawns.h
)

# Создаём исполняемый файл
add_executable(ScrollShooter ${SOURCES} ${HEADERS})

# Находим и подключаем библиотеку ncurses
find_package(Curses REQUIRED)
target_link_libraries(ScrollShooter ${CURSES_LIBRARIES})

# Находим и подключаем библиотеку nlohmann_json
find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(ScrollShooter nlohmann_json::nlohmann_json)

# Включаем директории заголовочных файлов
target_include_directories(ScrollShooter PRIVATE ${CURSES_INCLUDE_DIR})