# type_evidence v3 设计稿：T1 + T1b 双信号合并（2026-09-27 草案 / 2026-09-28 复核 1239c52d【有条件通过】修订版）

> **复核修订（8 项已并入，修订处标 [1239c52d]）**：状态机硬化（regs_write+别名归一+仅
> __thiscall 非 static 播种+index 排除+负 disp 拒）· 期望管理改数（≤26→**≤11**）·
> 解码率分母钉死 · premeasure 标 superseded · 输入面钉死 · emit_batch 双站点证据 ·
> R4-R7 新风险 · cmp/test 升冲突**未入档不生效**（现行=触碰类）。

## 1. 为什么（goal B"工具化"的完成态）
- 信号地图（_b_batch_premeasure §探针）裁定：**数据类 T1 主导、方法类 T1b 主导，
  最终工具必须双信号合并**。v2（T1-only）在方法型类上系统性盲：RoleSystem/CScreenMode/
  Actor 等成员访问是 this+disp32 形态，不出成员绝对地址。
- 解锁量化（_b_t1b_unlock_premeasure）：7 个方法型类 W=198 中 167 个有 T1b 上界信号；
  预演 19 A 可填充 + 107 WIDTH-4-MATCHED 升级 + 13 冲突待裁。
- 适用面扩展到 C 批：CEffMgr in-blob 成员同样走 this+disp 形态（28 方法 46 偏移实测）。

## 2. 信号定义与实现（v3 增量，v2 全部保留）
### T1b：this-relative disp32 census（方法函数体内）[1239c52d 硬化]
1. **函数界定**：decomp JSON `address`/`size_bytes`（load_func_ranges 现成）。口径：
   **仅方法体语料**（457/459 方法在 decomp 内=99.6%；勿与全语料 .text 79.6% 混用）；
   thunk/导入尾不在面内（W1 G3/G4 教训同源）。
2. **this 数据流跟踪用 capstone 实现**（不继承 access_map 正则版——其写失效只匹配
   `reg,reg` 尾形态，pop/inc/neg/部分寄存器写全漏=假阳路径）：
   - **仅对 signature 含 __thiscall 且非 static 的方法播种 ECX=this+0**（459 方法中 17 个
     非 thiscall——naive 播种实测 17 污染站点）；
   - 写失效按 **regs_write（含隐式写）+ 寄存器别名归一**（AL/AX/EAX 同族）；
   - call 后 EAX/ECX/EDX 失效；pop/inc/dec/neg/not/单操作数 imul/mul/div/cdq/setcc/
     部分寄存器写一律失效；
   - `mov ecx,reg`/`lea ecx,[reg+N]` 复制传播（W1 `_resolve_this_def` 同语义可复用）；
   - 栈参 this 与 EBP 槽恢复 = v3.1（实测填充增量 0）。
3. **载体收形**：仅 `op.mem.index == 0` 的 X(%reg)（index 形态实测 57 站点/1 W 槽误归属）；
   **负 disp 一律不入**（7 类实测 0，MI/C 批保持防线）；0≤disp<size 过滤只作提示
   （binary_size 不可当过滤器——PAL3 91024→4936 实证 18 倍虚高），越界命中单独成表。
4. 复用面（勘误）：exe_text_image/load_func_ranges/单遍反汇编骨架 + classify_insn ✓；
   **build_xref_index 不可复用**（只收绝对地址 base==0&&index==0）；
   "build_boundaries 现成"核实成立（type_evidence.py:166）。两遍合一切口=T1b 挂进
   build_boundaries 同一次逐函数线性反汇编（per-function 状态复位）。
5. **输入面钉死**（P1-e）：方法→函数映射 = data/annotations/structs/*.json `methods`
   （与 ida_structs 同数 163/31/89，含 __thiscall/static 标志）；报告 _meta 记输入 md5。
### 合并分级（propose v3）
- 同 (cls,off) 槽合并 T1 refs + T1b refs 一起过**现行分级规则**（D4 浮点证据优先、
  触碰/运算拆分、多宽度冲突、double 禁填、WIDTH-4-MATCHED 标签全部不动）；
  **cmp/test 归触碰类不变**（"带立即数升冲突"系 ff86c62f 建议、全仓无裁定出处，
  按 P1-e 不入规则——如需采用须先入档）；
- **来源标注**：notes 增 `T1:%d T1b:%d`（不投票、只溯源）；
  **跨源宽度不一致独立标签 `cross-source-width`**（[1239c52d] 与真多宽度冲突分装——
  它同时是 T1b 假阳/方法误归属的警报器，strict 实测仅 1 槽）；
- 单 float 站点 ⇒ grade **B** 不落盘（断言须带 grade）；T1 addr + T1b double ⇒ double
  提案（禁填分支显式覆盖）；
- **provenance 保守**：this 跟踪不确定的访问**不入证据**（宁缺勿滥）。

## 3. 工程面
- CLI 不变（--write 产守卫批次/--cls/--batch-out）；报告 meta 增 t1b 段 + version 2→3 + 输入 md5；
- **emit_batch evidence 同时携带 T1+T1b 站点**（[1239c52d] 现 :577 只拼 t1[:4]——守卫可追溯性）；
- **落盘批次排 W5（51 hex 键+4 变体键归一）后或每批重生成**（批次按 (cls,key) 会陈旧）；
- 测试增量（test_type_evidence.py 追加，v2 35 条全保留；字节 fixture 用 `_decode` 模式，
  状态机用序列级 fixture——勿引 TestPackedInlineSize（那是 W4-C0b 的，不含 capstone））：
  ①纯函数：`this_track_step` 状态机（regs_write 失效/别名归一/call 失效/复制传播）；
  ②合成 fixture：this+disp 载体 → Ref(note='this+disp')；
  ③合并分级：T1 addr-only + T1b float ⇒ float(B/A 视站点数)；T1 4B + T1b 1B ⇒ C + cross-source-width 标签；
  ④集成缝：**分母钉死=RoleSystem W 成员命中率**（≥1 个 this+0 站点的成员占比），实测
  **41/64=64%**，阈值 50%；**禁用站点留存率口径**（1,227/6,495=19% 不可作判据）；
  ⑤反面契约三条（[1239c52d]）：index 形态不得入证据 · 非 __thiscall 不得播种 ECX ·
  pop/部分寄存器写后旧值不得再作证据。

## 4. 验收（[1239c52d] 改数）
1. 全测试绿（42+v3 增量）；
2. 全量 dry-run：7 类 W 命中 **167(UB) → ≥120(provenance)**；**A 级可填充预期 2–4（实测 2：
   RoleSystem +0x508/+0x51c）**，单站点 float B 2 个只报告；W4M ~110（7 类）/全 W' 约 280–290；
   0 级 ~79/198 属**诚实结果，禁止回填凑数**；
3. 复核 A 的 10 样本表行为不变（回归锚）；
4. 提案增量走守卫批次 → 四道门（与 Step 3 同链；float 重定向 9 行走 global_retype 不属 v3）。

## 5. 风险（[1239c52d] 增 R4-R9）
- R1 this 跟踪编译器形态多样性——按"不确定即弃"；栈参 this/EBP 槽恢复列 v3.1（增量 0）；
- R2 跨源宽度冲突=**警报器**（见上），strict 下 C=3 vs UB 14——provenance 同时抑制 C 膨胀，
  "C 上升"预期在实现正确时**不会**发生（R9 校准）；
- R3 预演 19/107 是 UB 上界——**约 17 个是栈局部/外来基址污染**（CScreenMode+0xC 的 61"站点"
  全是 [esp+0xC] 类）；禁引旧数（P1-d，见 _b_t1b_unlock_premeasure superseded 标注）；
- **R4 方法误归属污染 T1b**（T1 免疫）：rolestatepanel_verdict.json 实证 PAL3::GetValue@0x462220
  访问 this+0x1795C(96KB)"非本类"——cross-source-width 是其检测器；
- R5 index 形态误归属（57 站点/1 槽）——载体收形排除；
- R6 负 disp/MI adjustor thunk——拒负 disp 防线保持；
- **R7 binary_size 不可当过滤器**（PAL3 91024→4936 实证 18 倍虚高）——size 只作提示，
  越界命中单独成表；
- R8 非 thiscall 播种污染（17 站点）——播种门 __thiscall∧非 static。
