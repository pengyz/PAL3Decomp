"""
IDAPython: 增量导出 — 只重新反编译类型变化的函数。

对比已有 decomp JSON 的签名与当前 IDB 的签名：
- 签名不同 → 重新反编译
- 签名相同 → 跳过

节省：大部分迭代只修改几十个 struct/签名，影响 <500 个函数。

用法:
  idat -A -S"tools/ida/pal3_export_incremental.py" original/PAL3.exe.91.i64
"""

import ida_auto
import ida_funcs
import ida_hexrays
import ida_name
import ida_typeinf
import idautils
import idc
import json
import os
import re
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
DECOMP_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")


def get_func_sig(ea):
    """获取函数当前签名字符串"""
    tinfo = ida_typeinf.tinfo_t()
    if ida_typeinf.guess_tinfo(tinfo, ea):
        return str(tinfo)
    return ""


def sanitize_filename(name, addr):
    """生成安全文件名"""
    clean = re.sub(r'[^a-zA-Z0-9_]', '_', name)
    if len(clean) > 60:
        clean = clean[:60]
    return "%s_%08x" % (clean, addr)


def export_incremental():
    ida_auto.auto_wait()

    os.makedirs(DECOMP_DIR, exist_ok=True)

    # 建立已有 decomp 文件的索引: addr → (filename, old_sig)
    existing = {}
    for fname in os.listdir(DECOMP_DIR):
        if not fname.endswith('.json'):
            continue
        # 从文件名提取地址
        m = re.search(r'_([0-9a-f]{8})\.json$', fname)
        if m:
            addr = int(m.group(1), 16)
            fpath = os.path.join(DECOMP_DIR, fname)
            try:
                d = json.load(open(fpath))
                existing[addr] = (fpath, d.get('signature', ''))
            except:
                existing[addr] = (fpath, '')

    # 扫描所有函数，对比签名
    total = 0
    skipped = 0
    updated = 0
    new_funcs = 0

    text_start = 0x00401000
    text_end = 0x005695D0

    for ea in idautils.Functions(text_start, text_end):
        func = ida_funcs.get_func(ea)
        if not func or func.size() <= 1:
            continue

        name = ida_name.get_name(ea) or ""
        if not name:
            continue

        total += 1
        cur_sig = get_func_sig(ea)

        if ea in existing:
            old_path, old_sig = existing[ea]
            if cur_sig == old_sig:
                skipped += 1
                continue
            # 签名变化，需要重新反编译
            out_path = old_path
        else:
            # 新函数
            fname = sanitize_filename(name, ea) + ".json"
            out_path = os.path.join(DECOMP_DIR, fname)
            new_funcs += 1

        # 反编译
        try:
            cfunc = ida_hexrays.decompile(ea)
            if cfunc:
                data = {
                    "name": name,
                    "mangled_name": name,
                    "address": "0x%08X" % ea,
                    "size_bytes": func.size(),
                    "signature": cur_sig,
                    "decompiled_c": str(cfunc),
                }
                with open(out_path, "w", encoding="utf-8") as f:
                    json.dump(data, f, indent=2, ensure_ascii=False)
                updated += 1
        except:
            pass

    print("[*] Incremental export: total=%d, skipped=%d, updated=%d, new=%d"
          % (total, skipped, updated, new_funcs))
    idc.qexit(0)


if __name__ == "__main__":
    export_incremental()
