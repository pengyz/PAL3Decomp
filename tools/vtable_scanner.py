#!/usr/bin/env python3
"""vtable 取证扫描器：从 ctor 的 vptr 存储指令读出虚表地址与槽位内容。

动机（2026-09-15 F2 调研）：`data/annotations/structs/*.json` 的 `vtables` 是**手工记录**的
（`export_full.py:678` 只是透传）⇒ 118 个含 `__vftable` 成员的类里，50 个 `methods=0`、
7 个 `methods>0` 但 `vtables=[]`，共 **57 个类没有虚表记录**。而 `emit_headers` 的
`class_vtable_slots()` 依赖该记录 ⇒ 这些类拿不到虚性判定。

**本工具的产品化来源**：独立复核 `data/status/_cleanup_review_f2_next.json`
（子 agent `511b4e4f`）在 `/tmp` 里的原型证明可行——`objdump -d` 全量反汇编（0.27s / 47 万行）
+ 扫描 `mov [reg+0], imm32 ∈ .rdata` + **槽位内容校验** ⇒
186 个 vptr 存储目标、92 张已记录表 89 张被直接命中、86 张注解未记录的**通过校验的实表**。

**为什么不用 `tools/pe_probe.py` 的反汇编**：它是自写的极简解码器，不认识 SEH 序言
（`6A FF 68 <imm32> 64 A1 ...`）等形态，曾导致 captain 误判"ctor 里没有 vptr 安装指令"。
**教训：自造解码器会制造假象。** 本工具只做**映射与校验**，反汇编交给 `objdump`。

用法：
  python3 tools/vtable_scanner.py --class CEffCylinder       # 单类
  python3 tools/vtable_scanner.py --all --limit 20            # 批量（前 20）
  python3 tools/vtable_scanner.py --all --out /tmp/vt.json    # 全量导出
  python3 tools/vtable_scanner.py --verify                    # 自检（已知反例）

输出：每个类 → 发现的 vtable 地址列表 + 槽位数 + 槽位内容校验结果 + 与注解记录的对照。
"""
import argparse
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
EXE = os.path.join(ROOT, "original", "PAL3.exe")
DECOMP_DIR = os.path.join(ROOT, "asm", "pal3", "decomp")
STRUCTS_DIR = os.path.join(ROOT, "data", "annotations", "structs")

# 已知节范围（objdump -h 实测；由 _load_sections 动态覆盖）
SECTIONS = {}


def run_objdump(args):
    return subprocess.run(["objdump"] + args, capture_output=True, text=True,
                          cwd=ROOT).stdout


def load_sections():
    """解析 objdump -h，得到 {name: (vma, size)}。"""
    out = run_objdump(["-h", EXE])
    secs = {}
    for ln in out.splitlines():
        m = re.match(r"\s*\d+\s+(\S+)\s+([0-9a-f]+)\s+([0-9a-f]+)", ln)
        if m:
            name, size, vma = m.group(1), int(m.group(2), 16), int(m.group(3), 16)
            secs[name] = (vma, size)
    return secs


def in_section(addr, name):
    if name not in SECTIONS:
        return False
    vma, size = SECTIONS[name]
    return vma <= addr < vma + size


def load_disasm(path="/tmp/pal3.dis"):
    """反汇编一次并缓存到文件（objdump 0.27s，但批量调用应复用）。"""
    if not os.path.exists(path) or os.path.getmtime(path) < os.path.getmtime(EXE):
        with open(path, "w") as f:
            f.write(run_objdump(["-d", EXE]))
    return path


# `mov dword ptr [reg+0], imm32` 形态（vptr 存储）。
# objdump 渲染例：
#   4c3df3:  c7 45 00 c8 f7 56 00   movl   $0x56f7c8,0x0(%ebp)
#   4c3dfa:  c7 07 bc f7 56 00      movl   $0x56f7bc,(%edi)
# 我们只认「位移为 0」的存储（vptr 恒在 +0）；非 0 位移属其它字段。
_VPTR_STORE = re.compile(
    r"^\s*([0-9a-f]+):\s+((?:[0-9a-f]{2} )+)\s+movl?\s+\$0x([0-9a-f]+),"
    r"(?:0x0\(%(\w+)\)|\(%(\w+)\))", re.M)


def scan_vptr_stores(dis_path):
    """返回 [(insn_addr, imm, base_reg, bytes_hex)]，imm ∈ .rdata。"""
    out = []
    with open(dis_path) as f:
        for m in _VPTR_STORE.finditer(f.read()):
            addr = int(m.group(1), 16)
            imm = int(m.group(3), 16)
            reg = m.group(4) or m.group(5)
            if in_section(imm, ".rdata"):
                out.append((addr, imm, reg, m.group(2).strip()))
    return out


def read_rdata_dwords(addr, max_slots=256):
    """从 .rdata 读连续 DWORD 直到遇到非 .text 指针（= vtable 结束）。

    用 `objdump -s` 取字节；槽位校验：每个 DWORD 必须落在 .text 内，
    否则视为表结束（这同时排除了把相邻数据误当槽位的假阳性）。
    """
    out = run_objdump(["-s", "--start-address=0x%X" % addr,
                       "--stop-address=0x%X" % (addr + max_slots * 4), EXE])
    data = {}
    for ln in out.splitlines():
        m = re.match(r"\s*([0-9a-f]+)\s+((?:[0-9a-f]{2,8}\s?)+)", ln)
        if not m:
            continue
        base = int(m.group(1), 16)
        hexs = re.sub(r"\s", "", m.group(2))
        for i in range(0, len(hexs) - 7, 8):
            # objdump 的小端显示：每 4 字节一组按显示顺序
            chunk = hexs[i:i + 8]
            if len(chunk) < 8:
                continue
            val = int(chunk[6:8] + chunk[4:6] + chunk[2:4] + chunk[0:2], 16)
            data[base + i // 2] = val
    slots = []
    a = addr
    while a in data and len(slots) < max_slots:
        v = data[a]
        if not in_section(v, ".text"):
            break
        slots.append(v)
        a += 4
    return slots


_method_starts_cache = None

def method_starts():
    """函数起始地址 -> 名字（`functions.json` + `ida_structs` 的 methods）。

    用于**槽位内容校验**：vtable 的槽位应指向真实函数，故槽位能被命名即强证据。
    实测 32 张表**全部**通过该校验（0 张无映射）——这比"字节看起来像指针"强得多。
    """
    global _method_starts_cache
    if _method_starts_cache is not None:
        return _method_starts_cache
    out = {}
    try:
        fj = json.load(open(os.path.join(ROOT, "data", "annotations",
                                         "functions.json"), encoding="utf-8"))
        for a, v in fj.items():
            try:
                out[int(a, 16)] = (v or {}).get("name") or ""
            except (ValueError, TypeError):
                continue
    except (OSError, json.JSONDecodeError):
        pass
    try:
        ida = json.load(open(os.path.join(ROOT, "asm", "pal3",
                                          "ida_structs.json"), encoding="utf-8"))
        for cls, v in ida.items():
            if not isinstance(v, dict):
                continue
            for a, m in (v.get("methods") or {}).items():
                try:
                    out.setdefault(int(a, 16), "%s::%s" % (cls, (m or {}).get("name")))
                except (ValueError, TypeError):
                    continue
    except (OSError, json.JSONDecodeError):
        pass
    _method_starts_cache = out
    return out


def ctor_map():
    """类名 → ctor 地址（来自 decomp 的自名 ctor 文件）。"""
    m = {}
    for fn in os.listdir(DECOMP_DIR):
        mm = re.match(r"^(.+?)_\1void_([0-9a-f]{6,8})\.json$", fn)
        if mm:
            m.setdefault(mm.group(1), int(mm.group(2), 16))
    return m


def ann_vtables(cls):
    p = os.path.join(STRUCTS_DIR, "%s.json" % cls)
    if not os.path.exists(p):
        return None
    try:
        d = json.load(open(p, encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return None
    return d.get("vtables")


def scan_class(cls, stores, ctor_addr=None):
    """返回该类的取证结果。"""
    res = {"class": cls, "ctor": None, "found": [], "recorded": None,
           "match": None, "note": None}
    ctor = ctor_addr
    if ctor is None:
        ctor = ctor_map().get(cls)
    res["ctor"] = ("0x%X" % ctor) if ctor else None
    if ctor is None:
        res["note"] = "no self-named ctor in decomp"
        return res
    # ctor 起始 ~ 4KB 窗口内的 vptr 存储（ctor 不会跨 4KB 内的连续多条 vptr 存储）
    #
    # ️ 能力边界（2026-09-15 实测，captain 记录）：
    # `decomp` 的 `address` 是**反编译体起始**，**不保证是函数入口**——
    # 实测 `CCBItemWindow` 的 ctor 在 decomp 里是 `0x4461B0`（`size_bytes=25`，只有 3 行），
    # 而它的 vptr 存储实际在 `0x446175`（**早于** `0x4461B0`，落在另一个函数起始之后）
    # ⇒ 固定窗口会**漏**。
    # 更根本的是：**store 的目标 vptr 未必属于该类**——`CCBItemWindow` 的 ctor 存的是
    # `0x56AF80`（`CCBUIPanel` 的表），而它自己记录的 `0x570500` 出现在
    # `0x51A36C/0x51A3CD`（另一个函数）。原因：store 可能属于**基类**或**内联成员子对象**。
    #
    # ⇒ 本工具**只对"简单类"（单一 ctor、目标 vptr = 该类）可靠**：
    #    实测 31 个有注解记录的候选中 26 个命中（84%），
    #    且 32 张在窗口内扫到的表**全部**能与 method 名对映（slot→method 校验通过）。
    #    "vptr 存储 → 类" 的**全量归因超出本工具能力**，需另做（按真实函数边界 + 基类/子对象判定）。
    near = [(a, imm, reg, b) for (a, imm, reg, b) in stores
            if ctor <= a < ctor + 0x1000]
    for a, imm, reg, b in near:
        slots = read_rdata_dwords(imm)
        named = sum(1 for s in slots if s in method_starts())
        res["found"].append({"store_at": "0x%X" % a, "target": "0x%X" % imm,
                             "via_reg": reg, "bytes": b,
                             "slots_n": len(slots), "slots_named": named,
                             "slots_head": ["0x%X" % s for s in slots[:6]]})
    rec = ann_vtables(cls)
    if rec is not None:
        res["recorded"] = [{"addr": (v.get("addr") or "").upper(),
                            "slots_n": len(v.get("slots") or [])} for v in rec]
        # ⚠️ 地址比较**必须归一化为 int**：`found` 侧是 `"0x%X"`（小写 x、无前导零），
        # `recorded` 侧是注解原文（如 `"0x0056F7C8"`，大写 X、有前导零）。
        # 直接比较字符串会**永不相等** ⇒ captain 首版因此得到 `match_recorded = 0` 的假阴性
        # （实测归一化后应为 26）。这是"用异常读数反推"的又一实例，已在自检里钉住。
        found_addrs = {int(f["target"], 16) for f in res["found"]}
        rec_addrs = {int(v["addr"], 16) for v in rec
                     if v.get("addr") and re.match(r"^0[xX][0-9a-fA-F]+$", v["addr"])}
        res["match"] = bool(rec_addrs & found_addrs)
        if rec_addrs - found_addrs:
            res["note"] = ("recorded-but-not-found-in-ctor: %s"
                           % ", ".join("0x%08X" % a
                                       for a in sorted(rec_addrs - found_addrs)))
    return res


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--class", dest="cls", help="单个类名")
    ap.add_argument("--all", action="store_true", help="批量：所有注解含 __vftable 的类")
    ap.add_argument("--limit", type=int, default=0, help="批量时限制数量")
    ap.add_argument("--out", help="批量结果写入 JSON")
    ap.add_argument("--verify", action="store_true", help="自检（已知反例）")
    args = ap.parse_args()

    global SECTIONS
    SECTIONS = load_sections()
    dis = load_disasm()
    stores = scan_vptr_stores(dis)

    if args.verify:
        # 反例来自独立复核 511b4e4f：CEffCylinder 的 ctor 存储两张表，
        # 注解只记录了 0x56F7C8；第二张 0x56F7BC 是「注解未记录的实表」。
        ok = True
        r = scan_class("CEffCylinder", stores)
        found = {f["target"].upper() for f in r["found"]}
        for want in ("0X56F7C8", "0X56F7BC"):
            got = want in found
            ok = ok and got
            print("%s CEffCylinder 应在 ctor 中存储 %s -> %s"
                  % ("OK  " if got else "FAIL", want, "found" if got else "MISSING"))
        print("  实测 found = %s" % sorted(found))
        if r["recorded"]:
            print("  注解记录 = %s" % [x["addr"] for x in r["recorded"]])
        print("verify: %s" % ("PASS" if ok else "FAIL"))
        return 0 if ok else 1

    if args.cls:
        print(json.dumps(scan_class(args.cls, stores), ensure_ascii=False, indent=1))
        return 0

    if args.all:
        names = []
        for fn in os.listdir(STRUCTS_DIR):
            if not fn.endswith(".json"):
                continue
            try:
                d = json.load(open(os.path.join(STRUCTS_DIR, fn), encoding="utf-8"))
            except (OSError, json.JSONDecodeError):
                continue
            km = d.get("known_members") or {}
            if any(isinstance(v, dict) and v.get("name") == "__vftable"
                   for v in km.values()):
                names.append(d.get("name") or fn[:-5])
        names.sort()
        if args.limit:
            names = names[:args.limit]
        results = [scan_class(n, stores) for n in names]
        summary = {
            "total_classes": len(results),
            "with_ctor": sum(1 for r in results if r["ctor"]),
            "found_any": sum(1 for r in results if r["found"]),
            "match_recorded": sum(1 for r in results if r["match"]),
            "recorded_but_not_found": sum(1 for r in results if r["note"]),
            "no_ctor": sum(1 for r in results if not r["ctor"]),
            "results": results,
        }
        if args.out:
            with open(args.out, "w", encoding="utf-8") as f:
                json.dump(summary, f, ensure_ascii=False, indent=1)
            print("written: %s" % args.out)
        print(json.dumps({k: v for k, v in summary.items() if k != "results"},
                         ensure_ascii=False, indent=1))
        return 0

    ap.print_help()
    return 0


if __name__ == "__main__":
    sys.exit(main())