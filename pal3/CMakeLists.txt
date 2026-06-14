# PAL3.exe — 游戏逻辑 (depends on gbengine)
# .h 和 .cpp 在同一目录下，通过 target_include_directories 互相解析

file(GLOB_RECURSE PAL3_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(PAL3 ${PAL3_SOURCES})
target_include_directories(PAL3 PRIVATE
    src                           # 让 #include "Combat/CCBAI.h" 能解析
    ${CMAKE_SOURCE_DIR}/include   # 共享头文件: gbengine/, pal3_types.h 等
)
target_compile_options(PAL3 PRIVATE /W0)

# Link gbengine target (must be built as dependency)
target_link_libraries(PAL3 PRIVATE gbengine)

target_link_libraries(PAL3 PRIVATE
    kernel32.lib user32.lib gdi32.lib winmm.lib ole32.lib
)
