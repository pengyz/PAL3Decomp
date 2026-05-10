"""
IDAPython: Batch import ALL class/struct definitions from PAL3A PDB into PAL3 IDA.

Strategy:
  1. Build dependency DAG (which structs reference which)
  2. Topological sort → import order (leaves first)
  3. For cycles: emit forward declarations first
  4. Import in order, using struct names for member types (not char[])

This ensures Hex-Rays can resolve nested member access (e.g. this->m_info.cityname)
instead of generating offset-based code (this->m_info[8]).

Usage:
  idat.exe -A -S"pal3_batch_import_structs.py" original/PAL3.exe.i64
"""
import ida_auto
import ida_typeinf
import idc
import json
import os
import re
import time
from collections import defaultdict

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
PDB_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_batch_import_structs_log.txt")

SKIP_PREFIXES = ('D3D', '_D3D', 'ID3D', 'IDirect', 'IUnknown', 'CD3D', 'D3DX',
                 'std', '_IMAGE', '_LARGE', '_LIST', '_RTL', '_EXCEPTION',
                 'tag_s_', 'Concurrency')
SKIP_NAMES = {
    '_iobuf', 'FILE', 'GUID', 'IID', '_GUID', 'CRITICAL_SECTION',
    'type_info', 'exception', '_FILETIME', '_SYSTEMTIME',
}

PRIMITIVES = {
    'int', 'unsigned int', 'long', 'unsigned long',
    'short', 'unsigned short', 'char', 'unsigned char', 'bool',
    'float', 'double', '__int64', 'unsigned __int64',
    'BYTE', 'WORD', 'DWORD', 'UINT', 'HRESULT', 'HWND', 'HANDLE',
    'void',
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


def get_member_deps(pdb_class):
    """Get set of struct names that this class depends on (value members, not pointers)."""
    deps = set()
    members = pdb_class.get('data_members', [])
    for m in members:
        mtype = m.get('type', '')
        # Pointer deps don't need full definition (forward decl suffices)
        if '*' in mtype:
            continue
        # Strip arrays
        base = re.sub(r'\[\d+\]', '', mtype).strip()
        # Skip primitives, templates, nested
        if base in PRIMITIVES or '<' in base or '::' in base:
            continue
        if not base or not base[0].isalpha():
            continue
        if should_skip(base):
            continue
        deps.add(base)
    return deps


def get_pointer_deps(pdb_class):
    """Get set of struct names referenced as pointers (need forward decl only)."""
    deps = set()
    members = pdb_class.get('data_members', [])
    for m in members:
        mtype = m.get('type', '')
        if '*' not in mtype:
            continue
        base = mtype.replace('*', '').strip()
        base = re.sub(r'\[\d+\]', '', base).strip()
        if base in PRIMITIVES or '<' in base or '::' in base:
            continue
        if not base or not base[0].isalpha():
            continue
        if should_skip(base):
            continue
        deps.add(base)
    return deps


def topological_sort(classes_dict):
    """Topological sort of classes by value-member dependencies."""
    # Build adjacency (class -> set of classes it depends on)
    deps = {}
    for name, c in classes_dict.items():
        d = get_member_deps(c)
        # Only track deps that are in our import set
        deps[name] = d & set(classes_dict.keys())

    # Kahn's algorithm
    in_degree = defaultdict(int)
    for name in classes_dict:
        in_degree[name] = 0
    for name, d in deps.items():
        for dep in d:
            in_degree[name] += 1  # wrong direction, fix below

    # Re-compute: in_degree[X] = number of classes X depends on (that are in set)
    in_degree = {name: len(d) for name, d in deps.items()}

    # Reverse graph: who depends on me?
    dependents = defaultdict(set)
    for name, d in deps.items():
        for dep in d:
            dependents[dep].add(name)

    queue = [n for n in classes_dict if in_degree.get(n, 0) == 0]
    order = []
    while queue:
        node = queue.pop(0)
        order.append(node)
        for dependent in dependents[node]:
            in_degree[dependent] -= 1
            if in_degree[dependent] == 0:
                queue.append(dependent)

    # Remaining (cycles) — append at end
    remaining = [n for n in classes_dict if n not in set(order)]
    return order, remaining


def build_type_decl(pdb_class, all_class_names):
    """Build C struct declaration using proper type names for known structs."""
    name = pdb_class['name']
    size = pdb_class['size']
    members = pdb_class.get('data_members', [])

    # Pre-compute sizes from offset gaps
    member_sizes = []
    for i, m in enumerate(members):
        if i + 1 < len(members):
            msize = members[i+1]['offset'] - m['offset']
        else:
            msize = size - m['offset']
        member_sizes.append(max(msize, 0))

    lines = []
    lines.append("struct %s {" % name)

    prev_end = 0
    for i, m in enumerate(members):
        mname = m.get('name', '_field_%04X' % m.get('offset', 0))
        mtype = m.get('type', 'int')
        moffset = m.get('offset', 0)
        msize = member_sizes[i]

        # Padding
        if moffset > prev_end:
            lines.append("  char _pad_%04X[%d];" % (prev_end, moffset - prev_end))

        # Pointer types → use typed pointer
        if '*' in mtype and '[' not in mtype:
            base = mtype.replace('*', '').strip()
            if '<' in base or '::' in base or not base or not base[0].isalpha():
                lines.append("  void *%s;" % mname)
            else:
                lines.append("  %s *%s;" % (base, mname))
            prev_end = moffset + 4
            continue

        # Pointer array
        if '*' in mtype and '[' in mtype:
            arr_m = re.search(r'\[(\d+)\]', mtype)
            count = int(arr_m.group(1)) if arr_m else 1
            base = mtype.split('*')[0].strip()
            if base and base[0].isalpha() and '<' not in base:
                lines.append("  %s *%s[%d];" % (base, mname, count))
            else:
                lines.append("  void *%s[%d];" % (mname, count))
            prev_end = moffset + 4 * count
            continue

        # Strip array suffix
        arr_match = re.search(r'(\[\d+\](?:\[\d+\])*)$', mtype)
        arr_suffix = arr_match.group(1) if arr_match else ""
        base_type = mtype[:arr_match.start()].strip() if arr_match else mtype

        # Primitive types
        if base_type in PRIMITIVES:
            lines.append("  %s %s%s;" % (base_type, mname, arr_suffix))
            prev_end = moffset + msize
            continue

        # Template/nested → char[]
        if '<' in base_type or '::' in base_type:
            if msize > 0:
                lines.append("  char %s[%d]; // %s" % (mname, msize, mtype))
            else:
                lines.append("  int %s;" % mname)
            prev_end = moffset + max(msize, 4)
            continue

        # Known struct type → use by name
        if base_type in all_class_names and base_type[0].isalpha():
            lines.append("  %s %s%s;" % (base_type, mname, arr_suffix))
            prev_end = moffset + msize
            continue

        # Unknown type → char[size]
        if msize > 0:
            lines.append("  char %s[%d]; // %s" % (mname, msize, mtype))
        else:
            lines.append("  int %s; // %s" % (mname, mtype))
        prev_end = moffset + max(msize, 4)

    # Tail padding
    if prev_end < size:
        lines.append("  char _tail[%d];" % (size - prev_end))

    lines.append("};")
    return '\n'.join(lines)


def main():
    ida_auto.auto_wait()
    til = ida_typeinf.get_idati()
    log("[*] Batch import PDB structs (DAG-ordered)")
    log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

    # Load PDB
    with open(PDB_FILE, 'r', encoding='utf-8') as f:
        pdb = json.load(f)

    # Collect all valid classes
    classes = {}
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
        if '$' in name or '?' in name:
            continue
        # CRITICAL: Only import classes WITHOUT base classes
        # Classes with inheritance have different base sizes in PAL3 vs PAL3A
        # Their member offsets are WRONG and will cause Hex-Rays misinterpretation
        if c.get('bases'):
            continue
        classes[name] = c

    log("[*] PDB classes with layout (no bases): %d" % len(classes))

    # Topological sort by value-member dependencies
    order, cycles = topological_sort(classes)
    log("[*] Topo order: %d, cycles: %d" % (len(order), len(cycles)))

    # Full import order: topo first, then cycles
    import_order = order + cycles
    all_names = set(classes.keys())

    # Phase 1: Forward declarations for ALL classes (handles cycles + pointer refs)
    fwd_decls = []
    for name in all_names:
        fwd_decls.append("struct %s;" % name)
    # Also forward-declare pointer-only deps not in our set
    for c in classes.values():
        for dep in get_pointer_deps(c):
            if dep not in all_names:
                fwd_decls.append("struct %s;" % dep)

    fwd_block = '\n'.join(fwd_decls)
    nerr = idc.parse_decls(fwd_block, idc.PT_TYP)
    log("[*] Forward declarations: %d (parse errors: %s)" % (len(fwd_decls), nerr))

    # Phase 2: Import structs in dependency order
    imported = 0
    errors = 0
    skipped = 0
    for name in import_order:
        c = classes[name]
        decl = build_type_decl(c, all_names)

        nerr = idc.parse_decls(decl, idc.PT_TYP)
        if nerr == 0:
            imported += 1
        else:
            errors += 1
            if errors <= 20:
                log("  [!] %s: %d errors" % (name, nerr))
                # Try simplified version (all non-primitive as char[])
                # Fallback: just skip it
            skipped += 1

    log("")
    log("[*] Results:")
    log("  Imported: %d / %d" % (imported, len(import_order)))
    log("  Errors: %d" % errors)
    log("  Cycle classes: %d" % len(cycles))

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
