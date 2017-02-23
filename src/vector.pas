//Warning: I can't find any document about template function
//Therefore, i can't solve Dot func duplication

unit Vector;

{$mode objfpc}{$H+}{$M+}

interface

uses Math, Classes;

type

  Tvec2 = class(TObject)
    private
      var hx,hy: real;

    public
      constructor Create(tx: real = 0; ty: real = 0);

      function Length: real;
      function Normalize: Tvec2;

      property X: real read hx write hx;
      property Y: real read hy write hy;

  end;

  Tvec3 = class
    public
      constructor Create(tx: real = 0; ty: real = 0; tz: real = 0);
      constructor Create(t1: Tvec2; t2: real = 0);

      function Length: real;
      function Normalize: Tvec3;

      var hx,hy,hz: real;

  end;

function Dot(para1, para2: Tvec2): real;
function Angle(para1, para2: Tvec2): real;

operator +(para1, para2: Tvec2) add: Tvec2;
operator -(para1, para2: Tvec2) sub: Tvec2;
operator *(para1, para2: Tvec2) mul: Tvec2;
operator /(para1, para2: Tvec2) divide: Tvec2;

operator +(para1: Tvec2; para2: real) addf: Tvec2;
operator -(para1: Tvec2; para2: real) subf: Tvec2;
operator *(para1: Tvec2; para2: real) mulf: Tvec2;
operator /(para1: Tvec2; para2: real) dividef: Tvec2;

operator +(para1, para2: Tvec2) add: Tvec2;
operator -(para1, para2: Tvec2) sub: Tvec2;
operator *(para1, para2: Tvec2) mul: Tvec2;
operator /(para1, para2: Tvec2) divide: Tvec2;

operator +(para1: Tvec2; para2: real) addf: Tvec2;
operator -(para1: Tvec2; para2: real) subf: Tvec2;
operator *(para1: Tvec2; para2: real) mulf: Tvec2;
operator /(para1: Tvec2; para2: real) dividef: Tvec2;

function Dot(para1, para2: Tvec3): real;
function Angle(para1, para2: Tvec3): real;
function Cross(para1, para2: Tvec3): Tvec3;

implementation

              function Tvec2f(x: float =0; y: float = 0): Tvec2;
              begin
                   Tvec2f:= Tvec2.Create(x,y);
              end;

              constructor Tvec2.Create(tx, ty :real);
              begin
                   hx:= tx;
                   hy:= ty;
              end;

              operator + (para1, para2: Tvec2) add: Tvec2;
              begin
                   add := Tvec2.Create;
                   add.X := para1.X + para2.X;
                   add.Y := para1.Y + para2.Y;
              end;

              operator - (para1, para2: Tvec2) sub: Tvec2;
              begin
                    sub := Tvec2.Create;
                    sub.X := para1.X - para2.X;
                    sub.Y := para1.Y - para2.Y;
              end;

              operator * (para1, para2: Tvec2) mul: Tvec2;
              begin
                   mul:= Tvec2.Create;
                   mul.X := para1.X * para2.X;
                   mul.Y := para1.Y * para2.Y;
              end;

              operator / (para1, para2: Tvec2) divide: Tvec2;
              begin
                    divide:= Tvec2.Create;
                    divide.X := para1.X / para2.X;
                    divide.Y := para1.Y / para2.Y;
              end;

              operator + (para1:Tvec2 ; para2: real) addf: Tvec2;
              begin
                   addf:= Tvec2.Create;
                   addf.X := para1.X + para2;
                   addf.Y := para1.Y + para2;
              end;

              operator - (para1:Tvec2 ; para2: real) subf: Tvec2;
              begin
                   subf:= Tvec2.Create;
                   subf.X := para1.X - para2;
                   subf.Y := para1.Y - para2;
              end;

              operator * (para1:Tvec2 ; para2: real) mulf: Tvec2;
              begin
                   mulf:= Tvec2.Create;
                   mulf.X := para1.X * para2;
                   mulf.Y := para1.Y * para2;
              end;

              operator / (para1:Tvec2 ; para2: real) dividef: Tvec2;
              begin
                   dividef := Tvec2.Create;
                   dividef.X := para1.X / para2;
                   dividef.Y := para1.Y / para2;
              end;

              function Tvec2.Length: real;
              begin
                   Length:= Sqrt(Power(hx,2)+ Power(hy,2));
              end;

              function Tvec2.Normalize: Tvec2;
              var tmp: real;
              begin
                   tmp:= Sqrt(Power(hx,2)+ Power(hy,2));
                   Normalize:= self / tmp;
              end;

              function Dot(para1, para2: Tvec2): real;
              begin
                        Dot:= para1.X * para2.X + para1.Y * para2.Y;
              end;

              function Angle(para1, para2: Tvec2): real;
              var tmp1, tmp2: Tvec2;
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

              function Tvec3.Normalize: Tvec3;
              var tmp: real;
              begin
                         tmp:= Sqrt(Power(hx,2)+ Power(hy,2) + Power(hz,2));
                         Normalize:= self / tmp;
              end;


              function Dot(para1, para2: Tvec3): real;
              begin
                            Dot := para1.hx * para2.hx + para1.hy + para2.hy + para1.hz * para2.hz;
              end;

              function Angle(para1, para2: Tvec3): real;
              var tmp1, tmp2: Tvec3;
              begin
                        tmp1 := para1.Normalize;
                        tmp2 := para2.Normalize;

                        Angle:= Dot(tmp1, tmp2);

                        Angle:= arccos(Angle);
              end;


              function Cross(para1, para2: Tvec3): Tvec3;
              begin
                            Cross.hx := para1.hy * para2.hz - para1.hz * para2.hy;
                            Cross.hy := para1.hz* para2.hx - para1.hx * para2.hz;
                            Cross.hz := para1.hx * para2.hy - para1.hy * para2.hx;
              end;

end.




