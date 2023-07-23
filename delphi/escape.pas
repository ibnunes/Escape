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

    IAnsiCode = interface
        function SetCode(const code : byte) : IAnsiCode;
        function AsString : string;
        function AsByte : byte;
    end;

    IAnsiColor = interface(IAnsiCode)
        function SetColor(const color : byte) : IAnsiColor; overload;
        function SetColor(const r, g, b : byte) : IAnsiColor; overload;
        function ColorMode : TAnsiColorEnum;
        function AsColor : TAnsiColorRec;
    end;

    TAnsiCode = class(TInterfacedObject, IAnsiCode)
    private
        vCode   : byte;
        vString : string;
    public
        class function New(const code : byte) : IAnsiCode;
        function SetCode(const code : byte) : IAnsiCode;
        function AsString : string;
        function AsByte : byte;
    end;


    TAnsiColor = class(TInterfacedObject, IAnsiColor)
    private
        vCode   : byte;
        vString : string;
        vColor : TAnsiColorRec;
    public
        class function New(const code : byte; const color : byte) : IAnsiColor; overload;
        class function New(const code : byte; const r, g, b : byte) : IAnsiColor; overload;
        function SetCode(const code : byte) : IAnsiCode; overload;
        function SetCode(const code : byte) : IAnsiColor; overload;
        function AsString : string;
        function AsByte : byte;
        function SetColor(const color : byte) : IAnsiColor; overload;
        function SetColor(const r, g, b : byte) : IAnsiColor; overload;
        function ColorMode : TAnsiColorEnum;
        function AsColor : TAnsiColorRec;
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


function FG(const color : byte)   : IAnsiColor; overload;
function FG(const r, g, b : byte) : IAnsiColor; overload;
function BG(const color : byte)   : IAnsiColor; overload;
function BG(const r, g, b : byte) : IAnsiColor; overload;




implementation

function FG(const color : byte) : IAnsiColor;
begin
    Result := TAnsiColor.New(38, color);
end;


function FG(const r, g, b : byte) : IAnsiColor;
begin
    Result := TAnsiColor.New(38, r, g, b);
end;


function BG(const color : byte) : IAnsiColor;
begin
    Result := TAnsiColor.New(48, color);
end;


function BG(const r, g, b : byte) : IAnsiColor;
begin
    Result := TAnsiColor.New(48, r, g, b);
end;


const
    ANSI_SEPARATOR : char   = ';';
    ANSI_BEGIN     : string = #27'[';
    ANSI_END       : char   = 'm';

class function TAnsiCode.New(const code : byte) : IAnsiCode;
begin
    New := Create.SetCode(code);
end;

function TAnsiCode.SetCode(const code : byte) : IAnsiCode;
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


class function TAnsiColor.New(const code : byte; const color : byte) : IAnsiColor;
begin
    New := IAnsiColor(Create.SetCode(code)).SetColor(color);
end;


class function TAnsiColor.New(const code : byte; const r, g, b : byte) : IAnsiColor;
begin
    New := IAnsiColor(Create.SetCode(code)).SetColor(r, g, b);
end;


function TAnsiColor.SetCode(const code : byte) : IAnsiCode;
var dummy : IAnsiCode;
begin
    dummy  := TAnsiCode.New(code);
    Result := IAnsiCode(dummy);
end;


function TAnsiColor.SetCode(const code : byte) : IAnsiColor;
begin
    self.vCode   := code;
    self.vString := IntToStr(code);
    Result       := self;
end;


function TAnsiColor.AsString : string;
begin
    Result := self.vString;
end;


function TAnsiColor.AsByte : byte;
begin
    Result := self.vCode;
end;


function TAnsiColor.SetColor(const color : byte) : IAnsiColor; overload;
begin
    self.vColor.mode  := AnsiColorStd;
    self.vColor.color := color;
    self.vString      += ANSI_SEPARATOR + IntToStr(color);
    Result := self;
end;


function TAnsiColor.SetColor(const r, g, b : byte) : IAnsiColor; overload;
begin
    self.vColor.mode := AnsiColorStd;
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


finalization

end.