#include "escape.hpp"
using namespace std;

namespace Ansi {
namespace Utils {

template<unsigned long N>
constexpr auto TStringify<N>::countdigits(unsigned long v) noexcept {
    unsigned len = 0;
    if (v == 0) len++;
    for (auto n = v; n; len++, n /= 10);
    return len;
}

template<unsigned long N>
constexpr auto TStringify<N>::buflen() noexcept {
    unsigned int len = 0;
    auto f = [&len](const unsigned long v) {
        len += countdigits(quad[4]) + 1;
        if (quad[4] == Code::FG_CODE_ONLY || quad[4] == Code::BG_CODE_ONLY) {
            for (auto i = 3; i >= (isRGB() ? 0 : 2); i--)
                len += countdigits(quad[i]) + 1;
            len += 0;
        }
    };
    f(N);
    return len;
}

template<unsigned long N>
constexpr TStringify<N>::TStringify() noexcept {
    auto ptr = buf + buflen();
    auto f = [this, &ptr](void) {
        auto g = [&ptr](unsigned long v) {
            if (v != 0) {
                for (auto n = v; n; n /= 10)
                    *--ptr = "0123456789"[(v < 0 ? -1 : 1) * (n % 10)];
            } else {
                *--ptr = '0';
            }
        };
        if (quad[4] == Code::FG_CODE_ONLY || quad[4] == Code::BG_CODE_ONLY) {
            for (auto i = (isRGB() ? 0 : 2); i < 4; i++) {
                *--ptr = ';';
                g(quad[i]);
            }
        }
        *--ptr = ';';
        g(quad[4]);
    };
    f();
    *(buf + buflen() - 1) = '\0';
}

template<unsigned L, unsigned long... N>
constexpr TAnsify<L, N...>::TAnsify(const char (&S)[L + 1]) noexcept {
    auto ptr = buf;
    for (auto s = begin; *s != '\0'; s++) *ptr++ = *s;
    ([&] {
        const char *s = Stringify<N>.c_str();
        for (; *s != '\0'; s++) *ptr++ = *s;
        *ptr++ = ';';
    } (), ...);
    *--ptr = *end;
    if (L > 0) {
        ptr++;
        for (auto s = S; *s != '\0'; s++) *ptr++ = *s;
        for (auto s = reset; *s != '\0'; s++) *ptr++ = *s;
    }
    *++ptr = '\0';
}

template<unsigned long X, unsigned long C>
constexpr TColorify<X, C>::TColorify() noexcept {
    vCode = X | (5 << 8) | (C << 16);
}

template<unsigned long X, unsigned long R, unsigned long G, unsigned long B>
constexpr TColorify<X, R, G, B>::TColorify() noexcept {
    vCode = X | (2 << 8) | (R << 16) | (G << 24) | (B << 32);
}

}   // === NAMESPACE Ansi::Utils

template <unsigned L, unsigned long... N>
constexpr auto AnsifyS(const char (&msg)[L + 1])
    -> TAnsify<L, N...> { return TAnsify<L, N...>(msg); }

template <unsigned long... N>
string Ansify(string s) {
    auto begin = string(TAnsify<0, N...>("").c_str());
    auto end   = string(TAnsify<0, 0>("").c_str());
    return begin + s + end;
}

}   // === NAMESPACE Ansi ===


/* === TESTING === */
// #include <iostream>
// using namespace Ansi;
// int main(void) {
//     cout << AnsifyS<9, Code::BOLD, Code::FG_RED>("Fatality!") << " An error has not occurred :(" << endl;
//     cout << "And here is a " << Ansify<Code::ITALIC, Color::FG<69>>("Color Test, Standard") << "." << endl;
//     cout << AnsifyS<15, Code::UNDERLINE, Color::BG<100, 50, 9>, Code::ITALIC>("Color Test, RGB") <<
//         ", and also " << Ansify<Code::ITALIC, Code::UNDERLINE, Color::FG<9, 100, 5>>("Color Test, RGB") << endl;
//     return 0;
// }
