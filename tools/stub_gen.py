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
CONV_WORDS = {'__stdcall', '__cdecl', '__fastcall', '__thiscall', 'virtual', 'static',
              'extern', '"C"', 'WINAPI', 'APIENTRY', 'CALLBACK', 'NTAPI', 'PASCAL'}
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
    其余 → return *(T *)0;（引用形剥 &/const 后同样式）。
    [2026-10-31 修] 先剥调用约定词再判 void——'void __cdecl' 曾落 return 0;
    分支 ⇒ C2562 连锁（nullsub 族 15 件+sub_ 系全灭根因）。"""
    if not ret:
        return '{ }'
    toks = [t for t in ret.split() if t not in CONV_WORDS]
    if not toks:
        return '{ }'
    r = ' '.join(toks)
    if r == 'void':
        return '{ }'
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


def definition_dups():
    """跨单元同名定义普查（2026-10-31 LNK2005 根因）：同名函数被多个单元锚定
    （codegen 聚合面重复）⇒ 真身优先，stub 间先到先得（字典序），其余剔除。
    返回 {unit: set(names_to_skip)}。"""
    c = json.loads(CENSUS.read_text(encoding='utf-8'))
    status = {x['unit']: x.get('status') for x in c['s2']['results']}
    owners = {}
    for x in c['s2']['results']:
        u = x['unit']
        try:
            t = (PROJECT_ROOT / u).read_text(encoding='utf-8', errors='replace')
        except OSError:
            continue
        for f in extract_functions(t):
            owners.setdefault(f['name'], []).append(u)
    drops = {}
    for name, us in owners.items():
        if len(us) < 2:
            continue
        real = sorted(u for u in us if status.get(u) == 'ok')
        keep = real[0] if real else sorted(us)[0]
        for u in us:
            if u != keep and status.get(u) != 'ok':
                drops.setdefault(u, set()).add(name)
    return drops


# ── 虚槽批量供给（2026-10-31 LNK2001 大类）──────────────────────────
SLOT_DECL_RE = re.compile(
    r'^\s*(?:virtual\s+|static\s+)?'
    r'((?:[\w:\*&\s]|::)*?)\s*(slot_\d+)\s*\(([^;{]*)\)\s*(?:const\s*)?;\s*(?://.*)?$')


def parse_header_slots(text):
    """类头 → [(cls, ret, name, params)]。slot_N 声明挂类上下文（brace 深度跟踪）。"""
    items, cls, depth = [], None, 0
    for line in text.splitlines():
        s = line.strip()
        if depth == 0:
            m = re.match(r'^(?:template\s*<[^>]*>\s*)?(?:class|struct)\s+(\w+)', s)
            if m:
                cls = m.group(1)
        else:
            m = SLOT_DECL_RE.match(line)
            if m and cls:
                ret = ' '.join(m.group(1).split())
                items.append((cls, ret, m.group(2), m.group(3).strip()))
        depth += line.count('{') - line.count('}')
        if depth <= 0:
            depth = 0
    return items


def generate_virtual_slots(out_dir=None):
    """全仓类头 slot_N 声明 → 批量定义体 stub（逐头一文件；未被真身/其它 stub 定义者）。
    语义无关（链接闭合用）；命名债（slot_N=地址占位名）归 annotation 阶段。"""
    c = json.loads(CENSUS.read_text(encoding='utf-8'))
    all_units = [x['unit'] for x in c['s2']['results']]
    # 定义面普查：真身 + 已生成 stub 全文（排除本生成面自身，防再生成自吞）
    haystack = []
    for u in all_units:
        try:
            haystack.append((PROJECT_ROOT / u).read_text(encoding='utf-8', errors='replace'))
        except OSError:
            pass
    for f in STUB_ROOT.rglob('*_stub.cpp'):
        if out_dir is None and '_slots' in f.parts:
            continue                      # 虚槽生成面自身不进定义普查（防再生成自吞）
        haystack.append(f.read_text(encoding='utf-8'))
    hay = '\n'.join(haystack)

    out_root = Path(out_dir) if out_dir else STUB_ROOT / '_slots'
    n_files = n_defs = 0
    for h in sorted(SRC_ROOT.rglob('*.h')):
        slots = parse_header_slots(h.read_text(encoding='utf-8', errors='replace'))
        defs, seen = [], set()
        for cls, ret, name, params in slots:
            key = (cls, name, params)
            if key in seen:
                continue
            seen.add(key)
            if re.search(r'\b%s::%s\s*\(' % (re.escape(cls), re.escape(name)), hay):
                continue                      # 已有定义面（真身/其它 stub）
            sig = '%s %s::%s(%s)' % (ret or 'void', cls, name, params)
            defs.append({'addr': 'header', 'name': '%s::%s' % (cls, name),
                         'ret': ret, 'sig': sig})
        if not defs:
            continue
        rel = str(h.resolve().relative_to(SRC_ROOT)).replace('\\', '/')
        inc = '#include "globals.h"\n#include "pal3/ida_defs.h"\n#include "%s"' % rel
        body = render_stub('virtual slots from %s' % rel, inc, defs)
        out = out_root / (rel.replace('/', '_') + '_slots_stub.cpp')
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(body, encoding='utf-8')
        n_files += 1
        n_defs += len(defs)
    return n_files, n_defs


# ── 按需供给（demand-driven，link 日志即需求单）────────────────────
_ACCESS_RE = re.compile(r'^\s*(?:public|private|protected):\s*')
_DLLIMPORT_MARK = '__declspec(dllimport)'


def parse_link_display(display):
    """LINK 显示名 → 条目。'public: int __thiscall X::f(int)' → ('func', ret, name, params)；
    'char * g_Foo' → ('data', 'char *', 'g_Foo', ''); dllimport → ('dllimport', ...);
    裸 C 符号（_NtCurrentTeb 等无引号形）→ ('cfunc', ...)。显示名即完整签名。"""
    s = _ACCESS_RE.sub('', display.strip())
    if _DLLIMPORT_MARK in s:
        return ('dllimport', None, None, None)
    i = s.find('(')
    if i < 0:
        # 裸 C 符号：单标识符、无型（LINK 无引号打印形）⇒ C 函数合成
        if re.match(r'^[A-Za-z_][\w$?@]*$', s):
            return ('cfunc', 'void *', s, 'void')
        # 数据形：末标识符为名，其余为型（static/class 修饰保留）
        m = re.search(r'([\w:~]+)\s*$', s)
        if not m:
            return ('unknown', None, None, None)
        return ('data', s[:m.start()].strip(), m.group(1), '')
    head, rest = s[:i].strip(), s[i:]
    depth = 0
    for j, ch in enumerate(rest):
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
            if depth == 0:
                break
    params = rest[1:j].strip()
    m = re.search(r'(operator\s*\S+|[\w:~]+)\s*$', head)
    if not m:
        return ('unknown', None, None, None)
    name = m.group(1)
    ret = head[:m.start()].strip()
    return ('func', ret, name, params)


_GLOBALS_DECL_CACHE = {}


_DECL_LOOKUP_CACHE = {}
# 特形表（编译器 C2556/C2733 自证形 + windows.h 形；2026-10-31 人工修剪面）
KNOWN_CFUNC_FORMS = {
    '_NtCurrentTeb': 'struct _TEB * NtCurrentTeb(void)',
    '_WinMain@16': 'int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)',
}


def decl_lookup(name):
    """include 链既有声明原文（ida_defs.h/globals.h 的 `ret name(params);` 形）。
    合成定义必须挂既有声明形——同名异形（void* vs _TEB* / void vs uint）
    是 C2556/C2733 的根因（2026-10-31 实测 NtCurrentTeb+Bink 三件）。
    extern "C" 块内声明带链接域前缀（定义缺包裹 ⇒ C2733 second C linkage）。"""
    if not _DECL_LOOKUP_CACHE:
        for p in (PROJECT_ROOT / 'include' / 'pal3' / 'ida_defs.h', SRC_ROOT / 'globals.h'):
            if not p.exists():
                continue
            t = p.read_text(encoding='utf-8', errors='replace')
            in_c = False
            for line in t.splitlines():
                if 'extern "C"' in line:
                    in_c = '{' in line
                if line.strip().startswith('}') and in_c:
                    in_c = False
                m = re.match(r'^\s*((?:[\w:\s\*&]|::)*?\b[\w:~]+)\s*\(([^;{]*)\)\s*;',
                             line)
                if not m:
                    continue
                nm = re.search(r'([\w:~]+)\s*$', m.group(1))
                if not nm:
                    continue
                form = '%s(%s)' % (' '.join(m.group(1).split()), m.group(2).strip())
                if in_c:
                    form = 'extern "C" ' + form
                _DECL_LOOKUP_CACHE.setdefault(nm.group(1), form)
    return _DECL_LOOKUP_CACHE.get(name)


def globals_decl(name):
    """globals.h 中 name 的声明形（去 extern）——数据定义挂声明形保 mangling 对齐。"""
    if not _GLOBALS_DECL_CACHE:
        p = SRC_ROOT / 'globals.h'
        if p.exists():
            t = p.read_text(encoding='utf-8', errors='replace')
            for m in re.finditer(
                    r'^extern\s+((?:[\w:\s\*&]|::)*?\b[\w:~]+(?:\s*\[[0-9]*\])*)\s*;',
                    t, re.M):
                decl = ' '.join(m.group(1).split())
                nm = re.search(r'([\w:~]+)(?:\s*\[[0-9]*\])?\s*$', decl)
                if nm:
                    _GLOBALS_DECL_CACHE[nm.group(1)] = decl
    return _GLOBALS_DECL_CACHE.get(name)


_SURFACE_DEF_RE = re.compile(
    r'^\s*((?:[\w:\*&\s~]|::)*?[\w:~]+)\s*\([^;{]*\)\s*\n\s*\{', re.M)
_SURFACE_DATA_RE = re.compile(
    r'^\s*[\w:\*&\s~]*?([\w:~]+)\s*(?:\[[0-9]*\])?\s*=\s*\{?', re.M)


def defined_surface_names():
    """已定义面普查（单元 stub/_real/_slots 的定义名集合）——防供给双定义 LNK2005
    （v2 D0-2.1：手修/真函数嵌入后同名供给 = 双定义，ArraySort 案）。"""
    names = set()
    files = list(STUB_ROOT.glob('*_stub.cpp'))
    for sub in ('_real', '_slots'):
        d = STUB_ROOT / sub
        if d.exists():
            files += list(d.glob('*.cpp'))
    for f in files:
        t = f.read_text(encoding='utf-8', errors='replace')
        for m in _SURFACE_DEF_RE.finditer(t):
            nm = re.search(r'([\w:~]+)\s*$', m.group(1))
            if nm:
                names.add(nm.group(1))
        for m in _SURFACE_DATA_RE.finditer(t):
            names.add(m.group(1))
    return names


def sym_base_forms(name):
    """显示名 → 匹配形集（限定形 + 裸形 + 去装饰形）。"""
    forms = {name}
    if '::' in name:
        forms.add(name.split('::')[-1])
    ms = re.match(r'^_(\w+)@(\d+)$', name)
    if ms:
        forms.add(ms.group(1))
    elif name.startswith('_'):
        forms.add(name[1:])
    return forms


def generate_supply_from_log(log_paths, out_root=None, exclude=None):
    """link 日志/需求台账 → 按需供给 stub（_supply/ 逐类文件 + 自由件合集）。
    语义无关（链接闭合用）；dllimport 误标件留缺口（归 annotation 线）。
    显示名含 class X 内联详型符 ⇒ 自由件零前向声明；成员定义挂类头（完整类）。
    log_paths：多源并集（demand_ledger.txt 累积，防迭代振荡）。
    exclude：自愈修剪排除集（display 全串）。"""
    exclude = exclude or set()
    disp = set()
    for lp in (log_paths if isinstance(log_paths, (list, tuple)) else [log_paths]):
        text = Path(lp).read_text(encoding='utf-8', errors='replace')
        if 'LNK2001' in text or 'LNK2019' in text:
            for l in text.splitlines():      # link 日志形：只认 LNK 行内符号
                if 'LNK2001' not in l and 'LNK2019' not in l:
                    continue
                i = l.find('symbol "')
                if i >= 0:
                    j = l.find('"', i + 8)
                    disp.add(l[i + 8:j])
                else:
                    m = re.search(r'symbol\s+([A-Za-z_][\w$?@]*)\s*$', l)
                    if m:                    # 裸 C 符号（无引号形）
                        disp.add(m.group(1))
        else:
            for l in text.splitlines():      # ledger 形（两态行 + 旧版纯行）
                l = l.strip()
                if not l or l.startswith('#'):
                    continue
                if l.startswith('retired\t'):
                    continue                  # 退役条目不得复活（v2 D0-2.1）
                if l.startswith('active\t'):
                    l = l[len('active\t'):]
                disp.add(l)
    # 持久排除面（人工退役/绕行，v2 D0-2.1）
    ex_file = STUB_ROOT / '_supply' / 'exclude.txt'
    if ex_file.exists():
        for l in ex_file.read_text(encoding='utf-8').splitlines():
            l = l.strip()
            if l and not l.startswith('#'):
                exclude.add(l)
    out_root = Path(out_root) if out_root else STUB_ROOT / '_supply'
    if out_root.exists():
        for f in out_root.glob('*.cpp'):
            f.unlink()                      # 陈旧供给面清场（防旧定义残留/震荡）
    out_root.mkdir(parents=True, exist_ok=True)

    hdr_of = {}
    for h in SRC_ROOT.rglob('*.h'):
        t = h.read_text(encoding='utf-8', errors='replace')
        # [2026-10-31 修] 只认真定义头（开括号行）——前向声明 `class X;`
        # 曾被误索引 ⇒ CCBItemWindow 挂到 CCBControlWindow.h ⇒ C2027。
        for m in re.finditer(r'^(?:class|struct)\s+(\w+)[^;{]*\{', t, re.M):
            hdr_of.setdefault(m.group(1), h)

    groups = {}
    skipped = []
    defined = defined_surface_names()
    for display in sorted(disp):
        if display in exclude:
            continue
        kind, ret, name, params = parse_link_display(display)
        if kind in ('dllimport', 'unknown'):
            skipped.append((kind, display))
            continue
        # 已定义面跳过（手修/真函数/_slots 同名 ⇒ 供给=双定义 LNK2005）
        if name and (name in defined or ('::' not in name and sym_base_forms(name) & defined)):
            continue
        cls = name.split('::')[0] if '::' in name else ''
        if kind == 'cfunc':
            # 裸 C 符号：先挂既有声明形（特形表→decl_lookup）；无源可挂才
            # 装饰感知合成（cdecl 去一底线、stdcall @N 按字节数），heal 兜底。
            form = KNOWN_CFUNC_FORMS.get(name) or decl_lookup(name) \
                or (decl_lookup(name[1:]) if name.startswith('_') else None)
            if form:
                f_ret, _ = split_signature(form)
                sig = form
            else:
                ms = re.match(r'^_(\w+)@(\d+)$', name)
                if ms:
                    nb = int(ms.group(2))
                    plist = ', '.join(['int'] * (nb // 4)) or 'void'
                    f_ret, sig = 'int', 'extern "C" int __stdcall %s(%s)' % (ms.group(1), plist)
                elif name.startswith('_'):
                    f_ret, sig = 'void *', 'extern "C" void * %s(void)' % name[1:]
                else:
                    f_ret, sig = 'void *', 'extern "C" void * %s(void)' % name
            groups.setdefault(cls, []).append(
                ('func', {'addr': 'supply', 'name': display,
                          'ret': f_ret or 'void *', 'sig': sig}))
            continue
        if kind == 'func':
            if not ret:                                  # ctor/dtor
                sig = '%s(%s)' % (name, params)
                f_ret, f_name = '', name
            else:
                # [2026-10-31 修] 成员定义禁写 __thiscall（C4234+C2562 连锁：
                # 成员默认 __thiscall，行内书写被 MSVC6 拒）；virtual 同剥。
                # 自由件保留 __stdcall/__cdecl（mangling 依词）。
                drop = {'virtual'}
                if '::' in name:
                    drop.add('__thiscall')
                clean = ' '.join(t for t in ret.split() if t not in drop)
                sig = '%s %s(%s)' % (clean, name, params)
                f_ret, f_name = clean, name
            groups.setdefault(cls, []).append(
                ('func', {'addr': 'supply', 'name': display,
                          'ret': f_ret, 'sig': sig}))
        else:
            # [2026-10-31 修] 数据定义挂 globals.h 声明形（MSVC6 数组数据按指针
            # mangling——display 'char * g_X' 实为 `char g_X[3]` 的 3PADA 还原形；
            # 按 display 直出 ⇒ C2372 缩进差异 + mangling 不对齐）。
            decl = globals_decl(name)
            if decl:
                text = '%s = {0};' % decl
            else:
                clean = ' '.join(t for t in ret.split() if t not in ('virtual', 'static'))
                text = '%s %s = {0};' % (clean, name)
            groups.setdefault(cls, []).append(
                ('data', {'text': text, 'label': display}))

    files = 0
    for cls, items in sorted(groups.items()):
        incs = ['windows.h', 'globals.h', 'pal3/ida_defs.h']
        if cls and cls in hdr_of:
            rel = str(hdr_of[cls].resolve().relative_to(SRC_ROOT)).replace('\\', '/')
            incs.append(rel)
        funcs = [it for k, it in items if k == 'func']
        data = [it for k, it in items if k == 'data']
        body = render_stub('missing-symbol supply (%s)' % (cls or 'free'),
                           '\n'.join('#include "%s"' % x for x in incs),
                           funcs, data)
        out = out_root / (('%s_supply_stub.cpp' % cls) if cls else '_free_supply_stub.cpp')
        out.write_text(body, encoding='utf-8')
        files += 1
    return files, sum(len(v) for v in groups.values()), skipped


def generate_for_unit(unit_path, out_path=None, skip_names=None, skip_data=None,
                      notes=None):
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
    if notes:
        body += '\n' + '\n'.join(notes) + '\n'
    out = Path(out_path) if out_path else stub_path_for_unit(rel)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(body, encoding='utf-8')
    return out, len(funcs) + len(data)


# ── 编译驱动修剪（设计 §3.2「人工修剪」的机械化初刀）────────────────
def stub_function_spans(text):
    """stub 文本 → [(起始行1基, 结束行1基, kind, label)]（// 0x|supply 函数段 + // D 数据段）。"""
    lines = text.splitlines()
    marks = [(i, l) for i, l in enumerate(lines)
             if l.startswith('// 0x') or l.startswith('// D  ') or l.startswith('// supply')]
    spans = []
    for k, (i, l) in enumerate(marks):
        end = marks[k + 1][0] - 1 if k + 1 < len(marks) else len(lines)
        if l.startswith('// D  '):
            spans.append((i + 1, end, 'data', l[6:].strip()))
        elif l.startswith('// supply'):
            a, b = l.find('('), l.rfind(')')
            spans.append((i + 1, end, 'func', l[a + 1:b] if a >= 0 and b > a else l))
        else:
            spans.append((i + 1, end, 'func', l.split('(')[-1].rstrip(')').strip()))
    return spans


def prune_stub(unit_rel, run_cl, wpath, incs, max_rounds=12, base_skip=None):
    """编译驱动修剪：错行→函数/数据段→剔除重生成，直到编译绿或无归属错。
    被剔除项以 `// PRUNED` 债账注记留档（人工修剪面，链接期 LNK2001 兜底催补）。"""
    src = PROJECT_ROOT / unit_rel
    base_skip = base_skip or set()
    dropped_f, dropped_d, report, ok = set(), set(), [], False
    for _ in range(max_rounds):
        out, _ = generate_for_unit(src, skip_names=(base_skip | dropped_f),
                                   skip_data=dropped_d)
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
    notes = []
    if dropped_f or dropped_d:
        notes.append('// PRUNED (hand-trim debt, compile-driven):')
        notes += ['//   func %s' % n for n in sorted(dropped_f)]
        notes += ['//   data %s' % n for n in sorted(dropped_d)]
    if base_skip:
        notes.append('// DUP-FALLBACK (defined elsewhere, LNK2005 dedup):')
        notes += ['//   %s' % n for n in sorted(base_skip)]
    out, _ = generate_for_unit(src, skip_names=(base_skip | dropped_f),
                               skip_data=dropped_d, notes=notes or None)
    return sorted(dropped_f) + sorted(dropped_d), report, ok


def main():
    ap = argparse.ArgumentParser(description='S2-fail 单元 stub 生成')
    ap.add_argument('--all-fail', action='store_true', help='按 probe_census 全量生成')
    ap.add_argument('--unit', help='指定单元（pal3/src/...）')
    ap.add_argument('--out', help='输出路径（仅 --unit 用）')
    ap.add_argument('--prune', action='store_true',
                    help='编译驱动修剪（剔除签名漂移/残留函数，落 PRUNED 债账）')
    ap.add_argument('--vslots', action='store_true',
                    help='虚槽批量供给（类头 slot_N 声明 → _slots/ 批量定义体）')
    ap.add_argument('--supply-log', help='按需供给（link 日志 unresolved → _supply/）')
    ap.add_argument('--retire', help='退役供给条目（ledger 标 retired + 原子重生成；'
                                     '实删后须 mock_link 闭合回归）')
    args = ap.parse_args()
    if args.retire:
        ledger = PROJECT_ROOT / 'build' / 'mock_link' / 'demand_ledger.txt'
        states = {}
        if ledger.exists():
            for l in ledger.read_text(encoding='utf-8').splitlines():
                l = l.strip()
                if not l:
                    continue
                st, sym = (l.split('\t', 1) + ['active'])[:2] if '\t' in l else ('active', l)
                states[sym] = 'retired' if st == 'retired' else 'active'
        n = 0
        for sym in list(states):
            if args.retire in sym and states[sym] != 'retired':
                states[sym] = 'retired'
                n += 1
        ledger.parent.mkdir(parents=True, exist_ok=True)
        ledger.write_text(''.join('%s\t%s\n' % (v, k) for k, v in sorted(states.items())),
                          encoding='utf-8')
        paths = []
        link_log = PROJECT_ROOT / 'build' / 'mock_link' / 'link.log'
        if link_log.exists():
            paths.append(str(link_log))
        paths.append(str(ledger))
        files, m, skipped = generate_supply_from_log(paths)
        print('retire: %d 条标 retired | 供给重生成 %d files/%d defs | 下一步: mock_link 闭合回归'
              % (n, files, m))
        return
    if args.supply_log:
        # 需求并集：当轮日志 + demand_ledger（累积台账，防迭代振荡）
        paths = [args.supply_log]
        ledger = Path(args.supply_log).parent / 'demand_ledger.txt'
        if ledger.exists():
            paths.append(str(ledger))
        # 自愈循环：编译驱动剔除病件（与 stub 同款错行归属），直到全绿或无归属
        sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))
        import probe_compile as pc
        incs = ['/I' + pc.wpath(d) for d in pc.INCLUDE_DIRS]
        exclude = set()
        for _ in range(8):
            files, n, skipped = generate_supply_from_log(paths, exclude=exclude)
            out_root = STUB_ROOT / '_supply'
            bad = set()
            for f in sorted(out_root.glob('*.cpp')):
                txt = f.read_text(encoding='utf-8')
                spans = stub_function_spans(txt)
                errs, err = pc.run_cl(incs + ['/Fo' + pc.wpath(str(f) + '.obj'),
                                              '/c', pc.wpath(str(f))], timeout=60)
                for l in errs.splitlines():
                    if ' error ' not in l:
                        continue
                    m = re.search(r'\((\d+)\) : (?:fatal )?error', l)
                    if not m:
                        bad.add(None)
                        continue
                    ln = int(m.group(1))
                    hit = [s for s in spans if s[0] <= ln <= s[1]]
                    bad.add(hit[0][3] if hit else None)
            if not bad:
                break
            exclude |= {b for b in bad if b}
        print('supply: %d files | %d defs | excluded %d | skipped %d'
              % (files, n, len(exclude), len(skipped)))
        for k, d in skipped[:10]:
            print('   skip [%s] %s' % (k, d[:90]))
        for b in sorted(exclude)[:15]:
            print('   excluded %s' % b[:90])
        return
    if args.vslots:
        n_files, n_defs = generate_virtual_slots()
        print('virtual slots: %d files | %d defs' % (n_files, n_defs))
        return
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
        drops = definition_dups()
        n_drop = 0
        for u in units:
            unit_dir = str(Path(u).parent)
            incs = incs_base + ['/I' + pc.wpath(str(PROJECT_ROOT / unit_dir))]
            dropped, report, ok = prune_stub(u, pc.run_cl, pc.wpath, incs,
                                             base_skip=drops.get(u, set()))
            n_drop += len(dropped)
            print('prune %-45s ok=%s dropped=%d %s'
                  % (u, ok, len(dropped), ('| ' + ', '.join(dropped[:4])) if dropped else ''))
        print('prune done | dropped total %d' % n_drop)
        # 债账自动入账（v2 D0-2.3：stub 内注记会被再生成灭失——台账才是权威）
        ledger_p = PROJECT_ROOT / 'data' / 'status' / 'pruned_debt.json'
        if n_drop and ledger_p.exists():
            led = json.loads(ledger_p.read_text(encoding='utf-8'))
            known = {e['name'] for e in led['entries']}
            added = 0
            for u in units:
                out_p = stub_path_for_unit(u)
                if not out_p.exists():
                    continue
                t = out_p.read_text(encoding='utf-8')
                i = t.find('// PRUNED')
                if i < 0:
                    continue
                for m in re.finditer(r'^//   (?:func |data )?(.+)$', t[i:], re.M):
                    nm = re.sub(r'^//   (?:func |data )?', '', m.group(0)).strip()
                    if nm not in known:
                        known.add(nm)
                        led['entries'].append({
                            'kind': 'data' if '//   data ' in m.group(0) else 'func',
                            'name': nm, 'status': 'open',
                            'origin': 'stub_gen prune_stub compile-driven (auto-append)'})
                        added += 1
            led['count'] = len(led['entries'])
            ledger_p.write_text(json.dumps(led, ensure_ascii=False, indent=2) + '\n',
                                encoding='utf-8')
            print('pruned_debt.json +%d 条' % added)
        return

    drops = definition_dups()
    total = 0
    for u in units:
        src = PROJECT_ROOT / u
        if not src.exists():
            print('MISSING unit: %s' % u, file=sys.stderr)
            continue
        notes = None
        if drops.get(u):
            notes = ['// DUP-FALLBACK (defined elsewhere, LNK2005 dedup):'] + \
                    ['//   %s' % n for n in sorted(drops[u])]
        out, n = generate_for_unit(src, args.out if args.unit else None,
                                   skip_names=drops.get(u), notes=notes)
        total += n
        print('stub %-60s funcs=%d' % (str(out.relative_to(PROJECT_ROOT)), n))
    print('units %d | functions %d' % (len(units), total))


if __name__ == '__main__':
    main()
