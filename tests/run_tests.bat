@echo off
REM PAL3 Decompilation Test Runner
REM ===============================
REM Runs all automated tests for the PAL3 decompilation project.
REM
REM Prerequisites:
REM   - Python 3.7+ installed
REM   - pytest installed (pip install pytest)
REM
REM Usage:
REM   run_tests.bat           - Run all tests with default verbosity
REM   run_tests.bat -v        - Run with verbose output
REM   run_tests.bat -vv       - Run with very verbose output
REM   run_tests.bat -k test_cmake - Run only tests matching pattern

echo ========================================
echo PAL3 Decompilation Test Suite
echo ========================================
echo.

REM Check if pytest is installed
python -m pytest --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: pytest is not installed
    echo.
    echo Please install pytest:
    echo   pip install pytest
    echo.
    echo Or install all requirements:
    echo   pip install -r requirements.txt pytest
    echo.
    pause
    exit /b 1
)

REM Run pytest with all arguments passed through
echo Running tests...
echo.
python -m pytest tests/ -v --tb=short %*

REM Capture exit code
set EXITCODE=%ERRORLEVEL%

echo.
echo ========================================
if %EXITCODE% equ 0 (
    echo ALL TESTS PASSED
) else (
    echo SOME TESTS FAILED - Exit code: %EXITCODE%
)
echo ========================================
echo.

exit /b %EXITCODE%
