"""
Post-processing: fix __vftable member types for classes with vtables.
Run AFTER apply_annotations.py.

For each class with vtables:
  1. Set cppobj flag (TAUDT_CPPOBJ = 128) — tells Hex-Rays it's a C++ object with vtable
  2. Set primary __vftable type from 'int' to 'vtbl_ADDR *'
  3. Type secondary vtable pointer fields (e.g. m_pVfTable)

This enables Hex-Rays to generate proper virtual function calls.
"""
import json, os, ida_auto, ida_typeinf, ida_pro
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

# ── Post-processing: rename PDB struct member names to match gbengine header ──
# PDB uses different naming conventions (PascalCase, m_ prefix) than our
# header (camelCase, p_ prefix). The gbengine header is the compilation
# target — the PAL3 IDB must use header-compatible names.
#
# Round 1 (completed in gbTexture.h): header renamed towards PDB convention.
# Remaining structs (gbChain, gbVisNode): rename_map bridges the gap until
# headers are also renamed to match PDB.
fix_count = 0
for cls, byte_off, new_name in [
    ("gbChain1D", 0, "pHead"),
    ("gbChain1D", 4, "pTail"),
    ("gbChain1D", 12, "pIterator"),
    ("gbChain1DNode", 4, "pNext"),
    ("gbNBTreeNode", 8, "pParent"),
    ("gbVisNode", 52, "renderPriority"),
    ("gbVisNode", 56, "timeScale"),
    ("gbVisNode", 60, "visible"),
    ("gbVisNode", 64, "enableShadow"),
    ("gbVisNode", 72, "cullPrev"),
    ("gbVisNode", 76, "cullNext"),
    ("gbVisNode", 80, "blendValue"),
    ("gbVisNode", 84, "blendMode"),
]:
    sid = idc.get_struc_id(cls)
    if sid in (-1, 0xFFFFFFFF): continue
    try:
        cur = idc.get_member_name(sid, byte_off)
    except: continue
    if not cur or cur == new_name: continue
    if idc.set_member_name(sid, byte_off, new_name):
        fix_count += 1
        print("  [FIX] %s+%d: %s -> %s" % (cls, byte_off, cur, new_name))
print("[*] Renamed %d struct members to gbengine header convention" % fix_count)

ida_pro.qexit(0)
