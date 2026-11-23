#!/usr/bin/env python3
"""[传播 2026-11-18] 泛型 CTaskTpl 已注成员 → 18 个 CTaskTpl_tagEffTaskParam_CEffXxx 实例化体。

定谳链:
  1. 泛型 CTaskTpl.json 已注 8 成员 (0x4..0x20): m_fCurTime/m_fDeltaTime/m_pTask/
     m_nCurTask/m_nCurSubTask/m_nTask/m_nMaxTask/m_nMaxSubTask。
  2. 18 个模板实例化体 (36B 各) 标注全空 → apply 后 IDB 全匿名 (_tail_000@0) →
     hexrays 全部 this+12 基访问渲染成 `_tail_000[X]` (语料 54 引用, N13a 阻断)。
  3. CEffCylinder 基列表二基 CTaskTpl_tagEffTaskParam_CEffCylinder@12 (ida_structs
     bases 直证); 语料语义互证: _tail_000[4]=float 时间(UpdateFrame) ≡ m_fCurTime,
     [12]=分配表指针(Create) ≡ m_pTask, [28]=8 组数 ≡ m_nMaxTask, [32]=10 ≡
     m_nMaxSubTask (72B×10 子任务池, RenderEffectPass v18+=72 循环界)。
  4. CEffModel 例外裁决: 其 IDB 实例化体曾误名 m_pGeomNode@0x20 (gbGeomNode*)——
     证伪: Create 写 10 后紧跟 `(int)>0` 循环界 (≡CEffCylinder m_nMaxSubTask=10
     同型); 全语料零真指针解引用; float+1 读取=尾成员锚走移伪影 (this+48 越入
     自有成员区)。→ 覆写为泛型成员, 原条目存档。

用法: python3 tools/propagate_ctasktpl_members_20261118.py
"""
import json
from pathlib import Path

REPO = Path(__file__).parent.parent
SDIR = REPO / 'data/annotations/structs'
GENERIC = SDIR / 'CTaskTpl.json'
ARCH = REPO / 'data/annotations/archive/ctasktpl_ceffmodel_mpgeomnode_misnomer_20261118.json'

INSTANTIATIONS = [
    'CEffAction', 'CEffAudio', 'CEffBink', 'CEffCallBack', 'CEffCamera',
    'CEffCustomShape', 'CEffCylinder', 'CEffExplosive', 'CEffgbParticle',
    'CEffGrid', 'CEffMeteor', 'CEffModel', 'CEffQuad', 'CEffQuake',
    'CEffSParticle', 'CEffShock', 'CEffTemplate', 'CEffTime',
]

gen = json.loads(GENERIC.read_text(encoding='utf-8'))
gen_km = gen.get('known_members', {})
assert len(gen_km) == 8, '泛型成员数异常: %d' % len(gen_km)

ARCH_DOCS = []
for cls in INSTANTIATIONS:
    f = SDIR / ('CTaskTpl_tagEffTaskParam_%s.json' % cls)
    if not f.exists():
        print('[warn] 缺文件: %s — 跳过' % f.name)
        continue
    d = json.loads(f.read_text(encoding='utf-8'))
    old_km = d.get('known_members', {})
    if old_km:
        # CEffModel m_pGeomNode 误名存档
        ARCH_DOCS.append({
            'file': f.name,
            'misnomer_members': old_km,
            'verdict': 'm_pGeomNode@0x20 = m_nMaxSubTask 误名。证伪链: '
                       'CEffModel::Create(0x4cfeb0) 写 10 后紧跟 (int)>0 子任务'
                       '循环界, ≡CEffCylinder::Create _tail_000[32]=10 同型; '
                       '全语料零真指针解引用; float+1 读取为尾成员锚走移伪影。',
        })
    src = ('[模板同构传播 2026-11-18] 自泛型 CTaskTpl.json 拷贝 (模板实例化布局'
           '等价; 语料语义互证: _tail_000[4]≡m_fCurTime/[12]≡m_pTask/[28]≡'
           'm_nMaxTask=8/[32]≡m_nMaxSubTask=10)')
    for k, m in gen_km.items():
        nm = dict(m)
        nm['source'] = nm.get('source', '') + ' | ' + src
        d.setdefault('known_members', {})[k] = nm
    f.write_text(json.dumps(d, indent=1, ensure_ascii=False), encoding='utf-8')
    print('[propagate] %s: %d members' % (f.name, len(gen_km)))

if ARCH_DOCS:
    ARCH.write_text(json.dumps({
        '_doc': 'CTaskTpl 实例化体误名成员存档 2026-11-18',
        'entries': ARCH_DOCS,
    }, indent=1, ensure_ascii=False), encoding='utf-8')
    print('[archive] %s' % ARCH.name)
print('[done]')
