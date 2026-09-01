# Pipeline Validation and Testing Infrastructure Requirements

## Executive Summary

This document defines the requirements for Phase B (Verification Tools) and Phase C (Test Cases) of the PAL3 decompilation pipeline validation infrastructure. The goal is to prevent regressions, accelerate debugging, and make iterations verifiable.

**Priority**: B > C > A

---

## Phase B: Verification Tools (Highest Priority)

### B1: Error Classification Tool

**Objective**: Automatically analyze the 159 failed compilation files and classify errors by root cause to prioritize fixes.

**Current State**:
- 159 out of 160 files fail compilation
- Existing `extract_type_errors.py` provides partial classification
- Error patterns include:
  - C2664: Type conversion errors (char → char*)
  - C2059/C2238: Syntax errors
  - C2440: Cannot convert between types
  - C2143: Syntax errors (missing semicolons)

**Requirements**:

1. **Error Parsing**
   - Parse MSVC build output to extract all compilation errors
   - Extract file path, line number, error code, and error message
   - Handle multi-line error messages and notes

2. **Root Cause Classification**
   - Classify errors into categories:
     - **annotation_fixable**: Errors caused by incorrect type annotations (e.g., wrong struct member type)
     - **codegen_fixable**: Errors caused by codegen output issues (e.g., syntax errors in generated code)
     - **idb_required**: Errors requiring manual IDB fixes (e.g., missing type definitions)
     - **unknown**: Unclassified errors
   - For each error, provide:
     - Suggested fix location (annotation file or codegen stage)
     - Confidence level (high/medium/low)
     - Related annotation references

3. **Report Generation**
   - Generate JSON report with:
     - Summary statistics (total errors, by category)
     - Per-file error breakdown
     - Prioritized fix recommendations
   - Generate human-readable summary report
   - Output to `pipeline/_logs/error_classification/`

4. **Acceptance Criteria**:
   - [ ] Successfully parses all 159 failed files from `build_output.txt`
   - [ ] Classifies at least 80% of errors into annotation/codegen/idb categories
   - [ ] Generates actionable JSON report with fix recommendations
   - [ ] Runs in <30 seconds on full build output

**Implementation Notes**:
- Extend existing `extract_type_errors.py` functionality
- Use pattern matching on error codes and messages
- Cross-reference with annotation files to identify fixable errors

---

### B2: Compilation Regression Detection

**Objective**: Automatically detect when codegen changes introduce new compilation failures or regressions.

**Current State**:
- No automated regression detection
- Manual comparison of build outputs required
- S2 (Stage 2 semantic) output is the key intermediate representation

**Requirements**:

1. **Baseline Management**
   - Store baseline compilation results (pass/fail status per file)
   - Support multiple baselines (e.g., "current stable", "last known good")
   - Version control baseline snapshots

2. **Regression Detection**
   - Compare current build output against baseline
   - Detect:
     - New failures (files that passed before but fail now)
     - New errors (additional errors in previously failing files)
     - Fixed files (files that now pass)
   - Track error count changes per file

3. **S2 Output Comparison**
   - Compare S2 semantic output before/after codegen changes
   - Detect semantic differences (not just textual)
   - Highlight changes in function signatures, struct layouts, etc.

4. **Alerting**
   - Generate regression report with:
     - List of new failures
     - Diff of error messages
     - Suggested investigation steps
   - Output to `pipeline/_logs/regression_detection/`

5. **Acceptance Criteria**:
   - [ ] Stores and manages baseline compilation results
   - [ ] Detects new failures within 1 minute of build completion
   - [ ] Generates clear regression report with actionable information
   - [ ] Integrates with existing build system

**Implementation Notes**:
- Create `pipeline/regression_detector.py`
- Use JSON format for baseline storage
- Implement diff algorithm for error message comparison

---

### B3: Annotation Diff Visualization

**Objective**: Show exactly what changed in annotations before/after apply_annotations runs.

**Current State**:
- `apply_annotations.py` writes to IDB but no diff output
- Hard to track what changed between annotation versions
- No visualization of type/offset modifications

**Requirements**:

1. **Diff Capture**
   - Capture annotation state before apply_annotations
   - Capture annotation state after apply_annotations
   - Compute structured diff of changes

2. **Change Categories**
   - Categorize changes:
     - **Type changes**: Member type modified
     - **Offset changes**: Member offset modified
     - **Added members**: New members added to struct
     - **Removed members**: Members removed from struct
     - **Function signature changes**: Function parameters/return type modified
     - **Global variable changes**: Global type/address modified

3. **Visualization**
   - Generate unified diff output (similar to git diff)
   - Color-coded terminal output (optional)
   - HTML report with:
     - Side-by-side comparison
     - Highlighted changes
     - Links to affected source files
   - Output to `pipeline/_logs/annotation_diffs/`

4. **Acceptance Criteria**:
   - [ ] Captures before/after annotation state
   - [ ] Generates clear diff showing all changes
   - [ ] Supports multiple output formats (text, HTML, JSON)
   - [ ] Runs in <10 seconds for full annotation set

**Implementation Notes**:
- Create `pipeline/annotation_diff.py`
- Use JSON diffing for structured comparison
- Generate HTML using simple templates

---

## Phase C: Test Cases

### C1: Codegen Unit Tests

**Objective**: Ensure each codegen stage produces correct output from known inputs.

**Current State**:
- Existing `pipeline/gen/test_pipeline.py` has basic tests
- No snapshot tests for individual stages
- Limited coverage of edge cases

**Requirements**:

1. **Snapshot Testing**
   - For each codegen stage (stage1-5, emit_cpp, emit_headers):
     - Store input/output snapshot pairs
     - Verify output matches expected snapshot
     - Detect unintended changes in output

2. **Test Cases**
   - Minimum 1 test case per stage covering:
     - Normal case (typical input)
     - Edge case (boundary conditions)
     - Error case (invalid input handling)
   - Test cases should cover:
     - Stage1 (structural): Struct parsing, inheritance
     - Stage2 (semantic): Type resolution, template handling
     - Stage3 (cleanup): Dead code removal, normalization
     - Stage4 (substitution): Type substitution, macro expansion
     - Stage5 (fixup): Final adjustments, MSVC-specific fixes
     - emit_cpp: C++ code generation
     - emit_headers: Header file generation

3. **Test Infrastructure**
   - Snapshot storage in `tests/snapshots/codegen/`
   - Automatic snapshot update on intentional changes
   - CI integration for regression detection

4. **Acceptance Criteria**:
   - [ ] At least 1 snapshot test per codegen stage
   - [ ] All tests pass on current codebase
   - [ ] Snapshot update mechanism works
   - [ ] Tests run in <2 minutes total

**Implementation Notes**:
- Extend `pipeline/gen/test_pipeline.py`
- Use pytest fixtures for snapshot management
- Store snapshots as JSON files

---

### C2: Annotation Regression Tests

**Objective**: Ensure known annotation fixes don't regress.

**Current State**:
- 66 pointer fixes and 22 __thiscall fixes documented
- No automated regression testing for these fixes
- Manual verification required

**Requirements**:

1. **Test Case Collection**
   - Extract known fixes from:
     - Git history (commit messages mentioning "fix" or "annotation")
     - CHANGE_LOG.md
     - Manual documentation
   - Create test cases for:
     - Pointer type fixes (66 cases)
     - __thiscall fixes (22 cases)
     - Other documented fixes

2. **Regression Verification**
   - For each fix:
     - Store the "before" state (what was wrong)
     - Store the "after" state (what is correct)
     - Verify annotation matches "after" state
   - Detect if annotation reverts to "before" state

3. **Test Execution**
   - Run on every annotation change
   - Run on every codegen change
   - Report regressions immediately

4. **Acceptance Criteria**:
   - [ ] All 88 known fixes have test cases
   - [ ] Tests detect regressions correctly
   - [ ] Tests run in <1 minute
   - [ ] Clear failure messages with fix suggestions

**Implementation Notes**:
- Create `tests/test_annotation_regression.py`
- Store test cases in `tests/fixtures/annotations/`
- Use parametrize for multiple test cases

---

### C3: End-to-End Smoke Tests

**Objective**: Verify the full pipeline works from annotation to compilation.

**Current State**:
- No end-to-end automation
- Manual process: apply → export → codegen → compile
- Time-consuming and error-prone

**Requirements**:

1. **Pipeline Execution**
   - Automate full pipeline:
     1. Apply annotations to IDB
     2. Export from IDB
     3. Run codegen stages
     4. Compile with MSVC 6.0
   - Support running on subset of files

2. **Success Criteria**
   - Pipeline completes without errors
   - At least N files compile successfully (configurable threshold)
   - No new failures compared to baseline

3. **Performance**
   - Full pipeline completes in <5 minutes
   - Support incremental runs (only changed files)

4. **Reporting**
   - Generate execution report:
     - Files processed
     - Success/failure counts
     - Execution time
     - Error details
   - Output to `pipeline/_logs/smoke_tests/`

5. **Acceptance Criteria**:
   - [ ] Full pipeline runs end-to-end
   - [ ] Completes in <5 minutes
   - [ ] Generates clear execution report
   - [ ] Integrates with regression detection

**Implementation Notes**:
- Create `pipeline/smoke_test.py`
- Use existing pipeline scripts as building blocks
- Implement parallel execution where possible

---

## Implementation Priority

### Phase 1 (Week 1): B1 + B3
- B1: Error classification tool (immediate value)
- B3: Annotation diff visualization (supports debugging)

### Phase 2 (Week 2): B2 + C2
- B2: Regression detection (prevents new issues)
- C2: Annotation regression tests (protects known fixes)

### Phase 3 (Week 3): C1 + C3
- C1: Codegen unit tests (ensures codegen correctness)
- C3: End-to-end smoke tests (validates full pipeline)

---

## Success Metrics

1. **Error Reduction**: Reduce compilation failures from 159 to <50 within 4 weeks
2. **Regression Prevention**: Zero new regressions after implementation
3. **Debugging Speed**: Reduce error diagnosis time from hours to minutes
4. **Pipeline Confidence**: Full pipeline runs successfully in <5 minutes

---

## Dependencies

1. **Build System**: MSVC 6.0 compiler via Wine
2. **IDA Pro**: For annotation application and export
3. **Existing Pipeline**: `pipeline/` directory scripts
4. **Test Framework**: pytest

---

## Risks and Mitigations

| Risk | Impact | Mitigation |
|------|--------|------------|
| MSVC compilation slow | High | Parallel compilation, incremental builds |
| IDA interaction complex | Medium | Use existing scripts, add error handling |
| Annotation format changes | Medium | Versioned snapshots, migration scripts |
| Test maintenance burden | Low | Automated snapshot updates, clear documentation |

---

## Appendix: Existing Tools

### Already Implemented
- `pipeline/extract_type_errors.py`: Partial error classification
- `pipeline/compare.py`: Binary comparison tool
- `pipeline/check_annotations.py`: Annotation validation
- `pipeline/snapshots/`: Snapshot infrastructure

### To Be Enhanced
- Error classification needs full implementation
- Regression detection is new
- Annotation diff needs visualization
- Test coverage needs expansion

---

*Document Version*: 1.0
*Date*: 2026-09-01
*Author*: engineer-tools (Pipeline Validation Team)
