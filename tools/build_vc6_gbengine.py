#!/usr/bin/env python3
"""
Automated VC6 build script for gbengine.dll

Compiles all source files with MSVC 6.0 SP5 and links into gbengine.dll.
Outputs to build_vc6/gbengine.dll with base address 0x10000000.

Usage:
    python tools/build_vc6_gbengine.py
    python tools/build_vc6_gbengine.py --clean     # clean and rebuild
    python tools/build_vc6_gbengine.py --verify    # build and compare exports
"""

import argparse
import os
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
SRC_DIR = PROJECT_ROOT / "src" / "gbengine"
VC6_DIR = PROJECT_ROOT / "tools" / "vc6"
VC6_BIN = VC6_DIR / "Bin"
VC6_INCLUDE = VC6_DIR / "Include"
VC6_LIB = VC6_DIR / "Lib"
BUILD_DIR = PROJECT_ROOT / "build_vc6"
INCLUDE_DIR = PROJECT_ROOT / "include"
DEF_FILE = SRC_DIR / "gbengine.def"

CL_EXE = str(VC6_BIN / "CL.EXE")
LINK_EXE = str(VC6_BIN / "LINK.EXE")

CL_FLAGS = [
    "/nologo",
    "/c",
    "/O2",
    "/Oi",
    "/Ob2",
    "/GF",
    "/Gy",
    "/Zp4",
    "/GX",
    "/DWINVER=0x0500",
    "/D_WIN32_WINNT=0x0400",
]

LINK_LIBS = [
    "LIBCMT.LIB",
    "KERNEL32.LIB",
    "USER32.LIB",
    "GDI32.LIB",
    "OLE32.LIB",
    "WINMM.LIB",
    "ADVAPI32.LIB",
    "UUID.LIB",
    "OLDNAMES.LIB",
    "d3d9.lib",
    "d3dx9.lib",
    "dinput8.lib",
    "mss32.lib",
]

EXTRA_LIBS = [
    str(PROJECT_ROOT / "lib" / "ijl15.lib"),
    str(PROJECT_ROOT / "lib" / "topo.lib"),
]

CPP_SOURCES = [
    "BEZIER.cpp",
    "CPK.cpp",
    "d3dframework.cpp",
    "gbAABBox.cpp",
    "gbActor.cpp",
    "gbAudioManager.cpp",
    "gbBaseMesh.cpp",
    "gbBladeMgr.cpp",
    "gbCamera.cpp",
    "gbCameraControl.cpp",
    "gbChain.cpp",
    "gbColorFlt.cpp",
    "gbDropGroup.cpp",
    "gbDynIndexBuf.cpp",
    "gbDynVertBuf.cpp",
    "gbEffectMgr.cpp",
    "gbGeomNode.cpp",
    "gbGfxManager.cpp",
    "gbGfxManager_D3D.cpp",
    "gbGlobals.cpp",
    "gbImage2D.cpp",
    "gbImage2DInfo.cpp",
    "gbIndexBubble.cpp",
    "gbLightObj.cpp",
    "gbMath_extra.cpp",
    "gbMatrix4.cpp",
    "gbMatrixStack.cpp",
    "gbMesh.cpp",
    "gbMisc.cpp",
    "gbNameVarBuf.cpp",
    "gbOBBox.cpp",
    "gbParticle.cpp",
    "gbPixelFormat.cpp",
    "gbPlane.cpp",
    "gbPrintFont.cpp",
    "gbPrintFontMgr.cpp",
    "gbQuaternion.cpp",
    "gbRay.cpp",
    "gbRenderEffect.cpp",
    "gbResManager.cpp",
    "gbRotMatrix.cpp",
    "gbSceneGraph.cpp",
    "gbSoundNode.cpp",
    "gbSphere.cpp",
    "gbTexture.cpp",
    "gbTextureArray.cpp",
    "gbTimeCounter.cpp",
    "gbUIRect.cpp",
    "gbVec3D.cpp",
    "gbVertPool.cpp",
    "gbVertPoolMgr.cpp",
    "gbVFile1.cpp",
    "gbVFileSystem.cpp",
    "gbVisNode.cpp",
    "gbVolModNode.cpp",
    "gbVTextFile.cpp",
    "gbWeather.cpp",
]

C_SOURCES = [
    "lzo/minilzo.c",
]


def is_linux():
    return sys.platform.startswith("linux")


def to_winpath(path):
    return "Z:" + str(Path(path).resolve()).replace("/", "\\")


def compile_file(src_path, obj_path, env):
    """Compile a single source file. Returns True on success."""
    use_wine = is_linux()

    if use_wine:
        cmd = ["wine", CL_EXE]
        cmd += CL_FLAGS
        cmd += [f"/I{to_winpath(VC6_INCLUDE)}", f"/I{to_winpath(INCLUDE_DIR)}"]
        cmd += [f"/Fo{to_winpath(obj_path)}", to_winpath(src_path)]
    else:
        cmd = [CL_EXE]
        cmd += CL_FLAGS
        cmd += [f"/I{VC6_INCLUDE}", f"/I{INCLUDE_DIR}"]
        cmd += [f"/Fo{obj_path}", str(src_path)]

    result = subprocess.run(cmd, capture_output=True, text=True, env=env)
    if result.returncode != 0:
        print(f"  FAILED: {src_path.name}")
        stderr = result.stderr.strip()
        if stderr:
            for line in stderr.split("\n")[:10]:
                print(f"    {line}")
        stdout = result.stdout.strip()
        if stdout:
            for line in stdout.split("\n")[:10]:
                print(f"    {line}")
        return False
    return True


def link_dll(obj_files, output_dll, env):
    """Link all object files into a DLL. Returns True on success."""
    use_wine = is_linux()
    map_file = output_dll.with_suffix(".map")

    link_flags = [
        "/nologo",
        "/DLL",
        "/BASE:0x10000000",
        "/NODEFAULTLIB",
        "/INCREMENTAL:NO",
        f"/DEF:{to_winpath(DEF_FILE) if use_wine else DEF_FILE}",
        f"/OUT:{to_winpath(output_dll) if use_wine else output_dll}",
        f"/MAP:{to_winpath(map_file) if use_wine else map_file}",
    ]

    if use_wine:
        cmd = ["wine", LINK_EXE] + link_flags
        cmd += [to_winpath(f) for f in obj_files]
        cmd += LINK_LIBS
        cmd += [to_winpath(f) for f in EXTRA_LIBS]
    else:
        cmd = [LINK_EXE] + link_flags
        cmd += [str(f) for f in obj_files]
        cmd += LINK_LIBS
        cmd += EXTRA_LIBS

    result = subprocess.run(cmd, capture_output=True, text=True, env=env)
    if result.returncode != 0:
        print(f"  Link FAILED (exit code {result.returncode})")
        stderr = result.stderr.strip()
        if stderr:
            for line in stderr.split("\n")[:20]:
                print(f"    {line}")
        stdout = result.stdout.strip()
        if stdout:
            for line in stdout.split("\n")[:20]:
                print(f"    {line}")
        return False
    return True


def count_exports(dll_path):
    """Count exports using dumpbin or by parsing PE."""
    import struct
    try:
        with open(dll_path, "rb") as f:
            f.seek(0x3C)
            pe_off = struct.unpack("<I", f.read(4))[0]
            f.seek(pe_off + 4 + 20)  # skip PE sig + COFF header
            # Optional header magic
            magic = struct.unpack("<H", f.read(2))[0]
            if magic == 0x10B:  # PE32
                f.seek(pe_off + 4 + 20 + 96)  # export table RVA in data directories
            else:
                return -1
            export_rva = struct.unpack("<I", f.read(4))[0]
            export_size = struct.unpack("<I", f.read(4))[0]
            if export_rva == 0:
                return 0

            # Find section containing export table
            f.seek(pe_off + 4 + 2)
            num_sections_raw = f.read(2)
            num_sections = struct.unpack("<H", num_sections_raw)[0]
            f.seek(pe_off + 4 + 16)
            opt_hdr_size = struct.unpack("<H", f.read(2))[0]
            f.seek(pe_off + 4 + 20 + opt_hdr_size)

            for _ in range(num_sections):
                sec_data = f.read(40)
                virt_size = struct.unpack_from("<I", sec_data, 8)[0]
                virt_addr = struct.unpack_from("<I", sec_data, 12)[0]
                raw_size = struct.unpack_from("<I", sec_data, 16)[0]
                raw_offset = struct.unpack_from("<I", sec_data, 20)[0]
                if virt_addr <= export_rva < virt_addr + virt_size:
                    file_off = raw_offset + (export_rva - virt_addr)
                    f.seek(file_off + 24)  # NumberOfNames at offset 24
                    num_names = struct.unpack("<I", f.read(4))[0]
                    return num_names
        return -1
    except Exception:
        return -1


def main():
    parser = argparse.ArgumentParser(description="Build gbengine.dll with VC6")
    parser.add_argument("--clean", action="store_true", help="Clean build directory first")
    parser.add_argument("--verify", action="store_true", help="Compare exports after build")
    args = parser.parse_args()

    # Setup build directory
    BUILD_DIR.mkdir(exist_ok=True)
    if args.clean:
        for f in BUILD_DIR.glob("*"):
            if f.is_file():
                f.unlink()
        print("[*] Cleaned build directory")

    # Setup environment
    env = os.environ.copy()
    if is_linux():
        env["WINEDEBUG"] = "-all"
    else:
        env["INCLUDE"] = f"{VC6_INCLUDE};{INCLUDE_DIR}"
        env["LIB"] = str(VC6_LIB)

    # Phase 1: Compile
    print(f"[*] Compiling {len(CPP_SOURCES) + len(C_SOURCES)} source files...")
    obj_files = []
    compiled = 0
    skipped = 0
    failed = 0

    all_sources = [(SRC_DIR / s, s) for s in CPP_SOURCES] + [(SRC_DIR / s, s) for s in C_SOURCES]

    for src_path, src_name in all_sources:
        stem = Path(src_name).stem
        obj_path = BUILD_DIR / f"{stem}.obj"

        # Skip if obj is newer than source
        if obj_path.exists() and obj_path.stat().st_mtime > src_path.stat().st_mtime:
            skipped += 1
            obj_files.append(obj_path)
            continue

        if not compile_file(src_path, obj_path, env):
            failed += 1
            continue

        compiled += 1
        obj_files.append(obj_path)

    print(f"    Compiled: {compiled}, Skipped (up-to-date): {skipped}, Failed: {failed}")

    if failed > 0:
        print(f"[!] {failed} file(s) failed to compile. Aborting link.")
        return 1

    # Phase 2: Link
    print(f"[*] Linking {len(obj_files)} object files...")
    output_dll = BUILD_DIR / "gbengine.dll"

    if not link_dll(obj_files, output_dll, env):
        return 1

    dll_size = output_dll.stat().st_size
    num_exports = count_exports(output_dll)
    print(f"[+] Build successful!")
    print(f"    Output: {output_dll}")
    print(f"    Size: {dll_size:,} bytes")
    print(f"    Exports: {num_exports}")

    if num_exports != 1019:
        print(f"[!] WARNING: Expected 1019 exports, got {num_exports}")

    # Phase 3: Verify (optional)
    if args.verify:
        print(f"\n[*] Verifying exports against original...")
        original_dll = PROJECT_ROOT / "original" / "gbengine.dll"
        if not original_dll.exists():
            print("    original/gbengine.dll not found, skipping verification")
        else:
            orig_exports = count_exports(original_dll)
            print(f"    Original exports: {orig_exports}")
            print(f"    Built exports: {num_exports}")
            if orig_exports == num_exports:
                print("    [OK] Export count matches!")
            else:
                print(f"    [MISMATCH] Export counts differ!")

    return 0


if __name__ == "__main__":
    sys.exit(main())
