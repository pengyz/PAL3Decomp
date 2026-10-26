# manual/pal3 可编译基（CMakeLists——MSVC 6.0·gbengine 链接）
# 迁移：WinMain+mock+PAL3_init+gbengine.dll 导入
# gbengine：gbengine.lib（def→lib）+include/gbengine/*.h
# 编译（Windows 直编）：
#   cl /c ... (sources) -> link ... gbengine.lib user32.lib gdi32.lib
cmake_minimum_required(VERSION 3.10)
project(PAL3_manual CXX)

# gbengine（DLL 导入——lib+header）
set(GBENGINE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../gbengine")
set(GBENGINE_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/../../include")

# 手动改写域（manual/pal3）——独立 codegen
add_executable(PAL3_manual
    platform/windows/WinMain.cpp
    mock/mock_interfaces.cpp
    core/PAL3_init.cpp
)

# 链接（gbengine+Windows 库）
target_link_libraries(PAL3_manual
    ${GBENGINE_DIR}/gbengine.lib
    user32 gdi32 winmm dinput8
)

# include 路径（gbengine header）
target_include_directories(PAL3_manual PRIVATE ${GBENGINE_INCLUDE} ${GBENGINE_INCLUDE}/gbengine)

# 编译选项（MSVC 6.0——匹配原版）
target_compile_options(PAL3_manual PRIVATE /W3 /GX /O2 /Ob2 /Oi /Ot /Oy)
