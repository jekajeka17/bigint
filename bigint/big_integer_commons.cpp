#include "big_integer.h"

big_integer& big_integer::operator=(big_integer const& other) {
    if (*this != other) {
        _module = other._module;
        _sign = other._sign;
    }

    return *this;
}

std::string to_string(const big_integer &a) {
    std::string s;
    big_integer tmp = a;
    while (tmp > 0) {
        std::pair<big_integer, uint64_t> res = tmp.div_digit(10);
        s += static_cast<char>(res.second + '0');
        tmp = res.first;
    }

    std::reverse(s.begin(), s.end());
    return s;
}

// 60 -> 30 -> 15 -> 7 - > 3 -> 1 -> 0
// 001111
// 111100