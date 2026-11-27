# R4 fade 注解改动最小编译实验（/tmp 副本，只读）

- 卡：#43 `tsk_01M8CM5DWT5MQM12Q5DPQ2`
- 输入：#34 二进制结论（`docs/specs/2026-11-27-screenfade-size-4b-evidence.md`）、#39 施工图（`docs/specs/2026-11-27-r4-screenfade-landing-plan.md`）
- 实验时点：2026-11-27T03:14:38+08:00（命令与输出见 §7，均为当场执行）
- 边界：只在 `/tmp/r4exp/` 的副本上改。仓库 `pal3/src` 改动数 **0**（`git status --porcelain pal3/src | wc -l` = 0），未跑 apply/export/codegen/probe/loop，未改 data/annotations、pipeline、tests、基线，未 commit；本卡唯一新增文件是本报告（`?? docs/specs/2026-11-27-r4-screenfade-minimal-experiment.md`）。工作区另有 15 条他人并发改动（`SaleUI.json`/`UIGameFrm.json`/`UITitle_JDHY.json` 等 3 个注解 M、5 份 `pipeline/_logs/loop_*.log` M、`stage5_fixup.py` M，以及他人新增的 `tests/test_gbvisnode_0x44.py` 等），均非本卡产物。

## §0 结论（5 条）

1. **布局算术闭合**：把 `PalScriptWaitObj` 的 `+0x0` 从「数据成员」改成「vfptr」后，编译期尺寸从 `28 / 32 / 28 / 28 / 28 / 168` 变为 **`24 / 28 / 24 / 24 / 24 / 152`**，与 #34 的二进制真值（ScreenFadeIn 28、FadeOut/White/White2 24、Mgr 152）**逐项相等**。
2. **偏移同步落到真值**：`ScreenEffect::m_nType` 12→**8**、`m_hold` 24→**20（0x14）**、`ScreenFadeIn::m_first` 28→**24（0x18）**；Mgr 四个子对象 36/64/92→**32/56/80（0x20/0x38/0x50）**、`m_nEffectCount` 164→**148（0x94）**。
3. **判别力已证**：同一断言集放到「未改副本」上编译报 **13 处 C2118**；放到「已改副本」上 0 错。反过来（改改前断言/未改）同样 13 处。⇒ 实验不是「怎么写都能过」。
4. **改动是外科手术**：另 10 个 `PSWO` 派生类尺寸不变（UICaption 96、PalScriptIdleObj 16、RoleFadeIn 20、RoleFadeOut 20、RotateObj 36、RotateInvObj 28、ScriptWaitFrm 12、XJ_Pic 16、ChoseCompose 3772、PSWO 自身 8）；唯一附带变化是 `Role` **8708 → 8704**，正好回到注解值 8704。
5. **可开实现卡，但有四条前置**：①`0x56AFA4` 三槽仍无 IDA 语义名（G1，禁用 `slot_N`）；②`Role` 的 PSWO 子对象在 0x38、其表不是 0x56AFA4（G2）；③本实验改的是**生成头**，注解层改动（`vtables` + 删 `0x0` 成员）后 codegen 是否真跳过 +0 成员需在实现卡里用产物断言验证；④`UICaption` 的重复第二表（0x56AFA6 三槽）必须同卡去重，否则同一地址两张表。

## §1 断言清单与来源

| 对象 | 断言 | 来源 |
|---|---|---|
| `sizeof(PalScriptWaitObj)` | 8（vfptr 4 + `gbImage2D*` 4） | #34 §2.2 / #39 §2 |
| `sizeof(ScreenEffect)` | 24 | #34（二进制 ctor 写界 0x14 → 0x18=24） |
| `sizeof(ScreenFadeIn)` | 28 | #34（ctor `[esi+0x18]=1` → 0x1C=28） |
| `sizeof(ScreenFadeOut/White/White2)` | 24 | #34（三 ctor 最大写 0x14/0x14/0x0C） |
| `sizeof(ScreenEffectMgr)` | 152 | #34（ctor 终点 0x98；实例 0xDE7DF8 与 guard 0xDE7E90 间距 0x98） |
| `offsetof(ScreenEffect, m_nType)` / `m_hold` | 8 / 0x14 | #34 ctor 写点 |
| `offsetof(ScreenFadeIn, m_first)` | 0x18 | #34 ctor 写点 |
| `offsetof(Mgr, m_fadeIn/fadeOut/fadeWhite/fadeWhite2/m_nEffectCount)` | 4 / 0x20 / 0x38 / 0x50 / 0x94 | #34 ctor 四个 `lea ecx,[esi+X]` 与末写 0x94 |

## §2 实验装置

### 2.1 副本与单点改动

```text
/tmp/r4exp/orig_src   = pal3/src 原样（负对照，sha256 12d82e1c06d5e84387dfbcf2…）
/tmp/r4exp/mod_src    = orig + PSWO 单点改动（sha256 0d1f46e84159249615f5df6a…）
/tmp/r4exp/mod2_src   = mod + UICaption 去重（PSWO sha 同上；UICaption cbaf3c0c… → 9fc6c35b…）
```

改动的唯一一处（`/tmp/r4exp/mod_src/Misc/PalScriptWaitObj.h`）：

```diff
 class PalScriptWaitObj {
 public:
-    void * m_nTodo_000; // +0x0
+    virtual ~PalScriptWaitObj(); // +0x0 (vfptr)
     gbImage2D * m_needscriptdel; // +0x4
     // total size: 0x8 (8)
```

`mod2` 另删 `UICaption.h` 的第二表三槽（对应注解 `vtables[1]=0x56AFA4`）：

```diff
 class UICaption : public UIWnd, public PalScriptWaitObj {
 public:
     ...
-    virtual CCBAIWindow * _ArraySlots(int); // slot0 0x0044ab40
-    virtual void slot_1(); // slot1 0x0044ab00
-    virtual void slot_2(); // slot2 0x004af760
```

### 2.2 编译参数（与 probe 同款）

```
wine tools/compilers/msvc6.0/Bin/CL.EXE /nologo /TP /c /W3 /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MT /Gd \
  /Fo/tmp/r4exp/ /I/tmp/r4exp/<副本>/src /Iinclude /Ipal3/src /I<msvc6 Include> /I<vc6 Include> <测量件>
```

测量件两种：
- `size.cpp`：`template<int N> struct ShowSize;` 只声明不实例化，用实例化触发的 **C2079** 错误信息把真实数值打出来（能取到精确数字，而不只是判等）。
- `assert.cpp`：`#define CHK(name, expr, want) typedef char chk_##name[(expr)==(want)?1:-1]`，编译通过即全断言成立；配 `/DMOD` 切换 mod/orig 两套期望值，用于负对照。

## §3 实测对账表

`size.cpp` 输出（原样，行号对应测量件）：

```text
$ python3 ... size.cpp   # orig_src
size.cpp(11) : error C2079: 'a1' uses undefined struct 'ShowSize<8>'     # sizeof(PalScriptWaitObj)
size.cpp(12) : error C2079: 'a2' uses undefined struct 'ShowSize<28>'    # sizeof(ScreenEffect)
size.cpp(13) : error C2079: 'a3' uses undefined struct 'ShowSize<32>'    # sizeof(ScreenFadeIn)
size.cpp(14) : error C2079: 'a4' uses undefined struct 'ShowSize<28>'    # sizeof(ScreenFadeOut)
size.cpp(15) : error C2079: 'a5' uses undefined struct 'ShowSize<28>'    # sizeof(ScreenFadeWhite)
size.cpp(16) : error C2079: 'a6' uses undefined struct 'ShowSize<28>'    # sizeof(ScreenFadeWhite2)
size.cpp(17) : error C2079: 'a7' uses undefined struct 'ShowSize<168>'   # sizeof(ScreenEffectMgr)
size.cpp(18) : error C2079: 'b1' uses undefined struct 'ShowSize<12>'    # m_nType
size.cpp(19) : error C2079: 'b2' uses undefined struct 'ShowSize<24>'    # m_hold
size.cpp(20) : error C2079: 'b3' uses undefined struct 'ShowSize<28>'    # m_first
size.cpp(21) : error C2079: 'c1' uses undefined struct 'ShowSize<4>'     # m_fadeIn
size.cpp(22) : error C2079: 'c2' uses undefined struct 'ShowSize<36>'    # m_fadeOut
size.cpp(23) : error C2079: 'c3' uses undefined struct 'ShowSize<64>'    # m_fadeWhite
size.cpp(24) : error C2079: 'c4' uses undefined struct 'ShowSize<92>'    # m_fadeWhite2
size.cpp(25) : error C2079: 'c5' uses undefined struct 'ShowSize<164>'   # m_nEffectCount
```

```text
$ python3 ... size.cpp   # mod_src（PSWO 改多态）
size.cpp(11) : error C2079: 'a1' uses undefined struct 'ShowSize<8>'
size.cpp(12) : error C2079: 'a2' uses undefined struct 'ShowSize<24>'
size.cpp(13) : error C2079: 'a3' uses undefined struct 'ShowSize<28>'
size.cpp(14) : error C2079: 'a4' uses undefined struct 'ShowSize<24>'
size.cpp(15) : error C2079: 'a5' uses undefined struct 'ShowSize<24>'
size.cpp(16) : error C2079: 'a6' uses undefined struct 'ShowSize<24>'
size.cpp(17) : error C2079: 'a7' uses undefined struct 'ShowSize<152>'
size.cpp(18) : error C2079: 'b1' uses undefined struct 'ShowSize<8>'
size.cpp(19) : error C2079: 'b2' uses undefined struct 'ShowSize<20>'
size.cpp(20) : error C2079: 'b3' uses undefined struct 'ShowSize<24>'
size.cpp(21) : error C2079: 'c1' uses undefined struct 'ShowSize<4>'
size.cpp(22) : error C2079: 'c2' uses undefined struct 'ShowSize<32>'
size.cpp(23) : error C2079: 'c3' uses undefined struct 'ShowSize<56>'
size.cpp(24) : error C2079: 'c4' uses undefined struct 'ShowSize<80>'
size.cpp(25) : error C2079: 'c5' uses undefined struct 'ShowSize<148>'
```

| 指标 | orig | mod | mod2 | #39 期望 | #34 二进制真值 | 判定 |
|---|---|---|---|---|---|---|
| sizeof(PSWO) | 8 | 8 | 8 | 8 | 8 | ✅ |
| sizeof(ScreenEffect) | 28 | **24** | 24 | 24 | 24 | ✅ |
| sizeof(ScreenFadeIn) | 32 | **28** | 28 | 28 | 28 | ✅ |
| sizeof(ScreenFadeOut) | 28 | **24** | 24 | 24 | 24 | ✅ |
| sizeof(ScreenFadeWhite) | 28 | **24** | 24 | 24 | 24 | ✅ |
| sizeof(ScreenFadeWhite2) | 28 | **24** | 24 | 24 | 24 | ✅ |
| sizeof(ScreenEffectMgr) | 168 | **152** | 152 | 152 | 152 | ✅ |
| m_nType | 12 | **8** | 8 | 8 | 8 | ✅ |
| m_hold | 24 | **20** | 20 | 0x14 | 0x14 | ✅ |
| m_first | 28 | **24** | 24 | 0x18 | 0x18 | ✅ |
| Mgr m_fadeIn | 4 | 4 | 4 | 4 | 4 | ✅ |
| Mgr m_fadeOut | 36 | **32** | 32 | 0x20 | 0x20 | ✅ |
| Mgr m_fadeWhite | 64 | **56** | 56 | 0x38 | 0x38 | ✅ |
| Mgr m_fadeWhite2 | 92 | **80** | 80 | 0x50 | 0x50 | ✅ |
| Mgr m_nEffectCount | 164 | **148** | 148 | 0x94 | 0x94 | ✅ |

**与 #39 期望、#34 二进制三方全等，无一项不一致，不需给差值。**

## §4 反向控制（证明实验有判别力）

`assert.cpp` 用负下标断言（`(expr)==want ? 1 : -1`），四项编译结果：

```text
$ ... assert.cpp  orig_src   （改前断言）        → 0 error（C2118/C2079 = 0）
$ ... assert.cpp  mod_src /DMOD（改后断言）      → 0 error
$ ... assert.cpp  orig_src /DMOD（负对照 A）     → 13 × C2118
$ ... assert.cpp  mod_src         （负对照 B）   → 13 × C2118
```

负对照 A 原样输出（节选）：

```text
assert.cpp(42) : error C2118: negative subscript or subscript is too large
assert.cpp(43) : error C2118: negative subscript or subscript is too large
assert.cpp(44) : error C2118: negative subscript or subscript is too large
assert.cpp(45) : error C2118: negative subscript or subscript is too large
assert.cpp(46) : error C2118: negative subscript or subscript is too large
assert.cpp(47) : error C2118: negative subscript or subscript is too large
...
（共 13 行，对应 7 个 sizeof + 3 个 Effect/FadeIn offsetof + 4 个 Mgr offsetof 中的 13 项）
```

含义：把改前/改后的期望值互换，同一份头就会在同一组断言行上报错 ⇒ 断言确实在约束真实布局。

## §5 附带影响（10 个 PSWO 派生类）

`collat.cpp` 用 `SizeProbe<sizeof(T)>` 输出，顺序 `[PSWO, UICaption, Role, PalScriptIdleObj, RoleFadeIn, RoleFadeOut, RotateObj, RotateInvObj, ScriptWaitFrm, XJ_Pic, ChoseCompose]`：

```text
orig : ['8', '96', '8708', '16', '20', '20', '36', '28', '12', '16', '3772']
mod  : ['8', '96', '8704', '16', '20', '20', '36', '28', '12', '16', '3772']
mod2 : ['8', '96', '8704', '16', '20', '20', '36', '28', '12', '16', '3772']
```

- 只有 `Role` 变：**8708 → 8704**，正好等于注解 `binary_size=8704`。原因：Role 自己已经声明了虚函数（主基类 `Object` 带 vptr），PSWO 子对象在 0x38；PSWO 自身有 vptr 后，编译器不再为 `Role + 0x38` 的 PSWO 子对象额外插一个 vptr。
- 其余全部不变；`UICaption` 96 在 mod / mod2 都不变 ⇒ 去重第二表**不影响布局**（它只是同一地址 0x56AFA4 的重复声明）。
- 结论：这是一次**尺寸层面安全**的外科手术，附带把 Role 的 4B 误差也修回注解值。

## §6 能否开实现卡

**能，但卡面必须写进四条前置。**

| 前置 | 内容 | 为什么必须 |
|---|---|---|
| P1 = G1 | `0x56AFA4` 三槽（0x44AB40/0x44AB00/0x4AF760）仍无 IDA 语义名 | 注解层必须给出 `slots`；命名铁律禁用 `slot_N` 占位，否则落地即违反命名规范 |
| P2 = G2 | `Role` 的 PSWO 子对象在 0x38，但其 3 张表都不是 0x56AFA4 | 若不核，Role 的 vptr 归属会与 annotation 再次错配（本实验已见 8708→8704 的连带效应） |
| P3 | 本实验改的是**生成头**；注解改动后 codegen 是否**真的**跳过 +0 成员 | 需在实现卡里对产物断言：`pal3/src/Misc/PalScriptWaitObj.h` 无 `m_nTodo_000` 且含 vfptr 注释；四个 fade 头 total size 注释为 24/28/24/24；Mgr 为 152 |
| P4 | `UICaption` 重复第二表必须同卡删 | 同地址 0x56AFA4 两张表会重复发射；本实验证明删后尺寸不变，属于零风险清理 |

**建议实现卡范围（交 PMO 决定，不在本卡建卡）**：
- 文件：`data/annotations/structs/PalScriptWaitObj.json`（删 `0x0 m_nTodo_000`、加 `vtables:[{addr:"0x0056AFA4", slots:[...]}]`、`binary_size` 仍 8）、`data/annotations/structs/UICaption.json`（删 `vtables[1]`）。
- 验收：本卡 §3 的 15 个断言 + `python pipeline/cli.py check` + `audit_type_layout --only {ScreenEffect,ScreenFadeIn,ScreenFadeOut,ScreenFadeWhite,ScreenFadeWhite2,ScreenEffectMgr,UICaption}` + 全链 `loop` 的 S2/总错误/L1 不退化（当场重取基线，不沿用卡面数字）。
- 停止条件：若 `check` 或 `audit_type_layout` 出现 PSWO 相关新错，或 `UICaption`/`Role` sizeof 偏离 96/8704，立即回退（两个 json 的 git checkout + 重跑 codegen）。

## §7 复现命令与原样输出

### C1 建副本并单点改动

```bash
cd /home/peng/workspace/PAL3Decomp
rm -rf /tmp/r4exp && mkdir -p /tmp/r4exp
cp -a pal3/src /tmp/r4exp/orig_src
cp -a pal3/src /tmp/r4exp/mod_src
python3 - <<'PY'
p='/tmp/r4exp/mod_src/Misc/PalScriptWaitObj.h'
s=open(p).read(); old='    void * m_nTodo_000; // +0x0\n'
assert old in s
open(p,'w').write(s.replace(old,'    virtual ~PalScriptWaitObj(); // +0x0 (vfptr)\n'))
PY
```

输出：`mod applied`（校验行存在后替换）。

### C2 测尺寸与偏移（size.cpp）

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import sys, re
sys.path.insert(0,'pipeline'); import probe_compile as pc
FL=('/nologo','/TP','/c','/W3','/O2','/Ob2','/Oi','/Ot','/Oy','/GF','/Gy','/GX','/GR','/MT','/Gd')
for tag, root in [('orig','/tmp/r4exp/orig_src'),('mod','/tmp/r4exp/mod_src')]:
    args=['/Fo'+pc.wpath('/tmp/r4exp/')+'\\', '/I'+pc.wpath(root)]
    for d in pc.INCLUDE_DIRS: args.append('/I'+pc.wpath(d))
    args.append(pc.wpath('/tmp/r4exp/size.cpp'))
    out,err=pc.run_cl(args,timeout=120,flags=FL)
    print('===',tag)
    for ln in out.splitlines():
        if re.search(r"'ShowSize<\d+>'", ln): print('   ', ln.strip()[:110])
PY
```

输出见 §3（orig 与 mod 两段，各 15 行）。

### C3 断言（assert.cpp，通过=0 error）

```bash
# 与 C2 同样的 include/参数，源码换成 /tmp/r4exp/assert.cpp：
#   orig_src 不加 /DMOD（改前期望值）
#   mod_src 加 /DMOD（改后期望值）
```

```text
assert_orig_noMOD            C2118/C2079 count= 0
assert_mod_MOD               C2118/C2079 count= 0
assert_orig_MOD(reverse)     C2118/C2079 count= 13
assert_mod_noMOD(reverse)    C2118/C2079 count= 13
```

### C4 附带类尺寸（collat.cpp）

```bash
# 同上 include/参数，源码换成 /tmp/r4exp/collat.cpp，orig_src 与 mod_src 各跑一次
```

```text
orig : ['8', '96', '8708', '16', '20', '20', '36', '28', '12', '16', '3772']
mod  : ['8', '96', '8704', '16', '20', '20', '36', '28', '12', '16', '3772']
```

### C5 mod2（UICaption 去重）

```bash
cp -a /tmp/r4exp/mod_src /tmp/r4exp/mod2_src
python3 - <<'PY'
p='/tmp/r4exp/mod2_src/Misc/UICaption.h'
s=open(p).read()
for old in ['    virtual CCBAIWindow * _ArraySlots(int); // slot0 0x0044ab40\n',
            '    virtual void slot_1(); // slot1 0x0044ab00\n',
            '    virtual void slot_2(); // slot2 0x004af760\n']:
    assert old in s; s=s.replace(old,'')
open(p,'w').write(s)
PY
# 再跑 C3/C4（root 换 /tmp/r4exp/mod2_src）
```

```text
mod2 collateral: ['8', '96', '8704', '16', '20', '20', '36', '28', '12', '16', '3772']
mod2 assert C2118: 0
```

### C6 元数据与仓库边界

```bash
date -Is
sha256sum pal3/src/Misc/PalScriptWaitObj.h /tmp/r4exp/mod_src/Misc/PalScriptWaitObj.h
git status --porcelain pal3/src | wc -l
```

```text
2026-11-27T03:14:38+08:00
12d82e1c06d5e84387df…  pal3/src/Misc/PalScriptWaitObj.h
0d1f46e84159249615f5…  /tmp/r4exp/mod_src/Misc/PalScriptWaitObj.h
0
```
