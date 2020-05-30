#include "big_integer.h"

big_integer& big_integer::operator=(big_integer const& other) {
    if (*this != other) {
        _module = other._module;
        _sign = other._sign;
    }

    return *this;
}

std::string to_string(const big_integer &a) {
    if (a == 0) {
        return "0";
    }
    std::string s;
    big_integer tmp = a;
    while (tmp != 0) {
        std::pair<big_integer, uint64_t> res = tmp.div_digit(10);
        s += static_cast<char>(res.second + '0');
        tmp = res.first;
    }
    if (a._sign) {
        s += '-';
    }

    std::reverse(s.begin(), s.end());

    return s;
}

std::ostream& operator<<(std::ostream& s, const big_integer &a) {
    s << to_string(a);
    return s;
}
