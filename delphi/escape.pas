{$mode objfpc}
unit escape;

interface
uses classes, sysutils;

type IAnsiCode = interface
        procedure SetCode(const code : byte);
        function GetCodeAsString() : string;
        function GetCodeAsByte() : byte;
        property AsString : string read GetCodeAsString;
        property AsByte : byte read GetCodeAsByte write SetCode;
    end;

type IAnsiColor = interface
        function Get : IAnsiCode;
    end;

type AnsiCode = class(TInterfacedObject, IAnsiCode)
    private
        var _str  : string;
        var _code : byte;
        procedure SetCode(const code : byte);
        function GetCodeAsString() : string;
        function GetCodeAsByte() : byte;
    public
        // property AsString : string read GetCodeAsString;
        // property AsByte : byte read GetCodeAsByte write SetCode;
    end;

type AnsiColorStd = class(TInterfacedObject, IAnsiCode, IAnsiColor)
    private
        var _color : byte;
    public
        function Get : IAnsiCode;
        procedure SetCode(const code, color : byte); overload;
    end;




type Ansi = class(TObject)

    end;


implementation

procedure AnsiCode.SetCode(const code : byte);
begin
    self._code := code;
    self._str  := IntToStr(code);
end;

function AnsiCode.GetCodeAsByte : byte;
begin
    GetCodeAsByte := self._code;
end;

function AnsiCode.GetCodeAsString : string;
begin
    GetCodeAsString := self._str;
end;

procedure SetCode(const code, color : byte); overload;



initialization

finalization

end.