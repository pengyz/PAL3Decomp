"""
Name the most-referenced sub_ functions based on calling context analysis.

Top candidates identified from code:
- sub_4B47E0 (62 refs): UI component destructor callback (passed as void(*)(void*) with size=0x248)
- sub_4B4690 (32 refs): UI component destructor callback
- sub_44BD80 (14 refs): UI item destructor (size=0x10)
- sub_431870 (10 refs): string helper (takes char* args, used with stru_BFAB60)
- sub_4318A0 (10 refs): string helper
- sub_444F60 (10 refs): UIWnd method
- sub_445E50 (10 refs): UI state method

Usage:
  idat.exe -A -S"pal3_name_top_subs.py" original/PAL3.exe.i64
"""
import ida_auto
import ida_hexrays
import ida_name
import idc
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)


def analyze_function(ea):
    """Decompile and return first few lines for identification."""
    ida_hexrays.mark_cfunc_dirty(ea)
    try:
        cfunc = ida_hexrays.decompile(ea)
        if cfunc:
            return str(cfunc)[:500]
    except:
        pass
    return ""


def main():
    ida_auto.auto_wait()
    log("[*] Analyzing top sub_ functions for naming")

    # Targets to analyze and potentially name
    targets = [
        0x4B47E0, 0x4B4690, 0x44BD80, 0x431870, 0x4318A0,
        0x444F60, 0x445E50, 0x557CA2, 0x4326A0, 0x445010,
        0x43FD90, 0x43A070, 0x43F640, 0x43F690, 0x4A1530,
        0x43EBB0, 0x44BD60, 0x4142E0, 0x432680, 0x4F2C30,
    ]

    names_to_set = []

    for ea in targets:
        name = ida_name.get_name(ea) or ""
        if name and not name.startswith("sub_"):
            log("  [skip] 0x%08X already named: %s" % (ea, name))
            continue

        code = analyze_function(ea)
        if not code:
            log("  [skip] 0x%08X: no decompile" % ea)
            continue

        # Analyze the decompiled code to determine function identity
        sig_line = code.split('\n')[0] if code else ""
        body_lines = code.split('\n')[1:10]
        body_preview = ' | '.join(l.strip() for l in body_lines if l.strip())[:200]

        log("")
        log("  0x%08X: %s" % (ea, sig_line[:80]))
        log("    body: %s" % body_preview[:150])

        # Heuristic naming based on patterns
        proposed = None

        # UI destructor pattern: Release + delete pattern
        if 'Release' in code and 'delete' in code:
            if 'UIWnd' in sig_line or 'UIItem' in sig_line:
                proposed = "UIWnd::Destroy_0x%X" % ea
            else:
                proposed = "ui_destroy_0x%X" % ea

        # String operations
        elif 'strlen' in code or 'strcpy' in code or 'memcpy' in code:
            if 'alloc' in code.lower() or 'new' in code:
                proposed = "String::Assign"
            else:
                proposed = "String::Copy"

        # Constructor pattern: memset + init
        elif 'memset' in code and 'this' in code:
            proposed = "ctor_0x%X" % ea

        # Log the analysis
        if proposed:
            names_to_set.append((ea, proposed))
            log("    -> proposed: %s" % proposed)
        else:
            log("    -> no match")

    # Apply names
    log("")
    log("[*] Applying names:")
    applied = 0
    for ea, name in names_to_set:
        if ida_name.set_name(ea, name, ida_name.SN_FORCE):
            applied += 1
            log("  [+] 0x%08X = %s" % (ea, name))
        else:
            log("  [!] 0x%08X = %s FAILED" % (ea, name))

    log("")
    log("[*] Applied: %d / %d" % (applied, len(names_to_set)))
    idc.qexit(0)

try:
    main()
except Exception as e:
    log("[ERROR] %s" % str(e))
    import traceback
    log(traceback.format_exc())
finally:
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(os.path.join(LOG_DIR, "pal3_name_top_subs_log.txt"), 'w') as f:
        f.write('\n'.join(log_lines))
