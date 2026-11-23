#!/usr/bin/env python3
"""[REF 病修复战 batch3 2026-11-20] 幻影方法退赔×5 + pending×1 + 拼写×1。

idalib 探针定谳链(本轮 [5b] 组C 真因闭环):
  parse_decl 全过 → apply_tinfo 拒 → at_start=False → **五址非函数头**
  → 全二进制扫描: 零表引用 + 零 call 引用 = **纯死代码幻影方法**
  (ICF折叠体借用注记史: 同体复制未被折叠的死拷贝)

三证齐(非函数头/零表引用/零call引用)⇒退赔(条目删除, 知识留档; 0x4a4820 先例):
  D1 CEffCylinder 0x004c2640 slot_4        (func@0x4c2620 体中偏移+0x20)
  D2 CEffCylinder 0x004c2660 ProcessData_2 (+0x40)
  D3 CEffCylinder 0x004c2680 ProcessData_3 (+0x60)
  D4 GRPinput    0x0044ca70 _Split         (func@0x44c970)
  D5 CCBUI       0x0051b9c0 _todo_51B9C0   (func@0x51b9a0)

  D6 Array 0x00411ba0 _nearby_411ba0 → pending=true
     (活函数: call 引用 0x434d53 直证——非退赔; return=自名污染且无体证据
      → pending 未定谳正当态, 与 CPK::Load 同案)

  D7 UIScene 0x0043c7b0 CreateScrollWidget return 'gbVFileSys *'→'gbVFileSystem *'
     (全树 gbVFileSys 零声明——UIScene.h:17 'class gbVFileSys;' 是 emitter
      为本病注解打的前向声明补丁, 修注解后随 codegen 消亡; gbVFileSystem
      有声明 gbVFileSystem.h + til 已入)

用法: python3 tools/fix_ref_diseases_batch3_20261120.py [--dry]
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
S = REPO / 'data' / 'annotations'

RETIRE = [
    ('CEffCylinder', '0x004c2640', 'slot_4',        'func@0x4c2620 体中+0x20'),
    ('CEffCylinder', '0x004c2660', 'ProcessData_2', 'func@0x4c2620 体中+0x40'),
    ('CEffCylinder', '0x004c2680', 'ProcessData_3', 'func@0x4c2620 体中+0x60'),
    ('GRPinput',     '0x0044ca70', '_Split',        'func@0x44c970'),
    ('CCBUI',        '0x0051b9c0', '_todo_51B9C0',  'func@0x51b9a0'),
]

OPS = []
for cls, addr, name, where in RETIRE:
    fp = S / 'structs' / ('%s.json' % cls)
    d = json.loads(fp.read_text(encoding='utf-8'))
    m = d.get('methods', {}).get(addr)
    assert m is not None and m.get('name') == name, (cls, addr, m and m.get('name'))
    del d['methods'][addr]
    if not DRY:
        fp.write_text(json.dumps(d, ensure_ascii=False, indent=1),
                      encoding='utf-8')
    OPS.append('%s %s %s 退赔(死代码三证: 非函数头[%s]/零表引用/零call引用; '
               'ICF折叠体借用史留档)' % (cls, addr, name, where))

# D6 Array pending
fp = S / 'structs' / 'Array.json'
d = json.loads(fp.read_text(encoding='utf-8'))
m = d['methods']['0x00411ba0']
sm = m['sig_model']
if not sm.get('pending'):
    sm['pending'] = True
    m['name_note'] = (m.get('name_note') or '') + (
        ' | REF修复20261120(batch3 D6): return=自名污染(_nearby_411ba0)→'
        'pending=true; 活函数(call引用0x434d53直证)非退赔; 真名/真返回型待'
        '体证据定谳')
    if not DRY:
        fp.write_text(json.dumps(d, ensure_ascii=False, indent=1),
                      encoding='utf-8')
    OPS.append('Array 0x00411ba0 pending=true (活函数, 类型未定谳)')

# D7 UIScene 拼写
fp = S / 'structs' / 'UIScene.json'
d = json.loads(fp.read_text(encoding='utf-8'))
m = d['methods']['0x0043c7b0']
sm = m['sig_model']
if str(sm.get('return')) == 'gbVFileSys *':
    sm['return'] = 'gbVFileSystem *'
    m['name_note'] = (m.get('name_note') or '') + (
        ' | REF修复20261120(batch3 D7): gbVFileSys→gbVFileSystem (全树'
        'gbVFileSys零声明——UIScene.h:17 fwd decl=emitter为本病打的补丁, '
        '修后随codegen消亡; gbVFileSystem声明gbVFileSystem.h)')
    if not DRY:
        fp.write_text(json.dumps(d, ensure_ascii=False, indent=1),
                      encoding='utf-8')
    OPS.append('UIScene 0x0043c7b0 return gbVFileSys->gbVFileSystem')
else:
    OPS.append('UIScene 0x0043c7b0: 已修过(%r), 跳过' % sm.get('return'))

for op in OPS:
    print(' ', op)
print('done (dry=%s), ops=%d' % (DRY, len(OPS)))
