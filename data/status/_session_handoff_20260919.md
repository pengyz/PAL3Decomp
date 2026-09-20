# 会话交接（2026-09-19，HEAD = d341ed42b + 10 条已落盘标注修正）

> ## 目标状态：**未完成**（goal `goal-e90a735c…`，30 轮用尽，phase=active）
>
> §49.4 **(1)** 9 条定案 **2** 条；**(2)** 11 条定案 **5** 条（另含 2 条签名修正）；
> **(3)** 落盘→验证闭环跑通 **10** 次，但"对发布基线 `new_failures` 归零"仍差
> **`__vftable` 裸链**那一项（2 个失败文件）。**下一步的确切入口见 §4 与
> `_baseline_repro_20260919.md` §14.2**（给形态 A 补 `cls_hint`：形态 A 无 cast ⇒ `cls_hint=None` ⇒ 消费者无法解析）。
> 非阻塞：剩余三项都是**有明确判据与验法的剩余工作**，不是卡死。
>
> 本文是**索引 + 状态**，不重复细节。细节在同目录的
> `_baseline_repro_20260919.md`（基线/收敛/队列）、`_size_evidence_20260919.md`（尺寸）、
> `_attribution_evidence_20260919.md`（归属）、`../annotations/CHANGE_LOG.md`（逐条证据）、
> `../knowledge/`（通用规律）。

## 1. 已落盘并逐条验证的改动（10 条）

| # | 类型 | 对象 | 内容 | 证据位置 |
|---|---|---|---|---|
| 1 | 尺寸 | `CCBProtectWindow` | `binary_size` 176 → **2632** | CHANGE_LOG 2026-09-19 §1；`_size_evidence` §2.1 |
| 2 | 尺寸 | `UIRenderObj` | `binary_size` 4 → **32**（两侧夹逼） | CHANGE_LOG §UIRenderObj；`_size_evidence` §7.1 |
| 3 | 归属 | `0x00504240` | `CIniFile::LoadFullConfig` → **`CCBStage`** | `_attribution_evidence` §5 |
| 4 | 归属 | `0x004C5DB0` | `CEffectSystem::GetThreadHandle` → **`CEffect::Activate`** | 同上 §6 |
| 5 | 归属 | `0x004C5DE0` | `CEffectSystem::ReleaseParticle` → **`CEffect::ReleaseTextures`** | 同上 §6 |
| 6 | 归属 | `0x004C5B90` | `_Texture_uv::operator=` → **`CEffectSystem::SetEffectVisible`** | 同上 §8.1 |
| 7 | 签名 | `0x004C5B90` | 残留旧签名 → `void __thiscall CEffectSystem::SetEffectVisible(int, unsigned char)` | 同上 §8.1 附 |
| 8 | 归属 | `0x00525080` | `UIWnd::_todo_525080` → **`PalScriptMgr::Get_m_nField_1490`** | 同上 §9.1 |
| 9 | 签名 | `0x00525080` | 残留旧签名 → `int __thiscall PalScriptMgr::Get_m_nField_1490()` | 同上 §9.1 附 |
| 10 | 归属 | `0x004CDAE0` | `gbRefObject::ReleaseAllRefs` → **`CEffMgr::ReleaseAllRefs`** | 同上 §12 |

**每条都过了验证清单**（同谱系改前/改后：`new_failures = 0`、L1 未回退）。

## 2. 被门禁挡下并**主动回退**的改动（4 批）—— 门禁在真实生效

1. 3 条 thunk 标 `skip` 与 `CCBProtectWindow` 尺寸一起落盘 ⇒ **L1 21→20**，整批回退（拆分后确认代价全在那 3 条上）；
2. 上条拆分出"只落尺寸"⇒ 中性，留下（即上面第 1 条）；
3. `cli.py init` 的"5 趟 apply"版本 ⇒ **复现不出** 71/201，未验证 ⇒ 回退；
4. `cli.py init` 的"5 对 (apply+fix_vtable)"版本 ⇒ 同样未复现 ⇒ 回退。
   （现只保留第 2 轮那条**已验证**的"两趟"修复。）

## 3. 当前实测口径（本机：Windows + IDA 9.2）

* **本地可复现**（`init --force` 两趟 + 全部 10 条）：S2 **70/201** · matched **222/256** · **L1 21** · 错误 ~2460。
* 对**发布基线**（`baselines/latest.json`，2026-09-19T00:05:52）：**新失败 3 / 已修复 4**。
* **长寿命 IDB 谱系**（注解版本序列 + 反复 apply/export 交替）：S2 **71/201** · matched **225/259** · L1 21
  —— 其中 `ScreenEffect.cpp` 转 ok ⇒ 那个新失败**不是 codegen 缺陷**，是 IDB 未收敛的产物。
* 共享棘轮 `data/status/s4_baseline.json` **始终未被推进**（保持发布值 L1 18 / matched 228）——
  本机读数与发布值不同源，不应单机推进共享文件。

## 4. 未闭合项与**确切的下一步**

| 优先级 | 项 | 状态与下一步 |
|---|---|---|
| 1 | **`__vftable` 裸链（11 处 → 2 个新失败）** | 方案已**完全机械化**（`_baseline_repro` §14）：识别 `RECV->__vftable->NAME(` 与其 cast 包裹形态 → 查接收者类 vtable 注解得槽归属类 `Owner`（`UIWnd` 第 7 槽 `0x00445D10` → `CGameData`）→ 发射 `((Owner *)RECV)->Owner::NAME(...)`（cast 形态需去掉作为 this 的首参）。先例 `free_functions.cpp:5798`（全仓 `CGameData::OnMessage(` 50 处）。**只差实现 + 一次全链验证**（预期消掉 `UIProgressBar.cpp`+`UIStatic.cpp`） |
| 2 | **IDB 收敛机制** | 四种假设已证伪（趟数 3/5、成对跑、`[6b3]` 判据、export 改 IDB）。剩下唯一解释：**不同注解版本的序列留下残留**。验法：从干净 IDB 按"改动前注解 → 改动后注解"分两步 apply，看能否复现 71/201。**这条不闭合，任何"干净重建复算历史读数"都不成立** |
| 3 | **`CEffMgr` 区段协同改** | `tagEffClass=72` 有**两侧证明**（`0x1C+32×72=0x91C` 精确落在 `m_EffTable` 起始）；但跨度内压着 **20 个**与指令冲突的成员（`m_fPosX`@0xA0 被当字节读、`m_fPosZ`@0xA8 被当指针用）⇒ 必须一次改完 + 全链验证（`_size_evidence` §8） |
| 4 | **`sub_479260` / `sub_4EC700` / `sub_504130`** | 前者有强签名（632 步长、基址 `+0xC2F80`）但宿主成员表在该区间为空；`sub_504130` 判定为"`this` 是结构体中间指针 ⇒ 很可能不是成员函数"；需 dataflow 或先补宿主成员模型 |

## 5. 本会话新增的可复用资产

* `tools/alloc_point_size.py` —— 分配点 → 对象真实尺寸（304 个分配点/141 个挂到 ctor）；
  判据 `push N; call operator new; …; mov ecx,eax; call <ctor>`。
* `tools/attribution_offset_match.py` —— this 字节偏移 ⇄ 类成员边界**精确**匹配（含 `--strict`）；
  文档里写明三条已知漏采形态（索引寻址、this 中途重装、负偏移已支持）。
* `tools/apply_annotation_batch.py` 扩展 —— `set_size` / `skip_method` / `set_signature`，
  并在"旧签名仍含原类名"时 WARN（搬类不搬签名的坑，踩了两次后做成机制）。
* 管线修复 —— `pipeline/snapshots/snapshot.py` 的 Windows 编码崩溃；`pipeline/cli.py init` 的第二趟 apply。
* 知识库 4 条（2 条新增 + 2 条更新）与 kairos 28 行。

## 6. 三条最该记住的纪律（本会话反复验证）

1. **只在同一 IDB 谱系内做改前/改后对比**（§3 已证明跨谱系会差 ±1 文件 / ±3 符号）。
2. **只有"精确命中"可作归属判据**；"成员内"会被末成员跨度兜底高估（工具文档已注明）。
3. **工具报"0 个偏移"必须手工读 asm** —— 本会话 3 条定案（`0x4C5B90`/`0x525080`/`0x4CDAE0`）全靠手工读。
