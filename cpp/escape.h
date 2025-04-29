// Escape Library
//   Escape the ANSI Escape Code hellhole
//   escape.hpp
//
// License: GNU-GPL v2.0
//
// Igor Nunes, 2023
// Contribute in https://github.com/ibnunes/Escape

#ifndef ESCAPE_H_SELFCONTAINED
#define ESCAPE_H_SELFCONTAINED

#include <vector>
#include <string>

using namespace std;

/**
 * Offers the tools to more easily use ANSI Escape Codes.
 */
namespace Ansi {

/**
 * Readable descriptors and their corresponding ANSI Escape Codes (Control Sequence Introducers)
 */
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
    FG_CODE_ONLY                = 38,       // To be used exclusively by `FG` templates
    FG_DEFAULT                  = 39,
    BG_BLACK                    = 40,
    BG_RED                      = 41,
    BG_GREEN                    = 42,
    BG_YELLOW                   = 43,
    BG_BLUE                     = 44,
    BG_MAGENTA                  = 45,
    BG_CYAN                     = 46,
    BG_WHITE                    = 47,
    BG_CODE_ONLY                = 48,       // To be used exclusively by `BG` templates
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

/**
 * Collection of utilities specifically designed for the purpose of building ANSI Escape Codes.
 */
namespace Utils {

/**
 * Compile-time int to string casting.
 *
 *   @param N    Unsigned int encoded by TAnsify or TColorify.
 *
 * @note Adapted from: https://stackoverflow.com/a/62596471/20566555
 */
template<unsigned long N>
class TStringify {
    constexpr static auto countdigits(unsigned long v) noexcept {
        unsigned len = 0;
        if (v == 0) len++;
        for (auto n = v; n; len++, n /= 10);
        return len;
    }

    constexpr static bool isRGB() noexcept { return quad[3] == 2; }

    constexpr static auto buflen() noexcept {
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

    /* Bytes encoded by `TColorify` and `TAnsify` are decoded and saved in `quad` */
    static constexpr unsigned long quad[5] = {
        (N & 0xFF00000000) >> 32,       // Color: channel B
        (N & 0x00FF000000) >> 24,       // Color: channel G
        (N & 0x0000FF0000) >> 16,       // Color: channel R or standard 8-bit
        (N & 0x000000FF00) >> 8,        // Color: mode (standard=5 or RGB=2)
        (N & 0x00000000FF)              // ANSI Escape Code
    };
    char buf[buflen()] = {};

public:
    /* Converts encoded unsigned long to string. */
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

    constexpr operator const char *() const { return buf; }

    /* Gets constant pointer to C-style string */
    constexpr const char* c_str() const { return buf; }

    /* Get single character at index `i`, no out-of-bounds check done. */
    constexpr const char at(int i) const { return buf[i]; }

    /* Returns the internal buffer length. Might not be the actual string length. */
    constexpr auto size() const { return buflen(); }
};

template<unsigned long N>
constexpr TStringify<N> Stringify;


/**
 * Builds either a complete Ansified string, or only the string version of a collection of codes.
 *
 *   @param L       Length of the string to be ansified (default = 0).
 *   @param N...    ANSI codes to apply.
 */
template<unsigned L = 0, unsigned long... N>
class TAnsify {
    constexpr static auto buflen() noexcept { return L + 7 + 20 * sizeof...(N); }

    const char *begin  = "\033[";       // size = 5
    const char *end    = "m";           // size = 1
    const char *reset  = "\033[0m";     // size = 7
    char buf[buflen()] = {};

public:
    /** Builds either a complete Ansified string, or only the string version of a collection of codes.
     * @param S     String to ansify with reset included. If empty, then only the AEC is built without reset.
     */
    constexpr TAnsify(const char (&S)[L + 1]) noexcept {
        auto ptr = buf;
        for (auto s = begin; *s != '\0'; s++) *ptr++ = *s;
        // Lambda inspired by: https://stackoverflow.com/a/60136761
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

    /* Gets constant pointer to C-style string */
    constexpr const char* c_str() const { return buf; }

    /* Get single character at index `i`, no out-of-bounds check done. */
    constexpr const char at(int i) const { return buf[i]; }

    /* Returns the internal buffer length. Might not be the actual string length. */
    constexpr auto size() const { return buflen(); }
};

/**
 * Builds the sequence of codes to apply color with ANSI Escape Codes.
 *
 *   @param X       ANSI Escape Code (color mode, either 38 or 48).
 *   @param N...    Colors to apply (range: [0, 255]).
 */
template<unsigned long X, unsigned long... N>
class TColorify {};

/**
 * Builds the sequence of codes to apply 8-bit color with ANSI Escape Codes.
 *
 *   @param X       ANSI Escape Code (color mode, either 38 or 48).
 *   @param C       8-bit color to apply (range: [0, 255]).
 */
template<unsigned long X, unsigned long C>
class TColorify<X, C> {
    unsigned long vCode;
public:
    constexpr TColorify() noexcept {
        vCode = X | (5 << 8) | (C << 16);
    }
    constexpr operator unsigned long () const { return vCode; }
};

/**
 * Builds the sequence of codes to apply 8-bit color with ANSI Escape Codes.
 *
 *   @param X       ANSI Escape Code (color mode, either 38 or 48).
 *   @param R       Red channel of RGB color to apply (range: [0, 255]).
 *   @param G       Green channel of RGB color to apply (range: [0, 255]).
 *   @param B       Blue channel of RGB color to apply (range: [0, 255]).
 */
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

}   // NAMESPACE Ansi::Utils


using namespace Utils;

template <unsigned L, unsigned long... N>
constexpr auto AnsifyS(const char (&msg)[L + 1])
    -> TAnsify<L, N...> { return TAnsify<L, N...>(msg); }

template <unsigned long... N>
string Ansify(string s) {
    auto begin = string(TAnsify<0, N...>("").c_str());
    auto end   = string(TAnsify<0, 0>("").c_str());
    return begin + s + end;
}


/**
 * Collection of templates to interface with Ansi::Utils in order to encode colors for ANSI Escape Codes.
 */
namespace Color {

/**
 * Encodes a foreground color.
 *
 *   @param X...    Sequence of colors to apply (range: [0, 255])
 */
template<unsigned long... X>
class _FG {};

/**
 * Encodes an 8-bit foreground color.
 *
 *   @param color   8-bit color to apply (range: [0, 255])
 */
template<unsigned long color>
class _FG<color> {
    unsigned long vCode = Colorify<Code::FG_CODE_ONLY, color>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

/**
 * Encodes an RGB foreground color.
 *
 *   @param r       Red channel of RGB color to apply (range: [0, 255]).
 *   @param g       Green channel of RGB color to apply (range: [0, 255]).
 *   @param b       Blue channel of RGB color to apply (range: [0, 255]).
 */
template<unsigned long r, unsigned long g, unsigned long b>
class _FG<r, g, b> {
    unsigned long vCode = Colorify<Code::FG_CODE_ONLY, r, g, b>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long... X>
constexpr _FG<X...> FG;


/**
 * Encodes a background color.
 * Parameters:
 *   @param X...    Sequence of colors to apply (range: [0, 255])
 */
template<unsigned long... X>
class _BG {};

/**
 * Encodes an 8-bit background color.
 * Parameters:
 *   @param color   8-bit color to apply (range: [0, 255])
 */
template<unsigned long color>
class _BG<color> {
    unsigned long vCode = Colorify<Code::BG_CODE_ONLY, color>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

/**
 * Encodes an RGB background color.
 *
 *   @param r       Red channel of RGB color to apply (range: [0, 255]).
 *   @param g       Green channel of RGB color to apply (range: [0, 255]).
 *   @param b       Blue channel of RGB color to apply (range: [0, 255]).
 */
template<unsigned long r, unsigned long g, unsigned long  b>
class _BG<r, g, b> {
    unsigned long vCode = Colorify<Code::BG_CODE_ONLY, r, g, b>;
public:
    constexpr operator unsigned long () const { return vCode; }
};

template<unsigned long... X>
constexpr _BG<X...> BG;

}   // === NAMESPACE Ansi::Color ===
}   // === NAMESPACE Ansi ===

#endif
