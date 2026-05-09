#!/bin/bash
# wine_vc6.sh - Wine wrapper for VC6 compiler toolchain on Linux
#
# Provides cl/link/lib/nmake commands that transparently call VC6 tools via Wine.
# Usage:
#   source tools/wine_vc6.sh       # set up environment
#   vc6_cl /c /O2 file.cpp         # compile
#   vc6_link /DLL /OUT:out.dll ... # link
#   vc6_compile file.cpp file.obj  # shorthand: compile single file to .obj
#
# Requirements: wine (apt install wine)

# Resolve paths (compatible with both bash and zsh)
if [ -n "${BASH_SOURCE+x}" ]; then
    _WINE_VC6_SCRIPT="${BASH_SOURCE[0]}"
else
    _WINE_VC6_SCRIPT="${0}"
fi
SCRIPT_DIR="$(cd "$(dirname "$_WINE_VC6_SCRIPT")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
VC6_ROOT="$PROJECT_ROOT/tools/compilers/msvc6.0"
VC6_BIN="$VC6_ROOT/Bin"
VC6_INCLUDE="$VC6_ROOT/Include"
VC6_LIB="$PROJECT_ROOT/tools/vc6/Lib"

# Convert Unix path to Wine Z: drive path
to_winpath() {
    echo "Z:$(realpath "$1")" | sed 's|/|\\|g'
}

# Suppress Wine debug noise
export WINEDEBUG=-all

# Windows-style paths for VC6
WIN_VC6_INCLUDE="$(to_winpath "$VC6_INCLUDE")"
WIN_VC6_LIB="$(to_winpath "$VC6_LIB")"
WIN_PROJECT_INCLUDE="$(to_winpath "$PROJECT_ROOT/include")"

# VC6 cl.exe wrapper
vc6_cl() {
    wine "$VC6_BIN/CL.EXE" /nologo "$@"
}

# VC6 link.exe wrapper
vc6_link() {
    wine "$VC6_BIN/LINK.EXE" /nologo "$@"
}

# VC6 lib.exe wrapper
vc6_lib() {
    wine "$VC6_BIN/LIB.EXE" /nologo "$@"
}

# VC6 nmake.exe wrapper
vc6_nmake() {
    wine "$VC6_BIN/NMAKE.EXE" /nologo "$@"
}

# Compile a single .cpp/.c to .obj with standard gbengine flags
# Usage: vc6_compile <source.cpp> [output.obj]
vc6_compile() {
    local src="$1"
    local obj="${2:-${src%.*}.obj}"
    local win_src win_obj

    win_src="$(to_winpath "$src")"
    win_obj="$(to_winpath "$obj")"

    wine "$VC6_BIN/CL.EXE" /nologo /c \
        /O2 /Ob2 /GF /Gy /Zp4 /GX /MD \
        /I"$WIN_VC6_INCLUDE" \
        /I"$WIN_PROJECT_INCLUDE" \
        /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS \
        /Fo"$win_obj" \
        "$win_src"
}

# Compile and produce .obj, return 0 on success
# Usage: vc6_compile_gbengine <source.cpp> [output.obj]
vc6_compile_gbengine() {
    local src="$1"
    local obj="${2:-${src%.*}.obj}"
    local win_src win_obj

    win_src="$(to_winpath "$src")"
    win_obj="$(to_winpath "$obj")"

    wine "$VC6_BIN/CL.EXE" /nologo /c \
        /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /Zp4 /GX /MD \
        /I"$WIN_VC6_INCLUDE" \
        /I"$WIN_PROJECT_INCLUDE" \
        /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS \
        /Fo"$win_obj" \
        "$win_src"
}

# Print environment info
vc6_info() {
    echo "=== VC6 Wine Environment ==="
    echo "PROJECT_ROOT: $PROJECT_ROOT"
    echo "VC6_ROOT:     $VC6_ROOT"
    echo "VC6 Version:  $(wine "$VC6_BIN/CL.EXE" 2>&1 | head -1)"
    echo "Wine Version: $(wine --version)"
    echo "============================="
}

# If script is executed (not sourced), run the command
if [[ "${_WINE_VC6_SCRIPT}" == "${0}" ]]; then
    case "${1:-info}" in
        cl)      shift; vc6_cl "$@" ;;
        link)    shift; vc6_link "$@" ;;
        lib)     shift; vc6_lib "$@" ;;
        nmake)   shift; vc6_nmake "$@" ;;
        compile) shift; vc6_compile "$@" ;;
        info)    vc6_info ;;
        *)
            echo "Usage: $0 {cl|link|lib|nmake|compile|info} [args...]"
            exit 1
            ;;
    esac
fi
