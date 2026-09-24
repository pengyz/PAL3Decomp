"""`tools/vtable_sig_infer.py` 的测试 —— **先写测试**（TDD，红→绿）。

本文件是 vtable **候选签名生成器**（原始指令字节 → 候选签名，写 methods_pending 旁路）
的金样本回归集。所有夹具均为真机 MSVC 6.0 SP0（cl 12.00.8168，`tools/wine_cl.sh`）编译 +
**原始指令字节**反汇编（objdump，**禁止 decomp JSON**）逐字输出。

覆盖要求（task-3-brief / 控制器 Ruling 1-6）：

* C-1 未用参数（`_vtable_attack_cases_20260925/s1.cpp` `?unused@S@@UAEXHH@Z`）
  读集 ∅ ⇒ 只靠读集会推 0 参（真值 2）；必须用 `ret 8` 补足 + 标"可能有隐藏参数"
* C-2 `__fastcall`（s1 `?freg@S@@UAIXHH@Z`）：首参在 edx（prologue 溢出）+ 栈 1 槽
  ⇒ 真值 2 参；**调用点 push 计数 = 1**（三层证据收敛到错误值的反例）
* C-3 `__cdecl` 成员（`r2.cpp` `?cf@Xc@@UAAXH@Z`）：this 在栈上（`[ebp+8]`）⇒ 读集 2 槽，
  真值 1 参 ⇒ 必须识别并扣除（调用点 push=2 亦"确认"错误答案）
* C-4 变参（s1 `?log@S@@UAAXPBDZZ`）：`ZZ` 结尾 ⇒ 必须识别变参，无参个数信息 ⇒ C 级
* C-5 同体折叠（`e1.cpp` `?o@E@@UAEXH@Z` / `?o@E@@UAEXPAX@Z` / `?o@E@@UAEXM@Z` 三体**字节相同**）
  ⇒ 一地址多签名：键值需支持多候选 + 标 ICF 折叠，不得给出唯一等价类
* C-6 BOOL ≠ int（`b1.cpp`）：callee 字节完全相同（`ret 4`）⇒ 等价类不可分（必须留
  `param_class_undetermined`）；调用点 `setne` 物化（+5B）才是区分证据，BOOL 单独成类

另含分级（A/B/C）与 Ruling 金样本：

* Ruling 1：`SigEvidence.disasm` 只接受**原始文本**（喂 Insn 元组 ⇒ TypeError），
  内部一律 `parse_disasm_report` + `classify_slot(原始文本)`
* Ruling 2：消费 `fn` 必查 notes —— 输入非空但解析 0 条指令 ⇒ 证据不足 ⇒ C 级 + 痕迹
* Ruling 3：fastcall 检测（edx 入口溢出；**裸 ret** 形态 `?f1@Rn@@UAIXH@Z` 亦命中）
* Ruling 4：cdecl 成员 this 在栈 ⇒ 首槽扣除（thiscall 不得扣）
* Ruling 5：BOOL/char/short 单独成类（`param_class_equiv('bool','i32') is False`）
* Ruling 6：sret（>8B 结构返回的隐藏首参）⇒ `?rb@Rn@@UAE?AUBig@@H@Z` 真值 1 参而非 2

分级定义（spec §4.2 逐字）：
    A = 调用约定 + 参数个数 + **返回宽度**全部确定（且无隐藏参数嫌疑/无 ICF 折叠）
    B = 缺返回宽度，或有隐藏参数嫌疑，或 ICF 折叠
    C = 参数个数不确定（变参 / cdecl 读集为空 / 证据不足）

运行：`python3 tests/test_vtable_sig_infer.py` 或 `pytest tests/test_vtable_sig_infer.py`
"""
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))

from vtable_slot_classifier import parse_disasm_report  # noqa: E402

from vtable_sig_infer import (  # noqa: E402
    GRADE_A,
    GRADE_B,
    GRADE_C,
    CC_CDECL,
    CC_FASTCALL,
    CC_STDCALL,
    CC_THISCALL,
    CC_UNKNOWN,
    RET_BOOL,
    RET_F32,
    RET_F64,
    RET_I64,
    RET_I16,
    RET_I32,
    RET_I8,
    RET_SRET,
    RET_UNKNOWN,
    FEATURE_AMBIGUOUS_PARAM_CLASS,
    FEATURE_EDX_REG_ARG,
    FEATURE_ECX_THIS,
    FEATURE_FP_WIDTH_AMBIGUOUS,
    FEATURE_HIDDEN_PARAM_SUSPICION,
    FEATURE_ICF_FOLDED,
    FEATURE_INSUFFICIENT_EVIDENCE,
    FEATURE_NO_PROLOGUE,
    FEATURE_REAL_PARAM_BLIND_SPOT,
    FEATURE_SRET,
    FEATURE_SRET_AMBIGUOUS,
    FEATURE_STACK_BASE_UNKNOWN,
    FEATURE_THIS_ON_STACK,
    FEATURE_VARIADIC,
    FEATURE_PARSER_ERROR,
    FEATURE_CC_FROM_MANGLING,
    FEATURE_SLOT0_DEREF,
    SigEvidence,
    analyze_call_sites,
    body_key,
    build_methods_pending,
    convention_from_symbol,
    find_icf_groups,
    infer_address_record,
    infer_signature,
    iter_candidates,
    param_class_equiv,
    param_class_family,
    sanitize_pe_relocs,
)
from vtable_sig_infer import main as cli_main  # noqa: E402


def E(**kw):
    return SigEvidence(**kw)


# ==========================================================================
# 金样本夹具（真机实测反汇编逐字；出处见文件头）
# ==========================================================================

# ---- C-1/C-2/C-4：s1.obj（attack README 攻击 3） ----
# `?unused@S@@UAEXHH@Z`：thiscall 溢出 ecx，读集 ∅，`ret 8`
C1_UNUSED = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b e5                 mov    %ebp,%esp
  9:  5d                    pop    %ebp
  a:  c2 08 00              ret    $0x8
"""

# `?freg@S@@UAIXHH@Z`：**edx 入口溢出**（首参寄存器）+ `ret 4`（栈 1 槽）⇒ 真值 2 参
C2_FREG = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  83 ec 08              sub    $0x8,%esp
  6:  89 55 f8              mov    %edx,-0x8(%ebp)
  9:  89 4d fc              mov    %ecx,-0x4(%ebp)
  c:  8b e5                 mov    %ebp,%esp
  e:  5d                    pop    %ebp
  f:  c2 04 00              ret    $0x4
"""

# s1 `_main` 里 `x.freg(1,2)` 的调用序列 —— push 计数只有 **1**（三层证据同错的反例）
C2_FREG_CALL = """
  0:  6a 02                 push   $0x2
  2:  ba 01 00 00 00        mov    $0x1,%edx
  7:  8d 4d fc              lea    -0x4(%ebp),%ecx
  a:  e8 00 00 00 00        call   0xf
"""

# `?log@S@@UAAXPBDZZ`：变参（强制 cdecl）；裸 ret、读集 ∅
C4_LOG = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  5d                    pop    %ebp
  4:  c3                    ret
"""

# `?idi@S@@UAEHH@Z` / `?idp@S@@UAEHPAX@Z`：**两体字节完全相同**（int ≡ 指针 的实测证据）
S1_IDI = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 45 08              mov    0x8(%ebp),%eax
  a:  8b e5                 mov    %ebp,%esp
  c:  5d                    pop    %ebp
  d:  c2 04 00              ret    $0x4
"""

# ---- C-3：r2.obj（cdecl 成员，this 在栈上） ----
C3_CF = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  8b 45 08              mov    0x8(%ebp),%eax
  6:  8b 4d 0c              mov    0xc(%ebp),%ecx
  9:  89 48 04              mov    %ecx,0x4(%eax)
  c:  5d                    pop    %ebp
  d:  c3                    ret
"""

C3_CF2 = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  8b 45 0c              mov    0xc(%ebp),%eax
  6:  03 45 10              add    0x10(%ebp),%eax
  9:  8b 4d 08              mov    0x8(%ebp),%ecx
  c:  89 41 04              mov    %eax,0x4(%ecx)
  f:  5d                    pop    %ebp
 10:  c3                    ret
"""

# r2 `ccall` 里 `p->cf(1)`：push 计数 = **2**（1 实参 + this）
C3_CCALL = """
  0:  6a 01                 push   $0x1
  2:  8b 45 08              mov    0x8(%ebp),%eax
  5:  8b 08                 mov    (%eax),%ecx
  7:  8b 55 08              mov    0x8(%ebp),%edx
  a:  52                    push   %edx
  b:  ff 11                 call   *(%ecx)
"""

# 裸 ret + 无任何读写/寄存器证据（既非 thiscall 也非 cdecl 可证）⇒ C 级
UNCLEAR_BARE_RET = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  5d                    pop    %ebp
  4:  c3                    ret
"""

# ---- C-5：e1.obj 三个空体（字节完全相同，13 字节） ----
C5_O_INT = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b e5                 mov    %ebp,%esp
  9:  5d                    pop    %ebp
  a:  c2 04 00              ret    $0x4
"""

# ---- C-6：b1.obj（BOOL 物化只在调用点可见） ----
C6_FB = C5_O_INT  # `?fb@SB@@UAEX_N@Z` 本体与 int 版逐字节相同（实测）
C6_FI = C5_O_INT  # `?fi@SB@@UAEXH@Z`

# b1 `c2(SB*, int)`：第一处调用 `p->fb(i)` = `setne` 物化（+5B），第二处 `p->fi(i)` = 裸 push
C6_C2_CALLS = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  33 c0                 xor    %eax,%eax
  5:  83 7d 0c 00           cmpl   $0x0,0xc(%ebp)
  9:  0f 95 c0              setne  %al
  c:  50                    push   %eax
  d:  8b 4d 08              mov    0x8(%ebp),%ecx
 10:  8b 11                 mov    (%ecx),%edx
 12:  8b 4d 08              mov    0x8(%ebp),%ecx
 15:  ff 12                 call   *(%edx)
 17:  8b 45 0c              mov    0xc(%ebp),%eax
 1a:  50                    push   %eax
 1b:  8b 4d 08              mov    0x8(%ebp),%ecx
 1e:  8b 11                 mov    (%ecx),%edx
 20:  8b 4d 08              mov    0x8(%ebp),%ecx
 23:  ff 52 04              call   *0x4(%edx)
"""

# ---- 分级/宽度/sret：_vtable_sig_probe_20260925/rw1.cpp（本轮真机实测） ----
# `?ri@Rn@@UAEHH@Z`：末尾 `mov 0x8(%ebp),%eax`（epilogue 前最后一次 eax 定义）⇒ i32
RW1_RI = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 45 08              mov    0x8(%ebp),%eax
  a:  8b e5                 mov    %ebp,%esp
  c:  5d                    pop    %ebp
  d:  c2 04 00              ret    $0x4
"""

RW1_RC = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8a 45 08              mov    0x8(%ebp),%al
  a:  8b e5                 mov    %ebp,%esp
  c:  5d                    pop    %ebp
  d:  c2 04 00              ret    $0x4
"""

RW1_RS = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  66 8b 45 08           mov    0x8(%ebp),%ax
  b:  8b e5                 mov    %ebp,%esp
  d:  5d                    pop    %ebp
  e:  c2 04 00              ret    $0x4
"""

# `?rf@Rn@@UAEMH@Z`：`fildl`（整数→x87）⇒ st(0) 结果宽度 f32/f64 **不可分**（rw2 实测同体）
RW1_RF = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  db 45 08              fildl  0x8(%ebp)
  a:  8b e5                 mov    %ebp,%esp
  c:  5d                    pop    %ebp
  d:  c2 04 00              ret    $0x4
"""

# `?rv@Rn@@UAEXH@Z`：eax 是 this 且被后续 store 消费 ⇒ 不是返回值 ⇒ 返回宽度未知
RW1_RV = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 45 fc              mov    -0x4(%ebp),%eax
  a:  8b 4d 08              mov    0x8(%ebp),%ecx
  d:  89 48 04              mov    %ecx,0x4(%eax)
 10:  8b e5                 mov    %ebp,%esp
 12:  5d                    pop    %ebp
 13:  c2 04 00              ret    $0x4
"""

# `?rb@Rn@@UAE?AUBig@@H@Z`：16B 结构返回 ⇒ sret 隐藏首参 @[ebp+8]，真值 1 参（ret 8 = sret + x）
RW1_RB = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  83 ec 14              sub    $0x14,%esp
  6:  89 4d ec              mov    %ecx,-0x14(%ebp)
  9:  8b 45 0c              mov    0xc(%ebp),%eax
  c:  89 45 f0              mov    %eax,-0x10(%ebp)
  f:  c7 45 f4 00 00 00 00  movl   $0x0,-0xc(%ebp)
 16:  c7 45 f8 00 00 00 00  movl   $0x0,-0x8(%ebp)
 1d:  c7 45 fc 00 00 00 00  movl   $0x0,-0x4(%ebp)
 24:  8b 4d 08              mov    0x8(%ebp),%ecx
 27:  8b 55 f0              mov    -0x10(%ebp),%edx
 2a:  89 11                 mov    %edx,(%ecx)
 2c:  8b 45 f4              mov    -0xc(%ebp),%eax
 2f:  89 41 04              mov    %eax,0x4(%ecx)
 32:  8b 55 f8              mov    -0x8(%ebp),%edx
 35:  89 51 08              mov    %edx,0x8(%ecx)
 38:  8b 45 fc              mov    -0x4(%ebp),%eax
 3b:  89 41 0c              mov    %eax,0xc(%ecx)
 3e:  8b 45 08              mov    0x8(%ebp),%eax
 41:  8b e5                 mov    %ebp,%esp
 43:  5d                    pop    %ebp
 44:  c2 08 00              ret    $0x8
"""

RW1_CV = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  8b 45 08              mov    0x8(%ebp),%eax
  6:  8b 4d 0c              mov    0xc(%ebp),%ecx
  9:  89 48 04              mov    %ecx,0x4(%eax)
  c:  5d                    pop    %ebp
  d:  c3                    ret
"""

# `?f1@Rn@@UAIXH@Z`：fastcall 成员 + **裸 ret**（0 栈参）⇒ arity = 1（仅 edx）
RW1_F1 = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  83 ec 08              sub    $0x8,%esp
  6:  89 55 f8              mov    %edx,-0x8(%ebp)
  9:  89 4d fc              mov    %ecx,-0x4(%ebp)
  c:  8b 45 fc              mov    -0x4(%ebp),%eax
  f:  8b 4d f8              mov    -0x8(%ebp),%ecx
 12:  89 48 04              mov    %ecx,0x4(%eax)
 15:  8b e5                 mov    %ebp,%esp
 17:  5d                    pop    %ebp
 18:  c3                    ret
"""

RW1_F0 = C5_O_INT  # thiscall 1 参（ret 4）

# `?f0u@Rn@@UAEXXZ`：thiscall 0 参 —— **裸 ret + ecx this** ⇒ 与 cdecl 靠 ecx 证据分开
RW1_F0U = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 45 fc              mov    -0x4(%ebp),%eax
  a:  c7 40 04 01 00 00 00  movl   $0x1,0x4(%eax)
 11:  8b e5                 mov    %ebp,%esp
 13:  5d                    pop    %ebp
 14:  c3                    ret
"""

# ---- rw2.cpp：f32/f64 返回不可分 + double 参数（2 槽）可由 qword 访问认出 ----
RW2_RF = RW1_RF  # `?rf@Rf@@UAEMH@Z` 与 `?rd@Rf@@UAENH@Z` 逐字节相同（实测）
# `?rfq@Rf@@UAEMN@Z`：`fldl`（qword 参数 ⇒ double，2 槽）+ `fsts`（⇒ 返回 float）+ ret 8
RW2_RFQ = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  83 ec 08              sub    $0x8,%esp
  6:  89 4d fc              mov    %ecx,-0x4(%ebp)
  9:  dd 45 08              fldl   0x8(%ebp)
  c:  d9 55 f8              fsts   -0x8(%ebp)
  f:  8b e5                 mov    %ebp,%esp
 11:  5d                    pop    %ebp
 12:  c2 08 00              ret    $0x8
"""

# ---- s3.obj `?two@SC@@UAEXHN@Z`：ret 0xc（3 槽）但读集 ∅ ⇒ 3 槽 ↛ 3 参（double 占双槽） ----
S3_TWO = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b e5                 mov    %ebp,%esp
  9:  5d                    pop    %ebp
  a:  c2 0c 00              ret    $0xc
"""

# ---- Task 2 合成槽金样本（T3 必须**跳过**，不推断签名） ----
ADJ_STATIC_FF = """
  0:  83 e9 08              sub    $0x8,%ecx
  3:  e9 00 00 00 00        jmp    0x8
"""

DTOR_GV = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 4d fc              mov    -0x4(%ebp),%ecx
  a:  e8 00 00 00 00        call   0xf
  f:  8b 45 08              mov    0x8(%ebp),%eax
 12:  83 e0 01              and    $0x1,%eax
 15:  85 c0                 test   %eax,%eax
 17:  74 0c                 je     0x25
 19:  8b 4d fc              mov    -0x4(%ebp),%ecx
 1c:  51                    push   %ecx
 1d:  e8 00 00 00 00        call   0x22
 22:  83 c4 04              add    $0x4,%esp
 25:  8b 45 fc              mov    -0x4(%ebp),%eax
 28:  8b e5                 mov    %ebp,%esp
 2a:  5d                    pop    %ebp
 2b:  c2 04 00              ret    $0x4
"""

COMPOSITE_ED = """
  0:  2b 49 fc              sub    -0x4(%ecx),%ecx
  3:  83 e9 10              sub    $0x10,%ecx
  6:  e9 00 00 00 00        jmp    0xb
"""

# s1 `_main` 里 `x.log("a",1)` 附近的**真实** objdump 文本 —— 含 PE-COFF 重定位注释行
# `6f: dir32\t$SG263`（本轮实测：该形态让 Task 2 解析器抛 ValueError）
PE_RELOC_TEXT = """
  6c:  6a 01                 push   $0x1
  6e:  68 00 00 00 00        push   $0x0
\t\t\t6f: dir32\t$SG263
  73:  8d 45 fc              lea    -0x4(%ebp),%eax
  76:  50                    push   %eax
  77:  e8 00 00 00 00        call   7c <_main+0x38>
\t\t\t78: DISP32\t?log@S@@UAAXPBDZZ-0x1f
  7c:  83 c4 0c              add    $0xc,%esp
"""

# esp 跟踪中断（`and $0xf0,%esp` 对齐）⇒ 栈参基址不可定位
BROKEN_ESP = """
  0:  83 e4 f0              and    $0xfffffff0,%esp
  3:  8b 44 24 04           mov    0x4(%esp),%eax
  7:  c2 04 00              ret    $0x4
"""

# 非空但解析不出任何指令（objdump 纯字节行）⇒ Task2 `insufficient_evidence`
BYTE_JUNK = """
  0:  00
  1:  00 00 00 00
  5:  00
"""



# ---- rw3.cpp：bool 返回（setcc 物化）/ char 返回 / __int64 返回（cltd） ----
RW3_RBOOL = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  33 c0                 xor    %eax,%eax
  9:  83 7d 08 00           cmpl   $0x0,0x8(%ebp)
  d:  0f 95 c0              setne  %al
 10:  8b e5                 mov    %ebp,%esp
 12:  5d                    pop    %ebp
 13:  c2 04 00              ret    $0x4
"""

RW3_RCHAR = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8a 45 08              mov    0x8(%ebp),%al
  a:  8b e5                 mov    %ebp,%esp
  c:  5d                    pop    %ebp
  d:  c2 04 00              ret    $0x4
"""

RW3_R64 = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 45 08              mov    0x8(%ebp),%eax
  a:  99                    cltd
  b:  8b e5                 mov    %ebp,%esp
  d:  5d                    pop    %ebp
  e:  c2 04 00              ret    $0x4
"""

# ---- rw4.cpp：sret 阴性（"指针参数 + 大范围写"不得判 sret）与真 sret ----
RW4_RETP = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 45 08              mov    0x8(%ebp),%eax
  a:  c7 00 01 00 00 00     movl   $0x1,(%eax)
 10:  8b 4d 08              mov    0x8(%ebp),%ecx
 13:  c7 41 04 02 00 00 00  movl   $0x2,0x4(%ecx)
 1a:  8b 55 08              mov    0x8(%ebp),%edx
 1d:  c7 42 08 03 00 00 00  movl   $0x3,0x8(%edx)
 24:  8b 45 08              mov    0x8(%ebp),%eax
 27:  8b e5                 mov    %ebp,%esp
 29:  5d                    pop    %ebp
 2a:  c2 04 00              ret    $0x4
"""

RW4_RETP2 = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 45 08              mov    0x8(%ebp),%eax
  a:  c7 00 07 00 00 00     movl   $0x7,(%eax)
 10:  8b 45 08              mov    0x8(%ebp),%eax
 13:  8b e5                 mov    %ebp,%esp
 15:  5d                    pop    %ebp
 16:  c2 04 00              ret    $0x4
"""

RW4_WR = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 45 08              mov    0x8(%ebp),%eax
  a:  c7 00 01 00 00 00     movl   $0x1,(%eax)
 10:  8b 4d 08              mov    0x8(%ebp),%ecx
 13:  c7 41 04 02 00 00 00  movl   $0x2,0x4(%ecx)
 1a:  8b 55 08              mov    0x8(%ebp),%edx
 1d:  c7 42 08 03 00 00 00  movl   $0x3,0x8(%edx)
 24:  8b e5                 mov    %ebp,%esp
 26:  5d                    pop    %ebp
 27:  c2 04 00              ret    $0x4
"""

RW4_MK = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  83 ec 10              sub    $0x10,%esp
  6:  89 4d f0              mov    %ecx,-0x10(%ebp)
  9:  8b 45 0c              mov    0xc(%ebp),%eax
  c:  89 45 f4              mov    %eax,-0xc(%ebp)
  f:  c7 45 f8 00 00 00 00  movl   $0x0,-0x8(%ebp)
 16:  c7 45 fc 00 00 00 00  movl   $0x0,-0x4(%ebp)
 1d:  8b 4d 08              mov    0x8(%ebp),%ecx
 20:  8b 55 f4              mov    -0xc(%ebp),%edx
 23:  89 11                 mov    %edx,(%ecx)
 25:  8b 45 f8              mov    -0x8(%ebp),%eax
 28:  89 41 04              mov    %eax,0x4(%ecx)
 2b:  8b 55 fc              mov    -0x4(%ebp),%edx
 2e:  89 51 08              mov    %edx,0x8(%ecx)
 31:  8b 45 08              mov    0x8(%ebp),%eax
 34:  8b e5                 mov    %ebp,%esp
 36:  5d                    pop    %ebp
 37:  c2 08 00              ret    $0x8
"""

# 0 实参 sret（12B / 16B）—— Ruling 6 的边界形态
RW4_MK0 = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  83 ec 10              sub    $0x10,%esp
  6:  89 4d f0              mov    %ecx,-0x10(%ebp)
  9:  c7 45 f4 01 00 00 00  movl   $0x1,-0xc(%ebp)
 10:  c7 45 f8 02 00 00 00  movl   $0x2,-0x8(%ebp)
 17:  c7 45 fc 03 00 00 00  movl   $0x3,-0x4(%ebp)
 1e:  8b 45 08              mov    0x8(%ebp),%eax
 21:  8b 4d f4              mov    -0xc(%ebp),%ecx
 24:  89 08                 mov    %ecx,(%eax)
 26:  8b 55 f8              mov    -0x8(%ebp),%edx
 29:  89 50 04              mov    %edx,0x4(%eax)
 2c:  8b 4d fc              mov    -0x4(%ebp),%ecx
 2f:  89 48 08              mov    %ecx,0x8(%eax)
 32:  8b 45 08              mov    0x8(%ebp),%eax
 35:  8b e5                 mov    %ebp,%esp
 37:  5d                    pop    %ebp
 38:  c2 04 00              ret    $0x4
"""

RW4_MK0B = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  83 ec 14              sub    $0x14,%esp
  6:  89 4d ec              mov    %ecx,-0x14(%ebp)
  9:  c7 45 f0 01 00 00 00  movl   $0x1,-0x10(%ebp)
 10:  c7 45 f4 02 00 00 00  movl   $0x2,-0xc(%ebp)
 17:  c7 45 f8 03 00 00 00  movl   $0x3,-0x8(%ebp)
 1e:  c7 45 fc 04 00 00 00  movl   $0x4,-0x4(%ebp)
 25:  8b 45 08              mov    0x8(%ebp),%eax
 28:  8b 4d f0              mov    -0x10(%ebp),%ecx
 2b:  89 08                 mov    %ecx,(%eax)
 2d:  8b 55 f4              mov    -0xc(%ebp),%edx
 30:  89 50 04              mov    %edx,0x4(%eax)
 33:  8b 4d f8              mov    -0x8(%ebp),%ecx
 36:  89 48 08              mov    %ecx,0x8(%eax)
 39:  8b 55 fc              mov    -0x4(%ebp),%edx
 3c:  89 50 0c              mov    %edx,0xc(%eax)
 3f:  8b 45 08              mov    0x8(%ebp),%eax
 42:  8b e5                 mov    %ebp,%esp
 44:  5d                    pop    %ebp
 45:  c2 04 00              ret    $0x4
"""

# ---- opt1.cpp / opt2.cpp：**真实项目开关** /O2 /Ob2 /Oi /Ot /Oy /GR（无帧指针） ----
# `?zero@Op@@UAEXH@Z`：ecx 直接作成员基址（无溢出）⇒ thiscall 证据来自"ecx 作内存基址"
OPT1_ZERO = """
  0:  c7 41 04 00 00 00 00  movl   $0x0,0x4(%ecx)
  7:  c2 04 00              ret    $0x4
   a:  90                    nop
   b:  90                    nop
"""

# `?add1@Op@@UAEHH@Z`：esp 相对栈参（无帧指针）+ `inc %eax` 返回
OPT1_ADD1 = """
  0:  8b 44 24 04           mov    0x4(%esp),%eax
  4:  40                    inc    %eax
  5:  c2 04 00              ret    $0x4
  8:  90                    nop
"""

# `?sd@Os@@UAGXH@Z`（__stdcall 成员）：this@[esp+4] 解引用 + `ret 8`
OPT2_SD = """
  0:  8b 44 24 04           mov    0x4(%esp),%eax
  4:  8b 4c 24 08           mov    0x8(%esp),%ecx
  8:  89 48 04              mov    %ecx,0x4(%eax)
  b:  c2 08 00              ret    $0x8
"""

# `?cd@Os@@UAAXH@Z`（__cdecl 成员）：同形但**裸 ret** ⇒ caller 清栈
OPT2_CD = """
  0:  8b 44 24 04           mov    0x4(%esp),%eax
  4:  8b 4c 24 08           mov    0x8(%esp),%ecx
  8:  89 48 04              mov    %ecx,0x4(%eax)
  b:  c3                    ret
"""

# `?fe@Os@@UAIXH@Z`（__fastcall 成员）：edx **直接作源**（无溢出）+ 裸 ret ⇒ arity 1
OPT2_FE = """
  0:  89 51 04              mov    %edx,0x4(%ecx)
  3:  c3                    ret
"""

# `?fu@Os@@UAIXH@Z`（__fastcall 成员、x 未用）：与 thiscall 0 参**逐字节同形** ⇒ 已知盲区
OPT2_FU = """
  0:  c7 41 04 00 00 00 00  movl   $0x0,0x4(%ecx)
  7:  c3                    ret
"""

# `?t2@Os@@UAEHHH@Z`：esp 相对两个栈参（读序倒置）+ `ret 8`
OPT2_T2 = """
  0:  8b 44 24 08           mov    0x8(%esp),%eax
  4:  8b 4c 24 04           mov    0x4(%esp),%ecx
  8:  03 c1                 add    %ecx,%eax
  a:  c2 08 00              ret    $0x8
"""


def notes_of(cand):
    return ' | '.join(cand.notes)


# ==========================================================================
# 0. Ruling 1 —— 只接受原始文本（禁止喂 Insn 元组）
# ==========================================================================

def test_ruling1_disasm_must_be_raw_text():
    """喂已解析的 Insn 元组 ⇒ 必须 `TypeError`（证据不足痕迹会失效，静默判 fn）"""
    with unittest.TestCase().assertRaises(TypeError):
        infer_signature(E(addr='0x0', disasm=(object(),)))


def test_ruling1_empty_text_is_not_silently_a_zero_arg_fn():
    """空输入 ⇒ C 级 + 证据不足痕迹（不得当"0 参 void"）"""
    cand = infer_signature(E(addr='0x0', disasm=''))
    assert cand is not None, cand
    assert cand.grade == GRADE_C, cand
    assert FEATURE_INSUFFICIENT_EVIDENCE in cand.features, cand.features


def test_ruling2_insufficient_evidence_is_flagged_not_defaulted():
    """Ruling 2：`classify_slot` 判 fn 且**证据不足** ⇒ 不得当安全默认 ⇒ C 级 + 痕迹"""
    cand = infer_signature(E(addr='0x0', disasm=BYTE_JUNK))
    assert cand.grade == GRADE_C, (cand.grade, cand.notes)
    assert FEATURE_INSUFFICIENT_EVIDENCE in cand.features, cand.features
    assert '证据不足' in notes_of(cand), cand.notes


def test_ruling2_genuine_fn_without_notes_still_infers():
    """对照：证据充分的普通函数（Task2 判 fn、零特征）必须正常推断（不得因"notes 空"拒绝）"""
    cand = infer_signature(E(addr='0x0', name='ri', disasm=RW1_RI))
    assert cand.grade == GRADE_A, (cand.grade, cand.notes)
    assert FEATURE_INSUFFICIENT_EVIDENCE not in cand.features


# ==========================================================================
# 1. C-1 未用参数：读集 ∅ 必须用 ret N 补足
# ==========================================================================

def test_c1_unused_params_are_recovered_from_ret_n():
    """C-1（s1 `?unused@S@@UAEXHH@Z`）：读集 ∅（真值 2 参）⇒ `ret 8` 补足 2 参 + 隐藏参数痕迹"""
    cand = infer_signature(E(addr='0x0', name='unused', symbol='?unused@S@@UAEXHH@Z',
                             disasm=C1_UNUSED))
    assert cand.convention == CC_THISCALL, cand
    assert cand.read_slots == 0, cand
    assert cand.stack_slots == 2, cand
    assert cand.arity == 2, cand
    assert FEATURE_HIDDEN_PARAM_SUSPICION in cand.features, cand.features
    assert '隐藏参数' in notes_of(cand), cand.notes
    # 读集单独只给 0 ⇒ 不得把它当参数个数
    assert cand.grade == GRADE_B, cand
    assert cand.signature == '? __thiscall unused(?,?)', cand.signature


# ==========================================================================
# 2. C-2 __fastcall（Ruling 3）
# ==========================================================================

def test_c2_fastcall_detected_from_edx_entry_spill():
    """C-2（s1 `?freg@S@@UAIXHH@Z`）：edx 入口溢出 + ret 4 ⇒ fastcall，真值 2 参"""
    cand = infer_signature(E(addr='0xd', name='freg', symbol='?freg@S@@UAIXHH@Z',
                             disasm=C2_FREG))
    assert cand.convention == CC_FASTCALL, cand
    assert FEATURE_EDX_REG_ARG in cand.features, cand.features
    assert cand.reg_arg_count == 1, cand
    assert cand.stack_slots == 1, cand
    assert cand.arity == 2, cand
    assert 'fastcall' in cand.signature, cand.signature


def test_c2_call_site_alone_would_say_one_arg():
    """C-2 反例的另一半：调用点 push 计数 = **1**（只数 push 必然推错）"""
    sites = analyze_call_sites(C2_FREG_CALL)
    assert len(sites) == 1, sites
    assert sites[0].push_count == 1, sites[0]
    assert 'edx' in sites[0].reg_args, sites[0]


def test_c2_call_site_crosscheck_is_consistent_with_callee():
    """callee（fastcall，栈 1 槽）与调用点（push 1 + edx）**一致** ⇒ 标记为一致旁证"""
    cand = infer_signature(E(addr='0xd', name='freg', disasm=C2_FREG,
                             call_sites=(C2_FREG_CALL,)))
    assert cand.call_site_consistent is True, (cand.call_site_consistent, cand.notes)


def test_ruling3_bare_ret_fastcall_is_still_fastcall():
    """Ruling 3 明文："首参在 edx/ecx，callee **裸 ret**" —— `?f1@Rn@@UAIXH@Z` 即此形态
    （fastcall 成员 + 0 栈参 ⇒ 裸 ret），arity 必须 = 1（仅 edx），不得判 0 参"""
    cand = infer_signature(E(addr='0xac', name='f1', disasm=RW1_F1))
    assert cand.convention == CC_FASTCALL, cand
    assert cand.arity == 1, cand
    assert cand.stack_slots == 0, cand
    assert FEATURE_EDX_REG_ARG in cand.features, cand.features


def test_ruling3_thiscall_must_not_be_misread_as_fastcall():
    """阴性：thiscall 只溢出 ecx（无 edx 入口证据）⇒ 不得判 fastcall"""
    cand = infer_signature(E(addr='0x0', name='unused', disasm=C1_UNUSED))
    assert cand.convention == CC_THISCALL, cand
    assert FEATURE_EDX_REG_ARG not in cand.features, cand.features


# ==========================================================================
# 3. C-3 __cdecl 成员：this 在栈上（Ruling 4）
# ==========================================================================

def test_c3_cdecl_member_this_on_stack_is_deducted():
    """C-3（r2 `?cf@Xc@@UAAXH@Z`）：读集含 [ebp+8]=this ⇒ 推 2 参（真值 1）⇒ 必须扣除"""
    cand = infer_signature(E(addr='0x0', name='cf', symbol='?cf@Xc@@UAAXH@Z', disasm=C3_CF))
    assert cand.convention == CC_CDECL, cand
    assert cand.read_slots == 2, cand          # 原始读集（含 this）
    assert cand.this_on_stack is True, cand
    assert FEATURE_THIS_ON_STACK in cand.features, cand.features
    assert cand.arity == 1, cand               # 扣除 this
    assert 'this' in notes_of(cand), cand.notes


def test_c3_cf2_three_read_slots_minus_this_is_two_params():
    """C-3 同型 `?cf2@Xc@@UAAXHH@Z`：读集 3 槽 − this = 2 参（真值 2）"""
    cand = infer_signature(E(addr='0xe', name='cf2', symbol='?cf2@Xc@@UAAXHH@Z', disasm=C3_CF2))
    assert cand.convention == CC_CDECL, cand
    assert cand.read_slots == 3, cand
    assert cand.arity == 2, cand


def test_c3_call_site_push_count_two_confirms_the_wrong_answer_without_the_rule():
    """C-3 反例的另一半：调用点 push = **2**（this + 实参）⇒ 与"错误读集"互相确认；
    正确做法是两侧都按"this 在栈"解释后一致（push 2 = arity 1 + this）"""
    sites = analyze_call_sites(C3_CCALL)
    assert len(sites) == 1 and sites[0].push_count == 2, sites
    cand = infer_signature(E(addr='0x0', name='cf', disasm=C3_CF, call_sites=(C3_CCALL,)))
    assert cand.arity == 1, cand
    assert cand.call_site_consistent is True, (cand.call_site_consistent, cand.notes)


def test_ruling4_thiscall_must_not_deduct_a_phantom_this():
    """阴性（Ruling 4）：thiscall 的 this 在 ecx（已溢出）⇒ `ret 4` 就是 1 参，不得再扣"""
    cand = infer_signature(E(addr='0x0', name='f0', disasm=RW1_F0))
    assert cand.convention == CC_THISCALL, cand
    assert cand.this_on_stack is False, cand
    assert cand.arity == 1, cand


def test_ruling4_bare_ret_thiscall_zero_args_vs_cdecl_unknown():
    """裸 ret 的二义性必须靠 ecx 证据解开：
       * thiscall 0 参（ecx 溢出 + 裸 ret）⇒ arity 0
       * cdecl（无 ecx 证据 + 裸 ret + 读集只到 this 槽）⇒ 参数个数不可定 ⇒ C 级"""
    thiscall0 = infer_signature(E(addr='0xdb', name='f0u', disasm=RW1_F0U))
    assert thiscall0.convention == CC_THISCALL, thiscall0
    assert thiscall0.arity == 0, thiscall0
    # 只有裸 ret（无读写）⇒ 既非 thiscall 也非 cdecl 可证
    unclear = infer_signature(E(addr='0x9e', name='cfx', disasm=UNCLEAR_BARE_RET))
    assert unclear.arity is None, unclear
    assert unclear.grade == GRADE_C, unclear


# ==========================================================================
# 4. C-4 变参
# ==========================================================================

def test_c4_variadic_is_recognized_and_graded_c():
    """C-4（s1 `?log@S@@UAAXPBDZZ`）：虚变参 mangling `UAA…ZZ` ⇒ 识别变参 + C 级"""
    cand = infer_signature(E(addr='0x1f', name='log', symbol='?log@S@@UAAXPBDZZ', disasm=C4_LOG))
    assert cand.variadic is True, cand
    assert FEATURE_VARIADIC in cand.features, cand.features
    assert cand.convention == CC_CDECL, cand
    assert cand.arity is None, cand
    assert cand.grade == GRADE_C, cand
    assert '...' in cand.signature, cand.signature


def test_c4_non_variadic_is_not_flagged():
    """阴性：单 `Z` 结尾（非 `ZZ`）不得判变参"""
    cand = infer_signature(E(addr='0x0', name='unused', symbol='?unused@S@@UAEXHH@Z',
                             disasm=C1_UNUSED))
    assert cand.variadic is False, cand
    assert FEATURE_VARIADIC not in cand.features, cand.features


# ==========================================================================
# 5. C-5 ICF / 同体折叠：一地址多签名
# ==========================================================================

def test_c5_identical_bodies_are_detected_as_one_icf_group():
    """C-5：e1 三个空体（int/void*/float）**字节相同** ⇒ 必须能识别为一个 ICF 组"""
    groups = find_icf_groups({'0x0': C5_O_INT, '0xd': C5_O_INT, '0x1a': C5_O_INT})
    assert len(groups) == 1, groups
    assert groups[0] == ('0x0', '0x1a', '0xd'), groups


def test_c5_one_address_may_carry_multiple_signatures():
    """C-5：折叠后**一地址对 3 签名 3 槽** ⇒ 记录必须是**多候选** + 标 ICF + 不得给 A 级"""
    evs = [E(addr='0x0', symbol=s, disasm=C5_O_INT)
           for s in ('?o@E@@UAEXH@Z', '?o@E@@UAEXPAX@Z', '?o@E@@UAEXM@Z')]
    rec = infer_address_record('0x0', evs)
    assert len(rec.candidates) == 3, rec
    assert rec.icf_folded is True, rec
    assert rec.ambiguous is True, rec
    assert FEATURE_ICF_FOLDED in rec.features, rec.features
    assert all(c.grade != GRADE_A for c in rec.candidates), [c.grade for c in rec.candidates]
    # 三候选结构化部分相同（callee 不可分），仅符号不同 —— 不得声称唯一等价类
    assert len({(c.convention, c.arity, c.return_kind) for c in rec.candidates}) == 1
    assert all(c.param_class_undetermined for c in rec.candidates)


def test_c5_single_evidence_address_is_not_marked_icf():
    """阴性：单候选地址不得标 ICF"""
    rec = infer_address_record('0x0', [E(addr='0x0', name='ri', disasm=RW1_RI)])
    assert rec.icf_folded is False, rec
    assert rec.ambiguous is False, rec
    assert len(rec.candidates) == 1, rec


# ==========================================================================
# 6. C-6 BOOL/char/short 单独成类（Ruling 5）
# ==========================================================================

def test_c6_callee_cannot_distinguish_bool_from_int():
    """C-6（b1 `?fb@SB@@UAEX_N@Z` vs `?fi@SB@@UAEXH@Z`）：本体逐字节相同 ⇒
    callee 侧等价类**不可分** ⇒ 必须留 `param_class_undetermined` + 候选类含 bool 与 i32"""
    fb = infer_signature(E(addr='0x0', name='fb', symbol='?fb@SB@@UAEX_N@Z', disasm=C6_FB))
    fi = infer_signature(E(addr='0xd', name='fi', symbol='?fi@SB@@UAEXH@Z', disasm=C6_FI))
    assert (fb.convention, fb.arity, fb.return_kind) == (fi.convention, fi.arity, fi.return_kind)
    assert fb.param_class_undetermined and fi.param_class_undetermined, (fb, fi)
    cands = fb.params[0].class_candidates
    assert 'bool' in cands and 'i32' in cands, cands
    assert len(cands) > 1, cands
    assert FEATURE_AMBIGUOUS_PARAM_CLASS in fb.features, fb.features


def test_c6_bool_is_not_byte_equivalent_to_int():
    """Ruling 5：BOOL **不**与 int 字节等价（调用点 +5B 物化）⇒ 等价类必须分开"""
    assert param_class_equiv('bool', 'i32') is False
    assert param_class_family('bool') != param_class_family('i32')


def test_c6_char_and_short_are_separate_classes_too():
    """Ruling 5：BOOL/char/short 单独成类（窄化转换会物化）"""
    assert param_class_equiv('i8', 'i32') is False
    assert param_class_equiv('i16', 'i32') is False
    assert param_class_equiv('char', 'i8') is True
    assert param_class_equiv('short', 'i16') is True
    # int/指针在 ABI 上字节等价（s1 idi/idp 逐字节同体实测）—— 但等价 ≠ 可断言类型
    assert param_class_equiv('i32', 'ptr') is True


def test_c6_bool_materialization_is_visible_at_the_call_site():
    """C-6 的正向证据：`p->fb(i)` = `xor; cmp; setne al; push`（物化）vs `p->fi(i)` = 裸 push"""
    sites = analyze_call_sites(C6_C2_CALLS)
    assert len(sites) == 2, sites
    assert sites[0].bool_materialized is True, sites[0]
    assert sites[0].arg_classes == ('bool',), sites[0]
    assert sites[1].bool_materialized is False, sites[1]
    assert 'bool' not in sites[1].arg_classes, sites[1]


# ==========================================================================
# 7. 分级 A/B/C（A = 约定 + 参数个数 + 返回宽度全定）
# ==========================================================================

def test_grade_a_requires_return_width_evidence():
    """A 级：thiscall + ret 4 + 末尾 eax 定义是 epilogue 前最后一条 ⇒ i32，arity 1"""
    cand = infer_signature(E(addr='0x0', name='ri', disasm=RW1_RI))
    assert (cand.convention, cand.arity, cand.return_kind) == (CC_THISCALL, 1, RET_I32), cand
    assert cand.grade == GRADE_A, (cand.grade, cand.notes)
    # A 级**不**意味着参数等价类已定（spec §4.2 只要求约定+个数+返回宽度）
    assert cand.param_class_undetermined is True, cand


def test_grade_a_narrow_returns():
    """A 级：8/16 位返回（`mov ...,%al` / `mov ...,%ax`）宽度可测"""
    rc = infer_signature(E(addr='0x10', name='rc', disasm=RW1_RC))
    rs = infer_signature(E(addr='0x20', name='rs', disasm=RW1_RS))
    assert (rc.return_kind, rc.grade) == (RET_I8, GRADE_A), rc
    assert (rs.return_kind, rs.grade) == (RET_I16, GRADE_A), rs


def test_grade_b_when_return_width_unobservable():
    """B 级：约定 + 个数已定但**缺返回宽度**（eax 被后续 store 消费 ⇒ 非返回值）"""
    cand = infer_signature(E(addr='0x41', name='rv', disasm=RW1_RV))
    assert cand.return_kind == RET_UNKNOWN, cand
    assert cand.arity == 1, cand
    assert cand.grade == GRADE_B, cand


def test_grade_b_when_fp_return_width_is_ambiguous():
    """B 级：`fildl`（整数→x87）⇒ f32/f64 不可分（rw2 实测 `rf`/`rd` 同体）⇒ 不得猜"""
    rf = infer_signature(E(addr='0x31', name='rf', disasm=RW2_RF))
    assert rf.return_kind == RET_UNKNOWN, rf
    assert FEATURE_FP_WIDTH_AMBIGUOUS in rf.features, rf.features
    assert rf.grade == GRADE_B, rf


def test_grade_a_fp_return_width_when_size_is_visible():
    """A 级：`fldl` 参数（double，2 槽）+ `fsts`（返回 float）⇒ 宽度可测 ⇒ arity 1、返回 f32"""
    cand = infer_signature(E(addr='0x20', name='rfq', disasm=RW2_RFQ))
    assert cand.return_kind == RET_F32, cand
    assert cand.convention == CC_THISCALL, cand
    assert cand.stack_slots == 2, cand
    assert cand.arity == 1, cand
    assert cand.params[0].slots == 2, cand
    assert cand.params[0].class_candidates == frozenset({'f64'}), cand
    assert cand.grade == GRADE_A, (cand.grade, cand.notes)
    assert cand.signature == 'float __thiscall rfq(double)', cand.signature


def test_grade_b_when_slot_count_cannot_be_mapped_to_param_count():
    """B 级：s3 `?two@SC@@UAEXHN@Z` —— ret 0xc（3 槽）但读集 ∅ ⇒ 3 槽 ↛ 3 参
    （double/int64 占双槽）⇒ arity 是**槽数估计**且必须带隐藏参数痕迹"""
    cand = infer_signature(E(addr='0x24', name='two', disasm=S3_TWO))
    assert cand.stack_slots == 3, cand
    assert cand.arity == 3, cand
    assert FEATURE_HIDDEN_PARAM_SUSPICION in cand.features, cand.features
    assert cand.grade == GRADE_B, cand
    assert 'double' in notes_of(cand) or '双槽' in notes_of(cand), cand.notes


def test_grade_c_for_variadic_and_unknown():
    """C 级：参数个数不确定（变参 / 零证据）"""
    assert infer_signature(E(addr='0x1f', disasm=C4_LOG, symbol='?log@S@@UAAXPBDZZ')).grade == GRADE_C
    assert infer_signature(E(addr='0x0', disasm='')).grade == GRADE_C


# ==========================================================================
# 8. Ruling 6 —— sret（返回 >8B 结构的隐藏首参）
# ==========================================================================

def test_ruling6_sret_hidden_first_param_is_deducted():
    """Ruling 6（rw1 `?rb@Rn@@UAE?AUBig@@H@Z`）：ret 8 = sret 指针 + 1 实参 ⇒
    必须扣除隐藏首参（arity 1，非 2），并标返回为 >8B 结构"""
    cand = infer_signature(E(addr='0x57', name='rb', disasm=RW1_RB))
    assert FEATURE_SRET in cand.features, cand.features
    assert cand.stack_slots == 2, cand          # 原始槽数
    assert cand.arity == 1, cand                # 扣除 sret 后
    assert cand.return_kind == RET_SRET, cand
    assert 'sret' in notes_of(cand), cand.notes


def test_ruling6_non_sret_is_not_flagged():
    """阴性（Ruling 6）：普通 thiscall（eax 即返回值）不得误判 sret"""
    for fx, nm in ((RW1_RI, 'ri'), (C1_UNUSED, 'unused'), (RW1_RV, 'rv')):
        cand = infer_signature(E(addr='0x0', name=nm, disasm=fx))
        assert FEATURE_SRET not in cand.features, (nm, cand.features)


# ==========================================================================
# 9. 合成槽跳过（Task 2 消费）+ 无 ecx 无 ret 的未知约定
# ==========================================================================

def test_synthetic_slots_are_skipped_not_signed():
    """T2↔T3 契约"T3 消费跳过合成槽"：adjustor / deleting_dtor / composite / purecall
    一律**不推断签名**（返回 None + 痕迹），交 IDA 定性"""
    assert infer_signature(E(addr='0x0', disasm=ADJ_STATIC_FF)) is None
    assert infer_signature(E(addr='0x0', symbol='??_GV@@UAEPAXI@Z', signature='void*(unsigned)',
                             disasm=DTOR_GV)) is None
    assert infer_signature(E(addr='0x0', disasm=COMPOSITE_ED)) is None
    assert infer_signature(E(addr='0x0', is_external=True,
                             external_symbol='__purecall')) is None
    rec = infer_address_record('0x0', [E(addr='0x0', disasm=ADJ_STATIC_FF)])
    assert rec.candidates == (), rec
    assert rec.skipped is True, rec


def test_stdcall_member_this_on_stack_callee_clean():
    """`__stdcall` 成员：无 ecx this 证据 + `ret N`（callee 清栈）⇒ this 在栈，arity = N/4 − 1"""
    stdcall = """
      0:  55                    push   %ebp
      1:  8b ec                 mov    %esp,%ebp
      3:  8b 45 08              mov    0x8(%ebp),%eax
      6:  8b 4d 0c              mov    0xc(%ebp),%ecx
      9:  89 48 04              mov    %ecx,0x4(%eax)
      c:  5d                    pop    %ebp
      d:  c2 08 00              ret    $0x8
    """
    cand = infer_signature(E(addr='0x0', name='sd', disasm=stdcall))
    assert cand.convention == CC_STDCALL, cand
    assert cand.arity == 1, cand
    assert cand.this_on_stack is True, cand


# ==========================================================================
# 10. methods_pending 旁路：绝不写 methods 真相源
# ==========================================================================

def test_methods_pending_is_a_bypass_field_and_methods_is_untouched():
    struct = {'name': 'S', 'methods': {'0x401000': {'name': 'f', 'signature': 'void f()'}}}
    rec = infer_address_record('0x0', [E(addr='0x0', name='unused', disasm=C1_UNUSED)])
    out = build_methods_pending(struct, [rec])
    # 真相源逐字未动；旁路字段是**新增副本**
    assert struct == {'name': 'S', 'methods': {'0x401000': {'name': 'f',
                                                           'signature': 'void f()'}}}
    assert 'methods_pending' not in struct
    assert out['methods'] == struct['methods'], out['methods']
    assert out['name'] == 'S'
    mp = out['methods_pending']
    assert list(mp) == ['0x00000000'], mp          # 键格式对齐真相源 methods（'0x%08X'）
    assert mp['0x00000000']['candidates'][0]['grade'] == GRADE_B, mp
    assert mp['0x00000000']['icf_folded'] is False
    assert mp['0x00000000']['candidates'][0]['arity'] == 2


def test_methods_pending_conflict_with_existing_methods_is_recorded_not_overwritten():
    """真相源已声明该地址且签名不同 ⇒ 只记冲突（旁路），methods 永远不动"""
    struct = {'name': 'S', 'methods': {'0x0': {'name': 'unused', 'signature': 'void unused()'}}}
    rec = infer_address_record('0x0', [E(addr='0x0', name='unused', disasm=C1_UNUSED)])
    out = build_methods_pending(struct, [rec])
    assert out['methods'] == {'0x0': {'name': 'unused', 'signature': 'void unused()'}}
    assert out['methods_pending']['0x00000000']['conflicts'], out['methods_pending']
    assert any('void unused()' in c
               for c in out['methods_pending']['0x00000000']['conflicts'])


def test_methods_pending_is_json_serializable():
    import json
    struct = {'name': 'E', 'methods': {}}
    rec = infer_address_record('0x0', [E(addr='0x0', symbol='?o@E@@UAEXH@Z', disasm=C5_O_INT),
                                       E(addr='0x0', symbol='?o@E@@UAEXPAX@Z', disasm=C5_O_INT)])
    out = build_methods_pending(struct, [rec])
    text = json.dumps(out, ensure_ascii=False)
    back = json.loads(text)
    assert back['methods_pending']['0x00000000']['icf_folded'] is True
    assert len(back['methods_pending']['0x00000000']['candidates']) == 2


# ==========================================================================
# 11. 结果确定性（同输入 ⇒ 同输出）
# ==========================================================================

def test_deterministic_output():
    a = infer_signature(E(addr='0x0', name='k', disasm=C1_UNUSED))
    b = infer_signature(E(addr='0x0', name='k', disasm=C1_UNUSED))
    assert a == b, (a, b)
    ra = infer_address_record('0x0', [E(addr='0x0', symbol='?o@E@@UAEXH@Z', disasm=C5_O_INT),
                                      E(addr='0x0', symbol='?o@E@@UAEXPAX@Z', disasm=C5_O_INT)])
    rb = infer_address_record('0x0', [E(addr='0x0', symbol='?o@E@@UAEXPAX@Z', disasm=C5_O_INT),
                                      E(addr='0x0', symbol='?o@E@@UAEXH@Z', disasm=C5_O_INT)])
    assert ra.icf_folded == rb.icf_folded is True
    assert [c.symbol for c in ra.candidates] == [c.symbol for c in rb.candidates]




def test_c5_int_and_pointer_callee_bytes_are_indistinguishable():
    """C-5 的前提证据：s1 `?idi@S@@UAEHH@Z`(int) 与 `?idp@S@@UAEHPAX@Z`(void*) 本体
    **逐字节相同** ⇒ callee 侧分不出 int/指针（`i32`/`ptr` 属同一字节族）；
    但这**不等于**可以断言类型 ⇒ 仍须 `param_class_undetermined`。"""
    idi = infer_signature(E(addr='0x24', name='idi', symbol='?idi@S@@UAEHH@Z', disasm=S1_IDI))
    idp = infer_signature(E(addr='0x34', name='idp', symbol='?idp@S@@UAEHPAX@Z', disasm=S1_IDI))
    assert (idi.convention, idi.arity, idi.return_kind) == (CC_THISCALL, 1, RET_I32), idi
    assert (idp.convention, idp.arity, idp.return_kind) == (idi.convention, idi.arity,
                                                            idi.return_kind), idp
    assert param_class_equiv('i32', 'ptr') is True
    assert idi.param_class_undetermined is True, idi
    assert 'i32' in idi.params[0].class_candidates and 'ptr' in idi.params[0].class_candidates


def test_cdecl_member_shape_confirmed_across_probe_tus():
    """跨 TU 复现：rw1 `?cv@Rn@@UAAXH@Z`（cdecl 成员）与 r2 `?cf` 同判
    （this 在首栈槽、arity 下界 1）—— 结论不依赖单一 TU 的寄存器分配"""
    cv = infer_signature(E(addr='0x9e', name='cv', disasm=RW1_CV))
    assert cv.convention == CC_CDECL, cv
    assert cv.this_on_stack is True and cv.arity == 1, cv
    assert cv.arity_is_lower_bound is True, cv


# ==========================================================================
# 12. 返回类细化：bool（setcc 物化）/ char / __int64（cltd）
# ==========================================================================

def test_bool_return_is_distinct_from_char_return():
    """Ruling 5 的返回侧：`bool f(){return x!=0;}` 是 `setcc %al`（物化），
    与 `char f()` 的 `mov ...,%al` 形不同 ⇒ 必须分开（否则调用点字节不同）"""
    rb = infer_signature(E(addr='0x0', name='rbool', disasm=RW3_RBOOL))
    rc = infer_signature(E(addr='0x16', name='rchar', disasm=RW3_RCHAR))
    assert (rb.return_kind, rb.grade) == (RET_BOOL, GRADE_A), rb
    assert (rc.return_kind, rc.grade) == (RET_I8, GRADE_A), rc
    assert rb.return_kind != rc.return_kind, (rb, rc)
    assert rb.signature.startswith('bool '), rb.signature


def test_i64_return_from_sign_extend():
    """`__int64 f(int)`：`mov 0x8(%ebp),%eax; cltd` ⇒ edx:eax ⇒ 返回宽度 i64
    （若只看 32 位 eax 会误判 int）"""
    c = infer_signature(E(addr='0x26', name='r64', disasm=RW3_R64))
    assert c.return_kind == RET_I64, c
    assert c.arity == 1, c
    assert c.grade == GRADE_A, (c.grade, c.notes)
    assert c.signature.startswith('__int64 '), c.signature


# ==========================================================================
# 13. Ruling 6 阴性：不得把"指针参数 + 大范围写"误判成 sret
# ==========================================================================

def test_sret_ambiguous_is_flagged_not_deducted():
    """rw4 `?retp@Rn2@@UAEHPAUInner@@@Z`：返回 int、经 3 个**不同**基址寄存器写 12 字节
    ⇒ 与真 sret 只差"基址寄存器个数" ⇒ 必须**不扣除**、标 sret_ambiguous、降级 B"""
    c = infer_signature(E(addr='0x0', name='retp', disasm=RW4_RETP))
    assert FEATURE_SRET not in c.features, c.features
    assert FEATURE_SRET_AMBIGUOUS in c.features, c.features
    assert c.arity == 1, c
    assert c.hidden_param_suspicion is True, c
    assert FEATURE_HIDDEN_PARAM_SUSPICION in c.features, c.features
    assert c.grade == GRADE_B, (c.grade, c.notes)


def test_sret_negative_small_pointer_write_stays_grade_a():
    """rw4 `?retp2@Rn2@@UAEHPAH@Z`：只写 4 字节 ⇒ 不是 sret，也不含糊 ⇒ A 级"""
    c = infer_signature(E(addr='0x2d', name='retp2', disasm=RW4_RETP2))
    assert FEATURE_SRET not in c.features and FEATURE_SRET_AMBIGUOUS not in c.features, c.features
    assert (c.convention, c.arity, c.return_kind) == (CC_THISCALL, 1, RET_I32), c
    assert c.grade == GRADE_A, (c.grade, c.notes)


def test_sret_negative_void_pointer_param():
    """rw4 `?wr@Rn2@@UAEXPAUInner@@@Z`：void 返回、写 12 字节 ⇒ 不是 sret"""
    c = infer_signature(E(addr='0x46', name='wr', disasm=RW4_WR))
    assert FEATURE_SRET not in c.features and FEATURE_SRET_AMBIGUOUS not in c.features, c.features
    assert c.arity == 1, c
    assert c.return_kind == RET_UNKNOWN, c


def test_sret_confirmed_including_zero_arg_form():
    """rw4 真 sret：`?mk@(1 实参)` / `?mk0@(0 实参)` / `?mk0b@(0 实参, 16B)`
    —— 单基址寄存器连续写 ⇒ 扣除隐藏首参（arity 各为 1/0/0）"""
    mk = infer_signature(E(addr='0x70', name='mk', disasm=RW4_MK))
    mk0 = infer_signature(E(addr='0xaa', name='mk0', disasm=RW4_MK0))
    mk0b = infer_signature(E(addr='0xe5', name='mk0b', disasm=RW4_MK0B))
    for c, want in ((mk, 1), (mk0, 0), (mk0b, 0)):
        assert FEATURE_SRET in c.features, c.features
        assert c.return_kind == RET_SRET, c
        assert c.arity == want, (c.name, c.arity)
        assert c.grade == GRADE_A, (c.name, c.grade, c.notes)


# ==========================================================================
# 14. 真实项目开关 /O2 /Oy（无帧指针、无 prologue）：esp 跟踪 + ecx 基址证据
# ==========================================================================

def test_optimized_thiscall_ecx_base_without_spill_is_detected():
    """opt1 `?zero@Op@@UAEXH@Z`：/O2 下 this **不溢出**，只有 `0x4(%ecx)` 成员写
    ⇒ ecx 作内存基址就是 thiscall 证据（否则会误判约定）"""
    c = infer_signature(E(addr='0x0', name='zero', disasm=OPT1_ZERO))
    assert c.convention == CC_THISCALL, c
    assert FEATURE_ECX_THIS in c.features, c.features
    assert c.arity == 1, c
    assert FEATURE_NO_PROLOGUE in c.features, c.features
    assert c.read_slots == 0 and c.grade == GRADE_B, c   # 读集 ∅ ⇒ 隐藏参数嫌疑


def test_optimized_esp_relative_param_and_return_width():
    """opt1 `?add1@Op@@UAEHH@Z`：无帧指针、栈参在 `[esp+4]`（esp 跟踪）⇒ arity 1 + 返回 i32；
    无 ecx 证据 ⇒ 约定只是**推定** ⇒ 降级 B"""
    c = infer_signature(E(addr='0x0', name='add1', disasm=OPT1_ADD1))
    assert c.convention == CC_THISCALL, c
    assert c.arity == 1, c
    assert c.return_kind == RET_I32, c
    assert c.cc_provisional is True, c
    assert c.grade == GRADE_B, (c.grade, c.notes)


def test_optimized_stdcall_vs_cdecl_distinguished_by_ret_n():
    """opt2：`__stdcall` 成员（`ret 8`）与 `__cdecl` 成员（裸 `ret`）**同形只差清栈方**
    ⇒ 必须分别判 stdcall（arity = N/4 − this）与 cdecl（下界）"""
    sd = infer_signature(E(addr='0x0', name='sd', disasm=OPT2_SD))
    cd = infer_signature(E(addr='0x0', name='cd', disasm=OPT2_CD))
    assert sd.convention == CC_STDCALL and sd.arity == 1, sd
    assert sd.this_on_stack is True, sd
    assert cd.convention == CC_CDECL and cd.arity == 1, cd
    assert cd.arity_is_lower_bound is True, cd


def test_optimized_fastcall_detected_from_edx_source_use():
    """opt2 `?fe@Os@@UAIXH@Z`：/O2 不溢出 edx，但 `mov %edx,0x4(%ecx)`（edx 作源、未先写）
    就是 fastcall 证据；裸 ret ⇒ 0 栈参 ⇒ arity 1（不是 0）"""
    c = infer_signature(E(addr='0x0', name='fe', disasm=OPT2_FE))
    assert c.convention == CC_FASTCALL, c
    assert FEATURE_EDX_REG_ARG in c.features, c.features
    assert c.arity == 1 and c.stack_slots == 0, c


def test_optimized_fastcall_blind_spot_is_flagged_not_hidden():
    """opt2 `?fu@Os@@UAIXH@Z`（fastcall 成员、实参未用）：与 thiscall 0 参**逐字节同形**
    ⇒ 不得静默给"0 参确定"：必须标 real_param_blind_spot + arity 下界"""
    c = infer_signature(E(addr='0x0', name='fu', disasm=OPT2_FU))
    assert c.convention == CC_THISCALL, c
    assert c.arity == 0, c
    assert FEATURE_REAL_PARAM_BLIND_SPOT in c.features, c.features
    assert c.arity_is_lower_bound is True, c
    assert c.grade == GRADE_B, (c.grade, c.notes)


def test_broken_esp_tracking_yields_grade_c():
    """esp 跟踪中断（`and $0xf0,%esp` 对齐后基址未知）⇒ 不得用 ret N 反推参数个数：
    必须 C 级 + stack_base_unknown 痕迹（否则会把 this/局部当实参）"""
    c = infer_signature(E(addr='0x0', name='aligned', disasm=BROKEN_ESP))
    assert FEATURE_STACK_BASE_UNKNOWN in c.features, c.features
    assert c.arity is None, c
    assert c.grade == GRADE_C, (c.grade, c.notes)
    assert 'stack_base_unknown' in notes_of(c), c.notes


def test_optimized_thiscall_two_params_from_esp_reads():
    """opt2 `?t2@Os@@UAEHHH@Z`：读序倒置（先读第 2 个）也不影响按槽号归位 ⇒ arity 2"""
    c = infer_signature(E(addr='0x0', name='t2', disasm=OPT2_T2))
    assert c.convention == CC_THISCALL, c
    assert c.arity == 2, c
    assert c.read_slots == 2, c
    assert c.return_kind == RET_I32, c




# ==========================================================================
# 15. Task 2 解析器的 PE-COFF 重定位行缺口 —— **根因已修**（Task 2 R=2，2026-09-25）
# ==========================================================================
#
# 本节原为"发现项留证"：`dir32 $SG263`/`DISP32 ?sym` 让 Task 2 `parse_disasm_report`
# 抛 `ValueError`。Task 2 R=2 已把该形态收进 `_RELOC_LINE`（PE-COFF howto 名家族）⇒ 原始
# 文本直接可解析。此处**必须翻转**断言的用例，否则会把已修复的缺陷固化下来。
#
# 后果（记录，不修本工具）：`_PE_RELOC_LINE` 能 sanitize 的行集合是 Task 2 `_RELOC_LINE` 的
# **子集**（`R_386_`/`R_IA64_`/`R_X86_64_` ⊆ `R_*`；DISP32/dir32/off32 大小写不敏感重复覆盖）
# ⇒ 不再存在"Task 2 抛异常、Task 3 能 sanitize 掉"的行 ⇒ `FEATURE_PARSER_ERROR` 分支对本节
# 输入成为**不可达的纵深防御**（保留，覆盖不到；见 Task 2 R=2 报告"顾虑"）。

def test_task2_parser_no_longer_raises_on_pe_coff_dir32_reloc_line():
    """**发现项已闭合**（原断言 `assertRaises(ValueError)` 已翻转）：PE-COFF 重定位注释行
    被 Task 2 正确跳过 —— 6 条真指令、0 行丢弃、2 行有意跳过。"""
    rep = parse_disasm_report(PE_RELOC_TEXT)
    assert [i.mnem for i in rep.insns] == ['push', 'push', 'lea', 'push', 'call', 'add'], rep.insns
    assert rep.skipped_lines == 3, rep          # 首行空行 + 2 行重定位注释
    assert rep.dropped_lines == 0, rep.dropped_examples


def test_pe_coff_reloc_lines_are_sanitized_without_semantic_change():
    """剥离重定位注释行**不改指令语义**（只丢注释行）"""
    clean, n = sanitize_pe_relocs(PE_RELOC_TEXT)
    assert n == 2, n
    manual = '\n'.join(l for l in PE_RELOC_TEXT.splitlines()
                       if 'dir32' not in l and 'DISP32' not in l)
    assert body_key(clean) == body_key(manual)
    assert len(body_key(clean)) == 6, body_key(clean)      # 6 条真指令（push/push/lea/push/call/add）


def test_infer_accepts_pe_coff_reloc_text_without_parser_error():
    """喂含 PE-COFF 重定位行的**原始**文本：根因修复后不再触发 `parser_error` 防御；
    原材料与 `sanitize_pe_relocs` 后结论**逐字相同**（sanitize 成为冗余的纵深防御）。
    片段不是函数本体 ⇒ 仍必须给 C 级（证据不足），不得当"0 参 void"的安全默认。"""
    raw = infer_signature(E(addr='0x0', name='log_region', disasm=PE_RELOC_TEXT))
    clean, n = sanitize_pe_relocs(PE_RELOC_TEXT)
    san = infer_signature(E(addr='0x0', name='log_region', disasm=clean))
    assert n == 2, n
    assert raw is not None, raw
    assert FEATURE_PARSER_ERROR not in raw.features, raw.features
    assert 'parser_error' not in notes_of(raw), raw.notes
    assert (raw.grade, raw.arity, raw.convention, raw.return_kind, set(raw.features)) == \
           (san.grade, san.arity, san.convention, san.return_kind, set(san.features)), (raw, san)
    assert raw.grade == GRADE_C, (raw.grade, raw.notes)


def test_infer_address_record_survives_pe_coff_reloc_text():
    """ICF/一地址多候选路径也必须免疫（body_key 同样走安全解析）"""
    rec = infer_address_record('0x0', [E(addr='0x0', disasm=PE_RELOC_TEXT),
                                       E(addr='0x0', disasm=PE_RELOC_TEXT)])
    assert rec.icf_folded is True, rec
    assert len(rec.candidates) == 2, rec


# ==========================================================================
# 13. 修复轮 R=1（评审：Critical C1 + Important I2/I3/I4/I5）
# ==========================================================================

# ---- C1：deref 形态的**两种真值逐字节相同**（真机 /O2 /Ob2 /Oi /Ot /Oy /GR） ----
# 复现（探针源见下，未入库；与既有 probe 同法）：
#   tools/wine_cl.sh /c /O2 /Ob2 /Oi /Ot /Oy /GR \
#       /Itools/compilers/msvc6.0/Include /Fo/tmp/deref_form.obj deref_form.cpp
#   objdump -dr /tmp/deref_form.obj
#
#   struct InnerV { int a; int b; int c; int d; };       // 无 vptr ⇒ b@+4, d@+0xc
#   struct Rn6 { virtual int wr2(InnerV* p); };          // 真值 __thiscall / 1 指针参 / int
#   int Rn6::wr2(InnerV* p) { p->b = 1; p->d = 3; return 0; }
#   struct C { int p0; int p1; int p2; virtual int __stdcall g(); };  // 含 vptr ⇒ p0@+4, p2@+0xc
#   int __stdcall C::g() { this->p0 = 1; this->p2 = 3; return 0; }    // 真值 __stdcall 成员 / 0 参
#
# 两者**逐字节相同**（`8b 44 24 04 / c7 40 04 01… / c7 40 0c 03… / 33 c0 / c2 04 00`）：
#   ?wr2@Rn6@@UAEHPAUInnerV@@@Z      ?g@C@@UAGHXZ
C1_R1_DEREF_SAME_BYTES = """
  0:  8b 44 24 04           mov    0x4(%esp),%eax
  4:  c7 40 04 01 00 00 00  movl   $0x1,0x4(%eax)
  b:  c7 40 0c 03 00 00 00  movl   $0x3,0xc(%eax)
 12:  33 c0                 xor    %eax,%eax
 14:  c2 04 00              ret    $0x4
"""

# ---- I2：store-through **不连续**（单基址但相对首址有窟窿）不得判 sret ----
# 复现（真机 /Od /GR）：
#   struct RnA { virtual int poff(int* p); };            // 真值 __thiscall / 1 指针参 / int
#   int RnA::poff(int* p) { p[3] = 3; return (int)p; }   // 只写 +0xc
# objdump -dr：单基址 eax，covered={0xc..0xf} ⇒ `max(covered)=15 ≥ 8` 但**不连续**
C1_R1_POFF_GAP = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 45 08              mov    0x8(%ebp),%eax
  a:  c7 40 0c 03 00 00 00  movl   $0x3,0xc(%eax)
 11:  8b 45 08              mov    0x8(%ebp),%eax
 14:  8b e5                 mov    %ebp,%esp
 16:  5d                    pop    %ebp
 17:  c2 04 00              ret    $0x4
"""

# ---- I3：COMDAT 切片混入数据行 ⇒ 丢弃 >50% 非空行（解析不完整） ----
C1_R1_PARTIALLY_PARSED = RW1_RI + '\n'.join(
    '@@@ junk %d' % i for i in range(1, 11)) + '\n'

# ---- I2 阴性对照：连续性判据**不得**误杀"带填充的真 sret" ----
# 复现（真机 /Od /GR）：struct Pad16 { char c; double d; };  // sizeof 16（1..7 填充）
#   struct Rn11 { virtual Pad16 mkp(); virtual int pwrite(Pad16* q); };
#   Pad16 Rn11::mkp() { Pad16 p; p.c='a'; p.d=1.5; return p; }
#   int Rn11::pwrite(Pad16* q) { q->d = 2.5; return 0; }
# MSVC 6 /Od 连**填充一起复制**（4×dword）⇒ covered={0..15} 连续 ⇒ 必须仍判 sret；
# 而 `pwrite` 只写 +0x8/+0xc（单基址 eax，max=15）⇒ 不得判 sret（旧实现误判）。
C1_R1_PAD_SRET = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  83 ec 14              sub    $0x14,%esp
  6:  89 4d ec              mov    %ecx,-0x14(%ebp)
  9:  c6 45 f0 61           movb   $0x61,-0x10(%ebp)
  d:  c7 45 f8 00 00 00 00  movl   $0x0,-0x8(%ebp)
 14:  c7 45 fc 00 00 f8 3f  movl   $0x3ff80000,-0x4(%ebp)
 1b:  8b 45 08              mov    0x8(%ebp),%eax
 1e:  8b 4d f0              mov    -0x10(%ebp),%ecx
 21:  89 08                 mov    %ecx,(%eax)
 23:  8b 55 f4              mov    -0xc(%ebp),%edx
 26:  89 50 04              mov    %edx,0x4(%eax)
 29:  8b 4d f8              mov    -0x8(%ebp),%ecx
 2c:  89 48 08              mov    %ecx,0x8(%eax)
 2f:  8b 55 fc              mov    -0x4(%ebp),%edx
 32:  89 50 0c              mov    %edx,0xc(%eax)
 35:  8b 45 08              mov    0x8(%ebp),%eax
 38:  8b e5                 mov    %ebp,%esp
 3a:  5d                    pop    %ebp
 3b:  c2 04 00              ret    $0x4
"""

C1_R1_PWRITE_NOT_SRET = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 45 08              mov    0x8(%ebp),%eax
  a:  c7 40 08 00 00 00 00  movl   $0x0,0x8(%eax)
 11:  c7 40 0c 00 00 04 40  movl   $0x40040000,0xc(%eax)
 18:  33 c0                 xor    %eax,%eax
 1a:  8b e5                 mov    %ebp,%esp
 1c:  5d                    pop    %ebp
 1d:  c2 04 00              ret    $0x4
"""

# ---- R=2：I2 的"连续性"判据不得让「多基址 + >8B + **不连续**」这条安全网**不可达** ----
# 复现（真机 /Od /GR，临时探针；与本目录 RW4_WR `?wr@Rn2@@UAEXPAUInner@@@Z` 同形，
# 只把第 2 次写从 +0x4 挪到 +0x8 造出窟窿）：
#   struct InnerV { int a; int b; int c; int d; };
#   struct Rn7 { virtual int mwp(InnerV* p); };
#   int Rn7::mwp(InnerV* p) { p->a = 1; p->c = 2; return (int)p; }
#   tools/wine_cl.sh /c /Od /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/rw7.obj /tmp/rw7.cpp
# objdump -dr：**多基址**（eax/ecx）+ covered={0..3}∪{8..0xb}（max=11 ≥ 8 但**不连续**）。
# 形态既不是真 sret（连续复制）也不是单基址散写（`?poff`）⇒ 与 `?retp` 同属"判不出"，
# 必须留 `sret_ambiguous` 痕迹并降级（R=1 的 I2 修复让这条安全网**不可达** ⇒ 退化成 A、无痕迹）
C1_R2_MULTI_BASE_GAP = """
   0:  55                    push   %ebp
   1:  8b ec                 mov    %esp,%ebp
   3:  51                    push   %ecx
   4:  89 4d fc              mov    %ecx,-0x4(%ebp)
   7:  8b 45 08              mov    0x8(%ebp),%eax
   a:  c7 00 01 00 00 00     movl   $0x1,(%eax)
  10:  8b 4d 08              mov    0x8(%ebp),%ecx
  13:  c7 41 08 02 00 00 00  movl   $0x2,0x8(%ecx)
  1a:  8b 45 08              mov    0x8(%ebp),%eax
  1d:  8b e5                 mov    %ebp,%esp
  1f:  5d                    pop    %ebp
  20:  c2 04 00              ret    $0x4
"""

#: CLI 拒绝写入的真相源路径（测试专用探针名）；上一轮残留会伪装成"CLI 写了真相源"
TRUTH_SOURCE_FORBIDDEN = (PROJECT_ROOT / 'data' / 'annotations'
                          / '__r1_cli_must_never_write.json')


def _cli_refuses_truth_source_write(src):
    """走一遍 CLI「拒绝写 `data/annotations/**`」路径，并断言**不留文件**。

    R=2 测试卫生：清理必须在**调用前** —— 上一轮残留的
    `data/annotations/__r1_cli_must_never_write.json` 会让
    `assert not forbidden.exists()` **假失败**（实测 65 passed / 1 failed）；
    而清理若只放在断言**前**，断言就是空的（清理会把 CLI 真写的文件一起删掉）。
    """
    import io
    from contextlib import redirect_stdout

    forbidden = TRUTH_SOURCE_FORBIDDEN
    forbidden.parent.mkdir(parents=True, exist_ok=True)
    if forbidden.exists():
        forbidden.unlink()
    try:
        with redirect_stdout(io.StringIO()):
            cli_main(['--slots', src, '--out', str(forbidden)])
    except SystemExit as e:
        assert 'data' in str(e) and 'annotations' in str(e), e
    else:
        raise AssertionError('必须拒绝写 data/annotations（真相源）')
    assert not forbidden.exists(), forbidden


def test_fix_r1_c1_deref_branch_without_symbol_is_provisional_not_grade_a():
    """🔴 C1：deref 只证明"首槽是**指针对象基址**"，不能定 this 归属
    ⇒ 无 mangling 旁证时必须 `cc_provisional=True` 且**不得给 A 级**（旧实现给 A）"""
    cand = infer_signature(E(addr='0x0', name='x', disasm=C1_R1_DEREF_SAME_BYTES))
    assert cand.cc_provisional is True, cand
    assert cand.grade != GRADE_A, cand
    assert cand.grade == GRADE_B, cand
    assert FEATURE_SLOT0_DEREF in cand.features, cand.features
    assert 'cc_provisional' in notes_of(cand), cand.notes


def test_fix_r1_c1_identical_bodies_two_truths_mangling_disambiguates():
    """🔴 C1：同一段字节的两种真值 —— mangling 虚成员前缀可判开
    （`UAE`=__thiscall ⇒ 首槽是**指针参数**；`UAG`=__stdcall 成员 ⇒ 首槽是 this）"""
    wr2 = infer_signature(E(addr='0x0', name='wr2',
                            symbol='?wr2@Rn6@@UAEHPAUInnerV@@@Z',
                            disasm=C1_R1_DEREF_SAME_BYTES))
    g = infer_signature(E(addr='0x0', name='g', symbol='?g@C@@UAGHXZ',
                          disasm=C1_R1_DEREF_SAME_BYTES))
    # 前提：两条证据的字节完全相同（body_key 是唯一体判据）
    assert body_key(C1_R1_DEREF_SAME_BYTES) == body_key(C1_R1_DEREF_SAME_BYTES)
    assert wr2 is not None and g is not None
    assert (wr2.convention, wr2.arity, wr2.this_on_stack) == (CC_THISCALL, 1, False), wr2
    assert (g.convention, g.arity, g.this_on_stack) == (CC_STDCALL, 0, True), g
    assert wr2.cc_provisional is False and g.cc_provisional is False, (wr2, g)
    assert wr2.grade == GRADE_A and g.grade == GRADE_A, (wr2, g)
    assert FEATURE_CC_FROM_MANGLING in wr2.features, wr2.features
    assert FEATURE_CC_FROM_MANGLING in g.features, g.features
    assert 'cc_from_mangling' in notes_of(wr2), wr2.notes
    # 旧实现把两者输出成同一个 `int __stdcall <name>()`/arity 0 —— 至少真值必须分开
    assert wr2.signature != g.signature, (wr2.signature, g.signature)


def test_fix_r1_c1_static_mangling_return_codes_are_not_read_as_conventions():
    """C1 旁证解码器：**静态**成员的第三个字符是返回类型码
    （`E`=unsigned char / `G`=unsigned short / `I`=unsigned int）⇒ 不得误读成约定
    （真机 mangle.cpp / mangle2.cpp：`?sf_i@N@@SAIXZ` 是 static unsigned int()，非 fastcall）"""
    assert convention_from_symbol('?v_cdecl@M@@UAEXXZ') == CC_THISCALL
    assert convention_from_symbol('?v_std@M@@UAGHH@Z') == CC_STDCALL
    assert convention_from_symbol('?v_fast@M@@UAIHH@Z') == CC_FASTCALL
    assert convention_from_symbol('?v_cd@M@@UAAHH@Z') == CC_CDECL
    assert convention_from_symbol('?nv_plain@M@@QAEXXZ') == CC_THISCALL
    assert convention_from_symbol('?pv@P@@MAEXXZ') == CC_THISCALL
    assert convention_from_symbol('?priv@Q@@AAEXXZ') == CC_THISCALL
    for static_sym in ('?sf_i@N@@SAIXZ', '?sf_c@N@@SAEXZ', '?sf_s@N@@SAGXZ',
                       '?st_std@M@@SGHH@Z', '?st_plain@M@@SAXXZ'):
        assert convention_from_symbol(static_sym) is None, static_sym
    assert convention_from_symbol('??_GV@@UAEPAXI@Z') is None
    assert convention_from_symbol('?o@E@@UAEXH@Z') == CC_THISCALL
    assert convention_from_symbol('') is None
    assert convention_from_symbol(None) is None


def test_fix_r1_i2_sret_requires_contiguous_store_through():
    """🟡 I2：单基址 + `max(covered) >= 8` 不足 —— 必须是**相对首址连续**的 ≥9 字节写
    （`?poff@RnA@@UAEHPAH@Z` 真机 /Od：只写 +0xc ⇒ 旧实现误扣隐藏首参 ⇒ arity 0）"""
    cand = infer_signature(E(addr='0x0', name='poff', symbol='?poff@RnA@@UAEHPAH@Z',
                             disasm=C1_R1_POFF_GAP))
    assert FEATURE_SRET not in cand.features, cand.features
    assert FEATURE_SRET_AMBIGUOUS not in cand.features, cand.features
    assert cand.return_kind != RET_SRET, cand
    assert cand.arity == 1, cand
    assert cand.convention == CC_THISCALL, cand
    # 阴性对照仍在：真 sret（连续 store-through）不得被这次收紧误杀
    mk0 = infer_signature(E(addr='0x0', name='mk0', disasm=RW4_MK0))
    assert FEATURE_SRET in mk0.features and mk0.arity == 0, mk0
    # 带**填充**的真 sret（新探针，真机 /Od）：MSVC 连填充一起复制 ⇒ covered 连续
    # ⇒ 收紧后必须仍判 sret（否则把真 sret 误杀成 arity 偏大 1 的 A 级）
    pad = infer_signature(E(addr='0x0', name='mkp', symbol='?mkp@Rn11@@UAE?AUPad16@@XZ',
                            disasm=C1_R1_PAD_SRET))
    assert FEATURE_SRET in pad.features, pad.features
    assert (pad.return_kind, pad.arity, pad.grade) == (RET_SRET, 0, GRADE_A), pad
    # 同一 TU 的单基址散写（`q->d = 2.5` 只写 +0x8/+0xc，max=15）⇒ 也不得判 sret
    pw = infer_signature(E(addr='0x0', name='pwrite', symbol='?pwrite@Rn11@@UAEHPAUPad16@@@Z',
                           disasm=C1_R1_PWRITE_NOT_SRET))
    assert FEATURE_SRET not in pw.features, pw.features
    assert (pw.return_kind, pw.arity) == (RET_I32, 1), pw


def test_fix_r1_i3_partially_parsed_forces_downgrade():
    """🟡 I3：丢弃 >50% 非空行（解析不完整）时 notes 说"不可信"却仍给 A
    ⇒ 必须至少降级 B（同一字节在完整文本下就是 A，证明降级来自解析不完整）"""
    rep = parse_disasm_report(C1_R1_PARTIALLY_PARSED)
    assert rep.partially_parsed is True, (rep.content_lines, rep.dropped_lines)
    full = infer_signature(E(addr='0x0', name='ri', disasm=RW1_RI))
    partial = infer_signature(E(addr='0x0', name='ri', disasm=C1_R1_PARTIALLY_PARSED))
    assert full.grade == GRADE_A, full
    assert partial.grade != GRADE_A, partial
    assert partial.grade == GRADE_B, partial
    assert 'partially_parsed' in notes_of(partial), partial.notes


def test_fix_r1_i4_multi_candidate_different_bodies_are_capped_to_b():
    """🟡 I4：一地址多候选**体不同**（非 ICF）时 `ambiguous=True` 却仍可给 A
    ⇒ 只要有多个候选就必须 cap（旧实现只在 `distinct_bodies==1` 时 cap）"""
    rec = infer_address_record('0x0', [E(addr='0x0', symbol='?ri@Rn@@UAEHH@Z', disasm=RW1_RI),
                                       E(addr='0x0', symbol='?rc@Rn@@UAEDH@Z', disasm=RW1_RC)])
    assert rec.icf_folded is False, rec
    assert rec.ambiguous is True, rec
    assert [c.symbol for c in rec.candidates] == sorted(['?ri@Rn@@UAEHH@Z',
                                                         '?rc@Rn@@UAEDH@Z']), rec.candidates
    assert all(c.grade != GRADE_A for c in rec.candidates), rec.candidates
    assert all(c.grade == GRADE_B for c in rec.candidates), rec.candidates
    assert all('grade_capped' in notes_of(c) for c in rec.candidates), rec.candidates
    assert any('multi_candidate' in n for n in rec.notes), rec.notes
    # 单候选地址不受影响（RW1_RI 本身是 A）
    solo = infer_address_record('0x0', [E(addr='0x0', symbol='?ri@Rn@@UAEHH@Z', disasm=RW1_RI)])
    assert solo.candidates[0].grade == GRADE_A, solo


def test_fix_r1_i5_iter_candidates_is_the_task5_traversal_face():
    """🟡 I5：`iter_candidates` 是 Task 5 的稳定遍历面（此前 0 测试）——
    yield (addr, candidate_dict)、跳过无候选的合成槽、接受整 struct 或裸 pending"""
    recs = [infer_address_record('0x0', [E(addr='0x0', name='unused', disasm=C1_UNUSED)]),
            infer_address_record('0x401000', [E(addr='0x401000', name='ri', disasm=RW1_RI)]),
            infer_address_record('0x402000', [E(addr='0x402000', disasm=ADJ_STATIC_FF)])]
    out = build_methods_pending({'name': 'S', 'methods': {}}, recs)
    assert sorted(out['methods_pending']) == ['0x00000000', '0x00401000', '0x00402000']
    pairs = list(iter_candidates(out))
    assert [a for a, _ in pairs] == ['0x00000000', '0x00401000'], pairs
    assert pairs == [(a, out['methods_pending'][a]['candidates'][0])
                     for a in ('0x00000000', '0x00401000')], pairs
    assert list(iter_candidates(out['methods_pending'])) == pairs      # 裸 pending 亦可
    assert list(iter_candidates({})) == [] and list(iter_candidates(None)) == []
    # 一地址多候选 ⇒ 每个候选各一行（Task 5 不得假设"一地址一候选"）
    multi = build_methods_pending({'methods': {}}, [infer_address_record(
        '0x0', [E(addr='0x0', symbol='?o@E@@UAEXH@Z', disasm=C5_O_INT),
                E(addr='0x0', symbol='?o@E@@UAEXPAX@Z', disasm=C5_O_INT)])])
    assert len(list(iter_candidates(multi))) == 2


def test_fix_r1_i5_cli_only_writes_bypass_and_refuses_truth_source():
    """🟡 I5：CLI 此前 0 测试 —— stdout/`--out` 只产出旁路（`methods` 逐字不动），
    且**拒绝**写 `data/annotations/**`（真相源）"""
    import io
    import json
    import os
    import tempfile
    from contextlib import redirect_stdout

    slots = {'slots': [
        {'addr': '0x4C5D50', 'name': 'unused', 'symbol': '?unused@S@@UAEXHH@Z',
         'disasm': C1_UNUSED},
        {'addr': '0x4C5D60', 'name': 'o', 'symbol': '?o@E@@UAEXH@Z', 'disasm': C5_O_INT},
        {'addr': '0x4C5D60', 'name': 'o2', 'symbol': '?o@E@@UAEXPAX@Z', 'disasm': C5_O_INT},
    ]}
    with tempfile.TemporaryDirectory() as d:
        src = os.path.join(d, 'slots.json')
        with open(src, 'w', encoding='utf-8') as fh:
            json.dump(slots, fh)

        buf = io.StringIO()
        with redirect_stdout(buf):
            rc = cli_main(['--slots', src])
        assert rc == 0, rc
        data = json.loads(buf.getvalue())
        assert data['methods'] == {}, data['methods']
        assert sorted(data['methods_pending']) == ['0x004C5D50', '0x004C5D60']
        assert len(data['methods_pending']['0x004C5D60']['candidates']) == 2
        assert data['methods_pending']['0x004C5D60']['icf_folded'] is True

        out_path = os.path.join(d, 'pending.json')
        summary = io.StringIO()
        with redirect_stdout(summary):
            rc = cli_main(['--slots', src, '--out', out_path])
        assert rc == 0, rc
        assert summary.getvalue().startswith('[vtable_sig_infer] 2 地址 / 3 候选 → '), \
            summary.getvalue()
        with open(out_path, encoding='utf-8') as fh:
            written = json.load(fh)
        assert written == data, (written, data)

        # 未知参数 ⇒ 报错退出（不静默忽略）
        try:
            with redirect_stdout(io.StringIO()):
                cli_main(['--slots', src, '--bogus'])
        except SystemExit as e:
            assert '未知参数' in str(e), e
        else:
            raise AssertionError('未知参数必须 SystemExit')

        # 拒绝写真相源目录（且**不得**留下文件）
        # R=2 测试卫生：改走 `_cli_refuses_truth_source_write`（清理在**调用前**）——
        # 残留文件会让 `assert not forbidden.exists()` 假失败（实测 65 passed / 1 failed）
        _cli_refuses_truth_source_write(src)


def test_fix_r2_sret_ambiguous_survives_non_contiguous_multi_base():
    """🔴 R=2：I2 的连续性判据使「多基址 + >8B + **不连续**」这条安全网**不可达**
    ⇒ 同一输入从"B + `sret_ambiguous` 痕迹"退化成"**A + 无痕迹**"（实测
    `int __thiscall mwp(?)` / A / {ecx_this, slot0_deref, ambiguous_param_class}），
    违反 A 级契约（A = 约定 + 个数 + 返回宽度全确定，无隐藏参数嫌疑）——
    Task 5 的 grade 棘轮会把这条错误结论当"确定"消费。"""
    cand = infer_signature(E(addr='0x0', name='mwp', symbol='?mwp@Rn7@@UAEHPAUInnerV@@@Z',
                             disasm=C1_R2_MULTI_BASE_GAP))
    assert FEATURE_SRET not in cand.features, cand.features        # 不扣除（不猜）
    assert FEATURE_SRET_AMBIGUOUS in cand.features, cand.features  # 但必须留痕
    assert FEATURE_HIDDEN_PARAM_SUSPICION in cand.features, cand.features
    assert cand.grade == GRADE_B, cand
    assert cand.return_kind != RET_SRET, cand
    assert any('sret_ambiguous' in n for n in cand.notes), cand.notes
    # 阳性对照：真 sret（单基址**连续**复制，Ruling 6）不受这条安全网影响
    mk0 = infer_signature(E(addr='0x0', name='mk0', disasm=RW4_MK0))
    assert (FEATURE_SRET in mk0.features, FEATURE_SRET_AMBIGUOUS not in mk0.features,
            mk0.arity) == (True, True, 0), mk0
    # 阴性对照：**单**基址散写（`?poff` 只写 +0xc）不得被拉成 B ⇒ 仍 A
    poff = infer_signature(E(addr='0x0', name='poff', symbol='?poff@RnA@@UAEHPAH@Z',
                             disasm=C1_R1_POFF_GAP))
    assert FEATURE_SRET_AMBIGUOUS not in poff.features, poff.features
    assert FEATURE_HIDDEN_PARAM_SUSPICION not in poff.features, poff.features
    assert (poff.grade, poff.arity) == (GRADE_A, 1), poff


def test_fix_r2_truth_source_refusal_is_immune_to_residue():
    """🟡 R=2 测试卫生：拒绝写真相源的断言必须对**残留文件**免疫 ——
    实测残留 `data/annotations/__r1_cli_must_never_write.json`（上一轮遗留）会让
    `assert not forbidden.exists()` **假失败**（65 passed / 1 failed）。
    本测试**主动制造残留**：若清理缺失或只放在断言前（空断言），本测试即红。"""
    import json
    import os
    import tempfile

    forbidden = TRUTH_SOURCE_FORBIDDEN
    forbidden.parent.mkdir(parents=True, exist_ok=True)
    forbidden.write_text('{"residue": "上一轮遗留"}\n', encoding='utf-8')
    try:
        with tempfile.TemporaryDirectory() as d:
            src = os.path.join(d, 'slots.json')
            with open(src, 'w', encoding='utf-8') as fh:
                json.dump({'slots': []}, fh)
            _cli_refuses_truth_source_write(src)     # 内部：调用**前**清残留 + 拒绝 + 断言
    finally:
        if forbidden.exists():                       # 失败也不留污染
            forbidden.unlink()


if __name__ == '__main__':
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)