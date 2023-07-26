// Escape Library
//   Escape the ANSI Escape Code hellhole
//   escape.c
//
// License: GNU-GPL v2.0
//
// Igor Nunes, 2023
// Contribute in https://github.com/ibnunes/Escape

#define __FONT_AS_ANSI_ESCAPE__
#include "escape.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

/* Appends strings, A to B */
#define append(A, B)                                                    \
    {                                                                   \
        aec_t temp;                                                     \
        int r = snprintf(temp, AEC_T_BUFSIZE, "%s%s", B, AEC_SEP);      \
        strcat(A, temp);                                                \
    }

/* Builds the final ANSI Code */
#define codify(A)                                           \
    {                                                       \
        char s[BUFFER_SIZE];                                \
        int r = snprintf(s, BUFFER_SIZE, AEC_FMT, A);       \
        strcpy(A, s);                                       \
    }

/* Parses the ANSI codes and buils an AEC */
const char *_ansi_escape(size_t count, aec_list_t codes) {
    static char ansi_code[BUFFER_SIZE] = "";
    for (size_t i = 0; i < count; i++)
        append(ansi_code, codes[i]);
    ansi_code[strlen(ansi_code) - 1] = '\0';
    codify(ansi_code);
    return ansi_code;
}

/* Just for initial internal developing purposes */
int main(void) { return 0; }
