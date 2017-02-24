program FRSMLO;

{$mode objfpc}{$H+}{$M+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes, SysUtils, CustApp, vector, Standard, nmmintrin;
  { you can add units after this }

type

  { FRSML }

  FRSML = class(TCustomApplication)
  protected
    procedure DoRun; override;
  public
    constructor Create(TheOwner: TComponent); override;
    destructor Destroy; override;
    procedure WriteHelp; virtual;
  end;

{ FRSML }


procedure FRSML.DoRun;
var
  ErrorMsg: String;
  t2, t3: floatp4;
begin

  // quick check parameters
  ErrorMsg:=CheckOptions('h', 'help');
  if ErrorMsg<>'' then begin
    ShowException(Exception.Create(ErrorMsg));
    Terminate;
    Exit;
  end;

  // parse parameters
  if HasOption('h', 'help') then begin
    WriteHelp;
    Terminate;
    Exit;
  end;

  { add your program here }
  //t := Tvec3.Create(3,4,5);

  //t1:= Tvec2.Create;
  //t1:= Reflect(vec2(0,87),vec2(5,7));

  t2:= set_floatp4(1,2,3,4);
  t3:= set_floatp4(2,3,4,5);

  t2:= t2 + t3;
  t2:= t2 - t3;

  writeln(t2.n0);

  //writeln(t1.X:0:4, ' ', t1.Y:0:4,' ',t1.Z:0:4);
  //writeln(t1.X:0:4,' ',t1.Y:0:4);
  readln;

  // stop program loop
  Terminate;
end;

constructor FRSML.Create(TheOwner: TComponent);
begin
  inherited Create(TheOwner);
  StopOnException:=True;
end;

destructor FRSML.Destroy;
begin
  inherited Destroy;
end;

procedure FRSML.WriteHelp;
begin
  { add your help code here }
  writeln('Usage: ', ExeName, ' -h');
end;

var
  Application: FRSML;
begin
  Application:=FRSML.Create(nil);
  Application.Title:='FRSMLTest';
  Application.Run;
  Application.Free;
end.

