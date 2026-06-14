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
add_subdirectory(topo)

# ========================================================================
# gbengine.dll — 引擎核心 (depends on topo)
# ========================================================================
message(STATUS "Configuring gbengine.dll")
add_subdirectory(gbengine)

# ========================================================================
# PAL3.exe — 游戏逻辑 (depends on gbengine)
# ========================================================================
message(STATUS "Configuring PAL3.exe")
add_subdirectory(pal3)
