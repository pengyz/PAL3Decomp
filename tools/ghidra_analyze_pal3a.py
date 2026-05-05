#!/usr/bin/env python3
"""
PAL3A.exe Ghidra 反编译导出工具。

使用已有 Ghidra 项目 (asm/pal3a/PAL3A_Project)，
应用 PDB 符号并导出所有 PAL3A 源函数的反编译结果。

用法:
    python tools/ghidra_analyze_pal3a.py --export-all
    python tools/ghidra_analyze_pal3a.py --module script
    python tools/ghidra_analyze_pal3a.py --module gamebase
    python tools/ghidra_analyze_pal3a.py --list-modules
"""

import argparse
import json
import os
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ASM_DIR = PROJECT_ROOT / "asm" / "pal3a"
DECOMP_DIR = ASM_DIR / "decomp"
PDB_EXPORT = ASM_DIR / "pdb_export.json"
GHIDRA_PROJECT_DIR = ASM_DIR
GHIDRA_PROJECT_NAME = "PAL3A_Project"
PDB_PATH = PROJECT_ROOT / "original" / "PAL3A.pdb"
EXE_NAME = "PAL3A.exe"

sys.path.insert(0, str(Path(__file__).parent))
from project_config import load_build_config


def get_ghidra_path():
    """获取 Ghidra analyzeHeadless 路径"""
    config = load_build_config()
    if 'ghidra_headless' in config:
        path = Path(config['ghidra_headless'])
        if path.exists():
            return path

    ghidra_dir = PROJECT_ROOT / "tools" / "ghidra"
    if ghidra_dir.exists():
        for d in sorted(ghidra_dir.iterdir(), reverse=True):
            if d.is_dir():
                candidate = d / "support" / "analyzeHeadless.bat"
                if candidate.exists():
                    return candidate
                candidate = d / "support" / "analyzeHeadless"
                if candidate.exists():
                    return candidate

    import shutil
    path = shutil.which('analyzeHeadless')
    if path:
        return Path(path)
    return None


def load_pdb_export():
    """加载 PDB 导出的函数列表"""
    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        return json.load(f)


def get_module_addresses(module_name):
    """获取指定模块的所有函数地址"""
    data = load_pdb_export()
    prefix = "D:\\PAL3A\\PAL3\\"
    addresses = []

    for func in data['functions']:
        src = func.get('source_file', '')
        if not src.startswith(prefix):
            continue
        rel_path = src[len(prefix):].replace('\\', '/')
        parts = rel_path.split('/')
        if len(parts) > 1:
            mod = parts[0].lower()
        else:
            mod = '(root)'

        if mod == module_name.lower():
            addr = func.get('address', '')
            if addr:
                addresses.append(addr)

    return addresses


def list_modules():
    """列出所有模块及其函数数量"""
    data = load_pdb_export()
    prefix = "D:\\PAL3A\\PAL3\\"
    from collections import Counter
    modules = Counter()

    for func in data['functions']:
        src = func.get('source_file', '')
        if not src.startswith(prefix):
            continue
        if '[thunk]' in func.get('return_type', ''):
            continue
        rel_path = src[len(prefix):].replace('\\', '/')
        parts = rel_path.split('/')
        if len(parts) > 1:
            modules[parts[0].lower()] += 1
        else:
            modules['(root)'] += 1

    print("PAL3A 模块函数统计:")
    print("-" * 40)
    total = 0
    for mod, count in modules.most_common():
        print(f"  {mod:20s} {count:5d}")
        total += count
    print("-" * 40)
    print(f"  {'TOTAL':20s} {total:5d}")


def export_functions(module_filter=None):
    """运行 Ghidra headless 导出反编译结果"""
    ghidra = get_ghidra_path()
    if ghidra is None:
        print("[!] Ghidra 未安装或未配置")
        print("    请在 build/project_config.json 中设置 ghidra_headless 路径")
        sys.exit(1)

    if not PDB_PATH.exists():
        print(f"[!] PDB 文件不存在: {PDB_PATH}")
        sys.exit(1)

    DECOMP_DIR.mkdir(parents=True, exist_ok=True)

    export_script = PROJECT_ROOT / "tools" / "ghidra_export.py"
    pdb_script = PROJECT_ROOT / "tools" / "ghidra" / "set_pdb_and_analyze.py"

    script_args = ['--output-dir', str(DECOMP_DIR)]

    if module_filter:
        addresses = get_module_addresses(module_filter)
        if not addresses:
            print(f"[!] 模块 '{module_filter}' 无函数")
            sys.exit(1)
        addr_file = DECOMP_DIR / f"_addrs_{module_filter}.txt"
        with open(addr_file, 'w') as f:
            for addr in addresses:
                f.write(f"{addr}\n")
        script_args.extend(['--addr-file', str(addr_file)])
        print(f"[*] 导出模块 '{module_filter}': {len(addresses)} 个函数")
    else:
        print("[*] 导出所有 PAL3A 函数")

    print(f"[*] Ghidra: {ghidra}")
    print(f"[*] 项目:   {GHIDRA_PROJECT_DIR}/{GHIDRA_PROJECT_NAME}")
    print(f"[*] PDB:    {PDB_PATH}")
    print(f"[*] 输出:   {DECOMP_DIR}")
    print()

    cmd = [
        str(ghidra),
        str(GHIDRA_PROJECT_DIR),
        GHIDRA_PROJECT_NAME,
        '-process', EXE_NAME,
        '-preScript', str(pdb_script), str(PDB_PATH),
        '-postScript', str(export_script),
    ] + script_args

    print("[*] 正在运行 Ghidra 反编译...")
    print(f"    命令: {' '.join(cmd[:6])} ...")
    print("    （可能需要 5-15 分钟）")
    print()

    result = subprocess.run(cmd, capture_output=True, text=True, timeout=1800)

    if result.returncode != 0:
        print("[!] Ghidra 导出失败:")
        print(result.stderr[-2000:] if len(result.stderr) > 2000 else result.stderr)
        return False

    json_files = list(DECOMP_DIR.glob("*.json"))
    export_files = [f for f in json_files if not f.name.startswith('_')]
    print(f"[+] 导出完成: {len(export_files)} 个函数文件")
    print(f"    目录: {DECOMP_DIR}")

    summary_path = DECOMP_DIR / "_export_summary.json"
    if summary_path.exists():
        with open(summary_path) as f:
            summary = json.load(f)
        print(f"    总函数: {summary.get('total_functions', '?')}")
        print(f"    已导出: {summary.get('exported', '?')}")
        print(f"    错误:   {summary.get('errors', '?')}")

    return True


def main():
    parser = argparse.ArgumentParser(description="PAL3A Ghidra 反编译导出")
    parser.add_argument('--export-all', action='store_true',
                        help='导出所有 PAL3A 函数')
    parser.add_argument('--module', metavar='NAME',
                        help='仅导出指定模块 (script, gamebase, ui, ...)')
    parser.add_argument('--list-modules', action='store_true',
                        help='列出所有模块')
    args = parser.parse_args()

    if args.list_modules:
        list_modules()
        return

    if args.export_all:
        export_functions(module_filter=None)
    elif args.module:
        export_functions(module_filter=args.module)
    else:
        parser.print_help()
        print()
        list_modules()


if __name__ == '__main__':
    main()
