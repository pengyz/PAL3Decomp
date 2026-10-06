"""判据器 v2（A′·返工版）：skip 分诊器+A 级证据通道。
【复核返工五修件】①槽行×ctor vptr 装配交叉（剔 CRT 注册表/数组/幻影 92.8% 误捕）
②raw 尾钳制（rsz——.data vsz≫rsz 越界幻影）③ctor vptr range=数据段+全形覆盖
④通道③删（死通道假象——registry 无修饰名源）⑤死输入删。
分层：A级=ctor 装配实证 vtable 槽件/待深证候选（非自动解禁）/线索档/永久 skip。"""
import sys, json, struct
sys.path.insert(0, r"D:\workspace\PAL3Decomp")
from tools.type_evidence import exe_text_image
import capstone

data, va2off, sections = exe_text_image()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True
BASE = 0x401000


def scan_ctor_vptr():
    """A 级通道②·再返工（复核③）：韧性续扫（disasm 空洞重同步）+首操作码校验。
    前版 capstone 逐窗 disasm 遇非法字节即停 ⇒ 64% 覆盖·19 真表装配点落空洞（漏 129 件）。
    修：逐指令 try-disasm（空洞跳 1 字节续扫）+ `mov [reg],imm32`/`mov reg,imm` 首操作码校验。"""
    vptr = {}
    text = sections[0]
    tstart = 4096
    tend = min(4096 + text[2], len(data))
    i = tstart
    while i < tend:
        ins_l = list(md.disasm(data[i:i + 16], BASE + (i - 4096), count=1))
        if not ins_l:
            i += 1                      # 空洞重同步（韧性续扫）
            continue
        ins = ins_l[0]
        if ins.mnemonic == 'mov' and len(ins.operands) == 2:
            op1 = ins.operands[1]
            if op1.type == capstone.x86.X86_OP_IMM:
                imm = op1.imm & 0xFFFFFFFF
                if 0x560000 <= imm < 0x620000:
                    vptr.setdefault(imm, []).append(ins.address)
        i += ins.size
    return vptr


def scan_vtable_slots(ctor_tables):
    """A 级通道①：槽行扫描×ctor 装配交叉（只认 ctor 装配实证表）。"""
    slots = {}
    for name, va, sz, raw in sections:
        if name not in ('.rdata', '.data'):
            continue
        start = raw if raw else va2off(va)
        # ②复核定性：现=文件尾钳制（非真 rsz——.data 越 raw 24KB 但幻影全被①拒·零效应实证）；
        # 真 rsz 需 section header SizeOfRawData（exe_text_image 未导出）——挂账
        end = min(start + sz, len(data) - 4)
        run = []
        for off in range(start, end, 4):
            val = struct.unpack_from('<I', data, off)[0]
            if 0x401000 <= val < 0x55F000:
                run.append((off, val))
            else:
                if len(run) >= 3:
                    tva = va + (run[0][0] - start)
                    if tva in ctor_tables:             # ①ctor 装配交叉
                        for i, (o, v) in enumerate(run):
                            slots.setdefault(v, []).append((tva, i))
                run = []
        if len(run) >= 3:
            tva = va + (run[0][0] - start)
            if tva in ctor_tables:
                for i, (o, v) in enumerate(run):
                    slots.setdefault(v, []).append((tva, i))
    return slots


def main():
    skip = json.load(open(r"D:\workspace\PAL3Decomp\data\annotations\skip_functions.json", encoding="utf-8"))
    adj = json.load(open(r"D:\workspace\PAL3Decomp\data\status\adjudication_skip_full.json", encoding="utf-8"))

    print("扫描 A 级通道（返工版）...")
    vptrs = scan_ctor_vptr()
    print("  ctor vptr 装配：%d 表（capstone 全形）" % len(vptrs))
    vslots = scan_vtable_slots(set(vptrs.keys()))
    print("  vtable 槽（×ctor 交叉）：%d 函数入槽" % len(vslots))

    out = []
    tiers = {"a_level_candidate": 0, "clue_only": 0, "permanent_skip": 0}
    for r in adj.get("rows", []):
        va = int(r["addr"], 16)
        if r["addr"] not in skip:
            continue
        a_evidence = []
        if va in vslots:
            # own-head 标签（复核⑤：合并链前版 8/46 错表——取 run 首表头）
            _own = min(vslots[va], key=lambda x: x[1])
            a_evidence.append("vtable_slot@%s" % hex(_own[0]))
        if r.get("gcc_aligned"):
            tier = "permanent_skip"
        elif a_evidence:
            tier = "a_level_candidate"
        else:
            tier = "clue_only"
        tiers[tier] += 1
        out.append({"addr": r["addr"], "verdict_v1": r.get("verdict"), "tier": tier,
                    "a_evidence": a_evidence,
                    "clues": {"prologue": r.get("prologue"), "this_refs": r.get("this_refs"),
                              "game_calls": r.get("game_calls"), "lib_calls": r.get("lib_calls")}})
    json.dump({"_meta": {"tiers": tiers, "ctor_tables": len(vptrs), "vtable_funcs": len(vslots),
                         "design": "A′ 返工版（复核五修件）：ctor 装配实证×槽行交叉·raw 尾钳制"},
               "rows": out},
              open(r"D:\workspace\PAL3Decomp\data\status\adjudication_v2.json", "w", encoding="utf-8"),
              ensure_ascii=False, indent=2)
    print("分层：%s" % tiers)


if __name__ == "__main__":
    main()
