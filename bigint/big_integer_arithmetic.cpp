#include "big_integer.h"

big_integer& big_integer::operator+=(big_integer const &rhs) {
    if (_sign == rhs._sign) {
        add(rhs);
    } else {
        if (module_compare(rhs) == -1) {
            big_integer tmp = rhs;
            tmp.sub(*this);
            *this = tmp;
        } else {
            sub(rhs);
        }
        if (_module.empty()) {
            _sign = false;
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
    return *this += 1;
}

const big_integer big_integer::operator++(int) {
    big_integer a = *this;
    *this += 1;
    return a;
}

big_integer& big_integer::operator--() {
    return *this -= 1;
}

const big_integer big_integer::operator--(int) {
    big_integer a = *this;
    *this -= 1;
    return a;
}

big_integer operator+(big_integer a, big_integer const& b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b) {
    return a *= b;
}

// TODO
big_integer& big_integer::operator/=(big_integer const &rhs) {
    return *this;
}

// TODO
big_integer& big_integer::operator%=(big_integer const &rhs) {
    return *this;
}

big_integer operator/(big_integer a, const big_integer &b) {
    return a /= b;
}

big_integer operator%(big_integer a, const big_integer &b) {
    return a %= b;
}