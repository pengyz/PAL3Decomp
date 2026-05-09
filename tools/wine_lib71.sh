#!/bin/bash
# Wine wrapper for VC7.1 LIB.EXE (VS2003) - used by CMake toolchain on Linux
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VC71_BIN="$SCRIPT_DIR/vc71/Bin"
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
            if [[ "$path" == /* ]]; then
                ARGS+=("${prefix}$(convert_path "$path")")
            else
                ARGS+=("$arg")
            fi
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

exec wine "$VC71_BIN/lib.exe" "${ARGS[@]}"
