#define __FONT_AS_ANSI_ESCAPE__
#include "escape.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

#define append(A, B)                                                    \
    {                                                                   \
        aec_t temp;                                                     \
        int r = snprintf(temp, AEC_T_BUFSIZE, "%s%s", B, AEC_SEP);      \
        strcat(A, temp);                                                \
    }


#define ansify(A)                                           \
    {                                                       \
        char s[BUFFER_SIZE];                                \
        int r = snprintf(s, BUFFER_SIZE, AEC_FMT, A);       \
        strcpy(A, s);                                       \
    }


const char *_ansi_escape(size_t count, aec_list_t codes) {
    static char ansi_code[BUFFER_SIZE] = "";
    for (size_t i = 0; i < count; i++)
        append(ansi_code, codes[i]);
    ansify(ansi_code);
    return ansi_code;
}
