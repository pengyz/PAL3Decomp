"""
IDAPython: 查询 struct 的所有字段访问（包括 gap 中未标注的偏移）。

不仅扫描 _todo_ 字段，还扫描 struct 整个偏移空间中被二进制访问但未标注的偏移。
这是 query_todo_fields.py 的完整版本，覆盖"真正的工作量"。

输出: pipeline/ida/_logs/all_field_discovery.json
结构: {ClassName: {offset_str: {type, refs, source: "known"|"gap_discovery"}}}

用法:
  idat.exe -A -S"pipeline/ida/query_all_fields.py ClassName1,ClassName2" original/PAL3.exe.i64
  idat.exe -A -S"pipeline/ida/query_all_fields.py --top20" original/PAL3.exe.i64
"""
import ida_auto, ida_bytes, ida_funcs, ida_name
import ida_hexrays, ida_typeinf
import idautils, idc
import json, os, re, struct, sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT_FILE = os.path.join(LOG_DIR, "all_field_discovery.json")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0


def load_struct_info(target_classes=None):
    """Load struct annotations. If target_classes specified, only load those."""
    structs_dir = os.path.join(ANNOTATIONS_DIR, "structs")
    result = {}
    for fname in os.listdir(structs_dir):
        if not fname.endswith(".json"):
            continue
        sname = fname.replace(".json", "")
        if target_classes and sname not in target_classes:
            continue
        with open(os.path.join(structs_dir, fname), "r", encoding="utf-8") as f:
            sdata = json.load(f)
        bs = sdata.get("binary_size", 0)
        base_size = sdata.get("base_size", 0)
        if bs < 100 or bs > 50000:
            continue
        known = set(int(o) for o in sdata.get("known_members", {}).keys())
        result[sname] = {
            "binary_size": bs,
            "base_size": base_size or 0,
            "known_offsets": known,
            "known_members": sdata.get("known_members", {}),
        }
    return result


def load_class_methods():
    """Load function annotations grouped by class."""
    funcs_path = os.path.join(ANNOTATIONS_DIR, "functions.json")
    with open(funcs_path, "r", encoding="utf-8") as f:
        funcs = json.load(f)
    class_methods = {}
    for addr_str, info in funcs.items():
        name = info.get("name", "")
        if "::" not in name or name.startswith("_misattrib"):
            continue
        cls = name.split("::")[0]
        ea = int(addr_str, 16)
        if cls not in class_methods:
            class_methods[cls] = []
        class_methods[cls].append(ea)
    return class_methods


def scan_func_for_offsets(ea, min_off, max_off):
    """Scan function binary for ALL [reg+disp32] where disp32 is in [min_off, max_off)."""
    func = ida_funcs.get_func(ea)
    if not func:
        return {}
    func_size = func.size()
    binary = ida_bytes.get_bytes(ea, func_size)
    if not binary:
        return {}

    hits = {}  # offset -> [access_info]

    # Scan for mod=10 (disp32) patterns
    for pos in range(2, len(binary) - 4):
        modrm = binary[pos]
        mod = (modrm >> 6) & 3
        rm = modrm & 7
        if mod != 2 or rm == 4:  # mod=10 only, no SIB
            continue

        # Extract disp32
        disp = struct.unpack_from("<I", binary, pos + 1)[0]
        # Treat as signed if > 0x80000000
        if disp > 0x80000000:
            continue
        if disp < min_off or disp >= max_off:
            continue
        # Must be 4-aligned for most fields
        if disp % 4 != 0:
            # Allow 1/2 byte offsets only with specific opcodes
            opcode = binary[pos - 1]
            if opcode not in (0xC6, 0x80, 0x38):  # byte store/cmp
                if not (pos >= 2 and binary[pos - 2] == 0x0F):  # movzx
                    continue

        opcode = binary[pos - 1]
        access = "unknown"
        if opcode in (0x8B, 0x8D, 0x03):
            access = "load" if opcode != 0x8D else "lea"
        elif opcode in (0x89, 0x01):
            access = "store"
        elif opcode == 0xD9:
            access = "fld_float"
        elif opcode == 0xDD:
            access = "fld_double"
        elif opcode == 0xC7:
            access = "store_imm"
        elif opcode in (0x3B, 0x39, 0x3D):
            access = "cmp"

        # Check for 0F prefix (movzx etc)
        if pos >= 2 and binary[pos - 2] == 0x0F:
            if opcode == 0xB6:
                access = "load_byte"
            elif opcode == 0xB7:
                access = "load_word"

        regs = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"]
        if disp not in hits:
            hits[disp] = []
        hits[disp].append({
            "va": "0x%08X" % (ea + pos - 1),
            "access": access,
            "base_reg": regs[rm],
        })

    return hits


def main():
    ida_auto.auto_wait()

    # Parse arguments
    args = idc.ARGV[1] if len(idc.ARGV) > 1 else ""
    target_classes = None

    if args == "--top20":
        # Auto-select top 20 classes by gap size
        all_structs = load_struct_info()
        ranked = sorted(all_structs.items(),
                       key=lambda x: x[1]['binary_size'] - len(x[1]['known_offsets']) * 4,
                       reverse=True)
        target_classes = set(name for name, _ in ranked[:20])
        print("[*] Auto-selected top 20 classes by gap size")
    elif args:
        target_classes = set(args.split(","))
        print("[*] Target classes: %s" % target_classes)

    structs = load_struct_info(target_classes)
    class_methods = load_class_methods()

    print("[*] Scanning %d classes" % len(structs))

    results = {}
    for cls_name, cls_info in sorted(structs.items()):
        methods = class_methods.get(cls_name, [])
        if not methods:
            continue

        min_off = cls_info["base_size"]
        max_off = cls_info["binary_size"]
        known = cls_info["known_offsets"]

        # Scan all methods for offset accesses
        all_hits = {}  # offset -> total refs
        for ea in methods:
            hits = scan_func_for_offsets(ea, min_off, max_off)
            for off, access_list in hits.items():
                if off not in all_hits:
                    all_hits[off] = []
                all_hits[off].extend(access_list)

        # Separate into known (already annotated) and discovered (gap)
        cls_results = {}
        for off, refs in sorted(all_hits.items()):
            source = "known" if off in known else "gap_discovery"
            off_str = str(off)

            # Get existing member info if known
            member_info = cls_info["known_members"].get(off_str, {})
            name = member_info.get("name", "_undiscovered_%03X" % off)

            cls_results[off_str] = {
                "name": name,
                "source": source,
                "refs_count": len(refs),
                "refs": refs[:10],  # limit to 10 per field
            }

        if cls_results:
            # Count discoveries
            discoveries = sum(1 for v in cls_results.values() if v["source"] == "gap_discovery")
            print("  %s: %d total offsets accessed (%d known, %d NEW)" %
                  (cls_name, len(cls_results), len(cls_results) - discoveries, discoveries))
            results[cls_name] = cls_results

    # Save
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    total_discovered = sum(
        sum(1 for v in cls.values() if v["source"] == "gap_discovery")
        for cls in results.values()
    )
    print("[*] Done. %d new field offsets discovered. Output: %s" %
          (total_discovered, OUTPUT_FILE))

    idc.qexit(0)


if __name__ == "__main__":
    main()
