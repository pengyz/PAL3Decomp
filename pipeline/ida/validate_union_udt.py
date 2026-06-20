"""
Validate that IDA's UDT API supports inline union members in structs.

Tests:
1. Union referencing an existing struct type: {"union": [{"type": "tagRoleSlot", "name": "slot"}]}
2. Union with inline struct: {"union": [{"type": "int", "name": "a"}, {"type": "float", "name": "b"}]}
3. Nested union in struct: {"struct": [{"type": {"union": [...]}, "name": "inner"}]}

Usage: idat -A -S"validate_union_udt.py" PAL3A.exe.i64
"""
import ida_typeinf, ida_bytes, ida_funcs, idautils, idc
import json, os, sys, traceback

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OUTPUT_LOG = os.path.join(SCRIPT_DIR, "_logs", "union_udt_validate.txt")

til = ida_typeinf.get_idati()

def log(msg):
    with open(OUTPUT_LOG, "a") as f:
        f.write(msg + "\n")
    print(msg)

def _resolve_member_type(mtype_str, til):
    """Copied from apply_annotations.py - resolve type string to tinfo_t."""
    s = mtype_str.strip()
    if not s:
        return None
    if '<' in s or '(' in s:
        tinfo = ida_typeinf.tinfo_t()
        if tinfo.get_named_type(til, s):
            return tinfo
        return None
    array_sizes = []
    while True:
        import re
        m = re.search(r'\[(\d+)\]$', s)
        if not m:
            break
        array_sizes.insert(0, int(m.group(1)))
        s = s[:m.start()].strip()
    ptr_count = 0
    while s.endswith('*'):
        ptr_count += 1
        s = s.rstrip('*').strip()
    # Check primitive
    primitives_map = {
        'void': 0, 'char': 1, 'unsigned char': 1, 'signed char': 1,
        'short': 2, 'unsigned short': 2, 'signed short': 2,
        'int': 4, 'unsigned int': 4, 'signed int': 4,
        'long': 4, 'unsigned long': 4, 'signed long': 4,
        'float': 4, 'double': 8, '__int64': 8,
        'bool': 1, 'BYTE': 1, 'WORD': 2, 'DWORD': 4,
        '_BYTE': 1, '_WORD': 2, '_DWORD': 4,
        'HWND': 4, 'UINT': 4, 'LONG': 4,
    }
    tinfo = ida_typeinf.tinfo_t()
    if s in primitives_map:
        tinfo.create_primitive(primitives_map[s], [ida_typeinf.BTF_BYTE, ida_typeinf.BTF_WORD, ida_typeinf.BTF_DWORD, ida_typeinf.BTF_QWORD][[1,2,4,8].index(primitives_map[s]) if primitives_map[s] in [1,2,4,8] else 0])
        # Simpler: use create_type from basic type
        for bt, sz in primitives_map.items():
            if bt == s:
                if sz == 1: tinfo.create_byte()
                elif sz == 2: tinfo.create_word()
                elif sz == 4: tinfo.create_dword()
                elif sz == 8: tinfo.create_qword()
                break
    elif tinfo.get_named_type(til, s):
        pass  # tinfo already set
    else:
        return None
    # Apply pointers
    for _ in range(ptr_count):
        pt = ida_typeinf.tinfo_t()
        pt.create_ptr(tinfo)
        tinfo = pt
    # Apply arrays
    for sz in array_sizes:
        at = ida_typeinf.tinfo_t()
        if at.create_array(tinfo, sz):
            tinfo = at
    return tinfo if tinfo.is_correct() else None


def build_union_type(members, til):
    """Build a union UDT from member definitions.
    members: list of {name, type, offset?}
    Returns tinfo_t or None
    """
    udt = ida_typeinf.udt_type_data_t()
    udt.is_union = True
    
    for m in members:
        mname = m.get("name", "")
        mtype = m.get("type", "int")
        moff = m.get("offset", 0)  # not used for union (all at 0)
        
        if isinstance(mtype, dict):
            # Recursive: {"struct": [...]} or {"union": [...]}
            inner = build_composite_type(mtype, til)
            if inner is None:
                log(f"  FAILED to build inner type for member '{mname}'")
                return None
            tinfo = inner
        else:
            # String type reference
            tinfo = _resolve_member_type(mtype, til)
            if tinfo is None:
                log(f"  FAILED _resolve_member_type('{mtype}') for '{mname}'")
                return None
        
        tsz = tinfo.get_size()
        if tsz in (0, 0xFFFFFFFFFFFFFFFF):
            log(f"  FAILED: member '{mname}' type '{mtype}' has invalid size {tsz}")
            return None
        
        um = ida_typeinf.udt_member_t()
        um.name = mname
        um.offset = 0  # union: all at offset 0
        um.size = tsz * 8  # bits
        um.type = tinfo
        udt.push_back(um)
    
    result = ida_typeinf.tinfo_t()
    if not result.create_udt(udt, ida_typeinf.BTF_UNION):
        log(f"  FAILED create_udt with BTF_UNION")
        return None
    return result


def build_struct_type(members, til):
    """Build a struct UDT from member definitions."""
    udt = ida_typeinf.udt_type_data_t()
    cursor = 0
    
    for m in members:
        mname = m.get("name", "")
        mtype = m.get("type", "int")
        moff = m.get("offset")  # optional explicit offset
        
        if isinstance(mtype, dict):
            inner = build_composite_type(mtype, til)
            if inner is None:
                log(f"  FAILED to build inner type for member '{mname}'")
                return None
            tinfo = inner
        else:
            tinfo = _resolve_member_type(mtype, til)
            if tinfo is None:
                log(f"  FAILED _resolve_member_type for '{mname}'")
                return None
        
        tsz = tinfo.get_size()
        if tsz in (0, 0xFFFFFFFFFFFFFFFF):
            log(f"  FAILED: member '{mname}' has invalid size {tsz}")
            return None
        
        # Use explicit offset if provided, else sequential
        if moff is not None:
            off = moff
        else:
            off = cursor
        
        sm = ida_typeinf.udt_member_t()
        sm.name = mname
        sm.offset = off * 8
        sm.size = tsz * 8
        sm.type = tinfo
        udt.push_back(sm)
        
        cursor = max(cursor, off + tsz)
    
    udt.taudt_bits = 1024  # TAUDT_FIXED
    udt.total_size = cursor
    
    result = ida_typeinf.tinfo_t()
    if not result.create_udt(udt, ida_typeinf.BTF_STRUCT):
        log(f"  FAILED create_udt with BTF_STRUCT")
        return None
    return result


def build_composite_type(tdef, til):
    """Dispatch: tdef is {"union": [...]} or {"struct": [...]}"""
    if "union" in tdef:
        return build_union_type(tdef["union"], til)
    elif "struct" in tdef:
        return build_struct_type(tdef["struct"], til)
    log(f"  Unknown composite type key: {list(tdef.keys())}")
    return None


def test_union_in_struct():
    """Test 1: Create a struct with an inline union member."""
    log("\n=== Test 1: Struct with inline union member ===")
    
    # Build tagRoleSlot type if not exists
    role_slot = ida_typeinf.tinfo_t()
    if not role_slot.get_named_type(til, "tagRoleSlot"):
        # Create tagRoleSlot as struct { unsigned short nRoleID; }
        rs_udt = ida_typeinf.udt_type_data_t()
        rs_udt.taudt_bits = 1024
        rs_udt.total_size = 896
        
        nid = _resolve_member_type("unsigned short", til)
        if nid:
            rm = ida_typeinf.udt_member_t()
            rm.name = "nRoleID"
            rm.offset = 0
            rm.size = 2 * 8
            rm.type = nid
            rs_udt.push_back(rm)
        
        if role_slot.create_udt(rs_udt, ida_typeinf.BTF_STRUCT):
            role_slot.set_named_type(til, "tagRoleSlot", ida_typeinf.NTF_REPLACE)
            log("  Created tagRoleSlot (size={})".format(role_slot.get_size()))
    
    # Build a test struct with:
    #   union {
    #     int raw;
    #     struct tagRoleSlot slot;
    #   } m_field;
    #   float next;
    
    union_members = [
        {"name": "raw", "type": "int"},
        {"name": "slot", "type": "tagRoleSlot"},
    ]
    union_tinfo = build_union_type(union_members, til)
    if not union_tinfo:
        log("  FAILED: could not build union type")
        return False
    
    log("  Union type built successfully (size={})".format(union_tinfo.get_size()))
    
    # Now embed the union in a struct
    struct_members = [
        {"name": "m_field", "type": union_tinfo, "offset": 0},
        {"name": "next", "type": "float", "offset": union_tinfo.get_size()},
    ]
    
    test_udt = ida_typeinf.udt_type_data_t()
    test_udt.taudt_bits = 1024
    test_udt.total_size = union_tinfo.get_size() + 4
    cursor = 0
    for m in struct_members:
        mname = m["name"]
        mtype = m["type"]
        moff = m.get("offset", cursor)
        
        # Resolve type
        if isinstance(mtype, str):
            tinfo = _resolve_member_type(mtype, til)
        else:
            tinfo = mtype
        
        if not tinfo or not tinfo.is_correct():
            log(f"  FAILED: could not resolve type for '{mname}'")
            return False
        
        tsz = tinfo.get_size()
        sm = ida_typeinf.udt_member_t()
        sm.name = mname
        sm.offset = moff * 8
        sm.size = tsz * 8
        sm.type = tinfo
        test_udt.push_back(sm)
        cursor = moff + tsz
    
    result = ida_typeinf.tinfo_t()
    if not result.create_udt(test_udt, ida_typeinf.BTF_STRUCT):
        log("  FAILED: create_udt for test struct")
        return False
    
    result.set_named_type(til, "TestUnionStruct", ida_typeinf.NTF_REPLACE)
    log("  TestUnionStruct created (size={})".format(result.get_size()))
    
    # Verify member types
    verify_udt = ida_typeinf.udt_type_data_t()
    if result.get_udt_details(verify_udt):
        for i in range(verify_udt.size()):
            mm = verify_udt[i]
            mm_name = mm.get_name() or "(anon)"
            mm_type = mm.type
            log(f"    Member {i}: '{mm_name}' offset={mm.offset//8} type_size={mm_type.get_size()}")
            # Check if union member's sub-members are accessible
            if mm_name == "m_field" and mm_type.is_union():
                sub_udt = ida_typeinf.udt_type_data_t()
                if mm_type.get_udt_details(sub_udt):
                    for j in range(sub_udt.size()):
                        sub_m = sub_udt[j]
                        log(f"      Union member {j}: '{sub_m.get_name()}' offset={sub_m.offset//8} size={sub_m.size//8}")
    
    return True


def test_anon_union():
    """Test 2: Anonymous union members directly in struct."""
    log("\n=== Test 2: Anonymous union in struct ===")
    
    # Build: struct { union { int a; float b; }; int c; };
    union_members = [
        {"name": "a", "type": "int"},
        {"name": "b", "type": "float"},
    ]
    union_tinfo = build_union_type(union_members, til)
    if not union_tinfo:
        log("  FAILED: anonymous union")
        return False
    
    log("  Anonymous union type built (size={})".format(union_tinfo.get_size()))
    
    test_udt = ida_typeinf.udt_type_data_t()
    test_udt.taudt_bits = 1024
    
    # Add anonymous union member (empty name)
    usz = union_tinfo.get_size()
    um = ida_typeinf.udt_member_t()
    um.name = ""  # anonymous
    um.offset = 0
    um.size = usz * 8
    um.type = union_tinfo
    test_udt.push_back(um)
    
    um2 = ida_typeinf.udt_member_t()
    um2.name = "c"
    um2.offset = usz * 8
    um2.size = 4 * 8
    um2.type = _resolve_member_type("int", til)
    test_udt.push_back(um2)
    
    test_udt.total_size = usz + 4
    result = ida_typeinf.tinfo_t()
    if not result.create_udt(test_udt, ida_typeinf.BTF_STRUCT):
        log("  FAILED: create_udt for anon union test")
        return False
    
    result.set_named_type(til, "TestAnonUnion", ida_typeinf.NTF_REPLACE)
    log("  TestAnonUnion created (size={})".format(result.get_size()))
    
    # Verify
    verify_udt = ida_typeinf.udt_type_data_t()
    if result.get_udt_details(verify_udt):
        for i in range(verify_udt.size()):
            mm = verify_udt[i]
            mm_name = mm.get_name() or "(anon)"
            mm_type = mm.type
            log(f"    Member {i}: '{mm_name}' offset={mm.offset//8} type={mm_type.get_size()}B union={mm_type.is_union()}")
    
    return True


def test_nested_union():
    """Test 3: Nested struct containing union containing struct."""
    log("\n=== Test 3: Nested struct → union → struct ===")
    
    # Inner struct: { char _gap[140]; void *ptr; }
    inner_members = [
        {"type": {"struct": [
            {"name": "_gap", "type": "char[140]", "offset": 0},
            {"name": "ptr", "type": "void *", "offset": 140},
        ]}, "name": "overlay"}
    ]
    union_tinfo = build_union_type(inner_members, til)
    if not union_tinfo:
        log("  FAILED: nested union")
        return False
    
    log("  Nested union type built (size={})".format(union_tinfo.get_size()))
    
    test_udt = ida_typeinf.udt_type_data_t()
    test_udt.taudt_bits = 1024
    test_udt.total_size = 512
    
    um = ida_typeinf.udt_member_t()
    um.name = "m_data"
    um.offset = 0
    um.size = union_tinfo.get_size() * 8
    um.type = union_tinfo
    test_udt.push_back(um)
    
    result = ida_typeinf.tinfo_t()
    if not result.create_udt(test_udt, ida_typeinf.BTF_STRUCT):
        log("  FAILED: create_udt for nested test")
        return False
    
    result.set_named_type(til, "TestNestedUnion", ida_typeinf.NTF_REPLACE)
    log("  TestNestedUnion created (size={})".format(result.get_size()))
    return True


def test_union_export():
    """Test 4: Export via json and verify the union structure is preserved."""
    log("\n=== Test 4: Export verification ===")
    import json
    
    # Get the struct via IDA API and serialize key properties
    for name in ["TestUnionStruct", "TestAnonUnion", "TestNestedUnion"]:
        tinfo = ida_typeinf.tinfo_t()
        if not tinfo.get_named_type(til, name):
            log(f"  {name}: NOT FOUND in TIL")
            continue
        
        log(f"\n--- {name} ---")
        log(f"  size: {tinfo.get_size()}")
        
        udt = ida_typeinf.udt_type_data_t()
        if tinfo.get_udt_details(udt):
            for i in range(udt.size()):
                m = udt[i]
                mname = m.get_name() or "(anon)"
                mt = m.type
                log(f"  [{i}] '{mname}' @+{m.offset//8} sz={m.size//8} is_union={mt.is_union()} is_struct={not mt.is_union() and mt.get_size()<10000}")
                
                # Recurse into union/struct members
                if mt.is_union() or (not mt.is_union() and mt.get_udt_details(ida_typeinf.udt_type_data_t())):
                    sub_udt = ida_typeinf.udt_type_data_t()
                    if mt.get_udt_details(sub_udt):
                        for j in range(sub_udt.size()):
                            sm = sub_udt[j]
                            sm_name = sm.get_name() or "(anon)"
                            log(f"    [{j}] '{sm_name}' @+{sm.offset//8} sz={sm.size//8}")


if __name__ == "__main__":
    log("=== Union UDT API Validation ===")
    
    try:
        t1 = test_union_in_struct()
        t2 = test_anon_union()
        t3 = test_nested_union()
        
        log("\n=== Results ===")
        log(f"  Test 1 (union referencing existing struct): {'PASS' if t1 else 'FAIL'}")
        log(f"  Test 2 (anonymous union):                   {'PASS' if t2 else 'FAIL'}")
        log(f"  Test 3 (nested union in struct):             {'PASS' if t3 else 'FAIL'}")
        
        if t1 and t2 and t3:
            test_union_export()
            log("\n=== ALL TESTS PASSED ===")
        else:
            log("\n=== SOME TESTS FAILED ===")
    except Exception as e:
        log(f"\n=== EXCEPTION: {e} ===")
        traceback.print_exc()
    
    idc.qexit(0)
