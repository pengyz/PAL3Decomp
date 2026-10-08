# 完善修复方案 v3（经 kiro + codex 交叉对抗复核）

**日期**：2026-10-08
**状态**：v3 · **我的 v2 修复提议已被告破**（两位复核者独立、交叉一致）
**依据**：kiro（代码级分支+安全性）+ codex（证据链+政策+回归风险）

---

## 0. 两位复核者的**交集结论**（交叉确认，可信度最高）

| # | 结论 | kiro | codex |
|---|---|---|---|
| 1 | 我提议的 **codegen 出口合法化修复不成立** | ✅ | ✅ |
| 2 | **真实属主是 `UIWnd`**（不是 `CGameData`）| ✅（注解 `from` 字段）| ✅（**二进制**：`ret 0xc` + UIWnd 三表槽6 + 调用点 `E8`+`%ecx`）|
| 3 | 09-17 的合法化**不覆盖**当前输入（是第三条分支）| ✅ | ✅（含 `transform_oop_calls` 实测复现）|
| 4 | 09-20 决议**不是**当前有效政策 | ✅ | ✅（`_longterm_plan.md:150` 明确纠偏）|
| 5 | 正确修法是 **修命名/注解仲裁层**，不是改 codegen 出口 | ✅ | ✅ |
| 6 | 需 **确定性属主仲裁 + 冲突审计器** 防复发 | ✅ | ✅（方案 e）|

---

## 1. 被证伪的 v2 主张（诚实记录）

| # | v2 主张 | 判决 | 证据 |
|---|---|---|---|
| 1 | 「09-20 决议可直接套用」| ❌ **证伪** | 该决议针对 **`stage3_cleanup.py`** 的 `obj->__vftable->N(...)` 裸链改写，**不是** `ast_transform.py` 的 `Cls::M(this,…)` 静态形；决议原文自写"落地位置：stage3_cleanup.py" |
| 2 | 「`0x00445D10` 已被 `CGameData` 拥有」| ❌ **证伪** | `CGameData.json` 自己的 vtable 条目标 **`"from": "UIWnd"`**；`UIWnd.json` 三表槽6 标 **`from: null`**（自认原创）；**14/15 类标 `from:UIWnd`，0 类标 `from:CGameData`** |
| 3 | 「`75f3b8760` 改的是 `identifier` 分支」| ❌ **证伪** | 实测 diff：改的是 **`cast_expression` + `inner=='this'`** 分支在 **Track-1 门禁不成立**时的 fallback（`ast_transform.py:1501/1608`）—— **第三条分支** |
| 4 | 「`apply_annotations.py` 不写函数名」| ❌ **证伪** | `:11` 明写 "functions — **set_name** + SetType"；`:2037` = `ida_name.set_name(addr, _mangled, …)` |
| 5 | 「按注解 `from` 推 Owner ⇒ 得到 `CGameData`」| ❌ **自我矛盾** | 按该算法机械推导得 **`UIWnd`**，与我方案假设的 `CGameData` 冲突 |
| 6 | 「站点数 44/41」| ⚠️ **不精确** | `MISATTRIBUTED` 全 marker = 44 文件；`CGameData::OnMessage` cluster = **29 文件 / 41 站点**；`CCBItemWindow::Create` cluster = **22 站点** |
| 7 | 「`0x00445D10` 被 15 个类**声明**」| ⚠️ **需精确** | 15 个类的 **vtable 继承槽**引用它；**`methods` 直接声明同址的只有 3 类**：`UIWnd`、`PalScript`、`CGameData` |
| 8 | 「21/23 退化全由该 cluster 造成」| ❌ **不成立** | 首错分布：`C2660` **8** 个 + `C2661` **5** 个 = **13/21**；**其余 8 个是别的错误** |

---

## 2. 修正后的根因（两位复核者交集）

### 2.1 病灶层：**命名仲裁**（`apply_annotations.py`）
```
data/annotations/structs/*.json 的 methods 里，同一地址 0x00445D10 被 3 个类声明
  ⇒ load_annotations() 合并（apply_annotations.py:1331）
  ⇒ 同一地址「首个合并者胜出」⇒ 实测胜出者 = CGameData
  ⇒ IDB 名 = CGameData::OnMessage（apply_annotations.py:1996/:2037 set_name 写入）
  ⇒ export 导出该名（decomp: name=CGameData::OnMessage 但 signature=(UIWnd *this) ← 自相矛盾）
  ⇒ ast_transform.py:1419 的 first_arg.type=='this' 分支看到 class_name=CGameData
     既非 cls_name（CCBResultWindow）也非其基类 ⇒ 落 else ⇒ 命中 :1466 broken 形
  ⇒ C2660/C2661
```

### 2.2 **二进制证据**（codex，决定性）
```
objdump -D -M intel --start-address=0x445d10 --stop-address=0x445d20 original/PAL3.exe
 445d10:  31 c0        xor eax,eax
 445d12:  c2 0c 00     ret 0xc        ← 3 个栈参数，符合三参 __thiscall
```
- `UIWnd` 三张表 `0x56AE2C/0x56AEC8/0x56AFB0` 槽6 均为 `0x445D10`
- `CGameData` 表 `0x56B094` 同槽标 `from:"UIWnd"`
- 调用点大量为**直接 `E8 sub_445D10` + `%ecx=this`** ⇒ 派生类 override 显式调基类默认实现

⇒ **`0x00445D10` 的真实属主 = `UIWnd`**（`name` 字段是"全局唯一标签被重复注解污染"的产物）

### 2.3 同机制第二簇
`0x00445B90 = UIWnd::Create` —— 被 `CCBItemWindow`/`PalScript` 等重复声明 ⇒ `MISATTRIBUTED] CCBItemWindow::Create` **22 站点**
（codex 实测：把名字改成 `UIWnd::Create` 后**现有转换直接合法**：`this->UIWnd::Create(id, &pRect, parent)`）

---

## 3. 修复方案

### 3.1 核心原则
> **只修命名层，不改 `[MISATTRIBUTED]` 出口。**
> 名字修正为已证实的基类属主（`UIWnd`）后，`class_name` 变成 `cls_name` 的**基类** ⇒ **走 `ast_transform.py:1443` 的合法分支** ⇒ 自动发射 `this->UIWnd::OnMessage(...)` ⇒ **无需任何 codegen 改动**。

### 3.2 步骤

| 步骤 | 动作 | 副作用 | 判据 |
|---|---|---|---|
| **S1（只读审计）** | 枚举**同地址多 `methods` 声明**，按"vtable `from:null` 的根表槽"判定定义者 | 无 | 产出冲突清单（预期含 `0x00445D10`、`0x00445B90` 等）|
| **S2（修命名）** | 对本例至少处理 **`0x00445D10`** 与 **`0x00445B90`**：**保留 `UIWnd` 的方法声明，移除派生/污染类的重复 `methods` 条目**（vtable 继承槽 `from:UIWnd` 的记录**保留**——那是合法的继承记录）| **中**（改 `data/annotations/structs/*.json`）| 该地址的 `methods` 声明**唯一**；`apply` 后 IDB 名为 `UIWnd::OnMessage` |
| **S3（冲突审计器）** | 新增**只读**审计工具：枚举同址多声明 + 按 vtable 根属主**确定性仲裁**，纳入门禁 | 低 | 报告"同址多声明"为 0（或全部有据）|
| **S4（全链验证）** | `loop`（**无 timeout**）| 无（产物可再生）| **S2 ≥108** · **L1 ≥94** · new failures=0 · 两簇 marker=0 · 总错误 ≤1515 |
| **S5（基线刷新）** | 仅 S4 通过后 | **高** | — |

### 3.3 ⚠️ **L1 硬约束**（codex 实测，真实风险）
`UIMap::OnMessage`、`UILoadingFrm::OnMessage`、`CCBFiveNimbusWindow::OnMessage` **本身就是 `match_L1`**，且函数体含该 marker。

⇒ **必须保留限定直呼 `this->UIWnd::OnMessage(...)`**（编译为直接 `E8`）；
**绝不可**改成非限定虚调用 `this->OnMessage(...)`（会引入 `call [vtable+N]` ⇒ **直接破 L1**）。
`tests/test_vtable_call_transform.py:496` 已钉死"虚调用不得发射限定形"——**本修复不触碰该契约**（我们走的是**基类直呼**分支，非虚派发）。

---

## 4. 被否决的替代方案（含理由）

| 方案 | 判决 | 理由 |
|---|---|---|
| **改 `own-this` 出口为合法 cast 形**（我的 v2）| ❌ **否决** | ① 广义合法化会把 **120 个重复方法地址**中的**真实误归属**洗白；② **真实反例**：`CCBResultWindow`（继承 `UIFrameWnd`→`UIWnd`）与 `CGameData`（**无基类**）无继承关系 ⇒ `(CGameData*)this` 是**类型谎言被 C 风格 cast 放行** ⇒ 把编译期错误转为**潜伏的布局解释错误、无检测手段**；③ 门禁与 bug **共享同一脆弱数据源**，无法自证安全 |
| **转 stub** | ❌ 不推荐 | 引入合成调用层，破坏直呼 `E8`/L1 概率高 |
| **`C2660` 入已知红色清单** | ⚠️ 仅诊断用 | 掩盖不可编译产物，使 S2 失去意义 |
| **`((Owner*)RECV)->Owner::N(...)`（09-20 旧案）** | ❌ **已被项目自己纠偏** | `_longterm_plan.md:150`："Owner=CGameData 会让调用改走 CGameData 的 vtable 槽位" |
| **（推荐）修命名仲裁 + 冲突审计器** | ✅ | 根治两簇；下游自动受益；无需碰 codegen |

---

## 5. 未解与残留（诚实标注）

| # | 项 | 状态 |
|---|---|---|
| 1 | **8/21 退化单元不是这两簇造成的** | ⚠️ **待单独归因**（首错是别的错误码）|
| 2 | **为何 10-06 基线无此失败** | ⚠️ **部分可判定**：10-06 的 `ida_functions.json` **已有** `CGameData_OnMessage…` ⇒ **不是"注解名不同"**；但当时的 decomp/生成态**不可复原**（`pal3/src`/`asm` 均 gitignored）⇒ 差异大概率在 **IDB 局部类型/decomp 形态/生成态**，**精确原因缺少可复原产物** |
| 3 | **当前 artifact 口径** | codex 实测 census = `total 210 / ok 88 / errors 2054`（**B 组状态**）；我此前写"86"是 A 组 ⇒ 引用时须注明组别 |
| 4 | **Task 7 的 2 单元** | 待单独定位（A/B 差集）|
| 5 | **`/GR`、T3、T2、T4** | v2 待办仍在队列 |

---

## 6. 管线防复发（F1-F4，来自前轮 kiro 复核）

| # | 问题 | 建议 |
|---|---|---|
| **F1** | `cmd_loop` **静默吞未知参数**（`--help` 落入正常路径启动全链路）| 未知 token ⇒ 提示 + `sys.exit(2)` |
| **F2** | `export` 无**完整性自检** | 比对 decomp 最大地址 vs `TEXT_END(0x5695D0)`；差距 >10% ⇒ 退出 1 |
| **F3** | 外部 `timeout` 破坏性 | 文档明确"**loop 不可加外部 timeout**"；export 需 ≥300s |
| **F4** | 无进度心跳 | 阶段开始先写 `IN_PROGRESS` 标记 |
| **F5（新）** | **命名仲裁不确定**（"首个合并者胜出"）| `load_annotations()` 改为**确定性属主仲裁**（vtable `from:null` 根表槽判定定义者），并对同址多声明**报错/告警** |

---

## 7. 可机械执行的下一步

```bash
# 1) 只读审计：枚举同址多 methods 声明（预期含 0x00445D10 / 0x00445B90）
python3 - <<'PY'
import json,glob,collections
m=collections.defaultdict(list)
for f in glob.glob('data/annotations/structs/*.json'):
    d=json.load(open(f))
    for a,mm in (d.get('methods') or {}).items():
        if isinstance(mm,dict): m[a.lower()].append((d.get('name'),mm.get('name')))
dup={a:v for a,v in m.items() if len(v)>1}
print('同址多声明:', len(dup))
for a,v in sorted(dup.items())[:10]: print(' ',a,v)
PY

# 2) 按 vtable from:null 根表槽判定定义者（对 0x00445D10 / 0x00445B90）
# 3) 修注解（移除污染类的重复 methods 条目，保留 vtable 继承记录）
# 4) python3 pipeline/cli.py loop     # 不加任何 timeout！
# 5) 验收：S2 ≥108 · L1 ≥94 · new failures=0 · marker=0 · errors ≤1515
```

**验收总表**：`MISATTRIBUTED] CGameData::OnMessage` 41→**0** · `MISATTRIBUTED] CCBItemWindow::Create` 22→**0** · S2 ≥**108** · L1 ≥**94** · 总错误 ≤**1515** · `git status` 干净