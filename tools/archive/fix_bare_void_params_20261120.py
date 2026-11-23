#!/usr/bin/env python3
"""[N19 修复 2026-11-20] 裸 void 参数 → void*（C2860 级联案两处）。

病灶（c6647134a 挂账堆批量·RET 判据产物混入，N17 void→void* 律漏网）:
  Actor.json      0x00539700 GetAnimDataBuffer  params[0] {type: void, name: Buffer}
  CScreenMode.json 0x0053ede0                 params[0] {type: void, name: Block}

危害直证（本轮 loop 实测）:
  Actor.h:239 `void GetAnimDataBuffer(void, int)` → C2860 "'void' cannot be
  an argument type" → S1 失败 6 头（Actor/Role/RoleSystem/Scene/SceneMgr/globals
  ——全是 include 级联）+ root_blame Actor.h blocks 222 cpp ⇒ S2 ok 0/222，
  整个编译面被单行封死。回归报告 C2860 +225（probe）/ +217（codegen）。

修法: type void → void*（出参占位，N17 律先例；真类型待 RET 证据复核定谳）。
门禁: check_annotations N19（本轮新增，先验证活性抓到两处病灶再修——
C9 门禁双重死因教训）。archive 挂档。

用法: python3 tools/fix_bare_void_params_20261120.py [--dry]
归档: data/annotations/archive/n19_bare_void_fix_20261120.json
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
S = REPO / 'data/annotations'

TARGETS = [
    ('structs/Actor.json', '0x00539700', 0),
    ('structs/CScreenMode.json', '0x0053ede0', 0),
]

archive = {'_doc': 'N19 裸void参数→void* 修复 2026-11-20 (C2860级联案)',
           'fixes': []}

for rel, addr, pidx in TARGETS:
    fp = S / rel
    d = json.loads(fp.read_text(encoding='utf-8'))
    m = d['methods'][addr]
    p = m['sig_model']['params'][pidx]
    # fail-loud 前置断言：必须正好是现行病灶，否则停（数据已被他人修过/漂移）
    assert p.get('type') == 'void', \
        '%s %s params[%d] 预期裸void, 实为 %r —— 数据已漂移, 停手核查' % (
            rel, addr, pidx, p.get('type'))
    old = dict(p)
    p['type'] = 'void *'
    p['source'] = ('N19修复20261120: 裸void→void*(C2860编译直证 Actor.h:239级联案'
                   'S2 ok 0/222 + 出参语义%s + N17 void→void*律先例); 真类型待'
                   'RET证据复核定谳' % p.get('name'))
    archive['fixes'].append({'file': rel, 'addr': addr,
                             'param': pidx, 'before': old, 'after': dict(p)})
    if not DRY:
        fp.write_text(json.dumps(d, ensure_ascii=False, indent=1), encoding='utf-8')
    print('  %s %s params[%d]: void -> void * (%s)' % (rel, addr, pidx, p.get('name')))

if not DRY:
    outp = S / 'archive/n19_bare_void_fix_20261120.json'
    outp.write_text(json.dumps(archive, ensure_ascii=False, indent=1), encoding='utf-8')
    print('归档 ->', outp.name)
print('done (dry=%s), fixes=%d' % (DRY, len(archive['fixes'])))
