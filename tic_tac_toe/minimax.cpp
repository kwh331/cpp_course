//
// Created by kwh331 on 6/17/2018.
//

#include "minimax.h"

bool winner(char mark, const std::vector<char> &board) {
    return (board[0] == mark && board[1] == mark && board[2] == mark) ||
           (board[3] == mark && board[4] == mark && board[5] == mark) ||
           (board[6] == mark && board[7] == mark && board[8] == mark) ||
           (board[0] == mark && board[3] == mark && board[6] == mark) ||
           (board[1] == mark && board[4] == mark && board[7] == mark) ||
           (board[2] == mark && board[5] == mark && board[8] == mark) ||
           (board[0] == mark && board[4] == mark && board[8] == mark) ||
           (board[2] == mark && board[4] == mark && board[6] == mark);
}


std::vector<Move> free_moves(const std::vector<char> &board) {
    std::vector<Move> moves;
    for (auto i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            moves.emplace_back(0, i);
        }
    }
    return moves;
}

bool draw(const std::vector<char> &board) {
    return !winner('x', board) && !winner('0', board) && free_moves(board).empty();
}

Move best_move(const std::vector<Move> &list, bool max) {
    auto best_move_index = list[0];
    for (auto v: list) {
        if ((max && best_move_index.first < v.first) || (!max && best_move_index.first > v.first))
            best_move_index = v;
    }
    return best_move_index;
}

Move minimax(char &maximizer, char &minimizer, std::vector<char> board, bool turn) {
    if (winner(maximizer, board)) return {1, -1};
    if (winner(minimizer, board)) return {-1, -1};
    if (draw(board)) return {0, -1};
    auto moves = free_moves(board);
    for (auto &i: moves) {
        auto new_board(board);
        new_board[i.second] = turn ? maximizer : minimizer;
        i.first = minimax(maximizer, minimizer, new_board, !turn).first;
    }
    return best_move(moves, turn);
}
