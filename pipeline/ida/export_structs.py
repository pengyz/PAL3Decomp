"""
IDAPython: Export all struct definitions from IDB to JSON.
Authoritative source for gen_headers — IDB has the complete picture
(PDB types + gbengine imports + annotation members).

Output: asm/pal3/ida_structs.json

Usage:
  idat -A -S"pipeline/ida/export_structs.py" original/PAL3.exe.i64
"""
import sys, os, json, traceback

# Redirect stdout/stderr to log file for debugging
_script_dir = os.path.dirname(os.path.abspath(__file__))
_log_dir = os.path.join(_script_dir, "_logs")
os.makedirs(_log_dir, exist_ok=True)
_log_path = os.path.join(_log_dir, "export_structs_log.txt")
_log_file = open(_log_path, 'w')

def log(msg):
    _log_file.write(str(msg) + '\n')
    _log_file.flush()
    print(msg)

try:
    import ida_auto, ida_typeinf, idautils, idc

    ida_auto.auto_wait()

    project_root = os.path.dirname(os.path.dirname(_script_dir))
    output_path = os.path.join(project_root, "asm", "pal3", "ida_structs.json")

    result = {}
    count = 0

    for idx, sid, name in idautils.Structs():
        size = idc.get_struc_size(sid)
        if size <= 0:
            continue

        members = []
        for offset, mname, msize in idautils.StructMembers(sid):
            # Get member type via tinfo
            tif = ida_typeinf.tinfo_t()
            member = ida_typeinf.udt_member_t()
            member.offset = offset * 8  # bytes to bits
            udm_found = False

            # Try to get type from the struct tinfo
            stinfo = ida_typeinf.tinfo_t()
            if stinfo.get_named_type(ida_typeinf.get_idati(), name):
                udt = ida_typeinf.udt_type_data_t()
                if stinfo.get_udt_details(udt):
                    for mi in range(udt.size()):
                        um = udt[mi]
                        if um.offset // 8 == offset:
                            mtype_str = um.type.dstr() if um.type else 'int'
                            udm_found = True
                            break

            if not udm_found:
                mtype_str = 'char[%d]' % msize if msize > 4 else 'int'

            members.append({
                'name': mname,
                'type': mtype_str,
                'offset': offset,
            })

        # Detect base class from tinfo
        bases = []
        stinfo = ida_typeinf.tinfo_t()
        if stinfo.get_named_type(ida_typeinf.get_idati(), name):
            udt = ida_typeinf.udt_type_data_t()
            if stinfo.get_udt_details(udt):
                for mi in range(udt.size()):
                    um = udt[mi]
                    umname = um.name
                    if umname and ('baseclass' in umname.lower() or umname.startswith('__parent')):
                        base_type = um.type.dstr() if um.type else ''
                        if base_type.startswith('struct '):
                            base_type = base_type[7:]
                        elif base_type.startswith('class '):
                            base_type = base_type[6:]
                        if base_type:
                            bases.append({'name': base_type, 'offset': um.offset // 8})

        # Filter out baseclass/vtable from members
        filtered = []
        for m in members:
            mn = m['name']
            if 'baseclass' in mn.lower() or '__parent' in mn.lower():
                continue
            if '__vftable' in mn or 'vtbl' in mn.lower():
                continue
            filtered.append(m)

        result[name] = {
            'size': size,
            'kind': 'struct',
            'data_members': filtered,
            'bases': bases,
        }
        count += 1

    log("[*] Exported %d structs" % count)

    # Enum export skipped — enums come from PDB/annotations, not IDB structs
    enum_count = 0
    log("[*] Total: %d types" % len(result))

    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(result, f, indent=2, ensure_ascii=False)
    log("[*] Written to %s" % output_path)

except Exception as e:
    log("ERROR: %s" % str(e))
    log(traceback.format_exc())

_log_file.close()
idc.qexit(0)
