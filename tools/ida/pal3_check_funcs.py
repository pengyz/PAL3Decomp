"""
IDAPython: Quick check that our manually annotated function names/signatures are intact.
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_check_funcs_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Sample of functions from our iter scripts
CHECK_FUNCS = [
    (0x00404FF0, "PAL3::InitGFX"),
    (0x00405490, "PAL3::Create"),
    (0x004055D0, "PAL3::Update"),
    (0x00405730, "PAL3::Render"),
    (0x00405810, "PAL3::Destroy"),
    (0x004022F0, "GRPinput::GetMousePos"),
    (0x004EF980, "CCBRoleState::CalcHealAmount"),
    (0x004F3020, "CCBRoleState::CalcAttackPower"),
    (0x00536D00, "Actor::SetTimeScale"),
    (0x0053C440, "CScreenMode::CreateDevice"),
    (0x004FC940, "CCBSystem::GetStageRoleByIdx"),
    (0x00431FB0, "PalScript::Update"),
    (0x00536560, "Actor::ProcessFrame"),
    (0x004DFE00, "CCBAIWindow::SetText"),
    (0x0041CA90, "CameraCtrl::SetDimention"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Checking annotated function names")

        found = 0
        missing = 0
        wrong = 0

        for addr, expected_name in CHECK_FUNCS:
            actual = ida_name.get_name(addr)
            if actual == expected_name:
                found += 1
                # Also check signature
                sig = idc.get_type(addr)
                log("  [+] 0x%08X: %s  sig=%s" % (addr, actual, sig if sig else "(none)"))
            elif actual and not actual.startswith("sub_"):
                wrong += 1
                log("  [?] 0x%08X: expected=%s actual=%s" % (addr, expected_name, actual))
            else:
                missing += 1
                log("  [-] 0x%08X: expected=%s actual=%s" % (addr, expected_name, actual))

        log("")
        log("[*] Result: %d OK, %d wrong name, %d missing" % (found, wrong, missing))

    except Exception as e:
        import traceback
        log("[!] %s" % str(e))
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
