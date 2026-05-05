#!/usr/bin/env python3
"""
PAL3 Decompilation - Cross-platform Task Runner

Replaces Makefile with a Python-based CLI that works on both Windows and Linux.

Usage:
    python run.py check                     # 检查环境
    python run.py pe-info                   # 分析 PAL3.exe
    python run.py imports                   # 解析导入表
    python run.py stubs                     # 生成第三方库 stub 头文件
    python run.py progress                  # 查看进度
    python run.py queue                     # 推荐处理队列
    python run.py decompile <json_file>     # 单函数 AI 反编译
    python run.py decompile <json> --dry-run
    python run.py batch [--count 5]         # 批量 AI 反编译
    python run.py compare <src> <addr> <size>  # 编译对比
    python run.py rename                    # 函数命名建议
    python run.py clean                     # 清理构建产物
"""

import os
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.resolve()
TOOLS_DIR = PROJECT_ROOT / "tools"
BUILD_DIR = PROJECT_ROOT / "build"


def python_exe():
    """Return the current Python interpreter path."""
    return sys.executable


def run_tool(script_name, args=None):
    """Run a tool script with given arguments."""
    script = TOOLS_DIR / script_name
    cmd = [python_exe(), str(script)] + (args or [])
    return subprocess.run(cmd, cwd=str(PROJECT_ROOT))


def cmd_check():
    """检查环境是否就绪"""
    run_tool("configure.py", ["check"])


def cmd_init():
    """初始化项目（首次）"""
    run_tool("configure.py", ["init"])


def cmd_setup_ghidra(args):
    """安装 Ghidra + Java"""
    extra = []
    if "--check" in args:
        extra.append("--check")
    if "--java-only" in args:
        extra.append("--java-only")
    if "--skip-java" in args:
        extra.append("--skip-java")
    run_tool("setup_ghidra.py", extra)


def cmd_pe_info():
    """分析 PAL3.exe PE 头（编译器检测）"""
    run_tool("configure.py", ["pe-info"])


def cmd_imports():
    """解析导入表 + 识别第三方库"""
    run_tool("analyze_imports.py")


def cmd_stubs():
    """生成第三方库 stub 头文件"""
    run_tool("analyze_imports.py", ["--generate-stubs"])


def cmd_progress(args):
    extra = []
    if '--target' in args:
        idx = args.index('--target')
        extra.extend(['--target', args[idx + 1]])
    run_tool('progress.py', extra)


def cmd_queue(args):
    """显示推荐处理队列"""
    extra = []
    if "--reasons" in args or "-r" in args:
        extra.append("--show-reasons")
    if "--top" in args:
        idx = args.index("--top")
        if idx + 1 < len(args):
            extra.extend(["--top", args[idx + 1]])
    if "--module" in args or "-m" in args:
        flag = "--module" if "--module" in args else "-m"
        idx = args.index(flag)
        if idx + 1 < len(args):
            extra.extend(["--module", args[idx + 1]])
    run_tool("prioritize.py", extra)


def cmd_decompile(args):
    """单函数 AI 反编译"""
    if not args:
        print("用法: python run.py decompile <json_file> [--dry-run] [--module core]")
        print("")
        print("示例: python run.py decompile asm/FUN_00451a30_00451a30.json")
        print("      python run.py decompile asm/FUN_00451a30_00451a30.json --dry-run")
        sys.exit(1)

    json_file = args[0]
    extra = ["process", "--function", json_file]

    if "--dry-run" in args:
        extra.append("--dry-run")
    if "--module" in args or "-m" in args:
        flag = "--module" if "--module" in args else "-m"
        idx = args.index(flag)
        if idx + 1 < len(args):
            extra.extend(["--module", args[idx + 1]])
    if "--retries" in args or "-r" in args:
        flag = "--retries" if "--retries" in args else "-r"
        idx = args.index(flag)
        if idx + 1 < len(args):
            extra.extend(["--retries", args[idx + 1]])

    run_tool("ai_decompile.py", extra)


def cmd_batch(args):
    """批量 AI 反编译"""
    extra = ["batch"]
    count = "5"

    if "--count" in args or "-c" in args:
        flag = "--count" if "--count" in args else "-c"
        idx = args.index(flag)
        if idx + 1 < len(args):
            count = args[idx + 1]
    extra.extend(["--max-count", count])

    if "--dry-run" in args:
        extra.append("--dry-run")
    if "--module" in args or "-m" in args:
        flag = "--module" if "--module" in args else "-m"
        idx = args.index(flag)
        if idx + 1 < len(args):
            extra.extend(["--module", args[idx + 1]])

    run_tool("ai_decompile.py", extra)


def cmd_compare(args):
    """编译对比"""
    if len(args) < 3:
        print("用法: python run.py compare <源文件> <地址> <大小>")
        print("")
        print("示例: python run.py compare src/core/math.c 0x00401000 128")
        sys.exit(1)

    source, addr, size = args[0], args[1], args[2]
    extra = ["--source", source, "--func-addr", addr, "--func-size", size]

    if len(args) > 3:
        extra.extend(["--func-name", args[3]])

    run_tool("compare.py", extra)


def cmd_batch_compare():
    """批量编译对比所有已反编译函数"""
    # First generate batch config
    run_tool("gen_batch.py")
    # Then run comparison
    batch_file = str(BUILD_DIR / "batch_compare.json")
    if Path(batch_file).exists():
        run_tool("compare.py", ["--batch", batch_file])
    else:
        print("没有可对比的函数（batch_compare.json 为空）")


def cmd_rename(args):
    """函数命名建议"""
    extra = []
    if "--apply" in args:
        extra.append("--apply")
    run_tool("rename_helper.py", extra)


def cmd_status():
    """显示 AI 处理状态"""
    run_tool("ai_decompile.py", ["status"])


def cmd_clean():
    """清理构建产物"""
    import shutil

    patterns = ["*.obj", "*.asm", "*.map", "*.pdb", "*.ilk"]
    removed = 0

    if BUILD_DIR.exists():
        # Remove compare results
        results_dir = BUILD_DIR / "compare_results"
        if results_dir.exists():
            shutil.rmtree(results_dir)
            removed += 1

        # Remove object files
        for pattern in patterns:
            for f in BUILD_DIR.glob(pattern):
                f.unlink()
                removed += 1

    print("已清理 {} 个构建产物".format(removed))


def cmd_clean_all():
    """清理所有构建目录"""
    import shutil
    if BUILD_DIR.exists():
        shutil.rmtree(BUILD_DIR)
    print("已清理 build/ 目录")


def print_help():
    """打印帮助信息"""
    print("""
PAL3 反编译项目 - 跨平台任务运行器
===================================

用法: python run.py <命令> [参数...]

环境/初始化:
  init                          初始化项目（首次）
  check                         检查工具链是否就绪
  setup-ghidra                  自动安装 Ghidra + Java
  setup-ghidra --check          仅检查 Ghidra 是否已安装

分析（需要 PAL3.exe）:
  pe-info                       分析 PE 头（编译器检测）
  imports                       解析导入表 + 识别第三方库
  stubs                         生成第三方库 stub 头文件

反编译工作流:
  queue [--reasons] [--top N]   显示推荐处理队列
  progress [--target pal3|pal3a|topo|gbengine]  查看指定目标进度
  status                        查看 AI 处理状态
  decompile <json> [--dry-run]  单函数 AI 反编译
  batch [--count N] [--dry-run] 批量 AI 反编译（默认 5 个）
  compare <src> <addr> <size>   编译 + 逐字节对比
  batch-compare                 批量对比所有已反编译函数

辅助工具:
  rename [--apply]              函数命名建议（--apply 生成 Ghidra 脚本）

清理:
  clean                         清理 .obj 等构建产物
  clean-all                     删除整个 build/ 目录

示例:
  python run.py check
  python run.py decompile asm/FUN_00451a30_00451a30.json --dry-run
  python run.py batch --count 10
  python run.py compare src/core/math.c 0x00401000 128
""")


def main():
    if len(sys.argv) < 2:
        print_help()
        sys.exit(0)

    command = sys.argv[1]
    args = sys.argv[2:]

    commands = {
        "help":          lambda: print_help(),
        "--help":        lambda: print_help(),
        "-h":            lambda: print_help(),
        "init":          lambda: cmd_init(),
        "check":         lambda: cmd_check(),
        "setup-ghidra":  lambda: cmd_setup_ghidra(args),
        "pe-info":       lambda: cmd_pe_info(),
        "imports":       lambda: cmd_imports(),
        "stubs":         lambda: cmd_stubs(),
        "progress":      lambda: cmd_progress(args),
        "status":        lambda: cmd_status(),
        "queue":         lambda: cmd_queue(args),
        "decompile":     lambda: cmd_decompile(args),
        "batch":         lambda: cmd_batch(args),
        "compare":       lambda: cmd_compare(args),
        "batch-compare": lambda: cmd_batch_compare(),
        "rename":        lambda: cmd_rename(args),
        "clean":         lambda: cmd_clean(),
        "clean-all":     lambda: cmd_clean_all(),
    }

    if command in commands:
        commands[command]()
    else:
        print("未知命令: {}".format(command))
        print("运行 'python run.py help' 查看可用命令")
        sys.exit(1)


if __name__ == "__main__":
    main()
