"""
Fix Scene struct: PAL3A PDB says Scene is 1094164 bytes,
but PAL3 binary analysis shows Scene functions only access offsets up to ~0x5D.
The PAL3A layout is WRONG for PAL3.

Replace with a minimal placeholder until proper binary analysis is done.
"""
import ida_auto, ida_typeinf, idc

ida_auto.auto_wait()
til = ida_typeinf.get_idati()

# Minimal Scene struct based on binary offsets found:
# +0x00: unknown (possibly vtable)
# +0x04: ptr (data begin)
# +0x08: ptr (data end)
# +0x0C: ptr (capacity)
# ... more members up to +0x5D
DECL = """
struct Scene {
  int _vftable;           // +0x00
  void *m_pDataBegin;    // +0x04 (dynamic array begin)
  void *m_pDataEnd;      // +0x08 (dynamic array end)
  void *m_pCapacity;     // +0x0C (dynamic array capacity)
  char _data[0x50];      // +0x10 to +0x60 (unknown, up to max observed offset)
};
"""

nerr = idc.parse_decls(DECL, idc.PT_TYP)
if nerr == 0:
    tif = ida_typeinf.tinfo_t()
    tif.get_named_type(til, "Scene")
    print("[+] Scene struct replaced: size=%d (was 1094164)" % tif.get_size())
else:
    print("[!] parse_decls errors: %d" % nerr)

idc.qexit(0)
