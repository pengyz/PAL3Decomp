"""挂账④ 批量取证器：解禁候选的三证自动采集（归属/元数/路由）。
输出解禁工单（register_func+add_method+unskip 原子批）。"""
import sys, json, struct
sys.path.insert(0, r"D:\workspace\PAL3Decomp")
from tools.type_evidence import exe_text_image
import capstone

data, va2off, sections = exe_text_image()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True
BASE = 0x401000

adj = json.load(open(r"D:\workspace\PAL3Decomp\data\status\adjudication_skip_batch1.json", encoding="utf-8"))
skip = json.load(open(r"D:\workspace\PAL3Decomp\data\annotations\skip_functions.json", encoding="utf-8"))

def probe(va):
    off = va2off(va)
    ins = list(md.disasm(data[off:off + 800], va))   # 全函数窗（800B——深偏移集）
    thisreg = None
    disp = set()
    for i in ins[:120]:
        if thisreg is None and i.mnemonic == 'mov':
            parts = i.op_str.split(',')
            if len(parts) == 2 and parts[1].strip() == 'ecx':
                thisreg = parts[0].strip()
        for op in i.operands:
            if op.type == capstone.x86.X86_OP_MEM and thisreg:
                for r, n in ((capstone.x86.X86_REG_EDI, 'edi'),
                             (capstone.x86.X86_REG_ESI, 'esi'),
                             (capstone.x86.X86_REG_EBX, 'ebx'),
                             (capstone.x86.X86_REG_EBP, 'ebp')):
                    if op.mem.base == r and n == thisreg:
                        disp.add(op.mem.disp)
    # 调用点 push 元数（首调用点）
    pushes = None
    for off2 in range(4096, 4096 + 1478656 - 5):
        if data[off2] == 0xE8:
            rel = struct.unpack_from('<i', data, off2 + 1)[0]
            va2 = BASE + (off2 - 4096)
            if ((va2 + 5 + rel) & 0xFFFFFFFF) == va:
                w = list(md.disasm(data[off2 - 28:off2 + 5], va2 - 28))
                pushes = sum(1 for i in w if i.mnemonic == 'push')
                break
    return thisreg, sorted(disp)[:8], pushes

# 成员偏移→类反查（annotation known_members 偏移索引）
import glob, os
offset_index = {}
for f in glob.glob(r"D:\workspace\PAL3Decomp\data\annotations\structs\*.json"):
    d = json.load(open(f, encoding="utf-8"))
    cn = str(d.get("name") or os.path.basename(f)[:-5])
    for off, m in (d.get("known_members") or {}).items():
        try:
            offset_index.setdefault(int(off), []).append((cn, str((m or {}).get("name") or "")))
        except Exception:
            pass

out = []
for r in adj.get("rows", []):
    if r.get("verdict") not in ("game_thiscall", "game_thiscall_weak", "game_thisbody_weak"):
        continue
    va = int(r["addr"], 16)
    if r["addr"] not in skip:
        continue
    thisreg, disp, pushes = probe(va)
    cls_hits = []
    for d in disp:
        for cn, mn in offset_index.get(d, [])[:3]:
            cls_hits.append((cn, mn, d))
    out.append({"addr": r["addr"], "thisreg": thisreg, "member_offsets": disp,
                "pushes": pushes, "class_hits": cls_hits[:6]})
    print("%s this=%s 偏移=%s pushes=%s 类证=%s" % (
        r["addr"], thisreg, disp, pushes, cls_hits[:3]))
json.dump(out, open(r"D:\workspace\PAL3Decomp\data\status\admission_evidence_batch3.json", "w",
                    encoding="utf-8"), ensure_ascii=False, indent=2)
print("取证 %d 件" % len(out))
