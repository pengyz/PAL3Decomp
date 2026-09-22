---
name: annotation-audit
description: "PAL3 annotation 的**布局/类型/名字/归属**修正审计工作流 —— DAG 序扫描、三形态访问证据、vtable/ctor 决定性证据、**四道基线门**、留痕与回滚纪律；含本仓已验证的盲区与反模式清单"
tags: [reverse-engineering, pal3, annotations, audit, baseline]
when_to_use: "当要修改 annotation 的偏移/类型/成员名/函数归属，或要对某类/某成员下'无冲突/无证据'的结论，或要批量修正布局与语义时加载"
rejects: "只是要跑管线 CLI/判证据等级/CRT 边界 → pal3-pipeline；只是要查 annotation JSON 字段格式与校验规则 → annotation-guide；只是要修 codegen 产出的 C++ 模式 → pal3-pipeline 的 codegen 章节"
---

## 与其它 skill 的边界

| 场景 | 用哪个 |
|---|---|
| **审计**：布局/类型/名字/归属是否与二进制一致；改前的证据与改后的四道门 | **本 skill** |
| 跑管线（apply/export/codegen/probe/match/loop）、证据等级表、CRT/模板/全局变量领域知识 | `pal3-pipeline` |
| `structs/*.json`、`functions.json`、`globals.json` 的**字段格式与校验规则** | `annotation-guide`（schema 唯一权威） |

---

# annotation 审计工作流

## 0. 一句话原则

**二进制是唯一 SoT；annotation 是假设。** 每个结论都必须有**证据指针**（VA:指令 / 模式命中）；
**未观测 ≠ 不存在**；**名字 ≠ 证据**；冲突**只报警、人工介入**，不自动改 ✓

## 0b. **来源登记表**（每个"真值断言"必须注明用的是哪个 oracle ✗ 不许混用）

| 等级 | 来源 | 独立性 | 能证明/不能证明 | 工具 |
|---|---|---|---|---|
| **O1** | **原始 `original/PAL3.exe` 字节** | **完全独立** ✓✓ | 编译产物是否与原字节相同（最终裁决 ✓）| `pipeline/compare_pal3.py`（`match`）|
| **O2** | **纯反汇编**（`objdump`，**IDB-无关** ✓）| 独立于注解与 IDB ✓ | `[reg+disp32]` / **绝对地址**访问是否成立 | `tools/bin_oracle.py` ✓（取代 MCP 字节路径）|
| **O3** | **编译器 MSVC6** | 与注解无关 ✓ | 发射出的 C++ **实际**布局/尺寸 | `audit_type_layout` · `verify_fix` |
| **O4** | IDB 导出物 / Hex-Rays 语料 | **混合** ⚠️ | vtable/继承/函数边界 = IDA 分析 ✓；**结构体偏移 = 注解的回声** ✗；**语料 = 注解版 IDB 的输出** ✗ | `audit_attribution_evidence`（vtable 部分 ✓）· 语义工具的 corpus 分支（**仅线索** ✗）|

**规则**：
1. **禁止把 O4 的"注解回声"当独立证据** ✗（结构体偏移一律以 O1/O2/O3 为准 ✓）
2. **MCP/IDB 没有问题，且不可替代** ✓ —— 它提供 objdump 给不了的 **IDA 分析**（类型重建 · vtable/UDT 语义 · **xref** ·
   函数边界 · 反编译 · 名字恢复），且其反汇编**知道哪些是数据**（我的 O2 是**线性扫描**，`.text` 夹数据时会误解码 ✗）
   ⇒ **按问题选通道**：
   * 「原始字节/偏移是否成立」⇒ **O2 与 MCP 都跑并交叉验证** ✓✓（实测二者对同一模式给出**完全相同**的命中 ✓）
   * 「类型/vtable 语义/xref/反编译/归属证据」⇒ **必须 MCP** ✓
   * 「发射层布局/尺寸」⇒ **必须编译器**（MCP 也答不了 ✓）
   * **独立性/不占用 IDB** 的场合（要并行跑 `apply`/`export` 时）优先 O2 ✓；**确认质量**优先 MCP ✓
   ⚠️ 唯一要避免的是**用 IDB 的结构体偏移去验证注解**（那是注解的回声 ✗）—— 这是**独立性问题**，不是 MCP 的问题 ✓
3. 工具输出必须带**来源等级标注**（如 `[O2 独立]` / `O4 语料·非独立` 占位符）✓

## 1. 四个维度与**可证性**（不要越界承诺）

| 维度 | 可证到什么 | 工具 |
|---|---|---|
| **布局**（成员偏移）| **完全可判定** ✓（编译器裁判）| `tools/audit_type_layout.py` |
| **类型** | 宽度 + int/float/指针 + 有/无符号 ✓；**精确源码类型不可证** ✗ | `tools/audit_member_semantics.py` |
| **成员名** | 仅当**语义把手**存在（字符串/RTTI/API 实参/mangled）✓；否则**保留 `_todo_`** ✗ | 同上 |
| **函数归属** | **vtable 槽位 / ctor vptr 可证** ✓；成员集合唯一相容性**实验性、不得据以决策** ✗ | `tools/audit_attribution_evidence.py`（可证）；`tools/audit_attribution.py`（**仅线索**）|

> ⚠️ **不要再用 `tools/audit_layout.py` 作为布局判据**：它比的是「注解 vs `ida_structs.json`」，
> 而后者正是注解自己写进 IDB 再导出的 ⇒ **同源比较、恒等、无判别力** ✗（其 docstring 自认）

## 2. 标准流程（DAG 序）

1. **取类**：按 **DAG 序**（按值成员依赖，**基础类型先**；指针/数组不构成依赖）✓
2. **布局审计**：`python3 tools/audit_type_layout.py --only <Cls>` ⇒ `offsetof(Cls,m) == 注解偏移` 全等？
3. **语义/类型证据**：三形态都要查（**缺一不可**）
   - ① `this`/指针：该偏移的 **disp32** 扫描
   - ② **全局对象**：枚举 `data/annotations/globals.json` 里 `type == Cls` 的对象地址 `G`，扫 **`G+off`**
   - ③ **语料名字**：全 decomp 语料按**成员名**搜索
   ⇒ **否定结论必须来自"权威批量原始扫描"**（一次调用多模式，实测 12 模式 0.06s ✓）
4. **归属证据**：`tools/audit_attribution_evidence.py`（vtable 槽位 + 祖先关系 + ctor vptr）
5. **出具证据表 ⇒ 人工确认**（工具**只报警**）✓
6. **一类一批改动**（等值优先：**尺寸不变 ⇒ 布局不变** ✓）
7. **出证物报告** `python3 tools/verify_fix.py --class <Cls>`（成员偏移 + **sizeof** + 传递依赖 + 端到端字节 + 基线）
8. **过四道门**（见 §3）⇒ 通过才提交
8. **留痕**：`data/annotations/CHANGE_LOG.md` 记**逐成员证据 + 盲区披露** ✓
9. **提交**：annotation 变更必须含 `Evidence:` 与 `Confidence:`（**pre-commit hook 强制** ✓）

## 3. 四道基线门（**缺一不可**）

| 门 | 命令 / 判据 | 为什么 |
|---|---|---|
| ① 布局等价 | 改动后 `audit_type_layout.py --only <Cls>` 全等 | 防止"改类型把布局带偏" |
| ② **编译错误** | `python3 pipeline/cli.py loop --expect-s2 75/205 --expect-errors 2150 --expect-l1 36` 的 **errors 不得增** | **实测抓到过假阴性**：撤类型后 `PAL3.cpp:2725 C2440`（+1）⇒ 该成员其实被使用 ✗ |
| ③ **L1 棘轮** | 同上，**`l1` 不得降** | 字节匹配是最终目标 ✓ |
| ④ **证据自校验** | 否定结论来自**权威批量原始扫描**（§2 步骤3）；"**未确认 ≠ 不存在**" | **实测：编译门 ✓ 但 5 个里撤错 2 个** ✗（`m_nTodo_C660/C848` 的全局形态有命中）|
| ⑤ **证物** | `tools/verify_fix.py --class <Cls>`：成员偏移 + **`sizeof`==`binary_size`** + **传递**依赖闭包 + 端到端字节 + 与 **HEAD** 基线比较 + **残余未知披露** | 只查成员偏移不够 ✗（`UIListBox` 的 +12 是**尺寸**问题）；探针**上界给足**，命中上界必须判 `unknown` ✗ |

补充：
- **C1003 例外**：3 个截断单元（`Combat/CCBStage.cpp`、`Combat/CCBUI.cpp`、`free_functions.cpp`）错误计数不可靠 ⇒
  改看「**同族新增错误**」+「截断行号是否前进」✓
- **回滚**：`git show HEAD:<path> > <path>`（仓规禁 `checkout/restore/stash/clean -fd`）✓

## 4. 已知盲区（必须披露，不得据此断言"无证据" ✗）

1. **批量拷贝/序列化**：`memcpy/memset` 覆盖的区间看不见 ⇒ 序列化/存档类字段常落此列 ✓
2. **全局对象访问**：`g_X.member` 编译成**绝对地址** `[g_X+off]` ⇒ 偏移**不作为独立 disp32 出现** ✓
   且 **IDA 把绝对地址渲染成符号名**（`dword_C057B4`）⇒ 只匹配 `0x...` 的确认逻辑**必然失配** ✓
3. **内联（/Ob2）**：IDB 里有 `_inline_*` 类型 ⇒ 一个函数体内**合法含别的类**的成员访问 ⇒
   naive"成员集合唯一相容"结论**可能按构造就错** ✗（实测 `SceneMgr::Create` 被判"唯一相容 CEffMgr" ✗）
4. **PDB 名**：来自 PAL3A，**偏移可能不同** ⇒ 只能作参考、不能单独作证据 ✓
   （实测 `??_GSceneMgr@0x4cd930` 是误名：该函数在 `[this+0]` 存 vtable 且访问 `[this+0x1C]`，与真 SceneMgr 布局不符 ✗）
5. **`bases` 是 dict 列表**（`[{'name':'UIWnd','offset':0}]`）⇒ 解析 ancestry 时必须兼容此形状 ✓
6. **模板实例类**（`CTaskTpl_<...>`）头无法独立编译 ⇒ 布局审计会报"测量不可信"（工具限制 ✓）

## 5. 反模式（写下来防复发）

- 只查 `this` 形态（不看全局对象形态）就断言"无证据" ✗
- 把"**有命中但指令未确认**"当作"无证据" ✗
- 用反汇编**文本**匹配绝对地址（IDA 用符号名）✗
- 在**证据方法不完整**时批量改注解 ✗
- 用 `tools/audit_layout.py` 作布局判据（同源比较 ✗）
- 在**截断单元**上用错误计数判退化 ✗
- 拿 **signature 里的 `this`** 或 **PDB 名**当归属证据 ✗（仓规明令）
- 未过**四道门**就提交 annotation 变更 ✗

## 5b. 进度双轴（别用 L1 单项评判结构工作 ✗）

| 轴 | 指标 | 现状（2026-09-22）|
|---|---|---|
| **先行（结构）** | 布局一致类数 · **被阻塞函数数** | 91 冲突类→86（已修 5）· 阻塞 1501→**1361** 函数 |
| **滞后（字节）** | `L1` · `partial` | 36 · 197 |
| **转化率** | **P(该单元 S2 绿)** | 本批 2/140 ≈ **1.4%** ⇒ **冻结积压** ✗ |

⇒ 布局错 = **硬上限**（编译位移与二进制不同 ⇒ 任何函数级修补都无法匹配 ✗）
⇒ **优先修"单元已绿"的类**（立即兑现）；并把"把已修好的单元弄绿"作为并行的兑现工作 ✓

## 6. 当前基线（改前先确认，改后必须复验）

```
S2 75/205 · 总错误 2150 · matched 265/319 · L1 36 · partial 197
全量布局审计（2026-09-22）：766 类中 ✓一致 355 · ✗冲突 91 · 不可信 22
归属证据对账：consistent 381 · contradiction（可证告警）38 · 无 vtable 证据 2977
```
命令：`python3 pipeline/cli.py status`（秒级只读）→ `loop --expect-...`（全链路断言）✓