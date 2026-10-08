# 双复核合流重定标：幻影容器/幻影成员是系统病（2026-09-27，B/C 批方向转向决策记录）

## 0. 结论一句话
两个独立对抗复核（ff86c62f B 线 / c34f38aa C 线）+ 编排者独立反汇编，三方合流指向同一系统病：
**凭地址区间重叠（auto:overlap_*）或 blob 自我闭合"精确"造出的容器与成员，装的根本不是对象存储**
（函数内 static、池化字符串字面量、独立 g_ 全局）。⇒ B 批"填充"与 C 批"缺口填充"都必须
先过**成员存在性/容器真实性裁定门**，否则是给幻影定型/把独立对象成员化。

## 1. 三方证据（全部原始字节级，非推断）
### PAL3（ff86c62f 四证 + 编排者复验 0x4C0F6C 区）
- PAL3.json key≥4952（0x1358）的 **20 条全是伪成员**：12 条 `auto:overlap_g_PAL3_at_*`
  （仅凭"落在地址区间"造出）+ 8 条 `global_analysis:g_nXXX`（source 自己写着**独立全局符号名**）。
- 决定性证据：0xDE8DF8..0xDE8E24 是 `RenderTarget2::SceneRoleCallback` 的**函数内 static**
  （guard 字节 0xDE8E24 按位 1/2/4/8 + `push 0x4C1240` 空析构 thunk + `call 0x553041`
  _onexit 包装；thunk 体全 `ret`）。**编译器生成的 static 不可能落在另一对象存储体内**。
- 真实成员最大偏移 0xF9C（key 3996）；census 里容器 `size_bytes=None` ⇒ binary_size=91024
  无任何外部锚（blob 自我闭合循环论证）。
- **7 条 float 提案的证据本身 100% 真实**（47 条字节级复核 0 失配）——错的是成员归属，
  不是定型 ⇒ **禁 --write**，正确动作是删/改归属这 20 条（幻影清理批），不是给它们定型。
### CEffMgr（c34f38aa 原始字节铁证）
- g_EffMgr@0x5D5484 的 .data 字节是 **VC6 池化字符串表**（"quake\0\0\0bink\0\0\0\0shock…
  meteor…explosive…grid…"）；.text 仅 1 处引用（`push 5D5484h` = 把 "quake" 当字符串实参）；
  m_sz5D8C3C@0x5D8C3C 是格式串 "(..)%s"（`push offset` 当 %s）；C0a 拟保留的"尾块 float"
  @0xA91C 是 "rollBar\scrollbar"。⇒ **43312B 容器是幻影**，263 行（123 个 a* 名=串字面量）
  是独立 .data 对象；C1 CEffMgr 半边整体暂停，先按 this 物化/ctor/atexit/GetInstance 锚重定位真身。
### SceneMgr（c34f38aa）
- g_palScript@0xC10968 = g_SceneMgr+0xC5D8，**A 级锚**（dynamic-init ctor thunk 0x4086c0、
  .text 12 处引用）+ 2176B(PalScript)，与现有成员 m_pCameraCtrl@+0xC5D8 **同字节冲突**
  （后者 source 仅 docs:scenemgr_layout.md = 非二进制证据）；[0xC5D8,…) 疑为 PalScript[N] 数组区
  （stride 0x880=PalScript 尺寸佐证）。129 行中 18 行与现有成员同偏移异名。
- 口径：真缺口 **258/111**（非 263/129；5/18 行已被 known_members 覆盖）；census 已陈旧
  （_meta.md5_globals_h 8989b2c0≠现 globals.h c54092e2）须重跑。

## 2. 对 B 批的改判
1. **Step 3 填充批次暂缓**（原 A 级 7 条 PAL3 float 全部挂在幻影上）；
2. 工作集 W=715 增加**成员存在性前置**（复核 ff86c62f 要求）：剔除 auto:overlap_* 与
   global_analysis:g_* 伪成员后重编目——W 会显著缩水，"211"叙事同步再校准；
3. 已实施（待复核 5560c6c5）：守卫 P1-2/P1-3 + key 纪律 + P1-4 旁证修复（42/42 测试绿）；
4. **幻影清理批**（新工项）：PAL3 20 条删除/改归属（g_nEffObjCount 等 8 个应入 globals.json
   独立全局；12 条 auto:overlap 删除）+ binary_size 证据化收缩——先过对抗复核再落。
## 3. 对 C 批的改判（_c_batch_plan.md 按 c34f38aa 终报修正）
1. **C0a 可做但缩水**：只删 key "33004"（m_nTodo_80EC）——_gap_80F0 是发射器产物
   （emit_headers.py:2039），非注解键，写进批次会被防陈旧整批拒；"尾块 float 保留"理由已失效。
2. **C0b 可做但病灶改定位**：emit_headers.py:**2174/2162**（`_inline_` 分支
   `member_size=_inline_data['size']`），非 2073（2073 只服务同偏移组）；打包尺寸公式
   **具名类型查自身 size**（tagTeamSlotsBOverlay 实证 607≠800）、struct=max(off+子打包尺寸)、
   union=max(子)；须与守卫 add_member 防重叠**共用同一尺寸函数**（缺口3）。
3. **C1 暂停**，前置两个门：§3.3 分区/锚裁定门（CEffMgr 真身重定位 + SceneMgr 尾区
   g_palScript/PalScript[N] 争端裁决 + 18 行同偏移冲突逐条裁）+ census 重跑。
4. SceneMgr 侧 111 行在分区裁定后走 **(甲) 拆 blob**（(乙) 三重阻断已坐实：data.py:140 排除
   _inline_、:156 同偏移覆盖、union 变体 name=""）。
## 4. 新工项队列（优先序）
1. 守卫加固落地（复核 5560c6c5 收敛后修复）——一切批次前置 ✓ 实现已完；
2. **成员存在性/容器真实性裁定门**（工具化）：this 物化锚（ctor/atexit/GetInstance/static-init
   guard）+ 串字面量识别 + 符号边界；输出逐成员"存在/幻影/待裁"；
3. 幻影清理批（PAL3 → CEffMgr 容器 → SceneMgr 尾区，逐类过复核）；
4. C0a（缩水版）→ C0b（2174/2162 + 共享尺寸 oracle）→ C1（门后）；
5. B 批重编目 W' + 填充（真实成员上的证据分级，T1+T1b 合并按 _b_type_evidence_v3_design）；
6. D 批：显式 this 调用修复（0cc3dbf0 复核在跑）→ 基线对账收官（_d_batch_baseline_reconciliation）。
## 5. 铁律重申（本轮教训）
- "binary_size 精确闭合"**不是**容器真实性证据（blob 自我闭合循环论证）；
- auto:overlap_* 只是地址区间猜测，**不是**成员存在证据；
- 成员存在性 = this 物化锚 / ctor 初始化范围 / 独立符号名 / 多函数访问模式，四选一以上；
- 否定结论与填充结论同标准：都要原始字节级证据（本轮三条结论全部可 capstone 复验）。
