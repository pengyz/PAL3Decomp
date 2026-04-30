#!/usr/bin/env python3
"""
Ghidra 自动安装脚本（跨平台）

自动完成：
1. 检测/安装 Java JDK 17+
2. 从 GitHub 下载 Ghidra
3. 解压到项目目录
4. 验证 analyzeHeadless 可用
5. 写入配置（路径）

Usage:
    python tools/setup_ghidra.py              # 自动安装
    python tools/setup_ghidra.py --check      # 仅检查是否已安装
    python tools/setup_ghidra.py --java-only  # 仅安装 Java
"""

import argparse
import json
import os
import platform
import shutil
import subprocess
import sys
import tarfile
import urllib.request
import zipfile
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
BUILD_DIR = PROJECT_ROOT / "build"
CONFIG_FILE = BUILD_DIR / "project_config.json"

# Ghidra 版本配置
GHIDRA_VERSION = "11.2.1"
GHIDRA_DATE = "20241105"
GHIDRA_BASE_URL = "https://github.com/NationalSecurityAgency/ghidra/releases/download"

# 默认安装位置
DEFAULT_INSTALL_DIR = PROJECT_ROOT / "tools" / "ghidra"

# Java 最低版本
JAVA_MIN_VERSION = 17


def get_system_info():
    """获取系统信息"""
    system = platform.system().lower()  # 'linux', 'windows', 'darwin'
    machine = platform.machine().lower()  # 'x86_64', 'amd64', 'aarch64'

    # 标准化架构名
    if machine in ('x86_64', 'amd64'):
        arch = 'x64'
    elif machine in ('aarch64', 'arm64'):
        arch = 'arm64'
    else:
        arch = machine

    return system, arch


def get_ghidra_download_url():
    """构造 Ghidra 下载 URL"""
    # Ghidra 发布命名格式: ghidra_VERSION_PUBLIC_YYYYMMDD.zip
    filename = "ghidra_{}_PUBLIC_{}.zip".format(GHIDRA_VERSION, GHIDRA_DATE)
    url = "{}/Ghidra_{}_build/{}".format(GHIDRA_BASE_URL, GHIDRA_VERSION, filename)
    return url, filename


def check_java():
    """检查 Java 是否已安装且版本足够"""
    # 尝试多个可能的命令
    java_cmds = ['java']

    # 检查 JAVA_HOME
    java_home = os.environ.get('JAVA_HOME')
    if java_home:
        java_bin = Path(java_home) / "bin" / "java"
        if platform.system() == 'Windows':
            java_bin = java_bin.with_suffix('.exe')
        java_cmds.insert(0, str(java_bin))

    for java_cmd in java_cmds:
        try:
            result = subprocess.run(
                [java_cmd, '-version'],
                capture_output=True, text=True, timeout=10
            )
            output = result.stderr + result.stdout  # java -version 输出到 stderr

            # 解析版本号
            # 格式: openjdk version "17.0.8" 或 java version "1.8.0_xxx"
            import re
            match = re.search(r'version "(\d+)', output)
            if match:
                version = int(match.group(1))
                # Java 8 报告为 "1.8"，Java 9+ 直接报主版本号
                if version == 1:
                    match2 = re.search(r'version "1\.(\d+)', output)
                    if match2:
                        version = int(match2.group(1))

                return java_cmd, version, output.strip().split('\n')[0]

        except (FileNotFoundError, subprocess.TimeoutExpired, OSError):
            continue

    return None, 0, ""


def check_ghidra(install_dir=None):
    """检查 Ghidra 是否已安装"""
    # 检查已知路径
    search_paths = []

    if install_dir:
        search_paths.append(Path(install_dir))

    search_paths.append(DEFAULT_INSTALL_DIR)

    # 检查 PATH 中的 analyzeHeadless
    analyze_cmd = 'analyzeHeadless.bat' if platform.system() == 'Windows' else 'analyzeHeadless'
    if shutil.which(analyze_cmd):
        return shutil.which(analyze_cmd), True

    # 搜索已知安装目录
    for base in search_paths:
        if not base.exists():
            continue
        # Ghidra 解压后目录名类似 ghidra_11.2.1_PUBLIC
        for entry in base.iterdir():
            if entry.is_dir() and entry.name.startswith('ghidra_'):
                support_dir = entry / "support"
                if platform.system() == 'Windows':
                    headless = support_dir / "analyzeHeadless.bat"
                else:
                    headless = support_dir / "analyzeHeadless"
                if headless.exists():
                    return str(headless), True

        # 也可能直接就是 ghidra 目录
        support_dir = base / "support"
        if platform.system() == 'Windows':
            headless = support_dir / "analyzeHeadless.bat"
        else:
            headless = support_dir / "analyzeHeadless"
        if headless.exists():
            return str(headless), True

    return None, False


def install_java_linux():
    """在 Linux 上安装 Java JDK"""
    print("[*] 尝试安装 Java JDK {}+ ...".format(JAVA_MIN_VERSION))

    # 检测包管理器
    if shutil.which('apt'):
        # Debian/Ubuntu
        pkg = "openjdk-{}-jdk".format(JAVA_MIN_VERSION)
        print("[*] 检测到 apt，安装 {}".format(pkg))
        print("[*] 需要 sudo 权限...")
        cmd = ['sudo', 'apt', 'install', '-y', pkg]
    elif shutil.which('dnf'):
        # Fedora/RHEL
        pkg = "java-{}-openjdk-devel".format(JAVA_MIN_VERSION)
        print("[*] 检测到 dnf，安装 {}".format(pkg))
        cmd = ['sudo', 'dnf', 'install', '-y', pkg]
    elif shutil.which('pacman'):
        # Arch
        pkg = "jdk17-openjdk"
        print("[*] 检测到 pacman，安装 {}".format(pkg))
        cmd = ['sudo', 'pacman', '-S', '--noconfirm', pkg]
    else:
        print("[!] 无法检测包管理器，请手动安装 JDK 17+")
        print("    推荐: https://adoptium.net/")
        return False

    result = subprocess.run(cmd)
    return result.returncode == 0


def install_java_windows():
    """在 Windows 上安装 Java JDK"""
    print("[*] 尝试安装 Java JDK...")

    # 尝试 winget
    if shutil.which('winget'):
        print("[*] 使用 winget 安装 Eclipse Temurin JDK 17...")
        result = subprocess.run([
            'winget', 'install', '-e',
            '--id', 'EclipseAdoptium.Temurin.17.JDK',
            '--accept-package-agreements', '--accept-source-agreements'
        ])
        if result.returncode == 0:
            return True

    # 尝试 choco
    if shutil.which('choco'):
        print("[*] 使用 choco 安装 Temurin JDK 17...")
        result = subprocess.run([
            'choco', 'install', 'temurin17', '-y'
        ])
        if result.returncode == 0:
            return True

    # 尝试 scoop
    if shutil.which('scoop'):
        print("[*] 使用 scoop 安装 JDK...")
        subprocess.run(['scoop', 'bucket', 'add', 'java'])
        result = subprocess.run(['scoop', 'install', 'temurin17-jdk'])
        if result.returncode == 0:
            return True

    print("[!] 无法自动安装 Java，请手动下载:")
    print("    https://adoptium.net/temurin/releases/?version=17")
    return False


def install_java():
    """安装 Java JDK"""
    system, _ = get_system_info()
    if system == 'linux':
        return install_java_linux()
    elif system == 'windows':
        return install_java_windows()
    elif system == 'darwin':
        # macOS
        if shutil.which('brew'):
            print("[*] 使用 brew 安装 JDK 17...")
            result = subprocess.run(['brew', 'install', 'openjdk@17'])
            return result.returncode == 0
        else:
            print("[!] 请安装 Homebrew 后重试，或手动安装 JDK 17")
            print("    https://adoptium.net/")
            return False
    else:
        print("[!] 不支持的系统: {}".format(system))
        return False


def download_file(url, dest_path, desc=""):
    """下载文件（带进度显示）"""
    print("[*] 下载: {}".format(desc or url))
    print("    保存到: {}".format(dest_path))

    def progress_hook(block_num, block_size, total_size):
        downloaded = block_num * block_size
        if total_size > 0:
            percent = min(100, downloaded * 100 // total_size)
            mb_done = downloaded / (1024 * 1024)
            mb_total = total_size / (1024 * 1024)
            sys.stdout.write(
                "\r    [{:50s}] {:.1f}/{:.1f} MB ({:d}%)".format(
                    '#' * (percent // 2), mb_done, mb_total, percent))
            sys.stdout.flush()

    try:
        urllib.request.urlretrieve(url, dest_path, reporthook=progress_hook)
        print()  # newline after progress bar
        return True
    except Exception as e:
        print("\n[!] 下载失败: {}".format(e))
        return False


def install_ghidra(install_dir=None):
    """下载并安装 Ghidra"""
    if install_dir is None:
        install_dir = DEFAULT_INSTALL_DIR

    install_dir = Path(install_dir)
    install_dir.mkdir(parents=True, exist_ok=True)

    url, filename = get_ghidra_download_url()

    # 下载
    zip_path = install_dir / filename
    if zip_path.exists():
        print("[*] 已有下载文件: {}".format(zip_path))
    else:
        print("[*] 正在从 GitHub 下载 Ghidra {}...".format(GHIDRA_VERSION))
        print("    URL: {}".format(url))
        if not download_file(url, str(zip_path), "Ghidra {}".format(GHIDRA_VERSION)):
            # 备选：提示手动下载
            print()
            print("[!] 自动下载失败。请手动下载:")
            print("    {}".format(url))
            print("    保存到: {}".format(zip_path))
            print("    然后重新运行此脚本")
            return None

    # 解压
    print("[*] 解压中...")
    try:
        with zipfile.ZipFile(str(zip_path), 'r') as zf:
            # 获取顶层目录名
            top_dirs = set()
            for name in zf.namelist():
                parts = name.split('/')
                if parts[0]:
                    top_dirs.add(parts[0])

            ghidra_dir_name = None
            for d in top_dirs:
                if d.startswith('ghidra_'):
                    ghidra_dir_name = d
                    break

            extract_to = install_dir
            ghidra_path = extract_to / ghidra_dir_name if ghidra_dir_name else extract_to

            if ghidra_path.exists():
                print("[*] 目标目录已存在，跳过解压: {}".format(ghidra_path))
            else:
                zf.extractall(str(extract_to))
                print("[*] 解压完成: {}".format(ghidra_path))

    except zipfile.BadZipFile:
        print("[!] ZIP 文件损坏，删除后重试")
        zip_path.unlink()
        return None

    # 设置执行权限（Linux/macOS）
    if platform.system() != 'Windows':
        support_dir = ghidra_path / "support"
        for script in support_dir.glob("*"):
            if not script.suffix:  # no extension = shell script
                script.chmod(script.stat().st_mode | 0o755)
        # ghidraRun 也需要
        ghidra_run = ghidra_path / "ghidraRun"
        if ghidra_run.exists():
            ghidra_run.chmod(ghidra_run.stat().st_mode | 0o755)

    # 验证
    headless_path, found = check_ghidra(str(install_dir))
    if found:
        print("[+] Ghidra 安装成功!")
        print("    analyzeHeadless: {}".format(headless_path))
        return headless_path
    else:
        print("[!] 安装完成但无法找到 analyzeHeadless")
        return None


def save_config(ghidra_path, java_cmd=None):
    """保存 Ghidra 路径到项目配置"""
    BUILD_DIR.mkdir(parents=True, exist_ok=True)

    config = {}
    if CONFIG_FILE.exists():
        with open(CONFIG_FILE) as f:
            config = json.load(f)

    config['ghidra_headless'] = ghidra_path
    if java_cmd:
        config['java_cmd'] = java_cmd

    # 推断 Ghidra 根目录
    headless = Path(ghidra_path)
    if headless.parent.name == 'support':
        config['ghidra_home'] = str(headless.parent.parent)

    with open(CONFIG_FILE, 'w') as f:
        json.dump(config, f, indent=2)

    print("[*] 配置已保存到: {}".format(CONFIG_FILE))


def run_check():
    """仅检查安装状态"""
    print()
    print("=" * 55)
    print("  Ghidra 环境检查")
    print("=" * 55)
    print()

    # Java
    java_cmd, java_ver, java_info = check_java()
    if java_cmd and java_ver >= JAVA_MIN_VERSION:
        print("  [+] Java:   OK (版本 {})".format(java_ver))
        print("              {}".format(java_info))
    elif java_cmd:
        print("  [!] Java:   版本过低 (当前 {}，需要 {}+)".format(java_ver, JAVA_MIN_VERSION))
    else:
        print("  [!] Java:   未安装")

    # Ghidra
    ghidra_path, found = check_ghidra()
    if found:
        print("  [+] Ghidra: OK")
        print("              {}".format(ghidra_path))
    else:
        print("  [!] Ghidra: 未安装")
        print("              运行 'python tools/setup_ghidra.py' 安装")

    print()
    print("=" * 55)

    return found and java_cmd and java_ver >= JAVA_MIN_VERSION


def run_install(args):
    """执行安装"""
    print()
    print("=" * 55)
    print("  Ghidra 自动安装")
    print("=" * 55)
    print()

    system, arch = get_system_info()
    print("  系统: {} ({})".format(system, arch))
    print()

    # Step 1: Java
    java_cmd, java_ver, java_info = check_java()
    if java_cmd and java_ver >= JAVA_MIN_VERSION:
        print("[+] Java 已安装: {} (版本 {})".format(java_info, java_ver))
    else:
        if java_cmd:
            print("[!] Java 版本过低: {} (需要 {}+)".format(java_ver, JAVA_MIN_VERSION))
        else:
            print("[!] Java 未安装")

        if args.java_only or not args.skip_java:
            print()
            success = install_java()
            if not success:
                print("[!] Java 安装失败，请手动安装后重试")
                if not args.java_only:
                    print("    或使用 --skip-java 跳过此步骤")
                sys.exit(1)
            # Re-check
            java_cmd, java_ver, java_info = check_java()
            if not java_cmd or java_ver < JAVA_MIN_VERSION:
                print("[!] Java 安装后仍无法检测到，可能需要重启终端")
                print("    请重启终端后再运行此脚本")
                sys.exit(1)
            print("[+] Java 安装成功: 版本 {}".format(java_ver))

    if args.java_only:
        return

    # Step 2: Ghidra
    print()
    ghidra_path, found = check_ghidra(args.install_dir)
    if found:
        print("[+] Ghidra 已安装: {}".format(ghidra_path))
    else:
        print("[*] 开始安装 Ghidra...")
        print()
        ghidra_path = install_ghidra(args.install_dir)
        if not ghidra_path:
            print("[!] Ghidra 安装失败")
            sys.exit(1)

    # Step 3: 保存配置
    save_config(ghidra_path, java_cmd)

    print()
    print("=" * 55)
    print("  安装完成!")
    print("=" * 55)
    print()
    print("  下一步:")
    print("    1. 将 PAL3.exe 放入 original/ 目录")
    print("    2. 运行: python run.py pe-info")
    print("    3. 创建 Ghidra 项目并导入 PAL3.exe:")
    print()

    # 给出具体命令
    if platform.system() == 'Windows':
        headless_cmd = ghidra_path
    else:
        headless_cmd = ghidra_path

    print('    {} /tmp/ghidra_project PAL3 \\'.format(headless_cmd))
    print('      -import original/PAL3.exe \\')
    print('      -processor x86:LE:32:default \\')
    print('      -postScript tools/initial_analysis.py')
    print()


def main():
    global GHIDRA_VERSION, GHIDRA_DATE

    parser = argparse.ArgumentParser(
        description="Ghidra 自动安装脚本"
    )
    parser.add_argument('--check', action='store_true',
                        help='仅检查安装状态')
    parser.add_argument('--java-only', action='store_true',
                        help='仅安装 Java')
    parser.add_argument('--skip-java', action='store_true',
                        help='跳过 Java 安装')
    parser.add_argument('--install-dir',
                        default=str(DEFAULT_INSTALL_DIR),
                        help='Ghidra 安装目录 (默认: tools/ghidra/)')
    parser.add_argument('--version',
                        help='指定 Ghidra 版本 (默认: {})'.format(GHIDRA_VERSION))

    args = parser.parse_args()

    if args.version:
        GHIDRA_VERSION = args.version
        GHIDRA_DATE = ""  # Will need manual URL if custom version

    if args.check:
        ok = run_check()
        sys.exit(0 if ok else 1)
    else:
        run_install(args)


if __name__ == '__main__':
    main()
