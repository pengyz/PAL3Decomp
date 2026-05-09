#!/bin/bash
# Wine wrapper for VC7.1 CL.EXE (VS2003) - used by CMake toolchain on Linux
# Converts Unix paths in arguments to Wine Z: drive format.
#
# Based on wine_cl.sh (VC6 version), adapted for VC7.1 paths.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VC71_BIN="$SCRIPT_DIR/vc71/Bin"
export WINEDEBUG=-all

convert_path() {
    # Convert a Unix absolute path to Wine Z: format
    echo "Z:${1//\//\\}"
}

# Convert arguments
ARGS=()
for arg in "$@"; do
    case "$arg" in
        # --- MSVC flags with embedded paths ---
        # /Fo<path>, /Fe<path>, /Fd<path>, /Fa<path>, /Fp<path>, /FR<path>, /Fi<path>
        /[Ff][oOeEdDaApPrRiI]*)
            prefix="${arg:0:3}"
            rest="${arg:3}"
            if [ -z "$rest" ]; then
                ARGS+=("$arg")
            elif [[ "$rest" == /* ]]; then
                ARGS+=("${arg:0:3}$(convert_path "$rest")")
            elif [[ "$rest" == */* ]]; then
                if [ -e "$(dirname "$rest")" ]; then
                    abs="$(cd "$(dirname "$rest")" && pwd)/$(basename "$rest")"
                    ARGS+=("${arg:0:3}$(convert_path "$abs")")
                else
                    ARGS+=("$arg")
                fi
            else
                ARGS+=("$arg")
            fi
            ;;

        # /I<path> (include directory)
        /I/*)
            path="${arg:2}"
            ARGS+=("/I$(convert_path "$path")")
            ;;
        /I*)
            rest="${arg:2}"
            if [[ "$rest" == */* ]] && [ -d "$rest" ]; then
                abs="$(cd "$rest" && pwd)"
                ARGS+=("/I$(convert_path "$abs")")
            else
                ARGS+=("$arg")
            fi
            ;;

        # /DEF:, /OUT:, /LIBPATH:, /MAP:, /PDB:, /IMPLIB: with path
        /[A-Z]*:/*|/[a-z]*:/*)
            prefix="${arg%%:*}:"
            path="${arg#*:}"
            if [[ "$path" == /* ]]; then
                ARGS+=("${prefix}$(convert_path "$path")")
            else
                ARGS+=("$arg")
            fi
            ;;

        # -I<path> (GCC-style include, CMake sometimes passes this)
        -I/*)
            path="${arg:2}"
            ARGS+=("/I$(convert_path "$path")")
            ;;
        -I*)
            rest="${arg:2}"
            if [ -d "$rest" ]; then
                abs="$(cd "$rest" && pwd)"
                ARGS+=("/I$(convert_path "$abs")")
            else
                ARGS+=("$arg")
            fi
            ;;

        # -D defines -> convert to /D
        -D*)
            ARGS+=("/D${arg:2}")
            ;;

        # -c flag -> /c
        -c)
            ARGS+=("/c")
            ;;

        # -o <file> (shouldn't happen with MSVC but just in case)
        -o)
            ARGS+=("/Fo")
            ;;

        # Any other flag starting with / that is NOT a real file path
        /*)
            if [[ "$arg" == */*/* ]]; then
                # Contains multiple slashes -> definitely a path
                ARGS+=("$(convert_path "$arg")")
            else
                # Single slash at start, no deeper path -> it's a flag
                ARGS+=("$arg")
            fi
            ;;

        # Source/obj files with path separators (relative)
        */*.cpp|*/*.c|*/*.obj|*/*.CPP|*/*.C|*/*.OBJ|*/*.lib|*/*.LIB|*/*.def|*/*.DEF|*/*.res|*/*.RES)
            if [ -e "$arg" ] || [ -e "$(dirname "$arg")" ]; then
                abs="$(cd "$(dirname "$arg")" && pwd)/$(basename "$arg")"
                ARGS+=("$(convert_path "$abs")")
            else
                ARGS+=("$arg")
            fi
            ;;

        # Everything else (flags, defines, plain filenames)
        *)
            ARGS+=("$arg")
            ;;
    esac
done

exec wine "$VC71_BIN/cl.exe" "${ARGS[@]}"
