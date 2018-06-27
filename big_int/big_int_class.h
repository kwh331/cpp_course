//
// Created by kwh331 on 6/26/2018.
//

#ifndef BIG_INT_BIG_INT_CLASS_H
#define BIG_INT_BIG_INT_CLASS_H


#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

class bigint {
    std::vector<unsigned char> digits;
    bool negative = false;
public:
    bigint() = default;

    explicit bigint(const std::string &);

    bigint(const bigint &);

    bigint(bigint &&) noexcept;

    std::string to_string() const;

    bigint &operator=(const bigint &);

    bigint operator+(const bigint &) const;

    bigint operator+=(const bigint &);

    bigint operator-(const bigint &) const;

    bigint operator*(const bigint &) const;

    bool operator<(const bigint &) const;

    bool operator>(const bigint &) const;

    bool operator<=(const bigint &) const;

    bool operator>=(const bigint &) const;

    bool operator==(const bigint &) const;

    bool operator!=(const bigint &) const;

};

#endif //BIG_INT_BIG_INT_CLASS_H
