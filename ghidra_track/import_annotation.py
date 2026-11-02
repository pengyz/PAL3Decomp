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
                ty = m.get('type')
                if isinstance(ty, dict) and 'union' in ty:
                    # inline-union → define_union op + 成员引用 union 型名（禁字节桩）
                    uname = 'UNION_%s_%d' % (cls, off)
                    umems = [{'name': v.get('name') or 'u%d' % i, 'type': v.get('type') or 'int'}
                             for i, v in enumerate(ty['union']) if isinstance(v, dict)]
                    plan.append({'kind': 'define_union', 'name': uname, 'members': umems})
                    members.append({'offset': off, 'name': m['name'], 'type': uname})
                else:
                    members.append({'offset': off, 'name': m['name'],
                                    'type': ty if isinstance(ty, str) else (ty or 'undefined')})
        plan.append({'kind': 'define_struct', 'name': cls,
                     'size': d.get('size') or d.get('binary_size'),
                     'members': sorted(members, key=lambda x: x['offset'])})
    for addr, info in sorted(globals.items()):
        if not isinstance(info, dict) or not info.get('name'):
            continue
        plan.append({'kind': 'define_global', 'addr': addr,
                     'name': info['name'], 'type': info.get('type') or 'undefined'})
    return plan


def partition_struct_passes(plan):
    """两遍建分区：pass1=全部空壳（name,size，前向引用可用）；pass2=成员填充。"""
    p1, p2 = [], []
    for op in plan:
        if op.get('kind') == 'define_struct':
            p1.append({'name': op['name'], 'size': op.get('size')})
            p2.append({'name': op['name'], 'members': op.get('members') or []})
    return p1, p2


def ghidra_sig_params(sig):
    """签名参数形（Ghidra ParameterDefinition 预览）：thiscall 注入隐藏 this 首参。"""
    params = []
    if sig.get('cls') and sig.get('conv') == '__thiscall':
        params.append(('this', '%s *' % sig['cls']))
    for p in sig.get('params') or []:
        params.append(('', p))
    return params


def reconcile_sizes(declared, observed):
    """sizeof 对账（导入即校验）：注解 size vs 库内实际——差异=布局钉。"""
    return {k: (v, observed[k]) for k, v in declared.items()
            if k in observed and observed[k] != v}
