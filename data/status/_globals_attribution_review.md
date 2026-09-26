# 全局变量归属：对抗复核报告与完备性方案（2026-09-27）

状态：子 agent 对抗复核完成（agent_1c8d35df）。本文件为复核报告全文 + 整合后的完备性方案。
用户裁定：overlaps_with 是 annotation check 的临时白名单、属错误机制，后续移除——
方案不得依赖它，其职能由证据驱动的非重叠分区规则（§分区）替代。

## 复核对草稿的关键修正
1. 口径钉死：globals.h 2,734 extern **全部带址**（1,980 为陈旧读数）；.data 初始化 937 / BSS 1,642 / .rdata 155。
2. int 无类型 1,158/2,734=42.4%（非 55%——分母错）。
3. **两个最大洲本身就是已 typed 容器的内部**：洲1 ⊂ g_ScriptSystemData(12,624B @0xD8B318，吞 641 个 extern)；洲2 ⊂ g_SceneMgr(58,692B @0xC04390，洲界 0xC056A4 = g_RoleSlotBuf 尾)。扫描器价值 = 补 known_members，不是找容器。
4. 覆盖真缺口：1,141/2,734（41.7%）已在某容器 extent 内；known_members 仅 78 偏移覆盖，缺 1,025（ScriptSystemData 缺 597 / CEffMgr 263 / SceneMgr 165）。
5. 重叠实态 = 3 对（非 7）；_overlap_data.json 陈旧勿用。当前重叠：g_RoleSlotBuf⊂g_SceneMgr、g_palScript⊂g_SceneMgr、g_vRotateAxis⊂g_ScriptSystemData。
6. 证据类扩充：E 类单例三元组（guard+ctor+atexit，107 函数）> A 类（60 站点）；D 类 XCU 用 IDA 函数边界三重条件可稳；F 类 .rdata 指针表 125 字/115 全局；H 类 memcpy 9 处。J(SEH)/K(字符串) 不参与 extent 判定。
7. CCBStage 0xC05F30：无 ctor 锚（0x40dcf0 是方法调用），673,988B extent 冲 SceneMgr 区——保持 B8 报冲突，不得作锚。
8. 修复路径纠正：容器 typing 走 **IDB UDT size 门**（globals 级 binary_size 无消费者）；apply 两趟；**stage4 首中语义（最低基址优先）使非重叠分区成为正确性前置**；SceneMgr 布局漂移 101/169 未修前禁止成员化（文本级替换编译必过字节必错）。

## 完备性方案（7 阶段骨架，各带门禁）
见同文件下方复核报告全文 §五；bucket taxonomy B0-B9、Σ==2734 完备门、B9 冲突只报警不自动改、批次顺序 ScriptSystemData 先/SceneMgr 最后。

---

## 子 agent 复核报告全文（agent_1c8d35df-fbea-472a-ada9-db2a96150766）

### 一、验证测量：四个数字里两个不可复现，且"最大洲"的定性比草稿更强

#### 1.1 实测 vs 草稿数字

| 草稿声称 | 实测（当前树） | 裁定 |
|---|---|---|
| globals.h 2,734 extern，1,980 带地址 | 2,734 extern，2,734 全部带地址（2,579 .data + 155 .rdata）。按 PE 节再切：初始化 .data(0x580000-0x60C000) 937 个、BSS(0x60C000-0x1897000) 1,642 个、.rdata 155 个 | ✗ "1,980" 不可复现，扫描器必须先钉死口径 |
| 1,100 个（55%）无类型 int | 1,158/2,734 = 42.4% 纯 int；.data 内 1,071/2,579 = 41.5%。其余：char 506、unsigned char 278、CHAR 157、unsigned short 166、float 96、void* 85 | ✗ 分母错 |
| 最大洲 0xD8B314-0xD8D424 有 627 个 | [0xD8B314,0xD8D424] 内 633 个（平均间距 13.4B） | ≈✓（边界效应）|
| 第二/三洲 104 / 49 个 | 127 / 50 | ≈✓ |
| ≥256B 容器仅 10 个、交叉只覆盖 25/1980（1%） | 两个口径都错：(a) globals 级 binary_size 只有 7 条；(b) 容器早已通过 type+IDA UDT size 成为 struct_instances（共 47 个，data.py:171-187），1,141/2,734（41.7%）的 extern 已落在某容器 extent 内。真正缺口是 known_members：内部非自身基址的 1,100 个 extern 中，仅 78 个偏移有 known_member 覆盖，1,025 个无（ScriptSystemData 缺 597、CEffMgr 缺 263、SceneMgr 缺 165） | ✗ 覆盖率 1% 是陈旧/错口径读数；真实瓶颈是 known_members 7% 覆盖 |
| ScriptSystemData 12,624B @0xD8B318 | structs/ScriptSystemData.json binary_size=12624，地址一致；extent [0xD8B318,0xD8E468) 吞掉 641 个 extern——最大洲整体是 ScriptSystemData 的内部，草稿的洲边界 0xD8D424 只是分块截断 | ✓ 且比草稿更强 |
| PalScript 2,176B @0xD8C2B0 附近 | 2,176 ✓ 但独立对象 g_palScript @0xC10968（globals.json 注明 ctor thunk 0x4086c0 证据）；0xD8C2B0 是 ScriptSystemData 内部偏移 0xF98 的 phantom，且被注成 PalScript *（指针！） | ✗ 混淆了两个东西，且指针/内嵌二义未决 |
| CCBStage 688KB 指派存疑 @unk_C05F30 | structs/CCBStage.json binary_size=673,988B（=658KiB，非 688KB）；0xC05F30 在 globals.json 无注解；capstone 找到 mov ecx,0xC05F30; call 0x40dcf0，但 0x40dcf0 函数头无 mov [ecx],vtable、反而读 [ecx+4]/[ecx+8]——是方法调用不是 ctor。即 0xC05F30 没有 ctor 锚 | "指派存疑"成立且更糟：连 A 级锚都没有 |
| g_SceneMgr 5.8 万 B @0xBF...? | @0xC04390，SceneMgr binary_size=58,692 → [0xC04390,0xC128D4)。第二洲 0xC056A4 恰是 g_RoleSlotBuf(0xC043A0+4,868=0xC056A4) 的结束地址——第二洲也是 SceneMgr 内部 | 地址记错，性质成立 |
| SaleUI 105,912 | structs/SaleUI.json binary_size=105,912 ✓ | ✓ |
| ctor 43 处/11 个；vtable 直存 0；atexit 111 | 线性扫描 mov ecx,<.data> + 3 指令窗内 call：60 处/18 个全局（草稿窗口更严故 43/11，量级一致）；C7 05 .data ← .rdata 0 处 ✓；atexit 252 个 call 站点 / 111 个函数 / 98 个唯一 thunk | ≈✓（"全局显式 ctor 极少"结论成立；atexit 111 是函数数不是站点数）|

#### 1.2 关键定性修正（比数字更重要）

1. 两个"最大洲"根本不是待归属的未知区域：洲 1 ⊂ 已 typed 的 g_ScriptSystemData，洲 2 ⊂ 已 typed 的 g_SceneMgr。扫描器的价值不在"发现容器"，而在"把 1,100 个内部 dword_ 补成 known_members"——草稿把重心放错了。
2. "当前重叠实例"是 3 对，不是 7 个：g_RoleSlotBuf ⊂ g_SceneMgr、g_palScript ⊂ g_SceneMgr、g_vRotateAxis ⊂ g_ScriptSystemData（重算 pipeline/gen/data.py 的构造逻辑所得）。"7 个重叠"是旧 IDB 状态（tools/_overlap_data.json 是陈旧产物：total_ida_globals=1390、仅 47 条 overlap、只覆盖 g_Input/g_RoleSystemExtra0 两个父）。
3. 头文件口径：pal3/src/globals.h 2,734 extern = IDB 命名数据(1,576 个头独有地址，其中 1,063 个 dword_/byte_ 风格) ∪ annotations(1,157 个共有地址，19 个名字不一致)；annotations 独有 149 个（多为 skip）。globals.json 1,306 条中 196 条 type=skip。

### 二、补证据类：A/B/C 之外还有 6 类可用，2 类在本二进制不可用

| 类 | 机制 | 本二进制实测可用性 | 证据 |
|---|---|---|---|
| D 动态初始化器/XCU 表 | /MT 直链：__cinit→_initterm(__xc_a,__xc_z)，每个 dyn-init stub 是含 mov ecx,<global>; call ctor 的小函数；stub 在 .rdata 有表项 | 可用且已被项目实践：globals.json 里 g_palScript 的 source 就是 "dynamic-init ctor thunk 0x4086c0"。"静态枚举不稳"可解：用 IDA 函数边界精确匹配（gotcha_attribution_signal_limits 实测 5,554 个函数边界 60/60 可靠）+ 表项必须等于函数起始 + stub 体含 E1 模式三重条件。decomp 3,608 个起始地址试跑已有 117 个 ≥3 连续精确命中 run | asm/pal3/ida_structs.json 同目录可取边界；decomp JSON 自带 address |
| E 单例懒初始化流（guard+ctor+atexit 三元组） | VC6 静态局部/单例：if((guard&1)==0){guard|=1; Ctor(&obj); atexit(DtorThunk);}，guard 字节常贴着对象（如 RenderTarget3 单例 obj=dword_DE6A30、guard=byte_DE6A4C，偏移 0x1C > binary_size 24，guard 在对象后补垫里） | 高可用：decomp 里 (&1)==0 guard + atexit 组合 107 个函数；*::GetInstance* 7 个类 8 个函数。每个三元组给出：类名(GetInstance 返回类型/thunk 调用)、extent(ctor sizeof+guard 位置)、析构(SingletonThunk) | decomp: CScreenMode_GetInstance、RenderTarget3、UIQuadManager 等 |
| F .rdata 指针表引用全局 | .rdata 数据字指向 .data | 中等：.rdata 内指向 .data 的字 1,272 个；精确命中带名全局 125 字/115 个唯一全局（g_UITemplateData x5、g_CCBStageData x3 等表驱动配置） | 脚本扫描 .rdata raw |
| G .data 初始化指针字 | 静态初始化的指针数组 | 弱：仅 5 处命中带名全局（指针多在运行期填） | 脚本扫描 .data raw(0x8C000) |
| H copy-init/memcpy 大块初始化 | memcpy(&g_X, src, N) 的 N 给出 extent 下界 | 低量但 A 级：decomp 中 memcpy 第一实参为带名全局 9 处/7 个目标（g_SaveSlotFlags、g_fCamRoleParams、g_EffTable、byte_17AC6DC…）；同族 tools/alloc_sizeof.py/alloc_point_size.py 已是既有工具链 | decomp 全文扫描 |
| I 形状证据（表/缓冲区） | 连续 run 全 .text 指针 ⇒ 函数表/vtable；run+等距访问 ⇒ 数组 | 可用：1,593 个 extent 外全局按 gap≤8 聚类，816 个孤立、777 个成 run（最大 run：0xA00510-0xA00572 52 个；0xBFDA2C-0xBFDAB0 34 个=全局指针块）。警告：run≠同一对象，BSS 池里相邻独立全局也会成 run——归并须步长/访问直方图佐证（gotcha_member_set_must_be_split_by_base_object） | 脚本聚类输出 |
| J SEH 范围表 | scope table 引用代码不引用数据 | 对全局身份不可用：decomp 0 个 _try/TryBlock；SEH 表只服务函数归属 | 扫描输出 0 |
| K 字符串引用定位 | 同时触字符串与全局的函数提供语义名 | 仅 C 级语义命名（pattern_member_evidence_grading_by_disp32_scan 已裁定），不参与 extent 判定 | — |
| 辅助 | operator new size(0x55353B，74 size 已验)、写 vtable 签名(38 种/46 函数)——不直接指认全局，但校验 E/D 锚给出的类与 sizeof；PDB(PAL3A 漂移)只可佐证不可单独作证 | | gotcha_attribution_signal_limits、gotcha_pdb_identity_drift_vtable_arbitration |

草稿证据面缺了 D/E/F/H 四类，其中 E 类覆盖面（107 函数）比 A 类（60 站点）大一个数量级，是第二支柱。

### 三、完备性框架：bucket taxonomy 与不重叠分区规则

#### 3.1 分母与目标
扫描器唯一分母：pal3/src/globals.h 的 2,734 条 extern（全部带地址）。判据：跑完后每条恰落一个 bucket，输出 11 项计数直方图，无"未分类"状态；B9/B10 是显式出口不是遗漏。

#### 3.2 Bucket 定义（按判定优先级即消解顺序，先命中先得）

| # | bucket | 判定证据（按序） | 当前规模 |
|---|---|---|---|
| B0 | 非全局/跳过 | type=skip；vtable 引用；IDA 字符串/导入 | 196（annotations 内）|
| B1 | 独立已类型对象（有自身 struct_instance）| 地址 == 某 instance base | 41 |
| B2 | 容器内部成员 | 地址 ∈ 不重叠分区的某顶层容器 [base,base+size) 且 ≠base | 1,100（78 已有 member）|
| B3 | 单例对象 | E 类三元组：guard 字节 ∈ [obj,obj+0x40] 邻域 + ctor 调用 + atexit thunk | ~107 候选函数 |
| B4 | 动态初始化对象 | D 类：XCU 表项==函数起始 ∧ stub 含 mov ecx,addr;call ∧ ctor 写自身 vtable（pattern_verify_ctor_body_before_binary_hooks）| ≥18 个唯一全局（E1∩D）|
| B5 | 数组/缓冲区 | H 类 memcpy 宽度 / alloc_sizeof / 等距访问直方图支撑的 T[N]（含已落地的 g_RoleSlotBuf 范式）| 待测 |
| B6 | 函数指针表 | 连续 run 全部字 ∈ .text（含 I 类形状证据）| 待测 |
| B7 | .rdata 常量 | 地址 ∈ .rdata（155 个，const char[]/表）| 155 |
| B8 | 独立标量（保持 int/指针原样）| 无任何锚/形状证据，但地址不与任何锚冲突 | ~816 孤立者为主 |
| B9 | 冲突隔离区 | 两个以上 A 级锚物理冲突且按 §3.3 规则不可消解 → 冻结 + 报警，不自动改 | 目标 0，现实报数 |

顺序依据：B0/B1 是既有事实；B2 必须在分区规则（§3.3）之后；B3/B4 是强二进制锚，优先于形状推断 B5-B7；B8 是诚实出口。

#### 3.3 不重叠分区规则（先于一切锚点扩展）
物理内存一个字节只能属于一个顶层对象 ⇒ 重叠 = 至少一个 extent 错。规则：
1. 包含（inner ⊆ outer）：inner 只有两条路——(a) 降级为 outer 的 known_member（从 globals 独立条目除名，如 g_vRotateAxis 已是 ScriptSystemData+2312 的先例）；(b) 若 inner 有独立生命证据（独立 ctor/atexit/GetInstance），则 outer 的 extent 收缩到 inner 前的最后一个有据边界。裁决证据：inner 内部偏移的访问直方图是否可用 outer 的成员步长解释。
2. 部分重叠：小 extent 者用严格证据重推（ctor sizeof / 最后触碰偏移+宽度 / guard 位置），重推后仍重叠 → 双双进 B9。
3. 分区产出 = 一棵"顶层对象互不重叠、成员可嵌套"的区间树；任何 typed 容器集合必须先过该树才能进 stage4。

#### 3.4 完备性门禁
- 扫描器输出：2,734 行 (addr, name, bucket, evidence_refs)；断言 Σbucket==2734。
- B2 的每条成员化建议须给三形态证据（gotcha_global_object_member_access_abs_addr：绝对地址 G+off、符号名渲染、memcpy 区间），0 命中 ⇒ 降 B8/padding，不给类型。
- 编译门 + 字节门：cli.py loop --expect-*；先 probe all 再 compile_regression（gotcha_compile_regression_reads_cached_census）。

### 四、修复路径风险：草稿的三条假设与 pipeline 事实不符

1. "容器在 globals.json 补 binary_size+known_members"——字段找错了层。struct_instances 由 globals 条目的 type + asm/pal3/ida_structs.json 的 IDB UDT size 构成（pipeline/gen/data.py:158-188），globals 级 binary_size 在 pipeline 中无消费者（全仓 grep：binary_size 只在 structs 级被 pipeline/check_annotations.py:79,333,489,608 读取）。容器要进入解析，需要的是：IDB UDT 存在且 size 正确（apply 侧 MemberExtent 门，pipeline/cli.py:467-475）+ structs/*.json 的 known_members。且 apply 必须两趟（gotcha_apply_single_pass_leaves_globals_untyped：单趟后 g_palScript item size=1 而非 2176）。
2. overlaps_with 只是校验白名单，不参与解析。【用户裁定 2026-09-27：该机制是错误机制，后续移除——分区规则取代其职能】pipeline/check_annotations.py:321-370：带 size 类型落进另一带 size 类型的 range 时，未列进 overlaps_with 即报 error；仅此而已。stage4 的解析是 sorted-by-base 首中 + known_member 回退（pipeline/gen/stages/stage4_substitution.py:207-233：for base,end,gname,gtype in store.struct_instances 首个命中即解析，失败才落下一个实例；data.py:188 排序 ⇒ 最低基址容

3. "stage4 自动消化内部 dword_"——消化器在，粮草没有。1,100 个内部引用只有 78 个能解析（known_members 缺 1,025）。补 known_members 的命名受两条既有 gotcha 约束：gotcha_member_name_voting_is_confounded_by_transitive_access、gotcha_member_set_must_be_split_by_base_object。
4. 布局漂移是最大的隐性雷。gotcha_emitted_layout_drifts_from_annotated_offsets：SceneMgr 生成头 169 成员 101 个 offsetof 不符（60%，首个成员就偏，成因含注入虚析构 + 注解 vtables:null）。成员路径替换是文本级替换，编译必过、字节必错——项目自己的教训"编译错误指标看不见语义错误"（gotcha_thiscall_free_function_is_model_error）。任何批量成员化之前必须先跑 offsetof 负下标门（该 gotcha 给出的编译器裁判法），SceneMgr 布局不修，1,100 个替换就是 1,100 个错误位移。RoleSystem 22/192 漂移同理波及 B1。
5. 名称连锁的实际形态比草稿轻但要按既有纪律做。pal3/src/ 整体是 codegen 产物（gitignore，commit f71df65f2），改名经 globals.json→重跑 codegen 传播，不需要手改引用点；风险在：gotcha_context_blind_text_substitution_corrupts_rewritten_calls（上下文无关替换毁已改写调用，既有 15 处）、gotcha_globals_cpp_nondeterministic_order（globals.cpp 顺序不定，md5 不能当锚）、C1003 截断掩盖净变化（gotcha_c1003_truncation_blinds_metric，批量替换必须内容 diff 而非错误计数）。类型从 int 变成员路径的编译风险集中在 C2440/C2039 族，应以"错误多重集不增 + L1 不降"为门。
6. 0xC05F30/CCBStage：673,988B 放 0xC05F30 会延到 0xCAE434，冲出 SceneMgr 区间且无 ctor 锚（§一.1），按 §3.3 应判"extent 无据"，保持 B8 并列冲突报告，不得当锚点。

### 五、结论与完备性方案骨架

站得住的：洲划分/密度测量方法；43→60 处 ctor + 0 vtable 直存 + atexit 的"显式全局初始化极少"定性（/MT 直链下绝大多数 .data 是零初始化 BSS 里的 POD 与缓冲，构造发生在游戏 Init 流而非 CRT）；E1 锚 + struct_instances 成员路径 + 校验门的三段式方向。

要改的：(1) 全部统计口径重钉（1,980/25/10 个数字陈旧）；(2) 修复路径改为"known_members 补齐 + IDB UDT size 门"，不是 globals 级 binary_size；(3) 锚点集加入 E 类单例三元组与 D 类 XCU（覆盖面大于 A 类）；(4) 重叠分区规则前置为一等公民；(5) 0xC05F30/洲边界等"容器指派"先过 extent 证据再入锚。

遗漏的：E/F/H 证据类、.data 初始化/BSS 结构（937/1,642/155 的三段分布，B5 类主战场在 BSS）、_overlap_data.json 陈旧性、stage4 首中语义、布局漂移与成员化的先后约束。

骨架（每阶段有产物与门禁）：
1. 测量：tools/global_region_audit.py 产出 census.json（2,734 行：addr/name/type/section(init/BSS/rdata)/bucket/锚引用）+ 直方图报告。门禁：Σ==2734，口径写死在脚本常量。
2. 分区：从 B1/B3/B4 锚建不重叠区间树（§3.3），输出 partition.json + 冲突清单。门禁：顶层区间零重叠；冲突只报警。
3. 锚定：E1(mov ecx+call) ∪ D(XCU 精确函数起始) ∪ E(guard+atexit) ∪ 已类型化对象，每锚记 class+sizeof+出处。门禁：每锚过"ctor 写自身 vtable"验伪。
4. 扩展：锚 [base,base+size) 内 dword_/byte_ 标 B2 候选，跑三形态访问证据（绝对地址/符号名/memcpy），0 证据者留 B8。产出 known_members 补丁草案。门禁：每成员带 A 级证据引用。
5. 验证：对目标容器跑 offsetof 负下标编译门（布局先于一切成员化）；codegen all → probe all → compile_regression → L1。门禁：布局匹配率不降、错误多重集不增、L1 不降。
6. 修复：按容器分批（先 ScriptSystemData——无布局漂移记录且内部 641 个缺口最集中；SceneMgr 排最后等布局修完）；每批走 annotations 批处理工具（守卫在唯一落盘出口），内容 diff 归档。
7. 棘轮：census.json 入 data/status/ 同级跟踪面；每轮 B9/B8 计数只许降不许升；结论回写 docs/knowledge。

关键文件：pipeline/gen/data.py（158-188 struct_instances 构造）、pipeline/gen/stages/stage4_substitution.py（207-271 解析）、pipeline/check_annotations.py（321-370 overlaps 语义）、docs/knowledge/gotcha_emitted_layout_drifts_from_annotated_offsets.md、tools/_overlap_data.json（陈旧，勿作输入）。
