#!/usr/bin/env python3
"""[CCBUI 身份污染清偿 2026-11-21] A/B 双类定谳后的注册表外科手术。

定谳链(探针 tools/probe_ccbui_identity_20261121.py + 三连追踪):
  A=0x5704C8 表类(注册名 CCBUI):
    - 分配硬锚: 0x51ccfb push 74h → operator new → ctor 0x519310 (CCBAIWindow::Destroy@0x51cce0 SEH函数内)
      ⇒ A 真身 = 0x74 = 116B (2648/2632/100572 全为历史伪值)
    - 完全 dtor = 0x519380 (79B: 写表0x5704C8 + ClearAttackSequence + ~UIListBox; 删除式 0x519360 slot5 → 调它)
    - 零内嵌 widget 析构 ⇒ 无按值成员
  B=0x5706CC 表类(未注册):
    - 删除式 sub_525520 → 完全 dtor 0x525540 (611B, 析构至 +100572, ~UIListBox 收尾)
    - 析构集 ≡ m_Task 池研究租户集(UICaption/PalScript×3/URoleDialog×2/UIFrameContainer×13+) ⇒ 池战役研究对象实为 B
    - 构造: InitUI@0x525120(+0x31B) / InitSkillUI@0x5257b0(+0x51D) 中途写表 = 内联放置构造, 无独立 ctor/堆分配点
  交叉证伪:
    - 0x525540 写表 0x5706CC ≠ A 表 0x5704C8 ⇒ 非 A 的 dtor (旧 _misattrib_evidence 旗升级实锤)
    - A 簇两段(0x519310..0x51C000)扫 [+0x4B8] 零访问 ⇒ m_Task@1208 无访问者
    - ?AddTask@CCBUI@@QAEHPAVtagUITask@@H@Z @0x51a430 ⇒ task 管理=指针式, 值数组语义证伪

手术(几何不可能性=算术裁决, SaleUI round6 先例):
  C1 binary_size 100572 → 116 (分配硬锚)
  C2 退赔 0x00525540 InitShopUI 条目 (B 的完全 dtor, 非 A 方法)
  C3 退赔 m_Task@0x4b8 (值数组语义证伪+零访问者+越界)
  C4 退赔偏移 ≥116 的全部 known_members (分配界外, 保留 <116 的 3 条待重推导)
  全量原貌归档 archive/ccbui_pre_contamination_cleanup_20261121.json

用法: python3 tools/fix_ccbui_identity_contamination_20261121.py [--dry]
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
FP = REPO / 'data' / 'annotations' / 'structs' / 'CCBUI.json'
ARCH = REPO / 'data' / 'annotations' / 'archive'

d = json.loads(FP.read_text(encoding='utf-8'))
d_before = json.loads(json.dumps(d))  # 原貌快照(先于一切变更)
OPS = []

# ── C1 binary_size ────────────────────────────────────────────────
old_size = d.get('binary_size')
assert old_size == 100572, ('binary_size 非预期态: %r' % old_size)
d['binary_size'] = 116
d['size_evidence'] = (
    'operator new(0x74)=116 @0x51ccfb(push 74h; call ??2@YAPAXI@Z) 紧跟 '
    'ctor ??0CCBUI@@QAE@XZ@0x51cd1a 调用(CCBAIWindow::Destroy@0x51cce0 SEH函数内)——分配硬锚. '
    '历史: 2648=ida_structs早期残留; 100572=B类(0x5706CC表)完全dtor(0x525540)析构界错落给A, '
    '20261121身份定谳后归还B(见 archive/ccbui_identity_adjudication_20261121.json). '
    'base 72(UIListBox) + 自有44B(≈指针槽), 与完全dtor(0x519380)零内嵌析构一致.')
OPS.append('C1 binary_size %s → 116 (分配硬锚 0x74)' % old_size)

# ── C2 退赔 0x525540 (B 的完全 dtor) ──────────────────────────────
m = (d.get('methods') or {}).get('0x00525540')
assert m is not None and m.get('name') == 'InitShopUI', '0x525540 条目非预期态'
del d['methods']['0x00525540']
OPS.append('C2 退赔 methods[0x00525540] InitShopUI (B类完全dtor: 写表0x5706CC≠0x5704C8; '
           '删除式对 sub_525520→0x525540; 旧 _misattrib_evidence 旗升级实锤)')

# ── C3+C4 成员清偿 ────────────────────────────────────────────────
km = d.get('known_members') or {}
retired, kept = [], []
for off, mm in sorted(km.items(), key=lambda kv: int(kv[0], 16)):
    o = int(off, 16)
    sz = mm.get('size')
    nm = mm.get('name')
    if nm == 'm_Task':
        retired.append((off, mm, '值数组语义证伪(AddTask=tagUITask*指针式)+零访问者+越界'))
    elif sz is not None and o + sz > 116:
        retired.append((off, mm, '越界(成员末端 %d > 分配界 116)' % (o + sz)))
    elif o >= 116:
        retired.append((off, mm, '起点越界(≥116)'))
    else:
        kept.append(off)
# size 缺失但起点越界的已由第三分支兜底; 有 size 字段才用末端算术
for off, mm, why in retired:
    del km[off]
    OPS.append('  退赔 known_members[%s] %s (%s)' % (off, mm.get('name'), why))

note_add = (
    ' | 身份定谳20261121(A/B双类): 本类(0x5704C8表)=116B小类——分配硬锚0x74; '
    '完全dtor=0x519380(删除式0x519360 slot5→调它); 零内嵌析构. '
    '0x525540(InitShopUI)=B类(0x5706CC表,100572B混居池复合体)完全dtor, 已退赔——'
    'binary_size=100572/25成员布局图/m_Task池研究(placement-new租户)全部实为B的取证, '
    '归档 archive/ccbui_identity_adjudication_20261121.json 待B注册后回迁. '
    '成员retire %d条(几何不可能); 保留<116的%s条待方法disp访问重推导. '
    'CCBUI名字归属(A vs B)挂账: 需corpus/调用流证据.' % (len(retired), kept))
d['note'] = (d.get('note') or '') + note_add

# ── 归档 ──────────────────────────────────────────────────────────
ARCH.mkdir(parents=True, exist_ok=True)
arch_payload = {
    '_doc': 'CCBUI 身份污染清偿 2026-11-21 (A=0x5704C8 116B / B=0x5706CC ~100572B 双类定谳)',
    'ops': OPS,
    'retired_members': {off: mm for off, mm, _ in retired},
    'kept_members': kept,
    'B_adjudication': {
        'vtable': '0x5706CC',
        'slots': {'0': '0x445e70 ShowClipped(UIWnd)', '1': '0x526660 CCBUI_Render@CCBUI(名源非权威)',
                  '2': '0x526740 UpdateStatics@CCBUI', '3': '0x43de40 Destroy',
                  '4': '0x445b90 Create(UIWnd)', '5': '0x525520 删除式dtor',
                  '6': '0x526a40 sub_526A40'},
        'complete_dtor': '0x525540 (611B, 析构至+100572, ~UIListBox收尾)',
        'size_evidence': 'dtor析构界100572 (无独立ctor/堆分配点: InitUI@0x525120/InitSkillUI@0x5257b0 内联放置构造)',
        'destroyed_members': '见 archive/ccbui_layout_map_20261121.json (25条, 待回迁)',
        'identity': '未定谳——原始IDB名(@CCBUI簇)与A名冲突, 名字归属挂账',
    },
    'A_alloc_anchor': 'push 74h @0x51ccfb → operator new → ctor 0x519310 @0x51cd1a (CCBAIWindow::Destroy@0x51cce0)',
}
if not DRY:
    (ARCH / 'ccbui_pre_contamination_cleanup_20261121.json').write_text(
        json.dumps({'snapshot': d_before,
                    'adjudication': arch_payload}, ensure_ascii=False, indent=1),
        encoding='utf-8')
    (ARCH / 'ccbui_identity_adjudication_20261121.json').write_text(
        json.dumps(arch_payload, ensure_ascii=False, indent=1), encoding='utf-8')
    FP.write_text(json.dumps(d, ensure_ascii=False, indent=1), encoding='utf-8')

for op in OPS:
    print(' ', op)
print('\nkept(<116, %d): %s' % (len(kept), kept))
print('retired: %d, methods退赔: 1, binary_size: %s→116 (dry=%s)'
      % (len(retired), old_size, DRY))
