"""
IDAPython: 查询 _todo_ 字段的 xref 和语义上下文。

从 annotations 中加载所有 _todo_ 字段，对每个字段：
1. 找到该类所有方法
2. 在方法的反汇编中搜索 [reg+offset] 访问
3. 提取上下文（函数名、指令、访问模式）
4. 输出 JSON 供后续命名使用

用法:
  idat.exe -A -S"pipeline/ida/query_todo_fields.py" original/PAL3.exe.i64
"""
import ida_auto, ida_bytes, ida_funcs, ida_name, ida_ua, ida_idp
import ida_hexrays, ida_typeinf
import idautils, idc
import json, os, re, struct

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT_FILE = os.path.join(LOG_DIR, "todo_field_context.json")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0


def load_todo_fields():
    """加载所有 _todo_ 字段，按类分组。"""
    structs_dir = os.path.join(ANNOTATIONS_DIR, "structs")
    result = {}
    for fname in os.listdir(structs_dir):
        if not fname.endswith(".json"):
            continue
        with open(os.path.join(structs_dir, fname), "r", encoding="utf-8") as f:
            sdata = json.load(f)
        sname = sdata.get("name", fname.replace(".json", ""))
        todos = {}
        for off_str, m in sdata.get("known_members", {}).items():
            if m["name"].startswith("_todo_") or m["name"].startswith("_field_"):
                todos[int(off_str)] = m
        if todos:
            result[sname] = {
                "binary_size": sdata.get("binary_size"),
                "fields": todos,
            }
    return result


def load_class_methods():
    """从 annotations 加载每个类的方法列表。

    读取两个来源：
    - structs/*.json 的 methods（主要来源）
    - functions.json 中带 ClassName:: 前缀的条目（补充来源）
    """
    from collections import defaultdict
    class_methods = defaultdict(list)

    # 来源 1: struct JSON methods
    structs_dir = os.path.join(ANNOTATIONS_DIR, "structs")
    for fname in os.listdir(structs_dir):
        if not fname.endswith(".json"):
            continue
        with open(os.path.join(structs_dir, fname), "r", encoding="utf-8") as f:
            sdata = json.load(f)
        sname = sdata.get("name", fname.replace(".json", ""))
        for addr_str, minfo in sdata.get("methods", {}).items():
            mname = minfo.get("name", "")
            method_short = mname.split("::")[-1] if "::" in mname else mname
            ea = int(addr_str, 16)
            class_methods[sname].append((ea, method_short))

    # 来源 2: functions.json（补充不在 struct JSON 中的条目）
    funcs_path = os.path.join(ANNOTATIONS_DIR, "functions.json")
    if os.path.exists(funcs_path):
        with open(funcs_path, "r", encoding="utf-8") as f:
            funcs = json.load(f)
        existing = {ea for list_ in class_methods.values() for ea, _ in list_}
        for addr_str, info in funcs.items():
            name = info.get("name", "")
            if "::" not in name:
                continue
            cls = name.split("::")[0]
            method = name.split("::", 1)[1]
            ea = int(addr_str, 16)
            if ea not in existing:
                class_methods[cls].append((ea, method))

    return dict(class_methods)


def find_disp32_in_func(ea, func_size, target_offsets):
    """在函数体中搜索 [reg+disp32] 访问指定偏移的指令。"""
    hits = {}
    binary = ida_bytes.get_bytes(ea, func_size)
    if not binary:
        return hits

    for offset in target_offsets:
        needle = struct.pack("<I", offset)
        pos = 0
        while pos < len(binary):
            idx = binary.find(needle, pos)
            if idx == -1:
                break
            # Check ModRM: preceding byte should have mod=10 (register+disp32)
            if idx >= 2:
                modrm = binary[idx - 1]
                opcode = binary[idx - 2]
                mod = (modrm >> 6) & 3
                rm = modrm & 7
                nnn = (modrm >> 3) & 7

                if mod == 2 and rm != 4:  # mod=10, not SIB
                    # Get disassembly from IDA for proper context
                    insn_ea = ea + idx - 2
                    disasm = idc.GetDisasm(insn_ea)

                    # Determine access type from opcode
                    access = "unknown"
                    width = 4
                    if opcode in (0x8B, 0x8D):
                        access = "load" if opcode == 0x8B else "lea"
                    elif opcode == 0x89:
                        access = "store"
                    elif opcode == 0xD9:
                        access = "fld"
                        width = 4
                    elif opcode == 0xDD:
                        access = "fld_double"
                        width = 8
                    elif opcode == 0xC6:
                        access = "store_byte"
                        width = 1
                    elif opcode == 0xC7:
                        access = "store_imm"
                    elif opcode == 0x3B:
                        access = "cmp"

                    # Check for 66 prefix (word access)
                    if idx >= 3 and binary[idx - 3] == 0x66:
                        width = 2
                    # Check for 0F B6/B7 (movzx byte/word)
                    if idx >= 3 and binary[idx - 3] == 0x0F:
                        if opcode == 0xB6:
                            access = "movzx_byte"
                            width = 1
                        elif opcode == 0xB7:
                            access = "movzx_word"
                            width = 2

                    regs = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"]

                    if offset not in hits:
                        hits[offset] = []
                    hits[offset].append({
                        "va": "0x%08X" % insn_ea,
                        "access": access,
                        "width": width,
                        "base_reg": regs[rm],
                        "disasm": disasm[:80] if disasm else "",
                    })
            pos = idx + 1
    return hits


def try_decompile_context(ea, offset):
    """尝试反编译函数并提取 _todo_ 字段使用的代码行。"""
    try:
        cfunc = ida_hexrays.decompile(ea)
        if not cfunc:
            return []
        code = str(cfunc)
        lines = []
        for line in code.split("\n"):
            # Look for references to the offset in various patterns
            patterns = [
                "_todo_%X" % offset,
                "_field_%X" % offset,
                "this + %d)" % offset,
                "this + %d)" % (offset + 1),  # byte within dword
            ]
            for pat in patterns:
                if pat.lower() in line.lower():
                    lines.append(line.strip()[:120])
                    break
        return lines[:5]  # max 5 lines per function
    except:
        return []


def main():
    ida_auto.auto_wait()
    print("[*] Query _todo_ field context")

    todo_fields = load_todo_fields()
    class_methods = load_class_methods()

    total_classes = len(todo_fields)
    total_fields = sum(len(v["fields"]) for v in todo_fields.values())
    print("[*] %d classes, %d _todo_ fields" % (total_classes, total_fields))

    results = {}
    processed = 0

    for cls_name, cls_info in sorted(todo_fields.items()):
        fields = cls_info["fields"]
        methods = class_methods.get(cls_name, [])

        if not methods:
            continue

        target_offsets = list(fields.keys())
        cls_results = {}

        for ea, method_name in methods:
            func = ida_funcs.get_func(ea)
            if not func:
                continue
            func_size = func.size()

            # Search for disp32 references to _todo_ offsets
            hits = find_disp32_in_func(ea, func_size, target_offsets)

            for offset, access_list in hits.items():
                if offset not in cls_results:
                    cls_results[offset] = {
                        "hex": "0x%X" % offset,
                        "type": fields[offset]["type"],
                        "refs": [],
                    }
                for a in access_list:
                    cls_results[offset]["refs"].append({
                        "method": method_name,
                        "va": a["va"],
                        "access": a["access"],
                        "width": a["width"],
                        "base_reg": a["base_reg"],
                        "disasm": a["disasm"],
                    })

        # Also try decompile context for high-value fields (3+ refs)
        for offset, info in cls_results.items():
            if len(info["refs"]) >= 3:
                # Get unique methods
                seen_methods = set()
                for ref in info["refs"]:
                    if ref["method"] not in seen_methods:
                        seen_methods.add(ref["method"])
                        method_ea = None
                        for ea, mn in methods:
                            if mn == ref["method"]:
                                method_ea = ea
                                break
                        if method_ea:
                            decomp_lines = try_decompile_context(method_ea, offset)
                            if decomp_lines:
                                info.setdefault("decomp_context", []).extend(
                                    [{"method": ref["method"], "line": l} for l in decomp_lines]
                                )
                    if len(seen_methods) >= 3:
                        break

        if cls_results:
            results[cls_name] = cls_results
            processed += 1
            if processed % 10 == 0:
                print("  [%d/%d classes]" % (processed, total_classes))

    # Save results
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    # Summary
    total_refs = sum(
        sum(len(finfo["refs"]) for finfo in cls.values())
        for cls in results.values()
    )
    fields_with_refs = sum(
        len(cls) for cls in results.values()
    )
    print("[*] Done: %d classes, %d fields with refs, %d total refs" % (
        len(results), fields_with_refs, total_refs))
    print("[*] Output: %s" % OUTPUT_FILE)

    idc.qexit(0)


if __name__ == "__main__":
    main()
