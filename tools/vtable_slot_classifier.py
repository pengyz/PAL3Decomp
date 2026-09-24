#!/usr/bin/env python3
"""vtable **合成槽分类器**（槽内容 → kind）—— 只认二进制可观测形态。

回答一个问题：**vtable 某槽指向的地址，其槽内容是哪一种？** 词表 6 种（与 Task 1
`vtable_slot_order.SYNTHETIC_KINDS` 兼容）：

    fn              普通函数（默认）
    deleting_dtor   虚析构删除器
    adjustor_static 静态 this 调整 thunk
    adjustor_vbase  虚基类动态调整 thunk
    purecall        纯虚占位（CRT stub）
    composite       复合槽（多种特征同时命中 ⇒ 需 IDA 人工定性）

## 识别特征（全部来自**原始指令字节**反汇编 + 地址特征；禁止 decomp JSON、不解析 mangling）

| kind | 特征 | 备注 |
|---|---|---|
| `fn` | 普通函数序言 | 默认 |
| `deleting_dtor` | 与 `??_G` 共享地址（`??_G`/`??_E` 弱别名同址）+ 签名 `void*(unsigned)` | IDA 可见共享地址 |
| `adjustor_static` | `add/sub imm; jmp` 序言，**仅 ecx 操作数** | 排除 import thunk / 增量链接 thunk / 参数转发包装器 |
| `adjustor_vbase` | `sub -N(%ecx),%ecx; jmp` 或 vbtable 间接调整 | 动态 delta |
| `purecall` | 指向 CRT stub 地址（链接后 `__purecall`） | 外部符号 |
| `composite` | 多种特征同时命中 | 需 IDA 人工定性 |

三条判据约定（测试逐条钉死）：

 * **deleting_dtor 的证据优先级**：`??_G`/`??_E` 共享地址（主）→ 签名缺失仍判但留"未确认"痕迹
   → 签名**已知且矛盾**则不判（留"矛盾"痕迹）→ 无符号证据时才允许**形态推断**（扩展判据：
   签名 `void*(unsigned)` + `and r,1; test; 条件跳过含 call 的释放块` 骨架，留"形态推断"痕迹）。
   形态推断只在符号证据缺席时生效，**不改变**任何有符号证据样本的结论。
 * **adjustor 的排除项**（简报明列）：`j_*`/`__imp_*` import thunk 家族、尾部**间接** jmp、
   增量链接 thunk（栈/帧操作，如 `mov %edi,%edi; push $t; jmp`）、参数转发包装器
   （跳转前动栈/非 ecx 操作数）⇒ 一律不判 adjustor_*，并留"排除"痕迹。
 * **composite** = 命中 ≥2 个特征（deleting_dtor × adjustor_* × 常量/动态 delta 混合链），
   无自动 kind 可归，`needs_manual_review` 恒为 True（attack README B-1 的混合槽）。

用法：
    ev  = SlotEvidence(symbols=('??_GV@@..', '??_EV@@..'), signature='void*(unsigned)',
                       instructions=parse_disasm(objdump_text))
    res = classify_slot(ev)          # SlotClassification(kind, features, notes)
    res.kind                        # 'deleting_dtor'
    res.slot_order_kind             # 'deleting_dtor'（喂 Task 1 SlotEntry.kind；'fn'→'func'）
"""
import re
from dataclasses import dataclass, field

__all__ = [
    'KIND_FN', 'KIND_DELETING_DTOR', 'KIND_ADJUSTOR_STATIC', 'KIND_ADJUSTOR_VBASE',
    'KIND_PURECALL', 'KIND_COMPOSITE', 'ALL_KINDS',
    'FEATURE_DELETING_DTOR', 'FEATURE_ADJUSTOR_STATIC', 'FEATURE_ADJUSTOR_VBASE',
    'FEATURE_PURECALL', 'ALL_FEATURES',
    'Operand', 'Insn', 'ParseReport', 'SlotEvidence', 'SlotClassification',
    'parse_disasm', 'parse_disasm_report', 'normalize_signature',
    'is_deleting_dtor_signature', 'normalize_kind', 'slot_order_kind', 'classify_slot',
]

KIND_FN = 'fn'
KIND_DELETING_DTOR = 'deleting_dtor'
KIND_ADJUSTOR_STATIC = 'adjustor_static'
KIND_ADJUSTOR_VBASE = 'adjustor_vbase'
KIND_PURECALL = 'purecall'
KIND_COMPOSITE = 'composite'
ALL_KINDS = (KIND_FN, KIND_DELETING_DTOR, KIND_ADJUSTOR_STATIC,
             KIND_ADJUSTOR_VBASE, KIND_PURECALL, KIND_COMPOSITE)

FEATURE_DELETING_DTOR = 'deleting_dtor'
FEATURE_ADJUSTOR_STATIC = 'adjustor_static'
FEATURE_ADJUSTOR_VBASE = 'adjustor_vbase'
FEATURE_PURECALL = 'purecall'
ALL_FEATURES = (FEATURE_DELETING_DTOR, FEATURE_ADJUSTOR_STATIC,
                FEATURE_ADJUSTOR_VBASE, FEATURE_PURECALL)

DELETING_DTOR_SIG = 'void*(unsigned)'


# ---------------- 词表对接（Task 1 `vtable_slot_order.KIND_FUNC == 'func'`） ----------------

def normalize_kind(kind):
    """Task 1 词面（'func'）与本模块词面（'fn'）互认；未知词面拒绝。"""
    k = KIND_FN if kind == 'func' else kind
    if k not in ALL_KINDS:
        raise ValueError('未知槽型 %r（词表 %s）' % (kind, list(ALL_KINDS)))
    return k


def slot_order_kind(kind):
    """本模块 kind → Task 1 `SlotEntry.kind` 词面（'fn' → 'func'，其余原样）。"""
    k = normalize_kind(kind)
    return 'func' if k == KIND_FN else k


# ---------------- 签名归一（只做书写差异归一，不做语义推断） ----------------

_SIG_NOISE = re.compile(
    r'\b(virtual|__thiscall|__cdecl|__stdcall|__fastcall|__unaligned|thiscall|cdecl|'
    r'stdcall|fastcall|__formal)\b', re.I)


def _split_top(text):
    out, depth, cur = [], 0, []
    for ch in text:
        if ch in '([<':
            depth += 1
        elif ch in ')]>':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(''.join(cur)); cur = []
        else:
            cur.append(ch)
    out.append(''.join(cur))
    return out


def _strip_param_names(params):
    out = []
    for p in _split_top(params):
        p = re.sub(r'([*&])\s*([A-Za-z_]\w*)', r'\1 \2', p)        # char *name → char * name
        p = re.sub(r'([\w*&])\s+([A-Za-z_]\w*)\s*$', r'\1', p)     # 尾部参数名剥掉
        out.append(p)
    return ','.join(out)


def normalize_signature(sig):
    """签名文本归一到 `ret(param,...)` 规范形（如 `void*(unsigned)`）。

    去掉调用约定 / 类限定 / 成员指针记号 `(*)` / 参数名 / `unsigned int`→`unsigned` 等书写差异。
    显式 this 形（IDA `void *(__thiscall void *this, unsigned int flags)`）保留首参。
    """
    s = ' '.join(sig.split())
    if not s:
        return ''
    s = _SIG_NOISE.sub(' ', s)
    s = re.sub(r'\b[A-Za-z_]\w*\s*::\s*', '', s)      # 类限定 / 成员指针类名
    s = re.sub(r'\(\s*\*\s*\)', '', s)                # 成员指针记号 (C::*)
    s = re.sub(r'\bunsigned\s+int\b', 'unsigned', s, flags=re.I)
    open_idx, close_idx = s.find('('), s.rfind(')')
    if open_idx >= 0 and close_idx > open_idx:
        s = (s[:open_idx + 1] + _strip_param_names(s[open_idx + 1:close_idx]) + s[close_idx:])
    return re.sub(r'\s+', '', s)


def is_deleting_dtor_signature(sig):
    """签名 ≡ `void*(unsigned)`（含 IDA 显式 this 形 `void*(void*,unsigned)`）？"""
    n = normalize_signature(sig)
    return n in (DELETING_DTOR_SIG, 'void*(void*,%s)' % 'unsigned')


# ---------------- 反汇编指令模型（AT&T / Intel 皆可，规范成 dst/src 序） ----------------

_REG_RE = re.compile(r'^(?:e?[abcd]x|[abcd][hl]|e?(?:si|di|sp|bp)|ip|eip|cs|ds|es|fs|gs|ss|'
                     r'st(?:\(\d\))?|mm\d|xmm\d|cr\d|dr\d)$')
_MNEM_BASES = {'mov', 'add', 'sub', 'and', 'or', 'xor', 'cmp', 'test', 'lea', 'push', 'pop',
               'inc', 'dec', 'neg', 'not', 'imul', 'mul', 'idiv', 'div', 'sal', 'sar', 'shl',
               'shr', 'jmp', 'call', 'xchg', 'movsx', 'movzx'}
_INTEL_SIZE = re.compile(r'\b(?:byte|word|dword|qword|fword|tbyte|oword|xmmword|mmword|ptr|'
                         r'short|near|far|large|small)\b', re.I)
_INT_RE = re.compile(r'^[-+]?0x[0-9a-fA-F]+$|^[-+]?\d+$|^[0-9a-fA-F]+h$', re.I)


def _norm_mnem(m):
    m = m.strip().lower()
    if m in ('retn', 'retf'):
        return 'ret'
    if len(m) > 2 and m[:-1] in _MNEM_BASES and m[-1] in 'bwlq':
        return m[:-1]
    return m


def _parse_int(text):
    t = text.strip().lower()
    sign = -1 if t.startswith('-') else 1
    t = t.lstrip('+-')
    if t.endswith('h'):
        v = int(t[:-1], 16)
    elif t.startswith('0x'):
        v = int(t, 16)
    else:
        v = int(t, 10)
    v *= sign
    # 32 位立即数的补码写法（`$0xfffffff8` = -8）按符号还原
    if v > 0x7FFFFFFF:
        v -= 0x100000000
    return v


def _is_reg(text):
    return bool(_REG_RE.match(text.strip().lower()))


def _parse_mem_expr(inner):
    """解析 `[ecx-4]` / `eax+ecx*4+8` 一类寻址 → (base, index, scale, disp)。"""
    base = index = ''
    scale = 0
    disp = 0
    for m in re.finditer(r'([+-]?)([^+-]+)', inner):
        sign, term = m.group(1), m.group(2).strip()
        if not term:
            continue
        sgn = -1 if sign == '-' else 1
        if '*' in term:
            a, b = [x.strip() for x in term.split('*', 1)]
            if _is_reg(a):
                index, scale = a, max(int(b, 0) if _INT_RE.match(b) else 1, 1)
            elif _is_reg(b):
                index, scale = b, max(int(a, 0) if _INT_RE.match(a) else 1, 1)
            else:
                disp += sgn * _parse_int(term)
        elif _is_reg(term):
            if not base:
                base = term
            else:
                index, scale = term, 1
        else:
            disp += sgn * _parse_int(term)
    return base, index, scale, disp


def _att_operand(text, branch):
    indirect = text.startswith('*')
    t = text[1:].strip() if indirect else text.strip()
    if t.startswith('$'):
        # `$` 后**非数字** ⇒ 未解析的符号引用（如裸文本 `push $SG240`：objdump 一般把它放在
        # 单独的重定位注释行里，但手抄/其他反汇编器可能内联）⇒ 回落 `other`。**不得抛异常**：
        # 一次 `_parse_int('sg240')` 会毁掉整段解析、抹掉该槽全部证据。
        body = t[1:].strip()
        if not _INT_RE.match(body):
            return Operand('other', text=text)
        return Operand('imm', value=_parse_int(body), text=text)
    if t.startswith('%'):
        return Operand('reg', reg=t[1:].split('(')[0].lower(), text=text)
    if t.endswith(')') and '(' in t:
        head, inner = t[:-1].split('(', 1)
        parts = [p.strip() for p in inner.split(',')]
        base = parts[0].lower().lstrip('%') if parts[0] else ''
        index = parts[1].lower().lstrip('%') if len(parts) > 1 and parts[1] else ''
        scale = int(parts[2]) if len(parts) > 2 and parts[2] else 0
        disp = _parse_int(head) if head not in ('', '+', '-') else 0
        return Operand('mem', base=base, index=index, scale=scale, disp=disp, text=text)
    if _INT_RE.match(t):
        v = _parse_int(t)
        if branch and not indirect:
            return Operand('target', value=v, text=text)
        return Operand('mem' if indirect else 'imm', value=v, disp=v, text=text)
    return Operand('target', text=text) if branch else Operand('other', text=text)


def _intel_operand(text, branch):
    t = _INTEL_SIZE.sub(' ', text.strip())
    t = re.sub(r'\b(?:ds|cs|ss|es|fs|gs)\s*:\s*', '', t, flags=re.I).strip()
    if t.startswith('*'):
        return _att_operand(t, branch)
    if t.startswith('[') and t.endswith(']'):
        base, index, scale, disp = _parse_mem_expr(t[1:-1])
        return Operand('mem', base=base, index=index, scale=scale, disp=disp, text=text)
    low = t.lower()
    if _is_reg(low):
        return Operand('reg', reg=low, text=text)
    if _INT_RE.match(t):
        v = _parse_int(t)
        if branch:
            return Operand('target', value=v, text=text)
        return Operand('imm', value=v, text=text)
    return Operand('target', text=text) if branch else Operand('other', text=text)


def _parse_operand(text, branch):
    t = text.strip()
    if t.startswith('%') or t.startswith('$') or t.startswith('*') or '(' in t and '%' in t:
        return _att_operand(t, branch)
    return _intel_operand(t, branch)


def _split_operands(text):
    out, depth, cur = [], 0, []
    for ch in text:
        if ch in '([<':
            depth += 1
        elif ch in ')]>':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(''.join(cur)); cur = []
        else:
            cur.append(ch)
    out.append(''.join(cur))
    return [o.strip() for o in out if o.strip()]


_OBJDUMP_LINE = re.compile(r'^\s*([0-9A-Fa-f]+):\s*(.*)$')
_OBJDUMP_HDR = re.compile(r'^\s*[0-9A-Fa-f]*\s*<[^>]*>:\s*$')
_NDISASM_LINE = re.compile(r'^\s*[0-9A-Fa-f]{4,}\s+[0-9A-Fa-f]{2,}\s\s+([A-Za-z].*)$')
_TEXT_LINE = re.compile(r'^\s*([A-Za-z][A-Za-z0-9._]*)\s*(.*)$')

# 重定位注释行：**无指令语义**，带不带 `offset:` 前缀都算。若被当指令解析，会抢占末位使尾 jmp
# 不再位于末位 ⇒ 真 adjustor thunk 被误判成静默 fn（零 notes）。两种书写形态：
#   1. GNU ELF：`objdump -dr` 的 `R_386_PC32 <sym>` / `R_IA64_PCREL21B <sym>` ⇒ `R_<ARCH>_<TYPE>`
#   2. PE-COFF：打印 howto **类型名**而非 `R_*` 前缀（binutils 2.38 pe-i386 实测，
#      MSVC 6.0 SP0 `/Od` 编译的 `_main`）：
#        `\t\t\t2f: dir32\t$SG240` / `\t\t\t37: DISP32\t?log@S@@UAEHPBDH@Z`
#      x86 PE 的字符串符号**带 `$` 前缀** ⇒ 被当指令解析时 `_att_operand('$SG240')`
#      → `_parse_int('sg240')` → `ValueError`（崩溃，非静默误判）。`off32` 为任务指定的第三
#      形态（本机 objdump 未发射，同族）；`secrel32` 实测存在于 libbfd-2.38 同名表。
#      这些名字不可能与任何 x86 助记符重名，故按名字家族通用匹配。
_RELOC_LINE = re.compile(
    r'^\s*(?:[0-9A-Fa-f]{1,16}:\s*)?'
    r'(?:R_[A-Za-z0-9_]+\b|(?i:dir32|disp32|off32|secrel32)\b)')

# IDA 粘贴形态的**地址列前缀**：`CODE:00401000 ` / `.text:00401000 ` / `00401000  `。
_IDA_ADDR_COL = re.compile(
    r'^(?:[A-Za-z_.$][A-Za-z0-9_.$]*:\s*)?(?:0x)?([0-9A-Fa-f]{4,16})(?=\s|$)')


def _strip_ida_addr_column(text):
    """剥 IDA 地址列前缀 → (剩余文本, 是否剥过)。

    纯十六进制字母词（如 x87 `fadd`，4 个 hex 字母）**不是**地址列 ⇒ 不剥，避免吞掉真指令。
    地址列可能重复（`CODE:00401000 00401000 sub …`），故循环剥到不再命中。
    """
    s = text.strip()
    matched = False
    while True:
        m = _IDA_ADDR_COL.match(s)
        if not m or not any(c.isdigit() for c in m.group(1)):
            return s, matched
        matched = True
        s = s[m.end():].lstrip()


def _split_objdump_rest(rest):
    """objdump 行的字节列与指令文本分离（指令文本首词不会是「2 位十六进制 + 空白」）。

    纯**数据**字节行（如 `  16:\\t00`、`  16:\\t00 00 00 00`，无指令文本）⇒ 返回 ''（视作
    纯字节续行跳过）。实测 PE-COFF 清单里这类行占比可到 ~4%，若计成"丢弃"会让数据密集的
    COMDAT 切片误报 `partially_parsed`。
    """
    s = rest.strip()
    while True:
        m = re.match(r'^[0-9A-Fa-f]{2}\s+', s)
        if not m:
            break
        s = s[m.end():].lstrip()
    if re.fullmatch(r'[0-9A-Fa-f]{2}', s):        # 末字节后无空白（整行皆字节）
        return ''
    return s


def _parse_insn_text(text):
    m = _TEXT_LINE.match(text.strip())
    if not m:
        return None
    mnem = _norm_mnem(m.group(1))
    ops_text = m.group(2).strip()
    branch = mnem.startswith('j') or mnem in ('call', 'loop', 'loope', 'loopne')
    op_texts = _split_operands(ops_text)
    # 语法判别：AT&T 有 %/$/* 或 disp(%reg)；其余按 Intel（dst,src 已是规范序）
    is_att = any(o.startswith(('%', '$', '*')) or ('(' in o and '%' in o) for o in op_texts)
    ops = tuple(_parse_operand(o, branch) for o in op_texts)
    if is_att and len(ops) == 2:
        ops = (ops[1], ops[0])            # AT&T (src,dst) → 规范 (dst,src)
    return Insn(mnem=mnem, ops=ops, raw=text.strip())


@dataclass(frozen=True)
class ParseReport:
    """反汇编文本的**解析完整性报告**（防"解析器静默失败"回流成静默 fn）。

    content_lines: 去掉空行/纯注释行后的**非空行数**（= 分母）
    parsed_lines:  成功解析出指令的行数
    skipped_lines: **有意跳过**的结构行（空行 / 节符号头 / 横幅 / 纯字节续行 / 重定位行 /
                   仅地址列行）——不算"丢弃"
    dropped_lines: 非空、非结构行，但**解析不出指令**的行（= 真丢弃）
    """
    insns: tuple = ()
    raw_lines: int = 0
    content_lines: int = 0
    parsed_lines: int = 0
    skipped_lines: int = 0
    dropped_lines: int = 0
    dropped_examples: tuple = ()

    @property
    def insufficient_evidence(self):
        """非空输入却一条指令都没解析出来 ⇒ 证据不足（不得静默回落 fn）。"""
        return self.content_lines > 0 and self.parsed_lines == 0

    @property
    def partially_parsed(self):
        """丢弃行占比 > 50% ⇒ 解析不完整，结论不可信。"""
        return self.content_lines > 0 and self.dropped_lines * 2 > self.content_lines


def parse_disasm_report(text):
    """解析反汇编文本 → `ParseReport`（指令 + 解析完整性计数）。

    逐行处理顺序（顺序即语义，改前先读"静默失败"三例）：
      1. 剥 `;` 行尾注释（IDA 语法；分号在字符串中的情形本场景忽略）
      2. 空行 / 节·符号头（冒号结尾）/ objdump 横幅 ⇒ **跳过**
      3. 重定位注释行（`R_386_*` / `R_IA64_*` …）⇒ **跳过**
      4. objdump 形态（`offset:` + 字节列）；纯字节续行/reloc 体 ⇒ 跳过
      5. ndisasm 形态（地址列 + 字节列 + 指令）
      6. 其余：剥 IDA 地址列前缀后解析（仅地址列行 ⇒ 跳过）
    解析不出指令的非结构行计入 `dropped_lines`（≥1 行即留痕，见 `classify_slot`）。
    """
    insns, examples = [], []
    raw_lines = content_lines = parsed = skipped = dropped = 0
    for raw in text.splitlines():
        raw_lines += 1
        line = raw.split(';', 1)[0]               # 1. `;` 注释剥离
        s = line.strip()
        if not s:
            skipped += 1
            continue
        content_lines += 1
        if (s.endswith(':') or _OBJDUMP_HDR.match(line)      # 2. 结构行
                or '文件格式' in s or 'file format' in s):
            skipped += 1
            continue
        if _RELOC_LINE.match(s):                  # 3. 重定位注释行
            skipped += 1
            continue
        m = _OBJDUMP_LINE.match(line)             # 4. objdump
        if m:
            body = _split_objdump_rest(m.group(2))
            if not body or _RELOC_LINE.match(body):   # 纯字节续行 / reloc 体
                skipped += 1
                continue
            ins = _parse_insn_text(body)
        else:
            m2 = _NDISASM_LINE.match(line)        # 5. ndisasm
            if m2:
                ins = _parse_insn_text(m2.group(1))
            else:                                 # 6. IDA 裸文本 / 地址列前缀
                body, _had_col = _strip_ida_addr_column(line)
                if not body:
                    skipped += 1                  # 仅地址列、无指令文本
                    continue
                ins = _parse_insn_text(body)
        if ins is not None:
            insns.append(ins)
            parsed += 1
        else:
            dropped += 1
            if len(examples) < 3:
                examples.append(s)
    return ParseReport(insns=tuple(insns), raw_lines=raw_lines, content_lines=content_lines,
                       parsed_lines=parsed, skipped_lines=skipped, dropped_lines=dropped,
                       dropped_examples=tuple(examples))


def parse_disasm(text):
    """解析反汇编文本 → tuple[Insn]（= `parse_disasm_report(text).insns`；完整性计数见报告）。

    接受三种逐字工具输出/手写形态：
      * objdump（AT&T）：`  0:\\t83 e9 08\\t\\tsub    $0x8,%ecx`（偏移 + 字节列 + 指令）
      * ndisasm（Intel）：`00000000  2B49FC            sub ecx,[ecx-0x4]`
      * IDA 裸文本：`sub     ecx, [ecx-4]`（可带 `CODE:00401000 ` / `00401000  ` 地址列前缀，
        可带 `;` 行尾注释）
    空行、节/符号/标签头（以冒号结尾的行）、objdump 横幅行、纯字节续行、**重定位注释行**
    （`R_386_PC32 <sym>` 等）一律跳过——这些行若被误解析成伪指令，会打断 thunk 调整链
    （端到端核对与"静默失败"三例实测均踩过）。
    """
    return parse_disasm_report(text).insns


def _as_insns_and_report(instructions):
    """→ (insns, ParseReport|None)。报告仅在文本输入时可得（已解析序列无线索可计）。"""
    if isinstance(instructions, str):
        report = parse_disasm_report(instructions)
        return report.insns, report
    return tuple(instructions), None


# ---------------- 特征判据 ----------------

def _is_dtor_symbol(name):
    """`??_G`（scalar deleting）/ `??_E`（vector deleting，弱别名同址）—— 只比符号名前缀。"""
    return name.startswith('??_G') or name.startswith('??_E')


def _is_purecall_name(name):
    return name.strip().lower().lstrip('_') == 'purecall'


def _import_symbol(symbols):
    for s in symbols:
        low = s.lower()
        if low.startswith('j_') or '__imp_' in low or '_imp__' in low or low.startswith('__imp__'):
            return s
    return None


def _is_dtor_shape(insns):
    """deleting dtor **形态骨架**（扩展判据，无符号证据时用）：

    `and r,1`（flags 低位）→ `test r,r` → 条件跳转跳过释放块，且全本体 ≥2 个 call
    （complete dtor 调用 + `operator delete` 调用）。真机实测 `??_GV@@UAEPAXI@Z` /
    `??_GD@@UAEPAXI@Z` / `??_GA@@UAEPAXI@Z`（c2.obj）四体同骨架。
    """
    if len([i for i in insns if i.mnem == 'call']) < 2:
        return False
    for i, ins in enumerate(insns):
        if ins.mnem != 'and' or len(ins.ops) != 2:
            continue
        if ins.ops[0].kind != 'reg' or ins.ops[1].kind != 'imm' or ins.ops[1].value != 1:
            continue
        reg = ins.ops[0].reg
        for j in range(i + 1, min(i + 5, len(insns))):
            nxt = insns[j]
            if (nxt.mnem == 'test' and len(nxt.ops) == 2
                    and all(o.kind == 'reg' and o.reg == reg for o in nxt.ops)):
                for k in range(j + 1, min(j + 3, len(insns))):
                    if insns[k].mnem.startswith('j') and insns[k].mnem != 'jmp':
                        return True
    return False


def _is_stack_or_frame_op(ins):
    if ins.mnem in ('push', 'pop', 'enter', 'leave'):
        return True
    return any(o.kind == 'mem' and o.base in ('esp', 'ebp', 'sp', 'bp') for o in ins.ops)


def _adjust_step(body, i):
    """识别一步 this 调整：静态（add/sub imm,%ecx）或动态（含 vbtable 间接两指令对）。"""
    ins = body[i]
    if ins.mnem in ('add', 'sub') and len(ins.ops) == 2 \
            and ins.ops[0].kind == 'reg' and ins.ops[0].reg == 'ecx':
        src = ins.ops[1]
        if src.kind == 'imm':
            return 'static', i + 1
        if src.kind == 'mem' and src.base == 'ecx':
            return 'vbase', i + 1
        if src.kind == 'mem' and src.base and i > 0:                 # delta 经 vbtable 中转
            prev = body[i - 1]
            if (prev.mnem == 'mov' and len(prev.ops) == 2 and prev.ops[0].kind == 'reg'
                    and prev.ops[0].reg == src.base):
                return 'vbase', i + 1
        if src.kind == 'reg' and i > 0:
            prev = body[i - 1]
            if (prev.mnem == 'mov' and len(prev.ops) == 2 and prev.ops[0].kind == 'reg'
                    and prev.ops[0].reg == src.reg):
                return 'vbase', i + 1
    if (ins.mnem == 'mov' and len(ins.ops) == 2 and ins.ops[0].kind == 'reg'
            and ins.ops[1].kind == 'mem' and ins.ops[1].base == 'ecx' and i + 1 < len(body)):
        nxt = body[i + 1]
        if (nxt.mnem in ('add', 'sub') and len(nxt.ops) == 2 and nxt.ops[0].kind == 'reg'
                and nxt.ops[0].reg == 'ecx'
                and ((nxt.ops[1].kind == 'mem' and nxt.ops[1].base == ins.ops[0].reg)
                     or (nxt.ops[1].kind == 'reg' and nxt.ops[1].reg == ins.ops[0].reg))):
            return 'vbase', i + 2
    return None


def _adjustor_candidate(insns, symbols=()):
    """整个函数体 = [调整链] + 尾部**直接** jmp ⇒ ('ok', {static|vbase})；
    否则命中简报排除项 ⇒ ('excluded', 原因)；非 thunk 形态 ⇒ (None, None)。"""
    if not insns or insns[-1].mnem != 'jmp':
        return None, None
    imp = _import_symbol(symbols)
    if imp:
        return 'excluded', 'import thunk（%s 属 j_*/__imp_* 家族）' % imp
    tail = insns[-1].ops[0] if insns[-1].ops else None
    if tail is None or tail.kind != 'target':
        return 'excluded', 'import thunk（尾部**间接** jmp）'
    body = insns[:-1]
    if any(_is_stack_or_frame_op(i) for i in body):
        return 'excluded', '增量链接 thunk / 参数转发包装器（栈/帧操作）'
    chain, i = set(), 0
    while i < len(body):
        step = _adjust_step(body, i)
        if step is None:
            return 'excluded', '参数转发包装器（跳转前存在非 this 调整指令 %r）' % (body[i].raw,)
        tag, i = step
        chain.add(tag)
    if not chain:
        return 'excluded', '纯 jmp 跳转（无 this 调整）'
    return 'ok', chain


# ---------------- 证据与结论 ----------------

@dataclass(frozen=True)
class Operand:
    """规范操作数。kind: reg | mem | imm | target | other"""
    kind: str
    reg: str = ''
    base: str = ''
    index: str = ''
    scale: int = 0
    disp: int = 0
    value: int = 0
    text: str = ''


@dataclass(frozen=True)
class Insn:
    """一条指令：mnem 归一小写（'retn'→'ret' 等），ops 为**规范序**（dst 在前）。"""
    mnem: str
    ops: tuple = ()
    raw: str = ''


@dataclass(frozen=True)
class SlotEvidence:
    """一个槽指向地址的**二进制可观测**证据（全部来自 IDA/反汇编，不来自 decomp JSON）。

    symbols:          同址符号集合（含弱别名；`??_G`/`??_E` 共享地址证据）
    signature:        函数签名文本（可空 = 证据缺失）
    instructions:     反汇编文本（str）或已解析的 Insn 序列
    is_external:      目标是外部符号/CRT stub（无本体）
    external_symbol:  外部符号名（如 '__purecall'）
    addr:             诊断用地址标签
    """
    symbols: tuple = ()
    signature: str = ''
    instructions: tuple = ()
    is_external: bool = False
    external_symbol: str = ''
    addr: str = ''


@dataclass(frozen=True)
class SlotClassification:
    """分类结论：kind + 命中特征集合 + 证据/排除痕迹（Task 5 诊断用）。"""
    kind: str
    features: frozenset = field(default_factory=frozenset)
    notes: tuple = ()

    @property
    def is_composite(self):
        return self.kind == KIND_COMPOSITE

    @property
    def needs_manual_review(self):
        """composite 无自动 kind 可归 ⇒ 必须 IDA 人工定性。"""
        return self.kind == KIND_COMPOSITE

    @property
    def slot_order_kind(self):
        return slot_order_kind(self.kind)


def _example_suffix(report):
    """丢弃行的示例后缀（诊断用，最多 3 条在报告里，这里取首条）。"""
    if not report.dropped_examples:
        return ''
    return '，如 %r' % (report.dropped_examples[0],)


def classify_slot(evidence):
    """按二进制可观测形态分类槽内容 → SlotClassification。

    特征集合命中 0 条 = fn；1 条 = 该特征同名词面；≥2 条 = composite（需人工定性）。
    """
    insns, report = _as_insns_and_report(evidence.instructions)
    names = tuple(evidence.symbols) + ((evidence.external_symbol,) if evidence.external_symbol else ())
    notes, features = [], set()

    # --- purecall：CRT stub / 外部符号 ---
    for n in names:
        if _is_purecall_name(n):
            features.add(FEATURE_PURECALL)
            notes.append('purecall: 槽指向 CRT stub / 外部符号 %s' % n)
            break

    # --- deleting_dtor：与 ??_G 共享地址（主）→ 形态推断（扩展，仅在无符号证据时） ---
    sig_ok = bool(evidence.signature) and is_deleting_dtor_signature(evidence.signature)
    sig_norm = normalize_signature(evidence.signature)
    dtor_syms = [s for s in evidence.symbols if _is_dtor_symbol(s)]
    if dtor_syms:
        if not evidence.signature:
            features.add(FEATURE_DELETING_DTOR)
            notes.append('deleting_dtor: 与 ??_G/??_E 共享地址（%s）；签名证据缺失 ⇒ 未确认'
                         % ', '.join(dtor_syms))
        elif sig_ok:
            features.add(FEATURE_DELETING_DTOR)
            notes.append('deleting_dtor: 与 ??_G/??_E 共享地址（%s）+ 签名 %s'
                         % (', '.join(dtor_syms), sig_norm))
        else:
            notes.append('矛盾: 同址 %s 但签名 %s ≠ %s ⇒ 不判 deleting_dtor'
                         % (', '.join(dtor_syms), sig_norm or evidence.signature,
                            DELETING_DTOR_SIG))
    elif sig_ok and _is_dtor_shape(insns):
        features.add(FEATURE_DELETING_DTOR)
        notes.append('deleting_dtor: 形态推断（无 ??_G/??_E 符号证据）：签名 %s + '
                     '`and r,1` 条件释放骨架' % sig_norm)

    # --- adjustor：调整链 + 尾部直接 jmp（含简报三项排除） ---
    status, got = _adjustor_candidate(insns, evidence.symbols)
    if status == 'ok':
        if 'static' in got:
            features.add(FEATURE_ADJUSTOR_STATIC)
            notes.append('adjustor_static: `add/sub imm,%ecx; jmp` 序言（仅 ecx 操作数）')
        if 'vbase' in got:
            features.add(FEATURE_ADJUSTOR_VBASE)
            notes.append('adjustor_vbase: 动态 delta 调整 + 尾 jmp（vbtable 相对/间接）')
    elif status == 'excluded':
        notes.append('排除: %s ⇒ 不判 adjustor' % got)

    # --- kind 映射 ---
    if len(features) >= 2:
        kind = KIND_COMPOSITE
        notes.append('composite: 同时命中 %s ⇒ 需 IDA 人工定性' % ' + '.join(sorted(features)))
    elif features:
        kind = sorted(features)[0]
    else:
        kind = KIND_FN

    # --- 解析完整性痕迹：解析器静默失败不得回流成"静默 fn（零 notes）" ---
    if report is not None:
        if report.insufficient_evidence:
            notes.append('insufficient_evidence: %d 行非空反汇编文本解析出 0 条指令'
                         '（丢弃 %d 行%s）⇒ 证据不足，回落 fn 不可信，需 IDA 人工复核'
                         % (report.content_lines, report.dropped_lines,
                            _example_suffix(report)))
        elif report.partially_parsed:
            notes.append('partially_parsed: 丢弃 %d/%d 行非空反汇编文本（>50%%）⇒ 解析不完整，'
                         'kind=%s 结论不可信，需 IDA 人工复核%s'
                         % (report.dropped_lines, report.content_lines, kind,
                            _example_suffix(report)))
    return SlotClassification(kind=kind, features=frozenset(features), notes=tuple(notes))
