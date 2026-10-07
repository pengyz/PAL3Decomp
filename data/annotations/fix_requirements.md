# PAL3 Annotation Infrastructure Fix - Requirements

## 1. Fix Scope

### 1.1 Pointer Level Mismatches (66 instances)
**Problem**: Annotation types have incorrect pointer levels (e.g., `char*` vs `char**`, `int` vs `int*`).

**Fix**: Correct all 66 pointer level mismatches in annotation files.

**Acceptance Criteria**:
- After fix, re-run audit tool → pointer level mismatch count = 0
- Each fix must have IDA-exported original type as evidence

**Evidence Requirements**:
- IDA decompiled output showing correct pointer level
- Cross-reference analysis confirming type usage

### 1.2 functions.json __thiscall Misclassification (48 instances)
**Problem**: 48 functions have `__thiscall` calling convention but no `::` in function name, suggesting they are member functions incorrectly classified as free functions.

**Fix**: Add proper class prefix (e.g., `ClassName::`) to all 48 misclassified functions.

**Acceptance Criteria**:
- After fix, `__thiscall without ::` count = 0
- Each fix must have IDA mangled name or xref evidence

**Evidence Requirements**:
- IDA mangled name showing class membership
- Cross-reference analysis showing `this` pointer usage

### 1.3 Layout Verification Tool (Completed - t4)
**Problem**: No tool to detect if type annotation changes break adjacent member layout.

**Status**: ✅ Completed by engineer-codegen (t4)

**Tool Location**: `tools/audit_type_layout.py`

**Features**:
- Compares annotation structs with IDA exported structs
- Detects type size mismatches, member overlaps, offset out-of-bounds
- Handles union variants correctly

### 1.4 Struct Type Annotation Errors
**Problem**: Type annotation errors cause layout destruction (e.g., `m_EffTable` type error: `tagEffObj[2048]` vs `_BYTE[584]`).

**Fix**: Correct struct type annotations to match IDA-exported types.

**Acceptance Criteria**:
- After fix, pointer level mismatch count = 0
- Use layout verification tool (t4) to confirm no layout breakage

**Evidence Requirements**:
- IDA-exported struct definitions
- Layout verification tool output showing no conflicts

## 2. Non-Goals

### 2.1 Not in Scope
- **Pseudo-semantic naming** (e.g., `m_nTodo_*`, `m_bFlag_*`) — naming style issue, doesn't affect compilation
- **Hex-Rays decompilation quality** (C2059/C2660 errors) — codegen layer issue, not annotation issue
- **Function signature optimization** — only fix incorrect types, not optimize signatures

### 2.2 Rationale
- Pseudo-semantic naming is a style issue that doesn't prevent compilation
- Hex-Rays errors are codegen layer problems that should be fixed in codegen, not annotations
- Focus on correctness, not optimization

## 3. Verification Plan

### 3.1 Pre-Fix Verification
1. Run `check_annotations.py` to establish baseline error count
2. Run `audit_signature_consistency.py` to identify signature conflicts
3. Document current state in `data/status/fix_baseline.json`

### 3.2 Post-Fix Verification
1. Run `check_annotations.py` → 0 errors
2. Run `audit_signature_consistency.py` → 0 signature conflicts
3. Run `audit_type_layout.py` → 0 layout conflicts
4. Run `apply_annotations.py` → successful apply
5. Run `export_full.py` → successful export
6. Run `codegen` → successful compilation

### 3.3 Acceptance Evidence
- All verification commands must pass
- Each fix must have documented evidence (IDA output, xref analysis)
- Layout verification tool must show no conflicts

## 4. Dependencies

### 4.1 Prerequisites
- IDA database with correct types (already available)
- Layout verification tool (completed in t4)

### 4.2 Downstream Tasks
- t2: Fix 66 pointer level mismatches (depends on t1)
- t3: Fix 48 __thiscall misclassification (depends on t1)
- t5: Fix struct type annotation errors (depends on t1, t2, t4)
- t6: Adversarial review (depends on t2, t3, t5)
- t7: Integration verification (depends on t6)

## 5. Timeline

### 5.1 Phase 1: Requirements (t1) - Current
- Define fix scope and acceptance criteria
- Document evidence requirements
- **Status**: In Progress

### 5.2 Phase 2: Implementation (t2, t3)
- Fix pointer level mismatches
- Fix __thiscall misclassification
- **Status**: Pending (waiting for t1)

### 5.3 Phase 3: Struct Fixes (t5)
- Fix struct type annotation errors
- Use layout verification tool
- **Status**: Pending (waiting for t1, t2, t4)

### 5.4 Phase 4: Review (t6)
- Adversarial review of all fixes
- **Status**: Pending (waiting for t2, t3, t5)

### 5.5 Phase 5: Integration (t7)
- Full pipeline verification
- **Status**: Pending (waiting for t6)

## 6. Risk Mitigation

### 6.1 Potential Risks
1. **IDA database inconsistency** — May need to refresh IDA analysis
2. **Missing evidence** — Some fixes may lack clear IDA evidence
3. **Layout breakage** — Type changes may break adjacent members

### 6.2 Mitigation Strategies
1. Use layout verification tool (t4) to detect breakage
2. Require IDA evidence for every fix
3. Implement fixes incrementally with verification at each step
