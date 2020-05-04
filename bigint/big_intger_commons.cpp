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
    big_integer res = a;
    for (size_t i = a._module.size(); res > 0; --i) {
        uint64_t res1 = res.digit(i) % 10;
        s += res1 + '0';
        res /= 10;
    }


//    std::string s = "abd";
//    std::reverse(s.begin(), s.end());

    return s;
}