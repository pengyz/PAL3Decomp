#!/usr/bin/env python3
"""B 批 type-evidence v2：容器成员占位类型 → 二进制证据分级定型（dry-run 报告，--write 发守卫批次）。

## 为什么（2026-09-27 收官方案 B 批）
全局归属工程 A 批已收口，B 批要把"结构地基"变成"语义类型"：int 占位成员里
相当一部分真实类型是 float / char。仓规（docs/knowledge/
pattern_member_evidence_grading_by_disp32_scan.md）：类型可证到
**宽度 + int/float/指针 + 有/无符号**，证不到就不填；名字一律不动。

## 工作集（2026-09-27 对抗复核裁定，写死口径）
W = {(cls, off) | cls ∈ globals_partition.top_levels 的容器类型（type≠unknown）；
off ∈ structs/cls.json 的 known_members 键（'0x' 前缀按 16 进制、否则 10 进制）；
成员当前 type ∈ PLACEHOLDER_TYPES}。
- B2 census 行**不进工作集**（与 known_member 是同一批字节的两种视图），
  仅作旁证列（b2_ref：该偏移是否已被外部符号覆盖）。
- va 不是单值：多实例类（RoleSystem×5、PAL3×2、Array×4…）按**全部实例**取证。
- 同 offset 多键（'0x8' 与 '0x08'）显式报 dup，不静默覆盖。

## 证据源与已知盲区（2026-09-27 复核量化，勿夸大）
- **T1 二进制直接引用（A 级原料）**：成员绝对地址 LE4 在 .text 的命中 → 真实指令边界上的
  承载指令（纯绝对寻址 mem.disp / imm）→ 操作数宽度 + 运算类。
  ⚠️ 覆盖率实测：已知真实类型成员仅 25–30% 有 T1 证据；经容器指针的 this+off 访问
  **不出现成员绝对地址**（盲区 ~70%）。disp32(this+off) 形态（T1b）是后续扩展，
  本版如实计数、不假装全覆盖。
  ⚠️ imm 形态（mov ecx, 0xC05B10 / push offset）= 地址物化，kind='addr'，不参与定型；
  但 imm 位型若是合法 float 位型（如 0xC2480000 = −50.0f）会记 note 作旁证。
- **T2 反编译渲染佐证（B 级）**：成员名渲染点上下文的显式 cast。只佐证，不单独定型；
  词边界匹配，不计数投票（gotcha_member_name_voting_is_confounded_by_transitive_access）。

## 分级与动作（2026-09-27 复核裁决版）
| 级 | 条件 | 动作 |
|----|------|------|
| A  | 多站点一致（浮点族 / 带符号位的 byte/word）| --write 发守卫批次（float/char/short 族）|
| B  | 单站点 / 符号位不可证 / 仅 T2 / double（布局高危 v1 禁填）| 只报告 |
| C  | 真冲突（见下）| 报告 CONFLICT，不落盘 |
| 0  | 无证据 | 不动 |

**冲突判定（D4 裁决：浮点证据优先，避免误杀真实 float）**：
- float 族与 double 族同槽 ⇒ C；
- 浮点族与**整型运算**站点（fild/fist/fi*、add/sub/imul…）同槽 ⇒ C（fild/fist vs fld/fstp）；
- 整型站点宽度混用（1/2B vs 4B）⇒ C；
- 浮点族与 1/2B 整型触碰同槽 ⇒ C（疑位域/复用）；
- **mov dword / imm 触碰与浮点族兼容**（真实 float 成员几乎总被 mov/清零触碰——
  实测该旧规则误杀 3 个已确证 float）。
- kind=unknown 站点与任何定型证据混入 ⇒ C（未理解的证据不落盘）。

**double（int→double）v1 禁填**：唯一布局高危（emit_headers 尺寸台账 4→8 超前推进 +
MSVC6 x86 double 8 字节对齐），只报告。

## 落地链（D5/D6 裁决：唯一落盘口 + 生效链）
--write 只**产出守卫批次** data/status/type_evidence_batch.json（每条 evidence 指到
insn VA + 反汇编文本），由 tools/apply_annotation_batch.py（唯一落盘守卫，evidence
为空整批拒绝）落盘 ⇒ annotation_diff 归档 ⇒ **apply_annotations → export_full
（不回灌 IDB 则改注解根本不进生成头！）** ⇒ codegen ⇒ audit_type_layout --only
⇒ verify_fix --class ⇒ 四道门（布局等价 / loop --expect-errors 不增 / L1 不降 /
证据自校验）。

## 用法
  python tools/type_evidence.py                  # dry-run：报告 data/status/type_evidence_report.json
  python tools/type_evidence.py --write          # 产出守卫批次（不直接改注解）
  python tools/type_evidence.py --cls CEffMgr    # 只跑一个类（调试）
  python tools/type_evidence.py --write --batch-out X.json
"""
import argparse
import json
import os
import re
import struct
import sys
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
DECOMP = os.path.join(ROOT, 'asm', 'pal3', 'decomp')
CENSUS = os.path.join(ROOT, 'data', 'status', 'globals_census.json')
PARTITION = os.path.join(ROOT, 'data', 'status', 'globals_partition.json')
STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')
REPORT = os.path.join(ROOT, 'data', 'status', 'type_evidence_report.json')
BATCH_OUT = os.path.join(ROOT, 'data', 'status', 'type_evidence_batch.json')

PLACEHOLDER_TYPES = {'int', 'unsigned int', '_DWORD', '__int32', 'unsigned __int32'}
# 可落盘的新类型（double 布局高危 v1 禁填；指针需数据流证明 v1 不做）
FILL_BY_WIDTH = {
    (1, 'unsigned'): 'unsigned char',
    (1, 'signed'): 'char',
    (2, 'unsigned'): 'unsigned short',
    (2, 'signed'): 'short',
}
FILLABLE = set(FILL_BY_WIDTH.values()) | {'float'}

# x87 实数内存操作数（float/double 证据）与 x87 整型内存操作数（fi* / fild/fist，int 证据）
X87_REAL = {
    'fld', 'fst', 'fstp', 'fadd', 'faddp', 'fsub', 'fsubp', 'fsubr', 'fsubrp',
    'fmul', 'fmulp', 'fdiv', 'fdivp', 'fdivr', 'fdivrp', 'fcom', 'fcomp', 'fcompp', 'ftst',
}
X87_INT = {
    'fiadd', 'fisub', 'fisubr', 'fimul', 'fidiv', 'fidivr',
    'fild', 'fist', 'fistp', 'ficom', 'ficomp',
}
SSE_FLOAT = {'movss', 'addss', 'subss', 'mulss', 'divss', 'comiss', 'ucomiss',
             'cvtss2sd', 'cvttss2si'}
SSE_DOUBLE = {'movsd', 'addsd', 'subsd', 'mulsd', 'divsd', 'comisd', 'ucomisd',
              'cvtsd2ss', 'cvttsd2si'}
SSE_INT_READ = {'cvtsi2ss', 'cvtsi2sd'}        # 内存操作数是整型
SIGN_UNSIGNED = re.compile(r'^(movzx|movzbl|movzwl)$')
SIGN_SIGNED = re.compile(r'^(movsx|movsbl|movswl)$')   # 不得用 ^movs——movss/movsd 是 SSE 浮点
# 整型**运算**站点（与浮点族构成真冲突）；mov/清零/比较等只是"触碰"（兼容）
INT_OP = {
    'add', 'adc', 'sub', 'sbb', 'and', 'or', 'xor', 'inc', 'dec', 'neg', 'not',
    'imul', 'mul', 'idiv', 'div', 'shl', 'shr', 'sar', 'rol', 'ror', 'rcl', 'rcr',
    'shld', 'shrd', 'bsf', 'bsr', 'bt', 'bts', 'btr', 'btc', 'xadd', 'cmpxchg',
} | X87_INT


# ---------------------------------------------------------------- PE / 取证基座

def exe_text_image():
    """原始 exe 的 (data, va2off, sections)，节界取 max(vsz,rsz)
    （gotcha_pe_section_extent_max_vsz_rsz）。"""
    data = open(EXE, 'rb').read()
    e_lfanew = struct.unpack_from('<I', data, 0x3c)[0]
    nsec = struct.unpack_from('<H', data, e_lfanew + 6)[0]
    optsz = struct.unpack_from('<H', data, e_lfanew + 20)[0]
    sect = e_lfanew + 24 + optsz
    imagebase = struct.unpack_from('<I', data, e_lfanew + 24 + 28)[0]
    sections = []
    for s in range(nsec):
        h = sect + s * 40
        name = data[h:h + 8].rstrip(b'\x00').decode('ascii', 'replace')
        vsz, vaddr, rsz, roff = struct.unpack_from('<IIII', data, h + 8)
        sections.append((name, imagebase + vaddr, max(vsz, rsz), roff))

    def va2off(va):
        for _, vaddr, ext, roff in sections:
            if vaddr <= va < vaddr + ext:
                return roff + (va - vaddr)
        return None
    return data, va2off, sections


def text_span(sections):
    for name, vaddr, ext, roff in sections:
        if name == '.text':
            return vaddr, ext, roff
    raise SystemExit('no .text section')


def load_func_ranges(decomp_dir=None):
    """decomp 语料的 (va, size) 函数区间（指令边界表的种子）。"""
    decomp_dir = decomp_dir or DECOMP
    out = []
    for f in sorted(os.listdir(decomp_dir)):
        if not f.endswith('.json'):
            continue
        try:
            d = json.load(open(os.path.join(decomp_dir, f), encoding='utf-8'))
        except Exception:
            continue
        va_s, size = d.get('address'), int(d.get('size_bytes') or 0)
        if not va_s or size <= 0:
            continue
        out.append((int(va_s, 16), size))
    return out


def build_boundaries(data, va2off, func_ranges, md=None):
    """逐函数线性反汇编 → 真实指令起点集合（D2：错位解码的疫苗）。
    函数起点可信 ⇒ 区间内线性反汇编不会漂移。"""
    import capstone
    if md is None:
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    bounds = set()
    for va, size in func_ranges:
        off = va2off(va)
        if off is None:
            continue
        for ins in md.disasm(data[off:off + size], va):
            bounds.add(ins.address)
    return bounds


# ---------------------------------------------------------------- T1 指令级引用

class Ref(object):
    __slots__ = ('va', 'insn_va', 'mnemonic', 'op_str', 'op_size', 'kind', 'sign', 'note')

    def __init__(self, va, insn_va, mnemonic, op_str, op_size, kind, sign, note=''):
        self.va = va
        self.insn_va = insn_va
        self.mnemonic = mnemonic
        self.op_str = op_str
        self.op_size = op_size
        self.kind = kind          # 'float' | 'double' | 'int' | 'addr' | 'unknown'
        self.sign = sign          # 'unsigned' | 'signed' | None
        self.note = note          # 'disp' | 'imm' | 'imm-float-bits' | 'ambiguous:<n>'

    def as_dict(self):
        return {'insn_va': '0x%08X' % self.insn_va, 'mnemonic': self.mnemonic,
                'op_str': self.op_str, 'op_size': self.op_size, 'kind': self.kind,
                'sign': self.sign, 'note': self.note}


def classify_insn(mnemonic, op_size, is_imm=False):
    """(kind, sign)。契约（2026-09-27 复核裁决）：
    - is_imm=True / lea ⇒ 'addr'（地址物化，永不参与定型）；
    - fi*（fiadd/fimul/fidiv/fild/fist/ficom…）= **整型**内存操作数 ⇒ 'int'（D3）；
    - x87 实数/SSE 浮点按宽度 float(4)/double(8)，其余宽度 unknown；
    - setcc 不证符号位（F10）；op_size==0 ⇒ unknown（F15）。"""
    if is_imm or mnemonic.lower() == 'lea':
        return 'addr', None
    m = mnemonic.lower()
    sign = None
    if SIGN_UNSIGNED.match(m):
        sign = 'unsigned'
    elif SIGN_SIGNED.match(m):
        sign = 'signed'
    if op_size == 0:
        return 'unknown', sign
    if m in X87_INT:
        return 'int', sign          # fi* / fild/fist 读整型内存，按宽度定宽
    if m in X87_REAL:
        if op_size == 4:
            return 'float', sign
        if op_size == 8:
            return 'double', sign
        return 'unknown', sign      # tbyte 等：不证
    if m in SSE_FLOAT and op_size == 4:
        return 'float', sign
    if m in SSE_DOUBLE and op_size == 8:
        return 'double', sign
    if m in SSE_INT_READ:
        return 'int', sign
    return 'int', sign


def _op_value(op, X86_OP_MEM, X86_OP_IMM):
    """返回 (value, is_imm)；非 mem/imm 操作数、或 mem 带 base/index ⇒ (None, False)。
    [reg+disp] 是 this-relative 形态，disp==VA 不构成绝对地址证据（F4）。"""
    if op.type == X86_OP_IMM:
        return op.imm & 0xFFFFFFFF, True
    if op.type == X86_OP_MEM:
        if op.mem.base or op.mem.index:      # capstone: INVALID_REG == 0
            return None, False
        return op.mem.disp & 0xFFFFFFFF, False
    return None, False


def _float_bits(val):
    """imm 位型是否像**常见量级**的 float——只作旁证 note。
    P2（复核 5560c6c5）：旧判据 0<exp<0xFF 对随机 32 位值通过率 99.2%（数据段地址也
    "像 float"，`push 0x00C05B10` 即造出误导旁证）⇒ 收紧到 exp∈[0x20,0xEF]
    （|v|≈1e-19..1e19，覆盖 -50.0f=0xC2480000/exp0x84 等游戏常量；本二进制地址 exp≤3 排除）。"""
    exp = (val >> 23) & 0xFF
    return 0x20 <= exp <= 0xEF


def decode_refs_at(blob, text_va, h_off, target_va, md, ops_consts,
                   boundaries=None, window=15):
    """命中点 h_off（**blob 相对偏移**，D1：缓冲与偏移基必须同源）的承载指令。
    从 h-window+1..h 逐点单指令解码，收集「覆盖 [h, h+4) 且操作数 == target_va」的解码：
    - boundaries（真实指令起点集合）非 None ⇒ 只接受边界上的解码（D2）；
      无边界过滤时要求**唯一**解码，多解码 = 歧义 ⇒ 不作证据（D2/F5）；
    - 同一指令 mem+imm 双命中 ⇒ **mem 优先**（disp 侧才是宽度证据，F5）。
    返回 (Ref | None, n_decodes)。"""
    X86_OP_MEM, X86_OP_IMM = ops_consts
    hits = {}          # insn_va -> Ref（mem 优先于 imm）
    for start in range(max(0, h_off - window + 1), h_off + 1):
        va_s = text_va + start
        if boundaries is not None and va_s not in boundaries:
            continue
        try:
            ins_list = list(md.disasm(blob[start:start + window], va_s, count=1))
        except Exception:
            continue
        if not ins_list:
            continue
        ins = ins_list[0]
        if ins.address > (text_va + h_off) or (ins.address + ins.size) <= (text_va + h_off + 3):
            continue
        mem_ref = imm_ref = None
        imm_val = None
        float_imm = None   # P1-4（2026-09-27 复核 ff86c62f）：**任意** imm 操作数的 float 位型旁证
        for op in ins.operands:      # （旧版只在 imm==目标地址时才看 ⇒ 全报告 0 行 = 死代码）
            val, is_imm = _op_value(op, X86_OP_MEM, X86_OP_IMM)
            # 复核 5560c6c5 Q5：imm==目标自身 = 地址物化，其位型不算旁证
            if is_imm and val is not None and (val & 0xFFFFFFFF) != (target_va & 0xFFFFFFFF) \
                    and _float_bits(val & 0xFFFFFFFF):
                float_imm = val & 0xFFFFFFFF
            if val != (target_va & 0xFFFFFFFF):
                continue
            op_size = op.size if op.size else 0
            kind, sign = classify_insn(ins.mnemonic, op_size, is_imm)
            ref = Ref(target_va, ins.address, ins.mnemonic, ins.op_str,
                      op_size, kind, sign, note='imm' if is_imm else 'disp')
            if is_imm:
                imm_ref, imm_val = ref, val
            elif mem_ref is None:
                mem_ref = ref
        chosen = mem_ref or imm_ref     # mem 优先（F5）
        if chosen is not None and float_imm is not None:
            # 标签按承载纠真（复核 5560c6c5 Q5：imm 承载时无 disp，不得写 disp+）
            chosen.note = 'disp+imm-float-bits' if mem_ref is not None else 'imm-float-bits'
        if chosen is not None:
            hits[ins.address] = chosen
    if not hits:
        return None, 0
    if len(hits) > 1 and boundaries is None:
        return None, len(hits)           # 歧义不作证据（D2）
    ordered = sorted(hits.values(), key=lambda r: (r.insn_va, r.mnemonic))
    return ordered[0], len(ordered)


def scan_t1(data, sections, target_vas, boundaries=None, md=None, progress=None):
    """全 .text 扫每个 target_va 的 LE4 命中 → 指令级 Ref。
    返回 (refs: {va: [Ref]}, raw_only: {va: [命中 VA…未解码/歧义]})。"""
    import capstone
    from capstone import x86 as cs_x86
    if md is None:
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        md.detail = True
    consts = (cs_x86.X86_OP_MEM, cs_x86.X86_OP_IMM)
    text_va, text_size, roff = text_span(sections)
    blob = data[roff:roff + text_size]
    refs = defaultdict(list)
    raw_only = defaultdict(list)
    for va in target_vas:
        pat = struct.pack('<I', va & 0xFFFFFFFF)
        start = 0
        while True:
            h = blob.find(pat, start)
            if h < 0:
                break
            start = h + 1
            # D1：decode 的缓冲与 h 偏移基必须同源（blob，而非整文件 data）
            ref, _amb = decode_refs_at(blob, text_va, h, va, md, consts,
                                       boundaries=boundaries)
            if ref is None:
                raw_only[va].append(text_va + h)
            else:
                refs[va].append(ref)
        if progress:
            progress()
    return refs, raw_only


# ---------------------------------------------------------------- T2 decomp 佐证

T2_PATTERNS = [
    ('float', re.compile(r'\(float \*\)|\*\(float \*\)|\(float\)')),
    ('double', re.compile(r'\*\(double \*\)|\(double\)')),
    ('byte', re.compile(r'\*\(_BYTE \*\)|\(_BYTE \*\)|LOBYTE\(|BYTE1\(')),
    ('word', re.compile(r'\*\(WORD \*\)|\*\(_WORD \*\)|\(_WORD \*\)|LOWORD\(|HIWORD\(')),
    ('dword', re.compile(r'\*\(_DWORD \*\)|\(_DWORD \*\)')),
]


def scan_t2(names_by_va, decomp_dir=None, context=90):
    """decomp 全文找成员名渲染点（单遍组合正则 + **词边界**，D11），上下文窗口模式佐证。
    返回 {va: {'sites': n, 'hints': Counter(tag->n), 'samples': [str]}}"""
    decomp_dir = decomp_dir or DECOMP
    name_to_vas = defaultdict(list)
    for va, n in names_by_va.items():
        if n:
            name_to_vas[n].append(va)
    if not name_to_vas:
        return {}
    body_pat = '|'.join(re.escape(n) for n in sorted(name_to_vas, key=len, reverse=True))
    combined = re.compile(r'(?<![A-Za-z0-9_])(?:%s)(?![A-Za-z0-9_])' % body_pat)
    out = {}
    for f in os.listdir(decomp_dir):
        if not f.endswith('.json'):
            continue
        try:
            d = json.load(open(os.path.join(decomp_dir, f), encoding='utf-8'))
        except Exception:
            continue
        body = d.get('decompiled_c') or ''
        if not body:
            continue
        for m in combined.finditer(body):
            lo = max(0, m.start() - context)
            hi = min(len(body), m.end() + context)
            win = body[lo:hi]
            for va in name_to_vas.get(m.group(0), ()):
                slot = out.setdefault(va, {'sites': 0, 'hints': Counter(), 'samples': []})
                slot['sites'] += 1
                for tag, pat in T2_PATTERNS:
                    if pat.search(win):
                        slot['hints'][tag] += 1
                if len(slot['samples']) < 2:
                    slot['samples'].append(win.replace('\n', ' ')[:150])
    return out


# ---------------------------------------------------------------- 提案与分级

def propose(refs, t2=None):
    """(proposal | None, grade, notes)。2026-09-27 复核裁决版（D4 浮点证据优先）：
    - mov/清零/比较的 dword 触碰与浮点族**兼容**；整型运算（fild/fi*/算术）才构成冲突；
    - double 提案只报告（布局高危 v1 禁填，emit 层再拦一道）；
    - 4B 整型只证宽度 ⇒ WIDTH-4-MATCHED（int/float/指针 不可分，D10）。"""
    t2 = t2 or {}
    notes = []
    addr_uses = [r for r in refs if r.kind == 'addr']
    unknowns = [r for r in refs if r.kind == 'unknown']
    typed = [r for r in refs if r.kind in ('int', 'float', 'double')]
    if addr_uses:
        notes.append('地址物化 %d 站点（当指针用，不定型）' % len(addr_uses))
    # P1-4（2026-09-27 复核）：浮点位型旁证对**全部 kind** 表面化（旧版只查 addr_uses ⇒
    # 验收表引用的 fstp+imm 旁证在报告里根本不存在 = 人工脑补）。
    for r in refs:
        if 'float-bits' in (r.note or ''):
            notes.append('imm 位型像 float（%s）：旁证' % r.op_str[-18:])
            break
    if unknowns and (typed or addr_uses):
        notes.append('CONFLICT: kind=unknown 站点 %d 与定型证据混入（未理解的证据不落盘，F11）'
                     % len(unknowns))
        return None, 'C', notes
    if not typed:
        if t2.get('sites'):
            return None, 'B', notes + [
                'T1 无宽度证据（%d 站点全为地址物化/未解码/歧义）+ T2 渲染 %d 站点 ⇒ '
                '疑经指针访问（T1 盲区），宽度不可证，不填' % (len(refs), t2['sites'])]
        return None, '0', notes + ['无 T1/T2 证据']
    if unknowns:
        notes.append('仅 kind=unknown 站点 %d（tbyte/非常规）⇒ 不填' % len(unknowns))
        return None, 'B', notes

    floats = [r for r in typed if r.kind == 'float']
    doubles = [r for r in typed if r.kind == 'double']
    ints = [r for r in typed if r.kind == 'int']
    int_ops = [r for r in ints if r.mnemonic.lower() in INT_OP]
    int_moves = [r for r in ints if r.mnemonic.lower() not in INT_OP]

    # —— 真冲突（C）——
    if floats and doubles:
        notes.append('CONFLICT: float %d 站点 vs double %d 站点（同槽混用）'
                     % (len(floats), len(doubles)))
        return None, 'C', notes
    if (floats or doubles) and int_ops:
        notes.append('CONFLICT: 浮点族 %d 站点 vs 整型运算 %d 站点（%s）——fild/fist vs fld/fstp'
                     % (len(floats) + len(doubles), len(int_ops),
                        ','.join(sorted({r.mnemonic.lower() for r in int_ops})[:4])))
        return None, 'C', notes

    # —— 浮点族（D4：浮点证据优先，mov 触碰兼容）——
    if floats or doubles:
        fam = floats or doubles
        fam_width = 4 if floats else 8
        if any(r.op_size != fam_width for r in fam):
            notes.append('CONFLICT: 浮点族宽度非 %d: %s' % (fam_width, [r.op_size for r in fam]))
            return None, 'C', notes
        if floats and any(r.op_size in (1, 2) for r in int_moves):
            notes.append('CONFLICT: float 4B 与 1/2B 整型触碰同槽（疑位域/复用）')
            return None, 'C', notes
        if floats:
            grade = 'A' if len(fam) >= 2 else 'B'
            notes.append('x87/SSE dword 浮点 %d 站点（+整型触碰 %d 兼容）' % (len(fam), len(int_moves)))
            return 'float', grade, notes
        grade = 'A' if len(fam) >= 2 else 'B'
        notes.append('qword 浮点 %d 站点 ⇒ double 提案（**v1 禁填**：布局高危 4→8）' % len(fam))
        return 'double', grade, notes

    # —— 纯整型 ——
    widths = Counter(r.op_size for r in ints)
    if len(widths) > 1:
        notes.append('CONFLICT: 整型多宽度 %s（1/2B vs 4B）' % dict(widths))
        return None, 'C', notes
    if set(widths) == {4}:
        notes.append('4 字节 %d 站点 ⇒ 占位 int **宽度**已正确（int/float/指针 不可分；符号位：%s）'
                     % (sum(widths.values()), sorted({r.sign for r in ints if r.sign}) or '不可证'))
        return None, 'A', notes + ['WIDTH-4-MATCHED']
    if set(widths) in ({1}, {2}):
        w = 1 if set(widths) == {1} else 2
        signs = {r.sign for r in ints if r.sign}
        if len(signs) == 1:
            grade = 'A' if len(ints) >= 2 else 'B'
            notes.append('%s %d 站点，符号位证据：%s'
                         % ('byte' if w == 1 else 'word', len(ints), signs))
            return FILL_BY_WIDTH[(w, signs.pop())], grade, notes
        notes.append('%s %d 站点但符号位%s ⇒ 不填'
                     % ('byte' if w == 1 else 'word', len(ints),
                        '证据互相矛盾' if len(signs) > 1 else '不可证（movzx/movsx 缺失）'))
        return None, 'B', notes
    notes.append('整型宽度 %s（8/16B 等）⇒ 报告不填（占位 int 宽度不符，需人工）' % dict(widths))
    return None, 'B', notes


# ---------------------------------------------------------------- 候选收集

def parse_member_key(key):
    """known_members 键 → offset。键形态混用：'50814'（十进制）/ '0x4C'（十六进制）
    / '188_2'（union 变体后缀）。D7。"""
    s = str(key).split('_')[0]
    return int(s, 16) if s.lower().startswith('0x') else int(s)


def load_candidates(only_cls=None, census_path=None, partition_path=None, structs_dir=None):
    """工作集 W（见模块 docstring）：容器类 known_members 的占位成员。
    返回 (cands, diags)；cands[i] 含 vas=[(实例名, VA)…]（D9 多实例）与 dup_keys 诊断。"""
    census = json.load(open(census_path or CENSUS, encoding='utf-8'))
    part = json.load(open(partition_path or PARTITION, encoding='utf-8'))
    structs_dir = structs_dir or STRUCTS
    tops = part['top_levels']
    insts_by_class = defaultdict(list)      # type -> [(实例名, base)]（D9：全实例）
    for t in tops:
        ty = t.get('type')
        if not ty or ty == 'unknown':
            continue
        insts_by_class[ty].append((t.get('name'), t['base']))

    diags = {'dups': [], 'multi_instance': {}, 'extent_anomalies': []}
    for t in tops:
        if isinstance(t.get('base'), int) and isinstance(t.get('end'), int) \
                and t['end'] - t['base'] <= 1:
            diags['extent_anomalies'].append('%s(%s) extent=%d'
                                             % (t.get('name'), t.get('type'), t['end'] - t['base']))
    for ty, insts in insts_by_class.items():
        if len(insts) > 1:
            diags['multi_instance'][ty] = ['%s@0x%X' % (n, b) for n, b in insts]

    # B2 行仅作旁证：(cls, off) -> 全局名
    b2_ref = {}
    tops_by_name = {t.get('name'): t for t in tops}
    for r in census.get('rows') or census.get('entries') or []:
        if r.get('bucket') != 'B2':
            continue
        ev = r.get('evidence_refs')
        first = ev[0] if isinstance(ev, list) and ev else (ev if isinstance(ev, str) else '')
        m = re.match(r'inside:(.+)\+0x([0-9a-fA-F]+)$', first or '')
        if not m:
            continue
        t = tops_by_name.get(m.group(1))
        if not t or not t.get('type') or t.get('type') == 'unknown':
            continue
        b2_ref[(t['type'], int(m.group(2), 16))] = r.get('name')

    cands = {}
    for cls, insts in sorted(insts_by_class.items()):
        if only_cls and cls != only_cls:
            continue
        p = os.path.join(structs_dir, cls + '.json')
        if not os.path.exists(p):
            continue
        d = json.load(open(p, encoding='utf-8'))
        seen_off = {}
        for key, m in (d.get('known_members') or {}).items():
            if not isinstance(m, dict):
                continue
            if str(m.get('type')) not in PLACEHOLDER_TYPES:
                continue
            off = parse_member_key(key)
            if off in seen_off:
                diags['dups'].append('%s +0x%X: keys %r / %r（显式报 dup，人工裁定）'
                                     % (cls, off, seen_off[off], key))
                continue
            seen_off[off] = key
            cands[(cls, off)] = {
                'cls': cls, 'offset': off, 'key': str(key),
                'vas': [(n, b + off) for n, b in insts],
                'name': m.get('name'), 'cur_type': m.get('type'),
                'b2_ref': b2_ref.get((cls, off)), 'src': 'member-placeholder',
            }
    return sorted(cands.values(), key=lambda c: (c['cls'], c['offset'])), diags


# ---------------------------------------------------------------- 批次产出（唯一落盘口的输入）

def emit_batch(results, out_path=None):
    """A 级 + 可落盘提案 → 守卫批次（kind=type_change，evidence 必填）。
    double / 不可落盘类型自动剔除。返回 (n_items, out_path)。"""
    out_path = out_path or BATCH_OUT
    items = []
    for r in results:
        if r['grade'] != 'A' or not r['proposal'] or r['proposal'] not in FILLABLE:
            continue
        ev = 'type-evidence T1: ' + '; '.join(
            '%s %s' % (s['insn_va'], s['op_str']) for s in r['t1'][:4])
        if r.get('t1b'):   # C6（复核 1239c52d）：evidence 必带 T1b 站点（守卫可追溯）
            ev += ' | T1b: ' + '; '.join(
                '%s %s' % (s['insn_va'], s['op_str']) for s in r['t1b'][:4])
        items.append({
            'kind': 'type_change', 'class': r['cls'], 'key': r['key'],
            'offset': r['offset'], 'old_type': r['cur_type'], 'new_type': r['proposal'],
            'evidence': ev, 'tool': 'type_evidence.py',
        })
    with open(out_path, 'w', encoding='utf-8', newline='') as f:
        json.dump(items, f, ensure_ascii=False, indent=2)
        f.write('\n')
    return len(items), out_path


# ---------------------------------------------------------------- 主流程

def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true', help='产出守卫批次（不直接改注解）')
    ap.add_argument('--cls', help='只跑一个类（调试）')
    ap.add_argument('--batch-out', default=BATCH_OUT)
    args = ap.parse_args(argv)

    cands, diags = load_candidates(args.cls)
    by_cls = Counter(c['cls'] for c in cands)
    print('=== type-evidence census（B 批工作集 W）===')
    print('候选成员: %d 个 / %d 类' % (len(cands), len(by_cls)))
    for cls, n in by_cls.most_common():
        print('  %-24s %d' % (cls, n))
    if diags['dups']:
        print('⚠️ 同偏移多键 %d 处（不静默覆盖）:' % len(diags['dups']))
        for s in diags['dups']:
            print('   ' + s)
    if diags['extent_anomalies']:
        print('⚠️ partition extent 异常（只报告不修）: %s' % '; '.join(diags['extent_anomalies']))

    data, va2off, sections = exe_text_image()
    print('\n[边界] decomp 函数区间线性反汇编 → 指令边界表 ...')
    func_ranges = load_func_ranges()
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    boundaries = build_boundaries(data, va2off, func_ranges, md)
    print('  函数 %d 个 / 指令边界 %d 条' % (len(func_ranges), len(boundaries)))

    all_vas = sorted({va for c in cands for _, va in c['vas']})
    print('\n[T1] 全 .text 扫描 %d 个成员地址（多实例并集）...' % len(all_vas))
    done = [0]

    def progress():
        done[0] += 1
        if done[0] % 200 == 0:
            print('    %d/%d' % (done[0], len(all_vas)))
    refs, raw_only = scan_t1(data, sections, all_vas, boundaries=boundaries,
                             md=md, progress=progress)

    print('\n[T2] decomp 渲染佐证 ...')
    t2 = scan_t2({va: c['name'] for c in cands for _, va in c['vas']})

    # v3（复核 1239c52d 硬化版）：T1b this-relative census——ECX provenance 跟踪
    # （播种门=__thiscall/*this；regs_write 失效+别名；index/负 disp 拒）。
    # 槽键=(cls, offset)：this+disp 是实例相对 ⇒ 与 T1 的绝对 VA 面正交。
    print('\n[T1b] this-relative census（ECX provenance）...')
    t1b_by_slot = {}
    try:
        # 脚本直跑时 sys.path[0]=tools/，仓库根不在路径 ⇒ tools.t1b 不可导（实测踩点）
        sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
        from tools.t1b import method_seed_map, collect_t1b_for_method, to_refs as _t1b_to_refs, \
            merge_sources as _merge_sources
        _seeds = method_seed_map()
        _findex = dict(func_ranges)
        _want = set(by_cls)
        _nmethods = 0
        for (_cls, _addr), _seed in sorted(_seeds.items()):
            if _cls not in _want:
                continue
            _sz = _findex.get(_addr)
            if not _sz:
                continue
            _off = va2off(_addr)
            _insns = list(md.disasm(data[_off:_off + _sz], _addr))
            _hits, _ = collect_t1b_for_method(_insns, seed_this=_seed)
            for _k, _v in _hits.items():
                t1b_by_slot.setdefault((_cls, _k), []).extend(_v)
            _nmethods += 1
        print('  方法 %d 个 / T1b 槽 %d 个（种子=%s）' % (
            _nmethods, len(t1b_by_slot), 'ECX provenance' ))
    except Exception as _e:  # noqa: BLE001
        print('  [WARN] T1b census 不可用：%r —— T1-only 继续' % (_e,))
        def _t1b_to_refs(off, hits): return []   # noqa: E306
        def _merge_sources(a, b, off): return list(a), []   # noqa: E306

    results = []
    agg = Counter()
    for c in cands:
        rs = []
        raws = []
        for inst, va in c['vas']:
            for r in refs.get(va, []):
                rs.append(r)
            raws.extend(raw_only.get(va, []))
        # T2 按名聚合（跨实例同名）
        t2_slot = None
        for _, va in c['vas']:
            if va in t2:
                t2_slot = t2[va]
                break
        t1b_hits = t1b_by_slot.get((c['cls'], c['offset']), [])
        t1b_rs = _t1b_to_refs(c['offset'], t1b_hits) if t1b_hits else []
        merged, xnotes = _merge_sources(rs, t1b_rs, c['offset'])
        proposal, grade, notes = propose(merged, t2_slot)
        # 溯源注前置（不改变 notes[-1] 的 WIDTH-4-MATCHED 判定位）
        notes = xnotes + (['T1:%d T1b:%d' % (len(rs), len(t1b_rs))] if t1b_rs else []) + list(notes)
        agg[grade] += 1
        if proposal:
            agg['fill:' + proposal] += 1
        if notes and notes[-1] == 'WIDTH-4-MATCHED':
            agg['WIDTH-4-MATCHED'] += 1
        results.append({
            'cls': c['cls'], 'offset': c['offset'], 'key': c['key'],
            'vas': ['%s:0x%08X' % (n, v) for n, v in c['vas']],
            'name': c['name'], 'b2_ref': c['b2_ref'], 'cur_type': c['cur_type'],
            'src': c['src'], 'proposal': proposal, 'grade': grade, 'notes': notes,
            't1': [r.as_dict() for r in rs],
            't1b': [r.as_dict() for r in t1b_rs],
            't1_raw_only': raws,
            't2': ({'sites': t2_slot['sites'], 'hints': dict(t2_slot['hints'])}
                   if t2_slot else None),
        })

    print('\n=== 分级汇总 ===')
    for k in ('A', 'B', 'C', '0'):
        print('  %s: %d' % (k, agg[k]))
    print('  WIDTH-4-MATCHED（int 宽度已正确，无动作）: %d' % agg['WIDTH-4-MATCHED'])
    fills = {k[5:]: n for k, n in agg.items() if k.startswith('fill:')}
    print('  填充提案: %s  (合计 %d；double 只报告 v1 禁填)' % (fills or '{}', sum(fills.values())))
    shown = 0
    for r in results:
        if r['proposal']:
            print('  [%-4s] %-22s +0x%-5x %-16s -> %-14s %s' % (
                r['grade'], r['cls'], r['offset'], str(r['name'])[:16],
                r['proposal'], '; '.join(r['notes'])[:70]))
            shown += 1
            if shown >= 24:
                print('  ...（其余见报告）')
                break

    report = {'_meta': {
        'tool': 'type_evidence.py', 'version': 3, 'batch': 'B',   # v3：T1+T1b 双信号
        'scope': 'W = 容器类 known_members 占位成员（B2 行仅旁证，多实例全 VA 取证）',
        'candidates': len(cands), 'by_class': dict(by_cls),
        'grades': {k: agg[k] for k in ('A', 'B', 'C', '0')},
        'width4_matched': agg['WIDTH-4-MATCHED'], 'fills': fills,
        'diags': diags, 'func_ranges': len(func_ranges), 'boundaries': len(boundaries),
        'coverage_note': 'T1 单源实测覆盖 25-30%（this+off 盲区 ~70%）；disp32(T1b) 是后续扩展',
        'gates': ('python tools/apply_annotation_batch.py --batch <batch> --dry-run → 落盘 → '
                  'tools/annotation_diff.py → apply_annotations → export_full（不回灌不生效！）'
                  '→ codegen → audit_type_layout --only <Cls> → verify_fix --class <Cls> '
                  '→ loop --expect-errors 不增 → L1 不降'),
    }, 'results': results}
    with open(REPORT, 'w', encoding='utf-8', newline='') as f:
        json.dump(report, f, ensure_ascii=False, indent=1)
    print('\n报告 -> %s' % os.path.relpath(REPORT, ROOT))

    if not args.write:
        print('(dry-run — 加 --write 产出守卫批次)')
        return 0

    n, out = emit_batch(results, args.batch_out)
    print('\n守卫批次 %d 条 -> %s' % (n, os.path.relpath(out, ROOT)))
    print('落盘走唯一守卫（evidence 为空整批拒绝）:')
    print('  python tools/apply_annotation_batch.py --batch %s --dry-run' % os.path.relpath(out, ROOT))
    print('  python tools/apply_annotation_batch.py --batch %s' % os.path.relpath(out, ROOT))
    print('⚠️ 生效链（D5）: annotation_diff → **apply_annotations → export_full**（不回灌 IDB '
          '则改注解不进生成头）→ codegen → audit_type_layout --only <Cls> → '
          'verify_fix --class <Cls> → 四道门')
    return 0


if __name__ == '__main__':
    sys.exit(main())
