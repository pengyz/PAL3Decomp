#!/usr/bin/env python3
"""[CCBUI 四路拆分落地 2026-11-21] 0x516xxx 家族+成员集迁回 CCBProtectWindow; B 槽函数挂账。

定谳链(承接 fix_ccbui_identity_contamination_20261121.py + 后续探针):
  - CCBProtectWindow 注册表自带表 0x5704A8 + binary_size=2632(旧 _misattrib 旗的 class_size 即它)
  - 0x5160a0 = CCBProtectWindow 真实 ctor(写表 0x5704A8 + this+0x488 真成员写入)
  - 0x516xxx~0x5192ff 家族 = CCBProtectWindow 方法族(Create*/InitRoleDisplay/Show*/IsResultWindowClosed)
  - 57 成员集偏移 ≤2576 ≤2632 几何有效; m_Task=tagUITask[19]@0x4b8→2576 ✓
    (旧 "CCBTaskSlot[18]闭合2648" 是先假设 2648 再凑数的循环论证, 2632 界下 CCBTaskSlot[18] 溢出)
  - 0x5257b0/0x526660/0x526740 = B类(0x5706CC)构造点/表槽1/表槽2 → 退役挂账 pending-B
  - Update@0x519660/OnMessage@0x5195e0 的 disp≤1160 = [this+0x20]->+0x488 成员指针中介, A(116B)自洽

手术:
  M1 迁移 23 方法 CCBUI → CCBProtectWindow
  M2 回迁 53 成员(除 0xa30 fp 挂账) CCBUI → CCBProtectWindow (0x48/0x4c/0x50 留 CCBUI)
  M3 退役 3 条 B 槽函数 → pending-B 归档
  M4 双侧 note 落定谳链

用法: python3 tools/fix_ccbui_split_family_20261121.py [--dry]
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
S = REPO / 'data' / 'annotations'
FP_A = S / 'structs' / 'CCBUI.json'
FP_P = S / 'structs' / 'CCBProtectWindow.json'
ARCH = S / 'archive'

a = json.loads(FP_A.read_text(encoding='utf-8'))
p = json.loads(FP_P.read_text(encoding='utf-8'))
OPS = []

# ── M1 方法迁移 ───────────────────────────────────────────────────
band = [x for x in sorted(a['methods'], key=lambda y: int(y, 16))
        if 0x5160a0 <= int(x, 16) <= 0x5192ff]
assert len(band) == 23, '迁移带条数非预期: %d' % len(band)
pwaddr = set(p.get('methods') or {})
for addr in band:
    assert addr not in pwaddr, '冲突: %s' % addr
    p.setdefault('methods', {})[addr] = a['methods'].pop(addr)
OPS.append('M1 迁移 %d 方法 → CCBProtectWindow (0x5160a0..0x5192ff 族, ctor 0x5160a0 锚)' % len(band))

# ── M2 成员回迁 ───────────────────────────────────────────────────
snap = json.loads((ARCH / 'ccbui_pre_contamination_cleanup_20261121.json')
                  .read_text(encoding='utf-8'))['snapshot']
old_km = snap['known_members']
restored, skipped = [], []
for off in sorted(old_km, key=lambda x: int(x, 16)):
    o = int(off, 16)
    if off in ('0x48', '0x4c', '0x50', '0xa30'):
        skipped.append(off)          # 留 CCBUI(A) / fp 挂账
        continue
    mm = old_km[off]
    end = o + (mm.get('size') or 0)
    assert end <= 2632, ('回迁越界: %s end=%d' % (off, end))
    p.setdefault('known_members', {})[off] = mm
    restored.append(off)
OPS.append('M2 回迁 %d 成员 → CCBProtectWindow (含 m_Task=tagUITask[19]@0x4b8→2576≤2632; '
           '跳过 %s: 0x48/4c/50 留A待证, 0xa30 fp挂账)' % (len(restored), skipped))

# ── M3 B 槽函数退役 ───────────────────────────────────────────────
pending_b = {}
for addr in ('0x005257b0', '0x00526660', '0x00526740'):
    m = a['methods'].get(addr)
    assert m is not None, addr
    pending_b[addr] = a['methods'].pop(addr)
OPS.append('M3 退役 3 条 B槽函数(0x5257b0构造点/0x526660表slot1/0x526740表slot2) → pending-B 归档')

# ── M4 note ───────────────────────────────────────────────────────
a['note'] = (a.get('note') or '') + (
    ' | 四路拆分20261121: 本类(0x5704C8表)=116B战斗板控制器——保留 ctor 0x519310/dtor对 '
    '0x519360+0x519380/表槽 Update+OnMessage/ClearAttackSequence/nimbus族/小disp族; '
    '0x516xxx族+57成员集归 CCBProtectWindow(表0x5704A8/2632B, 其ctor=0x5160a0写表+this+0x488直证); '
    '0x5257b0/0x526660/0x526740=B类(0x5706CC表/~100572B池复合体)槽函数, 退役挂账待B注册; '
    'Update/OnMessage 的 disp≤1160=[this+0x20]->+0x488 成员指针中介(非this直访), A自洽')
p['note'] = (p.get('note') or '') + (
    ' | 身份修正20261121: 0x5160a0=本类真实ctor(写表0x5704A8+this+0x488成员写入直证)——'
    '原注册ctor 0x51d6e0 与本ctor双ctor并存待裁; 0x516xxx~0x5192ff族23方法+52成员自CCBUI迁入'
    '(旧"CCBUI"注册=四路混血: 本类/A116B(0x5704C8)/B~100572B(0x5706CC)/编辑器DlgProc族); '
    'm_Task=tagUITask[19]@0x4b8 几何有效(→2576≤2632), 旧CCBTaskSlot[18]闭合2648系循环论证; '
    '本类 binary_size=2632 待分配点硬锚')

# ── 归档+写盘 ─────────────────────────────────────────────────────
arch = {
    '_doc': 'CCBUI 四路拆分 2026-11-21 (A=CCBUI 116B / CCBProtectWindow 扩编 / B 挂账)',
    'ops': OPS,
    'pending_B': {
        'functions': {k: v for k, v in pending_b.items()},
        'vtable': '0x5706CC',
        'complete_dtor': '0x525540',
        'deleting_dtor': '0x525520',
        'layout_map': 'archive/ccbui_layout_map_20261121.json (25成员, 待回迁)',
        'size_evidence': 'dtor析构界 100572',
    },
    'moved_methods': band,
    'restored_members': restored,
}
if not DRY:
    (ARCH / 'ccbui_split_pending_B_20261121.json').write_text(
        json.dumps(arch, ensure_ascii=False, indent=1), encoding='utf-8')
    FP_A.write_text(json.dumps(a, ensure_ascii=False, indent=1), encoding='utf-8')
    FP_P.write_text(json.dumps(p, ensure_ascii=False, indent=1), encoding='utf-8')

for op in OPS:
    print(' ', op)
print('\nCCBUI.methods=%d CCBProtectWindow.methods=%d members=%d (dry=%s)'
      % (len(a['methods']), len(p.get('methods') or {}),
         len(p.get('known_members') or {}), DRY))
