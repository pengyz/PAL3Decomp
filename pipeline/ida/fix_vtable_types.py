"""
Post-processing: fix __vftable member types for classes with vtables.
Run AFTER apply_annotations.py.

For each class with vtables:
  1. Set cppobj flag (TAUDT_CPPOBJ = 128) — tells Hex-Rays it's a C++ object with vtable
  2. Set primary __vftable type from 'int' to 'vtbl_ADDR *'
  3. Type secondary vtable pointer fields (e.g. m_pVfTable)

This enables Hex-Rays to generate proper virtual function calls.
"""
import json, os, ida_auto, ida_typeinf, ida_pro, ida_name, ida_funcs
ida_auto.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.normpath(os.path.join(SCRIPT_DIR, "..", ".."))
STRUCTS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
os.makedirs(LOG_DIR, exist_ok=True)

til = ida_typeinf.get_idati()

# Build vtable address → vtable struct name mapping
# From the annotation files, we know: vtables[N].addr -> vtbl_ADDR
vtbl_map = {}  # vtable addr (hex string without 0x) -> class_name
cls_vtables = {}  # class_name -> [(addr, slots)]
for fn in sorted(os.listdir(STRUCTS_DIR)):
    if not fn.endswith(".json"): continue
    with open(os.path.join(STRUCTS_DIR, fn), encoding='utf-8') as f:
        sd = json.load(f)
    cn = sd.get("name", fn.replace(".json", ""))
    for vt in sd.get("vtables", []):
        va = vt.get("addr", "")
        if va:
            addr_key = va[2:]  # strip "0x"
            vtbl_map.setdefault(addr_key, cn)
            cls_vtables.setdefault(cn, []).append((addr_key, vt.get("slots", [])))

TAUDT_CPPOBJ = 128
fixed_primary = 0
fixed_cppobj = 0
fixed_secondary = 0

for cls_name, vt_list in sorted(cls_vtables.items()):
    tif = ida_typeinf.tinfo_t()
    if not tif.get_named_type(til, cls_name):
        continue
    
    ud = ida_typeinf.udt_type_data_t()
    if not tif.get_udt_details(ud):
        continue
    
    needs_rebuild = False
    
    # ── 1. Set cppobj flag ──
    if not (ud.taudt_bits & TAUDT_CPPOBJ):
        ud.taudt_bits |= TAUDT_CPPOBJ
        needs_rebuild = True
        fixed_cppobj += 1
    
    # ── 2. Build vtable pointer type for each vtable ──
    for vt_idx, (addr_key, slots) in enumerate(vt_list):
        vtbl_type_name = "vtbl_%s" % addr_key
        vtif = ida_typeinf.tinfo_t()
        if not vtif.get_named_type(til, vtbl_type_name):
            continue
        
        # Create pointer type: vtbl_ADDR *
        vp_tif = ida_typeinf.tinfo_t()
        vp_decl = "%s *_vp;" % vtbl_type_name
        ida_typeinf.parse_decl(vp_tif, til, vp_decl, ida_typeinf.PT_VAR)
        if not vp_tif.is_correct() or vp_tif.get_size() != 4:
            continue
        
        # Find the corresponding field in the struct
        if vt_idx == 0:
            # Primary vtable → __vftable at offset 0
            target_name = "__vftable"
        else:
            # Secondary vtable → try to find from known_members
            # The annotation might name it (e.g. m_pVfTable)
            # Try a few naming conventions based on common patterns
            target_name = None
            # Check known_members for this class
            with open(os.path.join(STRUCTS_DIR, "%s.json" % cls_name), encoding='utf-8') as f:
                sd = json.load(f)
            for off_str, minfo in sd.get("known_members", {}).items():
                mn = minfo["name"]
                if mn != "__vftable" and ("vf" in mn.lower() or "vtbl" in mn.lower() or "vftable" in mn.lower()):
                    target_name = mn
                    break
        
        if not target_name:
            continue
        
        # Find the member and set its type
        for i in range(ud.size()):
            try:
                um = ud[i]
                try:
                    mname = um.name
                except AttributeError:
                    mname = um.get_name()
                
                if mname == target_name:
                    cur_type = um.type.dstr() if um.type else ""
                    if "vtbl" not in cur_type and "vftable" not in cur_type:
                        um.type = vp_tif
                        needs_rebuild = True
                        if vt_idx == 0:
                            fixed_primary += 1
                        else:
                            fixed_secondary += 1
            except:
                break
    
    if needs_rebuild:
        r2 = ida_typeinf.tinfo_t()
        if r2.create_udt(ud, ida_typeinf.BTF_STRUCT):
            r2.set_named_type(til, cls_name, ida_typeinf.NTF_REPLACE)

# ── 3. Fix gbengine vtable slot names ──
# The PDB imports gbTexture with wrong slot names (e.g. "IsLoaded").
# Override with correct names from gbengine header (source of truth).
# These vtbl structs were pre-created by apply_annotations step 3a.
# We only need to ensure the gbTexture struct references them.

# gbTexture: 4 pure virtual slots at [1]-[4] overridden by gbTexture_D3D
# vtable addr = 0x100F57E8, vtbl struct = vtbl_100F57E8
for cls_name, vtbl_addr, slot_names in [
    ("gbTexture", "100F57E8",
     ["~gbTexture", "CreateFromMemory", "UpdateTexture",
      "CreateForRenderTarget", "CreateFromFileMemory"]),
]:
    tif = ida_typeinf.tinfo_t()
    if not tif.get_named_type(til, cls_name):
        continue
    ud = ida_typeinf.udt_type_data_t()
    if not tif.get_udt_details(ud):
        continue
    
    # Ensure __cppobj flag
    if not (ud.taudt_bits & TAUDT_CPPOBJ):
        ud.taudt_bits |= TAUDT_CPPOBJ
        fixed_cppobj += 1
    
    # Create vtbl pointer type: vtbl_ADDR *
    vtbl_type_name = "vtbl_%s" % vtbl_addr
    vtif = ida_typeinf.tinfo_t()
    if not vtif.get_named_type(til, vtbl_type_name):
        # Create the vtbl struct if it doesn't exist yet
        lines = []
        for i, name in enumerate(slot_names):
            lines.append("    int (*%s)();" % name)
        decl = "struct %s {\n%s\n};" % (vtbl_type_name, "\n".join(lines))
        if ida_typeinf.parse_decl(vtif, til, decl, ida_typeinf.PT_TYP) is None:
            continue
        vtif.set_named_type(til, vtbl_type_name, ida_typeinf.NTF_REPLACE)
    
    vp_tif = ida_typeinf.tinfo_t()
    vp_decl = "%s *_vp;" % vtbl_type_name
    ida_typeinf.parse_decl(vp_tif, til, vp_decl, ida_typeinf.PT_VAR)
    if not vp_tif.is_correct() or vp_tif.get_size() != 4:
        continue
    
    # Find member at offset 0 (the vtable pointer) and type it
    for i in range(ud.size()):
        try:
            um = ud[i]
            mname = um.name if hasattr(um, 'name') else um.get_name()
            # Check if this is the first member (offset 0)
            if um.offset == 0:
                cur_type = um.type.dstr() if um.type else ""
                if "vtbl" not in cur_type:
                    um.type = vp_tif
                    fixed_primary += 1
                    # Rebuild UDT
                    r2 = ida_typeinf.tinfo_t()
                    if r2.create_udt(ud, ida_typeinf.BTF_STRUCT):
                        r2.set_named_type(til, cls_name, ida_typeinf.NTF_REPLACE)
                    break
        except:
            break

print("[*] Fixed: cppobj=%d, primary_vtbl=%d, secondary_vtbl=%d" % (
    fixed_cppobj, fixed_primary, fixed_secondary))

# ── 4. Force-rename (type propagation from vtable type changes may override names) ---
ida_auto.auto_wait()
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")
_force_renamed = 0
_rename_fail = []

funcs_path = os.path.join(ANNOTATIONS_DIR, "functions.json")
if os.path.exists(funcs_path):
    with open(funcs_path, "r", encoding="utf-8") as f:
        funcs = json.load(f)
    structs_path = os.path.join(ANNOTATIONS_DIR, "structs")
    for fn in sorted(os.listdir(structs_path)):
        if not fn.endswith(".json"): continue
        with open(os.path.join(structs_path, fn), encoding="utf-8") as f:
            sd = json.load(f)
        for addr_str, minfo in sd.get("methods", {}).items():
            if addr_str not in funcs:
                funcs[addr_str] = minfo

    for addr_str, info in funcs.items():
        desired = info.get("name", "")
        if not desired:
            continue
        desired_simple = desired.split("::")[-1] if "::" in desired else desired
        addr = int(addr_str, 16)
        cur = ida_name.get_name(addr) or ""
        if cur == desired_simple:
            continue
        ida_name.set_name(addr, "", ida_name.SN_NOWARN)
        if ida_name.set_name(addr, desired_simple, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            _force_renamed += 1
        else:
            _rename_fail.append((addr_str, cur, desired_simple))

if _force_renamed:
    print("[4] Force-renamed %d functions (post-vtable fix)" % _force_renamed)
if _rename_fail:
    for a, c, d in _rename_fail[:5]:
        print("    [!] %s: '%s' -> '%s' FAILED" % (a, c[:30], d[:30]))

ida_auto.auto_wait()

ida_pro.qexit(0)
