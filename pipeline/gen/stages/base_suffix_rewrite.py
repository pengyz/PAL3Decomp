# -*- coding: utf-8 -*-
"""基类名后缀访问等价重写（批 E 族 1）——纯函数，R15 单测驱动。

病灶（R16 三问）：Hex-Rays 按 IDA 成员名渲染基类子对象为 `x.Base`/`x->Base`；
消费者=MSVC6（Base 系基类名 ⇒ C2273/C2274 全量 106 点位同形——33c45090 逐点实证）；
修法层=codegen 等价重写（非注解：改继承回内嵌=红线禁止的破坏性 workaround）。

规则作用域（N5 收窄）：Base ∈ 已知基类名 **且后随非 `:`**（`x.Base::member` 限定形、
标签形、同名非基类成员一律不动）。
⚠️ **等价性前提（d0643565）**：①`recv->Base`（`->` 分隔）若 recv 是**真指针**，
`&recv` 是指针变量自身地址 ≠ `*(T*)recv`——指针接收者形**不等价**（回退态故无运行时影响，
重接线前须分派指针/内嵌接收者）；②隐含 **Base 子对象在 recv 偏移 0**（首基类/单继承）前提
——非首基类/虚继承时不成立，实现与测试均无守卫。
语义形：
  整拷贝 `*(T *)lhs = recv.Base`（LHS cast 类型==Base 名）→ `*(T *)lhs = *(T *)&recv`
  读/写/虚表调用值形                              → `*(_DWORD *)&recv`
"""
import re


def rewrite_base_suffix(text, base_names):
    """把 `recv.Base`/`recv->Base`（Base∈base_names 且非 `::` 跟随）等价重写。"""
    if not base_names:
        return text
    names = sorted(base_names, key=len, reverse=True)
    alt = '|'.join(re.escape(n) for n in names)
    # 整拷贝形：*(<T>*)<lhs> = <recv><.-><T>  （T==Base 名==LHS cast 类型）
    copy_re = re.compile(
        r'(?P<lhs>\*\s*\(\s*(?P<T>' + alt + r')\s*\*[^=]*?)\s*=\s*'
        r'(?P<recv>[\w\->.\[\]]+?)\s*(?:\.|->)\s*(?P=T)\b(?!\s*:)')
    text = copy_re.sub(lambda m: '%s= (*(%s *)&%s)' % (m.group('lhs'), m.group('T'),
                                                       m.group('recv')), text)
    # 值形（读/写/调用虚表）：recv<.-><Base> → (*(_DWORD *)&recv)（括号必须——链/调用/取址
    # 上下文的优先级保护：实测无括号 C2102 +220/C2064 +17 洪泛，2026-09-28 链验）。
    # 成员链上下文（后随 `.`/`->`）用基类**型**形（(*(T*)&recv).m_x 才有成员面——
    # _DWORD 形断链报 C2228/C2109，2026-09-28 RoleAtt L58-60 实证）。
    val_re = re.compile(
        r'(?P<recv>[\w\->.\[\]]+?)\s*(?:\.|->)\s*(?P<base>' + alt + r')\b(?!\s*:)')

    def _val(m):
        end = m.end()
        typed = end < len(text) and text[end:end + 1] in '.>' and not (
            end + 1 < len(text) and text[end:end + 2] == '::')
        if end < len(text) and text[end:end + 2] == '->':
            typed = True
        elif end < len(text) and text[end] == '.':
            typed = True
        if typed:
            return '(*(%s *)&%s)' % (m.group('base'), m.group('recv'))
        return '(*(_DWORD *)&%s)' % m.group('recv')

    text = val_re.sub(_val, text)
    return text


def base_names_from_store(store=None):
    """从注解 store 取基类名全集（struct_bases 的 keys+values 并集）。"""
    if store is None:
        return set()
    out = set()
    for _cls, bases in (getattr(store, 'struct_bases', None) or {}).items():
        items = bases.keys() if isinstance(bases, dict) else (bases or [])
        for x in items:
            nm = (x.get('name') or '') if isinstance(x, dict) else (x or '')
            if nm:
                out.add(nm)
    return out


def apply_base_suffix_rewrite(code, store=None, base_names=None):
    """管线入口：基类后缀访问等价重写（批 E 族 1；R2 模拟 100 行/绿单元 0 波及）。"""
    names = base_names if base_names is not None else base_names_from_store(store)
    return rewrite_base_suffix(code, names)
