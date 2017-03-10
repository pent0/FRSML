unit Matrix;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Vector;

type

  TArrVec4 = array[1..4] of Tvec4;
  TArr2Float = array[1..4,1..4] of real;
  TArr1Float = array[1..4] of real;

  {The saddest thing is that generic function is being worked on, and the second}
  {saddest thing is that operator [] overloadding isnt supported. So you will get}
  {thing manually}

  TMatrix4 = class(TObject)

    private

       function TInverse: TMatrix4;
       function TTranspose: TMatrix4;
       function TDeterminant: real;

       var rows: TArrVec4;

    public

       class constructor Create;

       constructor v2(para: TArr2Float);
       constructor v2(row1, row2, row3, row4: TArr1Float);
       constructor v2(n: real = 0);
       constructor v2(row1, row2, row3, row4: Tvec4);

       property Inverse: TMatrix4 read TInverse;
       property Transpose: TMatrix4 read TTranspose;
       property Determinant: real read TDeterminant;

       property TRows: TArrVec4 read rows write rows;

  end;

operator *(para1, para2: TMatrix4) mul: TMatrix4;
operator +(para1, para2: TMatrix4) add: TMatrix4;
operator -(para1, para2: TMatrix4) sub: TMatrix4;

implementation

       constructor TMatrix4.v2(para: TArr2Float);
       var ttrows: array [1..4] of TArr1Float;
           i, j: shortint;
       begin
            for i:=1 to 4 do
            begin
              for j:=1 to 4 do
                  ttrows[i][j] := para[j,i];
            end;

            rows[1]:= Tvec4.v2(Ttrows[1]);
            rows[2]:= Tvec4.v2(Ttrows[2]);
            rows[3]:= Tvec4.v2(Ttrows[3]);
            rows[4]:= Tvec4.v2(Ttrows[4]);

       end;

       constructor TMatrix4.v2(row1, row2, row3, row4: TArr1Float);
       begin
            rows[1]:= Tvec4.v2(row1);
            rows[2]:= Tvec4.v2(row2);
            rows[3]:= Tvec4.v2(row3);
            rows[4]:= Tvec4.v2(row4);
       end;

       constructor TMatrix4.v2(n: real = 0);
       begin
            rows[1]:= Tvec4.v2(n,n,n,n);
            rows[2]:= Tvec4.v2(n,n,n,n);
            rows[3]:= Tvec4.v2(n,n,n,n);
            rows[4]:= Tvec4.v2(n,n,n,n);
       end;

       constructor TMatrix4.v2(row1, row2, row3, row4: Tvec4);
       begin
            rows[1]:= row1;
            rows[2]:= row2;
            rows[3]:= row3;
            rows[4]:= row4;
       end;

       operator +(para1, para2: TMatrix4) add: TMatrix4;
       begin
            add:= TMatrix4.Create;
            add.rows[1]:= para1.Trows[1]+ para2.Trows[1];
            add.rows[2]:= para1.Trows[2]+ para2.Trows[2];
            add.rows[3]:= para1.Trows[3]+ para2.Trows[3];
            add.rows[4]:= para1.Trows[4]+ para2.Trows[4];
       end;

       operator -(para1, para2: TMatrix4) sub: TMatrix4;
       begin
            sub:= TMatrix4.Create;
            sub.rows[1]:= para1.Trows[1] - para2.Trows[1];
            sub.rows[2]:= para1.Trows[2] - para2.Trows[2];
            sub.rows[3]:= para1.Trows[3] - para2.Trows[3];
            sub.rows[4]:= para1.Trows[4] - para2.Trows[4];
       end;

       operator *(para1, para2: TMatrix4) mul: TMatrix4;
       var newRows: TArrVec4;
           rowt1, rowt2, rowt3, rowt4: Tvec4;
           i: shortint;
           t1,t2,t3,t4: real;

       begin

            rowt1 := para2.Trows[1];
            rowt2 := para2.Trows[2];
            rowt3 := para2.Trows[3];
            rowt4 := para2.Trows[4];

            for i:=1 to 4 do
            begin
                t1:= para1.Trows[i].X;
                t2:= para1.Trows[i].Y;
                t3:= para1.Trows[i].Z;
                t4:= para1.Trows[i].W;

                newRows[i]:= rowt1 * t1 + rowt2 * t2 + rowt3 * t3 + rowt4 * t4;
            end;

            mul:= TMatrix4.v2(newRows[1], newRows[2], newRows[3], newRows[4]);

       end;

       class constructor Create;
       begin
            rows[1]:= Tvec4.v2;
            rows[2]:= Tvec4.v2;
            rows[3]:= Tvec4.v2;
            rows[4]:= Tvec4.v2;
       end;

end.

