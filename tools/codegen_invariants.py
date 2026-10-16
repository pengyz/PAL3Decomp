#!/usr/bin/env python3
"""生成代码的**内部不变量检查**（编译之前就能跑，秒级）。

背景：项目的门禁（`probe`/`match`）要跑完 apply→export→codegen→probe 才能看见问题（一轮 ~15 分钟），
而下面这几类缺陷**在生成物里就已可判定**。

判据（经 2026-09-19 独立复核修正过，见 `data/status/_codegen_invariants_review.md`）：

* **A. `__vftable` 残留（编译阻塞）**：任何生成头**都不声明 `__vftable`**（全 `pal3/**` 搜 `*.h` 为 0 命中），
  而生成 C++ 里有 **150 行**（非注释）在用 `X.__vftable` / `X->__vftable` ⇒ 每一行都是编译错误。
  `data/status/probe_census.json` 里 `C2039 '__vftable' : is not a member of ...` 覆盖 **27 个文件、≥94 条**
  （7 个 unit 被 `--errorlimit` 截断在 102 条，故为下界）。
  ⚠️ 不要用"bare / cast / other"当严重性分类：`cast` 恒 0，而"other"里 ≥79/134 本来就是 cast 形态。
* **B. `sub_XXXX` 的「唯一声明的形参数」与「调用点实参数」不一致**（**语义可疑，不是编译错误**）。
  ⚠️ 第一版判据（"同一 `sub_` 有多份声明"）**已证伪**：它把调用语句（同样以 `;` 结尾）当成了声明，
  151 条 100% 假阳性。第二版改成"声明 1 份、调用 N 处，比较形参与实参个数"。
  ⚠️⚠️ **2026-09-21 再证伪一层**：第二版把 `(...)` 当作 "1 参" ⇒ 报出 56 处"不一致"，
  **全部是假阳性** ✗。真实 MSVC6 实测（`wine CL.EXE /TP /c`）：
  `int sub_401070(...); int f(){ return sub_401070(1,2,3,4,5); }` ⇒ **0 错误** ✓
  —— C++ 里 `(...)` 是**合法的可变参原型**，任意实参数都合法。
  实测 202 条 `C2660` 里指名叫省略号声明符号的 **0 条** ✗。
  ⇒ 现版本把 `(...)` 记为"元数不限"（`_arity_of` 返回 `None`）并跳过比较；
  B 项剩余报出的是**真·形参/实参个数不一致**（可编译但语义可疑），**不得**再称其为 C2660 成因。
* **C. 注解 `methods[addr].signature` 的 `__thiscall X::` 前缀 ≠ 该 JSON 的类名**（**潜伏**，不阻塞编译：
  codegen 按 JSON 的类名落位、丢掉前缀 ⇒ 生成物仍合法）。已知 28 条真阳性 + 1 条待裁定。

退出码：A/B 有问题 ⇒ 1；仅 C 有问题 ⇒ 0（除非 `--strict`）；参数错误 ⇒ 2。

用法::

    python tools/codegen_invariants.py                 # A+B（编译阻塞项）
    python tools/codegen_invariants.py --strict        # 连 C（潜伏项）也判失败
    python tools/codegen_invariants.py --check A       # 只跑 A（名字必须合法，否则 exit 2）
"""
import argparse
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, 'pal3', 'src')
STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')
INCLUDE = os.path.join(ROOT, 'include')
VALID_CHECKS = ('A', 'B', 'C', 'D')

ANY_VFT = re.compile(r'__vftable')
SUBFN = re.compile(r'\bsub_[0-9A-Fa-f]{6}\b')
DECL_LINE = re.compile(r'^\s*(?:extern\s+)?[\w\s\*&:<>,\[\]]+?\b(sub_[0-9A-Fa-f]{6})\s*\(')
THISCLASS = re.compile(r'__thiscall\s+([A-Za-z_]\w*)::')



def handwritten_vptr_verdict(cls, include_root):
    """手写头 vptr 判定（纯函数，R15 单测点）→ ('ok'|'bad'|'none', detail)。

    判据与生成头一致：「显式 vptr/占位」∨「声明了 virtual」⇒ ok。查找形：
    ① include/**/Cls.h 同名头 ② include/**/*.h 内 `class|struct Cls` 声明行。
    """
    import glob as _g, os as _o, re as _re
    texts = []
    for hp in _g.glob(_o.path.join(include_root, '**', cls + '.h'), recursive=True):
        texts.append((hp, open(hp, encoding='utf-8', errors='replace').read()))
    if not texts:
        decl = _re.compile(r'\b(?:class|struct)\s+(?:\w+\s+)*%s\b' % _re.escape(cls))
        for hp in _g.glob(_o.path.join(include_root, '**', '*.h'), recursive=True):
            t = open(hp, encoding='utf-8', errors='replace').read()
            if decl.search(t):
                texts.append((hp, t))   # 多声明全收集（CPK 双声明实证）
    if not texts:
        return 'none', ''
    # 多声明场景（如 CPK 在 pal3_structs.h 与 gbVFileSystem.h 双声明）：任一命中含
    # virtual/vptr 证据即 ok（2026-10-16 首版只判首命中 ⇒ CPK 误报，本版全遍历）
    _bad_hp = None
    for hp, t in texts:
        if '__vftable' in t or _re.search(r'^\s*virtual\s', t, _re.M) or 'vptr' in t:
            return 'ok', _o.path.relpath(hp)
        if _bad_hp is None:
            _bad_hp = hp
    return 'bad', _o.path.relpath(_bad_hp)

def gen_files(exts=('.cpp', '.h')):
    out = []
    for e in exts:
        out += glob.glob(os.path.join(SRC, '**', '*' + e), recursive=True)
    return sorted(out)


def strip_comments(text):
    """只保留真实 code（去行注释、块注释、字符串字面量），返回等长文本（用空格占位）。

    这样"某行是否含 code 位置的 __vftable"就等价于"该行在清理后的文本里是否还有 __vftable"，
    不会像第一版那样把 `*(...)` 续行误当成注释（那会漏掉 5 条真错误）。
    """
    out = []
    i, n = 0, len(text)
    state = None  # None | 'line' | 'block' | 'str' | 'chr'
    while i < n:
        c = text[i]
        nx = text[i + 1] if i + 1 < n else ''
        if state is None:
            if c == '/' and nx == '/':
                state = 'line'
                out.append('  ')
                i += 2
                continue
            if c == '/' and nx == '*':
                state = 'block'
                out.append('  ')
                i += 2
                continue
            if c == '"':
                state = 'str'
            elif c == "'":
                state = 'chr'
            out.append(c)
            i += 1
            continue
        if state == 'line':
            if c == '\n':
                state = None
                out.append('\n')
            else:
                out.append(' ')
            i += 1
            continue
        if state == 'block':
            if c == '*' and nx == '/':
                state = None
                out.append('  ')
                i += 2
                continue
            out.append('\n' if c == '\n' else ' ')
            i += 1
            continue
        # str / chr
        if c == '\\':
            out.append('  ')
            i += 2
            continue
        if (state == 'str' and c == '"') or (state == 'chr' and c == "'"):
            state = None
        out.append(c)
        i += 1
    return ''.join(out)


DECL_VFT = re.compile(r'^\s*(?:[\w:]+\s+)*[\w:]+\s*\*?\s*__vftable\s*(?:\[\d+\])?\s*;')


def check_a(verbose=False):
    hits = []
    for p in gen_files():
        raw = open(p, encoding='utf-8', errors='replace').read()
        clean = strip_comments(raw)
        for i, ln in enumerate(clean.split('\n'), 1):
            if not ANY_VFT.search(ln):
                continue
            # 2026-09-19：P1 修好后，**头里的声明行** `void * __vftable; // +0x0` 是合法的，
            # 不能再算违规（第一版把声明也算进去，P1 一改 A 就从 150 涨到 206，全是假阳性）。
            if DECL_VFT.match(ln):
                continue
            hits.append((os.path.relpath(p, ROOT), i,
                         raw.split('\n')[i - 1].strip()[:100]))
    if hits:
        files = sorted({h[0] for h in hits})
        print('[A] FAIL：__vftable 出现在真实 code 位置 %d 行 / %d 个文件'
              '（**结构性**指标：活代码位置的 __vftable 残留行数；不等于编译错误数 —— F11/F12 之后这些行多数已不再是错误）'
              % (len(hits), len(files)))
        per = {}
        for f, i, s in hits:
            per.setdefault(f, []).append(i)
        for f in files:
            print('    %-46s %2d 行（%s）' % (f, len(per[f]),
                  ','.join(str(x) for x in per[f][:8]) + ('...' if len(per[f]) > 8 else '')))
        if verbose:
            for f, i, s in hits:
                print('      %s:%d  %s' % (f, i, s))
    else:
        print('[A] PASS：没有任何 code 位置的 __vftable')
    return len(hits)


def _arity_of(args):
    """形参文本 → 元数；**`(...)` 返回 None = 可变参原型（元数不限）**。

    2026-09-21 用真实 MSVC6 实测（`wine CL.EXE /TP /c`）：

        int sub_401070(...);
        int user_a(void) { return sub_401070(1, 2, 3, 4, 5); }   // ← 0 错误 ✓

    C++ 里 `(...)` 是**合法的可变参声明**，任意个数实参都合法 ⇒ 它**永远不可能**
    与调用点数不符。第一版把它当 "1 参" ⇒ 报出 56 处"声明/调用不一致"，
    **全部是假阳性**，且其文档曾断言这是 "C2660/C2664 的直接成因" ✗
    （实测：202 条 C2660 里指名叫省略号声明符号的 **0 条**）。
    """
    s = args.strip()
    if s in ('', 'void'):
        return 0
    if s == '...':
        return None                      # 可变参 ⇒ 元数不限，不参与一致性比较
    return s.count(',') + 1


def _collect_sub_calls():
    """→ {sym: {'decl': [(arity, where)], 'calls': [(arity, where)]}}（括号跨行配平）。"""
    info = {}
    for p in gen_files():
        rel = os.path.relpath(p, ROOT)
        txt = strip_comments(open(p, encoding='utf-8', errors='replace').read())
        for m in SUBFN.finditer(txt):
            sym = m.group(0)
            j = m.end()
            while j < len(txt) and txt[j] in ' \t':
                j += 1
            if j >= len(txt) or txt[j] != '(':
                continue
            depth, k = 0, j
            while k < len(txt):
                if txt[k] == '(':
                    depth += 1
                elif txt[k] == ')':
                    depth -= 1
                    if depth == 0:
                        break
                k += 1
            args = txt[j + 1:k]
            # `(void)`/空 = 零参；`(...)` = 可变参（元数不限，返回 None）—— 见 `_arity_of` 的实测说明
            arity = _arity_of(args)
            line = txt.count('\n', 0, m.start()) + 1
            # 声明判定（独立复核后收紧）：生成的声明都在**文件作用域、列 0** 起（`__int64 sub_4B59B0(...)`），
            # 而调用都在函数体内（有缩进）。第一版只看"`;` 结尾 + 前缀像类型"，把调用点也算了进来
            # （`    sub_404350(v50, 1, pszBuf);`）⇒ 151 条 100% 假阳性。现要求列 0。
            ls = txt.rfind('\n', 0, m.start()) + 1
            prefix = txt[ls:m.start()]
            is_decl = (not prefix.startswith((' ', '\t'))) and bool(prefix.strip()) and \
                not re.match(r'\s*(?:return|=|,|\(|\[|if|while|for|switch|else)\b', prefix)
            rec = info.setdefault(sym, {'decl': [], 'calls': []})
            where = '%s:%d' % (rel, line)
            (rec['decl'] if is_decl else rec['calls']).append((arity, where))
    return info


def check_b(verbose=False):
    info = _collect_sub_calls()
    bad = []
    unbounded = 0
    for sym, rec in sorted(info.items()):
        decls = {a for a, _ in rec['decl']}
        # 可变参原型（`int sub_X(...)`）**元数不限** ⇒ 不可能与调用点不一致（实测，见 `_arity_of`）
        if None in decls:
            unbounded += 1
            continue
        if len(decls) != 1:
            if len(decls) > 1:
                bad.append((sym, '多份声明形参数不一致 %s' % sorted(decls),
                            [w for _, w in rec['decl']][:4]))
            continue
        d = decls.pop()
        for a, w in rec['calls']:
            if a is None:                # 调用点也写成 `f(...)` ⇒ 无从比较
                continue
            if a != d:
                bad.append((sym, '声明 %d 参 vs 调用 %d 实参' % (d, a), [w]))
    if bad:
        print('[B] FAIL：%d 处 声明形参数 与 调用实参数 不一致（**可编译但语义可疑**；'
              '不等于 C2660 成因）' % len(bad))
        for sym, why, where in bad:
            print('    %s  %-28s %s' % (sym, why, ', '.join(where[:3])))
    else:
        print('[B] PASS：%d 个 sub_ 符号的声明/调用形参数全部一致（另 %d 个是可变参原型 '
              '`(...)`，元数不限 ⇒ 不参与比较）' % (len(info), unbounded))
    if verbose:
        print('    [info] 见过 %d 个 sub_ 符号；可变参 %d 个；多份声明的 %d 个'
              % (len(info), unbounded,
                 len([r for r in info.values() if len({a for a, _ in r['decl']}) > 1])))
    return len(bad)


def check_c(verbose=False):
    bad = []
    for p in sorted(glob.glob(os.path.join(STRUCTS, '*.json'))):
        cls = os.path.basename(p)[:-5]
        d = json.load(open(p, encoding='utf-8'))
        for addr, m in (d.get('methods') or {}).items():
            if not isinstance(m, dict):
                continue
            sig = str(m.get('signature') or '')
            mm = THISCLASS.search(sig)
            if mm and mm.group(1) != cls:
                bad.append((cls, addr, sig[:76]))
    if bad:
        print('[C] 潜伏（不阻塞编译）：注解签名类前缀 ≠ 所属类 %d 条' % len(bad))
        for it in bad if verbose else bad[:12]:
            print('    %-22s %-12s %s' % it)
        if not verbose and len(bad) > 12:
            print('    ...（--verbose 看全部）')
    else:
        print('[C] PASS：签名类前缀与所属类一致')
    return len(bad)


def check_d(verbose=False):
    """D（根因前置检查，独立复核建议）：注解有 `vtables` 的类，生成头在 +0x0 必须是 vptr。

    实测：80 个类有非空 `vtables`，其中 **64 个**的生成头把 +0x0 发射成 `char _gap_000[N]`
    （`emit_headers` 只发射 `data_members`）⇒ 这些类的 .cpp 一旦出现 `X.__vftable` 就必编译失败。
    这条在 .cpp 写出 `__vftable` **之前**就能报，覆盖面（64 类）大于 A（29 个文件）。

    **2026-09-19 口径修正（长线计划第 1 条）**：类一旦声明 `virtual` 方法，MSVC 会在 +0
    **隐式**放入 vfptr，头文件此时**必须不发射**显式占位（否则显式占位被挤到 +4、其后每个成员
    偏 4 字节——实测 `AStarPathFinder::FindInOpen` 因此只有 94.1%）。所以判据改为
    **「显式 vptr/占位」∨「声明了 virtual」二者之一成立即通过**；两者都没有才是真问题。
    """
    bad, ok = [], 0
    # CRT/STL 类型豁免与 emit 同源（WINDOWS_CRT_TYPES 单一来源 import——防双副本分叉；
    # filebuf 实证：emit 按此表不生成头 ⇒ [D] 不得要求其有生成头）
    try:
        sys.path.insert(0, os.path.join(ROOT, 'pipeline', 'gen'))
        sys.path.insert(0, os.path.join(ROOT, 'pipeline', 'gen', 'stages'))
        from emit_headers import WINDOWS_CRT_TYPES as _CRT
    except Exception:
        _CRT = set()
    for p in sorted(glob.glob(os.path.join(STRUCTS, '*.json'))):
        cls = os.path.basename(p)[:-5]
        d = json.load(open(p, encoding='utf-8'))
        if not (d.get('vtables') or []):
            continue
        if cls in _CRT:
            continue
        hdrs = glob.glob(os.path.join(SRC, '**', cls + '.h'), recursive=True)
        if not hdrs:
            # [vptr 前置门查找面扩展 2026-10-16 verifier] 手写头并存制式回退（R15 纯函数）
            _hv, _hd = handwritten_vptr_verdict(cls, INCLUDE)
            if _hv == 'ok':
                ok += 1
                continue
            bad.append((cls, '(未找到生成头; 手写头 %s: %s)' % (_hv, _hd), d.get('binary_size')))
            continue
        htxt = open(hdrs[0], encoding='utf-8', errors='replace').read()
        if '__vftable' in htxt:
            ok += 1
            continue
        if re.search(r'^\s*virtual\s', htxt, re.M):
            ok += 1          # 编译器提供 +0 的 vfptr，显式占位反而错
            continue
        m = re.search(r'char\s+_gap_000\[(\d+)\]', htxt)
        bad.append((cls, ('_gap_000[%s] @+0x0' % m.group(1)) if m else '无 virtual、无 +0x0 vptr 也无 _gap_000',
                    d.get('binary_size')))
    if bad:
        print('[D] FAIL（根因前置）：注解有 vtables 但生成头 +0x0 不是 vptr 的类 **%d 个**' % len(bad))
        for cls, why, size in (bad if verbose else bad[:15]):
            print('    %-24s size=%-8s %s' % (cls, size, why))
        if not verbose and len(bad) > 15:
            print('    ...（--verbose 看全部；另 %d 个类的头里有 __vftable）' % ok)
    else:
        print('[D] PASS：%d 个有 vtables 的类，生成头 +0x0 都有 vptr' % ok)
    return len(bad)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--check', action='append', default=[])
    ap.add_argument('--strict', action='store_true',
                    help='把潜伏项 C 也算失败')
    ap.add_argument('--verbose', action='store_true')
    # 2026-09-20（三路复核要求的"先做一小步"）：**advisory 模式**。
    # 背景：本工具默认检查集是 A/B/D，而实测 A=132/B=56/D=10 **当前就失败** ⇒
    # 直接把本工具接进门禁会**立刻全红** ✗。advisory 模式只报告、恒 exit 0，
    # 使"存量未清零期间"也能把它接进门禁并**看见计数**；存量清零后再去掉该开关升为硬失败 ✓。
    ap.add_argument('--advisory', action='store_true',
                    help='只报告不失败（恒 exit 0）：存量未清零期间接门禁用')
    args = ap.parse_args()

    for c in args.check:                      # 修复：第一版静默忽略非法名字 ⇒ 假绿门禁
        if c not in VALID_CHECKS:
            print('[ERROR] --check 只接受 %s，收到 %r' % ('/'.join(VALID_CHECKS), c))
            return 2
    want = set(args.check) or {'A', 'B', 'D'}

    hard = 0
    if 'D' in want:
        hard += check_d(args.verbose)
    if 'A' in want:
        hard += check_a(args.verbose)
    if 'B' in want:
        hard += check_b(args.verbose)
    latent = check_c(args.verbose) if ('C' in want or args.strict) else 0
    print()
    # 2026-09-21 F2（评审后续项·假红框定）：advisory 时**先**框定，避免读者/日志把
    # `=> FAIL` 误判为门禁失败 —— 本模式下 exit 恒 0，判定词改 ADVISORY-ONLY（不阻断）✓。
    # 非 advisory 时判定词保持原样 FAIL/PASS（不改检测强度，只改框定）✓。
    if args.advisory:
        print('[ADVISORY] 非门禁报告：以下计数不影响任何退出码')
    verdict = ('ADVISORY-ONLY（不阻断）' if args.advisory
               else ('FAIL' if (hard or (args.strict and latent)) else 'PASS'))
    print('编译阻塞项 %d；潜伏项 %d  => %s' % (hard, latent, verdict))
    if args.advisory:
        print('[ADVISORY] 计数如上，**本模式恒 exit 0** —— 存量清零后才可升为硬失败 ✓')
        return 0
    return 1 if (hard or (args.strict and latent)) else 0


if __name__ == '__main__':
    sys.exit(main())
