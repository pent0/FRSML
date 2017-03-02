unit Matrix;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Vector;

type

  TArrVec4 = array[1..4] of Tvec4;
  TArr2Float = array[1..16] of real;
  TArr1Float = array[1..4] of real;

  {The saddest thing is that generic function is being worked on, and the second}
  {saddest thing is that operator [] overloadding isnt supported. So you will get}
  {thing manually}

  TMatrix4 = class(TObject)
    public
       constructor Create(para: TArr2Float);
       constructor Create(row1, row2, row3, row4: TArr1Float);
       constructor Create(n: real = 0);
       constructor Create(row1, row2, row3, row4: Tvec4);

       property Inverse: Matrix4 read TInverse;
       property Transpose: Matrix4 read TTranspose;
       property Determinant: real read TDeterminant;

       property TRows: TArrVec4 read rows write rows;

    private

       function TInverse: Matrix4;
       function TTranspose: Matrix4;
       function TDeterminant: real;

       rows: TArrVec4;
  end;

operator *(para1, para2: TMatrix4) mul: TMatrix4;
operator +(para1, para2: TMatrix4) add: TMatrix4;
operator -(para1, para2: TMatrix4) sub: TMatrix4;

implementation
       constructor TMatrix4.Create(para: TArr2Float);
       var trows: array [1..4] of TArr1Float;
           i, j: shortint;
       begin
            for i:=1 to 4 do
            begin
              for j:=1 to 4 do
                  trows[i]:= para[j,i];
            end;

            rows[1]:= Tvec4.Create(Trows[1]);
            rows[2]:= Tvec4.Create(Trows[2]);
            rows[3]:= Tvec4.Create(Trows[3]);
            rows[4]:= Tvec4.Create(Trows[4]);

       end;

       constructor TMatrix4.Create(row1, row2, row3, row4: TArr1Float);
       begin
            rows[1]:= Tvec4.Create(row1);
            rows[2]:= Tvec4.Create(row2);
            rows[3]:= Tvec4.Create(row3);
            rows[4]:= Tvec4.Create(row4);
       end;

       constructor TMatrix4.Create(n: real = 0);
       begin
            rows[1]:= Tvec4.Create(n,n,n,n);
            rows[2]:= Tvec4.Create(n,n,n,n);
            rows[3]:= Tvec4.Create(n,n,n,n);
            rows[4]:= Tvec4.Create(n,n,n,n);
       end;

       constructor TMatrix4.Create(row1, row2, row3, row4: Tvec4);
       begin
            rows[1]:= row1;
            rows[2]:= row2;
            rows[3]:= row3;
            rows[4]:= row4;
       end;

       operator +(para1, para2: TMatrix4) add: TMatrix4;
       begin
            add:= TMatrix4.Create;
            add.Trows[1]:= para1.Trows[1]+ para2.Trows[1];
            add.Trows[2]:= para1.Trows[2]+ para2.Trows[2];
            add.Trows[3]:= para1.Trows[3]+ para2.Trows[3];
            add.Trows[4]:= para1.Trows[4]+ para2.Trows[4];
       end;

       operator -(para1, para2: TMatrix4) sub: TMatrix4;
       begin
            sub:= TMatrix4.Create;
            sub.Trows[1]:= para1.Trows[1] - para2.Trows[1];
            sub.Trows[2]:= para1.Trows[2] - para2.Trows[2];
            sub.Trows[3]:= para1.Trows[3] - para2.Trows[3];
            sub.Trows[4]:= para1.Trows[4] - para2.Trows[4];
       end;

       operator *(para1, para2: TMatrix4) mul: Matrix4;
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

            mul:= TMatrix4.Create(newRows[1], newRows[2], newRows[3], newRows[4]);

       end;

end.

