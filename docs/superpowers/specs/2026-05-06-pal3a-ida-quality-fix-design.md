# PAL3A IDA Analysis Quality Fix — Design Spec

**Date:** 2026-05-06
**Goal:** Diagnose and fix quality issues in the PAL3A.exe IDA database to produce reliable decompilation output for matching decompilation.

**Context:** PAL3A.exe (仙剑奇侠传3外传) is an unpacked binary analyzed in IDA Pro 9.2 with Hex-Rays. A PDB file with function symbols AND type information is available. The current exported decompilation has severe quality issues preventing use in the decompilation workflow.

---

## Problem Statement

Current IDA analysis of PAL3A.exe (post-unpack) has these issues:

| Problem | Count | % of .text funcs | Root Cause |
|---------|-------|-------------------|------------|
| Function boundary errors (overlaps) | 4,258 | 34% | IDA can't determine function end; merges adjacent functions |
| Raw memory access `*(_DWORD*)(this+N)` | 7,505 | 47% | Class/struct types not imported into IDA |
| JUMPOUT (unresolved jumps) | 3,105 | 19% | Overlapping boundaries + EH funclets |
| SP analysis failure | 1,807 | 11% | Cascading from boundary errors |
| Wrong calling convention (__userpurge) | 849 | 5% | EH funclets misidentified as standalone |

**Additional findings:**
- 3,675 duplicate address entries (same function exported as both named + sub_)
- 849 EH funclets in .data/.rdata range (all contain JUMPOUT, expected)
- 14 functions at 0x0229xxxx (outside PE entirely — unpack artifact or loaded DLL)
- De-duplicated unique function count: 12,646 (not 16,531)

**Key constraint:** The binary is unpacked from StarForce protection. This means:
- Some code regions may have been imperfectly reconstructed
- Import table was rebuilt (PAL3mkimport)
- JMP trampolines from StarForce were patched out but may leave residue
- Function boundaries near patch points may be corrupted

---

## Solution: Three-Phase Diagnose-Fix-Verify Pipeline

### Phase 1: Diagnostic Engine (`ida_diagnose_quality.py`)

An IDAPython script that classifies every function in the database.

#### Classification Labels

| Label | Detection Logic | Auto-fixable? |
|-------|----------------|---------------|
| `EH_FUNCLET` | Name matches `$E\d+` or `$L\d+`; body is JUMPOUT-only or tiny cleanup; located in exception handler range of parent | No fix needed (mark as chunk or exclude from export) |
| `BOUNDARY_OVERLAP` | Function end > next PDB-known function start; verified by checking for ret/jmp/int3/prologue at split point | Yes, if confidence >= 0.8 |
| `UNPACK_ARTIFACT` | Address outside PE sections (>0x0060C000 or in unusual ranges); or references StarForce-related patterns | Exclude from export |
| `SP_CORRUPT` | IDA function flags indicate SP analysis failure; or "positive sp value" in decompilation output | Often fixed automatically after boundary fix |
| `USERPURGE_WRONG` | Calling convention is __userpurge but PDB records __thiscall/__cdecl/__stdcall for this address | Yes, via SetType |
| `STRUCT_NEEDED` | Decompiled code contains `*(_DWORD *)(this +` and this pointer has a known PDB class type | Yes, after type import |
| `DUPLICATE` | Same address exists with both PDB name and sub_ name | Merge (keep PDB name) |
| `CLEAN` | No issues detected | No action needed |

#### Strict Identification Rules (Not Simple Pattern Matching)

**EH Funclet verification:**
1. Name prefix `$E`/`$L` alone is NOT sufficient
2. Must verify at least TWO of:
   - Function body contains JUMPOUT to an address within a known parent function
   - Function size < 64 bytes
   - Located after the parent function's main body (address > parent_start + parent's code size before first EH entry)
   - Referenced from the parent's FuncInfo/UnwindInfo exception table
3. Catch/finally handlers that have real logic (>64 bytes, no JUMPOUT) are NOT funclets — they're legitimate functions

**Boundary overlap verification:**
1. PDB claims function B starts at address X, but IDA thinks function A (starting earlier) extends past X
2. Verify split point X is valid:
   - Instruction at X-1 (or X-2, X-3, X-5) must be ret/retn/jmp/int3/nop
   - OR: there's a CC/90 padding sequence before X
   - OR: X has a recognizable function prologue (push ebp; mov ebp,esp OR push reg; sub esp,N)
3. If NONE of the above: mark as `needs_manual_review` with confidence < 0.5

**Unpack artifact verification:**
1. Address clearly outside PE range (> .data end, or in 0x02xxxxxx range)
2. Code contains references to addresses that don't map to valid PE sections
3. Function contains INT3 sequences mixed with code (broken reconstruction)

#### Output Format

```json
{
  "meta": {
    "ida_db": "PAL3A.exe.i64",
    "script_version": "1.0",
    "timestamp": "2026-05-06T...",
    "pe_sections": {
      "text": [0x401000, 0x569018],
      "rdata": [0x56A000, 0x57F1F2],
      "data": [0x580000, 0x60C000]
    }
  },
  "summary": {
    "total_unique_functions": 12646,
    "by_label": { "CLEAN": 5200, "BOUNDARY_OVERLAP": 4000, ... },
    "auto_fixable": 8500,
    "needs_manual_review": 300
  },
  "functions": {
    "0x00413480": {
      "name": "AStarPathFinder::AStarPathFinder",
      "ida_size": 4005,
      "labels": ["BOUNDARY_OVERLAP", "SP_CORRUPT"],
      "details": {
        "overlap_with": "0x004134D0",
        "pdb_expected_next": "0x004134D0",
        "split_point_valid": true,
        "split_evidence": "ret_at_0x004134CF"
      },
      "fix_action": "truncate_at_0x004134D0",
      "confidence": 0.95
    }
  },
  "manual_review": [
    {
      "address": "0x004201B5",
      "name": "$E102",
      "reason": "EH funclet candidate but body size=32B exceeds threshold, ambiguous",
      "confidence": 0.6
    }
  ]
}
```

---

### Phase 2: Fix Scripts (Executed in Order)

#### Step 1: `ida_fix_boundaries.py`

**Input:** diagnosis_report.json, filtered to BOUNDARY_OVERLAP with confidence >= 0.8

**Algorithm:**
```python
for func in overlapping_functions:
    split_addr = func['pdb_expected_next']
    
    # Double-check before modifying
    if not verify_split_point(split_addr):
        log_skip(func, "split point verification failed")
        continue
    
    # Save current state for undo
    old_end = ida_funcs.get_func(func['address']).end_ea
    
    # Truncate parent function
    ida_funcs.set_func_end(func['address'], split_addr)
    
    # Create new function at split point
    if not ida_funcs.add_func(split_addr):
        # Rollback
        ida_funcs.set_func_end(func['address'], old_end)
        log_error(func, "add_func failed")
        continue
    
    # Apply PDB name
    pdb_name = get_pdb_name(split_addr)
    if pdb_name:
        ida_name.set_name(split_addr, pdb_name, ida_name.SN_FORCE)
    
    log_success(func)
```

**Safety:**
- Dry-run mode by default (`--execute` flag to actually modify)
- Saves IDA DB snapshot before execution
- Logs every operation for potential rollback

#### Step 2: `ida_import_pdb_types.py`

**Input:** PDB file (PAL3A.PDB)

**Strategy:**
1. Extract type information from PDB using one of:
   - IDA's built-in PDB loader with PDBTYP flag (preferred — `idautils.peutils_t().load_pdb()`)
   - cvdump.exe to export types, then parse and import via `idc.SetLocalType()`
   - pdbparse Python library as fallback
   
2. For each class/struct in PDB:
   - Create IDA local type with correct member offsets
   - For `__thiscall` methods: set first argument type to `ClassName *`
   
3. After type import, touch all affected functions to trigger re-decompilation:
   ```python
   for func_addr in functions_with_struct_needed_label:
       # Clear cached decompilation
       ida_hexrays.mark_cfunc_dirty(func_addr)
   ```

**Expected impact:** Resolves ~7,000 `STRUCT_NEEDED` issues — `*(_DWORD *)(this + 8)` becomes `this->m_count`

#### Step 3: `ida_fix_calling_conv.py`

**Input:** diagnosis_report.json, filtered to USERPURGE_WRONG

**Algorithm:**
```python
for func in userpurge_functions:
    pdb_sig = get_pdb_signature(func['address'])
    
    if pdb_sig:
        # PDB has the correct signature — apply directly
        success = idc.SetType(func['address'], pdb_sig)
        if not success:
            # Try simplified version (just calling convention + return type)
            simplified = f"{pdb_sig.return_type} __thiscall {func['name']}(...);"
            idc.SetType(func['address'], simplified)
    else:
        # No PDB info — heuristic
        if is_eh_funclet(func):
            # Don't fix, it's expected to be weird
            continue
        # Mark for manual review
        log_manual_review(func)
```

#### Step 4: `ida_verify_and_export.py`

**Input:** Completed fixes from Steps 1-3

**Actions:**
1. Force re-decompile all modified functions
2. Re-run Phase 1 diagnostic on the fixed database
3. Generate comparison report (before vs after)
4. Export qualified functions to JSON (replacing old asm/pal3a/decomp/)

**Export quality gate:**
- Must NOT have JUMPOUT (unless it's a known EH funclet call)
- Must NOT have __userpurge
- Must NOT have "positive sp value" warning
- Confidence >= 0.7

---

### Phase 3: Verification & Reporting

#### Quality Metrics (Before/After)

```markdown
| Metric                    | Before  | After   | Delta  |
|---------------------------|---------|---------|--------|
| Clean functions           | ~5,200  | target  | +N     |
| Boundary overlaps         | 4,258   | target  | -N     |
| Raw memory access         | 7,505   | target  | -N     |
| JUMPOUT (non-EH)          | 2,570   | target  | -N     |
| SP analysis failures      | 1,807   | target  | -N     |
| __userpurge               | 849     | target  | -N     |
| Export-ready functions     | ???     | target  | +N     |
```

#### Manual Review List

Functions that couldn't be automatically fixed (confidence < 0.8) are written to:
`tools/ida/_logs/manual_review_YYYYMMDD.md`

Format:
```markdown
## Manual Review Required (N functions)

### Boundary Unclear
- 0x004201B5 `$E102` — confidence 0.6, no clear ret/jmp before split point
- ...

### Possible Unpack Damage
- 0x0229A000 `SwordUI::SetSwordEffect` — outside PE, possibly from loaded DLL
- ...
```

---

## File Structure

```
tools/ida/
├── ida_diagnose_quality.py      # Phase 1: diagnostic engine
├── ida_fix_boundaries.py        # Phase 2 Step 1: fix function boundaries
├── ida_import_pdb_types.py      # Phase 2 Step 2: import struct/class types
├── ida_fix_calling_conv.py      # Phase 2 Step 3: fix calling conventions
├── ida_verify_and_export.py     # Phase 2 Step 4 + Phase 3: verify & re-export
├── _logs/
│   ├── diagnosis_report.json    # Full diagnostic output
│   ├── fix_boundaries_log.txt   # Boundary fix execution log
│   ├── fix_types_log.txt        # Type import log
│   ├── fix_callconv_log.txt     # Calling convention fix log
│   ├── quality_comparison.md    # Before/after comparison
│   └── manual_review_*.md       # Functions needing human attention
└── run_pipeline.bat             # Updated to include new scripts
```

---

## Execution Workflow

```
1. Run ida_diagnose_quality.py in IDA
   → Review diagnosis_report.json
   → Confirm the classification makes sense

2. Run ida_fix_boundaries.py --dry-run
   → Review proposed changes
   → Run ida_fix_boundaries.py --execute

3. Run ida_import_pdb_types.py
   → Verify some sample functions now show struct members

4. Run ida_fix_calling_conv.py --dry-run
   → Review, then --execute

5. Run ida_verify_and_export.py
   → Check quality_comparison.md
   → Exported functions replace asm/pal3a/decomp/
```

Each step is independent and can be re-run. Steps 2-4 all have dry-run modes.

---

## Constraints & Risks

1. **PDB type completeness** — PDB may not have ALL class definitions (template instantiations, anonymous structs). Accept that some `*(_DWORD*)` will remain.
2. **Unpack damage** — Some functions in the unpacked binary may genuinely have corrupted code. These should be flagged, not "fixed."
3. **IDA auto-analysis cascade** — Modifying function boundaries triggers re-analysis which may create NEW issues. The verify step catches this.
4. **Performance** — 12,646 functions × decompile can take 10+ minutes in IDA. Scripts should show progress.

---

## Success Criteria

- BOUNDARY_OVERLAP reduced by >= 90%
- Raw memory access reduced by >= 60% (limited by PDB type coverage)
- JUMPOUT in real functions (non-EH) reduced by >= 80%
- SP_CORRUPT reduced by >= 70% (cascading fix from boundaries)
- __userpurge reduced by >= 90%
- Export-ready functions >= 9,000 (up from current ~5,200 CLEAN)
