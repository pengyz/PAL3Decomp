# CMake Toolchain File for VC7.1 (cl.exe 13.10 - Visual Studio .NET 2003)
#
# Supports both Windows (native) and Linux (via Wine wrappers).
# The Wine wrappers (tools/wine_cl71.sh etc.) handle path conversion
# automatically — CMake passes normal Unix paths and the wrappers
# translate them to Wine Z: drive format before calling the real .EXE.
#
# Usage (Linux + Wine):
#   cmake -B build/pal3a -G "Unix Makefiles" \
#     -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc71.cmake \
#     -DBUILD_TARGET=pal3a
#   cmake --build build/pal3a
#
# Usage (Windows - NMake):
#   cmake -B build/pal3a -G "NMake Makefiles" ^
#     -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc71.cmake ^
#     -DBUILD_TARGET=pal3a
#   cmake --build build/pal3a
#
# Required files in tools/vc71/:
#   Bin/cl.exe, Bin/c1.dll, Bin/c1xx.dll, Bin/c2.dll, Bin/link.exe, Bin/lib.exe
#   Bin/mspdb71.dll, Bin/msvcr71.dll, Bin/1033/ (locale resources)
#   Include/ (VC7.1 CRT headers: stdio.h, stdlib.h, etc.)
#   Lib/ (VC7.1 CRT libs: libcmt.lib, msvcrt.lib, etc.)
#   PlatformSDK/Include/ (windows.h, d3d9.h, etc.)
#   PlatformSDK/Lib/ (kernel32.lib, user32.lib, d3d9.lib, etc.)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR X86)

# VC7.1 root: tools/vc71/ contains Bin/, Include/, Lib/, PlatformSDK/
get_filename_component(VC71_ROOT "${CMAKE_CURRENT_LIST_DIR}/../tools/vc71" ABSOLUTE)
get_filename_component(TOOLS_DIR "${CMAKE_CURRENT_LIST_DIR}/../tools" ABSOLUTE)

# --------------------------------------------------------------------------
# Platform-specific tool selection
# --------------------------------------------------------------------------
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(VC71_USE_WINE TRUE)
    # Wine wrapper scripts: accept Unix paths, convert internally
    set(CMAKE_C_COMPILER   "${TOOLS_DIR}/wine_cl71.sh")
    set(CMAKE_CXX_COMPILER "${TOOLS_DIR}/wine_cl71.sh")
    set(CMAKE_LINKER       "${TOOLS_DIR}/wine_link71.sh")
    set(CMAKE_AR           "${TOOLS_DIR}/wine_lib71.sh")
    set(CMAKE_C_COMPILER_AR "${TOOLS_DIR}/wine_lib71.sh")
    set(CMAKE_CXX_COMPILER_AR "${TOOLS_DIR}/wine_lib71.sh")
else()
    set(VC71_USE_WINE FALSE)
    set(CMAKE_C_COMPILER   "${VC71_ROOT}/Bin/cl.exe")
    set(CMAKE_CXX_COMPILER "${VC71_ROOT}/Bin/cl.exe")
    set(CMAKE_LINKER       "${VC71_ROOT}/Bin/link.exe")
    set(CMAKE_AR           "${VC71_ROOT}/Bin/lib.exe")
endif()

# --------------------------------------------------------------------------
# Skip compiler detection (VC7.1 won't pass CMake's test programs easily)
# --------------------------------------------------------------------------
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

# Identify as MSVC 7.1 to CMakeLists.txt logic
set(MSVC TRUE)
set(MSVC_VERSION 1310)
set(CMAKE_C_COMPILER_ID "MSVC")
set(CMAKE_CXX_COMPILER_ID "MSVC")
set(CMAKE_C_COMPILER_VERSION "13.10")
set(CMAKE_CXX_COMPILER_VERSION "13.10")

# --------------------------------------------------------------------------
# Compile/link rule templates for CMake
# --------------------------------------------------------------------------
set(CMAKE_C_COMPILE_OBJECT
    "<CMAKE_C_COMPILER> /nologo /c <DEFINES> <INCLUDES> <FLAGS> /Fo<OBJECT> <SOURCE>")
set(CMAKE_CXX_COMPILE_OBJECT
    "<CMAKE_CXX_COMPILER> /nologo /c <DEFINES> <INCLUDES> <FLAGS> /Fo<OBJECT> <SOURCE>")

set(CMAKE_C_CREATE_SHARED_LIBRARY
    "<CMAKE_LINKER> /nologo /DLL <LINK_FLAGS> /OUT:<TARGET> <OBJECTS> <LINK_LIBRARIES>")
set(CMAKE_CXX_CREATE_SHARED_LIBRARY
    "<CMAKE_LINKER> /nologo /DLL <LINK_FLAGS> /OUT:<TARGET> <OBJECTS> <LINK_LIBRARIES>")

set(CMAKE_C_CREATE_SHARED_MODULE ${CMAKE_C_CREATE_SHARED_LIBRARY})
set(CMAKE_CXX_CREATE_SHARED_MODULE ${CMAKE_CXX_CREATE_SHARED_LIBRARY})

set(CMAKE_C_LINK_EXECUTABLE
    "<CMAKE_LINKER> /nologo <LINK_FLAGS> /OUT:<TARGET> <OBJECTS> <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE
    "<CMAKE_LINKER> /nologo <LINK_FLAGS> /OUT:<TARGET> <OBJECTS> <LINK_LIBRARIES>")

set(CMAKE_C_CREATE_STATIC_LIBRARY
    "<CMAKE_AR> /nologo /OUT:<TARGET> <OBJECTS>")
set(CMAKE_CXX_CREATE_STATIC_LIBRARY
    "<CMAKE_AR> /nologo /OUT:<TARGET> <OBJECTS>")

# Object file extension
set(CMAKE_C_OUTPUT_EXTENSION ".obj")
set(CMAKE_CXX_OUTPUT_EXTENSION ".obj")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")
set(CMAKE_IMPORT_LIBRARY_PREFIX "")
set(CMAKE_IMPORT_LIBRARY_SUFFIX ".lib")
set(CMAKE_EXECUTABLE_SUFFIX ".exe")

# --------------------------------------------------------------------------
# Suppress CMake's default Windows libraries
# --------------------------------------------------------------------------
set(CMAKE_C_STANDARD_LIBRARIES "" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD_LIBRARIES "" CACHE STRING "" FORCE)

# --------------------------------------------------------------------------
# Include and library paths
# --------------------------------------------------------------------------
# VC7.1 has a split: CRT headers in VC71/Include, Platform SDK in PlatformSDK/Include
include_directories(SYSTEM
    "${VC71_ROOT}/Include"
    "${VC71_ROOT}/PlatformSDK/Include"
)
link_directories(
    "${VC71_ROOT}/Lib"
    "${VC71_ROOT}/PlatformSDK/Lib"
)
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES
    "${VC71_ROOT}/Include"
    "${VC71_ROOT}/PlatformSDK/Include"
)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
    "${VC71_ROOT}/Include"
    "${VC71_ROOT}/PlatformSDK/Include"
)

# Default to Release build (matching original binary)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
