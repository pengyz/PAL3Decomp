#!/usr/bin/env python3
"""vtable **候选签名生成器** —— 只从**原始指令字节**（反汇编）推断，产出 methods_pending 旁路。

回答一个问题：**vtable 某槽指向的函数，其调用约定 / 参数个数 / 返回宽度是什么？**
产出**候选**（A/B/C 分级）+ 全部证据痕迹，**绝不写 methods 真相源**（设计 §1.1：
工具生成候选 → IDA 二进制证据定性 → 人工确认 → 写入真相源）。

## 证据源（唯一：原始指令字节）

    第 1 步 合成槽分类：交 Task 2 `vtable_slot_classifier.classify_slot`（**传原始文本**）
                       非 `fn`（adjustor/deleting_dtor/purecall/composite）⇒ **跳过**，不推断
    第 2 步 调用约定：ecx 入口 this 证据 / edx 入口寄存器实参证据 / ret N 与裸 ret
                       （deref 形态单凭字节不可判 ⇒ 仅此时用 `symbol` 的 mangling
                        成员前缀作旁证判开；无旁证则 B 级，见已知局限 6）
    第 3 步 参数个数：[ebp+8..]（或 esp 跟踪）读取集 = 下界；ret N = 栈槽数上界；
                       sret 隐藏首参扣除；double/int64 占双槽
    第 4 步 返回宽度：epilogue 前最后一次 eax/st(0) 物化（宽度可测才声称）
    第 5 步 输出候选：A/B/C + notes + features ⇒ methods_pending 旁路字段

**禁止** decomp JSON、禁止先 `parse_disasm` 再喂 Insn 元组（Ruling 1：痕迹会失效）。

## 控制器 Ruling（逐条实现 + 测试）

* **Ruling 1** 必须传原始 disasm 文本 ⇒ `SigEvidence.disasm` 非 `str` 直接 `TypeError`；
  内部一律 `parse_disasm_report(text)` + `classify_slot(SlotEvidence(instructions=text))`
* **Ruling 2** 消费 `fn` 必查 notes：输入非空但解析 0 条指令 ⇒ `insufficient_evidence`
  ⇒ **C 级 + 痕迹**（不得把 `fn` 当安全默认）
* **Ruling 3** `__fastcall`：首参在 edx/ecx（入口使用/溢出，**裸 ret** 亦可）⇒ 单独分支；
  fastcall 成员 = ecx:this + edx:首个实参（栈上的其余实参由 callee 清）
* **Ruling 4** `__cdecl` 成员的 `this` 在栈上（首个栈槽）⇒ 读集必须**扣除**再计参数个数
* **Ruling 5** BOOL **不**与 int 字节等价（调用点 `setcc` 物化 +5B）⇒ BOOL/char/short
  单独成类；`param_class_equiv('bool','i32') is False`
* **Ruling 6** sret（返回 >8B 结构的隐藏首参）必须扣除，否则参数整体错位；
  识别用"单基址寄存器**相对首址连续** ≥9 字节 store-through + epilogue 前最后一次 eax 载入该槽"；
  多基址寄存器 ⇒ 只标 `sret_ambiguous` + 降级（不猜）；覆盖**不连续**（相对首址有窟窿，
  如 `/Od ?poff` 只写 `+0xc`）⇒ 不是结构复制，**不判** sret（修复轮 R=1 / I2）

## 分级（spec §4.2 逐字）

| 级 | 条件 |
|---|---|
| **A** | 调用约定 + 参数个数 + **返回宽度**全部确定（无隐藏参数嫌疑 / 无 ICF / 无约定推定） |
| **B** | 缺返回宽度，或有隐藏参数嫌疑，或 ICF 折叠 / **同地址多候选**，或约定系推定（无正面寄存器证据），或解析不完整（`partially_parsed`） |
| **C** | 参数个数不确定（变参 / cdecl 读集为空 / 证据不足 / 栈基址不可定位） |

⚠️ **A 级不保证参数等价类**（`param_class_undetermined`）：callee 字节对 int/指针/float/
BOOL 常常不可分（C-5/C-6 实测）⇒ A 级只保证"约定 + 个数 + 返回宽度"。

## 已知局限（务必与 IDA 交叉验证）

1. **/O2 未使用的寄存器实参无痕**：`void __fastcall f(int x){ m = 0; }` 在 /O2 下与
   thiscall 0 参字节相同（probe `opt2.cpp` `?fu@Os@@UAIXH@Z`）⇒ arity 只能是下界，
   该形态会带 `real_param_blind_spot` 痕迹（C-2 缺陷在优化代码里的残余）。
2. **`ret N` = 栈槽数 ≠ 参数个数**：double/int64/结构按值占双槽（s3 `?two@SC@@UAEXHN@Z`
   `ret 0xc` 真值 2 参）⇒ 无 qword 证据时 arity 是槽数估计，带 `hidden_param_suspicion`。
3. f32/f64 返回宽度：`fildl`（整数→x87）形态不可分（rw2 `rf`/`rd` 同体）⇒ B 级 + 痕迹；
   仅 `flds/fldl/fsts/fstps/fstpl` 一类**带宽度**的 x87 访存可判。
4. 多返回路径函数只取**最后**一个 `ret` 的 N；尾部 `jmp` 尾调用形态不看。
5. `this` 归属：vtable 槽恒为成员函数（`is_member=True`），cdecl/fastcall 的 `this` 约定按
   ABI 扣除；若某槽实际是自由函数（非 vtable 场景）需显式 `is_member=False`。
6. **deref 形态的 this 归属单凭字节不可判**（修复轮 R=1 / C1）："首槽值被解引用"同时符合
   「__thiscall 的**首个指针参数**」与「__stdcall/__cdecl 成员的 this」。真机 `/O2 /Ob2 /Oi
   /Ot /Oy` 实测 `?wr2@Rn6@@UAEHPAUInnerV@@@Z`（真值 __thiscall / 1 指针参 / int）与
   `?g@C@@UAGHXZ`（真值 __stdcall 成员 / 0 参 / int）**逐字节相同**：
   `8b 44 24 04 / c7 40 04 01… / c7 40 0c 03… / 33 c0 / c2 04 00`。
   ⇒ 无 mangling 旁证时只给 `cc_provisional` + B；有 mangling 虚成员前缀
   （`convention_from_symbol`：`UAE`=__thiscall / `UAG`=__stdcall / `UAA`=__cdecl /
   `UAI`=__fastcall，且**排除** `S`=static 的返回类型码）时才能判开（标 `cc_from_mangling`）。
7. `convention_from_symbol` 只认实证形态的**成员**前缀；模板类（类名内含 `@`）、自由函数、
   析构（`??_G…`）、静态成员（`S`，第 3 字符是返回类型码）一律返回 `None`（不猜）。

用法：
    from vtable_sig_infer import SigEvidence, infer_signature, infer_address_record, \\
        build_methods_pending, find_icf_groups
    c = infer_signature(SigEvidence(addr='0x4C5D50', name='f', disasm=objdump_text))
    rec = infer_address_record('0x4C5D50', [ev1, ev2])       # 一地址多候选（ICF）
    pending = build_methods_pending(struct_json, [rec])      # methods 原样不动

CLI（只读输入 → 只写 --out 指定的旁路文件，**永不**写 data/annotations）：
    python3 tools/vtable_sig_infer.py --slots slots.json [--out pending.json]
    # slots.json: {"slots": [{"addr","name?","symbol?","disasm","call_sites?": [...]}]}
"""
import copy
import json
import os
import re
import sys
from dataclasses import dataclass, field, replace

_HERE = os.path.dirname(os.path.abspath(__file__))
if _HERE not in sys.path:
    sys.path.insert(0, _HERE)

from vtable_slot_classifier import (  # noqa: E402
    KIND_FN,
    SlotEvidence,
    classify_slot,
    parse_disasm_report,
)

__all__ = [
    'GRADE_A', 'GRADE_B', 'GRADE_C', 'GRADES',
    'CC_THISCALL', 'CC_CDECL', 'CC_FASTCALL', 'CC_STDCALL', 'CC_UNKNOWN',
    'RET_VOID', 'RET_I8', 'RET_I16', 'RET_I32', 'RET_I64', 'RET_F32', 'RET_F64',
    'RET_BOOL', 'RET_SRET', 'RET_UNKNOWN',
    'CLASS_I8', 'CLASS_I16', 'CLASS_I32', 'CLASS_I64', 'CLASS_F32', 'CLASS_F64',
    'CLASS_PTR', 'CLASS_BOOL', 'CLASS_STRUCT',
    'FEATURE_ECX_THIS', 'FEATURE_EDX_REG_ARG', 'FEATURE_THIS_ON_STACK', 'FEATURE_SRET',
    'FEATURE_VARIADIC', 'FEATURE_HIDDEN_PARAM_SUSPICION', 'FEATURE_ICF_FOLDED',
    'FEATURE_INSUFFICIENT_EVIDENCE', 'FEATURE_READ_SET_EMPTY',
    'FEATURE_AMBIGUOUS_PARAM_CLASS', 'FEATURE_QWORD_ARG', 'FEATURE_FP_WIDTH_AMBIGUOUS',
    'FEATURE_SKIPPED_SYNTHETIC_SLOT', 'FEATURE_CALL_SITE_MISMATCH',
    'FEATURE_RET_CONTRADICTION', 'FEATURE_STACK_BASE_UNKNOWN', 'FEATURE_NO_PROLOGUE',
    'FEATURE_REAL_PARAM_BLIND_SPOT', 'FEATURE_SRET_AMBIGUOUS', 'FEATURE_SLOT0_DEREF',
    'FEATURE_PARSER_ERROR', 'FEATURE_CC_FROM_MANGLING', 'sanitize_pe_relocs',
    'ParamCandidate', 'SigEvidence', 'SignatureCandidate', 'PendingRecord',
    'CallSiteEvidence',
    'infer_signature', 'infer_address_record', 'find_icf_groups', 'body_key',
    'build_methods_pending', 'iter_candidates', 'analyze_call_sites',
    'param_class_equiv', 'param_class_family', 'convention_from_symbol',
]

# ---------------- 分级 / 调用约定 / 返回宽度 ----------------

GRADE_A, GRADE_B, GRADE_C = 'A', 'B', 'C'
GRADES = (GRADE_A, GRADE_B, GRADE_C)

CC_THISCALL = '__thiscall'
CC_CDECL = '__cdecl'
CC_FASTCALL = '__fastcall'
CC_STDCALL = '__stdcall'
CC_UNKNOWN = 'unknown'

RET_VOID = 'void'
RET_I8 = 'i8'
RET_I16 = 'i16'
RET_I32 = 'i32'
RET_I64 = 'i64'
RET_F32 = 'f32'
RET_F64 = 'f64'
RET_BOOL = 'bool'
RET_SRET = 'sret(>8B)'
RET_UNKNOWN = 'unknown'

# ---------------- 参数等价类（BOOL/char/short 单独成类，Ruling 5） ----------------

CLASS_I8 = 'i8'
CLASS_I16 = 'i16'
CLASS_I32 = 'i32'
CLASS_I64 = 'i64'
CLASS_F32 = 'f32'
CLASS_F64 = 'f64'
CLASS_PTR = 'ptr'
CLASS_BOOL = 'bool'
CLASS_STRUCT = 'struct'

#: 一个**4 字节栈槽**里的读/写无法区分这些类（callee 侧字节同形）⇒ 不得断言单一类
DWORD_AMBIGUOUS = frozenset({CLASS_I8, CLASS_I16, CLASS_I32, CLASS_PTR, CLASS_BOOL, CLASS_F32})
#: 8 字节访问（qword）分不出 double 还是 __int64
QWORD_AMBIGUOUS = frozenset({CLASS_F64, CLASS_I64})

_CLASS_ALIAS = {
    'char': CLASS_I8, 'signedchar': CLASS_I8, 'unsignedchar': CLASS_I8, 'byte': CLASS_I8,
    '__int8': CLASS_I8, 'i8': CLASS_I8,
    'bool': CLASS_BOOL, '_bool': CLASS_BOOL,
    'short': CLASS_I16, 'unsignedshort': CLASS_I16, 'word': CLASS_I16, '__int16': CLASS_I16,
    'i16': CLASS_I16,
    'int': CLASS_I32, 'unsigned': CLASS_I32, 'long': CLASS_I32, 'unsignedlong': CLASS_I32,
    'dword': CLASS_I32, 'enum': CLASS_I32, 'i32': CLASS_I32,
    'ptr': CLASS_PTR, 'void*': CLASS_PTR, 'pointer': CLASS_PTR, 'reference': CLASS_PTR,
    'float': CLASS_F32, 'f32': CLASS_F32,
    'double': CLASS_F64, 'longdouble': CLASS_F64, 'f64': CLASS_F64,
    '__int64': CLASS_I64, 'i64': CLASS_I64, 'longlong': CLASS_I64,
    'struct': CLASS_STRUCT,
}
#: **字节等价**族（同族 ⇒ 交换声明在调用点/callee 都不改字节）
_FAMILY = {
    CLASS_I32: 'dword32', CLASS_PTR: 'dword32',
    CLASS_I8: 'i8', CLASS_I16: 'i16', CLASS_BOOL: 'bool',
    CLASS_F32: 'f32', CLASS_F64: 'f64', CLASS_I64: 'i64', CLASS_STRUCT: 'struct',
}


def param_class_family(cls):
    """参数类名 → **字节等价族**（未知名原样返回，保守：不当作等价）。"""
    c = (cls or '').replace(' ', '').lower()
    return _FAMILY.get(_CLASS_ALIAS.get(c, c), _CLASS_ALIAS.get(c, c))


def param_class_equiv(a, b):
    """两类是否**字节等价**（同族）。

    Ruling 5：`bool` 与 `i32` **不等价**（调用点 `setcc` 物化 +5B，b1.cpp 实测）；
    `char`/`short` 亦单独成类（窄化物化）。`i32`/`ptr` 字节等价（s1 `idi`/`idp` 同体实测）
    —— 但等价 ≠ 可断言类型（C-5：同一字节可对应多种签名）。
    """
    return param_class_family(a) == param_class_family(b)


# MSVC 成员函数 mangling：`?<name>@<Class>@@<access>A<conv><return><params>@Z`
#   `<conv>` 第 3 字符 = 调用约定（真机 MSVC 6.0 SP0 + objdump -t 实证）：
#     ?v_cdecl@M@@UAEXXZ 默认成员 __thiscall · ?v_std@M@@UAGHH@Z __stdcall
#     ?v_fast@M@@UAIHH@Z __fastcall      · ?v_cd@M@@UAAHH@Z  __cdecl
#     ?nv_plain@M@@QAEXXZ 非虚 public    · ?pv@P@@MAEXXZ protected virtual
#     ?priv@Q@@AAEXXZ private 非虚
#   `<access>` ∈ {Q,U,M,E,I,A} = 成员函数（public/protected/private × 虚/非虚）；
#   `S` = **static** 成员 —— 它的第 3 字符是**返回类型码**
#     （?sf_i@N@@SAIXZ = static unsigned int()；?sf_c@N@@SAEXZ；?sf_s@N@@SAGXZ）
#   ⇒ 若不排除 `S`，静态函数会被凭空读成 __fastcall/__thiscall/__stdcall（已实测）。
_MANGLING_CC = {'A': CC_CDECL, 'E': CC_THISCALL, 'G': CC_STDCALL, 'I': CC_FASTCALL}
_MANGLING_MEMBER_RE = re.compile(r'^\?[A-Za-z_][A-Za-z0-9_]*@[^@]*@@[QUMEIA]A([AEGI])')


def convention_from_symbol(symbol):
    """从 MSVC mangling 的**虚/非虚成员前缀**解出调用约定；无证据 ⇒ `None`（绝不猜）。

    只认实证形态 `<access>A<conv>`（含 `S`=static 一律拒绝，见上表）；
    自由函数（`?f@@YA…`）、模板类（类名内含 `@`）、析构（`??_G…`）等形态一律 `None`。
    """
    m = _MANGLING_MEMBER_RE.match(symbol or '')
    return _MANGLING_CC[m.group(1)] if m else None


# ---------------- 特征词表（写进候选/记录，供 Task 5 诊断） ----------------

FEATURE_ECX_THIS = 'ecx_this'
FEATURE_EDX_REG_ARG = 'edx_reg_arg'
FEATURE_THIS_ON_STACK = 'this_on_stack'
FEATURE_SRET = 'sret'
FEATURE_VARIADIC = 'variadic'
FEATURE_HIDDEN_PARAM_SUSPICION = 'hidden_param_suspicion'
FEATURE_ICF_FOLDED = 'icf_folded'
FEATURE_INSUFFICIENT_EVIDENCE = 'insufficient_evidence'
FEATURE_READ_SET_EMPTY = 'read_set_empty'
FEATURE_AMBIGUOUS_PARAM_CLASS = 'ambiguous_param_class'
FEATURE_QWORD_ARG = 'qword_arg'
FEATURE_FP_WIDTH_AMBIGUOUS = 'fp_width_ambiguous'
FEATURE_SKIPPED_SYNTHETIC_SLOT = 'skipped_synthetic_slot'
FEATURE_CALL_SITE_MISMATCH = 'call_site_mismatch'
FEATURE_RET_CONTRADICTION = 'ret_contradiction'
FEATURE_STACK_BASE_UNKNOWN = 'stack_base_unknown'
FEATURE_NO_PROLOGUE = 'no_prologue'
FEATURE_REAL_PARAM_BLIND_SPOT = 'real_param_blind_spot'
FEATURE_SLOT0_DEREF = 'slot0_deref'
FEATURE_PARSER_ERROR = 'parser_error'
FEATURE_SRET_AMBIGUOUS = 'sret_ambiguous'
FEATURE_CC_FROM_MANGLING = 'cc_from_mangling'


# ---------------- 数据结构 ----------------

@dataclass(frozen=True)
class ParamCandidate:
    """一个候选参数：占几个 4 字节栈槽 + 字节等价类候选集合。

    `class_candidates` 为空集 = 完全无证据；长度 >1 = callee 不可分（不得断言单一类）。
    """
    slots: int = 1
    class_candidates: frozenset = field(default_factory=frozenset)

    @property
    def determined(self):
        return len(self.class_candidates) == 1

    def to_dict(self):
        return {'slots': self.slots,
                'class_candidates': sorted(self.class_candidates),
                'determined': self.determined}


@dataclass(frozen=True)
class SignatureCandidate:
    """候选签名（**只描述 callee 侧字节可证的部分**）。"""
    addr: str = ''
    name: str = ''
    symbol: str = ''
    signature: str = ''
    convention: str = CC_UNKNOWN
    arity: int = None                 # None = 不确定（C 级）
    return_kind: str = RET_UNKNOWN
    params: tuple = ()                # tuple[ParamCandidate]
    variadic: bool = False
    grade: str = GRADE_C
    features: frozenset = field(default_factory=frozenset)
    notes: tuple = ()
    # --- 证据数值（诊断/对账） ---
    ret_bytes: int = 0
    bare_ret: bool = True
    stack_slots: int = 0              # ret N/4 或读集下界
    read_slots: int = 0
    reg_arg_count: int = 0            # 入口寄存器实参个数（fastcall: 1，成员 ecx 除外）
    this_on_stack: bool = False
    param_class_undetermined: bool = False
    hidden_param_suspicion: bool = False
    arity_is_lower_bound: bool = False
    cc_provisional: bool = False
    call_site_consistent: bool = None  # None = 无调用点证据
    slot_kind: str = KIND_FN
    source = 'disasm'                 # 证据源标记（永远不是 decomp）

    def to_dict(self):
        return {
            'signature': self.signature,
            'convention': self.convention,
            'arity': self.arity,
            'arity_is_lower_bound': self.arity_is_lower_bound,
            'return_kind': self.return_kind,
            'params': [p.to_dict() for p in self.params],
            'variadic': self.variadic,
            'grade': self.grade,
            'features': sorted(self.features),
            'notes': list(self.notes),
            'evidence': {
                'ret_bytes': self.ret_bytes, 'bare_ret': self.bare_ret,
                'stack_slots': self.stack_slots, 'read_slots': self.read_slots,
                'reg_arg_count': self.reg_arg_count, 'this_on_stack': self.this_on_stack,
                'param_class_undetermined': self.param_class_undetermined,
                'hidden_param_suspicion': self.hidden_param_suspicion,
                'cc_provisional': self.cc_provisional,
                'call_site_consistent': self.call_site_consistent,
            },
            'slot_kind': self.slot_kind,
            'source': self.source,
        }


@dataclass(frozen=True)
class SigEvidence:
    """一个槽的输入证据。

    disasm:     **原始**反汇编文本（Ruling 1：非 str ⇒ TypeError）
    symbol:     mangled 名（COFF/反汇编头）—— 仅用于**变参**识别（`ZZ` 结尾，C-4）
    name:       可读名（可空）；只影响 signature 文本
    slot_kind:  若调用方已跑过 Task 2 可传入；空 ⇒ 本模块内部 classify（**传原始文本**）
    call_sites: 调用点反汇编文本（旁证；不覆盖 callee 结论）
    """
    addr: str = ''
    name: str = ''
    symbol: str = ''
    disasm: str = ''
    signature: str = ''
    slot_kind: str = ''
    slot_notes: tuple = ()
    is_member: bool = True
    is_external: bool = False
    external_symbol: str = ''
    call_sites: tuple = ()


@dataclass(frozen=True)
class CallSiteEvidence:
    """调用点旁证（**只作旁证**：C-2/C-3 实测单侧证据会收敛到错误值）。"""
    push_count: int = 0
    reg_args: tuple = ()          # 调用前设置的寄存器实参（如 ('edx',)）
    this_reg: str = ''            # 命中 `lea ...,%ecx` 一类"对象地址入 ecx"形态
    bool_materialized: bool = False
    arg_classes: tuple = ()       # 已物化的实参类（'bool' / 'dword_non_bool'）
    raw: str = ''

    def to_dict(self):
        return {'push_count': self.push_count, 'reg_args': list(self.reg_args),
                'this_reg': self.this_reg, 'bool_materialized': self.bool_materialized,
                'arg_classes': list(self.arg_classes)}


@dataclass(frozen=True)
class PendingRecord:
    """一个**地址**的候选集合（C-5：一地址可对多签名 ⇒ 键值必须是列表）。"""
    addr: str = ''
    candidates: tuple = ()
    icf_folded: bool = False
    ambiguous: bool = False
    skipped: bool = False
    slot_kind: str = KIND_FN
    features: frozenset = field(default_factory=frozenset)
    notes: tuple = ()

    def to_dict(self):
        return {'candidates': [c.to_dict() for c in self.candidates],
                'icf_folded': self.icf_folded, 'ambiguous': self.ambiguous,
                'skipped': self.skipped, 'slot_kind': self.slot_kind,
                'features': sorted(self.features), 'notes': list(self.notes)}


# ---------------- Task 2 解析器的 PE-COFF 重定位行缺陷（防御性处理） ----------------

#: PE-COFF objdump 的重定位注释行体（`dir32 $SG263` / `DISP32 ?sym` / `off32 ...`）。
#: ⚠️ Task 2 `parse_disasm_report` 只认 GNU 风格 `R_386_*`，PE-COFF 的 `dir32 $sym` 会被
#: 当指令解析 ⇒ `_parse_int('sg263')` 抛 **ValueError**（实测：任何含字符串地址压栈的函数
#: 都有这种行）。本模块**先传原始文本**（Ruling 1），捕获后剥该行重试并留痕；
#: 该缺陷本身属 Task 2 解析器，已作为发现项上报。
_PE_RELOC_LINE = re.compile(
    r'^\s*(?:[0-9A-Fa-f]{1,16}:\s*)?(?:DISP32|dir32|DIR32|off32|OFF32|'
    r'R_386_[A-Za-z0-9_]+|R_IA64_[A-Za-z0-9_]+|R_X86_64_[A-Za-z0-9_]+)\b')


def sanitize_pe_relocs(text):
    """剥掉 PE-COFF 重定位注释行 → (新文本, 剥离行数)。**不改指令语义**。"""
    keep, dropped = [], 0
    for line in text.splitlines():
        if _PE_RELOC_LINE.match(line):
            dropped += 1
            continue
        keep.append(line)
    return '\n'.join(keep), dropped


def _safe_parse(text):
    """→ (ParseReport, 实际解析用的文本, parser_error|None)。"""
    try:
        return parse_disasm_report(text), text, None
    except ValueError as exc:
        clean, n = sanitize_pe_relocs(text)
        return parse_disasm_report(clean), clean, (str(exc), n)


def _safe_classify(ev, text):
    """→ (kind, notes, 实际解析文本, parser_error|None)。Ruling 1：始终先传原始文本。"""
    def _run(t):
        return classify_slot(SlotEvidence(
            symbols=tuple(filter(None, (ev.symbol,))), signature=ev.signature,
            instructions=t, is_external=ev.is_external,
            external_symbol=ev.external_symbol, addr=ev.addr))
    try:
        cls = _run(text)
        return cls.kind, tuple(cls.notes), text, None
    except ValueError as exc:
        clean, n = sanitize_pe_relocs(text)
        cls = _run(clean)
        return cls.kind, tuple(cls.notes), clean, (str(exc), n)


# ---------------- 反汇编扫描（帧/栈参/寄存器入口/返回宽度） ----------------

_TEARDOWN_MNEMS = frozenset({'leave', 'ret', 'pop', 'popad', 'popa', 'popfd'})
#: 尾部对齐填充（objdump/IDA 切片常带）—— 必须先剥掉，否则 `ret` 不再是末位
_PADDING_MNEMS = frozenset({'nop', 'nopw', 'nopl', 'int3', 'hlt'})
#: 纯写内存（ops[0] 为 mem 时 ops[0] 是目的、不是读）
_PURE_STORE_MNEMS = frozenset({
    'mov', 'movsd', 'movss', 'stos', 'stosb', 'stosd',
    'fst', 'fsts', 'fstl', 'fstp', 'fstps', 'fstpl', 'fstpt',
    'fist', 'fists', 'fistl', 'fistp', 'fistps', 'fistpl', 'fistpq',
})
#: 读改写内存（ops[0] 为 mem 时 ops[0] 既是读又是写）
_RMW_MNEMS = frozenset({'add', 'sub', 'and', 'or', 'xor', 'adc', 'sbb', 'inc', 'dec',
                        'neg', 'not', 'shl', 'shr', 'sal', 'sar', 'rol', 'ror'})
#: 写 ops[0] 的助记符（含 setcc）
_WRITE_DST_MNEMS = frozenset({
    'mov', 'movzx', 'movsx', 'lea', 'xor', 'add', 'sub', 'and', 'or', 'adc', 'sbb',
    'imul', 'mul', 'shl', 'shr', 'sal', 'sar', 'rol', 'ror', 'neg', 'not', 'inc', 'dec',
    'pop', 'xchg', 'bswap',
})
#: 隐式使用/写 edx 的助记符（不得据此判"edx 入口实参"）
_IMPLICIT_EDX = frozenset({'mul', 'div', 'idiv', 'cdq', 'cltd', 'cwd', 'cwde', 'cbtw', 'cwtl'})
#: eax 的符号扩展（属于**返回值物化**，不算"读了 eax 就不是返回值"）
_SIGN_EXTEND_MNEMS = frozenset({'cdq', 'cltd', 'cwd', 'cwde'})

EAX_FAMILY = ('eax', 'ax', 'al', 'ah')
_REG_SIZE = {'eax': 4, 'ax': 2, 'al': 1, 'ah': 1}

_SIZE_KEYWORDS = (('xmmword', 16), ('oword', 16), ('qword', 8), ('fword', 6),
                  ('tbyte', 10), ('tword', 10), ('dword', 4), ('word', 2), ('byte', 1))
#: 带**宽度**的 x87 访存（可判 f32/f64）
_FP_WIDTH_MNEMS = {'flds': 4, 'fsts': 4, 'fstps': 4,
                   'fldl': 8, 'fstl': 8, 'fstpl': 8,
                   'fldt': 10, 'fstpt': 10}
#: 整数↔x87 家族（宽度不可判：结果进 st(0) 后再由调用者按声明转换）
_FP_INT_MNEMS = frozenset({'fild', 'filds', 'fildl', 'fildq', 'fildll',
                           'fist', 'fists', 'fistl', 'fistp', 'fistps', 'fistpl', 'fistpq',
                           'fisttp'})


def _strip_padding(insns):
    """剥掉尾部对齐填充（nop/int3/xchg %ax,%ax）——否则 `ret` 不在末位。"""
    i = len(insns)
    while i > 0:
        ins = insns[i - 1]
        if ins.mnem in _PADDING_MNEMS:
            i -= 1
            continue
        if (ins.mnem == 'xchg' and len(ins.ops) == 2
                and all(o.kind == 'reg' and o.reg == 'ax' for o in ins.ops)):
            i -= 1
            continue
        break
    return insns[:i]


def _is_teardown(ins):
    if ins.mnem in _TEARDOWN_MNEMS:
        return True
    ops = ins.ops
    if not ops:
        return False
    o0 = ops[0]
    if o0.kind != 'reg' or o0.reg != 'esp':
        return False
    if ins.mnem == 'mov' and len(ops) > 1 and ops[1].kind == 'reg' and ops[1].reg == 'ebp':
        return True                     # mov %ebp,%esp
    if ins.mnem == 'add' and len(ops) > 1 and ops[1].kind == 'imm':
        return True                     # add $N,%esp（调用者清栈/收尾）
    return False


def _split_body(insns):
    """→ (body, tail)：tail = 末尾连续帧收尾（mov %ebp,%esp / pop / add $N,%esp / ret）。"""
    insns = _strip_padding(tuple(insns))
    i = len(insns)
    while i > 0 and _is_teardown(insns[i - 1]):
        i -= 1
    return insns[:i], insns[i:]


def _has_frame_pointer(insns):
    for ins in insns:
        if (ins.mnem == 'mov' and len(ins.ops) == 2
                and ins.ops[0].kind == 'reg' and ins.ops[0].reg == 'ebp'
                and ins.ops[1].kind == 'reg' and ins.ops[1].reg == 'esp'):
            return True
    return False


def _ret_info(tail):
    """→ (N|0, bare)。裸 ret ⇒ (0, True)：callee 清 0 字节（或 caller 清，无信息）。"""
    for ins in reversed(tail):
        if ins.mnem == 'ret':
            if ins.ops and ins.ops[0].kind == 'imm':
                return int(ins.ops[0].value), False
            return 0, True
    return 0, True


def _mem_size(ins, op):
    """操作数宽度（字节）。AT&T 靠助记符后缀 / Intel 靠 `dword ptr` 等关键词；默认 4。"""
    if ins.mnem in _FP_WIDTH_MNEMS:
        return _FP_WIDTH_MNEMS[ins.mnem]
    raw = (ins.raw or '').lower()
    for kw, size in _SIZE_KEYWORDS:
        if kw in raw:
            return size
    base = ins.mnem
    for suf, size in (('ll', 8), ('l', 8), ('s', 4), ('q', 8)):
        if base.endswith(suf) and base[:-len(suf)] in ('fld', 'fst', 'fstp'):
            return size
    if op.text and '%' in op.text:
        m = op.text.rstrip(')').rsplit('%', 1)[-1].lower()
        if m in _REG_SIZE:
            return _REG_SIZE[m]
    return 4


def _mem_reads(ins):
    ops = ins.ops
    if not ops:
        return []
    if ins.mnem == 'push':
        return [o for o in ops if o.kind == 'mem']
    first_is_write = (ops[0].kind == 'mem'
                      and (ins.mnem in _PURE_STORE_MNEMS or ins.mnem in _RMW_MNEMS))
    out = []
    for i, o in enumerate(ops):
        if o.kind != 'mem':
            continue
        if i == 0 and first_is_write and ins.mnem not in _RMW_MNEMS:
            continue
        out.append(o)
    return out


def _mem_writes(ins):
    ops = ins.ops
    if not ops or ops[0].kind != 'mem':
        return []
    if ins.mnem in _PURE_STORE_MNEMS or ins.mnem in _RMW_MNEMS:
        return [ops[0]]
    return []


def _writes_reg(ins, reg):
    if ins.mnem not in _WRITE_DST_MNEMS and not ins.mnem.startswith('set'):
        return False
    return bool(ins.ops) and ins.ops[0].kind == 'reg' and ins.ops[0].reg == reg


def _reads_reg(ins, reg):
    """该指令是否读 reg（含作为内存基址/变址；不含 setcc/cdq 一类只写形态）。"""
    if reg == 'edx' and ins.mnem in _IMPLICIT_EDX:
        return False
    for i, o in enumerate(ins.ops):
        if i == 0 and _writes_reg(ins, reg):
            continue
        if o.kind == 'reg' and o.reg == reg:
            return True
        if o.kind == 'mem' and (o.base == reg or o.index == reg):
            return True
    return False


def _reads_eax(ins):
    for o in ins.ops:
        if o.kind == 'reg' and o.reg in EAX_FAMILY:
            # `mov %eax,...`（eax 作源）/ `push %eax` 等都是读
            if not (o is ins.ops[0] and _writes_reg(ins, o.reg)):
                return True
        if o.kind == 'mem' and (o.base in EAX_FAMILY or o.index in EAX_FAMILY):
            return True
    return False


def _fp_kind(ins):
    """→ ('width', 4|8|10) | ('int_fp', None) | None"""
    if ins.mnem in _FP_WIDTH_MNEMS:
        return ('width', _FP_WIDTH_MNEMS[ins.mnem])
    if ins.mnem in _FP_INT_MNEMS:
        return ('int_fp', None)
    m = ins.mnem
    for suf, size in (('ll', 8), ('l', 8), ('s', 4), ('t', 10)):
        if m.endswith(suf) and m[:-len(suf)] in ('fld', 'fst', 'fstp'):
            return ('width', size)
    if m in ('fld', 'fst', 'fstp') and any(o.kind == 'mem' for o in ins.ops):
        raw = (ins.raw or '').lower()
        for kw, size in (('qword', 8), ('dword', 4), ('tbyte', 10), ('tword', 10)):
            if kw in raw:
                return ('width', size)
        return ('int_fp', None)
    return None


@dataclass(frozen=True)
class _Scan:
    body: tuple = ()
    tail: tuple = ()
    frame: str = 'ebp'
    ret_bytes: int = 0
    bare_ret: bool = True
    reads: frozenset = frozenset()
    writes: frozenset = frozenset()
    qword_reads: frozenset = frozenset()
    ecx_this: bool = False
    edx_incoming: bool = False
    this_deref: bool = False
    sret_slot: int = None
    sret_ambiguous: bool = False
    return_kind: str = RET_UNKNOWN
    st_base_ok: bool = True
    no_prologue: bool = False
    notes: tuple = ()
    features: frozenset = frozenset()


def _scan(insns):
    """单趟过程内扫描：栈参读集 / ecx-this / edx 入口 / sret / 返回宽度。

    每指令的处理顺序**是语义**（踩过坑：先做"写失效"会把刚建立的
    `reg <- 参数槽` 映射立刻删掉 ⇒ this 解引用/sret store-through 全灭）：

      1 入口寄存器证据（ecx 作基址/溢出；edx 作源/溢出）—— 用**写之前**的状态
      2 栈参数读 / 写（含 qword 占双槽）
      3 store-through（用当前 `reg <- 槽` 映射）
      4 this 解引用（首槽值作内存基址）
      5 返回宽度候选（x87 / eax 族 / 符号扩展）
      6 **写失效**（本指令写了哪些寄存器）
      7 `reg <- 参数槽` 载入/清除（mov/lea）
      8 call 破坏 caller-saved
      9 esp 跟踪（无帧指针形态）
    """
    body, tail = _split_body(insns)
    frame = 'ebp' if _has_frame_pointer(body) else 'esp'
    ret_bytes, bare_ret = _ret_info(tail)
    ecx_written = edx_written = False
    ecx_this = edx_incoming = False
    this_deref = False
    sp = 0 if frame == 'esp' else None
    st_base_ok = (frame == 'ebp')
    reads, writes, qword = set(), set(), set()
    reg_slot = {}                 # reg -> 它当前持有的参数槽号（mov/lea 载入）
    store_through = {}            # (slot, base_reg) -> set(已写字节偏移)
    last_eax_idx = -1
    last_fp_idx = -1
    fp_kind = None
    eax_src_slot = None
    sign_extended = False

    def classify(op):
        """mem 操作数 → ('param', slot) | ('local', None) | (None, None)"""
        if op.base == 'ebp' and frame == 'ebp':
            if op.disp >= 8:
                return 'param', (op.disp - 8) // 4
            return 'local', None
        if op.base == 'esp' and frame == 'esp':
            if sp is None:
                return (None, None)
            if op.disp >= sp + 4:
                return 'param', (op.disp - sp - 4) // 4
            return 'local', None
        return (None, None)

    for idx, ins in enumerate(body):
        # --- 1 入口寄存器证据（写之前） ---
        for o in ins.ops:
            if o.kind == 'mem' and o.base == 'ecx' and not ecx_written:
                ecx_this = True                       # ecx 作成员访问基址 ⇒ 入口 this
                ecx_written = True                    # 只认第一次
        if (ins.mnem == 'mov' and len(ins.ops) == 2 and ins.ops[0].kind == 'mem'
                and ins.ops[1].kind == 'reg'):
            dst, src = ins.ops[0], ins.ops[1]
            _, dslot = classify(dst)
            if dslot is None and dst.base in ('ebp', 'esp'):
                if src.reg == 'ecx' and not ecx_written:
                    ecx_this = True
                if src.reg == 'edx' and not edx_written:
                    edx_incoming = True
        if (not edx_written and ins.mnem not in _IMPLICIT_EDX
                and not _writes_reg(ins, 'edx') and _reads_reg(ins, 'edx')):
            edx_incoming = True           # /O2：edx 直接作源使用（无溢出）

        # --- 2 栈参数读 / 写 ---
        for r in _mem_reads(ins):
            kind, slot = classify(r)
            if kind == 'param':
                reads.add(slot)
                if _mem_size(ins, r) >= 8:
                    qword.add(slot)
                    reads.add(slot + 1)
        for w in _mem_writes(ins):
            kind, slot = classify(w)
            if kind == 'param':
                writes.add(slot)

        # --- 3 store-through（sret 候选：经"从参数槽载入的寄存器"写出） ---
        for w in _mem_writes(ins):
            base = w.base
            if base in reg_slot:
                key = (reg_slot[base], base)
                offs = store_through.setdefault(key, set())
                size = _mem_size(ins, w)
                offs.update(range(w.disp, w.disp + max(size, 1)))

        # --- 4 this 解引用：首槽值被当**内存基址**用（对象访问） ---
        for o in ins.ops:
            if o.kind == 'mem' and o.base in reg_slot and reg_slot[o.base] == 0:
                this_deref = True

        # --- 5 返回宽度候选 ---
        fk = _fp_kind(ins)
        if fk is not None:
            last_fp_idx = idx
            fp_kind = fk
        if (ins.ops and ins.ops[0].kind == 'reg' and ins.ops[0].reg in EAX_FAMILY
                and _writes_reg(ins, ins.ops[0].reg)):
            last_eax_idx = idx
            eax_src_slot = None
            if ins.mnem == 'mov' and len(ins.ops) == 2 and ins.ops[1].kind == 'mem':
                kind, slot = classify(ins.ops[1])
                if kind == 'param':
                    eax_src_slot = slot
        if ins.mnem in _SIGN_EXTEND_MNEMS and idx > last_eax_idx:
            sign_extended = True

        # --- 6 写失效（本指令写了哪些寄存器） ---
        written_regs = set()
        for o in ins.ops:
            if o.kind == 'reg' and _writes_reg(ins, o.reg):
                written_regs.add(o.reg)
                if o.reg == 'ecx':
                    ecx_written = True
                if o.reg == 'edx':
                    edx_written = True

        # --- 7 `reg <- 参数槽` 载入/清除 ---
        if ins.mnem in ('mov', 'lea') and len(ins.ops) == 2 and ins.ops[0].kind == 'reg':
            dst, src = ins.ops[0].reg, ins.ops[1]
            if not (dst in written_regs and src.kind != 'mem'):
                reg_slot.pop(dst, None)
            kind, slot = classify(src) if src.kind == 'mem' else (None, None)
            if kind == 'param':
                reg_slot[dst] = slot
            else:
                reg_slot.pop(dst, None)

        # --- 8 call 破坏 caller-saved ---
        if ins.mnem == 'call':
            for r in ('eax', 'ecx', 'edx'):
                if r == 'ecx':
                    ecx_written = True
                if r == 'edx':
                    edx_written = True
                reg_slot.pop(r, None)

        # --- 9 esp 跟踪（无帧指针形态） ---
        if frame == 'esp':
            if sp is None:
                pass
            elif ins.mnem == 'push':
                sp += 4
            elif ins.mnem == 'pop':
                sp = max(sp - 4, 0)
            elif ins.mnem in ('sub', 'add') and ins.ops and ins.ops[0].kind == 'reg' \
                    and ins.ops[0].reg == 'esp' and len(ins.ops) > 1 and ins.ops[1].kind == 'imm':
                sp = sp + ins.ops[1].value if ins.mnem == 'sub' else sp - ins.ops[1].value
            elif (ins.ops and ins.ops[0].kind == 'reg' and ins.ops[0].reg == 'esp'
                  and ins.mnem == 'mov' and not (
                      len(ins.ops) > 1 and ins.ops[1].kind == 'reg'
                      and ins.ops[1].reg in ('esp', 'ebp'))):
                sp = None                     # mov esp,<未知> ⇒ 跟踪失效
            elif ins.mnem == 'and' and ins.ops and ins.ops[0].kind == 'reg' \
                    and ins.ops[0].reg == 'esp':
                sp = None

    if frame == 'esp':
        st_base_ok = sp is not None

    notes, features = [], set()
    if frame == 'esp':
        features.add(FEATURE_NO_PROLOGUE)
        if not st_base_ok:
            features.add(FEATURE_STACK_BASE_UNKNOWN)
            notes.append('stack_base_unknown: esp 跟踪中断（mov/and esp 或未建模指令）⇒ '
                         '栈参定位不可信 ⇒ 参数个数不确定')
    if ecx_this:
        features.add(FEATURE_ECX_THIS)
        notes.append('ecx_this: ecx 入口即 this（帧内溢出 / 作成员访问基址）')
    if edx_incoming:
        features.add(FEATURE_EDX_REG_ARG)
        notes.append('edx_reg_arg: edx 入口即首个实参（__fastcall）—— /O2 下未被使用的'
                     '寄存器实参无痕，属已知盲区')
    if this_deref:
        features.add(FEATURE_SLOT0_DEREF)
        notes.append('slot0_deref: 首个栈槽的值被解引用（对象访问）⇒ 该槽像隐藏 this'
                     '（也可能是 sret 指针；判决见 convention/return_kind）')
    if not reads:
        features.add(FEATURE_READ_SET_EMPTY)

    # --- sret：epilogue 前最后一次 eax 载入**首槽** + 单基址寄存器（相对首址）**连续**
    # ≥9 字节 store-through（I2 修复轮 R=1：只查 `max(covered) >= 8` 会把"相对首址有窟窿"
    # 的散写（如 /Od `?poff` 只写 +0xc）误判成 sret ⇒ 必须要求 covered 从 0 起连续） ---
    sret_slot = None
    sret_ambiguous = False
    terminal_eax = last_eax_idx >= 0 and not any(
        _reads_eax(i) and i.mnem not in _SIGN_EXTEND_MNEMS for i in body[last_eax_idx + 1:])
    if terminal_eax and eax_src_slot == 0:
        bases = {b for (s, b) in store_through if s == 0}
        covered = set()
        for (s, b), offs in store_through.items():
            if s == 0:
                covered |= offs
        # "连续"= 从首址 0 起逐字节覆盖到 max ⇒ 结构体逐字段复制（真 sret）的形态；
        # 散写（0 与 0xc、或只有 0xc）不是结构复制 ⇒ 不判 sret（连"含糊"都不标）
        contiguous = bool(covered) and covered == set(range(max(covered) + 1))
        if contiguous and max(covered) >= 8:
            if len(bases) == 1:
                sret_slot = 0
            else:
                sret_ambiguous = True
    if sret_slot is not None:
        features.add(FEATURE_SRET)
        notes.append('sret: 返回 >8B 结构 ⇒ 首槽 %d 是隐藏 sret 指针（单基址寄存器 %s 连续写 '
                     '≥9 字节 + eax 末次载入该槽）⇒ 已从参数里扣除'
                     % (sret_slot, ','.join(sorted({b for (s, b) in store_through if s == 0}))))
    elif sret_ambiguous:
        features.add(FEATURE_SRET_AMBIGUOUS)
        notes.append('sret_ambiguous: 末次 eax 载入首槽且该槽被多基址寄存器写出 >8 字节 ⇒ '
                     '可能是 sret 也可能是"指针参数 + 返回值即该指针"（probe rw4 `retp` 反例）'
                     '⇒ 不扣除、降级为 B 并留痕')

    # --- 返回宽度 ---
    return_kind = RET_UNKNOWN
    if last_fp_idx > last_eax_idx:
        kind, width = fp_kind if fp_kind else ('int_fp', None)
        if kind == 'width' and width == 4:
            return_kind = RET_F32
        elif kind == 'width' and width == 8:
            return_kind = RET_F64
        else:
            return_kind = RET_UNKNOWN
            features.add(FEATURE_FP_WIDTH_AMBIGUOUS)
            notes.append('fp_width_ambiguous: st(0) 结果由整数/无宽度 x87 访问产生 ⇒ '
                         'f32/f64 不可分（probe rw2 `rf`/`rd` 同体）⇒ 不得猜')
    elif terminal_eax:
        dst = body[last_eax_idx].ops[0]
        if sign_extended:
            return_kind = RET_I64
        elif body[last_eax_idx].mnem.startswith('set'):
            return_kind = RET_BOOL
        else:
            return_kind = {4: RET_I32, 2: RET_I16, 1: RET_I8}.get(
                _REG_SIZE.get(dst.reg, 4), RET_I32)
    elif last_eax_idx >= 0:
        notes.append('return_unknown: eax 的末次写入被后续指令消费（非返回值）⇒ 返回宽度不可证')

    return _Scan(body=body, tail=tail, frame=frame, ret_bytes=ret_bytes, bare_ret=bare_ret,
                 reads=frozenset(reads), writes=frozenset(writes),
                 qword_reads=frozenset(qword), ecx_this=ecx_this,
                 edx_incoming=edx_incoming, this_deref=this_deref,
                 sret_slot=sret_slot, sret_ambiguous=sret_ambiguous,
                 return_kind=return_kind, st_base_ok=st_base_ok,
                 no_prologue=not _has_frame_pointer(body),
                 notes=tuple(notes), features=frozenset(features))


# ---------------- 调用点旁证 ----------------

def analyze_call_sites(text):
    """调用点旁证：push 计数 / 寄存器实参 / BOOL 物化。

    ⚠️ 只作旁证：C-2（fastcall）与 C-3（cdecl 成员 this 入栈）实测**单侧证据会给出错误
    参数个数**，两侧共用同一错误 ABI 模型时还会互相"确认"（attack README D-2）。
    本函数的结论**不覆盖** callee 侧推断，只用于对账（`call_site_consistent`）。
    """
    if not isinstance(text, str):
        raise TypeError('Ruling 1: 调用点证据也必须是原始反汇编文本')
    insns = parse_disasm_report(text).insns
    sites, cur = [], []
    for ins in insns:
        cur.append(ins)
        if ins.mnem == 'call':
            sites.append(_call_site_from(cur))
            cur = []
    if cur and sites:
        sites.append(_call_site_from(cur))
    elif cur:
        sites.append(_call_site_from(cur))
    return tuple(sites)


def _trim_site_prologue(insns):
    """剥掉调用序列前部的 callee-saved 寄存器保存（`push %ebp/%ebx/%esi/%edi`）。

    实测坑（b1 `c2`）：整函数反汇编喂进来时首段区域带 `push %ebp; mov %esp,%ebp`
    ⇒ push 计数凭空 +1。寄存器保存**不是**实参传递 ⇒ 必须先剥掉。
    """
    out = list(insns)
    i = 0
    while i < len(out):
        ins = out[i]
        if (ins.mnem == 'push' and ins.ops and ins.ops[0].kind == 'reg'
                and ins.ops[0].reg in ('ebp', 'ebx', 'esi', 'edi')):
            i += 1
            continue
        break
    return out[i:]


def _call_site_from(insns):
    insns = _trim_site_prologue(insns)
    push_count = 0
    reg_args = []
    this_reg = ''
    bool_mat = False
    arg_classes = []
    materialized = False
    for ins in insns:
        if ins.mnem == 'push':
            push_count += 1
            arg_classes.append('bool' if materialized else 'dword_non_bool')
            materialized = False
            continue
        if ins.mnem.startswith('set') and ins.ops and ins.ops[0].kind == 'reg':
            bool_mat = True
            materialized = True
            continue
        if ins.mnem in ('and', 'xor') and ins.ops and ins.ops[0].kind == 'reg' \
                and ins.ops[0].reg == 'eax' and len(ins.ops) > 1 and ins.ops[1].kind == 'imm':
            if ins.ops[1].value == 0xff:
                bool_mat = True
                materialized = True
            continue
        if ins.mnem == 'mov' and len(ins.ops) == 2 and ins.ops[0].kind == 'reg':
            if ins.ops[0].reg == 'edx':
                reg_args.append('edx')
        if ins.mnem == 'lea' and len(ins.ops) == 2 and ins.ops[0].kind == 'reg' \
                and ins.ops[0].reg == 'ecx':
            this_reg = 'ecx'
    raw = ' ; '.join(i.raw for i in insns)
    return CallSiteEvidence(push_count=push_count, reg_args=tuple(reg_args),
                            this_reg=this_reg, bool_materialized=bool_mat,
                            arg_classes=tuple(arg_classes), raw=raw)


# ---------------- 槽序/槽数 → 参数分段 ----------------

def _segment_params(slots, qword_slots):
    """槽集合 → 参数分组（qword 访问的两槽并成一个参数）。

    slots: 已排序的槽号序列；返回 [(起始槽, 槽数), ...]。
    """
    groups = []
    i = 0
    s = sorted(slots)
    while i < len(s):
        if s[i] in qword_slots and (s[i] + 1) in s:
            groups.append((s[i], 2))
            i += 2
        else:
            groups.append((s[i], 1))
            i += 1
    return groups


def _param_class_candidates(scan, start, size):
    """callee 侧**参数等价类候选集合**（C-5/C-6：多为不可分，不得断言单一类）。"""
    if size >= 2:
        if start in scan.qword_reads:
            # `fldl` 一类带宽度 x87 载入 ⇒ 可确定为 double；否则 f64/i64 不可分
            return frozenset({CLASS_F64}) if _qword_is_fp(scan, start) else QWORD_AMBIGUOUS
        return frozenset({CLASS_STRUCT}) | QWORD_AMBIGUOUS
    if start in scan.reads:
        return DWORD_AMBIGUOUS
    return DWORD_AMBIGUOUS


def _qword_is_fp(scan, slot):
    """该 qword 读是否由**带宽度**的 x87 载入（`fldl`）产生 ⇒ double 可判。"""
    for ins in scan.body:
        for r in _mem_reads(ins):
            if r.disp >= 8 and r.base in ('ebp', 'esp') and _mem_size(ins, r) >= 8:
                if ins.mnem in _FP_WIDTH_MNEMS and _FP_WIDTH_MNEMS[ins.mnem] == 8:
                    if (r.disp - 8) // 4 == slot:
                        return True
    return False


# ---------------- 主推断 ----------------

def _signature_text(name, convention, return_kind, params, variadic):
    ret = {RET_I8: 'char', RET_I16: 'short', RET_I32: 'int', RET_I64: '__int64',
           RET_F32: 'float', RET_F64: 'double', RET_BOOL: 'bool',
           RET_SRET: '<struct>', RET_VOID: 'void'}.get(return_kind, '?')
    toks = []
    for p in params:
        if p.determined:
            tok = {CLASS_I8: 'char', CLASS_I16: 'short', CLASS_I32: 'int',
                   CLASS_PTR: 'void*', CLASS_BOOL: 'bool', CLASS_F32: 'float',
                   CLASS_F64: 'double', CLASS_I64: '__int64',
                   CLASS_STRUCT: '<struct>'}.get(next(iter(p.class_candidates)), '?')
        else:
            tok = '?'
        if p.slots > 1 and not p.determined:
            tok += '[%d]' % p.slots
        toks.append(tok)
    if variadic:
        toks.append('...')
    return '%s %s %s(%s)' % (ret, convention, name or '_slot', ','.join(toks))


def infer_signature(ev):
    """单个证据 → `SignatureCandidate`；合成槽（非 fn）⇒ **None**（T2↔T3 契约"跳过合成槽"）。

    Ruling 1：`ev.disasm` 必须是原始反汇编**文本**（非 str ⇒ TypeError）。
    """
    if not isinstance(ev.disasm, str):
        raise TypeError('Ruling 1: disasm 必须是原始反汇编文本，'
                        '禁止先 parse_disasm 再喂 Insn 元组（痕迹会失效）')
    report, text_used, parser_err = _safe_parse(ev.disasm)
    kind = ev.slot_kind
    slot_notes = tuple(ev.slot_notes)
    if not kind:
        kind, slot_notes, text_used2, err2 = _safe_classify(ev, ev.disasm)
        parser_err = parser_err or err2
        text_used = text_used2
    if kind != KIND_FN:
        return None                      # adjustor/删除器/纯虚/复合槽：不推断签名

    name = ev.name or (ev.symbol or '')
    variadic = bool(ev.symbol) and ev.symbol.rstrip().endswith('ZZ')

    # Ruling 2：fn 必查 notes；证据不足不得当安全默认
    insufficient = report.insufficient_evidence or not report.insns
    notes = list(slot_notes)
    features = set()
    if parser_err is not None:
        features.add(FEATURE_PARSER_ERROR)
        notes.append('parser_error: Task2 解析器在原始文本上抛 ValueError(%s)'
                     '⇒ 已剥离 %d 行 PE-COFF 重定位注释行（`dir32 $sym`/`DISP32 ?sym`，'
                     '无语义）后重试；该行形态属 Task 2 解析器缺口，需上报修复'
                     % (parser_err[0], parser_err[1]))
    if report.insufficient_evidence:
        features.add(FEATURE_INSUFFICIENT_EVIDENCE)
        notes.append('insufficient_evidence: %d 行非空反汇编文本解析出 0 条指令'
                     '（丢弃 %d 行）⇒ 证据不足，不得回落成"0 参 void"'
                     % (report.content_lines, report.dropped_lines))
    if report.partially_parsed:
        notes.append('partially_parsed: 丢弃 %d/%d 行（>50%%）⇒ 解析不完整、结论不可信'
                     '⇒ 至多 B 级（I3 修复轮 R=1），需 IDA 复核'
                     % (report.dropped_lines, report.content_lines))
    if insufficient:
        return SignatureCandidate(
            addr=ev.addr, name=name, symbol=ev.symbol,
            signature=_signature_text(name, CC_UNKNOWN, RET_UNKNOWN, (), variadic),
            convention=CC_UNKNOWN, arity=None, return_kind=RET_UNKNOWN, params=(),
            variadic=variadic, grade=GRADE_C,
            features=frozenset(features | {FEATURE_INSUFFICIENT_EVIDENCE}),
            notes=tuple(notes), slot_kind=kind)

    scan = _scan(report.insns)   # report 已按（必要时剥离后的）文本解析
    notes.extend(scan.notes)
    features |= scan.features
    ret_kind = RET_SRET if scan.sret_slot is not None else scan.return_kind

    # --- 约定（Ruling 3/4） ---
    cc = CC_UNKNOWN
    cc_provisional = False
    this_on_stack = False
    reg_arg_count = 0
    if variadic:
        cc = CC_CDECL
        features.add(FEATURE_VARIADIC)
        notes.append('variadic: mangling `ZZ` 结尾（虚变参 `UAA…ZZ`）⇒ 强制 __cdecl；'
                     '命名参数个数无 callee 证据（须 IDA/mangling 解码）')
    elif scan.edx_incoming:
        cc = CC_FASTCALL
        reg_arg_count = 1                    # 成员 fastcall：ecx=this, edx=首参
    elif scan.ecx_this:
        cc = CC_THISCALL
    elif scan.this_deref:
        # C1（修复轮 R=1）：deref 只证明"首槽值是**指针对象基址**"，它同时符合
        # 「__thiscall 的**首个指针参数**」与「__stdcall/__cdecl 成员的 this」两种真值
        # —— /O2 实测 `?wr2@Rn6@@UAEHPAUInnerV@@@Z`（真值 __thiscall / 1 指针参 / int）
        # 与 `?g@C@@UAGHXZ`（真值 __stdcall 成员 / 0 参 / int）**逐字节相同**：
        # `8b 44 24 04 / c7 40 04 01… / c7 40 0c 03… / 33 c0 / c2 04 00`
        # ⇒ 单凭字节**不得**给 A；唯一能判开的是 mangling 虚成员前缀（`UAE`/`UAG`）。
        mangled_cc = convention_from_symbol(ev.symbol)
        if mangled_cc == CC_THISCALL and not scan.bare_ret:
            # mangling 权威且与 ret 形态自洽 ⇒ ecx=this，被解引用的首槽是**指针参数**
            cc = CC_THISCALL
            features.add(FEATURE_CC_FROM_MANGLING)
            notes.append('cc_from_mangling: mangling 成员前缀 = __thiscall（且 callee 清栈自洽）'
                         '⇒ ecx=this，被解引用的首槽是**首个指针参数**而非 this'
                         '（C1：deref 单凭字节分不出 this 归属）')
        elif mangled_cc in (CC_STDCALL, CC_CDECL) \
                and scan.bare_ret == (mangled_cc == CC_CDECL):
            # stdcall 成员 ⇒ 必是 `ret N`；cdecl 成员 ⇒ 必是裸 ret（清栈方必须自洽）
            this_on_stack = True
            cc = mangled_cc
            features.add(FEATURE_CC_FROM_MANGLING)
            notes.append('cc_from_mangling: mangling 成员前缀 = %s（与 %s 清栈形态自洽）'
                         '⇒ this 在首栈槽（该槽被解引用 = 成员访问）'
                         % (mangled_cc, 'caller' if scan.bare_ret else 'callee'))
        else:
            # 无 mangling 旁证（或旁证与字节矛盾）⇒ 只给**推定**，降级 B（C1 必修）
            this_on_stack = True
            cc = CC_CDECL if scan.bare_ret else CC_STDCALL
            cc_provisional = True
            notes.append('cc_provisional: deref 只证明首槽是**指针对象基址**，与'
                         '「__thiscall 的首个指针参数」和「%s 成员的 this」两种真值**同形**'
                         '（C1 实测 ?wr2 与 ?g 逐字节相同）⇒ 推定 this 在首栈槽，降级 B'
                         % cc)
    elif ev.is_member and not scan.bare_ret and scan.ret_bytes > 0:
        # 无 ecx 证据但 callee 清栈：MSVC 成员默认 __thiscall（this 未使用 ⇒ 无痕）；
        # 备选读法是 __stdcall 成员（this@首槽）⇒ 结论只是**推定**
        cc = CC_THISCALL
        cc_provisional = True
        notes.append('cc_provisional: 无 ecx this 证据但 callee 清栈（ret %d）⇒ 推定 __thiscall'
                     '（备选：__stdcall 成员，this 占首槽）⇒ 降级 B'
                     % scan.ret_bytes)
    elif scan.bare_ret and scan.reads:
        cc = CC_CDECL
        this_on_stack = True
        this_deref_note = '（无解引用证据，按成员 ABI 推定）' if not scan.this_deref else ''
        cc_provisional = not scan.this_deref
        notes.append('caller 清栈（裸 ret）+ 存在栈读 ⇒ 成员 this 占首槽%s' % this_deref_note)
    else:
        cc = CC_UNKNOWN
        notes.append('cc_unknown: 无 ecx/edx 入口证据、无栈参读取、无 ret N ⇒ 调用约定不可证')

    # --- 参数个数 ---
    # 槽空间归一：raw = ret N/4（callee 清栈时才有意义）；shift = sret / 栈上 this 的槽数
    callee_clean = cc in (CC_THISCALL, CC_FASTCALL, CC_STDCALL)
    raw_stack_slots = None
    if callee_clean:
        raw_stack_slots = 0 if scan.bare_ret else scan.ret_bytes // 4
    shift = (1 if scan.sret_slot is not None else 0) + (1 if this_on_stack else 0)
    arg_slots = None if raw_stack_slots is None else max(raw_stack_slots - shift, 0)
    reads_rel = {s - shift for s in scan.reads if s >= shift}
    qw_rel = {s - shift for s in scan.qword_reads if s >= shift}
    if qw_rel:
        features.add(FEATURE_QWORD_ARG)
    hidden = False
    arity_is_lower = False
    if FEATURE_STACK_BASE_UNKNOWN in scan.features:
        # esp 跟踪中断 ⇒ 栈参定位不可信：不得用 ret N 反推参数个数（可能是 this/局部）
        arity = None
        hidden = True
        notes.append('stack_base_unknown ⇒ 参数个数不可定（C 级）')
    elif variadic:
        arity = None
        notes.append('variadic: 参数个数无 callee 证据（仅 mangling 有命名参数信息）⇒ C 级')
    elif cc == CC_UNKNOWN:
        arity = None
    elif callee_clean:
        slot_seq = list(range(arg_slots)) if arg_slots is not None else sorted(reads_rel)
        if arg_slots is not None and reads_rel - set(range(arg_slots)):
            slot_seq = sorted(set(slot_seq) | reads_rel)
            features.add(FEATURE_RET_CONTRADICTION)
            notes.append('ret_contradiction: 读集越出 ret N 给出的栈范围 ⇒ ret N 与读集矛盾，'
                         '参数个数不可信')
        groups = _segment_params(slot_seq, qw_rel) if slot_seq else []
        arity = len(groups) + reg_arg_count
        if arg_slots is not None and reads_rel != set(range(arg_slots)):
            hidden = True
            notes.append('hidden_param_suspicion: 读集 %s ⊊ 栈槽 0..%d ⇒ ret N 只给**槽数**，'
                         '可能有隐藏参数（未被读取的实参），或双槽参数'
                         '（double/__int64/按值结构占 2 槽）'
                         % (sorted(reads_rel), arg_slots - 1))
    else:
        # caller 清栈（cdecl）：读集只是**下界**（未用参数不可见）
        groups = _segment_params(sorted(reads_rel), qw_rel) if reads_rel else []
        arity = len(groups) if groups else None
        arity_is_lower = arity is not None
        if arity is not None:
            hidden = True
            notes.append('arity_is_lower_bound: caller 清栈（cdecl）⇒ 读集只给参数个数**下界**'
                         '（未用参数不可见）')
    if this_on_stack:
        features.add(FEATURE_THIS_ON_STACK)
    if scan.sret_ambiguous:
        hidden = True
        notes.append('sret_ambiguous ⇒ 参数个数可能整体错位一位（>8B 结构返回）⇒ 降级 B')
    if cc == CC_THISCALL and scan.bare_ret and arity == 0 and not variadic:
        features.add(FEATURE_REAL_PARAM_BLIND_SPOT)
        arity_is_lower = True
        notes.append('real_param_blind_spot: /O2 下未被使用的**寄存器实参**无痕'
                     '（probe opt2 `?fu@Os@@UAIXH@Z` 与 thiscall 0 参同形）'
                     '⇒ 0 只是下界，fastcall 可能漏检')
    if hidden:
        # 统一落账：上面三处（未读槽 / sret 含糊 / 寄存器实参盲区）任一为真都算"隐藏参数嫌疑"
        features.add(FEATURE_HIDDEN_PARAM_SUSPICION)

    # --- 参数分段（面向输出；callee 侧只给等价类候选集合） ---
    if arg_slots is not None:
        param_slot_seq = sorted(set(range(arg_slots)) | reads_rel | qw_rel
                                | {q + 1 for q in qw_rel})
        param_slot_seq = [s for s in param_slot_seq if 0 <= s < arg_slots]
    else:
        param_slot_seq = sorted(set(reads_rel) | qw_rel | {q + 1 for q in qw_rel})
    groups = _segment_params(param_slot_seq, qw_rel) if param_slot_seq else []
    params = [ParamCandidate(slots=size,
                             class_candidates=frozenset(
                                 _param_class_candidates(scan, start + shift, size)))
              for start, size in groups]
    for _ in range(reg_arg_count):        # 寄存器实参（fastcall 的 edx）排在最前
        params.insert(0, ParamCandidate(slots=1, class_candidates=frozenset(DWORD_AMBIGUOUS)))
    param_class_undetermined = any(not p.determined for p in params)
    if param_class_undetermined:
        features.add(FEATURE_AMBIGUOUS_PARAM_CLASS)
        notes.append('ambiguous_param_class: callee 字节分不出 int/指针/float/BOOL 等等价类'
                     '（C-5/C-6）⇒ A 级只保证"约定+个数+返回宽度"，参数类型须调用点/IDA 证据')

    # --- 调用点旁证（只对账，不覆盖 callee 结论） ---
    call_site_consistent = None
    if ev.call_sites:
        expected = None
        if callee_clean and arg_slots is not None:
            expected = arg_slots
        elif this_on_stack and arity is not None:
            expected = arity + 1
        if expected is not None:
            for site in ev.call_sites:
                sites = analyze_call_sites(site) if isinstance(site, str) else (site,)
                for s in sites:
                    call_site_consistent = (s.push_count == expected)
                    if not call_site_consistent:
                        features.add(FEATURE_CALL_SITE_MISMATCH)
                        notes.append('call_site_mismatch: 调用点 push=%d ≠ callee 期望栈槽 %d'
                                     '（旁证不符，需 IDA 定性）' % (s.push_count, expected))
                    break
                if call_site_consistent is not None:
                    break

    # --- 分级 ---
    if arity is None or cc == CC_UNKNOWN:
        grade = GRADE_C
    elif (hidden or scan.sret_ambiguous or ret_kind == RET_UNKNOWN
          or cc_provisional or arity_is_lower or report.partially_parsed):
        # `report.partially_parsed`（I3 修复轮 R=1）：>50% 非空行没解析成指令 ⇒
        # 指令层证据不完整，notes 说"不可信"就不能同时给 A
        grade = GRADE_B
    else:
        grade = GRADE_A

    return SignatureCandidate(
        addr=ev.addr, name=name, symbol=ev.symbol,
        signature=_signature_text(name, cc, ret_kind, params, variadic),
        convention=cc, arity=arity, return_kind=ret_kind, params=tuple(params),
        variadic=variadic, grade=grade, features=frozenset(features), notes=tuple(notes),
        ret_bytes=scan.ret_bytes, bare_ret=scan.bare_ret,
        stack_slots=raw_stack_slots if raw_stack_slots is not None else len(scan.reads),
        read_slots=len(scan.reads), reg_arg_count=reg_arg_count,
        this_on_stack=this_on_stack, param_class_undetermined=param_class_undetermined,
        hidden_param_suspicion=hidden, arity_is_lower_bound=arity_is_lower,
        cc_provisional=cc_provisional, call_site_consistent=call_site_consistent,
        slot_kind=kind)


# ---------------- ICF 分组 / 一地址多候选 ----------------

def body_key(text):
    """反汇编文本的**规范化体键**（ICF 同体判定；与地址/符号无关）。

    对 Task 2 的 PE-COFF 重定位行缺口免疫（见 `sanitize_pe_relocs`）。
    """
    if isinstance(text, str):
        insns = _safe_parse(text)[0].insns
    else:
        insns = tuple(text)
    out = []
    for ins in insns:
        ops = tuple((o.kind, o.reg, o.base, o.index, o.scale, o.disp) for o in ins.ops)
        out.append((ins.mnem, ops))
    return tuple(out)


def find_icf_groups(entries):
    """{key: disasm} → 同体组（组长 ≥2），组内按 key 排序；组间按首键排序。确定性。

    C-5：e1.cpp 的 `o(int)/o(void*)/o(float)` 三个空体**字节完全相同**，链接期 ICF 折叠
    后**一地址对多签名** ⇒ 任何"按地址给唯一签名"的写法都会写错等价类。
    """
    buckets = {}
    for key, text in entries.items():
        buckets.setdefault(body_key(text), []).append(key)
    groups = [tuple(sorted(v)) for v in buckets.values() if len(v) > 1]
    groups.sort(key=lambda g: g[0])
    return tuple(groups)


def _cap_grade(cand, floor):
    """把候选降级到至多 `floor`（A<B<C 的"确定度"序：A 最高）。"""
    order = {GRADE_A: 0, GRADE_B: 1, GRADE_C: 2}
    if order[cand.grade] >= order[floor]:
        return cand
    return replace(cand, grade=floor,
                   notes=cand.notes + ('grade_capped: 同地址存在多签名（ICF 折叠 / 多次声明）'
                                       '⇒ 不得给 A 级',))


def infer_address_record(addr, evidences):
    """一个**地址**的全部证据 → `PendingRecord`（多候选 + ICF 标记）。

    C-5 契约：`methods_pending[addr]` 的键值**必须**能放多签名（列表）；
    **只要候选数 > 1** 就降级到 B 并标 `ambiguous`（I4 修复轮 R=1：旧实现只在
    `distinct_bodies == 1`（ICF）时降级，体不同的多候选仍会给 A ⇒ 同样不得给 A）。
    """
    evidences = tuple(evidences)
    cands = []
    for ev in evidences:
        c = infer_signature(ev)
        if c is not None:
            cands.append(c)
    cands.sort(key=lambda c: (c.symbol, c.name, c.signature))
    keys = [body_key(ev.disasm) for ev in evidences if isinstance(ev.disasm, str)]
    distinct_bodies = set(keys)
    icf = len(evidences) > 1 and len(distinct_bodies) == 1
    if len(cands) > 1:
        cands = [_cap_grade(c, GRADE_B) for c in cands]
    notes, features = [], set()
    if icf:
        features.add(FEATURE_ICF_FOLDED)
        notes.append('icf_folded: 同地址 %d 个符号共享**完全相同**的函数体 ⇒ ICF 折叠；'
                     '一地址对多签名 ⇒ 必须由 IDA/调用点证据定性' % len(evidences))
    elif len(cands) > 1:
        notes.append('multi_candidate: 同地址 %d 个候选（函数体**不同**，非 ICF 折叠）⇒ '
                     '一地址对多签名同样不得给 A 级，须由 IDA/调用点证据定性' % len(cands))
    skipped = not cands and bool(evidences)
    if skipped:
        features.add(FEATURE_SKIPPED_SYNTHETIC_SLOT)
        notes.append('skipped_synthetic_slot: 该地址是合成槽（adjustor/删除器/纯虚/复合）'
                     '⇒ 签名推断跳过，声明映射归 Task 5 §2.1 表')
    kinds = {c.slot_kind for c in cands} or {KIND_FN}
    return PendingRecord(addr=addr, candidates=tuple(cands), icf_folded=icf,
                         ambiguous=bool(icf or len(cands) > 1), skipped=skipped,
                         slot_kind=sorted(kinds)[0], features=frozenset(features),
                         notes=tuple(notes))


# ---------------- methods_pending 旁路（绝不写 methods） ----------------

def _addr_key(addr):
    """地址键归一（'0x401000' / '401000h' / int 皆可）；不可解析则原样。"""
    if isinstance(addr, int):
        return '0x%08X' % addr
    s = str(addr).strip()
    try:
        if s.lower().endswith('h'):
            return '0x%08X' % int(s[:-1], 16)
        return '0x%08X' % int(s, 16)
    except (TypeError, ValueError):
        return s


def build_methods_pending(struct_data, records):
    """把候选写进**旁路字段** `methods_pending`，`methods` 真相源**逐字不动**。

    * 返回**新字典**（`copy.deepcopy` 输入），调用方持有的原对象不被修改；
    * 同一地址多候选 ⇒ 列表（C-5）；
    * 与已存在的 `methods[addr]` 签名冲突 ⇒ 只记 `conflicts`（旁路），永不覆盖真相源。
    """
    out = copy.deepcopy(struct_data) if isinstance(struct_data, dict) else {}
    methods = out.get('methods') if isinstance(out.get('methods'), dict) else {}
    existing = {}
    for k, v in methods.items():
        existing[_addr_key(k)] = v
    pending = {}
    for rec in records:
        key = _addr_key(rec.addr)
        conflicts = []
        prev = existing.get(key)
        if isinstance(prev, dict) and prev.get('signature'):
            cand_sigs = {c.signature for c in rec.candidates}
            if cand_sigs and prev['signature'] not in cand_sigs:
                conflicts.append('truth-source methods[%s].signature = %r 与候选 %s 不一致；'
                                 '旁路不覆盖，交 IDA 定性'
                                 % (key, prev['signature'], sorted(cand_sigs)))
        entry = rec.to_dict()
        entry['conflicts'] = conflicts
        pending[key] = entry
    out['methods_pending'] = pending
    return out


def iter_candidates(pending_or_struct):
    """Task 5 消费用：yield (addr, candidate_dict)（跳过无候选的合成槽记录）。"""
    pending = (pending_or_struct.get('methods_pending')
               if isinstance(pending_or_struct, dict) and 'methods_pending' in pending_or_struct
               else pending_or_struct) or {}
    for addr in pending:
        for cand in pending[addr].get('candidates', ()):
            yield addr, cand


# ---------------- CLI（只读输入 → 只写 --out 旁路文件） ----------------

def _slots_from_json(data):
    if isinstance(data, dict) and 'slots' in data:
        slots = data['slots']
    elif isinstance(data, list):
        slots = data
    else:
        slots = [data]
    evs = []
    for s in slots:
        if isinstance(s, str):
            evs.append(SigEvidence(disasm=s))
            continue
        evs.append(SigEvidence(
            addr=s.get('addr', ''), name=s.get('name', ''), symbol=s.get('symbol', ''),
            disasm=s.get('disasm', ''), signature=s.get('signature', ''),
            slot_kind=s.get('slot_kind', ''),
            is_member=s.get('is_member', True), is_external=s.get('is_external', False),
            external_symbol=s.get('external_symbol', ''),
            call_sites=tuple(s.get('call_sites', ()) or ())))
    return evs


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    if not argv or '--help' in argv or '-h' in argv:
        sys.stdout.write(__doc__ + '\n')
        return 0
    src = out = None
    i = 0
    while i < len(argv):
        if argv[i] == '--slots' and i + 1 < len(argv):
            src = argv[i + 1]
            i += 2
        elif argv[i] == '--out' and i + 1 < len(argv):
            out = argv[i + 1]
            i += 2
        elif argv[i] == '--struct' and i + 1 < len(argv):
            src = argv[i + 1]
            i += 2
        else:
            raise SystemExit('未知参数 %r（--help 看用法）' % argv[i])
    if not src:
        raise SystemExit('必须给 --slots <json>')
    with open(src, encoding='utf-8') as fh:
        data = json.load(fh)
    evs = _slots_from_json(data)
    by_addr = {}
    for ev in evs:
        by_addr.setdefault(_addr_key(ev.addr), []).append(ev)
    records = [infer_address_record(addr, by_addr[addr]) for addr in sorted(by_addr)]
    payload = build_methods_pending({'methods': {}}, records)
    text = json.dumps(payload, ensure_ascii=False, indent=1, sort_keys=False)
    if out:
        if os.path.abspath(out).startswith(os.path.abspath(
                os.path.join(_HERE, '..', 'data', 'annotations'))):
            raise SystemExit('拒绝写入真相源目录 data/annotations（本工具只产出旁路候选）')
        with open(out, 'w', encoding='utf-8') as fh:
            fh.write(text + '\n')
        n = sum(len(r.candidates) for r in records)
        sys.stdout.write('[vtable_sig_infer] %d 地址 / %d 候选 → %s\n'
                         % (len(records), n, out))
    else:
        sys.stdout.write(text + '\n')
    return 0


if __name__ == '__main__':
    sys.exit(main())