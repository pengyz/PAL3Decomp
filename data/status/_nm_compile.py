import subprocess, sys, os
sys.path.insert(0,'tools'); sys.path.insert(0,'pipeline')
import gbengine_compare as gc

ROOT = r'D:\workspace\PAL3Decomp'
targets = [
    (r'pal3\src\Effect\CEffect.cpp', 'CEffect.cpp', ['?SetRenderParam@CEffect@@QAEHH@Z']),
    (r'pal3\src\Misc\UITextArea.cpp', 'UITextArea.cpp', ['?Destroy@UITextArea@@QAEXH@Z']),
    (r'pal3\src\Combat\CCBAI.cpp', 'CCBAI.cpp', ['?RunValueAutomation@CCBAI@@QAEXXZ']),
    (r'pal3\src\Combat\CCBLineupWindow.cpp', 'CCBLineupWindow.cpp', ['?RefreshFacePos@CCBLineupWindow@@QAEXXZ']),
    (r'pal3\src\GameBase\Combat.cpp', 'Combat.cpp', ['?HandleControlCmd@Combat@@QAEXH@Z']),
    (r'pal3\src\UI\UIWnd.cpp', 'UIWnd.cpp', ['?sub_445FA0@UIWnd@@QAEXPAX@Z']),
]
flags=['/nologo','/TP','/c','/O2','/Ob2','/Oi','/Ot','/Oy','/GF','/Gy','/GX','/GR','/MT','/Gd']
incs=[r'/ID:\workspace\PAL3Decomp\include', r'/ID:\workspace\PAL3Decomp\pal3\src',
      r'/ID:\workspace\PAL3Decomp\tools\compilers\msvc6.0\Include', r'/ID:\workspace\PAL3Decomp\tools\vc6\Include']
CL=ROOT+r'\tools\compilers\msvc6.0\Bin\CL.EXE'
obj=ROOT+r'\data\status\_nm.obj'

for unit, base, syms in targets:
    src=os.path.join(ROOT, unit)
    if os.path.exists(obj): os.remove(obj)
    r=subprocess.run([CL,'/nologo','/TP','/c']+flags+incs+['/Fo'+obj, src], capture_output=True, text=True, errors='replace')
    if not os.path.exists(obj):
        print('COMPILE-FAIL', base); continue
    funcs = gc.parse_coff_obj(obj)
    found = False
    for sym_name in syms:
        if sym_name in funcs:
            b = funcs[sym_name]['bytes']
            print('== %s | %d bytes' % (base, len(b)))
            print('   编译:', b.hex(' ')[:160])
            found = True; break
    if not found:
        for k, v in funcs.items():
            if any(s.split('@')[0].lstrip('?') in k for s in syms):
                print('== %s | %s | %d bytes' % (base, k[:40], len(v['bytes'])))
                print('   编译:', v['bytes'].hex(' ')[:160])
                found = True; break
    if not found:
        print('== %s 符号未找到 (%d 符号)' % (base, len(funcs)))
