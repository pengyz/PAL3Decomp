#!/usr/bin/env python3
"""
PAL3Decomp Toolchain Abstraction
=================================

类似 CMake 的 toolchain file，但面向 Python 脚本层。
集中处理平台差异（Windows 原生 / Linux + Wine / macOS + Wine），
对外提供统一的工具调用接口。

设计原则：
  - 所有逻辑脚本只 import 本模块，不再关心平台
  - 路径转换、Wine 前缀、工具定位等细节全部在此封装
  - 通过 local_config.json 可覆盖默认工具路径

用法：
    from toolchain import ToolChain
    tc = ToolChain()

    # 编译
    tc.cl('/c', '/O2', '/GX', f'/Fo{obj}', src)

    # 链接
    tc.link('/DLL', f'/OUT:{dll}', obj1, obj2)

    # 反混淆
    tc.undname(mangled_names)  -> list of demangled

    # 导出表
    tc.dumpbin('/EXPORTS', dll_path) -> stdout text

    # 生成 .lib
    tc.lib(f'/DEF:{def_file}', f'/OUT:{lib_file}', '/MACHINE:X86')

    # 单文件编译（高级封装）
    result = tc.compile_obj(src_path, obj_path, flags=['/O2', '/GX'])
"""

import json
import os
import platform
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import List, Optional, Tuple

# ---------------------------------------------------------------------------
# Constants
# ---------------------------------------------------------------------------

PROJECT_ROOT = Path(__file__).parent.parent
VC6_ROOT = PROJECT_ROOT / "tools" / "vc6"
VC6_BIN = VC6_ROOT / "Bin"
VC6_INCLUDE = VC6_ROOT / "Include"
VC6_LIB = VC6_ROOT / "Lib"

LOCAL_CONFIG_FILE = PROJECT_ROOT / "local_config.json"


# ---------------------------------------------------------------------------
# Platform detection
# ---------------------------------------------------------------------------

class Platform:
    WINDOWS = "windows"
    LINUX = "linux"
    MACOS = "macos"

    @staticmethod
    def current():
        s = platform.system().lower()
        if s == "windows":
            return Platform.WINDOWS
        elif s == "linux":
            return Platform.LINUX
        elif s == "darwin":
            return Platform.MACOS
        return s


# ---------------------------------------------------------------------------
# Path utilities
# ---------------------------------------------------------------------------

def to_winpath(path) -> str:
    """Convert a Unix/local path to a Wine-compatible Windows path (Z:\\...)."""
    p = str(Path(path).resolve())
    return "Z:" + p.replace("/", "\\")


def to_winpath_slash(path) -> str:
    """Convert to Wine path using forward slashes (some tools accept this)."""
    p = str(Path(path).resolve())
    return "Z:" + p


# ---------------------------------------------------------------------------
# ToolChain class
# ---------------------------------------------------------------------------

class ToolChain:
    """
    Unified toolchain interface.

    Auto-detects platform and wraps VC6 tools with Wine when needed.
    Tool paths can be overridden via local_config.json "toolchain" section.
    """

    def __init__(self, config_path: Optional[Path] = None):
        self.platform = Platform.current()
        self.use_wine = self.platform != Platform.WINDOWS
        self.project_root = PROJECT_ROOT
        self.vc6_root = VC6_ROOT

        # Load user overrides
        cfg_path = config_path or LOCAL_CONFIG_FILE
        self._user_config = {}
        if cfg_path.exists():
            try:
                with open(cfg_path, 'r', encoding='utf-8') as f:
                    data = json.load(f)
                self._user_config = data.get("toolchain", {})
            except (json.JSONDecodeError, KeyError):
                pass

        # Tool paths (can be overridden)
        self._cl = self._resolve_tool("cl", VC6_BIN / "CL.EXE")
        self._link = self._resolve_tool("link", VC6_BIN / "LINK.EXE")
        self._lib = self._resolve_tool("lib", VC6_BIN / "LIB.EXE")
        self._dumpbin = self._resolve_tool("dumpbin", VC6_BIN / "DUMPBIN.EXE")
        self._undname = self._resolve_tool("undname", VC6_BIN / "UNDNAME.EXE")
        self._nmake = self._resolve_tool("nmake", VC6_BIN / "NMAKE.EXE")

        # Include/Lib paths
        self._include_dirs = [VC6_INCLUDE, PROJECT_ROOT / "include"]
        self._lib_dirs = [VC6_LIB]

        # Wine environment
        self._wine_env = {"WINEDEBUG": "-all"}

    def _resolve_tool(self, name: str, default: Path) -> Path:
        """Resolve tool path from user config or default."""
        override = self._user_config.get(name)
        if override:
            p = Path(override)
            if p.exists():
                return p
        return default

    def _build_env(self, extra_env=None) -> dict:
        """Build environment for subprocess calls."""
        env = os.environ.copy()
        if self.use_wine:
            env.update(self._wine_env)
        else:
            # Windows: set INCLUDE/LIB for cl.exe
            env["INCLUDE"] = ";".join(str(d) for d in self._include_dirs)
            env["LIB"] = ";".join(str(d) for d in self._lib_dirs)
        if extra_env:
            env.update(extra_env)
        return env

    def _make_cmd(self, tool_path: Path, args: tuple) -> list:
        """Build command list, prepending 'wine' if needed."""
        if self.use_wine:
            return ["wine", str(tool_path)] + list(args)
        else:
            return [str(tool_path)] + list(args)

    def _convert_path_arg(self, arg: str) -> str:
        """
        If running under Wine, convert path arguments to Wine format.
        Detects arguments that look like file paths (contain / or absolute).
        """
        if not self.use_wine:
            return arg

        # Don't convert flag arguments
        if arg.startswith("/") and not os.path.exists(arg):
            # Could be a compiler flag like /O2, /c, etc.
            # Heuristic: if it's 1-4 chars after /, it's a flag
            rest = arg[1:]
            if len(rest) <= 4 and not "/" in rest:
                return arg
            # Flags with values like /Fo<path>, /I<path>, /LIBPATH:<path>
            for prefix in ("/Fo", "/Fe", "/Fd", "/Fm", "/Fa", "/Fp", "/FR",
                           "/I", "/AI"):
                if arg.startswith(prefix) and len(arg) > len(prefix):
                    value = arg[len(prefix):]
                    if os.path.sep in value or value.startswith("/"):
                        return prefix + to_winpath(value)
                    return arg
            # /LIBPATH:, /DEF:, /OUT:, /MAP:, /PDB:
            for prefix in ("/LIBPATH:", "/DEF:", "/OUT:", "/MAP:", "/PDB:",
                           "/IMPLIB:"):
                if arg.upper().startswith(prefix):
                    value = arg[len(prefix):]
                    if value and (os.path.sep in value or value.startswith("/")):
                        return arg[:len(prefix)] + to_winpath(value)
                    return arg
            return arg

        # Bare path (source files, obj files)
        if "/" in arg and not arg.startswith("-"):
            # Looks like a Unix path
            if os.path.exists(arg) or os.path.exists(os.path.dirname(arg)):
                return to_winpath(arg)

        return arg

    def _run_tool(self, tool_path: Path, args: tuple,
                  capture=True, check=False, encoding='latin-1',
                  timeout=120, convert_paths=True) -> subprocess.CompletedProcess:
        """
        Run a tool with platform-appropriate wrapping.

        Args:
            tool_path: Path to the .EXE tool
            args: Arguments to pass
            capture: Capture stdout/stderr
            check: Raise on non-zero exit
            encoding: Output encoding (latin-1 for MSVC tools)
            timeout: Timeout in seconds
            convert_paths: Auto-convert path arguments for Wine
        """
        if convert_paths and self.use_wine:
            converted_args = tuple(self._convert_path_arg(str(a)) for a in args)
        else:
            converted_args = args

        cmd = self._make_cmd(tool_path, converted_args)
        env = self._build_env()

        result = subprocess.run(
            cmd,
            capture_output=capture,
            text=True,
            encoding=encoding,
            errors='replace',
            env=env,
            timeout=timeout,
        )

        if check and result.returncode != 0:
            raise subprocess.CalledProcessError(
                result.returncode, cmd,
                output=result.stdout, stderr=result.stderr
            )

        return result

    # -------------------------------------------------------------------
    # Public tool interfaces
    # -------------------------------------------------------------------

    def cl(self, *args, **kwargs) -> subprocess.CompletedProcess:
        """Run CL.EXE (compiler) with given arguments."""
        return self._run_tool(self._cl, args, **kwargs)

    def link(self, *args, **kwargs) -> subprocess.CompletedProcess:
        """Run LINK.EXE (linker) with given arguments."""
        return self._run_tool(self._link, args, **kwargs)

    def lib(self, *args, **kwargs) -> subprocess.CompletedProcess:
        """Run LIB.EXE (library manager) with given arguments."""
        return self._run_tool(self._lib, args, **kwargs)

    def dumpbin(self, *args, **kwargs) -> subprocess.CompletedProcess:
        """Run DUMPBIN.EXE (binary inspector) with given arguments."""
        return self._run_tool(self._dumpbin, args, **kwargs)

    def nmake(self, *args, **kwargs) -> subprocess.CompletedProcess:
        """Run NMAKE.EXE (build tool) with given arguments."""
        return self._run_tool(self._nmake, args, **kwargs)

    def undname(self, mangled_names: List[str]) -> dict:
        """
        Demangle MSVC mangled names.

        Args:
            mangled_names: List of mangled symbol names

        Returns:
            Dict mapping mangled -> demangled (only successful entries)
        """
        if not mangled_names:
            return {}

        # Try undname.exe first
        if self._undname.exists():
            return self._undname_exe(mangled_names)

        # Fallback: regex-based demangling (basic)
        return self._undname_fallback(mangled_names)

    def _undname_exe(self, mangled_names: List[str], batch_size=200) -> dict:
        """Demangle using undname.exe (via Wine if needed)."""
        result = {}

        for i in range(0, len(mangled_names), batch_size):
            batch = mangled_names[i:i + batch_size]

            with tempfile.NamedTemporaryFile(
                mode='w', suffix='.txt', delete=False, encoding='utf-8'
            ) as f:
                for name in batch:
                    f.write(name + '\n')
                tmpfile = f.name

            try:
                # undname.exe expects Windows path for input file
                if self.use_wine:
                    file_arg = to_winpath(tmpfile)
                else:
                    file_arg = tmpfile

                proc = self._run_tool(
                    self._undname, (file_arg,),
                    convert_paths=False, timeout=60
                )

                output_lines = proc.stdout.strip().split('\n')
                for j, line in enumerate(output_lines):
                    if j < len(batch):
                        line = line.strip()
                        if line and line != batch[j]:
                            result[batch[j]] = line
            except Exception as e:
                print(f"  [toolchain] undname batch error at {i}: {e}",
                      file=sys.stderr)
            finally:
                os.unlink(tmpfile)

        return result

    def _undname_fallback(self, mangled_names: List[str]) -> dict:
        """Basic regex fallback for demangling (no undname.exe available)."""
        # Try system c++filt (available on Linux)
        if shutil.which("c++filt"):
            return self._undname_cxxfilt(mangled_names)
        return {}

    def _undname_cxxfilt(self, mangled_names: List[str]) -> dict:
        """Use c++filt for demangling (partial MSVC support)."""
        result = {}
        input_text = "\n".join(mangled_names)
        try:
            proc = subprocess.run(
                ["c++filt", "-n"],
                input=input_text, capture_output=True, text=True, timeout=30
            )
            for orig, demangled in zip(mangled_names, proc.stdout.strip().split('\n')):
                demangled = demangled.strip()
                if demangled and demangled != orig:
                    result[orig] = demangled
        except Exception:
            pass
        return result

    # -------------------------------------------------------------------
    # High-level compilation helpers
    # -------------------------------------------------------------------

    def compile_obj(self, src_path, obj_path, flags=None,
                    extra_includes=None, defines=None) -> Tuple[bool, str]:
        """
        Compile a single source file to .obj.

        Args:
            src_path: Source file path (.cpp/.c)
            obj_path: Output object file path
            flags: Compiler flags (default: /O2 /Ob2 /GF /Gy /Zp4 /GX /MD)
            extra_includes: Additional include directories
            defines: Preprocessor definitions

        Returns:
            (success: bool, error_message: str)
        """
        src_path = Path(src_path)
        obj_path = Path(obj_path)
        obj_path.parent.mkdir(parents=True, exist_ok=True)

        if flags is None:
            flags = ['/O2', '/Ob2', '/GF', '/Gy', '/Zp4', '/GX', '/MD']

        args = ['/nologo', '/c'] + flags

        # Include directories
        all_includes = list(self._include_dirs)
        if extra_includes:
            all_includes.extend(Path(p) for p in extra_includes)

        for inc in all_includes:
            if self.use_wine:
                args.append(f'/I{to_winpath(inc)}')
            else:
                args.append(f'/I{inc}')

        # Defines
        all_defines = defines or ['NDEBUG', 'WIN32', '_WINDOWS', '_MBCS']
        for d in all_defines:
            args.append(f'/D{d}')

        # Output
        if self.use_wine:
            args.append(f'/Fo{to_winpath(obj_path)}')
            args.append(to_winpath(src_path))
        else:
            args.append(f'/Fo{obj_path}')
            args.append(str(src_path))

        result = self._run_tool(self._cl, tuple(args), convert_paths=False)

        if result.returncode != 0:
            return False, result.stderr or result.stdout
        return True, ""

    def gen_import_lib(self, dll_path, lib_path) -> Tuple[bool, str]:
        """
        Generate an import library (.lib) from a DLL.

        Uses DUMPBIN to extract exports, creates a .def, then LIB to produce .lib.

        Returns:
            (success: bool, error_message: str)
        """
        dll_path = Path(dll_path)
        lib_path = Path(lib_path)
        lib_path.parent.mkdir(parents=True, exist_ok=True)

        # Step 1: Extract exports via dumpbin
        result = self.dumpbin('/EXPORTS', str(dll_path))
        if result.returncode != 0:
            return False, f"dumpbin failed: {result.stderr}"

        # Parse exports
        exports = []
        in_exports = False
        empty_count = 0
        for line in result.stdout.splitlines():
            stripped = line.strip()
            if "ordinal hint RVA" in stripped:
                in_exports = True
                empty_count = 0
                continue
            if in_exports:
                if not stripped:
                    empty_count += 1
                    if empty_count > 1:
                        break
                    continue
                empty_count = 0
                parts = stripped.split()
                if len(parts) >= 4:
                    try:
                        ordinal = int(parts[0])
                        name = parts[3]
                        exports.append((ordinal, name))
                    except ValueError:
                        continue

        if not exports:
            return False, "No exports found in DLL"

        # Step 2: Generate .def file
        def_path = lib_path.with_suffix('.def')
        dll_name = dll_path.name
        with open(def_path, 'w') as f:
            f.write(f"LIBRARY {dll_name}\n")
            f.write("EXPORTS\n")
            for ordinal, name in exports:
                f.write(f"    {name} @{ordinal}\n")

        # Step 3: Generate .lib from .def
        result = self.lib(
            f'/DEF:{def_path}', f'/OUT:{lib_path}', '/MACHINE:X86'
        )
        if result.returncode != 0:
            return False, f"lib.exe failed: {result.stderr}"

        if lib_path.exists():
            return True, ""
        return False, f"{lib_path} not created"

    # -------------------------------------------------------------------
    # Info / diagnostics
    # -------------------------------------------------------------------

    def info(self) -> str:
        """Return a summary of the toolchain configuration."""
        lines = [
            "=== PAL3Decomp Toolchain ===",
            f"Platform:   {self.platform}",
            f"Wine:       {'yes' if self.use_wine else 'no (native Windows)'}",
            f"VC6 Root:   {self.vc6_root}",
            f"CL.EXE:     {self._cl} ({'exists' if self._cl.exists() else 'MISSING'})",
            f"LINK.EXE:   {self._link} ({'exists' if self._link.exists() else 'MISSING'})",
            f"LIB.EXE:    {self._lib} ({'exists' if self._lib.exists() else 'MISSING'})",
            f"DUMPBIN:    {self._dumpbin} ({'exists' if self._dumpbin.exists() else 'MISSING'})",
            f"UNDNAME:    {self._undname} ({'exists' if self._undname.exists() else 'MISSING'})",
            f"Include:    {', '.join(str(d) for d in self._include_dirs)}",
            f"Lib:        {', '.join(str(d) for d in self._lib_dirs)}",
            "============================",
        ]
        return "\n".join(lines)

    def check(self) -> bool:
        """Verify the toolchain is functional. Returns True if OK."""
        print(self.info())
        print()

        # Test cl.exe
        print("[*] Testing CL.EXE ...", end=" ")
        try:
            r = self.cl('/nologo', '/help', timeout=10)
            combined = r.stdout + r.stderr
            if "COMPILER OPTIONS" in combined or "Optimizing Compiler" in combined:
                print("OK")
            else:
                print("UNEXPECTED OUTPUT")
                return False
        except Exception as e:
            print(f"FAILED: {e}")
            return False

        # Quick compile test
        print("[*] Quick compile test ...", end=" ")
        test_c = tempfile.NamedTemporaryFile(
            mode='w', suffix='.c', delete=False, dir='/tmp'
        )
        test_c.write("int __cdecl test(int x) { return x + 1; }\n")
        test_c.close()
        test_obj = test_c.name.replace('.c', '.obj')

        try:
            ok, err = self.compile_obj(test_c.name, test_obj, flags=['/O2'])
            if ok and os.path.exists(test_obj):
                print("OK")
            else:
                print(f"FAILED: {err}")
                return False
        finally:
            os.unlink(test_c.name)
            if os.path.exists(test_obj):
                os.unlink(test_obj)

        print()
        print("[OK] Toolchain is functional.")
        return True


# ---------------------------------------------------------------------------
# Singleton for convenience
# ---------------------------------------------------------------------------

_default_tc = None


def get_toolchain() -> ToolChain:
    """Get the default (cached) ToolChain instance."""
    global _default_tc
    if _default_tc is None:
        _default_tc = ToolChain()
    return _default_tc


# Shortcut functions (for simple scripts that just need one tool)
def cl(*args, **kwargs):
    return get_toolchain().cl(*args, **kwargs)

def link(*args, **kwargs):
    return get_toolchain().link(*args, **kwargs)

def lib(*args, **kwargs):
    return get_toolchain().lib(*args, **kwargs)

def dumpbin(*args, **kwargs):
    return get_toolchain().dumpbin(*args, **kwargs)

def undname(names):
    return get_toolchain().undname(names)

def compile_obj(*args, **kwargs):
    return get_toolchain().compile_obj(*args, **kwargs)


# ---------------------------------------------------------------------------
# CLI: python tools/toolchain.py [check|info]
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "check"
    tc = ToolChain()

    if cmd == "info":
        print(tc.info())
    elif cmd == "check":
        ok = tc.check()
        sys.exit(0 if ok else 1)
    else:
        print(f"Usage: python {sys.argv[0]} [check|info]")
        sys.exit(1)
