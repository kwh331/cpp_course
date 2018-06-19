//
// Created by kwh331 on 6/18/2018.
//

#include "game_launcher.h"

Player *create_player(char= ' ');

void launch_game() {
    auto game_board = new Board();

    Player *player_one = create_player();
    Player *player_two = create_player('0' == player_one->mark ? 'x' : '0');

    player_one->set_game_board(game_board);
    player_two->set_game_board(game_board);

    bool turn = true;
    while (!game_board->game_over()) {
        game_board->show_board();
        if (turn) {
            player_one->make_move();
            turn = false;
        } else {
            player_two->make_move();
            turn = true;
        }
    }
    if (game_board->is_winner(player_one->mark)) {
        std::cout << "Player " << player_one->name << " won.\n";
    } else if (game_board->is_winner(player_two->mark)) {
        std::cout << "Player " << player_two->name << " won.\n";
    } else std::cout << "It is draw.\n";
    delete player_one;
    delete player_two;
    delete game_board;
}


Player *create_player(char mark) {
    std::string name;
    std::cout << "Enter name:";
    std::cin >> name;
    int type = 0;
    std::cout << "Enter type (Human - 0, Intermediate AI - 1, Advanced AI - 2):";
    std::cin >> type;
    if (mark == ' ') {
        std::cout << "Which one x or 0:";
        std::cin >> mark;
    }
    auto ptr = new Player(name, type, mark);
    return ptr;
}