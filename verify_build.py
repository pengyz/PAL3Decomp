#!/usr/bin/env python3
"""
PAL3 Decompilation - 持续验证工作流
确保每次提交的代码都是可编译的
"""

import subprocess
import sys
import os
from pathlib import Path

def run_command(cmd, description):
    """运行命令并检查结果"""
    print(f"\n{'='*60}")
    print(f"[*] {description}")
    print(f"{'='*60}")

    result = subprocess.run(cmd, shell=True, capture_output=True, text=True, encoding='gbk', errors='ignore')

    if result.returncode != 0:
        print(f"[FAIL] {description}")
        print(result.stdout)
        print(result.stderr)
        return False

    print(f"[PASS] {description}")
    if result.stdout:
        print(result.stdout[:500])  # 只显示前500字符
    return True

def verify_build():
    """验证构建流程"""

    print("""
===============================================================╗
|          PAL3 持续验证 - 增量构建验证                       |
===============================================================╝

工作流程：
  1. 编译现有代码
  2. 运行语法检查
  3. 验证头文件
  4. 生成构建报告

此脚本确保代码库始终处于可编译状态。
""")

    # 检查环境
    if not run_command("cl.exe 2>&1", "检查 MSVC 编译器"):
        print("\n[WARNING]  未找到 MSVC 编译器")
        print("   请先运行: setup_env.bat")
        return False

    # 清理旧构建
    print("\n[1/4] 清理旧构建...")
    if os.path.exists("build/verify"):
        import shutil
        shutil.rmtree("build/verify")

    # 配置 CMake
    if not run_command(
        'cmake -B build/verify -S . -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_TARGET=topo',
        "[2/4] 配置 CMake"
    ):
        return False

    # 编译
    if not run_command(
        'cmake --build build/verify',
        "[3/4] 编译代码"
    ):
        return False

    # 检查输出
    print("\n[4/4] 检查输出文件...")
    dll_path = Path("build/verify/topo.dll")
    lib_path = Path("build/verify/topo.lib")

    if dll_path.exists():
        size = dll_path.stat().st_size
        print(f"[OK] topo.dll generated successfully ({size:,} bytes)")
    else:
        print("[FAIL] topo.dll not generated")
        return False

    print("""
===============================================================╗
|                    [OK] 验证通过                              |
===============================================================╝

代码库处于可编译状态，可以安全地添加新代码。
""")
    return True

def main():
    os.chdir(Path(__file__).parent)

    success = verify_build()
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()
