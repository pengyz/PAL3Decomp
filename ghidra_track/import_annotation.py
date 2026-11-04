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


_DECIMAL_KEY = re.compile(r'[0-9]+')


def parse_variant_key(key):
    """known_members 键 → 偏移 int（仅十进制纯数字形）| 原样键 str（变体/异形）。

    键谱系 `base_offset[_variant]`（check_annotations.py:607 同款语义）：'144_1'
    = 偏移 144 的第 1 位面视图（同存储 alias），**不是**独立偏移。PEP 515 下划线
    数字分隔符语义下 int('144_1')==1441 / int('50814_0')==508140 / int('0_1')==1
    —— int() 直吞即发明偏移（病灶=本模块旧 `int(k)`，语料 PalScript.json '144_1'）。
    契约（task-1 Step 3）：十进制纯数字形才 int()；含 '_'/非数字（hex 等）原样返回，
    由下游显式处理——禁发明偏移、禁 lstrip('0x') 前导零陷阱（'0x0abc' 会丢 '0'）。
    """
    if isinstance(key, int):
        return key  # list 形 known_members 的 int 键直通
    s = str(key)
    return int(s) if _DECIMAL_KEY.fullmatch(s) else s


def merge_method_claims(ann):
    """{文件名: structdata} → {addr: claim} 归并（确定性纯函数·与插入序无关）。
    tie-break（对齐 apply_annotations.py:1382-1385 语义、代码独立）：
    owner(==本 struct name) 优先 > adjudication=='confirmed' > sorted 文件名序 > 首个。"""
    out = {}
    for fname in sorted(ann.keys()):
        d = ann[fname] or {}
        cls = d.get('name')
        for addr, m in (d.get('methods') or {}).items():
            if not isinstance(m, dict) or not m.get('name'):
                continue
            claim = dict(m)
            claim['class'] = cls
            prev = out.get(addr)
            if prev is None:
                out[addr] = claim
                continue
            # owner 赢（claim 自 owner==自类 且 prev 无同形 owner）
            if claim.get('owner') == cls and prev.get('owner') != prev.get('class'):
                out[addr] = claim
            # confirmed 赢（prev 非 confirmed）
            elif claim.get('adjudication') == 'confirmed' and prev.get('adjudication') != 'confirmed':
                out[addr] = claim
            # 其余保持 prev（sorted 文件名序=平局首个）
    return out


def load_ann_dir(ann_dir, only=None):
    """annotation 目录 → (functions, structs, globals)。sorted glob+merge_method_claims
    （确定性：文件系统序不得进入结果——test_ann_dir_glob_order_independent 钉）。"""
    import glob as _glob
    import json as _json
    import os as _os
    funcs = {}
    fp = _os.path.join(ann_dir, 'functions.json')
    if _os.path.exists(fp):
        funcs.update(_json.load(open(fp)))
    structs = {}
    ann_map = {}
    for f in sorted(_glob.glob(_os.path.join(ann_dir, 'structs', '*.json'))):
        d = _json.load(open(f))
        n = d.get('name')
        if not n or (only and n not in only):
            continue
        structs[n] = d
        ann_map[_os.path.basename(f)] = d
    for addr, m in merge_method_claims(ann_map).items():
        funcs[addr] = {'name': m['name'], 'signature': m.get('signature') or '',
                       'class': m.get('class')}
    g = {}
    gp = _os.path.join(ann_dir, 'globals.json')
    if _os.path.exists(gp):
        g = _json.load(open(gp))
    return funcs, structs, g


def build_import_plan(functions=None, structs=None, globals=None):
    # 目录形入口（brief 契约）：build_import_plan(ann_dir) → 走 load_ann_dir
    if isinstance(functions, str):
        functions, structs, globals = load_ann_dir(functions)
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
                off = parse_variant_key(k)
                if not isinstance(off, int):
                    # 变体键（'144_1'）/异形键（hex 等）不是偏移：显式排除——存储偏移
                    # 归基键（'144'→144）落位；禁 int() 吞发明偏移（144_1→1441 实锤）。
                    # 变体视图形补（union 折叠）= Task 7/8 missing-shapes 面。
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
