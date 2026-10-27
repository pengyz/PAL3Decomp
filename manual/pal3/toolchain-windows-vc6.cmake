# toolchain-windows-vc6.cmake - Windows MSVC 6.0 (CMake toolchain integration)
# Relative paths (no absolute) - reference: cmake/toolchain-vc6.cmake
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-windows-vc6.cmake -G Ninja ..

get_filename_component(VC6_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../tools/compilers/msvc6.0" ABSOLUTE)
get_filename_component(VC6_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/../../tools/vc6/Lib" ABSOLUTE)
get_filename_component(VC6_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../tools/vc6/Include" ABSOLUTE)
get_filename_component(GBENGINE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../gbengine" ABSOLUTE)
get_filename_component(GBENGINE_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/../../include" ABSOLUTE)

# Environment FIRST (before compiler detection - CMake's test compile needs INCLUDE/LIB)
set(ENV{INCLUDE} "${VC6_ROOT}/include;${VC6_INCLUDE_DIR};${GBENGINE_INCLUDE};${GBENGINE_INCLUDE}/gbengine")
set(ENV{LIB} "${VC6_ROOT}/lib;${VC6_LIB_DIR};${GBENGINE_DIR}")

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER "${VC6_ROOT}/bin/cl.exe")
set(CMAKE_CXX_COMPILER "${VC6_ROOT}/bin/cl.exe")
set(CMAKE_LINKER "${VC6_ROOT}/bin/link.exe")

# MSVC 6.0 identification (skip compiler test - MSVC6 old)
set(MSVC TRUE)
set(MSVC_VERSION 1200)
set(CMAKE_C_COMPILER_ID "MSVC")
set(CMAKE_CXX_COMPILER_ID "MSVC")
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_C_ABI_COMPILED 1)
set(CMAKE_CXX_ABI_COMPILED 1)
