//
// Created by kwh331 on 6/26/2018.
//

#include "big_int_class.h"
#include <cmath>
#include <stdexcept>

bigint::bigint(const std::string &var) {
    auto end = var.rend();
    if (var[0] == '-') {
        negative = true;
        --end;
    }
    for (auto i = var.rbegin(); i != end; ++i) {
        if (*i == ',' || *i == '.') digits.clear();
        else digits.push_back(static_cast<unsigned char>(*i));
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
            ret_val.push_back(static_cast<unsigned char>(add_result + 48));
        }
        for (auto i = small.size(); i < big.size(); ++i) {
            add_result = carry + big[i] - 48;
            carry = add_result / 10;
            add_result %= 10;
            ret_val.push_back(static_cast<unsigned char>(add_result + 48));
        }
        if (carry) ret_val.push_back(static_cast<unsigned char>(carry + 48));
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
            ret_val.push_back(static_cast<unsigned char>(add_result + 48));
        }
        for (auto i = small.size(); i < big.size(); ++i) {
            add_result = carry + big[i] - 48;
            carry = add_result / 10;
            add_result %= 10;
            ret_val.push_back(static_cast<unsigned char>(add_result + 48));
        }
        if (carry) ret_val.push_back(static_cast<unsigned char>(carry + 48));
        digits = ret_val;
    } else {
        auto left = *this, right = other;
        left.negative = false;
        right.negative = false;
        if (negative) {
            digits = (right - left).digits;
        } else {
            auto result = left - right;
            digits = result.digits;
        }
    }
    return *this;
}

bigint bigint::operator++() {
    int add_value = digits[0] - 48;
    if (negative) --add_value;
    else ++add_value;
    if (add_value >= 10) {
        int carry = 1;
        digits[0] = static_cast<unsigned char>((add_value % 10) + 48);
        for (auto i = 1; (i < digits.size() && carry != 0); ++i) {
            add_value = carry + digits[i] - 48;
            carry = add_value / 10;
            digits[i] = static_cast<unsigned char>((add_value % 10) + 48);
        }
        if (carry) digits.push_back(static_cast<unsigned char>(carry + 48));
    } else if (add_value < 0) {
        int carry = 1;
        digits[0] = static_cast<unsigned char>(10 + add_value + 48);
        for (auto i = 1; i < digits.size() && carry != 0; ++i) {
            add_value = digits[i] - carry - 48;
            if (add_value < 0) {
                carry = 1;
                add_value += 10;
            } else carry = 0;
            digits[i] = static_cast<unsigned char>(add_value + 48);
        }
    } else digits[0] = static_cast<unsigned char>(add_value + 48);
    return *this;
}

bigint bigint::operator-(const bigint &other) const {
    if (!(negative || other.negative)) {
        const auto &small = *this < other ? digits : other.digits;
        const auto &big = digits == small ? other.digits : digits;
        std::string ret_val;
        auto sub_result = 0, carry = 0;
        for (auto i = 0; i < small.size(); ++i) {
            sub_result = big[i] - small[i] - carry;
            if (sub_result < 0) {
                carry = 1;
                sub_result += 10;
            } else carry = 0;
            ret_val.push_back(static_cast<unsigned char>(sub_result + 48));
        }
        for (auto i = small.size(); i < big.size(); ++i) {
            sub_result = big[i] - carry - 48;
            if (sub_result < 0) {
                carry = 1;
                sub_result += 10;
            } else carry = 0;
            ret_val.push_back(static_cast<unsigned char>(sub_result + 48));
        }
        while (ret_val[ret_val.size() - 1] == '0' && ret_val.size() > 1) ret_val.pop_back();
        if ((big != digits) && ret_val != "0") ret_val.push_back('-');
        return bigint(std::string(ret_val.rbegin(), ret_val.rend()));
    }
    auto left = *this, right = other;
    left.negative = false;
    right.negative = false;
    if (negative && other.negative) {
        return right - left;
    } else if (negative) {
        auto result = left + right;
        result.negative = true;
        return result;
    } else return *this + right;
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

bigint bigint::operator/(const bigint &other) const {
    if (other.digits[other.digits.size() - 1] == '0') throw std::domain_error("Division by zero");
    if (digits[digits.size() - 1] == '0') return bigint("0");
    auto limit = bigint("0");
    auto result = bigint("0");
    auto left = *this;
    auto right = other;
    left.negative = false;
    right.negative = false;
    if (negative == other.negative) {
        while (limit <= left && (limit+right) <= left) {
            limit += right;
            ++result;
        }
    } else {
        while (limit <= left) {
            limit += right;
            ++result;
        }
        result.negative = true;
    }
    return result;


}

bool bigint::operator<(const bigint &other) const {
    if (!(negative || other.negative)) {
        if (*this == other) return false;
        if (digits.size() < other.digits.size()) return true;
        for (auto i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] > other.digits[i]) return false;
            if (digits[i] < other.digits[i]) return true;
        }
    }
    if (negative == other.negative) {
        if (*this == other) return false;
        if (digits.size() < other.digits.size()) return false;
        for (auto i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] > other.digits[i]) return true;
            if (digits[i] < other.digits[i]) return false;
        }
    }
    return negative;
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
