{$mode delphi}
unit escape;

interface
uses classes, sysutils;

type
    TAnsiColorEnum = (AnsiColorStd, AnsiColorRGB);

    TAnsiColorRec = record
        case mode : TAnsiColorEnum of
            AnsiColorStd: (color : byte);
            AnsiColorRGB: (r, g, b : byte);
    end;

    IAnsiCode = interface['{eeb511e3-0dbe-4fec-a72f-473f8bf8a8de}']
        function AsString : string;
        function AsByte : byte;
    end;

    TAnsiCode = class(TInterfacedObject, IAnsiCode)
    private
        vCode   : byte;
        vString : string;
        function WithCode(const code : byte) : IAnsiCode;
    public
        constructor Create(const code : byte);
        function AsString : string;
        function AsByte : byte;
    end;


    TAnsiColor = class(TInterfacedObject, IAnsiCode)
    private
        vCode   : byte;
        vString : string;
        vColor  : TAnsiColorRec;
        function WithCode(const code : byte) : IAnsiCode; overload;
        procedure Reset;
    public
        constructor Create(const code : byte);
        function AsString : string;
        function AsByte : byte;
        function WithColor(const color : byte) : IAnsiCode; overload;
        function WithColor(const r, g, b : byte) : IAnsiCode; overload;
        function ColorMode : TAnsiColorEnum;
        function AsColor : TAnsiColorRec;
    end;


var RESET                       : TAnsiCode;
    BOLD                        : TAnsiCode;
    FAINT                       : TAnsiCode;
    ITALIC                      : TAnsiCode;
    UNDERLINE                   : TAnsiCode;
    BLINK_SLOW                  : TAnsiCode;
    BLINK_RAPID                 : TAnsiCode;
    REVERSE                     : TAnsiCode;
    CONCEAL                     : TAnsiCode;
    CROSSOUT                    : TAnsiCode;
    FONT_PRIMARY                : TAnsiCode;
    FONT_ALTERNATE_1            : TAnsiCode;
    FONT_ALTERNATE_2            : TAnsiCode;
    FONT_ALTERNATE_3            : TAnsiCode;
    FONT_ALTERNATE_4            : TAnsiCode;
    FONT_ALTERNATE_5            : TAnsiCode;
    FONT_ALTERNATE_6            : TAnsiCode;
    FONT_ALTERNATE_7            : TAnsiCode;
    FONT_ALTERNATE_8            : TAnsiCode;
    FONT_ALTERNATE_9            : TAnsiCode;
    FRAKTUR                     : TAnsiCode;
    BOLD_OFF                    : TAnsiCode;
    UNDERLINE_DOUBLE            : TAnsiCode;
    COLOR_NORMAL                : TAnsiCode;
    ITALIC_OFF                  : TAnsiCode;
    FRAKTUR_OFF                 : TAnsiCode;
    UNDERLINE_OFF               : TAnsiCode;
    BLINK_OFF                   : TAnsiCode;
    INVERSE_OFF                 : TAnsiCode;
    REVEAL                      : TAnsiCode;
    CROSSOUT_OFF                : TAnsiCode;
    FG_BLACK                    : TAnsiCode;
    FG_RED                      : TAnsiCode;
    FG_GREEN                    : TAnsiCode;
    FG_YELLOW                   : TAnsiCode;
    FG_BLUE                     : TAnsiCode;
    FG_MAGENTA                  : TAnsiCode;
    FG_CYAN                     : TAnsiCode;
    FG_WHITE                    : TAnsiCode;
    FG_DEFAULT                  : TAnsiCode;
    BG_BLACK                    : TAnsiCode;
    BG_RED                      : TAnsiCode;
    BG_GREEN                    : TAnsiCode;
    BG_YELLOW                   : TAnsiCode;
    BG_BLUE                     : TAnsiCode;
    BG_MAGENTA                  : TAnsiCode;
    BG_CYAN                     : TAnsiCode;
    BG_WHITE                    : TAnsiCode;
    BG_DEFAULT                  : TAnsiCode;
    FRAME                       : TAnsiCode;
    ENCIRCLE                    : TAnsiCode;
    OVERLINE                    : TAnsiCode;
    FRAME_OFF                   : TAnsiCode;
    ENCIRCLE_OFF                : TAnsiCode;
    OVERLINE_OFF                : TAnsiCode;
    IDEOGRAM_UNDERLINE          : TAnsiCode;
    IDEOGRAM_UNDERLINE_DOUBLE   : TAnsiCode;
    IDEOGRAM_OVERLINE           : TAnsiCode;
    IDEOGRAM_OVERLINE_DOUBLE    : TAnsiCode;
    IDEOGRAM_STRESSMARK         : TAnsiCode;
    IDEOGRAM_OFF                : TAnsiCode;
    FG_BRIGHT_BLACK             : TAnsiCode;
    FG_BRIGHT_RED               : TAnsiCode;
    FG_BRIGHT_GREEN             : TAnsiCode;
    FG_BRIGHT_YELLOW            : TAnsiCode;
    FG_BRIGHT_BLUE              : TAnsiCode;
    FG_BRIGHT_MAGENTA           : TAnsiCode;
    FG_BRIGHT_CYAN              : TAnsiCode;
    FG_BRIGHT_WHITE             : TAnsiCode;
    BG_BRIGHT_BLACK             : TAnsiCode;
    BG_BRIGHT_RED               : TAnsiCode;
    BG_BRIGHT_GREEN             : TAnsiCode;
    BG_BRIGHT_YELLOW            : TAnsiCode;
    BG_BRIGHT_BLUE              : TAnsiCode;
    BG_BRIGHT_MAGENTA           : TAnsiCode;
    BG_BRIGHT_CYAN              : TAnsiCode;
    BG_BRIGHT_WHITE             : TAnsiCode;

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

var
    _FG : TAnsiColor;
    _BG : TAnsiColor;

function Codify(const codes : array of IAnsiCode) : string;
var code : IAnsiCode;
begin
    Result := '\x[';
    // Result := ANSI_BEGIN;
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
    self.WithCode(code);
end;

function TAnsiCode.WithCode(const code : byte) : IAnsiCode;
begin
    self.vCode := code;
    self.vString := IntToStr(code);
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


constructor TAnsiColor.Create(const code : byte);
begin
    self.WithCode(code);
end;


function TAnsiColor.WithCode(const code : byte) : IAnsiCode;
begin
    self.vCode := code;
    self.Reset();
    Result := self;
end;

procedure TAnsiColor.Reset;
begin
    self.vString := IntToStr(self.vCode);
end;


function TAnsiColor.AsString : string;
begin
    Result := self.vString;
end;


function TAnsiColor.AsByte : byte;
begin
    Result := self.vCode;
end;


function TAnsiColor.WithColor(const color : byte) : IAnsiCode; overload;
begin
    self.Reset();
    self.vColor.mode  := AnsiColorStd;
    self.vColor.color := color;
    self.vString      += ANSI_SEPARATOR + IntToStr(color);
    Result := self;
end;


function TAnsiColor.WithColor(const r, g, b : byte) : IAnsiCode; overload;
begin
    self.Reset();
    self.vColor.mode := AnsiColorRGB;
    self.vColor.r    := r;
    self.vColor.g    := g;
    self.vColor.b    := b;
    self.vString     += ANSI_SEPARATOR + IntToStr(r) + ANSI_SEPARATOR + IntToStr(g) + ANSI_SEPARATOR + IntToStr(b);
    Result := self;
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
RESET                       := TAnsiCode.Create(0);
BOLD                        := TAnsiCode.Create(1);
FAINT                       := TAnsiCode.Create(2);
ITALIC                      := TAnsiCode.Create(3);
UNDERLINE                   := TAnsiCode.Create(4);
BLINK_SLOW                  := TAnsiCode.Create(5);
BLINK_RAPID                 := TAnsiCode.Create(6);
REVERSE                     := TAnsiCode.Create(7);
CONCEAL                     := TAnsiCode.Create(8);
CROSSOUT                    := TAnsiCode.Create(9);
FONT_PRIMARY                := TAnsiCode.Create(10);
FONT_ALTERNATE_1            := TAnsiCode.Create(11);
FONT_ALTERNATE_2            := TAnsiCode.Create(12);
FONT_ALTERNATE_3            := TAnsiCode.Create(13);
FONT_ALTERNATE_4            := TAnsiCode.Create(14);
FONT_ALTERNATE_5            := TAnsiCode.Create(15);
FONT_ALTERNATE_6            := TAnsiCode.Create(16);
FONT_ALTERNATE_7            := TAnsiCode.Create(17);
FONT_ALTERNATE_8            := TAnsiCode.Create(18);
FONT_ALTERNATE_9            := TAnsiCode.Create(19);
FRAKTUR                     := TAnsiCode.Create(20);
BOLD_OFF                    := TAnsiCode.Create(21);
UNDERLINE_DOUBLE            := TAnsiCode.Create(21);
COLOR_NORMAL                := TAnsiCode.Create(22);
ITALIC_OFF                  := TAnsiCode.Create(23);
FRAKTUR_OFF                 := TAnsiCode.Create(23);
UNDERLINE_OFF               := TAnsiCode.Create(24);
BLINK_OFF                   := TAnsiCode.Create(25);
INVERSE_OFF                 := TAnsiCode.Create(27);
REVEAL                      := TAnsiCode.Create(28);
CROSSOUT_OFF                := TAnsiCode.Create(29);
FG_BLACK                    := TAnsiCode.Create(30);
FG_RED                      := TAnsiCode.Create(31);
FG_GREEN                    := TAnsiCode.Create(32);
FG_YELLOW                   := TAnsiCode.Create(33);
FG_BLUE                     := TAnsiCode.Create(34);
FG_MAGENTA                  := TAnsiCode.Create(35);
FG_CYAN                     := TAnsiCode.Create(36);
FG_WHITE                    := TAnsiCode.Create(37);
FG_DEFAULT                  := TAnsiCode.Create(39);
BG_BLACK                    := TAnsiCode.Create(40);
BG_RED                      := TAnsiCode.Create(41);
BG_GREEN                    := TAnsiCode.Create(42);
BG_YELLOW                   := TAnsiCode.Create(43);
BG_BLUE                     := TAnsiCode.Create(44);
BG_MAGENTA                  := TAnsiCode.Create(45);
BG_CYAN                     := TAnsiCode.Create(46);
BG_WHITE                    := TAnsiCode.Create(47);
BG_DEFAULT                  := TAnsiCode.Create(49);
FRAME                       := TAnsiCode.Create(51);
ENCIRCLE                    := TAnsiCode.Create(52);
OVERLINE                    := TAnsiCode.Create(53);
FRAME_OFF                   := TAnsiCode.Create(54);
ENCIRCLE_OFF                := TAnsiCode.Create(54);
OVERLINE_OFF                := TAnsiCode.Create(55);
IDEOGRAM_UNDERLINE          := TAnsiCode.Create(60);
IDEOGRAM_UNDERLINE_DOUBLE   := TAnsiCode.Create(61);
IDEOGRAM_OVERLINE           := TAnsiCode.Create(62);
IDEOGRAM_OVERLINE_DOUBLE    := TAnsiCode.Create(63);
IDEOGRAM_STRESSMARK         := TAnsiCode.Create(64);
IDEOGRAM_OFF                := TAnsiCode.Create(65);
FG_BRIGHT_BLACK             := TAnsiCode.Create(90);
FG_BRIGHT_RED               := TAnsiCode.Create(91);
FG_BRIGHT_GREEN             := TAnsiCode.Create(92);
FG_BRIGHT_YELLOW            := TAnsiCode.Create(93);
FG_BRIGHT_BLUE              := TAnsiCode.Create(94);
FG_BRIGHT_MAGENTA           := TAnsiCode.Create(95);
FG_BRIGHT_CYAN              := TAnsiCode.Create(96);
FG_BRIGHT_WHITE             := TAnsiCode.Create(97);
BG_BRIGHT_BLACK             := TAnsiCode.Create(100);
BG_BRIGHT_RED               := TAnsiCode.Create(101);
BG_BRIGHT_GREEN             := TAnsiCode.Create(102);
BG_BRIGHT_YELLOW            := TAnsiCode.Create(103);
BG_BRIGHT_BLUE              := TAnsiCode.Create(104);
BG_BRIGHT_MAGENTA           := TAnsiCode.Create(105);
BG_BRIGHT_CYAN              := TAnsiCode.Create(106);
BG_BRIGHT_WHITE             := TAnsiCode.Create(107);

_FG := TAnsiColor.Create(38);
_BG := TAnsiColor.Create(48);


finalization


end.