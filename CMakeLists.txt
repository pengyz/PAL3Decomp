cmake_minimum_required(VERSION 3.10)
project(PAL3Decomp C CXX)

# PAL3 Decompilation Build Configuration
# ========================================
# This project targets MSVC to produce binary-compatible output with original binaries.
#
# Build target selection:
#   cmake -B build -DBUILD_TARGET=topo      (topo.dll - requires VC6)
#   cmake -B build -DBUILD_TARGET=gbengine  (gbengine.dll - requires VC6)
#   cmake -B build -DBUILD_TARGET=pal3      (PAL3.exe - requires VS2003/VC7.0)
#
# Or use the provided build.bat script for easier configuration.

# Build target selection
set(BUILD_TARGET "topo" CACHE STRING "Build target: topo, gbengine, or pal3")
message(STATUS "Build target: ${BUILD_TARGET}")

# Force 32-bit build
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "Must use 32-bit compiler. Use x86 Native Tools Command Prompt or setup_env.bat.")
endif()

# Compiler detection and configuration
if(MSVC)
    # Detect MSVC version
    if(MSVC_VERSION EQUAL 1200)
        message(STATUS "Detected: Visual C++ 6.0 (binary-exact mode)")
        set(COMPILER_VERSION "VC6")
    elseif(MSVC_VERSION EQUAL 1310)
        message(STATUS "Detected: Visual Studio .NET 2003 (binary-exact mode)")
        set(COMPILER_VERSION "VS2003")
    elseif(MSVC_VERSION EQUAL 1300)
        message(STATUS "Detected: Visual Studio .NET 2002 / VC7.0")
        set(COMPILER_VERSION "VS2002")
    else()
        message(WARNING "Modern MSVC detected (version ${MSVC_VERSION}). Binary matching NOT guaranteed.")
        set(COMPILER_VERSION "MODERN")
    endif()

    # Base flags for all targets
    set(CMAKE_C_FLAGS "/nologo /W3")
    set(CMAKE_CXX_FLAGS "/nologo /W3")

    # Target-specific flags
    if(BUILD_TARGET STREQUAL "topo" OR BUILD_TARGET STREQUAL "gbengine")
        # VC6 flags for DLLs
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GX")  # Enable C++ exceptions (VC6 style)
        set(CMAKE_C_FLAGS_RELEASE "/O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS")
        set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS")

        if(COMPILER_VERSION STREQUAL "VC6")
            # Verified VC6 settings
            add_compile_options(/GF)  # String pooling
            add_compile_options(/Gy)  # Function-level linking
        endif()
    elseif(BUILD_TARGET STREQUAL "pal3")
        # VC7.0/VS2003 flags for PAL3.exe
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /GR")  # Modern exception handling + RTTI
        set(CMAKE_C_FLAGS_RELEASE "/O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD")
        set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD")

        if(COMPILER_VERSION STREQUAL "VS2003" OR COMPILER_VERSION STREQUAL "VS2002")
            # Link-time code generation (if supported)
            # add_compile_options(/GL)
            # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LTCG")
        endif()
    endif()

    # Debug flags (for development/testing)
    set(CMAKE_C_FLAGS_DEBUG "/Od /Zi /DDEBUG /DWIN32 /D_WINDOWS")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /DDEBUG /DWIN32 /D_WINDOWS")

    # Calling convention: __cdecl (default for MSVC)
    add_compile_options(/Gd)

    # Disable modern MSVC security features not present in original
    add_compile_options(/GS-)

    # Struct packing (8-byte default, verify from RE)
    # add_compile_options(/Zp8)
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

# Source file collections based on build target
if(BUILD_TARGET STREQUAL "topo")
    message(STATUS "Configuring topo.dll build")
    file(GLOB TOPO_SOURCES "src/topo/*.cpp" "src/topo/*.c")

    if(TOPO_SOURCES)
        add_library(topo SHARED ${TOPO_SOURCES})
        target_include_directories(topo PUBLIC include)
        set_target_properties(topo PROPERTIES
            OUTPUT_NAME "topo"
            PREFIX ""
            SUFFIX ".dll"
        )

        # Generate assembly listings for comparison
        if(MSVC)
            file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/asm)
            target_compile_options(topo PRIVATE /FAcs /Fa${CMAKE_BINARY_DIR}/asm/)
        endif()

        message(STATUS "topo.dll: ${TOPO_SOURCES} (${CMAKE_CURRENT_LIST_FILE})")
    else()
        message(WARNING "No source files found in src/topo/")
    endif()

elseif(BUILD_TARGET STREQUAL "gbengine")
    message(STATUS "Configuring gbengine.dll build")
    file(GLOB_RECURSE GBENGINE_SOURCES "src/gbengine/*.cpp" "src/gbengine/*.c")

    if(GBENGINE_SOURCES)
        add_library(gbengine SHARED ${GBENGINE_SOURCES})
        target_include_directories(gbengine PUBLIC include)
        set_target_properties(gbengine PROPERTIES
            OUTPUT_NAME "gbengine"
            PREFIX ""
            SUFFIX ".dll"
        )

        # Link DirectX and other dependencies
        target_link_libraries(gbengine ${PLATFORM_LIBS})

        if(MSVC)
            file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/asm)
            target_compile_options(gbengine PRIVATE /FAcs /Fa${CMAKE_BINARY_DIR}/asm/)
        endif()

        message(STATUS "gbengine.dll: ${CMAKE_CURRENT_LIST_FILE} source files")
    else()
        message(WARNING "No source files found in src/gbengine/")
    endif()

elseif(BUILD_TARGET STREQUAL "pal3")
    message(STATUS "Configuring PAL3.exe build")
    file(GLOB_RECURSE PAL3_SOURCES "src/pal3/*.cpp" "src/pal3/*.c")

    if(PAL3_SOURCES)
        add_executable(pal3 ${PAL3_SOURCES})
        target_include_directories(pal3 PUBLIC include)
        set_target_properties(pal3 PROPERTIES
            OUTPUT_NAME "PAL3"
            SUFFIX ".exe"
        )

        target_link_libraries(pal3 ${PLATFORM_LIBS})

        if(MSVC)
            file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/asm)
            target_compile_options(pal3 PRIVATE /FAcs /Fa${CMAKE_BINARY_DIR}/asm/)
        endif()

        message(STATUS "PAL3.exe: ${CMAKE_CURRENT_LIST_FILE} source files")
    else()
        message(WARNING "No source files found in src/pal3/")
    endif()

else()
    message(FATAL_ERROR "Invalid BUILD_TARGET: ${BUILD_TARGET}. Must be 'topo', 'gbengine', or 'pal3'")
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
