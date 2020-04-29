#include "big_integer.h"

big_integer& big_integer::operator+=(big_integer const &rhs) {
    int8_t com2 = module_compare(rhs);

    if (_sign == rhs._sign) {
        add(rhs);
    } else {
        if (com2 == -1) {
            big_integer res = rhs;
            res.sub(*this);
            *this = res;
        } else {
            sub(rhs);
        }
        if (_module.empty()) {
            _sign = false;
        } else {
            _sign ^= true;
        }
    }

    return *this;
}

big_integer& big_integer::operator-=(big_integer const &rhs) {

    if (!rhs._sign) {
        rhs._sign = true;
    } else {
        rhs._sign = false;
    }
    *this += rhs;

    return *this;
}