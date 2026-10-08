"""批量 dump 函数尾 retn（指令级）：vtable 槽签名验证的 arity 证据源。

用法: idat -S"ret_n_batch_dump.py" work.i64
输入: data/status/_vtable_slot_addrs.json (addr list, 0x-hex strings)
输出: data/status/_ret_n_batch.json  {addr: [retn 字节数列表]}（多值=mixedret 无证据）

MSVC6 __thiscall 被调方自清栈：函数尾 `ret N` 的 N = 栈参数字节数（4/槽）。
一次遍历：ida_funcs.get_func 定界 + ida_ua 逐指令到尾，只认函数末条 ret。
复用价值的管线工具（tools/）。
"""
import json, os, traceback
import ida_auto, ida_funcs, ida_ua, ida_pro

LOG = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'ret_n_batch_log.txt')
_lg = open(LOG, 'w')

def log(m):
    _lg.write('%s\n' % m); _lg.flush()

try:
    ida_auto.auto_wait()
    ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
    IN_PATH = os.path.join(ROOT, 'data', 'status', '_vtable_slot_addrs.json')
    OUT_PATH = os.path.join(ROOT, 'data', 'status', '_ret_n_batch.json')

    addrs = json.load(open(IN_PATH))
    log('addrs: %d' % len(addrs))
    out = {}
    insn = ida_ua.insn_t()
    for a in addrs:
        ea = int(a, 16)
        f = ida_funcs.get_func(ea)
        if not f:
            out[a] = None
            continue
        rets = []
        cur = f.start_ea
        while cur < f.end_ea:
            n = ida_ua.decode_insn(insn, cur)
            if n <= 0:
                break
            mnem = ida_ua.print_insn_mnem(cur)
            if mnem in ('retn', 'ret'):
                op = insn.ops[0]
                rets.append(op.value if op.type else 0)
            cur += n
        out[a] = rets if rets else None

    json.dump(out, open(OUT_PATH, 'w'), indent=0)
    log('resolved %d/%d' % (sum(1 for v in out.values() if v), len(out)))
except Exception:
    log(traceback.format_exc())
finally:
    _lg.close()
ida_pro.qexit(0)
