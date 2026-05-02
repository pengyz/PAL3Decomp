# PAL3A Phase 1 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build the first-phase PAL3A.exe decompilation scaffold: a buildable `src/pal3a/` target, target-aware PAL3A config/index tooling, and a script-subsystem workflow that goes from PDB-backed symbol export to source landing without doing byte matching yet.

**Architecture:** Extend the existing `pal3`/`topo`/`gbengine` repository shape instead of creating a separate PAL3A pipeline. Use Ghidra + loaded PDB as the symbol extraction source, normalize that exported data into repository-owned JSON indexes under `build/pal3a/`, then drive source landing and progress tracking from those indexes.

**Tech Stack:** CMake, MSVC/Win32, Python 3, pytest, Ghidra export scripts, JSON metadata, C/C++ skeleton source files.

---

## File Structure

### Files to create

- `src/pal3a/winmain.cpp` — PAL3A executable entry stub for the phase-1 build target.
- `src/pal3a/pal3a_stubs.cpp` — bootstrap glue and non-script placeholders for the PAL3A target.
- `src/pal3a/script/script_entry.cpp` — script subsystem registration entry used by the PAL3A bootstrap path.
- `src/pal3a/script/sce_runtime.cpp` — landing file for runtime-oriented script functions.
- `src/pal3a/script/sce_dispatch.cpp` — landing file for dispatch/driver script functions.
- `include/pal3a/pal3a_structs.h` — PAL3A-only structs and forward declarations.
- `include/pal3a/pal3a_globals.h` — PAL3A-only globals and addresses.
- `include/pal3a/pal3a_symbols.h` — generated/normalized symbol declarations used by PAL3A sources.
- `tests/test_project_config.py` — unit tests for target-aware PAL3/PAL3A config lookup.
- `tests/test_pal3a_symbol_index.py` — unit tests for PAL3A symbol-index normalization.
- `tests/test_pal3a_progress.py` — unit tests for PAL3A target progress and anchor selection.
- `tests/test_pal3a_emit_function_stub.py` — unit tests for source landing from PAL3A index data.
- `tests/fixtures/pal3a/pdb_export_sample.json` — fixture representing Ghidra-exported PAL3A symbol data.
- `tests/fixtures/pal3a/pdb_index_sample.json` — fixture representing normalized PAL3A index data.
- `tools/ghidra/export_pal3a_symbols.py` — Ghidra-side script to export PAL3A symbols after loading `PAL3A.PDB`.
- `tools/pal3a_build_index.py` — normalizes Ghidra export into repository-owned indexes.
- `tools/pal3a_pick_script_anchors.py` — selects first script-subsystem anchor functions from the normalized index.
- `tools/pal3a_emit_function_stub.py` — emits C/C++ function stubs into `src/pal3a/script/` landing files from normalized index data.
- `build/pal3a/module_map.json` — module boundaries for PAL3A source landing.
- `build/pal3a/translation_status.json` — PAL3A function tracking database for phase 1.

### Files to modify

- `CMakeLists.txt` — add `BUILD_TARGET=pal3a` and the PAL3A executable source list.
- `verify_build.py` — let build verification run against `pal3a`.
- `run.py` — add target-aware progress/index commands for PAL3A.
- `tools/project_config.py` — generalize config lookup from PAL3-only to per-target PAL3/PAL3A helpers.
- `tools/progress.py` — make progress reporting target-aware instead of hardcoded to the top-level PAL3 layout.
- `tests/test_compilation.py` — add PAL3A configure/build smoke coverage.
- `local_config.example.json` — document PAL3A game dir / exe / pdb keys.

### Existing files to read during implementation

- `docs/superpowers/specs/2026-05-02-pal3a-exe-decompilation-design.md`
- `CMakeLists.txt`
- `run.py`
- `verify_build.py`
- `tools/project_config.py`
- `tools/progress.py`
- `tests/test_compilation.py`
- `build/pal3_known_symbols.json`
- `docs/pal3a_pdb_guide.md`

---

### Task 1: Add a buildable PAL3A target

**Files:**
- Create: `src/pal3a/winmain.cpp`
- Create: `src/pal3a/pal3a_stubs.cpp`
- Create: `src/pal3a/script/script_entry.cpp`
- Modify: `CMakeLists.txt`
- Modify: `verify_build.py`
- Modify: `tests/test_compilation.py`

- [ ] **Step 1: Write the failing PAL3A build smoke test**

Add this block to `tests/test_compilation.py`:

```python
PAL3A_BUILD_DIR = os.path.join(PROJECT_ROOT, 'build', 'pal3a_test')


def test_pal3a_cmake_configure(project_root):
    os.makedirs(PAL3A_BUILD_DIR, exist_ok=True)
    result = subprocess.run(
        ['cmake', project_root, '-G', 'Visual Studio 17 2022', '-A', 'Win32',
         '-DBUILD_TARGET=pal3a'],
        cwd=PAL3A_BUILD_DIR,
        capture_output=True,
        text=True,
        timeout=60,
    )
    assert result.returncode == 0, result.stderr


def test_pal3a_build_release(project_root):
    if not os.path.exists(os.path.join(PAL3A_BUILD_DIR, 'CMakeCache.txt')):
        pytest.skip('PAL3A CMake not configured')
    result = subprocess.run(
        ['cmake', '--build', PAL3A_BUILD_DIR, '--config', 'Release'],
        capture_output=True,
        text=True,
        encoding='utf-8',
        errors='replace',
        timeout=300,
    )
    assert result.returncode == 0, result.stderr


def test_pal3a_exe_exists():
    exe_path = os.path.join(PAL3A_BUILD_DIR, 'Release', 'PAL3A.exe')
    assert os.path.exists(exe_path), exe_path
```

- [ ] **Step 2: Run the PAL3A build smoke test and verify it fails**

Run:

```bash
pytest tests/test_compilation.py -k pal3a -q
```

Expected: FAIL because `BUILD_TARGET=pal3a` is not recognized yet.

- [ ] **Step 3: Add the PAL3A CMake target and minimal source files**

Create `src/pal3a/winmain.cpp`:

```cpp
#include <windows.h>

int PAL3A_Bootstrap(void);

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    return PAL3A_Bootstrap();
}
```

Create `src/pal3a/pal3a_stubs.cpp`:

```cpp
void PAL3A_RegisterScriptSubsystem(void);

int PAL3A_Bootstrap(void)
{
    PAL3A_RegisterScriptSubsystem();
    return 0;
}
```

Create `src/pal3a/script/script_entry.cpp`:

```cpp
void PAL3A_RegisterScriptSubsystem(void)
{
}
```

Add this branch to `CMakeLists.txt` before the final `else()`:

```cmake
elseif(BUILD_TARGET STREQUAL "pal3a")
    message(STATUS "Configuring PAL3A.exe build")

    set(PAL3A_SOURCES
        src/pal3a/winmain.cpp
        src/pal3a/pal3a_stubs.cpp
        src/pal3a/script/script_entry.cpp
    )

    add_executable(pal3a WIN32 ${PAL3A_SOURCES})
    target_include_directories(pal3a PUBLIC include)
    set_target_properties(pal3a PROPERTIES
        OUTPUT_NAME "PAL3A"
        SUFFIX ".exe"
    )

    if(MSVC)
        target_compile_options(pal3a PRIVATE ${PAL3_COMPILE_FLAGS})
        target_link_options(pal3a PRIVATE
            /SUBSYSTEM:WINDOWS
            /ENTRY:WinMainCRTStartup
            /BASE:0x00400000
            /DYNAMICBASE:NO
            /FIXED:NO
            /MAP
        )
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/asm)
        target_compile_options(pal3a PRIVATE /FAcs /Fa${CMAKE_BINARY_DIR}/asm/)
    endif()

    target_compile_definitions(pal3a PRIVATE PAL3_DEV_MODE PAL3A_DEV_MODE)
    target_link_libraries(pal3a ${PLATFORM_LIBS} advapi32)

    message(STATUS "PAL3A.exe: ${CMAKE_CURRENT_LIST_FILE} source files")
```

Update `verify_build.py` in `main()`:

```python
    targets = sys.argv[1:] if len(sys.argv) > 1 else ["pal3", "topo", "pal3a"]
```

and in the target switch:

```python
        elif target == "pal3a":
            results[target] = verify_target("pal3a", "PAL3A.exe")
```

- [ ] **Step 4: Re-run the PAL3A build smoke test**

Run:

```bash
pytest tests/test_compilation.py -k pal3a -q
```

Expected: PASS with `PAL3A.exe` created under `build/pal3a_test/Release/`.

- [ ] **Step 5: Run direct build verification**

Run:

```bash
python verify_build.py pal3a
```

Expected: PASS and a line like `PAL3A.exe (<size> bytes)`.

- [ ] **Step 6: Commit Task 1**

```bash
git add CMakeLists.txt verify_build.py tests/test_compilation.py src/pal3a/winmain.cpp src/pal3a/pal3a_stubs.cpp src/pal3a/script/script_entry.cpp
git commit -m "feat: add PAL3A build target scaffold"
```

### Task 2: Make config and repository layout target-aware

**Files:**
- Create: `include/pal3a/pal3a_structs.h`
- Create: `include/pal3a/pal3a_globals.h`
- Create: `include/pal3a/pal3a_symbols.h`
- Modify: `tools/project_config.py`
- Modify: `run.py`
- Modify: `local_config.example.json`
- Test: `tests/test_project_config.py`

- [ ] **Step 1: Write the failing target-config tests**

Create `tests/test_project_config.py`:

```python
import json
from pathlib import Path

from tools import project_config


def test_get_target_exe_path_reads_pal3a_keys(tmp_path, monkeypatch):
    game_dir = tmp_path / 'PAL3A'
    game_dir.mkdir()
    exe_path = game_dir / 'PAL3Aunpacked.exe'
    exe_path.write_bytes(b'MZ')
    pdb_path = game_dir / 'PAL3A.pdb'
    pdb_path.write_bytes(b'RSDS')

    local_config = tmp_path / 'local_config.json'
    local_config.write_text(json.dumps({
        'pal3a_game_dir': str(game_dir),
        'pal3a_exe_name': 'PAL3Aunpacked.exe',
        'pal3a_pdb_path': str(pdb_path),
    }), encoding='utf-8')

    monkeypatch.setattr(project_config, 'LOCAL_CONFIG_FILE', local_config)
    monkeypatch.setattr(project_config, 'BUILD_CONFIG_FILE', tmp_path / 'build_config.json')

    assert project_config.get_target_exe_path('pal3a') == exe_path
    assert project_config.get_target_pdb_path('pal3a') == pdb_path


def test_get_target_exe_path_keeps_pal3_default(tmp_path, monkeypatch):
    game_dir = tmp_path / 'PAL3'
    game_dir.mkdir()
    exe_path = game_dir / 'PAL3.exe'
    exe_path.write_bytes(b'MZ')

    local_config = tmp_path / 'local_config.json'
    local_config.write_text(json.dumps({'game_dir': str(game_dir)}), encoding='utf-8')

    monkeypatch.setattr(project_config, 'LOCAL_CONFIG_FILE', local_config)
    monkeypatch.setattr(project_config, 'BUILD_CONFIG_FILE', tmp_path / 'build_config.json')

    assert project_config.get_target_exe_path('pal3') == exe_path
```

- [ ] **Step 2: Run the config tests and verify they fail**

Run:

```bash
pytest tests/test_project_config.py -q
```

Expected: FAIL with `AttributeError` because `get_target_exe_path` / `get_target_pdb_path` do not exist yet.

- [ ] **Step 3: Generalize the config helper and add PAL3A headers**

Add this block near the top of `tools/project_config.py`:

```python
TARGET_DEFAULTS = {
    'pal3': {
        'game_dir_key': 'game_dir',
        'exe_name_key': 'exe_name',
        'default_exe_name': 'PAL3.exe',
        'pdb_path_key': 'pdb_path',
    },
    'pal3a': {
        'game_dir_key': 'pal3a_game_dir',
        'exe_name_key': 'pal3a_exe_name',
        'default_exe_name': 'PAL3A.exe',
        'pdb_path_key': 'pal3a_pdb_path',
    },
}
```

Add these functions to `tools/project_config.py`:

```python
def get_target_game_dir(target='pal3'):
    keys = TARGET_DEFAULTS[target]
    env_key = f"{target.upper()}_GAME_DIR"
    env_dir = os.environ.get(env_key)
    if env_dir:
        p = Path(env_dir)
        if p.exists():
            return p

    local = load_local_config()
    if keys['game_dir_key'] in local:
        p = Path(local[keys['game_dir_key']])
        if p.exists():
            return p

    build = load_build_config()
    if keys['game_dir_key'] in build:
        p = Path(build[keys['game_dir_key']])
        if p.exists():
            return p

    return None


def get_target_exe_path(target='pal3'):
    keys = TARGET_DEFAULTS[target]
    game_dir = get_target_game_dir(target)
    if game_dir is None:
        return None

    local = load_local_config()
    exe_name = local.get(keys['exe_name_key'], keys['default_exe_name'])
    exe_path = game_dir / exe_name
    if exe_path.exists():
        return exe_path

    for f in game_dir.iterdir():
        if f.name.lower() == exe_name.lower():
            return f
    return None


def get_target_pdb_path(target='pal3a'):
    keys = TARGET_DEFAULTS[target]
    local = load_local_config()
    if keys['pdb_path_key'] in local:
        p = Path(local[keys['pdb_path_key']])
        if p.exists():
            return p

    game_dir = get_target_game_dir(target)
    if game_dir is None:
        return None

    candidate = game_dir / f"{keys['default_exe_name'].rsplit('.', 1)[0]}.pdb"
    if candidate.exists():
        return candidate
    return None
```

Keep backward compatibility by rewriting the old helpers as wrappers:

```python
def get_game_dir():
    return get_target_game_dir('pal3')


def get_exe_path():
    return get_target_exe_path('pal3')
```

Create `include/pal3a/pal3a_structs.h`:

```cpp
#ifndef PAL3A_STRUCTS_H
#define PAL3A_STRUCTS_H

struct PAL3A_SceContext;
struct PAL3A_ScriptFrame;

#endif
```

Create `include/pal3a/pal3a_globals.h`:

```cpp
#ifndef PAL3A_GLOBALS_H
#define PAL3A_GLOBALS_H

extern unsigned int PAL3A_SCRIPT_DISPATCH_TABLE;
extern unsigned int PAL3A_SCRIPT_CONTEXT;

#endif
```

Create `include/pal3a/pal3a_symbols.h`:

```cpp
#ifndef PAL3A_SYMBOLS_H
#define PAL3A_SYMBOLS_H

#define PAL3A_UNRESOLVED_ADDR 0u

#endif
```

Update `local_config.example.json` to:

```json
{
  "game_dir": "D:/Games/PAL3",
  "exe_name": "PAL3.exe",
  "pal3a_game_dir": "D:/Games/PAL3A",
  "pal3a_exe_name": "PAL3Aunpacked.exe",
  "pal3a_pdb_path": "D:/Games/PAL3A/PAL3A.pdb"
}
```

Add this command branch to `run.py` help text and dispatch logic:

```python
    print("  progress [--target pal3|pal3a|topo|gbengine]  查看指定目标进度")
```

- [ ] **Step 4: Run the target-config tests again**

Run:

```bash
pytest tests/test_project_config.py -q
```

Expected: PASS.

- [ ] **Step 5: Commit Task 2**

```bash
git add tools/project_config.py run.py local_config.example.json include/pal3a/pal3a_structs.h include/pal3a/pal3a_globals.h include/pal3a/pal3a_symbols.h tests/test_project_config.py
git commit -m "feat: add target-aware PAL3A project config"
```

### Task 3: Export and normalize PAL3A PDB-backed symbols

**Files:**
- Create: `tools/ghidra/export_pal3a_symbols.py`
- Create: `tools/pal3a_build_index.py`
- Create: `tests/test_pal3a_symbol_index.py`
- Create: `tests/fixtures/pal3a/pdb_export_sample.json`

- [ ] **Step 1: Write the failing symbol-index normalization test**

Create `tests/fixtures/pal3a/pdb_export_sample.json`:

```json
{
  "image_base": "0x00400000",
  "functions": [
    {
      "address": "0x00401000",
      "name": "Sce_RunOpcode",
      "source_file": "script\\sceexec.cpp",
      "return_type": "int",
      "parameters": ["PAL3A_SceContext *ctx", "int opcode"]
    }
  ],
  "globals": [
    {
      "address": "0x00600000",
      "name": "g_SceContext",
      "datatype": "PAL3A_SceContext *"
    }
  ],
  "types": [
    {
      "name": "PAL3A_SceContext",
      "kind": "struct",
      "size": 64
    }
  ]
}
```

Create `tests/test_pal3a_symbol_index.py`:

```python
import json
import subprocess
import sys
from pathlib import Path


def test_pal3a_build_index_creates_function_and_global_maps(tmp_path):
    project_root = Path(__file__).resolve().parents[1]
    fixture = project_root / 'tests' / 'fixtures' / 'pal3a' / 'pdb_export_sample.json'
    output = tmp_path / 'pdb_index.json'

    result = subprocess.run(
        [sys.executable, str(project_root / 'tools' / 'pal3a_build_index.py'),
         '--input', str(fixture), '--output', str(output)],
        capture_output=True,
        text=True,
    )

    assert result.returncode == 0, result.stderr
    data = json.loads(output.read_text(encoding='utf-8'))
    assert data['functions']['0x00401000']['name'] == 'Sce_RunOpcode'
    assert data['globals']['0x00600000']['name'] == 'g_SceContext'
    assert data['types']['PAL3A_SceContext']['size'] == 64
```

- [ ] **Step 2: Run the normalization test and verify it fails**

Run:

```bash
pytest tests/test_pal3a_symbol_index.py -q
```

Expected: FAIL because `tools/pal3a_build_index.py` does not exist yet.

- [ ] **Step 3: Add the Ghidra exporter and normalization tool**

Create `tools/ghidra/export_pal3a_symbols.py`:

```python
#@category PAL3A
import json

program = currentProgram
listing = program.getListing()
symbol_table = program.getSymbolTable()
function_manager = program.getFunctionManager()

output = {
    'image_base': str(program.getImageBase()),
    'functions': [],
    'globals': [],
    'types': [],
}

for function in function_manager.getFunctions(True):
    output['functions'].append({
        'address': str(function.getEntryPoint()),
        'name': function.getName(),
        'source_file': str(function.getSymbol().getSource()),
        'return_type': str(function.getReturnType()),
        'parameters': [str(p.getDataType()) + ' ' + p.getName() for p in function.getParameters()],
    })

for symbol in symbol_table.getAllSymbols(True):
    if symbol.isGlobal() and symbol.getAddress().isMemoryAddress():
        output['globals'].append({
            'address': str(symbol.getAddress()),
            'name': symbol.getName(),
            'datatype': '',
        })

with open(askFile('Save PAL3A symbol export', 'Save').getAbsolutePath(), 'w') as fp:
    json.dump(output, fp, indent=2)
```

Create `tools/pal3a_build_index.py`:

```python
#!/usr/bin/env python3
import argparse
import json
from pathlib import Path


def build_index(payload):
    return {
        'image_base': payload['image_base'],
        'functions': {
            item['address']: {
                'name': item['name'],
                'source_file': item.get('source_file', ''),
                'return_type': item.get('return_type', ''),
                'parameters': item.get('parameters', []),
                'status': 'indexed',
            }
            for item in payload.get('functions', [])
        },
        'globals': {
            item['address']: {
                'name': item['name'],
                'datatype': item.get('datatype', ''),
            }
            for item in payload.get('globals', [])
        },
        'types': {
            item['name']: {
                'kind': item.get('kind', ''),
                'size': item.get('size', 0),
            }
            for item in payload.get('types', [])
        },
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', required=True)
    parser.add_argument('--output', required=True)
    args = parser.parse_args()

    payload = json.loads(Path(args.input).read_text(encoding='utf-8'))
    output = build_index(payload)
    out_path = Path(args.output)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(json.dumps(output, indent=2, ensure_ascii=False), encoding='utf-8')


if __name__ == '__main__':
    main()
```

- [ ] **Step 4: Re-run the normalization test**

Run:

```bash
pytest tests/test_pal3a_symbol_index.py -q
```

Expected: PASS.

- [ ] **Step 5: Generate the first repository-owned PAL3A index**

Run:

```bash
python tools/pal3a_build_index.py --input asm/pal3a/pdb_export.json --output build/pal3a/pdb_index.json
```

Expected: `build/pal3a/pdb_index.json` exists and contains `functions`, `globals`, and `types` maps.

- [ ] **Step 6: Commit Task 3**

```bash
git add tools/ghidra/export_pal3a_symbols.py tools/pal3a_build_index.py tests/test_pal3a_symbol_index.py tests/fixtures/pal3a/pdb_export_sample.json
git commit -m "feat: add PAL3A symbol index pipeline"
```

### Task 4: Add PAL3A progress tracking and script anchor selection

**Files:**
- Create: `tools/pal3a_pick_script_anchors.py`
- Create: `tests/test_pal3a_progress.py`
- Create: `tests/fixtures/pal3a/pdb_index_sample.json`
- Create: `build/pal3a/module_map.json`
- Create: `build/pal3a/translation_status.json`
- Modify: `tools/progress.py`
- Modify: `run.py`

- [ ] **Step 1: Write the failing progress and anchor-selection test**

Create `tests/fixtures/pal3a/pdb_index_sample.json`:

```json
{
  "functions": {
    "0x00401000": {
      "name": "Sce_RunOpcode",
      "source_file": "script\\sceexec.cpp",
      "return_type": "int",
      "parameters": ["PAL3A_SceContext *ctx", "int opcode"],
      "status": "indexed"
    },
    "0x00402000": {
      "name": "Ui_OpenMenu",
      "source_file": "ui\\uimenu.cpp",
      "return_type": "void",
      "parameters": []
    }
  },
  "globals": {},
  "types": {}
}
```

Create `tests/test_pal3a_progress.py`:

```python
import json
import subprocess
import sys
from pathlib import Path


def test_pal3a_anchor_picker_prefers_script_functions(tmp_path):
    project_root = Path(__file__).resolve().parents[1]
    fixture = project_root / 'tests' / 'fixtures' / 'pal3a' / 'pdb_index_sample.json'
    output = tmp_path / 'anchors.json'

    result = subprocess.run(
        [sys.executable, str(project_root / 'tools' / 'pal3a_pick_script_anchors.py'),
         '--index', str(fixture), '--output', str(output)],
        capture_output=True,
        text=True,
    )

    assert result.returncode == 0, result.stderr
    data = json.loads(output.read_text(encoding='utf-8'))
    assert data['anchors'][0]['name'] == 'Sce_RunOpcode'


def test_progress_supports_pal3a_target(tmp_path):
    progress_db = tmp_path / 'progress.json'
    progress_db.write_text(json.dumps({'functions': {}, 'last_updated': ''}), encoding='utf-8')
    assert progress_db.exists()
```

- [ ] **Step 2: Run the PAL3A progress tests and verify they fail**

Run:

```bash
pytest tests/test_pal3a_progress.py -q
```

Expected: FAIL because `tools/pal3a_pick_script_anchors.py` does not exist yet.

- [ ] **Step 3: Add the anchor picker and PAL3A tracking files**

Create `tools/pal3a_pick_script_anchors.py`:

```python
#!/usr/bin/env python3
import argparse
import json
from pathlib import Path


def score_function(meta):
    source_file = meta.get('source_file', '').lower()
    name = meta.get('name', '').lower()
    score = 0
    if 'script' in source_file or 'sce' in source_file:
        score += 10
    if name.startswith('sce_') or name.startswith('script'):
        score += 10
    return score


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--index', required=True)
    parser.add_argument('--output', required=True)
    parser.add_argument('--limit', type=int, default=12)
    args = parser.parse_args()

    index = json.loads(Path(args.index).read_text(encoding='utf-8'))
    ranked = sorted(index['functions'].items(), key=lambda item: score_function(item[1]), reverse=True)
    payload = {
        'anchors': [
            {'address': address, 'name': meta['name'], 'source_file': meta.get('source_file', '')}
            for address, meta in ranked[:args.limit]
            if score_function(meta) > 0
        ]
    }
    Path(args.output).write_text(json.dumps(payload, indent=2, ensure_ascii=False), encoding='utf-8')


if __name__ == '__main__':
    main()
```

Create `build/pal3a/module_map.json`:

```json
{
  "script": ["script", "sce"],
  "runtime": ["main", "boot", "system"],
  "ui": ["ui", "menu"],
  "battle": ["battle", "fight"],
  "scene": ["scene", "map"],
  "resource": ["res", "pack", "archive"]
}
```

Create `build/pal3a/translation_status.json`:

```json
{
  "target": "pal3a",
  "phase": "phase1",
  "functions": {}
}
```

Modify `tools/progress.py` to accept a target and target-local paths:

```python
TARGET_DEFAULTS = {
    'pal3': {
        'asm_dir': ASM_DIR / 'pal3',
        'src_dir': SRC_DIR / 'pal3',
        'progress_db': BUILD_DIR / 'progress.json',
    },
    'pal3a': {
        'asm_dir': ASM_DIR / 'pal3a',
        'src_dir': SRC_DIR / 'pal3a',
        'progress_db': BUILD_DIR / 'pal3a' / 'translation_status.json',
    },
}
```

and add the CLI option:

```python
    parser.add_argument('--target', default='pal3', choices=sorted(TARGET_DEFAULTS.keys()))
```

Modify `run.py` `cmd_progress()` to forward `--target`:

```python
def cmd_progress(args):
    extra = []
    if '--target' in args:
        idx = args.index('--target')
        extra.extend(['--target', args[idx + 1]])
    run_tool('progress.py', extra)
```

- [ ] **Step 4: Re-run the PAL3A progress tests**

Run:

```bash
pytest tests/test_pal3a_progress.py -q
```

Expected: PASS.

- [ ] **Step 5: Generate the first script-anchor list from the normalized index**

Run:

```bash
python tools/pal3a_pick_script_anchors.py --index build/pal3a/pdb_index.json --output build/pal3a/script_anchor_candidates.json --limit 12
```

Expected: `build/pal3a/script_anchor_candidates.json` exists, and the top entries are script/SCE-flavored functions.

- [ ] **Step 6: Commit Task 4**

```bash
git add tools/progress.py run.py tools/pal3a_pick_script_anchors.py tests/test_pal3a_progress.py tests/fixtures/pal3a/pdb_index_sample.json build/pal3a/module_map.json build/pal3a/translation_status.json
git commit -m "feat: add PAL3A progress and anchor selection"
```

### Task 5: Close the symbol-to-source workflow for the script subsystem

**Files:**
- Create: `src/pal3a/script/sce_runtime.cpp`
- Create: `src/pal3a/script/sce_dispatch.cpp`
- Create: `tools/pal3a_emit_function_stub.py`
- Create: `tests/test_pal3a_emit_function_stub.py`
- Modify: `src/pal3a/pal3a_stubs.cpp`
- Modify: `CMakeLists.txt`

- [ ] **Step 1: Write the failing source-landing test**

Create `tests/test_pal3a_emit_function_stub.py`:

```python
import json
import subprocess
import sys
from pathlib import Path


def test_pal3a_emit_function_stub_writes_named_function(tmp_path):
    project_root = Path(__file__).resolve().parents[1]
    index = tmp_path / 'index.json'
    index.write_text(json.dumps({
        'functions': {
            '0x00401000': {
                'name': 'Sce_RunOpcode',
                'return_type': 'int',
                'parameters': ['PAL3A_SceContext *ctx', 'int opcode'],
                'source_file': 'script\\sceexec.cpp'
            }
        }
    }), encoding='utf-8')
    output = tmp_path / 'sce_runtime.cpp'

    result = subprocess.run(
        [sys.executable, str(project_root / 'tools' / 'pal3a_emit_function_stub.py'),
         '--index', str(index), '--address', '0x00401000', '--output', str(output)],
        capture_output=True,
        text=True,
    )

    assert result.returncode == 0, result.stderr
    text = output.read_text(encoding='utf-8')
    assert 'int Sce_RunOpcode(PAL3A_SceContext *ctx, int opcode)' in text
    assert '/* UNCERTAIN */' in text
```

- [ ] **Step 2: Run the source-landing test and verify it fails**

Run:

```bash
pytest tests/test_pal3a_emit_function_stub.py -q
```

Expected: FAIL because `tools/pal3a_emit_function_stub.py` does not exist yet.

- [ ] **Step 3: Add landing files and the function-stub emitter**

Create `src/pal3a/script/sce_runtime.cpp`:

```cpp
#include "pal3.h"
#include "pal3a/pal3a_structs.h"
#include "pal3a/pal3a_symbols.h"
```

Create `src/pal3a/script/sce_dispatch.cpp`:

```cpp
#include "pal3.h"
#include "pal3a/pal3a_structs.h"
#include "pal3a/pal3a_symbols.h"
```

Create `tools/pal3a_emit_function_stub.py`:

```python
#!/usr/bin/env python3
import argparse
import json
from pathlib import Path


def build_signature(meta):
    params = ', '.join(meta.get('parameters', [])) or 'void'
    return_type = meta.get('return_type', 'void') or 'void'
    return f"{return_type} {meta['name']}({params})"


def build_body(meta):
    return (
        build_signature(meta)
        + "\n{\n"
        + "    /* UNCERTAIN */\n"
        + ("    return 0;\n" if meta.get('return_type') not in ('void', '', None) else "")
        + "}\n"
    )


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--index', required=True)
    parser.add_argument('--address', required=True)
    parser.add_argument('--output', required=True)
    args = parser.parse_args()

    index = json.loads(Path(args.index).read_text(encoding='utf-8'))
    meta = index['functions'][args.address]
    out_path = Path(args.output)
    prefix = out_path.read_text(encoding='utf-8') if out_path.exists() else ''
    out_path.write_text(prefix + '\n' + build_body(meta), encoding='utf-8')


if __name__ == '__main__':
    main()
```

Update `src/pal3a/pal3a_stubs.cpp`:

```cpp
void PAL3A_RegisterScriptSubsystem(void);
int PAL3A_ScriptBootstrap(void);

int PAL3A_Bootstrap(void)
{
    PAL3A_RegisterScriptSubsystem();
    return PAL3A_ScriptBootstrap();
}
```

Update `src/pal3a/script/script_entry.cpp`:

```cpp
int PAL3A_ScriptBootstrap(void)
{
    return 0;
}

void PAL3A_RegisterScriptSubsystem(void)
{
}
```

Add the new files to `PAL3A_SOURCES` in `CMakeLists.txt`:

```cmake
        src/pal3a/script/sce_runtime.cpp
        src/pal3a/script/sce_dispatch.cpp
```

- [ ] **Step 4: Re-run the source-landing test**

Run:

```bash
pytest tests/test_pal3a_emit_function_stub.py -q
```

Expected: PASS.

- [ ] **Step 5: Emit the first real PAL3A script stubs from the normalized index**

Run:

```bash
python tools/pal3a_emit_function_stub.py --index build/pal3a/pdb_index.json --address 0x00401000 --output src/pal3a/script/sce_runtime.cpp
python tools/pal3a_emit_function_stub.py --index build/pal3a/pdb_index.json --address 0x00402000 --output src/pal3a/script/sce_dispatch.cpp
```

Expected: the target files contain named C/C++ stubs derived from real PAL3A index data, with `/* UNCERTAIN */` markers preserved.

- [ ] **Step 6: Rebuild the PAL3A target with the landed script files**

Run:

```bash
pytest tests/test_compilation.py -k pal3a -q
```

Expected: PASS again, proving the symbol-to-source workflow did not break the build target.

- [ ] **Step 7: Commit Task 5**

```bash
git add src/pal3a/pal3a_stubs.cpp src/pal3a/script/script_entry.cpp src/pal3a/script/sce_runtime.cpp src/pal3a/script/sce_dispatch.cpp tools/pal3a_emit_function_stub.py tests/test_pal3a_emit_function_stub.py CMakeLists.txt
git commit -m "feat: add PAL3A script source landing workflow"
```

## Self-Review Checklist

- Spec coverage:
  - `src/pal3a/` skeleton: Task 1 + Task 2.
  - PAL3A header layering: Task 2.
  - PDB-backed index layer: Task 3.
  - Module map / translation tracking: Task 4.
  - Script subsystem sample workflow: Task 4 + Task 5.
  - Validation without byte matching: Task 1 / Task 3 / Task 4 / Task 5 tests.
- Placeholder scan: no `TODO`, `TBD`, or “similar to above” steps remain.
- Type consistency: all PAL3A-specific source landing uses `PAL3A_SceContext`, `get_target_exe_path('pal3a')`, and `build/pal3a/*.json` consistently.
