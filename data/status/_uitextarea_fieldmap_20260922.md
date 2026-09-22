# `UITextArea` 二进制字段图（O2 实测，2026-09-22）—— 供注解重建

来源：`tools/bin_oracle.py`（原始 EXE + objdump，**IDB-无关** ✓）+ `this` 追踪（入口 ECX=this；`mov %ecx,%esi` ⇒ esi≡this ✓）
方法（来自 `asm/pal3/ida_structs.json`）：`0x444F60 InitAfterClear` · `0x444FF0` · `0x445170` · `0x445500` · `0x445720` · `0x445760` · `0x445920` · `0x4B7AF0`
窗口：每个方法的**前导区**（≤160 条，遇 `ret` 止 ✓）—— 覆盖 ctor/Init 类的全字段写入 ✓

## 观测到的字段（偏移 · 形态）
| 偏移 | 观测 | 推断宽度 |
|---|---|---|
| +0x04 | `movb $0xfa` 写 | 1（byte）|
| +0x05 / +0x06 | `mov $0xff` 写 | 1 / 1 |
| +0x08 | `mov` 读 | 4 |
| +0x10 | `lea` | 4 |
| +0x38 | `mov` 读 + `cmp` 写 | 4 |
| **+0x44** | **`movl $0x3f000000` 写（float 0.5）** | **4（float）**|
| +0x48 | `mov %al` 写 | 1（byte）|
| +0x4C | `mov %edi` 写（edi=0）| 4 |
| +0x50 | `mov %edi` 写 | 4 |
| +0x54 | `mov %edi` 写 | 4 |
| +0x58/5C/60/64 | `mov` 读 ×6–8 | 4 |
| +0x68 | `lea` 取址传参（`call 0x445EA0`）| 4（或聚合体起址）|
| +0xAC | `movl $0x2` 写 | 4 |
| +0xB0 | `mov` 写 ×2 | 4 |
| +0xB8 | `mov` 读 | 4 |
| +0xBC | `mov` 写 ×2 | 4 |
| +0xEC / +0xF0 | `mov` 读 + 写 | 4 |

⇒ **对象真实尺寸 ≥ 0xF4（244）**，而注解 `binary_size = 104 (0x68)` ✗✗

## 与注解的矛盾（新门已自动抓到 ✓）
* 注解 `m_buf: std::basic_string` **@0x44** ✗ —— 二进制在 +0x44 写 **float 0.5** ✗
* 注解 `m_bInvalidate: BYTE` **@0x50** ✗ —— 二进制在 +0x4C/0x50/0x54 写 **dword** ✗
* 注解 `binary_size=104` ✗ —— 观测已到 +0xF0 ✗
* 两条注解的 `source` 分别是 **`pdb_merge`** / **`gen_headers_9.2`** ⇒ **均无二进制证据** ✗

## 重建所需（下一步，独立工作项）
1. **全方法扫描**（不只前导区）⇒ 完整访问集（含读/写/宽度/频率）✓
2. **尺寸裁定**：找分配点（`new`/数组步长/相邻对象间距）⇒ 定 `binary_size` ✓
3. **命名**：无语义把手者一律 `_todo_`（仓规禁止伪语义命名 ✓），`source: binary:disasm@0x444F60` ✓
4. **验收**：`audit_type_layout`（全成员 `offsetof` + `sizeof`）+ **新门（注解 vs 二进制）** + 四道门 ✓
