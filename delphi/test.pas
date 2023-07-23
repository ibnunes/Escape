{$mode delphi}
program test;
uses escape;

begin
    writeln( Ansify([BOLD, FG_RED], 'Fatality!') );
    writeln( Ansify([BOLD, FG(69)], 'Color Test, Standard') );
    writeln( Ansify([BOLD, BG(100, 50, 9)], 'Color Test, RGB') );
end.