@echo off

SetLocal EnableDelayedExpansion

set clangdir=C:\Program Files\LLVM\bin
SET libMode=DYNAMIC
SET CompMode=CPP
SET clangv=
SET compext=

IF "%CompMode%" EQU "CPP" ( 
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

SET finalAssembly=library
SET outExt=
SET compilerFlags=-g -Wvarargs -Wall -Werror
SET includeFlags=-I../ -I../library
SET linkerFlags=-luser32
SET defines=-D_DEBUG -DEXPORT -D_CRT_SECURE_NO_WARNINGS
SET extraCompArgs=

IF "%libMode%" EQU "STATIC" (
  goto STATICCONFIG
) ELSE (
  goto DLLCONFIG
)

:STATICCONFIG
SET defines=%defines% -DSTATIC
SET extraCompArgs=-c
SET outExt=lib
goto next

:DLLCONFIG
SET defines=%defines% -DDYNAMIC
SET compilerFlags=%compilerFlags% -shared
SET outExt=dll
goto next

:next
IF NOT EXIST ..\build\ mkdir ..\build

@echo on
%clangv% %extraCompArgs% %filenames% %compilerFlags% -o ..\build\%finalAssembly%.%outExt% %defines% %includeFlags% %linkerFlags%
@echo off

IF %ERRORLEVEL% NEQ 0 (
  goto FAILUREBRANCH
) ELSE (
  goto SUCCESSBRANCH
)

:SUCCESSBRANCH
if "%libMode%" EQU "STATIC" (
  ECHO "%finalAssembly%.lib file built successfully for static Linking."
) ELSE (
  ECHO "%finalAssembly%.dll and %finalAssembly%.lib file built successfully for dynamic Linking."
)
goto commonexit


:FAILUREBRANCH
echo Error Level: %ERRORLEVEL%
goto commonexit 

:commonexit

