"""
IDAPython: Set correct function names and thiscall signatures for known functions.

This enables Hex-Rays to output Class::Method(this, args) form which our
post-processor (hexrays_to_oop.py) then converts to obj->Method(args).

Usage:
  idat.exe -A -S"pal3_set_signatures.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_name
import ida_typeinf
import ida_hexrays
import ida_funcs
import idautils
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_set_signatures_log.txt")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


# ============================================================
# Struct definitions to import
# ============================================================
STRUCT_DEFS = [
    """struct GRPinput {
        void *m_lpDI;
        void *m_lpDIDKeyboard;
        void *m_lpDIDMouse;
        float m_mouseSensitivity;
        long m_mouseMinX;
        long m_mouseMinY;
        long m_mouseMaxX;
        long m_mouseMaxY;
        long m_joystickMinX;
        long m_joystickMinY;
        long m_joystickMaxX;
        long m_joystickMaxY;
        char _rest[10000];
    };""",
    """struct CGameData {
        char _data[14544];
    };""",
]

# ============================================================
# Global variable types
# ============================================================
GLOBAL_TYPES = [
    # (address, type_str, name)
    (0x00BFDA60, "gbGfxManager *", "g_pGfxManager"),
    (0x00BFDA64, "void *", "g_pActorMgr"),
    (0x00BFDA68, "void *", "g_pCamera"),
    (0x00BFDA74, "void *", "g_pCBSystem"),
    # ppvOut/g_Input - GRPinput instance
    # Need to find exact address from IDA
]

# ============================================================
# Function signatures: (address, name, signature)
# name: desired IDA function name (Class::Method format)
# signature: C type string for SetType
# ============================================================
FUNC_SIGNATURES = [
    # GRPinput methods
    (0x004022B0, "GRPinput::SetMode",
     "int __thiscall GRPinput::SetMode(GRPinput *this, int mode)"),
    (0x004022C0, "GRPinput::GetKeyState",
     "short __thiscall GRPinput::GetKeyState(GRPinput *this, unsigned short key)"),
    (0x00402270, "GRPinput::SetMouseLimits",
     "int __thiscall GRPinput::SetMouseLimits(GRPinput *this, long a, long b, long c, long d)"),
    (0x004020E0, "GRPinput::Create",
     "int __thiscall GRPinput::Create(GRPinput *this, void *hInst, int hwnd, int flag)"),

    # CGameData methods
    (0x0044F430, "CGameData::Destroy",
     "void __thiscall CGameData::Destroy(CGameData *this)"),
    (0x0044FF60, "CGameData::GetMode",
     "int __thiscall CGameData::GetMode(CGameData *this)"),

    # CScreenMode methods (this type unknown, use void*)
    (0x0053C6F0, "CScreenMode::SetViewport",
     "int __thiscall CScreenMode::SetViewport(void *this, int x, int y)"),
    (0x0053C710, "CScreenMode::GetWidth",
     "int __thiscall CScreenMode::GetWidth(void *this)"),
    (0x0053C720, "CScreenMode::GetHeight",
     "int __thiscall CScreenMode::GetHeight(void *this)"),
    (0x0053CDD0, "CScreenMode::SetState",
     "int __thiscall CScreenMode::SetState(void *this, int state)"),
    (0x0053C440, "CScreenMode::CreateDevice",
     "int __thiscall CScreenMode::CreateDevice(void *this, int a, int b, int c, int d)"),
    (0x0053DEF0, "CScreenMode::Restore",
     "void __thiscall CScreenMode::Restore(void *this)"),
    (0x0053E500, "CScreenMode::GetAudioManager",
     "int __thiscall CScreenMode::GetAudioManager(void *this)"),
    (0x0053DD70, "CScreenMode::SetMode",
     "void __thiscall CScreenMode::SetMode(void *this, int mode)"),
    (0x0053EA60, "CScreenMode::AudioFadeOut",
     "void __thiscall CScreenMode::AudioFadeOut(void *this)"),
    (0x0053E950, "CScreenMode::AudioStopAll",
     "void __thiscall CScreenMode::AudioStopAll(void *this)"),
    (0x0053E490, "CScreenMode::AudioUpdate",
     "void __thiscall CScreenMode::AudioUpdate(void *this)"),

    # Logger methods
    (0x0053CC70, "Logger::Write",
     "char * __thiscall Logger::Write(void *this, char *fmt, ...)"),
    (0x0053CE90, "Logger::RegisterCallbacks",
     "int __thiscall Logger::RegisterCallbacks(void *this)"),
    (0x0053CC10, "Logger::RegisterCallback",
     "int __thiscall Logger::RegisterCallback(void *this, int pfn, char *name, char *desc)"),
    (0x0053CEF0, "Logger::FormatException",
     "char * __thiscall Logger::FormatException(char *this, char *msg, char *file, int line)"),

    # Camera methods
    (0x0041CA90, "CameraCtrl::SetDimention",
     "void __thiscall CameraCtrl::SetDimention(void *this, int w, int h)"),
    (0x0041C630, "CameraCtrl::SetAsCurrent",
     "void __thiscall CameraCtrl::SetAsCurrent(void *this, int flags)"),

    # Update subsystems (these are actually cdecl, not thiscall)
    (0x0040C230, "ScriptUpdate", None),
    (0x004105B0, "NPCAnimUpdate", None),
    (0x004181E0, "RoleSystemNotify", None),
    (0x0041C280, "InputUpdate", None),
    (0x0041D9A0, "CameraUpdate", None),
    (0x0041EB80, "UIPostUpdate", None),
    (0x00420150, "UIUpdate", None),
    (0x00422E40, "EffectUpdate", None),
    (0x0044F4C0, "SceneUpdate", None),

    # Singletons (cdecl, no this)
    (0x004BDB10, "CRenderTarget::GetInstance", None),
    (0x004BDED0, "CRenderTarget::Destroy",
     "void __thiscall CRenderTarget::Destroy(void *this)"),
    (0x004BFD20, "CRenderTarget2::GetInstance", None),
    (0x004C0400, "CRenderTarget2::Destroy",
     "void __thiscall CRenderTarget2::Destroy(void *this)"),
    (0x005415F0, "UIQuadManager::GetInstance", None),
    (0x005415C0, "UIQuadManager::Destroy",
     "void __thiscall UIQuadManager::Destroy(void *this)"),
    (0x004BE590, "ScreenEffectMgr::GetInstance", None),
    (0x004B65A0, "RenderTarget3::GetInstance", None),
    (0x004B6D30, "RenderTarget4::GetInstance", None),
    (0x0053D150, "SoundContext::GetInstance", None),
    (0x0053DF70, "CScreenMode::GetInstance", None),

    # Utility
    (0x0053CF80, "InitLogFiles", None),
    (0x0053D030, "LogMessage", None),
    (0x00540FA0, "PopMatrixStacks", None),
    (0x00540F60, "PushMatrixStacks", None),
    (0x004B65F0, "RenderTarget3::Init",
     "void __thiscall RenderTarget3::Init(void *this)"),
]


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe function signature annotation")
        log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        til = ida_typeinf.get_idati()

        # Phase 1: Import structs
        log("\n[Phase 1] Import struct definitions")
        for decl in STRUCT_DEFS:
            tinfo = ida_typeinf.tinfo_t()
            import re
            m = re.search(r'struct\s+(\w+)', decl)
            if m and ida_typeinf.parse_decl(tinfo, til, decl.strip(), ida_typeinf.PT_TYP) is not None:
                tinfo.set_named_type(til, m.group(1), ida_typeinf.NTF_REPLACE)
                log("  [+] %s" % m.group(1))

        # Phase 2: Set global variable types
        log("\n[Phase 2] Global variable types")
        for addr, type_str, name in GLOBAL_TYPES:
            cur = ida_name.get_name(addr) or ""
            if cur.startswith("dword_") or cur.startswith("unk_") or not cur:
                ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE)
            idc.SetType(addr, type_str)
            log("  [+] 0x%08X: %s (%s)" % (addr, name, type_str))

        # Phase 3: Set function names and signatures
        log("\n[Phase 3] Function names and signatures")
        named = 0
        sig_ok = 0
        for entry in FUNC_SIGNATURES:
            addr = entry[0]
            name = entry[1]
            sig = entry[2] if len(entry) > 2 else None

            # Set name
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                named += 1

            # Set signature if provided
            if sig:
                if idc.SetType(addr, sig):
                    sig_ok += 1
                    log("  [+] 0x%08X: %s" % (addr, name))
                else:
                    log("  [-] 0x%08X: sig FAILED for %s" % (addr, name))
            else:
                log("  [+] 0x%08X: %s (name only)" % (addr, name))

        log("\n[*] Named: %d, Signatures: %d" % (named, sig_ok))

        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB saved")

        # Phase 4: Re-export all functions
        log("\n[Phase 4] Re-export")
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
        named_total = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] Targets: %d (named: %d)" % (len(targets), named_total))

        exported = 0
        errors = 0
        t0 = time.time()
        for i, (ea, nm, size) in enumerate(targets):
            if (i+1) % 1000 == 0:
                log("  [%d/%d]" % (i+1, len(targets)))
            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    continue
                code = str(cfunc)
                sig = cfunc.type.dstr()
                demangled = idc.demangle_name(nm, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else nm
                safe = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
                safe = safe.replace('*', '_').replace(' ', '_').replace('?', '_')
                safe = safe.replace('@', '_').replace('$', '_').replace(',', '_')
                safe = safe.replace('(', '').replace(')', '').replace('/', '_')
                safe = safe.replace('"', '').replace("'", '').replace('\\', '_')
                while '__' in safe:
                    safe = safe.replace('__', '_')
                safe = safe.strip('_')
                if len(safe) > 100:
                    safe = safe[:100]
                filename = '%s_%08x.json' % (safe, ea)
                result = {
                    'name': display_name,
                    'address': '0x%08X' % ea,
                    'size_bytes': size,
                    'signature': sig,
                    'decompiled_c': code,
                }
                with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                    json.dump(result, f, indent=2, ensure_ascii=False)
                exported += 1
            except:
                errors += 1

        log("[*] Exported: %d, errors: %d (%.1fs)" % (exported, errors, time.time()-t0))
        log("[*] Done!")

    except Exception as e:
        log("[!] Error: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)


if __name__ == '__main__':
    main()
