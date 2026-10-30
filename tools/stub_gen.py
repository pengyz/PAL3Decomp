#!/usr/bin/env python3
"""tools/stub_gen.py — S2-fail 单元 stub 生成（codegen+stub overlay 设计 §3.2 初版）。

设计契约（docs/specs/2026-10-27-codegen-stub-overlay-design.md）：
  - 每个 S2-fail 单元一个 stub：include 与真身同款头（首段 #include 块原样搬），
    签名结构性一致（从真身单元按 `// 0x` 地址锚点提取），手维护的只有空函数体；
  - 路径约定：unit `pal3/src/Combat/X.cpp` → stub `phase2/stubs/Combat/X_stub.cpp`；
  - stub 不写入 pal3/src（铁律——否则 S2 量到 stub = 假绿）；
  - 初版自动生成、人工修剪；「允许手挑真函数原样嵌入」由人工在生成后进行。

空函数体三规则（2026-10-31 签名普查：2833 锚定函数，void/ctor 约 31%、
int/指针/typedef 元语约 69%、真类值返回仅 `_Texture_uv operator_` 1 例）：
  1. ctor/dtor/无返回型            → { }
  2. void                         → { }
  3. 元语/指针（白名单或尾 *）      → return 0;
  4. 其余（类值/引用/未知）         → return *(T *)0;   （引用形零例，容错保留）

用法:
  python tools/stub_gen.py --all-fail            # 按 probe_census 生成全部 S2-fail stub
  python tools/stub_gen.py --unit pal3/src/X.cpp # 单元生成
"""
import argparse
import json
import re
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
CENSUS = PROJECT_ROOT / 'data' / 'status' / 'probe_census.json'
SRC_ROOT = PROJECT_ROOT / 'pal3' / 'src'
STUB_ROOT = PROJECT_ROOT / 'phase2' / 'stubs'

ANCHOR_RE = re.compile(r'^// 0x([0-9A-Fa-f]{6,8})\s*$', re.M)
# 调用约定/修饰词（返回型里剥掉）
CONV_WORDS = {'__stdcall', '__cdecl', '__fastcall', '__thiscall', 'virtual', 'static'}
# 元语/typedef 白名单（`return 0;` 可赋形）
PRIM_RE = re.compile(
    r'^(?:unsigned\s+|signed\s+)?(?:void|char|short|int|long|float|double|bool|BOOL|'
    r'__int8|__int16|__int32|__int64|BYTE|WORD|DWORD|UINT|ULONG|LONG|'
    r'WPARAM|LPARAM|LRESULT|UINT_PTR|INT_PTR|LONG_PTR|ULONG_PTR|size_t|'
    r'HWND|HANDLE|HRESULT|HINSTANCE|HDC|LPSTR|LPCSTR|LPVOID|CHAR|WCHAR|'
    r'_BYTE|_WORD|_DWORD|_QWORD|u8|u16|u32|s8|s16|s32)$')


# ── 纯函数区（R15 单测点）─────────────────────────────────────────
def _post_prelude_lines(text):
    """前导序言（空行/注释/#行连run）之后的行。"""
    lines = text.splitlines()
    i = 0
    while i < len(lines):
        s = lines[i].strip()
        if not s or s.startswith('//') or s.startswith('#'):
            i += 1
        else:
            break
    return lines[i:]


def extract_data_items(text):
    """顶层数定义/声明语句（';' 收口；函数定义体整段跳过）。
    判据：深度回 0 的 '}' 同行无 ';' ⇒ 函数定义体收口（buf 丢弃）；
    否则 ';' 收口 ⇒ 数据/原型语句（globals.cpp 3011 行全属此类）。"""
    items, buf, depth = [], '', 0
    for l in _post_prelude_lines(text):
        s = l.strip()
        if depth == 0 and not buf and (not s or s.startswith('//')):
            continue
        buf = (buf + '\n' + l).strip()
        # 大括号深度（初始式 {..} 与函数体同形——靠收口字符区分）
        for ch in l:
            if ch == '{':
                depth += 1
            elif ch == '}':
                depth -= 1
                if depth == 0:
                    rest = l[l.rfind('}') + 1:]
                    if ';' not in rest:
                        buf = ''          # 函数定义体收口——丢弃
        if buf and ';' in l and depth == 0:
            stmt = buf[:buf.rfind(';') + 1]
            items.append({'text': stmt, 'label': stmt.replace('\n', ' ')[:60]})
            buf = ''
    return items


def extract_includes(text):
    """真身前导序言原样搬（stub 与真身同款头）。
    [2026-10-31 修] 原实现遇 #define/#undef 即断（CCBStage 病灶：`#define private
    public / #include <string> / #undef private` 序言被截断 ⇒ 类未定义 C2653）。
    现取「空行/注释/#行」前导连run（截尾空行）。"""
    out = []
    for line in text.splitlines():
        s = line.strip()
        if not s or s.startswith('//') or s.startswith('#'):
            out.append(line)
        else:
            break
    while out and not out[-1].strip():
        out.pop()
    return '\n'.join(out)


def _signature_after_anchor(after):
    """锚点后取函数签名（跳过 #pragma / 注释行；跨行签名按括号配平拼接）。
    [2026-10-31 修] 原实现停在首个含 '(' 的行 ⇒ 多行参数表截断（C2143 missing ')'）；
    现按 '('==')' 配平收口。前置 ';'（顶层数定义/函数指针变量）⇒ 非函数，返回 None。"""
    brace = after.find('{')
    if brace < 0 or brace > 4000:
        return None
    pre = after[:brace]
    # 函数签名不允许 ';'——顶层数定义/函数指针变量等非函数项跳过（人工修剪面）
    if ';' in pre:
        return None
    lines = []
    for l in pre.splitlines():
        s = l.strip()
        if not s or s.startswith('#') or s.startswith('//'):
            continue
        lines.append(s)
    if not lines:
        return None
    sig, depth = '', 0
    for l in lines:
        sig = (sig + ' ' + l).strip()
        depth = sig.count('(') - sig.count(')')
        if '(' in sig and depth <= 0:
            break
    return sig if '(' in sig and sig.count('(') == sig.count(')') else None


def split_signature(sig):
    """签名 → (返回型, 名)。无返回型（ctor/dtor/转换算子）返回型为 ''。
    名含 '::'/'~'/'operator_' 全形；调用约定/修饰词从返回型剥离；参数表不解析。"""
    head = sig.split('(')[0].strip()
    m = re.search(r'(operator\s*\S+|[\w:~]+)\s*$', head)
    if not m:
        return None, None
    name = m.group(1)
    ret = ' '.join(t for t in head[:m.start()].split() if t not in CONV_WORDS)
    # 无返回型判据：ret 为空（name 自含限定）
    return ret, name


def stub_body(ret, name):
    """空体三规则。ret=''（ctor/dtor）或 void → { }；白名单/指针 → return 0;；
    其余 → return *(T *)0;（引用形剥 &/const 后同样式）。"""
    if not ret or ret == 'void':
        return '{ }'
    toks = [t for t in ret.split() if t not in CONV_WORDS]
    if not toks:
        return '{ }'
    r = ' '.join(toks)
    if r.endswith('*') or PRIM_RE.match(r):
        return '{ return 0; }'
    base = r.rstrip('&').replace('const', '').strip()
    return '{ return *(%s *)0; }' % base


def extract_functions(text):
    """真身单元 → 函数清单 [{addr,name,ret,sig}]（按 // 0x 锚点）。"""
    funcs = []
    for m in ANCHOR_RE.finditer(text):
        sig = _signature_after_anchor(text[m.end():])
        if not sig:
            continue
        ret, name = split_signature(sig)
        if name is None:
            continue
        funcs.append({'addr': '0x' + m.group(1).upper(), 'name': name, 'ret': ret,
                      'sig': sig})
    return funcs


def render_stub(unit_rel, includes, funcs, data=None):
    """stub 文本渲染（确定性——同输入同输出）。数据项带 // D 标记（错行归属用）。"""
    lines = [
        '// AUTO-GENERATED by tools/stub_gen.py - DO NOT hand-edit here.',
        '// Stub for S2-fail unit: %s' % unit_rel,
        '// Purpose: link closure only (codegen+stub overlay design M1).',
        '// Empty bodies are intentional: run-time behavior is NOT represented.',
        '',
    ]
    if includes:
        lines.append(includes)
        lines.append('')
    for d in (data or []):
        lines.append('// D  %s' % d['label'])
        lines.append(d['text'])
        lines.append('')
    for f in funcs:
        lines.append('// %s  (%s)' % (f['addr'], f['name']))
        lines.append(f['sig'])
        lines.append(stub_body(f['ret'], f['name']))
        lines.append('')
    return '\n'.join(lines)


def stub_path_for_unit(unit_rel):
    """unit 'pal3/src/Combat/X.cpp' → phase2/stubs/Combat/X_stub.cpp（设计 §3.2）。"""
    rel = unit_rel.replace('\\', '/')
    if rel.startswith('pal3/src/'):
        rel = rel[len('pal3/src/'):]
    stem = rel[:-4] if rel.endswith('.cpp') else rel
    return STUB_ROOT / (stem + '_stub.cpp')


def generate_for_unit(unit_path, out_path=None, skip_names=None, skip_data=None):
    p = Path(unit_path)
    text = p.read_text(encoding='utf-8', errors='replace')
    # [铁律护栏 2026-10-31] 一律相对仓根归一后再算 stub 路径——绝对路径会让
    # Path / 'D:/...' 连接失效（Windows 盘符绝对形替换基），stub 会落进
    # pal3/src（设计明令禁止：S2 量到 stub = 假绿）。
    rel = str(p.resolve().relative_to(PROJECT_ROOT)).replace('\\', '/')
    funcs = extract_functions(text)
    data = extract_data_items(text)
    if skip_names:
        funcs = [f for f in funcs if f['name'] not in skip_names]
    if skip_data:
        data = [d for d in data if d['label'] not in skip_data]
    body = render_stub(rel, extract_includes(text), funcs, data)
    out = Path(out_path) if out_path else stub_path_for_unit(rel)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(body, encoding='utf-8')
    return out, len(funcs) + len(data)


# ── 编译驱动修剪（设计 §3.2「人工修剪」的机械化初刀）────────────────
def stub_function_spans(text):
    """stub 文本 → [(起始行1基, 结束行1基, kind, label)]（// 0x 函数段 + // D 数据段）。"""
    lines = text.splitlines()
    marks = [(i, l) for i, l in enumerate(lines)
             if l.startswith('// 0x') or l.startswith('// D  ')]
    spans = []
    for k, (i, l) in enumerate(marks):
        end = marks[k + 1][0] - 1 if k + 1 < len(marks) else len(lines)
        if l.startswith('// D  '):
            spans.append((i + 1, end, 'data', l[6:].strip()))
        else:
            spans.append((i + 1, end, 'func', l.split('(')[-1].rstrip(')').strip()))
    return spans


def prune_stub(unit_rel, run_cl, wpath, incs, max_rounds=12):
    """编译驱动修剪：错行→函数/数据段→剔除重生成，直到编译绿或无归属错。
    被剔除项以 `// PRUNED` 债账注记留档（人工修剪面，链接期 LNK2001 兜底催补）。"""
    src = PROJECT_ROOT / unit_rel
    dropped_f, dropped_d, report, ok = set(), set(), [], False
    for _ in range(max_rounds):
        out, _ = generate_for_unit(src, skip_names=dropped_f, skip_data=dropped_d)
        text = out.read_text(encoding='utf-8')
        spans = stub_function_spans(text)
        errs_txt, err = run_cl(incs + ['/Fo' + wpath(str(out) + '.obj'), '/c', wpath(str(out))])
        err_items, unattributed = set(), []
        for l in errs_txt.splitlines():
            if ' error ' not in l:
                continue
            m = re.search(r'\((\d+)\) : (?:fatal )?error', l)
            if not m:
                unattributed.append(l)
                continue
            ln = int(m.group(1))
            hit = [s for s in spans if s[0] <= ln <= s[1]]
            if hit:
                err_items.add(hit[0][2:])
            else:
                unattributed.append(l)
        if not err_items and not unattributed and err is None:
            ok = True
            break
        if not err_items:
            report = unattributed
            break
        for kind, name in err_items:
            (dropped_f if kind == 'func' else dropped_d).add(name)
        report += sorted('%s:%s' % it for it in err_items)
    # 收口：重生成 + PRUNED 债账注记（无论成功与否，债账都落盘）
    out, _ = generate_for_unit(src, skip_names=dropped_f, skip_data=dropped_d)
    if dropped_f or dropped_d:
        text = out.read_text(encoding='utf-8')
        text += '\n// PRUNED (hand-trim debt, compile-driven):\n'
        for n in sorted(dropped_f):
            text += '//   func %s\n' % n
        for n in sorted(dropped_d):
            text += '//   data %s\n' % n
        out.write_text(text, encoding='utf-8')
    return sorted(dropped_f) + sorted(dropped_d), report, ok


def main():
    ap = argparse.ArgumentParser(description='S2-fail 单元 stub 生成')
    ap.add_argument('--all-fail', action='store_true', help='按 probe_census 全量生成')
    ap.add_argument('--unit', help='指定单元（pal3/src/...）')
    ap.add_argument('--out', help='输出路径（仅 --unit 用）')
    ap.add_argument('--prune', action='store_true',
                    help='编译驱动修剪（剔除签名漂移/残留函数，落 PRUNED 债账）')
    args = ap.parse_args()
    if not (args.all_fail or args.unit):
        ap.error('需要 --all-fail 或 --unit')

    units = []
    if args.all_fail:
        c = json.loads(CENSUS.read_text(encoding='utf-8'))
        units = [x['unit'] for x in c['s2']['results'] if x.get('status') != 'ok']
    if args.unit:
        units.append(args.unit)

    if args.prune:
        sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))
        import probe_compile as pc
        incs_base = ['/I' + pc.wpath(d) for d in pc.INCLUDE_DIRS]
        n_drop = 0
        for u in units:
            unit_dir = str(Path(u).parent)
            incs = incs_base + ['/I' + pc.wpath(str(PROJECT_ROOT / unit_dir))]
            dropped, report, ok = prune_stub(u, pc.run_cl, pc.wpath, incs)
            n_drop += len(dropped)
            print('prune %-45s ok=%s dropped=%d %s'
                  % (u, ok, len(dropped), ('| ' + ', '.join(dropped[:4])) if dropped else ''))
        print('prune done | dropped total %d' % n_drop)
        return

    total = 0
    for u in units:
        src = PROJECT_ROOT / u
        if not src.exists():
            print('MISSING unit: %s' % u, file=sys.stderr)
            continue
        out, n = generate_for_unit(src, args.out if args.unit else None)
        total += n
        print('stub %-60s funcs=%d' % (str(out.relative_to(PROJECT_ROOT)), n))
    print('units %d | functions %d' % (len(units), total))


if __name__ == '__main__':
    main()
