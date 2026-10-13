# gotcha · noinline/内联控制路径关闭（两轮定量证伪）+ 源形重建池统一清单

**type**: gotcha
**created**: 2026-10-13（T88/T89/T91/T92 探针系列 + T93 归档）
**confidence**: high（两轮定量实验 + 回退复位 + 单测两形）

## 一句话
**字节匹配的 thunk/尾跳形不能用内联控制（inline_depth/auto_inline/noinline）
修**——noinline 改变的是 **callee 自身的 codegen**，与作用面无关；源形重建池
（20 函数）是唯一路径。

## 两轮定量证伪（T91/T92）
| 轮 | 形 | 实测 | 结论 |
|---|---|---|---|
| T89 | 调用侧 `auto_inline(off)`（thunk 包装层）| 0（编译物不变）| ✗ 不抑外部 callee 内联（MSVC6 语义）|
| T91 | 族面 noinline（全 dtor 定义）| **L1 150→85（−65）**| ✗ 族面炸 |
| T92 | targeted noinline（白名单单体）| **L1 150→148（−2）**| ✗ **同根**：callee 自身 codegen 变 |
| **根因** | **noinline 改变 callee 自身的栈帧/尾处理**，无法同时满足「caller 尾跳 + callee 字节不变」 | | **路径整体关闭** |

## 过程教训（T88-T92 系列）
1. **T88 缺件定性精度**（T66-F1 三度应用）：「尾调用优化条件」→「内联抑制」
   →「noinline 形」→「源形重建」——每轮 A 级 objdump 收窄。
2. **T90 注入点教训 3 项**：rfind 命中他 return（R13 grep 价值）· regex 漏
   返回型前缀 · early-return 之后注入失效——T91 用「唯一锚（单 return）」闭合。
3. **影响面先测后改**（T88 提示 → T91/T92 定量确认）：族面 65 函数 / targeted
   2 函数——作用面收窄不改变「callee 自身 codegen 变」的根因。

## 源形重建池统一清单（20 函数，T93 归档）
| 族 | 数量 | 判定 | 逐字节证据 |
|---|---|---|---|
| **thunk 族** | 6 | T92 归入（noinline 路径关闭）| T85 逐个 objdump（jmp 形）|
| **移位族** | 10 | T44/T47（编码长度差传播/寄存器分歧）| T44/T47 双侧指令序列 |
| **寄存器族** | 2 | T44（FindInOpen/InClosed 活区间）| T44 `8b 41 3c` vs `8b 40 3c` |
| **尾调用形** | 1 | T44（UITextArea::Destroy jmp 目标 0x445f20）| T44/T88 |
| **删除析构形** | 1 | T47（_sdtor_call_dtor 通道 T23 已立）| T47 |
| **合计** | **20** | | A 级全备（T44/T47/T85 档案）|

## 修法方向（源形重建池的共同深度）
- **COMDAT 折叠**（thunk 族）：MSVC6 在**源形层**触发别名折叠——需 ctor/dtor
  同形源（T85 ObjectCamera 定性：ctor→dtor 别名）。
- **指令选择**（移位族）：`mov reg,imm32` vs `imm8` 等编码形——源表达式形状。
- **活区间**（寄存器族）：FindInOpen 的 `OPEN=i; i=OPEN->next` 形已试（T44
  等价改写不够）——需更深源形。
- **尾调用**（Destroy）：jmp 目标归属 + 返回型对齐。
- **删除析构**（_sdtor）：T23 通道已立，形对齐待补。

## 相关
- 单测：`tests/test_drop_call_echo_arg.py` + `tests/test_stage4_lobberet_return.py`（9/9）
- 「测试绿证据力为 0」：`gotcha_wiring_type_changes_test_green_is_zero_evidence.md`
- thunk echo-drop 通路：`gotcha_thunk_echo_drop_src_rebuild.md`（T53/T56/T62 档）
