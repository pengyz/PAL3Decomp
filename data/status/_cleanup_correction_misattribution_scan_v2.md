# 归属误判扫描器：偏移链解析修复（含独立复核处置）

**日期**：2026-09-17 · **产物**：`tools/scan_misattribution.py`（重写）、
`tools/test_scan_misattribution.py`（42 用例）、
`data/status/_scan_misattribution{,_v2,_v3}.json`

**前置**：`_cleanup_correction_misattribution_scan.md`、
`_cleanup_review_misattribution_scan_kiro.md`
**独立复核**：`subagent-9`（kiro），两轮结论见 §5

---

## 1. 结论

| 项 | v1 旧实现 | v2（修 4 缺陷）| **v3（再修 3 缺陷）** |
|---|---|---|---|
| 工具默认输出候选数 | 1524 | 2196 | **2234** |
| 其中 `head_type_differs` 子集 | 1524 | 1524 | **1556** |
| 标记"物理不可能" | **71**（去重 52）| 70（去重 55）| **87**（去重 66）|
| 链不可解析 | — | 462 | **253** |
| 偏移链经二进制真值校验 | 未做 | 84 / 0 | **151 / 0** |
| 单元用例 | 0 | 28 | **42** |

- **v1 → v2**：4 个缺陷修复，28 个旧候选被证伪（占旧去重 52 的 54%）。
- **v2 → v3**：**独立复核抓出 3 个我漏掉的缺陷**（§5.1），其中"字段不查基类"
  一项就把 `impossible` 从 **70 抬到 87**（+24%）——**"70"不是终态**。
- v1 与 v3 的"物理不可能"去重后**共有 31 个**，即 **21 个旧结论被证伪**，
  v3 新增 35 个。
- 与方案的关系：**"统一扫描 + 批量重归属"仍不可做**，理由见 §7。

---

## 2. v1 的四个缺陷（每个都可复现证伪）

**缺陷 1 —— 偏移链不解析。** 旧正则 `(?:&?this->(m_\w+))` 忽略 `[k]`/`.field`/
`->field` 后缀。旧 71 个"物理不可能"里 **58 个（82%）带后缀**，于是
`&this->m_ShoesName.m_rect.bottom`（终值 `int`）被当成 `UIStatic`(152B) 去比
`CCBUI` 的需求(352B)。

**缺陷 2 —— 无函数边界。** 旧实现盲目反汇编 `va..va+0x400`。
`UIWnd::GetWidth`（`0x43FDC0`）真实长度 **13 字节**、只访问 `0x8c(%ecx)`=140，
旧实现报 `need=244` —— 因为它扫进了后面 60 多个**彼此只隔 16 字节**的小函数。
`decomp/*.json` 里本来就有真实 `size_bytes`（复核者用 objdump 独立核对 3 个函数，
逐条吻合）。

**缺陷 3 —— `%ecx` 活性判据写反。** 旧代码 `r'\bmov\s+%ecx\s*,'` 匹配的是 AT&T 的
**源**操作数（`mov %ecx,<dst>` = 把 this 拷出去，**无害**），而真正覆盖 ecx 的
`mov <src>,%ecx` **完全没检测**。修法：`,\s*%ecx`（目标操作数）+ `pop %ecx`，
且**先算本指令的读、再判覆盖**。

**缺陷 4 —— 指针数组元素步长错。** `UIScrollBar.m_texarrayInfo` 声明
`_PlugInfo *[10]`，每元素是 **4 字节指针**，旧实现用 `sizeof(_PlugInfo)=584`：
`m_scrollbar.m_texarrayInfo[4]` 解析成 **2676**，真值 **356**。

**附：`norm_va` 的 `.lstrip('0X')` 陷阱。** `'0X004F3D90'.lstrip('0X')` = `'4F3D90'`
（`lstrip` 按**字符集**剥离，连前导 `0` 一起吃掉）⇒ 查函数尺寸表永远失败、
`need` 全变 `None`。已改整数键。

---

## 3. v2 遗留、由独立复核抓出的三个缺陷（v3 已修）

### 缺陷 5 —— 字段查找不回溯基类（**影响最大**）
`resolve_chain` 处理 `.field`/`->field` 时只查 `S[cls]['members']`。
但 `UIStatic.m_bcreateok` 实际定义在**基类 `UIWnd`**，`m_nLoop` 等同理。

实测（我自己复现，非采信复核者的数字）：
```
                     候选      impossible   unknown_field
v2                   2196         70            462
v3（仅加基类查找）    2234         87            253
```
**87% 量级的"拒答"是工具能力不足，不是"annotation 缺失"。**

修法：`_find_member()` 沿 `bases[0]` 递归。**只沿主基类**——MSVC 单继承下主基类
子对象在偏移 0，成员偏移可直接沿用；**次要基类（`bases[1:]`）偏移未知，绝不猜**
（多继承时非主基类不在 0 偏移）。已加"次要基类必须查不到"的用例。

### 缺陷 6 —— `_ecx_sources` 不识别 `mov %reg,%ecx`
`this` 经寄存器传递（`mov %edi,%ecx`）时本可继续回溯，旧实现一律归为
`clobber`（覆盖）⇒ 把**本可判定**的调用点丢进"无法判定"堆，
**并让文档把这些数字全部归因于"必要的谨慎"**（这处归因不诚实，复核者指出后已改）。

修法：新增 `_this_regs()`（序言里 `mov %ecx,%r` 检测 this 别名，`%esi`/`%ebp`/
`%edi`/`%ebx` 都用过）+ `_trace_reg()`（有界回溯到 `lea X(%this),%reg`，遇 `call`
或寄存器被写即中断）。同时收紧：`lea X(%r),%ecx` 只当 `%r` 确实是 this 时才作数
——旧版会把 `lea X(%esp),%ecx`（**栈局部变量**）误当 this 偏移。

效果：真值校验覆盖 **84 → 151**，不吻合仍为 **0**。

### 缺陷 7 —— `parse_decl_type` 误读前缀/嵌套/模板
926 个类型串里：前缀关键字 15 个、嵌套 `::` 41 个、模板 33 个。
- `'const struct TypeDescriptor *'` → 旧抓出 `base='const'`；
- `'AStarPathFinder::NODE *'` → 旧抓出**外层类** `AStarPathFinder`
  （**尺寸是错的**，比漏判更危险）；
- `'std::vector<...>'` → 旧抓出 `'std'`。

修法：剥 `const/volatile/struct/class/enum/union`；含 `::` 或 `<` 一律
`base=None`（保守拒答，绝不用外层类冒充）；`sizeof_type` 对指针先返回 4。
复核者提到这些"目前未观察到已产生错误结果"——同意，属潜在风险，但仍已修。

---

## 4. 偏移链解析器已被**二进制真值**校验（151 / 0）

`python3 tools/scan_misattribution.py --limit 0 --verify-offsets`

在 caller 机器码里找 `call <callee>`，回溯 `%ecx` 来源；若为 `lea X(%this),%ecx`
（或经寄存器传递可回溯到它），则 **X 必须等于解析出的 `member_off`**。

```
单点可判定：吻合 151，不吻合 0；多点需配对 157；无法判定 119
```

- **不是循环论证**（复核者独立确认）：`resolve_chain` 的数据源是 annotation 的
  类型声明串，`_ecx_sources` 的数据源是 `objdump` 反汇编；两条独立路径。
- 只对 **(caller, callee) 恰有一个调用点、且只有一个候选**的组合下结论 ——
  多调用点必须先做表达式↔指令配对，集合级比较不构成证据（这正是缺陷 4 被发现后
  收紧的规则）。
- 收紧 `this` 寄存器判定后仍有 0 不吻合，说明原先 84 个 `lea` 都是真 this 相对寻址。

### 调用点定谳示例（区分"归属错"与"类型错"）
`LineupUI::OnMessage` → `UIListBox::GetGridOffset`：
```
4782bc: lea  0x1bcb4(%esi),%ecx     ← 对象内嵌在 LineupUI+0x1bcb4
4782c2: call 0x43ebb0
43ebb4: mov  0x45c(%ecx),%eax       ← callee 真的读 +0x45c(1116)
43ebbf: imul 0x454(%ecx),%edx
```
声明链 `m_btnPar2[10][0]._x` 解析 = **113844 = 0x1bcb4**（与 `lea` 一致），
终值声明类型是 **`float`(4B)** ⇒ **被调函数归属没错，是声明类型太小**
（`m_btnPar2` 是 `UIParticle[16][7]`，`_x` 在元素内 +136）。

---

## 5. 对独立复核（`subagent-9`）结论的逐条处置

| 复核主张 | 我的处置 |
|---|---|
| 缺陷 1/2/3/4 真实 | **证实**（我原本就是这么写的；复核者独立三重核对 `size_bytes`）|
| `--verify-offsets` 不是循环论证 | **证实** |
| **字段查找不回溯基类（缺陷 5）** | **证实并复现**：`impossible` 70→87。**已修** |
| **`_ecx_sources` 把 `mov %reg,%ecx` 误判为 clobber（缺陷 6）** | **证实**。**已修**，覆盖 84→151 |
| **`parse_decl_type` 误读 `const`/`struct`/`::`（缺陷 7）** | **证实**（真实数据里 15+41+33 个）。**已修** |
| "文档把 1524 当候选总数、具有误导性" | **部分成立**：表格该行原文写了"旧'类型不符'**过滤后**"，但**确实没有交代工具默认输出是 2196**。已在 §1 同时列出两个数 |
| "46 个类 `binary_size` 不自洽" | **口径差**：复核者算 44、我用当前规则算 **45**。差异来自"无法解析类型"的尺寸规则（±1 敏感）。**该指标不承载结论**，已给出可复算片段 |
| "文档说 28 用例、实际 31" | **时间差**：写文档时确为 28，其后又加了 14 个。现为 **42** |
| "§5.1'扫描器现在可信'过度推广" | **接受**。已新增 §6 置信度分层，明确"候选发生器"与"判决器"的区别 |

### 复核者自身的一处过度表述
我把"无法判定 114"归因于"必要的谨慎"确属**归因不完整**（已改）；
但复核者称 §1 表格"**直接矛盾**/相差 44%"的措辞强于事实——原文该行已标注
"过滤后"。真正的问题是**没写出默认总数**，已补。

---

## 6. 残余 87 的构成（诚实分类）

| 终值声明类型 | 行数 |
|---|---|
| 标量（`int`/`char`/`unsigned`/`float`/`long`/`DWORD`）| **48** |
| 类名（`gbTexture`/`Actor`/`_PlugInfo`/`UIWnd`/…）| **39** |

**超出幅度**（callee 需求 − 声明尺寸）：中位 **188B**；
`<=8B` 14、`9–32B` 5、`33–128B` 20、`129–512B` 25、`>512B` 23。
按 §9 的反例，**`<=32B` 那 19 个是启发式噪声**，不能单独当证据。

**分母可靠性**：`binary_size` 是判据分母，881 个类里 **45 个**成员上界 > `binary_size`。
但**残余额度中 0/87** 的终值类型落在这 45 个类里 ⇒ **分母误差不影响本次残余**。

### 6.2 `callee_self_overflow`（42 行 / 11 个 callee）—— 与调用点无关的一类
```
CCBFiveNimbusWindow::SetFloatParam need=296  类尺寸=160   x15
CCBAttackSequen    ::SetPause       need=457  类尺寸=456   x9
UIPushButton       ::SetAnimOffset  need=256  类尺寸=252   x5
UIFrameWnd         ::SetPosition    need=92   类尺寸=72    x3
UIWnd              ::GetHeight      need=148  类尺寸=68    x2
UIWnd              ::GetPosition    need=152  类尺寸=68    x2
UIWnd              ::GetWidth       need=144  类尺寸=68    x2
UIFrameWnd         ::SetFrameParam  need=152  类尺寸=72    x1
RenderTarget       ::SetState       need=584  类尺寸=200   x1
CCBSystem          ::GetThreadBase  need=98336 类尺寸=90840 x1
UISceneMap         ::GetSceneInfo   need=1744 类尺寸=1012  x1
```

**其中 `UIWnd::GetWidth/GetHeight/GetPosition` 已定谳（§9）**：
`sizeof(UIWnd)=68`，而三者写 `+140/+144/+148` ⇒ **写在自身对象之外，
`UIWnd` 归属必然有误**。

> **勘误（本轮自查）**：本节初稿曾写"`UIWnd` binary_size=68 但成员上界 `+0x64(100)`；
> `UIStatic` 152 而 `m_text char[16]` 到 `0xA6`"——**错的**。成因：临时脚本对
> `known_members` 的键调了 `norm_va()`，而 **9837/9849 个键是十进制无前缀**
> （仅 51 个带 `0x`），把十进制当十六进制读放大了偏移。用 `load_structs()` 的正确
> 规则重算：`UIWnd` 上界 **= 68 = binary_size**；`UIStatic` **= 152**，**都自洽**。
> 已加回归用例 `TestMemberKeyRadix`。**扫描器代码未受污染**（`norm_va` 只用于 VA）。

---

## 7. 这对方案意味着什么

- ✅ **扫描器现在是可信的候选发生器**：偏移链 151/0 真值校验、42 用例、
  7 个缺陷全部有可复现证据。
-  **"统一扫描 + 批量重归属"不可做** —— 理由换了：残余主体是
  **成员/元素类型过小**（48 个标量）与 **callee 侧 self_overflow**，
  不是"方法声明在了错误的类里"。批量改归属会把成员类型缺陷误修成归属改动。
- ⚠️ **"87"也不是终态**：v2→v3 已证明每修一个结构性缺陷数字就会变。
  在下游任何批量工作之前，必须先固定扫描器（本轮已固定 7 个缺陷）。

---

## 8. 复现

```bash
python3 -m unittest tools.test_scan_misattribution -v            # 42 用例
python3 tools/scan_misattribution.py --limit 40                  # 默认输出 2234
python3 tools/scan_misattribution.py --limit 0 --verify-offsets  # 151/0
```

v1 产物 `_scan_misattribution.json` 与 v2 产物 `_scan_misattribution_v2.json`
**保留**作为对照基线。

---

## 9. 附录：调用点定谳

### 9.1 标量终值（补 §4 缺的例子）
`PalScriptMgr::ShowTextBox(char const *)`（`0x00450BC0`，160B）：
```asm
450bc9: mov   %ecx,%esi          ; %esi = this (PalScriptMgr)
450c1d: lea   0x48(%esi),%edi    ; %edi = this + 0x48 (72)  ← 解析值 = 72
450c25: mov   %edi,%ecx          ; 第 1 个调用
450c2d: mov   %edi,%ecx          ; 第 2 个
450c35: mov   %edi,%ecx          ; 第 3 个
450c50: mov   %edi,%ecx          ; 第 4 个
```
（`%esi` 在本函数内**只被写两次**：`450801` 读全局、`450825`。）
`+0x48` 的成员声明是 **`float m_fPosZ`(4B)**，同一地址被
`RoleCameraCtrl::SetName`（体内最大 disp 72 ⇒ need=76）与
`UIScene::SetState`（188 ⇒ need=192）两个不同类当 `this` 用。
⇒ 该偏移是 **≥192 字节的内嵌对象**，声明成 float 是错的。

### 9.2 反向例子（必须承认的噪声）
`Actor::UpdateFrame`：`this->m_dwMatMsg[6]` 解析 off=**564**，调用点
`lea 0x234(%ebp),%ecx` = **564** ✓；但 `ArcSceneMonster::CheckDistance` 只读 `+8`
（need=12），而 `m_dwMatMsg` 是 `unsigned` 元素数组 ⇒ 多读 8 字节只是**相邻数组
元素**，正常。⇒ `<=32B` 桶是噪声。

### 9.3 `UIWnd::GetWidth/GetHeight/GetPosition` 归属定谳
1. 三者是 `fstps` 浮点存储到 `+0x8c/+0x90/+0x94`；`sizeof(UIWnd)=68`
   ⇒ UIWnd 归属必错。
2. `UILoadingFrm::InitFullScreen`：`4507f6 mov %ecx,%edi`（`%edi=this`）→
   `450825 lea 0x48(%edi),%esi` → 调用点 `%ecx = this+72`。
3. ~~`UILoadingFrm+72` 是 **`m_LoadProgress : UIProgressBar`（内嵌）**，
   其下一成员 `m_anitime` 在 **+316 = 72+244**，与 `UIProgressBar.binary_size=244`
   精确吻合。~~ **❌ 这一条已被 §10 证伪**（`sizeof(UIProgressBar)` 实际 ≥308）。
4. `CCBUI_SetupAIWindow` 调用点 `0x516c93 mov 0x42c(%esi),%ecx`，而 `CCBUI+1064`
   是 `m_pRoleStateGP : UIProgressBar *[4]` ⇒ `+1068=[1]` 是 `UIProgressBar *`。

⇒ 宿主收敛到 **`UIProgressBar`**（§10 用 vtable 锚点进一步确认）。
**但仍不能改归属**，理由见 §10 —— 比原来判断的严重得多。

未解析调用者：`UITitle_XJTM::UpdateMonsterEntry`（0x487cfa），
该类注解里没有 `UIProgressBar` 成员。

---

## 10. 消歧结论：`UIProgressBar` 布局注解在 +152 之后**与二进制不符**

**任务**：判定 `+140/144/148` 是 float 还是 `BYTE`/`gbColorQuad`，以便给
`UIWnd::GetWidth/GetHeight/GetPosition` 定宿主。

### 10.1 归属锚点（确证）
`UIProgressBar.json` 的 `vtables` 声明 `{"addr":"0x0056AC20", base:"UIWnd"}`，
而 `0x439030`（注解里的 `UIProgressBar::ctor`）在 `43909d` 执行
`movl $0x56ac20,(%esi)`，且全二进制只有 `43909d`/`43914d` 两处安装它。
`439048 mov %ecx,%esi` ⇒ `%esi = this`（偏移 0 写 vtable 更证其是对象起点）。
⇒ **`0x439030` 确为 `UIProgressBar::ctor`。**

### 10.2 `sizeof(UIProgressBar)` ≥ **308**，而 `binary_size = 244`
该 ctor 初始化的成员偏移（全部 `%esi` 相对）：
```
0xec(236) 0xf0(240,byte) 0xf4(244)=0x62 0xf8(248) 0xfc(252)
0x100(256) 0x104(260) 0x108(264) 0x10c(268) 0x110(272)
0x114(276)=1.0f 0x118(280)=1.0f 0x11c(284)=1.0f
0x120(288) 0x124(292) 0x128(296) 0x12c(300) 0x130(304)
```
`0x44(68)` 也被清零（= `m_mode` ✓）。**构造一个 244 字节的对象却初始化到 +304
不可能** ⇒ **`binary_size=244` 是错的，真实尺寸 ≥308**。
（且 `%eax = 0x3f800000` 存到 +276/280/284 ⇒ 那三处是 **float 1.0f**，
注解在这三个偏移**没有任何成员**。）

### 10.3 `FindChildByName` 证明 +152 之后声明全错
`0x43FDF0`（`UIProgressBar::FindChildByName`，159B）内 **`%ecx` 一次都没被写过**
（逐条核对 44 条指令，无 `,%ecx`/`pop %ecx`）⇒ 下列访问**全部作用在 `this`**：

| 指令 | 偏移 | 真实访问 | 注解声明 | 判定 |
|---|---|---|---|---|
| `flds 0x7c(%ecx)` | +124 | float | `m_tradius float` | ✅ |
| `fmuls 0x80(%ecx)` | +128 | float | `m_bradius float` | ✅ |
| `mov 0x78(%ecx),%eax` | +120 | dword | `m_rradius int` | ✅ |
| `fsts 0x74(%ecx)` | +116 | **float** | `m_lradius int` | ️ 宽度同、类型异 |
| **`flds 0x98(%ecx)`** | **+152** | **float** | `m_pbk gbTexture *` |  |
| `fmuls 0x6c(%ecx)` | +108 | float | `m_stepval float` | ✅ |
| **`fstps 0x9c(%ecx)`** | **+156** | **float** | `m_pbkInfo _PlugInfo *` | ❌ |
| **`fildl 0xf0(%ecx)`** | **+240** | **int** | （无成员）| ❌ |
| **`movb $0x1,0xed(%ecx)`** | **+237** | **byte** | （无成员）| ❌ |
| `mov %dl,0xee(%ecx)` | +238 | byte | （无成员）| ❌ |
| **`mov %dl,0xa0(%ecx)`** | **+160** | **byte** | `m_ppic gbTexture *` | ❌ |

⇒ `UIProgressBar` 的 `known_members` **从 +152 起就与二进制不符**：
三处声明成**指针**的偏移实际是 **float/byte**，且 +236/+237/+238/+240/…/+304
的成员**根本没登记**。

### 10.4 所以 `+140/144/148` 的答案
三个访问器是 `fstps` **4 字节 float 存储** ⇒ 那些偏移上**就是 float**。
`UIProgressBar` 在那里声明 `BYTE`/`gbColorQuad`/`gbColorQuad`
（`fstps` 不可能落进 1 字节成员）⇒ **该处声明也是错的**。

**结论：宿主确实是 `UIProgressBar`，但不能靠"改归属"落地** —— 它的布局注解
（`known_members` +152 起、`binary_size`）本身要先重建。
**归属修正与布局重建是同一件事的两面，必须先做布局。**

### 10.5 顺带修正两处口径
- §6 "45 个类成员上界 > `binary_size`" **低估了问题**：该统计只能看到**已声明**
  成员；`UIProgressBar` 的越界是靠 **ctor 写入了未登记的偏移**才暴露的。
  真正的"`binary_size` 不可靠"范围比 45 更大。
- §9.3 原第 3 条（`m_anitime@316 = 72+244` 佐证 244）**已证伪**：
  244 是错的，所以 `UILoadingFrm` 的 `+72` 槽位算术同样可疑
  （`UISceneFace` 的 `m_hp@68`/`m_mp@312` 也隐含 244 —— 两处注解可能来自
  同一个错误来源，例如 PAL3A 的 PDB）。

### 10.6 下一步（已可执行、且有明确证据边界）
1. **重建 `UIProgressBar` 布局**：以 ctor 初始化序列 + `FindChildByName`/
   `Render`/`Destroy` 的 `%ecx` 访问为证据，逐偏移登记成员与宽度；
   `binary_size` 改为实测下界（≥308）并继续用其他方法确认。
2. 布局定下来后，`+140/144/148` 的 float 成员与
   `0x43FDC0/D0/E0` 三个访问器的函数名/归属一并落地。
3. 再走完整管线（apply → annotation_diff → codegen → compile_regression →
   probe → match），给出 `ok`/`L1` 的 Δ。