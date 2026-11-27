# R5 收尾：SaleUI 残留三段落位（#35）

- 卡：`tsk_01M8CD5P3GN7WNP8M63QTF`（#35，owner 玄策）
- 写面：`data/annotations/structs/SaleUI.json`、`data/annotations/functions/`、`data/status/`、`docs/specs/`
- 日期：2026-11-27

## §0 结论

1. **卡面「0x10564 指针」的前提不成立**：该 4B 是**整数索引**，全部 3 个引用点无任何解引用/取址；它存的是「上一次填充所依据的条目索引」，与 `[this+0x150]` 同源。
2. `0xf574` = `tagRECT[240] m_aSlotSrcRects`（源/布局矩形，240×16B=3840B），`0x10658` = `tagRECT[240] m_aSlotDrawRects`（绘制矩形，由前者派生）。两段与卡面「16B×240」一致。
3. 卡面「残留 7,684B」是 #9 之前的历史洞值；本卡接手时 `census` 已无 SaleUI 条目。本卡的实际价值是**把三段从 `m_unk_*` 占位升级为 A 级类型/语义**，不是继续降洞数（census 改动前后同为 0 洞）。
4. 门禁：`check` 0 new PASS；loop 四段 rc 与 #31/#9 同形（apply/export 0，codegen 恒红、probe 因既有 SaleUI 红 rc=1）；match 单独复跑 RC=0、L1 192、无 LOST、未 rebaseline。
5. 独立对抗复核（workflow 单 agent，只读、未复用提交者脚本）总 verdict **pass**，两条非阻断文字建议已落到 source。

## §1 三处成员与证据

| 偏移 | 类型/名 | 等级 | 决定性证据 |
|---|---|---|---|
| 0x10564 | `int m_nLastGridItemIndex` | A | 引用仅 3 处：ctor `VA0x45A9E5 mov [esi+10564h],ebx`（ebx=0 清零）；`VA0x4623B3 mov eax,[esi+10564h]` 后 `VA0x4623C0 cmp edx,eax` 与 arg_0 比较；`VA0x4623E4 mov [esi+10564h],edx` 回写入参。`sub_4623A0` 自己把 arg_0 当数组下标：`VA0x4623B9 mov 0x3e08(%esi,%edx,4),%ebp`（元素随后被解引用）。入参来源：asm159559（sub_469EB0 的 arg_8）、159899、161943 均来自 `[obj+0x150]`。**无 `lea`/二次寻址 ⇒ 非指针** |
| 0xf574 | `tagRECT[240] m_aSlotSrcRects` | A | 访问点先算索引再 ×16：`VA0x460504 shl $0x7`（cell c=j+6i，8×16B）、asm148803 `shl $0x4`、asm158609 getter `shl $0x4` 后连拷 4 dword。字段写点 `VA0x45ECC9`(L)、`VA0x45ECA7`(T)、`VA0x45ECE9`(R=L+0x1A)、`VA0x45ED06`(B=T+0x26) ⇒ 4×4B；索引 `16*(k+8*(j+6*i))`，i<5（`cmp $0x5`）、j<6（`cmp $0x6`）、k<8（`cmp $0x8`）⇒ 5×6×8=240；`0xf574+0xF00=0x10474` 精确 |
| 0x10658 | `tagRECT[240] m_aSlotDrawRects` | A | 唯一写者 `sub_45E9F0`：`VA0x460507` 读 `0xf574(%ecx,%esi,1)` → 紧邻 `VA0x460511` 写 `0x10658(%eax)`（T−0xC、B=T+0x26，L/R 原样；8 个子矩形同构）。唯一读者 `sub_46B040`（`.rdata 0x56B5D4` 为 vtable `0x56B5CC` 第 3 槽 ⇒ slot2）：`VA0x46B0F4`/`VA0x46B1DA` 取 16B 压栈 `call 0x478880`；行标记读 `0x10568(%esi,%eax,8)` |

## §2 跨度算术与相邻关系

```
0xf574 + 0xF00 = 0x10474   (m_aSlotSrcRects 240×16B)
0x10474 + 0xF0 = 0x10564   (行标记 240B)
0x10564 + 0x4  = 0x10568   (行标记 240B)
0x10568 + 0xF0 = 0x10658   (m_aSlotDrawRects 240×16B)
0x10658 + 0xF00 = 0x11558
```

- 58 个成员区间扫描：**0 处重叠**，链尾 `0x19DB8 == binary_size`。
- ctor 侧独立佐证：`VA0x45AD54` 清 `0x10474`（`0x3C` dword=240B）、`VA0x45AD61` 清 `0x10568`（240B）；两段各 240B，中间 4B（`0x10564`）刻意未清，另在 `0x45A9E5` 单写 0 ⇒ 240/4/240 切分正确。

## §3 census 前后

- 改动前：`data/status/struct_holes_20261125.json` 200 类中**无 SaleUI 条目**（洞=0）。
- 改动后（03:0x 重跑）：sha256 `3dcb83141cf258027fd6e2831ab8933ff34f12cdf6a23393abae241e071d2d34`，仍**无 SaleUI 条目**。
- 结论：本卡不改变该类的洞面（已为 0），只提升类型/语义质量；卡面 7,684B 为 #9 之前历史值。

## §4 门禁读数

| 阶段 | rc | 读数 |
|---|---|---|
| `cli.py check` | 0 | `0 new errors + 37 frozen(advisory), 110 warnings — PASS`（`data/status/archive/r5_saleui_tail_check_20261127.log`；source 措辞修订后复跑 `data/status/archive/r5_saleui_tail_check2_20261127.log` 仍 `0 new errors ... PASS`） |
| `loop`（apply/export/codegen/probe） | 0/0/1/1 | apply 20.0s、export 153.1s、codegen 恒红 TOLERATED、probe 95.5s；**S2 159/230**（`r5_saleui_tail_loop_20261127.log`） |
| `match`（单独、管线清空后） | 0 | `matched 1154/1265 | L1 192 | partial 826 | compile-skip 0 | unresolved-synth 136`；`[metric] L1 8317 / reloc 2320(27.9%) / hidden 1653(19.9%/71.2%)`；棘轮 `previous 189 → 192`、semantic 12→13、population `1152/1259 → 1154/1265`、coverage 93→94；**无 LOST、未 rebaseline**，日志明示「可比总体已变化，两次 L1 不可直接比较」 |

- 回归归因（`tools/regression_detector.py --check --report`）：SaleUI.cpp 35→33，真新增 6 条（C2107×4 + C2102×2，L755/756/9268）全部是既有 codegen 族（`0x118[v36]` 常量当下标），行号因重渲位移；本卡三成员在生成源中质量正常（`pal3/src/Misc/SaleUI.cpp:2443-2446` 逐字段、`:3881` 索引赋值、`:3955` `48*v44+6`）。
- 同轮其它单元：`UIGameFrm.cpp` 12→9、`UITitle_JDHY.cpp` 6→1、RoleStatePanel 已修复；S2 158→159 来自 #19 拆出的 `ScreenEffectRingNode.cpp`。
- 并发污染已排除：首次 match 与别人 `export` 并发，伪造 161 LOST（`s4_diff_detail_regressed_20261127T031227.json`），等管线清空后复跑为 0 LOST。

## §5 独立对抗复核

- 方式：workflow 单 agent，只读，自行 grep/objdump，不引用本卡脚本。
- 结果：A–E 全 pass（int 索引无解引用；16B×240 与公式；派生关系与唯一读者 slot2；五段首尾相接零重叠；tagRECT 字段=绝对 L/T/R/B）。
- 两条非阻断建议已落地：①`0x10564` source 把 159899/161943 标为「入参来源（间接证据）」并补 asm159559；②`0xf574` source 把索引公式补全为 `16*(k+8*(j+6*i))`（i<5、j<6、k<8）。

## §6 限制与遗留

- `pal3/src/Misc/SaleUI.cpp` 仍为失败单元（33 错），本次三成员不是新增错误的来源；剩余为 codegen「常量当数组下标」族（`0x118[v36]` 等），属另一类问题，未在本卡修。
- `0x10564` 的语义名「上次填充条目索引」来自消费形态（与 arg_0 比较、回写、与 `[+0x150]` 同源），未发现更精确的名字；如后续找到调用方语料可再正名。
- 未改 `data/status/` 之外的基线，未 rebaseline；`data/status/struct_holes_20261125.json` 仅由官方 `census_struct_holes.py` 刷新。

## §7 台账

- `ev_0022`（A/open）：SaleUI 三段定型（0x10564 int 索引；0xf574/0x10658 tagRECT[240]）与跨度闭合、门禁读数。

## §8 复现命令

```bash
cd /home/peng/workspace/PAL3Decomp
# 1) 反汇编证据
objdump -d original/PAL3.exe | grep -nE "10564h|0f574h|10658h" | head -40
objdump -d --start-address=0x45E9F0 --stop-address=0x460A00 original/PAL3.exe | grep -nE "f574|10658"
# 2) 落位（幂等；默认干跑）
python3 data/status/archive/r5_saleui_tail_placement_20261127.py
# 3) 门禁
python3 pipeline/cli.py check            # 期望 0 new PASS
python3 pipeline/cli.py match            # 期望 RC0，L1>=189，无 LOST
python3 tools/census_struct_holes.py     # 期望 200 类中无 SaleUI 条目
# 4) 独立复核不复用脚本：自行 objdump 上述地址 + 读 SaleUI.json 成员表
```

## §9 QA 6 项对照

| checklist | 对应 |
|---|---|
| 0x10564 三段证据 | §1 第 1 行（ctor 清零 / 比较 / 回写 + 入参来源） |
| 两段 `tagRECT[240]` 证据 | §1 第 2–3 行（16B 步进、240 计数、派生写点） |
| census 前后对比 | §3（前后同为 0 洞，文件 sha 记录） |
| 门禁全套 | §4（check/loop/match 读数 + 外部红归因） |
| 独立复核 | §5（workflow 只读复核 pass + 两条建议已落地） |
| 只碰写面 | 改动仅 `data/annotations/structs/SaleUI.json`（+18/−15）与 `docs/specs/`、`data/status/archive/` 归档 |
