#!/bin/bash
# setup_wine_vc71.sh - Setup VC7.1 (VS2003) under Wine on Linux
#
# This script can work in two modes:
#
# Mode 1: Extract from VS2003 ISO (recommended)
#   bash tools/setup_wine_vc71.sh /path/to/en_vs.net_2003_pro_cd1.iso
#
# Mode 2: Verify an already-populated tools/vc71/ directory
#   bash tools/setup_wine_vc71.sh
#
# After running this script, the VC7.1 compiler should be usable via:
#   cmake -B build/pal3a -G "Unix Makefiles" \
#     -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc71.cmake \
#     -DBUILD_TARGET=pal3a
#
# Required ISO: en_vs.net_2003_pro_cd1.iso (649 MB)
#   SHA-1: adb19368ee9f5bd7e31a5699061c44b1db41c68b
# Or Chinese: sc_vs.net_2003_pro_cd1.iso (608 MB)
#   SHA-1: ee02963a818072d92eb732d38cc8c566ad7faaf7

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
VC71_ROOT="$PROJECT_ROOT/tools/vc71"

echo "=== PAL3Decomp: VC7.1 (VS2003) Wine Setup ==="
echo ""

# 1. Check Wine
if ! command -v wine &>/dev/null; then
    echo "[ERROR] Wine is not installed."
    echo "  Install with: sudo apt install wine"
    exit 1
fi
echo "[OK] Wine: $(wine --version 2>/dev/null)"

# 2. Check cabextract (needed for ISO extraction)
if ! command -v cabextract &>/dev/null; then
    echo "[WARN] cabextract not found. Needed for ISO extraction."
    echo "  Install with: sudo apt install cabextract"
fi

# --------------------------------------------------------------------------
# Mode 1: Extract from ISO
# --------------------------------------------------------------------------
if [ "${1:-}" != "" ] && [ -f "${1:-}" ]; then
    ISO_PATH="$1"
    echo ""
    echo "[*] Extracting VC7.1 tools from ISO: $ISO_PATH"

    # Mount ISO
    MOUNT_DIR=$(mktemp -d /tmp/vs2003_mount_XXXXXX)
    echo "[*] Mounting ISO to $MOUNT_DIR ..."
    sudo mount -o loop,ro "$ISO_PATH" "$MOUNT_DIR" 2>/dev/null || {
        echo "[ERROR] Failed to mount ISO. Try: sudo apt install fuseiso"
        rmdir "$MOUNT_DIR"
        exit 1
    }

    # VS2003 ISO structure: files are in MSI/CAB archives
    # The compiler tools are typically in:
    #   - VC_RTL/ or Program Files/Microsoft Visual Studio .NET 2003/Vc7/
    #   - Various .cab files that need extraction
    echo ""
    echo "[*] Looking for VC7 compiler files..."

    # Strategy: Look for the VS setup directory structure
    # VS2003 ISOs typically have a WCU/ and VS/ directory with .msi and .cab files
    # The VC7.1 compiler is in vs_setup.msi or vcXXX.cab files

    FOUND_SETUP=""
    for d in "$MOUNT_DIR" "$MOUNT_DIR/VS" "$MOUNT_DIR/vs" "$MOUNT_DIR/Setup"; do
        if [ -d "$d" ]; then
            echo "  Found directory: $d"
            # List .cab and .msi files
            find "$d" -maxdepth 2 \( -name "*.cab" -o -name "*.msi" -o -name "*.CAB" -o -name "*.MSI" \) 2>/dev/null | head -20
            FOUND_SETUP="$d"
        fi
    done

    if [ -z "$FOUND_SETUP" ]; then
        echo ""
        echo "[*] ISO directory listing:"
        ls -la "$MOUNT_DIR/" | head -30
        echo ""
        echo "[INFO] Could not auto-detect setup structure."
        echo "       You may need to manually extract the compiler files."
        echo "       See instructions below."
    else
        echo ""
        echo "[*] Attempting CAB extraction..."

        # Create temporary extraction directory
        EXTRACT_DIR=$(mktemp -d /tmp/vs2003_extract_XXXXXX)

        # Try to find and extract VC compiler cabs
        # Common VS2003 cab names: vc1.cab, vc2.cab, ... or VCCore.cab
        find "$FOUND_SETUP" -iname "vc*.cab" 2>/dev/null | while read cabfile; do
            echo "  Extracting: $cabfile"
            cabextract -q -d "$EXTRACT_DIR" "$cabfile" 2>/dev/null || true
        done

        # Look for compiler binaries in extracted content
        CL_EXE=$(find "$EXTRACT_DIR" -iname "cl.exe" 2>/dev/null | head -1)
        if [ -n "$CL_EXE" ]; then
            echo "[OK] Found cl.exe at: $CL_EXE"
            echo "[*] Copying compiler tools to $VC71_ROOT/Bin/ ..."

            BIN_DIR=$(dirname "$CL_EXE")
            cp -v "$BIN_DIR"/cl.exe "$VC71_ROOT/Bin/" 2>/dev/null || true
            cp -v "$BIN_DIR"/c1.dll "$VC71_ROOT/Bin/" 2>/dev/null || true
            cp -v "$BIN_DIR"/c1xx.dll "$VC71_ROOT/Bin/" 2>/dev/null || true
            cp -v "$BIN_DIR"/c2.dll "$VC71_ROOT/Bin/" 2>/dev/null || true
            cp -v "$BIN_DIR"/link.exe "$VC71_ROOT/Bin/" 2>/dev/null || true
            cp -v "$BIN_DIR"/lib.exe "$VC71_ROOT/Bin/" 2>/dev/null || true
            cp -v "$BIN_DIR"/mspdb71.dll "$VC71_ROOT/Bin/" 2>/dev/null || true
            cp -v "$BIN_DIR"/msvcr71.dll "$VC71_ROOT/Bin/" 2>/dev/null || true
            cp -v "$BIN_DIR"/mspdbcore.dll "$VC71_ROOT/Bin/" 2>/dev/null || true
            cp -v "$BIN_DIR"/mspdbsrv.exe "$VC71_ROOT/Bin/" 2>/dev/null || true
        else
            echo "[WARN] cl.exe not found in extracted cabs."
            echo "       The VS2003 ISO may use a different packaging structure."
            echo "       Listing extracted files:"
            find "$EXTRACT_DIR" -type f | head -30
        fi

        # Look for include/lib files
        INCLUDE_DIR=$(find "$EXTRACT_DIR" -type d -iname "include" | head -1)
        if [ -n "$INCLUDE_DIR" ]; then
            echo "[*] Copying Include files..."
            cp -r "$INCLUDE_DIR"/* "$VC71_ROOT/Include/" 2>/dev/null || true
        fi

        LIB_DIR=$(find "$EXTRACT_DIR" -type d -iname "lib" | head -1)
        if [ -n "$LIB_DIR" ]; then
            echo "[*] Copying Lib files..."
            cp -r "$LIB_DIR"/* "$VC71_ROOT/Lib/" 2>/dev/null || true
        fi

        rm -rf "$EXTRACT_DIR"
    fi

    # Unmount
    sudo umount "$MOUNT_DIR" 2>/dev/null || true
    rmdir "$MOUNT_DIR" 2>/dev/null || true
fi

# --------------------------------------------------------------------------
# Verification (both modes)
# --------------------------------------------------------------------------
echo ""
echo "=== Verifying VC7.1 installation ==="
echo ""

# Check required files
MISSING=0
check_file() {
    if [ -f "$1" ]; then
        echo "[OK] $2"
    else
        # Try case-insensitive match (Linux case sensitivity)
        # Follow symlinks with -L
        local dir=$(dirname "$1")
        local base=$(basename "$1")
        local found=$(find -L "$dir" -maxdepth 1 -iname "$base" 2>/dev/null | head -1)
        if [ -n "$found" ]; then
            echo "[OK] $2 (as $(basename "$found"))"
        else
            echo "[MISSING] $2 ($1)"
            MISSING=$((MISSING+1))
        fi
    fi
}

echo "--- Compiler Binaries ---"
check_file "$VC71_ROOT/Bin/cl.exe" "cl.exe (C/C++ compiler)"
check_file "$VC71_ROOT/Bin/c1.dll" "c1.dll (C frontend)"
check_file "$VC71_ROOT/Bin/c1xx.dll" "c1xx.dll (C++ frontend)"
check_file "$VC71_ROOT/Bin/c2.dll" "c2.dll (backend/optimizer)"
check_file "$VC71_ROOT/Bin/link.exe" "link.exe (linker)"
check_file "$VC71_ROOT/Bin/lib.exe" "lib.exe (librarian)"
check_file "$VC71_ROOT/Bin/mspdb71.dll" "mspdb71.dll (PDB support)"

echo ""
echo "--- CRT Headers ---"
check_file "$VC71_ROOT/Include/stdio.h" "stdio.h"
check_file "$VC71_ROOT/Include/stdlib.h" "stdlib.h"
check_file "$VC71_ROOT/Include/string.h" "string.h"
check_file "$VC71_ROOT/Include/new" "new (C++ allocator)"

echo ""
echo "--- CRT Libraries ---"
check_file "$VC71_ROOT/Lib/libcmt.lib" "libcmt.lib (static CRT)"
check_file "$VC71_ROOT/Lib/msvcrt.lib" "msvcrt.lib (DLL CRT import)"
check_file "$VC71_ROOT/Lib/oldnames.lib" "oldnames.lib"

echo ""
echo "--- Platform SDK Headers ---"
check_file "$VC71_ROOT/PlatformSDK/Include/windows.h" "windows.h"
check_file "$VC71_ROOT/PlatformSDK/Include/d3d9.h" "d3d9.h"
check_file "$VC71_ROOT/PlatformSDK/Include/dinput.h" "dinput.h"

echo ""
echo "--- Platform SDK Libraries ---"
check_file "$VC71_ROOT/PlatformSDK/Lib/kernel32.lib" "kernel32.lib"
check_file "$VC71_ROOT/PlatformSDK/Lib/user32.lib" "user32.lib"
check_file "$VC71_ROOT/PlatformSDK/Lib/d3d9.lib" "d3d9.lib"

echo ""
if [ $MISSING -gt 0 ]; then
    echo "=== $MISSING files missing ==="
    echo ""
    echo "To complete setup, you need to populate tools/vc71/ with files from VS2003."
    echo ""
    echo "Option A: Extract from ISO"
    echo "  1. Download: en_vs.net_2003_pro_cd1.iso"
    echo "     SHA-1: adb19368ee9f5bd7e31a5699061c44b1db41c68b"
    echo "  2. Run: bash tools/setup_wine_vc71.sh /path/to/iso"
    echo ""
    echo "Option B: Copy from a Windows installation"
    echo "  From a machine with VS2003 installed, copy:"
    echo "    C:\\Program Files\\Microsoft Visual Studio .NET 2003\\Vc7\\bin\\  → tools/vc71/Bin/"
    echo "    C:\\Program Files\\Microsoft Visual Studio .NET 2003\\Vc7\\include\\  → tools/vc71/Include/"
    echo "    C:\\Program Files\\Microsoft Visual Studio .NET 2003\\Vc7\\lib\\  → tools/vc71/Lib/"
    echo "    C:\\Program Files\\Microsoft Visual Studio .NET 2003\\Vc7\\PlatformSDK\\Include\\  → tools/vc71/PlatformSDK/Include/"
    echo "    C:\\Program Files\\Microsoft Visual Studio .NET 2003\\Vc7\\PlatformSDK\\Lib\\  → tools/vc71/PlatformSDK/Lib/"
    echo ""
    echo "Option C: Minimal extraction (compiler-only)"
    echo "  If you just need to compile .cpp → .obj (no linking):"
    echo "  Copy only: cl.exe, c1.dll, c1xx.dll, c2.dll, mspdb71.dll, msvcr71.dll"
    echo "  Plus headers from Include/ and PlatformSDK/Include/"
    exit 1
fi

# --------------------------------------------------------------------------
# Create lowercase symlinks (Linux case-sensitivity fix)
# --------------------------------------------------------------------------
echo ""
echo "[*] Creating lowercase symlinks..."

for dir in "$VC71_ROOT/Lib" "$VC71_ROOT/Include" "$VC71_ROOT/PlatformSDK/Lib" "$VC71_ROOT/PlatformSDK/Include"; do
    if [ -d "$dir" ]; then
        cd "$dir"
        count=0
        for f in *; do
            [ -e "$f" ] || continue
            lower=$(echo "$f" | tr '[:upper:]' '[:lower:]')
            if [ "$f" != "$lower" ] && [ ! -e "$lower" ]; then
                ln -sf "$f" "$lower"
                count=$((count+1))
            fi
        done
        echo "    $dir: $count symlinks"
    fi
done

# --------------------------------------------------------------------------
# Test compiler
# --------------------------------------------------------------------------
echo ""
echo "[*] Testing cl.exe ..."
export WINEDEBUG=-all
CL_OUTPUT=$(wine "$VC71_ROOT/Bin/cl.exe" 2>&1 | head -1)
if echo "$CL_OUTPUT" | grep -q "Version 13.10"; then
    echo "[OK] $CL_OUTPUT"
else
    echo "[ERROR] cl.exe did not produce expected output:"
    echo "  $CL_OUTPUT"
    echo ""
    echo "  Expected: Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.10.XXXX"
    echo "  This could indicate:"
    echo "    - Wrong cl.exe version (not VS2003)"
    echo "    - Missing DLL dependencies (mspdb71.dll, msvcr71.dll)"
    echo "    - Wine compatibility issue"
    exit 1
fi

# Quick compile test
echo ""
echo "[*] Quick compile test ..."
TEST_C=$(mktemp /tmp/vc71_test_XXXXXX.cpp)
cat > "$TEST_C" << 'TESTCODE'
#include <stdio.h>
int __cdecl test_func(int x) { return x * 2; }
TESTCODE
TEST_OBJ="${TEST_C%.cpp}.obj"
WIN_SRC="Z:${TEST_C//\//\\}"
WIN_OBJ="Z:${TEST_OBJ//\//\\}"
WIN_INC="Z:${VC71_ROOT//\//\\}\\Include"

if wine "$VC71_ROOT/Bin/cl.exe" /nologo /c /O2 /I"$WIN_INC" /Fo"$WIN_OBJ" "$WIN_SRC" >/dev/null 2>&1; then
    echo "[OK] Compile test passed"
    rm -f "$TEST_C" "$TEST_OBJ"
else
    echo "[WARN] Compile test failed (may need include paths adjusted)"
    rm -f "$TEST_C"
fi

echo ""
echo "=== VC7.1 Setup Complete! ==="
echo ""
echo "Usage:"
echo "  # CMake build (PAL3A.exe):"
echo "  cmake -B build/pal3a -G 'Unix Makefiles' \\"
echo "    -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc71.cmake \\"
echo "    -DBUILD_TARGET=pal3a"
echo "  cmake --build build/pal3a"
echo ""
echo "  # Single file compile test:"
echo "  source tools/wine_vc71.sh"
echo "  vc71_compile src/pal3a/SomeFile.cpp /tmp/SomeFile.obj"
