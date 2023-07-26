// Escape Library
//   Escape the ANSI Escape Code hellhole
//   escape.h
//
// License: GNU-GPL v2.0
//
// Igor Nunes, 2023
// Contribute in https://github.com/ibnunes/Escape

#ifndef ESCAPE_H
#define ESCAPE_H

#include <stdlib.h>

/* Type definitions */
#define AEC_T_BUFSIZE   17
typedef char aec_t[AEC_T_BUFSIZE];      // Maximum possible size for a single AEC
typedef aec_t aec_list_t[];             // A list of AECs

/* ANSI Escape Codes */
#define RESET                     "0"
#define BOLD                      "1"
#define FAINT                     "2"
#define ITALIC                    "3"
#define UNDERLINE                 "4"
#define BLINK_SLOW                "5"
#define BLINK_RAPID               "6"
#define REVERSE                   "7"
#define CONCEAL                   "8"
#define CROSSOUT                  "9"
#define FONT_PRIMARY              "10"
#define FONT_ALTERNATE_1          "11"
#define FONT_ALTERNATE_2          "12"
#define FONT_ALTERNATE_3          "13"
#define FONT_ALTERNATE_4          "14"
#define FONT_ALTERNATE_5          "15"
#define FONT_ALTERNATE_6          "16"
#define FONT_ALTERNATE_7          "17"
#define FONT_ALTERNATE_8          "18"
#define FONT_ALTERNATE_9          "19"
#define FRAKTUR                   "20"
#define BOLD_OFF                  "21"
#define UNDERLINE_DOUBLE          "21"
#define COLOR_NORMAL              "22"
#define ITALIC_OFF                "23"
#define FRAKTUR_OFF               "23"
#define UNDERLINE_OFF             "24"
#define BLINK_OFF                 "25"
#define INVERSE_OFF               "27"
#define REVEAL                    "28"
#define CROSSOUT_OFF              "29"
#define FG_BLACK                  "30"
#define FG_RED                    "31"
#define FG_GREEN                  "32"
#define FG_YELLOW                 "33"
#define FG_BLUE                   "34"
#define FG_MAGENTA                "35"
#define FG_CYAN                   "36"
#define FG_WHITE                  "37"
#define FG_DEFAULT                "39"
#define BG_BLACK                  "40"
#define BG_RED                    "41"
#define BG_GREEN                  "42"
#define BG_YELLOW                 "43"
#define BG_BLUE                   "44"
#define BG_MAGENTA                "45"
#define BG_CYAN                   "46"
#define BG_WHITE                  "47"
#define BG_DEFAULT                "49"
#define FRAME                     "51"
#define ENCIRCLE                  "52"
#define OVERLINE                  "53"
#define FRAME_OFF                 "54"
#define ENCIRCLE_OFF              "54"
#define OVERLINE_OFF              "55"
#define IDEOGRAM_UNDERLINE        "60"
#define IDEOGRAM_UNDERLINE_DOUBLE "61"
#define IDEOGRAM_OVERLINE         "62"
#define IDEOGRAM_OVERLINE_DOUBLE  "63"
#define IDEOGRAM_STRESSMARK       "64"
#define IDEOGRAM_OFF              "65"
#define FG_BRIGHT_BLACK           "90"
#define FG_BRIGHT_RED             "91"
#define FG_BRIGHT_GREEN           "92"
#define FG_BRIGHT_YELLOW          "93"
#define FG_BRIGHT_BLUE            "94"
#define FG_BRIGHT_MAGENTA         "95"
#define FG_BRIGHT_CYAN            "96"
#define FG_BRIGHT_WHITE           "97"
#define BG_BRIGHT_BLACK           "100"
#define BG_BRIGHT_RED             "101"
#define BG_BRIGHT_GREEN           "102"
#define BG_BRIGHT_YELLOW          "103"
#define BG_BRIGHT_BLUE            "104"
#define BG_BRIGHT_MAGENTA         "105"
#define BG_BRIGHT_CYAN            "106"
#define BG_BRIGHT_WHITE           "107"

/* ANSI Colors */
// Foreground
#define FG1(A)                    "38;5;" #A
#define FG2(A, B)                 "38;5;" #A
#define FG3(A, B, C)              "38;2;" #A AEC_SEP #B AEC_SEP #C
#define GET_FG(_1,_2,_3,NAME,...) NAME
#define FG(...) GET_FG(__VA_ARGS__, FG3, FG2, FG1)(__VA_ARGS__)

// Background
#define BG1(A)                    "48;5;" #A
#define BG2(A, B)                 "48;5;" #A
#define BG3(A, B, C)              "48;2;" #A AEC_SEP #B AEC_SEP #C
#define GET_BG(_1,_2,_3,NAME,...) NAME
#define BG(...) GET_BG(__VA_ARGS__, BG3, BG2, BG1)(__VA_ARGS__)

/* AEC formatting */
#define AEC_FMT     "\033[%sm"
#define AEC_SEP     ";"

/* Functions and aliases */
const char *_ansi_escape(size_t, aec_list_t);

#define ansi_escape(...) \
    _ansi_escape(sizeof ((aec_t []){ __VA_ARGS__ }) / sizeof(aec_t), (aec_t []){ __VA_ARGS__ })

// TODO: review the practicality of keeping this behind a definition
#ifdef __FONT_AS_ANSI_ESCAPE__
#define font        ansi_escape
#define nofont      font(RESET)
#endif

#endif