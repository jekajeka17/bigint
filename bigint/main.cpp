#include <iostream>
#include "big_integer.h"

int main() {
    std::string s;
    std::cin >> s;
    big_integer a(s);
//    a = ~(-a) + 1;
//    -a = ~(a) + 1;
//    -a - 1 = ~(a);


    std::cout << to_string(~a);
}

// a > 0, b > 0, |a| < |b| => a < b
// a < 0, b < 0, |a| < |b| => a > b

// x = ......00000000000000000101
// -x = .....11111111111111111011

// 00110101 | 11011110 | 00001011
// 01001111 | 00101011 | 10101010
// 00000101 | 00001010 | 00001010