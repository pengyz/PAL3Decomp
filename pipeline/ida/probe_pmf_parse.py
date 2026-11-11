"""[L-VAR 探针3] PMF 类型解析失败原因内省。"""
import ida_typeinf
import idc

out_lines = []
try:
    _main_body = True
except Exception:
    pass
til = ida_typeinf.get_idati()

# ① til 里有没有 CCBStage
for name in ('CCBStage', 'CCBStage *'):
    try:
        t = ida_typeinf.tinfo_t()
        ok = t.get_named_type(til, name)
        out_lines.append('til tinfo %s: %s (size=%s)' % (name, bool(ok), t.get_size() if ok else '-'))
    except Exception as _e:
        out_lines.append('til tinfo %s 异常: %s' % (name, str(_e)[:80]))
try:
    tif_p = ida_typeinf.tinfo_t()
    okp = ida_typeinf.parse_decl(tif_p, til, 'unsigned int (__thiscall *)(int) __lv;', ida_typeinf.PT_SIL)
    out_lines.append('平thiscall(无类名): %s (%s)' % (bool(okp), str(tif_p)[:50] if okp else '-'))
except Exception as _e:
    out_lines.append('平thiscall 异常: %s' % str(_e)[:80])

# ② parse_decl 变体
variants = [
    'unsigned int (CCBStage::*)(int) __lv_ann;',
    'unsigned int (CCBStage::*)(int);',
    'int (CCBStage::*)(int) __lv_ann;',
    'unsigned int (__thiscall *)(CCBStage *, int) __lv_ann;',
]
for v in variants:
    try:
        tif = ida_typeinf.tinfo_t()
        ok = ida_typeinf.parse_decl(tif, til, v, ida_typeinf.PT_SIL)
        out_lines.append('parse_decl %r -> %s (%s)' % (v, bool(ok), str(tif)[:50] if ok else '-'))
    except Exception as _e:
        out_lines.append('parse_decl %r 异常: %s' % (v, str(_e)[:80]))

# ③ typedef 路线: 先声明 fn-ptr 再用
try:
    ok1 = ida_typeinf.parse_decl(tif, til, 'typedef unsigned int (CCBStage::*CCBProcT)(int);', ida_typeinf.PT_SIL)
    out_lines.append('typedef 声明: %s' % bool(ok1))
    tif2 = ida_typeinf.tinfo_t()
    ok2 = ida_typeinf.parse_decl(tif2, til, 'CCBProcT __lv_ann;', ida_typeinf.PT_SIL)
    out_lines.append('typedef 用型: %s (%s)' % (bool(ok2), str(tif2)[:50] if ok2 else '-'))
except Exception as _e:
    out_lines.append('typedef 路线异常: %s' % str(_e)[:80])

p = __file__.replace('.py', '_out.txt')
try:
    open(p, 'w', encoding='utf-8').write('\n'.join(out_lines + ['EXC: none']))
except Exception:
    pass
import idc
idc.qexit(0)
