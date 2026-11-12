#!/usr/bin/env python3
"""[vptr补标 2026-11-12] 有vtables继承链的类补 offset0 __vftable 标注。

病灶定谳:
  全库 55 个 vtable 继承链的根类 known_members 缺 0x0 __vftable 条目
  → build_struct_decl 的 typed-vptr 注入 (apply_annotations:494-500) 永不触发
  → IDB UDT 无 __vftable 成员 → Hex-Rays 无法解析虚槽类型
  → 裸 (**ptr)(ptr,arg) 调用渲染 IDA 猜测 fn-ptr(this=int/_DWORD)
  → C2664 cannot convert parameter 1 (census 近绿池 7 站点实证:
    Array:1319/1333/1346, LineupComp:88/132, UITitle_XJTM:448/808,
    槽0=ShowClipped@0x445E70, vtbl_0056AE2C 已建 189/189 但零引用)

证据: MSVC ABI 多态类 vptr 恒在 +0; 各类 vtables[].slots 虚分派调用点即证。
范围: 有 vtables 的继承链的根类 (48 根有 vtables→typed 注入;
  7 根无 vtables (PalScriptWaitObj/gbCamera/gbRefObject/gbSingleton_gbGfxManager/
  gbVolumeModifier/sg_particle_scene) → 标记型 int __vftable (ABI 占位, 不编造
  vtable 地址)。

用法: python3 tools/fix_vptr_offset0_20261112.py [--apply]
"""
import json
import glob
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv

all_cls = {}
for f in glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json')):
    d = json.load(open(f, encoding='utf-8'))
    cls = d.get('name') or os.path.basename(f)[:-5]
    all_cls[cls] = d


def root_of(cls, depth=0):
    if depth > 8:
        return cls
    d = all_cls.get(cls)
    if not d:
        return cls
    bases = d.get('bases') or []
    if not bases:
        return cls
    b0 = bases[0].get('name')
    return root_of(b0, depth + 1) if b0 else cls


changed = []
for fname in sorted(os.listdir(os.path.join(ROOT, 'data', 'annotations', 'structs'))):
    if not fname.endswith('.json'):
        continue
    fp = os.path.join(ROOT, 'data', 'annotations', 'structs', fname)
    d = json.load(open(fp, encoding='utf-8'))
    cls = d.get('name') or fname[:-5]
    if not (d.get('vtables') or []):
        continue
    rt = root_of(cls)
    if rt != cls:
        continue  # 派生类: vptr 由根 UDT 提供
    km = d.setdefault('known_members', {})
    off0 = km.get('0x0') or km.get('0x00')
    if off0 and off0.get('name') in ('__vftable', 'vfptr'):
        continue
    has_vt = bool(d.get('vtables'))
    vt0 = (d.get('vtables') or [{}])[0].get('addr', '')
    km.pop('0x00', None)
    km['0x0'] = {
        'name': '__vftable',
        'type': 'int',
        'source': 'vptr_abi_fill',
        'evidence': 'MSVC ABI 多态类 vptr@0; vtables[0]@%s 虚分派调用点即证; '
                    'census 2026-11-12 7处C2664槽族' % (vt0 or '(继承链)'),
    }
    changed.append((cls, has_vt, vt0))
    if APPLY:
        json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

print('类数: %d (typed=%d, 标记型=%d)' % (
    len(changed), sum(1 for _, h, _ in changed if h), sum(1 for _, h, _ in changed if not h)))
for c, h, v in sorted(changed):
    print('  %-24s %s %s' % (c, 'typed' if h else 'plain', v))
if not APPLY:
    print('\n[dry-run] 加 --apply 落盘')
