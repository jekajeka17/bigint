#include "big_integer.h"

big_integer& big_integer::operator+=(big_integer const &rhs) {
    uint8_t com1 = sign_compare(rhs);
    uint8_t com2 = compare_without_sign(rhs);

    if (com1 == -1 && com2 == 1) {
        sub(rhs);
        _sign = true;
    }
    if (com1 == -1 && com2 == -1) {
        rhs.sub(*this);
        this = rhs;
    }
    if (com1 == 1 && com2 == 1) {
        sub(rhs);
    }
    if (com1 == 1 && com2 == -1) {
        rhs.sub(*this);
        this = rhs;
        _sign = true;
    }
    if (com1 == 0 && com2 == 0) {
        uint64_t pos = _module.size() - rhs._module.size();
        add(rhs, pos);
    }
    if (com1 == 0 && com2 == 1 && !_sign) {
        uint64_t pos = _module.size() - rhs._module.size();
        add(rhs, pos);
    }
    if (com1 == 0 && com2 == -1 && !_sign) {
        uint64_t pos = rhs._module.size() - _module.size();
        rhs.add(*this, pos);
        this = rhs;
    }
    if (com1 == 0 && com2 == 1 && _sign) {
        uint64_t pos = _module.size() - rhs._module.size();
        add(rhs, pos);
        _sign = false;
    }
    if (com1 == 0 && com2 == -1 && _sign) {
        uint64_t pos = rhs._module.size() - _module.size();
        rhs.add(*this, pos);
        this = rhs;
        _sign = false;
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