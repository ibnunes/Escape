#include "escape.hpp"
#include <iostream>

using namespace std;


int main(void) {
    cout << Ansi::ansify<Ansi::BOLD, Ansi::FG_RED>("Fatality!") << endl;
    return 0;
}
