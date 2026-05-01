"""Generate import libraries (.lib) from DLLs using dumpbin + lib tools.

Usage:
    python tools/gen_import_lib.py original/topo.dll lib/topo.lib
    python tools/gen_import_lib.py original/gbengine.dll lib/gbengine.lib
"""

import subprocess
import sys
import os
import tempfile
import re

DUMPBIN = r"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\bin\Hostx86\x86\dumpbin.exe"
LIB_TOOL = r"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\bin\Hostx86\x86\lib.exe"


def get_exports(dll_path):
    """Extract export names from a DLL using dumpbin."""
    result = subprocess.run(
        [DUMPBIN, "/EXPORTS", dll_path],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    content = result.stdout.decode('latin-1')

    exports = []
    in_exports = False
    empty_count = 0
    for line in content.splitlines():
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
    return exports


def generate_def(dll_name, exports, def_path):
    """Generate a .def file from exports list."""
    with open(def_path, 'w') as f:
        f.write(f"LIBRARY {dll_name}\n")
        f.write("EXPORTS\n")
        for ordinal, name in exports:
            f.write(f"    {name} @{ordinal}\n")
    return def_path


def generate_lib(def_path, lib_path):
    """Generate .lib from .def file using lib.exe."""
    result = subprocess.run(
        [LIB_TOOL, f"/DEF:{def_path}", f"/OUT:{lib_path}", "/MACHINE:X86"],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    if result.returncode != 0:
        print(f"  Warning: lib.exe returned {result.returncode}")
        print(f"  {result.stderr.decode('latin-1')}")
    return lib_path


def main():
    if len(sys.argv) < 3:
        print("Usage: python gen_import_lib.py <input.dll> <output.lib>")
        sys.exit(1)

    dll_path = os.path.abspath(sys.argv[1])
    lib_path = os.path.abspath(sys.argv[2])

    if not os.path.exists(dll_path):
        print(f"Error: DLL not found: {dll_path}")
        sys.exit(1)

    os.makedirs(os.path.dirname(lib_path), exist_ok=True)

    dll_name = os.path.basename(dll_path)
    print(f"Processing: {dll_name}")

    exports = get_exports(dll_path)
    print(f"  Found {len(exports)} exports")

    if not exports:
        print("  ERROR: No exports found!")
        sys.exit(1)

    def_path = lib_path.replace('.lib', '.def')
    generate_def(dll_name, exports, def_path)
    print(f"  Generated: {def_path}")

    generate_lib(def_path, lib_path)

    if os.path.exists(lib_path):
        size = os.path.getsize(lib_path)
        print(f"  Generated: {lib_path} ({size} bytes)")
        print(f"  SUCCESS")
    else:
        print(f"  FAILED: {lib_path} not created")
        sys.exit(1)


if __name__ == "__main__":
    main()
