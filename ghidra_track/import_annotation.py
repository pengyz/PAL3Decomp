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
            if m.get('adjudication') == 'rejected':
                continue   # [T7①] rejected 败者禁消费（25367 三连实锤缺口）
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


def build_import_plan(functions=None, structs=None, globals=None, enums=None):
    # 目录形入口（brief 契约）：build_import_plan(ann_dir) → 走 load_ann_dir
    if isinstance(functions, str):
        _ad = functions
        functions, structs, globals = load_ann_dir(_ad)
        if enums is None:
            import os as _os, json as _json
            _ep = _os.path.join(_ad, 'enums.json')
            if _os.path.exists(_ep):
                enums = _json.load(open(_ep))
    """注解三源 → Ghidra 导入 op 列表（set_name/set_func_sig/define_struct/define_global）。"""
    functions = functions or {}
    structs = structs or {}
    globals = globals or {}
    plan = []
    # define_enum 头插（2026-11-06 C 族：enums.json 68 枚举此前不进 plan——
    # 成员引用 ECB*/SCENE_TYPE 等全数 Unknown。先于 struct 建=创建序即依赖序）
    for _en in sorted((enums or {}).keys()):
        _evs = ((enums[_en] or {}).get('values')) or {}
        _ev = {}
        for _vk, _vv in _evs.items():
            try:
                _ev[_vk] = int(str(_vv), 0)
            except (ValueError, TypeError):
                _ev[_vk] = _vv   # 非整值原样透传→create_enum 契约层报错（禁静默吞）
        if _ev:
            plan.append({'kind': 'define_enum', 'name': _en, 'values': _ev})
    # 同名冲突消歧（2026-11-07 根修，204 组实证）：Ghidra 符号表允许多地址同名共存，
    # 但 C++ 名字空间无重载区分——三个 Load(0x44F610/0x47CB90/0x5062D0) 生成同一裸名
    # 调用点，C++ 重载解析歧义（C2059/C2660），且 sig 不同合法同名覆盖掉声明。
    # 规则：组内唯一名保留裸名；撞名组内有 class 的 → cls_name（与 vc6_nested_ns 的
    # 点号→下划线先例同构）；无 class 的 → name_0044F610（地址消歧——名字不承载
    # 语义主张，语义主张在 set_func_sig.cls；非伪语义命名）。
    # 两轮消歧：round1 cls_name / name_ADDR8；round2 对仍撞的（同 class 同名多址——
    # annotation 归属疑点族，账另记）加地址后缀。addr 归一小写计数（大小写变体
    # 00469EB0/00469eb0=同址重复 claim，禁误判为撞名）。
    _addr_norm = lambda a: a.lower()
    name_uses = {}
    _seen_addr = {}
    for _a, _i in functions.items():
        if isinstance(_i, dict) and _i.get('name') and _i.get('adjudication') != 'rejected' and not _i.get('skip'):
            name_uses.setdefault(_i['name'], []).append(_a)
            _seen_addr.setdefault(_addr_norm(_a), []).append(_a)
    for addr, info in sorted(functions.items()):
        if not isinstance(info, dict) or not info.get('name'):
            continue
        if info.get('adjudication') == 'rejected':
            continue   # [T7①] rejected 禁入 plan
        if info.get('skip'):
            continue   # [T7③] skip 语义消费（禁当正常 claim）
        name = info['name']
        if len(name_uses.get(name, ())) > 1:
            _cls = info.get('class')
            # addr 形 '0x0044F610'（或 16 位 '0x0000000000401308'）——[2:] 切片后取末 8 位
            # hex（lstrip('0x') 会吞前导零，parse_variant_key 同款陷阱；16 位形截出 16 位尾巴）
            name = ('%s_%s' % (_cls, name)) if _cls else ('%s_%s' % (name, addr[2:].upper()[-8:]))
        # round2: cls_name 仍撞（同 class 同名多址）→ 地址后缀终局消歧
        _final_uses = {}
        for _a, _i in functions.items():
            if not (isinstance(_i, dict) and _i.get('name') and _i.get('adjudication') != 'rejected' and not _i.get('skip')):
                continue
            _n = _i['name']
            if len(name_uses.get(_n, ())) > 1:
                _c = _i.get('class')
                _n = ('%s_%s' % (_c, _n)) if _c else ('%s_%s' % (_n, _a[2:]))
            _final_uses.setdefault(_n, []).append(_a)
        if len(_final_uses.get(name, ())) > 1:
            name = '%s_%s' % (name, addr[2:].upper()[-8:])
        sig = honest_signature(info.get('signature') or '', cls=info.get('class'), name=name)
        _op = {'kind': 'set_name', 'addr': addr, 'name': name}
        if info.get('owner'):
            _op['owner'] = info['owner']   # [T7⑤] owner 维入 plan（归属效果可验）
        plan.append(_op)
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
                if isinstance(ty, dict) and 'struct' in ty:
                    # [T7④] inline-struct dict 显式化：禁静默降 byte（复核实测 4 件）
                    iname = 'INLINE_%s_%d' % (cls, off)
                    imems = [{'offset': sm.get('offset') or 0,
                              'name': sm.get('name') or 'f%d' % i,
                              'type': sm.get('type') if isinstance(sm.get('type'), str) else 'int'}
                             for i, sm in enumerate(ty['struct']) if isinstance(sm, dict)]
                    plan.append({'kind': 'define_struct', 'name': iname,
                                 'size': None, 'members': sorted(imems, key=lambda x: x['offset'])})
                    members.append({'offset': off, 'name': m['name'], 'type': iname})
                    continue
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
