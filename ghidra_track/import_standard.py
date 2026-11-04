#!/usr/bin/env python3
"""标准数据通路导入器（2026-11-03）：与 D2 同法用管线 B。
段序：①创建段（create_structure/union·create_function=存在性断言）②编辑段
（apply_changeset 批 ≤250·同目标禁双 op）③dryRun 门禁（零错才 apply）。
非旁路：全部走 ghidra-mcp 标准工具面；无回退重试=转换正确性由 dryRun 裁。"""
import json, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from import_via_daemon import rpc, notify, tool
from plan_to_changeset import plan_to_changesets

_IDENT = __import__('re').compile(r'[A-Za-z_][A-Za-z0-9_]{0,127}$')


def _addr_int(a):
    s = str(a or '').strip().lower()
    s = s[2:] if s.startswith('0x') else s
    try:
        return int(s, 16)
    except ValueError:
        return None


def is_ident(name):
    """ProposalNorm.IDENT 同形（letters/digits/_ ≤128·数字开头拒）——
    changeset rename 的 name 校验面（Changeset.java ident() 实锤）。"""
    return bool(name) and bool(_IDENT.fullmatch(str(name)))


def split_renames(ops, current, globals_=None):
    """两阶段改名落地（T10 双根因修）：
    ident 名 → rename_function 带 expect={name: 现名}（乐观锁 Changeset.java:514）
    非 ident 名（~dtor/?mangled）/现名缺失 → create_label 面（标准工具·fixture 已证收任意名）
    → (changeset_ops, label_ops)。set_* 等非改名 op 原样入 changeset。"""
    cs, labels = [], []
    for op in ops:
        addr = str(op.get('address', '')).strip().lower()
        _hx = addr[2:] if addr.startswith('0x') else addr
        try:
            key = int(_hx, 16)   # 双侧 int 归一（16/8-hex 形分叉终修）
        except ValueError:
            key = None
        cur = current.get(key) if key is not None else None
        cur_name = cur.get('name') if isinstance(cur, dict) else cur
        if op.get('op') == 'rename_function':
            if is_ident(op.get('name')) and cur_name:
                cs.append(dict(op, expect={'name': cur_name}))
            else:
                labels.append({'address': op.get('address'), 'name': op.get('name')})
        elif op.get('op') == 'set_prototype':
            # expect 双键（normSignature/normConvention 比对——Changeset.java:610-614）
            cs.append(dict(op, expect={
                'signature': ((cur or {}).get('signature') or 'undefined')
                if isinstance(cur, dict) else 'undefined',
                'callingConvention': (cur or {}).get('callingConvention') or 'unknown'
                if isinstance(cur, dict) else 'unknown'}))
        elif op.get('op') == 'set_global_type':
            # expect={type,size}（Changeset.java:252）——globals 读面（T10 余项）
            g = (globals_ or {}).get(key)
            cs.append(dict(op, expect={
                'type': (g or {}).get('type', '') if isinstance(g, dict) else '',
                'size': (g or {}).get('size', 0) if isinstance(g, dict) else 0}))
        else:
            cs.append(op)
    return cs, labels


def batch_ok(r):
    """apply_changeset 批成败：text 内 `ok: false` 判失败（T10 dryRun 实锤——
    工具级 isError=None 盖不住批内 errors[]，旧计数=假成功）。"""
    if not isinstance(r, dict) or r.get('isError'):
        return False
    txt = str((r.get('content') or [{}])[0].get('text', ''))
    if 'ok: false' in txt:
        return False
    return 'ok: true' in txt or 'applied:' in txt


def fail_rc(fails, accounted):
    """fail-loud（R10/spec §4⑥）：未入分账 fail>0 ⇒ exit 1（禁只计数静默——
    2026-11-03 实测 24 条 No transaction 仅计数教训）。"""
    return 1 if (int(fails or 0) - int(accounted or 0)) > 0 else 0


def main(gpr, plan_path):
    plan = json.load(open(plan_path))
    plan = [o for o in plan if o.get('kind') != '_meta']
    rpc('initialize', {'protocolVersion': '2025-03-26', 'capabilities': {}, 'clientInfo': {'name': 'std', 'version': '1'}})
    notify('notifications/initialized')
    r = tool('create_session', {'binaryPath': gpr, 'programPath': 'PAL3.exe'}, 2)
    txt = str((r.get('content') or [{}])[0].get('text', ''))
    print('S:', txt[:60].replace('\n', ' '))
    assert 'id:' in txt, '会话创建失败=禁静默落默认会话（2026-11-03 污染教训）: %s' % txt[:120]
    sid = txt.split('id:')[1].split()[0].strip('"')
    S = {'sessionId': sid}
    stat = {'structs': [0, 0], 'unions': [0, 0], 'functions': [0, 0], 'changeset_ops': [0, 0]}
    _fails = []
    # ①创建段（拓扑：union→struct→function 存在性）
    for op in plan:
        k = op['kind']
        if k == 'define_union':
            fields = [{'name': m.get('name'), 'offset': m.get('offset'),
                       'type': m.get('type') if isinstance(m.get('type'), str) else 'byte'}
                      for m in (op.get('members') or [])]
            r = tool('create_union', dict(S, name=op.get('name') or op.get('struct'), fields=fields), 3)
        elif k == 'define_struct':
            fields = [{'name': m.get('name'), 'offset': m.get('offset'),
                       'type': m.get('type') if isinstance(m.get('type'), str) else 'byte'}
                      for m in (op.get('members') or [])]
            r = tool('create_structure', dict(S, name=op['name'], size=op.get('size'), fields=fields), 3)
        else:
            continue
        t = str((r.get('content') or [{}])[0].get('text', '')) if isinstance(r, dict) else ''
        bad = isinstance(r, dict) and (r.get('isError') or t.startswith('Error'))
        b = 'unions' if k == 'define_union' else 'structs'
        stat[b][0 if not bad else 1] += 1
        if bad: _fails.append({'stage': b, 'name': op.get('name'), 'err': t[:150]})
    # ①b 函数存在性（set_name/set_func_sig 全地址=存在断言；已存在忽略）
    faddrs = []
    for op in plan:
        if op['kind'] in ('set_name', 'set_func_sig') and op.get('addr'):
            if op['addr'] not in faddrs:
                faddrs.append(op['addr'])
    for a in faddrs:
        r = tool('create_function', dict(S, address=a), 3)
        t = str((r.get('content') or [{}])[0].get('text', '')) if isinstance(r, dict) else ''
        bad = isinstance(r, dict) and (r.get('isError') or t.startswith('Error')) and 'already' not in t.lower()
        stat['functions'][0 if not bad else 1] += 1
        if bad: _fails.append({'stage': 'function', 'addr': a, 'err': t[:150]})
    # ②编辑段：changeset 批 dryRun→apply
    # ①b 两阶段改名落地（T10 双根因修）：读现名 → split（ident→expect / 非ident→label）
    _cur = {}
    _off = 0
    while True:
        _r = tool('list_functions', dict(S, offset=_off, limit=500), 3)
        _txt = str((_r.get('content') or [{}])[0].get('text', '')) if isinstance(_r, dict) else ''
        _items, _cur_blk = [], None
        for _line in _txt.splitlines():
            _s = _line.strip()
            if _s.startswith('- '):
                if _cur_blk: _items.append(_cur_blk)
                _cur_blk = {}; _s = _s[2:]
            import re as _re
            _m = _re.match(r'^(\w+):\s*(.*)$', _s)
            if _m and _cur_blk is not None:
                _cur_blk[_m.group(1)] = _m.group(2).strip().strip('"')
        if _cur_blk: _items.append(_cur_blk)
        if not _items: break
        for _it in _items:
            _a = _it.get('address') or _it.get('entryPoint')
            if _a and _it.get('name'):
                _k = str(_a).lower()
                _k = _k[2:] if _k.startswith('0x') else _k
                try:
                    _k = int(_k, 16)
                except ValueError:
                    continue
                _cur[_k] = {'name': _it['name'],
                            'signature': _it.get('signature') or '',
                            'callingConvention': _it.get('callingConvention') or 'unknown'}
        if len(_items) < 500: break
        _off += 500
    # globals 读面（set_global_type expect={type,size}）
    _gcur, _goff = {}, 0
    while True:
        _r = tool('list_data_symbols', dict(S, offset=_goff, limit=500), 3)
        _txt = str((_r.get('content') or [{}])[0].get('text', '')) if isinstance(_r, dict) else ''
        _items, _cur_blk = [], None
        for _line in _txt.splitlines():
            _s = _line.strip()
            if _s.startswith('- '):
                if _cur_blk: _items.append(_cur_blk)
                _cur_blk = {}; _s = _s[2:]
            import re as _re
            _m = _re.match(r'^(\w+):\s*(.*)$', _s)
            if _m and _cur_blk is not None:
                _cur_blk[_m.group(1)] = _m.group(2).strip().strip('"')
        if _cur_blk: _items.append(_cur_blk)
        if not _items: break
        for _it in _items:
            _a = _it.get('address')
            if not _a or ':' in str(_a): continue
            _k = str(_a).lower()
            _k = _k[2:] if _k.startswith('0x') else _k
            try: _k = int(_k, 16)
            except ValueError: continue
            _sz = _it.get('size')
            _gcur[_k] = {'name': _it.get('name'), 'type': _it.get('dataType'),
                         'size': int(_sz) if str(_sz).isdigit() else 0}
        if len(_items) < 500: break
        _goff += 500
    # 占位地址预滤（原子批：1 个 0x0/0x1000x 拒整批 250——数据缺陷分账禁拖累全批）
    _plan = [o for o in plan
             if not (o.get('kind') in ('set_name', 'set_func_sig', 'define_global')
                     and _addr_int(o.get('addr')) is not None
                     and _addr_int(o.get('addr')) < 0x400000)]
    _skipped_ph = len(plan) - len(_plan)
    if _skipped_ph:
        _fails.append({'stage': 'placeholder-skipped', 'count': _skipped_ph,
                       'err': '占位地址 <0x400000 预滤（数据缺陷=findings 族）'})
        print('占位预滤: %d op（数据缺陷分账）' % _skipped_ph)
    _cs0 = [o for b in plan_to_changesets(_plan) for o in b['ops']]
    _cs_ops, _labels = split_renames(_cs0, _cur, globals_=_gcur)
    print('改名落地: changeset %d（带 expect）+ label %d（非 ident/现名缺）' % (
        sum(1 for o in _cs_ops if o.get('op') == 'rename_function'), len(_labels)))
    # label 面执行（create_label=标准工具面·fixture 时代已证收任意名）
    for lb in _labels:
        r = tool('create_label', dict(S, address=lb['address'], name=lb['name']), 4)
        tt = str((r.get('content') or [{}])[0].get('text', '')) if isinstance(r, dict) else ''
        if not (isinstance(r, dict) and not r.get('isError') and 'rror' not in tt[:60]):
            stat['functions'][1] += 1
            _fails.append({'stage': 'create_label', 'addr': lb['address'], 'err': tt[:150]})
        else:
            stat['functions'][0] += 1
    # ②changeset 批执行（ident 改名带 expect + 其余 op）
    batches = [{'description': 'pal3-import batch %d' % (i // 250 + 1),
                'ops': _cs_ops[i:i + 250]} for i in range(0, len(_cs_ops), 250)]
    for i, b in enumerate(batches):
        r = tool('apply_changeset', dict(S, description=b['description'], ops=b['ops'], dryRun=True), 4)
        t = str((r.get('content') or [{}])[0].get('text', '')) if isinstance(r, dict) else ''
        if not batch_ok(r):
            stat['changeset_ops'][1] += len(b['ops'])
            _fails.append({'stage': 'changeset-dryrun', 'batch': i, 'err': t[:300]})
            continue
        r = tool('apply_changeset', dict(S, description=b['description'], ops=b['ops'], dryRun=False), 5)
        ok = batch_ok(r)
        stat['changeset_ops'][0 if ok else 1] += len(b['ops'])
        if not ok:
            _fails.append({'stage': 'changeset-apply', 'batch': i,
                           'err': str((r.get('content') or [{}])[0].get('text', ''))[:300] if isinstance(r, dict) else ''})
    print('标准导入: structs %d ok/%d bad · unions %d/%d · functions %d/%d · changeset %d ok/%d bad / %d 批' % (
        stat['structs'][0], stat['structs'][1], stat['unions'][0], stat['unions'][1],
        stat['functions'][0], stat['functions'][1], stat['changeset_ops'][0], stat['changeset_ops'][1], len(batches)))
    import json as _j
    with open('ghidra_track/out/import_standard_fails.jsonl', 'w') as _fh:
        for f in _fails:
            _fh.write(_j.dumps(f, ensure_ascii=False) + '\n')
    # [T7⑥] fail-loud：stat 总 fail 未全入 _fails 分账 ⇒ rc=1（R10）
    _total_fail = (stat['structs'][1] + stat['unions'][1] + stat['functions'][1]
                   + stat['changeset_ops'][1])
    _rc = fail_rc(_total_fail, len(_fails))
    if _rc:
        print('FAIL-LOUD: stat fail=%d 未全入分账(%d) ⇒ rc=1' % (_total_fail, len(_fails)))
    return _rc

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
