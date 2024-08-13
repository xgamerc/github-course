@echo off
SetLocal EnableDelayedExpansion

SET import=Yes
SET LOADLIBRARYA=No
SET importMode=DYNAMIC
SET cver=CPP
set clangdir=C:\Program Files\LLVM\bin

SET compext=
IF "%cver%" EQU "CPP" ( 
SET clangv="%clangdir%\clang++"
SET compext=cpp
) ELSE (
SET clangv="%clangdir%\clang"
SET compext=c
)

SET filenames=
FOR /R %%f in (*.%compext%) do (
SET filenames=!filenames! %%f
)

@REM SET compilerFlags=-g -Wvarargs -Wall -Werror
@REM SET defines=-D_CRT_SECURE_NO_WARNINGS
SET assembly=prog
SET compilerFlags=-g
SET defines=
SET includeFlags=-I../ -I../program/

if "%import%" EQU "Yes" (
SET defines=%defines% -DIMPORT
SET linkerFlags=-L../build/ -llibrary
IF "%importMode%" EQU "DYNAMIC" (
SET defines=%defines% -DDYNAMIC
) ELSE (
SET defines=%defines% -DSTATIC
)
) ELSE (
    IF "%LOADLIBRARYA%" EQU "Yes" (
        SET linkerFlags=
        SET defines=%defines% -DLLA
    ) ELSE (
        SET linkerFlags=
    )
)

IF NOT EXIST ../build/ mkdir ../build/
@echo on
%clangv% %filenames% %compilerFlags% -o ../build/%assembly%.exe %defines% %includeFlags% %linkerFlags%
@echo off

IF %ERRORLEVEL% NEQ 0 (
goto FAILUREBRANCH
) ELSE (
goto SUCCESSBRANCH
)

:SUCCESSBRANCH
ECHO "%assembly%.exe file built successfully."
goto commonexit

:FAILUREBRANCH
@REM echo Error Level: %ERRORLEVEL%
goto commonexit 

:commonexit
