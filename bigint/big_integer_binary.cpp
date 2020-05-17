#include "big_integer.h"

big_integer big_integer::operator~() const {
    big_integer res = *this;
    return -res - 1;
}

big_integer& big_integer::operator&=(big_integer const& rhs) {
    size_t op_size = std::max(_module.size(), rhs._module.size());
    _module.reserve(op_size);
    for (size_t i = 0; i < op_size; ++i) {
        uint64_t d = digit(i) & rhs.digit(i);
        if (i < _module.size()) {
            _module[i] = d;
        } else {
            _module.push_back(d);
        }
    }
    shrink();
    return *this;
}

big_integer& big_integer::operator|=(big_integer const& rhs) {
    size_t op_size = std::max(_module.size(), rhs._module.size());
    _module.reserve(op_size);
    for (size_t i = 0; i < op_size; ++i) {
        uint64_t d = digit(i) | rhs.digit(i);
        if (i < _module.size()) {
            _module[i] = d;
        } else {
            _module.push_back(d);
        }
    }
    shrink();
    return *this;
}

big_integer& big_integer::operator^=(big_integer const& rhs) {
    size_t op_size = std::max(_module.size(), rhs._module.size());
    _module.reserve(op_size);
    for (size_t i = 0; i < op_size; ++i) {
        uint64_t d = digit(i) ^ rhs.digit(i);
        if (i < _module.size()) {
            _module[i] = d;
        } else {
            _module.push_back(d);
        }
    }
    shrink();
    return *this;
}

big_integer operator&(big_integer a, big_integer const& b) {
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const& b) {
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const& b) {
    return a ^= b;
}

big_integer& big_integer::operator<<=(int rhs) {
    auto shift = static_cast<size_t>(rhs);
    if (shift >= 64) {
        size_t cnt = shift / 64;
        _module.resize(_module.size() + cnt);
        for (size_t i = _module.size() - 1; i >= cnt; --i) {
            _module[i] = _module[i - cnt];
        }
        for (size_t i = 0; i < cnt; ++i) {
            _module[i] = 0;
        }
    }
    shift %= 64;
    uint64_t carry = 0;
    uint64_t mask = ~((1ULL << (64ULL - shift)) - 1ULL);
    for (uint64_t & i : _module) {
        uint64_t new_carry = (i & mask) >> (64ULL - shift);
        i <<= shift;
        i += carry;
        carry = new_carry;
    }
    if (carry != 0) {
        _module.push_back(carry);
    }
    shrink();
    return *this;
}

big_integer& big_integer::operator>>=(int rhs) {
    auto shift = static_cast<size_t>(rhs);
    if (shift >= 64) {
        size_t cnt = shift / 64;
        for (size_t i = 0; i < _module.size() - cnt; ++i) {
            _module[i] = _module[i + cnt];
        }
        for (size_t i = _module.size() - 1; i >= _module.size() - cnt; --i) {
            _module[i] = 0;
        }
    }
    shift %= 64;
    uint64_t carry = 0;
    uint64_t mask = (1ULL << (shift)) - 1ULL;
    for (size_t i = _module.size(); i-- > 0;) {
        uint64_t new_carry = _module[i] & mask;
        _module[i] >>= shift;
        carry <<= (64ULL - shift);
        _module[i] += carry;
        carry = new_carry;
    }
    shrink();
    return *this;
}

big_integer operator<<(big_integer a, int b) {
    return a <<= b;
}

big_integer operator>>(big_integer a, int b) {
    return a >>= b;
}