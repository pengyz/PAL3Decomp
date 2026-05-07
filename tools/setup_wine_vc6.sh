#!/bin/bash
# setup_wine_vc6.sh - One-time setup for VC6 under Wine on Linux
#
# This script:
# 1. Checks that Wine is installed
# 2. Creates lowercase symlinks in vc6/Lib/ and vc6/Include/ (Linux case-sensitivity fix)
# 3. Verifies CL.EXE works
#
# Run once after cloning the repo on Linux:
#   bash tools/setup_wine_vc6.sh

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
VC6_ROOT="$PROJECT_ROOT/tools/vc6"

echo "=== PAL3Decomp: VC6 Wine Setup ==="
echo ""

# 1. Check Wine
if ! command -v wine &>/dev/null; then
    echo "[ERROR] Wine is not installed."
    echo "  Install with: sudo apt install wine"
    exit 1
fi
echo "[OK] Wine: $(wine --version 2>/dev/null)"

# 2. Create lowercase symlinks for Lib/
echo ""
echo "[*] Creating lowercase symlinks in vc6/Lib/ ..."
cd "$VC6_ROOT/Lib"
count=0
for f in *.LIB *.OBJ *.PDB; do
    [ -e "$f" ] || continue
    lower=$(echo "$f" | tr '[:upper:]' '[:lower:]')
    if [ "$f" != "$lower" ] && [ ! -e "$lower" ]; then
        ln -sf "$f" "$lower"
        count=$((count+1))
    fi
done
echo "    Created $count symlinks in Lib/"

# 3. Create lowercase symlinks for Include/
echo "[*] Creating lowercase symlinks in vc6/Include/ ..."
cd "$VC6_ROOT/Include"
count=0
for f in *; do
    [ -e "$f" ] || continue
    lower=$(echo "$f" | tr '[:upper:]' '[:lower:]')
    if [ "$f" != "$lower" ] && [ ! -e "$lower" ]; then
        ln -sf "$f" "$lower"
        count=$((count+1))
    fi
done
echo "    Created $count symlinks in Include/"

# 4. Verify CL.EXE
echo ""
echo "[*] Testing CL.EXE ..."
export WINEDEBUG=-all
CL_OUTPUT=$(wine "$VC6_ROOT/Bin/CL.EXE" 2>&1 | head -1)
if echo "$CL_OUTPUT" | grep -q "Version 12.00"; then
    echo "[OK] $CL_OUTPUT"
else
    echo "[ERROR] CL.EXE did not produce expected output:"
    echo "  $CL_OUTPUT"
    exit 1
fi

# 5. Quick compile test
echo ""
echo "[*] Quick compile test ..."
TEST_C=$(mktemp /tmp/vc6_test_XXXXXX.c)
echo "int __cdecl test_func(int x) { return x * 2; }" > "$TEST_C"
TEST_OBJ="${TEST_C%.c}.obj"
WIN_SRC="Z:${TEST_C//\//\\\\}"
WIN_OBJ="Z:${TEST_OBJ//\//\\\\}"

if wine "$VC6_ROOT/Bin/CL.EXE" /nologo /c /O2 /Fo"$WIN_OBJ" "$WIN_SRC" >/dev/null 2>&1; then
    echo "[OK] Compile test passed"
    rm -f "$TEST_C" "$TEST_OBJ"
else
    echo "[ERROR] Compile test failed"
    rm -f "$TEST_C"
    exit 1
fi

echo ""
echo "=== Setup complete! ==="
echo ""
echo "Usage:"
echo "  # Interactive (source the helper):"
echo "  source tools/wine_vc6.sh"
echo "  vc6_compile src/gbengine/BEZIER.cpp /tmp/BEZIER.obj"
echo ""
echo "  # Binary comparison:"
echo "  python tools/gbengine_compare.py --compile src/gbengine/BEZIER.cpp --all"
echo ""
echo "  # CMake build (full gbengine.dll):"
echo "  cmake -B build/gbengine -G 'Unix Makefiles' \\"
echo "    -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake \\"
echo "    -DBUILD_TARGET=gbengine"
echo "  cmake --build build/gbengine"
