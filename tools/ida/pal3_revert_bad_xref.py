"""
IDAPython: Revert bad xref-propagated names back to sub_XXXXXX.

Removes ClassName_HEXADDR style names that were incorrectly attributed.
Keeps only names that are:
  - Class::Method (proper IDA thiscall names with ::)
  - Manually set known names (from pal3_set_signatures.py)
  - FLIRT-identified names

Usage:
  idat.exe -A -S"pal3_revert_bad_xref.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, ida_funcs, ida_hexrays, idautils, idc
import json, os, re, time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_revert_bad_xref_log.txt")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
TEXT_START = 0x00401000
TEXT_END = 0x005695D0

# Names to KEEP (from pal3_set_signatures.py - manually verified)
KEEP_NAMES = {
    "GRPinput::SetMode", "GRPinput::GetKeyState", "GRPinput::SetMouseLimits",
    "GRPinput::Create", "CGameData::Destroy", "CGameData::GetMode",
    "CScreenMode::SetViewport", "CScreenMode::GetWidth", "CScreenMode::GetHeight",
    "CScreenMode::SetState", "CScreenMode::CreateDevice", "CScreenMode::Restore",
    "CScreenMode::GetAudioManager", "CScreenMode::SetMode", "CScreenMode::AudioFadeOut",
    "CScreenMode::AudioStopAll", "CScreenMode::AudioUpdate", "CScreenMode::GetInstance",
    "Logger::Write", "Logger::RegisterCallbacks", "Logger::RegisterCallback",
    "Logger::FormatException", "CameraCtrl::SetDimention", "CameraCtrl::SetAsCurrent",
    "ScriptUpdate", "NPCAnimUpdate", "RoleSystemNotify", "InputUpdate",
    "CameraUpdate", "UIPostUpdate", "UIUpdate", "EffectUpdate", "SceneUpdate",
    "CRenderTarget::GetInstance", "CRenderTarget::Destroy",
    "CRenderTarget2::GetInstance", "CRenderTarget2::Destroy",
    "UIQuadManager::GetInstance", "UIQuadManager::Destroy",
    "ScreenEffectMgr::GetInstance", "RenderTarget3::GetInstance",
    "RenderTarget4::GetInstance", "SoundContext::GetInstance",
    "InitLogFiles", "LogMessage", "PopMatrixStacks", "PushMatrixStacks",
    "RenderTarget3::Init",
}

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Reverting bad xref propagation")

        reverted = 0
        kept = 0

        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if not name or name.startswith("sub_") or name.startswith("nullsub_"):
                continue

            # Keep :: names (proper IDA thiscall)
            if name in KEEP_NAMES:
                kept += 1
                continue

            # Keep FLIRT-identified (CRT/library functions)
            # These typically have names like _malloc, __ftol, operator new, etc.
            if name.startswith("_") or name.startswith("??") or name.startswith("operator"):
                kept += 1
                continue

            # Keep unknown_libname_ (IDA auto-identified)
            if name.startswith("unknown_libname_"):
                kept += 1
                continue

            # Check if it's a bad xref name: ClassName_HEXADDR pattern
            m = re.match(r'^([A-Z]\w+)_([0-9A-Fa-f]{5,8})$', name)
            if m:
                # This is a bad propagated name - revert to sub_
                addr_hex = m.group(2).upper()
                original = "sub_%s" % addr_hex
                ida_name.set_name(ea, original, ida_name.SN_NOWARN | ida_name.SN_FORCE)
                reverted += 1
            else:
                kept += 1

        log("[*] Reverted: %d, Kept: %d" % (reverted, kept))
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB saved")

        # Re-export
        log("[*] Re-exporting...")
        os.makedirs(OUTPUT_DIR, exist_ok=True)
        import glob
        for f in glob.glob(os.path.join(OUTPUT_DIR, "*.json")):
            if not os.path.basename(f).startswith('_'):
                os.remove(f)

        targets = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            nm = ida_name.get_name(ea) or ""
            if not nm or nm.startswith("nullsub_") or nm.startswith("j_"):
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() <= 1:
                continue
            targets.append((ea, nm, func.size()))
        targets.sort()

        exported = 0
        for i, (ea, nm, size) in enumerate(targets):
            if (i+1) % 1000 == 0:
                log("  [%d/%d]" % (i+1, len(targets)))
            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc: continue
                code = str(cfunc)
                sig = cfunc.type.dstr()
                demangled = idc.demangle_name(nm, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else nm
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

        named_count = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] Exported: %d, Named: %d" % (exported, named_count))
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
