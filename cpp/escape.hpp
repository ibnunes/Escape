#ifndef ESCAPE_H
#define ESCAPE_H

#include <cassert>
#include <vector>
#include <string>
#include <string_view>

using namespace std;

namespace detail
{
    template<unsigned... digits>
    struct to_chars { static const char value[]; };

    template<unsigned... digits>
    constexpr char to_chars<digits...>::value[] = {('0' + digits)..., 0};

    template<unsigned rem, unsigned... digits>
    struct explode : explode<rem / 10, rem % 10, digits...> {};

    template<unsigned... digits>
    struct explode<0, digits...> : to_chars<digits...> {};
}

template<unsigned num>
struct string_of_int : detail::explode<num> {};

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


    static string ansi_codify(int code) {
        string ansi_code(Ansi::ESCAPECODE_BEGIN);
        ansi_code.append(to_string(code));
        return ansi_code.append(Ansi::ESCAPECODE_END);
    }

    static string ansi_codify(vector<int> codes) {
        string ansi_code(Ansi::ESCAPECODE_BEGIN);
        for (auto code : codes) {
            ansi_code.append(to_string(code));
            ansi_code.append(Ansi::SEPARATOR);
        }
        ansi_code.pop_back();
        return ansi_code.append(Ansi::ESCAPECODE_END);
    }

    template<int... codes>
    static string ansify(string msg) {
        string ansified_msg(Ansi::ansi_codify(vector<int> {codes...}));
        ansified_msg.append(msg);
        return ansified_msg.append(Ansi::ansi_codify(Ansi::RESET));
    }
};



#endif