#include "escape.hpp"
#include <iostream>

using namespace std;

string Ansi::ansi_codify(int code) {
    string ansi_code(Ansi::ESCAPECODE_BEGIN);
    ansi_code.append(to_string(code));
    return ansi_code.append(Ansi::ESCAPECODE_END);
}

string Ansi::ansi_codify(vector<int> codes) {
    string ansi_code(Ansi::ESCAPECODE_BEGIN);
    for (auto code : codes) {
        ansi_code.append(to_string(code));
        ansi_code.append(Ansi::SEPARATOR);
    }
    ansi_code.pop_back();
    return ansi_code.append(Ansi::ESCAPECODE_END);
}

template<int... codes>
string Ansi::ansify(string msg) {
    string ansified_msg(Ansi::ansi_codify(vector<int> {codes...}));
    ansified_msg.append(msg);
    return ansified_msg.append(Ansi::ansi_codify(Ansi::RESET));
}

int main(void) {
    cout << Ansi::ansify<Ansi::BOLD, Ansi::FG_RED>("Fatality!") << endl;
    // cout << to_string_t<420, 6, true>("fooooo") + to_string_t<420, 3, true>("bar") << endl;
    // cout << to_string_t<420, 4, true>("hey!") << endl;
    // cout << FG<69>() << endl;
    // cout << AnsiCode<420> << endl;
    return 0;
}
