#!/usr/bin/env python3
"""[REF 病修复战 batch2 2026-11-20] fastcall cc 组 11 项 → thiscall（二进制定谳）。

[5b] fail=24 的组B（cc='fastcall' 成员）——REF 门不覆盖 cc 维度, [5b] parse
失败机制层拦到。本轮用序言汇编逐项定谳：

  A. UIParticle::CountActiveParticles 0x529400: 序言全程 ECX=this 基址
     ([ecx+0x7BC] 扫描循环), 零 EDX/栈参读取 → thiscall 直证
  B. GRPinput::SetMousePos 0x402ba0: 读栈参([esp+4+var]→cl→[this+8])——
     fastcall 首参走 EDX 绝不读栈 → thiscall 带参直证
     (参数数未定谳挂账: 现注解 params=[] 需后续 S4/语料定谳)
  C. ~CEffCylinder 0x4c3dd0 等 dtor 族: 标准 VC6 dtor 序言(SEH setup+
     push ecx 存 this) → VC6 律析构恒 thiscall
  D. 其余零参成员: 零参 fastcall 成员与 thiscall ABI 等价(this 均走 ECX),
     切换零风险; VC6 成员缺省 thiscall=源码真值约定

用法: python3 tools/fix_ref_diseases_batch2_20261120.py [--dry]
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
S = REPO / 'data' / 'annotations'

TARGETS = [
    ('GRPinput', '0x00402ba0',
     'A2案: 序言读栈参[esp+4+var]→cl→[this+8]——fastcall首参走EDX绝不读栈, '
     'thiscall直证; 真参数数未定谳挂账(现params=[]待S4/语料定谳)'),
    ('ScriptSystem', '0x0040cc60', 'D案: 零参成员ABI等价+VC6成员缺省thiscall'),
    ('PalScript', '0x00431f10', 'D案: 零参成员ABI等价+VC6成员缺省thiscall'),
    ('CEffCylinder', '0x004c3dd0', 'C案: 标准VC6 dtor序言(SEH+push ecx存this)直证'),
    ('CEffgbParticle', '0x004c6980', 'D案: 零参成员ABI等价+VC6成员缺省thiscall'),
    ('CEffGrid', '0x004c9650', 'C案: VC6律析构恒thiscall'),
    ('CEffMeteor', '0x004cb4c0', 'C案: VC6律析构恒thiscall'),
    ('CEffect', '0x004d0db0', 'D案: 零参成员ABI等价+VC6成员缺省thiscall'),
    ('CEffect', '0x004d3950', 'C案: VC6律析构恒thiscall'),
    ('CCBRoleState', '0x004ed250', 'D案: 零参成员ABI等价+VC6成员缺省thiscall'),
    ('UIParticle', '0x00529400',
     'A1案: 序言全程ECX=this基址([ecx+0x7BC]扫描循环)零EDX/栈参读取, '
     'thiscall直证; params原样保留(不新增断言)'),
]

archive = {'_doc': 'fastcall cc→thiscall 修复 2026-11-20 (batch2, 序言汇编定谳)',
           'ops': []}
for cls, addr, ev in TARGETS:
    fp = S / 'structs' / ('%s.json' % cls)
    d = json.loads(fp.read_text(encoding='utf-8'))
    m = d['methods'][addr]
    sm = m['sig_model']
    note = ('cc修复20261120(batch2): fastcall→thiscall (%s)' % ev)
    if 'cc修复20261120(batch2)' in (m.get('name_note') or ''):
        archive['ops'].append('%s %s: 已修过, 跳过(幂等)' % (cls, addr))
        continue
    old_cc = sm.get('cc')
    assert old_cc == 'fastcall', (cls, addr, old_cc)
    sm['cc'] = 'thiscall'
    m['name_note'] = (m.get('name_note') or '') + ' | ' + note
    if not DRY:
        fp.write_text(json.dumps(d, ensure_ascii=False, indent=1),
                      encoding='utf-8')
    archive['ops'].append('%s %s: cc %s->thiscall' % (cls, addr, old_cc))

if not DRY:
    outp = S / 'archive' / 'batch2_cc_thiscall_20261120.json'
    outp.write_text(json.dumps(archive, ensure_ascii=False, indent=1),
                    encoding='utf-8')
    print('归档 ->', outp.name)
for op in archive['ops']:
    print(' ', op)
print('done (dry=%s)' % DRY)
