"""Debug: test different SetType formats."""
import ida_auto, ida_name, ida_typeinf, idc

ida_auto.auto_wait()
til = ida_typeinf.get_idati()

# Ensure GRPinput forward declaration exists
decl = "struct GRPinput;"
tinfo = ida_typeinf.tinfo_t()
ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
tinfo.set_named_type(til, "GRPinput", ida_typeinf.NTF_REPLACE)
print("[*] GRPinput forward decl created")

ea = 0x004034E0  # UnacquireKeyboard - simplest (void, no params besides this)
name = ida_name.get_name(ea)
print("[*] Testing on 0x%08X %s" % (ea, name))
print("  Current: %s" % idc.get_type(ea))

# Try format 1: anonymous (what we tried before)
fmt1 = "void __thiscall(GRPinput *this)"
r1 = idc.SetType(ea, fmt1)
print("  Format1 '%s': %s" % (fmt1, r1))

# Try format 2: with function name (demangled)
fmt2 = "void __thiscall GRPinput::UnacquireKeyboard(GRPinput *this)"
r2 = idc.SetType(ea, fmt2)
print("  Format2 '%s': %s" % (fmt2, r2))

# Try format 3: just the type without this explicitly named
fmt3 = "void __thiscall(GRPinput *)"
r3 = idc.SetType(ea, fmt3)
print("  Format3 '%s': %s" % (fmt3, r3))

# Check result
print("  After: %s" % idc.get_type(ea))

idc.qexit(0)
