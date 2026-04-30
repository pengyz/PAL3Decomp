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
# 按照开发阶段组织源文件：
#   Phase 0 (基础设施): 占位符 main.cpp
#   Phase 1 (框架): 窗口初始化、游戏循环、DirectX 设置
#   Phase 2 (脚本): SCE VM 实现
#   Phase 3 (UI): 菜单、对话、HUD
#   Phase 4 (战斗): 战斗管理、技能系统
#   Phase 5 (场景): 场景管理、相机
#   Phase 6 (存档): 保存/加载系统
#   Phase 7 (其他): 音频、物品、NPC

set(PAL3_SOURCES
    # Phase 0: 占位符
    main.cpp
)

# ========================================================================
# 未来的源文件（按阶段注释）
# ========================================================================
#
# # Phase 1: 框架
# set(PAL3_PHASE1_SOURCES
#     framework/window.cpp
#     framework/init.cpp
#     framework/game_loop.cpp
#     framework/render.cpp
# )
#
# # Phase 2: 脚本系统
# set(PAL3_PHASE2_SOURCES
#     script/sce_vm.cpp
#     script/sce_opcodes.cpp
#     script/sce_stack.cpp
# )
#
# # Phase 3: UI 系统
# set(PAL3_PHASE3_SOURCES
#     ui/ui_manager.cpp
#     ui/menu_main.cpp
#     ui/dialog.cpp
#     ui/hud.cpp
# )
#
# # Phase 4: 战斗系统
# set(PAL3_PHASE4_SOURCES
#     battle/battle_manager.cpp
#     battle/skill_system.cpp
#     battle/unit.cpp
# )
#
# # Phase 5: 场景管理
# set(PAL3_PHASE5_SOURCES
#     scene/scene_manager.cpp
#     scene/camera.cpp
#     scene/object.cpp
# )
#
# # Phase 6: 存档系统
# set(PAL3_PHASE6_SOURCES
#     save/save_manager.cpp
#     save/save_format.cpp
# )
#
# # Phase 7: 其他系统
# set(PAL3_PHASE7_SOURCES
#     audio/audio_manager.cpp
#     item/item_manager.cpp
#     npc/npc_manager.cpp
# )

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

# 由于 PAL3.exe 使用 VC7.0，我们需要一些特定的标志
if(MSVC)
    # 添加 PAL3.exe 特定的标志
    target_compile_options(PAL3 PRIVATE
        /EHsc               # C++ 异常处理（VC7 风格）
        /GR                 # RTTI
        /O2                 # 最大速度优化
        /Ob2                # 内联
        /Oi                 # 内部函数
        /Ot                 # 优先速度
        /Oy                 # 省略帧指针
        /GF                 # 字符串池
        /Gy                 # 函数级链接
        /FD                 # 完整程序数据库
        /MD                 # 多线程 DLL 运行时
    )

    # 链接器标志 - 必须设置 /SUBSYSTEM:WINDOWS 用于 WinMain 入口点
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
