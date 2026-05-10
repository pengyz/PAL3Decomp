# SceneMgr Binary Layout Analysis (PAL3.exe)

## Summary

`g_SceneMgr` @ `0x00C04390` in `.data` section.

**Size**: approximately **0xFE108 bytes (1,040,648 bytes ≈ 1016 KB)**

This is consistent with PAL3A PDB where Scene alone is 1,094,164 bytes.
SceneMgr contains one or more Scene objects plus management overhead.

## Reference Density Map

```
+0x00000-0x01FFF:  1621 refs  ████████████████████  HEADER + MAIN ARRAY
+0x02000-0x0BFFF:    63 refs  ▒                     sparse (large data buffers)
+0x0C000-0x0EFFF:  1085 refs  █████████████████     SECOND HOT ZONE
+0x0F000-0x1FFFF:    23 refs  ▒                     sparse
+0x20000-0xFFFFF:   ~250 refs ░                     long tail (NPC/Role data?)
```

## Confirmed Layout (from binary disassembly)

### Header (+0x0000 — +0x001C): Runtime Pointers

| Offset | Type | Name | Refs | Source |
|--------|------|------|------|--------|
| +0x0000 | `gbGfxManager*` | m_pGfxMgr | 22 | Create param 1 |
| +0x0004 | `void*` | m_pSceneRoot | 16 | Create param 3 |
| +0x0008 | `gbRenderEffect*` | m_pAddEffect2 | 25 | NewRenderEffect("additive_0") |
| +0x000C | `gbRenderEffect*` | m_pAlphaEffect2 | 6 | NewRenderEffect("alpha_0") |
| +0x0010 | `gbRenderEffect*` | m_pAddEffect | 30 | NewRenderEffect("additive") |
| +0x0014 | `gbRenderEffect*` | m_pAlphaEffect | 2 | NewRenderEffect("alpha") |
| +0x0018 | `gbCamera*` | m_pCamera | 3 | Create param 2 |

### Pre-Array Region (+0x001C — +0x0288)

Zeroed in `SceneMgr::Create` via `memset(this+0x1C, 0, 0x900)`.
Contains 620 bytes (0x26C) of unidentified data before the array.

### Main Array (+0x0288 — +0x1E08): stride=0x580, 5 elements

Detected from binary pattern: identical initialization at offsets
+0x0288, +0x0808, +0x0D88, +0x1308, +0x1888.

Each element is **1408 bytes (0x580)**. Key internal offsets:

| Elem Offset | Refs | Type | Notes |
|-------------|------|------|-------|
| +0x000 | 53 | DWORD | first field (highly accessed) |
| +0x004-0x034 | ~12ea | DWORDs | init block (13 DWORDs) |
| +0x034-0x038 | 14 | BYTE[4] | flags (byte-level access) |
| +0x06C | 19 | DWORD | |
| +0x0DC | 16 | DWORD | indexed pair (sub_460A90) |
| +0x0E4 | 23 | DWORD | |
| +0x0F0 | 22 | DWORD | |
| +0x286 | varies | BYTE | flag (sub_4E5800) |
| +0x288 | varies | DWORD | counter/state |
| +0x308 | varies | ptr | lea target |

**Element[4]+0x318 = SceneMgr+0x1BA0**: This is the embedded **CCBAI** (or related combat)
object's address. 325 references, all from CCBRoleState/CCBAI methods. Confirmed via
`MOV ECX, 0xC05F30` instruction pattern (ECX = this for thiscall).

### Second Hot Zone (+0xC000 — +0xEFFF)

| Offset | Refs | Access | Functions |
|--------|------|--------|-----------|
| +0xC5D0 | 15 | various | CGameData, EffectUpdate, PAL3::SnapScreen |
| +0xC5D8 | 12 | lea/ptr | CameraUpdate, PAL3::InitSubsystems |
| +0xC938 | 59 | mov_eax | CameraUpdate_Internal, ScriptSystem |
| +0xC9A8 | 296 | push_addr | CCBControlWindow (STRING buffer!) |
| +0xCD0C | 70 | fop_mem | RoleSystem::MoveRole/PathFind (float) |
| +0xD35C | 152 | mov_r1 | Camera::CheckCollision (pointer) |

The +0xC9A8 offset (296 refs) stores a **string** passed to UI functions.
The +0xD35C offset (152 refs) stores a **pointer** used by Camera collision.
The +0xCD0C offset (70 refs) stores a **float** used by RoleSystem path/movement.

### Rendering Data (+0xA91C — +0xA930)

Set in `SceneMgr::Create`:
```c
this+0xA91C = 0.0f;  // light direction X
this+0xA920 = 0.0f;  // light direction Y
this+0xA924 = 0.0f;  // light direction Z
this+0xA928 = 0.0f;  // up vector X
this+0xA92C = 1.0f;  // up vector Y (Y-up)
```

## PAL3A PDB Cross-Reference

PAL3A PDB has SceneMgr **forward-declared** (size=1, all member offsets=0).
Member names from PDB (offset unknown for PAL3):

| Member | PAL3A Type | PAL3A Size | Notes |
|--------|-----------|------------|-------|
| s_curscene | SCENE_TYPE | 4 | enum (STORYA/STORYB/FIGHT) |
| s_scene[3] | Scene | 3×1,094,164 | Scene = 1MB each in PAL3A! |
| s_scnfile | SCNFile | 187,596 | |
| m_objscript | SceneObjScript | 12 | |
| m_fHurtTime | float | 4 | |
| s_map[4] | SceneMapPlayer | 4×392 | Only 392 in PAL3A, 1408 in PAL3? |
| m_specialvariable_m17water | int | 4 | |
| m_specialvariable_m13unite | int | 4 | |
| m_GeomNote[10] | GeomNote | 10×7 | |

**Key Discrepancy**: PAL3A Scene is 1,094,164 bytes. If PAL3 has Scene[1] embedded
(not [3]), that alone explains the ~1MB size of SceneMgr in PAL3 binary.

## Recommendations for IDA

1. **Do NOT import PAL3A's SceneMgr struct** — it's forward-declared and useless
2. **Create a minimal SceneMgr struct** with the 7 header pointers + opaque regions
3. **Focus on the high-frequency offsets** for naming:
   - +0x1BA0: rename to `m_AI` or `m_RoleState` (CCBAI embedded)
   - +0xC9A8: rename to `m_szUIBuffer` (char[])
   - +0xD35C: rename to `m_pGeomNode` (gbGeomNode*)
   - +0xCD0C: rename to `m_fMoveParam` (float)
4. **The array at +0x288** (5×1408) may be `s_map[5]` (extended from PAL3A's [4])
   or a completely different organization

## Open Questions

1. What is the actual SceneMgr end boundary? (no next global found in data)
2. Are offsets >0x10000 from embedded Scene object or separate arrays?
3. The 5-element array: is it s_map (PAL3A has [4]) or something else entirely?
4. Relationship between memset regions in Create and the array structure
