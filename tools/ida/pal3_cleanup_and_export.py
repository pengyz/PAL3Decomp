"""
IDAPython: Cleanup bad names + apply iter10 + fresh full export.

1. Revert all ClassName_sub_HEXADDR names back to sub_HEXADDR
2. Apply iter10 annotations (correct names)
3. Full export

Usage:
  idat.exe -A -S"pal3_cleanup_and_export.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, ida_funcs, ida_hexrays, idautils, idc
import json, os, re, time, glob

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_cleanup_log.txt")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Iter 10 annotations
ITER10 = [
    (0x004D58A0, "CEffMgr::Reset",
     "_DWORD * __thiscall CEffMgr::Reset(CEffMgr *this)"),
    (0x004DB920, "CCBSystem::SetCmdParam",
     "int __thiscall CCBSystem::SetCmdParam(CCBSystem *this, int idx, int value)"),
    (0x004DB710, "CCBSystem::GetCmdPtr",
     "char * __thiscall CCBSystem::GetCmdPtr(CCBSystem *this, int idx)"),
    (0x004DB750, "CCBSystem::GetCmdData",
     "char * __thiscall CCBSystem::GetCmdData(CCBSystem *this, int idx)"),
    (0x0053E310, "CCBStageRole::PlaySound",
     "void __thiscall CCBStageRole::PlaySound(CCBStageRole *this, char *name, int a3)"),
    (0x00515C50, "CCBSystem::ClearEffect",
     "char __thiscall CCBSystem::ClearEffect(CCBSystem *this, int idx)"),
    (0x004DC5C0, "CCBUI::SetParam",
     "int __thiscall CCBUI::SetParam(CCBUI *this, int a2, int a3)"),
    (0x004F3E20, "CCBRoleState::ProcessRound",
     "char __thiscall CCBRoleState::ProcessRound(CCBRoleState *this, unsigned int a2)"),
    (0x004EFFC0, "CCBRoleState::IsRoleReady",
     "bool __thiscall CCBRoleState::IsRoleReady(CCBRoleState *this, int roleIdx)"),
    (0x004FC8F0, "CCBSystem::GetStageRole",
     "char __thiscall CCBSystem::GetStageRole(CCBSystem *this, int idx)"),
    (0x00412940, "RoleSystem::UpdatePath",
     "int __thiscall RoleSystem::UpdatePath(RoleSystem *this, int a2)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Cleanup + Iter10 + Full Export")

        # Phase 1: Revert ClassName_sub_HEXADDR names
        reverted = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            # Match: ClassName_sub_HEXADDR
            m = re.match(r'^([A-Z]\w+)_(sub_[0-9A-Fa-f]+)$', name)
            if m:
                original = m.group(2)
                ida_name.set_name(ea, original, ida_name.SN_NOWARN | ida_name.SN_FORCE)
                reverted += 1

        log("[*] Reverted %d bad ClassName_sub_ names" % reverted)

        # Phase 2: Apply iter10
        named = 0
        for entry in ITER10:
            addr, new_name = entry[0], entry[1]
            sig = entry[2] if len(entry) > 2 else None
            if ida_name.set_name(addr, new_name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                named += 1
            if sig:
                idc.SetType(addr, sig)
        log("[*] Iter10: named %d, sigs %d" % (named, len(ITER10)))

        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)

        # Phase 3: Full export
        log("[*] Full export...")
        os.makedirs(OUTPUT_DIR, exist_ok=True)
        for f in glob.glob(os.path.join(OUTPUT_DIR, "*.json")):
            if not os.path.basename(f).startswith('_'):
                os.remove(f)

        targets = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if not name or name.startswith("nullsub_") or name.startswith("j_"):
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() <= 1:
                continue
            targets.append((ea, name, func.size()))
        targets.sort()

        named_count = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] Targets: %d (named: %d)" % (len(targets), named_count))

        exported = 0
        t0 = time.time()
        for i, (ea, name, size) in enumerate(targets):
            if (i+1) % 1000 == 0:
                log("  [%d/%d]" % (i+1, len(targets)))
            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc: continue
                code = str(cfunc)
                sig = cfunc.type.dstr()
                demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else name
                safe = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
                safe = safe.replace('*', '_').replace(' ', '_').replace('?', '_')
                safe = safe.replace('@', '_').replace('$', '_').replace(',', '_')
                safe = safe.replace('(', '').replace(')', '').replace('/', '_')
                safe = safe.replace('"', '').replace("'", '').replace('\\', '_')
                while '__' in safe: safe = safe.replace('__', '_')
                safe = safe.strip('_')
                if len(safe) > 100: safe = safe[:100]
                filename = '%s_%08x.json' % (safe, ea)
                with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                    json.dump({'name': display_name, 'address': '0x%08X' % ea,
                               'size_bytes': size, 'signature': sig,
                               'decompiled_c': code}, f, indent=2, ensure_ascii=False)
                exported += 1
            except: pass

        log("[*] Exported: %d (%.1fs)" % (exported, time.time()-t0))
        log("[*] Done!")
    except Exception as e:
        log("[!] %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
