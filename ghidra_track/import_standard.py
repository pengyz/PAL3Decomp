#!/usr/bin/env python3
"""标准数据通路导入器（2026-11-03）：与 D2 同法用管线 B。
段序：①创建段（create_structure/union·create_function=存在性断言）②编辑段
（apply_changeset 批 ≤250·同目标禁双 op）③dryRun 门禁（零错才 apply）。
非旁路：全部走 ghidra-mcp 标准工具面；无回退重试=转换正确性由 dryRun 裁。"""
import json, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from import_via_daemon import rpc, notify, tool
from plan_to_changeset import plan_to_changesets

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
    # ②编辑段：changeset 批 dryRun→apply
    batches = plan_to_changesets(plan)
    for i, b in enumerate(batches):
        r = tool('apply_changeset', dict(S, description=b['description'], ops=b['ops'], dryRun=True), 4)
        t = str((r.get('content') or [{}])[0].get('text', '')) if isinstance(r, dict) else ''
        if isinstance(r, dict) and (r.get('isError') or 'fail' in t[:200].lower() or 'refuse' in t.lower()):
            stat['changeset_ops'][1] += len(b['ops'])
            if i < 3: print('dryRun 拒:', t[:150])
            continue
        r = tool('apply_changeset', dict(S, description=b['description'], ops=b['ops'], dryRun=False), 5)
        t = str((r.get('content') or [{}])[0].get('text', '')) if isinstance(r, dict) else ''
        ok = not (isinstance(r, dict) and r.get('isError'))
        stat['changeset_ops'][0 if ok else 1] += len(b['ops'])
    print('标准导入: structs %d ok/%d bad · unions %d/%d · functions %d/%d · changeset %d ok/%d bad / %d 批' % (
        stat['structs'][0], stat['structs'][1], stat['unions'][0], stat['unions'][1],
        stat['functions'][0], stat['functions'][1], stat['changeset_ops'][0], stat['changeset_ops'][1], len(batches)))
    # [T7⑥] fail-loud：stat 总 fail 未全入 _fails 分账 ⇒ rc=1（R10）
    _total_fail = (stat['structs'][1] + stat['unions'][1] + stat['functions'][1]
                   + stat['changeset_ops'][1])
    _rc = fail_rc(_total_fail, len(_fails))
    if _rc:
        print('FAIL-LOUD: stat fail=%d 未全入分账(%d) ⇒ rc=1' % (_total_fail, len(_fails)))
    return _rc

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
