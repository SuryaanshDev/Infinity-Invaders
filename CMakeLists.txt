cmake_minimum_required(VERSION 3.28)
project(GameCpp LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(main src/main.cpp "include/Player.h" "src/player.cpp" "include/Bullet.h" "src/bullet.cpp" "src/Enemy.cpp" "include/EnemySpawner.h" "src/EnemySpawner.cpp" "include/Math.h" "src/math.cpp" "include/HUD.h" "src/hud.cpp" "include/Menu.h" "src/menu.cpp")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)
target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
