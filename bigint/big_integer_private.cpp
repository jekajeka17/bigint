#include "big_integer.h"

big_integer big_integer::mul_digit(const uint64_t a) {
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

std::pair<big_integer, uint64_t> big_integer::div_digit(uint64_t x) {
    uint64_t remainder = 0;
    big_integer res;

    for (size_t i = 0; i < _module.size(); ++i) {
        uint64_t d = digit(_module.size() - 1 - i);
        uint64_t r = 0;
        __asm__ (
            "div %%rbx;"
            : "=a" (r), "=d" (remainder)
            : "a" (d), "b" (x), "d" (remainder)
        );

        // RDX | RAX -> result -> RAX, remainder -> RDX

        res._module.push_back(r);
    }

    std::reverse(res._module.begin(), res._module.end());

    res.shrink();
    return std::make_pair(res, remainder);
}

big_integer& big_integer::shrink() {
    size_t cnt = _module.size();
    for (size_t i = _module.size(); i-- > 0;) {
        if (_module[i] == 0) {
            cnt--;
        } else {
            break;
        }
    }
    if (cnt == 0) {
        _sign = false;
    }
    _module.resize(cnt);
    return *this;
}

int8_t big_integer::compare(big_integer const &rhs) const {
    if (_sign != rhs._sign) {
        return sign_compare(rhs);
    } else {
        return module_compare(rhs) * (_sign ? -1 : 1);
    }
}

int8_t big_integer::module_compare(big_integer const &rhs) const {
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

int8_t big_integer::sign_compare(big_integer const &rhs) const {
    if (_sign && !rhs._sign) {
        return -1;
    }
    if (!_sign && rhs._sign) {
        return 1;
    }
    return 0;
}

uint64_t big_integer::digit(size_t i) const {
    if (i >= _module.size()) {
        return 0;
    } else {
        return _module[i];
    }
}

big_integer& big_integer::add(const big_integer &rhs, const size_t pos) {
    uint64_t carry = 0;
    size_t length = std::max(_module.size(), rhs._module.size() + pos);
    _module.resize(length, 0);
    for (size_t i = pos; i < length; ++i) {
        uint64_t a = digit(i);
        uint64_t b = rhs.digit(i - pos);
        __asm__(
                "xor %%rdx, %%rdx;"
                "add %%rbx, %%rax;"
                "adc $0, %%rdx;"
                "add %%rcx, %%rax;"
                "adc $0, %%rdx;"
                : "=a" (_module[i]), "=d" (carry)
                : "a" (a), "b" (b), "c" (carry)
                );
    }
    _module.push_back(carry);
    shrink();
    return *this;
}

big_integer& big_integer::sub(const big_integer &rhs) {
    uint64_t borrow = 0;
    for (size_t i = 0; i < _module.size(); ++i) {
        uint64_t a = digit(i);
        uint64_t b = rhs.digit(i);
        __asm__(
                "xor %%rdx, %%rdx;"
                "sub %%rbx, %%rax;"
                "adc $0, %%rdx;"
                "sub %%rcx, %%rax;"
                "adc $0, %%rdx;"
                : "=a" (_module[i]), "=d" (borrow)
                : "a" (a), "b" (b), "c" (borrow)
                );
    }
    shrink();
    return *this;
}

big_integer big_integer::to_two_comp(size_t size) const {
    big_integer res = *this;
    res._sign = false;

    if (_sign) {
        for (uint64_t & d : res._module) {
            d = ~d;
        }
        res._module.resize(size, ~static_cast<uint64_t>(0));
        ++res;
    } else {
        res._module.resize(size, 0);
    }

    return res;
}

big_integer big_integer::from_two_comp() const {
    big_integer res = *this;

    res._sign = !res._module.empty() && (res._module[res._module.size() - 1] != 0);

    if (res._sign) {
        ++res;
        for (uint64_t & d : res._module) {
            d = ~d;
        }
    }
    res.shrink();

    return res;
}