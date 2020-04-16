#include "big_integer.h"

big_integer& big_integer::operator*=(const uint64_t a) {
    uint64_t p = 0;
    uint64_t sum = 0;
    int i = _module.size();
    while(_module[i] > 0) {
        --i;
        sum = (_module[i] * a) % (uint64_t )pow(2, 64) + p;
        p = sum/(uint64_t )pow(2, 64);
        _module[i] = sum;
    }
    _module[i - 1] = p;
    _sign = false;
}

big_integer& big_integer::shrink() {
    std::string s = "";
    int j = 0;
    while (_module[j] == 0) {
        j++;
    }
    for (size_t i = j; i < _module.size(); ++i) {
        s += (char)_module[i];
    }
    *this = big_integer(s);
}

uint8_t big_integer::compare(big_integer const &rhs) {
    if (_sign && !rhs._sign) {
        return -1;
    }
    if (!_sign && rhs._sign) {
        return 1;
    }
    if (_sign == rhs._sign) {
        if (_module.size() < rhs._module.size()) {
            return -1;
        }
        if (_module.size() > rhs._module.size()) {
            return 1;
        }
        if (_module.size() == rhs._module.size()) {
            for (size_t i = 0; i < _module.size(); ++i) {
                if (_module[i] < rhs._module[i]) {
                    return -1;
                }
                if (_module[i] > rhs._module[i]) {
                    return 1;
                }
            }
            return 0;
        }
    }
}

uint64_t big_integer::digit(size_t) {

}

