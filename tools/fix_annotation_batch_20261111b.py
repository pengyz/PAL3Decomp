#!/usr/bin/env python3
"""annotation 批量修复 2026-11-11b（lvars 第二批 + FormatException 变参定谳）。

批二 lvars（全部使用点全列取证=纯赢判定）:
- CCBStage 0x004FCE70 / 0x004FD1A0  v8: float → int
    证据: `v8 = *(_DWORD*)(v3+20)`(dword 写) 后全为字节算术基址用法
    (`*(_DWORD*)(v8+900/904/908/916)` EndTurnAndAdvance 实参)——
    dword 槽存基址, int 是字节算术合法持有型; float 声明使 v8+904
    炸成 C2440 ×5(2471-2473 实证)。
- CEffCylinder 0x004C2600  v2: float → CEffMgr *
    证据: `this->m_pEM = ((CEffMgr *)(v2))` 唯一指针语境;
    `*(float *)&v2` 位读形式在 retype 后仍合法(C-style 位取)。
- CameraCtrl 0x0041CC50  v7: float → float *
    证据: `v7 = (float *)&this->m_pTarget[13]._tail_000[24]` 写 +
    `v7[1]=..`/`*v7=..`/`v7[2]=..` 三处 float* 解引用写——全指针语境。

签名定谳:
- Logger FormatException: `(Logger*, char *msg, char *file, int line)` →
  `(Logger*, char *msg, ...)` 变参
    证据: CEffMgr.cpp:827/872 实参 (aCouldnTOpenEff, pSrc.m_fSize)=
    (格式串, float 值)——printf 族形态; 固定 (file,line) 签名与调用
    实参数不符(C2660/C2664 双证)。evidence: unverified→use_site_majority。

用法: python3 tools/fix_annotation_batch_20261111b.py [--apply]
"""
import json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv

def main():
    # lvars 批二
    for cls, addr, var, typ, ev in (
        ('CCBStage',     '0x004FCE70', 'v8', 'int',
         'v8=dword 写(v3+20)后全字节算术基址(*(DWORD*)(v8+900/904/908/916) 实参); float 声明炸 C2440 x5'),
        ('CCBStage',     '0x004FD1A0', 'v8', 'int',
         '同 0x4FCE70 平行块: v8=dword 写(v7+20)后字节算术基址'),
        ('CEffCylinder', '0x004C2600', 'v2', 'CEffMgr *',
         '唯一指针语境 this->m_pEM=((CEffMgr*)v2); *(float*)&v2 位读 retype 后仍合法'),
        ('CameraCtrl',   '0x0041CC50', 'v7', 'float *',
         'v7=(float*)&m_pTarget[13]._tail_000[24] 写 + v7[1]/*v7/v7[2] 三处 float* 解引用'),
    ):
        p = os.path.join(ROOT, 'data/annotations/structs/%s.json' % cls)
        d = json.load(open(p, encoding='utf-8'))
        me = d.setdefault('methods', {}).setdefault(addr, {})
        me.setdefault('lvars', {})[var] = typ
        me['lvars_source'] = ' | L-VAR 批二 2026-11-11(纯赢=全部使用点自洽): ' + ev
        print('lvars %s%s: %s -> %s' % (cls, addr, var, typ))
        if APPLY:
            json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    # FormatException 变参
    p2 = os.path.join(ROOT, 'data/annotations/structs/Logger.json')
    d2 = json.load(open(p2, encoding='utf-8'))
    for a, m in (d2.get('methods') or {}).items():
        if m.get('name') == 'FormatException':
            old = m.get('signature')
            m['signature'] = 'char *__thiscall(Logger *this, char *msg, ...)'
            m['evidence_level'] = 'use_site_majority'
            m['source'] = m.get('source', '') + (' | L-VAR 2026-11-11 变参定谳: '
                'CEffMgr.cpp:827/872 实参 (格式串, float 值) printf 族形态; '
                '固定 (file,line) 与调用实参数不符')
            print('FormatException %s: %s -> 变参' % (a, old))
    if APPLY:
        json.dump(d2, open(p2, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    print('=== %s ===' % ('APPLIED' if APPLY else 'DRY-RUN(加 --apply 落盘)'))

if __name__ == '__main__':
    main()
