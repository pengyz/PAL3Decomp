#!/usr/bin/env python3
"""[UIEmote 删除式 dtor 定谳 2026-11-21] 0x44e5c0 rejected 解除+C8 declaration_only+陈名纠正。

回归归因(19:26 loop probe, scScriptInstance.cpp 4错全链):
  生成物 pal3/src/Misc/scScriptInstance.cpp:8 = `scScriptInstance *scScriptInstance::_UIEmote(char a2)`
  体 this->~UIEmote() + 条件 operator delete(this) = UIEmote 删除式 dtor(编译器包装, 无源体)。
  病灶链: UIEmote.json 0x44e5c0 带 adjudication=rejected(20261117 机械迁移时身份待裁标记)
    → apply_annotations.py:1401 对 rejected 条目 continue(不进 IDB)
    → IDB 陈名残留 scScriptInstance::_UIEmote(旧基链时代命名)
    → export 出陈名单元 → collect 按名域路由进 scScriptInstance.cpp
    → 坏定义发射(C2039/C2673 ×4)。

修(数据层单点):
  F1 adjudication rejected 解除(身份现已定谳: UIEmote 删除式 dtor, N18 v2 体证据在档)
  F2 declaration_only=true (C8 源模型: 删除式=包装声明, 完全形 0x44e5e0=定义源, 已在 UIEmote)
  F3 sig return scScriptInstance*→UIEmote* (this 返回型随真身纠正)
  F4 name_note 补本定谳证据链

用法: python3 tools/fix_uiemote_deleting_dtor_20261121.py [--dry]
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
P = REPO / 'data' / 'annotations' / 'structs' / 'UIEmote.json'
d = json.loads(P.read_text(encoding='utf-8'))
m = d['methods']['0x0044e5c0']
assert m.get('adjudication') == 'rejected', '预期 rejected 条目'
assert m['flags'] == ['dtor', 'deleting']

# F1+F2
m.pop('adjudication', None)
m['declaration_only'] = True
# F3
m['sig_model']['return'] = 'UIEmote *'
# F4
m['name_note'] = (m.get('name_note') or '') + (
    ' | 定谳20261121: UIEmote删除式dtor(slot5伴生, 完全形0x44e5e0=定义源同文件); '
    'rejected解除(身份已裁)+declaration_only(C8: 编译器包装无源体, 体=调用完全形+条件operator delete); '
    'sig return UIEmote*(陈scScriptInstance*=旧基链残留). '
    '回归闭环: apply曾跳过rejected→IDB陈名scScriptInstance::_UIEmote残留→'
    'collect按名域路由进scScriptInstance.cpp坏定义发射(C2039/C2673×4, 19:26 loop实录)')
m['source'] = (m.get('source') or '') + ' | 定谳20261121(见name_note)'

OPS = ['F1 rejected解除', 'F2 declaration_only=true(C8删除式)', 'F3 sig return→UIEmote*', 'F4 证据链name_note']
if not DRY:
    P.write_text(json.dumps(d, ensure_ascii=False, indent=1), encoding='utf-8')
for o in OPS:
    print(' ', o)
print('done (dry=%s)' % DRY)
