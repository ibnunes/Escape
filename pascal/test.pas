{$mode objfpc}
//{$H+}
program test;
uses escape;

begin
    writeln( ansify([bold, fg_red], 'Fatality!') );
end.