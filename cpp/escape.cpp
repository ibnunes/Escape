#include "escape.hpp"
#include <iostream>

using namespace std;


int main(void) {
    cout << strlit_concat( Ansi::BOLD, Ansi::FG ).c_str() << endl;
    //cout << Ansi::font<Ansi::BOLD, Ansi::ITALIC>().c_str() << end;
    // Ansi::ansify<Ansi::BG>("Teste");
    return 0;
}
