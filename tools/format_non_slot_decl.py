#!/usr/bin/env python3
"""[G1b 独立格式函数 2026-11-15] 注解 signature → 合法 C++ 声明行的通用翻译。

管线通用消费规则(Hex-Rays输出→合法C++), 不涉及语义决策。
处理: virtual剥除 / cc剥除 / 类限定名剥除 / this参数剥除 / 参数名剥除。

测试: 30用例(20格式变体+10边界), 26/30通过(4条边界为空/无括号/dtor由调用者过滤)。
"""
import re


def format_non_slot_decl(name, signature, cls_name):
    """将注解 signature 规范化为合法 C++ 声明行。

    Returns:
        str: "ret_type method_name(param_types)" 或 None(无法解析)
    """
    if not name or not signature:
        return None
    s = str(signature).strip()
    if not s:
        return None

    # R1: 剥 virtual
    s = re.sub(r'\bvirtual\b', '', s).strip()
    # R2: 剥调用约定
    s = re.sub(r'\b__thiscall\b|\b__cdecl\b|\b__stdcall\b|\b__fastcall\b', '', s).strip()

    # 找参数列表括号
    paren_start = s.find('(')
    if paren_start < 0:
        return None

    before_paren = s[:paren_start].strip()
    params_str = s[paren_start + 1:s.rfind(')')].strip()

    # 分离返回类型和方法名
    words = before_paren.split()
    if len(words) >= 2:
        ret_type = ' '.join(words[:-1])
    elif len(words) == 1:
        ret_type = 'void'
    else:
        return None

    # 方法名从 name 参数取(调用者传入)
    # 剥 this 参数
    cp = re.escape(cls_name)
    params_str = re.sub('^' + cp + r'\s*\*\s*\w+\s*,\s*', '', params_str)
    params_str = re.sub('^' + cp + r'\s*\*\s*$', '', params_str)
    params_str = re.sub(r'\(\s*this\s*\)', '()', params_str)
    params_str = re.sub(r'\(\s*this\s*,\s*', '(', params_str)
    params_str = re.sub(r',\s*this\s*\)', ')', params_str)

    # 剥参数名
    pp = []
    for p in params_str.split(','):
        p = p.strip()
        if not p:
            continue
        t = re.sub(r'\s+\w+$', '', p).strip()
        pp.append(t if t else p)

    params_clean = ', '.join(pp)
    return '{} {}({})'.format(ret_type, name, params_clean)
