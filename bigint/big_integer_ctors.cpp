#include "big_integer.h"

big_integer::big_integer() : _sign(false) {}

big_integer::big_integer(const big_integer &that)
    : _module(that._module), _sign(that._sign) {}

big_integer::big_integer(const int a) {
    if (a == 0) {
        _sign = false;
    } else {
        _sign = a < 0;
        auto a_mod = static_cast<int64_t>(a);
        _module.push_back(static_cast<uint64_t>(a_mod < 0 ? -a_mod : a_mod));
    }
}

big_integer::big_integer(std::string str) {
    for (size_t i = (str[0] == '-' || str[0] == '+') ? 1 : 0; i < str.size(); ++i) {
        int digit = static_cast<int>(str[i] - '0');
        *this *= 10;
        *this += digit;
    }
    _sign = !_module.empty() && (str[0] == '-');
}

big_integer::~big_integer() = default;
