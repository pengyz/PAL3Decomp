@echo off
REM run_headless_export.bat
REM Run Ghidra headless export for PAL3.exe
REM
REM This script runs the Ghidra export_functions.py script in headless mode
REM to export all functions from the PAL3.exe Ghidra project to JSON files.
REM
REM Prerequisites:
REM   - Ghidra project created at: asm\pal3\PAL3.rep
REM   - PAL3.exe imported and analyzed in the project
REM   - Java 17+ installed at: C:\Java\jdk-17.0.8+7
REM
REM Output:
REM   - Individual function JSON files: asm\pal3\functions\*.json
REM   - Summary index: asm\pal3\pal3_functions.json
REM
REM Usage:
REM   run_headless_export.bat

setlocal enabledelayedexpansion

REM ============================================================================
REM Configuration
REM ============================================================================

set JAVA_HOME=C:\Java\jdk-17.0.8+7
set GHIDRA_HOME=D:\workspace\project-x\tools\ghidra
set PROJECT_ROOT=D:\workspace\project-x
set PROJECT_DIR=%PROJECT_ROOT%\asm\pal3
set PROJECT_NAME=PAL3
set BINARY_NAME=PAL3.exe
set SCRIPT_PATH=%PROJECT_ROOT%\tools\ghidra\export_functions.py
set OUTPUT_DIR=%PROJECT_ROOT%\asm\pal3\functions

REM ============================================================================
REM Environment Setup
REM ============================================================================

REM Set PATH to include Java
set PATH=%JAVA_HOME%\bin;%PATH%

echo ========================================================================
echo PAL3.exe Ghidra Headless Export
echo ========================================================================
echo.

REM ============================================================================
REM Validation
REM ============================================================================

REM Check Java
if not exist "%JAVA_HOME%\bin\java.exe" (
    echo ERROR: Java not found at %JAVA_HOME%
    echo Please install Java 17+ or update JAVA_HOME in this script.
    exit /b 1
)

echo [OK] Java: %JAVA_HOME%

REM Check Ghidra
if not exist "%GHIDRA_HOME%\support\analyzeHeadless.bat" (
    echo ERROR: Ghidra not found at %GHIDRA_HOME%
    echo Please install Ghidra or update GHIDRA_HOME in this script.
    exit /b 1
)

echo [OK] Ghidra: %GHIDRA_HOME%

REM Check Ghidra project
if not exist "%PROJECT_DIR%\%PROJECT_NAME%.rep" (
    echo ERROR: Ghidra project not found at %PROJECT_DIR%\%PROJECT_NAME%.rep
    echo.
    echo Please create the Ghidra project first:
    echo   1. Run Ghidra GUI
    echo   2. Create project: %PROJECT_NAME%
    echo   3. Import binary: %BINARY_NAME%
    echo   4. Analyze the binary
    echo.
    echo Or complete Task 1: Ghidra 项目设置和初步分析
    exit /b 1
)

echo [OK] Project: %PROJECT_DIR%\%PROJECT_NAME%.rep

REM Check export script
if not exist "%SCRIPT_PATH%" (
    echo ERROR: Export script not found at %SCRIPT_PATH%
    exit /b 1
)

echo [OK] Script: %SCRIPT_PATH%

REM Create output directory if needed
if not exist "%OUTPUT_DIR%" (
    echo Creating output directory: %OUTPUT_DIR%
    mkdir "%OUTPUT_DIR%"
)

echo [OK] Output: %OUTPUT_DIR%
echo.

REM ============================================================================
REM Run Ghidra Headless Export
REM ============================================================================

echo ------------------------------------------------------------------------
echo Running Ghidra headless analysis...
echo ------------------------------------------------------------------------
echo.

REM Run analyzeHeadless with the export script
REM   -import:       Don't re-import (binary already in project)
REM   -process:      Process the specified binary
REM   -postScript:   Run script after analysis (no re-analysis with -noanalysis)
REM   -noanalysis:   Skip auto-analysis (project already analyzed)
REM   -readOnly:     Don't modify the project

"%GHIDRA_HOME%\support\analyzeHeadless.bat" ^
    "%PROJECT_DIR%" ^
    "%PROJECT_NAME%" ^
    -process "%BINARY_NAME%" ^
    -postScript "%SCRIPT_PATH%" ^
    -noanalysis ^
    -readOnly

set ERRORLEVEL_GHIDRA=!ERRORLEVEL!

echo.
echo ------------------------------------------------------------------------

REM ============================================================================
REM Report Results
REM ============================================================================

if !ERRORLEVEL_GHIDRA! neq 0 (
    echo.
    echo [FAILED] Ghidra export failed with error code: !ERRORLEVEL_GHIDRA!
    echo.
    echo Check the Ghidra output above for error messages.
    exit /b !ERRORLEVEL_GHIDRA!
)

echo.
echo ========================================================================
echo Export Complete!
echo ========================================================================
echo.

REM Count exported files
set FILE_COUNT=0
for %%F in ("%OUTPUT_DIR%\*.json") do set /a FILE_COUNT+=1

echo [OK] Exported %FILE_COUNT% function files
echo.
echo Output locations:
echo   - Individual functions: %OUTPUT_DIR%\*.json
echo   - Summary index:        %PROJECT_ROOT%\asm\pal3\pal3_functions.json
echo.

REM Check if summary was created
if exist "%PROJECT_ROOT%\asm\pal3\pal3_functions.json" (
    echo [OK] Summary file created successfully
) else (
    echo [WARNING] Summary file not found - check Ghidra output for errors
)

echo.
echo ========================================================================
echo Next Steps:
echo   1. Review asm\pal3\pal3_functions.json for summary
echo   2. Browse asm\pal3\functions\ for individual function exports
echo   3. Proceed to Task 3: 函数分类和优先级排序
echo ========================================================================

endlocal
exit /b 0
