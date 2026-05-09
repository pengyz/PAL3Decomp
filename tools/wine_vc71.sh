#!/bin/bash
# wine_vc71.sh - Helper functions for VC7.1 (VS2003) under Wine
#
# Source this file to get convenience functions:
#   source tools/wine_vc71.sh
#
# Available functions:
#   vc71_cl       - Direct CL.EXE wrapper (pass any CL flags)
#   vc71_compile  - Single file to .obj (with PAL3 flags)
#   vc71_link     - LINK.EXE wrapper
#   vc71_lib      - LIB.EXE wrapper
#   vc71_info     - Show VC7.1/Wine environment info

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
VC71_ROOT="$PROJECT_ROOT/tools/vc71"
export WINEDEBUG=-all

_vc71_convert_path() {
    echo "Z:${1//\//\\}"
}

vc71_cl() {
    wine "$VC71_ROOT/Bin/cl.exe" "$@"
}

vc71_link() {
    wine "$VC71_ROOT/Bin/link.exe" "$@"
}

vc71_lib() {
    wine "$VC71_ROOT/Bin/lib.exe" "$@"
}

vc71_compile() {
    # Usage: vc71_compile <source.cpp> <output.obj>
    # Compiles with PAL3 flags (matching original binary)
    local src="$1"
    local obj="${2:-${src%.cpp}.obj}"

    if [ ! -f "$src" ]; then
        echo "Error: Source file not found: $src"
        return 1
    fi

    local abs_src="$(cd "$(dirname "$src")" && pwd)/$(basename "$src")"
    local abs_obj
    if [[ "$obj" == /* ]]; then
        abs_obj="$obj"
    else
        abs_obj="$(pwd)/$obj"
    fi

    local win_src="$(_vc71_convert_path "$abs_src")"
    local win_obj="$(_vc71_convert_path "$abs_obj")"
    local win_inc="$(_vc71_convert_path "$VC71_ROOT/Include")"
    local win_sdk_inc="$(_vc71_convert_path "$VC71_ROOT/PlatformSDK/Include")"
    local win_proj_inc="$(_vc71_convert_path "$PROJECT_ROOT/include")"

    wine "$VC71_ROOT/Bin/cl.exe" /nologo /c \
        /EHsc /GR /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /MD \
        /W3 /GS- /Gd /Zc:wchar_t \
        /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS \
        /I"$win_inc" /I"$win_sdk_inc" /I"$win_proj_inc" \
        /Fo"$win_obj" "$win_src"
}

vc71_info() {
    echo "=== VC7.1 (VS2003) Environment ==="
    echo "  Root:     $VC71_ROOT"
    echo "  Bin:      $VC71_ROOT/Bin/"
    echo "  Include:  $VC71_ROOT/Include/"
    echo "  Lib:      $VC71_ROOT/Lib/"
    echo "  SDK Inc:  $VC71_ROOT/PlatformSDK/Include/"
    echo "  SDK Lib:  $VC71_ROOT/PlatformSDK/Lib/"
    echo "  Wine:     $(wine --version 2>/dev/null)"
    echo ""
    if [ -f "$VC71_ROOT/Bin/cl.exe" ]; then
        echo "  CL.EXE:   $(wine "$VC71_ROOT/Bin/cl.exe" 2>&1 | head -1)"
    else
        echo "  CL.EXE:   NOT FOUND"
    fi
}

echo "[vc71] VC7.1 helper functions loaded. Type 'vc71_info' for details."
