//
// Created by kwh331 on 6/17/2018.
//

#include "compute_postfix_expression.h"
#include <map>
#include <cmath>

int is_oper_func(const std::string&);

double eval(const std::string&, const std::string&, const std::string&);

double eval(const std::string&, const std::string&);

double compute(std::vector<std::string> &expression) {
    std::string operator_function, item_one, item_two;
    int z = 0, status = 0;
    while (expression.size() != 1) {
        status = is_oper_func(expression[z]);
        while (!status) {
            ++z;
            status = is_oper_func(expression[z]);
        }
        operator_function = expression[z];
        if (status > 6) {
            item_one = expression[z - 1];
            expression[z - 1] = std::to_string(eval(item_one, operator_function));
            expression.erase(expression.begin() + z);
        } else {
            item_one = expression[z - 2];
            item_two = expression[z - 1];
            expression[z - 2] = std::to_string(eval(item_one, operator_function, item_two));
            expression.erase(expression.begin() + z - 1, expression.begin() + z + 1);
        }
        status = 0;
        z = 0;
    }
    auto result = stod(expression[expression.size() - 1]);
    if (result == -0) return -result;
    return result;
}

namespace {
    std::map<std::string, int> operator_identifier{{"+",    1},
                                              {"-",    2},
                                              {"*",    3},
                                              {"/",    4},
                                              {"^",    5},
                                              {"%",    6},
                                              {"sqrt", 7},
                                              {"cos",  8},
                                              {"sin",  9},
                                              {"tg",   10},
                                              {"ctg",  11},
                                              {"ln",   12}};
}
int is_oper_func(const std::string& token) {
    for (const auto& it:operator_identifier) {
        if (token == it.first) {
            return it.second;
        }
    }
    return 0;
}


double eval(const std::string& operand_one, const std::string& oper_func, const std::string& operand_two) {
    double result = 0;
    switch (operator_identifier[oper_func]) {
        case 1:
            result = std::stod(operand_one) + std::stod(operand_two);
            break;
        case 2:
            result = std::stod(operand_one) - std::stod(operand_two);
            break;
        case 3:
            result = std::stod(operand_one) * std::stod(operand_two);
            break;
        case 4:
            result = std::stod(operand_one) / std::stod(operand_two);
            break;
        case 5:
            result = std::pow(std::stod(operand_one), std::stod(operand_two));
            break;
        case 6:
            result = std::fmod(std::stod(operand_one), std::stod(operand_two));
            break;
        default:
            break;
    }
    return result;
}

double eval(const std::string& operand, const std::string& oper_func) {
    double result = 0;
    switch (operator_identifier[oper_func]) {
        case 7:
            result = std::sqrt(std::stod(operand));
            break;
        case 8:
            result = std::cos(std::stod(operand));
            break;
        case 9:
            result = std::sin(std::stod(operand));
            break;
        case 10:
            result = std::tan(std::stod(operand));
            break;
        case 11:
            result = std::pow(std::tan(std::stod(operand)), -1);
            break;
        case 12:
            result = std::log(std::stod(operand));
            break;
        default:
            break;
    }
    return result;
}
