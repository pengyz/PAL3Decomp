"""
IDAPython: 从 annotations.json 批量应用所有标注到当前 IDB。

用法:
  idat -A -S"tools/ida/pal3_apply_annotations.py" original/PAL3.exe.91.i64

annotations.json 格式:
{
  "functions": {
    "0x00404800": {"name": "PAL3::Create", "signature": "void __cdecl PAL3::Create(HINSTANCE)"},
    ...
  },
  "globals": {
    "0x00BFDA60": {"name": "g_pGfxManager", "type": "gbGfxManager *"},
    ...
  }
}
"""

import ida_auto
import ida_name
import ida_typeinf
import idautils
import idc
import json
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "annotations.json")


def apply_annotations():
    ida_auto.auto_wait()

    if not os.path.exists(ANNOTATIONS_FILE):
        print(f"[!] Annotations file not found: {ANNOTATIONS_FILE}")
        idc.qexit(1)
        return

    with open(ANNOTATIONS_FILE, 'r', encoding='utf-8') as f:
        data = json.load(f)

    # Apply function names
    funcs = data.get("functions", {})
    renamed = 0
    sig_applied = 0
    for addr_str, info in funcs.items():
        addr = int(addr_str, 16)
        name = info.get("name", "")
        sig = info.get("signature", "")

        if name:
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                renamed += 1

        if sig:
            if idc.SetType(addr, sig):
                sig_applied += 1

    # Apply global variable names and types
    globs = data.get("globals", {})
    glob_named = 0
    glob_typed = 0
    for addr_str, info in globs.items():
        addr = int(addr_str, 16)
        name = info.get("name", "")
        typ = info.get("type", "")

        if name:
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                glob_named += 1

        if typ:
            if idc.SetType(addr, typ + ";"):
                glob_typed += 1

    print(f"[*] Annotations applied:")
    print(f"    Functions renamed: {renamed}/{len(funcs)}")
    print(f"    Signatures applied: {sig_applied}")
    print(f"    Globals renamed: {glob_named}/{len(globs)}")
    print(f"    Globals typed: {glob_typed}")

    idc.save_database(idc.get_idb_path(), 0)
    idc.qexit(0)


if __name__ == "__main__":
    apply_annotations()
