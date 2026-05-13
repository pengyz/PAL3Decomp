"""
IDAPython: 对指定的数组成员，在引用该偏移的函数中搜索 stride 模式。

查找 `add reg, IMM` / `lea reg, [reg+IMM]` / `imul reg, IMM` 等指令
来确定 PAL3 中的真实 element size。

用法:
  idat.exe -A -S"pipeline/ida/find_strides.py" original/PAL3.exe.i64
"""
import ida_auto, ida_bytes, ida_funcs, ida_name, ida_ua
import idautils, idc
import json, os, struct, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "pipeline", "data", "annotations")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT_FILE = os.path.join(LOG_DIR, "stride_analysis.json")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

# The 5 remaining arrays to analyze
TARGETS = [
    ("CCBStageCam", 736, "tagCamTask", 50, 80),
    ("CCBStageRole", 560, "tagRoleTask", 64, 96),
    ("CCBSystem", 152, "tagThread", 1024, 88),
    ("EquipUI", 17884, "PlayerAtt", 5, 1524),
    ("PAL_GDB", 160, "RoleAtt", 200, 852),
]


def find_stride_in_func(ea, func_size, array_offset):
    """Search function binary for stride patterns near the array offset."""
    code = ida_bytes.get_bytes(ea, func_size)
    if not code:
        return []

    results = []
    # Search for the array offset as disp32
    needle = struct.pack("<I", array_offset)
    pos = 0
    while pos < len(code):
        idx = code.find(needle, pos)
        if idx == -1:
            break
        va = ea + idx
        # Check surrounding instructions for stride patterns
        # Look at +-50 bytes around this reference for imul/add/lea with constant
        region = code[max(0, idx - 50):min(len(code), idx + 50)]
        region_start = ea + max(0, idx - 50)

        # Search for common stride instructions in region
        for j in range(len(region) - 5):
            b = region[j]
            # imul reg, reg, imm32: 69 ModRM imm32
            if b == 0x69 and j + 6 <= len(region):
                imm = struct.unpack_from("<I", region, j + 2)[0]
                if 4 < imm < 100000:
                    results.append(("imul_imm32", imm, "0x%08X" % (region_start + j)))
            # imul reg, reg, imm8: 6B ModRM imm8
            if b == 0x6B and j + 3 <= len(region):
                imm = region[j + 2]
                if 4 < imm < 255:
                    results.append(("imul_imm8", imm, "0x%08X" % (region_start + j)))
            # add reg, imm32: 81 C0-C7 imm32 or 05 imm32
            if b == 0x81 and j + 6 <= len(region):
                modrm = region[j + 1]
                if 0xC0 <= modrm <= 0xC7:
                    imm = struct.unpack_from("<I", region, j + 2)[0]
                    if 4 < imm < 100000:
                        results.append(("add_imm32", imm, "0x%08X" % (region_start + j)))
            # lea reg, [reg+imm32]: 8D ModRM(mod=10) imm32
            if b == 0x8D and j + 6 <= len(region):
                modrm = region[j + 1]
                if (modrm >> 6) & 3 == 2 and (modrm & 7) != 4:  # mod=10, not SIB
                    imm = struct.unpack_from("<I", region, j + 2)[0]
                    if 4 < imm < 100000:
                        results.append(("lea_disp32", imm, "0x%08X" % (region_start + j)))
            # shl reg, imm8 (shift as stride indicator)
            if b == 0xC1 and j + 3 <= len(region):
                modrm = region[j + 1]
                nnn = (modrm >> 3) & 7
                if nnn == 4:  # shl
                    shift = region[j + 2]
                    if 2 <= shift <= 12:
                        results.append(("shl", 1 << shift, "0x%08X" % (region_start + j)))

        pos = idx + 1

    return results


def main():
    ida_auto.auto_wait()
    print("[*] Stride analysis for remaining array members")

    # Load function annotations
    funcs_path = os.path.join(ANNOTATIONS_DIR, "functions.json")
    with open(funcs_path, "r", encoding="utf-8") as f:
        all_funcs = json.load(f)

    class_methods = {}
    for addr_str, info in all_funcs.items():
        name = info.get("name", "")
        if "::" not in name:
            continue
        cls = name.split("::")[0]
        if cls not in class_methods:
            class_methods[cls] = []
        class_methods[cls].append((int(addr_str, 16), name))

    results = {}
    for cls, array_off, elem_type, pdb_count, pdb_elem in TARGETS:
        print("[*] %s+%d: %s[%d] pdb_elem=%d" % (cls, array_off, elem_type, pdb_count, pdb_elem))
        methods = class_methods.get(cls, [])

        all_strides = []
        for ea, func_name in methods:
            func = ida_funcs.get_func(ea)
            if not func:
                continue
            strides = find_stride_in_func(ea, func.size(), array_off)
            for kind, value, va in strides:
                all_strides.append({
                    "kind": kind,
                    "value": value,
                    "va": va,
                    "func": func_name,
                })

        # Count stride values
        from collections import Counter
        stride_counts = Counter(s["value"] for s in all_strides)
        print("  Stride candidates:")
        for val, cnt in stride_counts.most_common(10):
            print("    stride=%d (%d hits)" % (val, cnt))

        results["%s+%d" % (cls, array_off)] = {
            "elem_type": elem_type,
            "pdb_count": pdb_count,
            "pdb_elem": pdb_elem,
            "strides": all_strides,
            "stride_counts": dict(stride_counts.most_common(10)),
        }

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    print("[*] Output: %s" % OUTPUT_FILE)
    idc.qexit(0)


if __name__ == "__main__":
    main()
