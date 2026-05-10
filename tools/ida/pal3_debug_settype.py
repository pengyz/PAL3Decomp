"""Debug: check what idc.get_type returns for specific functions."""
import ida_auto, ida_name, idc, idautils

ida_auto.auto_wait()

# Check a few GRPinput functions
test_addrs = [0x00402570, 0x00402D00, 0x00403000, 0x004034E0]
for ea in test_addrs:
    name = ida_name.get_name(ea)
    cur_type = idc.get_type(ea)
    print("0x%08X %s" % (ea, name))
    print("  get_type: %s" % cur_type)
    # Also try GetType
    gt = idc.GetType(ea) if hasattr(idc, 'GetType') else 'N/A'
    print("  GetType:  %s" % gt)
    print()

idc.qexit(0)
