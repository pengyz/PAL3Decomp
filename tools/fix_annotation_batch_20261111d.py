#!/usr/bin/env python3
"""annotation 批量修复 2026-11-11d（DLGPROC 族反汇编定谳 + 工厂返回型别 + 两槽位）。

1. DLGPROC 族三方法 thiscall→static __stdcall（反汇编入口证据）:
   - CCBUI.HandleWindowMessage@0x004E2430: `mov eax,[esp+8]; sub eax,0x110(WM_INITDIALOG)`
     读栈取参, 无 ecx-this ⇒ stdcall 4 栈参; 用作 (DLGPROC) 强转(CCBUI/CCBRoleState 5+ 站)
   - CCBUI.SettingsDialogProc@0x004E1F70: `mov ecx,[esp+0x30]` ecx 取自局部 spill 槽
     (thiscall 特征是入口即用 ecx), 参数全栈读 ⇒ stdcall
   - CCBStageCam.StoreCurrentView@0x004E8450: `mov eax,[esp+0x10]; mov ecx,[esp+0xc];
     mov edx,[esp+8]` 全栈读 ⇒ stdcall
2. globals dword_5DB6C4: dword→CCBUI *（CreateUIObj param1=CCBUI** ppUI, 调用传
   &dword_5DB6C4——槽型别由被调签名反证）
3. PAL3.cpp 0x00404800 lvars: hgfxwnd void*→HWND（::UpdateWindow(HWND) 实参 +
   hgfxwnd=(void*)g_DrvInfo.hgfxwnd 源=CreateWindow 句柄）
4. include/pal3/ida_defs.h: gbCreateGraphManager void*→gbGfxManager *
   （工厂语义: 唯一调用点 `gfxMgr = gbCreateGraphManager(&g_DrvInfo)` 赋给
   gbGfxManager*; 原型为占位 void*）

用法: python3 tools/fix_annotation_batch_20261111d.py [--apply]
"""
import json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv

DLGPROC = '(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)'

def main():
    # 1. DLGPROC 族
    for cls, addr, name in (('CCBUI', '0x004E2430', 'HandleWindowMessage'),
                            ('CCBUI', '0x004E1F70', 'SettingsDialogProc'),
                            ('CCBStageCam', '0x004E8450', 'StoreCurrentView')):
        p = os.path.join(ROOT, 'data/annotations/structs/%s.json' % cls)
        d = json.load(open(p, encoding='utf-8'))
        m = d['methods'][addr]
        old = m.get('signature')
        m['signature'] = 'static int __stdcall %s::%s%s' % (cls, name, DLGPROC)
        m['evidence_level'] = 'A'
        m['source'] = m.get('source', '') + (' | L-VAR 2026-11-11d 反汇编定谳: 入口无 ecx-this, '
            '参数全栈读(stdcall); 用作 (DLGPROC) 强转多站; 原 thiscall 归属是 IDB 类作用域命名惯性')
        print('%s.%s: %s -> static __stdcall' % (cls, name, (old or '')[:40]))
        if APPLY:
            json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    # 2. dword_5DB6C4
    p2 = os.path.join(ROOT, 'data/annotations/globals.json')
    g = json.load(open(p2, encoding='utf-8'))
    key = '0x005DB6C4'
    e = g.setdefault(key, {})
    e.setdefault('name', 'dword_5DB6C4')
    old2 = e.get('type')
    e['type'] = 'CCBUI *'
    e['evidence_level'] = 'use_site_majority'
    e['source'] = (' | L-VAR 2026-11-11d: CreateUIObj param1=CCBUI** ppUI, 调用传'
                   '&dword_5DB6C4——槽型别由被调签名反证'
                   + ('; 原类型=%s 退役' % old2 if old2 else ''))
    print('dword_5DB6C4: %s -> CCBUI *' % (old2 or '(缺省)'))
    if APPLY:
        json.dump(g, open(p2, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    # 3. hgfxwnd lvars
    p3 = os.path.join(ROOT, 'data/annotations/structs/PAL3.json')
    d3 = json.load(open(p3, encoding='utf-8'))
    me = d3.setdefault('methods', {}).setdefault('0x00404800', {})
    me.setdefault('lvars', {})['hgfxwnd'] = 'HWND'
    me['lvars_source'] = (' | L-VAR 2026-11-11d: ::UpdateWindow(HWND) 实参 + '
                          'hgfxwnd=(void*)g_DrvInfo.hgfxwnd 源=CreateWindow 句柄, void* 系占位')
    print('PAL3 0x404800 lvars: hgfxwnd -> HWND')
    if APPLY:
        json.dump(d3, open(p3, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    # 4. ida_defs.h 工厂返回型别
    p4 = os.path.join(ROOT, 'include/pal3/ida_defs.h')
    src = open(p4, encoding='utf-8', errors='ignore').read()
    old4 = 'void * __cdecl gbCreateGraphManager(struct gbGfxDriverInfo *pDriverInfo);'
    new4 = ('gbGfxManager * __cdecl gbCreateGraphManager(struct gbGfxDriverInfo *pDriverInfo);'
            ' /* [L-VAR 2026-11-11d] return retyped: factory, sole call site assigns to gbGfxManager* */')
    if old4 in src:
        src = src.replace(old4, new4)
        print('ida_defs.h gbCreateGraphManager: void* -> gbGfxManager *')
        if APPLY:
            open(p4, 'w', encoding='utf-8').write(src)
    else:
        print('ida_defs.h: 原文未命中(已改过?), 跳过')

    print('=== %s ===' % ('APPLIED' if APPLY else 'DRY-RUN'))

if __name__ == '__main__':
    main()
