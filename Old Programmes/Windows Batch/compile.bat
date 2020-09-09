::-----------------------------------------------------------------------------------::
::                                                                                   ::
::				"D:\Documents\compile.bat" "$(FULL_CURRENT_PATH)"                    ::
::                                                                                   ::
::-----------------------------------------------------------------------------------::

echo off

::----------------------------------------------------------------------------------- Set Path ------::
set NPP="C:\Program Files (x86)\Notepad++\notepad++.exe"

set GPLUSPLUS="C:\mingw\bin\g++.exe"
set GCC="C:\mingw\bin\gcc.exe"
set GFORTRAN="C:\mingw\bin\gfortran.exe"

set JAVAC="C:\Program Files\Java\jdk1.7.0_45\bin\javac.exe"
set JAVA="C:\Program Files\Java\jdk1.7.0_45\bin\java.exe"

set PYTHON="C:\Python27\python.exe"

set LEX="C:\Program Files (x86)\GnuWin32\bin\flex.exe"
set YACC="C:\Program Files (x86)\GnuWin32\bin\yacc.exe"

set LIB_OPENGL=-lopengl32 -lglu32 -lfreeglut 
set LIB_SDL=-lSDL 
set LIB_OPENCV=-lcv210.dll -lcvaux210.dll -lcvaux_pch_dephelp -lcvhaartraining -lcvtest_pch_dephelp -lcv_pch_dephelp -lcxcore210.dll -lcxcoretest_pch_dephelp -lcxcore_pch_dephelp -lcxts210.dll -lhighgui210.dll -lhighgui_pch_dephelp -lml210.dll -lml_pch_dephelp -lopencv_ffmpeg210.dll
set link=-lm 

%~d1
cd "%~p1"

::----------------------------------------------------------------------------------- Compile 1 ----::
cls
echo Compilation
echo -------------------------------------------------------------------------------
echo.

if %~x1==.c 		%GCC% %1 %clink% -o "%~n1.exe"
if %~x1==.C 		%GCC% %1 %clink% -o "%~n1.exe"
if %~x1==.h 		%GCC% %1 %link%
if %~x1==.H 		%GCC% %1 %link%
if %~x1==.cpp 		%GPLUSPLUS% %1 %link% -o "%~n1.exe"
if %~x1==.CPP 		%GPLUSPLUS% %1 %link% -o "%~n1.exe"
if %~x1==.hpp 		%GPLUSPLUS% %1 %link%
if %~x1==.HPP 		%GPLUSPLUS% %1 %link%

if %~x1==.f 		%GFORTRAN% %1
if %~x1==.F 		%GFORTRAN% %1

if %~x1==.java 		%JAVAC% %1
if %~x1==.JAVA 		%JAVAC% %1

if %~x1==.l 		%LEX% %1
if %~x1==.L 		%LEX% %1
if %~x1==.lex 		%LEX% %1
if %~x1==.LEX 		%LEX% %1
if %~x1==.yacc 		%LEX% "%~n1.lex"
if %~x1==.yacc 		%YACC% -d %1
if %~x1==.YACC 		%LEX% "%~n1.lex"
if %~x1==.YACC 		%YACC% -d %1

::----------------------------------------------------------------------------------- Compile 2 ----::
if %errorlevel%==1 	goto DONT_COMPILE
cls
echo Compilation
echo -------------------------------------------------------------------------------
echo.

if %~x1==.yacc 		%GCC% -w y.tab.c -o "%~n1.exe"
if %~x1==.YACC 		%GCC% -w y.tab.c -o "%~n1.exe"

:DONT_COMPILE

::----------------------------------------------------------------------------------- Run ----------::
if %errorlevel%==1 	goto DONT_RUN
cls
echo Execution
echo -------------------------------------------------------------------------------
echo.

if %~x1==.bat 		%1
if %~x1==.BAT 		%1

if %~x1==.c 		"%~n1.exe"
if %~x1==.C 		"%~n1.exe"
if %~x1==.cpp 		"%~n1.exe"
if %~x1==.CPP 		"%~n1.exe"

if %~x1==.f 		"%~n1.exe"
if %~x1==.F 		"%~n1.exe"

if %~x1==.py 		%PYTHON% %1
if %~x1==.PY 		%PYTHON% %1

if %~x1==.java 		%JAVA% "%~n1"
if %~x1==.JAVA 		%JAVA% "%~n1"

if %~x1==.yacc 		"%~n1.exe"
if %~x1==.YACC 		"%~n1.exe"

:DONT_RUN

echo.
pause
