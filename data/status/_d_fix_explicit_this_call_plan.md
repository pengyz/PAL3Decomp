# D 前移项方案：接线 _fix_explicit_this_calls（2 回退单元 + 53 条已知 C2660）——2026-09-27 草案，待对抗复核

## 1. 病灶层三问（CLAUDE.md 红线，已只读作答）
1. **病灶在哪一层**：codegen stage5 有现成变换 `rewrite_explicit_this_call`
   （pipeline/gen/stages/stage5_fixup.py:431-458，纯函数 + 19 单测）但
   `_fix_explicit_this_calls`（:461）**未接线**——Hex-Rays 对导入型 thiscall 输出
   `Cls::M(obj, args)` 显式 this 自由形态，MSVC 按成员声明（1 参）编译 ⇒ C2660。
2. **消费者实际读哪个文件**：编译器读生成头（pal3/src/**/*.h，来自注解 methods 表）与
   手写 SDK 头（include/gbengine/*.h）。2026-09-21 不接线的原因正是元数取了
   **decomp 侧**（store.method_sigs，运行时由 decomp 填充）与上述声明不一致 ⇒
   定义头被误改写（②类：C2199/C2143/C2447）。
3. **报错还缺什么**：C2660 只给个数不给类型 ⇒ 不能据此推断重载；真实约定由二进制定谳
   （本方案已做，见 §2）。

## 2. 二进制证据（已完成，_d_batch_baseline_reconciliation.md §3.1）
- `CameraCtrl::SetAsCurrent` @0x41C630 = __thiscall + 1 显式参（mov esi,ecx + ret 4）；
- 转调 `call [0x56a2dc]`（gbengine 导入槽）ECX=this+4 + push flags ⇒ `gbCamera::SetAsCurrent`
  = thiscall 成员 1 显式参；include/gbengine/gbCamera.h 的成员声明**正确**；
- 同理 `gbGeomNode::GetOBBox(gbOBBox*)`。
- ⇒ 真实调用 ABI：`mov ecx,obj; push arg; call`（成员形态可生成正确字节；静态/自由形态
  push this **字节不符**，是假修复，禁）。

## 3. 修复设计（根治 2026-09-21 记载的前置条件）
**元数取自"MSVC 实际读的声明"**，双源合并：
- (a) 注解 methods 表（data/annotations/structs/*.json `methods` 的 signature）——
  pal3 类生成头声明的源头；
- (b) include/gbengine/*.h 手写 SDK 头的成员声明（20 个文件，范围有界）——
  轻量类作用域声明扫描（class X { ... Ret M(args); ... }）。

接线不变量（全部已有测试/守卫）：
- CHAIN 守卫（'>' '.' ':' 前缀不改写）——①类双解引用已修；
- 安全闸 `实参数 == 形参数 + 1`（含 this）——声明/定义头实参数==形参数天然豁免；
- 元数正确的前提下 ②（定义头误改写）自然消失（docstring 已注明根治路径）；
- 改写产物 `((Cls *)obj)->M(rest...)` 生成 thiscall ABI ✓（与 §2 一致）。

## 4. 验收（四道门 + 显式读数）
1. `pipeline/gen/tests/test_explicit_this_call.py` 19 项全绿（含 4 条反面）；
2. MatrixStack.cpp / UIProgressBar.cpp 由 2×C2660 转绿（本项直接目标）；
3. 总错误数不增（对 probe_census 1796；注意 C1003 截断单元按最大行号判）；
4. C2660 总量下降、无新 C2199/C2143/C2447（②类回归哨兵）；
5. L1 不降（match 当场读，不回看棘轮文件）。
全流程：codegen all → compile_regression → probe → regression_detector → match，
病灶层三问写进 commit message。

## 5. 风险与边界
- R1：SDK 头声明扫描器的正确性（类作用域/嵌套/typedef）——纯函数 + 单测先行（R15）；
- R2：(a) 源里 signature 的 this 计数约定（含/不含 this）须逐一实测对齐（53 条样本集可当校验集）；
- R3：可能暴露**真语义分歧**（声明与二进制不符的既有标注错）——逐条转人工裁定，不静默改；
- R4：本项是 codegen 层（跨层）——四道门 + 对抗复核后再合入；不与 B/C 批次混批。
