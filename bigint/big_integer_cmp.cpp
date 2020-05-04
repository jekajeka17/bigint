#include "big_integer.h"

bool operator==(big_integer const& a, big_integer const& b) {
    return a.compare(b) == 0;
}

bool operator!=(big_integer const& a, big_integer const& b) {
    return !(a == b);
}

bool operator<(big_integer const& a, big_integer const& b) {
    return a.compare(b) == -1;
}

bool operator<=(big_integer const& a, big_integer const& b) {
    return !(b < a);
}

bool operator>(big_integer const& a, big_integer const& b) {
    return b < a;
}

bool operator>=(big_integer const& a, big_integer const& b) {
    return !(a < b);
}
