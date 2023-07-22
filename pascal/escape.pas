{$mode objfpc}
unit escape;

interface

const reset                     : string = '0';
const bold                      : string = '1';
const faint                     : string = '2';
const italic                    : string = '3';
const underline                 : string = '4';
const blink_slow                : string = '5';
const blink_rapid               : string = '6';
const reverse                   : string = '7';
const conceal                   : string = '8';
const crossout                  : string = '9';
const font_primary              : string = '10';
const font_alternate_1          : string = '11';
const font_alternate_2          : string = '12';
const font_alternate_3          : string = '13';
const font_alternate_4          : string = '14';
const font_alternate_5          : string = '15';
const font_alternate_6          : string = '16';
const font_alternate_7          : string = '17';
const font_alternate_8          : string = '18';
const font_alternate_9          : string = '19';
const fraktur                   : string = '20';
const bold_off                  : string = '21';
const underline_double          : string = '21';
const color_normal              : string = '22';
const italic_off                : string = '23';
const fraktur_off               : string = '23';
const underline_off             : string = '24';
const blink_off                 : string = '25';
const inverse_off               : string = '27';
const reveal                    : string = '28';
const crossout_off              : string = '29';
const fg_black                  : string = '30';
const fg_red                    : string = '31';
const fg_green                  : string = '32';
const fg_yellow                 : string = '33';
const fg_blue                   : string = '34';
const fg_magenta                : string = '35';
const fg_cyan                   : string = '36';
const fg_white                  : string = '37';
const fg                        : string = '38';
const fg_default                : string = '39';
const bg_black                  : string = '40';
const bg_red                    : string = '41';
const bg_green                  : string = '42';
const bg_yellow                 : string = '43';
const bg_blue                   : string = '44';
const bg_magenta                : string = '45';
const bg_cyan                   : string = '46';
const bg_white                  : string = '47';
const bg                        : string = '48';
const bg_default                : string = '49';
const frame                     : string = '51';
const encircle                  : string = '52';
const overline                  : string = '53';
const frame_off                 : string = '54';
const encircle_off              : string = '54';
const overline_off              : string = '55';
const ideogram_underline        : string = '60';
const ideogram_underline_double : string = '61';
const ideogram_overline         : string = '62';
const ideogram_overline_double  : string = '63';
const ideogram_stressmark       : string = '64';
const ideogram_off              : string = '65';
const fg_bright_black           : string = '90';
const fg_bright_red             : string = '91';
const fg_bright_green           : string = '92';
const fg_bright_yellow          : string = '93';
const fg_bright_blue            : string = '94';
const fg_bright_magenta         : string = '95';
const fg_bright_cyan            : string = '96';
const fg_bright_white           : string = '97';
const bg_bright_black           : string = '100';
const bg_bright_red             : string = '101';
const bg_bright_green           : string = '102';
const bg_bright_yellow          : string = '103';
const bg_bright_blue            : string = '104';
const bg_bright_magenta         : string = '105';
const bg_bright_cyan            : string = '106';
const bg_bright_white           : string = '107';

function ansify(codes : array of const; const msg : string) : string;

implementation
uses sysutils;

const ansi_begin : string = #27'[';
const ansi_end : string = 'm';
const ansi_separator : char = ';';

function codify(codes : array of const) : string;
const
    COLOR_MODE : array[1..3] of string = ('5', '5', '2');

var _color : array[1..3] of byte;
    _clind : 1..3 = 1;
    _catch : boolean = false;
    _param : string = '';
    i : word;

    function color_to_string(const color : array of byte) : string;
    var c : byte;
    begin
        color_to_string := '';
        for c in color do
            color_to_string += IntToStr(c) + ansi_separator;
        Delete(color_to_string, Length(color_to_string) - 1, 1);
    end;

    procedure flush_color;
    begin
        _param += COLOR_MODE[_clind] + ansi_separator + color_to_string(_color[1.._clind]);
    end;

begin
    for i := 0 to High(codes) do begin
        case codes[i].vType of
            vtString:
                case codes[i].vString^ of
                    'fg', 'bg': begin
                        if _catch then flush_color;
                        _param += codes[i].vString^ + ansi_separator;;
                        _catch := true;
                    end
                else begin
                    if _catch then begin
                        _catch := false;
                        flush_color;
                    end;
                    _param += codes[i].vString^ + ansi_separator;
                end;
                end;

            vtInteger:
                if _catch then begin
                    _color[_clind] := codes[i].vInteger;
                    Inc(_clind);
                end;
        else
            exit;
        end;
    end;
    codify := ansi_begin + _param + ansi_end;
end;


function ansify(codes : array of const; const msg : string) : string;
begin
    ansify := codify(codes) + msg + codify([reset]);
end;

end.
