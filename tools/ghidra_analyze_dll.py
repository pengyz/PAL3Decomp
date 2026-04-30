#!/usr/bin/env python3
"""
使用 Ghidra headless 分析 DLL 并导出反编译结果。

此脚本自动化以下流程：
1. 创建 Ghidra 项目（如果不存在）
2. 导入 DLL
3. 运行自动分析
4. 应用已知符号名（从 demangled exports）
5. 导出所有函数的反编译伪代码

用法：
    python ghidra_analyze_dll.py topo.dll       # 分析 topo.dll
    python ghidra_analyze_dll.py gbengine.dll   # 分析 gbengine.dll
    python ghidra_analyze_dll.py --list         # 列出已分析的项目
    python ghidra_analyze_dll.py topo.dll --export-all   # 导出所有函数
    python ghidra_analyze_dll.py topo.dll --export-class gbVec3D  # 导出某个类
"""

import argparse
import json
import os
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
BUILD_DIR = PROJECT_ROOT / "build"
ASM_DIR = PROJECT_ROOT / "asm"

sys.path.insert(0, str(Path(__file__).parent))
from project_config import get_dll_path, load_build_config


def get_ghidra_path():
    """获取 Ghidra analyzeHeadless 路径"""
    # 先检查 build config
    config = load_build_config()
    if 'ghidra_headless' in config:
        path = Path(config['ghidra_headless'])
        if path.exists():
            return path

    # 检查项目目录下的安装
    ghidra_dir = PROJECT_ROOT / "tools" / "ghidra"
    if ghidra_dir.exists():
        for d in sorted(ghidra_dir.iterdir(), reverse=True):
            candidate = d / "support" / "analyzeHeadless"
            if candidate.exists():
                return candidate

    # 检查 PATH
    import shutil
    path = shutil.which('analyzeHeadless')
    if path:
        return Path(path)

    return None


def get_ghidra_project_dir():
    """获取 Ghidra 项目目录"""
    project_dir = BUILD_DIR / "ghidra_projects"
    project_dir.mkdir(parents=True, exist_ok=True)
    return project_dir


def import_dll(dll_name):
    """将 DLL 导入 Ghidra 项目并运行分析"""
    ghidra = get_ghidra_path()
    if ghidra is None:
        print("[!] Ghidra 未安装")
        print("    运行: python tools/setup_ghidra.py")
        sys.exit(1)

    dll_path = get_dll_path(dll_name)
    if dll_path is None:
        print("[!] 未找到 DLL: {}".format(dll_name))
        sys.exit(1)

    project_dir = get_ghidra_project_dir()
    project_name = "PAL3_DLLs"

    print("[*] Ghidra: {}".format(ghidra))
    print("[*] DLL:    {}".format(dll_path))
    print("[*] 项目:   {}/{}".format(project_dir, project_name))
    print()
    print("[*] 正在导入并分析 {} ...".format(dll_name))
    print("    （这可能需要几分钟）")
    print()

    cmd = [
        str(ghidra),
        str(project_dir),
        project_name,
        '-import', str(dll_path),
        '-processor', 'x86:LE:32:default',
        '-cspec', 'windows',
        '-overwrite',
    ]

    result = subprocess.run(cmd, capture_output=True, text=True, timeout=600)

    if result.returncode != 0:
        print("[!] Ghidra 分析失败:")
        print(result.stderr[-2000:] if len(result.stderr) > 2000 else result.stderr)
        return False

    # 摘要信息
    print("[+] 分析完成")
    # 从输出中提取统计
    for line in result.stdout.split('\n'):
        if 'Function' in line or 'function' in line:
            print("    {}".format(line.strip()))

    return True


def export_functions(dll_name, class_filter=None, export_all=False):
    """从 Ghidra 项目导出反编译结果"""
    ghidra = get_ghidra_path()
    if ghidra is None:
        print("[!] Ghidra 未安装")
        sys.exit(1)

    project_dir = get_ghidra_project_dir()
    project_name = "PAL3_DLLs"

    # 确定输出目录
    output_dir = ASM_DIR / dll_name.replace('.dll', '')
    output_dir.mkdir(parents=True, exist_ok=True)

    # 准备 Ghidra 脚本参数
    script_args = ['--output-dir', str(output_dir)]
    if not export_all and class_filter:
        # 从 demangled JSON 中查找该类的函数地址范围
        demangled_path = BUILD_DIR / "{}_demangled.json".format(
            dll_name.replace('.dll', ''))
        if demangled_path.exists():
            with open(demangled_path) as f:
                data = json.load(f)
            class_data = data['classes'].get(class_filter)
            if class_data:
                # 导出指定地址列表
                addrs = [m['rva'] for m in class_data['methods']]
                addr_file = output_dir / "_export_addrs.txt"
                with open(addr_file, 'w') as f:
                    for addr in addrs:
                        f.write("0x{:08X}\n".format(addr))
                script_args.extend(['--addr-file', str(addr_file)])
                print("[*] 导出类 {} 的 {} 个方法".format(
                    class_filter, len(addrs)))
            else:
                print("[!] 类 '{}' 不存在于 {}".format(class_filter, dll_name))
                return False

    # 使用 ghidra_export.py 脚本
    export_script = PROJECT_ROOT / "tools" / "ghidra_export.py"

    cmd = [
        str(ghidra),
        str(project_dir),
        project_name,
        '-process', dll_name,
        '-noanalysis',  # 已经分析过了
        '-postScript', str(export_script),
    ] + script_args

    print("[*] 正在导出反编译结果...")
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=600)

    if result.returncode != 0:
        print("[!] 导出失败:")
        print(result.stderr[-1000:])
        return False

    # 统计导出文件数
    json_files = list(output_dir.glob("*.json"))
    print("[+] 导出完成: {} 个函数文件".format(len(json_files)))
    print("    目录: {}".format(output_dir))
    return True


def list_projects():
    """列出已有的 Ghidra 项目"""
    project_dir = get_ghidra_project_dir()
    print("Ghidra 项目目录: {}".format(project_dir))
    print()

    gpr_files = list(project_dir.glob("*.gpr"))
    if not gpr_files:
        print("  (无项目)")
        return

    for gpr in gpr_files:
        print("  {}".format(gpr.name))
        # 检查对应的 .rep 目录
        rep_dir = gpr.with_suffix('.rep')
        if rep_dir.exists():
            # 列出已导入的文件
            for f in sorted(rep_dir.glob("idata/*")):
                print("    - {}".format(f.name))


def show_export_status():
    """显示各 DLL 的导出状态"""
    print("反编译导出状态:")
    print("-" * 50)

    for dll_name in ['topo', 'gbengine']:
        dll_dir = ASM_DIR / dll_name
        if dll_dir.exists():
            json_files = list(dll_dir.glob("*.json"))
            print("  {}.dll: {} 个函数已导出".format(dll_name, len(json_files)))
        else:
            print("  {}.dll: 未导出".format(dll_name))

        # 检查 demangled 数据
        demangled = BUILD_DIR / "{}_demangled.json".format(dll_name)
        if demangled.exists():
            with open(demangled) as f:
                data = json.load(f)
            print("    符号: {} 个导出, {} 个类".format(
                data['num_exports'], len(data['classes'])))


def main():
    parser = argparse.ArgumentParser(
        description="Ghidra DLL 分析与导出管理")
    parser.add_argument('dll_name', nargs='?',
                        help='DLL 名称 (如 topo.dll 或 gbengine.dll)')
    parser.add_argument('--list', action='store_true',
                        help='列出已有项目')
    parser.add_argument('--status', action='store_true',
                        help='显示导出状态')
    parser.add_argument('--export-all', action='store_true',
                        help='导出所有函数')
    parser.add_argument('--export-class', metavar='CLASS',
                        help='仅导出指定类的方法')
    parser.add_argument('--import-only', action='store_true',
                        help='仅导入，不导出')
    args = parser.parse_args()

    if args.list:
        list_projects()
        return

    if args.status:
        show_export_status()
        return

    if not args.dll_name:
        parser.print_help()
        print()
        show_export_status()
        return

    dll_name = args.dll_name
    if not dll_name.endswith('.dll'):
        dll_name += '.dll'

    # 导入
    if not (get_ghidra_project_dir() / "PAL3_DLLs.gpr").exists():
        import_dll(dll_name)
    elif args.import_only:
        import_dll(dll_name)

    # 导出
    if not args.import_only:
        if args.export_all:
            export_functions(dll_name, export_all=True)
        elif args.export_class:
            export_functions(dll_name, class_filter=args.export_class)


if __name__ == '__main__':
    main()
