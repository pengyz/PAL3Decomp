# vtable slot-annotation proposal (read-only survey)

Scope: make `store.struct_vtables[cls]` name **every** slot index N that Hex-Rays actually 
references, so that `_resolve_vtbl_method()` can safely switch from `d['offset'] // 4` to `d['offset']`.

No file was modified except this pair. No IDB write, no `pipeline/` change, no `pal3/src` change,
no `match`/`codegen all`.

## 0. How the must-cover set was measured (reproducible)

1. Naive scan `__vftable + N` over `asm/pal3/decomp/*.json`: **866** hits, but only **89** are vtable
   dispatches. The rest are `&obj->__vftable + N` (**object memory at offset 4*N**, not a slot) or
   `*(_DWORD *)obj->__vftable + N` (integer byte arithmetic). Any table that counts those produces
   phantom rows (see §6).
2. Authoritative measurement: import `stages.stage3_cleanup`, call the real `run(code, ctx)` for every
   decomp file with a spy on `_resolve_vtbl_method`, and additionally re-match the legacy `_vtable_re`
   on the produced text. This is what actually consumes `store.struct_vtables`.
   * `_resolve_vtbl_method` (AST path) gets a usable `cls_hint` **only after run()'s pre-pass strips
     `__thiscall `** — measuring on raw decomp text gives `cls_hint = None` everywhere and hides the set.
   * the legacy `_vtable_re` resolver already uses `slot = N` (line 887), so its gaps are pre-existing.

### Must-cover set (authoritative)

| class | referenced N | current covered idx | source of the reference |
|---|---|---|---|
| `gbGfxManager` | 0, **2**, **12**, **13**, **15**, **21**, **22**, **23**, **25**, **26**, **28** | 0-6 | AST+legacy |
| `gbTexture` | 0,2,**4**,**5** | 0-3 | AST+legacy |
| `gbActorDef` | **7**, **15** | (no vtables at all) | AST+legacy |
| `gbRenderEffect` | **2** | (no vtables at all) | legacy |
| `SceneObj` | 1 | 1 = `ValidateState` OK | AST |
| `CTaskTpl_tagEffTaskParam_CEff{Action,Cylinder,Grid,Meteor,Quake,SParticle,gbParticle}` | **1** | (files exist, no methods/vtables) | AST |
| `StateUI`,`UIStatic`,`CCBProtectWindow` | **0** | slot0 addr present, no `methods` entry | AST |

Bold = needs action. `N=5` for `gbTexture` and `N=2` for `gbRenderEffect` are **out of the real vtable
range** and cannot be named from evidence (§2.3, §4).

Measured effect of the pending change today: **51 / 3598** decomp files change. The dominant change is a
**fix** (`gbGfxManager N=2`, 47 sites: `//4` -> slot 0 -> `~gbGfxManager()`, `N` -> slot 2 -> `NewTexture()`,
which is what the source says: `this->m_pbk = gfxMgr->NewTexture(...)`). The regressions come from the
gbGfxManager 12/13/15/21/22/23/25/26 and gbTexture 4/5 sites, i.e. exactly the slots proposed here.

## 1. `gbGfxManager` — grade A, 29/29 slots, full 0..28 proposed

Primary evidence `include/gbengine/gbGfxManager.h:140-169` (explicit `// slot N` comments).
Cross-validation `original/gbengine.dll.asm:433353` — `off_100F56B4`, the `gbGfxManager_D3D` vtable:
**exactly 29 dwords**; each of the 28 overrides the header claims an address for matches the table
index-for-index (27 exact addresses + slot 3 left as the base symbol `?NewMesh@gbGfxManager@@`).

| slot | name | header | DLL table `off_100F56B4[i]` |
|---|---|---|---|
| 0 | `~gbGfxManager` | `gbGfxManager.h:141` | `0x10018BB0` |
| 1 | `MsgProc` | `gbGfxManager.h:142` | `0x1001B4C0` |
| 2 | `NewTexture` | `gbGfxManager.h:143` | `0x10019040` |
| 3 | `NewMesh` | `gbGfxManager.h:144` | `?NewMesh@gbGfxManager@@ (base, not overridden)` |
| 4 | `NewVertexPool` | `gbGfxManager.h:145` | `0x100190D0` |
| 5 | `NewIndexPool` | `gbGfxManager.h:146` | `0x10019140` |
| 6 | `NewDynVertBuf` | `gbGfxManager.h:147` | `0x100191B0` |
| 7 | `SetFrustum` | `gbGfxManager.h:148` | `0x10019220` |
| 8 | `SetOrtho` | `gbGfxManager.h:149` | `0x100192B0` |
| 9 | `SetViewport` | `gbGfxManager.h:150` | `0x10019380` |
| 10 | `SetLight` | `gbGfxManager.h:151` | `0x100193E0` |
| 11 | `SetMaterial` | `gbGfxManager.h:152` | `0x10019460` |
| 12 | `BeginScene` | `gbGfxManager.h:153` | `0x10018CD0` |
| 13 | `Present` | `gbGfxManager.h:154` | `0x10018F00` |
| 14 | `DrawIndexedPrimitive` | `gbGfxManager.h:155` | `?NewMesh@gbGfxManager@@ (base, not overridden)` |
| 15 | `DrawPrimitive` | `gbGfxManager.h:156` | `0x10019500` |
| 16 | `GetFrustumPlanes` | `gbGfxManager.h:157` | `0x10019620` |
| 17 | `GetGfxCaps` | `gbGfxManager.h:158` | `0x1001B190` |
| 18 | `ApplyTransform` | `gbGfxManager.h:159` | `0x10009210` |
| 19 | `SetGammaRamp` | `gbGfxManager.h:160` | `0x1001B210` |
| 20 | `GetGammaRamp` | `gbGfxManager.h:161` | `0x1001B2B0` |
| 21 | `CreateDepthStencil` | `gbGfxManager.h:162` | `0x10018F40` |
| 22 | `RestoreDepthStencil` | `gbGfxManager.h:163` | `0x10019030` |
| 23 | `SetRenderTarget` | `gbGfxManager.h:164` | `0x1001B360` |
| 24 | `LoadCursor` | `gbGfxManager.h:165` | `0x1001B840` |
| 25 | `SetCursor` | `gbGfxManager.h:166` | `0x1001B9D0` |
| 26 | `ShowCursor` | `gbGfxManager.h:167` | `0x1001BA00` |
| 27 | `SetSoftwareVP` | `gbGfxManager.h:168` | `0x1001BA20` |
| 28 | `SetFog` | `gbGfxManager.h:169` | `0x10019480` |

**Conflict (non-blocking):** slot 14 — the header claims `0x100194F0` but the D3D table holds
`nullsub_8`. Slot 14 is not referenced by Hex-Rays, so it does not affect the change.

Keyed by the mandated synthetic convention `addr = 0x00010000 + slot` (`methods` entries carry
`"ordinal": slot`).

## 2. `gbTexture` — grade A for the table, conflict for the slot indices

Real tables (both 5 dwords, `original/gbengine.dll.asm`):

```
gbTexture      @0x100F57E8 (433437): [loc_100203A0, __purecall, __purecall, __purecall, __purecall]
gbTexture_D3D  @0x100F5738 (433391): [loc_1001BA80, CreateFromMemory, UpdateTexture,
                                      CreateForRenderTarget, CreateFromFileMemory]
```

`data/gbengine_registry.jsonl` confirms the four function addresses are real:
`0x1001BD30 gbTexture_D3D::CreateFromMemory`, `0x1001BEA0 ...::UpdateTexture`,
`0x1001BF80 ...::CreateForRenderTarget`, `0x1001C010 ...::CreateFromFileMemory`.

**Defect:** the annotation stores those four addresses at indices **0..3**; the truth is indices
**1..4** (slot 0 is the scalar deleting destructor). Fix = move them, do not append.
`data.py` joins `slots[i].addr` to `methods`, so the off-by-one silently mis-names every resolution
(`//4` currently masks it because 4//4 = 1 and 5//4 = 1).

### 2.3 Unresolved: `__vftable + 5`

`CCBParabolaWindow::Destroy` (PAL3.exe `sub_51C880`) and `CCBProtectWindow::Destroy` (`sub_5164D0`)
both emit `(*((int (__thiscall **)(gbTexture *, int))m_pbktex->__vftable + 5))(m_pbktex, 1)`.
Binary: `mov ecx,[esi+48h]; mov eax,[ecx]; push 1; call dword ptr [eax+14h]` — 0x14 = 20 bytes =
**slot 5**, so "N = slot index" holds here too. But `gbTexture`/`gbTexture_D3D` contain only 5 dwords
(slots 0..4). => the object at that member is **not** a plain `gbTexture`, i.e. the IDB member type
(`UIFrameWnd`/`UIGameOver` `m_pbktex : gbTexture *`) is wrong, or the call is not a vtable dispatch.
**No name can be derived from evidence — slot 5 stays `null`.**
Impact: after the change this site falls to the `pal3_vtbl_unk` stub path. That is a *deliberate*
degradation, not a wrong name; but it is the reason `Misc/UIStatic.cpp`-family files were seen to fail.
Whoever lands the change must first fix the member type (needs IDA work, out of scope here).

## 3. `gbActorDef` — grade B names, no binary table

No `vtables`/`methods` block exists. IDA never named the hierarchy: `original/gbengine.dll.asm` has
**zero** `gbActorDef` symbols (`gbActorDef` appears only as a parameter type of `gbActor::gbActor`),
`gbActorDef` is not among the 27 exported `??_7` tables, and no `??_7...ActorDef` run exists in .rdata.

| slot | proposed name | evidence |
|---|---|---|
| 7 | `GetCollideOBB` | `include/gbengine/gbActor.h:74` (`// vtable[7] offset 0x1C`). **Conflict:** the only call site `PAL3.exe sub_536FD0` does `call dword ptr [edx+1Ch]` and *returns* the result (`retn 4` passes (this, int, gbActor*)), while the header declares `void GetCollideOBB(gbOBBox*, gbActor*)`. Name kept, return type flagged. |
| 15 | `SetCurMaterial` | `include/gbengine/gbActor.h:82`; three call sites (`Actor::SetMaterialName`, `SetTextureName`, `SetVisible`) pass exactly one `char *` name, matching `SetCurMaterial(char*)`. |

Addresses are **synthetic** (`0x00020000+slot`) because no real table address is recoverable here.

## 4. `gbRenderEffect` — conflict, must stay `null`

`PAL3::ClearAdditiveEffects` (`PAL3.exe 0x004C0400`) does `mov ecx,[eax]; push eax; call dword ptr
[ecx+8]` on all three members — slot **2**. But `??_7gbRenderEffect@@6B@`
(`original/gbengine.dll.asm:433107`) holds **exactly one dword** (`sub_10004CB0`), and
`gbRenderEffect::gbRenderEffect` (`0x1001CEF0`) writes that same symbol. So slot 2 does not exist.

Corroboration that the cast type is wrong rather than the slot: `PAL3.json` already documents the
same `[+8]` access as `Release()` — and `gbRefObject::Release` (`0x1002F7F0`) is **non-virtual**,
so it holds no slot. => evidence insufficient; `null`.
Not blocking: stage3 leaves the raw text verbatim (both before and after the change) and it compiles.

## 5. The seven `CTaskTpl_tagEffTaskParam_CEff*` classes — grade B/C

All seven annotation files exist with `known_members` only. The dispatch Hex-Rays emits is
`(*((void (__thiscall **)(CTaskTpl_tagEffTaskParam_CEffX *, _DWORD,_DWORD,_DWORD))vN->__vftable + 1))(...)`
— a genuine **slot-1** virtual call (verified in `sub_4C0740`: `mov edx,[esi] … call dword ptr [edx+4]`),
emitted through the *template base* name (`template_bases.json`) rather than the derived class, so
`struct_vtables` must be keyed by the template-base name.

| template-base key | derived vtable | slot1 addr | proposed name | grade |
|---|---|---|---|---|
| `CEffAction` | `CEffAction` @0x0056F5E4 | `0x004C0650` | `AllocSegments` | C |
| `CEffCylinder` | `CEffCylinder` @0x0056F7C8 | `0x004C4060` | `Create` | C |
| `CEffGrid` | `CEffGrid` @0x0056F920 | `0x004C98F0` | `Create` | C |
| `CEffMeteor` | `CEffMeteor` @0x0056F978 | `0x004CB800` | `Create` | C |
| `CEffQuake` | `CEffQuake` @0x0056FA88 | `0x004C0650` | `AllocSegments` | B |
| `CEffSParticle` | `CEffSParticle` @0x0056FB34 | `0x004C0650` | `AllocSegments` | C |
| `CEffgbParticle` | `CEffgbParticle` @0x0056F8CC | `0x004C8A40` | `CreateTask` | B |

`0x004C0650` is shared by `CEffAction`/`CEffQuake`/`CEffSParticle` (COMDAT folding); the decomp export
names it `CEffQuake::AllocSegments(int)` — grade C. Its IDA signature (`retn 4`, one stack arg)
**conflicts** with the observed three-argument call site, so the name is provisional.

## 6. Slot 0 of the exe UI classes — grade A, and the phantom rows

59 exe vtables share `slots[0] = 0x00445E70`. `PAL3.exe .rdata off_56AE2C[0] = sub_445E70` (UIWnd
vtable) and the decomp export names `0x00445E70` = `UIWnd::ShowWindow(int)`. The address has a
`methods` entry only in `UIWnd.json`, so `data.py` drops slot 0 for `StateUI`, `UIStatic` and
`CCBProtectWindow`. Fix = add the same `methods` entry in those three files (slot 0 is already in
their `vtables[0].slots[0]`).

**Phantom rows in the task table.** Reproducing the table with a loose "nearest preceding cast"
attribution pulls in `&obj->__vftable + N`, which is object memory:
* `CEffect` N=3/N=8 — from `*((_DWORD *)&v2->__vftable + 3)` etc. in `CEffCylinder::ProcInitTask`,
  `CEffQuake::AllocSegments`, … No `**)(CEffect *` dispatch cast exists anywhere in the corpus;
  `CEffect` has **zero** genuine slot references.
* `ParticleEffect` N=7 — from `*((_DWORD *)&this[1].CTaskTpl_…CEffgbParticle::__vftable + 7)`.
* `SceneObj` N=6 — from `*((CCBStage **)&this->SceneObj::…::__vftable + 7)` (offset 24/28 bytes).
* `gbActorDef` N=7 additionally appears as an `int`-cast row (`int` N=21) and `LONG` N=86 — cast-parse
  artifacts with no class to annotate.
They need no annotation (and `CEffect`/`ParticleEffect` must not be annotated on this evidence).

## 7. Answer: can `//4` -> `N` be landed safely?

**Not yet — one blocker, everything else is ready.**

* `gbGfxManager` (grade A) and the three slot-0 exe classes (grade A) are fully specified here: after
  applying them the gbGfxManager part of the regression disappears and 47 mis-resolutions become correct.
* `gbTexture` needs the index shift (§2) **plus** a decision on the two `__vftable + 5` sites, which
  have **no evidence-based name** and must fall back to the stub. If those two files must stay `ok`,
  the member type has to be fixed first — this is the one true blocker.
* `gbActorDef` (`SetCurMaterial`, grade B) removes 3 of the 4 remaining legacy-path misses; slot 7 is
  named but flagged.
* `gbRenderEffect` N=2 cannot be named from evidence; it is unaffected by the change, so it is not a
  blocker.
* Everything else in the table is either already covered (`SceneObj`) or a phantom row.

Recommended order: (1) add gbGfxManager 7..28, (2) add `ShowWindow` to the three exe classes,
(3) fix the gbTexture index shift, (4) add the seven `CTaskTpl_*` slot-1 entries, (5) add gbActorDef,
(6) decide the two `gbTexture + 5` sites, then (7) flip `//4 -> N` and re-run `match` to confirm no
L1 regression.
