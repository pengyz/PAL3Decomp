"""
IDAPython Phase 2 Step 3: Fix __userpurge/__usercall Calling Conventions

Reads diagnosis_report.json and fixes USERPURGE_WRONG entries by applying
correct calling conventions based on PDB function signatures.

Strategy:
  1. Load diagnosis report (USERPURGE_WRONG entries with conf >= 0.8 and has_pdb_signature)
  2. Load PDB functions by address
  3. For each target:
     - Determine correct calling convention (__thiscall for methods, __cdecl for functions)
     - Clear any existing type with idc.SetType(addr, "")
     - Apply new signature with idc.SetType(addr, sig)
     - On failure: fallback to replacing calling convention in current type
     - Mark dirty with ida_hexrays.mark_cfunc_dirty(addr)
  4. Log all results and save database if success > 0

Modes:
  --dry-run (default): Show what would be fixed without modifying
  --execute: Actually apply fixes and save database

Output: _logs/fix_callconv_log.txt
"""

import sys
import os
import json
import traceback
import builtins

# IDA imports
import idc
import ida_auto
import ida_typeinf
import ida_hexrays
import ida_funcs
import ida_name
import idautils

# Add tools/ida to path
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, SCRIPT_DIR)

import ida_common

# ============================================================================
# Configuration
# ============================================================================

DIAGNOSIS_REPORT = os.path.join(ida_common.LOG_DIR, "diagnosis_report.json")
LOG_FILE = os.path.join(ida_common.LOG_DIR, "fix_callconv_log.txt")

# Type mapping for normalization
TYPE_MAP = {
    'void': 'void',
    'int': 'int',
    'uint': 'unsigned int',
    'long': 'long',
    'ulong': 'unsigned long',
    'short': 'short',
    'ushort': 'unsigned short',
    'char': 'char',
    'uchar': 'unsigned char',
    'float': 'float',
    'double': 'double',
    'bool': '_BOOL1',
    'BOOL': 'int',
    'BYTE': 'unsigned char',
    'WORD': 'unsigned short',
    'DWORD': 'unsigned long',
    'LONG': 'long',
    'UINT': 'unsigned int',
    'HWND': 'HWND',
    'HINSTANCE': 'HINSTANCE',
    'LPARAM': 'LPARAM',
    'WPARAM': 'WPARAM',
    'LRESULT': 'LRESULT',
    'HANDLE': 'HANDLE',
    'LPCSTR': 'LPCSTR',
    'LPSTR': 'LPSTR',
    'LPVOID': 'LPVOID',
    'HDC': 'HDC',
    'HRESULT': 'HRESULT',
}

# ============================================================================
# Utility Functions
# ============================================================================


def normalize_type(pdb_type):
    """Convert PDB type to IDA-compatible C type"""
    if not pdb_type:
        return None

    t = pdb_type.strip()
    t = t.replace('virtual ', '').replace('static ', '')

    if t in TYPE_MAP:
        return TYPE_MAP[t]

    # Pointer types
    if t.endswith(' *') or t.endswith(' **'):
        base = t
        stars = ''
        while base.endswith(' *'):
            base = base[:-2]
            stars += ' *'

        base = base.strip()
        if base.startswith('class '):
            base = base[6:]
        elif base.startswith('struct '):
            base = base[7:]
        elif base.startswith('const class '):
            base = base[12:]
            stars = ' const' + stars
        elif base.startswith('const struct '):
            base = base[13:]
            stars = ' const' + stars
        elif base.startswith('const '):
            base = base[6:]
            if base in TYPE_MAP:
                return 'const ' + TYPE_MAP[base] + stars
            if '<' in base:
                return 'void' + stars
            return base + stars

        if '<' in base:
            return 'void' + stars
        if base in TYPE_MAP:
            return TYPE_MAP[base] + stars
        if base.replace('_', '').replace('::', '').isalnum():
            return base + stars
        return 'void' + stars

    # Reference -> pointer
    if t.endswith(' &'):
        inner = t[:-2].strip()
        result = normalize_type(inner + ' *')
        return result

    # const without pointer
    if t.startswith('const '):
        inner = normalize_type(t[6:])
        if inner:
            return 'const ' + inner
        return None

    if t.startswith('class '):
        name = t[6:].strip()
        if '<' in name:
            return None
        return name

    if t.startswith('struct '):
        name = t[7:].strip()
        if '<' in name:
            return None
        return name

    if t.startswith('enum '):
        return 'int'

    # Template types
    if '<' in t:
        return None

    # Simple identifier
    if t.replace('_', '').isalnum() and not t[0].isdigit():
        if t in TYPE_MAP:
            return TYPE_MAP[t]
        return t

    return None


def build_signature(pdb_func, class_name):
    """Build IDA function signature from PDB function info

    Returns: (ret_type, calling_conv, safe_name, param_list) or None if failed
    """
    name = pdb_func.get('name', '')
    if not name:
        return None

    ret_type_str = pdb_func.get('return_type', '')
    params = pdb_func.get('parameters', [])
    is_method = bool(class_name)

    # Determine return type
    # Destructors should have void return
    if '~' in name or 'destructor' in ret_type_str.lower():
        ret_type = 'void'
    else:
        ret_type = normalize_type(ret_type_str) if ret_type_str else 'int'
        if not ret_type or ret_type == 'void *':
            ret_type = 'int'

    # Determine calling convention
    if is_method:
        calling_conv = '__thiscall'
    else:
        calling_conv = '__cdecl'

    # Build safe name
    safe_name = name.replace('::', '_').replace('<', '_').replace('>', '_')
    safe_name = safe_name.replace('~', '_dtor_').replace(' ', '_')

    # Build parameter list
    param_list = []
    if is_method and class_name:
        param_list.append(f'{class_name} *this')

    for p in params:
        p_type = normalize_type(p.get('type', ''))
        p_name = p.get('name', '')
        if not p_type:
            p_type = 'int'
        if p_name and p_name.replace('_', '').isalnum() and not p_name[0].isdigit():
            param_list.append(f'{p_type} {p_name}')
        else:
            param_list.append(p_type)

    return (ret_type, calling_conv, safe_name, param_list)


def load_pdb_functions():
    """Load PDB functions by address"""
    try:
        with open(ida_common.PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        addr_to_func = {}
        for func in pdb_data.get('functions', []):
            addr_str = func.get('address', '')
            if not addr_str:
                continue
            try:
                addr = int(addr_str, 16)
            except ValueError:
                continue
            addr_to_func[addr] = func

        return addr_to_func
    except Exception as e:
        print(f"[!] Failed to load PDB: {e}")
        return {}


def load_diagnosis_report():
    """Load diagnosis report and extract USERPURGE_WRONG entries"""
    try:
        with open(DIAGNOSIS_REPORT, 'r', encoding='utf-8') as f:
            report = json.load(f)

        targets = []
        for addr_str, func_info in report.get('functions', {}).items():
            try:
                addr = int(addr_str, 2 if addr_str.startswith('0b') else 16)
            except ValueError:
                continue

            # Extract labels
            for label_entry in func_info.get('labels', []):
                if isinstance(label_entry, list) and len(label_entry) >= 2:
                    label, confidence = label_entry[0], label_entry[1]
                    details = label_entry[2] if len(label_entry) > 2 else {}
                else:
                    continue

                # Filter: USERPURGE_WRONG, conf >= 0.8, has_pdb_signature
                if label == "USERPURGE_WRONG" and confidence >= ida_common.CONF_AUTO_FIX:
                    has_pdb_sig = details.get('has_pdb_signature', False)
                    if has_pdb_sig:
                        targets.append((addr, func_info['name'], confidence))

        return targets
    except Exception as e:
        print(f"[!] Failed to load diagnosis report: {e}")
        return []


# ============================================================================
# Main Execution
# ============================================================================


def main():
    log_lines = []

    def log(msg):
        msg_str = str(msg)
        log_lines.append(msg_str)
        print(msg_str)

    # Parse command-line arguments
    execute_mode = '--execute' in sys.argv
    dry_run_mode = '--dry-run' in sys.argv or not execute_mode

    try:
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")
        log(f"[*] Mode: {'EXECUTE' if execute_mode else 'DRY-RUN'}")
        log("")

        # Load diagnosis report
        targets = load_diagnosis_report()
        log(f"[*] Found {len(targets)} USERPURGE_WRONG targets (conf >= {ida_common.CONF_AUTO_FIX})")

        if not targets:
            log("[*] No targets to fix")
            log_lines.append("")
            os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
            with open(LOG_FILE, "w", encoding="utf-8") as f:
                f.write("\n".join(log_lines))
            return

        # Load PDB functions
        pdb_funcs = load_pdb_functions()
        log(f"[*] Loaded {len(pdb_funcs)} PDB functions")
        log("")

        # Process targets
        success_count = 0
        fallback_count = 0
        fail_count = 0
        skip_count = 0
        dbg_errors = []

        for addr, ida_name_str, confidence in sorted(targets):
            pdb_func = pdb_funcs.get(addr)
            if not pdb_func:
                skip_count += 1
                if len(dbg_errors) < 10:
                    dbg_errors.append(f"  0x{addr:08X} {ida_name_str} [skip]: no PDB data")
                continue

            # Extract class name
            pdb_name = pdb_func.get('name', '')
            class_name = pdb_name.split('::')[0] if '::' in pdb_name else ''

            # Build signature components
            sig_parts = build_signature(pdb_func, class_name)
            if not sig_parts:
                skip_count += 1
                if len(dbg_errors) < 10:
                    dbg_errors.append(f"  0x{addr:08X} {ida_name_str} [skip]: bad signature")
                continue

            ret_type, calling_conv, safe_name, param_list = sig_parts

            # Format full signature
            if param_list:
                params_str = ', '.join(param_list)
            else:
                params_str = 'void'

            full_sig = f'{ret_type} {calling_conv} {safe_name}({params_str});'

            if dry_run_mode:
                log(f"[DRY] 0x{addr:08X} {ida_name_str} (conf={confidence:.2f})")
                log(f"      -> {full_sig}")
            else:
                try:
                    # Clear existing type
                    idc.SetType(addr, "")

                    # Apply new signature
                    result = idc.SetType(addr, full_sig)
                    if result:
                        success_count += 1
                        ida_hexrays.mark_cfunc_dirty(addr)
                        log(f"[OK] 0x{addr:08X} {ida_name_str}")
                    else:
                        # Fallback: replace calling convention in current type
                        tif = ida_typeinf.tinfo_t()
                        if ida_typeinf.get_tinfo(tif, addr):
                            current_type = str(tif)
                            # Try to replace __userpurge with __thiscall or __usercall with __cdecl
                            if '__userpurge' in current_type:
                                fallback_sig = current_type.replace('__userpurge', calling_conv)
                            elif '__usercall' in current_type:
                                fallback_sig = current_type.replace('__usercall', calling_conv)
                            else:
                                fallback_sig = None

                            if fallback_sig:
                                fallback_result = idc.SetType(addr, fallback_sig)
                                if fallback_result:
                                    fallback_count += 1
                                    ida_hexrays.mark_cfunc_dirty(addr)
                                    log(f"[FB] 0x{addr:08X} {ida_name_str} [fallback]")
                                else:
                                    fail_count += 1
                                    if len(dbg_errors) < 10:
                                        dbg_errors.append(
                                            f"  0x{addr:08X} {ida_name_str} [fail]: both methods failed"
                                        )
                            else:
                                fail_count += 1
                                if len(dbg_errors) < 10:
                                    dbg_errors.append(
                                        f"  0x{addr:08X} {ida_name_str} [fail]: no userpurge/usercall found"
                                    )
                        else:
                            fail_count += 1
                            if len(dbg_errors) < 10:
                                dbg_errors.append(
                                    f"  0x{addr:08X} {ida_name_str} [fail]: no current type"
                                )
                except Exception as e:
                    fail_count += 1
                    if len(dbg_errors) < 10:
                        dbg_errors.append(f"  0x{addr:08X} {ida_name_str} [error]: {str(e)[:40]}")

        log("")
        log("[*] Summary:")
        log(f"  Success:  {success_count}")
        log(f"  Fallback: {fallback_count}")
        log(f"  Failed:   {fail_count}")
        log(f"  Skipped:  {skip_count}")
        log(f"  Total:    {len(targets)}")

        if dbg_errors:
            log("")
            log("[*] Error details (first 10):")
            for e in dbg_errors:
                log(e)

        # Save database if execute mode and made changes
        if execute_mode and (success_count + fallback_count) > 0:
            log("")
            log("[*] Saving IDA database...")
            idc.save_database(idc.get_idb_path(), 0)
            log("[*] Database saved")

    except Exception as e:
        log(f"[!] Error: {e}")
        log(traceback.format_exc())

    # Write log file
    log("")
    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    # Standard pipeline exit pattern
    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
