# manual/pal3 可编译基（CMakeLists——MSVC 6.0·参考 codegen 编译流程）
# 迁移起点：WinMain+mock→可编译→调用链推进→可运行
# 编译（参考 cli.py cmd_compile）：
#   cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchain-vc6.cmake .
#   ninja -C build -k 0
cmake_minimum_required(VERSION 3.10)
project(PAL3_manual CXX)

# 手动改写域（manual/pal3）——独立 codegen
add_executable(PAL3_manual
    platform/windows/WinMain.cpp
    mock/mock_interfaces.cpp
)

# Windows 库（user32/gdi32）
target_link_libraries(PAL3_manual user32 gdi32)

# 编译选项（MSVC 6.0——匹配原版）
target_compile_options(PAL3_manual PRIVATE /W3 /GX /O2 /Ob2 /Oi /Ot /Oy)
