cmake_minimum_required(VERSION 3.23)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "/Users/christiancarey/Downloads/SFML-2.5.1/include")

include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(minesweeper minesweeper.cpp minesweeper.h Button.cpp Button.h Toolbox.cpp Toolbox.h Tile.cpp Tile.h GameState.cpp GameState.h)
target_link_libraries(minesweeper sfml-graphics sfml-audio)


