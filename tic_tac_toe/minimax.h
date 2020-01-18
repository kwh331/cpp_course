//
// Created by kwh331 on 6/17/2018.
//

#ifndef TIC_TAC_TOE_MINIMAX_H
#define TIC_TAC_TOE_MINIMAX_H

#include <vector>
#include <utility>

using Move = std::pair<int, int>;

Move minimax(char &, char &, std::vector<char>, bool = true);

#endif //TIC_TAC_TOE_MINIMAX_H
