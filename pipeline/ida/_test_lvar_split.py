"""Test: can we split a reused lvar via save_user_lvar_settings?
Target: CEffMgr::CreateEffect (0x004CDCA0) — v14 is used for both
  - m_EffTable[idx].pEffect access: *((_DWORD *)v14 + 587)
  - CEffMgr tail offset: v14[2345]
"""
import ida_hexrays, ida_funcs, ida_typeinf, ida_auto, ida_ida
import json, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

ida_auto.auto_wait()

ea = 0x004CDCA0
func = ida_funcs.get_func(ea)
print("[*] Decompiling CEffMgr::CreateEffect...")

try:
    cfunc = ida_hexrays.decompile(func)
except Exception as e:
    print("[!] Decompile failed: %s" % str(e))
    ida_hexrays.term_hexrays()
    ida_ida.qexit(0)

print("[*] Lvars before modification:")
for lv in cfunc.lvars:
    loc = lv.location
    stkoff = loc.stkoff() if loc.is_stkoff() else -1
    defea = lv.defea if hasattr(lv, 'defea') else 'N/A'
    print("  %s: stack=%s defea=%s type=%s" % (
        lv.name, stkoff, defea, lv.type.dstr() if lv.type else '?'))

# Check if v14 exists
v14 = None
for lv in cfunc.lvars:
    if lv.name == 'v14':
        v14 = lv
        break

if v14 is None:
    print("[!] v14 not found in lvars")
    ida_hexrays.term_hexrays()
    ida_ida.qexit(0)

print("\n[*] Found v14: stack=%s, defea=%s" % (
    v14.location.stkoff() if v14.location.is_stkoff() else 'reg',
    v14.defea if hasattr(v14, 'defea') else 'N/A'))

# Try to modify v14's type to tagEffObj*
print("[*] Attempting to change v14 type to tagEffObj*...")
tif = ida_typeinf.tinfo_t()
decl = "tagEffObj *v14;"
if ida_typeinf.parse_decl(tif, None, decl, ida_typeinf.PT_VAR):
    v14.set_lvar_type(tif)
    print("[*] Type set OK. Saving...")
    try:
        uvec = ida_hexrays.lvar_uservec_t()
        uvec.lvvec = ida_hexrays.lvar_saved_infos_t()
        for lv in cfunc.lvars:
            si = ida_hexrays.lvar_saved_info_t()
            ll = ida_hexrays.lvar_locator_t()
            ll.location = lv.location
            ll.defea = cfunc.entry_ea
            si.ll = ll
            si.name = lv.name
            si.type = lv.type  # save the modified type
            uvec.lvvec.push_back(si)
        ida_hexrays.save_user_lvar_settings(ea, uvec)
        print("[*] save_user_lvar_settings OK")
    except Exception as e:
        print("[!] Save failed: %s" % str(e))
else:
    print("[!] parse_decl failed for tagEffObj*")

# Re-decompile and check
print("\n[*] Re-decompiling...")
try:
    cfunc2 = ida_hexrays.decompile(func)
    code = str(cfunc2)
    # Check if v14 type changed
    if 'tagEffObj *' in code:
        print("[*] tagEffObj* type FOUND in re-decompiled output")
    if 'char *v14' in code or 'char v14' in code:
        print("[*] char* type STILL present")
    # Check key patterns
    print("\n[*] First 300 chars of re-decompiled body:")
    body_start = code.find('{')
    if body_start > 0:
        print(code[body_start:body_start+300])
except Exception as e:
    print("[!] Re-decompile failed: %s" % str(e))

print("\n[*] Done. Saving log.")
with open(os.path.join(LOG_DIR, "lvar_split_test_result.txt"), 'w') as f:
    f.write("LVAR SPLIT TEST RESULT\n")
    f.write("=====================\n")
    f.write("Changed v14 type to tagEffObj* via set_lvar_type + save_user_lvar_settings\n")
    if 'tagEffObj *' in str(cfunc):
        f.write("SUCCESS: tagEffObj* type persisted\n")
    else:
        f.write("FAIL: tagEffObj* type NOT in output\n")
    f.write("\nOriginal code sample:\n")
    f.write(str(cfunc)[:2000])

ida_hexrays.term_hexrays()
ida_ida.qexit(0)
