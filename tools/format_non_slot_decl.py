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
    name = str(name).strip()
    s = str(signature).strip()
    if not name or not s:
        return None

    # R0: dtor/ctor 非法声明形态(无返回类型语义) → 专用路径发射, 此处拒绝 [事故钉死#3]
    if name.startswith('~') or name == cls_name:
        return None
    # R0b: 编译器生成名(`scalar deleting destructor'/`vcall'x'/`adjustor{n}')含反引号,
    #       源码层声明非法(C2018) → 拒绝(槽0 dtor 专用路径发射) [事故钉死#4]
    if '`' in name:
        return None
    # R0c: dtor 族分析名(_scalar_dtor_XXXX/_sdtor_*/scalar_deleting)走 dtor 槽规则,
    #       非普通方法声明 [事故钉死#5:C2535族]
    if re.match(r'^(~|_sdtor_|_scalar_dtor|.*scalar_deleting)', name):
        return None

    # R1: 剥 virtual
    s = re.sub(r'\bvirtual\b', '', s).strip()
    # R2: 剥调用约定
    s = re.sub(r'\b__thiscall\b|\b__cdecl\b|\b__stdcall\b|\b__fastcall\b', '', s).strip()
    # R2b: 剥自有类限定名(类体内合法且更净; 他类限定名保留——盲剥会破坏可见性) [事故钉死#1]
    if cls_name:
        s = re.sub(r'\b' + re.escape(str(cls_name)) + r'::', '', s)

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
    # 剥 this 参数(泛化: 任意 X *this 首参——条目可能从他类上下文拷贝, this 类型不必等于 cls)
    cp = re.escape(str(cls_name)) if cls_name else ''
    if cp:
        params_str = re.sub('^' + cp + r'\s*\*\s*\w+\s*,\s*', '', params_str)
        params_str = re.sub('^' + cp + r'\s*\*\s*\w+\s*$', '', params_str)  # 单参有名this [事故钉死#2]
        params_str = re.sub('^' + cp + r'\s*\*\s*$', '', params_str)
    params_str = re.sub(r'^[\w:]+[\s\*&]+this\s*,\s*', '', params_str)   # 泛化有名this [事故钉死#6:UIScene *this]
    params_str = re.sub(r'^[\w:]+[\s\*&]+this\s*$', '', params_str)
    params_str = re.sub(r'\(\s*this\s*\)', '()', params_str)
    params_str = re.sub(r'\(\s*this\s*,\s*', '(', params_str)
    params_str = re.sub(r',\s*this\s*\)', ')', params_str)
    params_str = re.sub(r'^this$', '', params_str)  # 裸this独参

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
