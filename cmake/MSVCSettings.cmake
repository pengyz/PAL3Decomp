# cmake/MSVCSettings.cmake
# MSVC 编译器设置 - 匹配原版 PAL3 编译选项
#
# 此文件由根 CMakeLists.txt 包含，为所有目标设置特定于 MSVC 的编译标志。
# 标志从 Rich Header 分析和二进制逆向工程中获取。

if(NOT MSVC)
    message(STATUS "MSVCSettings.cmake: Skipping - not building with MSVC")
    return()
endif()

message(STATUS "Configuring MSVC compiler settings")

# ========================================================================
# 清除默认的 CMake 生成的标志
# ========================================================================
# 我们需要精确控制编译器标志以实现字节匹配，因此清除 CMake 的默认值。

string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REGEX REPLACE "/W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

# ========================================================================
# PAL3 通用编译标志
# ========================================================================
# 这些标志应用于 topo.dll、gbengine.dll 和 PAL3.exe

if(MSVC_VERSION EQUAL 1200)
    # VC6: minimal common flags (no /GS, /Zc: etc.)
    set(PAL3_COMMON_COMPILE_FLAGS
        /nologo
        /W3
        /Gd
    )
else()
    # VC7+: modern flags
    set(PAL3_COMMON_COMPILE_FLAGS
        /nologo
        /W3
        /GS-
        /Gd
        /Zc:wchar_t
    )
endif()

# 为所有配置应用通用标志
add_compile_options(${PAL3_COMMON_COMPILE_FLAGS})

# ========================================================================
# topo.dll / gbengine.dll 标志 (VC6 风格)
# ========================================================================

if(MSVC_VERSION EQUAL 1200)
    # VC6: only flags it understands
    # Note: /FD omitted — causes PDB lock conflicts with parallel builds under Wine
    set(TOPO_GBENGINE_COMPILE_FLAGS
        /GX /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /MD
    )
else()
    set(TOPO_GBENGINE_COMPILE_FLAGS
        /GX                  # C++ 异常处理（VC6 风格）/EHsc 的别名
        /O2                  # 最大速度优化
        /Ob2                 # 自动内联任何合适的函数
        /Oi                  # 启用内部函数优化
        /Ot                  # 优先代码速度而不是大小
        /Oy                  # 省略帧指针
        /GF                  # 启用字符串池
        /Gy                  # 启用函数级链接
        /FD                  # 生成完整程序数据库信息
        /MD                  # 多线程 DLL 运行时库
        /Zc:sizedDealloc-    # 禁用 C++14 sized deallocation（VC6 不支持）
        /arch:IA32           # 强制 x87 FPU（避免 SSE 内部函数）
    )
endif()

# ========================================================================
# PAL3.exe 标志 (VC7 风格)
# ========================================================================

set(PAL3_COMPILE_FLAGS
    /EHsc                # C++ 异常处理（VC7 风格）
    /GR                  # 启用 RTTI（运行时类型信息）
    /O2                  # 最大速度优化
    /Ob2                 # 内联函数展开（任何合适的）
    /Oi                  # 启用内部函数优化
    /Ot                  # 优先代码速度而不是大小
    /Oy                  # 省略帧指针
    /GF                  # 启用字符串池
    /Gy                  # 启用函数级链接
    /FD                  # 生成完整程序数据库信息
    /MD                  # 多线程 DLL 运行时库
    /arch:IA32           # 强制 x87 FPU 代码生成（匹配原版 MSVC 7.1 输出）
)

# ========================================================================
# 定义与原版匹配的预处理器符号
# ========================================================================

set(PAL3_DEFINES
    NDEBUG              # Release 模式
    WIN32               # Windows 平台
    _WINDOWS            # Windows 应用程序
    _MBCS               # 多字节字符集
    _CRT_SECURE_NO_WARNINGS  # 原版代码使用标准 C 函数
)

# ========================================================================
# Release 配置特定标志
# ========================================================================

set(CMAKE_C_FLAGS_RELEASE "/DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_CRT_SECURE_NO_WARNINGS")
set(CMAKE_CXX_FLAGS_RELEASE "/DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_CRT_SECURE_NO_WARNINGS")

# ========================================================================
# Debug 配置特定标志（用于开发/测试）
# ========================================================================

set(CMAKE_C_FLAGS_DEBUG "/Od /Zi /DDEBUG /DWIN32 /D_WINDOWS")
set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /DDEBUG /DWIN32 /D_WINDOWS")

# ========================================================================
# 链接器标志
# ========================================================================

set(PAL3_COMMON_LINK_FLAGS
    /NOLOGO              # 不显示链接器横幅
    /MACHINE:X86         # 目标机器：x86
    /SUBSYSTEM:WINDOWS   # Windows 应用程序
)

# 仅 PAL3.exe 特定
set(PAL3_EXE_LINK_FLAGS
    /INCREMENTAL:NO      # 禁用增量链接
    /OPT:REF             # 移除未引用的函数
    /OPT:ICF             # 合并相同的函数/数据
)

# ========================================================================
# 导出给调用端的变量
# ========================================================================
# CMakeLists.txt 可以引用这些变量来为特定目标设置标志

set(PAL3_TOPO_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
set(PAL3_TOPO_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
set(PAL3_GBENGINE_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
set(PAL3_GBENGINE_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
set(PAL3_EXE_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
set(PAL3_EXE_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

message(STATUS "MSVC settings configured successfully")
