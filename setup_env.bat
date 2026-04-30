@echo off
REM PAL3 Decompilation - Environment Setup Script
REM This script detects and configures the appropriate compiler toolchain

echo ========================================
echo PAL3 Decompilation Toolchain Setup
echo ========================================
echo.

REM Check for Visual Studio installations
set "VS_FOUND="
set "VC6_FOUND="
set "VS2003_FOUND="
set "VS_MODERN="

echo [1/5] Detecting Visual Studio installations...
echo.

REM Check for VC++ 6.0
if exist "C:\Program Files\Microsoft Visual Studio\VC98\bin\cl.exe" (
    set "VC6_FOUND=1"
    set "VC6_PATH=C:\Program Files\Microsoft Visual Studio\VC98"
    echo [+] Visual C++ 6.0 found at: !VC6_PATH!
)
if exist "C:\Program Files (x86)\Microsoft Visual Studio\VC98\bin\cl.exe" (
    set "VC6_FOUND=1"
    set "VC6_PATH=C:\Program Files (x86)\Microsoft Visual Studio\VC98"
    echo [+] Visual C++ 6.0 found at: !VC6_PATH!
)

REM Check for VS .NET 2003 (VC7.1)
if exist "C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\bin\cl.exe" (
    set "VS2003_FOUND=1"
    set "VS2003_PATH=C:\Program Files\Microsoft Visual Studio .NET 2003"
    echo [+] Visual Studio .NET 2003 found at: !VS2003_PATH!
)
if exist "C:\Program Files (x86)\Microsoft Visual Studio .NET 2003\Vc7\bin\cl.exe" (
    set "VS2003_FOUND=1"
    set "VS2003_PATH=C:\Program Files (x86)\Microsoft Visual Studio .NET 2003"
    echo [+] Visual Studio .NET 2003 found at: !VS2003_PATH!
)

REM Check for modern Visual Studio (2017+)
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat" (
    set "VS_MODERN=2022"
    set "VS_MODERN_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community"
    echo [+] Visual Studio 2022 found at: !VS_MODERN_PATH!
)
if exist "C:\Program Files\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat" (
    set "VS_MODERN=2019"
    set "VS_MODERN_PATH=C:\Program Files\Microsoft Visual Studio\2019\Community"
    echo [+] Visual Studio 2019 found at: !VS_MODERN_PATH!
)
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat" (
    set "VS_MODERN=2019"
    set "VS_MODERN_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community"
    echo [+] Visual Studio 2019 found at: !VS_MODERN_PATH!
)

if not defined VC6_FOUND if not defined VS2003_FOUND if not defined VS_MODERN (
    echo [-] No Visual Studio installation found
    echo.
    echo You have the following options:
    echo   1. Install Visual C++ 6.0 SP6 ^(for binary-exact matching^)
    echo   2. Install Visual Studio 2022 with C++ workload ^(for testing^)
    echo   3. Use MinGW-w64 GCC ^(cross-platform development^)
    echo.
    echo See docs/compiler_setup.md for detailed instructions.
    pause
    exit /b 1
)

echo.
echo [2/5] Select compiler mode:
echo   1 = VC++ 6.0 ^(topo.dll, gbengine.dll - binary exact^)
echo   2 = VS .NET 2003 ^(PAL3.exe - binary exact^)
echo   3 = Modern VS ^(testing only^)
echo   4 = Auto-detect
echo.

set /p "COMPILER_MODE=Enter choice [1-4]: "

if "%COMPILER_MODE%"=="1" goto USE_VC6
if "%COMPILER_MODE%"=="2" goto USE_VS2003
if "%COMPILER_MODE%"=="3" goto USE_MODERN
if "%COMPILER_MODE%"=="4" goto AUTO_DETECT

:AUTO_DETECT
echo [3/5] Auto-detecting best available compiler...
if defined VC6_FOUND goto USE_VC6
if defined VS2003_FOUND goto USE_VS2003
if defined VS_MODERN goto USE_MODERN
goto NO_COMPILER

:USE_VC6
if not defined VC6_FOUND (
    echo [-] Visual C++ 6.0 not found!
    goto NO_COMPILER
)
echo [+] Using Visual C++ 6.0
echo.
echo Setting up environment...
set "PATH=%VC6_PATH%\bin;%PATH%"
set "INCLUDE=%VC6_PATH%\include;%VC6_PATH%\ATL\include;%VC6_PATH%\MFC\include"
set "LIB=%VC6_PATH%\lib;%VC6_PATH%\MFC\lib"
set "MSVC_VERSION=VC6"
goto VERIFY

:USE_VS2003
if not defined VS2003_FOUND (
    echo [-] Visual Studio .NET 2003 not found!
    goto NO_COMPILER
)
echo [+] Using Visual Studio .NET 2003
echo.
call "%VS2003_PATH%\Common7\Tools\vsvars32.bat"
set "MSVC_VERSION=VS2003"
goto VERIFY

:USE_MODERN
if not defined VS_MODERN (
    echo [-] Modern Visual Studio not found!
    goto NO_COMPILER
)
echo [+] Using Visual Studio %VS_MODERN% ^(testing mode^)
echo.
echo WARNING: Modern compilers cannot produce binary-exact matches.
echo This is for functional testing only.
echo.
call "%VS_MODERN_PATH%\VC\Auxiliary\Build\vcvars32.bat"
set "MSVC_VERSION=VS%VS_MODERN%"
goto VERIFY

:NO_COMPILER
echo [-] No suitable compiler found!
echo Please install Visual Studio and run this script again.
pause
exit /b 1

:VERIFY
echo [4/5] Verifying compiler setup...
cl.exe 2>&1 | findstr /C:"Compiler Version" >nul
if errorlevel 1 (
    echo [-] Compiler verification failed!
    pause
    exit /b 1
)

echo [+] Compiler ready:
cl.exe 2>&1 | findstr "Compiler Version"

echo.
echo [5/5] Environment configured successfully!
echo.
echo MSVC Version: %MSVC_VERSION%
echo.
echo Next steps:
echo   - Run 'build.bat' to compile the project
echo   - Run 'python run.py check' to verify dependencies
echo.
echo This environment is active for the current terminal session only.
echo To persist it, run this script in each new terminal.
echo.
pause
