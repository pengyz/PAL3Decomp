# Phantom Global Variable Resolution Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Eliminate compilation errors from global variables whose addresses fall within a larger parent struct's memory range by resolving them through struct_instances instead of extern declarations.

**Architecture:** Three independent stages: (A) stop generating extern for phantom globals in globals.h, (B) extend identifier resolution to find parent struct via address for any named global, (C) remove the hardcoded Buffer→g_ScriptRoleBuf mapping from thunk_map that bypassed address validation.

**Tech Stack:** Python 3, IDAPython, tree-sitter AST transforms, MSVC 6.0

---

### Task 1: Stage C — Remove hardcoded Buffer→g_ScriptRoleBuf from thunk_map

**Files:**
- Modify: `pipeline/gen/stages/stage4_substitution.py:39`

- [ ] **Step 1: Delete the hardcoded mapping line**

In `_build_identifier_map()`, remove the line:
```python
    m['Buffer'] = 'g_ScriptRoleBuf'
```

The function should now read:
```python
def _build_identifier_map():
    """Build a unified replacement map for identifiers."""
    m = {}
    m.update(store.thunks)
    for cls in store.game_classes:
        if cls.startswith('_') and cls[1:] not in store.game_classes:
            m[cls[1:]] = cls
    return m
```

- [ ] **Step 2: Run codegen + build to measure baseline**

```bash
python pipeline/gen/codegen.py all
cmake --build build -- -k 9999 2>&1 | grep -c 'error C'
```

Expected: Error count decreases slightly (Buffer no longer renamed, keeps its extern from globals.h). C2065 for `g_ScriptRoleBuf` disappears, C2228 for `Buffer.m_partyActor` in PAL_GDB.cpp should also be gone since `Buffer` is now a valid `extern RoleSystem Buffer;`.

- [ ] **Step 3: Commit**

```bash
git add pipeline/gen/stages/stage4_substitution.py
git commit -m "fix(codegen): remove Buffer->g_ScriptRoleBuf from thunk_map

Buffer at 0xC043A0 is within g_SceneMgr range.
It should not be blindly renamed — Stage B will resolve
it through struct_instances instead."
```

---

### Task 2: Stage A — Skip phantom globals in globals.h generation

**Files:**
- Modify: `pipeline/gen/stages/emit_headers.py` (in `generate_globals()`)
- Data: `store.struct_instances` (already loaded by data.py)

- [ ] **Step 1: Add struct_instances check to generate_globals()**

In `generate_globals()` in `emit_headers.py`, after the `sorted_globs` list is built and before generating `extern` lines, filter out globals whose addresses fall within any `struct_instance` range.

The `generate_globals()` function is at approximately line 1659. It reads `_globals` from `ida_structs.json`. The function currently generates `extern` for ALL entries in `_globals`.

```python
def generate_globals():
    import struct as _st
    _is_data = _get_ida_structs()
    globs = _is_data.get('_globals', {})
    if not globs:
        return
    
    # Load struct_instances to detect phantom globals
    # struct_instances format: [(base_addr, end_addr, name, type), ...]
    _by_addr = {}
    for _entry in store.struct_instances:
        _base, _end, _gname, _gtype = _entry
        _by_addr[_base] = _entry
    
    # ... existing code to compute sorted_globs, exe_data, etc. ...
    
    # BEFORE generating extern lines, filter phantom globals:
    sorted_globs = sorted(globs.items(), key=lambda x: int(x[0], 16))
    _filtered = []
    for _addr_s, _g in sorted_globs:
        _addr = int(_addr_s, 16)
        _is_phantom = False
        for _base, _end, _, _ in store.struct_instances:
            if _base < _addr < _end:  # strictly inside a range (not the range base itself)
                _is_phantom = True
                break
        if not _is_phantom:
            _filtered.append((_addr_s, _g))
    sorted_globs = _filtered
    # ... rest of generate_globals() unchanged ...
```

Note: This requires importing `store` from `data`. Check the existing imports at the top of `emit_headers.py` — if `store` isn't imported, add:
```python
from pipeline.gen.data import store
```

- [ ] **Step 2: Run codegen + build to verify**

```bash
python pipeline/gen/codegen.py all
grep 'Buffer' include/pal3/gen/globals.h
```

Expected: `Buffer` no longer appears in `globals.h`. `extern RoleSystem Buffer;` is gone.

```bash
cmake --build build -- -k 9999 2>&1 | grep -c 'error C'
```

Expected: Error count may increase slightly (Buffer now has no declaration at all). This is expected — Stage B will provide the resolution.

- [ ] **Step 3: Commit**

```bash
git add pipeline/gen/stages/emit_headers.py
git commit -m "fix(codegen): skip phantom globals in globals.h generation

Globals whose address falls within a struct_instance range
should not have extern declarations. They are fields of
the parent struct and will be resolved via struct_instances."
```

---

### Task 3: Stage B — Extend _try_global_name() for all identifiers

**Files:**
- Modify: `pipeline/gen/stages/stage4_substitution.py` (in `_try_global_name()`)
- Data: `store.global_types`, `store.struct_instances`, `store.globals_map`

- [ ] **Step 1: Load ida_structs.json at startup for address lookup**

In `data.py:_load_exported_data()`, store the `_globals` address-to-name mapping for use by stage4. Add a new field:

In `DataStore.__init__()`:
```python
self.global_addrs = {}  # name -> base_address (from ida_structs.json _globals)
```

In `_load_exported_data()` where `_globals` is iterated, after building `globals_map`:
```python
# Build name->address lookup for identifier resolution
for addr_str, ginfo in _globals.items():
    gname = ginfo.get('name', '')
    if gname and not gname.startswith(('dword_', 'byte_', 'word_', 'off_', 'unk_', 'stru_', 'flt_')):
        addr_int = int(addr_str, 16) if isinstance(addr_str, str) else addr_str
        self.global_addrs[gname] = addr_int
```

- [ ] **Step 2: Extend _try_global_name() to handle non-dword_ identifiers**

Modify `_try_global_name()` in `stage4_substitution.py`:

```python
def _try_global_name(name):
    """Map IDA unnamed globals (dword_XXX) → annotated name via globals_map + direct lookup.
    Also resolves named globals within struct_instance ranges to g_Parent.field expressions."""
    
    # Existing path: dword_/byte_/etc. prefixed identifiers
    if name.startswith(('dword_', 'byte_', 'word_', 'off_', 'unk_', 'stru_', 'flt_')):
        # Check globals_map first (direct name mapping)
        if name in store.globals_map:
            return store.globals_map[name]
        # Fall back to struct_instances address match
        try:
            addr = int(name.split('_', 1)[1], 16)
        except (ValueError, IndexError):
            return None
        for base, end, gname, _ in store.struct_instances:
            if base <= addr < end:
                store.globals_map[name] = gname
                return gname
        return None
    
    # NEW path: named identifiers (like Buffer, src, pEnd)
    # Check if this name corresponds to a known global within a struct_instance
    if name in store.global_addrs:
        addr = store.global_addrs[name]
        for base, end, gname, gtype in store.struct_instances:
            if base < addr < end:  # strictly inside (not the range base itself)
                offset = addr - base
                resolved = _resolve_offset(gtype, offset, '')
                if resolved:
                    return '%s%s' % (gname, resolved)
    
    return None
```

- [ ] **Step 3: Run codegen + build to verify**

```bash
python pipeline/gen/codegen.py all
grep 'Buffer' src/pal3/gen/Data/PAL_GDB.cpp | head -5
```

Expected: `Buffer.m_partyActor` is now resolved to `g_SceneMgr.fieldName.m_partyActor` (or similar struct_instances expression).

```bash
cmake --build build -- -k 9999 2>&1 | grep -c 'error C' && find build/src/pal3 -name '*.obj' | wc -l
```

Expected: Error count decreases. C2065/C2228 for phantom globals should be resolved.

- [ ] **Step 4: Commit**

```bash
git add pipeline/gen/stages/stage4_substitution.py pipeline/gen/data.py
git commit -m "fix(codegen): resolve named globals through struct_instances

Extended _try_global_name() to check ALL identifiers (not just
dword_/byte_ patterns) against struct_instance ranges. When a
named global's address falls within a parent struct, it is
resolved to g_Parent.field expression instead of keeping the
alias name.

This completes the phantom global resolution fix: no extern
declarations for overlapping globals, no blind renaming,
all access goes through the canonical parent struct path."
```

---

### Verification

After all three tasks:

```bash
# Full pipeline verification
python pipeline/cli.py init --force
python pipeline/cli.py export
python pipeline/cli.py codegen all
cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake -G Ninja
cmake --build build -- -k 9999 2>&1 | grep -c 'error C'

# Verify no phantom globals escaped
grep -c 'extern.*Buffer' include/pal3/gen/globals.h  # should be 0
grep -c 'g_ScriptRoleBuf' src/pal3/gen/ -r --include='*.cpp'  # should be 0
```
