#ifndef ESCAPE_H
#define ESCAPE_H

#include <cassert>
#include <cstdint>
#include <vector>
#include <string>
#include <string_view>

using namespace std;


// Reverse wrapper, thanks to:
// https://stackoverflow.com/a/28139075/20566555
namespace AnsiUtils {
    template <typename T>
    struct reversion_wrapper { T& iterable; };

    template <typename T>
    constexpr auto begin (reversion_wrapper<T> w) { return std::rbegin(w.iterable); }

    template <typename T>
    constexpr auto end (reversion_wrapper<T> w) { return std::rend(w.iterable); }

    template <typename T>
    constexpr reversion_wrapper<T> reverse (T&& iterable) { return { iterable }; }
}

// Compile-time int to string, adapted from:
// https://stackoverflow.com/a/62596471/20566555

template<unsigned... N>
class Stringify {
    constexpr static auto buflen() noexcept {
        unsigned int len = 0;
        unsigned int add = 0;
        auto f = [&len, &add](const vector<unsigned> vec) {
            for (auto v : vec) {
                if (v == 0) add++;
                len++;
                for (auto n = v; n; len++, n /= 10);
            }
        };
        f(vector<unsigned>{N...});
        return len + add;
    }
    char buf[buflen()] = {};
public:
    constexpr Stringify() noexcept {
        auto ptr = buf + buflen();
        auto f = [&ptr](const vector<unsigned> vec) {
            for (auto v : AnsiUtils::reverse(vec)) {
                *--ptr = ';';
                if (v != 0) {
                    for (auto n = v; n; n /= 10)
                        *--ptr = "0123456789"[(v < 0 ? -1 : 1) * (n % 10)];
                } else {
                    *--ptr = '0';
                }
            }
        };
        f(vector<unsigned>{N...});
        *(buf + buflen() - 1) = '\0';
    }
    constexpr operator const char *() const { return buf; }
    constexpr const char* c_str() const { return buf; }
    constexpr const char at(int i) const { return buf[i]; }
    constexpr auto size() const { return buflen(); }
};

template<unsigned code>
using AnsiCode = Stringify<code>;

template<unsigned code, unsigned color>
using AnsiColorStd = Stringify<code, 5, color>;

template<unsigned code, unsigned r, unsigned g, unsigned b>
using AnsiColorRGB = Stringify<code, 2, r, g, b>;




template<typename T>
concept Codes = std::is_same_v<T, Stringify<>>;


template<Codes... S>
class Codify {
    static constexpr int offset = 6;
    static constexpr int size = Stringify<S...>().size();
    const char code[size] = Stringify<S...>().c_str();
    char buf[size + offset] = {};
public:
    constexpr Codify() noexcept {
        auto ptr = buf + size + offset;
        *--ptr = '\0';
        for (auto n = size; n; n--)
            *--ptr = code[size-1];
    }
    constexpr operator const char *() const { return buf; }
    constexpr const char* c_str() const { return buf; }
};


class Ansi {
public:
    template<Codes... Cs> static constexpr string ansify(string);

    static constexpr AnsiCode<0>     RESET                      ;
    static constexpr AnsiCode<1>     BOLD                       ;
    static constexpr AnsiCode<2>     FAINT                      ;
    static constexpr AnsiCode<3>     ITALIC                     ;
    static constexpr AnsiCode<4>     UNDERLINE                  ;
    static constexpr AnsiCode<5>     BLINK_SLOW                 ;
    static constexpr AnsiCode<6>     BLINK_RAPID                ;
    static constexpr AnsiCode<7>     REVERSE                    ;
    static constexpr AnsiCode<8>     CONCEAL                    ;
    static constexpr AnsiCode<9>     CROSSOUT                   ;
    static constexpr AnsiCode<10>    FONT_PRIMARY               ;
    static constexpr AnsiCode<11>    FONT_ALTERNATE_1           ;
    static constexpr AnsiCode<12>    FONT_ALTERNATE_2           ;
    static constexpr AnsiCode<13>    FONT_ALTERNATE_3           ;
    static constexpr AnsiCode<14>    FONT_ALTERNATE_4           ;
    static constexpr AnsiCode<15>    FONT_ALTERNATE_5           ;
    static constexpr AnsiCode<16>    FONT_ALTERNATE_6           ;
    static constexpr AnsiCode<17>    FONT_ALTERNATE_7           ;
    static constexpr AnsiCode<18>    FONT_ALTERNATE_8           ;
    static constexpr AnsiCode<19>    FONT_ALTERNATE_9           ;
    static constexpr AnsiCode<20>    FRAKTUR                    ;
    static constexpr AnsiCode<21>    BOLD_OFF                   ;
    static constexpr AnsiCode<21>    UNDERLINE_DOUBLE           ;
    static constexpr AnsiCode<22>    COLOR_NORMAL               ;
    static constexpr AnsiCode<23>    ITALIC_OFF                 ;
    static constexpr AnsiCode<23>    FRAKTUR_OFF                ;
    static constexpr AnsiCode<24>    UNDERLINE_OFF              ;
    static constexpr AnsiCode<25>    BLINK_OFF                  ;
    static constexpr AnsiCode<27>    INVERSE_OFF                ;
    static constexpr AnsiCode<28>    REVEAL                     ;
    static constexpr AnsiCode<29>    CROSSOUT_OFF               ;
    static constexpr AnsiCode<30>    FG_BLACK                   ;
    static constexpr AnsiCode<31>    FG_RED                     ;
    static constexpr AnsiCode<32>    FG_GREEN                   ;
    static constexpr AnsiCode<33>    FG_YELLOW                  ;
    static constexpr AnsiCode<34>    FG_BLUE                    ;
    static constexpr AnsiCode<35>    FG_MAGENTA                 ;
    static constexpr AnsiCode<36>    FG_CYAN                    ;
    static constexpr AnsiCode<37>    FG_WHITE                   ;
    static constexpr AnsiCode<39>    FG_DEFAULT                 ;
    static constexpr AnsiCode<40>    BG_BLACK                   ;
    static constexpr AnsiCode<41>    BG_RED                     ;
    static constexpr AnsiCode<42>    BG_GREEN                   ;
    static constexpr AnsiCode<43>    BG_YELLOW                  ;
    static constexpr AnsiCode<44>    BG_BLUE                    ;
    static constexpr AnsiCode<45>    BG_MAGENTA                 ;
    static constexpr AnsiCode<46>    BG_CYAN                    ;
    static constexpr AnsiCode<47>    BG_WHITE                   ;
    static constexpr AnsiCode<49>    BG_DEFAULT                 ;
    static constexpr AnsiCode<51>    FRAME                      ;
    static constexpr AnsiCode<52>    ENCIRCLE                   ;
    static constexpr AnsiCode<53>    OVERLINE                   ;
    static constexpr AnsiCode<54>    FRAME_OFF                  ;
    static constexpr AnsiCode<54>    ENCIRCLE_OFF               ;
    static constexpr AnsiCode<55>    OVERLINE_OFF               ;
    static constexpr AnsiCode<60>    IDEOGRAM_UNDERLINE         ;
    static constexpr AnsiCode<61>    IDEOGRAM_UNDERLINE_DOUBLE  ;
    static constexpr AnsiCode<62>    IDEOGRAM_OVERLINE          ;
    static constexpr AnsiCode<63>    IDEOGRAM_OVERLINE_DOUBLE   ;
    static constexpr AnsiCode<64>    IDEOGRAM_STRESSMARK        ;
    static constexpr AnsiCode<65>    IDEOGRAM_OFF               ;
    static constexpr AnsiCode<90>    FG_BRIGHT_BLACK            ;
    static constexpr AnsiCode<91>    FG_BRIGHT_RED              ;
    static constexpr AnsiCode<92>    FG_BRIGHT_GREEN            ;
    static constexpr AnsiCode<93>    FG_BRIGHT_YELLOW           ;
    static constexpr AnsiCode<94>    FG_BRIGHT_BLUE             ;
    static constexpr AnsiCode<95>    FG_BRIGHT_MAGENTA          ;
    static constexpr AnsiCode<96>    FG_BRIGHT_CYAN             ;
    static constexpr AnsiCode<97>    FG_BRIGHT_WHITE            ;
    static constexpr AnsiCode<100>   BG_BRIGHT_BLACK            ;
    static constexpr AnsiCode<101>   BG_BRIGHT_RED              ;
    static constexpr AnsiCode<102>   BG_BRIGHT_GREEN            ;
    static constexpr AnsiCode<103>   BG_BRIGHT_YELLOW           ;
    static constexpr AnsiCode<104>   BG_BRIGHT_BLUE             ;
    static constexpr AnsiCode<105>   BG_BRIGHT_MAGENTA          ;
    static constexpr AnsiCode<106>   BG_BRIGHT_CYAN             ;
    static constexpr AnsiCode<107>   BG_BRIGHT_WHITE            ;

    struct FG {
        template<unsigned color> static constexpr AnsiColorStd<38, color> std;
        template<unsigned r, unsigned g, unsigned b> static constexpr AnsiColorRGB<38, r, g, b> rgb;
    };

    struct BG {
        template<unsigned color> static constexpr AnsiColorStd<48, color> std;
        template<unsigned r, unsigned g, unsigned b> static constexpr AnsiColorRGB<48, r, g, b> rgb;
    };
};


#endif