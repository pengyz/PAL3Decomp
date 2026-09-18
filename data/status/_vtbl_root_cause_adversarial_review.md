# 对抗性复核：`_cleanup_vtable_class_reconcile.md` §22/§23/§24 的根因分析

**复核对象**：`data/status/_cleanup_vtable_class_reconcile.md` §22 / §23 / §24
**副输入**：`data/status/_vtbl_annotation_proposal.{md,json}`
**纪律**：只读仓库；未修改 `pipeline/`、`data/annotations/`、`pal3/src/`；未 apply、未 `codegen all`、未 `match`。唯一写入 = 本文件。
所有 in-memory 实验通过 `python3 - <<PY` / `g++ -x c++ -`（stdin）完成，**未落任何文件**（除本报告）。
每个数字均为本次自行重数。

**约定**：下文 `【实测】` = 我亲自跑出并已核对；`【代码】` = 只读代码得出；`【推断】` = 未直接测量。

---

## 0. 复核结论总览

| 条目 | 原判定 | 我的判定 | 一句话 |
|---|---|---|---|
| C1 算术不一致 | 两套口径不一致 | **字面成立、实质夸大（部分证伪）** | 两套口径确实不同，但"legacy 那套"**全树命中 0 次**，只是死代码；在跑的口径只有一套 |
| C2 N=槽位下标 | 成立 | **成立**（证据加强） | 8 组干净配对中 6 组 `disp=N*4`、**0 组 `disp=N`**；116 个 `__vftable` 变体**全是 `void *`**，无按类差异 |
| C3 65/25/1 | 前缀全对·长度不足 | **不成立（分布与主结论双双被推翻）** | 你的启发式把**相邻的不同 vtable 串成一张**；硬口径是 77/13/2/1。`CEffAction 15/80`、`UIWnd 真表 29` 都是**假阳性** |
| C4 gbTexture 来源错误 | 4 个地址与表无关 | **不成立（定性要改）** | 4 个地址是 `gbTexture_D3D` 表 `off_100F5738` 的**第 1–4 槽**（真实函数），是**整体错位一格**，不是"无中生有" |
| C5 只补注解更糟 | 成立（看 diff 断言） | **(a) 成立 (b) 结论成立但当时是未测量断言；我补了测量** | 我复现了 diff，并用 g++ 实测 **arity 编译错误** |
| C6 四条静默通道 | 1/2/3 成立，4 疑似 | **1/2/3 成立；4 不成立（原因错）**；另发现**第 5、6 条** | 第 4 条的"分组错配"是**误判**；真正致命的是 `_ast_cleanup` 的静默整行删除 |
| C7 未闭合的一环 | 未知 | **已闭合** | `_ast_cleanup` 删的；触发链是 `//4` → 槽 0 → `~gbGfxManager` → "独立 dtor 调用"启发式 → 整行 `delete` |

**我推翻或修正的关键几条**：
1. **C3 的 65/25/1 分布**（→ 77/13/2/1；25 例"截断"多数是启发式假阳性；实际有 **13 例注解过长**，你完全没提）。
2. **C4 的"来源错误/无关"定性**（→ `off_100F5738` 槽 1–4，整体错位一格）。
3. **C6-4 的原因**（分组没错；死是因为正则太严 + AST 先跑）。
4. **C7 已查明**，并且它反证了 **§24.0/§22.3 的"`//4` 不是根因、只是遮蔽物"**：`//4` 是 **46 条语句被静默删除的直接原因**（可复现：改成 `N` 后 46 → **0**）。
5. **§22.3/§23.2 把 stub 称为"老实的 stub"**：实测 stub **函数体为空**（`{\n    \n}`），它**静默丢弃了整个调用**（全树 312 处）。这不是"老实"。

---

## C1｜算术不一致 —— **字面成立，实质夸大（部分证伪）**

### 1.1 字面核对（成立）
`pipeline/gen/stages/stage3_cleanup.py`：
- `_try_resolve_vtable`（定义在 `:881`，`slot = off` 在 `:887`）—— `off = int(m.group(3))` = 文本里的 `+N` ⇒ **`slot = N`**。
- `_resolve_vtbl_method`（`:487`，`slots.get(d['offset'] // 4)` 在 `:501`）—— `d['offset']` 由 `_decode_vtbl_call` 的 `\+\s*(\d+)` 取得 = 同一个 `N` ⇒ **`slot = N // 4`**。

⇒ 同文件两处算术**确实不同**。这一条字面成立。

### 1.2 但两条是否都可达？（攻击面 —— 结果是关键）
**【实测】** 我 monkeypatch 了 `stage3_cleanup` 内部的 `re.compile`，把 `run()` 里现编译的三个 `__vftable` 正则全部抓出来，然后对**全部 3598 个 decomp JSON** 走 `stage1 → stage2 → stage3` 完整路径，统计正则匹配次数与"替换函数返回非 None"的次数：

| 正则 | 匹配次数 | 成功解析次数 |
|---|---|---|
| `_vtable_re`（`slot = off`，即 C1 的主角） | **0** | **0** |
| `_vtable_re3`（`slot = 0`） | **0** | **0** |
| `_vtable_re2`（`0 in _slots`） | 13 | 13 |

⇒ **`slot = off` 那条永不生效**。所谓"两套口径不一致"是**潜伏的矛盾（死代码）**，不是"两套口径在互相打架"。在生效的口径只有 `//4` 一套 + `_vtable_re2` 的固定槽 0（第三套语义）。

补充核对：`_try_resolve_vftable`（`:77`，正则里写 `slot_index = offset // 4`）在**整个仓库没有任何调用点**（`grep -rn "_try_resolve_vftable" --include=*.py .` 只有定义那一行）⇒ 你的 §22.1"那是死代码，不过同一颗地雷"成立，但它与你 §24.1 点名的 `:887` 那个函数是**两个不同的函数**（一个用 `//4`、一个用 `slot=off`），§22.1 与 §24.1 混用了名字，容易误导下一位。

### 1.3 结论
- C1「两套口径算术不同」：**成立（字面）**。
- C1「因此是症状放大器」：**实质被夸大** —— 真正在跑的只有一套；把它列为"层 1 根因"会让人去找一个**不存在的运行时冲突**。正确的表述是：`//4` 是唯一在跑的口径，另一条是死代码里的第二个（未被触发的）错口径。

---

## C2｜N 是槽位下标、不是字节偏移 —— **成立（证据加强）**

### 2.1 我的独立配对方法（可复核）
对每个有 `__vftable` 的 decomp JSON：取其 `address` → 在 `original/PAL3.exe.asm` 里定位同名 `proc near`…`endp`（注意 IDA 9 列表是 `^(\S+)\s+proc near`，`\s+` 不能写成单空格），抽出该函数**全部** `call dword ptr [reg+disp]`（含 `[reg]` 即 disp=0），与 decomp 里全部 `__vftable + N`。

**方法为何可信**：不依赖逐点文本对齐（那正是你"9 例里 3 例配对失败"的来源），而是比较**同一个函数内的多重集** `{N}` vs `{disp/4}`；只有整组相等才记一例。逐点配对失败通常是因为一个函数里既有 vftable 调用又有其它间接调用，多重集法能把这类噪声直接判为"不干净"而不是硬凑。

**【实测】结果**

| 口径 | 数量 |
|---|---|
| 多重集完全相等且满足 `N == disp/4` | **7** |
| 多重集完全相等且满足 `N == disp`（字节偏移假设） | **0** |
| 全部间接调用位移中 `disp % 4 != 0` 的 | **0** |

7 例清单（含一个 3 元多重集，很有说服力）：

| 函数 | decomp 的 N | asm 的 disp | disp/4 | cast 类 |
|---|---|---|---|---|
| `sub_4C52C0` | 2 | `+8` | 2 | gbGfxManager |
| `sub_536FD0` | 7 | `+1Ch` | 7 | gbActorDef |
| `sub_536AC0` | 15 | `+3Ch` | 15 | gbActorDef |
| `sub_537120` | 15 | `+3Ch` | 15 | gbActorDef |
| `sub_5371B0` | 15 | `+3Ch` | 15 | gbActorDef |
| `sub_541710` | 26 | `+68h` | 26 | gbGfxManager |
| `sub_541590` | 25 | `+64h` | 25 | gbGfxManager |
| `sub_406D70` | **21, 22, 22** | **`+54h`,`+58h`,`+58h`** | 21,22,22 | gbGfxManager |

单 N/单间接调用 的"干净对"共 **8** 组：6 组满足 `disp=N*4`，**0** 组满足 `disp=N`，2 组是配对噪声（`sub_4207D0` 实为多间接调用、`sub_43E5C0` 含 `[edx+18h]` 的另一次派发）。—— 你报的 6/9 与我的 6/8 是"同一结论、不同取样口径"。

### 2.2 重点攻击：`__vftable` 的声明类型是否按类而异？
**【实测】** `asm/pal3/ida_structs.json` 里所有含 `__vftable` 成员的 struct：**116 个，`type` 全部是 `void *`，offset 全部是 0**。没有任何一个是 `char *` / `_BYTE *`。

```（枚举结果）
structs with a __vftable variant: 116
   'void *'   116
   offset 0   116
```

**这条证据的强度与边界（我不夸大）**：
- 强：它直接否掉了"导出层存在按类不同的指针类型"这一假设。
- 弱：该 export 的 `source` 写着 `annotation: vtable ptr fix for ->0` / `vtable_fix`，说明这个 `void *` 本身**可能不是 Hex-Rays 反编译当时的类型**，而是后来为修 `->0` 加上的注解。所以严格说：它证明的是"导出里没有按类差异"，**不能单独**证明 IDB 当时的类型。
- 因此我把结论压在**经验关系**上：`disp = 4N` 在多类上成立、`disp = N` **零例**、且所有 `disp` 都是 4 的倍数。若某类真按字节解释，它的 `N` 必须是 4 的倍数；而全树 867 个 `N` 里 651 个（75.1%）不是 4 的倍数。

### 2.3 你的分布数字重数
| | 你 | 我 |
|---|---|---|
| `__vftable + N` 站点 | 855 | **867** |
| N 不是 4 的倍数 | 639 | **651**（75.1%） |

Top N（我的计数）：`3`×243、`1`×102、`7`×85、`2`×82、`8`×81、`4`×72、`5`×52、`6`×29、**`192`×28**、`20`×11…
注意 `+192` 那 28 处：形如 `*((_BYTE *)&this->...__vftable + 28) = v3;`（你提示的幻影行陷阱），它们**不是**槽位访问，混进分布统计会稀释结论；建议下一步把 `&__vftable + N`（对象内存 +N 字节）与 `->__vftable + N`（槽位）分开统计。

### 2.4 结论
C2 **成立**。**残留不确定性（忠实记录）**：对"既没有任何间接调用证据、又只出现 4 的倍数 N"的类，我**没有**逐一排除字节偏移解释；但这类残差在 651/867 的非 4 倍数分布与 0 例 `disp=N` 面前可以忽略。

---

## C3｜65/25/1 —— **不成立：分布与"前缀全对·长度不足"的主结论都被推翻**

### 3.1 先复现你的口径（很重要：你的数字能复现）
你的方法：`va2off(va)=0x1000+(va-0x401000)` 读表，用 `0x401000 <= v < 0x620000` 判断"还是表项"定表尾。我按此实现：

**【实测】我的复现**：`consistent 66 / truncated 26 / annot_longer 1`（共 **93** 个 exe 注解表）。

**你报 91，我数 93** —— 差 2 例，来源已查明：注解集合里有一个 **`gbGfxManager`，其 `vtables[0].addr = "0x00010000"`**（这是 DLL 导出序号的占位写法，不是 exe 地址），它会落进 `v<0x620000` 的 exe 集合；另有 `RoleStatePanel`（注解 0 槽）在你的口径下也算 truncated。把这两例剔掉正好回到 **65+25+1=91**。⇒ 你的 91 是"93 减去这两个特例"，**口径本身自洽**。

### 3.2 但这个口径是错的（你担心的正是这一点，事实证明担心成立）
`0x401000<=w<0x620000` 的连续 dword **会跨过 vtable 边界**：相邻的多个不同类的 vtable 在 `.rdata` 里是连续排布的，一串函数指针会被读成"一张长表"。

**【实测】更硬的口径**：以 **IDA 自己的清单**定表尾 —— `original/PAL3.exe.asm` 里 `off_XXXXXX dd offset ...` 之后的连续 `dd` 行，遇到下一个 label / `align` / `dq` / 非 `dd` 行即结束；表项地址再从 `original/PAL3.exe` 原始 PE 按 `va2off` 独立读出（两条独立通道互相印证）。

| 判定 | 你的口径 | 硬口径（IDA label 表尾 + 原始 PE 读址） |
|---|---|---|
| 完全一致 | 66 | **77** |
| 注解**过长**（跨到别的表） | 1 | **13** |
| 真正截断 | 26 | **2** |
| 无 label | 0 | 1（`gbGfxManager` 的 `0x00010000`） |

### 3.3 逐例证伪（这三例足以推翻主结论）
- **`UIWnd @0x56AE2C`：你说"注解 7/7 但真表 29" —— 假阳性。**
  IDA 清单在 `0x56AE2C` 之后恰好 **7** 条 `dd`，下一条 label 是 `off_56AE48`（`0x56AE2C + 7*4 = 0x56AE48` ✅）。
  你的 29 = **7 + 7 + 8 + 7**，正是 `0x56AE2C / 0x56AE48 / 0x56AE64 / 0x56AE84` **四张相邻且互不相同的 vtable 被串成一张**。
- **`CEffAction @0x56F5E4`：你称"最极端 15/80" —— 假阳性。** IDA 清单此处恰好 **15** 条 `dd`，下一 label 是 `off_56F620`（`+0x3C` ✅）。**注解 15/15 = 完全一致**。你的方法在这里读到 96（我复现），连 80 都不是。
- **`CEffect @0x56FA30`：你称"15/15" —— 结论对，但你同一套方法给我的读数是 18**（它吞掉了 `off_56FA6C` 的 3 项，直到撞上 `dword_56FA78 dd 41400000h` 这个 float 才停）。你自己的两个例子（CEffect、UIWnd）在你的同一口径下不自洽，说明这套启发式的**截断点由"表后恰好是什么数据"决定**，不可作为长度证据。

### 3.4 哪些结论**幸存**
- **"没有任何一例注解地址是错的" ≈ 成立**：**[实测]** 对 93 个 exe 表逐项检查 `slots[i] == 真表第 i 个 dword`，**92/93 前缀 100% 正确**；唯一"违规"是 `gbGfxManager` 的 `0x00010000` 占位地址（DLL 类，本不该算进 exe 集合）。所以你的**前缀不变量**是真结论，我保留它。
- **但"缺陷只是数组比真表短"不成立**：真正截断的只有 **2** 例 —— `RoleStatePanel @0x56F040`（注解 **0** 槽，真表 **7** 项）与 `CCBPanelSlot @0x56AE2C`（注解 **3** 槽，真表 **7** 项；且它与 `UIWnd` **共用同一个 vtable 地址**，两者注解长度不同）。
- **你完全漏了一类反向缺陷：13 例"注解过长/跨表"**（这比"截断"更危险，因为 `_load_vtable_data` 会把别的类的方法名注册进本类的槽位映射）：
  `RenderTarget2`（**99** 与 **42**，真表各 3）、`RoleSystem`（9→3）、`ScriptObj`（5→1）、`CCBSkillWindow`（14→7）、`CEffectSystem`（9→8）、`gbLightObj`（6→3）、`PalScript`（6→3）、`PalScriptMgr`（6→3）、`CCBControlWindow`/`CCBFiveNimbusWindow`/`CCBItemWindow`/`CCBResultWindow`（各 8→7）。
  例：`0x570570`(CCBSkillWindow) IDA 表尾 7 项；注解 14 槽 ⇒ 后 7 槽实为下一张表的内容。

### 3.5 结论
**C3 的 65/25/1 不成立**（同口径可复现为 66/26/1，剔除 2 特例即你的 91；但口径本身错）。**"前缀全对"成立**；**"长度不足"要改成"2 例偏短 + 13 例偏长"**。建议把 `tools/audit_vtable_slots.py` 的表尾判据从"地址区间"换成"IDA 清单 label 边界 + 原始 PE 交叉验证"，并把"注解过长"作为第三类缺陷报出来。

---

## C4｜`gbTexture` 是"来源错误" —— **不成立，定性必须改（是"错位一格"，且地址都是真的）**

### 4.1 那 4 个地址究竟在哪？（你要求的独立归属）
**【实测】** 直接在 `original/gbengine.dll` 里按 PE 段表把 VA 映射成文件偏移并取字节：

| VA | 文件偏移 | 首 16 字节 | 判读 |
|---|---|---|---|
| `0x1001BD30` | `0x01BD30` | `83 ec 38 53 8b 5c 24 40 55 8b 6c 24 48 56 8b f1` | `sub esp,38h; push ebx; … mov esi,ecx` → **标准 `__thiscall` 函数入口** |
| `0x1001BEA0` | `0x01BEA0` | `83 ec 48 8b 44 24 4c …` | 函数入口 |
| `0x1001BF80` | `0x01BF80` | `8b 44 24 08 53 55 …` | 函数入口 |
| `0x1001C010` | `0x01C010` | `83 ec 20 53 8b 5c 24 2c …` | 函数入口 |

⇒ 它们**不是野地址**，是 DLL 里真实的 4 个函数。

**【实测】** 再把整张 `.rdata` 扫一遍"哪个 dword 引用了它们"：

```
1001BD30 -> referenced at 0x100F573C
1001BEA0 -> referenced at 0x100F5740
1001BF80 -> referenced at 0x100F5744
1001C010 -> referenced at 0x100F5748
```

四个地址**连续、恰好落在 `off_100F5738 + 4/8/12/16`**。而 `original/gbengine.dll.asm:433390` 明写：

```
off_100F5738    dd offset loc_1001BA80   ; DATA XREF: gbTexture_D3D::gbTexture_D3D(void)+A
                dd offset ?CreateFromMemory@gbTexture_D3D@@...
                dd offset ?UpdateTexture@gbTexture_D3D@@...
                dd offset ?CreateForRenderTarget@gbTexture_D3D@@...
                dd offset ?CreateFromFileMemory@gbTexture_D3D@@...
off_100F574C    dd offset loc_1001C2D0   ; ← 下一张表
```

5 项 = `[scalar deleting dtor, CreateFromMemory, UpdateTexture, CreateForRenderTarget, CreateFromFileMemory]`，下一张表从 `0x100F574C` 开始。

**⇒ 那 4 个地址 = `gbTexture_D3D` 的表 `off_100F5738` 的槽 1/2/3/4。它们不仅"属于某张表"，而且在该表内完全自洽 —— 只是注解把它们写成了槽 0/1/2/3。**

### 4.2 你自称的那张表（核对无误）
**【实测】** `off_100F57E8` 的 `dd` 序列 = `[loc_100203A0, __purecall × 4]` = **5 项**，第 6 个 dword 位置（`0x100F57FC`）已是 `align 10h` 之后的 `dbl_100F5800`。⇒ 你数的项数与内容都对，`loc_100203A0` 正是 `gbTexture` 的 scalar deleting destructor（`gbTexture::gbTexture(void)+14` 往对象里写的就是 `off_100F57E8`）。

### 4.3 定性该怎么改
- **不成立的部分**：§24.2 的"**与它自称的表无关（张冠李戴）**"。那 4 个地址是**货真价实的 `gbTexture` 虚函数实现**（派生类的 override），不是无关数据。
- **成立的部分**：注解的 `addr` 指向 `0x100F57E8`，但槽列表取自 `gbTexture_D3D` 的表 ⇒ **"指错了表/条目"** 这个说法（§23.4 第 2 条）是准确的；而 §23.4 自己已经写出"真值 idx 1–4"，与 §24.2 的措辞**互相矛盾**，说明 §24.2 的定性是过度归纳。
- **影响比我预想的严重**：`_load_vtable_data` 按**数组下标**建映射：`{0:CreateFromMemory, 1:UpdateTexture, 2:CreateForRenderTarget, 3:CreateFromFileMemory}`；而真值（基表 `0x100F57E8`，槽 0 = `~gbTexture`）应为 `{1:CreateFromMemory, 2:UpdateTexture, 3:CreateForRenderTarget, 4:CreateFromFileMemory}`。⇒ **gbTexture 的每一个槽名都整体错位一格**，不是"一个坏地址"。

### 4.4 结论
**C4 不成立（定性需改）**：不是"4 个地址一个都不在表内 ⇒ 与表无关"，而是"槽列表取自派生类表、且整体下移一格"。修法应是**把注解改成 `addr=0x100F57E8` 且槽 0 放 `~gbTexture`、槽 1–4 放那 4 个实现**（或直接引 `off_100F5738` 并同步改写 `addr`），而不是"另找一张表"。

---

## C5｜"只补注解会更糟" —— **(a) 成立；(b) 结论成立，但当时是未测量断言；我补了测量**

### 5.1 (a) slot 7 / slot 28 是谁（原文行）
`include/gbengine/gbGfxManager.h`：
- `:148  virtual void SetFrustum(double l, double r, double b, double t, double n, double f);  // slot 7`
- `:169  virtual void SetFog(gbFogParam* pFogParam);                                     // slot 28`

⇒ 你的 (a) **成立**，逐字无误。

### 5.2 (b) 我复现了"只补注解"的内容 diff（未落任何文件）
用 `data/status/archive/20260918_2108_gbgfxmanager_29slots/gbgfxmanager_29slots.verified.json` 重建 29 槽映射，在内存里改 `store.struct_vtables['gbGfxManager']` 后重跑 `stage1→stage2→stage3`（对 `PAL3_Rendervoid_00405c00.json`）：

```diff
-// ---- synthesized vtable stubs (unresolved slots) ----
-static void pal3_vtbl_unk_0(gbGfxManager *, int *);
-static void pal3_vtbl_unk_1(gbGfxManager *, _DWORD);
...
-        pal3_vtbl_unk_0(gfxMgr, &g_nPAL3_D8E488) /* [VFTABLE-STUB] */;
+        gfxMgr->SetFrustum(&g_nPAL3_D8E488);
...
-        pal3_vtbl_unk_1(gfxMgr, 0) /* [VFTABLE-STUB] */;
+        gfxMgr->SetFrustum(0);
```
**你的 diff 逐字复现成功。** 机制也对：HEAD 只有槽 0–6 ⇒ `28//4=7` 不在表 ⇒ stub；补到 29 槽后 `slots.get(7)` = `SetFrustum`。

### 5.3 把它从"断言"升级成"测量"（我做的补充）
**你确实没有编译过。** 我用 `g++ -fsyntax-only -x c++ -`（从 stdin 读，不落文件）对 `SetFrustum` 的真实签名做 arity 检查：

```
error: no matching function for call to 'gbGfxManager::SetFrustum(int*&)'
note:   candidate expects 6 arguments, 1 provided
error: no matching function for call to 'gbGfxManager::SetFrustum(int)'
```
而 `PAL3.cpp` 确实能看见这个完整类（`pal3/src/globals.h:58` 是 forward decl，但 `PAL3.cpp` 经 `Render/CScreenMode.h → gbGfxManager.h` 拿到完整定义）。
⇒ **"只补注解"会把 `GameBase/PAL3.cpp` 从 ok 打成 fail，是真实可测量的**，不过：
- 失败性质是**arity/参数不匹配**，不是你写的 C2664/C2440 具体码（这个位点是"6 个 double 给了 1 个指针"）。**你的错误码描述要修**。
- **"更糟"只在 S2（可编译性）维度成立**。在 L1（字节匹配）维度上：stub 版**根本没有任何调用**，`SetFrustum` 版**调用错了槽（7 而非 28）**——**两者都不字节匹配**。所以"更糟"这个论断需要限定"更糟 = S2 退化"，不能说成总体更糟。
- 我**没有**跑真实 MSVC 编译（编译生成树需要写文件/跑 codegen，超出只读范围）⇒ 这是**签名级 arity 测量**，不是完整构建验证。

### 5.4 一个必须纠正的措辞：stub 不是"老实的 stub"
**【实测】** 生成树里 stub 的定义体是**空的**：
```cpp
static void pal3_vtbl_unk_0(gbGfxManager *, int *)
{
    
}
```
⇒ `[VFTABLE-STUB]` 把原调用**替换成一个空函数调用**，即**静默丢弃该次虚调用**（语句还在，调用没了）。全树 `[VFTABLE-STUB]` 标记出现 **618** 次（51 个文件）；**【实测】** AST 通道口径统计：`stub=312`、`resolved_to_name=118`、`repl=None=20`。
§22.3 说"没有注解目前比错的注解更糟"——按上面的 L1 分析，这句也**不成立**（stub 与错命名在 L1 上等价地坏），真正成立的是"stub 至少能编译"。

---

## C6｜四条静默失败通道 —— **1/2/3 成立；4 不成立；另发现第 5、6 条**

### 6-1 错误算术 × 可信前缀 = 别名后"永不失手" —— **成立（具体计算如下）**
`gbGfxManager`，`//4` 口径（0–6 已标注时）：

| N | N//4 | 拿到的名字（0–6 表） | 真值（29 槽表） |
|---|---|---|---|
| 4–7 | 1 | `MsgProc` | `NewVertexPool`/`NewIndexPool`/`NewDynVertBuf`/`SetFrustum` |
| 8–11 | 2 | `NewTexture` | `SetOrtho`…`SetMaterial` |
| 12–15 | 3 | `NewMesh` | `BeginScene`/`Present`/… |
| 16–19 | 4 | `NewVertexPool` | `GetFrustumPlanes`… |
| 20–23 | 5 | `NewIndexPool` | `CreateDepthStencil`… |
| 24–27 | 6 | `NewDynVertBuf` | `LoadCursor`… |
| **28** | **7** | `None`（0–6 表）→ stub | `SetFog` |

补到 29 槽后只改一行：`28 → slots[7] = SetFrustum`（其余 N//4 仍错，只是错得"更像真的"）。
`gbTexture`：`struct_vtables['gbTexture'] = {0:CreateFromMemory, 1:UpdateTexture, 2:CreateForRenderTarget, 3:CreateFromFileMemory}` ⇒ `N=2→CreateFromMemory`、`N=4→UpdateTexture`、`N=5→UpdateTexture`；用 `N` 口径则 `2→CreateForRenderTarget`、`4/5→None`。你的 §22.3 此处**完全正确**。

### 6-2 `data.py` 的静默丢弃 —— **成立**
**【代码】** `pipeline/gen/data.py:246`（你写 :243，实际 **:246**）：
```python
if _addr in _methods:      # 没有 else、没有 counter、没有 log
```
且 `_load_vtable_data` 还有两处**你没提**的静默行为：
- `if _method not in _slot_map.values(): _slot_map[_i] = _method` —— **同名去重**，后面的槽会被静默丢掉；
- `for _vt in _vtables:` 把**多 vtable 类（10 个类有 2–5 张表）的所有表按同一个下标空间合并**，`RenderTarget2`（99+42 槽）这类会互相覆盖。这是与 C3 的"注解过长"叠加的第二个数据面缺陷。

### 6-3 `stage3_cleanup.py` 的 `else: repl = None` —— **成立**
**【代码】** 实际在 `:585`（你写 :587）：`# no cast info at all — leave for legacy fallbacks` / `repl = None`，**无计数无日志**。
**【实测】** 该路径全树命中 **20** 次（对比 stub 312、命名成功 118）。⇒ 通道是真的，但**量最小、危害也最小**（它至少不改文本）。

### 6-4 legacy 正则分组错配 —— **不成立（原因错，结论侥幸对）**
**【代码】** `_vtable_re`（在 `run()` 内编译）的分组是：
```
... \(\s*(\w+)\s*\*[^)]*\)\s*\)  \s*\(?\s*(\w+(?:\s*->\s*\w+)*)\s*->\s*__vftable\s*(?:\+\s*(\d+))?\s*\)
        ^^^^^^^^^^^^ group(1) = cast 的【类名】        ^^^^^^^^^^^^^^^^^^^^^^^^ group(2) = 【对象链】
```
⇒ `cls = m.group(1)` **就是类名**，`gfxMgr` 是 `group(2)`。**"group(1) 是对象链"是误判**，`store.struct_vtables.get('gfxMgr')` 这种恒 None 的情形**不会发生**。

但"该分支从不生效"**结论正确**——原因是我在 C1.2 测到的：`_vtable_re` 全树 **0 次匹配**（`_vtable_re3` 也 0；只有 `_vtable_re2` 13 次且全部成功）。⇒ 请把 §24.3-4 从"疑似分组错配"改成"**正则过严 + AST 通道先消费，全树零命中**"。

### 6-5（我新发现的通道）`_ast_cleanup` 的**静默整行删除** —— 这才是 C7 的答案
**【代码】** `stage3_cleanup.py:254 _ast_cleanup()`：
- `:271 edits[line_idx] = ('delete', None)`（唯一产生 `delete` 的分支）；
- `:363 if action == 'delete': continue` —— **整行消失，无任何标记**（既无 `// [VFTABLE]` 也无 `[AUTO-COMMENTED]`）。

**【实测】** 对全树 3598 个函数统计 `_ast_cleanup` 造成的净行数减少：**408 行被静默删除**（绝大多数是合法的显式 ctor/dtor 调用，如 `(UIFrameWnd *)this->UIFrameWnd();`）。

### 6-6（我新发现的通道）`[VFTABLE-STUB]` = **空函数体的静默调用丢弃**
见 5.4：312 处 AST stub / 618 个标记，语义上把虚调用**换成空函数**。它与"命名成功"一起，构成"看生成文本完全看不出问题"的主因。这一条你的清单里**没有**（你只在 §22.3 把它当成无害回退）。

---

## C7｜"我未闭合的一环" —— **已查明（这是本次最重要的收获）**

### 7.1 结论：是 `_ast_cleanup` 删的，触发链完全确定
**【实测】** 我按 `run()` 的真实顺序逐步执行（全部 in-memory），单文件 `UI3DCtrl::CreateWithTexture`：

| 步骤 | `v7 =` 那一行 |
|---|---|
| S2 输出 | `v7 = (gbTexture *)(*((int (__thiscall **)(gbGfxManager *, int))gfxMgr->__vftable + 2))(gfxMgr, nVal);` |
| 去掉 `__thiscall` | `v7 = (gbTexture *)(*((int (**)(gbGfxManager *, int))gfxMgr->__vftable + 2))(gfxMgr, nVal);` |
| `_resolve_vftable_calls_ast`（:869 → `_resolve_vtbl_method` :501） | `v7 = (gbTexture *)gfxMgr->**~gbGfxManager**(nVal);` |
| `_comment_vptr_stores` / `_fold_vftable_mask` / `_fix_ref_params` | 不变 |
| **`_ast_cleanup`**（:254） | **整行消失** |

**机制（逐条对上）**：
1. `_resolve_vtbl_method` 用 `d['offset'] // 4`：`2 // 4 = 0`；
2. `store.struct_vtables['gbGfxManager'][0] = '~gbGfxManager'`（注解 `methods['0x00010000'].name = "~gbGfxManager"`）⇒ **解析出的是析构函数名**；
3. `_ast_cleanup` 的 `_get_ctor_call_info()`（:162 起）对 `field_expression` 的 `method_name` 有一条 `if method_name.startswith('~'): return method_name, ...`（:174）⇒ 这个调用被当成**析构调用**；
4. `child.parent.type == 'cast_expression'`（外层 `(gbTexture *)`）且 `is_standalone = node.child_count <= 2`（`expression_statement` = 赋值表达式 + `;`）⇒ `edits[line_idx] = ('delete', None)`；
5. `if action == 'delete': continue` ⇒ **整行删除，零标记**。

⇒ 完全解释了你的观察"`gbTexture *v7;` 声明在、下一行直接读未初始化的 v7；既无 `[VFTABLE]` 也无 stub 标记"。**`[VFTABLE]` 标记全树 0 个文件也复核过（0 occurrences）**。

### 7.2 量级：这不是个例，而是系统性的
**【实测】** 全树被 `_ast_cleanup` 删除、且形态为「`=` + `~\w+(`」的赋值语句：**46 条**，全部是 `gfxMgr->~gbGfxManager(...)` 形态的 `NewTexture` 派发被错名后误删，例如：

```
C2DSpark(int,int)            v4 = (gbTexture *)gfxMgr->~gbGfxManager(aEffectFlare3Bm);
C3DSpark(void)               v4/v7/v10/v13/v16 = (gbTexture *)gfxMgr->~gbGfxManager(...);
CCBStageShadow(void)         v2 = (gbTexture *)gfxMgr->~gbGfxManager(aShadowTga_0);
PalScript::OpenScript(...)   this->m_pTexture = (gbTexture *)gfxMgr->~gbGfxManager(Buffer);
RenderTarget::LoadTexture    v6 = (gbTexture *)gfxMgr->~gbGfxManager(m_szTexPath);
RoleSystem::LoadRoleImage    result = (unsigned __int8 *)gfxMgr->~gbGfxManager(0);
UI3DCtrl::CreateWithTexture  v7 = (gbTexture *)gfxMgr->~gbGfxManager(nVal);
UIFrameWnd::SetTextureByName this[1].m_bvisible = gfxMgr->~gbGfxManager(v3);
UIListBox::SetItemOffset     v6 = (gbTexture *)gfxMgr->~gbGfxManager(Source);
UIStatic::LoadTexture        this->m_texty = (gbRefObject *)gfxMgr->~gbGfxManager(lpString);
UIScene::SetTextParam        this->m_hFont = gfxMgr->~gbGfxManager(v1);
…（共 46 条）
```

### 7.3 因果性证明（把 `//4` 改成 `N` 后归零）
**【实测】** 只 monkeypatch `_resolve_vtbl_method` 把 `slots.get(d['offset'] // 4)` 换成 `slots.get(d['offset'])`（其余一律不动），重跑全树：

| 口径 | 上述"`= obj->~Cls(`"静默删除数 |
|---|---|
| `//4`（HEAD） | **46** |
| `N`（提案） | **0** |

同一口径下 `UI3DCtrl` 的那一行变成 `v7 = (gbTexture *)gfxMgr->NewTexture(nVal);` —— 正好对应你实测到的 `'NewTexture' : cannot convert parameter 1 from 'int' to 'const char *'`。

### 7.4 这条对 §22/§24 的**反证**
- §24.4 的前提"按 24.3-3，AST 路径对它是 `repl = None`（不改）"——**不成立**：AST 路径返回的是 `~gbGfxManager`，它**改了**，而且正是"改"才导致删除。
- §24.0/§22.3 的"`//4` 不是任何东西的根因，它只是把 (1) 掩盖住了"——**不成立**：`//4` 是 **46 条语句被静默删除**的直接原因（可复现地 46→0），这是实打实的功能/语义损失，不是"遮蔽"。
- 正确的层级关系：**`//4`（算术错）→ 槽 0 别名成析构名 → `_ast_cleanup` 的 ctor/dtor 启发式误判 → 整行删除**。这三步任何一步修掉都能消除 46 例（最省事的是让 `_resolve_vtbl_method` 在别名到 `~` 名时拒绝解析，或让 `_ast_cleanup` 只在 `left` 不是赋值目标时才走 delete）。

### 7.5 顺带核实的两条死代码
- `_try_resolve_vftable`（:77）：**无任何调用点**（确认死代码）。
- stage3 末尾的 `[VTBL_DISPATCH]` 通道：生成树里 **0** 次出现 ⇒ 同样从未生效。

---

## 8. 我**没能**证伪的（如实记录）

| 项 | 我试了什么 | 为什么没推翻 |
|---|---|---|
| C2 的普适性 | 全树多重集配对、按类类型枚举、位移取模检查 | 对"只出现 4 的倍数 N 且没有任何间接调用证据"的类，无法排除字节偏移解释（残差；但 0 例 `disp=N` + 75% 非 4 倍数使其可忽略） |
| C2 的 IDB 真实类型 | 读 `asm/pal3/ida_structs.json`、读 PE 字节、读 asm | 该 JSON 的 `type` 是**注解产物**（`source: annotation: vtable ptr fix for ->0`），不能当"反编译当时的类型"证据；.i64 是二进制，无法可靠反查成员类型 |
| C3 的"65"具体成员 | 复现同口径 | 我能复现 66/26/1 并定位到 91 = 93 − {gbGfxManager 占位, RoleStatePanel}，但**无法确知你当时剔的是哪 2 个**；只能说明"你的数字自洽、口径错" |
| C5 的完整编译 | 想跑 MSVC6 编译生成树 | 需要写文件 / 跑 `codegen`，超出"只读 + 只写报告"的授权；我改用 `g++ -fsyntax-only` 从 stdin 做 arity 测量 |
| C6-4 | 读代码 + 全树统计匹配次数 | 只否掉了"分组错配"这个**原因**；"分支不生效"这个**结论**我确认成立 |

---

## 9. 给下一步的修正建议（顺序性结论）

1. **保留**你的"前缀不变量"结论与可观测性优先的路线（§24.5）——它是对的。
2. **修正** `tools/audit_vtable_slots.py` 的表尾判据：**不要**用地址区间；用 IDA 清单 label 边界 + 原始 PE 交叉验证，并新增"**注解过长/跨表**"这一类（本次 13 例，含 `RenderTarget2` 99/42）。
3. **修正** C4 的修法：`gbTexture` 是**整体错位一格**，不是"找另一张表"。
4. **把 §24.3 的第 4 条改成**"`_vtable_re` 全树零命中（正则过严 + AST 先消费）"，**删掉**"分组错配"的判断。
5. **新增两条通道**：(5) `_ast_cleanup` 的 `delete`（408 行/46 例由 `//4` 直接导致）；(6) `[VFTABLE-STUB]` 的空函数体调用丢弃（312 例）。
6. **§22.3/§24.0 的"`//4` 不是根因"要撤回**：它是 46 例静默删除的直接原因。翻转算术的收益评估应把这 46 条算进去（这正是你 §24.4 缺失的那一块）。
7. **翻转 `//4 → N` 之前**，先落一个**便宜的护栏**：`_resolve_vtbl_method` 解析出的名字若以 `~` 开头，视为不可信并返回 `None`（可立刻消掉 46 例误删，且不必动数据/算术）。