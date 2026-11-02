"""annotation_import 转换层（双轨 spec §4）——注解 JSON → Ghidra 导入计划。
纯函数层（计划=op 列表），apply 层后续经 ghidra-mcp/脚本执行。
铁律：载体诚实化 · 已 mangled 名直通禁重绞 · 占位名原样过。"""
import re

_MANGLED = re.compile(r'^\?')
# IDA 载体约定：__fastcall(int self)=thiscall 模拟（self=ecx 槽）
_CARRIER = re.compile(r'^(\w[\w:*&<> ]*?)\s+__fastcall\s*\(\s*int\s+self\s*(?:,\s*)?')


def honest_signature(sig, cls=None, name=None):
    """载体形诚实化：__fastcall(int self[, rest]) → __thiscall(cls*)，self 消隐。"""
    sig = (sig or '').strip()
    m = _CARRIER.match(sig)
    if m and cls:
        ret = m.group(1).strip()
        rest = sig[m.end() - (1 if sig[m.end() - 1:m.end()] == ')' else 0):] if False else sig[sig.find('(') + 1:sig.rfind(')')]
        # rest=参数串（self 已被正则吞）——重建
        params_str = sig[sig.find('(') + 1:sig.rfind(')')]
        params = [p.strip() for p in params_str.split(',') if p.strip() and p.strip() != 'int self']
        params = [re.sub(r'\s+\w+$', '', p).strip() for p in params]
        return {'conv': '__thiscall', 'ret': ret, 'params': params, 'cls': cls}
    paren = sig.find('(')
    if paren == -1:
        return {'conv': '__thiscall', 'ret': sig, 'params': [], 'cls': cls}
    head = sig[:paren].strip()
    conv = '__cdecl'
    for c in ('__thiscall', '__cdecl', '__stdcall', '__fastcall'):
        if c in head:
            conv = c
            break
    ret = head.replace(conv, '').strip()
    params_str = sig[paren + 1:sig.rfind(')')] if sig.rfind(')') > paren else ''
    params = [re.sub(r'\s+\w+$', '', p).strip() for p in params_str.split(',') if p.strip() and p.strip() != 'void']
    return {'conv': conv, 'ret': ret, 'params': params, 'cls': cls}


def build_import_plan(functions=None, structs=None, globals=None):
    """注解三源 → Ghidra 导入 op 列表（set_name/set_func_sig/define_struct/define_global）。"""
    functions = functions or {}
    structs = structs or {}
    globals = globals or {}
    plan = []
    for addr, info in sorted(functions.items()):
        if not isinstance(info, dict) or not info.get('name'):
            continue
        name = info['name']
        sig = honest_signature(info.get('signature') or '', cls=info.get('class'), name=name)
        plan.append({'kind': 'set_name', 'addr': addr, 'name': name})
        if sig['ret'] or sig['params']:
            plan.append({'kind': 'set_func_sig', 'addr': addr, 'name': name, **sig})
    for cls, d in sorted(structs.items()):
        km = (d or {}).get('known_members') or {}
        members = []
        pairs = km.items() if isinstance(km, dict) else [(m.get('offset'), m) for m in km if isinstance(m, dict)]
        for k, m in pairs:
            if isinstance(m, dict) and m.get('name') and k is not None:
                try:
                    off = int(k)
                except (TypeError, ValueError):
                    continue
                members.append({'offset': off, 'name': m['name'],
                                'type': m.get('type') or 'undefined'})
        plan.append({'kind': 'define_struct', 'name': cls,
                     'size': d.get('size') or d.get('binary_size'),
                     'members': sorted(members, key=lambda x: x['offset'])})
    for addr, info in sorted(globals.items()):
        if not isinstance(info, dict) or not info.get('name'):
            continue
        plan.append({'kind': 'define_global', 'addr': addr,
                     'name': info['name'], 'type': info.get('type') or 'undefined'})
    return plan
