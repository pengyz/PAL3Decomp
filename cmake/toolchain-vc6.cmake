# CMake Toolchain File for VC6 (cl.exe 12.00.8804)
#
# Supports both Windows (native) and Linux (via Wine wrappers).
# The Wine wrappers (tools/wine_cl.sh etc.) handle path conversion
# automatically — CMake passes normal Unix paths and the wrappers
# translate them to Wine Z: drive format before calling the real .EXE.
#
# Usage (Windows - NMake):
#   cmake -B build/gbengine -G "NMake Makefiles" ^
#     -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake ^
#     -DBUILD_TARGET=gbengine ^
#     -DCMAKE_MAKE_PROGRAM=tools/vc6/Bin/NMAKE.EXE
#   cmake --build build/gbengine
#
# Usage (Linux + Wine):
#   cmake -B build/gbengine -G "Unix Makefiles" \
#     -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake \
#     -DBUILD_TARGET=gbengine
#   cmake --build build/gbengine
#

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR X86)

# VC6 root: tools/vc6/ contains Bin/, Include/, Lib/
get_filename_component(VC6_ROOT "${CMAKE_CURRENT_LIST_DIR}/../tools/vc6" ABSOLUTE)
get_filename_component(TOOLS_DIR "${CMAKE_CURRENT_LIST_DIR}/../tools" ABSOLUTE)

# --------------------------------------------------------------------------
# Platform-specific tool selection
# --------------------------------------------------------------------------
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(VC6_USE_WINE TRUE)
    # Wine wrapper scripts: accept Unix paths, convert internally
    set(CMAKE_C_COMPILER   "${TOOLS_DIR}/wine_cl.sh")
    set(CMAKE_CXX_COMPILER "${TOOLS_DIR}/wine_cl.sh")
    set(CMAKE_LINKER       "${TOOLS_DIR}/wine_link.sh")
    set(CMAKE_AR           "${TOOLS_DIR}/wine_lib.sh")
    set(CMAKE_C_COMPILER_AR "${TOOLS_DIR}/wine_lib.sh")
    set(CMAKE_CXX_COMPILER_AR "${TOOLS_DIR}/wine_lib.sh")
else()
    set(VC6_USE_WINE FALSE)
    set(CMAKE_C_COMPILER   "${VC6_ROOT}/Bin/CL.EXE")
    set(CMAKE_CXX_COMPILER "${VC6_ROOT}/Bin/CL.EXE")
    set(CMAKE_LINKER       "${VC6_ROOT}/Bin/LINK.EXE")
    set(CMAKE_AR           "${VC6_ROOT}/Bin/LIB.EXE")
endif()

# --------------------------------------------------------------------------
# Skip compiler detection (VC6 won't pass CMake's test programs)
# --------------------------------------------------------------------------
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

# Identify as MSVC 6.0 to CMakeLists.txt logic
set(MSVC TRUE)
set(MSVC_VERSION 1200)
set(CMAKE_C_COMPILER_ID "MSVC")
set(CMAKE_CXX_COMPILER_ID "MSVC")
set(CMAKE_C_COMPILER_VERSION "12.0")
set(CMAKE_CXX_COMPILER_VERSION "12.0")

# --------------------------------------------------------------------------
# Compile/link rule templates for CMake
# --------------------------------------------------------------------------
# CMake needs to know how to invoke the compiler/linker.
# On Linux the wrappers handle path conversion, so we write rules
# using normal CMake variables (paths in host format).

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
# Include and library paths
# --------------------------------------------------------------------------
include_directories(SYSTEM "${VC6_ROOT}/Include")
link_directories("${VC6_ROOT}/Lib")
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES "${VC6_ROOT}/Include")
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${VC6_ROOT}/Include")

# Default to Release build (matching original binary)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
