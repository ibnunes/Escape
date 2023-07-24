{$mode objfpc}
unit escape;

interface
uses classes, sysutils;

type
    TAnsiColorEnum = (AnsiColorRGB = 2, AnsiColorStd = 5);

    TAnsiColorRec = record
        case mode : TAnsiColorEnum of
            AnsiColorStd: (color : byte);
            AnsiColorRGB: (r, g, b : byte);
    end;

    IAnsiCode = interface['{eeb511e3-0dbe-4fec-a72f-473f8bf8a8de}']
        function AsString : string;
        function AsByte : byte;
        function WithColor(const color : byte) : IAnsiCode; overload;
        function WithColor(const r, g, b : byte) : IAnsiCode; overload;
    end;

    IAnsiColor = interface['{a9f9f329-e69f-436c-b17f-ee0b962c1486}']
        function AsString : string;
        function ColorMode : TAnsiColorEnum;
        function AsColor : TAnsiColorRec;
    end;

    TAnsiColor = class(TInterfacedObject, IAnsiColor)
    private
        vString : string;
        vColor  : TAnsiColorRec;
    public
        constructor Create(const color : byte); overload;
        constructor Create(const r, g, b : byte); overload;
        class function New(const color : byte) : IAnsiColor; overload;
        class function New(const r, g, b : byte) : IAnsiColor; overload;
        function AsString : string;
        function ColorMode : TAnsiColorEnum;
        function AsColor : TAnsiColorRec;
    end;


    TAnsiCode = class(TInterfacedObject, IAnsiCode)
    private
        vCode   : byte;
        vString : string;
        vHasColor : boolean;
        function WithCode(const code : byte) : IAnsiCode;
    public
        constructor Create(const code : byte);
        class function New(const code : byte) : IAnsiCode;
        function WithColor(const color : byte) : IAnsiCode; overload;
        function WithColor(const r, g, b : byte) : IAnsiCode; overload;
        function AsString : string;
        function AsByte : byte;
    end;




var RESET                       : IAnsiCode;
    BOLD                        : IAnsiCode;
    FAINT                       : IAnsiCode;
    ITALIC                      : IAnsiCode;
    UNDERLINE                   : IAnsiCode;
    BLINK_SLOW                  : IAnsiCode;
    BLINK_RAPID                 : IAnsiCode;
    REVERSE                     : IAnsiCode;
    CONCEAL                     : IAnsiCode;
    CROSSOUT                    : IAnsiCode;
    FONT_PRIMARY                : IAnsiCode;
    FONT_ALTERNATE_1            : IAnsiCode;
    FONT_ALTERNATE_2            : IAnsiCode;
    FONT_ALTERNATE_3            : IAnsiCode;
    FONT_ALTERNATE_4            : IAnsiCode;
    FONT_ALTERNATE_5            : IAnsiCode;
    FONT_ALTERNATE_6            : IAnsiCode;
    FONT_ALTERNATE_7            : IAnsiCode;
    FONT_ALTERNATE_8            : IAnsiCode;
    FONT_ALTERNATE_9            : IAnsiCode;
    FRAKTUR                     : IAnsiCode;
    BOLD_OFF                    : IAnsiCode;
    UNDERLINE_DOUBLE            : IAnsiCode;
    COLOR_NORMAL                : IAnsiCode;
    ITALIC_OFF                  : IAnsiCode;
    FRAKTUR_OFF                 : IAnsiCode;
    UNDERLINE_OFF               : IAnsiCode;
    BLINK_OFF                   : IAnsiCode;
    INVERSE_OFF                 : IAnsiCode;
    REVEAL                      : IAnsiCode;
    CROSSOUT_OFF                : IAnsiCode;
    FG_BLACK                    : IAnsiCode;
    FG_RED                      : IAnsiCode;
    FG_GREEN                    : IAnsiCode;
    FG_YELLOW                   : IAnsiCode;
    FG_BLUE                     : IAnsiCode;
    FG_MAGENTA                  : IAnsiCode;
    FG_CYAN                     : IAnsiCode;
    FG_WHITE                    : IAnsiCode;
    FG_DEFAULT                  : IAnsiCode;
    BG_BLACK                    : IAnsiCode;
    BG_RED                      : IAnsiCode;
    BG_GREEN                    : IAnsiCode;
    BG_YELLOW                   : IAnsiCode;
    BG_BLUE                     : IAnsiCode;
    BG_MAGENTA                  : IAnsiCode;
    BG_CYAN                     : IAnsiCode;
    BG_WHITE                    : IAnsiCode;
    BG_DEFAULT                  : IAnsiCode;
    FRAME                       : IAnsiCode;
    ENCIRCLE                    : IAnsiCode;
    OVERLINE                    : IAnsiCode;
    FRAME_OFF                   : IAnsiCode;
    ENCIRCLE_OFF                : IAnsiCode;
    OVERLINE_OFF                : IAnsiCode;
    IDEOGRAM_UNDERLINE          : IAnsiCode;
    IDEOGRAM_UNDERLINE_DOUBLE   : IAnsiCode;
    IDEOGRAM_OVERLINE           : IAnsiCode;
    IDEOGRAM_OVERLINE_DOUBLE    : IAnsiCode;
    IDEOGRAM_STRESSMARK         : IAnsiCode;
    IDEOGRAM_OFF                : IAnsiCode;
    FG_BRIGHT_BLACK             : IAnsiCode;
    FG_BRIGHT_RED               : IAnsiCode;
    FG_BRIGHT_GREEN             : IAnsiCode;
    FG_BRIGHT_YELLOW            : IAnsiCode;
    FG_BRIGHT_BLUE              : IAnsiCode;
    FG_BRIGHT_MAGENTA           : IAnsiCode;
    FG_BRIGHT_CYAN              : IAnsiCode;
    FG_BRIGHT_WHITE             : IAnsiCode;
    BG_BRIGHT_BLACK             : IAnsiCode;
    BG_BRIGHT_RED               : IAnsiCode;
    BG_BRIGHT_GREEN             : IAnsiCode;
    BG_BRIGHT_YELLOW            : IAnsiCode;
    BG_BRIGHT_BLUE              : IAnsiCode;
    BG_BRIGHT_MAGENTA           : IAnsiCode;
    BG_BRIGHT_CYAN              : IAnsiCode;
    BG_BRIGHT_WHITE             : IAnsiCode;

function FG(const color : byte)   : IAnsiCode; overload;
function FG(const r, g, b : byte) : IAnsiCode; overload;
function BG(const color : byte)   : IAnsiCode; overload;
function BG(const r, g, b : byte) : IAnsiCode; overload;

function Codify(const codes : array of IAnsiCode) : string;
function Ansify(const codes : array of IAnsiCode; const msg : string) : string;


implementation
const
    ANSI_SEPARATOR : char   = ';';
    ANSI_BEGIN     : string = #27'[';
    ANSI_END       : char   = 'm';
    VALID_ANSI_COLOR_CODES : array of byte = (38, 48);

var
    _FG : IAnsiCode;
    _BG : IAnsiCode;


operator in (val : byte; arr : array of byte) Res : boolean;
var elem : byte;
begin
    Res := false;
    for elem in arr do
        if val = elem then begin
            Res := true;
            break;
        end;
end;


function Codify(const codes : array of IAnsiCode) : string;
var code : IAnsiCode;
begin
    // Result := '\x[';     // Only for development purposes
    Result := ANSI_BEGIN;
    for code in codes do begin
        Result += code.AsString;
        Result += ANSI_SEPARATOR;
    end;
    Delete(Result, Length(Result), 1);
    Result += ANSI_END;
end;


function Ansify(const codes : array of IAnsiCode; const msg : string) : string;
begin
    Result := Codify(codes) + msg + Codify([RESET]);
end;


function FG(const color : byte) : IAnsiCode;
begin
    Result := _FG.WithColor(color);
end;


function FG(const r, g, b : byte) : IAnsiCode;
begin
    Result := _FG.WithColor(r, g, b);
end;


function BG(const color : byte) : IAnsiCode;
begin
    Result := _BG.WithColor(color);
end;


function BG(const r, g, b : byte) : IAnsiCode;
begin
    Result := _BG.WithColor(r, g, b);
end;


constructor TAnsiCode.Create(const code : byte);
begin
    self.vHasColor := code in VALID_ANSI_COLOR_CODES;
    self.WithCode(code);
end;


class function TAnsiCode.New(const code : byte) : IAnsiCode;
begin
    Result := TAnsiCode.Create(code);
end;


function TAnsiCode.WithCode(const code : byte) : IAnsiCode;
begin
    self.vCode := code;
    self.vString := IntToStr(code);
    Result := self;
end;


function TAnsiCode.WithColor(const color : byte) : IAnsiCode; overload;
begin
    with TAnsiColor.New(color) do
        self.vString := IntToStr(self.vCode) + ANSI_SEPARATOR + AsString;
    Result := self;
end;


function TAnsiCode.WithColor(const r, g, b : byte) : IAnsiCode; overload;
begin
    with TAnsiColor.New(r, g, b) do
        self.vString := IntToStr(self.vCode) + ANSI_SEPARATOR + AsString;
    Result := self;
end;


function TAnsiCode.AsString : string;
begin
    Result := self.vString;
end;


function TAnsiCode.AsByte : byte;
begin
    Result := self.vCode;
end;


constructor TAnsiColor.Create(const color : byte);
begin
    self.vColor.mode  := AnsiColorStd;
    self.vColor.color := color;
    self.vString      += '5' + ANSI_SEPARATOR + IntToStr(color);
end;


constructor TAnsiColor.Create(const r, g, b : byte);
begin
    self.vColor.mode := AnsiColorRGB;
    self.vColor.r    := r;
    self.vColor.g    := g;
    self.vColor.b    := b;
    self.vString     += '2' + ANSI_SEPARATOR + IntToStr(r) + ANSI_SEPARATOR + IntToStr(g) + ANSI_SEPARATOR + IntToStr(b);
end;


class function TAnsiColor.New(const color : byte) : IAnsiColor;
begin
    Result := TAnsiColor.Create(color);
end;


class function TAnsiColor.New(const r, g, b : byte) : IAnsiColor;
begin
    Result := TAnsiColor.Create(r, g, b);
end;


function TAnsiColor.AsString : string;
begin
    Result := self.vString;
end;


function TAnsiColor.ColorMode : TAnsiColorEnum;
begin
    Result := self.vColor.mode;
end;


function TAnsiColor.AsColor : TAnsiColorRec;
begin
    Result := self.vColor;
end;




initialization
RESET                       := TAnsiCode.New(0);
BOLD                        := TAnsiCode.New(1);
FAINT                       := TAnsiCode.New(2);
ITALIC                      := TAnsiCode.New(3);
UNDERLINE                   := TAnsiCode.New(4);
BLINK_SLOW                  := TAnsiCode.New(5);
BLINK_RAPID                 := TAnsiCode.New(6);
REVERSE                     := TAnsiCode.New(7);
CONCEAL                     := TAnsiCode.New(8);
CROSSOUT                    := TAnsiCode.New(9);
FONT_PRIMARY                := TAnsiCode.New(10);
FONT_ALTERNATE_1            := TAnsiCode.New(11);
FONT_ALTERNATE_2            := TAnsiCode.New(12);
FONT_ALTERNATE_3            := TAnsiCode.New(13);
FONT_ALTERNATE_4            := TAnsiCode.New(14);
FONT_ALTERNATE_5            := TAnsiCode.New(15);
FONT_ALTERNATE_6            := TAnsiCode.New(16);
FONT_ALTERNATE_7            := TAnsiCode.New(17);
FONT_ALTERNATE_8            := TAnsiCode.New(18);
FONT_ALTERNATE_9            := TAnsiCode.New(19);
FRAKTUR                     := TAnsiCode.New(20);
BOLD_OFF                    := TAnsiCode.New(21);
UNDERLINE_DOUBLE            := TAnsiCode.New(21);
COLOR_NORMAL                := TAnsiCode.New(22);
ITALIC_OFF                  := TAnsiCode.New(23);
FRAKTUR_OFF                 := TAnsiCode.New(23);
UNDERLINE_OFF               := TAnsiCode.New(24);
BLINK_OFF                   := TAnsiCode.New(25);
INVERSE_OFF                 := TAnsiCode.New(27);
REVEAL                      := TAnsiCode.New(28);
CROSSOUT_OFF                := TAnsiCode.New(29);
FG_BLACK                    := TAnsiCode.New(30);
FG_RED                      := TAnsiCode.New(31);
FG_GREEN                    := TAnsiCode.New(32);
FG_YELLOW                   := TAnsiCode.New(33);
FG_BLUE                     := TAnsiCode.New(34);
FG_MAGENTA                  := TAnsiCode.New(35);
FG_CYAN                     := TAnsiCode.New(36);
FG_WHITE                    := TAnsiCode.New(37);
FG_DEFAULT                  := TAnsiCode.New(39);
BG_BLACK                    := TAnsiCode.New(40);
BG_RED                      := TAnsiCode.New(41);
BG_GREEN                    := TAnsiCode.New(42);
BG_YELLOW                   := TAnsiCode.New(43);
BG_BLUE                     := TAnsiCode.New(44);
BG_MAGENTA                  := TAnsiCode.New(45);
BG_CYAN                     := TAnsiCode.New(46);
BG_WHITE                    := TAnsiCode.New(47);
BG_DEFAULT                  := TAnsiCode.New(49);
FRAME                       := TAnsiCode.New(51);
ENCIRCLE                    := TAnsiCode.New(52);
OVERLINE                    := TAnsiCode.New(53);
FRAME_OFF                   := TAnsiCode.New(54);
ENCIRCLE_OFF                := TAnsiCode.New(54);
OVERLINE_OFF                := TAnsiCode.New(55);
IDEOGRAM_UNDERLINE          := TAnsiCode.New(60);
IDEOGRAM_UNDERLINE_DOUBLE   := TAnsiCode.New(61);
IDEOGRAM_OVERLINE           := TAnsiCode.New(62);
IDEOGRAM_OVERLINE_DOUBLE    := TAnsiCode.New(63);
IDEOGRAM_STRESSMARK         := TAnsiCode.New(64);
IDEOGRAM_OFF                := TAnsiCode.New(65);
FG_BRIGHT_BLACK             := TAnsiCode.New(90);
FG_BRIGHT_RED               := TAnsiCode.New(91);
FG_BRIGHT_GREEN             := TAnsiCode.New(92);
FG_BRIGHT_YELLOW            := TAnsiCode.New(93);
FG_BRIGHT_BLUE              := TAnsiCode.New(94);
FG_BRIGHT_MAGENTA           := TAnsiCode.New(95);
FG_BRIGHT_CYAN              := TAnsiCode.New(96);
FG_BRIGHT_WHITE             := TAnsiCode.New(97);
BG_BRIGHT_BLACK             := TAnsiCode.New(100);
BG_BRIGHT_RED               := TAnsiCode.New(101);
BG_BRIGHT_GREEN             := TAnsiCode.New(102);
BG_BRIGHT_YELLOW            := TAnsiCode.New(103);
BG_BRIGHT_BLUE              := TAnsiCode.New(104);
BG_BRIGHT_MAGENTA           := TAnsiCode.New(105);
BG_BRIGHT_CYAN              := TAnsiCode.New(106);
BG_BRIGHT_WHITE             := TAnsiCode.New(107);

_FG := TAnsiCode.New(38);
_BG := TAnsiCode.New(48);


finalization


end.