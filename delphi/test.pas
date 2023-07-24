{$mode delphi}
program test;
uses escape;

begin
    writeln( Ansify([BOLD, FG_RED], 'Fatality!') );
    writeln( Ansify([ITALIC, FG(69)], 'Color Test, Standard') );
    writeln( Ansify([UNDERLINE, BG(100, 50, 9), ITALIC], 'Color Test, RGB') );
    writeln( Ansify([UNDERLINE, FG(9, 100, 50), ITALIC], 'Color Test, RGB') );
end.