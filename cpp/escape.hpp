#ifndef ESCAPE_H
#define ESCAPE_H

#include <cassert>
#include <vector>
#include <string>
#include <string_view>

using namespace std;

#if defined __GNUC__
# define LIKELY(EXPR)  __builtin_expect(!!(EXPR), 1)
#else
# define LIKELY(EXPR)  (!!(EXPR))
#endif

#if defined NDEBUG
# define X_ASSERT(CHECK) void(0)
#else
# define X_ASSERT(CHECK) \
    ( LIKELY(CHECK) ?  void(0) : []{assert(!#CHECK);}() )
#endif


template<int N>
class string_literal {
    const char (&_lit)[N + 1];
public:
    constexpr string_literal(const char (&lit)[N + 1]) : _lit(lit) {}
    constexpr char operator[](int i) const {
        return X_ASSERT(i >= 0 && i < N), _lit[i];
    }
    constexpr char* const c_str() { return (char*) _lit; }
};


template <int N_PLUS_1>
constexpr auto literal(const char (&lit)[N_PLUS_1])
    -> string_literal<N_PLUS_1 - 1>
{
    return string_literal<N_PLUS_1 - 1>(lit);
}


template <int N>
class array_string {
    char _array[N + 1];

public:
    template <int N1> requires (N1 <= N)
    constexpr array_string(const string_literal<N1>&     s1,
                           const string_literal<N - N1>& s2)
    {
        for (int i = 0; i < N1; ++i)
            _array[i] = s1[i];
        for (int i = 0; i < N - N1; ++i)
            _array[N1 + i] = s2[i];
        _array[N] = '\0';
    }

    constexpr char operator[](int i) const {
        return X_ASSERT(i >= 0 && i < N), _array[i];
    }

    constexpr std::size_t size() const { return N; }

    constexpr string_literal<N> as_literal() { return string_literal<N>(_array); }
    constexpr char* const c_str() { return (char*) _array; }
};

template <int N1, int N2>
constexpr auto operator+(const string_literal<N1>& s1,
                         const string_literal<N2>& s2)
    -> array_string<N1 + N2>
{
    return array_string<N1 + N2>(s1, s2);
}

template <int... N>
constexpr auto strlit_concat(string_literal<N> const&... args) {
    return (... + args);
}





class Ansi {
public:
    static constexpr string_literal<1> RESET                     = "0";
    static constexpr string_literal<1> BOLD                      = "1";
    static constexpr string_literal<1> FAINT                     = "2";
    static constexpr string_literal<1> ITALIC                    = "3";
    static constexpr string_literal<1> UNDERLINE                 = "4";
    static constexpr string_literal<1> BLINK_SLOW                = "5";
    static constexpr string_literal<1> BLINK_RAPID               = "6";
    static constexpr string_literal<1> REVERSE                   = "7";
    static constexpr string_literal<1> CONCEAL                   = "8";
    static constexpr string_literal<1> CROSSOUT                  = "9";
    static constexpr string_literal<2> FONT_PRIMARY              = "10";
    static constexpr string_literal<2> FONT_ALTERNATE_1          = "11";
    static constexpr string_literal<2> FONT_ALTERNATE_2          = "12";
    static constexpr string_literal<2> FONT_ALTERNATE_3          = "13";
    static constexpr string_literal<2> FONT_ALTERNATE_4          = "14";
    static constexpr string_literal<2> FONT_ALTERNATE_5          = "15";
    static constexpr string_literal<2> FONT_ALTERNATE_6          = "16";
    static constexpr string_literal<2> FONT_ALTERNATE_7          = "17";
    static constexpr string_literal<2> FONT_ALTERNATE_8          = "18";
    static constexpr string_literal<2> FONT_ALTERNATE_9          = "19";
    static constexpr string_literal<2> FRAKTUR                   = "20";
    static constexpr string_literal<2> BOLD_OFF                  = "21";
    static constexpr string_literal<2> UNDERLINE_DOUBLE          = "21";
    static constexpr string_literal<2> COLOR_NORMAL              = "22";
    static constexpr string_literal<2> ITALIC_OFF                = "23";
    static constexpr string_literal<2> FRAKTUR_OFF               = "23";
    static constexpr string_literal<2> UNDERLINE_OFF             = "24";
    static constexpr string_literal<2> BLINK_OFF                 = "25";
    static constexpr string_literal<2> INVERSE_OFF               = "27";
    static constexpr string_literal<2> REVEAL                    = "28";
    static constexpr string_literal<2> CROSSOUT_OFF              = "29";
    static constexpr string_literal<2> FG_BLACK                  = "30";
    static constexpr string_literal<2> FG_RED                    = "31";
    static constexpr string_literal<2> FG_GREEN                  = "32";
    static constexpr string_literal<2> FG_YELLOW                 = "33";
    static constexpr string_literal<2> FG_BLUE                   = "34";
    static constexpr string_literal<2> FG_MAGENTA                = "35";
    static constexpr string_literal<2> FG_CYAN                   = "36";
    static constexpr string_literal<2> FG_WHITE                  = "37";
    static constexpr string_literal<2> FG                        = "38";
    static constexpr string_literal<2> FG_DEFAULT                = "39";
    static constexpr string_literal<2> BG_BLACK                  = "40";
    static constexpr string_literal<2> BG_RED                    = "41";
    static constexpr string_literal<2> BG_GREEN                  = "42";
    static constexpr string_literal<2> BG_YELLOW                 = "43";
    static constexpr string_literal<2> BG_BLUE                   = "44";
    static constexpr string_literal<2> BG_MAGENTA                = "45";
    static constexpr string_literal<2> BG_CYAN                   = "46";
    static constexpr string_literal<2> BG_WHITE                  = "47";
    static constexpr string_literal<2> BG                        = "48";
    static constexpr string_literal<2> BG_DEFAULT                = "49";
    static constexpr string_literal<2> FRAME                     = "51";
    static constexpr string_literal<2> ENCIRCLE                  = "52";
    static constexpr string_literal<2> OVERLINE                  = "53";
    static constexpr string_literal<2> FRAME_OFF                 = "54";
    static constexpr string_literal<2> ENCIRCLE_OFF              = "54";
    static constexpr string_literal<2> OVERLINE_OFF              = "55";
    static constexpr string_literal<2> IDEOGRAM_UNDERLINE        = "60";
    static constexpr string_literal<2> IDEOGRAM_UNDERLINE_DOUBLE = "61";
    static constexpr string_literal<2> IDEOGRAM_OVERLINE         = "62";
    static constexpr string_literal<2> IDEOGRAM_OVERLINE_DOUBLE  = "63";
    static constexpr string_literal<2> IDEOGRAM_STRESSMARK       = "64";
    static constexpr string_literal<2> IDEOGRAM_OFF              = "65";
    static constexpr string_literal<2> FG_BRIGHT_BLACK           = "90";
    static constexpr string_literal<2> FG_BRIGHT_RED             = "91";
    static constexpr string_literal<2> FG_BRIGHT_GREEN           = "92";
    static constexpr string_literal<2> FG_BRIGHT_YELLOW          = "93";
    static constexpr string_literal<2> FG_BRIGHT_BLUE            = "94";
    static constexpr string_literal<2> FG_BRIGHT_MAGENTA         = "95";
    static constexpr string_literal<2> FG_BRIGHT_CYAN            = "96";
    static constexpr string_literal<2> FG_BRIGHT_WHITE           = "97";
    static constexpr string_literal<3> BG_BRIGHT_BLACK           = "100";
    static constexpr string_literal<3> BG_BRIGHT_RED             = "101";
    static constexpr string_literal<3> BG_BRIGHT_GREEN           = "102";
    static constexpr string_literal<3> BG_BRIGHT_YELLOW          = "103";
    static constexpr string_literal<3> BG_BRIGHT_BLUE            = "104";
    static constexpr string_literal<3> BG_BRIGHT_MAGENTA         = "105";
    static constexpr string_literal<3> BG_BRIGHT_CYAN            = "106";
    static constexpr string_literal<3> BG_BRIGHT_WHITE           = "107";


    // template<int I, string_literal<I>... T>
    // static constexpr string_view ansify(string msg) {
    //     return "";
    // }
};



#endif