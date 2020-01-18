//
// Created by kwh331 on 6/17/2018.
//

#include "player_board.h"
#include "minimax.h"
#include <random>
#include <ctime>

void Board::change_board(int move, char mark) {
    if (valid_move(move)) board[move] = mark;
}

bool Board::valid_move(int index) {
    if (0 <= index && index <= 8)
        return board[index] == ' ';
    return false;
}

std::vector<int> Board::free_moves() {
    std::vector<int> free_cells;
    for (auto i = 0; i <= 8; ++i) {
        if (board[i] == ' ') free_cells.push_back(i);
    }
    return free_cells;
}

bool Board::is_winner(char mark) {
    return (board[0] == mark && board[1] == mark && board[2] == mark) ||
           (board[3] == mark && board[4] == mark && board[5] == mark) ||
           (board[6] == mark && board[7] == mark && board[8] == mark) ||

           (board[0] == mark && board[3] == mark && board[6] == mark) ||
           (board[1] == mark && board[4] == mark && board[7] == mark) ||
           (board[2] == mark && board[5] == mark && board[8] == mark) ||

           (board[0] == mark && board[4] == mark && board[8] == mark) ||
           (board[2] == mark && board[4] == mark && board[6] == mark);
}

bool Board::game_over() {
    return is_winner('x') || is_winner('0') || free_moves().empty();
}


void Board::show_board() {
    std::cout << "_______\n";
    std::cout << '|' << board[0] << '|' << board[1] << '|' << board[2] << '|' << std::endl;
    std::cout << '|' << board[3] << '|' << board[4] << '|' << board[5] << '|' << std::endl;
    std::cout << '|' << board[6] << '|' << board[7] << '|' << board[8] << '|' << std::endl;
    std::cout << "-------\n";
}

int random_choice(int, int);

void Player::make_move() {
    int move = 0;
    if (type == 0) {
        // Human, prompt to enter the move
        std::cout << "Enter the move: ";
        std::cin >> move;
        while (!game_board->valid_move(move)) {
            std::cout << "Move is not available. Please, try again.\n";
            std::cout << "Enter the move: ";
            std::cin >> move;
        }
    } else if (type == 1) {
        // Intermediate AI, random move choice
        auto moves_list = game_board->free_moves();
        move = moves_list[random_choice(0, static_cast<int>(moves_list.size() - 1))];
    } else {
        // Advanced AI, use mini_max algorithm
        char opponent = '0' == mark ? 'x' : '0';
        move = minimax(mark, opponent, game_board->board_handle()).second;
    }
    game_board->change_board(move, mark);
}

int random_choice(int lower, int upper) {
    auto seed = static_cast<int>(time(nullptr));
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> dist(lower, upper);
    return static_cast<int>(dist(rng));
}