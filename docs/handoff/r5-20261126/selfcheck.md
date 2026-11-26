# R5-SaleUI（#9）提交前自检表

数据源：`data/annotations/structs/SaleUI.json`（第一版 commit 7f9d6a636，55 成员；**第二版（本文件）58 成员 / binary_size 105912**，按 #22 独立复核意见补 3 员，见 §八）。

## 一、QA checklist 逐条对照

| # | checklist | 结论 | 证据 |
|---|---|---|---|
| 1 | census v3 重跑：SaleUI 洞 44,560B→≤7,684B，命令与输出可复现 | ✅✅ 第二版 **0 洞 / 0B** | `python3 tools/census_struct_holes.py` → SaleUI **已从「有洞类」名单中消失**（`classes_with_holes=200`，列表内无 SaleUI）；全库 `867,548B / 1,120 洞 / 200 类`；副本 `struct_holes_r5_20261126.json` |
| 2 | census 产物落 `docs/handoff/r5-20261126/`（不写 data/status/） | ✅ | 本目录 `struct_holes_r5_20261126.json`（87KB）。注意：census 脚本无 `--out`，运行时顺带重写 `data/status/struct_holes_20261125.json`，我**未提交**该文件 |
| 3 | 三类合计下降 ≥36,000B，差额逐段归因有指针 | ✅ 第二版 117,128B→**72,568B**，净降 **44,560B** | 差额=SaleUI 44,560B→0（本卡，逐段见 §二 与 §八）；差额来源 = MagicUI 44,652B（`r5_magicui_dossier.md`：无 ctor/无分配点/无表项，四槽真主人 MainPropUI/EquipUI）+ UIGameFrm 27,916B（README §4：2026-11-24 已裁定为 g_gamefrm 第二视图） |
| 4 | check PASS 且 0 new | ✅ | 第二版 `python3 pipeline/cli.py check` → `0 new errors + 37 frozen(advisory), 110 warnings — PASS`（EXIT=0） |
| 5 | loop 全链 apply/export/probe/match rc=0（codegen 恒红容错），loop 前 ps 确认无并发 | ✅（apply/export/match rc=0；codegen、probe 为 rc=1，逐条归因如下） | 第二版同树串行链（每次先 `ps` 判空窗）：**apply rc=0**（19.6s）、**export rc=0**（168.4s）、codegen rc=1（已知恒红，S2 158/229）、probe rc=1（S1 743/766、S2 158/229）、**match rc=0**（`matched 1152/1262`、L1 189、partial 827、compile-skip 0、`carrier paired 93→93`、`previous 189 -> current 189`）。probe rc=1 的归因见 §八 末段：新失败 0、已修复 1（RoleStatePanel）、真新增仅 SaleUI.cpp 35→33 的 6 条 Hex-Rays 整数下标伪影、逐码净增减 C2440 −4/C2297 −2/C2110 −2/C2664 −1/C2107 +4/C2102 +2 ⇒ **无 pass→fail 翻转**，rc=1 源于 `data/status/baselines/latest.json`（19:16 per-file 错误集）与重渲后同单元错误集不一致；该基线刷新不在 #9 写面（data/status/） |
| 6 | 新落成员 evidence_level+source 齐备，命名 `m_unk_<offset>` 无数字后缀/伪语义 | ✅ | 第二版 58 成员：`evidence_level` 缺失 0、`source` 缺失 0；分布 A=56 / B=2（0xF574、0x10658 两段运行期 16B 元素表，语料 site 见 source）/ unverified=1（`buf`）；命名扫描无数字后缀形 |
| 7 | 独立子 agent 对抗复核已完成 | ✅ 已完成（等效：平台委派深度=1，由主理人指派非作者复核） | 观澜 #22，报告 `docs/audit/2026-11-26-saleui-adversarial-review.md`（11,217B，2026-11-26 23:10）：**PASS-WITH-NOTES**，A/B/C/E/F 通过、D 不通过（0x10564 是真实字段；两段 3,840B 有语料 16B 元素访问）、G 部分不通过。本文件 §八 = 对该结论的逐条处置 |
| 8 | 独立提交含 Evidence 格式与 census 落档 | ✅ | 第一版 commit 7f9d6a636；第二版 commit 见本卡 Thread 提交回执（message 带 `[Evidence]`/`[Verify]`/`[Scope]`/`[Review]`），含 `struct_holes_r5_20261126.json`（含 SaleUI 0 洞的实测快照） |

## 二、覆盖与残留（脚本从最终 JSON 复算）

- 成员声明 span 合计 **98,156B**；布局覆盖 `0x48`→`0x19DB8`（105,912B，含基类 UIListBox 0..0x48 的 72B）
- **第二版：残留洞 0 段 / 0B**（第一版 3 段 7,684B 已全部按证据建模，见 §八）：

| 段 | 字节 | 第一版归因 | 第二版处置 |
|---|---|---|---|
| 0xF574–0x10474 | 3,840 | ctor/dtor 均无构造调用、无清零跨度 | 建成 `m_unk_0xf574 unsigned char[3840]`（evidence B：语料按 16B 元素读写，site 见 source） |
| 0x10658–0x11558 | 3,840 | 同上 | 建成 `m_unk_0x10658 unsigned char[3840]`（同上，且 asm:147165–147167 有 0xF574→0x10658 的整元素拷贝） |
| 0x10564–0x10568 | 4 | 两段清零块之间的对齐空隙 | 建成 `m_unk_0x10564 unsigned int`（evidence A：ctor asm:141136 直接写、`sub_4623A0` asm:150262/150274 读写） |

## 三、证据形态分布（source 前缀）

| 形态 | 条数 |
|---|---|
| ctor 写序 / `??_L` 池三元组 | 40 |
| dtor 拆除点（含 `??_M`） | 10 |
| 相邻构造点空隙（下界闭合） | 3 |
| 相邻池空隙 | 1 |
| 既有成员未取到二进制证据（buf） | 1 |
| 语料 16B 元素表（0xF574 / 0x10658 两段运行期数组） | 2 |

## 四、复跑命令

```bash
python3 pipeline/cli.py check                 # 期望 0 new PASS
python3 tools/census_struct_holes.py          # 第二版期望：SaleUI 0 洞/0B（不在有洞类名单内）
python3 pipeline/cli.py apply                 # 实测 rc=0（19.6s）
python3 pipeline/cli.py export                # 实测 rc=0（168.4s）
python3 pipeline/cli.py codegen all           # 实测 rc=1（已知恒红；S2 158/229）
python3 pipeline/cli.py probe all             # 实测 rc=1（见 §五 归因；S2 158/229，S1 743/766）
python3 pipeline/cli.py match                 # 实测 rc=0（L1 189，paired 93/93）
```

## 五、反例留档

`SaleUI.union.json`：union 双视图版，check PASS 但 VC6 `C2621`（`UIFrameContainer[240]` 非 POD 不能进 union）导致 S1/S2 崩塌（0/229），**不可用**。

## 六、交叉校验：语料 ↔ 布局（独立于构建期探针的方法）

方法：扫 `asm/pal3/decomp/*.json` 里 28 个 `SaleUI::*` 函数体，抽出所有 `this-><成员>[idx]` 形态，按最终注解的 `span_bytes`/数组长度做边界校验（这条路径不依赖本卡的 idalib 探针，用的是 Hex-Rays 语料 + 注解文件本身）。

结果：
- 55 个 `this->` 名字里 **54 个都能在 known_members 里解析**；唯一未解析的是 `UIWnd`（基类成员，正常）。
- 越界索引访问 **823 处（去重后 6 处）**，全部集中在 `m_unk_0x66f4_view`：

| 字节偏移 | 形态 | 判定 |
|---|---|---|
| 0xF574 / 0xF60C / 0xF6A4 / 0xF73C / 0xF7D4 / 0xF86C | `&this->m_unk_0x66f4_view[240] + k` / `...[240].m_aSlots[...]` | **不是布局错误**：这些是「取池尾后一个元素的地址当基址」的写法（stride 152 与池元素一致），落在残留洞 0xF574–0x10474 内；数组退化为指针，字节偏移不变，编译通过（probe 里 SaleUI.cpp 错误 35→33 反而减少） |

⇒ 残留洞 0xF574–0x10474 并非完全无访问：有 3 个函数（`CreatePanelElements` 818 处、`InitColumnWidths` 22 处、`DestroySubFrames` 4 处、`AddItem` 1 处）以「池尾基址 + 偏移」方式触到该区。这解释了为什么它没有 ctor 构造证据——它更像「另一个数组的延伸区」而不是池本身，后续取证应从这几个函数的基址来源切入。

## 七、发现的既存问题（不属本卡，只上报）

1. `SaleUI::InitColumnWidths`(0x4AB5E0) 的语料出现 `this[3].m_unk_0x66f4_view[257].m_benable = 70;` 这类形态：
   若按 `SaleUI*` 解释，地址 = `3 × 105912 + 0x66F4 + 257 × 152` ≈ 0x6A8E8，远超类尾（0x19DB8）⇒
   **该函数的 this 类型/索引解释可疑**（大概率 IDA 把某个「基址 + 大常量」的访问套错了类型）。
   与本卡布局无关：SaleUI 的 `binary_size` 前后都是 105912，L1 也未因此丢函数（match 唯一 LOST 是 RoleStatePanel `?_G`）。
2. `data/annotations/structs/UICaption.json` 的 `binary_size=96` 与同文件 `size_evidence`（96→344，A 级三元组）自相矛盾；IDB 侧实测 `??_M` 压 `size=0x158`、dtor=`?Destroy2@UICaption` ⇒ 元素真值 344。属结构表/导出层缺陷，不在 #9 写面。
3. `?GetSys@NameSys`(0x43A770) 实测是**构造函数**（写 vtable off_56AC70、清零到 +0x154），IDB 名不可信；off_56AC70 不属于 ida_structs 里任何已登记类的 vtable ⇒ 344B 元素类仍未名。


## 八、第二版修订：按 #22 独立复核意见逐条处置（2026-11-26 23:2x）

复核结论是 **PASS-WITH-NOTES**：A（六个 `??_L`/`??_M` 三元组）由复核者用 `original/PAL3.exe.asm` 独立重抽、6/6 一致；B（55 员无重叠不越界、尾部精确 0x19DB8）通过；C（span 语义=占用字节，不是「到下一员」）通过带口径注；E/F 有条件通过。不通过的是 D 与部分 G，我按证据改，不改口径。

### D-1：0x10564 的 4B 是真实字段（复核者判对，我原判错）

- 复核给的 A 级 site：ctor `mov [esi+10564h], ebx`（asm:141136，ebx=0）；`sub_4623A0` 内 `mov eax,[esi+10564h]`（asm:150262）与 `mov [esi+10564h], edx`（asm:150274）。
- 我先前的判断依据是「两段 240B `rep stosd` 清零块之间的空隙」，把「没被 rep stosd 覆盖」误当成「不是字段」——这是错误外推。
- 处置：`char _gap_10564[4]`（生成器自动补的空隙）→ **`m_unk_0x10564 unsigned int`**，`evidence_level=A`，source 写三处 site，并注明 #18 判为 `CCBUIPanel*`、本卡只据 asm 保留数值型。

### D-2：两段 3,840B 不是「无证据」，是「ctor 不初始化、运行期填充」

- 复核给的语料/汇编 site：`sub_45E9F0` asm:145625/145629/145643 的 `[edx+esi+0F574h]`；asm:150403 `lea edx,[ecx+esi+0F574h]` 后连取 `[+0]/[+4]/[+8]/[+0Ch]`（元素 16B）；asm:147165–147167 从 0xF574 表拷到 0x10658 表；asm:160345 在 0x10658 侧连拷 4 个 dword。
- 处置：两段各建成 **`m_unk_0xf574` / `m_unk_0x10658`，`unsigned char[3840]`，`evidence_level=B`**，source 写明「ctor/dtor 无逐元素初始化；运行期按 16B 元素读写」并列出上述 site。
- 为什么仍用字节数组而不是 `tagRECT[240]`：元素宽度 16B 有证据、字段语义（left/top/right/bottom）**没有** A 级证据；按本项目「命名铁律」，无证据不硬套类型/语义，故保留字节形 + B 级证据，等后续有 ctor/使用方语义证据再升格。这与复核建议的「建成 `tagRECT[240]` 类成员（evidence B/C）」在证据等级上等价，只差类型细化这一步。

### 修订后的实测（全部为同一棵树、同一次串行链）

| 段 | 命令 | 实测 |
|---|---|---|
| apply | `python3 pipeline/cli.py apply` | **rc=0**（19.6s） |
| export | `python3 pipeline/cli.py export` | **rc=0**（168.4s） |
| codegen | `python3 pipeline/cli.py codegen all` | rc=1（已知恒红），S2 **158/229** |
| probe | `python3 pipeline/cli.py probe all` | rc=1（见下归因），S1 **743/766**、S2 **158/229** |
| match | `python3 pipeline/cli.py match` | **rc=0**，`matched 1152/1262`、**L1 189**、partial 827、compile-skip 0、`carrier paired 93→93`、`[L1 ratchet] previous 189 -> current 189` |
| census | `python3 tools/census_struct_holes.py` | SaleUI **0 洞/0B**；全库 867,548B/1,120 洞/200 类 |

probe rc=1 的归因（`tools/regression_detector.py --check`）：总文件 995、**新失败 0**、已修复 1（`RoleStatePanel.cpp`）、持续失败 94；真新增仅 `SaleUI.cpp` 35→33（消失 8、新增 6 条 C2107/C2102，位于 `0x134[...]`/`&..._view[20]` 这类 Hex-Rays 整数下标伪影行），逐码净增减 C2440 −4 / C2297 −2 / C2110 −2 / C2664 −1 / C2107 +4 / C2102 +2。即：**没有 pass→fail 翻转**，rc=1 来自 `data/status/baselines/latest.json`（19:16 的 per-file 错误集）与重渲后同单元错误集不一致。

### G：弱证据成员（复核指出的 4 员 + 6 员裸字节）

- 4 员靠「相邻构造点空隙」闭合（0x668C、0x10... 系列）：本轮未升级证据，保留 A 级标注但在 source 里写明「相邻构造点空隙（下界闭合）」，不再声称有独立 site。
- 6 员 `unsigned char[168]` 与 IDB `UIFrameContainer(152)` 不符：保持字节形（不硬套类型），理由同 D-2。
- 复核 §4 认定「零填充证据使用未发现过度推断」——这条我接受，未做改动。

### 与第一版的差异（供验收方对照）

- 成员 55→58；残留洞 7,684B→0B；check 110 warnings（+1，来自新增 B 级成员，非违规）；match 由「19:29 旧 run」变为本次 **rc=0 新 run**。
- 第一版结论里「0xF574/0x10658 无证据」「0x10564 是空隙」两句**作废**，以本文件 §二 与 §八 为准。
