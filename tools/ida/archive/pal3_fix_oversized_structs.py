"""
Replace oversized PAL3A structs with minimal placeholders.

These structs have massive size differences between PAL3A PDB and PAL3 binary:
- Scene: 1094164 → ~96 (already fixed)
- CEffect: 245800 → ~256
- CCBSystem: 90840 → ~512
- CEffMgr: 43312 → ~1024

The PAL3A sizes are WRONG for PAL3. Replace with placeholders
sized to cover the maximum observed binary offset, padded to a safe margin.
"""
import ida_auto, ida_typeinf, idc

ida_auto.auto_wait()

# (name, max_binary_offset, safe_size_estimate)
# safe_size = max_offset * 2 (conservative, covers unobserved members)
FIXES = [
    # Scene already fixed
    ("CEffect", 0xED, 0x200),       # max binary +0xED, set to 512
    ("CCBSystem", 0x1B8, 0x400),    # max binary +0x1B8, set to 1024
    ("CEffMgr", 0x408, 0x900),      # max binary +0x408, set to 2304
    ("PropUI", 0x43C, 0x900),       # max binary +0x43C, set to 2304
    ("CEffMeteor", 0xC0, 0x200),    # max binary +0xC0, set to 512
    ("CEffCylinder", 0xC0, 0x200),  # max binary +0xC0, set to 512
    ("CEffExplosive", 0x283, 0x500),# max binary +0x283, set to 1280
]

for name, max_off, safe_size in FIXES:
    decl = "struct %s { char _data[%d]; };" % (name, safe_size)
    nerr = idc.parse_decls(decl, idc.PT_TYP)
    if nerr == 0:
        print("[+] %s: replaced (was huge, now %d bytes)" % (name, safe_size))
    else:
        print("[!] %s: parse error %d" % (name, nerr))

idc.qexit(0)
