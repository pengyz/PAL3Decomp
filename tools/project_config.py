#!/usr/bin/env python3
"""
项目配置读取模块

优先级（从高到低）：
1. 环境变量 PAL3_GAME_DIR
2. local_config.json（用户本地配置，不入 git）
3. build/project_config.json（项目构建配置）

用法：
    from project_config import get_game_dir, get_exe_path, load_config
"""

import json
import os
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
LOCAL_CONFIG_FILE = PROJECT_ROOT / "local_config.json"
BUILD_CONFIG_FILE = PROJECT_ROOT / "build" / "project_config.json"


def load_local_config():
    """读取 local_config.json"""
    if LOCAL_CONFIG_FILE.exists():
        with open(LOCAL_CONFIG_FILE, 'r', encoding='utf-8') as f:
            return json.load(f)
    return {}


def load_build_config():
    """读取 build/project_config.json"""
    if BUILD_CONFIG_FILE.exists():
        with open(BUILD_CONFIG_FILE, 'r', encoding='utf-8') as f:
            return json.load(f)
    return {}


def save_build_config(config):
    """保存到 build/project_config.json"""
    BUILD_CONFIG_FILE.parent.mkdir(parents=True, exist_ok=True)
    with open(BUILD_CONFIG_FILE, 'w', encoding='utf-8') as f:
        json.dump(config, f, indent=2, ensure_ascii=False)


def get_game_dir():
    """获取游戏安装目录

    Returns:
        Path 对象，或 None（如果未配置）
    """
    # 优先级 1: 环境变量
    env_dir = os.environ.get('PAL3_GAME_DIR')
    if env_dir:
        p = Path(env_dir)
        if p.exists():
            return p

    # 优先级 2: local_config.json
    local = load_local_config()
    if 'game_dir' in local:
        p = Path(local['game_dir'])
        if p.exists():
            return p

    # 优先级 3: build/project_config.json
    build = load_build_config()
    if 'game_dir' in build:
        p = Path(build['game_dir'])
        if p.exists():
            return p

    return None


def get_exe_path():
    """获取 PAL3.exe 的完整路径

    Returns:
        Path 对象，或 None
    """
    game_dir = get_game_dir()
    if game_dir is None:
        return None

    # 读取配置中的 exe 名
    local = load_local_config()
    exe_name = local.get('exe_name', 'PAL3.exe')

    exe_path = game_dir / exe_name
    if exe_path.exists():
        return exe_path

    # 尝试大小写不敏感查找
    for f in game_dir.iterdir():
        if f.name.lower() == exe_name.lower():
            return f

    return None


def get_dll_path(dll_name):
    """获取游戏目录中某个 DLL 的路径"""
    game_dir = get_game_dir()
    if game_dir is None:
        return None

    dll_path = game_dir / dll_name
    if dll_path.exists():
        return dll_path

    # 大小写不敏感
    for f in game_dir.iterdir():
        if f.name.lower() == dll_name.lower():
            return f

    return None


def require_game_dir():
    """获取游戏目录，不存在则报错退出"""
    game_dir = get_game_dir()
    if game_dir is None:
        print("[!] 未配置游戏安装目录")
        print()
        print("    请通过以下方式之一指定:")
        print()
        print("    方法 1: 创建 local_config.json")
        print('    cp local_config.example.json local_config.json')
        print('    # 然后编辑 game_dir 字段')
        print()
        print("    方法 2: 设置环境变量")
        print('    export PAL3_GAME_DIR="/path/to/PAL3"')
        print()
        sys.exit(1)
    return game_dir


def require_exe_path():
    """获取 exe 路径，不存在则报错退出"""
    exe_path = get_exe_path()
    if exe_path is None:
        game_dir = get_game_dir()
        if game_dir is None:
            require_game_dir()  # will exit
        print("[!] 在游戏目录中未找到 PAL3.exe:")
        print("    {}".format(game_dir))
        sys.exit(1)
    return exe_path


def print_config():
    """打印当前配置状态"""
    print("项目配置:")
    print("  项目根目录: {}".format(PROJECT_ROOT))

    game_dir = get_game_dir()
    if game_dir:
        print("  游戏目录:   {}".format(game_dir))
    else:
        print("  游戏目录:   [未配置]")

    exe_path = get_exe_path()
    if exe_path:
        size_mb = exe_path.stat().st_size / (1024 * 1024)
        print("  PAL3.exe:   {} ({:.1f} MB)".format(exe_path, size_mb))
    else:
        print("  PAL3.exe:   [未找到]")

    # Ghidra
    build = load_build_config()
    if 'ghidra_headless' in build:
        print("  Ghidra:     {}".format(build['ghidra_headless']))
    else:
        print("  Ghidra:     [未安装]")


if __name__ == '__main__':
    print_config()
