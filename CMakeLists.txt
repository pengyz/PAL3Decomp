cmake_minimum_required(VERSION 3.10)
project(PAL3Decomp C CXX)

# PAL3 Decompilation Build Configuration
# ========================================
# This project targets MSVC (Visual Studio .NET 2003 / MSVC 7.1)
# to produce binary-compatible output with the original PAL3.exe.
#
# Usage:
#   cmake -B build -G "NMake Makefiles" -DCMAKE_C_COMPILER=cl
#   cmake --build build
#
# Or with Visual Studio 2003 command prompt:
#   cmake -B build -G "NMake Makefiles"
#   cd build && nmake

# Force 32-bit build
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "Must use 32-bit compiler. Use x86 Native Tools Command Prompt.")
endif()

# Compiler detection and configuration
if(MSVC)
    # Match original compilation flags
    # These need to be confirmed from the PE Rich Header analysis
    set(CMAKE_C_FLAGS "/nologo /GS- /W3")
    set(CMAKE_CXX_FLAGS "/nologo /GS- /W3 /GR /EHsc")

    # Release flags (default - matches original binary)
    set(CMAKE_C_FLAGS_RELEASE "/O2 /DNDEBUG /DWIN32 /D_WINDOWS")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG /DWIN32 /D_WINDOWS")

    # Debug flags (for development/testing)
    set(CMAKE_C_FLAGS_DEBUG "/Od /Zi /DDEBUG /DWIN32 /D_WINDOWS")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /DDEBUG /DWIN32 /D_WINDOWS")

    # Calling convention: __cdecl (default for MSVC)
    add_compile_options(/Gd)

    # Disable modern MSVC security features not present in original
    add_compile_options(/GS-)

    # Struct packing (verify from reverse engineering)
    # add_compile_options(/Zp8)  # 8-byte alignment (default)
else()
    message(WARNING
        "Non-MSVC compiler detected. Binary matching will NOT work. "
        "This configuration is for development/testing only.")
    set(CMAKE_C_FLAGS "-m32 -Wall")
    set(CMAKE_CXX_FLAGS "-m32 -Wall")
endif()

# Include paths
include_directories(${CMAKE_SOURCE_DIR}/include)

# Platform libraries (Windows)
if(WIN32)
    set(PLATFORM_LIBS
        kernel32
        user32
        gdi32
        ole32
        winmm
        # DirectX libraries (add as needed)
        # d3d8 or d3d9
        # dinput8
        # dsound
    )
endif()

# Source file collections - add files as they are decompiled
# Core engine
file(GLOB_RECURSE CORE_SOURCES "src/core/*.c" "src/core/*.cpp")

# Game logic
file(GLOB_RECURSE GAME_SOURCES "src/game/*.c" "src/game/*.cpp")

# Script engine
file(GLOB_RECURSE SCRIPT_SOURCES "src/script/*.c" "src/script/*.cpp")

# Third-party stubs
file(GLOB_RECURSE THIRDPARTY_SOURCES "src/third_party/*.c" "src/third_party/*.cpp")

# Combine all sources
set(ALL_SOURCES
    ${CORE_SOURCES}
    ${GAME_SOURCES}
    ${SCRIPT_SOURCES}
    ${THIRDPARTY_SOURCES}
)

# Only build if we have source files
if(ALL_SOURCES)
    # Build as static library first (for incremental development)
    add_library(pal3_lib STATIC ${ALL_SOURCES})
    target_include_directories(pal3_lib PUBLIC include)

    # Build as executable when ready
    # add_executable(PAL3 ${ALL_SOURCES})
    # target_link_libraries(PAL3 ${PLATFORM_LIBS})

    # Individual object file compilation (for per-function comparison)
    # This allows comparing individual .obj files against original
    if(MSVC)
        # Generate assembly listings for comparison
        target_compile_options(pal3_lib PRIVATE /FA /Fa${CMAKE_BINARY_DIR}/asm/)
    endif()
else()
    message(STATUS "No source files found yet. Add decompiled .c/.cpp files to src/")
endif()

# Custom target: compare a specific function
# Usage: cmake --build build --target compare_func -- FUNC_ADDR=0x00401000
add_custom_target(compare_func
    COMMAND python ${CMAKE_SOURCE_DIR}/tools/compare.py
        --source ${FUNC_SOURCE}
        --func-addr ${FUNC_ADDR}
        --func-size ${FUNC_SIZE}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Comparing function at ${FUNC_ADDR}"
)

# Custom target: run progress report
add_custom_target(progress
    COMMAND python ${CMAKE_SOURCE_DIR}/tools/progress.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Showing decompilation progress"
)

# Custom target: batch export from Ghidra
add_custom_target(ghidra_export
    COMMAND echo "Run manually: analyzeHeadless <project> PAL3Project -process PAL3.exe -postScript ghidra_export.py"
    COMMENT "Ghidra export reminder"
)
