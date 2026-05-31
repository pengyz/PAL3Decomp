"""
Query unknown global variable addresses in the IDB.
For each address, report: current name, type, cross-references, and size hints.
"""
import json
import idc
import idautils
import idaapi
import ida_bytes
import ida_nalt
import ida_segment
import ida_typeinf
import ida_xref

TARGETS = [0xDBAF10, 0xDBA260, 0xDBB364, 0x592E58, 0x17B1550]

def get_type_name(ea):
    """Get the type name at an address."""
    tif = ida_typeinf.tinfo_t()
    if ida_nalt.get_tinfo(tif, ea):
        return str(tif)
    return None

def get_xrefs(ea):
    """Get cross-references to an address."""
    refs = []
    for xref in idautils.XrefsTo(ea):
        func = idaapi.get_func(xref.frm)
        func_name = idc.get_func_name(xref.frm) if func else ""
        refs.append({
            "from": xref.frm,
            "type": str(xref.type),
            "func": func_name,
            "disasm": idc.generate_disasm_line(xref.frm, 0).strip()
        })
    return refs

def get_nearby_data(ea, size=64):
    """Get nearby data items to understand layout."""
    nearby = []
    for off in range(0, size, 4):
        addr = ea + off
        name = idc.get_name(addr)
        dword_val = ida_bytes.get_dword(addr)
        nearby.append({
            "offset": off,
            "name": name or "",
            "dword": dword_val,
            "is_code": ida_bytes.is_code(ida_bytes.get_flags(addr))
        })
    return nearby

def estimate_size(ea):
    """Estimate the size of a data structure at ea by scanning forward."""
    max_size = 0
    seg = ida_segment.getseg(ea)
    if not seg:
        return None
    end = seg.end_ea
    # Scan for the next named item after ea
    next_name = None
    for addr in range(ea + 4, min(ea + 0x10000, end), 4):
        if idc.get_name(addr):
            next_name = addr
            break
    if next_name:
        max_size = next_name - ea
    else:
        max_size = min(end - ea, 0x10000)
    return max_size

def main():
    results = {}
    for ea in TARGETS:
        info = {
            "address": "0x%X" % ea,
            "current_name": idc.get_name(ea) or "(none)",
            "type": get_type_name(ea),
            "segment": idc.get_segm_name(ea),
            "flags": ida_bytes.get_flags(ea),
            "is_data": ida_bytes.is_data(ida_bytes.get_flags(ea)),
            "is_unknown": ida_bytes.is_unknown(ida_bytes.get_flags(ea)),
            "dword_value": ida_bytes.get_dword(ea),
            "estimated_size": estimate_size(ea),
            "xrefs": get_xrefs(ea),
            "nearby_data": get_nearby_data(ea, 32)
        }
        results["0x%X" % ea] = info
        print("=== 0x%X ===" % ea)
        print("  Name: %s" % info["current_name"])
        print("  Type: %s" % info["type"])
        print("  Seg: %s" % info["segment"])
        print("  Dword: 0x%X" % info["dword_value"])
        print("  Est size: %s" % info["estimated_size"])
        print("  Xrefs (%d):" % len(info["xrefs"]))
        for x in info["xrefs"][:10]:
            print("    0x%X (%s): %s" % (x["from"], x["func"], x["disasm"]))
        print()

    # Write results to JSON
    out_path = idc.get_idb_path().replace(".i64", "") + "_addr_query.json"
    with open(out_path, 'w') as f:
        json.dump(results, f, indent=2, ensure_ascii=False)
    print("Results written to: %s" % out_path)

if __name__ == "__main__":
    main()
    idc.qexit(0)
