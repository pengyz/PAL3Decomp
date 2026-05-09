#!/usr/bin/env python3
"""
Batch-infer inferred_class and our_name for all 'unknown' functions in gbengine_registry.jsonl.

Method: Read IDA decompiled JSON for each function, analyze patterns to infer:
- Class membership (from this pointer type, method calls, offset patterns)
- Function name (from behavior: ctor/dtor/getter/setter/init/release/load/render/update)
"""

import json
import re
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
REGISTRY_PATH = PROJECT_ROOT / "data" / "gbengine_registry.jsonl"
IDA_DIR = PROJECT_ROOT / "asm" / "gbengine_ida"

# File -> primary classes mapping
FILE_CLASS_MAP = {
    "gbSoundNode.cpp": ["gbSoundNode", "gbSound3DNode", "gbSound2DNode"],
    "gbVFileSystem.cpp": ["gbVFileSystem", "CPK", "gbVFile", "CIniFile", "CPKFile"],
    "gbParticle.cpp": ["gbParticle", "gbParticleEmitter", "gbParticleGroup"],
    "gbGfxManager_D3D.cpp": ["gbGfxManager_D3D"],
    "gbTexture.cpp": ["gbTexture", "gbTexture_D3D", "gbTextureArray"],
    "gbMesh.cpp": ["gbBaseMesh", "gbStaticMesh", "gbMeshSection"],
    "gbVertPool.cpp": ["gbVertexPool", "gbIndexPool", "gbVertPoolMgr", "gbDynVertBuf",
                       "gbVertexBubble", "gbIndexBubble"],
    "d3dframework.cpp": ["CD3DEnumeration", "CArrayList", "CD3DSettings"],
    "gbGlobals.cpp": [],
    "gbBladeMgr.cpp": ["gbBladeMgr"],
    "gbSceneGraph.cpp": ["gbSceneGraph", "gbGeomNode"],
    "gbVisNode.cpp": ["gbVisNode", "gbVolModNode"],
    "gbCamera.cpp": ["gbCamera", "gbCameraControl"],
    "gbPrintFont.cpp": ["gbPrintFont", "gbPrintFontMgr"],
    "gbMisc.cpp": [],
    "gbGeomNode.cpp": ["gbGeomNode"],
    "gbResManager.cpp": ["gbResManager", "gbResource", "gbRefObject"],
    "gbGfxManager.cpp": ["gbGfxManager"],
    "gbImage2D.cpp": ["gbImage2D", "gbImage2DInfo"],
    "BEZIER.cpp": ["BEZIER"],
    "gbVec3D.cpp": ["gbVec3D"],
    "gbMatrixStack.cpp": ["gbMatrixStack"],
    "gbWeather.cpp": ["gbWeather"],
    "gbChain.cpp": ["gbChain1D", "gbChain1DNode", "gbStaticChain", "gbNBTreeNode"],
    "gbAudioManager.cpp": ["gbAudioManager", "gbSoundData"],
    "gbActor.cpp": ["gbActor"],
    "gbDynVertBuf.cpp": ["gbDynVertBuf"],
    "CPK.cpp": ["CPK"],
}

# Known class names that should NOT be treated as inferred classes
INVALID_CLASSES = {'_DWORD', 'void', 'int', 'char', 'float', 'unsigned',
                   'HANDLE', 'HWND', 'BOOL', 'LPVOID', 'SIZE_T', 'DWORD',
                   'struct', 'size_t'}


def find_ida_json(addr_str: str) -> Path | None:
    """Find the IDA JSON file for a given address."""
    addr_upper = addr_str.upper().replace("0X", "")
    addr_lower = addr_str.lower().replace("0x", "")
    candidate = IDA_DIR / f"sub_{addr_upper}_{addr_lower}.json"
    if candidate.exists():
        return candidate
    candidates = list(IDA_DIR.glob(f"*_{addr_lower}.json"))
    if candidates:
        return candidates[0]
    return None


def load_decompiled(path: Path) -> dict | None:
    """Load IDA JSON and return the dict."""
    try:
        with open(path) as f:
            return json.load(f)
    except (json.JSONDecodeError, IOError):
        return None


def infer_file_from_adjacency(entries_sorted: list, idx: int) -> str:
    """Infer source file from nearby entries that have a file field."""
    # Look backward
    prev_file = None
    for i in range(idx - 1, max(0, idx - 15), -1):
        f = entries_sorted[i].get("file")
        if f:
            prev_file = f
            break

    # Look forward
    next_file = None
    for i in range(idx + 1, min(len(entries_sorted), idx + 15)):
        f = entries_sorted[i].get("file")
        if f:
            next_file = f
            break

    if prev_file == next_file and prev_file:
        return prev_file
    if prev_file and next_file:
        # Different files - could be at a boundary. Use the prev (conservative)
        return prev_file
    if prev_file:
        return prev_file
    if next_file:
        return next_file
    return ""


def extract_class_from_sig(sig: str) -> str | None:
    """Try to extract class from IDA signature type annotations."""
    m = re.search(r'(\w+)\s*\*+\s*this', sig)
    if m:
        cls = m.group(1)
        if cls not in INVALID_CLASSES:
            return cls
    return None


def find_base_dtor_calls(code: str) -> list[str]:
    """Find base class destructor calls like ClassName::~ClassName(...)."""
    return re.findall(r'(\w+)::~\1\(', code)


def find_base_ctor_calls(code: str) -> list[str]:
    """Find base class constructor calls like ClassName::ClassName(...)."""
    return re.findall(r'(\w+)::(?!~)\1\(', code)


def infer_class(code: str, signature: str, inferred_file: str) -> str | None:
    """Infer class from decompiled code."""
    is_thiscall = '__thiscall' in signature

    if not is_thiscall:
        return None

    # 1. From signature type annotation
    sig_class = extract_class_from_sig(signature)
    if sig_class and sig_class not in INVALID_CLASSES:
        file_classes = FILE_CLASS_MAP.get(inferred_file, [])
        if sig_class in file_classes:
            return sig_class
        # Common base types that need deeper analysis
        if sig_class in ('gbResource', 'gbRefObject', 'gbResManager',
                         'gbChain1DNode', 'gbMatrixStack', 'gbGfxManager'):
            pass  # Fall through to deeper analysis
        else:
            # Trust the signature type if it's a real class name
            return sig_class

    if not code:
        file_classes = FILE_CLASS_MAP.get(inferred_file, [])
        return file_classes[0] if len(file_classes) == 1 else None

    file_classes = FILE_CLASS_MAP.get(inferred_file, [])

    # 2. From method calls and patterns in code
    # === gbVFileSystem.cpp ===
    if inferred_file == "gbVFileSystem.cpp":
        if 'HeapDestroy' in code or 'VirtualFree' in code or 'HeapAlloc' in code or 'VirtualAlloc' in code:
            return "gbMemAllocator"
        if 'VertPoolMgr' in code or 'VertexBubble' in code or 'IndexBubble' in code:
            return "gbBaseMesh"
        if 'gbVFileSystem::Read' in code:
            # If calling Read on g_pVFileSys, we're inside a method that reads data
            if 'g_pVFileSys' in code:
                return "gbBaseMesh"  # Loading mesh/model data, not gbVFileSystem itself
        offsets = [int(m) for m in re.findall(r'this\s*\+\s*(\d+)', code)]
        if offsets:
            max_off = max(offsets)
            if max_off > 200:
                return "gbVFileSystem"
            if max_off < 12:
                return "CPKFile"
        if 'gbVFileSystem' in code:
            return "gbVFileSystem"
        return "gbVFileSystem"

    # === gbParticle.cpp ===
    if inferred_file == "gbParticle.cpp":
        if 'gbResource::~gbResource' in code:
            return "gbParticleGroup"
        if 'gbSound3DNode' in code or 'gbSoundNode' in code:
            return "gbSoundNode"
        if 'gbChain1D::~gbChain1D' in code or 'gbChain1DNode::~gbChain1DNode' in code:
            return "gbSoundNode"
        if 'gbNBTreeNode' in code:
            return "gbSoundNode"
        if 'ParticleEmitter' in code or 'Emitter' in code:
            return "gbParticleEmitter"
        offsets = [int(m) for m in re.findall(r'this\s*\+\s*(\d+)', code)]
        if offsets and max(offsets) > 80:
            return "gbParticleGroup"
        return "gbParticle"

    # === gbTexture.cpp ===
    if inferred_file == "gbTexture.cpp":
        if 'D3DXCreateTexture' in code or 'IDirect3DTexture' in code or 'D3DX' in code:
            return "gbTexture_D3D"
        if 'gbTexture_D3D' in code:
            return "gbTexture_D3D"
        if 'TextureArray' in code:
            return "gbTextureArray"
        return "gbTexture"

    # === gbGfxManager_D3D.cpp ===
    if inferred_file == "gbGfxManager_D3D.cpp":
        return "gbGfxManager_D3D"

    # === gbMesh.cpp ===
    if inferred_file == "gbMesh.cpp":
        if 'MeshSection' in code or 'section' in code.lower():
            return "gbMeshSection"
        if 'StaticMesh' in code:
            return "gbStaticMesh"
        return "gbBaseMesh"

    # === gbVertPool.cpp ===
    if inferred_file == "gbVertPool.cpp":
        if 'DrawPrimitive' in code or 'SetStreamSource' in code:
            return "gbDynVertBuf"
        offsets = [int(m) for m in re.findall(r'this\s*\+\s*(\d+)', code)]
        if offsets:
            max_off = max(offsets)
            if max_off > 100:
                return "gbVertPoolMgr"
            if max_off <= 15:
                return "gbDynVertBuf"
        return "gbVertexPool"

    # === d3dframework.cpp ===
    if inferred_file == "d3dframework.cpp":
        if 'CArrayList' in code or 'pData' in code:
            return "CArrayList"
        if 'Adapter' in code or 'D3DFORMAT' in code or 'EnumDevice' in code:
            return "CD3DEnumeration"
        return "CD3DEnumeration"

    # === gbBladeMgr.cpp ===
    if inferred_file == "gbBladeMgr.cpp":
        return "gbBladeMgr"

    # === gbSceneGraph.cpp ===
    if inferred_file == "gbSceneGraph.cpp":
        if 'SceneGraph' in code or 'Scene' in code:
            return "gbSceneGraph"
        return "gbGeomNode"

    # === gbVisNode.cpp ===
    if inferred_file == "gbVisNode.cpp":
        if 'VolMod' in code:
            return "gbVolModNode"
        return "gbVisNode"

    # === gbCamera.cpp ===
    if inferred_file == "gbCamera.cpp":
        if 'Control' in code:
            return "gbCameraControl"
        return "gbCamera"

    # === gbPrintFont.cpp ===
    if inferred_file == "gbPrintFont.cpp":
        if 'Mgr' in code or 'pFontMgr' in code:
            return "gbPrintFontMgr"
        return "gbPrintFont"

    if inferred_file == "gbGfxManager.cpp":
        return "gbGfxManager"
    if inferred_file == "gbGeomNode.cpp":
        return "gbGeomNode"
    if inferred_file == "gbResManager.cpp":
        return "gbResManager"
    if inferred_file == "gbImage2D.cpp":
        return "gbImage2D"
    if inferred_file == "gbChain.cpp":
        return "gbChain1D"
    if inferred_file == "gbAudioManager.cpp":
        return "gbAudioManager"
    if inferred_file == "gbActor.cpp":
        return "gbActor"

    # Single-class files
    if len(file_classes) == 1:
        return file_classes[0]

    # Multi-class files with no pattern match
    if file_classes:
        return file_classes[0]

    return None


def infer_name(code: str, signature: str, inferred_file: str,
               inferred_class: str | None, size: int) -> str:
    """Infer function name from decompiled code behavior."""
    if not code:
        return "?"

    is_thiscall = '__thiscall' in signature

    # --- Pattern detection ---
    has_vtable_set = bool(re.search(
        r'\*\s*(?:\(_DWORD\s*\*\)\s*)?this\s*=\s*(?:&\s*)?(?:off_|`)', code))
    if not has_vtable_set:
        has_vtable_set = bool(re.search(r'__vftable\s*=\s*&', code))
    if not has_vtable_set:
        has_vtable_set = bool(re.search(r'\*\(_DWORD\s*\*\)this\s*=\s*\(', code))

    base_ctors = find_base_ctor_calls(code)
    base_dtors = find_base_dtor_calls(code)

    has_new = 'operator new(' in code
    has_delete = 'operator delete(' in code
    has_free = 'free(' in code
    has_memset = 'memset(' in code
    has_release = '::Release(' in code

    # Count assignments
    zero_assigns = len(re.findall(r'=\s*(?:0|NULL)\s*;', code))
    this_assigns = len(re.findall(r'\*\(.*this.*\)\s*=', code))
    this_assigns += len(re.findall(r'this\[\d+\]\s*=', code))
    this_assigns += len(re.findall(r'this->.*=', code))
    this_assigns += len(re.findall(r'\*\(_DWORD\s*\*\)this\s*=', code))

    # --- DESTRUCTOR ---
    if is_thiscall and base_dtors:
        if inferred_class:
            return f"{inferred_class}::~{inferred_class}"
        return "?_Dtor"

    if is_thiscall and has_vtable_set and (has_delete or has_free or has_release):
        if inferred_class:
            return f"{inferred_class}::~{inferred_class}"
        return "?_Dtor"

    if is_thiscall and (has_delete or has_free) and not has_new and zero_assigns >= 2:
        if inferred_class:
            return f"{inferred_class}::~{inferred_class}"
        return "?_Dtor"

    # eh vector deleting destructor pattern (84/87 bytes, scalar deleting)
    if size in (84, 87, 83) and 'operator delete' in code:
        if re.search(r'scalar|vector', code) or (has_vtable_set and has_delete):
            # These are compiler-generated destructors
            if inferred_class:
                return f"{inferred_class}::~{inferred_class}"
            # Try to figure out from vtable class
            return "?_VectorDtor"

    if is_thiscall and has_release and not has_new and zero_assigns >= 2:
        if inferred_class:
            return f"{inferred_class}::Release"
        return "?_Release"

    # --- CONSTRUCTOR ---
    if is_thiscall and has_vtable_set and base_ctors:
        if inferred_class:
            return f"{inferred_class}::{inferred_class}"
        return "?_Ctor"

    if is_thiscall and has_vtable_set and zero_assigns >= 3 and not has_delete and not has_free:
        if inferred_class:
            return f"{inferred_class}::{inferred_class}"
        return "?_Ctor"

    if is_thiscall and (has_memset or zero_assigns >= 6) and not has_delete and not has_free:
        if has_vtable_set or base_ctors:
            if inferred_class:
                return f"{inferred_class}::{inferred_class}"
            return "?_Ctor"
        # Many zero-inits could be Init or Reset
        if size < 80:
            if inferred_class:
                return f"{inferred_class}::Reset"
            return "?_Reset"

    # --- GETTER (very short) ---
    if is_thiscall and size <= 15:
        if re.search(r'return\s+\*\(', code) or re.search(r'return\s+this', code):
            if inferred_class:
                return f"{inferred_class}::Get?"
            return "?_Getter"
        if this_assigns <= 2 and zero_assigns >= 1:
            if inferred_class:
                return f"{inferred_class}::Reset"
            return "?_Reset"

    # --- SETTER (short) ---
    if is_thiscall and size <= 30 and this_assigns >= 1 and this_assigns <= 3:
        if re.search(r'\*\(.*this.*\)\s*=\s*a\d', code):
            if inferred_class:
                return f"{inferred_class}::Set?"
            return "?_Setter"
        if zero_assigns >= 2:
            if inferred_class:
                return f"{inferred_class}::Reset"
            return "?_Reset"

    # --- LOAD (file reading) ---
    read_calls = len(re.findall(r'gbVFileSystem::Read', code))
    if read_calls >= 2:
        if is_thiscall:
            if inferred_class:
                return f"{inferred_class}::Load"
            return "?_Load"
        return "?_LoadFromFile"

    # --- RENDER (D3D draw) ---
    if re.search(r'DrawPrimitive|DrawIndexedPrimitive|SetStreamSource|SetIndices', code):
        if is_thiscall:
            if inferred_class:
                return f"{inferred_class}::Render"
            return "?_Render"
        return "?_Render"

    # --- D3D state ---
    if re.search(r'SetRenderState|SetTextureStageState|SetSamplerState', code):
        if is_thiscall:
            if inferred_class:
                return f"{inferred_class}::SetState"
            return "?_SetState"

    # --- Initialize (D3D device creation) ---
    if 'Direct3DCreate9' in code or 'CreateWindow' in code:
        if inferred_class:
            return f"{inferred_class}::Initialize"
        return "?_Initialize"

    # --- Device Reset ---
    if 'OnLostDevice' in code and 'OnResetDevice' in code:
        if inferred_class:
            return f"{inferred_class}::HandleDeviceReset"
        return "?_HandleDeviceReset"
    if 'OnLostDevice' in code:
        if inferred_class:
            return f"{inferred_class}::OnLostDevice"
        return "?_OnLostDevice"

    # --- BeginScene ---
    if 'gbGfxManager::BeginScene' in code or ('BeginScene' in code and is_thiscall):
        if inferred_class:
            return f"{inferred_class}::BeginScene"
        return "?_BeginScene"

    # --- Buffer management ---
    if 'NewVertexBubble' in code or 'NewIndexBubble' in code:
        if 'Lock' in code and 'Unlock' in code:
            if inferred_class:
                return f"{inferred_class}::BuildBuffers"
            return "?_BuildBuffers"
        if inferred_class:
            return f"{inferred_class}::AllocBuffers"
        return "?_AllocBuffers"

    if 'DelVertexBubble' in code or 'DelIndexBubble' in code:
        if inferred_class:
            return f"{inferred_class}::ReleaseBuffers"
        return "?_ReleaseBuffers"

    # --- Memory allocator ---
    if 'HeapAlloc' in code or 'VirtualAlloc' in code:
        if is_thiscall:
            if inferred_class:
                return f"{inferred_class}::Alloc"
            return "?_Alloc"

    if 'HeapDestroy' in code or 'VirtualFree' in code:
        if is_thiscall:
            if inferred_class:
                return f"{inferred_class}::~{inferred_class}"
            return "?_Dtor"

    # --- Find/Search ---
    if is_thiscall and size < 200:
        if re.search(r'(while|do)\s*[{(]', code):
            if re.search(r'==|strcmp', code) and 'break' in code:
                if inferred_class:
                    return f"{inferred_class}::Find"
                return "?_Find"

    # --- Update (time) ---
    if re.search(r'Time|Frame|Delta', code) and is_thiscall:
        if 'gbTimeCounter' in code or 'LastTime' in code:
            if inferred_class:
                return f"{inferred_class}::Update"
            return "?_Update"

    # --- CreateTexture ---
    if 'gbTexture_D3D' in code and has_new:
        if is_thiscall:
            if inferred_class:
                return f"{inferred_class}::CreateTexture"
            return "?_CreateTexture"

    # --- Error/Log ---
    if ('MessageBox' in code or 'gbReportError' in code) and not is_thiscall:
        return "?_ErrorHandler"
    if 'sprintf' in code and not is_thiscall:
        return "?_FormatString"

    # --- Init with allocations ---
    if is_thiscall and has_new and not has_delete:
        if inferred_class:
            return f"{inferred_class}::Init"
        return "?_Init"

    # --- Short reset ---
    if is_thiscall and size < 60 and zero_assigns >= 3 and not has_new and not has_delete:
        if inferred_class:
            return f"{inferred_class}::Reset"
        return "?_Reset"

    # --- Fallback ---
    if is_thiscall:
        if inferred_class:
            return f"{inferred_class}::?"
        return "?_Method"

    return "?_Function"


def analyze_function(entry: dict, inferred_file: str) -> tuple[str | None, str]:
    """Analyze a single function and return (inferred_class, our_name)."""
    addr = entry["addr"]
    size = entry.get("size", 0)

    # Find and load IDA JSON
    json_path = find_ida_json(addr)
    if not json_path:
        return None, "?"

    data = load_decompiled(json_path)
    if not data:
        return None, "?"

    code = data.get("decompiled_c", "")
    ida_sig = data.get("signature", "")

    # Infer class
    cls = infer_class(code, ida_sig, inferred_file)

    # Validate class
    if cls and cls in INVALID_CLASSES:
        cls = None

    # Infer name
    name = infer_name(code, ida_sig, inferred_file, cls, size)

    return cls, name


def main():
    # Load registry
    all_entries = []
    with open(REGISTRY_PATH) as f:
        for line in f:
            line = line.strip()
            if line:
                all_entries.append(json.loads(line))

    # Sort by address for adjacency-based file inference
    addr_to_idx = {}
    for i, entry in enumerate(all_entries):
        addr_to_idx[entry["addr"]] = i

    entries_sorted = sorted(all_entries, key=lambda e: int(e["addr"], 16))
    sorted_idx_map = {e["addr"]: i for i, e in enumerate(entries_sorted)}

    # Find unknown entries
    unknown_indices = []
    for i, entry in enumerate(all_entries):
        if entry.get("status") == "unknown":
            unknown_indices.append(i)

    print(f"Found {len(unknown_indices)} unknown functions to annotate")
    print(f"IDA JSON directory: {IDA_DIR}")
    print()

    # Process each unknown
    stats = {
        "total": len(unknown_indices),
        "class_inferred": 0,
        "class_none": 0,
        "name_confident": 0,
        "name_partial": 0,
        "name_unknown": 0,
        "no_json": 0,
    }

    results = []

    for idx in unknown_indices:
        entry = all_entries[idx]
        addr = entry["addr"]

        # Infer file from adjacency
        sorted_pos = sorted_idx_map[addr]
        inferred_file = infer_file_from_adjacency(entries_sorted, sorted_pos)

        cls, name = analyze_function(entry, inferred_file)

        # Update entry
        if cls:
            entry["inferred_class"] = cls
            stats["class_inferred"] += 1
        else:
            stats["class_none"] += 1

        if name and name != "?":
            entry["our_name"] = name
            if "?" not in name:
                stats["name_confident"] += 1
            else:
                stats["name_partial"] += 1
        else:
            entry["our_name"] = "?"
            stats["name_unknown"] += 1

        if inferred_file:
            entry["inferred_file"] = inferred_file

        results.append((addr, cls, name, inferred_file, entry.get("size", 0)))
        all_entries[idx] = entry

    # Write back registry
    with open(REGISTRY_PATH, 'w') as f:
        for entry in all_entries:
            f.write(json.dumps(entry, ensure_ascii=False) + '\n')

    # Print results grouped by file
    print("=" * 90)
    print("ANNOTATION RESULTS")
    print("=" * 90)

    by_file = {}
    for addr, cls, name, file, size in results:
        by_file.setdefault(file or "(unknown)", []).append((addr, cls, name, size))

    for file in sorted(by_file.keys()):
        entries_list = by_file[file]
        print(f"\n--- {file} ({len(entries_list)} functions) ---")
        for addr, cls, name, size in entries_list:
            cls_str = cls or "(global)"
            conf = " " if "?" not in name else "*"
            print(f"  {conf} {addr} [{size:4d}B] {cls_str:25s} {name}")

    # Summary
    print()
    print("=" * 90)
    print("SUMMARY")
    print("=" * 90)
    print(f"  Total unknown:        {stats['total']}")
    print(f"  Class inferred:       {stats['class_inferred']}")
    print(f"  No class (global):    {stats['class_none']}")
    print(f"  Name confident:       {stats['name_confident']}")
    print(f"  Name partial (?):     {stats['name_partial']}")
    print(f"  Name unknown:         {stats['name_unknown']}")
    print()

    # List confidently named
    confident = [(a, c, n, f) for a, c, n, f, _ in results if n and "?" not in n]
    print(f"  Fully identified ({len(confident)}):")
    for addr, cls, name, file in confident:
        print(f"    {addr}  {name:45s} [{file}]")


if __name__ == "__main__":
    main()
