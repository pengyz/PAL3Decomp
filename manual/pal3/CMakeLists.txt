# manual/pal3 CMakeLists (out-of-tree build - CMake toolchain VC6)
# Build: cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=toolchain-windows-vc6.cmake .
#        ninja -C build
cmake_minimum_required(VERSION 3.10)
project(PAL3_manual CXX)

# gbengine (DLL import - lib+header)
set(GBENGINE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../gbengine")
set(GBENGINE_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/../../include")

# Manual rewrite domain (manual/pal3) - independent of codegen
add_executable(PAL3_manual
    platform/windows/WinMain.cpp
    mock/mock_interfaces.cpp
    core/GameBase/PAL3.cpp
    core/CUtil.cpp
)

# Link (gbengine+Windows libs)
target_link_libraries(PAL3_manual
    ${GBENGINE_DIR}/gbengine.lib
    user32 gdi32 winmm
)

# Include paths
target_include_directories(PAL3_manual PRIVATE ${GBENGINE_INCLUDE} ${GBENGINE_INCLUDE}/gbengine)

# Compile options (MSVC 6.0 - match original)
target_compile_options(PAL3_manual PRIVATE /W3 /GX /O2 /Ob2 /Oi /Ot /Oy)
