# SaleUI 池证据落位 · 独立对抗复核（#22）

- 复核对象：`data/annotations/structs/SaleUI.json`（内容与 `docs/handoff/r5-20261126/SaleUI.final.json` 逐字节相同，sha256 `1e7fbaf8…66c47`），HEAD 提交 7f9d6a636。
- 复核人：观澜（mem_biz，业务），**不是 #9 作者**，未参与 SaleUI 注解或探针编写。
- 复核输入只三类：`original/PAL3.exe.asm`（IDA 文本清单，独立证据源）、`data/handoff/r5-20261126/adversarial_review_brief.md`（待判定问题）、`SaleUI.final.json`（被审对象）。
- **未使用**：青岚的 `saleui_ctor_dtor_map.json`、`selfcheck.md` 作为依据（仅事后对照）。未运行 `pipeline/cli.py` 任何子命令，未碰 `original/PAL3.exe.i64`，未写 annotation/生成树/基线。
- 复核路径自选：**asm 文本逐条解 `??_L`/`??_M` 压栈** + 注解 JSON 区间算术 + 全 asm 搜偏移访问（grep `[esi+disp]` 形态）。不复用作者的 idalib this 跟踪探针。

## 0. 总结论

**PASS-WITH-NOTES（有条件通过）**：布局主干成立——6 个池的 `??_L`/`??_M` 三元组经独立抽取逐项一致（A 通过）；55 成员无重叠、不越界、尾部精确到 `0x19DB8`（B 通过）；span 语义自洽（C 通过但需注明口径）；命名未出现明令禁止的形态（E 有条件通过）；证据字段齐备（F 有条件通过）。

**但有两处必须修（不是风格问题）**：

1. **`0x10564` 的 4B 不是"无证据残留洞"，而是一个被 ctor 直接写零、并在方法里读写 4 次的真实字段**（D 不通过）。这使「残留洞 7,684B / 3 段」这个数字与证据不符。
2. **`0xF574–0x10474` 与 `0x10658–0x11558` 两段 3,840B 说"无构造/清零证据"只对 ctor/dtor 成立，对语料不成立**：SaleUI 自己的方法按 16B 元素粒度索引读写这两段（D 部分不通过）。作者把结论从"ctor 未初始化"外推成"无证据"，步子大了。

## 1. A–G 逐条判定

| 问题 | 判定 | 关键证据 |
|---|---|---|
| A `??_L`/`??_M` 三元组 | **通过** | 6/6 池在 ctor 与 dtor 双侧独立对上，见 §2 表 |
| B 成员重叠/越界 | **通过** | 55 员区间两两不相交；末员 `0x19C86+306=0x19DB8`=binary_size；起点最小 `0x48`（0–0x48 为 `UIListBox` 基类 72B，`bases=[UIListBox@0]`）|
| C span 自洽 | **通过（带口径注）** | 55 员中 52 员 `span == 下一员起始 − 本员起始`；3 员不等，差值**恰好等于声明的 3 段洞**（0x66F4 后 3840、0x10474 后 4、0x10568 后 3840）⇒ span 的语义是"占用字节"，不是"到下一员"。若检查器按 brief 原措辞判会误报 3 处 |
| D 残留洞是否真无证据 | **不通过** | 见 §3：`0x10564` 有 ctor 写 + 2 处方法级读写；两段 3,840B 有语料索引访问 |
| E 命名合规 | **通过（带注）** | 49 员精确 `m_unk_<hex>`、3 员语义名（`bkWidth`/`bkHeight`/`buf`）、3 员 `m_unk_<hex>_view`；无 `slot_N`/`sub_xxxx`/`_todo_`/数字后缀 |
| F 证据完备 | **通过（带注）** | 54 员 A + 1 员 unverified（`buf`，既有成员、本轮未取证）；A 级中 1 员（`0x668C`）source 只写"相邻池空隙"、无可核对 site |
| G 找反例 | **部分不通过** | 4 员仅靠"相邻构造点空隙"闭合（弱）；6 员 `uchar[168]` 与 IDB `UIFrameContainer(152)` 不符被留成裸字节；零填充证据使用**未发现**过度推断（见 §4） |

## 2. A：6 个池的三元组（独立抽取）

`??_L`/`??_M` 的 cdecl 压栈序实测：ctor = `dtor, ctor, count, size, ptr`；dtor = `dtor, count, size, ptr`。下表 ptr 均以 `[esi+off]` 形式出现。

| 池 | offset | size | count | ctor 调用行号 | dtor 调用行号 | 判定 |
|---|---|---|---|---|---|---|
| UIFrameContainer[5] | 0x6394 | 0x98=152 | 5 | asm:141120 | asm:141628 | ✓ |
| UIFrameContainer[240] | 0x66F4 | 0x98=152 | 0xF0=240 | asm:141128 | asm:141621 | ✓ |
| 未名 52B 元素池[240] | 0x11558 | 0x34=52 | 0xF0=240 | asm:141137（ctor `sub_45ADD0`、dtor `nullsub_1`）| asm:141614 | ✓ |
| CCBResultWindow[30] | 0x14618 | 0xB4=180 | 0x1E=30 | asm:141145（ctor `sub_444A20`、dtor `sub_444AC0`）| asm:141607 | ✓ |
| UIFrameContainer[30] | 0x15B30 | 0x98=152 | 0x1E=30 | asm:141153 | asm:141600 | ✓ |
| UIFrameContainer[13] | 0x17A9C | 0x98=152 | 0xD=13 | asm:141196 | asm:141563 | ✓ |

作者声明的 6 组 `(offset, stride, count)` 全部复现，无一处错位。ctor 与 dtor 覆盖的点集也一致（dtor 少 `0x11558` 的 `nullsub_1` 语义但三元组相同）。

补证：分配尺寸不是注解自说——`push 19DB8h` 在 asm:139310，紧接 `call sub_45A7B0`（asm:139318）；dtor 首部 `mov dword ptr [esi], offset off_56B5CC` 与注解 vtable `0x0056B5CC` 一致；dtor 对 `[esi+19DB4h]` 的 byte 写（asm:141493 区）与 `size_evidence` 描述的"末 4 字节被摸到"吻合。

## 3. D：残留洞复核（本卡的核心反例）

brief 声明 3 段洞共 7,684B"ctor/dtor 无构造/清零证据"。逐段查 asm：

### 3.1 `0x10564–0x10568`（4B）——**判错，有 A 级证据**

- ctor 直接写：`mov [esi+10564h], ebx`（asm:141136，ebx=0）。
- 方法级读写同一偏移：`mov eax, [esi+10564h]`（asm:150262）、`mov [esi+10564h], edx`（asm:150274），位于 `sub_4623A0`（asm:149799 起）。
- 4 字节整对齐、被当 dword 指针使用（先读后写、与 `arg_0` 关联）⇒ 这是一个真实字段，不是 padding。这与 #18 残留分析"`0x10564` 是 `CCBUIPanel*`"互相印证，但本判定**只依据 asm 本身**。
- 结论：该 4B 应从"无证据洞"改为**已建模成员**（建议 `void*`/`unsigned int`，evidence A，source 写 ctor site + 两处方法 site）。残留洞字节应为 **7,680**，段数 2（若两段大洞保留）。

### 3.2 `0xF574–0x10474`（3,840B）与 `0x10658–0x11558`（3,840B）——"ctor 无证据"成立，但"无证据"不成立

- ctor/dtor 确实**没有** `[esi+0xF5xx…]`/`[esi+0x106xx…]` 的直接写（全文 grep 命中的都是"基址+索引"形态，不是固定 disp）。
- 但 SaleUI 自己的方法里，这两段是**按 16B 元素读写的数组**：
  - `mov [eax+esi+0F574h], edx` / `mov edx, [ecx+esi+0F574h]` / `lea ecx, [edx+esi+0F574h]`（asm:145625/145629/145643，函数 `sub_45E9F0`）。
  - `mov ecx, [edx+esi+0F578h]` → `mov [eax+1065Ch], ecx`；`mov edx, [ecx+esi+0F574h]` → `mov [eax+10658h], edx`（asm:147165–147167，同函数）——**从 0xF574 表拷贝到 0x10658 表**，两表同构。
  - `lea edx, [ecx+esi+0F574h]` 后连续取 `[ebp+0]/[+4]/[+8]/[+0Ch]`（asm:150403 起，`sub_4623A0`）⇒ 元素 16B。
  - `[esi+eax*8+10568h]`、`lea edx,[edx+esi+10658h]` 后连续 4 个 dword 拷贝到栈（asm:160345–160372，`sub_46B040`= vtable slot Update）⇒ 0x10658 侧同样是 16B 元素表。
- 结论：两段 3,840B = **2 × (240 × 16B) 的同构矩形表**（源表 0xF574、目标表 0x10658），ctor 不做逐元素初始化（运行期由上述方法填充），所以"洞里没有构造点"字面成立，但**"无证据 ⇒ 无法建模"不成立**。建议：要么建成 `tagRECT[240]` 类成员（evidence B/C，source 写语料索引 site），要么保留洞但把 source/报告措辞改成"ctor 不初始化、运行期填充"，不能写"无证据"。
- 追加：`0x10564` 的 4B 正好夹在 `0x10474[240]`（尾 0x10564）与 `0x10568[240]` 两个 240B 块之间，两段 3,840B 大洞又分列这块 240B 区两侧；这一排布也解释了 #18 为何把 0x10564 单列为 `CCBUIPanel*`。

## 4. G：反例与弱证据清单

- 4 员仅由"相邻构造点空隙"闭合（no site）：`0x615C[16]`、`0x668C[104]`、`0x16EA4[64]`、`0x189A4[404]`。其中 `0x668C` 连 site 都没有，只有"相邻池空隙"五字 ⇒ F/G 双重弱。建议补 ctor/dtor 邻接点间距算式，或降级为 unverified。
- 6 员 declared `uchar[168]` 而 IDB 同位置组件类型是 `UIFrameContainer(152)`（`0x17604/0x1795C/0x18BD0/0x18C78/0x18D20/0x18DC8`，全量）：作者自己写在 source 里"段长 168 与 IDB UIFrameContainer(152) 不符"。留裸字节是保守做法，但**没有给出 168 与 152 差 16B 的结构解释**；若这 16B 是子对象尾部字段，后续会被当成洞反复考古。
- 零填充证据核查：`m_unk_0x178` 的 source 写"rep stosd 0x1118 dword 整段清零"，实测 ctor `mov ecx,1118h; lea edi,[esi+178h]; rep stosd`（asm:141287–141290），0x1118×4=17,504=span，**完全吻合，不是过度推断**；`0x10474`/`0x10568` 的 `ecx=3Ch`（60 dword=240B）同样吻合。零填充作为"占用范围"证据使用得当。
- 未发现"把 memset/rep stosd 当成类型证据"的情形：所有零填充成员的 type 都是 `unsigned char[N]`，与证据强度匹配。

## 5. 命名与证据字段（E/F）

- 55 员命名分布：精确 `m_unk_<hex>` 49、语义名 3（`bkWidth`/`bkHeight`/`buf`）、`m_unk_<hex>_view` 3（`0x150`/`0x66F4`/`0x11558`）。
- 无 `slot_`/`sub_`/`_todo_`/`m_Xxx_1234` 形态；但 **`_view` 后缀使这 3 员逃过 `^m_unk_(0x)?[0-9a-f]+$` 的普查正则**——`docs/audit/munk_census_20261126.json`（#12）对 SaleUI 只数到 49 条即由此而来，全库计数会少 3。建议把 `_view` 名登记进过渡台账，并在下次 export 刷新语料后改回规范形态。
- `buf`(0x50) 是既有成员、本轮未取证（unverified），在 55 员中唯一；不是本轮新增缺陷，但应在下一轮补二进制证据或降级说明。
- A 级 source 均有 `0x` site（唯一例外 `0x668C`），可核对性总体良好。

## 6. 实际用过的命令（可复跑）

```bash
# 1) 池三元组：ctor / dtor 区间内的向量迭代器调用（含压栈值）
s=$(grep -n 'sub_45A7B0      proc' original/PAL3.exe.asm | cut -d: -f1)
e=$(grep -n 'sub_45A7B0      endp' original/PAL3.exe.asm | head -1 | cut -d: -f1)
sed -n "${s},${e}p" original/PAL3.exe.asm | grep -n "push\|call\|lea \|rep stosd"
# dtor 同法：sub_45AE60 proc / endp
grep -n "call    ??_L@YGXPAXIHP6EX0@Z1@Z" original/PAL3.exe.asm | awk -F: '$1>=140983 && $1<=141339'
grep -n "call    ??_M@YGXPAXIHP6EX0@Z"     original/PAL3.exe.asm | awk -F: '$1>=141431 && $1<=141652'

# 2) 洞偏移在 asm 中的访问（[esi+disp] 与 基址+索引）
grep -n "10564h" original/PAL3.exe.asm
grep -n "F574h"  original/PAL3.exe.asm
grep -n "10658h" original/PAL3.exe.asm

# 3) 成员区间/span/命名/证据统计（脚本化的那几条）
python3 - <<'PY'
import json,re
d=json.load(open('docs/handoff/r5-20261126/SaleUI.final.json'))
rows=sorted((int(k,16),v) for k,v in d['known_members'].items())
for i,(o,v) in enumerate(rows):
    nxt=rows[i+1][0] if i+1<len(rows) else d['binary_size']
    print(hex(o),v['name'],v['span_bytes'],nxt-o)
PY
```

## 7. 只读自证

- 本卡仅新增 `docs/audit/` 下本文件；未改 `data/annotations/`、`pal3/src/`、基线、`data/status/`。
- 未执行 `pipeline/cli.py`；未打开/写 `original/PAL3.exe.i64`。
- 与 #9 作者无共同作者身份；本报告结论不引用 `saleui_ctor_dtor_map.json` / `selfcheck.md` 的任何数据，仅在 §3.1 提到 #18 的既有结论作为旁证（并注明本判定独立于它）。
