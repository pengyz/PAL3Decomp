# manual/pal3 可编译基（CMakeLists——MSVC 6.0·tools/vc6）
# 迁移起点：WinMain+mock→可编译→调用链推进→可运行
# 参考：cmake/toolchain-vc6.cmake（codegen 编译脚本）
cmake_minimum_required(VERSION 3.10)
project(PAL3_manual CXX)

# MSVC 6.0 工具链（wine_cl.sh——参考 toolchain-vc6.cmake）
set(VC6_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../tools/compilers/msvc6.0")
set(VC6_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/../../tools/vc6/Lib")
set(DXSDK_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/../../tools/vc6/Include")
set(TOOLS_DIR "${CMAKE_CURRENT_LIST_DIR}/../../tools")

if(WIN32)
    set(CMAKE_C_COMPILER "${TOOLS_DIR}/wine_cl.sh")
    set(CMAKE_CXX_COMPILER "${TOOLS_DIR}/wine_cl.sh")
endif()

# MSVC 6.0 标识（CMakeLists 逻辑）
set(MSVC TRUE)
set(MSVC_VERSION 1200)
set(CMAKE_C_COMPILER_ID "MSVC")
set(CMAKE_CXX_COMPILER_ID "MSVC")

# 手动改写域（manual/pal3）——独立 codegen
add_executable(PAL3_manual
    platform/windows/WinMain.cpp
    mock/mock_interfaces.cpp
)

# Windows 库（user32/gdi32）
target_link_libraries(PAL3_manual user32 gdi32)

# 编译选项（MSVC 6.0——参考 MSVCSettings.cmake）
target_compile_options(PAL3_manual PRIVATE /W3 /GX /O2 /Ob2 /Oi /Ot /Oy)

# include 路径（DXSDK/VC6）
target_include_directories(PAL3_manual PRIVATE ${DXSDK_INCLUDE} ${VC6_ROOT}/include)
target_link_directories(PAL3_manual PRIVATE ${VC6_LIB_DIR})
