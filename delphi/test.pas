{$mode delphi}
program test;
uses escape, heaptrc;

begin
    writeln( Ansify([BOLD, FG_RED], 'Fatality!') );
    writeln( Ansify([ITALIC], 'Color Test, Standard') );
    writeln( Ansify([BOLD, BG(100, 50, 9)], 'Color Test, RGB') );
    DumpHeap;
end.