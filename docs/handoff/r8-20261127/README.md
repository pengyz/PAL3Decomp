# #145 R8-T5 UITitle 洞区落位（交付报告）

任务：`tsk_01M8EB8H3X6332VTFM43WR`（R8-T5 第五类洞区落位，按 #143 六列清单执行）。
产出：`data/annotations/structs/UITitle.json`。工作树 commit 见 `git log`（message 带 `[Evidence]`）。

## 1. 结果

| 项 | 落位前 | 落位后 |
|---|---|---|
| binary_size | 9,520 | 9,520（不变，三证一致） |
| known_members | 24 | **35** |
| bases | `UIFrameWnd@0`（base_size 72） | **`UIWnd@0`（base_size 68）** |
| census 洞 | 19 洞 / **8,223B** | 4 洞 / **18B**（−8,205B） |

剩余 4 段（均为窄对齐/无证据段，按 #143 §4 口径不落成员）：
`0x44–0x4c`(8B，基类 UIWnd 尾部对齐) · `0xce5–0xce8`(3B) · `0x1cf9–0x1cfc`(3B) · `0x252c–0x2530`(4B，类尾 pad)。

## 2. 布局（证据形态）

| offset | 成员 | 形态 | 证据 |
|---|---|---|---|
| 0x4c / 0x5c | m_rcWindow / m_rcWidgetRect | tagRECT | 旧注解（本轮未取新证据，unverified 保留） |
| 0x74 / 0x78 | m_unk_0x74 / m_unk_0x78 | int | #143 §4 第 1 行：ctor 写 0 的两个活字段（B 级） |
| 0x7c / 0x114 | m_nTodo_07C / m_nInitRoles | UIFrameContainer | ctor `sub_4422E0` 直调（写表 0x56ADD0），A- |
| 0x1ac | m_subObjA | UIFrameContainer[3] | `??_L` 三元组 0x98×3 |
| 0x374 / 0x4cc / 0x624 | m_RoleDataA/B/C | inline struct（char[104] + int m_nTodo_3DC/3E0 等 + char[232]） | 344B 是 `sub_43A770` 构造的按钮族（写表 0x56AC70，非 UIPushButton/UIButton），旧注解里的 int 落在其内腔 ⇒ 用 inline struct 逐位移保留旧名（#143 §4 第 3/4 行） |
| 0x77c / 0xcec / 0x1244 / 0x179c | m_ItemSlotA–D | UIRoleDialog | ctor `sub_443010` 直调，1368B 与 IDB 一致 |
| 0x1cfc / 0x2110 | m_unk_0x1cfc[1040] / m_unk_0x2110[1024] | byte 缓冲 | #143 §4 第 5 行：`sub_4623A0` 内按 16B 元素与 `[+0/+4/+8/+0xC]` 访问，元素语义未定 ⇒ 不硬套类型 |
| 其余 | 标量 | int/uchar | 旧注解 unverified 保留 |

## 3. 门禁（同树串行，每步前 `ps` 确认无并发 `pipeline/cli.py`）

```
check        : 0 new errors + 34 frozen(advisory), 111 warnings — PASS
apply        : rc=0
export       : rc=0   （asm/pal3/ida_structs.json 的 UITitle = 9520 / 35 员 / bases UIWnd）
codegen all  : rc=1   （已知恒红；S2 160/229 ok，与落位前持平）
probe all    : rc=1   （S1 743/766、S2 160/229；regression_detector：新失败 0，真新增 1 组 6 条全在 SaleUI.cpp，已修复 2，消失 8）
match        : rc=0   matched 1161/1278 · L1 196 · partial 827 · compile-skip 1
               [L1 ratchet] previous 196 -> current 196 · paired 94 -> 94（无回退）
census       : UITitle 19 洞/8,223B → 4 洞/18B；全库 total_hole_bytes 205,775 / 910 洞 / 196 类
```

## 4. 归因与踩坑

1. **`unsigned char[N]` 在 ns 头被发射成 `_BYTE`**：`_ns_udts.h` 不含 windows typedef ⇒ C2501/C2146，S1 真新增 9。改用 `char[N]` 后仍不够——inline **union** 会触发 ns 头重生成并连带暴露 latent 问题；最终改成 **inline struct 逐位移**（char 填充 + 原 int 成员），S1 回到 743/766。
2. **并发管线**：20:47 起他卡在跑 `codegen all --skip-probe`，冲掉 `/tmp/pal3_probe` 的 obj ⇒ 我 21:08 的 match 塌成 `matched 283/675`、L1 47。pid 退出后同一窗口内重跑 `probe all → match` 才得到上面的正确读数。**教训：`probe` 与 `match` 必须在同一空窗内连跑。**
3. **bases 变更**：`UIFrameWnd → UIWnd` 属 C11 变更，已在 `data/status/bases_adjudications.json` 写入 UITitle 条目（ctor 直接 `sub_445AA0`，未调 UIFrameWnd ctor）。
4. **census 文件是共享快照**：`data/status/struct_holes_20261125.json` 每次重跑都反映全树（含他卡并行落位），不是本卡单独差值来源；本卡差值以上表 UITitle 行为准。

## 5. 未覆盖 / 待办

- 0x1cfc / 0x2110 两个 1KB 缓冲的元素语义（16B 元素、4 dword 访问）未定 —— 需专门取证。
- 0x374 族 344B 类（写表 `0x56AC70`）仍未登记进 IDB 类型表，只能按 inline struct 表达。
- 4 个残留洞（18B）按口径留白，不建议为凑数占位。

## 6. 复跑

```bash
python3 pipeline/cli.py check
python3 pipeline/cli.py apply && python3 pipeline/cli.py export
python3 pipeline/cli.py codegen all      # 已知 rc=1
python3 pipeline/cli.py probe all        # 已知 rc=1
python3 pipeline/cli.py match            # 必须紧接 probe；期望 L1 196
python3 tools/census_struct_holes.py     # 期望 UITitle 4 洞/18B
```
