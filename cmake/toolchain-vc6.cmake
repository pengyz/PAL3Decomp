# CMake Toolchain File for VC6 (cl.exe 12.00.8804)
#
# Usage:
#   cmake -B build/gbengine -G "NMake Makefiles" ^
#     -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake ^
#     -DBUILD_TARGET=gbengine ^
#     -DCMAKE_MAKE_PROGRAM=tools/vc6/Bin/NMAKE.EXE
#   cmake --build build/gbengine
#

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR X86)

# VC6 root: tools/vc6/ contains Bin/, Include/, Lib/
get_filename_component(VC6_ROOT "${CMAKE_CURRENT_LIST_DIR}/../tools/vc6" ABSOLUTE)

set(CMAKE_C_COMPILER   "${VC6_ROOT}/Bin/CL.EXE")
set(CMAKE_CXX_COMPILER "${VC6_ROOT}/Bin/CL.EXE")
set(CMAKE_LINKER       "${VC6_ROOT}/Bin/LINK.EXE")
set(CMAKE_AR           "${VC6_ROOT}/Bin/LIB.EXE")

# Skip compiler detection (VC6 won't pass CMake's test programs)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

# Identify as MSVC 6.0
set(MSVC TRUE)
set(MSVC_VERSION 1200)
set(CMAKE_C_COMPILER_ID "MSVC")
set(CMAKE_CXX_COMPILER_ID "MSVC")
set(CMAKE_C_COMPILER_VERSION "12.0")
set(CMAKE_CXX_COMPILER_VERSION "12.0")

# Include and library search paths
include_directories(SYSTEM "${VC6_ROOT}/Include")
link_directories("${VC6_ROOT}/Lib")
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES "${VC6_ROOT}/Include")
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${VC6_ROOT}/Include")

# Default to Release build (matching original binary)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
