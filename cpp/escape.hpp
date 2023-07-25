#ifndef ESCAPE_H
#define ESCAPE_H

#include <vector>
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

namespace Ansi {
enum Code {
    RESET                       = 0,
    BOLD                        = 1,
    FAINT                       = 2,
    ITALIC                      = 3,
    UNDERLINE                   = 4,
    BLINK_SLOW                  = 5,
    BLINK_RAPID                 = 6,
    REVERSE                     = 7,
    CONCEAL                     = 8,
    CROSSOUT                    = 9,
    FONT_PRIMARY                = 10,
    FONT_ALTERNATE_1            = 11,
    FONT_ALTERNATE_2            = 12,
    FONT_ALTERNATE_3            = 13,
    FONT_ALTERNATE_4            = 14,
    FONT_ALTERNATE_5            = 15,
    FONT_ALTERNATE_6            = 16,
    FONT_ALTERNATE_7            = 17,
    FONT_ALTERNATE_8            = 18,
    FONT_ALTERNATE_9            = 19,
    FRAKTUR                     = 20,
    BOLD_OFF                    = 21,
    UNDERLINE_DOUBLE            = 21,
    COLOR_NORMAL                = 22,
    ITALIC_OFF                  = 23,
    FRAKTUR_OFF                 = 23,
    UNDERLINE_OFF               = 24,
    BLINK_OFF                   = 25,
    INVERSE_OFF                 = 27,
    REVEAL                      = 28,
    CROSSOUT_OFF                = 29,
    FG_BLACK                    = 30,
    FG_RED                      = 31,
    FG_GREEN                    = 32,
    FG_YELLOW                   = 33,
    FG_BLUE                     = 34,
    FG_MAGENTA                  = 35,
    FG_CYAN                     = 36,
    FG_WHITE                    = 37,
    FG_CODE_ONLY                = 38,
    FG_DEFAULT                  = 39,
    BG_BLACK                    = 40,
    BG_RED                      = 41,
    BG_GREEN                    = 42,
    BG_YELLOW                   = 43,
    BG_BLUE                     = 44,
    BG_MAGENTA                  = 45,
    BG_CYAN                     = 46,
    BG_WHITE                    = 47,
    BG_CODE_ONLY                = 48,
    BG_DEFAULT                  = 49,
    FRAME                       = 51,
    ENCIRCLE                    = 52,
    OVERLINE                    = 53,
    FRAME_OFF                   = 54,
    ENCIRCLE_OFF                = 54,
    OVERLINE_OFF                = 55,
    IDEOGRAM_UNDERLINE          = 60,
    IDEOGRAM_UNDERLINE_DOUBLE   = 61,
    IDEOGRAM_OVERLINE           = 62,
    IDEOGRAM_OVERLINE_DOUBLE    = 63,
    IDEOGRAM_STRESSMARK         = 64,
    IDEOGRAM_OFF                = 65,
    FG_BRIGHT_BLACK             = 90,
    FG_BRIGHT_RED               = 91,
    FG_BRIGHT_GREEN             = 92,
    FG_BRIGHT_YELLOW            = 93,
    FG_BRIGHT_BLUE              = 94,
    FG_BRIGHT_MAGENTA           = 95,
    FG_BRIGHT_CYAN              = 96,
    FG_BRIGHT_WHITE             = 97,
    G_BRIGHT_BLACK              = 100,
    G_BRIGHT_RED                = 101,
    G_BRIGHT_GREEN              = 102,
    G_BRIGHT_YELLOW             = 103,
    G_BRIGHT_BLUE               = 104,
    G_BRIGHT_MAGENTA            = 105,
    G_BRIGHT_CYAN               = 106,
    G_BRIGHT_WHITE              = 107
};

namespace Utils {

template<unsigned long N>
class TStringify {
    constexpr static auto countdigits(unsigned long v) noexcept;
    constexpr static bool isRGB() noexcept { return quad[3] == 2; }
    constexpr static auto buflen() noexcept;

    static constexpr unsigned long quad[5] = {
        (N & 0xFF00000000) >> 32,       // Color: channel B
        (N & 0x00FF000000) >> 24,       // Color: channel G
        (N & 0x0000FF0000) >> 16,       // Color: channel R or standard 8-bit
        (N & 0x000000FF00) >> 8,        // Color: mode (standard=5 or RGB=2)
        (N & 0x00000000FF)              // ANSI Escape Code
    };
    char buf[buflen()] = {};

public:
    constexpr TStringify() noexcept;
    constexpr operator const char *() const { return buf; }
    constexpr const char* c_str() const { return buf; }
    constexpr const char at(int i) const { return buf[i]; }
    constexpr auto size() const { return buflen(); }
};

template<unsigned long N>
constexpr TStringify<N> Stringify;


// Lambda inspired by:
// https://stackoverflow.com/a/60136761

template<unsigned L = 0, unsigned long... N>
class TAnsify {
    constexpr static auto buflen() noexcept { return L + 7 + 20 * sizeof...(N); }

    const char *begin = "\033[";           // size = 5
    const char *end   = "m";                // size = 1
    const char *reset = "\033[0m";         // size = 7
    char buf[buflen()] = {};

public:
    constexpr TAnsify(const char (&S)[L + 1]) noexcept;
    constexpr operator const char *() const { return buf; }
    constexpr const char* c_str() const { return buf; }
    constexpr const char at(int i) const { return buf[i]; }
    constexpr auto size() const { return buflen(); }
};

template<unsigned long X, unsigned long... N>
class TColorify {};

template<unsigned long X, unsigned long C>
class TColorify<X, C> {
    unsigned long vCode;
public:
    constexpr TColorify() noexcept;
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long X, unsigned long R, unsigned long G, unsigned long B>
class TColorify<X, R, G, B> {
    unsigned long vCode;
public:
    constexpr TColorify() noexcept;
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long X, unsigned long... N>
constexpr TColorify<X, N...> Colorify;

}   // NAMESPACE Ansi::Utils

using namespace Utils;

template <unsigned L, unsigned long... N>
constexpr auto AnsifyS(const char (&msg)[L + 1])
    -> TAnsify<L, N...>;

template <unsigned long... N>
string Ansify(string s);

namespace Color {

template<unsigned long ... X>
class _FG {};

template<unsigned long  color>
class _FG<color> {
    unsigned long vCode = Colorify<Code::FG_CODE_ONLY, color>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long  r, unsigned long  g, unsigned long  b>
class _FG<r, g, b> {
    unsigned long vCode = Colorify<Code::FG_CODE_ONLY, r, g, b>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long ... X>
constexpr _FG<X...> FG;

template<unsigned long ... X>
class _BG {};

template<unsigned long  color>
class _BG<color> {
    unsigned long vCode = Colorify<Code::BG_CODE_ONLY, color>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long r, unsigned long g, unsigned long  b>
class _BG<r, g, b> {
    unsigned long vCode = Colorify<Code::BG_CODE_ONLY, r, g, b>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long ... X>
constexpr _BG<X...> BG;

}   // === NAMESPACE Ansi::Color ===
}   // === NAMESPACE Ansi ===

#endif
