#include "big_integer.h"

big_integer big_integer::operator~() const {
    big_integer res = *this;
    return -res - 1;
}