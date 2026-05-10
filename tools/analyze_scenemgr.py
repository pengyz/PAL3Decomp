#!/usr/bin/env python3
"""
Analyze SceneMgr struct layout from PAL3.exe binary.

Strategy:
  1. Find all functions referencing g_SceneMgr (0x00C04390) from decomp data
  2. Read their machine code from PAL3.exe
  3. Find all 4-byte immediates that point into the SceneMgr address range
  4. Classify the access type (MOV ECX=this, PUSH addr, LEA, read DWORD, etc.)
  5. Detect repeating stride patterns (arrays)
  6. Cross-reference with PAL3A PDB member names
  7. Output proposed struct layout with semantic annotations

Results:
  SceneMgr is approximately 43-51KB. Key structure:
  - Header: 7 DWORD pointers (+0x00 to +0x18)
  - Main array: 5 elements × 0x580 bytes (stride 1408) at +0x288
  - Embedded CCBAI object at +0x1BA0 (= array elem[4] + 0x318)
  - Scene rendering data ending around +0xA930
  - Possible extension to ~0xC944

Usage:
  python tools/analyze_scenemgr.py [--verbose] [--ida-script]
"""

import json
import os
import re
import struct
import sys
from collections import defaultdict, Counter
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
PAL3_EXE = PROJECT_ROOT / "original" / "PAL3.exe"
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
PDB_FILE = PROJECT_ROOT / "asm" / "pal3a" / "pdb_export.json"

IMAGE_BASE = 0x400000
SCENEMGR_ADDR = 0x00C04390
MAX_STRUCT_SIZE = 0x20000  # 128KB max search range

# Section info
TEXT_VA_START = 0x401000
TEXT_VA_END = 0x401000 + 0x1685D0


def va_to_file_offset(va):
    return va - IMAGE_BASE


def find_scenemgr_functions():
    """Find all functions that reference g_SceneMgr from decomp data."""
    functions = []
    for f in sorted(DECOMP_DIR.glob("*.json")):
        try:
            d = json.load(open(f, encoding='utf-8'))
            body = d.get('decompiled_c', '')
            name = d.get('name', '')
            addr_str = d.get('address', '')
            size = d.get('size_bytes', 0)
            if 'g_SceneMgr' in body or 'SceneMgr' in name:
                addr = int(addr_str, 16) if addr_str.startswith('0x') else int(addr_str)
                if TEXT_VA_START <= addr < TEXT_VA_END and size > 0:
                    functions.append({
                        'name': name,
                        'addr': addr,
                        'size': size,
                    })
        except Exception:
            continue
    return functions


def classify_access(code, pos):
    """Given position of a 4-byte SceneMgr address in code, classify the instruction."""
    if pos < 1:
        return 'unknown', 4

    prev1 = code[pos-1]
    access_size = 4

    # Single-byte opcode before the address
    if prev1 == 0x68:
        return 'push_addr', 0  # push imm32 (passing address)
    if prev1 == 0xA1:
        return 'mov_eax_mem', 4  # mov eax, [addr]
    if prev1 == 0xA3:
        return 'mov_mem_eax', 4  # mov [addr], eax
    if prev1 == 0xB8:
        return 'mov_eax_imm', 0  # mov eax, imm32
    if prev1 == 0xB9:
        return 'mov_ecx_imm', 0  # mov ecx, imm32 (THIS pointer!)
    if prev1 == 0xBA:
        return 'mov_edx_imm', 0
    if prev1 == 0xBB:
        return 'mov_ebx_imm', 0
    if prev1 == 0xBE:
        return 'mov_esi_imm', 0
    if prev1 == 0xBF:
        return 'mov_edi_imm', 0
    if prev1 == 0xBD:
        return 'mov_ebp_imm', 0

    if pos < 2:
        return 'unknown', 4

    prev2 = code[pos-2:pos]

    # Two-byte opcode patterns with ModRM for [disp32] (mod=00, rm=101)
    modrm = prev2[1]
    opcode = prev2[0]

    if (modrm & 0xC7) == 0x05:  # mod=00, rm=101 → [disp32]
        reg = (modrm >> 3) & 7
        if opcode == 0x8B:
            return f'mov_r{reg}_mem', 4
        if opcode == 0x89:
            return f'mov_mem_r{reg}', 4
        if opcode == 0x8D:
            return f'lea_r{reg}', 0
        if opcode == 0x3B:
            return f'cmp_r{reg}_mem', 4
        if opcode == 0x39:
            return f'cmp_mem_r{reg}', 4
        if opcode == 0x01:
            return 'add_mem', 4
        if opcode == 0x29:
            return 'sub_mem', 4
        if opcode == 0xFF:
            if reg == 0:
                return 'inc_mem', 4
            if reg == 1:
                return 'dec_mem', 4
            if reg == 6:
                return 'push_mem', 4
            if reg == 2:
                return 'call_mem', 4

    if opcode == 0xC7 and (modrm & 0xC7) == 0x05:
        return 'mov_mem_imm32', 4
    if opcode == 0xC6 and (modrm & 0xC7) == 0x05:
        return 'mov_mem_imm8', 1
    if opcode == 0xD9 and (modrm & 0xC7) == 0x05:
        return 'fld_mem', 4
    if opcode == 0xD8 and (modrm & 0xC7) == 0x05:
        return 'fop_mem', 4
    if opcode == 0xDD and (modrm & 0xC7) == 0x05:
        return 'fld_qword', 8
    if opcode == 0x80 and (modrm & 0xC7) == 0x05:
        return 'cmp_byte_imm', 1
    if opcode == 0x83 and (modrm & 0xC7) == 0x05:
        return 'arith_dword_imm8', 4

    # 3-byte prefix patterns
    if pos >= 3:
        if code[pos-3] == 0x0F:
            if prev2[0] == 0xB6:
                return 'movzx_byte', 1
            if prev2[0] == 0xBE:
                return 'movsx_byte', 1
            if prev2[0] == 0xB7:
                return 'movzx_word', 2
            if prev2[0] == 0xBF:
                return 'movsx_word', 2
        if code[pos-3] == 0x66:
            return 'word_access', 2

    return 'unknown', 4


def analyze_binary():
    """Main analysis: scan all SceneMgr-referencing functions."""
    print("Finding functions that reference g_SceneMgr...")
    funcs = find_scenemgr_functions()
    print(f"  Found {len(funcs)} functions")

    offset_data = defaultdict(lambda: {
        'count': 0, 'access_types': Counter(), 'functions': set(), 'size': set()
    })

    with open(PAL3_EXE, 'rb') as f:
        for func in funcs:
            addr = func['addr']
            size = min(func['size'], 50000)
            f.seek(va_to_file_offset(addr))
            code = f.read(size)

            # Find all 4-byte values pointing into SceneMgr range
            for i in range(len(code) - 3):
                val = struct.unpack_from('<I', code, i)[0]
                if SCENEMGR_ADDR <= val < SCENEMGR_ADDR + MAX_STRUCT_SIZE:
                    offset = val - SCENEMGR_ADDR
                    access_type, access_size = classify_access(code, i)

                    info = offset_data[offset]
                    info['count'] += 1
                    info['access_types'][access_type] += 1
                    info['functions'].add(func['name'])
                    if access_size > 0:
                        info['size'].add(access_size)

    print(f"  Found {len(offset_data)} unique offsets")
    return offset_data


def detect_arrays(offset_data):
    """Detect repeating stride patterns in the offset data."""
    offsets = sorted(k for k in offset_data.keys() if k < 0x20000)

    # Look for specific stride patterns
    results = []

    # Check stride 0x580
    stride = 0x580
    for base in offsets:
        if base + stride > 0x20000:
            break
        count = 1
        while base + count * stride in offset_data:
            count += 1
        if count >= 3:
            results.append({
                'base': base,
                'stride': stride,
                'count': count,
                'total_refs': sum(offset_data[base + i*stride]['count'] for i in range(count))
            })

    # Deduplicate (keep longest chain per stride)
    seen_bases = set()
    unique_results = []
    for r in sorted(results, key=lambda x: -x['count']):
        if r['base'] not in seen_bases:
            unique_results.append(r)
            for i in range(r['count']):
                seen_bases.add(r['base'] + i * r['stride'])

    return unique_results


def print_layout(offset_data, arrays):
    """Print the proposed SceneMgr layout."""
    print()
    print("=" * 80)
    print("SceneMgr BINARY LAYOUT ANALYSIS")
    print(f"g_SceneMgr @ 0x{SCENEMGR_ADDR:08X}")
    print("=" * 80)

    # Header region
    print()
    print("--- HEADER (from SceneMgr::Create disassembly) ---")
    header = [
        (0x00, 'gbGfxManager*', 'm_pGfxMgr', 'Create param 1'),
        (0x04, 'void*', 'm_pSceneRoot', 'Create param 3'),
        (0x08, 'gbRenderEffect*', 'm_pAddEffect2', 'NewRenderEffect(additive_0)'),
        (0x0C, 'gbRenderEffect*', 'm_pAlphaEffect2', 'NewRenderEffect(alpha_0)'),
        (0x10, 'gbRenderEffect*', 'm_pAddEffect', 'NewRenderEffect(additive)'),
        (0x14, 'gbRenderEffect*', 'm_pAlphaEffect', 'NewRenderEffect(alpha)'),
        (0x18, 'gbCamera*', 'm_pCamera', 'Create param 2'),
    ]
    for off, typ, name, note in header:
        refs = offset_data.get(off, {}).get('count', 0)
        print(f"  +0x{off:04X}  {typ:20s}  {name:20s}  [{refs:3d} refs] {note}")

    # Array region
    print()
    print("--- MAIN ARRAY (stride = 0x580 = 1408 bytes) ---")
    print(f"  Start: +0x0288, Elements: 5, End: +0x1E08")
    print(f"  Element offsets: +0x0288, +0x0808, +0x0D88, +0x1308, +0x1888")
    print()

    # Show per-element field map
    # Collect all offsets that repeat with stride 0x580
    elem_fields = defaultdict(int)
    for off in sorted(offset_data.keys()):
        if off < 0x288 or off >= 0x1E08:
            continue
        rel = (off - 0x288) % 0x580
        elem_idx = (off - 0x288) // 0x580
        elem_fields[rel] += offset_data[off]['count']

    print("  Per-element field map (offset within element → total refs):")
    for rel_off in sorted(elem_fields.keys())[:30]:
        refs = elem_fields[rel_off]
        if refs >= 3:
            print(f"    +0x{rel_off:04X}  [{refs:4d} refs]")

    # High-frequency offsets
    print()
    print("--- HIGH-FREQUENCY OFFSETS (>20 refs) ---")
    hot_offsets = [(off, info) for off, info in offset_data.items()
                   if info['count'] >= 20 and off < 0x20000]
    hot_offsets.sort(key=lambda x: -x[1]['count'])

    for off, info in hot_offsets[:25]:
        top_type = info['access_types'].most_common(1)[0][0] if info['access_types'] else '?'
        top_funcs = sorted(info['functions'], key=lambda x: x)[:3]
        sizes = ','.join(str(s) for s in sorted(info['size']))
        print(f"  +0x{off:04X}  [{info['count']:4d} refs]  {top_type:20s}  size={sizes:5s}  {'; '.join(top_funcs)[:60]}")

    # Semantic regions
    print()
    print("--- SEMANTIC REGIONS ---")
    print("  +0x0000-0x001C: Runtime pointers (gbGfxManager, gbCamera, gbRenderEffect)")
    print("  +0x001C-0x0288: Pre-array data (zeroed in Create, 620 bytes)")
    print("  +0x0288-0x1E08: 5-element array, stride 0x580 (SceneMapPlayer or similar)")
    print("  +0x1BA0:        CCBAI/CCBRoleState 'this' (MOV ECX, addr pattern)")
    print("                  = array elem[4] + offset 0x318")
    print("  +0x1E08-0x3DC0: Post-array sparse data (scripts, combat)")
    print("  +0x3DC0-0x3E00: Script system state")
    print("  +0x3DDC-0x3DF8: Float vectors (hurt time, direction)")
    print("  +0xA8C0:        CEffMgr region")
    print("  +0xA91C-0xA930: Light direction + up vector (float[6])")
    print()
    print("  ESTIMATED SIZE: 0xA930 (43312 bytes) minimum")
    print("  UPPER BOUND:    0xC944 (51524 bytes) if late refs are SceneMgr members")

    # Cross-reference with PAL3A PDB
    print()
    print("--- PAL3A PDB CROSS-REFERENCE ---")
    print("  PAL3A PDB: SceneMgr is forward-declared (size=1, no layout)")
    print("  PAL3A PDB members (names only, offsets unknown for PAL3):")
    print("    s_curscene       SCENE_TYPE (enum: STORYA=0, STORYB=1, FIGHT=2)")
    print("    s_scene[3]       Scene (1094164 bytes in PAL3A — MUCH larger!)")
    print("    s_scnfile        SCNFile (187596 bytes in PAL3A)")
    print("    m_objscript      SceneObjScript (12 bytes)")
    print("    m_fHurtTime      float")
    print("    s_map[4]         SceneMapPlayer (392 bytes in PAL3A vs 1408 in PAL3?)")
    print("    m_specialvariable_m17water  int")
    print("    m_specialvariable_m13unite  int")
    print("    m_GeomNote[10]   GeomNote (7 bytes each)")
    print()
    print("  CRITICAL DIFFERENCE: PAL3 SceneMgr is ~43KB, PAL3A would be >3.4MB")
    print("  The sub-structures (Scene, SceneMapPlayer) have vastly different sizes.")
    print("  Array stride 0x580 (1408) matches no PAL3A type directly.")


def print_ida_script(offset_data):
    """Generate IDA Python script to create the SceneMgr struct."""
    print()
    print("=" * 80)
    print("IDA IMPORT SCRIPT (copy to tools/ida/pal3_fix_SceneMgr.py)")
    print("=" * 80)
    print("""
import idc
import ida_struct
import ida_bytes
import ida_name

# Delete existing SceneMgr struct if present
sid = ida_struct.get_struc_id("SceneMgr")
if sid != idc.BADADDR:
    ida_struct.del_struc(ida_struct.get_struc(sid))

# Create new SceneMgr struct
sid = ida_struct.add_struc(-1, "SceneMgr", 0)
sptr = ida_struct.get_struc(sid)

# Header pointers
ida_struct.add_struc_member(sptr, "m_pGfxMgr",     0x0000, idc.FF_DWORD, None, 4)
ida_struct.add_struc_member(sptr, "m_pSceneRoot",   0x0004, idc.FF_DWORD, None, 4)
ida_struct.add_struc_member(sptr, "m_pAddEffect2",  0x0008, idc.FF_DWORD, None, 4)
ida_struct.add_struc_member(sptr, "m_pAlphaEffect2",0x000C, idc.FF_DWORD, None, 4)
ida_struct.add_struc_member(sptr, "m_pAddEffect",   0x0010, idc.FF_DWORD, None, 4)
ida_struct.add_struc_member(sptr, "m_pAlphaEffect", 0x0014, idc.FF_DWORD, None, 4)
ida_struct.add_struc_member(sptr, "m_pCamera",      0x0018, idc.FF_DWORD, None, 4)

# Pre-array region (600 bytes, mostly zeroed)
ida_struct.add_struc_member(sptr, "_preArray",      0x001C, idc.FF_BYTE, None, 0x26C)

# Main array: 5 elements × 0x580 bytes
for i in range(5):
    base = 0x288 + i * 0x580
    ida_struct.add_struc_member(sptr, f"m_slot{i}", base, idc.FF_BYTE, None, 0x580)

# Post-array to rendering data
ida_struct.add_struc_member(sptr, "_postArray",     0x1E08, idc.FF_BYTE, None, 0xA91C - 0x1E08)

# Light/direction vectors at end
ida_struct.add_struc_member(sptr, "m_lightDirX",    0xA91C, idc.FF_FLOAT, None, 4)
ida_struct.add_struc_member(sptr, "m_lightDirY",    0xA920, idc.FF_FLOAT, None, 4)
ida_struct.add_struc_member(sptr, "m_lightDirZ",    0xA924, idc.FF_FLOAT, None, 4)
ida_struct.add_struc_member(sptr, "m_upX",          0xA928, idc.FF_FLOAT, None, 4)
ida_struct.add_struc_member(sptr, "m_upY",          0xA92C, idc.FF_FLOAT, None, 4)

# Pad to end
ida_struct.add_struc_member(sptr, "_tail",          0xA930, idc.FF_BYTE, None, 4)

print(f"SceneMgr struct created: size = 0x{ida_struct.get_struc_size(sptr):X}")

# Apply to g_SceneMgr global
g_addr = 0x00C04390
ida_name.set_name(g_addr, "g_SceneMgr", ida_name.SN_FORCE)
# ida_bytes.del_items(g_addr, 0, 0xA934)
# ida_bytes.create_struct(g_addr, 0xA934, sid)
print("Done. Re-decompile SceneMgr methods to verify.")
""")


def main():
    verbose = '--verbose' in sys.argv
    ida_script = '--ida-script' in sys.argv

    if not PAL3_EXE.exists():
        print(f"ERROR: {PAL3_EXE} not found")
        return
    if not DECOMP_DIR.exists():
        print(f"ERROR: {DECOMP_DIR} not found")
        return

    offset_data = analyze_binary()
    arrays = detect_arrays(offset_data)
    print_layout(offset_data, arrays)

    if ida_script:
        print_ida_script(offset_data)


if __name__ == '__main__':
    main()
