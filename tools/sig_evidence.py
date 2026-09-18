#!/usr/bin/env python3
"""Phase-1 evidence pack generator for C2660 signature mismatches.

For every C2660 ("function does not take N parameters") error:
  1. attribute the callee to its true class (call-site text: `Cls::M(`
     prefix, else the caller file's own class for unqualified calls);
  2. collect the callee's ret instructions via MCP disassembly
     (instruction-accurate, not byte-grep);
  3. grade the cluster:
       A   rets unanimous, N%4==0, param slots == caller arg count
       B   anything structurally ambiguous (mixed rets, N%4!=0,
           call sites disagreeing on arg count, sret suspected)
       C   attribution failed (multi-address binding / object call
           without type context)
No annotation is modified here - output is a graded evidence pack for
human review (A-grade bulk, B-grade per-item, C deferred).
"""
import json, glob, re, sys
from collections import Counter, defaultdict

sys.path.insert(0, 'tools')
from mcp_query import call

BASE = 'data/status/baselines/latest.json'
OUT = 'data/status/_sig_evidence_pack.json'

# FIX(2026-09-18): `h?` 原先写在**捕获组之外**，于是 'retn 20h' 捕获到 '20'、
# h 被吃掉 ⇒ 下面 parse_ret_num 的 `endswith('h')` 分支成了死代码，
# 所有多位立即数被按十进制解析：20h→20（真值 32，slots 5 而非 8）、
# 10h→10（真值 16，非 4 倍数 ⇒ grade B-ODDRET ⇒ 不发 slots ⇒ 证据门永久阻塞）、
# 0Ch→ int('0C') → ValueError（被 rets_of 的 except 吞成 C-DISASM-ERR）。
# 实测 original/PAL3.exe.asm 里所有多位立即数都带 h（无 h 的多位数 0 条），
# 故把 h 收进捕获组即可。
RET_RE = re.compile(r'^(?:retn|ret)(?:\s+([0-9A-Fa-f]+h?))?\s*$')


def parse_ret_num(rest):
    if not rest:
        return 0
    if rest.lower().endswith('h'):
        return int(rest[:-1], 16)
    return int(rest)


def load_errors():
    n = json.load(open(BASE, encoding='utf-8'))['results']
    errs = []
    for u, r in n.items():
        cls = None
        m = re.search(r'/([A-Za-z_][\w]*)\.cpp$', u)
        if m:
            cls = m.group(1)
        for e in r.get('errors', []):
            if e['code'] != 'C2660':
                continue
            mm = re.search(r"'([\w:~=]+)' : function does not take (\d+) parameters", e['msg'])
            if not mm:
                continue
            errs.append({'file': u, 'line': e.get('line'), 'cls': cls,
                         'method': mm.group(1), 'caller_args': int(mm.group(2))})
    return errs


def load_method_addrs():
    """(cls, method) -> [addr, ...] from structs annotations."""
    m2a = {}
    for p in glob.glob('data/annotations/structs/*.json'):
        d = json.load(open(p, encoding='utf-8'))
        cls = d.get('name')
        for a, m in (d.get('methods') or {}).items():
            mn = str(m.get('name', ''))
            m2a.setdefault((cls, mn), []).append(int(a, 16))
            # operator= style: '=' annotates as 'operator=' or '='
            if mn in ('operator=',):
                m2a.setdefault((cls, '='), []).append(int(a, 16))
    return m2a


def call_site_class(file, line, method):
    """Read the generated cpp call site; return the class of the callee."""
    try:
        t = open(file, encoding='utf-8', errors='replace').read().split('\n')
        txt = t[line - 1] if line and line <= len(t) else ''
    except Exception:
        return None
    m = re.search(r'([\w]+)::' + re.escape(method) + r'\s*\(', txt)
    if m:
        return m.group(1)
    return None


ASM_PATH = 'original/PAL3.exe.asm'
_ASM_INDEX = None


def _asm_proc_index():
    """建 original/PAL3.exe.asm 的 `label proc near` -> 行号 索引（惰性）。"""
    global _ASM_INDEX
    if _ASM_INDEX is None:
        idx = {}
        try:
            with open(ASM_PATH, encoding='utf-8', errors='replace') as fh:
                for i, line in enumerate(fh):
                    m = re.match(r'^(\S+)\s+proc near', line)
                    if m:
                        idx.setdefault(m.group(1), i)
        except OSError:
            idx = {}
        _ASM_INDEX = idx
    return _ASM_INDEX


def rets_of_asm(addr, max_lines=4000):
    """从 IDA 反汇编清单取某地址函数的 retn 立即数（instruction-accurate）。

    与 MCP 的 disassemble_function 等价：`original/PAL3.exe.asm` 是**同一个
    不可变 exe** 的 IDA 清单，函数字节不会变，故 retn 值同源。只用于在
    IDA MCP 不可用时离线重建证据，避免把证据源变成硬依赖。
    """
    idx = _asm_proc_index()
    if not idx:
        return None, 'asm 清单不可读: %s' % ASM_PATH
    hexs = ('%X' % addr)
    label = 'sub_%s' % hexs
    start = idx.get(label)
    if start is None:
        return None, 'asm 中找不到 %s' % label
    rets = []
    try:
        with open(ASM_PATH, encoding='utf-8', errors='replace') as fh:
            for i, line in enumerate(fh):
                if i <= start:
                    continue
                if i > start + max_lines:
                    break
                if re.match(r'^\S+\s+endp', line):
                    break
                m = RET_RE.match(line.strip())
                if m:
                    rets.append(parse_ret_num(m.group(1)))
    except OSError as ex:
        return None, str(ex)[:80]
    return rets, None


def rets_of(addr, source='auto'):
    """取函数 retn 立即数。source: mcp / asm / auto。

    auto = 先试 IDA MCP，失败则回退到 original/PAL3.exe.asm 并在 stderr 明确
    提示（证据源切换必须可见，不能静默）。
    """
    if source in ('asm', 'auto'):
        if source == 'asm':
            rets, err = rets_of_asm(addr)
            if err:
                raise RuntimeError('rets_of(asm): %s' % err)
            return rets, -1
    try:
        return _rets_of_mcp(addr)
    except Exception as ex:
        if source == 'auto':
            rets, err = rets_of_asm(addr)
            if not err:
                print('[NOTE] sig_evidence: IDA MCP 不可用(%s)；改用 %s 取 retn '
                      '(addr=0x%08X)' % (str(ex)[:50], ASM_PATH, addr),
                      file=sys.stderr)
                return rets, -1
        raise


def _rets_of_mcp(addr):
    r = call('disassemble_function', {'start_address': '0x%08X' % addr}, 90)
    res = r.get('result', r)
    lines = res.get('lines') or []
    rets = []
    for l in lines:
        ins = l.get('instruction', '').strip()
        m = RET_RE.match(ins)
        if m:
            rets.append(parse_ret_num(m.group(1)))
    return rets, len(lines)


def apply_rets_grading(entry, rets):
    """按 retn 真值给条目定级（**唯一实现**，main 与离线修复共用）。

    grade 语义（勿改）：
      B-NORET       无 ret 指令
      B-MIXEDRET    多个 ret 立即数不一致
      B-ODDRET      立即数非 4 的倍数（不可能是 __thiscall 的栈字节数）
      A             slots 与调用点实参数**唯一且一致**
      B-ARGCONFLICT 调用点对实参数各执一词
      B-SLOTMISMATCH 调用点只有一个实参数、但与 retn 真值不一致
                     —— 这是「调用点在说谎」的信号，**发布 retn 真值本身是对的**
    """
    entry.pop('err', None)
    entry['rets'] = rets
    caller_args = entry.get('args') or []
    if not rets:
        entry['grade'] = 'B-NORET'
        entry.pop('slots', None)
    elif len(set(rets)) != 1:
        entry['grade'] = 'B-MIXEDRET'
        entry.pop('slots', None)
    elif rets[0] % 4 != 0:
        entry['grade'] = 'B-ODDRET'
        entry.pop('slots', None)
    else:
        slots = rets[0] // 4
        entry['slots'] = slots
        if len(caller_args) == 1 and slots == caller_args[0]:
            entry['grade'] = 'A'
        elif len(caller_args) > 1:
            entry['grade'] = 'B-ARGCONFLICT'
        else:
            entry['grade'] = 'B-SLOTMISMATCH'
    return entry


def provably_misparsed(entry):
    """该条目的 retn 派生值是否**可被证明**解析错了（只修这些）。

    三类，都是自证的：
      B-ODDRET      rets 不是 4 的倍数 —— 真 __thiscall 的 retn 立即数必为 4×slots；
      C-DISASM-ERR  pack 的 `err` 里已记录 `int('0C')` 的 ValueError（h 后缀被吃掉的现场）；
      静默错值      rets 里存在 >=10 且为 4 的倍数的值 —— 它通过了 %4 校验、
                    于是发布了错 slots（如 20h→20→slots 5，真值 32→8）。
    注意：**不能**顺手"重新评分"整张 pack —— 实测 pack 里有 54 条 `A-V2`，
    是现行评分函数产不出的更高等级（说明它由别的版本写入），重评会误伤它们。
    """
    if entry.get('grade') in ('B-ODDRET', 'C-DISASM-ERR'):
        return True
    rets = entry.get('rets') or []
    return any(v >= 10 and v % 4 == 0 for v in rets)


def repair_from_asm(pack_path=OUT, asm_path=ASM_PATH, write=True):
    """离线重建 pack 里 retn 派生的 rets/slots/grade（IDA MCP 不可用时）。

    证据源优先级：
      1. `original/PAL3.exe.asm` 的指令级扫描（与 MCP 同源：同一个不可变 exe）；
      2. 该函数在 asm 里是 COLLAPSED（无指令行）时，回退为**把旧值当十六进制读回**
         —— 依据是实测「asm 里所有多位立即数都带 h、无 h 的多位数 0 条」，
         故旧值里 >=10 的数必然是某 `NNh` 被按十进制读出的结果。
         单值 0..9 两种读法相同，无需处理。
    """
    global ASM_PATH
    ASM_PATH = asm_path
    global _ASM_INDEX
    _ASM_INDEX = None
    pack = json.load(open(pack_path, encoding='utf-8'))
    changes = []
    for e in pack.get('graded', []):
        addrs = e.get('addrs') or []
        if not addrs:
            continue
        if not provably_misparsed(e):
            continue
        old = (e.get('rets'), e.get('slots'), e.get('grade'))
        new_rets = None
        src = None
        rets, err = rets_of_asm(int(addrs[0], 16))
        if rets:
            new_rets, src = rets, 'asm'
        elif e.get('rets'):
            new_rets, src = [int(str(v), 16) if v >= 10 else v
                             for v in e['rets']], 'hex-reinterpret'
        if new_rets is None:
            continue
        apply_rets_grading(e, new_rets)
        if (e.get('rets'), e.get('slots'), e.get('grade')) != old:
            changes.append((e.get('cls'), e.get('method'), old,
                            (e['rets'], e.get('slots'), e['grade']), src))
    if write:
        json.dump(pack, open(pack_path, 'w', encoding='utf-8'),
                  ensure_ascii=False, indent=1)
    return pack, changes


def main():
    errs = load_errors()
    print('C2660 errors parsed:', len(errs))
    m2a = load_method_addrs()

    # group by (attributed class, method)
    clusters = defaultdict(list)
    unattr = []
    for e in errs:
        cls = call_site_class(e['file'], e['line'], e['method'])
        if cls is None:
            cls = e['cls']
        if cls is None:
            unattr.append(e)
            continue
        clusters[(cls, e['method'])].append(e)
    print('clusters:', len(clusters), '| unattributed:', len(unattr))

    pack = {'graded': [], 'unattributed': len(unattr)}
    disasm_cache = {}

    for (cls, meth), sites in sorted(clusters.items()):
        addrs = sorted(set(m2a.get((cls, meth), [])))
        entry = {'cls': cls, 'method': meth, 'sites': len(sites),
                 'args': sorted(set(s['caller_args'] for s in sites)),
                 'addrs': ['0x%08X' % a for a in addrs]}
        if not addrs:
            entry['grade'] = 'C-NOADDR'
            pack['graded'].append(entry)
            continue
        if len(addrs) > 1:
            entry['grade'] = 'C-MULTIADDR'
            entry['addrs_detail'] = entry['addrs']
            pack['graded'].append(entry)
            continue
        addr = addrs[0]
        if addr in disasm_cache:
            rets = disasm_cache[addr]
        else:
            try:
                rets, nl = rets_of(addr)
                disasm_cache[addr] = rets
            except Exception as ex:
                entry['grade'] = 'C-DISASM-ERR'
                entry['err'] = str(ex)[:80]
                pack['graded'].append(entry)
                continue
        apply_rets_grading(entry, rets)
        pack['graded'].append(entry)

    grades = Counter(g['grade'] for g in pack['graded'])
    print('grades:', dict(grades))
    json.dump(pack, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('pack ->', OUT)
    return pack


if __name__ == '__main__':
    if '--repair-from-asm' in sys.argv:
        _pack, _ch = repair_from_asm()
        print('修复条目数: %d' % len(_ch))
        for _c, _m, _o, _n, _s in _ch:
            print('  %-16s %-24s %s -> %s  [%s]' % (_c, _m, _o, _n, _s))
    else:
        main()
