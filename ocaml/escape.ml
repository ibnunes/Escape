

type ansiCode =
  | Reset
  | Bold
  | Faint
  | Italic
  | Underline
  | Blink_Slow
  | Blink_Rapid
  | Reverse
  | Conceal
  | Crossout
  | Font_Primary
  | Font_Alternate_1
  | Font_Alternate_2
  | Font_Alternate_3
  | Font_Alternate_4
  | Font_Alternate_5
  | Font_Alternate_6
  | Font_Alternate_7
  | Font_Alternate_8
  | Font_Alternate_9
  | Fraktur
  | Bold_Off
  | Underline_Double
  | Color_Normal
  | Italic_Off
  | Fraktur_Off
  | Underline_Off
  | Blink_Off
  | Inverse_Off
  | Reveal
  | Crossout_Off
  | Fg_Black
  | Fg_Red
  | Fg_Green
  | Fg_Yellow
  | Fg_Blue
  | Fg_Magenta
  | Fg_Cyan
  | Fg_White
  | Fg  of int
  | Fgx of int * int * int
  | Fg_Default
  | Bg_Black
  | Bg_Red
  | Bg_Green
  | Bg_Yellow
  | Bg_Blue
  | Bg_Magenta
  | Bg_Cyan
  | Bg_White
  | Bg  of int
  | Bgx of int * int * int
  | Bg_Default
  | Frame
  | Encircle
  | Overline
  | Frame_Off
  | Encircle_Off
  | Overline_Off
  | Ideogram_Underline
  | Ideogram_Underline_Double
  | Ideogram_Overline
  | Ideogram_Overline_Double
  | Ideogram_Stressmark
  | Ideogram_Off
  | Fg_Bright_Black
  | Fg_Bright_Red
  | Fg_Bright_Green
  | Fg_Bright_Yellow
  | Fg_Bright_Blue
  | Fg_Bright_Magenta
  | Fg_Bright_Cyan
  | Fg_Bright_White
  | Bg_Bright_Black
  | Bg_Bright_Red
  | Bg_Bright_Green
  | Bg_Bright_Yellow
  | Bg_Bright_Blue
  | Bg_Bright_Magenta
  | Bg_Bright_Cyan
  | Bg_Bright_White

let stringify = function
  | Reset                     -> "0"
  | Bold                      -> "1"
  | Faint                     -> "2"
  | Italic                    -> "3"
  | Underline                 -> "4"
  | Blink_Slow                -> "5"
  | Blink_Rapid               -> "6"
  | Reverse                   -> "7"
  | Conceal                   -> "8"
  | Crossout                  -> "9"
  | Font_Primary              -> "10"
  | Font_Alternate_1          -> "11"
  | Font_Alternate_2          -> "12"
  | Font_Alternate_3          -> "13"
  | Font_Alternate_4          -> "14"
  | Font_Alternate_5          -> "15"
  | Font_Alternate_6          -> "16"
  | Font_Alternate_7          -> "17"
  | Font_Alternate_8          -> "18"
  | Font_Alternate_9          -> "19"
  | Fraktur                   -> "20"
  | Bold_Off                  -> "21"
  | Underline_Double          -> "21"
  | Color_Normal              -> "22"
  | Italic_Off                -> "23"
  | Fraktur_Off               -> "23"
  | Underline_Off             -> "24"
  | Blink_Off                 -> "25"
  | Inverse_Off               -> "27"
  | Reveal                    -> "28"
  | Crossout_Off              -> "29"
  | Fg_Black                  -> "30"
  | Fg_Red                    -> "31"
  | Fg_Green                  -> "32"
  | Fg_Yellow                 -> "33"
  | Fg_Blue                   -> "34"
  | Fg_Magenta                -> "35"
  | Fg_Cyan                   -> "36"
  | Fg_White                  -> "37"
  | Fg (color)                -> "38;5;" ^ string_of_int color
  | Fgx (r, g, b)             -> List.fold_left (fun s c -> s ^ ";" ^ string_of_int c) "38;2" [r; g; b]
  | Fg_Default                -> "39"
  | Bg_Black                  -> "40"
  | Bg_Red                    -> "41"
  | Bg_Green                  -> "42"
  | Bg_Yellow                 -> "43"
  | Bg_Blue                   -> "44"
  | Bg_Magenta                -> "45"
  | Bg_Cyan                   -> "46"
  | Bg_White                  -> "47"
  | Bg (color)                -> "48;5;" ^ string_of_int color
  | Bgx (r, g, b)             -> List.fold_left (fun s c -> s ^ ";" ^ string_of_int c) "48;2" [r; g; b]
  | Bg_Default                -> "49"
  | Frame                     -> "51"
  | Encircle                  -> "52"
  | Overline                  -> "53"
  | Frame_Off                 -> "54"
  | Encircle_Off              -> "54"
  | Overline_Off              -> "55"
  | Ideogram_Underline        -> "60"
  | Ideogram_Underline_Double -> "61"
  | Ideogram_Overline         -> "62"
  | Ideogram_Overline_Double  -> "63"
  | Ideogram_Stressmark       -> "64"
  | Ideogram_Off              -> "65"
  | Fg_Bright_Black           -> "90"
  | Fg_Bright_Red             -> "91"
  | Fg_Bright_Green           -> "92"
  | Fg_Bright_Yellow          -> "93"
  | Fg_Bright_Blue            -> "94"
  | Fg_Bright_Magenta         -> "95"
  | Fg_Bright_Cyan            -> "96"
  | Fg_Bright_White           -> "97"
  | Bg_Bright_Black           -> "100"
  | Bg_Bright_Red             -> "101"
  | Bg_Bright_Green           -> "102"
  | Bg_Bright_Yellow          -> "103"
  | Bg_Bright_Blue            -> "104"
  | Bg_Bright_Magenta         -> "105"
  | Bg_Bright_Cyan            -> "106"
  | Bg_Bright_White           -> "107"

let (<|) f g x = f (g x)
let (<<) f x = f x

let codify =
  (fun s -> String.sub s 0 (String.length s - 1) ^ "m") <|
  List.fold_left (fun s c -> s ^ stringify c ^ ";") "\x1b["

let ansify codes msg =
  let ansi_codes = codify codes in
  let ansi_codes = String.sub ansi_codes 0 (String.length ansi_codes - 1) ^ "m" in
    ansi_codes ^ msg ^ codify [Reset]


let () =
  let () = ansify [Bold; Fg_Red] "Fatality!" |> print_endline in
  let () = ansify [Bold; Underline] ("Cor " ^ codify [Fgx (34, 238, 177)] ^ "bonita") |> print_endline in
    ()
