cmake_minimum_required(VERSION 3.10)
project(PAL3Decomp C CXX)

# PAL3 Decompilation Build Configuration
# ========================================
# Builds: topo.dll → gbengine.dll → PAL3.exe (dependency order)
# Requires: VC6 SP0 toolchain (cmake/toolchain-vc6.cmake)
#
# Usage:
#   cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake -G Ninja
#   cmake --build build

# Force 32-bit build
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "Must use 32-bit compiler. Use x86 Native Tools Command Prompt or VC6 toolchain.")
endif()

# Compiler detection
if(MSVC)
    if(MSVC_VERSION EQUAL 1200)
        message(STATUS "Detected: Visual C++ 6.0 SP0 (binary-exact mode)")
        set(COMPILER_VERSION "VC6")
    else()
        message(WARNING "Modern MSVC detected (version ${MSVC_VERSION}). Binary matching NOT guaranteed.")
        set(COMPILER_VERSION "MODERN")
    endif()
endif()

# Module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# MSVC-specific settings
if(MSVC)
    include(MSVCSettings)
endif()

# Global include path
include_directories(${CMAKE_SOURCE_DIR}/include)

# Platform libraries
if(WIN32)
    set(PLATFORM_LIBS kernel32.lib user32.lib gdi32.lib ole32.lib winmm.lib advapi32.lib)
endif()

# ========================================================================
# topo.dll — 数学库
# ========================================================================
message(STATUS "Configuring topo.dll")
file(GLOB TOPO_SOURCES "src/topo/*.cpp" "src/topo/*.c")

if(TOPO_SOURCES)
    add_library(topo SHARED ${TOPO_SOURCES})
    target_include_directories(topo PUBLIC include)
    set_target_properties(topo PROPERTIES OUTPUT_NAME "topo" PREFIX "" SUFFIX ".dll")
    target_compile_options(topo PRIVATE ${TOPO_GBENGINE_COMPILE_FLAGS} /Zp4)
    target_link_libraries(topo "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/LIBCMT.LIB" kernel32.lib)
    if(MSVC_VERSION EQUAL 1200)
        set_target_properties(topo PROPERTIES
            LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/lib/topo.def\" /MAP:\"${CMAKE_BINARY_DIR}/topo.map\"")
    else()
        set_target_properties(topo PROPERTIES
            LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/lib/topo.def\" /SAFESEH:NO /MAP:\"${CMAKE_BINARY_DIR}/topo.map\"")
        target_link_libraries(topo vcruntime.lib ucrt.lib)
        target_link_options(topo PRIVATE /FORCE:MULTIPLE)
    endif()
endif()

# ========================================================================
# gbengine.dll — 引擎核心 (depends on topo)
# ========================================================================
message(STATUS "Configuring gbengine.dll")
file(GLOB_RECURSE GBENGINE_SOURCES "src/gbengine/*.cpp" "src/gbengine/*.c")

if(GBENGINE_SOURCES)
    add_library(gbengine SHARED ${GBENGINE_SOURCES})
    target_include_directories(gbengine PUBLIC include "${CMAKE_SOURCE_DIR}/tools/vc6/Include")
    set_target_properties(gbengine PROPERTIES OUTPUT_NAME "gbengine" PREFIX "" SUFFIX ".dll")
    target_link_libraries(gbengine
        topo
        ${PLATFORM_LIBS}
        "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/LIBCMT.LIB"
        "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/d3d9.lib"
        "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/d3dx9.lib"
        "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/dinput8.lib"
        "${CMAKE_SOURCE_DIR}/tools/vc6/Lib/mss32.lib"
        "${CMAKE_SOURCE_DIR}/lib/ijl15.lib"
    )
    target_compile_options(gbengine PRIVATE ${TOPO_GBENGINE_COMPILE_FLAGS})
    if(MSVC_VERSION EQUAL 1200)
        set_target_properties(gbengine PROPERTIES
            LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/src/gbengine/gbengine.def\" /BASE:0x10000000 /MAP:\"${CMAKE_BINARY_DIR}/gbengine.map\"")
    else()
        set_target_properties(gbengine PROPERTIES
            LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/src/gbengine/gbengine.def\" /BASE:0x10000000 /SAFESEH:NO /MAP:\"${CMAKE_BINARY_DIR}/gbengine.map\"")
        target_link_libraries(gbengine vcruntime.lib ucrt.lib)
        target_link_options(gbengine PRIVATE /FORCE:MULTIPLE)
    endif()
endif()

# ========================================================================
# PAL3.exe — 游戏逻辑 (depends on gbengine)
# ========================================================================
message(STATUS "Configuring PAL3.exe")
add_subdirectory(src/pal3)
