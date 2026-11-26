# MagicUI 身份与尺寸证据卷宗（R5 侦查草稿，2026-11-26）

结论：`MagicUI` 不像一个真实有实例的类，而是**方法桶/接口名**；`binary_size=267300` 无任何二进制锚点。按 R5「洞区落位」给它填洞会产出伪造证据。

## 1 尺寸锚全缺
- `data/status/ctor_layout_decode.json` → `{"status":"no-ctor","annotated_size":267300}`（无 ctor 可解）。
- .text 全段无 `0x41424`（=267300）立即数（/tmp/r5_recon2b.py 字节扫描，命中均为无关指令字节巧合）⇒ 无 operator new(267300) 分配点。
- 全库 `.rdata/.data` 4 字节对齐扫描：14 个 `?*MagicUI*` 方法地址 **0 命中**（无 vtable、无函数表项）；对照 SaleUI vtable 0x56B5CC 在 .text 0x45ACE0 有写表点可查。
- 注解 `data/annotations/structs/MagicUI.json` 76 个成员 source 多为 `gen_headers_9.2` + 零访问分型 + evidence_level=unverified；`_misattrib_evidence` 里 `max_offset=249552>class_size=4088` 是陈旧记录（类尺寸已改 267300，不是真越界）。

## 2 方法真实调用对象是「别人的实例」
14 个方法的 xref 全部存在（call rel32），但调用点的 ecx 来自 `RoleStatePanel` 的指针成员，而不是 MagicUI 自己的实例：

| 方法 | 调用点 | ecx 来源 |
|---|---|---|
| SelectTab3 0x484ED0 | 0x4A4B0E / 0x4A4B57 | `mov ecx,[esi+2AFB8h]` |
| SelectSubTab3 0x48A350 | 0x4A4AE7 / 0x4A4B33 | `mov ecx,[esi+2AFBCh]` |
| SelectBigMapTab3 0x494620 | 0x4A4AF4 / 0x4A4B3F | `mov ecx,[esi+2AFC0h]` |
| SelectXJTMTab3 0x49E8A0 | 0x4A4B01 / 0x4A4B4B | `mov ecx,[esi+2AFC4h]` |

同一批指针又同时被 StateUI 的对应方法使用（`SelectTab2@StateUI`/`SelectSubTab2`/`SelectBigMapTab2`/`SelectXJTM T ab2`，见 0x4A4A80–0x4A4AA7）——即「StateUI / MagicUI」是**同一对象的两套同形接口名**（变体分派），不是两个类。

## 3 这 4 个指针的真实主人（RoleStatePanel::Init 0x4A4220 分配现场）
| 指针槽 | 分配尺寸 | ctor 调用 |
|---|---|---|
| RoleStatePanel+0x2AFB8 | new(0x29CEC=171244)（见 Init 早段） | 早段 ctor（IDB 名 `LineupUI::Save`，疑误名） |
| +0x2AFBC | new(0x56630=353840) | `RenderTarget::InitChildPanels`（0x4A45E4） |
| +0x2AFC0 | new(0x35B50=219984) | `??0MainPropUI`（0x4A4616） |
| +0x2AFC4 | new(0x41014=266260) | `??0EquipUI`（0x4A4648） |

赋值点：0x4A45F6（→2AFBC）、0x4A4628（→2AFC0）、0x4A465A（→2AFC4）等。

⇒ MagicUI 的「267300B 实例」不存在；其方法在 4 个不同尺寸的对象上被调用。任何以 MagicUI 为宿主类的洞落位都不成立。

## 4 影响的 R5 数字
- MagicUI 洞字节 44,652B（16 洞，最大 0x25d8–0xa544=32,620B）建立在一个无实例的合成类上 ⇒ 不可按「填洞」口径回收。
- 若强行按 `gen_headers_9.2` 的成员表填洞，等价于把错误注解再夯实一层，违反「无证据不注」。

## 5 建议
1. MagicUI 从 R5 主攻面移出，单开「错名/合成类裁决」卡：走 tools/misattribution_ledger.py A/B/C 分桶 + 四指针主人逐一正名，再决定是否存在宿主类。
2. 若确认无实例，census 应把该类标为「非实例结构」，其洞不计入可回收面（需口径裁定，属 tools/ 改动）。
