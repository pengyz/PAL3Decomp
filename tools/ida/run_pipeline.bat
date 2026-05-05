@echo off
REM PAL3A IDA 反编译质量优化 - 启动器
REM
REM 用法:
REM   run_pipeline.bat "D:\Program Files\IDA Professional 9.2\idat.exe" [options]
REM
REM 选项 (传递给 ida_master_pipeline.py):
REM   --skip-import    跳过结构体导入 (已导入过)
REM   --skip-export    跳过反编译导出
REM   --phase=N        只执行 Phase N (1-5)
REM
REM 示例:
REM   run_pipeline.bat "D:\Program Files\IDA Professional 9.2\idat.exe"
REM   run_pipeline.bat "D:\Program Files\IDA Professional 9.2\idat.exe" --skip-import
REM   run_pipeline.bat "D:\Program Files\IDA Professional 9.2\idat.exe" --phase=4

setlocal

if "%~1"=="" (
    echo 用法: run_pipeline.bat ^<IDA路径^> [options]
    echo.
    echo 示例:
    echo   run_pipeline.bat "D:\Program Files\IDA Professional 9.2\idat.exe"
    echo   run_pipeline.bat "C:\IDA\idat.exe" --skip-import --skip-export
    exit /b 1
)

set IDA_PATH=%~1
shift

REM 收集剩余参数
set EXTRA_ARGS=
:argloop
if "%~1"=="" goto argdone
set EXTRA_ARGS=%EXTRA_ARGS% %1
shift
goto argloop
:argdone

set SCRIPT_DIR=%~dp0
set SCRIPT_PATH=%SCRIPT_DIR%ida_master_pipeline.py
set I64_PATH=%SCRIPT_DIR%..\..\original\PAL3A.exe.i64

echo ================================================================
echo   PAL3A IDA Pipeline
echo ================================================================
echo.

if not exist "%IDA_PATH%" (
    echo [!] IDA 未找到: %IDA_PATH%
    exit /b 1
)

if not exist "%I64_PATH%" (
    echo [!] .i64 未找到: %I64_PATH%
    echo     请确认 original\PAL3A.exe.i64 存在
    exit /b 1
)

echo   IDA:    %IDA_PATH%
echo   DB:     %I64_PATH%
echo   Script: %SCRIPT_PATH%
echo   Args:   %EXTRA_ARGS%
echo.
echo   启动中... (预计 5-15 分钟)
echo.

"%IDA_PATH%" -A -S"\"%SCRIPT_PATH%\"%EXTRA_ARGS%" "%I64_PATH%"

echo.
if %ERRORLEVEL% == 0 (
    echo [+] 完成!
) else (
    echo [!] 异常退出 (code: %ERRORLEVEL%)
)
pause
