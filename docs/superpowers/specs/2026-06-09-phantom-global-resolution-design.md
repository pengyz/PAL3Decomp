# Phantom Global Variable Resolution Design

## Problem

The PAL3 decompilation codegen pipeline produces incorrect code for global variables
whose addresses fall within a larger parent struct's memory range ("phantom globals").

These phantom globals get `extern` declarations in `globals.h` (address conflict with
the parent struct) and are renamed through `thunk_map` without address validation,
causing cascading C2065 and C2228 compilation errors.

### Current State (as of 2026-06-09)

```
g_SceneMgr (0xC04390, size=6904)
  ├─ +0x0004: src               ← phantom, has extern
  ├─ +0x0008: pEnd              ← phantom, has extern
  ├─ +0x0010: Buffer            ← phantom, has extern RoleSystem Buffer;
  ├─ +0x0590: g_ScriptRoleBuf   ← phantom, no extern (thunk_map renames to this)
  └─ +0x1610: stru_C059A0       ← phantom, has extern
```

**Total phantom globals in `_globals` (within g_SceneMgr range):** 4
**Total phantom globals from annotation (not in `_globals`):** ~2

## Design

### Rule

**If a global variable's address falls within a `struct_instance` range, it MUST NOT
have an `extern` declaration. All accesses go through `g_Parent.field` resolution.**

### Mechanism

The resolution pipeline has three independent stages that work together:

#### Stage A: globals.h Generation (`emit_headers.py:generate_globals()`)

**Change:** When generating `extern` declarations for globals from `_globals`, check
each global's address against all `struct_instances` ranges. If the address falls
within any range (and is not the range's base itself), skip the `extern` declaration.

**Data source:** `store.struct_instances` (already loaded by `data.py` from
`ida_structs.json` via `_globals` + struct sizes).

**Scope:** Only `_globals` entries whose address is strictly within an existing
`struct_instance` range.

#### Stage B: Identifier Resolution (`stage4_substitution.py:_try_global_name()`)

**Current behavior:** Only processes `dword_`/`byte_`/etc. prefixed identifiers.
Uses `globals_map` for direct lookup, then `struct_instances` for address fallback.

**Change:** Extend to process ALL identifiers (not just IDA default names). When
an identifier matches an entry in `globals_map` (which maps default names to
annotated names), resolve the annotated name's address through `struct_instances`.

The extended logic:
1. If the identifier is not `dword_`/`byte_`/etc. prefixed (currently returns None):
   a. Check if identifier is in `global_types`
   b. If yes, look up its address from ida_structs.json `_globals` (loaded at startup)
   c. If address found and it falls within a `struct_instance`, resolve to `g_StructName.field`
   d. If successful, return the resolved expression
2. If identifier IS `dword_`/`byte_`/etc. prefixed (existing path unchanged):
   a. Check `globals_map` (direct lookup)
   b. Fall back to `struct_instances` address match

Note: `struct_instances` ranges include BOTH the parent struct AND all its
children. The resolution must prefer the outermost range to produce the shortest
access path.

#### Stage C: Remove Incorrect thunk_map Entry (`stage4_substitution.py`)

**Change:** Delete the hardcoded `m['Buffer'] = 'g_ScriptRoleBuf'` line from
`_build_identifier_map()`.

**Why:** `Buffer`'s address (0xC043A0 = g_SceneMgr+0x10) is within g_SceneMgr's
range. It should be resolved through `struct_instances`, not blindly renamed.
The thunk_map is for thunk function replacements, not global variable aliasing.

### Data Flow

```
decomp JSON "Buffer.m_partyActor"
  │
  ├─ Stage4: identifier "Buffer"
  │   ├─ _try_struct_member_resolution: "Buffer" not dword_ → skip
  │   ├─ _try_global_name (EXTENDED):
  │   │   "Buffer" not in globals_map → not dword_ → old code would skip
  │   │   NEW: check all identifiers against global_types
  │   │   "Buffer" IS in global_types (RoleSystem)
  │   │   Look up Buffer's address from _globals: 0xC043A0
  │   │   Check struct_instances: within g_SceneMgr (0xC04390-0xC05E88)
  │   │   Offset 0x10 → _resolve_offset(SceneMgr, 0x10, '')
  │   │   → returns ".fieldName" if SceneMgr has member at +0x10
  │   │   → returns "g_SceneMgr.fieldName"
  │   └─ thunk_map: Buffer → g_ScriptRoleBuf (DELETED)
  │
  └─ RESULT: g_SceneMgr.fieldName.m_partyActor ✅
      (or Buffer.m_partyActor if struct_instances fails fallback)
```

### Fallback Behavior

If Stage B's address resolution fails (`struct_instances` doesn't cover the
address, or the parent struct doesn't have the member at the expected offset,
or `_resolve_offset` returns None):

1. Return None from `_try_global_name()` — do NOT attempt resolution
2. The identifier then hits `thunk_map` (existing behavior)
3. If no thunk_map match either, identifier stays unchanged (existing fallback)

This ensures backward compatibility: identifiers that aren't phantom globals
are unaffected.

**Critical edge case — missing struct member at offset:** If the address falls
within a `struct_instance` range but the parent struct's `data_members` don't
have a field at the corresponding offset, `_resolve_offset` returns None.
In this case the identifier falls through to thunk_map (step 2). This is
correct behavior — the struct member definition is missing from annotations,
which is an annotation quality issue, not a codegen problem.

### Verification

1. Codegen produces no `extern RoleSystem Buffer;` in `globals.h`
2. `g_ScriptRoleBuf` does not appear anywhere in generated code
3. C2065 and C2228 errors for `g_ScriptRoleBuf` and `Buffer` member accesses
   should decrease significantly
4. `Buffer` member accesses that are within g_SceneMgr+0x10 range resolve to
   `g_SceneMgr.fieldName` if the struct member exists, or keep `Buffer` name
   with proper `extern` if not

## Implementation Order

1. Stage C: Delete thunk_map line (simplest, independent)
2. Stage A: Skip phantom globals in `generate_globals()`
3. Stage B: Extend `_try_global_name()` for all identifiers
4. Codegen + build to verify

Each stage is independently verifiable and can be committed separately.
