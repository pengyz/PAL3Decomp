# EquipUI 落位预期基准（R7 第 3 类 oracle）

生成时间：2026-11-27 02:0x（Asia/Shanghai）
任务：tsk_01M8CG15XKRDZ38R31A59T（R7 第 3 类 oracle）
写面：`docs/audit/`。只读产出，不落位、不改 annotation。

## 0. 结论摘要（六条）

1. **尺寸三证一致：266,260 = 0x41014**。注解 `binary_size`、ctor `sub_498820` 39 段建链求和、分配立即数 `push 41014h`（全库唯一 1 处）三者相同。
2. **ctor 逐段闭合**：39 段（含 5 段对齐间隙与 1 段尾部 80B）首尾相接 = 0x41014，脚本逐段断言 `offset == 上一段 end` 全通过；末段为尾部 80B 无写点区。
3. **槽位顺序复核通过**：`[esi+2AFC4h]` 写点在 **asm:240550**，位于 `call sub_498820`@asm:240540 返回之后（`loc_4A4651` 里先 `push 62588h` 建下一个对象）⇒ 与 #34 记录一致，不推翻。
4. **洞 15,960B / 7 段中，15,880B 由"已构造但未建模的对象"产生，只有尾部 80B（0x40FC4–0x41014）是真正未闭合**：ctor 该区无任何写点。
5. **注解的主要缺口是"漏对象"而非坐标错位**（与 MainPropUI 的步长错位不同）：漏掉 `UIRoleDialog`@0x25CA0、6×`cls_43dfc0`@0x2DB10、`152+84+152`@0x2D26C、5×152@0x2C184、以及 0x26C–0x1414 整段（6×152+9×344+3×152）。另有 2 段对象序列被写成 `unsigned char[]`（0x261F8 的 5×0x131C、0x2C48C 的 6×344），尺寸对但类型退化。
6. **共用构建层未介入本类 ctor**：ctor 没有调用 #34 §5 的 8 对 StpCtl 函数，所有子对象都在 ctor 内就地构造 ⇒ 本类没有"应归共用层"的私有段；若 UI 侧另有创建路径，需在 #38 落盘后补证（见 §9-2）。

## 1. 只读声明与复现命令

只读：未运行任何 `pipeline/cli.py` 子命令；未改 `data/annotations/`、基线、生成树；本卡写面仅 `docs/audit/`。

```bash
python3 - <<'EOF'
import json
d=json.load(open('data/annotations/structs/EquipUI.json'))
print(d['binary_size'],d['base_size'],d['bases'],len(d['known_members']),len(d['methods']))
print(d['vtables'])
EOF
# -> 266260 72 [{'name': 'UIListBox', 'offset': 0}] 23 23
# -> [{'addr': '0x0056e170', ... 7 slots ...}]

python3 - <<'EOF'
import json
d=json.load(open('data/status/struct_holes_20261125.json'))
c=[x for x in d['classes'] if x['cls']=='EquipUI'][0]
print(c['size'],c['hole_bytes'],len(c['holes']))
print(sum(n for a,b,n in c['holes']))
EOF
# -> 266260 15960 7
# -> 15960

grep -c "41014h" original/PAL3.exe.asm      # -> 1
grep -n "push    41014h" original/PAL3.exe.asm # -> 240530
```

## 2. 尺寸三证

| 证据 | 值 | 位置/命令 |
|---|---|---|
| 注解 `binary_size` | 266,260 = 0x41014 | `data/annotations/structs/EquipUI.json` |
| ctor 建链求和 | 266,260 | 39 段表求和（§4，脚本断言连续） |
| 分配立即数 | 0x41014 | `original/PAL3.exe.asm:240530 push 41014h`；`grep -c "41014h"` = **1** |

分配—构造—存槽（asm:240530–240550）：

```
240530  push    41014h          ; Size
...
240540  call    sub_498820      ; EquipUI ctor
        jmp     short loc_4A4651
loc_4A4651:
        push    62588h          ; 下一个对象（402,824B 类）
        mov     [esi+2AFC4h], eax   ; <- EquipUI 槽位写点（ctor 返回后）@240550
        call    ??2@YAPAXI@Z
```

## 3. 「ctor 返回后才写槽位」复核（卡面②）

- 写点：`[esi+2AFC4h]` @ **asm:240550**。
- 判据：它前一条是 `push 62588h`（下一个对象尺寸），再前是 `call sub_498820`（asm:240540）；即在 ctor 返回后、下一对象分配前写入。
- 与 #34 记录一致，**不推翻**。工厂槽序：`[2AFC0]=35B50/MainPropUI` → `[2AFC4]=41014/EquipUI` → `[2AFC8]=62588`（402,824B 类）。

## 4. ctor 建链 span 表（真 sizeof 构成）

`sub_498820`（asm:223644–223882，另含 chunk 0x564320）：首调基类 `sub_43DCD0`（UIListBox 表 `0x56AD20`），`[esi+58h]=0x320`、`[esi+5Ch]=0x258`。

| 段 | 起始 | 长度 | 范围 | ctor 证据 |
|---|---:|---:|---|---|
| 基类 UIListBox | 0x00000 | 72 | 0x0–0x48 | sub_43DCD0（写 0x56AD20） |
| 标量/缓冲区 | 0x00048 | 588 | 0x48–0x294 | 0x58=320h、0x5Ch=258h；0x68…0x290 标量 |
| UIFrameContainer @294 | 0x00294 | 152 | 0x294–0x32c | sub_4422E0 |
| UIFrameContainer @32C | 0x0032c | 152 | 0x32c–0x3c4 | sub_4422E0 |
| UIFrameContainer @3C4 | 0x003c4 | 152 | 0x3c4–0x45c | sub_4422E0 |
| UIFrameContainer @45C | 0x0045c | 152 | 0x45c–0x4f4 | sub_4422E0 |
| UIFrameContainer @4F4 | 0x004f4 | 152 | 0x4f4–0x58c | sub_4422E0 |
| UIFrameContainer @58C | 0x0058c | 152 | 0x58c–0x624 | sub_4422E0，止 0x624 |
| UIButton ×9 | 0x00624 | 3096 | 0x624–0x123c | sub_43A770 @624/77C/8D4/A2C/B84/CDC/E34/F8C/10E4 |
| UIFrameContainer @123C | 0x0123c | 152 | 0x123c–0x12d4 | sub_4422E0 |
| 对齐间隙 | 0x012d4 | 16 | 0x12d4–0x12e4 | @123C 止 0x12D4，下一对象 0x12E4 |
| UIFrameContainer @12E4 | 0x012e4 | 152 | 0x12e4–0x137c | sub_4422E0 |
| UIFrameContainer @137C | 0x0137c | 152 | 0x137c–0x1414 | sub_4422E0，止 0x1414 |
| UIParticle ×128（A） | 0x01414 | 74752 | 0x1414–0x13814 | ??_L(1414,248h,80h,sub_4B4690,sub_4B47E0) |
| UIParticle ×128（B） | 0x13814 | 74752 | 0x13814–0x25c14 | ??_L(13814,248h,80h,…) 止 0x25C14 |
| 对齐间隙 | 0x25c14 | 140 | 0x25c14–0x25ca0 | 下一对象 0x25CA0 |
| UIRoleDialog | 0x25ca0 | 1368 | 0x25ca0–0x261f8 | sub_4A12F0 |
| 记录 ×5（0x131C） | 0x261f8 | 24460 | 0x261f8–0x2c184 | ??_L(261F8,131Ch,5,sub_498C90,sub_498E60) 止 0x2C184（24,460B，注解写成 uchar[24460]） |
| UIFrameContainer @2C184 | 0x2c184 | 152 | 0x2c184–0x2c21c | sub_4422E0 |
| UIFrameContainer @2C21C | 0x2c21c | 152 | 0x2c21c–0x2c2b4 | sub_4422E0 |
| UIFrameContainer @2C2B4 | 0x2c2b4 | 152 | 0x2c2b4–0x2c34c | sub_4422E0 |
| 对齐间隙 | 0x2c34c | 16 | 0x2c34c–0x2c35c | @2C2B4 止 0x2C34C，下一对象 0x2C35C |
| UIFrameContainer @2C35C | 0x2c35c | 152 | 0x2c35c–0x2c3f4 | sub_4422E0 |
| UIFrameContainer @2C3F4 | 0x2c3f4 | 152 | 0x2c3f4–0x2c48c | sub_4422E0，止 0x2C48C |
| UIButton ×6 | 0x2c48c | 2064 | 0x2c48c–0x2cc9c | ??_L(2C48C,158h,6,sub_43A770,sub_43A810) 止 0x2D26C（2,064B，注解写成 uchar[2064]） |
| UIPushButton ×6 | 0x2cc9c | 1488 | 0x2cc9c–0x2d26c | ??_L(2CC9C,0F8h,6,sub_440740,…) 止 0x2D338 |
| UIFrameContainer @2D26C | 0x2d26c | 152 | 0x2d26c–0x2d304 | sub_4422E0 |
| UIFlexBar（84B） | 0x2d304 | 84 | 0x2d304–0x2d358 | sub_43D830 |
| UIFrameContainer @2D358 | 0x2d358 | 152 | 0x2d358–0x2d3f0 | sub_4422E0，止 0x2D3F0 |
| UIFrameContainer ×12 | 0x2d3f0 | 1824 | 0x2d3f0–0x2db10 | ??_L(2D3F0,98h,0Ch,sub_4422E0,sub_442390) 止 0x2DB10 |
| cls_43dfc0 ×6（1208B） | 0x2db10 | 7248 | 0x2db10–0x2f760 | sub_43DFC0 @2DB10/2DFC8/2E480/2E938/2EDF0/2F2A8 |
| tagPlayerSet ×5（52B） | 0x2f760 | 260 | 0x2f760–0x2f864 | ??_L(2F760,34h,5,sub_45ADD0,nullsub_1) 止 0x2F864 |
| 对齐间隙 | 0x2f864 | 96 | 0x2f864–0x2f8c4 | 下一对象 0x2F8C4 |
| UIButton ×3 | 0x2f8c4 | 1032 | 0x2f8c4–0x2fccc | sub_43A770 @2F8C4/2FA1C/2FB74 |
| 对齐间隙 | 0x2fccc | 4 | 0x2fccc–0x2fcd0 | 写 [2FCCCh]=-1，下一对象 0x2FCD0 |
| UI3DCtrl（308B） | 0x2fcd0 | 308 | 0x2fcd0–0x2fe04 | sub_439030，止 0x2FE04 |
| UIParticle ×60（A） | 0x2fe04 | 35040 | 0x2fe04–0x386e4 | ??_L(2FE04,248h,3Ch,…) 止 0x386E4 |
| UIParticle ×60（B） | 0x386e4 | 35040 | 0x386e4–0x40fc4 | ??_L(386E4,248h,3Ch,…) 止 0x40FC4 |
| 尾部未用 80B | 0x40fc4 | 80 | 0x40fc4–0x41014 | ctor 无任何写点；到 0x41014=类尾 |

**闭合断言**：39 段逐段 `offset == 上一段 end`，总和 **266,260 = 0x41014 = 类尾**。

## 5. vtable 与基类

- 表 `0x0056E170`，7 槽与注解一致：`0x445E70` / Render `0x49FE00` / Update `0x4A00B0` / HideAll `0x43DE40` / `0x445B90` / `_scalar_dtor 0x498C70` / OnMessage `0x4A0370`。
- ctor 在 asm:223865 写表；完整 dtor `sub_499030` 在 asm:224158 再写同表；`.rdata` 表定义在 asm:537496（DATA XREF `sub_498820+40E`）。
- 基类：`bases=[UIListBox@0]` 与 ctor 首调 `sub_43DCD0` 一致（不像 MainPropUI 那样存疑）；仅 `vtables[0].base` 标成 `UIWnd`，属注解小口径不一致，不影响布局。

## 6. 洞 15,960B / 7 段逐段分解

| 洞区间 | 字节 | 构成（按 ctor） | 性质 |
|---|---:|---|---|
| 0x26c–0x1414 | 4520 | 0x26C–0x294 标量 40 + 6×152（912）+ 9×344（3096）+ 3×152（456）+ 对齐 16 | 已构造未建模 |
| 0x25c14–0x261f8 | 1508 | 对齐 0x8C（140）+ UIRoleDialog 0x558（1368） | 已构造未建模 |
| 0x2c184–0x2c48c | 776 | 5×152（760）+ 对齐 16 | 已构造未建模 |
| 0x2d26c–0x2d3f0 | 388 | 152 + 84 + 152 | 已构造未建模 |
| 0x2db10–0x2f760 | 7248 | 6×1208（6×cls_43dfc0） | 已构造未建模 |
| 0x2f864–0x2fe04 | 1440 | 对齐 96 + 3×344（1032）+ 对齐 4 + 308 | 已构造未建模 |
| 0x40fc4–0x41014 | 80 | ctor 无写点 | **真未闭合（填充/预留）** |

合计 15,880 + 80 = **15,960B**，与 census 闭合。

### 6.1 两段"尺寸对但类型退化"（不是洞，但实施时会被漏掉）

- `m_unk_0x261f8 :: unsigned char[24460]` @0x261F8 实际是 `??_L(261F8, 131Ch, 5, sub_498C90, sub_498E60)` 的 **5 个 4,892B 记录**（5×0x131C=24,460）。
- `m_unk_0x2c48c :: unsigned char[2064]` @0x2C48C 实际是 `??_L(2C48C, 158h, 6, sub_43A770, sub_43A810)` 的 **6 个 344B 对象**。

这两段因为总长度与 ctor 完全一致，census 不计洞，但类型退化会让"成员归属/访问语义"无法建立。建议实施卡把它们当对象数组建模，并按 4,892B/344B 记录内部继续取证。

### 6.2 共用构建层归属（卡面③）

ctor `sub_498820` 的全部调用面是：`sub_43DCD0`（基类）+ `sub_4422E0`/`sub_43A770`/`sub_439030`/`sub_43DFC0`/`sub_4A12F0`/`sub_440740`/`sub_45ADD0`/`sub_43D830` 与 9 个 `??_L`；**没有**调用 #34 §5 的 8 对 StpCtl 函数（`sub_4826A0+sub_482BB0` 等）。因此本类 ctor 覆盖的段都是本类私有构造，**没有需要标"非私有"的段**。若 UI 卷宗认为某个 tab 页控件由共用层建，需要在 #38 清单落盘后用调用点补证，再回填本报告。

## 7. 与 PropUI / MainPropUI 的对比

| 维度 | PropUI | MainPropUI | EquipUI |
|---|---|---|---|
| 尺寸三证 | 注解 29,056 vs 分配 28,892（差 164） | 一致 219,984 | 一致 266,260 |
| 洞性质 | 真实残留（st_Manager 未建模 + 尾部越界 96B） | 成员表整体错位（步长/数组尺寸） | 漏对象（含 6×1208、UIRoleDialog）+ 尾部 80B |
| 首要动作 | 缩 size、补 st_Manager | 重排成员坐标 | 补 6 段对象 + 2 段去 byte 化 |

## 8. 验收检查点（≥5，实施卡交上来时逐条对）

1. `binary_size == 266,260` 且末对象/尾段止于 0x41014；`push 41014h` 仍全库唯一（`grep -c` = 1）。
2. `[2AFC4h]` 写点仍在 ctor 返回后（asm:240550 附近）；改动工厂顺序必须给反证。
3. 0x26C–0x1414 整段必须有对象：6×152 @0x294…、9×344 @0x624…、3×152 @0x123C/12E4/137C（含 0x12D4 的 16B 对齐），不能只留裸字段。
4. 0x25CA0 必须有 `UIRoleDialog`（0x558）；0x2DB10–0x2F760 必须是 6 个 1,208B 对象（`cls_43dfc0`），不是字节数组或空洞。
5. 0x261F8 的 24,460B 与 0x2C48C 的 2,064B 必须是对象数组（5×4,892 / 6×344），不能保留 `unsigned char[]`。
6. 洞字节只允许剩 0x40FC4–0x41014 的 80B；若报"0 洞"或"80B 也是成员"，需给 ctor/dtor 写点证据。
7. `bases` 保持 `UIListBox@0`；`vtables[0].base` 若改成 UIWnd/UIListBox 要有统一口径。
8. 实施后 `check` 不新增错误；不得借本卡顺带改 `st_Manager`（0x178/244B）等无关结构。

## 9. 未决（本卡不判）

1. **6×1,208B 对象是谁**：ctor 用 `sub_43DFC0`（= `cls_43dfc0`，UIListBox 1,208B 变体）构造 6 个，语义（装备栏页签？）需 UI 卷宗定名。
2. **共用构建层**：#38 报告未落盘，本卡只能以 ctor 调用面判定"本类无私有无归属问题"；#38 落盘后若出现本类 this 的 StpCtl 调用，需回填。
3. **4,892B 记录（0x131C）结构**：5 个记录内部字段未知，需 `sub_498C90/sub_498E60` 的访问面普查（与 MainPropUI 的 0x26FC 记录同族问题时一并做）。
4. **`UIFlexBar`(84B)@0x2D304、`UI3DCtrl`(308B)@0x2FCD0 的成员名**：ctor 身份已定，名字待 UI 语义。
5. **尾部 80B**：0x40FC4–0x41014 无 ctor 写点，也无 dtor 调用；是保留槽还是对齐填充，需 IDA UDT 或别的消费点证据。
6. **st_Manager@0x178（244B）内部**：本卡只确认它止于 0x26C，与洞起点一致；内部字段是否完整不在本卡范围。

## 10. 只读自证

- `git status --short`：本卡只新增 `?? docs/audit/2026-11-27-equipui-expectation-baseline.md`；`git diff data/annotations/structs/EquipUI.json` 为空。
- 未执行 `pipeline/cli.py apply/export/codegen/probe/match/loop`；`pal3/src` 无改动。
- 所有数字来自上述命令输出或 `original/PAL3.exe.asm` 行号（当前工作树）。
