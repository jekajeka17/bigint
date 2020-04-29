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

//    std::string s = "abd";
//    std::reverse(s.begin(), s.end());

    return "";
}