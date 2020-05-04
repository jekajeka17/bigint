#include <iostream>
#include "big_integer.h"

int main() {
    std::string s, t;

    std::cin >> s >> t;

    big_integer a(s);
    big_integer b(t);

    big_integer c = a + b;

    std::cout << to_string(c);
}