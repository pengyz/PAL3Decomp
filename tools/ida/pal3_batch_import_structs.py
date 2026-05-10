"""
IDAPython: Batch import class/struct definitions from PAL3A PDB into PAL3 IDA database.

Imports classes that are:
  - Small (<=256 bytes) — low risk of PAL3/PAL3A size mismatch
  - OR mostly pointer members — layout unlikely to differ between versions
  - NOT already defined with full layout in IDA

This gives Hex-Rays the type information it needs to generate proper member access
instead of (int) casts and hardcoded offsets.

Usage:
  idat.exe -A -S"pal3_batch_import_structs.py" original/PAL3.exe.i64
"""
import ida_auto
import ida_typeinf
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
PDB_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_batch_import_structs_log.txt")

# Types to skip (system/library)
SKIP_PREFIXES = ('D3D', '_D3D', 'ID3D', 'IDirect', 'IUnknown', 'CD3D', 'D3DX',
                 'std', '_IMAGE', '_LARGE', '_LIST', '_RTL', '_EXCEPTION',
                 'tag_s_', 'Concurrency')
SKIP_NAMES = {
    '_iobuf', 'FILE', 'GUID', 'IID', '_GUID', 'CRITICAL_SECTION',
    'type_info', 'exception', '_FILETIME', '_SYSTEMTIME',
}

# IDA type name mapping for PDB types
TYPE_MAP = {
    'unsigned char': 'unsigned __int8',
    'unsigned short': 'unsigned __int16',
    'unsigned long': 'unsigned __int32',
    'unsigned int': 'unsigned __int32',
    'char': '__int8',
    'short': '__int16',
    'long': '__int32',
    'int': '__int32',
    'bool': 'unsigned __int8',
    'BYTE': 'unsigned __int8',
    'WORD': 'unsigned __int16',
    'DWORD': 'unsigned __int32',
    'UINT': 'unsigned __int32',
}

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)


def should_skip(name):
    if name in SKIP_NAMES:
        return True
    for p in SKIP_PREFIXES:
        if name.startswith(p):
            return True
    return False


def build_type_decl(pdb_class):
    """Build a C struct declaration string from PDB class data."""
    name = pdb_class['name']
    size = pdb_class['size']
    members = pdb_class.get('data_members', [])

    lines = []
    lines.append("struct %s {" % name)

    prev_end = 0
    for i, m in enumerate(members):
        mname = m.get('name', '_field_%04X' % m.get('offset', 0))
        mtype = m.get('type', 'int')
        moffset = m.get('offset', 0)

        # Add padding if gap
        if moffset > prev_end:
            gap = moffset - prev_end
            lines.append("  char _pad_%04X[%d];" % (prev_end, gap))

        # Simplify type for IDA parsing
        # Handle arrays: "Type[N]"
        arr_suffix = ""
        import re
        arr_match = re.search(r'(\[\d+\](?:\[\d+\])*)$', mtype)
        if arr_match:
            arr_suffix = arr_match.group(1)
            mtype = mtype[:arr_match.start()].strip()

        # Handle templates/nested: use char[] with correct size
        if '<' in mtype or '::' in mtype:
            # Calculate size from next member offset
            if i + 1 < len(members):
                msize = members[i+1]['offset'] - moffset
            else:
                msize = size - moffset
            if msize > 0:
                lines.append("  char %s[%d];" % (mname, msize))
                prev_end = moffset + msize
            else:
                lines.append("  int %s;" % mname)
                prev_end = moffset + 4
            continue

        # Handle pointer types
        is_ptr = '*' in mtype
        if is_ptr:
            # Keep as void* for simplicity (forward decls may not exist)
            base = mtype.replace('*', '').strip()
            if base and not base.startswith('_') and base[0].isupper():
                lines.append("  %s %s%s;" % (mtype, mname, arr_suffix))
            else:
                lines.append("  void *%s%s;" % (mname, arr_suffix))
            if arr_suffix:
                # Parse array size
                import re
                nums = re.findall(r'\[(\d+)\]', arr_suffix)
                elem_count = 1
                for n in nums:
                    elem_count *= int(n)
                prev_end = moffset + 4 * elem_count
            else:
                prev_end = moffset + 4
            continue

        # Map primitive types
        mapped = TYPE_MAP.get(mtype, mtype)

        # Calculate member size for prev_end tracking
        size_map = {
            '__int8': 1, 'unsigned __int8': 1, 'char': 1,
            '__int16': 2, 'unsigned __int16': 2, 'short': 2,
            '__int32': 4, 'unsigned __int32': 4, 'int': 4, 'long': 4,
            '__int64': 8, 'unsigned __int64': 8,
            'float': 4, 'double': 8,
        }
        base_size = size_map.get(mapped, 4)

        if arr_suffix:
            import re
            nums = re.findall(r'\[(\d+)\]', arr_suffix)
            elem_count = 1
            for n in nums:
                elem_count *= int(n)
            prev_end = moffset + base_size * elem_count
            lines.append("  %s %s%s;" % (mapped, mname, arr_suffix))
        else:
            prev_end = moffset + base_size
            lines.append("  %s %s;" % (mapped, mname))

    # Final padding to reach declared size
    if prev_end < size:
        lines.append("  char _tail[%d];" % (size - prev_end))

    lines.append("};")
    return '\n'.join(lines)


def main():
    ida_auto.auto_wait()
    til = ida_typeinf.get_idati()
    log("[*] Batch import PDB struct definitions")
    log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

    # Load PDB
    with open(PDB_FILE, 'r', encoding='utf-8') as f:
        pdb = json.load(f)

    # Collect candidates
    candidates = []
    for c in pdb.get('classes', []):
        name = c.get('name', '')
        size = c.get('size', 0)
        members = c.get('data_members', [])
        if not name or '<' in name or '::' in name or size <= 1:
            continue
        if not members:
            continue
        if should_skip(name):
            continue

        # Check if already defined with full layout in IDA
        tif = ida_typeinf.tinfo_t()
        if tif.get_named_type(til, name):
            existing_size = tif.get_size()
            if existing_size >= size * 0.8:  # already has reasonable definition
                continue

        # Only import small or mostly-pointer classes
        ptr_count = sum(1 for m in members if '*' in m.get('type', ''))
        if size <= 256 or ptr_count > len(members) * 0.4:
            candidates.append(c)

    log("[*] Candidates for import: %d" % len(candidates))

    # Import
    imported = 0
    errors = 0
    for c in candidates:
        name = c['name']
        decl = build_type_decl(c)

        # First ensure all referenced types have forward declarations
        import re
        ref_types = set(re.findall(r'\b([A-Z]\w+)\s*\*', decl))
        for rt in ref_types:
            if rt != name and not should_skip(rt):
                fwd = "struct %s;" % rt
                tinfo = ida_typeinf.tinfo_t()
                ida_typeinf.parse_decl(tinfo, til, fwd, ida_typeinf.PT_TYP)

        # Parse and apply
        nerrors = idc.parse_decls(decl, idc.PT_TYP)
        if nerrors == 0:
            imported += 1
        else:
            errors += 1
            if errors <= 10:
                log("  [!] %s: parse_decls returned %d" % (name, nerrors))
                if errors <= 3:
                    log("      decl: %s" % decl[:200])

    log("")
    log("[*] Results:")
    log("  Imported: %d" % imported)
    log("  Errors: %d" % errors)
    log("  Total in IDA TIL now: check with ida_export_structs.py")

    ida_auto.auto_wait()
    idc.qexit(0)


try:
    main()
except Exception as e:
    log("[ERROR] %s" % str(e))
    import traceback
    log(traceback.format_exc())
finally:
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w') as f:
        f.write('\n'.join(log_lines))
