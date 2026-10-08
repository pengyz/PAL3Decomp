"""签名缺参族普查：ret N（stdcall 清栈）> 签名参 => 签名缺参（GetTargetRole 型）。"""
import sys, json, glob, os
sys.path.insert(0, r"D:\workspace\PAL3Decomp")
from tools.type_evidence import exe_text_image
import capstone

data, va2off, sections = exe_text_image()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True

def ret_n(va):
    off = va2off(va)
    for i in md.disasm(data[off:off + 200], va):
        if i.mnemonic in ('ret', 'retn'):
            try:
                return int(i.op_str, 16) if i.op_str else 0
            except Exception:
                return 0
    return None

def sig_params(sig):
    if not sig or '(' not in sig:
        return None
    inner = sig[sig.find('(') + 1:sig.rfind(')')]
    inner = inner.replace('__hidden this', '').strip()
    if not inner or inner == 'void':
        return 0
    depth = 0
    n = 1
    for ch in inner:
        if ch in '<([':
            depth += 1
        elif ch in '>)]':
            depth -= 1
        elif ch == ',' and depth == 0:
            n += 1
    return n

misses = []
for f in glob.glob(r"D:\workspace\PAL3Decomp\data\annotations\structs\*.json"):
    d = json.load(open(f, encoding="utf-8"))
    for mk, mv in (d.get("methods") or {}).items():
        sig = str((mv or {}).get("signature") or "")
        sp = sig_params(sig)
        if sp is None:
            continue
        try:
            va = int(mk, 16)
            rn = ret_n(va)
        except Exception:
            continue
        if rn is None:
            continue
        # stdcall 清栈：ret N => N/4 个栈参（thiscall this 在 ECX 不计）
        stack_args = rn // 4
        if stack_args > sp:
            misses.append((os.path.basename(f)[:-5], mk, (mv or {}).get("name"),
                           sp, stack_args, sig[:52]))
print("签名缺参族 %d 件（ret N/4 > 签名参）:" % len(misses))
for cls, mk, nm, sp, sa, sig in misses[:14]:
    print("  %s.%s %s 签名 %d 参 vs ret=%d (%d 参)" % (cls[:16], mk, str(nm)[:16], sp, sa * 4, sa))
json.dump({"rows": [{"cls": c, "addr": m, "name": n, "sig_p": sp, "ret_p": sa, "sig": s}
                    for c, m, n, sp, sa, s in misses]},
          open(r"D:\workspace\PAL3Decomp\data\status\sig_missing_params.json", "w", encoding="utf-8"),
          ensure_ascii=False, indent=2)
