# PAL3A IDA Quality Fix - Final Report
Generated: 2026-05-06

## Export Results

- **Total named functions in .text**: 5322
- **Successfully exported**: 5028 (94.7%)
- **Rejected (userpurge)**: 66
- **Decompile failures**: 217
- **Write errors (bad filenames)**: 15

## Exported Function Quality

- Clean (no issues): 2304 (45.8%)
- Has JUMPOUT (soft warning): 705 (14.0%)
- Has raw memory access (soft warning): 2498 (49.7%)

## Remaining Hard Issues (294 total)

These are **unfixable artifacts of StarForce unpacking** — PDB addresses map to
wrong locations in the unpacked binary.

### 75 Userpurge Functions

These are not real functions — they are code fragments in the middle of other
functions. The PDB addresses were incorrectly used to create function entries.

Evidence:
- No standard function prologue (push ebp / mov ebp, esp)
- Start with mid-function instructions (fstp, mov esi, lea eax, etc.)
- Located within the body of neighboring functions
- Concentrated in template math code (matrix, Collide_Ray, STL containers)

### 219 Decompile Failures

Functions where `ida_hexrays.decompile()` returns None. Mostly caused by
incorrect function boundaries (end_ea doesn't correspond to a `retn`).

By size:
- Tiny (<=16 bytes): 28 — code fragments, not real functions
- Small (17-64 bytes): 89 — likely wrong boundaries
- Medium (65-256 bytes): 72 — boundary or SP issues
- Large (>256 bytes): 28 — real functions with corrupted boundaries

The 28 large functions (e.g., `EquipUI::OnMessage` 4060b, `CCBRoleState::InitRoleState`
2371b) are the most valuable but would require manual IDA analysis to fix their
boundaries.

## What Was Fixed

| Issue | Before | After | Method |
|-------|--------|-------|--------|
| Userpurge calling conv | 546 | 7 (original) + 66 (boundary) | SetType with cleaned signatures |
| SP corruption (false positives) | 7944 | 0 | Changed detection from FUNC_FRAME to positive SP delta |
| JUMPOUT rejection | 704 rejected | 705 exported (soft) | Downgraded to soft warning after target analysis |
| IDA 9.2 API errors | 4 scripts broken | 0 | Replaced ida_typeinf/ida_funcs/ida_ua calls |
| Export success rate | ~81% (4300/5311) | 94.7% (5028/5311) | All fixes combined |

## Conclusion

The 294 remaining failures represent ~5.5% of named functions and are caused by
fundamental PDB/EXE version mismatch after StarForce unpacking. They cannot be
automatically fixed. Manual IDA work could recover the 28 large functions (~15,000
bytes of code), but the ROI is low compared to the 5028 already exported.
