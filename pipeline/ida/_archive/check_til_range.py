"""
IDAPython: 检查TIL中ordinal的范围，找出orphan ordinal来自哪里
"""
import ida_auto, ida_typeinf

def main():
    ida_auto.auto_wait()
    print("[*] Checking TIL ordinal range...")

    til = ida_typeinf.get_idati()
    if not til:
        print("[!] No TIL")
        return

    qty = ida_typeinf.get_ordinal_qty(til)
    print(f"[*] Total ordinals in local TIL: {qty}")

    # 检查orphan ordinal是否超出TIL范围
    orphans = [115, 821, 116, 133, 105, 114, 101, 123, 129, 127, 136, 138]

    print(f"\n[*] Orphan ordinal analysis:")
    for ord_num in orphans:
        status = "IN RANGE" if ord_num <= qty else "OUT OF RANGE"
        print(f"  #{ord_num}: {status} (qty={qty})")

    # 检查前20个ordinal是否有类型名
    print(f"\n[*] First 20 ordinals in TIL:")
    for i in range(1, min(21, qty + 1)):
        name = ida_typeinf.get_numbered_type_name(til, i)
        print(f"  #{i}: {name if name else '(no name)'}")

    # 检查orphan ordinal附近的ordinal
    print(f"\n[*] Checking ordinals around #115:")
    for i in range(110, 120):
        if i <= qty:
            name = ida_typeinf.get_numbered_type_name(til, i)
            tif = ida_typeinf.tinfo_t()
            exists = tif.get_numbered_type(til, i)
            print(f"  #{i}: name='{name if name else 'None'}' exists={exists}")
        else:
            print(f"  #{i}: OUT OF RANGE")

if __name__ == "__main__":
    main()
    import ida_pro
    ida_pro.qexit(0)
