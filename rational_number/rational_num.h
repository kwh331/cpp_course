//
// Created by kwh331 on 6/28/2018.
//

#ifndef RATIONAL_NUMBER_RATIONAL_NUM_H
#define RATIONAL_NUMBER_RATIONAL_NUM_H

#include <string>

unsigned gcd(unsigned, unsigned);

class rational_num {
public:
    explicit rational_num(int, int);

    rational_num(const rational_num &);

    rational_num &operator=(const rational_num &) = default;

    rational_num operator+(const rational_num &) const;

    rational_num operator-(const rational_num &) const;

    rational_num operator*(const rational_num &) const;

    rational_num operator/(const rational_num &) const;

    rational_num &operator+=(const rational_num &);

    rational_num &operator-=(const rational_num &);

    rational_num &operator*=(const rational_num &);

    rational_num &operator/=(const rational_num &);

    std::string to_string();

    explicit operator double() const;

    inline int get_numerator() const { return numerator; }

    inline int get_denominator() const { return denominator; }

    inline rational_num &set_numerator(int x) {
        numerator = x;
        return *this;
    }

    inline rational_num &set_denominator(int x) {
        denominator = x;
        return *this;
    }

private:
    int numerator;
    int denominator;

    void reduce();
};

#endif //RATIONAL_NUMBER_RATIONAL_NUM_H
