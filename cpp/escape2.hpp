#ifndef ESCAPE2_H
#define ESCAPE2_H

#include <vector>
//#include <string.h>
#include <string>

using namespace std;


// Reverse wrapper, thanks to:
// https://stackoverflow.com/a/28139075/20566555
namespace VecUtils {
    template<typename T>
    struct reversion_wrapper { T& iterable; };

    template<typename T>
    constexpr auto begin(reversion_wrapper<T> w) { return std::rbegin(w.iterable); }

    template<typename T>
    constexpr auto end(reversion_wrapper<T> w) { return std::rend(w.iterable); }

    template<typename T>
    constexpr reversion_wrapper<T> reverse(T&& iterable) { return { iterable }; }
}


// Compile-time int to string, adapted from:
// https://stackoverflow.com/a/62596471/20566555

template<unsigned long N>
class TStringify {

    constexpr static auto countdigits(unsigned long v) noexcept {
        unsigned len = 0;
        if (v == 0) len++;
        for (auto n = v; n; len++, n /= 10);
        return len;
    }

    static constexpr unsigned long quad[5] = {
        (N & 0xFF00000000) >> 32,       // Color: channel B
        (N & 0x00FF000000) >> 24,       // Color: channel G
        (N & 0x0000FF0000) >> 16,       // Color: channel R or standard 8-bit
        (N & 0x000000FF00) >> 8,        // Color: mode (standard=5 or RGB=2)
        (N & 0x00000000FF)              // ANSI Escape Code
    };

    constexpr static bool isRGB() noexcept { return quad[3] == 2; }

    constexpr static auto buflen() noexcept {
        unsigned int len = 0;
        auto f = [&len](const unsigned long v) {
            len += countdigits(quad[4]) + 1;
            if (quad[4] == 38 || quad[4] == 48) {
                for (auto i = 3; i >= (isRGB() ? 0 : 2); i--)
                    len += countdigits(quad[i]) + 1;
                len += 0;
            }
        };
        f(N);
        return len;
    }

    char buf[buflen()] = {};

public:

    constexpr TStringify() noexcept {
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
            if (quad[4] == 38 || quad[4] == 48) {
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

    constexpr operator const char *() const { return buf; }
    constexpr const char* c_str() const { return buf; }
    constexpr const char at(int i) const { return buf[i]; }
    constexpr auto size() const { return buflen(); }
};

template <unsigned long N>
constexpr TStringify<N> Stringify;


// Lambda inspired by:
// https://stackoverflow.com/a/60136761

template<unsigned L = 0, unsigned long... N>
class TAnsify {

    const char *begin = "\\033[";           // size = 5
    const char *end   = "m";                // size = 1
    const char *reset = "\\033[0m";         // size = 7

    constexpr static auto buflen() noexcept {
        return L + 20 * sizeof...(N) + 7;
    }

    char buf[buflen()] = {};

public:
    constexpr TAnsify(const char (&S)[L + 1]) noexcept {
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

    constexpr operator const char *() const { return buf; }
    constexpr const char* c_str() const { return buf; }
    constexpr const char at(int i) const { return buf[i]; }
    constexpr auto size() const { return buflen(); }
};


template <unsigned L, unsigned long... N>
constexpr auto AnsifyS(const char (&msg)[L + 1])
    -> TAnsify<L, N...>
{
    return TAnsify<L, N...>(msg);
}

template <unsigned long... N>
auto Ansify(string s) {
    auto begin = string(TAnsify<0, N...>("").c_str());
    auto end   = string(TAnsify<0, 0>("").c_str());
    return begin + s + end;
}


template<unsigned long X, unsigned long... N>
class TColorify {};

template<unsigned long X, unsigned long C>
class TColorify<X, C> {
    unsigned long vCode;
public:
    constexpr TColorify() noexcept {
        vCode = X | (5 << 8) | (C << 16);
    }
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long X, unsigned long R, unsigned long G, unsigned long B>
class TColorify<X, R, G, B> {
    unsigned long vCode;
public:
    constexpr TColorify() noexcept {
        vCode = X | (2 << 8) | (R << 16) | (G << 24) | (B << 32);
    }
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long X, unsigned long... N>
constexpr TColorify<X, N...> Colorify;



template<unsigned long ... X>
class _FG {};

template<unsigned long  color>
class _FG<color> {
    unsigned long vCode = Colorify<38, color>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long  r, unsigned long  g, unsigned long  b>
class _FG<r, g, b> {
    unsigned long vCode = Colorify<38, r, g, b>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long ... X>
constexpr _FG<X...> FG;


template<unsigned long ... X>
class _BG {};

template<unsigned long  color>
class _BG<color> {
    unsigned long vCode = Colorify<48, color>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long r, unsigned long g, unsigned long  b>
class _BG<r, g, b> {
    unsigned long vCode = Colorify<48, r, g, b>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long ... X>
constexpr _BG<X...> BG;




#endif