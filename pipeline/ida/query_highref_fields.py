"""
IDAPython: 对高引用但无 decomp context 的 _todo_ 字段，强制反编译获取上下文。

读取 query_todo_fields.py 的输出，找到 refs>=5 但无 decomp_context 的字段，
对引用最多的前3个方法做 Hex-Rays 反编译，提取包含该偏移的代码行。

用法:
  idat.exe -A -S"pipeline/ida/query_highref_fields.py" original/PAL3.exe.i64
"""
import ida_auto, ida_hexrays, ida_funcs, ida_name
import idautils, idc
import json, os, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "pipeline", "data", "annotations")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
INPUT_FILE = os.path.join(LOG_DIR, "todo_field_context.json")
OUTPUT_FILE = os.path.join(LOG_DIR, "highref_field_context.json")


def load_class_methods():
    funcs_path = os.path.join(ANNOTATIONS_DIR, "functions.json")
    with open(funcs_path, "r", encoding="utf-8") as f:
        funcs = json.load(f)
    class_methods = {}
    for addr_str, info in funcs.items():
        name = info.get("name", "")
        if "::" not in name:
            continue
        cls = name.split("::")[0]
        method = name.split("::", 1)[1]
        ea = int(addr_str, 16)
        if cls not in class_methods:
            class_methods[cls] = {}
        class_methods[cls][method] = ea
    return class_methods


def decompile_field_context(ea, offset):
    """反编译函数，提取包含指定偏移的代码行。"""
    try:
        ida_hexrays.mark_cfunc_dirty(ea)
    except:
        pass
    try:
        cfunc = ida_hexrays.decompile(ea)
        if not cfunc:
            return []
        code = str(cfunc)
        lines = []
        # Search for various offset patterns
        patterns = [
            "this + %d)" % offset,
            "this + %d)" % (offset + 1),
            "this + %d)" % (offset + 2),
            "this + %d)" % (offset + 3),
            "_todo_%X" % offset,
            "_field_%X" % offset,
            "_todo_%x" % offset,
            "_field_%x" % offset,
        ]
        # Also check DWORD pointer math: *(this + N) where N*4 = offset
        if offset % 4 == 0:
            patterns.append("this + %d)" % (offset // 4))

        for line in code.split("\n"):
            for pat in patterns:
                if pat in line:
                    lines.append(line.strip()[:140])
                    break
        return lines[:8]
    except:
        return []


def main():
    ida_auto.auto_wait()
    print("[*] Query high-ref fields without decomp context")

    with open(INPUT_FILE, "r", encoding="utf-8") as f:
        data = json.load(f)

    class_methods = load_class_methods()

    # Find fields with 5+ refs but no decomp_context
    targets = []
    for cls, fields in data.items():
        for off_str, f in fields.items():
            if not f.get("decomp_context") and len(f["refs"]) >= 3:
                # Get unique methods sorted by ref count
                method_counts = {}
                for ref in f["refs"]:
                    m = ref["method"]
                    method_counts[m] = method_counts.get(m, 0) + 1
                top_methods = sorted(method_counts.items(), key=lambda x: -x[1])[:5]
                targets.append((cls, int(off_str), f, top_methods))

    targets.sort(key=lambda x: -len(x[2]["refs"]))
    print("[*] %d fields to process" % len(targets))

    results = {}
    for i, (cls, offset, finfo, top_methods) in enumerate(targets):
        if (i + 1) % 50 == 0:
            print("  [%d/%d]" % (i + 1, len(targets)))

        cls_methods = class_methods.get(cls, {})
        decomp_lines = []

        for method_name, ref_count in top_methods:
            ea = cls_methods.get(method_name)
            if not ea:
                # Try partial match
                for mn, addr in cls_methods.items():
                    if method_name in mn or mn in method_name:
                        ea = addr
                        break
            if not ea:
                continue

            lines = decompile_field_context(ea, offset)
            for line in lines:
                decomp_lines.append({
                    "method": method_name,
                    "line": line,
                })

        if decomp_lines:
            if cls not in results:
                results[cls] = {}
            results[cls][str(offset)] = {
                "hex": "0x%X" % offset,
                "type": finfo["type"],
                "n_refs": len(finfo["refs"]),
                "decomp_context": decomp_lines,
            }

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    total_fields = sum(len(cls) for cls in results.values())
    print("[*] Done: %d fields with new decomp context" % total_fields)
    print("[*] Output: %s" % OUTPUT_FILE)

    idc.qexit(0)


if __name__ == "__main__":
    main()
