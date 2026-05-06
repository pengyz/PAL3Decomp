# PAL3A Quality Fix Pipeline - Comparison Report

Generated: 2026-05-06 14:16:31

================================================================================

## Before/After Comparison

| Metric | Before | After | Change |
|--------|--------|-------|--------|
| Total functions | 10515 | 5057 | - |
| Userpurge issues | 546 | 8 | -538 |
| SP corruption | 718 | 0 | -718 |
| JUMPOUT (soft) | 1521 | 683 | -838 |
| Clean functions | 7308 | 2307 | -5001 |

## Export Results

- **Total candidates**: 5057
- **Successfully exported**: 5012 (99.1%)
- **Rejected (userpurge)**: 8
- **Rejected (sp corruption)**: 0
- **Errors**: 37

## Exported Function Quality

- **Clean** (no issues): 2307 (46.0%)
- **Has JUMPOUT** (soft warning): 683 (13.6%)
- **Has raw memory** (soft issue): 2481 (49.5%)

================================================================================

## Summary

✅ Successfully exported 5012 qualified functions to `asm/pal3a/decomp/`

⚠️ 8 functions rejected due to quality issues:
  - 8 with calling convention issues

⚠️ 37 functions failed to decompile