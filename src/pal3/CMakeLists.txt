# src/pal3/CMakeLists.txt
# PAL3.exe 子项目构建配置
#
# 此文件定义 PAL3.exe 可执行文件的编译方式。
# 源文件会随着反编译项目的进展逐步添加。

cmake_minimum_required(VERSION 3.10)

message(STATUS "Configuring PAL3.exe sub-project")

# Force dynamic runtime library (/MD) instead of static (/MT)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

# ========================================================================
# 查找依赖项
# ========================================================================

# DirectX SDK
if(NOT DirectX_FOUND)
    find_package(DirectX REQUIRED)
endif()

# ========================================================================
# 源文件列表
# ========================================================================
# 反编译源文件 — 随 BFS 调用图展开逐步添加。
# 每个文件独立编译为 .obj (通过 pal3_compare.py --compile-all 验证)。
# 注意: 完整链接不可行（缺外部符号），构建门控只验证编译。
#
# 维护规则: 新增 .cpp 文件时添加到此列表。

set(PAL3_SOURCES
    WinMain.cpp
    gamebase/PAL3.cpp
    gamebase/GRPinput.cpp
    gamebase/ScreenMode.cpp
    effect/RenderTarget.cpp
    Combat/CBSystem.cpp
    Combat/CBStage.cpp
    globals.cpp
)

# ========================================================================
# 头文件列表
# ========================================================================

set(PAL3_HEADERS
    ${CMAKE_SOURCE_DIR}/include/pal3.h
    ${CMAKE_SOURCE_DIR}/include/pal3_config.h
    ${CMAKE_SOURCE_DIR}/include/pal3_types.h
    ${CMAKE_SOURCE_DIR}/include/pal3_structs.h
    ${CMAKE_SOURCE_DIR}/include/pal3_globals.h
)

# ========================================================================
# 创建可执行文件
# ========================================================================

add_executable(PAL3 WIN32
    ${PAL3_SOURCES}
    ${PAL3_HEADERS}
)

# ========================================================================
# 设置目标属性
# ========================================================================

set_target_properties(PAL3 PROPERTIES
    OUTPUT_NAME "PAL3"
    SUFFIX ".exe"
    # 为 Visual Studio 调试设置
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# ========================================================================
# 包含目录
# ========================================================================

target_include_directories(PAL3 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${DirectX_INCLUDE_DIR}
)

# ========================================================================
# 链接依赖项
# ========================================================================

# DirectX 库
target_link_libraries(PAL3 PRIVATE
    ${DirectX_LIBRARIES}
)

# 已编译的 DLL 导入库（如果存在）
# 这些会在 Task 5 中生成
if(EXISTS "${CMAKE_SOURCE_DIR}/lib/gbengine.lib")
    target_link_libraries(PAL3 PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/gbengine.lib
    )
    message(STATUS "Linking against gbengine.lib")
else()
    message(WARNING "gbengine.lib not found. Will be created in Task 5.")
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/lib/topo.lib")
    target_link_libraries(PAL3 PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/topo.lib
    )
    message(STATUS "Linking against topo.lib")
else()
    message(WARNING "topo.lib not found. Will be created in Task 5.")
endif()

# Windows 系统库
target_link_libraries(PAL3 PRIVATE
    kernel32            # Windows 内核
    user32              # Windows 用户界面
    gdi32               # Graphics Device Interface
    winspool            # 打印支持
    comdlg32            # 公共对话框
    advapi32            # Advanced Services
    shell32             # Shell 支持
    ole32               # OLE
    oleaut32            # OLE Automation
    uuid                # UUID 库
    odbc32              # ODBC
    odbccp32            # ODBC 管理员
    winmm               # Multimedia（音频/视频）
)

# ========================================================================
# 编译选项
# ========================================================================

# 链接器标志 - 必须设置 /SUBSYSTEM:WINDOWS 用于 WinMain 入口点
if(MSVC)
    target_link_options(PAL3 PRIVATE
        /SUBSYSTEM:WINDOWS
        /INCREMENTAL:NO
        /OPT:REF
        /OPT:ICF
    )

    # 告知 VS 不要查找 main 符号
    set_target_properties(PAL3 PROPERTIES VS_GLOBAL_DesktopApplicationBinaryFormat "true")

    # 生成汇编清单用于比较
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/asm)
    target_compile_options(PAL3 PRIVATE /FAcs /Fa${CMAKE_BINARY_DIR}/asm/)
endif()

# ========================================================================
# 安装规则
# ========================================================================

install(TARGETS PAL3
    RUNTIME DESTINATION bin
)

message(STATUS "PAL3.exe target configured successfully")
