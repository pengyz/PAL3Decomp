"""
IDAPython: 测试IDA是否支持union类型定义
"""
import ida_auto, ida_typeinf

def main():
    ida_auto.auto_wait()
    print("[*] Testing IDA union support...")

    til = ida_typeinf.get_idati()

    # Test 1: 简单union前向声明
    print("\n[Test 1] Forward declaration: union TestUnion;")
    tif1 = ida_typeinf.tinfo_t()
    result1 = ida_typeinf.parse_decl(tif1, til, "union TestUnion;", ida_typeinf.PT_TYP)
    if result1 is not None:
        print("  ✓ Forward declaration SUCCESS")
        if tif1.set_named_type(til, "TestUnion", ida_typeinf.NTF_REPLACE):
            print("  ✓ set_named_type SUCCESS")
        else:
            print("  ✗ set_named_type FAILED")
    else:
        print("  ✗ Forward declaration FAILED")

    # Test 2: 完整union定义
    print("\n[Test 2] Full definition: union TestUnion { int a; float b; };")
    tif2 = ida_typeinf.tinfo_t()
    decl = "union TestUnion { int a; float b; };"
    result2 = ida_typeinf.parse_decl(tif2, til, decl, ida_typeinf.PT_TYP)
    if result2 is not None:
        print("  ✓ Full definition SUCCESS")
        print(f"  Size: {tif2.get_size()}")
        print(f"  Is union: {tif2.is_union()}")
        if tif2.set_named_type(til, "TestUnion", ida_typeinf.NTF_REPLACE):
            print("  ✓ set_named_type SUCCESS")
        else:
            print("  ✗ set_named_type FAILED")
    else:
        print("  ✗ Full definition FAILED")

    # Test 3: 尝试导入PDB中的Actor（union, 596字节）
    print("\n[Test 3] Actor from PDB (union, 596 bytes, 7 members)")
    tif3 = ida_typeinf.tinfo_t()
    actor_decl = """union Actor {
    int m_actarray;
    int m_actordata;
    int m_combatbirth;
    int m_comlayer;
    int m_acttype;
    int m_pdata;
    int m_status;
};"""
    result3 = ida_typeinf.parse_decl(tif3, til, actor_decl, ida_typeinf.PT_TYP)
    if result3 is not None:
        print("  ✓ Actor union SUCCESS")
        print(f"  Size: {tif3.get_size()}")
        if tif3.set_named_type(til, "Actor", ida_typeinf.NTF_REPLACE):
            print("  ✓ set_named_type SUCCESS")
            # 验证是否能解析
            verify_tif = ida_typeinf.tinfo_t()
            if verify_tif.get_named_type(til, "Actor"):
                print(f"  ✓ Verification: Actor found in TIL")
                print(f"    Size: {verify_tif.get_size()}")
                print(f"    Is union: {verify_tif.is_union()}")
                print(f"    Ordinal: {verify_tif.get_ordinal()}")
        else:
            print("  ✗ set_named_type FAILED")
    else:
        print("  ✗ Actor union FAILED")

    print("\n[*] Test complete")

if __name__ == "__main__":
    main()
    import ida_pro
    ida_pro.qexit(0)
