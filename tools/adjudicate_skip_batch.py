"""挂账⑤ 批量裁决器（adjudication_432 同法）：skip 件的 game/库/三方判据。
D 名形初筛 → A 序言指纹（thiscall/gcc_aligned）→ C 调用图（game_calls/lib_calls）→
A′ 体征（this_refs/fpu）。输出 data/status/adjudication_skip_full.json。"""
import sys, json, os
sys.path.insert(0, r"D:\workspace\PAL3Decomp")
from tools.type_evidence import exe_text_image
import capstone

data, va2off, sections = exe_text_image()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True

GAME_TOP = 0x542000          # 游戏区上界（phase3 判据）
skip = json.load(open(r"D:\workspace\PAL3Decomp\data\annotations\skip_functions.json", encoding="utf-8"))
fj = json.load(open(r"D:\workspace\PAL3Decomp\data\annotations\functions.json", encoding="utf-8"))

rows = []
TARGET_REASONS = {"between_std_methods", "crt_runtime", "trivial_accessor",
                  "thunk", "compiler_thunk", "crt_init", "std_library",
                  "compiler_generated_nop", "compiler_generated_init",
                  "compiler_global_init_seg", "compiler_float_init_seg", "non_real_function_auto"}
for addr, info in skip.items():
    if (info or {}).get("reason") not in TARGET_REASONS:
        continue
    va = int(addr, 16)
    try:
        off = va2off(va)
    except Exception:
        continue
    ins = list(md.disasm(data[off:off + 64], va))
    if not ins:
        continue
    pro = "other"
    first = ins[0]
    if first.mnemonic == "mov" and "ecx" in first.op_str:
        pro = "thiscall"
    elif first.mnemonic == "push" and "ebp" in first.op_str and len(ins) > 2 and ins[1].mnemonic == "mov" and "esp" in ins[1].op_str:
        pro = "cdecl_frame"
    elif first.mnemonic.startswith("sub") and "esp" in first.op_str:
        pro = "frame"
    gcc_aligned = any(i.mnemonic == "and" and "0xfffffff0" in i.op_str for i in ins[:4])
    # A′ 体征（深度批）：this 访问密度（thisreg 相对访存数）
    thisreg = None
    this_refs = 0
    for i in ins[:40]:
        if thisreg is None and i.mnemonic == "mov":
            parts = i.op_str.split(",")
            if len(parts) == 2 and parts[1].strip() == "ecx":
                thisreg = parts[0].strip()
        if thisreg:
            for op in i.operands:
                if op.type == capstone.x86.X86_OP_MEM:
                    for r, n in ((capstone.x86.X86_REG_EDI, "edi"),
                                 (capstone.x86.X86_REG_ESI, "esi"),
                                 (capstone.x86.X86_REG_EBX, "ebx"),
                                 (capstone.x86.X86_REG_EBP, "ebp")):
                        if op.mem.base == r and n == thisreg:
                            this_refs += 1
    game_calls = lib_calls = 0
    for i in ins:
        if i.mnemonic == "call":
            t = None
            if i.op_str.startswith("0x"):
                t = int(i.op_str, 16)
            if t is not None:
                if t < GAME_TOP:
                    game_calls += 1
                else:
                    lib_calls += 1
    rows.append({
        "addr": addr, "name": info.get("name"), "prologue": pro,
        "gcc_aligned": gcc_aligned, "this_refs": this_refs,
        "game_calls": game_calls, "lib_calls": lib_calls,
    })

from collections import Counter
vc = Counter()
for r in rows:
    if r["gcc_aligned"]:
        r["verdict"] = "third_party_gcc"
    elif r["prologue"] == "thiscall" and r["this_refs"] >= 4:
        r["verdict"] = "game_thisbody"       # 深度体征强档（this 密度）
    elif r["prologue"] == "thiscall" and r["game_calls"] >= 1:
        r["verdict"] = "game_thiscall"
    elif r["prologue"] == "thiscall":
        r["verdict"] = "game_thiscall_weak"
    elif r["this_refs"] >= 6:
        r["verdict"] = "game_thisbody_weak"  # 非 thiscall 序言但 this 密度高
    elif r["game_calls"] >= 2:
        r["verdict"] = "game_caller_edge"
    else:
        r["verdict"] = "undecided"
    vc[r["verdict"]] += 1

out = {"_meta": {"batch": "skip_between_std_methods", "count": len(rows),
                 "criteria": "D 名形→A 序言/gcc_aligned→C 调用图→verdict 分层",
                 "verdicts": dict(vc)},
       "rows": rows}
p = r"D:\workspace\PAL3Decomp\data\status\adjudication_skip_full.json"
json.dump(out, open(p, "w", encoding="utf-8"), ensure_ascii=False, indent=2)
print("批 1 裁决 %d 件:" % len(rows), dict(vc))
