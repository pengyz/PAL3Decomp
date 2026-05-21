"""
IDAPython: 检查Actor类型在TIL中的状态
"""
import ida_auto, ida_typeinf, idc

def main():
    ida_auto.auto_wait()
    print("[*] Checking Actor type in TIL...")

    til = ida_typeinf.get_idati()

    # Method 1: 查找Actor类型
    tif = ida_typeinf.tinfo_t()
    if tif.get_named_type(til, "Actor"):
        print("[+] Actor type found in TIL")
        print(f"    Size: {tif.get_size()}")
        print(f"    Is struct: {tif.is_struct()}")
        print(f"    Is forward decl: {tif.is_decl_struct()}")
        print(f"    dstr: {tif.dstr()[:200]}")

        # 获取ordinal
        ordinal = tif.get_ordinal()
        print(f"    Ordinal: {ordinal}")
    else:
        print("[-] Actor type NOT found in TIL")

    # Method 2: 检查函数0x0050ACF0的当前类型
    addr = 0x0050ACF0
    print(f"\n[*] Checking function at 0x{addr:08X}:")

    current_type = idc.GetType(addr)
    print(f"    Current IDA type: {current_type}")

    func_tif = ida_typeinf.tinfo_t()
    if ida_typeinf.get_tinfo(func_tif, addr):
        print(f"    tinfo dstr: {func_tif.dstr()}")

        # 检查this指针的类型
        if func_tif.is_func():
            funcdata = ida_typeinf.func_type_data_t()
            if func_tif.get_func_details(funcdata):
                print(f"    Arguments: {funcdata.size()}")
                if funcdata.size() > 0:
                    arg0 = funcdata[0]
                    print(f"    Arg 0 (this): {arg0.type.dstr()}")

                    # 如果this是指针，获取指向的类型
                    if arg0.type.is_ptr():
                        pointed = arg0.type.get_pointed_object()
                        print(f"    Pointed type: {pointed.dstr()}")
                        pointed_ordinal = pointed.get_ordinal()
                        print(f"    Pointed ordinal: {pointed_ordinal}")
    else:
        print("    No tinfo available")

if __name__ == "__main__":
    main()
    import ida_pro
    ida_pro.qexit(0)
