//
// Created by kwh331 on 6/17/2018.
//

#ifndef TIC_TAC_TOE_PLAYER_BOARD_H
#define TIC_TAC_TOE_PLAYER_BOARD_H

#include <vector>
#include <string>
#include <iostream>

class Board {
    std::vector<char> board = {' ', ' ', ' ',
                               ' ', ' ', ' ',
                               ' ', ' ', ' '};

public:
    Board() = default;

    std::vector<char> &board_handle() { return board; }

    void change_board(int, char);

    bool valid_move(int);

    std::vector<int> free_moves();

    bool is_winner(char);

    bool game_over();

    void show_board();
};

class Player {
    Board *game_board = nullptr;
public:
    std::string name;
    int type;
    char mark;

    Player(std::string &name, int type, char mark) :
            name{name}, type{type}, mark{mark} {}

    void set_game_board(Board *ptr) { game_board = ptr; }

    void make_move();
};


#endif //TIC_TAC_TOE_PLAYER_BOARD_H
