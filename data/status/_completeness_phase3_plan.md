# 完备性工程·阶段③方案：目标集补齐（2026-09-28 round 22 草版；②判据/①终稿待 155c71bb）

## 一、目标集完备性现状（矩阵 `_completeness_phase1_matrix.md` 三附D）
| 态 | 数 | 占目标集 |
|---|---|---|
| L1 字节全同 | 55 | — |
| partial | 236 | — |
| **未进可比面** | **2,684** | **90.2%**（=113 红单元吞 3,522 定义=89.5% 生成面）|

缺口三分型（155c71bb Q6 定谳）：**语料缺 1,940**（需补 860）· 生成缺 160（84 合成正确跳过+
**59 sub_ 名形误跳（~57 真逻辑 12,557B）**+17 SKIP_CLASSES 含 **CPK 3/CIniFile 2 游戏类误跳**）·
**匹配缺=可比面堵塞**（红单元攻坚优先于匹配算法——复核硬建议 3）。

## 〇、开工前置（155c71bb 硬建议 2——**方向性裁决，先于一切批**）
**432 条判决矛盾裁决**：missing_funcs_report 称"游戏函数需注解" vs skip_functions 标
"crt_runtime/between_std_methods 跳过"——两工具判决相反，**必须先裁**（否则一边补注解一边跳过）。
裁决材料：逐条抽样×3 组（skip reason 分层）+ 调用图邻域 + 指令指纹 → 裁决表 → 各归批 A/B/库桶。

## 二、补齐批次设计（v2 按 33c45090 首报重标定）
| 批 | 内容 | 量 | 预期 | 优先 |
|---|---|---|---|---|
| **E** | 单错单元修复——**14-17 独立病灶**（非 6 族修）：族 1=**基类名后缀访问**（`x.Base`/`x->Base`，C2273+C2274 全量 106/106 同形！）codegen 等价重写规则（≥3 语义形：读首 DWORD/取子对象址/整拷贝）；族 2-6=签名/归属/lvar/合成占位/__PAIR64__ 各异 | 19 单元 | **S2 95→114** ✓ 算术成立；增益：扩 ≤2 错单元再 +14 绿 | **①** |
| A-游戏 | sub_ 游戏区 74 件（reason∈{between_std_methods,无}）——**归属优先**（同类方法候选 add_method，勿默认落 free_functions.cpp）| 74 | 语料+74 | ② |
| A-库尾 | 32 件（crt_runtime/crt_init）逐条裁决——无证据者**保持 skip 并移出目标集** | 32 | 待裁 | ③ |
| B | **重标定**：game 47+待证 34（非 432！）；76 类剔伪类型（__m64 63/double 43/__m128 22/BYTE 19/WPARAM 14——game_missing_report 已判伪 171/真缺 289）| 47+34 | 语料+47~81 | ④ |
| F | 类型族修（C2440 368/C2664 162/C2228 95…≈667 错）| ~667 | 长坡 | ⑤ |
| C/G | 小件 92 分桶 / 生成缺 160（59 sub_ 误跳+CPK 3+CIniFile 2）| — | — | ⑥ |
| **⚠️ 不可匹配桶** | **third_party_gcc 25 件**（GCC 对齐序言=非 MSVC6 编译产物）⇒ **不得入目标集**（L1 终态无解）——目标集口径须显式排除 | 25 | — | 全程 |

**R2 防线（批 E 族 1 开工前必建）**：①纯函数单测（R15）②95 绿单元重生成文本 **diff=0** ③106 点位前后对照清单
④**限定形不误伤**（绿单元实存 `(((UIWnd*)v4))->UIWnd::sub_...` 合法形；规则作用域须收窄为"名字是静态类型
的基类**且后随字符非 `:`**"——N5）⑤C1003 判据=截断单元看 max-line 前进而非错误净数。

## 二附D、批 3（fix_struct_value_casts）复核闭环账
- d8ca4fd2 判须返工（前提证伪/成员集双向错/影子测试）→ 返工四路线 → 6e90d6f0 判**有条件清账**
  → 四条件兑现：①N-a 廉价收窄（同名任一标量/指针实例⇒整名出局——4 处语义反转误修清零）
  ②N-f 谓词提纯函数+单测 ③N-c M4 不可达守卫删除（结构原因记 docstring）④N-d PVOID 等入标量表。
  **101/101 测绿**。
- **【挂账 N1】** fix 先于 echo-drop 执行序——`&` 落入回波形字符类外 ⇒ 回波剔除丢失
  （3608 语料 0 发作=语料盲，无法证否）；修法=序 swap 或 `_echo_ok` 认 `&`。
- **【挂账】** 类域数据源（接口已备未接线——N-a 廉价收窄为保守替代）；dict 形 5/9 漏收；
  返工代码未提交（提交前 probe+regression_detector 对账）。

## 二附C、c1e92014 返工复核（Q1/Q6 先行）【有条件收】
- **三反例 A/B/C 关死 ✓**（实测）+ (int) 铸形分支复活 ✓ + RemoveAt 撤回双侧一致 ✓ +
  PAIR64 双铸 8 组数值等价 ✓——返工本体按件可收。
- **再攻新孔（同族残孔，语料可达性低——`else if`=0 命中/Hex-Rays 无块注释/hex 默认参仅合成头）**：
  ①块注释逗号虚增 argc ②`else if`/宏头未排除 ③数字守卫不盖 0x10/100u ④**匹配侧不避字符串/注释**
  （`sprintf(buf,"UpdateAnim(a1,v4)")` 字面量内容被改写——较重）⑤铸形变体假阴（安全向）。
- **【挂账 E-1】** drop_call_echo_arg 词法化：块注释跳过+匹配避开字符串/注释+数字/浮点/十六进制
  守卫+`else`/宏头排除。
- **【挂账 E-2】** _expand_pair64_double 同族（不跳字符串逗号+单参畸形形静默吞前缀
  `(double)__PAIR64__(a)`→`(a)` 实测）。
- **【挂账 N5】** functions.json 条目缺 class 字段 ⇒ 不走 mangle/类限定 tinfo 主路径（Q5 细则待全报）。

## 二附B、批 E 实施发现（2026-09-28 轮实施累计）
- **管线缺口 N1（新）**：成员函数签名订正的 **SetType 静默失效**（apply_annotations:2575 既有怪癖
  "报成功但不生效"）——OffsetRect 订正（int*→long*）注解/导出双侧已落但 **IDB 型未变**（decomp
  渲染仍 int* ⇒ C2664 持续）。emit_headers:2454 设计注释**正确**拒绝注解直通（防 C2556）⇒
  正道=修 SetType 成员函数路径（或 tinfo_t API 备路——:1846 已有 fallback 函数）。
  OffsetRect/RemoveAt 两订正暂为**注解侧已落、渲染面待通**状态。
- **批 E 已验证战果**：**S2 95→100**（五绿单元：Camera（array→ref）/TextureLibDataBase（PAIR64）/
  CCBResultWindow（丢限定成员转写）/Comp_DonateUI（echo 双证据门）/CCBItemWindow（N1 签名
  全链修）——零回归链验 ✓ errors 1,660→1,645。
- **N1 修复路径端到端实证**：functions.json=IDB 型源（apply:2514 设计）→ 类限定 tinfo 形 →
  decomp 渲染 → 声明面 ✓；⚠️ 双 this 陷阱（显式 this+apply __hidden 自加=C2665 双重载）——
  functions.json 条目**不写显式 this**。
- **d0643565 返工账**：echo 门三反例修（字面量逗号/控制流头/铸形死代码复活，+4 回归测 77/77）·
  RemoveAt 撤 int（体证据 strcmp=字符串）· PAIR64 双铸（符号反例）· 件 1 两前提注记。
- **下一批（待 c1e92014 出报）**：base_suffix_rewrite 两洞修（①接收者形分派：this/指针形
  `(*_T*)recv` vs 成员形 `(*_T*)&recv` ②偏移 0 守卫=struct_bases 带偏移核）→ 重接线 →
  族 1 五单元（C2273/C2274 ×5）转绿。
- **机制件账**：base_suffix_rewrite（回退态+7 测）· _expand_pair64_double（2 测）·
  rewrite_unqualified_member_call（2 测）· drop_call_echo_arg 双证据门（3 测）·
  stage5 ref-param array 分支 · stage3 vftable strip 正证 · 6 存量测试设计演进更新。

## 二附、Q2-Q5 复核增补（33c45090 全案）
- **批 A 落地墙**：自由函数全落 free_functions.cpp（832KB/C1003 黑洞）⇒ 解禁前先做**归属**
  （between_std_methods 53 件=add_method 入类单元）或**单元拆分**；解 skip 须整轮 IDA 重跑（攒批一次）；
  apply_annotations:2519 对 skip 地址**静默跳过签名**——批 B 注解+解 skip **原子落地**（单源守卫会拦）。
- **unskip_function 五防线**：①evidence 绑 adjudication VA 级判决（verdict=game 才许）②拒 crt_runtime/
  crt_init/gcc_aligned 无翻案证据者 ③与注解 add 同条原子 ④后置门（check_annotations 绿+registry
  skipped→decompiled 计数=工单数）⑤批级棘轮对齐。
- **批序修正**：可比面维度 **E→F**（F 唯一直接开可比面）；A/B/G=覆盖维度并行（A'=A-游戏 74+G 的 59+17
  解 skip 合轨）；E 扩容 ≤2 错单元（2 错 14 个/3 错 11 个）再 +14 绿。
- **五堵隐藏墙（"全可比"分层口径）**：①生成缺 160 不进任何单元 ②C1003 黑洞（**现 2 个**：CCBStage+
  free_functions——CCBUI 已退出，CLAUDE.md"3 个"过时）③208/208 分母随批增长（每批重推）④s4 残余
  （unresolved_synth 47+unmatched 73）⑤**第三方编译产物墙**（gcc_aligned 25+crt 尾=永不可能 L1）
  ⇒ **可比 ≠ 可全同**；第三方/CRT 尾划出目标集。
- **门禁豁免条款**：新语料成员落现绿单元可合法致红（L1 降）——按"同族可解释回退+白名单记录"放行
  （仿 C1003 条款），否则批 A 被自装门卡死。棘轮五件套对齐（s4/compile_baseline/regression_detector/
  census/bucket+ida_functions）挂**每批**。

**期望校准（v2 修正归因）**：**批 E 独立即可可比面 ~500+**（E 的 19 单元含 234 个生成定义，s4 符号
468→~700；现目标集可比=L1 **65**+partial 236=301——注：55 系骨架桶口径，Q6 全量复算为 65）；
批 A 对可比面贡献=0 直至其函数生成+所在单元编译绿（其落点 free_functions.cpp=832KB/326 函数/
C1003 已截断的红单元——隐藏墙）；"113 红单元吞 3,522 定义"=census 口径（`// 0x` 复算 3,052/3,448——
两口径并记）。

**棘轮对齐门（v2 挂全批）**：批 E/F 转绿同样改 s4 可比总体 ⇒ **每批**后对齐五件套：s4（--rebaseline）+
compile_baseline + regression_detector 基线 + completeness_census/bucket_report + ida_functions 分母。

## 三、每批门禁
字节面 (a)-(e) + 四道门（布局等价/错误不增/L1 不降/证据自校验）+ 零回归 + 终验复核；
改语料批（A/B）额外门：**语料扩员后基线棘轮显式对齐**（L1 口径变化预告——b827549e 教训）。

## 四、风险
R1 批 A 解禁大件引发生成面新错误形态（巨型函数的 codegen 承压）；
R2 批 E 族修误伤（cast 形改动需 W6 级回归验证）；
R3 语料扩员改 L1/匹配分母（棘轮对齐）；
R4 判据选型变化改目标集口径（2,975 数随 ② 定稿移动——批 E 不受影响）。
