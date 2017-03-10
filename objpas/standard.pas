unit Standard;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Vector;

const PI = 3.14159265358979323846264338327950288;
      PI2 = 6.28318530717958647692528676655900577;
      PID2 = 1.57079632679489661923132169163975144;
      PISQ = 9.86960440108935861883449099987615114;

function TAbs(para: Tvec2): Tvec2;
function TAbs(para2: Tvec3): Tvec3;

procedure Register;

function ClampLength(para: Tvec2; maxLength: real): Tvec2;
function ClampLength(para: Tvec3; maxLength: real): Tvec3;

function ToRadians(Degrees: real): real;
function ToDegrees(Radians: real): real;

function Max(para, para1: Tvec2): Tvec2;
function Max(para, para1: Tvec3): Tvec3;
function Min(para, para1: Tvec2): Tvec2;
function Min(para, para1: Tvec3): Tvec3;
function Lerp(a, b: Tvec2; t: real): Tvec2;
function Lerp(a,b: Tvec3; t:real): Tvec3;

implementation

       procedure Register;
       begin

       end;

     function ToRadians(Degrees: real): real;
     begin
          ToRadians:= degrees / 180 * PI;
     end;

     function ToDegrees(Radians: real): real;
     begin
          ToDegrees:= Radians / PI * 180;
     end;

     function Lerp(a, b: Tvec2; t: real): Tvec2;
     begin
          Lerp:= Tvec2.Create;
          Lerp:= a* (1-t) + b*t;
     end;

     function Lerp(a,b: Tvec3; t:real): Tvec3;
     begin
          Lerp:= Tvec3.Create;
          Lerp:= a* (1-t) + b*t;
     end;

     function TAbs(para: Tvec2): Tvec2;
     begin
          TAbs := Tvec2.Create;
          TAbs.X := Abs(para.X);
          TAbs.Y := Abs(para.Y);
     end;

     function TAbs(para2: Tvec3): Tvec3;
     begin
          TAbs := Tvec3.Create;
          TAbs.X := Abs(para2.X);
          TAbs.Y := Abs(para2.Y);
          TAbs.Z := Abs(para2.Z);
     end;

     function ClampLength(para: Tvec2; maxLength: real): Tvec2;
     begin
          if (para.Length > maxLength) then exit(para);
     end;

     function ClampLength(para: Tvec3; maxLength: real): Tvec3;
     begin
          if (para.Length > maxLength) then exit(para);
     end;

     function Max(para, para1: Tvec2): Tvec2;
     begin
          Max:= Tvec2.Create;
          if (para.X> para1.X) then Max.X:= para.X else Max.X:= para1.X;
          if (para.Y> para1.Y) then Max.Y:= para.Y else Max.Y:= para1.Y;
     end;

     function Max(para, para1: Tvec3): Tvec3;
     begin
          Max:= Tvec3.Create;
          if (para.X> para1.X) then Max.X:= para.X else Max.X:= para1.X;
          if (para.Y> para1.Y) then Max.Y:= para.Y else Max.Y:= para1.Y;
     end;

     function Min(para, para1: Tvec2): Tvec2;
     begin
          Min:= Tvec2.Create;
          if (para.X< para1.X) then Min.X:= para.X else Min.X:= para1.X;
          if (para.Y< para1.Y) then Min.Y:= para.Y else Min.Y:= para1.Y;
     end;

     function Min(para, para1: Tvec3): Tvec3;
     begin
          Min:= Tvec3.Create;
          if (para.X< para1.X) then Min.X:= para.X else Min.X:= para1.X;
          if (para.Y< para1.Y) then Min.Y:= para.Y else Min.Y:= para1.Y;
     end;



end.

