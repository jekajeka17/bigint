#include "big_integer.h"

big_integer& big_integer::operator+=(big_integer const &rhs) {
    if (_sign == rhs._sign) {
        add(rhs);
    } else {
        if (module_compare(rhs) == -1) {
            big_integer res = rhs;
            res.sub(*this);
            *this = res;
        } else {
            this->sub(rhs);
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
    return *this += -rhs;
}

big_integer& big_integer::operator*=(big_integer const &rhs) {
    big_integer res;

    for (size_t i = 0; i < rhs._module.size(); ++i) {
        big_integer tmp = this->mul_digit(rhs.digit(i));
        res.add(tmp, i);
    }

    res._sign = (!res._module.empty()) && (_sign != rhs._sign);

    return *this = res;
}

big_integer big_integer::operator+() const {
    return big_integer(*this);
}

big_integer big_integer::operator-() const {
    big_integer res = *this;
    res._sign = (!_module.empty()) && (!_sign);
    return res;
}

big_integer& big_integer::operator++() {
    //TODO: Implement!
}

const big_integer big_integer::operator++(int) {
    //TODO: Implement!
}

big_integer& big_integer::operator--() {
    //TODO: Implement!
}

const big_integer big_integer::operator--(int) {
    //TODO: Implement!
}