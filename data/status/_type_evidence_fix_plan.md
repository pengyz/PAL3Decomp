# type_evidence 修复方案（步骤 1 输入：复核 B 裁决 F1–F15 + 探针实测交叉）

来源：对抗复核 agent cd5778b9（2026-09-27，只读复核 + dry-run 实测）+ 本会话探针 2/3/4 交叉验证。
裁决：**不可进入实现、禁开 --write**，先修下列各批。复核 B 的实测数字均独立复算过（口径略有差异、结论一致）。

## 第 1 批（P0，必修，随补测落地）
| # | 缺陷 | 修法（复核 B 处方） | 本会话交叉证据 |
|---|---|---|---|
| F1 | scan_t1 偏移基错位（blob 相对 h 当文件偏移）| `type_evidence.py:216` `decode_refs_at(data,…)` → `decode_refs_at(blob,…)`；docstring 注明偏移基 | 探针 3：429/431 假阴性；探针 4 定位 .text roff=0x1000 |
| F2 | load_candidates hex key 崩溃（'0x68C'/'0x4C'）| `head=str(key).split('_')[0]; off=int(head,16) if startswith('0x') else int(head)` | 探针 2：CGameData '0x4C' 实证；10 文件 51 个 0x 键 |
| F3 | propose 冲突检测漏 double×int ⇒ ('double','A') 落盘 | float/double/int 两两互斥；double 分支补 `set(widths)=={8}` | 复核实测（可信） |

## 第 2 批（P1，F1 修复前必须同批——否则 40% 假证据涌入）
| # | 缺陷 | 修法 |
|---|---|---|
| F4 | `[reg+disp]` 被当证据（40%）| `_op_value`：`if op.mem.base or op.mem.index: return None, False` |
| F5 | 最早 insn_va 被伪解码抢占（139 处选错）+ _amb 丢弃 + mem/imm 双命中互覆盖 | 只接受纯 abs 候选；多候选标 ambiguous 不得单独凑 A；mem 优先于 imm（disp 侧才是宽度证据）；中期可升级"线性反汇编边界表" |
| F7 | fi* 整数内存判浮点（fidiv 24+fimul 9 站点）| fi* 全族归 'int'（按 op_size 定宽）|
| F8 | apply_fills 重写风格不一致（CEffMgr.json 342 行 100% 全改，CRLF→LF）| 读原文件探测换行/indent/尾换行按原风格回写；tmp+os.replace 原子落盘（并 F13）|

## 第 3 批（强烈建议同批）
| # | 缺陷 | 修法 |
|---|---|---|
| F6 | lea 当宽度证据（9 站点）| `classify_insn` 首部 `if m=='lea': return 'addr', None` |
| F9 | 多实例类 VA 口径错（116/876 = 13% 候选）| 逐实例生成证据聚合到 (cls,off)；报告记 multi-va |

## 第 4 批（记录在案随后）
F10（setcc 符号位/cvtt*）、F11（unknown 计入冲突）、F12（int 8/16 注记）、F13（原子写/缺文件守卫）、
F14（T2 词边界）、F15（--cls 无参 IndexError / op.size=0 / evidence_refs isinstance）。

## 补测清单（契约穿过集成缝，随修复落地）
- test_chain_movzx_byte_to_unsigned_char（SIGN→decode→propose 全链联调）
- test_decode_fake_earlier_must_not_steal（F5）· test_decode_base_register_rejected（F4）
- test_decode_lea_is_addr（F6）· test_decode_mem_wins_over_coincident_imm（F5）
- test_classify_fi_is_int（F7）· test_propose_double_int_conflict（F3）
- test_propose_unknown_counts_in_conflict（F11）· test_setcc_no_sign_evidence（F10）
- test_apply_fills_preserves_file_style（F8）· test_apply_fills_missing_struct_file（F13）
- test_load_candidates_smoke_real_repo（F2 端到端缝）· test_scan_t1_offset_basis_real_pe（F1 端到端缝，断言解码率下界 ≥50%）

## 设计层增量（待复核 A 裁决后定稿）
- **T1b this-relative disp32 census** 接入为主信号之一（探针 2 信号地图：数据类 T1 主导、方法类
  T1b 主导；CEffMgr 28 函数 46 偏移证据实测可行）。载体指令确认按 pattern 文档；ECX provenance
  追踪按 access_map.py 语义。数组元素内部偏移按成员分段归属（探针 1 注意点）。
- 工作集口径（"211"对账）等复核 A 裁决后钉死。
