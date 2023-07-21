#include "escape.hpp"
#include <iostream>

using namespace std;

template<Stringify... codes>
constexpr string Ansi::ansify(string s) {
    constexpr const char* code  = Codify<codes...>().c_str();
    constexpr const char* reset = Ansi::RESET.c_str();
    return string(code).append(s).append(reset);
}


int main(void) {
    cout << AnsiCode<420>() << endl;
    cout << FG::std<69> << endl;
    cout << FG::rgb<4, 2, 0> << endl;
    // cout << Ansi::ansify<Ansi::BOLD, Ansi::FG_RED>("Fatality!") << endl;     // <-- ERROR!!! arghhhh
    return 0;
}
