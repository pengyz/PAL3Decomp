# PAL3.exe source files (auto-generated from IDA decomp)
# CONFIGURE_DEPENDS: re-glob on every build, detect added/removed files automatically
file(GLOB_RECURSE PAL3_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable(PAL3 ${PAL3_SOURCES})
target_include_directories(PAL3 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_compile_options(PAL3 PRIVATE /W0)

# Link gbengine target (must be built as dependency)
target_link_libraries(PAL3 PRIVATE gbengine)

target_link_libraries(PAL3 PRIVATE
    kernel32.lib user32.lib gdi32.lib winmm.lib ole32.lib
)
