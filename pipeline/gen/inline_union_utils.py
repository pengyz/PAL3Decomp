#!/usr/bin/env python3
"""inline union 工具函数（R15 生产纯函数）

**R15 制式**：新渲染/字符串逻辑先写纯函数单测
**本模块**：inline union 相关纯函数（生产代码，非测试代码）

三段分层：
1. apply_annotations 测写入（_build_udt 产出 TIL union）
2. export_full 测消解（合成名消解/具名传播）
3. codegen 测不生成（负向断言，不造信息）
"""
import re


def resolve_synthetic_name(synthetic_name, origin_field, named_name=None):
    """R15 纯函数：解析合成名 → 具名（从 _origin 字段）

    输入：
        synthetic_name: 合成名（如 _inline_SceneMgr_::$6537DBC7...）
        origin_field: annotation _origin 字段（如 "原合成名 _inline_SceneMgr_::$6537DBC7..."）
        named_name: 具名（如 tagPartyInitView）
    输出：
        (named_name, replaced): 具名 + 是否替换
        如果无具名，返回 (None, False)
    """
    if not origin_field:
        return None, False

    # 模式 1：原合成名 XXX（停止符集：空白/标点/结尾；支持双 $ 复合键）
    m = re.search(r'原合成名 ((?:_inline_\S+?|\S+?::\$\S+?))(?=[\s。；;，、）)]|$)', origin_field)
    if m:
        orig_name = m.group(1)
        if orig_name == synthetic_name and named_name:
            return named_name, True

    # 模式 2：lead 指定名 XXX
    m2 = re.search(r'lead 指定名 ([^\s）);；]+)', origin_field)
    if m2:
        lead_name = m2.group(1)
        if named_name and lead_name == named_name:
            return named_name, True

    return None, False


def check_pod_constraint(member_type):
    """R15 纯函数：POD 约束检查（C2620 防回归）

    输入：
        member_type: 成员类型（如 "PtrArray" 或 "int" 或 "int[100]" 或 "RoleSystem *" 或 "void (__cdecl *)(int)"）
    输出：
        True 如果是 POD 类型，False 如果非 POD
    """
    # 去除数组后缀（如 int[100] -> int）
    base_type = re.sub(r'\[.*\]', '', member_type).strip()

    # 指针类型是 POD（trivial）
    if base_type.endswith('*'):
        return True

    # 函数指针类型是 POD（trivial）（如 void (__cdecl *)(int)）
    if base_type.endswith(')') and '(' in base_type:
        return True

    # POD 类型（trivial）
    pod_types = {'int', 'float', 'double', 'char', 'short', 'long',
                 'unsigned int', 'unsigned char', 'unsigned short', 'unsigned long',
                 'BYTE', 'WORD', 'DWORD', 'UINT', 'BOOL', 'LONG', 'UINT32',
                 '__int8', '__int16', '__int32', '__int64',
                 'signed __int8', 'signed __int16', 'signed __int32', 'signed __int64',
                 'unsigned __int8', 'unsigned __int16', 'unsigned __int32', 'unsigned __int64'}
    return base_type in pod_types


def check_cross_tu_name(type_name):
    """R15 纯函数：跨 TU 裸名检查（C2228 防回归）

    输入：
        type_name: 类型名（如 _inline_tagCam_yaw 或 tagCam_yaw）
    输出：
        True 如果是合法标识符（可跨 TU 解析），False 否则
    """
    # 合法标识符：以字母或下划线开头，只含字母/数字/下划线
    return bool(re.match(r'^[A-Za-z_]\w*$', type_name))


def check_variant_key(offset_key):
    """R15 纯函数：variant 键双 repr 检查

    输入：
        offset_key: 偏移键（如 "50814_0" 或 "50814"）
    输出：
        True 如果是 variant 键（off_N 形），False 否则
    """
    return bool(re.match(r'^\d+_\d+$', offset_key))


def validate_member_for_union(member_type, member_name):
    """R15 纯函数：验证成员是否可入 union（apply 层行为断言）

    输入：
        member_type: 成员类型（如 "int" 或 "PtrArray"）
        member_name: 成员名（如 "m_nValue"）
    输出：
        (valid, reason): 是否有效 + 原因
    """
    # POD 约束检查
    if not check_pod_constraint(member_type):
        return False, f"Non-POD type '{member_type}' cannot be in union (C2620)"

    # 跨 TU 裸名检查
    if not check_cross_tu_name(member_name):
        return False, f"Invalid identifier '{member_name}' (C2228)"

    return True, "OK"


def compute_union_size(member_types):
    """R15 纯函数：计算 union 尺寸（apply 层行为断言）

    输入：
        member_types: 成员类型列表（如 ["int", "float"]）
    输出：
        union 尺寸（max of member sizes）
    """
    size_map = {
        'int': 4, 'float': 4, 'double': 8, 'char': 1, 'short': 2, 'long': 4,
        'unsigned int': 4, 'unsigned char': 1, 'unsigned short': 2, 'unsigned long': 4,
        'BYTE': 1, 'WORD': 2, 'DWORD': 4, 'UINT': 4, 'BOOL': 4
    }
    sizes = [size_map.get(re.sub(r'\[.*\]', '', t).strip(), 4) for t in member_types]
    return max(sizes) if sizes else 0
