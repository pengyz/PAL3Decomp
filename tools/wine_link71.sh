#!/bin/bash
# Wine wrapper for VC7.1 LINK.EXE (VS2003) - used by CMake toolchain on Linux
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VC71_BIN="$SCRIPT_DIR/vc71/Bin"
export WINEDEBUG=-all

convert_path() {
    echo "Z:${1//\//\\}"
}

ARGS=()
for arg in "$@"; do
    case "$arg" in
        # Linker flags with embedded paths: /OUT:, /DEF:, /LIBPATH:, /MAP:, /PDB:, /IMPLIB:
        /[A-Z]*:/*|/[a-z]*:/*)
            prefix="${arg%%:*}:"
            path="${arg#*:}"
            if [[ "$path" == /* ]]; then
                ARGS+=("${prefix}$(convert_path "$path")")
            else
                ARGS+=("$arg")
            fi
            ;;

        # Absolute paths (files: .obj, .lib, .res, .exp, .dll, .exe)
        /*)
            if [[ "$arg" == */*/* ]]; then
                ARGS+=("$(convert_path "$arg")")
            else
                ARGS+=("$arg")
            fi
            ;;

        # Relative paths with path separators
        */*.obj|*/*.OBJ|*/*.lib|*/*.LIB|*/*.res|*/*.RES|*/*.exp|*/*.EXP|*/*.def|*/*.DEF)
            if [ -e "$arg" ] || [ -e "$(dirname "$arg")" ]; then
                abs="$(cd "$(dirname "$arg")" && pwd)/$(basename "$arg")"
                ARGS+=("$(convert_path "$abs")")
            else
                ARGS+=("$arg")
            fi
            ;;

        # Response file (@file)
        @/*)
            path="${arg:1}"
            ARGS+=("@$(convert_path "$path")")
            ;;
        @*)
            rest="${arg:1}"
            if [ -e "$rest" ]; then
                abs="$(cd "$(dirname "$rest")" && pwd)/$(basename "$rest")"
                ARGS+=("@$(convert_path "$abs")")
            else
                ARGS+=("$arg")
            fi
            ;;

        *)
            ARGS+=("$arg")
            ;;
    esac
done

exec wine "$VC71_BIN/link.exe" "${ARGS[@]}"
