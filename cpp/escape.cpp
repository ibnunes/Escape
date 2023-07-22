#include "escape.hpp"
#include <iostream>

using namespace std;

// template<Codes... codes>
// constexpr string Ansi::ansify(string s) {
//     constexpr const char* code  = Codify<codes...>().c_str();
//     constexpr const char* reset = Ansi::RESET.c_str();
//     return string(code).append(s).append(reset);
// }



template<Base_Stringify... codes>
constexpr string Ansi::ansify(const char* s) {
    constexpr const char* code  = codify<codes...>();
    constexpr const char* reset = Ansi::RESET.c_str();
    return string(code).append(s).append(reset);
}



int main(void) {
    cout << AnsiCode<420>           << "\t\t" << typeid(AnsiCode<420>).name()             << endl;
    cout << Ansi::RESET             << "\t\t" << typeid(Ansi::RESET).name()               << endl;
    cout << Ansi::FG::std<69>       << "\t\t" << typeid(Ansi::FG::std<69>).name()         << endl;
    cout << Ansi::BG::rgb<4, 2, 0>  << "\t"   << typeid(Ansi::BG::rgb<4, 2, 0>).name()    << endl;
    // cout << Ansi::ansify<>("Fatality!") << endl;
    // cout << Ansi::ansify<Ansi::BOLD, Ansi::FG_RED>("Fatality!") << endl;     // <-- ERROR!!! arghhhh
    return 0;
}
