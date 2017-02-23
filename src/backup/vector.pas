//Warning: I can't find any document about template function
//Therefore, i can't solve Dot func duplication

unit Vector;

{$mode objfpc}{$H+}{$M+}
{$MACRO ON}

{$IFDEF WINDOWS}
{$DEFINE CALLBACK := stdcall}
{$ENDIF}

interface

uses
  Classes, SysUtils, Math;

type

  vec2 = interface
  ['{2EFAD1BB-0B41-469A-9F67-9DCFFDC47808}']
      function Length: real;
      function Normalize: vec2;

      function GetX: real; procedure SetX(tx: real); function GetY: real;
      procedure SetY(ty: real);

      property X: real read GetX write SetX;
      property Y: real read GetY write SetY;

  end;

  vec3 = interface
  ['{021806EB-651E-409A-A98E-93B7B551D5A8}']
      function Length: real;
      function Normalize: vec2;

      function GetX: real; procedure SetX(tx: real); function GetY: real;
      procedure SetY(ty: real);

      property X: real read GetX write SetX;
      property Y: real read GetY write SetY;

  end;

  Tvec2 = class(TInterfacedObject, vec2)
    private
      var hx,hy: real;

      function GetX: real; procedure SetX(tx: real); function GetY: real;
      procedure SetY(ty: real);

    public
      constructor Create(tx: real = 0; ty: real = 0);

      function Length: real;
      function Normalize: vec2;


      property X: real read GetX write SetX;
      property Y: real read GetY write SetY;

  end;

  Tvec3 = class
    public
      constructor Create(tx: real = 0; ty: real = 0; tz: real = 0);
      constructor Create(t1: Tvec2; t2: real = 0);

      function Length: real;
      function Normalihze: Tvec3;

      var hx,hy,hz: real;

  end;

  function Dot(para1, para2: vec2): real; CALLBACK;
  function Angle(para1, para2: vec2): real; CALLBACK;
  function vec2f(x: float =0; y: float = 0): vec2; CALLBACK;

  function Dot(para1, para2: Tvec3): real;
  function Angle(para1, para2: Tvec3): real;
  function Cross(para1, para2: Tvec3): Tvec3;

implementation

     function vec2f(x: float =0; y: float = 0): vec2; CALLBACK;
     begin
              vec2f:= TVec2.Create(x,y);
     end;

     function Tvec2.GetX: real;
     begin
          GetX := hx;
     end;

     procedure Tvec2.SetX(tx: real);
     begin
          hx := tx;
     end;

     function Tvec2.GetY: real;
     begin
          GetY := hy;
     end;

     procedure Tvec2.SetY(ty: real);
     begin
          hy := ty;
     end;


     constructor Tvec2.Create(tx, ty :real);
     begin
                 hx:= tx;
                 hy:= ty;
     end;

     operator + (para1, para2: vec2) add: vec2;
     begin
           add.X := para1.X + para2.X;
           add.Y := para1.Y + para2.Y;
     end;

     operator - (para1, para2: vec2) sub: vec2;
     begin
           sub.X := para1.X - para2.X;
           sub.Y := para1.Y - para2.Y;
     end;

     operator * (para1, para2: vec2) mul: vec2;
     begin
           mul.X := para1.X * para2.X;
           mul.Y := para1.Y * para2.Y;
     end;

     operator / (para1, para2: vec2) divide: vec2;
     begin
           divide.X := para1.X / para2.X;
           divide.Y := para1.Y / para2.Y;
     end;

     operator + (para1:vec2 ; para2: real) addf: vec2;
     begin
           addf.X := para1.X + para2;
           addf.Y := para1.Y + para2;
     end;

     operator - (para1:vec2 ; para2: real) subf: vec2;
     begin
           subf.X := para1.X - para2;
           subf.Y := para1.Y - para2;
     end;

     operator * (para1:vec2 ; para2: real) mulf: vec2;
     begin
           mulf.X := para1.X * para2;
           mulf.Y := para1.Y * para2;
     end;

     operator / (para1:vec2 ; para2: real) dividef: vec2;
     begin
           dividef.X := para1.X / para2;
           dividef.Y := para1.Y / para2;
     end;

     function Tvec2.Length: real;
     begin
           Length:= Sqrt(Power(hx,2)+ Power(hy,2));
     end;

     function Tvec2.Normalize: vec2;
     var tmp: real;
     begin
           tmp:= Sqrt(Power(hx,2)+ Power(hy,2));
           Normalize:= self / tmp;
     end;

     function Dot(para1, para2: vec2): real; CALLBACK;
     begin
          Dot:= para1.X * para2.X + para1.Y * para2.Y;
     end;

     function Angle(para1, para2: vec2): real; CALLBACK;
     var tmp1, tmp2: vec2;
     begin
          tmp1 := para1.Normalize;
          tmp2 := para2.Normalize;

          Angle:= Dot(tmp1, tmp2);

          Angle:= arccos(Angle);
     end;

     constructor Tvec3.Create(tx, ty, tz :real);
     begin
            hx:= tx; hy:= ty;
            hz:= tz;
     end;

     constructor Tvec3.Create(t1: Tvec2; t2: real);
     begin
          hx:=t1.hx; hy:=t1.hy; hz:= t2;
     end;

       operator + (para1, para2: Tvec3) add: Tvec3;
     begin
           add.hx := para1.hx + para2.hx;
           add.hy := para1.hy + para2.hy;
           add.hz := para1.hz + para2.hz;
     end;

     operator - (para1, para2: Tvec3) sub: Tvec3;
     begin
           sub.hx := para1.hx - para2.hx;
           sub.hy := para1.hy - para2.hy;
           sub.hz := para1.hz - para2.hz;
     end;

     operator * (para1, para2: Tvec3) mul: Tvec3;
     begin
           mul.hx := para1.hx * para2.hx;
           mul.hy := para1.hy * para2.hy;
           mul.hz := para1.hz * para2.hz;
     end;

     operator / (para1, para2: Tvec3) divide: Tvec3;
     begin
           divide.hx := para1.hx / para2.hx;
           divide.hy := para1.hy / para2.hy;
           divide.hz := para1.hz / para2.hz;
     end;

     operator + (para1:Tvec3 ; para2: real) addf: Tvec3;
     begin
           addf.hx := para1.hx + para2;
           addf.hy := para1.hy + para2;
           addf.hz := para1.hz + para2;
     end;

     operator - (para1:Tvec3 ; para2: real) subf: Tvec3;
     begin
           subf.hx := para1.hx - para2;
           subf.hy := para1.hy - para2;
           subf.hz := para1.hz - para2;
     end;

     operator * (para1:Tvec3 ; para2: real) mulf: Tvec3;
     begin
           mulf.hx := para1.hx * para2;
           mulf.hy := para1.hy * para2;
           mulf.hz := para1.hz * para2;
     end;

     operator / (para1:Tvec3 ; para2: real) dividef: Tvec3;
     begin
           dividef.hx := para1.hx / para2;
           dividef.hy := para1.hy / para2;
           dividef.hz := para1.hz / para2;
     end;


     function Tvec3.Length: real;
     begin
          Length:= Sqrt(Power(hx,2)+ Power(hy,2) + Power(hz,2));
     end;

     function Tvec3.Normalihze: Tvec3;
     var tmp: real;
     begin
           tmp:= Sqrt(Power(hx,2)+ Power(hy,2) + Power(hz,2));
           Normalihze:= self / tmp;
     end;

     function Angle(para1, para2: Tvec3): real;
     var tmp1, tmp2: Tvec3;
     begin
          tmp1 := para1.Normalihze;
          tmp2 := para2.Normalihze;

          Angle:= Dot(tmp1, tmp2);

          Angle:= arccos(Angle);
     end;

     function Dot(para1, para2: Tvec3): real;
     begin
              Dot := para1.hx * para2.hx + para1.hy + para2.hy + para1.hz * para2.hz;
     end;

     function Cross(para1, para2: Tvec3): Tvec3;
     begin
              Cross.hx := para1.hy * para2.hz - para1.hz * para2.hy;
              Cross.hy := para1.hz* para2.hx - para1.hx * para2.hz;
              Cross.hz := para1.hx * para2.hy - para1.hy * para2.hx;
     end;

end.

exports
       Dot(para1, para2: vec2): real name 'Dot2f';
       Angle(para1, para2: vec2): real name 'Angle2f';
       vec2f(x: real =0; y: float = 0): vec2 name 'TVec2';
end.

end.

