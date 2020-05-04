#include "big_integer.h"

big_integer& big_integer::operator=(big_integer const& other) {
    if (*this != other) {
        _module = other._module;
        _sign = other._sign;
    }

    return *this;
}

std::string to_string(const big_integer &a) {
    // TODO: Implement!
    std::string s;
    big_integer tmp = a;
    for (size_t i = a._module.size(); tmp > 0; --i) {
        uint64_t res1 = tmp.digit(i) % 10;
        s += res1 + '0';
        tmp /= 10;
    }


//    std::string s = "abd";
//    std::reverse(s.begin(), s.end());

    return s;
}

// 60 -> 30 -> 15 -> 7 - > 3 -> 1 -> 0
// 001111
// 111100