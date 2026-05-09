#!/usr/bin/env python3
"""
PAL3 Decompilation - Toolchain Checker
Detects and verifies compiler installations
"""

import os
import sys
import subprocess
import json
from pathlib import Path

class Color:
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BLUE = '\033[94m'
    RESET = '\033[0m'
    BOLD = '\033[1m'

def run_command(cmd, capture=True):
    """Run a command and return output"""
    try:
        if capture:
            result = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=5)
            return result.returncode == 0, result.stdout + result.stderr
        else:
            result = subprocess.run(cmd, shell=True, timeout=5)
            return result.returncode == 0, ""
    except:
        return False, ""

def check_visual_studio():
    """Check for Visual Studio installations"""
    print(f"\n{Color.BOLD}Visual Studio Detection:{Color.RESET}")
    print("=" * 60)

    vs_found = []

    # Check for VC++ 6.0
    vc6_paths = [
        r"C:\Program Files\Microsoft Visual Studio\VC98\bin\cl.exe",
        r"C:\Program Files (x86)\Microsoft Visual Studio\VC98\bin\cl.exe"
    ]

    for path in vc6_paths:
        if os.path.exists(path):
            # Get version
            success, output = run_command(f'"{path}" 2>&1')
            if "Version 12.00" in output:
                build = "8804" if "8804" in output else "unknown"
                sp_status = "SP6 ✓" if build == "8804" else "needs SP6 ⚠"
                print(f"  {Color.GREEN}[+] Visual C++ 6.0{Color.RESET}")
                print(f"      Path: {path}")
                print(f"      Build: {build} ({sp_status})")
                vs_found.append(("VC6", path, build))

    # Check for modern VS using vswhere
    vswhere = r"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"
    if os.path.exists(vswhere):
        success, output = run_command(f'"{vswhere}" -latest -property installationPath')
        if success and output.strip():
            vs_path = output.strip()
            year = "2022" if "2022" in vs_path else "2019" if "2019" in vs_path else "2017"
            print(f"  {Color.GREEN}[+] Visual Studio {year}{Color.RESET}")
            print(f"      Path: {vs_path}")
            print(f"      {Color.YELLOW}Note: Modern VS for testing only (no binary match){Color.RESET}")
            vs_found.append((f"VS{year}", vs_path, year))

    if not vs_found:
        print(f"  {Color.RED}[-] No Visual Studio found{Color.RESET}")
        print(f"      See install_msvc.md for installation instructions")

    return vs_found

def check_cmake():
    """Check CMake installation"""
    print(f"\n{Color.BOLD}CMake:{Color.RESET}")
    print("=" * 60)

    success, output = run_command("cmake --version")
    if success:
        version = output.split('\n')[0].split()[-1] if output else "unknown"
        print(f"  {Color.GREEN}[+] CMake found: {version}{Color.RESET}")
        return True
    else:
        print(f"  {Color.RED}[-] CMake not found{Color.RESET}")
        print(f"      Download: https://cmake.org/download/")
        return False

def check_python():
    """Check Python and dependencies"""
    print(f"\n{Color.BOLD}Python Environment:{Color.RESET}")
    print("=" * 60)

    print(f"  {Color.GREEN}[+] Python {sys.version.split()[0]}{Color.RESET}")

    # Check for pefile
    try:
        import pefile
        print(f"  {Color.GREEN}[+] pefile library installed{Color.RESET}")
    except ImportError:
        print(f"  {Color.YELLOW}[!] pefile not installed{Color.RESET}")
        print(f"      Run: pip install pefile")

    return True

def check_game_files():
    """Check for game installation"""
    print(f"\n{Color.BOLD}Game Files:{Color.RESET}")
    print("=" * 60)

    # Check local_config.json
    if not os.path.exists("local_config.json"):
        print(f"  {Color.YELLOW}[!] local_config.json not found{Color.RESET}")
        print(f"      Copy local_config.example.json and edit with game path")
        return False

    # Load config
    try:
        with open("local_config.json") as f:
            config = json.load(f)

        game_dir = config.get("game_dir", "")

        # Check files
        files_to_check = [
            ("PAL3.exe", "Main executable"),
            ("gbengine.dll", "Game engine DLL"),
            ("topo.dll", "Math library DLL")
        ]

        all_found = True
        for filename, desc in files_to_check:
            path = os.path.join(game_dir, filename)
            if os.path.exists(path):
                size = os.path.getsize(path)
                print(f"  {Color.GREEN}[+] {filename:20} {Color.RESET} {size:,} bytes - {desc}")
            else:
                print(f"  {Color.RED}[-] {filename:20}{Color.RESET} NOT FOUND")
                all_found = False

        return all_found

    except Exception as e:
        print(f"  {Color.RED}[-] Error reading config: {e}{Color.RESET}")
        return False

def check_source_files():
    """Check decompiled source files"""
    print(f"\n{Color.BOLD}Source Files:{Color.RESET}")
    print("=" * 60)

    targets = {
        "topo": "src/topo",
        "gbengine": "src/gbengine",
        "pal3": "src/pal3"
    }

    for name, path in targets.items():
        if os.path.exists(path):
            cpp_files = list(Path(path).rglob("*.cpp"))
            c_files = list(Path(path).rglob("*.c"))
            total = len(cpp_files) + len(c_files)

            if total > 0:
                total_lines = 0
                for f in cpp_files + c_files:
                    try:
                        with open(f, encoding='utf-8') as file:
                            total_lines += len(file.readlines())
                    except:
                        pass

                print(f"  {Color.GREEN}[+] {name:10}{Color.RESET} {total:4} files, {total_lines:,} lines")
            else:
                print(f"  {Color.YELLOW}[-] {name:10}{Color.RESET} No source files yet")
        else:
            print(f"  {Color.YELLOW}[-] {name:10}{Color.RESET} Directory not found")

def generate_recommendation():
    """Generate recommended next steps"""
    print(f"\n{Color.BOLD}Recommended Next Steps:{Color.RESET}")
    print("=" * 60)

    # Check what's available
    vs_found = []
    for path in [r"C:\Program Files\Microsoft Visual Studio\VC98\bin\cl.exe",
                 r"C:\Program Files (x86)\Microsoft Visual Studio\VC98\bin\cl.exe"]:
        if os.path.exists(path):
            vs_found.append("VC6")
            break

    vswhere = r"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"
    if os.path.exists(vswhere):
        vs_found.append("MODERN")

    if not vs_found:
        print(f"  1. {Color.YELLOW}Install a compiler{Color.RESET}")
        print(f"     - Quick start: Visual Studio 2022 (see docs/install_msvc.md)")
        print(f"     - Binary match: VC++ 6.0 SP6 (see docs/install_msvc.md)")
        print()
        print(f"  2. After installation, run: test_build.bat")

    elif "VC6" in vs_found:
        print(f"  1. {Color.GREEN}Build topo.dll{Color.RESET} (binary-exact matching)")
        print(f"     setup_env.bat")
        print(f"     build.bat topo")
        print()
        print(f"  2. {Color.GREEN}Verify binary match{Color.RESET}")
        print(f"     python run.py compare src/topo/gbVec3D.cpp 0x10001000 100")

    elif "MODERN" in vs_found:
        print(f"  1. {Color.GREEN}Quick test build{Color.RESET}")
        print(f"     test_build.bat")
        print()
        print(f"  2. {Color.YELLOW}For binary matching, install VC6{Color.RESET}")
        print(f"     See: docs/install_msvc.md")

    print()
    print(f"  Documentation:")
    print(f"     - Toolchain guide: docs/TOOLCHAIN_SETUP.md")
    print(f"     - Installation:    docs/install_msvc.md")
    print(f"     - Compiler setup:  docs/compiler_setup.md")
    print(f"     - Project guide:   CLAUDE.md")

def main():
    print(f"\n{Color.BOLD}{Color.BLUE}")
    print("╔══════════════════════════════════════════════════════════╗")
    print("║   PAL3 Decompilation - Toolchain Configuration Check   ║")
    print("╚══════════════════════════════════════════════════════════╝")
    print(f"{Color.RESET}")

    check_python()
    vs_installations = check_visual_studio()
    has_cmake = check_cmake()
    has_game = check_game_files()
    check_source_files()

    generate_recommendation()

    print()
    print("=" * 60)

    # Summary
    status = []
    if vs_installations:
        status.append(f"{Color.GREEN}OK Compiler{Color.RESET}")
    else:
        status.append(f"{Color.RED}X Compiler{Color.RESET}")

    if has_cmake:
        status.append(f"{Color.GREEN}OK CMake{Color.RESET}")
    else:
        status.append(f"{Color.RED}X CMake{Color.RESET}")

    if has_game:
        status.append(f"{Color.GREEN}OK Game Files{Color.RESET}")
    else:
        status.append(f"{Color.YELLOW}! Game Files{Color.RESET}")

    print(f"Status: {' | '.join(status)}")
    print()

if __name__ == "__main__":
    main()
