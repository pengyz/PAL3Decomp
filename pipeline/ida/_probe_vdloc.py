"""探针：0x401500 的 lvar location API 自省（一次性）。"""
import ida_auto, ida_hexrays, idc, ida_pro
import sys

class _Log:
    def write(self, m): open(r'D:\workspace\PAL3Decomp\pipeline\ida\_logsdloc_probe.txt', 'a', encoding='utf-8').write(m)
    def flush(self): pass
sys.stdout = _Log()
open(r'D:\workspace\PAL3Decomp\pipeline\ida\_logsdloc_probe.txt', 'w').close()

ida_auto.auto_wait()
ea = 0x401500
cfunc = ida_hexrays.decompile(ea)
for lv in cfunc.lvars:
    loc = lv.location
    print('[probe]', lv.name, 'is_reg=', loc.is_reg(), 'is_stkoff=', loc.is_stkoff(),
          'stkoff=', loc.stkoff() if loc.is_stkoff() else None)
    if loc.is_reg():
        attrs = [a for a in dir(loc) if not a.startswith('_')]
        print('[probe] vdloc attrs:', attrs)
        for cand in ('regidx', 'reg1', 'reg'):
            if hasattr(loc, cand):
                try:
                    v = getattr(loc, cand)
                    v = v() if callable(v) else v
                    print('[probe] %s =' % cand, v)
                except Exception as e:
                    print('[probe] %s raised: %s' % (cand, e))
ida_pro.qexit(0)
