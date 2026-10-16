# L1「字节全同」≠ 全字节相同——三重限定（截断 / 长度相等 / 重定位 don't-care）

**type**: gotcha
**created**: 2026-10-16（reviewer 复核实证归档；度量源=T146 度量校正，2026-10-15）
**实证案**: `match` 报的 L1（match_L1）真实判据在 `pipeline/compare_pal3.py`（`compiled = info['bytes'][:size]`）+ `tools/gbengine_compare.py:compare_bytes`，三重限定：
1. **截断**：编译产物先截到原函数长度 `size` 再比较 ⇒ **编译多出来的尾部完全不可见**（实测 L1 182 例里 **179 例**编译字节长于 size，合计 **1903 尾字节**，抽样为 0x90 NOP 对齐填充——目前无害，但「我方多编出真实指令」会被掩盖成 L1）；
2. **长度相等**：截断后两侧长度必须相等（编译**短**于原函数 ⇒ 直接 partial）；
3. **重定位 4 字节 = don't care**：每处重定位覆盖的 4 字节即使双侧不同也计 match（实测 L1 182 函数/7089 字节：重定位覆盖 **27.65%** 字节，其中**双侧真的不同**（被跳过的隐藏差异）= 全部 L1 字节的 **19.24%** / 重定位字节的 **69.6%**）。

**为什么：** L1 是「截断 + 长度 + 跳重定位」三重过滤后的判定，不是逐字节证明。把 L1 外推为「每字节已验证」会三处踩空：① 尾部多编的指令被截断藏住（只在最终链接体积/尾部比对里露头）；② 重定位 4 字节内的目标差异（调用指向错误函数/错误 vtable）被 don't-care 放过——**rsite 符号法核对**（match 输出 `[metric]` 两行）才是这一层的判据（实证：77 目标 mismatch 中 66 条经本体判读为真析构名实不符族）；③ 隐藏差异占 L1 字节 19.24% ⇒ 「L1=N」的语义边界必须随数字一起引用。这是度量盲区而非判据缺陷——判据本身是对的（可比性优先），错在引用时丢限定。

**何时使用：** ① 任何汇报/断言引用 L1 数字（L1=188 之类）时，**必须带三限定**或指向本条；② 评估「某函数已 L1」并打算据此宣称语义正确时，先看该函数重定位站点的目标核对（`match` 输出 `[metric]` 行当场读，重定位站点值核对/目标核对两行）；③ 改动 match/compare 工具时，三限定是**判据契约**——放宽任一条都要过 `tests/test_gbengine_reloc_sites.py` 回归锁；④ 链接级差异（调用目标错）不在 L1 视野内——与 `gotcha_s2_compiles_but_does_not_link`（链接层盲区）连读。

**复算命令（数字重证）：**
```bash
python3 -c "
import json; s=json.load(open('data/status/s4_baseline.json'))['stats']
print('L1 bytes', s['l1_bytes'], '| reloc覆盖', s['l1_reloc_covered_bytes'], '| 隐藏差异', s['l1_hidden_reloc_bytes'])"
# + python pipeline/cli.py match 输出末尾 [metric] 三行当场读
```
