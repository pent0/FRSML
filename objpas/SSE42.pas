unit SSE42;

{$mode objfpc}{$H+}
{$MACRO ON}
{$asmmode intel}


interface

uses
  Classes, SysUtils;

type

  TArr1Single = array[0..3] of Single;
  TArr1Word = array[0..3] of DWord;

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

  dwordp4 = class(TObject)
    private
        mainPack: TArr1Word;

    public

        class constructor Create;
        constructor Crt5198(a: TArr1Word);

        property ps: TArr1Word read mainPack write mainPack;

        constructor v2(a,b,c,d: Dword);

        property n0: Dword read mainPack[0] write mainPack[0];
        property n1: Dword read mainPack[1] write mainPack[1];
        property n2: Dword read mainPack[2] write mainPack[2];
        property n3: Dword read mainPack[3] write mainPack[3];

  end;

function set_floatp4(a,b,c,d: single): floatp4;

operator + (para1, para2: floatp4) add: floatp4;
operator - (para1, para2: floatp4) sub: floatp4;
operator * (para1, para2: floatp4) mul: floatp4;
operator / (para1, para2: floatp4) divide: floatp4;

operator and (para1, para2: floatp4) andv: floatp4;
operator or (para1, para2: floatp4) orv: floatp4;
operator xor (para1, para2: floatp4) xorv: floatp4;
operator not (para1: floatp4) notv: floatp4;
operator mod (para1, para2: floatp4) modq: floatp4;

operator > (para1, para2: floatp4) big: boolean;
operator < (para1, para2: floatp4) less: boolean;
operator >= (para1, para2: floatp4) bige: boolean;
operator <= (para1, para2: floatp4) lesse: boolean;

function ArrEqual(para1, para2: floatp4): boolean;

function set_floatp4_ss(a: single): floatp4;
function set_floatp4(a: TArr1Single): floatp4;

function Dot(para1,para2: floatp4): single;
function Max(para1,para2: floatp4): floatp4;
function Min(para1,para2: floatp4): floatp4;
function Sqrt(para1, para2: floatp4): floatp4;
function Reserve_Sqrt(para1, para2: floatp4): floatp4;
function Sign(para1: floatp4): floatp4;
function Floor(para1: floatp4): floatp4;
function Ceil(para1: floatp4): floatp4;
function Round(para1: floatp4; a: shortint): floatp4;

function Shuffle(para1, para2: floatp4; np3, np2, np1, np0: byte): floatp4;

function set_dwordp4(a,b,c,d: Dword): dwordp4;

operator + (para1, para2: dwordp4) add: dwordp4;
operator - (para1, para2: dwordp4) sub: dwordp4;
function dword4_mulu(para1, para2: dwordp4): dwordp4;

//I can't port this. Figure out yourself. I have the code finding magic number on
//So you can uses it to port your own version.
//C++ Standard.cpp
//operator / (para1, para2: dwordp4) divide: dwordp4;

operator and (para1, para2: dwordp4) andv: dwordp4;
operator or (para1, para2: dwordp4) orv: dwordp4;
operator xor (para1, para2: dwordp4) xorv: dwordp4;
operator not (para1: dwordp4) notv: dwordp4;

operator > (para1, para2: dwordp4) big: boolean;
operator < (para1, para2: dwordp4) less: boolean;
operator >= (para1, para2: dwordp4) bige: boolean;
operator <= (para1, para2: dwordp4) lesse: boolean;

function Max(para1,para2: dwordp4): dwordp4;
function Min(para1,para2: dwordp4): dwordp4;

implementation

              function ArrEqual(para1, para2: floatp4): boolean;
              var t1, t2, t3: TArr1Single;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movups xmm0, [t1]
                        movups xmm1, [t2]

                        cmpps xmm0, xmm1, 0

                        movups [t3],xmm0
                     end;

                     ArrEqual:= (t3[0] = $FFFFFFFF);
              end;

              function Sign(para1: floatp4): floatp4;
              var t1: array [0..3] of DWord;
                  t2, t3, t4: TArr1Single;

              begin
                  t1[0]:= $ffffffff; t1[2]:= $ffffffff;
                  t1[1]:= $ffffffff; t1[3]:= $ffffffff;

                  t2[0]:=1; t2[1]:=1; t2[2]:=1; t2[3]:=1;
                  t4[0]:=-1; t4[1]:=-1; t4[2]:=-1; t4[3]:=-1;

                  asm
                     movups xmm0, [para1]
                     movups xmm1, [t2]
                     xorps xmm0, xmm1

                     cvtps2dq xmm2, xmm0
                     movdqu xmm3, [t1]

                     psrldq xmm2, 31

                     xorps xmm2, xmm3

                     cvtdq2ps xmm4, xmm2

                     movups xmm5, [t4]

                     mulps xmm4, xmm5

                     movups [t3], xmm4
                  end;
;
                  Sign:= set_floatp4(t3);
              end;

              operator mod (para1, para2: floatp4) modq: floatp4;
              var t1, t2, t3: TArr1Single;
              begin
                  t1:= para1.mainPack;
                  t2:= para2.mainPack;

                  asm
                     movups xmm0, [t1]
                     movups xmm1, [t2]
                     movups xmm2, xmm0

                     divps xmm0, xmm1
                     mulps xmm0, xmm1

                     subps xmm2, xmm0

                     movups [t3], xmm2
                  end;

                  modq:= set_floatp4(t3);
              end;

              operator > (para1, para2: floatp4) big: boolean;
              var t1, t2: TArr1Single;
                  t3: array [0..3] of longint;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movups xmm0, [t1]
                        movups xmm1, [t2]

                        cmpps xmm0, xmm1, 5

                        movups [t3],xmm0
                     end;

                     big:= (t3[0] = -1);
              end;

              operator < (para1, para2: floatp4) less: boolean;
              var t1, t2: TArr1Single;
                  t3: array [0..3] of longint;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movups xmm0, [t1]
                        movups xmm1, [t2]

                        cmpps xmm0, xmm1, 1

                        movups [t3],xmm0
                     end;

                     less:= (t3[0] = -1);
              end;

              operator >= (para1, para2: floatp4) bige: boolean;
              var t1, t2: TArr1Single;
                  t3: array [0..3] of longint;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movups xmm0, [t1]
                        movups xmm1, [t2]

                        cmpps xmm0, xmm1, 6

                        movups [t3],xmm0
                     end;

                     bige:= (t3[0] = -1);
              end;

              operator <= (para1, para2: floatp4) lesse: boolean;
              var t1, t2: TArr1Single;
                  t3: array [0..3] of longint;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movups xmm0, [t1]
                        movups xmm1, [t2]

                        cmpps xmm0, xmm1, 2

                        movups [t3],xmm0
                     end;

                     lesse:= (t3[0] = -1);
              end;

              function Shuffle(para1, para2: floatp4; np3, np2, np1, np0: byte): floatp4;
              var t1,t2, t3: TArr1Single;
              begin

                   Shuffle:= floatp4.Create;

                   t1:= para1.mainPack; t2:= para2.mainPack;

                   asm
                        movups xmm0, [t1]
                        movups xmm1, [t2]

                        shufps xmm0, xmm1, $e4

                        movups [t3],xmm0
                   end;

                   Shuffle.n3:= t3[np3];
                   Shuffle.n2:= t3[np2];
                   Shuffle.n1:= t3[np1];
                   Shuffle.n0:= t3[np0];

              end;

              function set_floatp4_ss(a: single): floatp4;
              begin
                   set_floatp4_ss:= floatp4.Create;
                   set_floatp4_ss.n0 := a;
              end;

              function set_floatp4(a: TArr1Single): floatp4;
              begin
                    set_floatp4:= floatp4.Crt5198(a);
              end;

              constructor floatp4.Crt5198(a: TArr1Single);
              begin
                   mainPack:= a;
              end;

              //Normal Dot function, not using Mask. To using Mask, there
              //is a intric name dpps. I cant let you pass an imm8
              //because i cant

              //Dot product of two floatp4
              function Dot(para1,para2: floatp4): single;
              const dotsize1 = 5;
              var t1,t2,t3, arr1, arr2: TArr1Single;
                  i: shortint;
              begin

                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                      movups xmm0, [t1]
                      movups xmm1, [t2]

                      mulps xmm0, xmm1

                      haddps xmm0, xmm0
                      haddps xmm0, xmm0

                      movups [t3], xmm0
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

              function Reserve_Sqrt(para1, para2: floatp4): floatp4;
              var t1,t2,t3: TArr1Single;
              begin

                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                        movups xmm0, [t1]
                        movups xmm1, [t2]
                        rsqrtps xmm0, xmm1
                        movups [t3], xmm0
                   end;

                   Reserve_Sqrt:= floatp4.Crt5198(t3);

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

              operator not (para1: floatp4) notv: floatp4;
              var t1,t2: TArr1Single;
              begin
                 notv:= floatp4.Create;
                 t1:= para1.ps;

                 asm
                    movups xmm0, [t1]
                    movups xmm1, [t1]

                    cmpps xmm1, xmm1, 0

                    xorps xmm0, xmm1

                    movups [t2], xmm0
                 end;

                 notv.ps := t2;
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

              class constructor dwordp4.Create;
              begin
                   Create.mainPack[0] := 0;
                   Create.mainPack[1] := 0;
                   Create.mainPack[2] := 0;
                   Create.mainPack[3] := 0;
              end;

              constructor dwordp4.v2(a,b,c,d: Dword);
              begin
                   mainPack[3]:= a;
                   mainPack[2]:= b;
                   mainPack[1]:= c;
                   mainPack[0]:= d;
              end;

              constructor dwordp4.Crt5198(a: TArr1Word);
              begin
                   mainPack:= a;
              end;

              function set_dwordp4(a,b,c,d: Dword): dwordp4;
              begin
                   set_dwordp4:= dwordp4.v2(a,b,c,d);
              end;

              operator + (para1, para2: dwordp4) add: dwordp4;
              var t1, t2, t3: TArr1Word;
              begin
                   add:= dwordp4.Create;
                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                      movdqu xmm0, [t1]
                      movdqu xmm1, [t2]
                      paddq xmm0, xmm1
                      movdqu [t3], xmm0
                   end;

                   add.ps := t3;
              end;

              operator - (para1, para2: dwordp4) sub: dwordp4;
              var t1, t2, t3: TArr1Word;
              begin
                   sub:= dwordp4.Create;
                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                      movdqu xmm0, [t1]
                      movdqu xmm1, [t2]
                      psubq xmm0, xmm1
                      movdqu [t3], xmm0
                   end;

                   sub.ps := t3;
              end;

              function dword4_mulu(para1, para2: dwordp4): dwordp4;
              var t1, t2, t3: TArr1Word;
              begin
                   dword4_mulu:= dwordp4.Create;
                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                      movdqu xmm0, [t1]
                      movdqu xmm1, [t2]
                      pmuludq xmm0, xmm1
                      movdqu [t3], xmm0
                   end;

                   dword4_mulu.ps := t3;
              end;

              operator and (para1, para2: dwordp4) andv: dwordp4;
              var t1, t2, t3: TArr1Word;
              begin
                   andv:= dwordp4.Create;
                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                      movdqu xmm0, [t1]
                      movdqu xmm1, [t2]
                      andps xmm0, xmm1
                      movdqu [t3], xmm0
                   end;

                   andv.ps := t3;
              end;

              operator or (para1, para2: dwordp4) orv: dwordp4;
              var t1, t2, t3: TArr1Word;
              begin
                   orv:= dwordp4.Create;
                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                      movdqu xmm0, [t1]
                      movdqu xmm1, [t2]
                      orps xmm0, xmm1
                      movdqu [t3], xmm0
                   end;

                   orv.ps := t3;
              end;

              operator xor (para1, para2: dwordp4) xorv: dwordp4;
              var t1, t2, t3: TArr1Word;
              begin
                   xorv:= dwordp4.Create;
                   t1:= para1.ps;
                   t2:= para2.ps;

                   asm
                      movdqu xmm0, [t1]
                      movdqu xmm1, [t2]
                      xorps xmm0, xmm1
                      movdqu [t3], xmm0
                   end;

                   xorv.ps := t3;
              end;

              operator not (para1: dwordp4) notv: dwordp4;
              var t1,t2: TArr1Word;
              begin
                 notv:= dwordp4.Create;
                 t1:= para1.ps;

                 asm
                    movdqu xmm0, [t1]
                    movdqu xmm1, [t1]

                    pcmpgtd xmm1, xmm1

                    xorps xmm0, xmm1

                    movdqu [t2], xmm0
                 end;

                 notv.ps := t2;
              end;

              operator > (para1, para2: dwordp4) big: boolean;
              var t1, t2: TArr1Word;
                  t3: array [0..3] of longint;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movdqu xmm0, [t1]
                        movdqu xmm1, [t2]

                        pcmpgtd xmm0, xmm1

                        movdqu [t3],xmm0
                     end;

                     big:= (t3[0] = -1);
              end;

              operator < (para1, para2: dwordp4) less: boolean;
              var t1, t2: TArr1Word;
                  t3, t4: array [0..3] of longint;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movdqu xmm0, [t1]
                        movdqu xmm1, [t2]
                        movdqu xmm2, xmm0

                        pcmpgtd xmm0, xmm1
                        pcmpeqd xmm2, xmm1

                        movdqu [t3],xmm0
                        movdqu [t4],xmm2
                     end;

                     less:= (t3[0] = 0) and (t4[0] <> -1);
              end;

              operator >= (para1, para2: dwordp4) bige: boolean;
              var t1, t2: TArr1Word;
                  t3: array [0..3] of longint;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movdqu xmm0, [t1]
                        movdqu xmm1, [t2]
                        movdqu xmm2, xmm0

                        pcmpgtd xmm0, xmm1
                        pcmpeqd xmm2, xmm1

                        andps xmm0, xmm2

                        movdqu [t3],xmm0
                     end;

                     bige:= (t3[0] = -1);
              end;


              operator <= (para1, para2: dwordp4) lesse: boolean;
              var t1, t2: TArr1Word;
                  t3, t4: array [0..3] of longint;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movdqu xmm0, [t1]
                        movdqu xmm1, [t2]
                        movdqu xmm2, xmm0

                        pcmpgtd xmm0, xmm1
                        pcmpeqd xmm2, xmm1

                        movdqu [t3],xmm0
                        movdqu [t4],xmm2
                     end;

                     lesse:= (t3[0] = 0) and (t4[0] <> -1);
              end;

              function Max(para1,para2: dwordp4): dwordp4;
              var t1, t2, t3: TArr1Word;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movdqu xmm0, [t1]
                        movdqu xmm1, [t2]

                        pmaxsw xmm0, xmm1

                        movdqu [t3],xmm0
                     end;

                     Max := dwordp4.Create;
                     Max.mainPack := t3;
              end;

              function Min(para1,para2: dwordp4): dwordp4;
              var t1, t2, t3: TArr1Word;
              begin
                     t1:= para1.mainPack;
                     t2:= para2.mainPack;

                     asm
                        movdqu xmm0, [t1]
                        movdqu xmm1, [t2]

                        pminsw xmm0, xmm1

                        movdqu [t3],xmm0
                     end;

                     Min := dwordp4.Create;
                     Min.mainPack := t3;
              end;


              //Credit to stephani, which i adopted the theory from
              //http://dss.stephanierct.com/DevBlog/?p=8
              //Since i cant find floor instric

              function Floor(para1: floatp4): floatp4;
              var t1: array[0..3] of longint;
                  t2: TArr1Single;
              begin

                     t2:= para1.mainPack;

                     t1[0] := 0; t1[1]:= 0; t1[2]:= 0;
                     t1[3]:= 0;

                     //First, get a vector 1
                     //Then round it by convert to word
                     //Then check if it's negative or not and sub by one
                     //The theory is very good, depends on the rounding func of
                     //the SIMD

                     asm
                          movdqu xmm0, t1
                          pcmpeqd xmm0, xmm0

                          psrldq xmm0, 25
                          pslldq xmm0, 23

                          cvtdq2ps xmm1, xmm0
                          movups xmm3, xmm1

                          cvtps2dq xmm2, [t2]
                          cvtdq2ps xmm2, xmm2

                          movups xmm4, xmm2

                          cmpps xmm1, xmm2, 5

                          andps xmm3, xmm1

                          subps xmm4, xmm3
                     end;
              end;

              function Ceil(para1: floatp4): floatp4;
              var t1: array[0..3] of longint;
                  t2: TArr1Single;
              begin

                     t2:= para1.mainPack;

                     t1[0] := 0; t1[1]:= 0; t1[2]:= 0;
                     t1[3]:= 0;


                     asm
                          movdqu xmm0, t1
                          pcmpeqd xmm0, xmm0

                          psrldq xmm0, 25
                          pslldq xmm0, 23

                          cvtdq2ps xmm1, xmm0
                          movups xmm3, xmm1

                          cvtps2dq xmm2, [t2]
                          cvtdq2ps xmm2, xmm2

                          movups xmm4, xmm2

                          cmpps xmm1, xmm2, 1

                          andps xmm3, xmm1

                          addps xmm4, xmm3
                     end;
              end;

              function Round(para1: floatp4; a: shortint): floatp4;
              var
                  t2, t3: TArr1Single;
              begin

                     t2:= para1.mainPack;

                     if (a = 0) then
                     asm
                        movups xmm0, [t2]

                        roundps xmm0, xmm0, 0

                        movups [t3], xmm0
                     end
                     else
                     if (a = 1) then
                       asm
                          movups xmm0, [t2]

                          roundps xmm0, xmm0, 0

                          movups [t3], xmm0
                       end;

                     Round:= set_floatp4(t3);
              end;


end.

