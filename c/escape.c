#include "escape.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_SIZE 256

char *_ansi_escape(size_t count, aec_list_t codes) {
    bool catch = false;
    aec_t color[3];
    int color_count = 0;
    char *ansi_code = malloc(BUFFER_SIZE * sizeof(char));
    // ansi_code[0] = '\0';

    aec_t code;
    for (size_t i = 0; i < count; i++) {
        code = codes[i];
        switch (code) {
            case FG:
            case BG:
                if (catch) {
                    switch (color_count) {
                        case 1:
                            snprintf(ansi_code, BUFFER_SIZE, "%s;%hu;%hu", ansi_code, 5, color[0]);
                            break;
                        case 3:
                            snprintf(ansi_code, BUFFER_SIZE, "%s;%hu;%hu;%hu;%hu", ansi_code, 5, color[0], color[1], color[2]);
                            break;
                        default:
                            break;
                    }
                    snprintf(ansi_code, BUFFER_SIZE, "%s;%hu", ansi_code, code);
                    catch = true;
                }
                break;

            default:
                break;
        }
    }
}