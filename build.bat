@echo off
REM PAL3 Decompilation - Build Script
REM Compiles source files using the configured toolchain

setlocal enabledelayedexpansion

echo ========================================
echo PAL3 Decompilation - Build
echo ========================================
echo.

REM Check if cl.exe is available
where cl.exe >nul 2>&1
if errorlevel 1 (
    echo [-] MSVC compiler not found in PATH
    echo Please run 'setup_env.bat' first to configure the toolchain.
    pause
    exit /b 1
)

REM Parse command line arguments
set "BUILD_TARGET=%~1"
set "BUILD_TYPE=Release"

if "%BUILD_TARGET%"=="" set "BUILD_TARGET=topo"
if "%BUILD_TARGET%"=="help" goto SHOW_HELP
if "%BUILD_TARGET%"=="clean" goto CLEAN

echo [1/4] Configuration:
echo   Target: %BUILD_TARGET%
echo   Type:   %BUILD_TYPE%
echo.

REM Detect compiler version
cl.exe 2>&1 | findstr "Version 12.00" >nul
if not errorlevel 1 (
    set "COMPILER=VC6"
    set "CMAKE_GENERATOR=NMake Makefiles"
)

cl.exe 2>&1 | findstr "Version 13.10" >nul
if not errorlevel 1 (
    set "COMPILER=VS2003"
    set "CMAKE_GENERATOR=NMake Makefiles"
)

cl.exe 2>&1 | findstr "Version 1" >nul
if not errorlevel 1 if not defined COMPILER (
    set "COMPILER=MODERN"
    set "CMAKE_GENERATOR=NMake Makefiles"
)

echo [2/4] Configuring CMake...
echo   Compiler: %COMPILER%
echo   Generator: %CMAKE_GENERATOR%
echo.

REM Configure based on target
if "%BUILD_TARGET%"=="topo" (
    cmake -B build\topo -S . -G "%CMAKE_GENERATOR%" ^
        -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
        -DBUILD_TARGET=topo ^
        || goto BUILD_ERROR

    echo.
    echo [3/4] Building topo.dll...
    cmake --build build\topo --config %BUILD_TYPE% || goto BUILD_ERROR

    echo.
    echo [4/4] Build complete!
    echo Output: build\topo\
    goto BUILD_SUCCESS
)

if "%BUILD_TARGET%"=="gbengine" (
    cmake -B build\gbengine -S . -G "%CMAKE_GENERATOR%" ^
        -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
        -DBUILD_TARGET=gbengine ^
        || goto BUILD_ERROR

    echo.
    echo [3/4] Building gbengine.dll...
    cmake --build build\gbengine --config %BUILD_TYPE% || goto BUILD_ERROR

    echo.
    echo [4/4] Build complete!
    echo Output: build\gbengine\
    goto BUILD_SUCCESS
)

if "%BUILD_TARGET%"=="pal3" (
    cmake -B build\pal3 -S . -G "%CMAKE_GENERATOR%" ^
        -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
        -DBUILD_TARGET=pal3 ^
        || goto BUILD_ERROR

    echo.
    echo [3/4] Building PAL3.exe...
    cmake --build build\pal3 --config %BUILD_TYPE% || goto BUILD_ERROR

    echo.
    echo [4/4] Build complete!
    echo Output: build\pal3\
    goto BUILD_SUCCESS
)

if "%BUILD_TARGET%"=="all" (
    echo Building all targets...
    call :BUILD_ONE topo
    call :BUILD_ONE gbengine
    call :BUILD_ONE pal3
    goto BUILD_SUCCESS
)

echo [-] Unknown build target: %BUILD_TARGET%
goto SHOW_HELP

:BUILD_ONE
echo.
echo ======== Building %~1 ========
cmake -B build\%~1 -S . -G "%CMAKE_GENERATOR%" ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    -DBUILD_TARGET=%~1
cmake --build build\%~1 --config %BUILD_TYPE%
exit /b

:CLEAN
echo [*] Cleaning build directories...
if exist build rmdir /s /q build
echo [+] Clean complete
exit /b 0

:SHOW_HELP
echo Usage: build.bat [target] [options]
echo.
echo Targets:
echo   topo      - Build topo.dll (math library)
echo   gbengine  - Build gbengine.dll (game engine)
echo   pal3      - Build PAL3.exe (main executable)
echo   all       - Build all targets
echo   clean     - Remove all build artifacts
echo   help      - Show this help message
echo.
echo Examples:
echo   build.bat topo        Build topo.dll
echo   build.bat clean       Clean all builds
echo   build.bat all         Build everything
echo.
exit /b 0

:BUILD_ERROR
echo.
echo [-] Build failed! See errors above.
pause
exit /b 1

:BUILD_SUCCESS
echo.
echo [+] Build successful!
echo.
echo Next steps:
echo   - Run 'python run.py compare' to verify binary matching
echo   - Check build\ directory for output files
echo.
pause
exit /b 0
