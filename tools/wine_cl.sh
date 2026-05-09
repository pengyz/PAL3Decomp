#!/bin/bash
# Wine wrapper for VC6 CL.EXE - used by CMake toolchain on Linux
# Converts Unix paths in arguments to Wine Z: drive format.
#
# Strategy: MSVC flags always start with / followed by a letter then more
# letters/digits/punctuation. Real Unix paths contain multiple / separators
# or reference files that exist on disk. We only convert things that are
# clearly file paths.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VC6_BIN="$SCRIPT_DIR/compilers/msvc6.0/Bin"
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
            # If prefix is /Fd with no path value, keep as-is
            if [ -z "$rest" ]; then
                ARGS+=("$arg")
            elif [[ "$rest" == /* ]]; then
                ARGS+=("${arg:0:3}$(convert_path "$rest")")
            elif [[ "$rest" == */* ]]; then
                # Relative path
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
            # /I with relative path or no path
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
        # Key insight: MSVC flags are /Xx or /WORD — they never contain
        # multiple slashes, so /home/... is clearly a path.
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
        */*.cpp|*/*.c|*/*.obj|*/*.CPP|*/*.C|*/*.OBJ|*/*.lib|*/*.LIB|*/*.def|*/*.DEF)
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

exec wine "$VC6_BIN/CL.EXE" "${ARGS[@]}"
