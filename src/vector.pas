//Warning: I can't find any document about template function
//Therefore, i can't solve Dot func duplication
//Things cant just be multiple

unit Vector;

{$mode objfpc}{$H+}{$M+}

interface

uses Math, Classes;

type

  Tvec2 = class(TObject)
    private
      hx,hy: real;

      class function TDown: Tvec2; static;
      class function TUp: Tvec2; static;
      class function TLeft: Tvec2;  static;
      class function TRight: Tvec2;  static;

    public
      constructor Create(tx: real = 0; ty: real = 0);


      class property Down: Tvec2 read TDown;
      class property Up: Tvec2 read TUp;
      class property Left: Tvec2 read TLeft;
      class property Right: Tvec2 read TRight;


      function Length: real;
      function Normalize: Tvec2;

      property X: real read hx write hx;
      property Y: real read hy write hy;

  end;

  Tvec3 = class(TObject)
    private
      hx,hy,hz: real;

      class function TDown: Tvec3; static;
      class function TUp: Tvec3; static;
      class function TLeft: Tvec3;  static;
      class function TRight: Tvec3;  static;
      class function TForward: Tvec3; static;
      class function TBackward: Tvec3; static;

    public
      constructor Create(tx: real = 0; ty: real = 0; tz: real = 0);
      constructor Create(t1: Tvec2; t2: real = 0);

      function Length: real;
      function Normalize: Tvec3;

      class property Down: Tvec3 read TDown;
      class property Up: Tvec3 read TUp;
      class property Left: Tvec3 read TLeft;
      class property Right: Tvec3 read TRight;
      class property Forward: Tvec3 read TForward;
      class property Backward: Tvec3 read TBackward;

      property X: real read hx write hx;
      property Y: real read hy write hy;
      property Z: real read hz write hz;

  end;

   Tvec4 = class(TObject)
    private
      hx,hy,hz, hw: real;

    public
      constructor Create(tx: real = 0; ty: real = 0; tz: real = 0; tw: real = 0);
      constructor Create(t1: Tvec3; t2: real = 0);

      function Length: real;
      function Normalize: Tvec4;

      property X: real read hx write hx;
      property Y: real read hy write hy;
      property Z: real read hz write hz;
      property W: real read hw write hw;

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

operator +(para1, para2: Tvec3) add: Tvec3;
operator -(para1, para2: Tvec3) sub: Tvec3;
operator *(para1, para2: Tvec3) mul: Tvec3;
operator /(para1, para2: Tvec3) divide: Tvec3;

operator +(para1: Tvec3; para2: real) addf: Tvec3;
operator -(para1: Tvec3; para2: real) subf: Tvec3;
operator *(para1: Tvec3; para2: real) mulf: Tvec3;
operator /(para1: Tvec3; para2: real) dividef: Tvec3;

operator +(para1, para2: Tvec4) add: Tvec4;
operator -(para1, para2: Tvec4) sub: Tvec4;
operator *(para1, para2: Tvec4) mul: Tvec4;
operator /(para1, para2: Tvec4) divide: Tvec4;

operator +(para1: Tvec4; para2: real) addf: Tvec4;
operator -(para1: Tvec4; para2: real) subf: Tvec4;
operator *(para1: Tvec4; para2: real) mulf: Tvec4;
operator /(para1: Tvec4; para2: real) dividef: Tvec4;

function Dot(para1, para2: Tvec3): real;
function Angle(para1, para2: Tvec3): real;
function Cross(para1, para2: Tvec3): Tvec3;

implementation

               class function Tvec2.TDown: Tvec2;
               begin
                             TDown:= Tvec2.Create(0,-1);
               end;

               class function Tvec2.TUp: Tvec2;
               begin
                             TUp:= Tvec2.Create(0,1);
               end;

               class function Tvec2.TLeft: Tvec2;
               begin
                             TLeft:= Tvec2.Create(-1,0);
               end;

               class function Tvec2.TRight: Tvec2;
               begin
                             TRight:= Tvec2.Create(1,0);
               end;

               class function Tvec3.TDown: Tvec3;
               begin
                             TDown:= Tvec3.Create(0,-1);
               end;

               class function Tvec3.TUp: Tvec3;
               begin
                             TUp:= Tvec3.Create(0,1);
               end;

               class function Tvec3.TLeft: Tvec3;
               begin
                             TLeft:= Tvec3.Create(-1,0);
               end;

               class function Tvec3.TRight: Tvec3;
               begin
                             TRight:= Tvec3.Create(1,0);
               end;

               class function Tvec3.TForward: Tvec3;
               begin
                              TForward:= Tvec3.Create(0,0,1);
               end;

               class function Tvec3.TBackward: Tvec3;
               begin
                              TBackward:= Tvec3.Create(0,0,-1);
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
                         add := Tvec3.Create;
                         add.X := para1.X + para2.X;
                         add.Y := para1.Y + para2.Y;
                         add.Z := para1.Z + para2.Z;
              end;

              operator - (para1, para2: Tvec3) sub: Tvec3;
              begin
                         sub := Tvec3.Create;
                         sub.X := para1.X - para2.X;
                         sub.Y := para1.Y - para2.Y;
                         sub.Z := para1.Z - para2.Z;
              end;

              operator * (para1, para2: Tvec3) mul: Tvec3;
              begin
                         mul := Tvec3.Create;
                         mul.X := para1.X * para2.X;
                         mul.Y := para1.Y * para2.Y;
                         mul.Z := para1.Z * para2.Z;
              end;

              operator / (para1, para2: Tvec3) divide: Tvec3;
              begin
                         divide := Tvec3.Create;
                         divide.X := para1.X / para2.X;
                         divide.Y := para1.Y / para2.Y;
                         divide.Z := para1.Z / para2.Z;
              end;

              operator + (para1:Tvec3 ; para2: real) addf: Tvec3;
              begin
                         addf := Tvec3.Create;
                         addf.X := para1.X + para2;
                         addf.Y := para1.Y + para2;
                         addf.Z := para1.Z + para2;
              end;

              operator - (para1:Tvec3 ; para2: real) subf: Tvec3;
              begin
                         subf := Tvec3.Create;
                         subf.X := para1.X - para2;
                         subf.Y := para1.Y - para2;
                         subf.Z := para1.Z - para2;
              end;

              operator * (para1:Tvec3 ; para2: real) mulf: Tvec3;
              begin
                         mulf := Tvec3.Create;
                         mulf.X := para1.X * para2;
                         mulf.Y := para1.Y * para2;
                         mulf.Z := para1.Z * para2;
              end;

              operator / (para1:Tvec3 ; para2: real) dividef: Tvec3;
              begin
                         dividef := Tvec3.Create;
                         dividef.X := para1.X / para2;
                         dividef.Y := para1.Y / para2;
                         dividef.Z := para1.Z / para2;
              end;

              function Tvec3.Length: real;
              begin
                        Length:= Sqrt(Power(X,2)+ Power(Y,2) + Power(Z,2));
              end;

              function Tvec3.Normalize: Tvec3;
              var tmp: real;
              begin
                         tmp:= Sqrt(Power(X,2)+ Power(Y,2) + Power(Z,2));
                         Normalize:= self / tmp;
              end;

              function Dot(para1, para2: Tvec3): real;
              begin
                            Dot := para1.X * para2.X + para1.Y + para2.Y + para1.Z * para2.Z;
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
                            Cross.X := para1.Y * para2.Z - para1.Z * para2.Y;
                            Cross.Y := para1.Z* para2.X - para1.X * para2.Z;
                            Cross.Z := para1.X * para2.Y - para1.Y * para2.X;
              end;

              constructor Tvec4.Create(tx: real = 0; ty: real = 0; tz: real = 0; tw: real = 0);
              begin
                            hx:= tx; hy:= ty; hz:= tz; hw:= tw;
              end;

              constructor Tvec4.Create(t1: Tvec3; t2: real = 0);
              begin
                            hx:= t1.X; hy:= t1.Y; hz:= t1.Z; hw:= t2;
              end;

              function Tvec4.Length: real;
              begin
                            Length:= Sqrt(Power(hx,2) + Power(hy,2) +
                            Power(hz,2) + Power(hw,2));
              end;

              function Tvec4.Normalize: Tvec4;
              var tmp: real;
              begin
                            tmp:= Sqrt(Power(hx,2) + Power(hy,2) +
                            Power(hz,2) + Power(hw,2));
                            Normalize:= self/ tmp;
              end;

              operator + (para1, para2: Tvec4) add: Tvec4;
              begin
                         add := Tvec4.Create;
                         add.X := para1.X + para2.X;
                         add.Y := para1.Y + para2.Y;
                         add.Z := para1.Z + para2.Z;
                         add.W := para1.W + para2.W;
              end;

              operator - (para1, para2: Tvec4) sub: Tvec4;
              begin
                         sub := Tvec4.Create;
                         sub.X := para1.X - para2.X;
                         sub.Y := para1.Y - para2.Y;
                         sub.Z := para1.Z - para2.Z;
                         sub.W := para1.W - para2.W;
              end;

              operator * (para1, para2: Tvec4) mul: Tvec4;
              begin
                         mul := Tvec4.Create;
                         mul.X := para1.X * para2.X;
                         mul.Y := para1.Y * para2.Y;
                         mul.Z := para1.Z * para2.Z;
                         mul.W := para1.W * para2.W;
              end;

              operator / (para1, para2: Tvec4) divide: Tvec4;
              begin
                         divide := Tvec4.Create;
                         divide.X := para1.X / para2.X;
                         divide.Y := para1.Y / para2.Y;
                         divide.Z := para1.Z / para2.Z;
                         divide.W := para1.W / para2.W;
              end;

              operator + (para1:Tvec4 ; para2: real) addf: Tvec4;
              begin
                         addf := Tvec4.Create;
                         addf.X := para1.X + para2;
                         addf.Y := para1.Y + para2;
                         addf.Z := para1.Z + para2;
                         addf.W := para1.W + para2;
              end;

              operator - (para1:Tvec4 ; para2: real) subf: Tvec4;
              begin
                         subf := Tvec4.Create;
                         subf.X := para1.X - para2;
                         subf.Y := para1.Y - para2;
                         subf.Z := para1.Z - para2;
                         subf.W := para1.W - para2;
              end;

              operator * (para1:Tvec4 ; para2: real) mulf: Tvec4;
              begin
                         mulf := Tvec4.Create;
                         mulf.X := para1.X * para2;
                         mulf.Y := para1.Y * para2;
                         mulf.Z := para1.Z * para2;
                         mulf.W := para1.W * para2;
              end;

              operator / (para1:Tvec4 ; para2: real) dividef: Tvec4;
              begin
                         dividef := Tvec4.Create;
                         dividef.X := para1.X / para2;
                         dividef.Y := para1.Y / para2;
                         dividef.Z := para1.Z / para2;
                         dividef.W := para1.W / para2;
              end;

end.




