#include "escape2.hpp"
#include <iostream>

using namespace std;

int main(void) {
    cout << Stringify<0x6432090526> << endl;
    cout << Stringify<0x6432090226> << endl;
    cout << Stringify<69> << endl;
    cout << TAnsify<4, FG<9>, BG<9, 50, 100>, 69>("Test") << endl;
    cout << Ansify<FG<9>, BG<9, 50, 100>, 69>("Test") << endl;
    cout << AnsifyS<4, FG<9>, BG<9, 50, 100>, 69>("Test") << endl;
    return 0;
}
