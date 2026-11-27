# R7 三类落位执行清单（MainPropUI / EquipUI / LineupUI）

日期：2026-11-27 · 卡号 #51（tsk_01M8CK28M15ZXEHESHHFET）· 只读产出
模板：沿用 #48 PropUI 清单的六列（段偏移 / 长度 / 类型 / 拟用名 / 证据等级 / 证据指针）。

## §0 一句话用法与覆盖

编程侧按本文 §2 三张表逐行落位：`类型` 列已是可写进注解的形态，`拟用名` 只是候选（命名权在落位卡），`证据等级` 决定能不能直接落（<B 必须按 §3 补证）。三张表的段长求和分别等于三个类的真 sizeof（219,984 / 266,260 / 162,772），脚本逐行断言连续、无缺口（§5）。

数据来源：oracle（#39/#41/#42 的 ctor 建链与洞分解）+ 语义底稿（#40/#43/#44 的分区、形态、用途）+ #38 共用构建层归属表。**本卡不重现取证**，只把三套口径合并成一张可执行表；凡两套口径不一致处，以 asm 建链为准，并在 §7 写明差异。

## §1 证据分级（本文件口径）

| 等级 | 含义 | 落位时怎么用 |
|---|---|---|
| A | 构造器 + 类身份双证（ctor/`??_L` + vtable 或已知类尺寸吻合） | 可直接写类型 |
| A- | 构造器证据充分，类名为尺寸族名（`UIFrameContainer`/`UIButton` 族） | 可直接写类型；名字用族名 |
| B+ | 构造器 + 尺寸已证，但元素 vtable 未写（EquipUI 6×344） | 可写「N×尺寸」，元素类型待补 |
| B | 长度/构造器清楚，元素内部未拆（记录/缓冲/状态块） | 只写不透明块，禁拆子成员 |
| B- | 类型靠尺寸或注解推定，或段尾有未建字节 | 标「实施时需补证」，按 §3 补 |
| C | ctor 未构造或全方法零访问 | 不得落成员；先补证，或保留 gap |

规则：**<B（B-/C）一律在表内标「实施时需补证」，且 §3 给出取证入口；不得把候选类名当类型写进注解。**

## §2 三份执行清单

### MainPropUI

| # | 段偏移 | 长度(B) | 类型 | 拟用名 | 证据等级 | 证据指针 |
|---:|---|---:|---|---|---|---|
| 1 | 0x0 | 72 | UIListBox 基类 | （基类子对象） | A | sub_43DCD0 @asm212594 写 0x56AD20 |
| 2 | 0x48 | 288 | tagRECT + char[256]×2 + 16B 标量 | m_header | A- | asm212595–212604 内联写；DisplayCaption/Update/OnMessage 访问 |
| 3 | 0x168 | 24 | uchar[6]+uchar[1]+dword（页标志） | m_pageFlags | A- | asm212596–212604；OnMessage 26 / HandleKeyInput 7 |
| 4 | 0x180 | 152 | UIFrameContainer 152B | m_topFrame0 | A- | sub_4422E0 @asm212595；DisplayCaption 2 |
| 5 | 0x218 | 152 | UIFrameContainer 152B | m_topFrame1 | A- | sub_4422E0 @asm212606 |
| 6 | 0x2B0 | 152 | UIFrameContainer 152B | m_topFrame2 | A- | sub_4422E0 @asm212609；ShowSubPanels 2 |
| 7 | 0x348 | 152 | UIFrameContainer 152B（共用层页签栏左条） | —（共用层，不落成员） | A | sub_4422E0 + sub_491630 @asm213339 贴 StpBarL.tga |
| 8 | 0x3E0 | 152 | UIFrameContainer 152B（共用层页签栏中条） | —（共用层，不落成员） | A | sub_491630 @asm213359 贴 StpBarM.tga |
| 9 | 0x478 | 152 | UIFrameContainer 152B（共用层页签栏右条） | —（共用层，不落成员） | A | sub_491630 @asm213373 贴 StpBarR.tga |
| 10 | 0x510 | 3,096 | UIButton 344B ×9（共用层页签） | —（共用层，不落成员） | A | sub_43A770 @212621–645 9 处；sub_491630 @213402–213440 |
| 11 | 0x1128 | 152 | UIStatic 152B（共用层第 10 页签 Effect） | —（共用层，不落成员） | A | sub_4422E0 @212648；[0x1128] 走 CreateFromTemplate |
| 12 | 0x11C0 | 16 | 4×dword（共用层页签栏状态） | —（共用层，不落成员） | A- | A4 建栏 asm213436–213450 直写 |
| 13 | 0x11D0 | 152 | UIFrameContainer 152B | m_frame152_0 | A- | sub_4422E0 @asm212651；Update 1 |
| 14 | 0x1268 | 152 | UIFrameContainer 152B | m_frame152_1 | A- | sub_4422E0 @asm212654；Update 1 |
| 15 | 0x1300 | 74,752 | UIParticle[128]（584B×128） | m_particlePoolA | A- | ??_L @asm212660：248h×80h + sub_4B4690 |
| 16 | 0x13700 | 74,892 | UIParticle[128] + 140B 尾 | m_particlePoolB | A- | ??_L @asm212668；Render 5 / OnMessage 32（尾 140B 见 G7） |
| 17 | 0x25B8C | 49,916 | 5×0x26FC 页面记录（元素内部未拆） | m_pageRecords[5] | B | ??_L @asm212676；ShowSubPanels 14；首尾 16B 待核（G7） |
| 18 | 0x31E88 | 760 | UIFrameContainer 152B ×5 | m_frame152_grp2[5] | A- | sub_4422E0 @212681–693 |
| 19 | 0x32180 | 16 | 16B 未构造 | —（未构造）（实施时需补证） | C | G7：来源未定；补证：ctor 反汇编末段 + dtor 触达面 |
| 20 | 0x32190 | 4,260 | 5×852B 槽记录（3 dword+4 串+12 dword） | m_slotRecords[5] | B | 循环 5 次 @asm212696；用途 inferred（G2） |
| 21 | 0x33234 | 1,368 | UIRoleDialog 1368B | m_roleDialog | A | sub_4A12F0 @asm212739；vtable 0x56E190 |
| 22 | 0x3378C | 1,720 | UIButton 344B ×5 | m_btn344_grp3[5] | A- | ??_L @asm212744 |
| 23 | 0x33E44 | 912 | UIFrameContainer 152B ×6 | m_frame152_grp3[6] | A- | sub_4422E0 @212749–764 |
| 24 | 0x341D4 | 16 | 16B 未构造 | —（未构造）（实施时需补证） | C | G7；补证：ctor 反汇编末段 |
| 25 | 0x341E4 | 1,720 | UIButton 344B ×5 | m_btn344_grp4[5] | A- | ??_L @asm212770；DisplayCaption 索引触达 |
| 26 | 0x3489C | 4 | 1×dword（=-1） | m_gaugeIndex | A- | ctor @asm212772–775 写 [0x3489C]=-1 |
| 27 | 0x348A0 | 84 | 84B 控件（vtable 0x56ACFC，类名未证） | m_ctrl84（实施时需补证） | B- | sub_43D830 @asm212776；补证：0x56ACFC DATA XREF 与 84B 类登记 |
| 28 | 0x348F4 | 152 | UIFrameContainer 152B | m_frame152_2 | A- | sub_4422E0 @asm212780 |
| 29 | 0x3498C | 1,824 | UIFrameContainer 152B ×12 | m_frame152_grp4[12] | A- | ??_L @asm212786 |
| 30 | 0x350AC | 152 | UIFrameContainer 152B | m_frame152_3 | A- | sub_4422E0 @asm212791 |
| 31 | 0x35144 | 1,208 | cls_43dfc0 1208B（列表控件） | m_itemList | A- | sub_43DFC0 @asm212794；OnMessage 8 |
| 32 | 0x355FC | 20 | 1×dword(-1) + 16B 未构造 | m_listIndex（实施时需补证） | B- | ctor @212795–796；补证：16B 归属（dtor/方法访问面） |
| 33 | 0x35610 | 344 | UIButton 344B | m_btn344_5 | A- | sub_43A770 @asm212797 |
| 34 | 0x35768 | 344 | UIButton 344B | m_btn344_6 | A- | sub_43A770 @asm212801 |
| 35 | 0x358C0 | 344 | UIButton 344B | m_btn344_7 | A- | sub_43A770 @asm212804 |
| 36 | 0x35A18 | 4 | 1×dword（=-1） | m_scaleIndex | A- | ctor @asm212806 写 [0x35A18]=-1 |
| 37 | 0x35A1C | 308 | UI3DCtrl 308B（vtable 0x56AC20） | m_scaleCtrl | A- | sub_439030 @asm212807；OnMessage 15 |

**闭合校验**：行数 37，段长求和 **219,984 = 0x35B50**，连续断点 0。


### EquipUI

| # | 段偏移 | 长度(B) | 类型 | 拟用名 | 证据等级 | 证据指针 |
|---:|---|---:|---|---|---|---|
| 1 | 0x0 | 72 | UIListBox 基类 | （基类子对象） | A | sub_43DCD0 @asm223660 写 0x56AD20；本类 0x56E170 覆写 |
| 2 | 0x48 | 588 | tagRECT + char[256] + flags（588B） | m_header | A- | asm223669–681；Item\%s\%s.pol/.tga 拼接到 +0x68 |
| 3 | 0x294 | 152 | UIFrameContainer 152B | m_frame152_0 | A- | sub_4422E0 @asm223682 |
| 4 | 0x32C | 152 | UIFrameContainer 152B | m_frame152_1 | A- | sub_4422E0 @asm223685 |
| 5 | 0x3C4 | 152 | UIFrameContainer 152B | m_frame152_2 | A- | sub_4422E0 @asm223688 |
| 6 | 0x45C | 152 | UIFrameContainer 152B（共用层 StpBarL） | —（共用层，不落成员） | A | sub_4422E0 @223691；A5 sub_4993D0 贴 off_56D648 |
| 7 | 0x4F4 | 152 | UIFrameContainer 152B（共用层 StpBarM） | —（共用层，不落成员） | A | A5 贴 off_56D64C |
| 8 | 0x58C | 152 | UIFrameContainer 152B（共用层 StpBarR） | —（共用层，不落成员） | A | A5 贴 off_56D650 |
| 9 | 0x624 | 344 | UIButton 344B（共用层 State 页签） | —（共用层，不落成员） | A | A5 @224350 起；off_56D674 |
| 10 | 0x77C | 344 | UIButton 344B（共用层 Magic 页签） | —（共用层，不落成员） | A | off_56D678 |
| 11 | 0x8D4 | 344 | UIButton 344B（共用层 Equip 页签） | —（共用层，不落成员） | A | off_56D67C |
| 12 | 0xA2C | 344 | UIButton 344B（共用层 Prop 页签，身份页） | —（共用层，不落成员） | A | off_56D680；B5 用 UnProp.tga |
| 13 | 0xB84 | 344 | UIButton 344B（共用层 Sword 页签） | —（共用层，不落成员） | A | off_56D684；B5 受 byte_DE5F92 |
| 14 | 0xCDC | 344 | UIButton 344B（共用层 JusticeBook 页签） | —（共用层，不落成员） | A | off_56D688；B5 受 byte_DE5F93 |
| 15 | 0xE34 | 344 | UIButton 344B（共用层 Battle_Array 页签） | —（共用层，不落成员） | A | off_56D68C |
| 16 | 0xF8C | 344 | UIButton 344B（共用层 System 页签） | —（共用层，不落成员） | A | off_56D690 |
| 17 | 0x10E4 | 344 | UIButton 344B（共用层 Exit 页签） | —（共用层，不落成员） | A | off_56D694 |
| 18 | 0x123C | 152 | UIStatic 152B（共用层 Effect 页签） | —（共用层，不落成员） | A | off_56D658 |
| 19 | 0x12D4 | 16 | 4×dword（共用层页签栏状态） | —（共用层，不落成员） | A- | A5 写 [esi+12D4h] 起 |
| 20 | 0x12E4 | 152 | UIFrameContainer 152B | m_frame152_3 | A- | sub_4422E0 @asm223730；Update 1 |
| 21 | 0x137C | 152 | UIFrameContainer 152B | m_frame152_4 | A- | sub_4422E0 @asm223733 |
| 22 | 0x1414 | 74,752 | UIParticle[128]（584B×128） | m_particlePoolA | A- | ??_L @asm223736；InitParticleEffects/UpdateDisplay |
| 23 | 0x13814 | 74,752 | UIParticle[128]（584B×128） | m_particlePoolB | A- | ??_L @asm223744；仅 ctor/dtor |
| 24 | 0x25C14 | 140 | 140B 特效/渲染状态区 | m_fxState | B | asm223863 清 2 dword；OnMessage 33 / Render 5；内部未拆 |
| 25 | 0x25CA0 | 1,368 | UIRoleDialog 1368B | m_roleDialog | A | sub_4A12F0 @asm223749；vtable 0x56E190 |
| 26 | 0x261F8 | 24,460 | 5×0x131C 记录（元素内部未拆） | m_pageRecords[5] | B | ??_L @asm223755；OnMessage 5；字段语义未证 |
| 27 | 0x2C184 | 152 | UIFrameContainer 152B | m_frame152_5 | A- | sub_4422E0 @asm223760 |
| 28 | 0x2C21C | 152 | UIFrameContainer 152B | m_frame152_6 | A- | sub_4422E0 @asm223763 |
| 29 | 0x2C2B4 | 168 | UIFrameContainer 152B + 16B 尾 | m_frame152_7（实施时需补证） | B- | sub_4422E0 @asm223766；补证：16B 尾归属 |
| 30 | 0x2C35C | 152 | UIFrameContainer 152B | m_frame152_8 | A- | sub_4422E0 @asm223769 |
| 31 | 0x2C3F4 | 152 | UIFrameContainer 152B | m_frame152_9 | A- | sub_4422E0 @asm223772 |
| 32 | 0x2C48C | 2,064 | 6×344B 控件（ctor 未写 vtable） | m_ctrl344_grp | B+ | ??_L @asm223778；类型靠 344B 尺寸推定；补证：元素 vtable |
| 33 | 0x2CC9C | 1,488 | 6×UIPushButton 248B | m_pushButtons[6] | A- | ??_L @asm223786 |
| 34 | 0x2D26C | 152 | UIFrameContainer 152B | m_frame152_10 | A- | sub_4422E0 @asm223791 |
| 35 | 0x2D304 | 84 | 84B 控件（vtable 0x56ACFC，类名未证） | m_ctrl84（实施时需补证） | B- | sub_43D830 @asm223794；注解记 UI3DCtrl(308) 不符（G6）；补证：0x56ACFC DATA XREF |
| 36 | 0x2D358 | 152 | UIFrameContainer 152B | m_frame152_11 | A- | sub_4422E0 @asm223797 |
| 37 | 0x2D3F0 | 1,824 | UIFrameContainer 152B ×12 | m_frame152_grp2[12] | A- | ??_L @asm223803 |
| 38 | 0x2DB10 | 7,248 | cls_43dfc0 1208B ×6（对话框） | m_dialogs[6] | A- | 6×sub_43DFC0 @223808–823；vtable 0x56AD40 |
| 39 | 0x2F760 | 260 | 5×52B tagPlayerSet | m_playerSets[5] | B | ??_L @asm223829；无本类方法访问 |
| 40 | 0x2F864 | 96 | 96B 未构造 | —（未构造）（实施时需补证） | C | G4；补证：ctor 覆盖 + 方法访问面 |
| 41 | 0x2F8C4 | 344 | UIButton 344B | m_btn344_0 | A- | sub_43A770 @asm223834 |
| 42 | 0x2FA1C | 344 | UIButton 344B | m_btn344_1 | A- | sub_43A770 @asm223837 |
| 43 | 0x2FB74 | 344 | UIButton 344B | m_btn344_2 | A- | sub_43A770 @asm223840 |
| 44 | 0x2FCCC | 4 | 1×dword（=-1） | m_sentinel | A- | asm223843 写 [0x2FCCC]=-1；OnMessage 3 |
| 45 | 0x2FCD0 | 308 | UI3DCtrl 308B（vtable 0x56AC20） | m_progressCtrl | A- | sub_439030 @asm223850；OnMessage 7 |
| 46 | 0x2FE04 | 35,040 | UIParticle[60]（584B×60） | m_particlePoolC | A- | ??_L @asm223859；HandleInput 34 / ResetProgressList 5 |
| 47 | 0x386E4 | 35,040 | UIParticle[60]（584B×60） | m_particlePoolD | A- | ??_L @asm223863；Render 1 |
| 48 | 0x40FC4 | 80 | 80B 尾块未构造 | —（未构造）（实施时需补证） | C | G4；census 最后一段洞；补证：ctor 零写 + 方法零访问已核，须判是否属下一对象 |

**闭合校验**：行数 48，段长求和 **266,260 = 0x41014**，连续断点 0。


### LineupUI

| # | 段偏移 | 长度(B) | 类型 | 拟用名 | 证据等级 | 证据指针 |
|---:|---|---:|---|---|---|---|
| 1 | 0x0 | 72 | UIListBox 基类（注解写 UIFrameWnd，见 G） | （基类子对象） | A | sub_43DCD0 @asm187101 写 0x56AD20 |
| 2 | 0x48 | 296 | 头块 296B：rect/800×600/i,j/buf[256]/m_Is[5] | m_header | A- | asm187104–187119；OnMessage 10 / ctor 5 |
| 3 | 0x170 | 152 | 152B 容器（共用层 A1 页签栏） | —（共用层，不落成员） | A | A1 sub_4826A0；ctor 只建空容器，运行期灌入 |
| 4 | 0x208 | 152 | 152B 容器（共用层 A1 页签栏） | —（共用层，不落成员） | A | 同上 |
| 5 | 0x2A0 | 152 | 152B 容器（共用层 StpBarL） | —（共用层，不落成员） | A | A1 落点 0x2A0；StpBarL.tga |
| 6 | 0x338 | 152 | 152B 容器（共用层 StpBarM） | —（共用层，不落成员） | A | A1 落点 0x338；StpBarM.tga |
| 7 | 0x3D0 | 152 | 152B 容器（共用层 StpBarR） | —（共用层，不落成员） | A | A1 落点 0x3D0；StpBarR.tga |
| 8 | 0x468 | 344 | UIButton 344B（共用层 State 页签） | —（共用层，不落成员） | A | A1 落点 0x468；off_56B8DC |
| 9 | 0x5C0 | 344 | UIButton 344B（共用层 Magic 页签） | —（共用层，不落成员） | A | A1 落点 0x5C0 |
| 10 | 0x718 | 344 | UIButton 344B（共用层 Equip 页签） | —（共用层，不落成员） | A | A1 落点 0x718 |
| 11 | 0x870 | 344 | UIButton 344B（共用层 Prop 页签） | —（共用层，不落成员） | A | A1 落点 0x870 |
| 12 | 0x9C8 | 344 | UIButton 344B（共用层 Sword 页签） | —（共用层，不落成员） | A | A1 落点 0x9C8；B1 受 byte_DE5F92 |
| 13 | 0xB20 | 344 | UIButton 344B（共用层 JusticeBook 页签，身份页） | —（共用层，不落成员） | A | A1 落点 0xB20；B1 受 byte_DE5F93 |
| 14 | 0xC78 | 344 | UIButton 344B（共用层 Battle_Array 页签） | —（共用层，不落成员） | A | A1 落点 0xC78 |
| 15 | 0xDD0 | 344 | UIButton 344B（共用层 System 页签） | —（共用层，不落成员） | A | A1 落点 0xDD0 |
| 16 | 0xF28 | 344 | UIButton 344B（共用层 Exit 页签） | —（共用层，不落成员） | A | A1 落点 0xF28 |
| 17 | 0x1080 | 152 | UIStatic 152B（共用层 Effect 页签） | —（共用层，不落成员） | A | A1 落点 0x1080 |
| 18 | 0x1118 | 16 | 4×dword（共用层页签栏状态） | —（共用层，不落成员） | A- | A1 写 0x1118–0x1124 |
| 19 | 0x1128 | 152 | UIFrameContainer 152B | m_frame152_0 | A- | sub_4422E0 @asm187154；Update 1 |
| 20 | 0x11C0 | 152 | UIFrameContainer 152B | m_frame152_1 | A- | sub_4422E0 @asm187157；Update 1 |
| 21 | 0x1258 | 74,752 | UIParticle[128]（584B×128） | m_particlePoolA | A- | ??_L @asm187165–172 |
| 22 | 0x13658 | 74,752 | UIParticle[128]（584B×128） | m_particlePoolB | A- | ??_L @asm187173–180 |
| 23 | 0x25A58 | 128 | 128B 未构造 | —（未构造）（实施时需补证） | C | 补证：ctor 未建、方法访问面；属对齐还是下一对象前置 |
| 24 | 0x25AD8 | 12 | 8B 数组 + 4B 索引 | m_stateArray | B | asm187248 写 [0x25AE0]；Render 按索引取 [0x25AD8+eax] |
| 25 | 0x25AE4 | 308 | UI3DCtrl 308B | m_ctrl308_0 | A- | sub_439030 @asm187182；Update 3 / OnMessage 22 |
| 26 | 0x25C18 | 308 | UI3DCtrl 308B | m_ctrl308_1 | A- | sub_439030 @asm187185；Update 2 |
| 27 | 0x25D4C | 152 | UIFrameContainer 152B | m_frame152_2 | A- | sub_4422E0 @asm187188 |
| 28 | 0x25DE4 | 152 | UIFrameContainer 152B | m_frame152_3 | A- | sub_4422E0 @asm187191 |
| 29 | 0x25E7C | 152 | UIFrameContainer 152B | m_frame152_4 | A- | sub_4422E0 @asm187194 |
| 30 | 0x25F14 | 760 | UIFrameContainer 152B ×5 | m_frame152_grp2[5] | A- | sub_4422E0 @asm187196–203 |
| 31 | 0x2620C | 760 | UIFrameContainer 152B ×5 | m_frame152_grp3[5] | A- | sub_4422E0 @asm187204–211 |
| 32 | 0x26504 | 608 | UIFrameContainer 152B ×4 | m_frame152_grp4[4] | A- | sub_4422E0 @asm187212–219 |
| 33 | 0x26764 | 64 | 64B 未构造 | —（未构造）（实施时需补证） | C | 补证：ctor 未建、方法访问面 |
| 34 | 0x267A4 | 152 | UIFrameContainer 152B | m_frame152_5 | A- | sub_4422E0 @asm187221 |
| 35 | 0x2683C | 152 | UIFrameContainer 152B | m_frame152_6 | A- | sub_4422E0 @asm187224 |
| 36 | 0x268D4 | 344 | UIButton 344B | m_btn344_0 | A- | sub_43A770 @asm187227；Update 3 / OnMessage 3 |
| 37 | 0x26A2C | 344 | UIButton 344B | m_btn344_1 | A- | sub_43A770 @asm187230；Update 3 / OnMessage 1 |
| 38 | 0x26B84 | 248 | UIPushButton 248B | m_btn248_0 | A- | sub_440740 @asm187233；OnMessage 26 |
| 39 | 0x26C7C | 248 | UIPushButton 248B | m_btn248_1 | A- | sub_440740 @asm187236；OnMessage 28 |
| 40 | 0x26D74 | 248 | UIPushButton 248B | m_btn248_2 | A- | sub_440740 @asm187239；OnMessage 26 |
| 41 | 0x26E6C | 248 | UIPushButton 248B | m_btn248_3 | A- | sub_440740 @asm187242；OnMessage 26 |
| 42 | 0x26F64 | 248 | UIPushButton 248B | m_btn248_4 | A- | sub_440740 @asm187245；OnMessage 26 |
| 43 | 0x2705C | 248 | UIPushButton 248B | m_btn248_5 | A- | sub_440740 @asm187248；OnMessage 26 |
| 44 | 0x27154 | 2,432 | 2432B 清零缓冲区 | m_clearBuffer | B | sub_47EC00 @asm187249（this 在 edx）；内部未拆 |
| 45 | 0x27AD4 | 256 | 256B 状态块 | m_stateBlock | B | sub_47EC00 写 0x27AD4..；Update 19 / OnMessage 135 |

**闭合校验**：行数 45，段长求和 **162,772 = 0x27BD4**，连续断点 0。

## §3 补证入口（<B 段逐条）

### MainPropUI（37 行，A 7 / A- 24 / B 2 / B- 2 / C 2）

| 段 | 偏移/长度 | 缺什么 | 取证入口 |
|---|---|---|---|
| 19 | 0x32180 / 16B | 未构造块的来源（G7） | 重读 ctor `sub_4909F0` 尾段 asm212800–212832 与 dtor `sub_4912D0`；若两侧都不写，判为对齐并写注释 |
| 24 | 0x341d4 / 16B | 同上（G7） | 同上 |
| 17 | 0x25b8c / 49,916B | 5×0x26FC 元素内部未拆；`0x25B8C+5×0x26FC=0x31E84` 与下一段 0x31E88 差 4B | dump 元素首 0x30 字节找类型/计数；查 `ShowSubPanels` 的索引步长 |
| 20 | 0x32190 / 4,260B | 5×852B 记录的 4 个字符串未命名（用途 inferred） | 从 5 条记录的 +6/+0x200/+0x21E/+0x252 取字面量（预期为条目 id/名称） |
| 27 | 0x348a0 / 84B | 类名未证（注解记 `UI3DCtrl` 308B，实为 84B） | `0x56ACFC` 的 DATA XREF + 84B 类登记（疑 `UIFlexBar`） |
| 32 | 0x355fc / 20B | 尾 16B 未建 | 查 `OnMessage` 对 `[esi+35600h]` 附近访问面 |

### EquipUI（48 行，A 15 / A- 25 / B+ 1 / B 3 / B- 2 / C 2）

| 段 | 偏移/长度 | 缺什么 | 取证入口 |
|---|---|---|---|
| 26 | 0x261f8 / 24,460B | 5×0x131C 元素内部未拆（注解写成 `unsigned char[]`） | 元素首 0x40 字节 dump + `OnMessage` 5 处索引步长 |
| 28 | 0x2c2b4 / 168B | 152B 容器 + 16B 尾的尾归属 | 查 dtor 与 `OnMessage` 1 处访问 |
| 32 | 0x2c48c / 2,064B | 6×344B 元素 vtable 未写，类型只能按 344 推 | 查元素初始化是否由外部代码写表（跨宿主） |
| 35 | 0x2d304 / 84B | 类名未证（`0x56ACFC`） | 同 MainPropUI 段 27 |
| 39 | 0x2f760 / 260B | 5×52B `tagPlayerSet` 用途未证 | 找写入者（全局设置/存档） |
| 40 | 0x2f864 / 96B | ctor 未构造、方法未访问（G4） | ctor 全段重扫 + 方法访问面；判对齐或前置 |
| 48 | 0x40fc4 / 80B | 尾块零访问（G4，census 最后一段洞） | 同上；须判是否属下一个对象 |

### LineupUI（45 行，A 16 / A- 24 / B 3 / C 2）

| 段 | 偏移/长度 | 缺什么 | 取证入口 |
|---|---|---|---|
| 23 | 0x25a58 / 128B | 未构造 | ctor `sub_47E5C0` 尾段与 dtor 重扫；判对齐 |
| 24 | 0x25ad8 / 12B | 8B 数组 + 4B 索引的元素语义 | `Render` 对 `[esi+eax+25AD8h]` 的取值去向 |
| 33 | 0x26764 / 64B | 未构造 | 同段 23 |
| 44 | 0x27154 / 2,432B | `sub_47EC00` 清零缓冲区内部未拆 | dump 首 0x40 字节；查 OnMessage 是否按字段写 |
| 45 | 0x27ad4 / 256B | 状态块字段语义（OnMessage 135 处） | 按 `sub_47EC00` 写入点与消息号分组 |

## §4 共用构建层「不落成员」表

三类的页签栏都由 #38 的 A/B 族函数在运行期灌入，**ctor 只建空容器**；落位时不得写成私有成员。

| 类 | 段 | 控件 | 归属 | 落位处理 |
|---|---|---|---|---|
| MainPropUI | 7–9 | 152B ×3（`StpBarL/M/R`） | 共用层 A4（`sub_491630`） | 不落成员；页签栏整体按共用层结构体内嵌，父指针由 A4 持有 |
| MainPropUI | 10 | 344B ×9（9 个页签） | 同上 | 同上；其中 Equip 页签为身份页（+0x7C0） |
| MainPropUI | 11 | 152B ×1（Effect 页签） | 同上 | 同上；注意它是 152B，不能并进 344B 数组 |
| MainPropUI | 12 | 16B 状态块 | 同上 | 同上 |
| EquipUI | 6–8 | 152B ×3（`StpBar`） | 共用层 A5（`sub_4993D0`） | 不落成员；父链 `[2AFC4]`→wrapper `sub_49F2E0`→A5 |
| EquipUI | 9–18 | 344B ×9 + 152B ×1（10 页签） | 同上 | 同上；身份页 = Prop |
| EquipUI | 19 | 16B 状态块 | 同上 | 同上 |
| LineupUI | 3–4 | 152B ×2（页签栏容器） | 共用层 A1（`sub_4826A0`） | 不落成员；父链 `[2AFBC]`→`sub_47F590`→A1 |
| LineupUI | 5–7 | 152B ×3（`StpBar`） | 同上 | 同上 |
| LineupUI | 8–17 | 344B ×9 + 152B ×1（10 页签） | 同上 | 同上；身份页 = JusticeBook |
| LineupUI | 18 | 16B 状态块 | 同上 | 同上 |

**通用规则**：若落位卡坚持要有一个成员，只能建「页签栏实例」一个指针（或按共用层结构体整体内嵌），并把 13/14 个控件留在共用层，不能拆成 13 个私有成员。

## §5 尺寸闭合与口径差异（脚本实跑）

| 类 | 清单行数 | 求和 | 真 sizeof | 连续断点 | 说明 |
|---|---:|---:|---:|---:|---|
| MainPropUI | 37 | 219,984 = 0x35B50 | 219,984 | 0 | 比 oracle 的 30 段更细（拆开 6×152、9×344、5×152 等）；无差额 |
| EquipUI | 48 | 266,260 = 0x41014 | 266,260 | 0 | 比 oracle 的 39 段细；两类差额均为拆分口径，不是尺寸争议 |
| LineupUI | 45 | 162,772 = 0x27BD4 | 162,772 | 0 | 含 220B 对齐（16+140+64）与 128B 未构造段，三者都在 ctor 建链区间内 |

复现方式：本文件表格由 `docs/audit/2026-11-27-r7-manifest-gen.py` 从两份底稿的段表生成（长度取底稿数值），逐行断言 `off==上一段 end` 与总和：

```
python3 docs/audit/2026-11-27-r7-manifest-gen.py
# 输出 [MainPropUI] rows=37 sum=219984 bad=0
#      [EquipUI]  rows=48 sum=266260 bad=0
#      [LineupUI] rows=45 sum=162772 bad=0
```

脚本只读、无第三方依赖；表格本身是脚本输出的副本，不是手抄。

## §6 实施顺序与验收检查点

**建议顺序**：MainPropUI → EquipUI → LineupUI。理由：MainPropUI 的 A/A- 占比最高（31/37）、无 bases 争议；EquipUI 有两段类型退化需要同时处理；LineupUI 的 bases 口径（UIFrameWnd vs UIListBox）未决，放在最后可避免与前三类抢 bases 晶格。

每类固定五步：
1. 先改 `binary_size` / `bases`（如需），过 `check`；
2. 按 §2 表落 A/A- 段（类型+名）；
3. B/B+/B- 段按「不透明块 + 尺寸」落，不拆子成员；
4. 共用层段按 §4 处理（不落成员）；
5. 跑 `check → loop → verify_fix`，洞面预期：落位后残余洞应只剩 §2 中标 C 的未构造段（MainPropUI 32B、EquipUI 176B、LineupUI 192B，合计 400B）。

**9 条验收检查点**：
1. 每类清单行数与段长求和同 §5；实施卡改完后 `sizeof` 与清单一致；
2. §4 的共用层控件在该类注解中**零成员**；
3. 所有 <B 段都带「实施时需补证」且指向 §3 入口；
4. 未构造段（C）不得凭空造成员，保留 gap 注释；
5. 基类口径统一（EquipUI=`UIListBox`；LineupUI 先裁 UIFrameWnd/UIListBox 再落）；
6. 落位后 census 洞字节 ≈ 未构造段之和（400B 量级），不出现「100% 洞」类整类计洞；
7. `check` 0 new errors；
8. `loop` S2 不降、L1 不降（当前 S2 158/229、棘轮 L1 189）；
9. `verify_fix --class <Cls>` 通过后才提交。

## §7 已知缺口（显式挂账，不藏正文）

### EquipUI
- **漏建 UIRoleDialog@0x25CA0（1,368B）**：ctor 表段 25 有、注解无；落位必须补。
- **漏建 6×cls_43dfc0@0x2DB10（7,248B）**：表段 38；注解把该区当洞。
- **漏建整段 0x26C–0x1414**：含私有段 3–5、20、21 与共用层 6–19；注解在 0x26C 后直接跳到 0x1414 的粒子池。
- 两段类型退化：段 26（0x261F8，24,460B=5×0x131C）与段 32（0x2C48C，2,064B=6×344）现被写成 `unsigned char[]`，落位时须按记录/对象拆。

### LineupUI
- **`m_btnPar`/`m_btnPar2` 112×584 vs ctor 两个 128×584 向量**：注解少 16 元素/组，stride 一致；落位按 128 写，并注明注解旧值。
- **尾块 0x27154–0x27BD4 由 `sub_47EC00` 初始化**：不是 ctor 内联写，注解把这段当洞；落位须建 2,432B 缓冲 + 256B 状态块两段，或整体不透明块 + 注释。
- **bases 口径未决**：注解 `UIFrameWnd@0`，ctor 首调 `sub_43DCD0` 写 `0x56AD20`（72B `UIListBox` 表）；改 bases 需另证（两者同 72B），落位卡不得顺手改。

### MainPropUI
- 注解 21 个 8B 洞的成因是「成员起点 0x298/步长 0xA0」vs ctor「0x180/0x98」——落位必须按 ctor 表重写，旧成员整体替换，不能逐个补 8B。
- `m_btnPar/m_btnPar2` 16×7=112 与 ctor 128 不符；`m_Role` `p_RoleState[5]@0x22728` 与 ctor 5×0x26FC@0x25B8C 不符；`m_Dlg` `MUIDialog(1288)` 与 ctor `UIRoleDialog(1368)@0x33234` 家族冲突。
- 尾部 0x33D1C–0x35B50（7,732B）在注解中无 owner（`m_parSingle` 只到 0x33D1C）。

## §8 未决（不在本卡解决）

1. MainPropUI 段 15/16 是否「按钮特效」用途（现只到形态级）。
2. MainPropUI 段 17 首元素是否含 624B 前置（0x26FC×5 与段长差 16B 的第二种解释）。
3. EquipUI 段 32 的 344B 元素 vtable（ctor 未写，类型只能按尺寸）。
4. EquipUI 两段 84B/96B/80B 的归属（类名与是否对齐）。
5. LineupUI bases 口径（UIFrameWnd vs UIListBox）。
6. LineupUI 段 3–4 两个 152B 容器在 A1 里的确切角色（页签栏容器还是标题条）。
7. 三类拟用名均为形态直译候选，最终命名由落位卡按命名铁律裁定。

## §9 只读自证

- 未改任何 `data/annotations/`、`pal3/src/`、基线或 `data/status/` 产物；本卡写面仅 `docs/audit/`。
- 未运行 `pipeline/cli.py` 任何子命令（本文件所有数字来自已提交产物与 asm 文本）。
- 生成脚本为一次性只读解析（读两份底稿的段表 + 输出 markdown），未写回仓库。
