"""Check gbGfxManager struct in IDA TIL."""
import ida_auto, ida_typeinf, idc

ida_auto.auto_wait()
til = ida_typeinf.get_idati()

tif = ida_typeinf.tinfo_t()
if tif.get_named_type(til, "gbGfxManager"):
    print("gbGfxManager: size=%d" % tif.get_size())
    if tif.is_struct():
        udt = ida_typeinf.udt_type_data_t()
        if tif.get_udt_details(udt):
            print("  Members: %d" % udt.size())
            for i in range(min(udt.size(), 10)):
                m = udt[i]
                print("  +0x%04X %s %s" % (m.offset//8, m.type.dstr(), m.name))
    else:
        print("  NOT a struct! is_decl=%s" % tif.is_decl())
else:
    print("gbGfxManager: NOT FOUND in TIL")

idc.qexit(0)
