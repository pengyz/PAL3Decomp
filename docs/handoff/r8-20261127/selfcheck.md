# #145 提交前自检

对照 #145 qaChecklist 逐条：

| # | 要求 | 状态 | 证据 |
|---|---|---|---|
| 1 | UITitle 尺寸/成员三证一致 | ✅ | binary_size 9,520；独立三路：operator new 字面量、ctor 布局终点 0x252c+4、知微 #148 独立复算（md5 99ab0783…）；成员 35、末员 0x2528+1=0x2529 ≤ 0x2530 闭合 |
| 2 | 洞字节按 #143 清单下降 | ✅ | 19 洞/8,223B → 4 洞/18B（−8,205B，与草案预估一致） |
| 3 | 证据齐备（evidence_level + source） | ✅ | 35 员全部有 source；A- 级 8（构造点直调）、C 级 5（字节缓冲/内腔）、B 级 2、unverified 20（旧注解保留，未取新证据不升级） |
| 4 | 命名合规 | ✅ | 新增名仅 `m_unk_0x74/0x78/0x1cfc/0x2110`（留白形）；无 `slot_/sub_/_todo_` 新名；旧 `m_nTodo_*` 保留是因为语料引用（#143 §4 允许保名修型） |
| 5 | check 0 new | ✅ | `0 new errors + 34 frozen(advisory), 111 warnings — PASS` |
| 6 | 管线读数不退化 | ✅ | apply/export rc=0；codegen S2 160/229 持平；probe 新失败 0（真新增 6 条均 SaleUI.cpp，属早前卡）；match rc=0 L1 196 持平、paired 94→94 |
| 7 | 独立复核 | ⏳ 待指派 | 与 #148（知微）做过交叉核对：基类 UIWnd@0/68B、0x74/0x78 活字段、0xCE5 对齐 pad、19 段=4 活+12 内腔+3 对齐，两路结论一致 |
| 8 | 独立提交含 Evidence | ✅ | commit message 含 `[Evidence]`/`[Verify]`/`[Scope]` |

## 未闭合项（已写入报告 §5）

- 两个 1KB 缓冲的元素语义未定（按字节落，A/C 级）。
- 344B 族写表 `0x56AC70` 未进 IDB 类型表。
- 4 残留洞 18B 按口径留白。
