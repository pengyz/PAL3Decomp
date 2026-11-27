# R4 首查归因：match 棘轮红（L1 189→188，RoleStatePanel `??_G` @0x4A2150 30B LOST）

- 任务：#1 `tsk_01M8BVF13X4X15VVRBAVJE`「R4首查：match 棘轮红归因（RoleStatePanel 0x4A2150 30B LOST）」
- 执行：玄策（mem_coder）　日期：2026-11-26
- 证据台账：`ev_0003`（LOST 归因）、`ev_0004`（0x25B78 类型判定）
- 可复跑取证：`data/status/archive/s4_lost_0x4a2150_repro_20261126.py`
  → 产出 `data/status/archive/s4_lost_0x4a2150_repro_20261126.json`（约 6 秒，只写系统临时目录 + 该 JSON）
- 并行报告（另一张卡同一议题）：`data/status/match_red_attribution_20261126.md`；本报告独立复跑了编译/字节级证据，
  并把「codegen 为什么没补 cast」定位到 `stage5_fixup.py` 的具体判定行（§2.3），二者结论一致（真退化，不重锚）。

---

## 0. 结论

**真退化（管线结果层面），但不是这 30 字节的函数体退化。**

1. R3（`ac9c67673`）把 `RoleStatePanel` 的 `0x25B78` 落位为 `unsigned char[8]` 成员后，语料重渲，`OnMessage` 里出现
   `_DWORD *m_bRtVisible` 局部 + `m_bRtVisible = this->m_bRtVisible;`（裸赋值）。
2. 该行在 MSVC 6.0 下是 C2440（`char [8]` → `unsigned long *`），`pal3/src/Misc/RoleStatePanel.cpp` **整单元编译失败**
   （probe_census：该单元只有这一条 error）。
3. S2 fail ⇒ 无 obj ⇒ 该单元所有符号退出可比域 ⇒ 单元内唯一的 L1 函数 `??_G` 被棘轮记为 **LOST**，
   L1 189→188、paired 行 −17、units −1（另 −2 是 unresolved-synth，见 §1.4）。
4. **只要在赋值处补一次显式转换**，整单元恢复编译，`??_G` 的 30 字节与原 exe 完全一致（重定位 4 字节窗口除外），
   18 条基线行全部回到之前的状态（§1.3、§3.1）。所以「30B 被改坏」不成立，**红是真编译缺陷造成的计量蒸发**。
5. 处置：**保持红、禁止 `--rebaseline`**；修 R3 暴露的 codegen 缺口后按 `apply→export→codegen→probe→match`
   复跑，L1 应自然回到 189。重锚会把真缺陷洗白，不可接受。

---

## 1. ① 30B 原 exe vs 我方编译产物逐字节对照

### 1.1 原 exe（`original/PAL3.exe`，VA 0x4A2150，.text 偏移 0xa1150，共 30 字节）

| off | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 0a | 0b | 0c | 0d | 0e | 0f |
|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
| orig | 56 | 8b | f1 | e8 | **f8** | **02** | **00** | **00** | f6 | 44 | 24 | 08 | 01 | 74 | 09 | 56 |
| ours | 56 | 8b | f1 | e8 | **00** | **00** | **00** | **00** | f6 | 44 | 24 | 08 | 01 | 74 | 09 | 56 |

| off | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 1a | 1b | 1c | 1d | 1e |
|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
| orig | e8 | **ab** | **fb** | **09** | **00** | 83 | c4 | 04 | 8b | c6 | 5e | c2 | 04 | 00 | — |
| ours | e8 | **00** | **00** | **00** | **00** | 83 | c4 | 04 | 8b | c6 | 5e | c2 | 04 | 00 | — |

- **加粗 = 重定位 don't-care 的 4 字节窗口**：`off 4–7`（REL32，`call ??1RoleStatePanel`）与 `off 17–20`
  （REL32，`call ??3@YAXPAX@Z` operator delete）。原 PE **没有 `.reloc` 节**（只有 `.text/.rdata/.data/.rsrc`），
  所以 don't-care 站点取自我方 COFF 的重定位表——这与 `compare_pal3.py` 的比对口径一致。
- 除这两个 4 字节窗口外，**30/30 字节逐一相等**，`compare_bytes` 报 `perfect=True / matches 30 / total 30 / match_pct 100.0`。
- 我方编译产物长度 **32 字节**，末尾 2 字节是 `90 90`（`/Gy` COMDAT 段对齐填充），按 L1 口径先截断到 `size=30` 再比较，
  不影响判定（见 CLAUDE.md「度量盲区」三限定）。

我方完整 32 字节：
`56 8b f1 e8 00 00 00 00 f6 44 24 08 01 74 09 56 e8 00 00 00 00 83 c4 04 8b c6 5e c2 04 00 90 90`

### 1.2 原函数反汇编（`objdump -d --start-address=0x4a2150 --stop-address=0x4a216e`）

```
4a2150: 56              push   %esi
4a2151: 8b f1           mov    %ecx,%esi
4a2153: e8 f8 02 00 00  call   0x4a2450          ; ??1RoleStatePanel@@UAE@XZ
4a2158: f6 44 24 08 01  testb  $0x1,0x8(%esp)
4a215d: 74 09           je     0x4a2168
4a215f: 56              push   %esi
4a2160: e8 ab fb 09 00  call   0x541d10          ; ??3@YAXPAX@Z（operator delete）
4a2165: 83 c4 04        add    $0x4,%esp
4a2168: 8b c6           mov    %esi,%eax
4a216a: 5e              pop    %esi
4a216b: c2 04 00        ret    $0x4
```

**丢失/变化的具体指令序列：无。** 8 条指令逐条一致；所谓「LOST」是整个编译单元消失，不是这 8 条里哪条被改写。

### 1.3 重定位目标核对（不是只跳过 4 字节，目标也一致）

| off | 类型 | 我方 COFF 重定位符号 | 原 exe call 目标 | 目标身份证据 |
|---|---|---|---|---|
| 4 | REL32 | `??1RoleStatePanel@@UAE@XZ` | `0x4A2450` | `data/status/s4_baseline.json` 行：va=0x004a2450 symbol=`??1RoleStatePanel@@UAE@XZ` size=630 |
| 17 | REL32 | `??3@YAXPAX@Z` | `0x541D10` | `data/annotations/skip_functions.json` → `"0x00541d10": {"name":"??3@YAXPAX@Z","reason":"crt_runtime"}`；`data/annotations/CHANGE_LOG.md:6150` 记录同一「testb+call delete+ret$4」教科书形 |

> `gc.compare_bytes` 的 `reloc_target` 字段本轮报 `unresolved=2`，原因是它拿 PAL3.exe 的符号表解析目标，而原 exe 无符号；
> 上表用**地址↔符号身份记录**独立核对了两个目标，结论不受 `unresolved` 影响。

### 1.4 与棘轮读数的账（19:29 `pipeline/_logs/loop_match.log`）

- 基线：`symbols 1259 / matched 1152 / L1 189 / partial 827 / unresolved_synth 136`
  （827+189+136=1152 ✓）
- 本轮：`symbols 1238 / matched 1132 / L1 188 / partial 810 / unresolved_synth 134`
  （810+188+134=1132 ✓）
- 逐单元差分（`data/status/s4_diff_detail.json` vs 存档 `...regressed_20261126T192902.json`）：
  **唯一消失单元 = `pal3/src/Misc/RoleStatePanel.cpp`**（带 17 条 partial 行）；其余 148 个单元 807 行逐行一致。
- 差额闭环：partial −17、L1 −1、unresolved_synth −2 合计 **matched −20**；
  units −1。`symbols` 侧 −21（该单元 COMDAT 函数 22 个，差 1 属配对域外的边角，不影响 L1/matched 账，见 §7）。

---

## 2. ② 变化源定位到具体层

### 2.1 三层链条（每环可复跑）

| 层 | 事实 | 证据 |
|---|---|---|
| 标注层（变化源） | R3 `ac9c67673` 在 `RoleStatePanel.json` 新增 `known_members["0x25b78"]`: `m_bRtVisible` / `unsigned char[8]` / verified | `git log -S"m_bRtVisible" -- data/annotations/structs/RoleStatePanel.json` → 只命中 `ac9c67673`；`git show cf70c0b48:...` 该偏移不存在 |
| 语料层（重渲） | export 重渲 `OnMessage` 语料，Hex-Rays 依据原 asm 的两笔 dword 清零把局部定型为 `_DWORD *m_bRtVisible`，赋值处不写 cast | `asm/pal3/decomp/RoleStatePanel_OnMessageint_uint_int_004a6120.json`（mtime 19:10:04，晚于 apply/export）；`decompiled_c` 片段与 `local_vars` 条目 |
| codegen 层（缺补） | stage5 的 C2440 cast 规则**没有命中**这一形态 ⇒ 生成源第 777 行原样输出裸赋值 | `pipeline/gen/stages/stage5_fixup.py:779-809`、`:812`、`:988-1035`；运行时探针见 §2.3 |
| 编译层（后果） | 该单元 `C2440`，S2 fail，整单元退出比对 | `data/status/probe_census.json`（19:14:46）该单元 errors 仅 1 条：line 777 C2440 |

### 2.2 为什么「必须」是 dword 访问（成员不能改成 uint[2]）

原 `OnMessage` case 1000（VA 0x4A6185）：

```
4a6185: 81 c6 78 5b 02 00  add  $0x25b78,%esi
4a618b: 33 c0              xor  %eax,%eax
4a618d: 89 06              mov  %eax,(%esi)        ; dword 写 4B
4a618f: 89 46 04           mov  %eax,0x4(%esi)     ; dword 写 4B
```

即 8 字节按 **两笔 dword** 清零；而 case 1003（VA 0x4A647E 起）是**逐字节**清零（`movb $0x0,0x25b78(%esi)`、
`0x25b79`…），`Update` 里 `m_bRtVisible[m_nRtIndex]`、`m_nRtIndex` 0..7 也是逐字节判定。
⇒ `unsigned char[8]` 是正确标注；把成员改成 `unsigned long[2]` 会让 case 1003 变 4 字节写（语义/字节退化）。
⇒ 唯一合法修法是在「字节数组 → dword 指针局部」这一次赋值上补显式转换（转换在 x86 上零指令、字节中性）。

### 2.3 codegen 为什么没补（病灶点，运行时探针）

`_fix_c2440_casts` 的 Family 2（`_fix_line_plain_var_assign`）本来就会给「指针局部 = 指针 RHS」补 cast，
但前置判定 `_expr_is_pointer` 依赖 `_path_is_pointer`，而后者对**数组成员**判 False：

```python
# pipeline/gen/stages/stage5_fixup.py:804-809
mt = str(mt).strip()
if '*' in mt:            # ← "unsigned char[8]" 里没有 '*'
    return True
cls = re.sub(r'\s*\[[^\]]*\]\s*$', '', mt)   # 只把 [8] 剥成元素类型
return False             # ← 于是数组被当成"非指针"
```

实测探针（`s4_lost_0x4a2150_repro_20261126.py` step4，可复跑）：

```
_path_is_pointer('this->m_bRtVisible') = False
_expr_is_pointer('this->m_bRtVisible')  = False
_fix_line_plain_var_assign(...) 输出     = '        m_bRtVisible = this->m_bRtVisible;'   # 原样未改
# 反证：同一规则在「成员声明写成指针」时立刻补出正确文本
= '        m_bRtVisible = (_DWORD *)this->m_bRtVisible;'
```

即：**cast 机制本身是好的，缺的是「数组成员在表达式中退化为指针」这一条分类**。
全库当前同形 C2440 只有这 1 处（`probe_census` 19:14:46，按 `cannot convert from 'char [N]' to 'T *'` 统计）。

### 2.4 复现（任何人 6 秒可验）

```bash
cd /home/peng/workspace/PAL3Decomp
python3 data/status/archive/s4_lost_0x4a2150_repro_20261126.py          # 只打印，不写文件
python3 data/status/archive/s4_lost_0x4a2150_repro_20261126.py --write  # 另写 JSON
# 期望：asis errors [(777,'C2440')]；patched errors []；byte_match_30_of_30 true；
#      unit_rows_recovered 18；expectation_met true（不符则 exit 1）
```

脚本做 5 步：①现役源直接编译（应仅 777 C2440）；②只把 777 行改成 `(_DWORD *)this->m_bRtVisible` 再编译（应 0 error）；
③取 `??_G` 机器码与 exe 逐字节对照 + 原函数反汇编；④stage5 判定探针（上节）；⑤把 18 条基线行逐符号重算，
证明「不是字节退化」（下表）。

### 2.5 单元恢复对照（补 cast 后，patched obj 逐符号 vs 原 exe）

| 符号 | 基线 pct | 补 cast 后 pct | 状态 |
|---|---:|---:|---|
| `??_GRoleStatePanel@@UAEPAXI@Z` | 100.0 | **100.0** | match_L1 → match_L1 |
| `??1RoleStatePanel@@UAE@XZ` | 19.8 | 33.8 | partial → partial |
| `?InitUI@...` | 15.1 | 15.7 | partial → partial |
| `?OnMessage@...` | 24.0 | 24.1 | partial → partial |
| 其余 14 条 | 8.1–88.2 | 与基线一致（≤0.6 的舍入/布局差） | partial → partial |

18/18 行全部回到可比域，L1 保住 100%、无一条变差（差异均在 partial 的舍入/布局层面，且 `??1` 反而 +14 点）。

---

## 3. ③ 裁决：真退化（给修复方案与代价）

### 3.1 判定依据

1. 变化方向确定：R3 标注 → 语料重渲 → 生成源出现不可编译行 → 单元 S2 fail → match 排除单元 → L1 189→188。
2. 唯一性：逐单元差分证明唯一消失单元是 `RoleStatePanel.cpp`，行数账严丝合缝（§1.4）。
3. 不是统计噪声：R2 基线时该单元编译通过、`??_G` 是真实配对的 L1（R2 重锚记录在案）。
4. 不是渲染 churn：`s_RoleState.cpp` 两轮都在、均 3 条 partial（交接文档 §5 的「s_RoleState.cpp 内联/重渲」假设**不成立**）。
5. 不是基线错误：`s4_baseline.json` 内容与 HEAD 完全一致（§5），本轮无 `--rebaseline`。

### 3.2 修复选型（代价与风险）

| 方案 | 做法 | 代价 | 风险/评价 |
|---|---|---|---|
| **A（推荐）** | `_path_is_pointer` 把「声明类型是数组」的成员按指针处理（数组成员衰减），现有 `_fix_line_plain_var_assign` 即自动补 `(_DWORD *)`；补一个纯函数单测（仓库 R15 纪律）；跑一次全链 loop | 改 1 个判定 + 1 个单测 ≈ 0.5–1h；全链 `apply→export→codegen→probe→match` ≈ 20–25min（一次） | 影响面已量：全库同形仅 1 处，且只对「指针局部 = 数组成员」插 cast（x86 零指令、字节中性）；仍须以 loop 的 L1 不降为准（管线改动，落前报批） |
| B | L-VAR 引脚 | 需读 `emit_cpp.py::_apply_lvar_overrides` 机制并验证 | **单独不够**：它只改声明行；钉 `_DWORD*` 仍 C2440，钉 `unsigned char*` 会把两笔 dword 清零退化成两笔 byte（字节/语义双退化）。仅在能表达「声明+赋值转换」时才有意义 |
| C | 成员拆 8 个 byte 员 | apply/export + loop 一次 | 破坏 `m_bRtVisible[m_nRtIndex]` 与逐字节判定表达式，`OnMessage/Render` 字节大概率变差；**不建议** |
| D | 成员改 `unsigned int[2]` 或用 union 加 dword 视图 | apply/export + loop 一次 | case 1003 八笔 byte 清零会退化；语义不诚实；**不建议** |

**估算总代价（A）**：≈1–1.5 小时（含全链复跑），不新增 annotation 变更、不改 IDB。

### 3.3 修复后预期（以实况为准，不硬套）

- S2：158/229（该单元从 fail 恢复；若暴露新错误以 probe 实况为准）。
- L1：**≥189**，`RoleStatePanel.cpp` 的 `??_G` 重新出现在 L1 列表（非 partial）。
- partial ≈827、units 149、matched ≈1152（± 边角）。
- 只有全链绿 + probe 零回归，才允许讨论重锚；**本轮不重锚**（重锚会把真缺陷洗白，且会一并掩盖 §7 的 +1 符号边角）。

---

## 4. ④ 证据台账登记

| ev id | 等级/状态 | subject | 一句话 |
|---|---|---|---|
| `ev_0003` | A/open | 0x4A2150 `??_GRoleStatePanel` 30B LOST 归因 | LOST 非函数体退化：R3 标注触发 C2440 → 整单元蒸发；补一次 cast 后 30/30 字节全同、18 行恢复；修复层 = stage5 `_path_is_pointer` 未建模数组衰减；禁止 rebaseline |
| `ev_0004` | A/open | RoleStatePanel 0x25B78 `m_bRtVisible` 类型判定 | 8 字节=两笔 dword 清零 + case 1003 逐字节清零 + `m_nRtIndex` 0..7 ⇒ `unsigned char[8]` 正确，不可改 `uint[2]`；C2440 只能在赋值处 cast |

指针：`ev_0003` → 本报告 + repro 脚本/JSON + `probe_census.json` 该单元 + `OnMessage` 语料 JSON；
`ev_0004` → `data/annotations/structs/RoleStatePanel.json#0x25b78` + `RoleStatePanel.cpp:99-101/485/858-879` + 上述反汇编。

---

## 5. ⑤ 未重锚、未写基线（可核）

```text
$ sha256sum data/status/s4_baseline.json
f3aa8279df6d0440dd9e28b85366ad935755415b6f7cf93b8d151c78f659d372  data/status/s4_baseline.json
$ git show HEAD:data/status/s4_baseline.json | sha256sum
f3aa8279df6d0440dd9e28b85366ad935755415b6f7cf93b8d151c78f659d372  -
$ git diff --quiet -- data/status/s4_baseline.json ; echo diff_exit=$?
diff_exit=0
```

- `s4_baseline.json` / `s4_diff_detail.json` mtime 19:29 是棘轮把「基线+明细对」恢复成上一轮造成的，内容与 HEAD 一致；
  `rebaseline` 字段仍是 R2 的记录（`prev/cur=189`）。
- 本卡只新增：本报告、repro `.py`/`.json`、台账 `evidence_ledger.json` 两条 add（台账不是基线文件）。
- 未执行 `pipeline/cli.py match --rebaseline`，未跑 apply/export/codegen/probe 写任何 status 基线。

---

## 6. 验收对照（QA checklist）

| QA 项 | 本报告落点 |
|---|---|
| 30B 有原 exe vs 编译产物逐字节对照，重定位 4 字节已标注 | §1.1（表 + 加粗窗口）、§1.3（目标身份） |
| 变化源定位到具体层并附可复现证据（commit/语料/编译日志） | §2.1 表 + §2.3 探针 + §2.4 脚本（6s 可跑）；commit=`ac9c67673` |
| 结论真退化/假退化二选一（假退化给 rebaseline 依据链） | §3 选**真退化**，给 4 个修复方案与代价 + 修后预期；并说明为何重锚不可接受 |
| 结论已登记证据台账并带 ev id | §4（`ev_0003` / `ev_0004`） |
| 未执行 rebaseline、未写任何基线文件 | §5（sha 相等 + `git diff` 干净） |

---

## 7. 局限与未做（诚实边界）

- **没有为本卡跑完整 loop**（约 20–25 分钟）：结论依据同一次 loop 的 `probe_census.json`（19:14:46）与
  `loop_match.log`/存档（19:29），并用 repro 脚本在约 6 秒内独立复现编译与字节对照；全链修后验收留给修复卡。
- **`symbols` 侧 −21 vs 该单元 22 个 COMDAT 函数的 −22** 差 1，属配对域外边角（matched 账已在 §1.4 用
  17+1+2 精确闭合）；未逐符号定位那 +1 个符号来自哪个单元，需 scope 化 match 复跑才能钉死（不在本卡范围）。
- **A 方案是管线改动**（stage5 判定 + 单测），按仓库纪律需报批后再落地；本卡未改任何生产代码。
- 本卡未改 annotation；`ac9c67673` 的 `unsigned char[8]` 落位本身是正确的（§2.2），不需要回退标注。
