# ANSI Escape Codes (AEC)

**Notice!** This document can be expanded or changed without prior notice.

These are the descriptors to be used across all supported languages when feasible.



# Control Sequence Introducers (CSI)

Format: `ESC[...`

Using ASCII character `ESC` (Escape):

|  |  |
| --- | --- |
| Octal | `\033` |
| Hexadecimal | `\x1b` |
| Unicode | `\u001b` |



## Select Graphic Rendition (SGR)

Format: `ESC[...m`

| Descriptor | AEC |
| --- | --- |
|  `reset`                     | 0       |
|  `bold`                      | 1       |
|  `faint`                     | 2       |
|  `italic`                    | 3       |
|  `underline`                 | 4       |
|  `blink_slow`                | 5       |
|  `blink_rapid`               | 6       |
|  `reverse`                   | 7       |
|  `conceal`                   | 8       |
|  `crossout`                  | 9       |
|  `font_primary`              | 10      |
|  `font_alternate_1`          | 11      |
|  `font_alternate_2`          | 12      |
|  `font_alternate_3`          | 13      |
|  `font_alternate_4`          | 14      |
|  `font_alternate_5`          | 15      |
|  `font_alternate_6`          | 16      |
|  `font_alternate_7`          | 17      |
|  `font_alternate_8`          | 18      |
|  `font_alternate_9`          | 19      |
|  `fraktur`                   | 20      |
|  `bold_off`                  | 21      |
|  `underline_double`          | 21      |
|  `color_normal`              | 22      |
|  `italic_off`                | 23      |
|  `fraktur_off`               | 23      |
|  `underline_off`             | 24      |
|  `blink_off`                 | 25      |
|  `inverse_off`               | 27      |
|  `reveal`                    | 28      |
|  `crossout_off`              | 29      |
|  `fg_black`                  | 30      |
|  `fg_red`                    | 31      |
|  `fg_green`                  | 32      |
|  `fg_yellow`                 | 33      |
|  `fg_blue`                   | 34      |
|  `fg_magenta`                | 35      |
|  `fg_cyan`                   | 36      |
|  `fg_white`                  | 37      |
|  `fg`                        | 38      |
|  `fg_default`                | 39      |
|  `bg_black`                  | 40      |
|  `bg_red`                    | 41      |
|  `bg_green`                  | 42      |
|  `bg_yellow`                 | 43      |
|  `bg_blue`                   | 44      |
|  `bg_magenta`                | 45      |
|  `bg_cyan`                   | 46      |
|  `bg_white`                  | 47      |
|  `bg`                        | 48      |
|  `bg_default`                | 49      |
|  `frame`                     | 51      |
|  `encircle`                  | 52      |
|  `overline`                  | 53      |
|  `frame_off`                 | 54      |
|  `encircle_off`              | 54      |
|  `overline_off`              | 55      |
|  `ideogram_underline`        | 60      |
|  `ideogram_underline_double` | 61      |
|  `ideogram_overline`         | 62      |
|  `ideogram_overline_double`  | 63      |
|  `ideogram_stressmark`       | 64      |
|  `ideogram_off`              | 65      |
|  `fg_bright_black`           | 90      |
|  `fg_bright_red`             | 91      |
|  `fg_bright_green`           | 92      |
|  `fg_bright_yellow`          | 93      |
|  `fg_bright_blue`            | 94      |
|  `fg_bright_magenta`         | 95      |
|  `fg_bright_cyan`            | 96      |
|  `fg_bright_white`           | 97      |
|  `bg_bright_black`           | 100     |
|  `bg_bright_red`             | 101     |
|  `bg_bright_green`           | 102     |
|  `bg_bright_yellow`          | 103     |
|  `bg_bright_blue`            | 104     |
|  `bg_bright_magenta`         | 105     |
|  `bg_bright_cyan`            | 106     |
|  `bg_bright_white`           | 107     |


### Color modes

Possible AEC-CSI-SGR codes:

| Descriptor | AEC | Type |
| --- | --- | --- |
| `fg` | `38` | Foreground |
| `bg` | `48` | Background |

Color formats (where `A` is the previously listed ANSI Code):

| Color mode | ANSI Code | Format |
| --- | --- | --- |
| 8-bit (from 0 to 255) | `5` | `A;5;C`</br>Where `C` is an 8-bit color code. |
| RGB                   | `2` | `A;2;R;G;B`</br>Where `R`, `G` and `B` are red, green and blue channels of RGB color. |

Examples:
  * `38;2;9;100;50` &mdash; foreground color with RGB `#096432` (9, 100, 50);
  * `48;5;32` &mdash; pre-defined 8-bit background color with code `32`.
