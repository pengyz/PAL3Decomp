# 「归属错 11 条」取证开工（2026-09-19，§49.4 第 (2) 项）

> 来源：`data/status/_structural_contradictions.json` 中 `verdict=attribution_wrong` 的 11 条
> （7 个类）。本文只记**方法**与**当前线索**，不含任何 annotation 改动。

## 1. 清单（11 条 / 7 类）

| 类 | 注解 size | 成员数 | 成员最大偏移 | 涉事函数 |
|---|---|---|---|---|
| `CEffectSystem` | 344 | 14 | 340 | `0x004C5DE0`、`0x004C5DB0` |
| `CIniFile` | 8 | 2 | 4 | `0x00504240`、`0x004EC700`、`0x00504130` |
| `RenderTarget` | 200 | 39 | 196 | `0x0048F3A0`、`0x004867F0` |
| `UIAnimateCtrl` | 164 | 8 | 160 | `0x00479260` |
| `UIWnd` | 68 | 11 | 64 | `0x00525080` |
| `_Texture_uv` | 8 | 2 | 4 | `0x004C5B90` |
| `gbRefObject` | 8 | 2 | 4 | `0x004CDAE0` |

**共同形态**：这几个类的**成员模型是完整的**（末成员 + 4 ≈ binary_size，handoff §48 的判据），
所以矛盾不该由"改尺寸"消解 —— 是**这些函数不属于该类**。

## 2. 方法（不能用启发式，经验教训都在库里）

项目已逐个证伪过三条启发式（成员名投票 273 假阳性、`// ecx` 首局部 360、首个指针 `// ecx` 32，
见 `_cleanup_vtable_class_reconcile.md` §46.3 与 `gotcha_member_name_voting_is_confounded_by_transitive_access.md`）。
本项要求的证据是 CLAUDE.md 明写的：

> **必须有 decomp member access evidence**：函数内 `this->member` 引用的成员
> 在**目标类中存在**、且**不在原类中存在**。

因此取证的可靠形态是**结构性的**，而不是名字投票：

1. 取该函数在 `this` 上访问的**偏移集合**（decomp 或 asm 皆可；asm 更硬）；
2. 在候选类里找**偏移边界恰好对上**的类（成员起始偏移 == 被访问偏移，或
   被访问偏移落在**有名字的成员**内，且该类的其余访问点也都对得上）；
3. 反向确认：这些偏移在**原类里没有对应成员**（原类的成员表已完整，所以"没有"是可判定的）；
4. 有**数组步长**信号时优先用它（stride = sizeof(元素类型)，比单点偏移强得多）。

## 3. 第一条线索：`CIniFile` 的 3 个函数都不是 CIniFile 的方法

三个函数的反编译（`asm/pal3/decomp/CIniFile_*_00*.json`）都长这样：

```c
CIniFile v7;                      // 栈上真正 8 字节的 CIniFile
CIniFile::CIniFile(&v7);          // ← 用对了类型（注解完整，所以能正确构造）
CIniFile::OpenFileRead(&v7, "datascript\\combat.ini");
v3 = this + 2522;                 // ← 但 this 是"另一个大对象"
...
v3->m_fp = v6;  v3 = (CIniFile*)((char*)v3 + 8);   // 8 字节步长的 CIniFile 数组
```

* `0x004EC700`（`LoadData`）：`this + 2522` 起按 **8 字节步长**操作 `CIniFile` 数组（stride 证据）；
* `0x00504240`（`LoadFullConfig`）：`*((_DWORD *)this + 123)` = `this + 492`；
* `0x00504130`（`LoadStructuredConfig`）：`(float *)this + 1147` = `this + 4588`。

⇒ 宿主类必须在这三个偏移上有成员（其中 +2522 处是 `CIniFile[N]`）。
下一步：在 struct 注解里按**偏移边界精确匹配**（不是"覆盖"）这三个偏移，
并检查语义侧证据（这三个函数围绕 `datascript\cbCam.ini` / `combat.ini`、
`g_CCBCamControlData`、`g_dwGameFlags` 工作 ⇒ 与 CCB（战斗）配置相关）。

> ⚠️ 本轮我第一次尝试用"成员区间覆盖该偏移"来筛宿主类，**失败**：覆盖判据太松，
> 每次命中上百个类（大类的无类型空洞会覆盖任意偏移）。必须收紧为
> **成员起始偏移 == 被访问偏移**，或**数组步长 == 元素类型尺寸**。

## 4. 关键方法修正：decomp 的 `this + N` **不能**当字节偏移用

Hex-Rays 的 `this` 类型来自**注解**；函数被错误归属时，`this` 类型就是错的，
于是 `this + N` 按**错误的元素尺寸**缩放。实测 `sub_4EC700`：

* decomp 写 `v3 = this + 2522;`（`this` 是 `CIniFile *`，sizeof=8）⇒ 真实字节偏移 **2522×8 = 20176 = 0x4ED0**；
* asm 独立确认：该函数访问 `[ebp+4ED0h]`、`[ebp+505Ch]`、`[ebp+204h]` ✓ —— 与 0x4ED0 完全对上。

⇒ **归属取证必须读 asm 的 `[reg+imm]`**（无歧义字节偏移）。
`_structural_contradictions.json` 里那批 `max_offset` 数字对"指针算术"形态是**元素下标**而非字节，
引用时要按 asm 复核（结论方向不变：都远大于原类尺寸，但数字含义要改口）。

## 5. 第一条定案：`0x00504240` 属于 **`CCBStage`**（原注解：`CIniFile::LoadFullConfig`）

新工具 `tools/attribution_offset_match.py`：逐指令跟踪"此刻哪个寄存器装的是 this"（前向覆盖感知），
取 asm 字节偏移，再与每个注解类的**成员起始偏移**做**精确**匹配打分。

| 候选类 | 精确命中 | 成员内命中 |
|---|---|---|
| **`CCBStage`**（size 673988） | **7/7** | **7/7** |
| `tagPAL3GameState`（672） | 6/7 | 6/7 |
| `CameraCtrl`（4088） | 4/7 | 6/7 |
| 其余类 | ≤4/7 | ≤6/7 |

`sub_504240` 的 7 个访问偏移**逐个落在 `CCBStage` 的具名成员起始处**，且类型与访问宽度一致：

```
0x1C4 m_fRotPitch(float)   0x1C8 m_fRotYaw(float)     0x1D0 m_fTimeAccum(float)
0x1EC m_ActionAngles(float)0x1F0 m_fTurnDelay(float)  0x1F4 m_nActionTimer(int)
0x11E8 m_TurnBuffer(int)
```

**"不在原类中"的确认**：`CIniFile` 只有 `m_fp`@0 与 `m_bRead`@4，上述成员**一个都不存在** ✓。
语义也吻合：该函数读 `datascript\cbCam.ini`，写入的正是"转动/相机"一族字段（pitch/yaw/action angle/turn buffer）。

⇒ 该条按 `reattribute` 入批：`CIniFile → CCBStage`（保留名字 `LoadFullConfig`，`name_evidence` 说明依据）。

**另两条待续**：`0x004EC700`（访问 0x204/0x4ED0/0x505C）暂无任何类能达到 >1/3 精确命中；
`0x00504130` 的 this 寄存器跟踪未成功（0 个偏移）。两者都留待下一轮换更强手段
（例如用 `0x4ED0` 与 `0x505C` 的差、或从调用点反查 `this` 的真实来源）。

## 6. 第 2、3 条定案 + 三条一起落盘并验证（本轮实测）

用同一工具扫其余 8 个函数，`CEffectSystem` 的两条给出**唯一且远高于次优**的候选：

| 函数 | 原注解 | 访问偏移（asm 字节） | 结论 |
|---|---|---|---|
| `0x004C5DB0` | `CEffectSystem::GetThreadHandle` | `0xC` `0xD` `0x3A020` | **`CEffect` 3/3 精确**（次优 `tagEffObj`/`tagPartical` 2/3） |
| `0x004C5DE0` | `CEffectSystem::ReleaseParticle` | `0x3C020` `0x3C024` | **`CEffect` 2/2 精确**（次优 0/2） |

命中的成员名与访问宽度/动作完全自洽：
`+0xC m_bActive(u8)`、`+0xD m_bVisible(u8)`、`+0x3A020 m_nQ2PIndex(int[2048])`
（循环 0x800 次 × 4 字节 = 0x2000 ✓）、`+0x3C020 m_pTexture(gbTexture*)`、`+0x3C024 m_pTextureArray(gbTextureArray*)`。
`CEffectSystem` 成员止于 `+0x154`（size=344）⇒ **"不在原类中"成立**。
两条原名（`GetThreadHandle` / `ReleaseParticle`）均与函数体无关，已证伪，按逻辑改名为
`Activate` / `ReleaseTextures`。

**三条一起落盘（`--run-pipeline`）结果**：

| 指标 | 前 | 后 |
|---|---|---|
| S2 | 70/201 | **71/201**（`Effect/ScreenEffect.cpp` fail→ok） |
| matched | 222/256 | **225/259** |
| **L1** | 21 | **21** |
| new_failures | — | **0** |

⇒ 验证清单全过，且**首次正向**（前两条尺寸修正为中性）。

**仍未定案**：`0x0048F3A0`/`0x004867F0`（RenderTarget，前者 4 个偏移无明确赢家，后者 82 个偏移里
`SceneMgr` 成员内 82/82 但精确仅 13/82 ⇒ 需要 stride 判据）、`0x00479260`（UIAnimateCtrl，this 跟踪失败）、
`0x00525080`（UIWnd，仅 1 个偏移 0x1490 命中 `PalScriptMgr`，弱证据）、`0x004C5B90`（_Texture_uv，this 跟踪失败）、
`0x004CDAE0`（gbRefObject，5/6 精确但三个类并列 ⇒ 需 stride 判据）。

## 7. 第 9 轮：严格判据给出**干净的反例**，并查出评分表本身的两处偏差

### 7.1 `--strict`（要求**全部**访问偏移都精确命中成员起始）的结果

```
sub_4CDAE0 (gbRefObject)     访问 0x8 0xC 0x10 0x14 0x60 0x92C   → strict 命中 0 个类
sub_48F3A0 (RenderTarget)    访问 0x4 0x378 0x38D 0x323CC        → strict 命中 0 个类
sub_525080 (UIWnd)           访问 0x1490                          → PalScriptMgr 1/1（唯一，但仅 1 个偏移 ⇒ 证据太弱，不落盘）
```

**正确解读**（已写进工具文档）：strict 返回空 ⇒ "**没有单个注解类的成员模型能覆盖这些偏移**"，
**不等于**"这些函数没有归属"。两种可能：
(a) 目标类的成员表在这些偏移上不完整（未标注）；
(b) **同一函数里 `this` 寄存器被复用去指另一个对象**，多个偏移本就不属于同一对象 ——
本工具的逐指令跟踪只能缓解，根治需要**逐访问的对象溯源（dataflow）**。

### 7.2 自查发现：评分表"成员内"一列会被高估

末成员的跨度按 `binary_size` 兜底 ⇒ "落在大类最后一个成员之后"的偏移也被算成"成员内"，
这解释了 `SceneMgr` 在 `0x4867F0` 上"成员内 82/82 而精确仅 13/82"的假象。
**⇒ 只有"精确命中"一列可作判据**，"成员内"仅用于同分辅助排序。工具文档已加醒目提示。

### 7.3 顺带确认：`UIManager` 的全局实例在 IDB 里类型正确

`asm/pal3/ida_structs.json` 的 `_globals['0xc11758'] = {name: unk_C11758, type: UIManager}`，
且前一个全局是 `0xc11754 g_pCombatRole (int)` —— 说明注解→IDB 的类型链路是通的。
`UIManager` 的**上界仍未取到**：它的初始化函数 `sub_41F5E0` 只写 +4/+8/+0xC（无 memset、无 vtable 安装），
数据区里 `0xC11760`（= +8）又被别的函数按绝对地址访问（说明它是本对象的成员，不是独立全局），
其后是 `dd 449h dup(?)` 的无类型区。⇒ **本轮按纪律不猜、不落盘**，只记录下界 ≥ 0x44。

## 8. 第 9 轮续：第 4 条定案（`0x004C5B90` → `CEffectSystem`）与一条新的取证形态

工具"0 个偏移"的两个函数改用**手工读函数体**后各有着落，其中一条直接定案：

### 8.1 `0x004C5B90`：`_Texture_uv::operator=` → **`CEffectSystem::SetEffectVisible`**（已落盘）

```
mov eax, [esp+arg_0]        ; 索引
mov esi, ecx                ; this
push eax ; call sub_4C5940  ; 索引规范化
mov ecx, [esi+eax*4+118h]   ; this->m_pEffect[idx]      ← CEffectSystem: known_members['280'] = m_pEffect, CEffect *[8]
mov dl,  [esp+4+arg_4]      ; 传入的字节
mov [ecx+0Dh], dl           ; effect->m_bVisible = 字节   ← CEffect: known_members['13'] = m_bVisible, unsigned char
```

**这是本项最强的一种证据形态**：一条指令链把**两个类的具名成员**串起来
（宿主类的指针数组 + 被指类的字节成员），两端类型都与指令形态吻合。
原类 `_Texture_uv`（size 8，成员只有 `u`@0/`v`@4）两端都不可能有。
**验证**：落盘后 S2 `71/201`、matched `225/259`、L1 `21`、`new_failures 0`（中性）。

**搬类必须连签名一起修**（本次踩到）：`reattribute` 只搬 `methods[addr]`，签名留在原类，
于是生成头出现 `static struct _Texture_uv & SetEffectVisible(_Texture_uv *);`
（既错类型又退化成 `static` 自由函数）。已按 asm 改正为
`void __thiscall CEffectSystem::SetEffectVisible(int nIndex, unsigned char bVisible)`
（`retn 8` ⇒ 两栈参；字节存储 ⇒ 第二参为字节；无返回值），改后生成头
`void SetEffectVisible(int nIndex, unsigned char bVisible); // 0x004C5B90`（CEffectSystem.h 行 43），
验证同样中性。工具已加 `set_signature` 种类 + "`__thiscall` 必须带 `::`"的护栏。

### 8.2 `0x00479260`：仍未定案，但拿到了强签名

`sub_479260` 本体：`idx ∈ [0,10]` 时 `eax = [ecx + 632*idx + 0xC2F80]`（`lea edx,[eax+eax*4] ;
shl edx,4 ; sub edx,eax` ⇒ 79×idx，再 `*8` ⇒ **632 字节步长**，基址 **+0xC2F80**）。
但**没有任何注解类在 `0xC2F80` 上有成员**（精确搜索为空）⇒ 宿主类的成员表在该区间不完整，
无法在本轮定案。下次可用"632 字节步长 + 该数组元素内部的字段偏移"反向匹配元素类型。
（第 10 轮复核：覆盖 `0xC2F80` 的类共 8 个，最接近的是 `ARC_PAL_GDB` 的
`m_ComboData ARC_ComboAttack[10]`@+0xC2F60（元素尺寸恰为 **632**），但 `0xC2F80` 落在该数组
**第 0 个元素内 +0x20 处**、并非元素起始 ⇒ 不构成对齐证据，**仍不改**。）

## 9. 第 10 轮：第 5 条定案（`0x00525080` → `PalScriptMgr`）与 `sub_4CDAE0` 的新线索

### 9.1 `0x00525080`：`UIWnd::_todo_525080` → **`PalScriptMgr::Get_m_nField_1490`**（已落盘）

本体只有两条指令：`mov eax,[ecx+1490h] ; retn` ⇒ `return this->[0x1490]`。
`UIWnd` 的 size=68（成员止于 +0x44）不可能有 `+0x1490`；而**全部 894 个注解类里唯一**
在 `+0x1490` 上有成员的是 `PalScriptMgr`（size=9512）的 `m_nField_1490`（`int`），
与 4 字节读精确吻合。一元访问器 ⇒ 单个偏移即完整证据。
**验证**：S2 `71/201`、matched `225/259`、L1 `21`、`new_failures 0`（中性）。

### 9.2 `sub_4CDAE0`（原注解 `gbRefObject`）的新线索：数组基址是 **+0x58** 而非 +0x60

手工读函数体后修正了工具给出的偏移集合（工具此前把循环里的 `[esi+..]` 也算进来了）：

```
mov ecx,[edi+10h] / [edi+14h] / [edi+8] / [edi+0Ch]  → 四次 gbRefObject::Release()   ← 4 个指针成员
lea esi,[edi+60h] ; mov ebx,20h                     → 循环 32 次
  mov al,[esi-8] ; test/jz        ← 元素首字节（相对 [esi-8]）
  mov al,[esi-7] ; test/jnz       ← 元素第二字节
  mov ecx,[esi] ; call [eax+0Ch]  ← 元素内的指针，取 vtable[3] 调用
```
⇒ **数组基址 = this+0x58**，元素数 32，元素内至少 3 个字段（2 个 bool + 1 个带 vtable 的指针）。
下一轮按"**成员起始 == 0x58 且为 32 元素数组**"去筛宿主类（0x60 是 `[esi]` 的位置，别再用它）。

## 10. 第 11 轮：`sub_4CDAE0` 的完整循环结构 —— **指向 `CEffMgr` 但不构成证据，故不落盘**

继续读完函数体，拿到两个循环的**步长与计数**（这是本项目里少见的强结构信号）：

```
mov ecx,[edi+10h]/[edi+14h]/[edi+8]/[edi+0Ch] → 4 次 gbRefObject::Release()   ← 4 个引用成员
lea esi,[edi+58h] + 0x08 = edi+60h ; mov ebx,20h                              ← 首元素在 +0x58，计 32
   mov al,[esi-8] / [esi-7] / mov ecx,[esi] ; call [eax+0Ch]                  ← 元素内 +0,+1,+8 三个字段
   add esi, 48h ; dec ebx ; jnz                                               ← **步长 0x48 = 72**
lea esi,[edi+92Ch] ; mov edi,800h                                             ← 第二个循环：基址 +0x92C，计 2048
   mov al,[esi-4] ; test/jz ; mov ecx,[esi] ; ...                             ← 元素内 -4、+0
```

**为什么看起来像 `CEffMgr`**（三重巧合）：
1. `CEffMgr` 在 +8/+0xC/+0x10/+0x14 正好是 4 个 `gbRenderEffect *`（`m_pAdditiveBlendNoZ`/`m_pAlphaBlendNoZ`/
   `m_pAdditiveBlend`/`m_pAlphaBlend`），与 4 次 `Release()` 一一对应；
2. `CEffMgr` 有 `m_EffClass tagEffClass[32]`@+0x1C，**元素数 32 与第一个循环的计数完全相同**；
3. `m_EffTable`@+0x91C 与第二个循环的基址 +0x92C 只差 16 字节，**计数 2048 正对应历史上
   `tagEffObj[2048]` 的读法**（CLAUDE.md 记载过这条注释从 `tagEffObj[2048]` 改成 `_BYTE[584]`）。

**为什么仍不落盘（判据没过）**：
* 循环步长 **72** 与 `tagEffClass` 的当前模型（**元素 4 字节**，32×4=128=0x9C−0x1C 与 CEffMgr 下一成员
  `m_fEffParam`@+0x9C 严丝合缝）**互相矛盾** —— 要么 `m_EffClass` 的元素类型/尺寸是错的，
  要么这里的 `this` 根本不是 `CEffMgr`；
* `+0x58` 处**没有任何注解成员**；第二个循环 2048 次也放不进 `_BYTE[584]`。

⇒ 按"禁止猜测性修改"，本轮**记录不动手**。要定案需要先解决其中之一：
(a) 查 `tagEffClass` 的真实尺寸（找它的构造/数组步长，同 §7.1 的两侧夹逼法）；
(b) 看 `m_EffTable` 的真实元素类型与 `_BYTE[584]` 的由来（CLAUDE.md 提到过那次改动的原因）。
两个都属 `CEffMgr` 自身的布局问题，可能牵出比归属更值得修的东西。

## 11. 第 13 轮：`sub_504130` 手工读出的结构 —— 它很可能**不是成员函数**

工具对它长期报"0 个偏移"。手工读 asm（行 392991-393083）后拿到真相：

```
mov esi, ecx                     ; this
lea ecx,[esp+24h+var_14] ; call CIniFile::CIniFile        ← 栈上真 CIniFile
... OpenFileRead("datascript\cbCam.ini") / ReadStart / ReadSection
sprintf(Buffer, "EditorCam%d", k)
lea ecx,[esi-4]  ; push … ; call CIniFile::ReadLine(char const*, float*)
push esi         ;                 call CIniFile::ReadLine(char const*, float*)
lea edx,[esi+4] / [esi+8] / [esi+0Ch] / [esi+10h] ; … call ReadLine
```

⇒ 它把 **`&this[-4]`、`this`、`&this[+4]`、`&this[+8]`、`&this[+0xC]`、`&this[+0x10]`**
逐个当 `float*` 输出缓冲传给 `CIniFile::ReadLine` —— 即往一块 **5 个 float 的相机参数块**里填值。

**两个结论**：
1. 注解把 `this` 当 `CIniFile`（8 字节）是错的（它显然指向那块 float 区）；
2. 但**它很可能根本不是成员函数**：`this` 是**结构体中间指针**（用了 `-4`），
   这种"基址不在类起点"的形态**无法与任何类的基址对齐** ⇒ offsets 匹配法对它天然失效，
   更可能是一个 `static`/自由函数（或以 `float*` 为参数的帮助函数）。

**工具侧**：`--func` 的偏移采集补上了**负偏移**（`[reg-imm]`）；另记录两条仍存在的漏采形态
（索引寻址 `[reg+reg*scale+disp]`、`this` 中途被重装）—— 遇到"0 个偏移"必须手工读函数体，
别把 0 当成"没有归属"。

## 12. 第 14 轮：第 6 条定案 `0x004CDAE0` → **`CEffMgr::ReleaseAllRefs`**（已落盘）

把 §10 判据不足的那条补齐后落盘（**只改了类与 this，返回类型保留原注解的 PDB 值 `char`**）：

| 段 | asm | 与 CEffMgr 的对应 |
|---|---|---|
| 1 | 对 `[edi+8]/[edi+0Ch]/[edi+10h]/[edi+14h]` 各调一次 `gbRefObject::Release()` | 这 4 个偏移在 `CEffMgr` 上正是 4 个 `gbRenderEffect *`（`m_pAdditiveBlendNoZ`/`m_pAlphaBlendNoZ`/`m_pAdditiveBlend`/`m_pAlphaBlend`） |
| 2 | `lea esi,[edi+60h] ; mov ebx,20h`；元素内 `+0/+1/+8`；`add esi,48h` | 32 条 **72 字节**记录（32 = `m_EffClass tagEffClass[32]` 的元素数） |
| 3 | `lea esi,[edi+92Ch] ; mov edi,800h`；`add esi,14h` | 2048 次 × **20 字节** = `tagEffObj` 尺寸；`0x92C+2048×20 = 0xA92C` **恰好落在 CEffMgr 的 size=43312(0xA930) 内** |

**唯一性**：894 个注解类里同时具备那 4 个偏移**且四者类型都是 `gbRenderEffect *`** 的只有 `CEffMgr` 与 `SceneMgr`；
而只有 `CEffMgr` 另有 32 元素数组 ⇒ 唯一。原类 `gbRefObject`（size=8）不可能有 `+0x14/+0x58/+0x92C`。

**验证**：S2 `71/201`、matched `225/259`、**L1 `21`**、`new_failures 0`、总错误 `2481→2477`（中性）。

> 注意：这条的归属成立**不等于** `CEffMgr` 的成员模型正确 —— §8 已证 `tagEffClass` 应为 72 字节、
> 且跨度内 20 个成员与指令冲突。两者独立：本条只动"函数属于谁"，没碰成员表。






