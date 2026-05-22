# Type Annotation Systematic Correction Design

## Overview

Systematically correct type annotations across all 7999 fields in PAL3 annotations to establish data standard correctness and completeness. Compilation passing is the natural result of annotation quality improvement.

**Method**: Strict sequential batch approach (fully manual, A-level binary evidence first)

**Current state**:
- 680 structures, 7999 fields
- 87% named (6957), 9% _todo_ (716), 4.1% _field_ (326)
- 3302 compilation errors (baseline: 2026-05-22)
- 257 suspicious type annotations (gap_fill/decomp_access sources)
- Main pattern: pointers incorrectly marked as unsigned long/DWORD (89 known cases)

## Architecture

5-stage pipeline per field:

```
Extract Candidates → Evidence Collection → Type Determination → Annotation Modification → Full Verification
       ↓                    ↓                     ↓                      ↓                      ↓
  compile errors     binary instructions      A-level confidence      CHANGE_LOG           init --force
  C2440/C2664        + decomp context         algorithm               + check              + compile
```

## Batch Strategy

### Priority Order (5 batches)

| Batch | Target | Count | Trigger |
|-------|--------|-------|---------|
| 1 | Compile-error related fields | ~200-300 | Immediate |
| 2 | High-reference fields (refs >= 10) | ~100-150 | Batch 1 complete |
| 3 | Suspicious source fields (gap_fill/decomp_access) | 257 | Batch 2 complete |
| 4 | Core class fields (Combat, SceneMgr, Actor) | TBD | Batch 3 complete |
| 5 | Remaining _todo_/_field_ fields | ~300-500 | Batch 4 complete |

### Multi-round Verification Strategy

- Round 1 (Batch 1): Strictest A-level (binary instruction) verification only
- Subsequent rounds: Gradually relax based on established trusted base
- Strict strategy value: provides absolutely trusted foundation

## Batch 1: Compile-Error Related Fields

### Scope

**Input**: `pipeline/snapshots/data/20260522_142429/compile_result.json` (3302 errors)

**Selection criteria**:
- C2440 (1123): prioritize `cannot convert 'TYPE *' to 'unsigned long'` pattern (89 known)
- C2664 (426): parameter type mismatch, locate specific parameter position
- Exclude pure syntax errors (C2059) and missing members (C2039)

**Output targets**:
- Correct 200-300 field types
- Compilation errors drop >50% (target <1500)
- Establish 100+ A-level confidence (85-90) reference cases

### Stage 1: Candidate Extraction

**Tool**: `pipeline/extract_type_errors.py` (new)

**Process**:
1. Parse all C2440/C2664 errors from compile_result.json
2. Extract type conversion patterns from error messages:
   - `cannot convert 'X *' to 'unsigned long'` -> field type should be X*
   - `cannot convert 'unsigned long' to 'X *'` -> same
3. Trace back to specific struct+offset via generated .cpp
4. Output candidate list: `{struct, offset, current_type, suggested_type, error_count}`

**Output**: `pipeline/_logs/batch1/candidates.json` (sorted by error_count descending)

### Stage 2: Evidence Collection

For each candidate field:

**A. Binary instruction location** (existing tools):
- Method 1 (preferred): Query pipeline/ida/_logs/todo_field_context.json or query_class_full output
- Method 2: `python pipeline/verify_offset.py StructName OFFSET` (global instances)
- Method 3: Manual disp32 search in original/PAL3.exe binary

**B. Decompilation context** (existing data):
- From asm/pal3/decomp/*.json: find access patterns (assignments, comparisons, function calls)

**Output per field**: Evidence package with VA, instruction bytes, disassembly, confidence score

### Stage 3: Type Determination & Structural Issue Detection

#### 3A. Type Determination

MSVC 6.0 instruction pattern recognition:

| Pattern | Type Conclusion | Confidence |
|---------|----------------|------------|
| `fld dword [reg+off]` / `fstp` / `fadd` | **float** | 90 |
| `fld qword [reg+off]` / `fistp` | **double** | 90 |
| `lea eax, [reg+off]; push eax; call Func(char*)` | **char[]** buffer | 85 |
| `lea ecx, [reg+off]; call ctor` | **embedded sub-object** | 90 |
| `movzx eax, byte [reg+off]` | **unsigned char** | 90 |
| `cmp dword [reg+off], 0x3F800000` | **float** (IEEE 754 = 1.0) | 85 |
| mov/test/cmp with 4-byte field | **CANNOT distinguish int from float** | N/A |

**Critical rules**:
- Integer operations (mov/test/cmp) CANNOT distinguish int from float (both 4 bytes)
- Pointer evidence: must have function call passing to pointer parameter, or assignment to known pointer field
- FPU instructions or IEEE 754 constants are the ONLY definitive float proof

#### 3B. Structural Issue Detection (mandatory)

**Check 1: Offset alignment**
- 4-byte types (int, float, DWORD, pointer): offset % 4 == 0 required
- 2-byte types (short, WORD): offset % 2 == 0 required
- Exception: pack(1) structures
- Violation: flag for full structure layout re-analysis

**Check 2: Inheritance chain integrity**
- If offset < base_class_size: field belongs in base class, not subclass
- Verify base class binary_size correctness
- If base class missing member: add to base class, remove from subclass

**Check 3: Structure size boundary**
- max_offset + last_member_size must not exceed binary_size
- Large gap at tail (>16 bytes): potential undiscovered fields/arrays

**Check 4: Base class member propagation**
- Subclass must not redefine fields at base class offsets
- Duplicate fields at same offset: keep only in base class

**Handling strategy**: 
- Structural issues halt current field modification
- Fix structural issue first (inheritance, size, layout)
- After fix: re-run evidence collection and type determination
- Record structural fixes separately in CHANGE_LOG

### Stage 4: Annotation Modification & Audit

#### 4A. Single field modification
1. Read `data/annotations/structs/{StructName}.json`
2. Locate `known_members[str(offset)]`
3. Update: type, source (format: `"A:binary_instruction:VA=0xXXXXXX"`)
4. Run `python pipeline/check_annotations.py` - rollback immediately if fails
5. Write modification

#### 4B. Structural modification
- Scenario 1 (field belongs in base class): move from subclass to base, check all sibling classes
- Scenario 2 (binary_size wrong): find new evidence from ctor stride/global array, update
- Scenario 3 (inheritance missing): update vtables.json, full re-apply+export needed

#### 4C. CHANGE_LOG format
```markdown
### [YYYY-MM-DD] Batch1-Field-NNN: StructName.offset_XXX

**Change type**: TYPE_CORRECTION | INHERITANCE_FIX | SIZE_FIX | ALIGNMENT_FIX
- **Current**: old_type
- **Corrected**: new_type
- **Confidence**: NN

**Evidence**:
1. [A] VA=0xADDR: `instruction bytes` = `disassembly` (reg=this source: `mov esi,ecx` @ func+0)
2. [B] Cross-validation: N references with consistent access pattern

**Structural checks**: PASS/FAIL
- Alignment: offset % type_align == 0
- Inheritance: not in base class range / correctly in base class
- Size: offset + size <= binary_size

**Impact** (structural fixes only):
- Affected classes: [list]
- Requires re-apply+export: yes/no
```

### Stage 5: Full Verification

#### 5A. Verification procedure (mandatory complete path)

Triggered every 20-30 field modifications:

```bash
python pipeline/cli.py init --force    # Mandatory! Not apply
python pipeline/cli.py export          # Refresh decomp JSON
python pipeline/cli.py codegen all     # Regenerate source
python pipeline/cli.py compile         # Compile verification
```

Compare with baseline and previous round.

#### 5B. Verification criteria

**Success**: errors decreased (allow ±5% fluctuation), no new C2039, no new alignment violations

**Failure requiring rollback**: errors increased >10%, new structural errors, check_annotations fails

**Neutral (manual judgment)**: error count stable but distribution changed, some files pass while others gain errors (annotation correction may expose previously hidden issues)

#### 5C. Snapshot management

Preserve key milestones:
- baseline: 20260522_142429 (3302 errors)
- batch1_roundN: after each 20-30 field batch
- batch1_final: batch 1 complete

## Single Field SOP

Standard Operating Procedure (every field must complete all steps):

```
1. Extract candidate (from candidates.json, by error_count desc)
     ↓
2. Evidence collection (IDA logs → verify_offset → binary search)
     ↓
3. Type determination (instruction pattern → IEEE constants → confidence calc)
     ↓
4. Structural checks (alignment → inheritance → size → base propagation)
     ↓
5a. No structural issues → modify field type
5b. Has structural issues → fix structural problem FIRST (no workaround allowed)
     ↓
6. Audit record (CHANGE_LOG.md with evidence + confidence + impact)
     ↓
7. Local validation (check_annotations, pass → count++, fail → rollback)
     ↓
8. Accumulate → trigger full verification at 20-30 fields
```

## Convergence Criteria

### Batch 1 completion (AND conditions)

1. **All candidates processed**: completed >= candidates - failed; failed entries have documented reason
2. **Compilation errors decreased**: 3302 → <1500 (-54% or more)
3. **No new structural issues**: check_annotations passes, no alignment violations, inheritance intact
4. **Audit trail complete**: every modification in CHANGE_LOG with evidence+confidence

### Early termination conditions

- **Diminishing returns**: 3 consecutive rounds (<2% error reduction each) → end batch early
- **Systemic blocker**: 10+ fields fail due to same structural issue → pause, fix structure first
- **Insufficient evidence**: failed.json "evidence insufficient" >30% → need more IDA query runs

## Risk Management

| Risk | Impact | Mitigation |
|------|--------|------------|
| Long verification cycles | 15min per round, slow feedback | First 3 rounds: verify every 10 fields; preserve snapshots for fast rollback |
| Structural cascading | 1 base class fix affects 12+ subclasses | Structural fixes in separate batches; grep for impact scope before fixing |
| Insufficient confidence | Some fields only have C-level evidence | Mark as pending, don't modify; revisit in later batches with more trusted base |
| PAL3Patch misleading | PAL3A offsets may differ from PAL3 | Only use when offset AND type both match exactly |
| Fixes expose new errors | Type correction reveals previously hidden issues | This is PROGRESS, not regression; new errors join next round candidates |

## Quality Assurance Checkpoints

After every verification round:

1. **Type consistency**: all pointer fields contain '*'; all float fields at 4-byte aligned offsets
2. **Source consistency**: no modifications with only "decomp_access" source (C-level insufficient)
3. **Inheritance integrity**: no subclass fields within base_class_size range (for classes with base_class)
4. **Audit traceability**: every CHANGE_LOG entry has VA address or "structural" marker; confidence >= 85

## Progress Tracking

```
pipeline/_logs/batch1/
├── candidates.json          # Initial 200-300 candidates
├── completed.json           # Completed fields (cumulative)
├── structural_fixes.json    # Structural fix records
├── failed.json              # Failed fields needing retry
└── progress.txt             # Text progress summary
```

## Timeline (Batch 1)

- **Week 1**: Build extract_type_errors.py, generate candidates; first 30 fields → Round 1 verification
- **Week 2-3**: Steady execution, 20-30 fields every 2-3 days + verification rounds
- **Week 4**: Final 100-120 fields, handle difficult cases from failed.json, final verification

**Expected output**:
- 3302 → 1400-1500 errors
- 200-300 A-level confidence annotations
- Complete Batch 1 audit trail
- Trusted base established for Batch 2+

## Subsequent Batches (Summary)

| Batch | Target | Method | Expected Outcome |
|-------|--------|--------|-----------------|
| 2 | High-ref fields (refs>=10) | Cross-reference validation from multiple access points | +3% naming rate, -20-30% more errors |
| 3 | Suspicious sources (257) | Re-verify from binary (replace gap_fill/decomp_access) | Eliminate unreliable annotations |
| 4 | Core classes (Combat, SceneMgr, Actor) | Per-class complete coverage | 100% naming for core logic |
| 5 | Long tail | Relaxed evidence (B-level 70+) | Maximum coverage |
