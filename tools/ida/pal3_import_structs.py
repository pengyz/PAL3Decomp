"""
IDAPython: Import class struct definitions from PAL3A PDB into PAL3 IDB.

Uses udt_type_data_t API to set exact member offsets (no parsing, no padding).
Reads from asm/pal3a/pdb_export.json (classes with inheritance + struct types).
"""
import ida_auto, ida_typeinf, idc, os, json, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
PDB_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_import_structs_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Type mapping for basic types
TYPE_MAP = {
    'uchar': ('unsigned char', 1),
    'uint': ('unsigned int', 4),
    'ulong': ('unsigned long', 4),
    'ushort': ('unsigned short', 2),
    'long': ('long', 4),
    'int': ('int', 4),
    'float': ('float', 4),
    'double': ('double', 8),
    'char': ('char', 1),
    'short': ('short', 2),
    'bool': ('bool', 1),
    'BOOL': ('int', 4),
    'BYTE': ('unsigned char', 1),
    'WORD': ('unsigned short', 2),
    'DWORD': ('unsigned long', 4),
    'HWND': ('void *', 4),
    'HINSTANCE': ('void *', 4),
    'HANDLE': ('void *', 4),
    'HRESULT': ('long', 4),
    '__int64': ('__int64', 8),
    'unsigned __int64': ('unsigned __int64', 8),
}


def make_tinfo(type_str, til, all_class_names):
    """Create a tinfo_t for a given PDB type string."""
    t = type_str.strip()
    if not t:
        return None

    tif = ida_typeinf.tinfo_t()

    # Pointer types
    is_ptr = False
    base_t = t
    if t.endswith(' *'):
        is_ptr = True
        base_t = t[:-2].strip()
    elif t.endswith('*'):
        is_ptr = True
        base_t = t[:-1].strip()

    # Array + pointer: "Type[N] *" -> pointer
    m = re.match(r'^(.+?)\[\d+\]\s*\*$', t)
    if m:
        # Pointer to array element type -> just void*
        tif.create_ptr(ida_typeinf.tinfo_t(ida_typeinf.BT_VOID))
        return tif

    # Array: "type[N]" or "type[N][M]"
    arr_match = re.match(r'^(.+?)(\[\d+\](?:\[\d+\])*)$', t)
    if arr_match and not is_ptr:
        base = arr_match.group(1).strip()
        dims = [int(x) for x in re.findall(r'\[(\d+)\]', arr_match.group(2))]
        # Get base type
        base_tif = make_tinfo(base, til, all_class_names)
        if not base_tif:
            base_tif = ida_typeinf.tinfo_t(ida_typeinf.BT_INT8)  # fallback char
        # Build array from innermost
        result = base_tif
        for dim in reversed(dims):
            arr_tif = ida_typeinf.tinfo_t()
            arr_tif.create_array(result, dim)
            result = arr_tif
        return result

    if is_ptr:
        # Create pointer to base type
        base_tif = ida_typeinf.tinfo_t()
        # Try named type first
        if base_t in all_class_names:
            if base_tif.get_named_type(til, base_t):
                ptr_tif = ida_typeinf.tinfo_t()
                ptr_tif.create_ptr(base_tif)
                return ptr_tif
        # Try basic types
        if base_t in TYPE_MAP:
            c_name = TYPE_MAP[base_t][0]
            if ida_typeinf.parse_decl(base_tif, til, c_name + " x;", 0) is not None:
                ptr_tif = ida_typeinf.tinfo_t()
                ptr_tif.create_ptr(base_tif)
                return ptr_tif
        # Fallback: void*
        tif.create_ptr(ida_typeinf.tinfo_t(ida_typeinf.BT_VOID))
        return tif

    # Non-pointer, non-array: scalar or struct
    if t in TYPE_MAP:
        c_name = TYPE_MAP[t][0]
        if ida_typeinf.parse_decl(tif, til, c_name + " x;", 0) is not None:
            return tif
    # Try named type
    if t in all_class_names:
        if tif.get_named_type(til, t):
            return tif
    # Fallback: int
    tif.create_simple_type(ida_typeinf.BT_INT32)
    return tif


def import_class(cls, til, all_class_names):
    """Import one class as a UDT with exact offsets."""
    name = cls['name']
    members = cls.get('data_members', [])
    bases = cls.get('bases', []) or []
    size = cls.get('size', 0)

    udt = ida_typeinf.udt_type_data_t()

    # Base classes as members (with baseclass flag)
    for base in bases:
        base_name = base['name']
        base_offset = base.get('offset', 0)

        member = ida_typeinf.udt_member_t()
        member.name = "baseclass_%s" % re.sub(r'[^a-zA-Z0-9_]', '_', base_name)
        member.offset = base_offset * 8  # bits

        # Try to get base class type
        base_tif = ida_typeinf.tinfo_t()
        if base_name in all_class_names and base_tif.get_named_type(til, base_name):
            member.type = base_tif
            base_size = base_tif.get_size()
            member.size = base_size * 8 if base_size > 0 else 4 * 8
        else:
            # Unknown base - use int placeholder
            member.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT32)
            member.size = 4 * 8

        member.set_baseclass()
        udt.push_back(member)

    # Data members
    for i, m in enumerate(members):
        mname = m['name']
        mtype = m['type']
        moffset = m['offset']

        # Calculate member size
        if i + 1 < len(members):
            member_size = members[i+1]['offset'] - moffset
        else:
            member_size = size - moffset if size > moffset else 4
        if member_size <= 0:
            member_size = 4

        # Sanitize name
        if not mname:
            mname = 'field_%04X' % moffset
        mname = re.sub(r'[^a-zA-Z0-9_]', '_', mname)
        if not mname or mname[0].isdigit():
            mname = '_' + mname

        member = ida_typeinf.udt_member_t()
        member.name = mname
        member.offset = moffset * 8  # bits

        # Get type
        type_tif = make_tinfo(mtype, til, all_class_names)
        if type_tif:
            member.type = type_tif
            ts = type_tif.get_size()
            if ts > 0:
                member.size = ts * 8
            else:
                member.size = member_size * 8
        else:
            member.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT32)
            member.size = member_size * 8

        udt.push_back(member)

    # Create the UDT
    tif = ida_typeinf.tinfo_t()
    if not tif.create_udt(udt, ida_typeinf.BTF_STRUCT):
        return False

    # Set named type
    err = tif.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
    return err == 0


def main():
    try:
        ida_auto.auto_wait()
        log("[*] Importing struct definitions (udt_type_data_t API)")

        with open(PDB_FILE, 'r', encoding='utf-8') as f:
            pdb = json.load(f)

        classes = pdb.get('classes', [])
        all_class_names = set(c['name'] for c in classes)
        log("[*] PDB entries: %d" % len(classes))

        til = ida_typeinf.get_idati()

        # Filter valid classes
        valid = [c for c in classes
                 if c.get('data_members')
                 and '<' not in c['name']
                 and '::' not in c['name']]
        log("[*] Valid to import: %d" % len(valid))

        # Phase 1: Forward-declare all (so cross-references work)
        fwd = 0
        for cls in classes:
            name = cls['name']
            if '<' in name or '::' in name:
                continue
            tif = ida_typeinf.tinfo_t()
            udt = ida_typeinf.udt_type_data_t()
            if tif.create_udt(udt, ida_typeinf.BTF_STRUCT):
                tif.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                fwd += 1
        log("[*] Forward-declared: %d" % fwd)

        # Phase 2: Import full definitions (small first for dependencies)
        valid.sort(key=lambda c: c.get('size', 0))

        defined = 0
        failed = 0
        for cls in valid:
            if import_class(cls, til, all_class_names):
                defined += 1
            else:
                failed += 1
            if (defined + failed) % 100 == 0:
                log("  [%d defined, %d failed...]" % (defined, failed))

        log("[*] Defined: %d, Failed: %d" % (defined, failed))

        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] Saved IDB")
        log("[*] Done")

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
