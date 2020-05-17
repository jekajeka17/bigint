#include <iostream>
#include "big_integer.h"

int main() {
    std::string s;
    std::cin >> s;
    big_integer a(s);

    (((((std::cout << a) << ' ') << (a + 1)) << ' ') << (a * 2));
}
