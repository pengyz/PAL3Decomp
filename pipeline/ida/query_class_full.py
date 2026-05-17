"""
IDAPython: 对指定类的所有方法做完整反编译，提取所有 _todo_/_field_ 字段上下文。

用法:
  idat.exe -A -S"pipeline/ida/query_class_full.py Camera,TextureLib,PalScript" original/PAL3.exe.i64
"""
import ida_auto, ida_hexrays, ida_funcs, ida_name
import idautils, idc
import json, os, re, sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT_FILE = os.path.join(LOG_DIR, "class_full_context.json")


def get_target_classes():
    """从脚本参数获取目标类名列表。"""
    # IDA passes script args after the script path
    for arg in idc.ARGV[1:]:
        if arg and not arg.startswith("-"):
            return [c.strip() for c in arg.split(",") if c.strip()]
    return []


def main():
    ida_auto.auto_wait()

    targets = get_target_classes()
    if not targets:
        print("[!] No target classes specified")
        print("    Usage: idat -A -S\"script.py Camera,TextureLib\" db.i64")
        idc.qexit(1)
        return

    print("[*] Target classes: %s" % ", ".join(targets))

    # Load functions
    funcs_path = os.path.join(ANNOTATIONS_DIR, "functions.json")
    with open(funcs_path, "r", encoding="utf-8") as f:
        all_funcs = json.load(f)

    # Load struct _todo_ fields
    structs_info = {}
    for cls in targets:
        spath = os.path.join(ANNOTATIONS_DIR, "structs", "%s.json" % cls)
        if os.path.exists(spath):
            with open(spath, "r", encoding="utf-8") as f:
                sdata = json.load(f)
            todos = set()
            for off_str, m in sdata.get("known_members", {}).items():
                if m["name"].startswith("_todo_") or m["name"].startswith("_field_"):
                    todos.add(int(off_str))
            structs_info[cls] = todos

    # Collect methods per class
    class_methods = {}
    for addr_str, info in all_funcs.items():
        name = info.get("name", "")
        if "::" not in name:
            continue
        cls = name.split("::")[0]
        if cls in targets:
            if cls not in class_methods:
                class_methods[cls] = []
            class_methods[cls].append((int(addr_str, 16), name))

    results = {}
    for cls in targets:
        methods = class_methods.get(cls, [])
        todos = structs_info.get(cls, set())
        if not methods or not todos:
            print("[!] %s: %d methods, %d todos — skipping" % (cls, len(methods), len(todos)))
            continue

        print("[*] %s: %d methods, %d _todo_ fields" % (cls, len(methods), len(todos)))
        field_context = {}

        for ea, func_name in sorted(methods):
            method = func_name.split("::", 1)[1]
            try:
                ida_hexrays.mark_cfunc_dirty(ea)
            except:
                pass
            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    continue
                code = str(cfunc)

                # Extract lines containing _todo_ or _field_ references
                for line in code.split("\n"):
                    stripped = line.strip()
                    if not stripped:
                        continue
                    # Check for this->_todo_XXX or this->_field_XXX
                    for m in re.finditer(r"this->(_(?:todo|field)_[0-9A-Fa-f]+)", stripped):
                        field_name = m.group(1)
                        if field_name not in field_context:
                            field_context[field_name] = []
                        field_context[field_name].append({
                            "method": method,
                            "line": stripped[:150],
                        })

                    # Check for (this + OFFSET) patterns
                    for m in re.finditer(r"\(this \+ (\d+)\)", stripped):
                        offset = int(m.group(1))
                        if offset in todos:
                            key = "_todo_%X" % offset
                            if key not in field_context:
                                field_context[key] = []
                            field_context[key].append({
                                "method": method,
                                "line": stripped[:150],
                            })

                    # Check for *((_DWORD *)this + N) patterns
                    for m in re.finditer(r"\*\(\(_DWORD \*\)this \+ (\d+)\)", stripped):
                        offset = int(m.group(1)) * 4
                        if offset in todos:
                            key = "_todo_%X" % offset
                            if key not in field_context:
                                field_context[key] = []
                            field_context[key].append({
                                "method": method,
                                "line": stripped[:150],
                            })

                    # Check for *((float *)this + N) patterns
                    for m in re.finditer(r"\*\(\(float \*\)this \+ (\d+)\)", stripped):
                        offset = int(m.group(1)) * 4
                        if offset in todos:
                            key = "_todo_%X" % offset
                            if key not in field_context:
                                field_context[key] = []
                            field_context[key].append({
                                "method": method,
                                "line": stripped[:150],
                            })

            except Exception as e:
                pass

        # Deduplicate and limit
        for field_name, entries in field_context.items():
            seen = set()
            unique = []
            for e in entries:
                key = (e["method"], e["line"][:60])
                if key not in seen:
                    seen.add(key)
                    unique.append(e)
            field_context[field_name] = unique[:10]

        results[cls] = field_context
        print("  → %d fields with context" % len(field_context))

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    print("[*] Output: %s" % OUTPUT_FILE)
    idc.qexit(0)


if __name__ == "__main__":
    main()
