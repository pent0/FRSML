program FRSMLO;

{$mode objfpc}{$H+}{$M+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes, SysUtils, CustApp, vector;
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
  t, t2: Tvec2;

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
  t := Tvec2.Create(3,4);
  t2 := Tvec2.Create(4,9);


  writeln(t.Length:0:4,' ');

  t :=t+t2;

  writeln(t.X:0:4, ' ', t.Y:0:4);
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

