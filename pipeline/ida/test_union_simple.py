"""
IDAPython: 最小化测试 - IDA是否支持union
"""
import ida_auto, ida_typeinf

def main():
    ida_auto.auto_wait()

    til = ida_typeinf.get_idati()

    tests = [
        ("union TestUnion;", "前向声明"),
        ("union TestUnion { int a; float b; };", "完整定义（两成员）"),
        ("union Actor { int m1; int m2; int m3; int m4; int m5; int m6; int m7; };", "Actor模拟（7成员）"),
    ]

    print("=" * 60)
    print("IDA Union Support Test")
    print("=" * 60)

    for decl, desc in tests:
        print(f"\n[Test] {desc}")
        print(f"  Decl: {decl}")

        tif = ida_typeinf.tinfo_t()
        result = ida_typeinf.parse_decl(tif, til, decl, ida_typeinf.PT_TYP)

        if result is None:
            print("  ✗ parse_decl FAILED")
            continue

        print("  ✓ parse_decl SUCCESS")

        # 尝试设置到TIL
        name = decl.split()[1].rstrip(';').split('{')[0].strip()
        if tif.set_named_type(til, name, ida_typeinf.NTF_REPLACE):
            print(f"  ✓ set_named_type SUCCESS")

            # 验证
            verify = ida_typeinf.tinfo_t()
            if verify.get_named_type(til, name):
                print(f"  ✓ Verification SUCCESS")
                print(f"    - Size: {verify.get_size()}")
                print(f"    - Is union: {verify.is_union()}")
                print(f"    - Ordinal: {verify.get_ordinal()}")
            else:
                print(f"  ✗ Verification FAILED - type not found in TIL")
        else:
            print("  ✗ set_named_type FAILED")

    print("\n" + "=" * 60)
    print("Test complete")
    print("=" * 60)

if __name__ == "__main__":
    main()
    import ida_pro
    ida_pro.qexit(0)
