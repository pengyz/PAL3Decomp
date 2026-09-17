# 归属误判扫描器：偏移链解析修复（勘误 + 结果）

**日期**：2026-09-17 · **前置**：`_cleanup_correction_misattribution_scan.md`、
`_cleanup_review_misattribution_scan_kiro.md`
**产物**：`tools/scan_misattribution.py`（重写）、`tools/test_scan_misattribution.py`（新，28 用例）、
`data/status/_scan_misattribution_v2.json`

---

## 1. 结论（先说结果）

| 项 | 修复前 | 修复后 |
|---|---|---|
| 候选（旧"类型不符"过滤后） | 1524 | **1524**（候选面不变）|
| 标记为"物理不可能" | **71**（去重 52）| **70**（去重 55）|
| 旧候选仍存活 | — | **24 / 52**（**28 个被证伪**）|
| 偏移链**经二进制真值校验** | 未做 | **84 吻合 / 0 不吻合** |
| 单元用例 | 0 | **28 全绿** |

**新增的第二类发现**：`callee_self_overflow` **42 行（11 个不同 callee）** —— callee
的访问跨度超过**它自己所属类**的 `binary_size`。这与调用点无关，是**callee 自身归属/
类尺寸**的矛盾，见 §4。

**对"批量重归属"这个方案的影响：结论不变（不可做），但理由被换掉了。**
原来的理由是"物理不可能有 71 个"；现在的理由是：残余 70 个**不是"函数归属错"**，
而是**成员/元素类型过小**（A 级证据见 §3）。两者要用完全不同的 fix。

---

## 2. 四个缺陷（全部有可复现证据）

### 缺陷 1 —— 偏移链不解析（**82% 的旧结论建立在此之上**）
旧正则 `(?:&?this->(m_\w+))` 只抓成员名，忽略 `[k]` / `.field` / `->field` 后缀。
于是 `&this->m_ShoesName.m_rect.bottom`（终值是个 `int`）被当成 `UIStatic`(152B)
去和 `CCBUI` 的访问需求(352B)比，判成"物理不可能"。

```
旧 71 个"物理不可能"里：带后缀 58 个（82%）、裸成员 13 个
```

### 缺陷 2 —— 无函数边界：盲目反汇编 `va .. va+0x400`
`UIWnd::GetWidth` 在 `0x0043FDC0`，**真实长度 13 字节**（`decomp/*.json` 的
`size_bytes`），函数体只有 `fildl 0x4(%esp); fstps 0x8c(%ecx); ret $0x4`，
即只访问 `+0x8c`(140)。旧实现却报 `need=244` —— 因为它把之后 60 多个**彼此只隔
16 字节**的小函数一起扫了进来。修法：用 `size_bytes` 界定，遇 `ret` 立即停。

### 缺陷 3 —— `%ecx` 活性判据写反
旧代码 `re.search(r'\bmov\s+%ecx\s*,', body)` 匹配的是 AT&T 里的**源**操作数
（`mov %ecx,<dst>` = 把 this 拷出去，**恰恰无害**），而真正致命的
`mov <src>,%ecx`（ecx 被覆盖）**完全没检测**。修法：改成 `,\s*%ecx`（目标操作数）
+ `pop %ecx`，且**先算本指令的读、再判覆盖**（`mov 0x8(%ecx),%ecx` 那次读必须算）。

### 缺陷 4 —— 指针数组元素步长错（由 §3 的验证器抓出）
`UIScrollBar::m_texarrayInfo` 声明是 `_PlugInfo *[10]`。每元素是 **4 字节指针**，
旧实现用了 `sizeof(_PlugInfo)=584`：`m_scrollbar.m_texarrayInfo[4]` 解析成 **2676**，
编译器真值是 **356**。

### 额外：`norm_va` 的 `.lstrip('0X')` 陷阱
`'0X004F3D90'.lstrip('0X')` = `'4F3D90'`（`lstrip` 按**字符集**剥离，连前导 `0`
一起吃掉）⇒ 查函数尺寸表**永远失败**，`need` 全变 `None`。旧代码靠 `int()` 侥幸
无事，新代码依赖字符串键就暴露了。已改整数键 + `norm_va()` 统一入口。

---

## 3. 偏移链解析器已被**二进制真值**校验

`python3 tools/scan_misattribution.py --verify-offsets`

做法：在 caller 的机器码里找 `call <callee>`，回溯 `%ecx` 的来源；若为
`lea X(%this),%ecx`，则 **X 必须等于解析出的 `member_off`**。

```
单点可判定：吻合 84，不吻合 0；多点需配对 128；无法判定 114
```

- 只对 **(caller, callee) 恰有一个调用点、且只有一个候选**的组合下结论 ——
  多调用点时集合级比较**不构成证据**（这正是缺陷 4 被发现后收紧的规则）。
- 修复缺陷 4 之前是 `84/4`；4 个不吻合**全部**是 `m_texarrayInfo` 同族。

### 调用点定谳示例（决定"是归属错还是类型错"）
`LineupUI::OnMessage` → `UIListBox::GetGridOffset`：
```
4782bc:	lea    0x1bcb4(%esi),%ecx     ← 对象内嵌在 LineupUI+0x1bcb4
4782c2:	call   0x43ebb0               ← UIListBox::GetGridOffset
43ebb4:	mov    0x45c(%ecx),%eax       ← callee 真的读 +0x45c(1116)
43ebbf:	imul   0x454(%ecx),%edx
```
声明链 `m_btnPar2[10][0]._x` 解析 = **113844 = 0x1bcb4**（与 `lea` 完全一致，说明
偏移链算法正确），但终值声明类型是 **`float`(4B)**。
⇒ **被调函数是它本身没错，错的是"声明类型太小"** —— 这是成员/元素类型缺陷，
**不是** `CalcSpeed` 那一型的函数归属误判。

---

## 4. 残余 70 的构成（诚实分类）

| 终值声明类型 | 行数 |
|---|---|
| 标量（`int`14 / `char`9 / `unsigned`8 / `float`6 / `long`3 / `DWORD`1）| **41** |
| 类名（`gbTexture`14 / `Actor`5 / `_PlugInfo`3 / `UIWnd`2 / 其余 7 种各 1）| 29 |

**41/70 是"标量字段的地址被当成类对象用"**：`&this->m_X`（`m_X` 声明 `int`）被
cast 成 `UIScene*`，callee 读 `this+0x5c`。含义是**该偏移上的存储其实是一个对象**，
声明类型写小了 —— 与 `CalcSpeed` 的推断同构，但结论指向**成员类型**而非函数归属。

**超出幅度**：中位 159B；`<=8B` 13 个、`9–32B` 5 个、`33–128B` 16 个、
`129–512B` 18 个、`>512B` 18 个。`<=8B` 那 13 个是**启发式噪声**的边界，不应单独当证据。

**分母可靠性核查**：`binary_size` 是"物理不可能"判据的分母，而 881 个类里有
**46 个（5%）**已知成员上界 > `binary_size`（`SceneMgr` 差 5.2MB、`Comp_DonateUI`
差 416KB…）。但**残余额度中 0/70** 的终值类型落在这 46 个类里 ⇒ **分母误差不影响
本次残余**。

### 4.2 `callee_self_overflow`（42 行 / 11 个 callee）—— 新的一类发现
callee 的访问跨度 > 它**自己所属类**的 `binary_size`：

```
UIWnd::GetWidth        need=144  UIWnd.size=68     x2
UIWnd::GetHeight       need=148  UIWnd.size=68     x2
UIWnd::GetPosition     need=152  UIWnd.size=68     x2
UIFrameWnd::SetPosition need=92  UIFrameWnd.size=72 x3
CCBFiveNimbusWindow::SetFloatParam need=296 类尺寸=160 x15
RenderTarget::SetState  need=584 RenderTarget.size=200
UISceneMap::GetSceneInfo need=1744 UISceneMap.size=1012
CCBSystem::GetThreadBase need=98336 CCBSystem.size=90840
```

`UIWnd::GetWidth/GetHeight/GetPosition` 实测分别写 `+0x8c/+0x90/+0x94`（140/144/148），
而 `UIStatic`(152) 恰好覆盖这三个偏移 —— 但它们被登记在 `UIWnd`(68) 名下。
**这是与调用点无关的、纯 callee 侧的归属矛盾。**

⚠️ **但 `binary_size` 不是权威值**：`UIWnd` 自己 `binary_size=68` 而成员上界已到
`+0x64`；`UIStatic` 152 而 `+0x96 m_text char[16]` 到 `0xA6`。所以"UIWnd 真的是 68 吗"
必须先独立确定，**不能**据此直接改方法归属。

---

## 5. 这对方案意味着什么（诚实结论）

- ✅ **扫描器现在可信**：偏移链经 84/0 真值校验，边界与活性判据可证伪地修好。
- ❌ **"统一扫描 + 批量重归属"依然不可做**，但**理由换了**：
  残余的主体是**成员/元素类型过小**（41 个标量）与 **callee 侧 self_overflow**，
  不是"方法声明在了错误的类里"。批量改归属会把成员类型缺陷误修成归属改动。
- ▶ **可独立推进的两条**（互不依赖）：
  1. **成员/元素类型修复**：对 41 个标量终值逐个取"调用点 `lea` + callee disp32"
     证据。**这会改 `known_members` 的 `type`**，与已有的 `+0x12`/`m_Sequen` 类
     偏移工作同一批。
  2. **`binary_size` 一致性**：46 个类成员上界 > `binary_size`，其中
     `UIWnd`/`UIStatic` 直接影响 6 行 `self_overflow`。先定 `binary_size` 权威性，
     再谈 `UIWnd::GetWidth` 归属。

---

## 6. 复现

```bash
python3 -m unittest tools.test_scan_misattribution -v        # 28 用例
python3 tools/scan_misattribution.py --limit 40              # 全量扫描
python3 tools/scan_misattribution.py --limit 0 --verify-offsets   # 偏移真值校验
```

旧产物 `data/status/_scan_misattribution.json`（1524 候选 / 71 不可能）**保留**，
作为对照基线。

---

## 7. 附：标量终值案例的调用点定谳（补 §3 缺少的例子）

§3 只给了**类名终值**（`UIParticle._x`）的例子，而残余主体是**标量终值**（41/70）。
补一个，把"`%ecx` 里到底是什么"直接摆在机器码上：

`PalScriptMgr::ShowTextBox(char const *)`（`0x00450BC0`，160B）：

```asm
450bc9: mov   %ecx,%esi          ; %esi = this (PalScriptMgr)
...
450c1d: lea   0x48(%esi),%edi    ; %edi = this + 0x48 (72)      ← 解析出的 member_off = 72
450c25: mov   %edi,%ecx          ; 第 1 个调用
450c2d: mov   %edi,%ecx          ; 第 2 个调用
450c35: mov   %edi,%ecx          ; 第 3 个调用
450c50: mov   %edi,%ecx          ; 第 4 个调用
```

`%edi = this+72` 与解析值**逐值相同**。而 `+0x48` 上的成员声明是 **`float m_fPosZ`(4B)**，
同一个地址被交给：

| callee | 体内 `[ecx+disp]` 最大 | need |
|---|---|---|
| `RoleCameraCtrl::SetName` | 72 | 76 |
| `UIScene::SetState` | 188 | 192 |

⇒ 该偏移上的存储是一个**≥192 字节的内嵌对象**，声明成 `float` 是错的；
同一个地址被两个不同类当 `this` 用，说明这些 callee 的 `this` 归属里
**至少有一个也是错的**。

### 反向例子（必须承认的噪声）
`Actor::UpdateFrame`：`this->m_dwMatMsg[6]` 解析 off=**564**，调用点
`lea 0x234(%ebp),%ecx` = 0x234 = **564** ✓；但 callee `ArcSceneMonster::CheckDistance`
只读 `+8`（need=12），而 `m_dwMatMsg` 是 `unsigned` 元素数组 ⇒ 多读 8 字节
**只是相邻数组元素**，属正常。
⇒ **`<=32B` 那 5 个（`<=8B` 13 个）是启发式噪声，不能单独当证据。**

### 由此得到的一个新判据（尚未落地）
**"同一地址被 ≥2 个不同类当 `this`"** 是一个不依赖尺寸、不易假阳性的信号：
它直接说明这些 callee 的归属互相矛盾。`PalScriptMgr+0x48` 就是一例
（`RoleCameraCtrl::SetName` vs `UIScene::SetState`）。在残余 70 里跑一遍，
命中 **2 组**：
```
00450BC0 +0x48  -> RoleCameraCtrl, UIScene
00451200 +0x350 -> UIListBox, UIProgressBar
```

---

## 8. 置信度分层（防止把"解析器可信"读成"残余结论可信"）

**不要把这两件事混为一谈：**

| 对象 | 证据强度 |
|---|---|
| **偏移链解析器**（`resolve_chain`）| **高**：84 个单点组合经调用点 `lea` 逐值校验，0 不吻合；28 个单元用例 |
| **残余 70 行"类型过小"这一判决** | **中**：依赖 `min_required_span` 启发式 + 声明类型比较，**只有 3 例做了人工定谳**（§3、§7）|

残余 70 行**自身**的调用点校验分布：

```
多点需配对 37 行   非 lea 装载 26 行   单点 lea 直接印证 7 行
```

（41 行标量终值里 36 行**算出了**常量偏移，但"算出常量偏移" ≠ "被二进制印证"。）

**⇒ 正确的说法是**：扫描器已经成为一个可信的**候选发生器**；
把它当**判决器**用之前，必须对每一行补"调用点 `%ecx` 装载 + callee 体内 disp32"
的逐案证据（§3/§7 就是范式）。`<=32B` 桶（18 行）按 §7 的反例应直接降级。