# cmake/FindDirectX.cmake
# 查找 DirectX SDK
#
# 此模块尝试查找 DirectX SDK（首选夏季 2003 版本）并设置以下变量：
#
#  DirectX_FOUND          - 如果找到 DirectX SDK
#  DirectX_ROOT_DIR       - DirectX SDK 根目录
#  DirectX_INCLUDE_DIR    - Include 目录
#  DirectX_LIBRARIES      - 所有 DirectX 库的列表
#  DirectX_D3D9_LIBRARY   - Direct3D 9 库
#  DirectX_D3DX9_LIBRARY  - D3DX9 库
#  DirectX_DINPUT8_LIBRARY - DirectInput 8 库
#  DirectX_DSOUND_LIBRARY  - DirectSound 库
#
# 查找优先级：
#  1. DXSDK_DIR 环境变量
#  2. 标准安装位置（C:/DXSDK、Program Files）
#  3. Windows SDK 附带的 DirectX

set(DirectX_FOUND FALSE)

# ========================================================================
# 查找 DirectX SDK 根目录
# ========================================================================

# 首先检查 DXSDK_DIR 环境变量
if(DEFINED ENV{DXSDK_DIR})
    set(DirectX_ROOT_DIR "$ENV{DXSDK_DIR}")
    message(STATUS "DirectX SDK found via DXSDK_DIR: ${DirectX_ROOT_DIR}")
else()
    # 检查常见安装位置
    if(EXISTS "C:/DXSDK")
        set(DirectX_ROOT_DIR "C:/DXSDK")
        message(STATUS "DirectX SDK found at: ${DirectX_ROOT_DIR}")
    elseif(EXISTS "D:/DXSDK")
        set(DirectX_ROOT_DIR "D:/DXSDK")
        message(STATUS "DirectX SDK found at: ${DirectX_ROOT_DIR}")
    elseif(EXISTS "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")
        set(DirectX_ROOT_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")
        message(WARNING "Found DirectX SDK June 2010, but PAL3 uses Summer 2003. May cause incompatibilities.")
    elseif(EXISTS "C:/Program Files (x86)/Microsoft DirectX SDK (August 2007)")
        set(DirectX_ROOT_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (August 2007)")
        message(WARNING "Found DirectX SDK August 2007, but PAL3 uses Summer 2003. May cause incompatibilities.")
    else()
        message(WARNING "DirectX SDK not found in standard locations.")
        message(WARNING "Please set DXSDK_DIR environment variable or manually specify DirectX_ROOT_DIR")
        return()
    endif()
endif()

# ========================================================================
# 查找 Include 目录
# ========================================================================

find_path(DirectX_INCLUDE_DIR
    NAMES d3d9.h
    PATHS "${DirectX_ROOT_DIR}/Include"
    NO_DEFAULT_PATH
)

if(NOT DirectX_INCLUDE_DIR)
    message(WARNING "DirectX Include directory not found in: ${DirectX_ROOT_DIR}/Include")
    return()
endif()

# ========================================================================
# 查找 D3D9 库
# ========================================================================

find_library(DirectX_D3D9_LIBRARY
    NAMES d3d9
    PATHS "${DirectX_ROOT_DIR}/Lib/x86"
    NO_DEFAULT_PATH
)

if(NOT DirectX_D3D9_LIBRARY)
    message(WARNING "d3d9.lib not found in: ${DirectX_ROOT_DIR}/Lib/x86")
endif()

# ========================================================================
# 查找 D3DX9 库
# ========================================================================

find_library(DirectX_D3DX9_LIBRARY
    NAMES d3dx9
    PATHS "${DirectX_ROOT_DIR}/Lib/x86"
    NO_DEFAULT_PATH
)

if(NOT DirectX_D3DX9_LIBRARY)
    message(WARNING "d3dx9.lib not found in: ${DirectX_ROOT_DIR}/Lib/x86")
    # D3DX9 是可选的，某些程序可能不使用它
endif()

# ========================================================================
# 查找 DirectInput8 库
# ========================================================================

find_library(DirectX_DINPUT8_LIBRARY
    NAMES dinput8
    PATHS "${DirectX_ROOT_DIR}/Lib/x86"
    NO_DEFAULT_PATH
)

if(NOT DirectX_DINPUT8_LIBRARY)
    message(WARNING "dinput8.lib not found in: ${DirectX_ROOT_DIR}/Lib/x86")
endif()

# ========================================================================
# 查找 DirectSound 库
# ========================================================================

find_library(DirectX_DSOUND_LIBRARY
    NAMES dsound
    PATHS "${DirectX_ROOT_DIR}/Lib/x86"
    NO_DEFAULT_PATH
)

if(NOT DirectX_DSOUND_LIBRARY)
    message(WARNING "dsound.lib not found in: ${DirectX_ROOT_DIR}/Lib/x86")
endif()

# ========================================================================
# 构建库列表
# ========================================================================

set(DirectX_LIBRARIES)
if(DirectX_D3D9_LIBRARY)
    list(APPEND DirectX_LIBRARIES ${DirectX_D3D9_LIBRARY})
endif()
if(DirectX_D3DX9_LIBRARY)
    list(APPEND DirectX_LIBRARIES ${DirectX_D3DX9_LIBRARY})
endif()
if(DirectX_DINPUT8_LIBRARY)
    list(APPEND DirectX_LIBRARIES ${DirectX_DINPUT8_LIBRARY})
endif()
if(DirectX_DSOUND_LIBRARY)
    list(APPEND DirectX_LIBRARIES ${DirectX_DSOUND_LIBRARY})
endif()

# ========================================================================
# 标准查找包处理
# ========================================================================

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(DirectX
    REQUIRED_VARS DirectX_INCLUDE_DIR DirectX_D3D9_LIBRARY
    VERSION_VAR "9.0"
)

if(DirectX_FOUND)
    message(STATUS "DirectX SDK found successfully")
    message(STATUS "  Root: ${DirectX_ROOT_DIR}")
    message(STATUS "  Include: ${DirectX_INCLUDE_DIR}")
    message(STATUS "  Libraries: ${DirectX_LIBRARIES}")
else()
    message(FATAL_ERROR "DirectX SDK not found. Aborting.")
endif()

# ========================================================================
# 标记为高级
# ========================================================================

mark_as_advanced(
    DirectX_INCLUDE_DIR
    DirectX_D3D9_LIBRARY
    DirectX_D3DX9_LIBRARY
    DirectX_DINPUT8_LIBRARY
    DirectX_DSOUND_LIBRARY
    DirectX_ROOT_DIR
)
