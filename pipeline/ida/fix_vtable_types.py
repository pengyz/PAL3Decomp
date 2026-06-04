"""
Post-processing script: fix __vftable member types for classes with vtables.
Run AFTER apply_annotations.py. For each class with vtables, finds the __vftable
member and sets its type to the correct vtbl_ADDR * pointer type.

This enables Hex-Rays to generate proper virtual function calls (obj->Method())
instead of __vftable + N dispatch.
"""
import json, os, ida_auto, ida_typeinf, ida_pro, ida_funcs, ida_name, idautils, idc
ida_auto.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.normpath(os.path.join(SCRIPT_DIR, "..", ".."))
STRUCTS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
os.makedirs(LOG_DIR, exist_ok=True)

til = ida_typeinf.get_idati()

fixed = 0
skipped = 0

for fn in sorted(os.listdir(STRUCTS_DIR)):
    if not fn.endswith(".json"): continue
    with open(os.path.join(STRUCTS_DIR, fn)) as f:
        sd = json.load(f)
    cls_name = sd.get("name", fn.replace(".json", ""))
    vtables = sd.get("vtables", [])
    if not vtables:
        continue
    
    # Check if class struct exists in TIL
    tif = ida_typeinf.tinfo_t()
    if not tif.get_named_type(til, cls_name):
        continue
    
    # Get the first vtable address
    va = vtables[0].get("addr", "")
    if not va:
        continue
    
    vtbl_name = "vtbl_%s" % va[2:]
    vtif = ida_typeinf.tinfo_t()
    if not vtif.get_named_type(til, vtbl_name):
        continue
    
    # Create pointer type: vtbl_ADDR *
    vp_tif = ida_typeinf.tinfo_t()
    vp_decl = "%s *_vp;" % vtbl_name
    ida_typeinf.parse_decl(vp_tif, til, vp_decl, ida_typeinf.PT_VAR)
    if not vp_tif.is_correct() or vp_tif.get_size() != 4:
        continue
    
    # Get the class struct and fix __vftable member
    ud = ida_typeinf.udt_type_data_t()
    if not tif.get_udt_details(ud):
        continue
    
    found = False
    for i in range(ud.size()):
        try:
            um = ud[i]
            try:
                mname = um.name
            except AttributeError:
                mname = um.get_name()  # fallback for older API
            if mname == "__vftable":
                cur_type = um.type.dstr() if um.type else ""
                if "vtbl" not in cur_type and "vftable" not in cur_type:
                    um.type = vp_tif
                    found = True
                    fixed += 1
        except: break
    
    if found:
        # Rebuild the struct with the corrected member type
        r2 = ida_typeinf.tinfo_t()
        if r2.create_udt(ud, ida_typeinf.BTF_STRUCT):
            r2.set_named_type(til, cls_name, ida_typeinf.NTF_REPLACE)
            print("  Fixed __vftable type for %s (%s)" % (cls_name, vtbl_name))
    else:
        skipped += 1

print("[*] Done: %d fixed, %d skipped (no __vftable)" % (fixed, skipped))
ida_pro.qexit(0)
