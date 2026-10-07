# PAL3.exe IDA Export Workflow Design

**Date:** 2026-05-09
**Status:** Approved
**Target:** original/PAL3.exe (StarForce protected, .text analyzable)

## Goal

Establish an IDA-based decompilation pipeline for PAL3.exe that leverages PAL3A.PDB data (types, function signatures) via FLIRT matching and type import.

## Context

- PAL3.exe .text: 0x401000-0x5695D0 (1444 KB, readable)
- PAL3A.PDB: 11412 functions, 1057 classes, 351 enums, 3300+ globals
- 4530 PAL3A functions fall in .text range — high overlap with PAL3.exe
- Same compiler (MSVC 7.0/7.1), same DX SDK, same gbengine.dll
- Existing infrastructure: `tools/ida/gbengine_export_all.py` (3744 functions exported)

## Architecture

```
PAL3A.exe.i64 ──[pal3a_create_sig.py]──→ pal3a_text.pat → sigmake → pal3a.sig
                                                                         │
PAL3.exe.i64 ←──[FLIRT apply]───────────────────────────────────────────┘
     │
     ├──[pal3_import_types.py]←── pdb_export.json (structs, enums)
     ├──[pal3_apply_globals.py]←── globals_export.json (named globals)
     │
     └──[pal3_export_all.py]──→ asm/pal3/*.json (Hex-Rays output)
```

## Scripts

### 1. `tools/ida/pal3a_create_sig.py`

**Runs on:** PAL3A.exe.i64 (has PDB symbols)
**Purpose:** Extract FLIRT-compatible byte patterns from all named .text functions
**Output:** `tools/ida/pal3a_text.pat`

Logic:
- Iterate all functions in .text (0x401000-0x558000)
- Skip unnamed (sub_) and thunk functions
- For each function: extract first 32+ bytes, mark relocation positions as `..`
- Output in IDA `.pat` format (one line per function)
- Run `sigmake` externally to produce `.sig`

### 2. `tools/ida/pal3_import_types.py`

**Runs on:** PAL3.exe IDB (new database)
**Purpose:** Import PAL3A.PDB type system into PAL3.exe analysis
**Input:** `asm/pal3a/pdb_export.json`

Logic:
- Parse classes array (1057 entries) → create IDA Local Types
- Parse enums array (351 entries) → create IDA enums
- Topological sort for dependency order (same as existing `ida_import_all.py`)
- Skip types that already exist in IDB

### 3. `tools/ida/pal3_apply_globals.py`

**Runs on:** PAL3.exe IDB
**Purpose:** Name global variables using PAL3A data
**Input:** `asm/pal3a/globals_export.json`

Logic:
- For each global in .data/.rdata range (0x580000-0x60C000):
  - Check if address exists in PAL3.exe sections
  - If same section layout → apply name directly
  - If address out of range → skip (PAL3A-specific)
- Apply type information where available

### 4. `tools/ida/pal3_export_all.py`

**Runs on:** PAL3.exe IDB (after types + FLIRT applied)
**Purpose:** Export Hex-Rays decompilation for all recognized functions
**Output:** `asm/pal3/` directory, one JSON per function

Format (same as gbengine):
```json
{
  "name": "Scene::Update",
  "mangled_name": "?Update@Scene@@UAEXXZ",
  "address": "0x00456F40",
  "size_bytes": 92,
  "signature": "void __thiscall Scene::Update(Scene *this)",
  "decompiled_c": "..."
}
```

Filename: `ClassName_FunctionName_Address.json`

## PE Section Mapping

| Section | PAL3A.exe | PAL3.exe | Shared? |
|---------|-----------|----------|---------|
| .text   | 0x401000-0x558000 | 0x401000-0x5695D0 | Layout differs (PAL3 has mini-games) |
| .rdata  | 0x56A000-0x57F1F2 | 0x56A000-0x57F178 | Nearly identical |
| .data   | 0x580000-0x60C000 | 0x580000-0x1897000 | First 0x8C000 shared, rest is StarForce |

## Transferability Estimate

- **Type system:** 100% (compiler-independent, same codebase)
- **FLIRT matches:** Expected 60-80% hit rate (same compiler, shared code)
- **Globals:** ~90% in .rdata/.data overlap region
- **PAL3-only code:** ~200 functions (Rowing/Skee/Encampment mini-games) — no symbols

## Integration with src/pal3/

After export, the existing `pal3a_fill_stubs.py` pattern can be adapted:
1. Map exported functions to source files (via PDB source_file_index)
2. Fill stub functions in `src/pal3/` with decompiled code
3. Compile-verify with MSVC 7.1

## Execution Order

1. Create PAL3.exe IDB in IDA (load original/PAL3.exe, auto-analysis)
2. Run `pal3_import_types.py` (types don't need addresses)
3. Run `pal3a_create_sig.py` on PAL3A.exe.i64 → generate .pat → .sig
4. Apply .sig to PAL3.exe IDB (File → Load → FLIRT)
5. Run `pal3_apply_globals.py` (name globals in shared address range)
6. Run `pal3_export_all.py` (export everything)

## Dependencies

- IDA Pro 9.x with Hex-Rays decompiler
- `sigmake` tool (bundled with IDA SDK, or FLAIR toolkit)
- Existing: `asm/pal3a/pdb_export.json`, `asm/pal3a/globals_export.json`
