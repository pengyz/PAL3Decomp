@echo off
REM Start Ghidra for PAL3.exe analysis
REM This script sets up the environment and launches Ghidra

echo ========================================
echo  Ghidra PAL3.exe Analysis Launcher
echo ========================================
echo.

REM Set Java home
set JAVA_HOME=C:\Java\jdk-17.0.8+7
set PATH=%JAVA_HOME%\bin;%PATH%

REM Verify Java
echo Checking Java runtime...
java -version 2>&1 | find "openjdk" >nul
if errorlevel 1 (
    echo ERROR: Java runtime not found!
    echo Please ensure Java is installed at: %JAVA_HOME%
    pause
    exit /b 1
)
echo [OK] Java found

REM Launch Ghidra
echo.
echo Starting Ghidra (this may take 30-60 seconds on first launch)...
echo.

cd ..\..\tools\ghidra
call ghidraRun.bat

echo.
echo Ghidra has exited. Project saved to: %CD%\..\pal3\PAL3.gpr
echo.
pause
