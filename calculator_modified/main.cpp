#include "infix_notation_to_postfix.h"
#include "compute_postfix_expression.h"

std::string& input_data();
void launch_calculator();

int main() {
    launch_calculator();
    return 0;
}


std::string& input_data() {
    std::string& expression = *(new std::string);
    std::cout << "Enter the expression (cos(), sin(), sqrt(), ln(), tg(), ctg(), e, pi) or q to quit:\n";
    std::getline(std::cin, expression);
    return expression;
}

void launch_calculator() {
    std::string& infix = input_data();
    while (infix != "q") {
        std::vector<std::string>& postfix = shunting_yard(infix);
        std::cout << "The result is: " << compute(postfix) << std::endl;
        delete &infix;
        delete &postfix;
        infix = input_data();
    }
}