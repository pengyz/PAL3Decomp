"""
IDAPython: Import gbGeomNode struct into gbengine.dll.i64 and verify via Hex-Rays.

Usage (headless):
  "D:\Program Files\IDA Professional 9.2\idat.exe" -A -S"tools/ida/ida_import_gbgeomnode.py" "original/gbengine.dll.i64"

Output: asm/gbengine_ida/_gbgeomnode_verify.txt
"""

import ida_auto
import ida_typeinf
import ida_hexrays
import ida_funcs
import ida_name
import ida_nalt
import idautils
import idc
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
HEADER_PATH = os.path.join(SCRIPT_DIR, "gbengine_types_for_ida.h")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "gbengine_ida")
OUTPUT_FILE = os.path.join(OUTPUT_DIR, "_gbgeomnode_verify.txt")

# Correct addresses from export JSON filenames
GEOMNODE_FUNCS = {
    # Getters (for verifying layout)
    0x1000C9B0: ("GetCacheToWorld", "struct gbMatrix4 *__thiscall f(gbGeomNode *this)"),
    0x1000C9C0: ("GetMesh", "struct gbBaseMesh *__thiscall f(gbGeomNode *this)"),
    0x1000C9D0: ("GetAnimMaxTime", "double __thiscall f(gbGeomNode *this)"),
    0x1000C9A0: ("GetLoopPast", "int __thiscall f(gbGeomNode *this)"),
    0x1000C9E0: ("EnableBlade", "void __thiscall f(gbGeomNode *this, int a2)"),
    # Core methods
    0x100115E0: ("Reset", "void __thiscall f(gbGeomNode *this, float a2)"),
    0x10011460: ("Render", "void __thiscall f(gbGeomNode *this, struct gbRenderInfoObj *a2)"),
    0x10011520: ("RenderShadowVolume", "void __thiscall f(gbGeomNode *this, struct gbRenderInfoObj *a2)"),
    0x10011780: ("EnableShadow", "void __thiscall f(gbGeomNode *this, int a2)"),
    0x10011130: ("AttachSelf", "void __thiscall f(gbGeomNode *this, struct gbRenderEffect *a2)"),
    0x10011440: ("Attach", "int __thiscall f(gbGeomNode *this, struct gbRenderEffect *a2)"),
    0x10011650: ("GetBoundSphere", "void __thiscall f(gbGeomNode *this, struct gbSphere *a2)"),
    0x100117B0: ("GetAABBox", "int __thiscall f(gbGeomNode *this, struct gbAABBox *a2)"),
    0x1000FDE0: ("GetOBBox", "struct gbOBBox *__thiscall f(gbGeomNode *this, struct gbOBBox *a2)"),
    0x1000FEC0: ("GetTotalOBBox", "struct gbOBBox *__thiscall f(gbGeomNode *this, struct gbOBBox *a2)"),
    0x10011740: ("SetAnimLoop", "void __thiscall f(gbGeomNode *this, int a2)"),
    0x100117E0: ("SetBladeTime", "void __thiscall f(gbGeomNode *this, float a2)"),
    0x10011800: ("SetBladeTimeScale", "void __thiscall f(gbGeomNode *this, float a2)"),
    0x10011820: ("GetLastBladePos", "struct gbVec3D *__thiscall f(gbGeomNode *this, struct gbGeomNode *a2)"),
    0x10011840: ("ReplaceTexture_str", "void __thiscall f(gbGeomNode *this, char *a2)"),
    0x10011880: ("ReplaceTexture_tex", "void __thiscall f(gbGeomNode *this, struct gbTexture *a2)"),
    # Update and Load
    0x10010EC0: ("Update", "void __thiscall f(gbGeomNode *this)"),
    0x100102C0: ("LoadFromFile", "int __thiscall f(gbGeomNode *this, char *a2, char *a3, void *a4)"),
    0x100108B0: ("LoadCVDFile", "int __thiscall f(gbGeomNode *this, char *a2)"),
    0x10010CD0: ("LoadCVDFromStream", "void __thiscall f(gbGeomNode *this, struct gbVFile *a2, float a3)"),
}

# Which ones to show full decompilation for
VERIFY_SHOW = [
    0x1000C9B0,  # GetCacheToWorld - simplest, should show &this->worldTransform
    0x1000C9C0,  # GetMesh
    0x1000C9D0,  # GetAnimMaxTime
    0x1000C9A0,  # GetLoopPast
    0x1000C9E0,  # EnableBlade
    0x100115E0,  # Reset
    0x10011460,  # Render
    0x10011520,  # RenderShadowVolume
    0x10011780,  # EnableShadow
    0x10011650,  # GetBoundSphere
    0x10011440,  # Attach
    0x10011740,  # SetAnimLoop
    0x10010EC0,  # Update
]


def main():
    out = []

    def log(msg):
        out.append(msg)
        print(msg)

    ida_auto.auto_wait()
    log("=" * 70)
    log("  gbGeomNode Struct Import & Verification")
    log("=" * 70)

    # Step 1: Import header types
    log("\n[Step 1] Importing types from gbengine_types_for_ida.h...")
    if not os.path.exists(HEADER_PATH):
        log(f"[ERROR] Header not found: {HEADER_PATH}")
        write_output(out)
        idc.qexit(1)
        return

    with open(HEADER_PATH, 'r', encoding='utf-8') as f:
        header_content = f.read()

    errors = ida_typeinf.idc_parse_types(header_content, 0)
    if errors:
        log(f"[WARN] parse_types: {errors} error(s)")
    else:
        log("[OK] Types parsed without errors")

    # Verify sizes
    til = ida_typeinf.get_idati()
    for tname, expect_size in [("gbGeomNode", 0x118), ("gbVisNode", 0x58),
                                ("gbMatrix4", 0x40), ("gbNBTreeNode", 0x1C)]:
        ti = ida_typeinf.tinfo_t()
        if ti.get_named_type(til, tname):
            sz = ti.get_size()
            ok = "OK" if sz == expect_size else "MISMATCH"
            log(f"  [{ok}] {tname}: size=0x{sz:X} (expected 0x{expect_size:X})")
        else:
            log(f"  [MISS] {tname} not found")

    # Step 2: Apply function prototypes with gbGeomNode* this
    log("\n[Step 2] Applying function prototypes...")
    applied = 0
    for ea, (name, proto) in GEOMNODE_FUNCS.items():
        func = ida_funcs.get_func(ea)
        if not func:
            log(f"  [SKIP] No function at 0x{ea:08X} ({name})")
            continue
        # Apply prototype using SetType
        result = idc.SetType(ea, proto)
        if result:
            applied += 1
        else:
            log(f"  [FAIL] SetType at 0x{ea:08X} ({name}): {proto[:60]}")
    log(f"  Applied {applied}/{len(GEOMNODE_FUNCS)} prototypes")

    # Step 3: Decompile and verify
    log("\n[Step 3] Decompiling with struct-typed 'this'...")
    log("(Named fields = struct layout CORRECT; raw offsets = WRONG or type not applied)")
    log("")

    for ea in VERIFY_SHOW:
        name = GEOMNODE_FUNCS.get(ea, ("???", ""))[0]
        log(f"\n{'='*60}")
        log(f"  {name} @ 0x{ea:08X}")
        log(f"{'='*60}")
        try:
            cfunc = ida_hexrays.decompile(ea)
            if cfunc:
                text = str(cfunc)
                lines = text.split('\n')
                for line in lines[:40]:
                    log(f"  {line}")
                if len(lines) > 40:
                    log(f"  ... ({len(lines)-40} more lines)")
            else:
                log("  [ERROR] decompile returned None")
        except Exception as e:
            log(f"  [ERROR] {e}")

    # Summary
    log("\n" + "=" * 70)
    log("  EXPECTED RESULTS (if struct is correct):")
    log("  GetCacheToWorld  → return &this->worldTransform")
    log("  GetMesh          → return this->mesh")
    log("  GetAnimMaxTime   → return this->animMaxTime")
    log("  GetLoopPast      → return this->loopPast")
    log("  EnableBlade      → this->bladeEnabled = a2")
    log("  Reset            → this->currentTime, this->animMaxTime, this->loopPast")
    log("  Render           → this->visible, this->mesh")
    log("  SetAnimLoop      → this->animLoop = a2")
    log("=" * 70)

    write_output(out)

    # Do NOT save database - verification is read-only
    idc.qexit(0)


def write_output(lines):
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(lines))
    print(f"\n[*] Written to: {OUTPUT_FILE}")


if __name__ == '__main__':
    main()
