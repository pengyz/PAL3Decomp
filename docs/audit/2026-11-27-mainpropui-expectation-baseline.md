# MainPropUI 落位预期基准（R7 第 2 类 oracle）

生成时间：2026-11-27 02:02（Asia/Shanghai）
任务：tsk_01M8CFF4EFZBFZXN9V46VY（R7 第 2 类 oracle）
写面：`docs/audit/`。本报告只读产出，不落位、不改 annotation。

## 0. 结论摘要（六条）

1. **尺寸三证一致：219,984 = 0x35B50**。注解 `binary_size`、ctor `sub_4909F0` 逐段建链求和、分配立即数 `push 35B50h`（全库唯一 1 处）三者相同，**不存在 PropUI 那种 164B 差额**。因此本类的问题不是"注解尺寸错了"，而是"注解成员表整体陈旧/错位"。
2. **ctor 逐段求和逐字节闭合**：30 段（含 7 段对齐间隙）首尾相接 = 0x35B50，脚本断言 `offset == 上一段 end` 全通过；末对象 `sub_439030`(308B)@0x35A1C 止于 0x35B50，正好是类尾。
3. **槽位顺序复核通过**：`[esi+2AFC0h]` 的写点在 `call sub_4909F0` 返回之后（`loc_4A461F`，asm:240532），与 #34 记录一致；其前 `[2AFBCh]` 存 `push 56630h` 的对象，其后 `push 41014h`(EquipUI) 才建下一个 ⇒ 无"C2440 式"提前写槽位反例。
4. **洞 16,896B 全部落在真实构造 span 内部或尾部跨对象段，顶层对象之间零空隙**。四类归因：A 注解步长错位 168B（21 段×8B）；B 大数组误建模 1,984B（96+896+896+96）；C `0x26FC` 记录内部未建模 7,012B；D 尾部跨对象 7,732B。合计 = 16,896B（与 census 原值闭合）。
5. **错位根因（本卡新证据）**：注解把 UIStatic/UIFrame 系列放在 0x298 起、步长 0xA0；ctor 真实序列是 0x180 起、步长 0x98。注解还把 `UIParticle[16][7]`（112×584）放在 0x1B44/0x11E44，而 ctor 建的是两段 `128×584`@0x1300/0x13700；`m_Role[5]`（5×4,132）@0x22728 对应 ctor 的 `5×0x26FC`@0x25B8C。⇒ 洞不是"缺成员"，是"成员表坐标整体偏了"。
6. **基类与注解不符（待另证，不宣称错）**：ctor 首调 `sub_43DCD0`，该函数写 `off_56AD20`（UIListBox 表）；注解写 `bases=[UIFrameWnd@0]`。两者都 72B，不影响尺寸，但影响 `this->` 归属，需单独取证后再改。

## 1. 只读声明与复现命令

只读：未运行任何 `pipeline/cli.py` 子命令；未改 `data/annotations/`、基线、生成树；本卡写面仅 `docs/audit/`。

```bash
# 1) 注解读数
python3 - <<'EOF'
import json
d=json.load(open('data/annotations/structs/MainPropUI.json'))
print(d['binary_size'],d['base_size'],d['bases'],len(d['known_members']),len(d['methods']))
print(d['vtables'])
EOF
# -> 219984 72 [{'name': 'UIFrameWnd', 'offset': 0}] 80 18
# -> [{'addr': '0x0056d618', ...7 slots...}]

# 2) census 洞面
python3 - <<'EOF'
import json
d=json.load(open('data/status/struct_holes_20261125.json'))
c=[x for x in d['classes'] if x['cls']=='MainPropUI'][0]
print(c['size'],c['hole_bytes'],len(c['holes']),c['members'],c['bases'])
print(sum(n for a,b,n in c['holes']))
EOF
# -> 219984 16896 34 80 1
# -> 16896

# 3) 分配点全库唯一性
grep -c "35B50h" original/PAL3.exe.asm       # -> 1
grep -n "push    35B50h" original/PAL3.exe.asm # -> 240512
```

## 2. 尺寸三证

| 证据 | 值 | 位置/命令 |
|---|---|---|
| 注解 `binary_size` | 219,984 = 0x35B50 | `data/annotations/structs/MainPropUI.json` |
| ctor 建链求和 | 219,984 | 30 段表求和（见 §4，脚本断言 offset 连续） |
| 分配立即数 | 0x35B50 | `original/PAL3.exe.asm:240512 push 35B50h`；`grep -c "35B50h"` = **1** |

分配—构造—存槽链路（asm:240512–240532）：

```
loc_4A45ED:
    push    35B50h              ; Size
    ...
    call    ??2@YAPAXI@Z        ; operator new(uint)
    ...
    mov     ecx, eax
    call    sub_4909F0          ; MainPropUI ctor
    jmp     short loc_4A461F
loc_4A461F:
    push    41014h              ; 下一个对象 EquipUI 的 Size
    mov     [esi+2AFC0h], eax   ; <- MainPropUI 槽位写点（ctor 返回后）
    call    ??2@YAPAXI@Z
```

三者一致 ⇒ 尺寸不需要"差额解释"；PropUI 的 164B 教训此处不适用（已先查边界再下结论）。

## 3. 「ctor 返回后才写槽位」复核（卡面②）

- 写点地址：`[esi+2AFC0h]` @ **asm:240532**，位于 `call sub_4909F0`（asm:240522）返回后的 `loc_4A461F` 块内。
- 位置判据：该指令之前是 `push 41014h`（下一个对象的分配尺寸），之后才是下一个 `??2` 与 `sub_498820`；也就是说，MainPropUI 槽位在 ctor **已返回**、且下一个分配尚未发生时写入。与 #34 记录一致，**不推翻**。
- 工厂 `sub_4A4220` 的槽序（供后续卡对照）：`[2AFB8]=29CEC/sub_482ED0` → `[2AFBC]=56630/sub_4867F0` → `[2AFC0]=35B50/sub_4909F0` → `[2AFC4]=41014/sub_498820`（EquipUI）。

## 4. ctor 建链 span 表（真 sizeof 的构成）

`sub_4909F0`（asm:212570–212832；另含 chunk 0x563A40）：首调基类 `sub_43DCD0`，随后按下列顺序就地构造；`[esi+58h]=0x320`、`[esi+5Ch]=0x258`。

| 段 | 起始 | 长度 | 范围 | ctor 证据 |
|---|---:|---:|---|---|
| 基类 UIListBox | 0x00000 | 72 | 0x0–0x48 | sub_43DCD0（写 0x56AD20） |
| 头字段 rc/宽高 | 0x00048 | 16 | 0x48–0x58 | 0x58=320h、0x5Ch=258h@asm212596 |
| 字符串/缓冲 | 0x00058 | 272 | 0x58–0x168 | char[256]×2 + char[256] + 状态字节 |
| 对齐间隙 | 0x00168 | 24 | 0x168–0x180 | 0x168–0x180，ctor 只写 168/169/16A/16B/16C/16D/16F/170/174/178/17C |
| UIFrameContainer ×6 | 0x00180 | 912 | 0x180–0x510 | sub_4422E0 @180/218/2B0/348/3E0/478 |
| UIButton ×9 | 0x00510 | 3096 | 0x510–0x1128 | sub_43A770 @510/668/7C0/918/A70/BC8/D20/E78/FD0 |
| UIFrameContainer @1128 | 0x01128 | 152 | 0x1128–0x11c0 | sub_4422E0 |
| 对齐间隙 | 0x011c0 | 16 | 0x11c0–0x11d0 | 152@1128 止 0x11C0，下一对象 0x11D0 |
| UIFrameContainer @11D0 | 0x011d0 | 152 | 0x11d0–0x1268 | sub_4422E0 |
| UIFrameContainer @1268 | 0x01268 | 152 | 0x1268–0x1300 | sub_4422E0，止 0x1300 |
| UIParticle ×128（A） | 0x01300 | 74752 | 0x1300–0x13700 | ??_L(0x1300,248h,80h,sub_4B4690,sub_4B47E0) |
| UIParticle ×128（B） | 0x13700 | 74752 | 0x13700–0x25b00 | ??_L(0x13700,248h,80h,…) 止 0x25B00 |
| 对齐间隙 | 0x25b00 | 140 | 0x25b00–0x25b8c | ctor 只在 25B80–25B88 写清零 |
| 记录 ×5（0x26FC） | 0x25b8c | 49900 | 0x25b8c–0x31e78 | ??_L(25B8C,26FCh,5,sub_490E90,sub_4910B0) 止 0x31E78 |
| 对齐间隙 | 0x31e78 | 16 | 0x31e78–0x31e88 | 下一对象 31E88 |
| UIFrameContainer ×5 | 0x31e88 | 760 | 0x31e88–0x32180 | sub_4422E0 @31E88/31F20/31FB8/32050/320E8 |
| 对齐间隙 | 0x32180 | 16 | 0x32180–0x32190 | 下一段 32190 |
| 记录 ×5（0x354） | 0x32190 | 4260 | 0x32190–0x33234 | 循环 5 次：lstrcpyA×4 + rep stosd 12 dword + [306h] |
| UIRoleDialog | 0x33234 | 1368 | 0x33234–0x3378c | sub_4A12F0 |
| UIButton ×5 | 0x3378c | 1720 | 0x3378c–0x33e44 | ??_L(3378C,158h,5,sub_43A770,sub_43A810) |
| UIFrameContainer ×6 | 0x33e44 | 912 | 0x33e44–0x341d4 | sub_4422E0 @33E44..3413C |
| 对齐间隙 | 0x341d4 | 16 | 0x341d4–0x341e4 | 下一段 341E4 |
| UIButton ×5 | 0x341e4 | 1720 | 0x341e4–0x3489c | ??_L(341E4,158h,5,…) 止 0x3489C |
| 对齐间隙 | 0x3489c | 4 | 0x3489c–0x348a0 | 下一对象 348A0 |
| UIFlexBar（84B） | 0x348a0 | 84 | 0x348a0–0x348f4 | sub_43D830（写 off_56ACFC） |
| UIFrameContainer @348F4 | 0x348f4 | 152 | 0x348f4–0x3498c | sub_4422E0 |
| UIFrameContainer ×12 | 0x3498c | 1824 | 0x3498c–0x350ac | ??_L(3498C,98h,0Ch,sub_4422E0,sub_442390) |
| UIFrameContainer @350AC | 0x350ac | 152 | 0x350ac–0x35144 | sub_4422E0 |
| cls_43dfc0（1208B） | 0x35144 | 1208 | 0x35144–0x355fc | sub_43DFC0 |
| 对齐间隙 | 0x355fc | 20 | 0x355fc–0x35610 | ctor 写 [355FCh]=-1 |
| UIButton ×3 | 0x35610 | 1032 | 0x35610–0x35a18 | sub_43A770 @35610/35768/358C0 |
| 对齐间隙 | 0x35a18 | 4 | 0x35a18–0x35a1c | ctor 写 [35A18h]=-1 |
| UI3DCtrl（308B） | 0x35a1c | 308 | 0x35a1c–0x35b50 | sub_439030 止 0x35B50 = 类尾 |

**闭合断言**（脚本）：30 段逐段 `offset == 上一段 end`，总和 **219,984 = 0x35B50 = 类尾**。

> 说明：表内 9 段"对齐间隙"（0x168、0x11C0、0x25B00、0x31E78、0x32180、0x341D4、0x3489C、0x355FC、0x35A18，其中 0x25B00 段 140B 最大）均为 ctor 只做少量标量写、无对象构造的区域，属真实布局的一部分，不是洞（census 也没有把它们算成洞）。

## 5. vtable 与基类

- 表地址 `0x0056D618`，7 槽与注解 `vtables[0]` 完全一致：`0x445E70` / Render `0x496FA0` / Update `0x4971E0` / HideAll `0x43DE40` / `0x445B90` / `_scalar_dtor 0x490E70` / OnMessage `0x4974A0`。
- ctor 在 asm:212813 写表；完整 dtor `sub_4912D0` 在 asm:213146 再次写同表（`sub_490E90` 是 0x26FC 记录的构造器，不是 dtor）；`.rdata` 表定义在 asm:537291，DATA XREF 标注 `sub_4909F0+43A`。
- 基类疑问：ctor 首调 `sub_43DCD0`（写 `off_56AD20` = UIListBox 表，72B）；注解 `bases=[UIFrameWnd@0]`。二者尺寸同为 72B，故本卡尺寸结论不受影响；改名/改 bases 需单独取证（见 §9-1）。

## 6. 洞 16,896B 逐段分解（34 段）

分类口径：以 **ctor 真实 span**（§4）为底，判断每段落在哪个 span 内、以及由注解的哪种错位造成。

| 洞区间 | 字节 | 归因 | 落在真实 span |
|---|---:|---|---|
| 0x000330–0x000338 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 容器2B0 |
| 0x0003d0–0x0003d8 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 容器348 |
| 0x000470–0x000478 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 容器3E0 |
| 0x000510–0x000518 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 按钮×9 |
| 0x0005b0–0x0005b8 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 按钮×9 |
| 0x000650–0x000658 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 按钮×9 |
| 0x0006f0–0x0006f8 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 按钮×9 |
| 0x000790–0x000798 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 按钮×9 |
| 0x000830–0x000838 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 按钮×9 |
| 0x000924–0x00092c | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 按钮×9 |
| 0x001484–0x00148c | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 粒子A |
| 0x001534–0x00153c | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 粒子A |
| 0x0015d4–0x0015dc | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 粒子A |
| 0x001ae4–0x001b44 | 96 | B 大数组误建模（[16][7]=112×584 vs 真 128×584） | 粒子A |
| 0x011ac4–0x011e44 | 896 | B 大数组误建模（[16][7]=112×584 vs 真 128×584） | 粒子A |
| 0x021dc4–0x022144 | 896 | B 大数组误建模（[16][7]=112×584 vs 真 128×584） | 粒子B |
| 0x0226c8–0x022728 | 96 | B 大数组误建模（[16][7]=112×584 vs 真 128×584） | 粒子B |
| 0x0277dc–0x027afc | 800 | C 0x26FC 记录内部未建模 | 记录×5 |
| 0x027b94–0x027b9c | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 记录×5 |
| 0x027c34–0x027c3c | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 记录×5 |
| 0x027cd4–0x027cdc | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 记录×5 |
| 0x027d84–0x027d8c | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 记录×5 |
| 0x027e24–0x027e2c | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 记录×5 |
| 0x0289bc–0x0289d0 | 20 | C 0x26FC 记录内部未建模 | 记录×5 |
| 0x028a68–0x028a70 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 记录×5 |
| 0x028b08–0x028b10 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 记录×5 |
| 0x029360–0x0293d0 | 112 | C 0x26FC 记录内部未建模 | 记录×5 |
| 0x029468–0x029470 | 8 | A 注解步长错位（UIStatic 系列 0xA0 vs 真 0x98） | 记录×5 |
| 0x0294b8–0x029978 | 1216 | C 0x26FC 记录内部未建模 | 记录×5 |
| 0x0299c0–0x029e80 | 1216 | C 0x26FC 记录内部未建模 | 记录×5 |
| 0x029ec8–0x02a388 | 1216 | C 0x26FC 记录内部未建模 | 记录×5 |
| 0x02a3d0–0x02a890 | 1216 | C 0x26FC 记录内部未建模 | 记录×5 |
| 0x02a8d8–0x02ad98 | 1216 | C 0x26FC 记录内部未建模 | 记录×5 |
| 0x033d1c–0x035b50 | 7732 | D 尾部跨对象（注解到 0x33d1c 为止） | 跨对象 3378C…35B50 |

**四类合计**：A 168B（21 段）+ B 1,984B（4 段）+ C 7,012B（8 段）+ D 7,732B（1 段）= **16,896B**，与 census 原值一致。

### 6.1 每一类的机制（可复核）

- **A（8B×21）**：注解把 12 个 UIStatic/UIFrame 成员排在 0x298 起、步长 0xA0；ctor 的真实 152B 容器是 0x180 起、步长 0x98。每错一个成员，其末端与下一成员之间就露 8B。典型：`m_Frame@0x298`（注解）对应 ctor `0x180`，`m_TimeMoney@0x338` 对应 `0x218`。⇒ 修法是把成员序列整体重排到 0x180/0x98，并删掉不存在的 8B 间隙，不是"补 8B 成员"。
- **B（96+896+896+96）**：注解 `m_btnPar = UIParticle[16][7]`@0x1B44（112×584=65,408，止 0x11AC4）、`m_btnPar2` 同型 @0x11E44；ctor 实际建两段 **128×584** @0x1300（止 0x13700）与 @0x13700（止 0x25B00），共 149,504B。数量与起点都不同，故四个边界处露出 96/896/896/96。⇒ 正确模型是「UIParticle[128] ×2」，不是 `[16][7]`。
- **C（7,012B）**：ctor 用 `??_L(0x25B8C, 0x26FC, 5, sub_490E90, sub_4910B0)` 建 5 个 9,980B 记录；注解只给 `m_Role = p_RoleState[5]`@0x22728（5×4,132=20,660，止 0x277DC），既起点偏 0x3464、元素尺寸也差 5,848B。5×1,216 等洞全部在记录内部。⇒ 需先定谳记录结构（9,980B/条）再建模，不能按 p_RoleState 摊。
- **D（7,732B）**：注解最后一个成员 `m_parSingle = UIParticle[12][5]`@0x2B43C（60×584=35,040，止 0x33D1C）之后没有任何成员；ctor 却继续建 344B×5、152B×6、344B×5、84B、152B、152B×12、152B、1,208B、344B×3、308B，直到 0x35B50。⇒ 尾部约 9 个对象（含 `cls_43dfc0` 1,208B 与 `UI3DCtrl` 308B）完全未进注解。

### 6.2 共用构建层归属（卡面③，不计为私有 span）

`stp_*`（`stp_BarL/M/R`、`stp_State/Magic/Equip/Prop/BattleArray/TaskBook/System/Exit/Effect`、`stp_Rect` 等 13 个成员，注解 0x838–0x148C）**不由 `sub_4909F0` 构造**——ctor 在这段只建了 9 个 344B 按钮（0x510–0xFD0）与后续容器。它们属于 `UI\GameMainUI\Communal\StpCtl\*` 的共用构建层，由 #34 §5 记录的 8 组函数对（#38 清单，尚未落盘，此处暂引 #34）：

`sub_4826A0+sub_482BB0` / `sub_484810+sub_484D20` / `sub_487650+sub_487B60` / `sub_491630+sub_491B40` / `sub_4993D0+sub_4998E0` / `sub_4A26D0+sub_4A4ED0` / `sub_4A7C40+sub_4A8150` / `sub_4B3DA0+sub_4B42F0`。

处置要求：这些控件若出现在本类偏移上，段注必须写「归属共用构建层，非本类私有」；**不得**为了消除 0x838–0x148C 的洞而把它们算成本类私有成员。实施卡若要动这段，先给出这 8 对函数中带本类 `this` 的调用点与偏移证据。

## 7. 与 PropUI（164B 差）的差异

| 维度 | PropUI | MainPropUI |
|---|---|---|
| 注解 vs 分配 | 29,056 vs 28,892（差 164） | 219,984 vs 219,984（**一致**） |
| 洞的性质 | 真实残留：st_Manager 未建模 + 尾部越界 96B | 全部由成员表错位产生，顶层无空隙 |
| 首要动作 | 缩小 size、补 st_Manager 语义 | 重排成员表（0x180/0x98、128×584、5×0x26FC、尾部 9 对象） |

## 8. 验收检查点（≥5，实施卡交上来时逐条对）

1. `binary_size == 219,984` 且**末对象**止于 0x35B50；若报"缩小到 0x33D1C"之类，说明用了旧注解尾部，直接可疑。
2. `push 35B50h` 仍全库唯一（`grep -c "35B50h"` = 1）；出现第二处必须解释（新分配/复制）。
3. 152B 容器序列从 **0x180 起、步长 0x98**（0x180/218/2B0/348/3E0/478），不是 0x298 起 0xA0。
4. UIParticle 是 **128×584 ×2**（0x1300 与 0x13700），不是 `[16][7]`；若实施卡保留 112×584，A/B 类洞必然重现。
5. `0x25B8C` 处必须有 `5×0x26FC` 记录（`??_L` 的 size/count 字面量 0x26FC/5）；用 p_RoleState[5] 覆盖该区间即为错。
6. 尾部 0x33D1C 之后仍要有对象直到 0x35B50（344×5、152×6、344×5、84、152、152×12、152、1208、344×3、308）；漏建则 ctor 写界与类尾不符。
7. `[2AFC0h]` 写点必须在 ctor 返回之后（asm:240532 附近）；若实施卡改成 ctor 内写，需给反证。
8. 表地址仍为 0x56D618、7 槽不变；ctor/dtor 各写一次。
9. 洞面：允许保留的是"C 类记录内部"未建模部分（≤7,012B）与 D 类中尚无字段语义的对象内部；A/B 类（2,152B）应清零，否则说明只是把注解坐标换了皮。
10. 只读面核对：实施卡不得顺带改 `bases`（基类疑问未定谳）。

## 9. 未决（本卡不判）

1. **基类**：注解 `[UIFrameWnd@0]` vs ctor 首调 `sub_43DCD0`（UIListBox 表）。两者同 72B，尺寸无影响；需 `this->` 成员归属证据或 IDA UDT 才能改。
2. **共用构建层清单**：#38 报告尚未落盘，本卡引 #34 §5 的 8 对函数；#38 交付后应以其为唯一清单，若有差异以 #38 为准并回填本报告。
3. **0x26FC 记录结构**：5×9,980B 的内部字段（含 5×1,216 洞）全未知；需该记录 ctor `sub_490E90`/dtor `sub_4910B0` 的访问面普查。
4. **两段 128×584 的语义**：ctor 用 `sub_4B4690/sub_4B47E0` 成对构造/析构，元素是 UIParticle(584)；这两段与 `m_btnPar` 的"按键粒子"语义是否同一物，需 UI 侧证据（#38/#40 界面卷宗）。
5. **0x168–0x180 24B**：ctor 只写字节/标量（168/169/16A/16B/16C/16D/16F/170/174/178/17C），无对象；语义待定。
6. **尾部 0x33D1C–0x35B50 的 9 个对象**（含 1,208B `cls_43dfc0`、308B UI3DCtrl、UIRoleDialog）分别是什么成员名，需逐对象 ctor 身份 + UI 用途。

## 10. 只读自证

- `git status --short`：本卡只新增 `?? docs/audit/`（及本报告）；`git diff data/annotations/structs/MainPropUI.json` 为空。
- 未执行 `pipeline/cli.py apply/export/codegen/probe/match/loop` 任一子命令；`pal3/src` 无改动。
- 本报告所有数字均来自上述命令输出或 asm 行号；asm 行号对应 `original/PAL3.exe.asm`（当前工作树）。
