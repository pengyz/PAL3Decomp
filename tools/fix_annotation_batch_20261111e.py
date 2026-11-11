#!/usr/bin/env python3
"""annotation 批量修复 2026-11-11e（HandleViewMove 反转 + 字符串常量定谳 + 句柄成员真型）。

1. CEffectSystem.HandleViewMove@0x4C65F0: `static void (float x, float y)` →
   `void __thiscall(CEffectSystem *this, float fVal)`
   证据: 入口 `push esi; mov esi, ecx` 读 [esi+4]/[esi+5] = thiscall;
   栈访问仅 [esp+8] 一参(push esi 后即原 [esp+4]); 调方 CCBStage 渲染
   v22->HandleViewMove(v2) 一实参——旧注解 static+双参双错, C2660 根因。
2. globals 0x00580AFC aBasedataSystem: → char[28]
   证据: exe 字节直读 b"Basedata system init failed.\\x00" = 28 字节字符串常量;
   发射器把它注成 `extern Logger` 是 Hex-Rays 类型混淆的忠实传播
   (FormatException 调用语境), C2653/C2440/C2227 三错根因。
3. gbGfxDriverInfo.hgfxwnd@172: unsigned int → HWND
   证据: 字段名+注释 HWND; PAL3.InitGFX `hgfxwnd = (void *)g_DrvInfo.hgfxwnd`
   赋给 HWND 槽(lvars 批D), uint 系 IDB 占位; gbGfxManager.h:95 同名成员同款。
   修后 decomp 渲染自然消 (void*) cast。头资产 include/gbengine/gbengine_types.h
   同步 gbGfxDriverInfo 定义(若含)。

用法: python3 tools/fix_annotation_batch_20261111e.py [--apply]
"""
import json, os, sys, re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv

def main():
    # 1. HandleViewMove 反转
    p = os.path.join(ROOT, 'data/annotations/structs/CEffectSystem.json')
    d = json.load(open(p, encoding='utf-8'))
    m = d['methods'].get('0x004C65F0')
    if m is None:
        for k, v in d['methods'].items():
            if str(k).upper() == '0x004C65F0':
                m = v; break
    old = m.get('signature')
    m['signature'] = 'void __thiscall(CEffectSystem *this, float fVal)'
    m['evidence_level'] = 'A'
    m['source'] = m.get('source', '') + (' | L-VAR 2026-11-11e 反汇编反转: 入口 push esi;'
        ' mov esi,ecx 读 [esi+4]/[esi+5] = thiscall; 栈访问仅 [esp+8] 一参;'
        ' 调方 v22->HandleViewMove(v2) 一实参——旧 static(float,float) 双错')
    print('HandleViewMove: %s -> void __thiscall(this, float)' % (old or '')[:50])
    if APPLY:
        json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    # 2. aBasedataSystem 字符串常量
    p2 = os.path.join(ROOT, 'data/annotations/globals.json')
    g = json.load(open(p2, encoding='utf-8'))
    key = '0x00580AFC'
    e2 = g.setdefault(key, {})
    e2.setdefault('name', 'aBasedataSystem')
    old2 = e2.get('type')
    e2['type'] = 'char[28]'
    e2['evidence_level'] = 'A'
    e2['source'] = (' | L-VAR 2026-11-11e exe 字节直读: b"Basedata system init failed.'
                    '\\x00" 28 字节字符串常量; 发射器 Logger 型系 Hex-Rays 调用语境混淆传播'
                    + ('; 原类型=%s 退役' % old2 if old2 else ''))
    print('aBasedataSystem@0x580AFC: %s -> char[28]' % (old2 or '(缺省)'))
    if APPLY:
        json.dump(g, open(p2, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    # 3. hgfxwnd 成员真型 (ida_structs 侧不手改——走 gbengine 头资产)
    p3 = os.path.join(ROOT, 'include/gbengine/gbengine_types.h')
    src = open(p3, encoding='utf-8', errors='ignore').read()
    pat = re.compile(r'(struct [^\n]*gbGfxDriverInfo \{[^}]*?)(\bunsigned int\s+hgfxwnd;\s*// HWND)', re.S)
    m3 = pat.search(src)
    if m3:
        src = src[:m3.start(2)] + 'HWND hgfxwnd; // [L-VAR 2026-11-11e: uint 系 IDB 占位, 帧真型 HWND]' + src[m3.end(2):]
        print('gbengine_types.h gbGfxDriverInfo.hgfxwnd: unsigned int -> HWND')
        if APPLY:
            open(p3, 'w', encoding='utf-8').write(src)
    else:
        print('gbengine_types.h: gbGfxDriverInfo.hgfxwnd 未找到(形态确认后手补)')

    print('=== %s ===' % ('APPLIED' if APPLY else 'DRY-RUN'))

if __name__ == '__main__':
    main()
