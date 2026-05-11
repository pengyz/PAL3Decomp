"""
Fix CCBUI struct for PAL3.

Binary analysis shows:
- Min member offset: +0x1D (PAL3A PDB says first member at +0x48 — MISMATCH!)
- Max member offset: +0xA44
- Estimated size: ~2648 bytes

Since PAL3A PDB offsets don't match PAL3, use a placeholder struct
of the correct size. Let Hex-Rays use offset-based access (more honest
than wrong member names at wrong offsets).
"""
import ida_auto, ida_typeinf, idc

ida_auto.auto_wait()

# Simple placeholder with correct size — no misleading member names
DECL = """
struct CCBUI {
  char _data[2664];
};
"""

nerr = idc.parse_decls(DECL, idc.PT_TYP)
if nerr == 0:
    til = ida_typeinf.get_idati()
    tif = ida_typeinf.tinfo_t()
    tif.get_named_type(til, "CCBUI")
    print("[+] CCBUI: size=%d (placeholder, offsets need binary analysis)" % tif.get_size())
else:
    print("[!] CCBUI parse errors: %d" % nerr)

idc.qexit(0)
