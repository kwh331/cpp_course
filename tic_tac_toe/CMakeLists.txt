cmake_minimum_required(VERSION 3.10)
project(tic_tac_toe)

set(CMAKE_CXX_STANDARD 11)

add_executable(tic_tac_toe main.cpp player_board.cpp player_board.h minimax.cpp minimax.h game_launcher.cpp game_launcher.h)