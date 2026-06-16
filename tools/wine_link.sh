#!/bin/bash
# Wine wrapper for VC6 LINK.EXE - used by CMake toolchain on Linux
# Converts Unix paths in arguments to Wine Z: drive format.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VC6_BIN="$SCRIPT_DIR/compilers/msvc6.0/Bin"
export WINEDEBUG=-all

convert_path() {
    echo "Z:${1//\//\\}"
}

ARGS=()
for arg in "$@"; do
    case "$arg" in
        # /OUT:/path, /DEF:/path, /LIBPATH:/path, /MAP:/path, /PDB:/path, /IMPLIB:/path
        /[A-Za-z][A-Za-z]*:*/*)
            prefix="${arg%%:*}:"
            path="${arg#*:}"
            ARGS+=("${prefix}$(convert_path "$path")")
            ;;
        # -LIBPATH:/path (CMake passes link_directories with dash prefix)
        -[A-Z]*:/*|-[a-z]*:/*)
            prefix="/${arg#-}"
            prefix="${prefix%%:*}:"
            path="${arg#*:}"
            ARGS+=("${prefix}$(convert_path "$path")")
            ;;
        # Absolute paths (contain multiple /)
        /*)
            if [[ "$arg" == */*/* ]]; then
                ARGS+=("$(convert_path "$arg")")
            else
                ARGS+=("$arg")
            fi
            ;;
        # Relative paths to obj/lib/dll/def/exe files
        */*.obj|*/*.OBJ|*/*.lib|*/*.LIB|*/*.dll|*/*.DLL|*/*.def|*/*.DEF|*/*.exe|*/*.EXE|*/*.exp|*/*.res)
            if [ -e "$arg" ] || [ -e "$(dirname "$arg")" ]; then
                abs="$(cd "$(dirname "$arg")" && pwd)/$(basename "$arg")"
                ARGS+=("$(convert_path "$abs")")
            else
                ARGS+=("$arg")
            fi
            ;;
        # -D, -l etc (GCC-style, shouldn't appear but handle gracefully)
        -*)
            ARGS+=("$arg")
            ;;
        *)
            ARGS+=("$arg")
            ;;
    esac
done

exec wine "$VC6_BIN/LINK.EXE" "${ARGS[@]}"
