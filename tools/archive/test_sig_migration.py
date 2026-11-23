#!/usr/bin/env python3
"""[S2迁移用例 2026-11-16 TDD] 注解层 sig 结构化迁移 + 消费装载器 行为定义。
先于实现编写(红→绿): 本文件初始运行必失败——被测函数尚不存在。
"""
import sys, os, json, tempfile
sys.path.insert(0, os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')))
from pipeline.sigmodel import node_of, migrate_entry, validate

PASS = FAIL = 0
def ok(cond, note):
    global PASS, FAIL
    if cond: PASS += 1
    else:
        FAIL += 1
        print('[FAIL] %s' % note)

# ── 装载器 node_of(entry): 结构优先, 字符串回退, 双缺pending ──
def t_node_of():
    # 1. 有结构 → 直返
    e = {'sig_model': {'return': 'void', 'cc': 'thiscall', 'params': [], 'varargs': False, 'pending': False}}
    n = node_of(e)
    ok(n and n['return'] == 'void', 'node_of: 结构优先')
    # 2. 仅字符串 → 解析
    e2 = {'signature': 'int __thiscall(int nMsg, unsigned int wParam)'}
    n2 = node_of(e2)
    ok(n2 and n2['return'] == 'int' and len(n2['params']) == 2
       and n2['params'][0]['name'] == 'nMsg', 'node_of: 字符串解析回退(名保留)')
    # 3. 双缺 → pending诚实态
    n3 = node_of({})
    ok(n3 and n3.get('pending') is True, 'node_of: 双缺=pending诚实态')
    # 4. 垃圾字符串 → pending(不伪造)
    n4 = node_of({'signature': '___垃圾___'})
    ok(n4 and n4.get('pending') is True, 'node_of: 垃圾串=pending不伪造')

# ── 迁移 migrate_entry(entry) → (entry变异, 迁移报告行) ──
def t_migrate_entry():
    # 1. 合法串 → 加sig_model, 原串保留(S5前兼容)
    e = {'name': 'OnMessage', 'signature': 'int __thiscall(int nMsg, unsigned int wParam)'}
    report = migrate_entry(e)
    ok(e.get('sig_model') is not None, '迁移: 合法串加sig_model')
    ok(e.get('signature') == 'int __thiscall(int nMsg, unsigned int wParam)', '迁移: 原串保留(S5前兼容)')
    ok(report.get('status') == 'migrated', '迁移报告: migrated')
    # 2. 幂等: 已有sig_model → no-op
    report2 = migrate_entry(e)
    ok(report2.get('status') == 'noop', '迁移: 幂等noop')
    # 3. 零串 → pending标记
    e2 = {'name': 'X'}
    r2 = migrate_entry(e2)
    ok(e2.get('sig_model', {}).get('pending') is True, '迁移: 零串pending')
    ok(r2.get('status') == 'pending', '迁移报告: pending')
    # 4. 垃圾串 → pending+报告
    e3 = {'signature': '###'}
    r3 = migrate_entry(e3)
    ok(e3.get('sig_model', {}).get('pending') is True, '迁移: 垃圾串pending')
    ok(r3.get('status') == 'pending', '迁移报告: pending')
    # 5. 结构化后过validate
    ok(validate(e['sig_model']) == [], '迁移: 产物过validate')

# ── 端到端: 临时注解文件迁移往返 ──
def t_roundtrip_file():
    doc = {'methods': {
        '0x00445d10': {'name': 'OnMessage', 'signature': 'int __thiscall(int nMsg, unsigned int wParam, long lParam)'},
        '0x00451800': {'name': 'Mystery'},
    }}
    tf = tempfile.NamedTemporaryFile('w', suffix='.json', delete=False)
    json.dump(doc, tf); tf.close()
    from tools.migrate_sig_struct_20261116 import migrate_file
    n_mig, report = migrate_file(tf.name)
    d2 = json.load(open(tf.name, encoding='utf-8'))
    m1 = d2['methods']['0x00445d10']
    ok(m1.get('sig_model', {}).get('return') == 'int', '端到端: 结构落盘')
    ok(len(m1.get('sig_model', {}).get('params') or []) == 3, '端到端: 三参结构')
    ok(m1.get('signature') is not None, '端到端: 原串保留')
    m2 = d2['methods']['0x00451800']
    ok(m2.get('sig_model', {}).get('pending') is True, '端到端: 零证据槽pending落盘')
    ok(n_mig == 1 and report.get('pending') == 1, '端到端: 迁移计数(1迁移+1pending分账)')
    os.unlink(tf.name)

for t in (t_node_of, t_migrate_entry, t_roundtrip_file):
    try:
        t()
    except (ImportError, AttributeError) as ex:
        print('[RED] %s 未实现: %s' % (t.__name__, ex)); FAIL += 1

print('\nTDD: %d pass / %d fail' % (PASS, FAIL))
sys.exit(0 if FAIL == 0 else 1)
