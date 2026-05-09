"""
IDAPython: Load PAL3A's type information library (.til) into PAL3 IDB.

The PAL3A IDB has all PDB types (classes with inheritance, enums, etc.)
stored in its .til file. We load this as a referenced TIL in PAL3's IDB,
which makes all those types available to Hex-Rays for decompilation.

This only affects Local Types - does NOT modify function names or signatures.
"""
import ida_auto, ida_typeinf, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
PAL3A_TIL = os.path.join(PROJECT_ROOT, "original", "PAL3A.exe.til")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_load_til_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)


def main():
    try:
        ida_auto.auto_wait()
        log("[*] Loading PAL3A types into PAL3 IDB")

        if not os.path.exists(PAL3A_TIL):
            log("[!] PAL3A.exe.til not found: %s" % PAL3A_TIL)
            log("[!] Make sure PAL3A IDB is unpacked (open it in IDA first)")
            return

        til = ida_typeinf.get_idati()
        log("[*] Current local types: %d" % ida_typeinf.get_ordinal_qty(til))

        # Method 1: Load the TIL file as a referenced library
        # This makes all types from PAL3A available
        log("[*] Loading TIL: %s" % PAL3A_TIL)

        # Copy TIL to IDA's til directory so it can be loaded
        import shutil
        ida_til_dir = os.path.join(os.path.dirname(idc.idadir("")), "til", "pc")
        if not os.path.isdir(ida_til_dir):
            ida_til_dir = os.path.join(idc.idadir(""), "til", "pc")
        if not os.path.isdir(ida_til_dir):
            # Just try loading from current location
            ida_til_dir = os.path.dirname(PAL3A_TIL)

        # Try loading directly
        loaded_til = ida_typeinf.load_til(PAL3A_TIL, None)
        if loaded_til:
            log("[+] Loaded TIL successfully")
            log("[*] TIL types: %d" % ida_typeinf.get_ordinal_qty(loaded_til))

            # Now copy types from loaded TIL into our local TIL
            src_count = ida_typeinf.get_ordinal_qty(loaded_til)
            imported = 0
            skipped = 0
            failed = 0

            for ordinal in range(1, src_count + 1):
                tif = ida_typeinf.tinfo_t()
                if not tif.get_numbered_type(loaded_til, ordinal):
                    continue

                name = tif.get_type_name()
                if not name:
                    continue

                # Skip STL/internal types
                if '<' in name or name.startswith('_') or name.startswith('std::'):
                    skipped += 1
                    continue

                # Import into local types
                err = tif.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                if err == 0:
                    imported += 1
                else:
                    failed += 1

                if imported % 100 == 0 and imported > 0:
                    log("  [%d imported...]" % imported)

            log("[*] Imported: %d, Skipped: %d, Failed: %d" % (imported, skipped, failed))
        else:
            log("[-] Failed to load TIL, trying alternative method...")

            # Method 2: Parse the TIL as a type library reference
            # add_til() adds it as a dependency
            result = ida_typeinf.add_til(PAL3A_TIL, ida_typeinf.ADDTIL_DEFAULT)
            if result:
                log("[+] Added TIL as reference: %s" % PAL3A_TIL)
            else:
                log("[-] add_til also failed")

                # Method 3: Try importing individual types via idc
                log("[*] Attempting idc.import_type method...")
                # This requires the TIL to be in IDA's search path
                log("[-] Cannot load PAL3A types automatically.")
                log("[*] Manual steps needed:")
                log("    1. Close PAL3A in IDA")
                log("    2. Run this script again (it will open the packed .i64)")

        log("[*] Final local types: %d" % ida_typeinf.get_ordinal_qty(til))
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] Saved IDB")

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
