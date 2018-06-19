//
// Created by kwh331 on 6/17/2018.
//

#include "infix_notation_to_postfix.h"
#include <map>
#include <iostream>

std::vector<std::string> &shunting_yard(const std::string &expression) {
    std::map<std::string, int> operator_precedence{{"+",    2},
                                                   {"-",    2},
                                                   {"%",    4},
                                                   {"*",    4},
                                                   {"/",    3},
                                                   {"^",    5},
                                                   {"sqrt", 6},
                                                   {"cos",  6},
                                                   {"sin",  6},
                                                   {"tg",   6},
                                                   {"ctg",  6},
                                                   {"ln",   6},
                                                   {"(",    0},
                                                   {")",    0}};
    std::string token;
    std::vector<std::string> operator_stack;
    std::vector<std::string> &output_queue = *(new std::vector<std::string>);
    int z = 0;
    while (z != expression.size()) {
        if (expression[z] == ' ') {
            ++z;
        } else if (expression[z] == 'e') {
            token = "2.7182818284";
            output_queue.push_back(token);
            ++z;
        } else if (expression[z] == 'p') {
            token = "3.14159265359";
            z += 2;
            output_queue.push_back(token);
        } else if (expression[z] >= '0' && expression[z] <= '9') {
            while (expression[z] >= '0' && expression[z] <= '9' || expression[z] == '.') {
                token += expression[z];
                ++z;
            }
            output_queue.push_back(token);
        } else {
            token += expression[z];
            int status = 0;
            while (status == 0) {
                for (const auto &it: operator_precedence) {
                    if (token == it.first) {
                        status = 1;
                        ++z;
                        break;
                    }
                }
                if (status == 0) {
                    if (token.size() == 5) throw std::invalid_argument("Invalid operator was inputted.\n");
                    else {
                        ++z;
                        token += expression[z];
                    }
                }
            }
            auto j = static_cast<int>(operator_stack.size() - 1);
            if (token == ")") {
                while (operator_stack[j] != "(") {
                    output_queue.push_back(operator_stack[j]);
                    operator_stack.erase(operator_stack.begin() + j);
                    --j;
                }
                operator_stack.erase(operator_stack.begin() + j);
            } else {
                if (token == "(") operator_stack.push_back(token);
                else {
                    if (j >= 0) {
                        while (operator_precedence[operator_stack[j]] >= operator_precedence[token] and
                               operator_stack[j] != "(") {
                            output_queue.push_back(operator_stack[j]);
                            operator_stack.erase(operator_stack.begin() + j);
                            --j;
                        }
                        operator_stack.push_back(token);
                    } else {
                        operator_stack.push_back(token);
                    }
                }
            }
        }
        token.clear();
    }
    for (auto i = static_cast<int>(operator_stack.size() - 1); i >= 0; --i) output_queue.push_back(operator_stack[i]);
    return output_queue;
}