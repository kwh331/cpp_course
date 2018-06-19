//
// Created by kwh331 on 6/18/2018.
//

#include "game_launch.h"

#include <iostream>
#include <random>
#include <ctime>

int secret_number_generator(int, int);

void run_game() {
    int lower_bound, upper_bound;
    std::cout << "Enter the lower bound: \n";
    std::cin >> lower_bound;
    std::cout << "Enter the upper bound: \n";
    std::cin >> upper_bound;
    int secret_number = secret_number_generator(lower_bound, upper_bound);
    int guess = secret_number - 1, previous_guess = 0;
    std::string msg = "N/A";
    while (guess != secret_number) {
        std::cout << "Your guess is:";
        std::cin >> guess;
        if ((previous_guess >= guess && msg == "Bigger") || (previous_guess <= guess && msg == "Smaller")) {
            std::cout << "I said that secret number was " << msg << std::endl;
            previous_guess = guess;
        } else {
            previous_guess = guess;
            msg = guess < secret_number ? "Bigger" : guess == secret_number ? "You guessed." : "Smaller";
            std::cout << msg << std::endl;
        }
    }
}

int secret_number_generator(int lower, int upper) {
    auto seed = time(nullptr);
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> dist(lower, upper);
    return static_cast<int>(dist(rng));
}
