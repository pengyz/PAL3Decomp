cmake_minimum_required(VERSION 3.10)
project(PAL3Decomp C CXX)

# PAL3 Decompilation Build Configuration
# ========================================
# This project targets MSVC to produce binary-compatible output with original binaries.
#
# Build target selection:
#   cmake -B build -DBUILD_TARGET=topo      (topo.dll - requires VC6)
#   cmake -B build -DBUILD_TARGET=gbengine  (gbengine.dll + topo.dll - requires VC6)
#   cmake -B build -DBUILD_TARGET=pal3      (PAL3.exe - requires VC6 SP0)
#   cmake -B build -DBUILD_TARGET=pal3a     (PAL3A.exe)
#
# Dependency graph: gbengine.dll → topo.dll (auto-built as dependency)
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
        message(STATUS "Detected: Visual C++ 6.0 SP0 (binary-exact mode)")
        set(COMPILER_VERSION "VC6")
    else()
        message(WARNING "Modern MSVC detected (version ${MSVC_VERSION}). Binary matching NOT guaranteed.")
        set(COMPILER_VERSION "MODERN")
    endif()
else()
    message(WARNING
        "Non-MSVC compiler detected. Binary matching will NOT work. "
        "This configuration is for development/testing only.")
    set(CMAKE_C_FLAGS "-m32 -Wall")
    set(CMAKE_CXX_FLAGS "-m32 -Wall")
endif()

# Set CMAKE_MODULE_PATH for find_package to locate custom modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Include MSVC-specific settings (flags, optimizations)
if(MSVC)
    include(MSVCSettings)
endif()

# Include paths
include_directories(${CMAKE_SOURCE_DIR}/include)

# Platform libraries (Windows)
# Use .lib suffix explicitly so CMake passes them directly to the linker
# without trying to resolve paths (which breaks under Wine)
if(WIN32)
    set(PLATFORM_LIBS
        kernel32.lib
        user32.lib
        gdi32.lib
        ole32.lib
        winmm.lib
        advapi32.lib
    )
endif()

# ========================================================================
# topo.dll — 数学库 (gbengine.dll 的依赖)
# 当 BUILD_TARGET=topo 或 BUILD_TARGET=gbengine 时构建
# ========================================================================
if(BUILD_TARGET STREQUAL "topo" OR BUILD_TARGET STREQUAL "gbengine")
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

        # Apply VC6 optimization flags
        target_compile_options(topo PRIVATE ${TOPO_GBENGINE_COMPILE_FLAGS} /Zp4)

        # Use .def file for exports (matching original DLL export table)
        if(MSVC_VERSION EQUAL 1200)
            set_target_properties(topo PROPERTIES
                LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/lib/topo.def\" /MAP:\"${CMAKE_BINARY_DIR}/topo.map\""
            )
        else()
            set_target_properties(topo PROPERTIES
                LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/lib/topo.def\" /SAFESEH:NO /MAP:\"${CMAKE_BINARY_DIR}/topo.map\""
            )
        endif()

        # Link libraries
        target_link_libraries(topo
            "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/LIBCMT.LIB"
            kernel32.lib
        )

        # Modern MSVC needs vcruntime
        if(MSVC_VERSION GREATER_EQUAL 1900)
            target_link_libraries(topo vcruntime.lib ucrt.lib)
            target_link_options(topo PRIVATE /FORCE:MULTIPLE)
        endif()

        # Generate assembly listings for topo-only build
        if(BUILD_TARGET STREQUAL "topo" AND MSVC)
            file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/asm)
            target_compile_options(topo PRIVATE /FAcs /Fa${CMAKE_BINARY_DIR}/asm/)
        endif()

        message(STATUS "topo.dll: ${TOPO_SOURCES}")
    else()
        message(WARNING "No source files found in src/topo/")
    endif()
endif()

# ========================================================================
# gbengine.dll — 引擎核心 (依赖 topo.dll)
# ========================================================================
if(BUILD_TARGET STREQUAL "gbengine")
    message(STATUS "Configuring gbengine.dll build")
    file(GLOB_RECURSE GBENGINE_SOURCES "src/gbengine/*.cpp" "src/gbengine/*.c")

    if(GBENGINE_SOURCES)
        add_library(gbengine SHARED ${GBENGINE_SOURCES})
        target_include_directories(gbengine PUBLIC include
            "${CMAKE_SOURCE_DIR}/tools/vc6/Include"
        )
        set_target_properties(gbengine PROPERTIES
            OUTPUT_NAME "gbengine"
            PREFIX ""
            SUFFIX ".dll"
        )

        # Link dependencies — topo 来自构建产物，不再用预构建的 lib/topo.lib
        target_link_libraries(gbengine ${PLATFORM_LIBS}
            topo
            "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/LIBCMT.LIB"
            "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/d3d9.lib"
            "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/d3dx9.lib"
            "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/dinput8.lib"
            "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/mss32.lib"
            "${CMAKE_SOURCE_DIR}/lib/ijl15.lib"
        )

        # Modern MSVC needs vcruntime for __CxxFrameHandler3/__ftol2 etc.
        # VC6 LIBCMT.LIB provides CRT for d3dx9.lib; suppress duplicates.
        if(MSVC_VERSION GREATER_EQUAL 1900)
            target_link_libraries(gbengine vcruntime.lib ucrt.lib)
            target_link_options(gbengine PRIVATE /FORCE:MULTIPLE)
        endif()

        # Use .def file for exports (matching original DLL export table)
        if(MSVC_VERSION EQUAL 1200)
            set_target_properties(gbengine PROPERTIES
                LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/src/gbengine/gbengine.def\" /BASE:0x10000000 /MAP:\"${CMAKE_BINARY_DIR}/gbengine.map\""
            )
        else()
            set_target_properties(gbengine PROPERTIES
                LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/src/gbengine/gbengine.def\" /BASE:0x10000000 /SAFESEH:NO /MAP:\"${CMAKE_BINARY_DIR}/gbengine.map\""
            )
        endif()

        # Apply VC6 optimization flags
        target_compile_options(gbengine PRIVATE ${TOPO_GBENGINE_COMPILE_FLAGS})

        message(STATUS "gbengine.dll: depends on topo.dll (from build)")
    else()
        message(WARNING "No source files found in src/gbengine/")
    endif()
endif()

# ========================================================================
# PAL3.exe / PAL3A.exe — 游戏可执行文件
# ========================================================================
if(BUILD_TARGET STREQUAL "pal3")
    message(STATUS "Configuring PAL3.exe build")

    # PAL3.exe 反编译源文件列表
    # 随 BFS 调用图展开逐步添加。每个文件包含已实现函数 + callee stub。
    # 维护规则: 新增 .cpp 文件时添加到此列表。
    set(PAL3_SOURCES
        src/pal3/WinMain.cpp
        src/pal3/gamebase/PAL3.cpp
        src/pal3/gamebase/ScreenMode.cpp
        src/pal3/gamebase/GRPinput.cpp
        src/pal3/Combat/CBSystem.cpp
        src/pal3/Combat/CBStage.cpp
        src/pal3/globals.cpp
    )

    add_executable(pal3 WIN32 ${PAL3_SOURCES})
    target_include_directories(pal3 PUBLIC include)
    set_target_properties(pal3 PROPERTIES
        OUTPUT_NAME "PAL3"
        SUFFIX ".exe"
    )

    if(MSVC)
        target_compile_options(pal3 PRIVATE ${PAL3_COMPILE_FLAGS})

        target_link_options(pal3 PRIVATE
            /SUBSYSTEM:WINDOWS
            /BASE:0x00400000
            /FIXED
            /MAP
            ${PAL3_EXE_LINK_FLAGS}
        )

        # Generate assembly listings for byte comparison
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/asm)
        target_compile_options(pal3 PRIVATE /FAcs /Fa${CMAKE_BINARY_DIR}/asm/)
    endif()

    target_link_libraries(pal3
        ${CMAKE_SOURCE_DIR}/lib/gbengine.lib
        ${PLATFORM_LIBS}
        advapi32
    )

    message(STATUS "PAL3.exe: ${list_length} source files configured")
endif()

if(BUILD_TARGET STREQUAL "pal3a")
    message(STATUS "Configuring PAL3A.exe build")

    file(GLOB_RECURSE PAL3A_SOURCES "src/pal3a/*.cpp" "src/pal3a/*.c")

    if(PAL3A_SOURCES)
        add_executable(PAL3A WIN32 ${PAL3A_SOURCES})
        target_include_directories(PAL3A PRIVATE
            ${CMAKE_SOURCE_DIR}/src/pal3a
            ${CMAKE_SOURCE_DIR}/include
        )
        target_link_libraries(PAL3A
            ${CMAKE_SOURCE_DIR}/lib/gbengine.lib
            ${CMAKE_SOURCE_DIR}/lib/topo.lib
            ${PLATFORM_LIBS}
            advapi32
        )

        target_compile_definitions(PAL3A PRIVATE PAL3A_DEV_MODE)

        set_target_properties(PAL3A PROPERTIES OUTPUT_NAME "PAL3A")

        if(MSVC)
            target_link_options(PAL3A PRIVATE
                /SUBSYSTEM:WINDOWS
                /ENTRY:WinMainCRTStartup
                /DYNAMICBASE:NO
                /BASE:0x00400000
                /MAP
            )
            file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/asm)
            target_compile_options(PAL3A PRIVATE /FAcs /Fa${CMAKE_BINARY_DIR}/asm/)
        endif()

        list(LENGTH PAL3A_SOURCES PAL3A_SRC_COUNT)
        message(STATUS "PAL3A.exe: ${PAL3A_SRC_COUNT} source files")
    else()
        message(WARNING "No source files found in src/pal3a/")
    endif()
endif()

# Validate BUILD_TARGET
set(_VALID_TARGETS topo gbengine pal3 pal3a)
if(NOT BUILD_TARGET IN_LIST _VALID_TARGETS)
    message(FATAL_ERROR "Invalid BUILD_TARGET: ${BUILD_TARGET}. Must be 'topo', 'gbengine', 'pal3', or 'pal3a'")
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
