unit SSE42;

{$mode objfpc}{$H+}
{$MACRO ON}
{$asmmode intel}


interface

uses
  Classes, SysUtils;

type

  TArr1Single = array[0..3] of Single;

  //Work like C++ header. Damn!
  //Also, unaligned.
  //You dont need asm knowledge to understand the code
  //Must say that intel asm is the easiest asm i have learned

  floatp4 = class(TObject)
     private
        mainPack: TArr1Single;

    public

        class constructor Create;
        constructor Crt5198(a: TArr1Single);

        property ps: TArr1Single read mainPack write mainPack;

        constructor v2(a,b,c,d: single);

        property n0: single read mainPack[0] write mainPack[0];
        property n1: single read mainPack[1] write mainPack[1];
        property n2: single read mainPack[2] write mainPack[2];
        property n3: single read mainPack[3] write mainPack[3];

  end;

function set_floatp4(a,b,c,d: single): floatp4;
operator + (para1, para2: floatp4) add: floatp4;
operator - (para1, para2: floatp4) sub: floatp4;
operator * (para1, para2: floatp4) mul: floatp4;
operator / (para1, para2: floatp4) divide: floatp4;
operator and (para1, para2: floatp4) andv: floatp4;
operator or (para1, para2: floatp4) orv: floatp4;
operator xor (para1, para2: floatp4) xorv: floatp4;

function Dot(para1,para2: floatp4; dotsize: byte): single;
function Max(para1,para2: floatp4): floatp4;
function Min(para1,para2: floatp4): floatp4;
function Sqrt(para1, para2: floatp4): floatp4;

implementation

              constructor floatp4.Crt5198(a: TArr1Single);
              begin
                   mainPack:= a;
              end;

              //Normal Dot function, not using Mask. To using Mask, there
              //is a intric name dpps. I cant let you pass an imm8
              //because i cant

              //Dot size. Get to from the 0 pos to dotsize pos
              function Dot(para1,para2: floatp4; dotsize: byte): single;
              var t1,t2,t3, arr1, arr2: TArr1Single;
                  i: shortint;
              begin

                   t1:= para1.ps;
                   t2:= para2.ps;

                   for i:=0 to dotsize do
                   begin
                        arr1[0]:= t1[i];
                        arr2[0]:= t1[i];

                        asm
                          movss xmm0, [arr1]
                          movss xmm1, [arr2]
                          movss xmm2, [t3]

                          mulps xmm0, xmm1

                          addps xmm2, xmm0

                          movss [t3],xmm2

                        end;

                   end;

                   Dot:= t3[0];

              end;

              function Max(para1, para2: floatp4): floatp4;
              var t1,t2,t3: TArr1Single;
              begin
                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                        movups xmm0, [t1]
                        movups xmm1, [t2]
                        maxps xmm0, xmm1
                        movups [t3], xmm0
                   end;

                   Max:= floatp4.Crt5198(t3);
              end;

              function Min(para1, para2: floatp4): floatp4;
              var t1,t2,t3: TArr1Single;
              begin

                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                        movups xmm0, [t1]
                        movups xmm1, [t2]
                        minps xmm0, xmm1
                        movups [t3], xmm0
                   end;

                   Min:= floatp4.Crt5198(t3);
              end;

              function set_floatp4(a,b,c,d: single): floatp4;
              begin
                   set_floatp4:= floatp4.v2(a,b,c,d);
              end;

              function Sqrt(para1, para2: floatp4): floatp4;
              var t1,t2,t3: TArr1Single;
              begin

                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                        movups xmm0, [t1]
                        movups xmm1, [t2]
                        sqrtps xmm0, xmm1
                        movups [t3], xmm0
                   end;

                   Sqrt:= floatp4.Crt5198(t3);

              end;

              //Gag will see this is an Intel asm
              operator + (para1, para2: floatp4) add: floatp4;
              var t1, t2, t3: TArr1Single;
              begin
                   add:= floatp4.Create;
                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                      movups xmm0, [t1]
                      movups xmm1, [t2]
                      addps xmm0, xmm1
                      movups [t3], xmm0
                   end;

                   add.ps := t3;
              end;

              operator - (para1, para2: floatp4) sub: floatp4;
              var t1, t2, t3: TArr1Single;
              begin
                   sub:= floatp4.Create;
                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                      movups xmm0, [t1]
                      movups xmm1, [t2]
                      subps xmm0, xmm1
                      movups [t3], xmm0
                   end;

                   sub.ps := t3;
              end;

            operator * (para1, para2: floatp4) mul: floatp4;
            var t1, t2, t3: TArr1Single;
            begin
                 mul:= floatp4.Create;
                 t1:= para1.ps;
                 t2:= para2.ps;

                 asm
                    movups xmm0, [t1]
                    movups xmm1, [t2]
                    mulps xmm0, xmm1
                    movups [t3], xmm0
                 end;

                 mul.ps := t3;
            end;

            operator / (para1, para2: floatp4) divide: floatp4;
            var t1, t2, t3: TArr1Single;
            begin
                 divide:= floatp4.Create;
                 t1:= para1.ps;
                 t2:= para2.ps;

                 asm
                    movups xmm0, [t1]
                    movups xmm1, [t2]
                    divps xmm0, xmm1
                    movups [t3], xmm0
                 end;

                 divide.ps := t3;
            end;


            operator or (para1, para2: floatp4) orv: floatp4;
            var t1, t2, t3: TArr1Single;
            begin
                 orv:= floatp4.Create;
                 t1:= para1.ps;
                 t2:= para2.ps;

                 asm
                    movups xmm0, [t1]
                    movups xmm1, [t2]
                    orps xmm0, xmm1
                    movups [t3], xmm0
                 end;

                 orv.ps := t3;
            end;

            operator xor (para1, para2: floatp4) xorv: floatp4;
            var t1, t2, t3: TArr1Single;
            begin
                 xorv:= floatp4.Create;
                 t1:= para1.ps;
                 t2:= para2.ps;

                 asm
                    movups xmm0, [t1]
                    movups xmm1, [t2]
                    xorps xmm0, xmm1
                    movups [t3], xmm0
                 end;

                 xorv.ps := t3;
            end;

            operator and (para1, para2: floatp4) andv: floatp4;
            var t1,t2,t3: TArr1Single;
            begin
                 andv:= floatp4.Create;
                 t1:= para1.ps;
                 t2:= para2.ps;

                 asm
                    movups xmm0, [t1]
                    movups xmm1, [t2]
                    andps xmm0, xmm1
                    movups [t3], xmm0
                 end;

                 andv.ps := t3;
            end;

              constructor floatp4.v2(a,b,c,d: single);
              begin
                   mainPack[3]:= a;
                   mainPack[2]:= b;
                   mainPack[1]:= c;
                   mainPack[0]:= d;
              end;

              class constructor floatp4.Create;
              begin
                   Create.mainPack[0] := 0;
                   Create.mainPack[1] := 0;
                   Create.mainPack[2] := 0;
                   Create.mainPack[3] := 0;
              end;


end.

