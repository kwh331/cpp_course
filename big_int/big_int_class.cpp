//
// Created by kwh331 on 6/26/2018.
//

#include "big_int_class.h"
#include <cmath>

using std::cout;

bigint::bigint(const std::string &var) {
    auto end = var.rend();
    if (var[0] == '-') {
        negative = true;
        --end;
    }
    for (auto i = var.rbegin(); i != end; ++i) {
        if (*i == ',' || *i == '.') digits.clear();
        else digits.push_back(*i);
    }

}

bigint::bigint(const bigint &other) {
    digits = other.digits;
    negative = other.negative;
}

bigint::bigint(bigint &&other) noexcept {
    digits = other.digits;
    other.digits.clear();
    negative = other.negative;
}

std::string bigint::to_string() const {
    std::string retval;
    if (negative) retval.push_back('-');
    for (auto i = digits.rbegin(); i != digits.rend(); ++i) retval.push_back(*i);
    return retval;
}

bigint &bigint::operator=(const bigint &other) {
    digits = other.digits;
    negative = other.negative;
}

bigint bigint::operator+(const bigint &other) const {
    if (negative == other.negative) {
        std::string ret_val;
        auto carry = 0, add_result = 0;
        const auto &small = *this < other ? digits : other.digits;
        const auto &big = small == digits ? other.digits : digits;
        for (auto i = 0; i < small.size(); ++i) {
            add_result = carry + small[i] + big[i] - 2 * 48;
            carry = add_result / 10;
            add_result %= 10;
            ret_val.push_back(add_result + 48);
        }
        for (auto i = small.size(); i < big.size(); ++i) {
            add_result = carry + big[i] - 48;
            carry = add_result / 10;
            add_result %= 10;
            ret_val.push_back(add_result + 48);
        }
        if (carry) ret_val.push_back(carry + 48);
        if (negative) ret_val.push_back('-');
        return bigint(std::string(ret_val.rbegin(), ret_val.rend()));
    }
    auto left = *this, right = other;
    left.negative = false;
    right.negative = false;
    if (negative) return right - left;
    return left - right;
}

bigint bigint::operator+=(const bigint &other) {
    if (negative == other.negative) {
        std::vector<unsigned char> ret_val;
        auto carry = 0, add_result = 0;
        const auto &small = *this < other ? digits : other.digits;
        const auto &big = small == digits ? other.digits : digits;
        for (auto i = 0; i < small.size(); ++i) {
            add_result = carry + small[i] + big[i] - 2 * 48;
            carry = add_result / 10;
            add_result %= 10;
            ret_val.push_back(add_result + 48);
        }
        for (auto i = small.size(); i < big.size(); ++i) {
            add_result = carry + big[i] - 48;
            carry = add_result / 10;
            add_result %= 10;
            ret_val.push_back(add_result + 48);
        }
        if (carry) ret_val.push_back(carry + 48);
        if (negative) ret_val.push_back('-');
        digits = ret_val;
        return *this;
    }
    auto left = *this, right = other;
    left.negative = false;
    right.negative = false;
    if (negative) return right - left;
    auto result = left - right;
    digits = result.digits;
    return *this;
}

bigint bigint::operator-(const bigint &other) const {
    if (negative == other.negative) {
        const auto &small = *this < other && negative ||
                            *this > other && !negative ? other.digits : digits;
        const auto &big = digits == small ? other.digits : digits;
        std::string ret_val;
        auto sub_result = 0, carry = 0;
        for (auto i = 0; i < small.size(); ++i) {
            sub_result = big[i] - small[i] - carry;
            if (sub_result < 0) {
                carry = 1;
                sub_result = 10 + sub_result;
            } else carry = 0;
            ret_val.push_back(sub_result + 48);
        }
        for (auto i = small.size(); i < big.size(); ++i) {
            sub_result = big[i] - carry;
            if (sub_result < 0) {
                carry = 1;
                sub_result = 10 - sub_result;
            } else carry = 0;
            ret_val.push_back(sub_result);
        }
        while (ret_val[ret_val.size() - 1] == '0' && ret_val.size() >= 2) ret_val.pop_back();
        if ((big != digits || big == digits && negative) && ret_val != "0") ret_val.push_back('-');

        return bigint(std::string(ret_val.rbegin(), ret_val.rend()));
    }
    auto left = *this, right = other;
    left.negative = false;
    right.negative = false;
    auto result = left + right;
    if (negative) result.negative = true;
    return result;
}

bigint bigint::operator*(const bigint &other) const {
    auto result = bigint("0");
    for (auto i = 0; i < digits.size(); ++i) {
        for (auto z = 0; z < other.digits.size(); ++z) {
            result += bigint(std::to_string((digits[i] - 48) * (other.digits[z] - 48) * std::pow(10, z + i)));
        }
    }
    result.negative = negative && !other.negative || !negative && other.negative;
    return result;
}

bool bigint::operator<(const bigint &other) const {
    if (negative == other.negative) {
        if (negative)
            return !(*this == other) && (digits.size() > other.digits.size() ||
                                         digits.size() == other.digits.size() &&
                                         digits[digits.size() - 1] >
                                         other.digits[other.digits.size() - 1]);
        else
            return !(*this == other) && (digits.size() < other.digits.size() ||
                                         digits.size() == other.digits.size() &&
                                         digits[digits.size() - 1] <
                                         other.digits[other.digits.size() - 1]);
    } else if (negative) return true;
    return false;
}

bool bigint::operator==(const bigint &other) const {
    return (negative == other.negative) && (digits == other.digits);
}

bool bigint::operator!=(const bigint &other) const {
    return !(*this == other);
}

bool bigint::operator>(const bigint &other) const {
    return !(*this < other) && !(*this == other);
}

bool bigint::operator<=(const bigint &other) const {
    return *this < other || *this == other;
}

bool bigint::operator>=(const bigint &other) const {
    return *this > other || *this == other;
}


