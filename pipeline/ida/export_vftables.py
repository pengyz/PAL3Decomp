"""从 IDB 导出 **IDA 自己划定的 vtable 结构**（只读，不修改 IDB）。

## 为什么必须从 IDB 取

`pipeline/ida/export_full.py:50-52` 已写明：`ida_structs.json` 的 `vtables` 与注解
**逐字段等值**（761/761）⇒ **它们是"注解的复制"，不是 IDB 状态的证据**。
而离线工具（`vtable_scanner.py`/`vtable_compare.py`）用启发式边界，
在多继承连续子表下失效（实测 CEffShock 的表被读出 28/43 槽，混进 RenderTarget2::*）。

**IDA 为每个 vftable 建了一个 UDT**（`idaapi.get_tinfo(ea)` 可取出条目与条目数）
⇒ 本脚本导出它，这才是 A 级证据。

## 用法
    idat -A -S"pipeline/ida/export_vftables.py" original/PAL3.exe.i64
只读；输出 pipeline/ida/_logs/vftables.json（gitignore ⇒ 入库需复制到 data/status/）。
"""
import json, os, re, traceback
import idaapi, idautils, idc, ida_typeinf

idaapi.auto_wait()
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
os.makedirs(LOG_DIR, exist_ok=True)
OUT = os.path.join(LOG_DIR, "vftables.json")
ERR = os.path.join(LOG_DIR, "vftables_error.txt")


def main():
    til = ida_typeinf.get_idati()
    # 直接枚举 ??_7 符号（vftable 符号名约定）
    vt_ea = []
    for ea, name in idautils.Names():
        if name and name.startswith('??_7'):
            vt_ea.append((ea, name))
    print("[export_vftables] ??_7 symbols: %d" % len(vt_ea))

    rows = []
    for ea, name in vt_ea:
        row = {"ea": ea, "ea_hex": "0x%08X" % ea, "sym": name}
        # IDA 为该 ea 建的 UDT（权威：条目数 + 条目）
        ti = ida_typeinf.tinfo_t()
        got = False
        try:
            got = idaapi.get_tinfo(ti, ea)
        except Exception:
            got = False
        if got and ti.is_udt():
            udt = ida_typeinf.udt_type_data_t()
            if ti.get_udt_details(udt):
                ents = [{"offset": m.offset, "name": m.name, "size": m.size}
                        for m in udt]
                row["udt_name"] = (ti.get_type_name() or "")
                row["n_entries"] = len(ents)
                row["total_size"] = udt.total_size
                row["entries"] = ents
                row["source"] = "ida_udt"
        if "n_entries" not in row:
            row["source"] = "no_udt"
        # 原始 DWORD（供交叉验证，不用于判边界）
        seg_end = idc.get_segm_end(ea)
        dws = []
        a = ea
        while a + 4 <= seg_end and len(dws) < 128:
            dws.append(idc.get_wide_dword(a)); a += 4
        row["raw_head"] = ["0x%08X" % v for v in dws[:48]]
        rows.append(row)

    with open(OUT, "w", encoding="utf-8") as f:
        json.dump({"count": len(rows), "rows": rows}, f, ensure_ascii=False, indent=1)
    n_udt = sum(1 for r in rows if r.get("source") == "ida_udt")
    print("[export_vftables] wrote %s (%d rows, %d with ida_udt)" % (OUT, len(rows), n_udt))


try:
    main()
except Exception:
    with open(ERR, "w", encoding="utf-8") as f:
        f.write(traceback.format_exc())
    print("[export_vftables] EXCEPTION -> %s" % ERR)
    idc.qexit(3)
idc.qexit(0)
