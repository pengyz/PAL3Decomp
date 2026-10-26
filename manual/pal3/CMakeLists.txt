# manual/pal3 可编译基（CMakeLists——MSVC 6.0）
# 迁移起点：WinMain+mock→可编译→调用链推进→可运行
cmake_minimum_required(VERSION 3.10)
project(PAL3_manual CXX)

# MSVC 6.0 工具链（wine_cl.sh）
set(CMAKE_CXX_COMPILER "wine_cl.sh")

# 手动改写域（manual/pal3）——独立 codegen
add_executable(PAL3_manual
    platform/windows/WinMain.cpp
    mock/mock_interfaces.cpp
)

# Windows 库（user32/gdi32）
target_link_libraries(PAL3_manual user32 gdi32)

# 编译选项（MSVC 6.0）
target_compile_options(PAL3_manual PRIVATE /W3 /GX)
