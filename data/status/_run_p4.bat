@echo off
set INCLUDE=D:\workspace\PAL3Decomp\include;D:\workspace\PAL3Decomp\pal3\src;D:\workspace\PAL3Decomp\tools\compilers\msvc6.0\Include;D:\workspace\PAL3Decomp\tools\vc6\Include
set LIB=D:\workspace\PAL3Decomp\tools\vc6\Lib
D:\workspace\PAL3Decomp\tools\compilers\msvc6.0\Bin\CL.EXE /nologo /TP /c /Fo"D:\workspace\PAL3Decomp\data\status\_p4.obj" "D:\workspace\PAL3Decomp\data\status\_p4.cpp"
if errorlevel 1 exit /b 1
D:\workspace\PAL3Decomp\tools\vc6\Bin\LINK.EXE /OUT:"D:\workspace\PAL3Decomp\data\status\_p4.exe" "D:\workspace\PAL3Decomp\data\status\_p4.obj" msvcrt.lib oldnames.lib kernel32.lib
if errorlevel 1 exit /b 2
D:\workspace\PAL3Decomp\data\status\_p4.exe
