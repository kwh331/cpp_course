//
// Created by kwh331 on 6/28/2018.
//

#include "rational_num.h"
#include <cmath>
#include <cassert>

unsigned gcd(unsigned a, unsigned b) {
    assert(a != 0);
    return b == 0 ? a : gcd(b, a % b);
}

void rational_num::reduce() {
    if (numerator == 0) {
        denominator = 1;
        return;
    }
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    if (denominator == 1 || numerator == 1) return;
    int dv = gcd(static_cast<unsigned>(std::abs(numerator)), static_cast<unsigned>(denominator));
    denominator /= dv;
    numerator /= dv;
}

rational_num::operator double() const {
    return static_cast<double>(numerator) / static_cast<double>(denominator);
}

std::string rational_num::to_string() {
    auto ret_val = std::to_string(double(*this));
    while (ret_val[ret_val.size() - 1] == '0' and ret_val.size() >= 4) ret_val.pop_back();
    return ret_val;
}

rational_num::rational_num(int a, int b) : numerator{a}, denominator{b} { reduce(); }

rational_num::rational_num(const rational_num &other) : numerator{other.numerator}, denominator{other.denominator} {}

rational_num rational_num::operator+(const rational_num &other) const {

    int new_numerator = numerator * other.denominator + other.numerator * denominator;
    int new_denominator = denominator * other.denominator;
    return rational_num(new_numerator, new_denominator);
}

rational_num rational_num::operator-(const rational_num &other) const {
    int new_numerator = numerator * other.denominator - other.numerator * denominator;
    int new_denominator = denominator * other.denominator;
    return rational_num(new_numerator, new_denominator);
}

rational_num rational_num::operator*(const rational_num &other) const {
    int new_numerator = numerator * other.numerator;
    int new_denominator = denominator * other.denominator;
    return rational_num(new_numerator, new_denominator);
}

rational_num rational_num::operator/(const rational_num &other) const {
    int new_numerator = numerator * other.denominator;
    int new_denominator = denominator * other.numerator;
    return rational_num(new_numerator, new_denominator);
}

rational_num &rational_num::operator+=(const rational_num &other) {
    numerator = numerator * other.denominator + other.numerator * denominator;
    denominator *= other.denominator;
    reduce();
    return *this;
}

rational_num &rational_num::operator-=(const rational_num &other) {
    numerator = numerator * other.denominator - other.numerator * denominator;
    denominator *= other.denominator;
    reduce();
    return *this;
}

rational_num &rational_num::operator*=(const rational_num &other) {
    numerator *= other.numerator;
    denominator *= other.denominator;
    reduce();
    return *this;
}

rational_num &rational_num::operator/=(const rational_num &other) {
    numerator *= other.denominator;
    denominator *= other.numerator;
    reduce();
    return *this;
}
