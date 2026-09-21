---
type: gotcha
date: 2026-09-18
---

# 注解里"自造的名字"是**声明**，不是二进制证据 —— 别拿它当事实往下推

## 现象

`GlowObj` 的 offset0 在**注解**里是：

```json
"0": {"name": "__vftable", "type": "void *",
      "source": "annotation",
      "note": "renamed vfptr -> __vftable (unified with IDA convention)"}
```

而在 **IDB 导出**（`asm/pal3/ida_structs.json`）里，`GlowObj` 的**最小成员偏移是 4** ——
也就是说 **IDA 从没在 offset0 放过任何成员**；同一份 `_variants["0"]` 也只是把注解那份抄了过来。

于是这个 `__vftable` **只存在于注解层**，`source` 字段已经写着 `annotation`。

## 坑

我在修限定形 vtable 访问（147 个 `X::__vftable` 位点）时，看到这个 `source: vtable_fix` /
`annotation` 的 `__vftable` 条目，就把它当成了"注解层已经声明了 vfptr 成员"，于是准备让头生成器
**发射它**（在 `GlowObj` 等类里把 `char _gap_000[4]` 换成 `void *__vftable`）。
**这是拿一个自造名字去断言一个二进制事实。**

被纠正是因为有人问了一句："`GlowObj` 应该有基类，而不是用 gap 填充，对吗？"——
顺着查下去才发现：

* **整库没有任何指令把 vtable 装到该偏移**（复核时带上了 lea/寄存器装载形态：位移 8 与 0x28
  **一次都不存在**，全部非零位移是 0xC/0x38/0x40/0x44/0x48/0x50/0x60/0x68/0xAC/…）；
* `GlowObj` 自身 `methods=0`、`vtables=None`，**没有任何多态证据**；
* `SceneObj` 方法里 28 处 `[reg+8]`，**27 处是数值/比较用**，无一像"经 vfptr 调用"。

⇒ 若那 4 字节真是 vfptr（自己的或某个基类的），编译器**必须**在该偏移装一次表。它没有。

## 规则

1. **`source: annotation` / `vtable_fix` / `renamed ...` 这类条目是"声明"**，
   只有 `source` 指向二进制（如 `reg+disp32`、ctor 安装位移、thunk 位移）时才算证据。
   引用前先看 `source` 字段，别只看 `name`。
2. **不要用注解的名字去反推布局**。名字可能是为了让某段文本能编译而加的。
3. **"不存在"这一类否定结论，扫描必须覆盖全部写入形态**：立即数、寄存器装载
   （`mov reg, offset V; mov [base+d], reg`）、以及**基址被 lea 算进寄存器**
   （`lea reg,[base+d]; mov [reg], offset V`）。只匹配第一种会把存在的东西判成不存在。
4. 遇到"这块内存到底是什么"的问题，可用的**独立**证据是：谁写它、谁读它、怎么用
   （数值/比较/解引用/被调用）——而不是注解怎么命名它。

## 实例：`GlowObj` / `TaskMgr_*` / `PalScriptWaitObj` 的 offset0（2026-09-18）

**注解怎么说**：`known_members["0"] = {"name": "__vftable", "type": "void *", "source": "annotation",
"note": "renamed vfptr -> __vftable"}`；`source` 分布上，全库 118 个这样声明的类里
只有 **7 个**是二进制支撑的（`binary:vtable_ptr` / `binary:all CEffXxx first_off=…`），
其余是 **59 个 `vtable_fix`、21 个无 source、11 个 `annotation` 自造**、10 个 PDB……

**二进制/用法怎么说**（独立证据）：

* `CCBStage::GetRoleIndex((CCBStage *)this->SceneObj::GlowObj::__vftable, …)` ——
  **被强转成对象指针使用**；全库统计 `GlowObj::__vftable` 的强转类型：
  **`CCBStage*` 38 次**、`char*` 17、`_DWORD*` 5、`CCBSystem*` 2，**从未被当 vtable 调用**；
* `Actor_DoSceneTransition`：`v17 = (Actor *)strlen(v66); p_m_nScreenFlags->GlowObj::__vftable = v17;`
  —— **存进去的是对象指针**；
* `TaskMgr_SceneObjParam_SceneObj::__vftable` 被当成一族成员的**锚点**用：
  `*((_DWORD *)&…__vftable + 4) = 264;` / `if (!*((_BYTE *)&…__vftable + 12))` / `… = 0;` —— 数据；
* **整库没有任何指令把 vtable 装到该偏移**（带 lea/寄存器装载形态复核：位移 8 与 0x28 不存在）；
* IDA 自己**从未在 offset0 放成员**（`GlowObj` 最小成员偏移 = 4）；
* `GlowObj` 自身 `methods=0`、`vtables=None` —— 无多态证据。

**⇒ 那 4 字节是"普通数据成员（对象指针）"**，不是 vfptr，也不是基类子对象
（它是**该类自己的具名成员**，所以"应该有基类"这个假设也不成立）。

**⇒ 推论**：那 147 个限定 `X::__vftable` 位点与 **vtable 无关** —— 它们只是
"**成员名错了 + 该成员没被发射进头**"的普通成员访问。整族应归到
**注解完整性 / 命名**问题，而不是 vtable 机制问题。

**处理时的一个硬约束**（容易踩）：生成 `.cpp` 里的拼写来自 **export 产物**，
所以在**不重跑 apply/export** 的前提下改注解名字，`.cpp` 里仍然写着 `__vftable` ——
头里就必须有叫 `__vftable` 的成员才能编译。**要真正改名，必须走
annotation → apply → export → codegen 全管线**。

## 2026-09-21 更强的实例：连"尺寸证据"也被循环命名污染

修 `UIStatic.binary_size 152→248` 时，我列了"三重 A 级证据"：
① `??_L size=248 且 ctor=0x440740` ×3 · ② `operator new(248)+call 0x440740` · ③
**"ctor 0x440740 写入 `0x56AD88`，正是 UIStatic *自己声明的* vtable"**。

第三条里的引号就是漏洞 —— `0x56AD88` 在 IDB 里是**匿名 `stru_56AD88`**，
**它是不是 UIStatic 的 vtable，只能靠注解回答**；前两条的"ctor 属于 UIStatic"同样来自注解命名。
⇒ **三条证据全部回流到注解自己写进 IDB 的名字**，构成**自证循环** ✗。

**用非循环锚一撞就碎**：`??0<Cls>@@QAE@XZ` 是**编译器原生重整名**，其唯一调用点前的 `push N` 给出真实尺寸：

| 类 | 原生 ctor 符号 | 唯一调用点 | `push N` | 注解现值 | 判定 |
|---|---|---|---|---|---|
| `UIRoleSelectDialog` | `??0UIRoleSelectDialog@@QAE@XZ` | `CGameData::_init_44f8d0` | **0x89C = 2204** | 2300 | **注解多 96** ✗ |
| `CScreenMode` | `??0CScreenMode@@QAE@XZ` | `CUtil::InitGameSystems` | **0x1578 = 5496** | 5880 | **注解多 384** ✗ |

⇒ 这两个 `push N` 与 **`UIStatic=152`** 自洽，与 **248 矛盾** ✓；而 `248` 的"证据"是循环的 ✗。
（注意：`UITitle_ArcSave`/`JusticeBookUI` 的原生 ctor **只被 `??_G…`（scalar dtor）调用、无 `push`** ⇒
它们**从不被 `new`** ⇒ 任何"它们的分配尺寸"的说法都必须换锚 ✗。）

## 规则（补充）

- **凡"某符号属于某类"的判断，必须能追到一个编译器原生物**：
  `??0<Cls>@@` / `??1<Cls>@@` / `??_7<Cls>@@6B@` / 重整名里的类名 ✓ —— **不是** IDB 里的
  `?ctor@<Cls>@@…`（那是 `apply` 把注解写进 IDB 的结果 ✗）也不是匿名 `stru_` ✗。
- 若某个类**只被 `??_G…`（scalar deleting dtor）引用、没有 `push N` 的 `new` 点** ⇒
  **本次取证对它无效** ✓，必须明确写"该类的整对象尺寸本方法给不出" ✗，**不得**用别的类的 `push N` 顶上。
- 与本仓 R 系列纪律配合：**两侧冲突时（模型说 X、IDB 说 Y）先问"两边各自依赖谁命名"** ✓。
