#!/bin/bash
# Wine wrapper for VC6 LIB.EXE - used by CMake toolchain on Linux
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
        /[A-Z]*:/*|/[a-z]*:/*)
            prefix="${arg%%:*}:"
            path="${arg#*:}"
            ARGS+=("${prefix}$(convert_path "$path")")
            ;;
        /*)
            if [[ "$arg" == */*/* ]]; then
                ARGS+=("$(convert_path "$arg")")
            else
                ARGS+=("$arg")
            fi
            ;;
        */*.obj|*/*.OBJ|*/*.lib|*/*.LIB)
            if [ -e "$arg" ] || [ -e "$(dirname "$arg")" ]; then
                abs="$(cd "$(dirname "$arg")" && pwd)/$(basename "$arg")"
                ARGS+=("$(convert_path "$abs")")
            else
                ARGS+=("$arg")
            fi
            ;;
        *)
            ARGS+=("$arg")
            ;;
    esac
done

exec wine "$VC6_BIN/LIB.EXE" "${ARGS[@]}"
