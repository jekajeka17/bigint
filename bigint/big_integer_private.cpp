#include "big_integer.h"

big_integer big_integer::operator*=(const uint64_t a) {
    uint64_t carry = 0;

    big_integer res;
    res._module.reserve(_module.size() + 1);

    for (size_t i = 0; i < _module.size(); ++i) {
        uint64_t d0 = digit(i);
        uint64_t d1;

        __asm__ (
            "mul %%rbx;"
            "add %%rcx, %%rax;"
            "adc $0, %%rdx;"
            : "=a" (d1), "=d" (carry)
            : "a" (d0), "b" (a), "c" (carry)
        );

        // RAX <- d0
        // RBX <- a
        // RCX <- carry
        // d0 * a = RDX | RAX

        res._module.push_back(d1);
    }

    if (carry != 0) {
        res._module.push_back(carry);
    }

    res.shrink();
    return res;
}

big_integer& big_integer::shrink() {
    std::string s;
    int j = 0;
    while (_module[j] == 0) {
        j++;
    }
    for (size_t i = j; i < _module.size(); ++i) {
        s += (char)_module[i];
    }
    *this = big_integer(s);
    return *this;
}

uint8_t big_integer::compare(big_integer const &rhs) {
    if (_sign && !rhs._sign) {
        return -1;
    }
    if (!_sign && rhs._sign) {
        return 1;
    }

    if (_module.size() < rhs._module.size()) {
        return -1;
    }
    if (_module.size() > rhs._module.size()) {
        return 1;
    }

    for (size_t i = _module.size(); i-- > 0;) {
        if (_module[i] < rhs._module[i]) {
            return -1;
        }
        if (_module[i] > rhs._module[i]) {
            return 1;
        }
    }
    return 0;
}

uint64_t big_integer::digit(size_t i) {
    if (i >= _module.size()) {
        return 0;
    } else {
        return _module[i];
    }
}

