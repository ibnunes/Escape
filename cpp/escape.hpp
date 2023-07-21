#ifndef ESCAPE_H
#define ESCAPE_H

#include <cassert>
#include <cstdint>
#include <vector>
#include <string>
#include <string_view>

using namespace std;



template<int N>
class to_string_t {

    constexpr static auto buflen() noexcept {
        unsigned int len = N > 0 ? 1 : 2;
        for (auto n = N; n; len++, n /= 10);
        return len;
    }

    char buf[buflen()] = {};

public:
    constexpr to_string_t() noexcept {
        auto ptr = buf + buflen();
        *--ptr = '\0';
        if (N != 0) {
            for (auto n = N; n; n /= 10)
                *--ptr = "0123456789"[(N < 0 ? -1 : 1) * (n % 10)];
            if (N < 0)
                *--ptr = '-';
        } else {
            buf[0] = '0';
        }
    }

    constexpr operator const char *() const { return buf; }
};

struct RefImpl {};
struct ArrayImpl {};

template <int N, typename Impl>
class sstring { };

template<int N>
class sstring<N, RefImpl> {
    const char (&_lit)[N + 1];
public:
    constexpr sstring(const char (&lit)[N + 1]) : _lit(lit) {}
    constexpr char operator[](int i) const requires (i >= 0 && i < N) { return _lit[i]; }
};



template<std::intmax_t N>
constexpr to_string_t<N> stringify;














// ----------------------------------------------------------------------

/*
struct RefImpl {};
struct ArrayImpl {};

template <int N, typename Impl>
class sstring {
    static_assert(N != N, "***");
};

template<int N>
class sstring<N, RefImpl> {
    const char (&_lit)[N + 1];
public:
    constexpr sstring(const char (&lit)[N + 1])
        //requires (lit[N] == '\0')
        : _lit(lit) {}
    constexpr char operator[](int i) const requires (i >= 0 && i < N) { return _lit[i]; }
};

template<int N>
class sstring<N, ArrayImpl> {
    char _array[N + 1];
public:
    template<int N1> requires (N1 <= N)
    constexpr sstring(const sstring<N1, RefImpl>&     s1,
                      const sstring<N - N1, RefImpl>& s2)
    {
        for (int i = 0; i < N1; ++i)
            _array[i] = s1[i];
        for (int i = 0; i < N - N1; ++i)
            _array[N1 + i] = s2[i];
        _array[N] = '\0';
    }
    constexpr char operator[](int i) const requires (i >= 0 && i < N) { return _array[i]; }
    constexpr std::size_t size() const { return N; }
};

template <int N_PLUS_1>
sstring(const char (&lit)[N_PLUS_1])
    -> sstring<N_PLUS_1 - 1, RefImpl>;

template<int N> using array_string     = sstring<N, ArrayImpl>;
template<int N> using string_literal   = sstring<N, RefImpl>;

template<int N_PLUS_1>
constexpr auto literal(const char (&lit)[N_PLUS_1])
    -> string_literal<N_PLUS_1 - 1>
{
    return string_literal<N_PLUS_1 - 1>(lit);
}

template<int N1, int N2>
constexpr auto operator+(const string_literal<N1>& s1,
                         const string_literal<N2>& s2)
    -> array_string<N1 + N2>
{
    return array_string<N1 + N2>(s1, s2);
}

template<std::intmax_t N>
class to_string_t {

    constexpr static auto buflen() noexcept {
        unsigned int len = N > 0 ? 1 : 2;
        for (auto n = N; n; len++, n /= 10);
        return len;
    }

    char buf[buflen()] = {};

public:
    constexpr to_string_t() noexcept {
        auto ptr = buf + buflen();
        *--ptr = '\0';
        if (N != 0) {
            for (auto n = N; n; n /= 10)
                *--ptr = "0123456789"[(N < 0 ? -1 : 1) * (n % 10)];
            if (N < 0)
                *--ptr = '-';
        } else {
            buf[0] = '0';
        }
    }

    constexpr operator const char *() const { return buf; }
};

template<std::intmax_t N>
constexpr to_string_t<N> string_of_int;

template<const char* code>
constexpr sstring AnsiCode = code;
*/

// ----------------------------------------------------------------------

/*
template<std::intmax_t N, std::intmax_t C = 0, bool shownum = true>
class to_string_t {

    constexpr static auto buflen() noexcept {
        unsigned int len = !shownum ? 0 : (N > 0 ? 1 : 2);
        for (auto n = !shownum ? 0 : N; n; len++, n /= 10);
        return len + C + (!shownum ? 1 : 0);
    }

    char buf[buflen()] = {};

public:
    constexpr to_string_t(const char (&cc)[C+1] = "") noexcept {
        auto ptr = buf + buflen();
        *--ptr = '\0';

        for (auto c = C; c; c--)
            *--ptr = cc[c-1];

        if (N != 0) {
            for (auto n = N; n; n /= 10)
                *--ptr = "0123456789"[(N < 0 ? -1 : 1) * (n % 10)];
            if (N < 0)
                *--ptr = '-';
        } else {
            buf[0] = '0';
        }
    }

    constexpr operator const char *() const { return buf; }
    constexpr const char* c_str() { return buf; }
    constexpr const char at(int i) { return buf[i]; }
    constexpr const int size() { return buflen() - 1; }
};


template<std::intmax_t N1, std::intmax_t N2, std::intmax_t C1, std::intmax_t C2, bool B1, bool B2>
constexpr auto operator+(to_string_t<N1, C1, B1> a, to_string_t<N2, C2, B2> b)
    //-> to_string_t<N1+N2, C1 + C2, B1||B2>
{
    constexpr auto buflen = a.size() + b.size() + 1;
    char buf[buflen] = {};
    auto ptr = buf + buflen;
    *--ptr = '\0';
    for (auto n = b.size(); n; n--)
        *--ptr = b.at(n-1);
    for (auto n = a.size(); n; n--)
        *--ptr = a.at(n-1);
    return to_string_t<N1, buflen - 1, false>( buf );
};

template<std::intmax_t N>
constexpr to_string_t<N> string_of_int;

constexpr int size(const char *s) {
    int c = 0;
    for (; *s != '\0'; s++, c++);
    return c;
}

template<int code, std::intmax_t N = 0>
class AnsiCode : public to_string_t<code, N> {
public:
    constexpr AnsiCode(const char (&s)[N+1] = "") noexcept : to_string_t<code, N>(s) {}
};

template<int code, int color>
class AnsiColorStd : public AnsiCode<code, to_string_t<color>().size() + 3> {
public:
    constexpr AnsiColorStd() noexcept : AnsiCode<code, to_string_t<color>().size() + 3>(
        to_string_t<0, 3, false>(";5;") +
        to_string_t<color>()
    ) {}
};

template<int code, int r, int g, int b>
class AnsiColorRGB : public AnsiCode<code> {
public:
    constexpr AnsiColorRGB() noexcept : to_string_t<code>(
        to_string_t<0, 3, false>(";2;") +
        to_string_t<r>()                +
        to_string_t<0, 1, false>(";")   +
        to_string_t<g>()                +
        to_string_t<0, 1, false>(";")   +
        to_string_t<b>()
    ) {}
};

template<int... Is>
class FG;

template<int color>
class FG<color> : public AnsiColorStd<38, color> {};

template<int r, int g, int b>
class FG<r, g, b> : public AnsiColorRGB<38, r, g, b> {};
*/

// ----------------------------------------------------------------------




class Ansi {
private:
    static constexpr string_view SEPARATOR          = ";";
    static constexpr string_view ESCAPECODE_BEGIN   = "\033[";
    static constexpr string_view ESCAPECODE_END     = "m";

public:
    static constexpr int RESET                     = 0;
    static constexpr int BOLD                      = 1;
    static constexpr int FAINT                     = 2;
    static constexpr int ITALIC                    = 3;
    static constexpr int UNDERLINE                 = 4;
    static constexpr int BLINK_SLOW                = 5;
    static constexpr int BLINK_RAPID               = 6;
    static constexpr int REVERSE                   = 7;
    static constexpr int CONCEAL                   = 8;
    static constexpr int CROSSOUT                  = 9;
    static constexpr int FONT_PRIMARY              = 10;
    static constexpr int FONT_ALTERNATE_1          = 11;
    static constexpr int FONT_ALTERNATE_2          = 12;
    static constexpr int FONT_ALTERNATE_3          = 13;
    static constexpr int FONT_ALTERNATE_4          = 14;
    static constexpr int FONT_ALTERNATE_5          = 15;
    static constexpr int FONT_ALTERNATE_6          = 16;
    static constexpr int FONT_ALTERNATE_7          = 17;
    static constexpr int FONT_ALTERNATE_8          = 18;
    static constexpr int FONT_ALTERNATE_9          = 19;
    static constexpr int FRAKTUR                   = 20;
    static constexpr int BOLD_OFF                  = 21;
    static constexpr int UNDERLINE_DOUBLE          = 21;
    static constexpr int COLOR_NORMAL              = 22;
    static constexpr int ITALIC_OFF                = 23;
    static constexpr int FRAKTUR_OFF               = 23;
    static constexpr int UNDERLINE_OFF             = 24;
    static constexpr int BLINK_OFF                 = 25;
    static constexpr int INVERSE_OFF               = 27;
    static constexpr int REVEAL                    = 28;
    static constexpr int CROSSOUT_OFF              = 29;
    static constexpr int FG_BLACK                  = 30;
    static constexpr int FG_RED                    = 31;
    static constexpr int FG_GREEN                  = 32;
    static constexpr int FG_YELLOW                 = 33;
    static constexpr int FG_BLUE                   = 34;
    static constexpr int FG_MAGENTA                = 35;
    static constexpr int FG_CYAN                   = 36;
    static constexpr int FG_WHITE                  = 37;
    //static constexpr int FG                        = "38";
    static constexpr int FG_DEFAULT                = 39;
    static constexpr int BG_BLACK                  = 40;
    static constexpr int BG_RED                    = 41;
    static constexpr int BG_GREEN                  = 42;
    static constexpr int BG_YELLOW                 = 43;
    static constexpr int BG_BLUE                   = 44;
    static constexpr int BG_MAGENTA                = 45;
    static constexpr int BG_CYAN                   = 46;
    static constexpr int BG_WHITE                  = 47;
    //static constexpr int BG                        = "48";
    static constexpr int BG_DEFAULT                = 49;
    static constexpr int FRAME                     = 51;
    static constexpr int ENCIRCLE                  = 52;
    static constexpr int OVERLINE                  = 53;
    static constexpr int FRAME_OFF                 = 54;
    static constexpr int ENCIRCLE_OFF              = 54;
    static constexpr int OVERLINE_OFF              = 55;
    static constexpr int IDEOGRAM_UNDERLINE        = 60;
    static constexpr int IDEOGRAM_UNDERLINE_DOUBLE = 61;
    static constexpr int IDEOGRAM_OVERLINE         = 62;
    static constexpr int IDEOGRAM_OVERLINE_DOUBLE  = 63;
    static constexpr int IDEOGRAM_STRESSMARK       = 64;
    static constexpr int IDEOGRAM_OFF              = 65;
    static constexpr int FG_BRIGHT_BLACK           = 90;
    static constexpr int FG_BRIGHT_RED             = 91;
    static constexpr int FG_BRIGHT_GREEN           = 92;
    static constexpr int FG_BRIGHT_YELLOW          = 93;
    static constexpr int FG_BRIGHT_BLUE            = 94;
    static constexpr int FG_BRIGHT_MAGENTA         = 95;
    static constexpr int FG_BRIGHT_CYAN            = 96;
    static constexpr int FG_BRIGHT_WHITE           = 97;
    static constexpr int BG_BRIGHT_BLACK           = 100;
    static constexpr int BG_BRIGHT_RED             = 101;
    static constexpr int BG_BRIGHT_GREEN           = 102;
    static constexpr int BG_BRIGHT_YELLOW          = 103;
    static constexpr int BG_BRIGHT_BLUE            = 104;
    static constexpr int BG_BRIGHT_MAGENTA         = 105;
    static constexpr int BG_BRIGHT_CYAN            = 106;
    static constexpr int BG_BRIGHT_WHITE           = 107;

    static string ansi_codify(int);
    static string ansi_codify(vector<int>);
    template<int... codes> static string ansify(string);
};



#endif