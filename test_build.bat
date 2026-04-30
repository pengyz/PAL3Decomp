@echo off
REM Quick test build script - uses any available compiler for testing

echo ========================================
echo PAL3 Quick Test Build
echo ========================================
echo.

REM Try to find any MSVC
set "VSWHERE=C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"

if exist "%VSWHERE%" (
    echo [*] Detecting Visual Studio...
    for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        set "VS_PATH=%%i"
    )

    if defined VS_PATH (
        echo [+] Found Visual Studio at: !VS_PATH!
        call "!VS_PATH!\VC\Auxiliary\Build\vcvars32.bat"
        goto BUILD
    )
)

REM Fallback: check if cl.exe is already in PATH
where cl.exe >nul 2>&1
if not errorlevel 1 (
    echo [+] Using MSVC from PATH
    goto BUILD
)

echo [-] No MSVC compiler found!
echo.
echo Please install Visual Studio with C++ workload, or run setup_env.bat
pause
exit /b 1

:BUILD
echo.
echo [*] Testing build with topo.dll...
echo.

cmake -B build\test -S . -G "NMake Makefiles" ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DBUILD_TARGET=topo

if errorlevel 1 (
    echo [-] CMake configuration failed
    pause
    exit /b 1
)

cmake --build build\test

if errorlevel 1 (
    echo [-] Build failed
    pause
    exit /b 1
)

echo.
echo [+] Test build successful!
echo.
echo Output files in build\test\
dir /b build\test\*.dll 2>nul
dir /b build\test\*.lib 2>nul
echo.

pause
