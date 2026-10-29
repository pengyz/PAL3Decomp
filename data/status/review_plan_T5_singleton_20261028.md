# 独立对抗复核 · Plan Task 5(i) SingletonThunk 胶水剥离（commit 88a7af860）

- **复核对象**：`88a7af860` · `fix(gen): T5(i) SingletonThunk 胶水剥离——LNK2001 六件排雷`
- **变更面**：`pipeline/gen/stages/stage5_fixup.py`（+接线）· `pipeline/gen/textutil.py`（+`strip_singleton_thunk_glue`）· `tests/test_singleton_glue_strip.py`（+4 测）
- **复核方式**：objdump 字节形独立复解 + 生成源实测 + link_census 对账 + 反编译语料配对取证（不采信 commit 自述，逐条独立复验）
- **日期**：2026-10-29

---

## 一句话裁决

# ✅ ACCEPT-WITH-FIXES

核心 deliverable（LNK2001 六件排雷）**已达成并经 link_census 实测证实**；字节形复解**全对**。但「等价剥离」宣称**在 6 站点里只对 4 站成立**——Site 2/3 存在**语义配对 atexit 半剥离**（剥 ctor 留 cleanup），是核心缺陷 D2；配套有记账缺失（D5）、测试锁缺口（D3）、接线教训未沉淀（D4）。均**可修**，不构成 REJECT。

---

## 逐项复验

### ① 字节形复验 —— ✅ PASS（全对，仅 1 处 commit 笔误）

objdump 独立复解 6 件，全部为 **`B9 imm32 E9`**（`mov ecx, imm32; jmp rel32`）跳板形：

| # | Thunk @ | imm32=对象 | jmp 目标 | 目标实解 | 角色 |
|---|---------|-----------|----------|----------|------|
| 1 | `0x431D90` | `0xD8C338` | `0x408BC0` | `mov eax,ecx; ret`（平凡 ctor，return this） | Iostream_init **ctor** |
| 2 | `0x431DB0` | `0xD8C338` | `0x431FA0` | `jmp 0x432480`（dtor 包装） | Iostream_init **dtor** |
| 3 | `0x431E70` | `0xD8C2E8` | `0x434470` | 真 ctor 体（初始化 +4..+0x10） | PtrArray **ctor** |
| 4 | `0x431EC0` | `0xD8C2C8` | `0x434470` | 同上（**共 ctor**） | PtrArray **ctor** |
| 5 | `0x4B6D70` | `0xDE6CD8`（=g_RenderTarget3） | `0x408BD0` | `ret` = **NullCallback** | 空 dtor |
| 6 | `0x4BFD60` | `0xDE8B40` | `0x408BD0` | `ret` = **NullCallback**（**共**） | 空 dtor |

- **5 对象** ✓：`0xD8C338`（ctor/dtor 对）· `0xD8C2E8` · `0xD8C2C8` · `0xDE6CD8` · `0xDE8B40`。
- **4 jmp 目标** ✓：`0x408BC0` / `0x431FA0` / `0x434470`（3、4 共）/ `0x408BD0`（5、6 共）。
- **NullCallback = `0x408BD0`** ✓：`pal3_names.json` 命名锚定 + 体=`ret`（空），与 5、6 两件 `mov ecx, obj; jmp ret`（纯 no-op）自洽。
- **共 ctor 共 Callback 关系** ✓：`0xD8C2C8` 共 `0x434470`、`0xDE8B40` 共 `0x408BD0`，与被审对象描述完全一致。

> **缺陷 D1（trivial/文档）**：commit message 写作「`0xBFD60`」，实为 **`0x4BFD60`**（漏一位）。字节解码本身以 `0x4BFD60` 正确完成，仅 commit 文本笔误。

### ② 等价性攻击（胶水是否等价，逐站点判定 6 处）—— ⚠️ PARTIAL（4 净 2 污，核心缺陷 D2）

6 条被剥语句映射到 5 个反编译站点（`PalScript::_StaticInit` 0x431d80 独占 2 条）。逐站判定：

| 站点 | 宿主函数 | 被剥语句 | 语义（配对取证） | 剥离是否等价 |
|------|----------|----------|------------------|--------------|
| **1** | `PalScript::_StaticInit` | `SingletonThunk_00431D90(this);` + `atexit(SingletonThunk_00431DB0);` | Iostream_init（0xD8C338）ctor+dtor **对**，均 CRT iostream 合成物 | ✅ **等价**（对称双剥 + `<iostream>` 再生） |
| **2** | `PalScriptMgr::PalScriptMgr` | `SingletonThunk_00431E70(this);` | **构造 0xD8C2E8**（真 ctor 0x434470）；其配对 cleanup `ConditionalCleanup`=`PtrArray::Remove(&unk_D8C2E8)` **未剥** | ⚠️ **不对称**（半剥离） |
| **3** | `PalScriptMgr::OpenSCE` | `SingletonThunk_00431EC0(this);` | **构造 0xD8C2C8**（真 ctor 0x434470）；配对 cleanup `FindScript`=`PtrArray::Remove(&unk_D8C2C8)` **未剥** | ⚠️ **不对称**（半剥离） |
| **4** | `PAL3::GetInstance` | `atexit(SingletonThunk_004B6D70);` | 注册 NullCallback（`ret` 空）；真初始化 `RenderTarget3::Reset` **保留** | ✅ **等价**（删 no-op atexit） |
| **5** | `PAL3::GetInstance_fd20` | `atexit(SingletonThunk_004BFD60);` | 注册 NullCallback（`ret` 空）；真初始化 `ResetFadeState` **保留** | ✅ **等价**（删 no-op atexit） |

**4 站（1、4、5，共 4 条语句）干净等价**：Site 1 为 CRT iostream 对称双剥（`<iostream>` 自动再生）；Site 4/5 目标是 `ret` 空体，删 no-op atexit 注册零行为差。

> **缺陷 D2（核心）—— Site 2/3 语义配对 atexit 半剥离**：
> `_ST_GLUE` 正则是**名字字面**匹配（只认 `SingletonThunk_XXXX`）。Site 2/3 的 ctor/dtor 是**同一对象的语义对**：
> - `SingletonThunk_00431E70` = 构造 `0xD8C2E8`；`ConditionalCleanup` = `PtrArray::Remove(&unk_D8C2E8)` = 销毁 `0xD8C2E8`。
> - `SingletonThunk_00431EC0` = 构造 `0xD8C2C8`；`FindScript` = `PtrArray::Remove(&unk_D8C2C8)` = 销毁 `0xD8C2C8`。
>
> 正则剥掉 ctor（名含 `SingletonThunk`）却留下配对 cleanup（名 `ConditionalCleanup`/`FindScript` 不匹配）。生成源实证（`pal3/src/Script/PalScriptMgr.cpp`）：
> ```
> 3133: PalScriptMgr::PalScriptMgr()
> 3135:   atexit(ConditionalCleanup);   ← 保留（0xD8C2E8 的 cleanup）
>        // SingletonThunk_00431E70(this); ← 已剥（0xD8C2E8 的 ctor）
> 3139: void PalScriptMgr::OpenSCE()
> 3141:   atexit(FindScript);           ← 保留（0xD8C2C8 的 cleanup）
>        // SingletonThunk_00431EC0(this); ← 已剥（0xD8C2C8 的 ctor）
> ```
> 后果：(a) 构造函数不再构造、OpenSCE 不再开脚本，只剩一个为「从未构造之对象」注册的 cleanup（悬空 atexit）；(b) 「等价剥离」**过度宣称**——仅对 1/4/5 成立；(c) 违反项目自身纪律「改名走语义不走字面 / 禁名字结论」（CLAUDE.md）——用名字字面把一个语义 ctor/dtor 对劈开。
> **待作者裁断**：`ConditionalCleanup`/`FindScript` 究竟是 (i) 源码级手工 cleanup（则 ctor 剥离 = 真初始化丢失，须补 regen_path 证明编译器再生），还是 (ii) 编译器胶水另一半（则应连 atexit 一并剥，保持对称）。commit 两者皆未做。**注意**：这两件 cleanup 带 `byte_D8C324` 位守卫（跑一次），形似**手工单例**而非编译器 dtor thunk，故「编译器随对象定义再生」对 Site 2/3 **未证**。

### ③ LNK2001 排雷实效 —— ✅ 达成（六件消失已实证；总数归因须剥离单元增长噪声）

跑 `data/status/link_census.json`（`generated_at=2026-10-29T12:26:22`，commit 12:27:01 前一轮）对账：

- **SingletonThunk 六件从 unresolved 消失** ✓：全 census JSON `SingletonThunk` 命中 **0**；`duplicates=0`（无 LNK2005 新增）。
- **「SingletonThunk 引用残留 0」** ✓：`pal3/src` 仅 `free_functions.h` 存 6 条**声明**，`.cpp` 零调用点（声明本身不产生 LNK2001，仅被调才产生）。
- **unresolved 总数归因**：`1124`（HEAD~1=T4，**124 单元**）→ `1370`（当前，**135 单元**）。**+246 由 S2 单元增长（+11）主导**，非 T5 所致；link_probe 棘轮判定（`link_probe.py:123`）明确「units 增长期 unresolved 增长 = advisory」。**T5 净贡献 = 六件 −6**，被增长噪声淹没，方向正确（减）。
- **⚠️ 归因诚实性**：Site 2/3 的 LNK2001 是**删真实初始化引用**（保真度下降）而非**定义消解**（保真度上升）清掉的；Site 1/4/5 删除即正确消解（胶水/no-op）。故 LNK2001 改善「指标有效、Site 2/3 空心」。

> **与 plan 处置的偏离（非缺陷但须记账）**：Plan Task 5 Step 3 规定处置=「记 `regen_path` + 转 `compiler_regenerated` + 仍被调者入 link_probe expected 集合」。commit 走了**第三条路**（删引用 → 零 LNK2001，自称「改调用路由」），未走 expected-set、未落实 regen_path。对 1/4/5 是更干净的等价选择；对 2/3 则留下 D2 缺口。

### ④ Ruling 复核：(ii) 5 对象全局定义挂账 —— ✅ 有条件接受，⛔ 须强化

被审 Ruling：「(ii) 5 对象全局定义（保真静态初始化）挂账下拍取证——本拍零引用=零 LNK2001」。

- **可接受性**：对**中间态字节匹配反编译**，把 5 对象（`0xD8C338`/`0xD8C2E8`/`0xD8C2C8`/`0xDE6CD8`/`0xDE8B40`）的全局定义推迟（挂账）**可接受**——终局对象落地时编译器随定义再生胶水，最终二进制仍可匹配。
- **⛔ 但「保真静态初始化缺失窗口」是真实缺口，且记账不足**：
  1. **regen_path/object_addr/source_owner 三字段全缺**（plan「Produces」明文要求）：`functions.json` 六条 `regen: None`、`skip_functions.json` 六条 source 空，仅 `skip_reason: compiler_regenerated`。⇒ **「编译器如何再生」的配方丢失**，等价宣称无法事后核验，挂账缺乏锚点。
  2. **Site 2/3 缺口大于挂账口径**：ctor 为真体（`0x434470`）、cleanup 为带守卫手工形（非编译器 dtor thunk），「compiler_regenerated」对这两件**未证**；叠加 D2 不对称，保真风险集中于此，远超「零引用=零 LNK2001」的轻描。
- **裁定（强化要求）**：挂账**接受**为已追踪中间态，但须补——(a) 逐 thunk 记 `object_addr/source_owner/regen_path`（哪个 TU 的 static 声明 / 哪个 include 再生）；(b) 逐对象显式记「静态初始化缺失窗口」台账；(c) 先解 D2（配对 atexit）使缺口对称、可解释，再谈闭合。

### ⑤ 测试锁度 + 接线断言教训 —— ⚠️ 锁偏弱（D3）+ 教训未沉淀（D4）

- **测试锁度**：`tests/test_singleton_glue_strip.py` 4 测全绿（`atexit_form`/`call_with_this`/`unrelated_untouched`/`idempotent`）。属**冒烟锁**，但**缺口**：
  - **未覆盖 D2 场景**（`atexit(ConditionalCleanup)`/`atexit(FindScript)` 这类「配对但非 SingletonThunk 名」的 cleanup 去留）——`unrelated_untouched` 只测了 `SingletonHelper_real()`，未测配对 atexit。⇒ **D2 无测试守卫**（缺陷 D3）。
  - 无 stage5 接线级断言（strip 是否真在 codegen 链触发）。
- **接线断言教训**：commit 自述「replace 须断言命中（首跑静默落空=NameError 速崩，补正复跑全绿）」。核查：**仅存于 commit message**——`textutil.py` 注释只述剥离语义、未述「须断言命中」；`docs/knowledge/` 无沉淀；代码**未强制**（`strip_singleton_thunk_glue`=裸 `sub` 无 assert，stage5=裸调用）。按 CLAUDE.md「实测数字写进被改代码旁注释」+ knowledge 纪律，应沉淀并宜 assert 化（缺陷 D4，minor）。

---

## 缺陷清单（按严重度）

| ID | 严重度 | 缺陷 | 修法 |
|----|--------|------|------|
| **D2** | **核心** | Site 2/3 语义配对 atexit 半剥离：名字字面正则剥 ctor 留 `ConditionalCleanup`/`FindScript` cleanup；「等价剥离」过度宣称；违反「语义不走字面」 | 作者裁断 cleanup 归属（源码级 vs 编译器胶水）→ 连 atexit 一并剥（对称）**或** 保留并补 ctor 的 regen_path 证据；正则改走对象配对而非名字字面 |
| **D5** | 高 | `regen_path/object_addr/source_owner` 三字段全缺（plan「Produces」未落实）；等价/再生配方不可核验，Ruling(ii) 挂账失锚 | 六条逐 thunk 补三字段（哪个 TU static / 哪个 include 再生）+ 逐对象记静态初始化缺失台账 |
| **D3** | 中 | 4 测不覆盖 D2 配对 atexit 场景，核心缺陷无测试守卫 | 增测 `atexit(ConditionalCleanup)`/`atexit(FindScript)` 去留（按 D2 裁断结果定期望） |
| **D4** | 低 | 接线教训「replace 须断言命中」仅 commit msg，未入注释/knowledge，代码未 assert 强制 | 沉淀进 `textutil.py` 注释或 `docs/knowledge/`；宜在 stage5 接线加「命中非空」断言 |
| **D1** | trivial | commit msg `0xBFD60` 笔误（实为 `0x4BFD60`） | 勘误（文档层） |

## 未复验（本次时间盒外 / 需作者补证）

1. **「全套 915 绿 · loop 5/5」** 未整跑（时间盒）；仅复跑 4 条 dedicated 测（绿）。`S2 135/214` 已由 census `units_linked=135` 交叉印证。
2. **剥离对 6 站点的字节匹配影响**——本任务范围是 LNK2001 非 match；终局字节等同留待后续 `match` 三限定口径验证。
3. **`ConditionalCleanup`/`FindScript` 的源码级 vs 编译器胶水定性**（D2 裁断前置）——需作者语义取证 + regen_path 证据，本次只能标注「未证/存疑」。
4. **T5 净 −6 与 +11 单元增长的精确切分**——仅得 HEAD~1（124 单元）对照，缺「135 单元态剥离前」快照；已据 link_probe 棘轮「增长期 advisory」定性，未得逐件净额。

---

## 附：证据锚点

- 字节形：`objdump -d PAL3.exe`（`original/PAL3.exe`）逐件解 6 thunk + 4 target。
- 配对取证：`asm/pal3/decomp/`——`ConditionalCleanup_00431e90.json`（`PtrArray::Remove(&unk_D8C2E8)`）· `FindScript_00431ee0.json`（`PtrArray::Remove(&unk_D8C2C8)`）· `PalScript_StaticInitvoid_00431d80` 等 5 站点 decompiled_c。
- 生成源不对称：`pal3/src/Script/PalScriptMgr.cpp:3133-3141`。
- LNK2001：`data/status/link_census.json`（`SingletonThunk`=0 · `unresolved`=1370 · `duplicates`=0）；对照 `git show HEAD~1:data/status/link_census.json`（1124/124）。
- 注解记账：`data/annotations/functions.json`（六条 `regen: None`）· `skip_functions.json`（六条 `skip_reason: compiler_regenerated`，source 空）。
- 测试：`tests/test_singleton_glue_strip.py`（4 passed）。
