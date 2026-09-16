"""导出 IDA 的**函数边界**（起始/结束/名字）——只读，不修改 IDB。

## 为什么需要它

"表 → 类"映射（把 0x56xxxx 的 vtable 归属到类）需要**可靠的函数归属**：
给定一条 `movl $0x56F62C,(%esi)` 指令地址，要判断它属于哪个函数。

本会话尝试了 **6 种离线口径，全部失败**（见
`docs/specs/2026-09-15-f2-supply-checklist.md` §6.1），根因是
**`asm/pal3/decomp/*.json` 的 `address` 不是可靠函数入口**：
实测 `CCBItemWindow` 的 `decomp.address=0x4461B0` **高于**其 vptr 存储 `0x446175`。

**函数边界是 IDA auto-analysis 的职责**，用 `objdump` + Python 无法重建
⇒ 必须从 IDB 导出（这正是不该舍近求远的原因）。

## 用法

    idat -A -S"pipeline/ida/export_func_bounds.py" original/PAL3.exe.i64

**只读**：不调用 `save_database`；结果写 `pipeline/ida/_logs/func_bounds.json`。
"""
import idaapi
import idautils
import ida_funcs
import idc
import json
import os

idaapi.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
os.makedirs(LOG_DIR, exist_ok=True)
OUT = os.path.join(LOG_DIR, "func_bounds.json")

rows = []
for ea in idautils.Functions():
    f = ida_funcs.get_func(ea)
    if not f:
        continue
    rows.append({
        "start": f.start_ea,
        "end": f.end_ea,
        "name": idc.get_func_name(f.start_ea) or "",
        # 是否被 IDA 标为 thunk / 库函数（便于后续过滤）
        "flags": int(f.flags),
        "lib": bool(f.flags & ida_funcs.FUNC_LIB),
        "thunk": bool(f.flags & ida_funcs.FUNC_THUNK),
    })

# 同时导出 vptr 写指令的归属（直接给出答案，省一次离线重算）
VPTR_SITES = []
import ida_bytes
import ida_ua
pat = None
# 扫描 .text 里 movl $imm32,(%reg) / movl $imm32,disp(%reg) 且 imm 落在 .rdata
text_seg = None
for s in idautils.Segments():
    nm = idc.get_segm_name(s)
    if nm == ".text":
        text_seg = (s, idc.get_segm_end(s))
        break

if text_seg:
    lo, hi = text_seg
    ea = lo
    while ea < hi:
        insn = ida_ua.insn_t()
        n = ida_ua.decode_insn(insn, ea)
        if n > 0 and insn.itype == idaapi.NN_mov:
            # 形态：`mov [mem], imm32`
            # ⚠️ 首版把内存操作数判为 `o_displ`，**漏掉了绝大多数**：
            # 实测只抓到 80/467 条（objdump 侧 467 条）。
            # `o_mem`（绝对地址，如 `movl $imm,(%esi)` 经 IDA 归一化）与
            # `o_displ`（含位移）**都要接受**；只要求"首个操作数是内存、第二个是立即数"。
            o0, o1 = insn.ops[0], insn.ops[1]
            if (o0.type in (ida_ua.o_mem, ida_ua.o_displ, ida_ua.o_phrase)
                    and o1.type == ida_ua.o_imm):
                imm = o1.value
                if 0x56A000 <= imm < 0x580000:
                    fn = ida_funcs.get_func(ea)
                    VPTR_SITES.append({
                        "insn": ea,
                        "table": imm,
                        "func_start": fn.start_ea if fn else 0,
                        "func_name": idc.get_func_name(fn.start_ea) if fn else "",
                    })
        ea += max(n, 1)

data = {"funcs": rows, "vptr_sites": VPTR_SITES,
        "counts": {"funcs": len(rows), "vptr_sites": len(VPTR_SITES)}}
with open(OUT, "w", encoding="utf-8") as f:
    json.dump(data, f, ensure_ascii=False, indent=1)
print("[export_func_bounds] funcs=%d vptr_sites=%d -> %s"
      % (len(rows), len(VPTR_SITES), OUT))
idc.qexit(0)