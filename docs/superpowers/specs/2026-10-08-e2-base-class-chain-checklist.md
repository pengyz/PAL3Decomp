# E2 补 base_class 继承链 — 三条硬裁决清单

**日期**：2026-10-08
**状态**：待执行（本清单是下次推进的可执行依据）
**风险**：⚠️ **高** —— `base_class` 写错 → codegen 发射"合法编译但 this 调整错误"的调用 → **运行时崩溃，S2 编译探针查不出**（知识库 `arch_gbui_seven_slot_vtables_inheritance_chain.md` 明示）

---

## 0. 目标与预期

| 项 | 值 |
|---|---|
| 目标 | 补全 UI 家族的 `base_class` 继承链，让 `ast_transform` 能判定"基类直调"合法 |
| 预期收益 | 消化 **~500±50 处 MISATTRIBUTED**（约 50%）|
| 不适用 | 全局单例/成员对象/命名错位簇（~180+ 处）|

> ⚠️ **2026-10-08 修正**：原估计"~500±50 MISATTRIBUTED"**量错了对象**。实测当前 `[ROWTABLE]`=544、`[MISATTRIBUTED]`=9、`C2352=0`。**收益估计改为 ~0**。详见 `2026-10-08-e2-prime-design.md`。

## 1. 知识库给出的链（**不可直接写入，须逐类三裁决**）

```
CCBResultWindow → UIFrameWnd → UIWnd → SceneObj → CGameData(根)
```

## 2. 当前状态（与知识库冲突）

| 类 | 当前 `base_class` | 知识库 | 状态 |
|---|---|---|---|
| `CGameData` | `None` | 根 | ✓ |
| `SceneObj` | `['PalScriptWaitObj','GlowObj','TaskMgr_SceneObjParam_SceneObj']` | `CGameData` | ⚠️ **冲突** |
| `UIWnd` | `None` | `SceneObj` | ⚠️ **缺失** |
| `UIFrameWnd` | `['UIWnd']` | `UIWnd` | ✓ |
| `CCBResultWindow` | `['UIFrameWnd']` | `UIFrameWnd` | ✓ |

**全仓**：898 个 struct，**719 个 `base_class` 为空**。

---

## 3. 三条硬裁决（**每个类写入前必做**）

### 裁决 1：thunk 检查（二进制）

**目的**：确认该类的 vtable 槽是否需要 `this` 调整（多继承证据）。

**判据**：
- 槽函数字节以 `83 e9 <N>`（`sub ecx, N`）开头 ⇒ **this-adjustment thunk** ⇒ 该类有多继承第二基
- 无 thunk ⇒ 槽均为 `this` 在偏移 0（单继承或基类在偏移 0）

**命令**（已跑通，可复用）：
```python
# 读 vtable 的 7 个槽，检查函数字节
import struct
d=open('original/PAL3.exe','rb').read()
# ... 解析 PE → .text/.rdata 的 VA↔文件偏移
# 对每个槽地址：读 12 字节，检查前 2 字节是否 83 e9
```

**已测结果**：
| 类 | vtable | thunk |
|---|---|---|
| `UIWnd` | `0x56AE2C` / `0x56AEC8` / `0x56AFB0` | **无**（三表均无 `sub ecx,N`）|

### 裁决 2：ctor/dtor 安装顺序互证（二进制）

**目的**：确认继承链（基类 vtable 先装，派生类覆盖）。

**判据**：
- 派生类的 ctor 里，基类 vtable 先写、派生类 vtable 后写
- dtor 反向（派生类先恢复基类 vtable）

**命令**：
```python
# 在 .text 中搜 C7 01 <vtbl_addr>（mov [ecx], imm32）
# 对每个 vtable，找它的写入点，看上下文里是否还有其他 vtable 写入
```

**已测结果**：
| 地址 | 写入 | 备注 |
|---|---|---|
| `0x004431D0` | `mov [ecx], 0x56AE2C`（UIWnd#1）| 单一写入 |
| `0x0044A7F9` | `mov [ecx], 0x56AFB0`（UIWnd#3）+ `mov [edx], 0x56AFA4` | ⚠️ **双对象写入**（MI 或成员对象）|

⚠️ `0x0044A7F9` 的双写入需进一步判定（`0x56AFA4` 是什么？成员对象还是第二基？）

### 裁决 3：槽兼容（注解 + 二进制）

**目的**：确认派生类的 vtable 槽是基类的**超集**（继承不丢槽）。

**判据**：
- 派生类 vtable 的前 N 槽 == 基类 vtable 的全部槽（地址相同）
- 多出的槽是派生类新增/覆写

**命令**：
```python
# 对比基类与派生类的 vtable 槽地址序列
```

---

## 4. 逐类执行清单

### 4.1 `UIWnd`（最小改动，KB 兜底 + thunk 已验证）

- [ ] **裁决 1** ✅ 已做：三表无 thunk
- [ ] **裁决 2**：找 UIWnd 的 ctor（`0x004431D0` 附近），确认它是否先装 `SceneObj` 的 vtable
- [ ] **裁决 3**：对比 `UIWnd` 与 `SceneObj` 的 vtable 槽序列
- [ ] **写入** `UIWnd.base_class = ['SceneObj']`
- [ ] **验证**：`vtable_mapper` `own_unresolved` 保持 0 · 全链跑一次 S2 不降

### 4.2 `SceneObj`（**冲突，需先澄清**）

- [ ] **先澄清**：当前 `base_class=['PalScriptWaitObj','GlowObj','TaskMgr_...']` 与 KB 的 `CGameData` 冲突
  - 可能是**多继承**（`SceneObj : public PalScriptWaitObj, public GlowObj, ...`）
  - 也可能是**注解错误**
- [ ] **裁决 1-3**：逐基类做
- [ ] **写入**（若确认）
- [ ] **验证**

### 4.3 其余 UI 家族（`UIProgressBar`/`UIButton`/`UISceneFrm`/`UIListBox`/`SaleUI`/`LineupUI`/`EquipUI`/`StateUI`/`RenderTarget`/`UITitle`…）

- [ ] 逐类做三条硬裁决
- [ ] 写入 + 验证

---

## 5. 验收（每写一个类后必做）

| 判据 | 命令 | 门槛 |
|---|---|---|
| `vtable_mapper` 未破坏 | `own_unresolved` | **保持 0** |
| S2 不降 | `loop --stages codegen,probe,match` | **不劣于当前 99/210** |
| L1 不降 | `loop` 当场读 | **≥94**（棘轮回写基线，不可事后查文件）|
| MISATTRIBUTED 数下降 | `grep -r` | 单调不升 |
| **无 this 调整错误** | ⚠️ **S2 查不出** | 需人工/语义级校验 |

## 6. 禁止

- ❌ **不可按知识库的链直接写入**（KB 与当前注解冲突，且 KB 自己警告"写入前必须过三条硬裁决"）
- ❌ **不可批量写入**（每类独立裁决 + 验证）
- ❌ **不可仅凭 signature this 修归属**（CLAUDE.md 红线）

## 7. 回退

- `base_class` 改动在 `data/annotations/structs/*.json`（git 跟踪）⇒ **可 git 回退**
- ⚠️ **但 IDB 命名是派生状态** ⇒ 回退注解后需重跑 `apply` 才能恢复 IDB
- ⚠️ **`asm/` 不可回退**（gitignore）⇒ 重新 `export`

---

## 8. 与本轮工作的关系

| 已完成 | 状态 |
|---|---|
| 命名仲裁修复（S2 86→99）| ✅ 已推送 |
| 确定性 + 工具 + 回归保护 | ✅ 已推送 |
| **E2 继承链** | ⏸ **本清单就绪，待执行** |

**下一步**：按本清单从 **4.1 `UIWnd`** 开始（最小改动验证流程），再扩到其他类。
