"""Apply function pointer types to vtable struct members in IDB."""
import json, os, ida_auto, ida_typeinf, ida_funcs, ida_name, idautils, idc, ida_pro
ida_auto.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.normpath(os.path.join(SCRIPT_DIR, "..", ".."))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")
STRUCTS_DIR = os.path.join(ANNOTATIONS_DIR, "structs")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
os.makedirs(LOG_DIR, exist_ok=True)

til = ida_typeinf.get_idati()
log = lambda msg: print(msg)
func_sigs = {}

funcs_path = os.path.join(ANNOTATIONS_DIR, "functions.json")
if os.path.exists(funcs_path):
    with open(funcs_path) as f:
        for a, i in json.load(f).items():
            if i.get("signature"):
                func_sigs[int(a, 16)] = i["signature"]

for fn in sorted(os.listdir(STRUCTS_DIR)):
    if not fn.endswith(".json"): continue
    with open(os.path.join(STRUCTS_DIR, fn)) as f:
        sd = json.load(f)
    for a, mi in sd.get("methods", {}).items():
        sig = mi.get("signature", "")
        if sig:
            ea = int(a, 16)
            func_sigs.setdefault(ea, sig)

log("[*] %d signatures loaded" % len(func_sigs))

conv_list = ["__thiscall", "__cdecl", "__stdcall", "__fastcall"]

def sig_to_fp(s):
    s = s.strip()
    if s.startswith("virtual "): s = s[8:]
    for c in ["__userpurge ", "__usercall "]:
        s = s.replace(c, "")
    p = s.find("(")
    if p < 0: return None
    ret_conv, params = s[:p].strip(), s[p:]
    conv, ret = "", ret_conv
    for cc in conv_list:
        if cc in ret:
            ret, conv = ret.rsplit(cc, 1)[0].strip(), cc
            break
    return "%s (%s *)%s" % (ret, conv, params) if conv else "%s (*)%s" % (ret, params)

typed, nslots, nvt = 0, 0, 0

for fn in sorted(os.listdir(STRUCTS_DIR)):
    if not fn.endswith(".json"): continue
    with open(os.path.join(STRUCTS_DIR, fn)) as f:
        sd = json.load(f)
    cn = sd.get("name", fn.replace(".json", ""))
    for vi, vt in enumerate(sd.get("vtables", [])):
        slots = vt.get("slots", [])
        if not slots: continue
        va = vt.get("addr", "")
        names = []
        if va: names.append("vtbl_%s" % va[2:])
        names.append("%s_vtbl" % cn)
        if vi > 0: names.append("%s_vtbl_%d" % (cn, vi))
        ti = ida_typeinf.tinfo_t()
        vn = None
        for n in names:
            if ti.get_named_type(til, n): vn = n; break
        if not vn: continue
        ud = ida_typeinf.udt_type_data_t()
        if not ti.get_udt_details(ud): continue
        nvt += 1; nslots += len(slots)
        log("  [%s] %s (%d)" % (cn, vn, len(slots)))
        for si, sl in enumerate(slots):
            if si >= ud.size(): break
            ea = int(sl.get("addr", "0"), 16)
            if not (0x401000 <= ea <= 0x5695D0): continue
            sig = func_sigs.get(ea, "")
            if not sig:
                t2 = ida_typeinf.tinfo_t()
                if t2.get_func_type(ea): sig = t2.dstr()
            if not sig: continue
            fp = sig_to_fp(sig)
            if not fp: continue
            try:
                ft = ida_typeinf.tinfo_t()
                if ida_typeinf.parse_decl(ft, til, "%s __d;" % fp, ida_typeinf.PT_VAR) is not None: continue
                um = ud[si]
                if um.get_size() != ft.get_size(): continue
                um.type = ft
                fn = ida_name.get_name(ea) or ""
                if fn:
                    sn = fn.split("::")[-1]
                    if len(sn) > 2: um.name = sn
                typed += 1
            except: pass
    if typed > 0:
        rt = ida_typeinf.tinfo_t()
        if rt.create_udt(ud, ida_typeinf.BTF_STRUCT):
            ida_typeinf.force_named_type(til, vn, rt)

log("[*] %d vtables, %d slots, %d typed" % (nvt, nslots, typed))
ida_pro.qexit(0)
