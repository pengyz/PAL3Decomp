# 管线病灶映射表 v1（指标 → 病灶 → 管线落点）

> 2026-10-31 · 「指标→管线」反推仪器的沉淀面。机器聚类（tools/diff_byteform_cluster.py），
> 判因每簇一次（病灶三问），条目带证据与验证面；未判簇挂"待裁"（不准确=不判定）。
> 数据源：s4_diff_detail（690 partial）· len-delta 桶 246 先行。

## A. EH 状态机摊平（判因 3/3 坐实）

| 项 | 内容 |
|---|---|
| **指标症状** | len-delta shorter + orig 序言 SEH 形（`6A FF 68` / FPO-SEH `64 A1 … 6A FF 68`） |
| **簇规模** | 83 件（首字节形 70 + 深位变体 12）＝ len-delta 桶 33% |
| **判因证据** | 3/3 抽样（CCBAIWindow::Reset/Destroy/OnMessage）：decomp 含 `ebp-4h` SEH 状态变量 + `v6=0/-1` 跃迁 + `_CxxThrowException`；我方生成体**原样搬摊平形**（v6 当普通 int、裸 _CxxThrowException）⇒ 编译器看不到 try ⇒ 不发 SEH 序言；decomp 语料 123 件含异常构形 |
| **判因实验** | E 形（离线 ctor `new T(...)`）→ SEH 序言 `6A FF 68` ✓ HIT（与原版 `0x51CCE0` 同形）；A/B/C/F 形 ✗；D 形（`try { } catch`）✓ |
| **管线病灶** | codegen 层：Hex-Rays EH 状态机摊平形未还原为 C++ `new` 表达式/`try` 块 |
| **落点** | `stage5_fixup._rewrite_new_expression`（已实施）：`ptr=(T*)operator new(N); [state;] if(ptr) ptr->T::Method(); else r=0; [state;]` → `ptr=new T(); r=(int)ptr;` |
| **命中率** | **15/83 = 18%**（正则扩面三连修：Method 形/多层括号/结果 cast）；有模式仍漏 7（异形：`operator new` 在 if 条件内/复杂流）；**61 件无 new 模式**（构造链/try-catch 形，需不同修法） |
| **验证面** | 修复后 15 件 SEH 序言回归（字节形）；L1 增量当场读 |
| **状态** | 已判因·部分实施（15 件已修；61 件构造链形待 try/catch 还原修法） |

## B. 帧指针形缺失（部分判因——/Oy- 复现实证）

| 项 | 内容 |
|---|---|
| **指标症状** | orig `55 8B EC`（EBP 序言、无 SEH 标记）vs 我方 FPO 形；opcode 对 `55→83` |
| **簇规模** | 13 件（len-delta 内 EBP 无 SEH；跨 partial 面待扫） |
| **判因证据** | flag 对照实验：`/Oy-` 显式禁 FPO 后 **DemandChecker 前 8 字节 8/8 全同**、HandleEnemyAction 7/8（帧尺寸 0x10 vs 0x38 局部布局差）；`/Oy` 有无无效（/O2 隐含 /Oy）——原版为**逐函数混合 FPO**（同 TU 内 CCBAI::GetTargetRole=FPO 形、HandleEnemyAction=EBP 形） |
| **管线病灶** | 帧指针控制面：我方全局 /Oy，原版对特定函数禁 FPO。**触发特性未定谳**（样本无 alloca/EH/asm/setjmp 显性标记——MSVC6 逐函数禁 FPO 触发条件待考古，13 件样本池） |
| **落点（候选）** | codegen 对该簇函数发 `#pragma optimize("y",off)`（per-function 字节证据锚定）；或源特性还原使编译器自动禁 FPO（待触发特性定谳后二选一） |
| **验证面** | /Oy- 复现前缀同已实证（DemandChecker 8/8）；全局 flag 翻转会破 L1 161 件（对照已知） |
| **状态** | 部分判因（触发特性待考古；per-function 修法有字节证据） |

## C. 其它序言形态差（待裁）

| 项 | 内容 |
|---|---|
| **指标症状** | 首差点位序言区、opcode 对 `6a→56/81/51` 等（寄存器保存序/立即数形） |
| **簇规模** | 151 件（len-delta 桶内剔除 A/B 后）+ dense-scattered 317 件（另桶） |
| **状态** | 待裁（下一步：同法二特征分解 + 抽样） |

## 仪器规则（本表的使用与进化）

1. 聚类（机器）→ 判因（每簇一次抽样+病灶三问）→ 入表 → 同簇自动路由；
2. 簇内同质性由抽样复核（<60% 同因 ⇒ 拆簇/降级待裁）；
3. 误分类代价 = 白试一轮（读数验证门兜底）；
4. 未命中桶 = 新发现（low 置信入表，人工判因后升级）。
