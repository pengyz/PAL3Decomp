#!/usr/bin/env python3
"""[R4 事件修复 2026-11-19] Object/ObjectCamera dtor 身份裁决——C2084 双定义 + '@' mangled 泄漏。

证据链:
  Object 0x411bd0 = ??_GObject(删除析构): vtable slot0 表归属实证(0x56A9BC 表地图,
    slot0=0x411bd0); 语料体=??_G 织入形态(调 ~Object + flags&1 条件删 + return)。
    现 sig_model 为借用垃圾(return CCBAIWindow * / int 参——语料体借用病)。
  Object 0x411ca0 = ??1Object(完全析构): 16:19 终裁, 保留定义发射。
  N18 律: 源级单析构声明, VC6 自生 ??1/??_G 对 → ??_G 条目 declaration_only 压制。

  ObjectCamera 0x47c570 = adjustor thunk(纯转发调 0x47c580, hexrays 'attributes: thunk')
  ObjectCamera 0x47c580 = 完全析构真体(flt_DE4A00=24.0 写全局常数=真实源级体),
    现被 decl_only 压制 → 定义缺位, thunk 体反被发射 + 引用压制函数的 raw mangled 名
    (??1ObjectCamera@@QAE@XZ_0) → '@' C2018。
  修复: 真体发定义(除 decl_only), thunk 压制(加 decl_only)——VC6 按源自生 thunk 对。

用法: python3 tools/sem_conv_r4_dtor_identity_object_20261119.py [--dry]
归档: data/annotations/archive/dtor_identity_object_objectcamera_20261119.json
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv

ops = []
archive = {'_doc': 'Object/ObjectCamera dtor 身份裁决 2026-11-19', 'entries': []}

# ── Object 0x411bd0: ??_G → declaration_only + deleting 形 sig ──
fp = REPO / 'data/annotations/structs/Object.json'
d = json.loads(fp.read_text(encoding='utf-8'))
m = d['methods']['0x00411bd0']
assert 'deleting' in (m.get('flags') or []), '0x411bd0 应带 deleting'
ops.append(('Object 0x411bd0', 'declaration_only', m.get('declaration_only'), True))
m['declaration_only'] = True
ops.append(('Object 0x411bd0', 'sig_model',
            json.dumps(m.get('sig_model'), ensure_ascii=False)[:60],
            '{"return":"int","params":[{"type":"char"}]} deleting 形'))
m['sig_model'] = {'return': 'int', 'cc': 'thiscall',
                  'params': [{'type': 'char', 'name': None}],
                  'varargs': False, 'pending': False}
# 0x411ca0 断言: 完全析构不带 decl_only(定义载体)
m2 = d['methods']['0x00411ca0']
assert not m2.get('declaration_only'), '0x411ca0 应为定义载体'
assert 'deleting' not in (m2.get('flags') or []), '0x411ca0 应为 complete(无 deleting)'
archive['entries'].append({'cls': 'Object', 'addr': '0x00411bd0',
                           'evidence': 'vtable slot0 表归属(0x56A9BC 地图)+??_G织入语料形',
                           'action': 'declaration_only=True + sig deleting 形'})
archive['entries'].append({'cls': 'Object', 'addr': '0x00411ca0',
                           'evidence': '16:19 终裁 ??1 complete', 'action': '保留定义载体'})
if not DRY:
    fp.write_text(json.dumps(d, ensure_ascii=False, indent=1), encoding='utf-8')

# ── ObjectCamera: 真体除压制, thunk 加压制 ──
fp2 = REPO / 'data/annotations/structs/ObjectCamera.json'
d2 = json.loads(fp2.read_text(encoding='utf-8'))
mc = d2['methods']['0x0047c580']
assert mc.get('declaration_only') is True, '0x47c580 现应被压制(前态断言)'
ops.append(('ObjectCamera 0x47c580', 'declaration_only', True, None))
mc['declaration_only'] = None  # 除压制 → 定义载体(真实源级体)
mt = d2['methods']['0x0047c570']
assert mt.get('declaration_only') is None, '0x47c570 现应发射(前态断言)'
ops.append(('ObjectCamera 0x47c570', 'declaration_only', None, True))
mt['declaration_only'] = True  # thunk 压制
archive['entries'].append({'cls': 'ObjectCamera', 'addr': '0x0047c580',
                           'evidence': "真体(flt_DE4A00=24.0 源级体); hexrays 'attributes: thunk' 在 0x47c570",
                           'action': '除 decl_only → 定义载体'})
archive['entries'].append({'cls': 'ObjectCamera', 'addr': '0x0047c570',
                           'evidence': '纯转发 thunk(调 0x47c580)——编译器产物, VC6 自生',
                           'action': 'decl_only=True 压制(灭 "@1ObjectCamera@@QAE@XZ_0" 泄漏)'})
if not DRY:
    fp2.write_text(json.dumps(d2, ensure_ascii=False, indent=1), encoding='utf-8')

for tag, field, old, new in ops:
    print('  %-24s %-18s %r -> %r' % (tag, field, old, new))

if not DRY:
    outp = REPO / 'data/annotations/archive/dtor_identity_object_objectcamera_20261119.json'
    outp.write_text(json.dumps(archive, ensure_ascii=False, indent=1), encoding='utf-8')
    print('归档 -> %s' % outp.name)
print('done (dry=%s)' % DRY)
