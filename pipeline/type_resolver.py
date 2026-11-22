#!/usr/bin/env python3
"""[ref语义 2026-11-20·用户裁定] 注解层类型完备性 resolve。

不变量: 任何被引用的类型(含 primitive)必须能 resolve——拼错/缺档/污染同罪。
  普查实证(650 基型): 'cha'/'unsined char'(拼写)/'static int'(存储类污染)/
  'int pRoleTriple'(参数名污染)/*this 污染/'gbVFileSys'(疑拼错)——
  全部经 resolve 拦截, 不再流毒到 apply([5b] fail=24 案)。

类型注册表(类型↔声明域映射, 七类):
  builtin   void/int/__int64/long double...      无需头
  win32sdk  BOOL/DWORD/_D3D*/IDirect3D9/FILE...  windows.h/d3d9.h/dinput.h/CRT
            (VC6 SDK 信任域, 不解析真产物)
  ida       _BYTE/_DWORD/uchar/uint/__m64...     include/pal3/ida_types.h
            (+ida_defs.h 自有 typedef)            (解析真产物)
  gbengine  gbVec3D/gbTexture/gbVFileSystem...   include/gbengine/*.h (解析真产物)
  gen树     全部生成头(class/struct/enum/typedef  include/pal3/gen/*.h
            + globals.h vtbl_/_PVFV)              (解析真产物)
  enums     枚举名                                data/annotations/enums.json
  std::     vector/queue/basic_string/deque...    pal3_stl.h/MSVC STL

registry 自验证: 可解析域(ida/gbengine/gen树)的名字**从真产物解析而来**;
硬编码信任域(win32sdk/builtin)与真产物无耦合, 标注信任级别。
ref 图: class→class 引用边(A引用B), 供 include 计算/影响面分析复用。

rollout(房规): report 模式先行——产出不可解析集清单, 逐项裁定
[真数据病/宇宙缺口], 宇宙补齐后升 hard(check_annotations 挂 gate)。
新鲜度: gen 树 mtime 早于注解 mtime ⇒ WARN(陈旧, codegen 后复跑)。

用法: python3 pipeline/type_resolver.py [--hard]
"""
import json
import os
import re
import sys
import glob

_PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# [声明域勘误 2026-11-20] include/pal3/gen/=陈旧壳树(转发include+旧vtbl残留
# ——发射器 2026-11-14 起停发 vtbl struct); pal3/src/=现行生成树
# (output_headers 指向, 785 头, canonical 单定义点)。解析域=真身。
_GEN_INCLUDE = os.path.join(_PROJECT_ROOT, 'pal3', 'src')
_IDA_TYPES_H = os.path.join(_PROJECT_ROOT, 'include', 'pal3', 'ida_types.h')
_IDA_DEFS_H = os.path.join(_PROJECT_ROOT, 'include', 'pal3', 'ida_defs.h')
_GBENGINE_DIR = os.path.join(_PROJECT_ROOT, 'include', 'gbengine')
_STRUCTS_DIR = os.path.join(_PROJECT_ROOT, 'data', 'annotations', 'structs')

# ---------------------------------------------------------------- 信任域

# [builtin] MSVC6 内建/关键字——无需声明域
_BUILTIN = frozenset((
    'void', 'int', 'char', 'short', 'long', 'float', 'double', 'bool',
    'signed', 'unsigned', 'const', 'volatile', 'struct', 'class', 'union',
    'enum', 'long double', 'unsigned char', 'unsigned short', 'unsigned int',
    'unsigned long', 'signed char', '__int8', '__int16', '__int32', '__int64',
    'unsigned __int64',
))

# [win32sdk] VC6 SDK 信任域(声明域=windows.h/d3d9.h/d3dx.h/dinput.h/
# mmsystem.h/CRT/MSVC RTTI 内部/STL)。不解析真产物, 信任级别=SDK 标准。
_WIN32SDK = frozenset((
    # windows.h (windef/winnt/winbase/winuser/richedit/commctrl)
    'BOOL', 'BYTE', 'WORD', 'DWORD', 'UINT', 'ULONG', 'LONG', 'USHORT',
    'HANDLE', 'HWND', 'HDC', 'HINSTANCE', 'HMODULE', 'HGLOBAL', 'HKEY',
    'HBITMAP', 'HBRUSH', 'HCURSOR', 'HICON', 'HMENU', 'HPALETTE', 'HRGN',
    'HFONT', 'HDC__', 'LPVOID', 'PVOID', 'LPSTR', 'LPCSTR', 'LPCTSTR',
    'LPTSTR', 'LPPOINT', 'LPRECT', 'WPARAM', 'LPARAM', 'LRESULT',
    'HRESULT', 'SIZE_T', 'DWORD_PTR', 'UINT_PTR', 'INT_PTR', 'COLORREF',
    'CHAR', 'WCHAR', 'TCHAR', 'BOOLEAN', 'PBYTE', 'LPBYTE', 'ATOM', 'FLOAT',
    'POINT', 'RECT', 'SIZE', 'tagPOINT', 'tagRECT', 'tagSIZE', 'tagMSG',
    'tagNMHDR', 'tagRGBQUAD', 'tagLOGFONTA', 'tagPALETTEENTRY',
    'tagRegion', 'tagThread', 'tagTHREADNAME_INFO',
    'HWND__', 'HINSTANCE__', 'HDC__', 'HBITMAP__', 'HBRUSH__', 'HICON__',
    'HMENU__', 'HPALETTE__', 'HRGN__', 'HFONT__', 'HWAVEOUT__',
    '_GUID', '_LARGE_INTEGER', '_FILETIME', '_CONTEXT', '_EXCEPTION_RECORD',
    '_EXCEPTION_POINTERS', 'EXCEPTION_POINTERS', '_IMAGE_DATA_DIRECTORY',
    '_IMAGE_FILE_HEADER', '_IMAGE_OPTIONAL_HEADER', '_IMAGE_DOS_HEADER',
    '_RGNDATAHEADER', '_WINDOWPLACEMENT', '_SYSTEMTIME', '_OSVERSIONINFOA',
    '_WIN32_FIND_DATAA', '_STARTUPINFOA', '_PROCESS_INFORMATION',
    '_SECURITY_ATTRIBUTES', '_CRITICAL_SECTION', '_LIST_ENTRY',
    '_FLOATING_SAVE_AREA', '_EH3_EXCEPTION_REGISTRATION',
    'TypeDescriptor', '_TypeDescriptor', 'CatchableType', '_CatchableType',
    'CatchableTypeArray', '_CatchableTypeArray', '_s__CatchableTypeArray',
    'PMD', '_PMD', 'PMFN', '_PMFN', '_Collvec', '_Ctypevec', '_Cvtvec',
    '_SCOPETABLE_ENTRY', '_SCOPETABLE', 'PSCOPETABLE_ENTRY',
    '_s_ThrowInfo', '_ThrowInfo', '_CatchableTypeArray',
    # mmsystem.h
    'HWAVEOUT', 'WAVEFORMAT', 'waveformat_tag', 'WAVEHDR', 'wavehdr_tag',
    'PCMWAVEFORMAT', 'pcmwaveformat_tag', 'MMTIME', 'mmtime_tag',
    # d3d9.h / d3dx9.h (d3d*_ 类型族前缀信任)
    # dinput.h
    'IUnknown', 'IDispatch',
    'IDirectInput8', 'IDirectInputDevice8', 'DIEFFECT', 'DIENVELOPE',
    'DIPROPHEADER', 'DICONFIGURECALLS',
    # CRT
    'FILE', '_iobuf', 'size_t', 'time_t', 'clock_t',
    'Iostream_init',
    'DllMain',
))

# [win32sdk 前缀信任] SDK 类型族前缀(d3d9/d3dx/dinput 大族逐名列不现实,
# 前缀+大小写边界信任; 误信风险=拼错恰好落在族前缀内, 可接受)
_WIN32SDK_PREFIXES = ('_D3D', 'D3D', 'D3DX', 'IDirect3D', 'ID3DX', '_DI',
                      'DIACTION', 'DIDEVICE', 'DIOBJECT', 'DICONFIG')

# [std:: 容器] pal3_stl.h / MSVC STL——容器名信任, 模板实参递归 resolve
_STD_CONTAINERS = frozenset((
    'vector', 'queue', 'deque', 'list', 'basic_string', 'allocator',
    'char_traits', 'pair', 'map', 'set',
))

# ---------------------------------------------------------------- 真产物解析域

# 函数指针 typedef: 'typedef void (__cdecl *_PVFV)(void);' 名在 * 后 ) 前
_TYPEDEF_FP_RE = re.compile(r'\btypedef\b[^;]*?\*\s*([A-Za-z_]\w*)\s*\)')
# 对象 typedef: 尾名 'typedef unsigned long _DWORD;'
_TYPEDEF_RE = re.compile(r'\btypedef\b[^;]*?[\s*]([A-Za-z_]\w*)\s*;', )
_DECL_RE = re.compile(
    r'\b(?:class|struct|enum)\s+(?:\w+\s+)?([A-Za-z_]\w*)\s*(?::[^;{]*)?[{;]')


def _parse_header_types(path, names_out, fp_typedef=True):
    """从头文件解析 typedef/class/struct/enum 声明名(轻量正则, 保守)。"""
    try:
        txt = open(path, encoding='utf-8', errors='replace').read()
    except OSError:
        return False
    for m in _TYPEDEF_RE.finditer(txt):
        names_out.add(m.group(1))
    if fp_typedef:
        for m in _TYPEDEF_FP_RE.finditer(txt):
            names_out.add(m.group(1))
    for m in _DECL_RE.finditer(txt):
        names_out.add(m.group(1))
    return True


def build_registry():
    """构建类型注册表 {type_name: 声明域描述}。

    可解析域(ida/gbengine/gen树)从真产物解析而来——registry 条目即真产物,
    无自验证需求; 信任域(win32sdk/builtin/std)为硬编码, 标注信任级别。
    """
    reg = {}
    for t in _BUILTIN:
        reg[t] = ('builtin', 'MSVC6 内建')
    for t in _WIN32SDK:
        reg[t] = ('win32sdk', 'VC6 SDK 信任域(windows.h/d3d/dinput/CRT/RTTI)')

    # ida: ida_types.h + ida_defs.h 自有 typedef(仅typedef——前向声明会
    # 把别的类误标进ida域, 标签失真; 名字有效性由gen树域承载)
    names = set()
    for m in _TYPEDEF_RE.finditer(_read(_IDA_TYPES_H) + _read(_IDA_DEFS_H)):
        names.add(m.group(1))
    for m in _TYPEDEF_FP_RE.finditer(_read(_IDA_TYPES_H) + _read(_IDA_DEFS_H)):
        names.add(m.group(1))
    for t in names:
        reg.setdefault(t, ('ida', 'pal3/ida_types.h|ida_defs.h'))

    # gbengine: 全部引擎头
    names = set()
    for gh in glob.glob(os.path.join(_GBENGINE_DIR, '*.h')):
        _parse_header_types(gh, names)
    for t in names:
        reg.setdefault(t, ('gbengine', 'include/gbengine/*.h'))

    # gen 树: 全部生成头(类头+globals.h vtbl_/_PVFV+枚举头)
    names = set()
    for gh in glob.glob(os.path.join(_GEN_INCLUDE, '**', '*.h'), recursive=True):
        _parse_header_types(gh, names)
    for t in names:
        reg.setdefault(t, ('gen', 'include/pal3/gen/*.h'))

    # 嵌套类型限定名: structs nested_types + detached_nested_types.json
    # (注解命名两式: 'A::B' 与 'A__B'; 解析域=注解声明真相)
    def _add_nested(owner, subs):
        for nt, info in (subs or {}).items():
            for form in ('%s::%s' % (owner, nt), '%s__%s' % (owner, nt)):
                reg.setdefault(form, ('nested', 'structs/%s.json' % owner))
            _add_nested(nt, (info or {}).get('nested_types'))
    stems = set()
    for sf in sorted(glob.glob(os.path.join(_STRUCTS_DIR, '*.json'))):
        try:
            d = json.load(open(sf, encoding='utf-8'))
        except (OSError, json.JSONDecodeError):
            continue
        owner = str(d.get('name') or os.path.basename(sf)[:-5])
        stems.add(owner)
        stems.add(os.path.basename(sf)[:-5])
        # [顶层 stem 入域 2026-11-22] structs/*.json 本身=类型声明真相域——
        # 原 registry 只收 __ 嵌套变体与 nested_types, 顶层名依赖「生成头已进
        # gen 域」(存量型先例 REF 门引入前头已在) ⇒ 新类型首引入鸡生蛋
        # (tagAnimStateSplit 案: codegen 前置 check 必拦)。补齐: 顶层名同登
        # structs 域, 与既有 ('structs', ...) 标签一致。
        reg.setdefault(owner, ('structs', os.path.basename(sf)))
        reg.setdefault(os.path.basename(sf)[:-5],
                       ('structs', os.path.basename(sf)))
        if '__' in owner:
            reg.setdefault(owner.replace('__', '::', 1),
                           ('structs', os.path.basename(sf)))
        _add_nested(owner, d.get('nested_types'))
    # [嵌套单_变体·前缀验证] SceneObj_Common_State(单_形) ↔ SceneObj::Common_State
    # (引用形)——切分变体仅在前缀本身是已注册类名时登记(精准性: ARC_PlayerItem
    # 不得产 ARC::PlayerItem 假变体)
    for _own in sorted(stems):
        if '::' in _own or '__' in _own or '_' not in _own:
            continue
        _h, _t = _own.split('_', 1)
        if _h in stems:
            reg.setdefault('%s::%s' % (_h, _t), ('structs', 'nested-variant'))
    try:
        # detached_nested_types.json 形态: {Owner: {Nested: {...}, ...}, _元字段...}
        # (PlayerMgr::PoisonState 实证——已解散幻影类的嵌套类型名载体)
        dj = json.load(open(os.path.join(_PROJECT_ROOT, 'data', 'annotations',
                                         'detached_nested_types.json'),
                            encoding='utf-8'))
        for owner, subs in dj.items():
            if owner.startswith('_') or not isinstance(subs, dict):
                continue
            for nt in subs:
                for form in ('%s::%s' % (owner, nt), '%s__%s' % (owner, nt)):
                    reg.setdefault(form, ('nested',
                                          'detached_nested_types.json'))
    except (OSError, json.JSONDecodeError):
        pass

    # enums: 枚举名(枚举可作类型)
    try:
        ej = json.load(open(os.path.join(_PROJECT_ROOT, 'data', 'annotations',
                                         'enums.json'), encoding='utf-8'))
        for t in ej:
            reg.setdefault(str(t), ('enums', 'data/annotations/enums.json'))
    except (OSError, json.JSONDecodeError):
        pass

    return reg


def harvest_header_edges(directory, domain):
    """[外部库引用边 2026-11-20·用户裁定] 外部导入库(gbengine)头文件真产物
    解析→引用边补充。声明行类型token→registry resolve→edges(kind同规则)。
    过近似可接受(假边=多余前向声明候选, 无害; 漏边=include缺失, 有害⇒宁滥)。"""
    edges = []
    for h in sorted(glob.glob(os.path.join(directory, '*.h'))):
        try:
            txt = open(h, encoding='utf-8', errors='replace').read()
        except OSError:
            continue
        hdr = os.path.basename(h)
        reg = build_registry()
        # 类型样token: 类名形态标识符 + 可选指针/引用缀
        for m in re.finditer(
                r'\b((?:gb|GB|Gb)[A-Z]\w*|[A-Z]\w{2,})\s*((?:\*|&\s*)+)', txt):
            name, ptrs = m.group(1), m.group(2)
            if name in reg and reg[name][0] in ('gbengine', 'structs', 'gen'):
                edges.append((hdr, name,
                              'ref' if ptrs else 'value', domain))
    return edges


def freshness_check():
    """gen 树新鲜度: 任一注解文件晚于最新生成头 ⇒ 陈旧。返回 WARN 文本或 None。"""
    newest_ann = 0.0
    for root in (_STRUCTS_DIR,
                 os.path.join(_PROJECT_ROOT, 'data', 'annotations')):
        for f in glob.glob(os.path.join(root, '*.json')):
            try:
                newest_ann = max(newest_ann, os.path.getmtime(f))
            except OSError:
                pass
    newest_gen = 0.0
    for gh in glob.glob(os.path.join(_GEN_INCLUDE, '**', '*.h'), recursive=True):
        newest_gen = max(newest_gen, os.path.getmtime(gh))
    if newest_ann > newest_gen:
        return ('gen 树(%d)早于最新注解(%d)——生成头陈旧, resolve 结果以'
                '陈旧声明域为准; codegen 后复跑'
                % (int(newest_gen), int(newest_ann)))
    return None


# ---------------------------------------------------------------- 类型串解析

def _read(path):
    try:
        return open(path, encoding='utf-8', errors='replace').read()
    except OSError:
        return ''

_THIS_POLLUTE_RE = re.compile(r'\bthis\b')
_FP_RE = re.compile(r'^(.*?)\s*\(\s*(__\w+\s*)?\*\s*\)\s*\((.*)\)$')
_TEMPLATE_RE = re.compile(r'^([A-Za-z_][\w:]*)\s*<(.*)>$')
_SPLIT_RE = re.compile(r'[,<]')


def _split_top(s):
    """按顶层逗号切分(模板实参/函数参数共用, 尖括号深度感知)。"""
    parts, depth, cur = [], 0, []
    for ch in s:
        if ch == '<':
            depth += 1
        elif ch == '>':
            depth -= 1
        elif ch == ',' and depth == 0:
            parts.append(''.join(cur).strip())
            cur = []
            continue
        cur.append(ch)
    tail = ''.join(cur).strip()
    if tail:
        parts.append(tail)
    return parts


def classify_kind(t):
    """[include优化语义 2026-11-20·用户裁定] 引用kind分类:
    'value'=值类型(成员按值/基类子对象/值数组/值模板)——必须加include(完整定义);
    'ref'=引用类型(指针/引用/函数指针/指针数组)——前向声明足够。
    答案供头文件生成优化: value边→include, ref边→fwd decl候选。"""
    if isinstance(t, dict):
        return 'value'   # 内联struct/union=值
    s = str(t or '').strip()
    if not s:
        return 'ref'
    if '(' in s:
        return 'ref'     # 函数指针
    elem = re.sub(r'\[[^\]]*\]', '', s).strip()
    if '*' in elem or '&' in elem:
        return 'ref'     # 指针/引用(含指针数组)
    tm = _TEMPLATE_RE.match(elem)
    if tm:
        short = tm.group(1).split('::')[-1]
        if short in _STD_CONTAINERS:
            args = _split_top(tm.group(2))
            return 'value' if any(classify_kind(a) == 'value'
                                  for a in args) else 'ref'
        return 'value'
    return 'value'


def _base_token(t):
    """剥指针/引用/数组/const 后缀与修饰前缀 → 基型(供 registry 查)。"""
    s = str(t or '').strip()
    s = re.sub(r'\[[^\]]*\]', '', s).strip()
    s = re.sub(r'\s*\*\s*', '*', s)   # 星号粘合('X * *'=X** 带空格实证)
    s = s.rstrip('*').rstrip('&').strip()
    while s.endswith('const'):
        s = s[:-5].rstrip().rstrip('*').strip()
    for p in ('const ', 'unsigned ', 'signed ', 'struct ', 'class ',
              'union ', 'enum ', 'typename '):
        while s.startswith(p):
            s = s[len(p):].strip()
    return s.strip()


def iter_type_refs(refs_out, refgraph):
    """遍历全部注解类型引用位点。

    refs_out 收 (source, owner, field, type_str, kind);
    kind: classify_kind裁定('value'必须include/'ref'前向声明足够);
    bases=基类子对象=值边(最强include契约, 2026-11-20补位点)。
    """
    # structs: bases(值边) + sig_model + known_members + nested
    for sf in sorted(glob.glob(os.path.join(_STRUCTS_DIR, '*.json'))):
        cls = os.path.basename(sf)[:-5]
        try:
            d = json.load(open(sf, encoding='utf-8'))
        except (OSError, json.JSONDecodeError):
            continue
        for b in (d.get('bases') or []):
            bn = b.get('name') if isinstance(b, dict) else b
            if bn:
                refs_out.append((cls, 'base', 'base', str(bn), 'value'))
        for addr, m in (d.get('methods') or {}).items():
            sm = m.get('sig_model') or {}
            if sm.get('pending'):
                continue  # R4: pending=声明未定谳, 非类型契约(CPK::Load 案)
            if sm.get('return'):
                refs_out.append((cls, addr, 'sig.return', sm['return'],
                                 classify_kind(sm['return'])))
            for pi, p in enumerate(sm.get('params') or []):
                if isinstance(p, dict) and p.get('type'):
                    refs_out.append((cls, addr, 'sig.p%d' % pi, p['type'],
                                     classify_kind(p['type'])))
        for off, mm in (d.get('known_members') or {}).items():
            t = mm.get('type')
            if isinstance(t, (str, dict)) and t:
                refs_out.append((cls, off, 'member', t, classify_kind(t)))
        _walk_nested(d.get('nested_types') or {}, cls, refs_out)
    # globals
    try:
        g = json.load(open(os.path.join(_PROJECT_ROOT, 'data', 'annotations',
                                        'globals.json'), encoding='utf-8'))
        for addr, e in g.items():
            t = e.get('type')
            if isinstance(t, str) and t and t != 'skip':
                refs_out.append(('globals', addr, 'type', t,
                                 classify_kind(t)))
    except (OSError, json.JSONDecodeError):
        pass
    # functions: legacy signature 串(尚未 sig_model 单源)
    try:
        fj = json.load(open(os.path.join(_PROJECT_ROOT, 'data', 'annotations',
                                         'functions.json'), encoding='utf-8'))
        from pipeline.gen.annotation_view import sm_text as _sm_r
        for addr, e in fj.items():
            if not isinstance(e, dict):
                continue
            sig = _sm_r(e)   # [sig 退役收尾 20261123] signature→sm_text
            if sig:
                refs_out.append(('functions', addr, 'signature', sig, 'ref'))
    except (OSError, json.JSONDecodeError):
        pass


def _walk_nested(nested, cls, refs_out):
    for _nt, info in (nested or {}).items():
        for mm in ((info or {}).get('members')
                   or (info or {}).get('known_members') or []):
            if isinstance(mm, dict) and mm.get('type'):
                refs_out.append((cls, _nt, 'nested.member', mm['type'],
                                 classify_kind(mm['type'])))
        sub = (info or {}).get('nested_types')
        if sub:
            _walk_nested(sub, cls, refs_out)


class Resolver:
    def __init__(self):
        self.reg = build_registry()
        self.failures = []      # (source, owner, field, type_str, base, reason)
        self.refgraph = {}      # {cls: set(referenced base)} (兼容保留)
        self.edges = []         # (owner, base, kind, field) [include优化语义]

    def _resolve_param(self, pt, source, owner, field):
        """签名参数串: 'TYPE NAME' 对——剥尾参数名后 resolve。
        ('int *pRect'→'int *'; 'unsigned __int64 volume'→'unsigned __int64')
        误剥仅伤复合primitive形(仍可resolve, 无害)。'...'变arg直过。"""
        s = str(pt or '').strip()
        if s == '...' or not s:
            return
        toks = s.split()
        if toks:
            toks[-1] = re.sub(r'@<[^>]*>$', '', toks[-1])  # R3: @<reg> 注记剥
        if (len(toks) >= 2 and re.match(r'^\**[A-Za-z_]\w*$', toks[-1])
                and not toks[-1].startswith('__')):
            s = ' '.join(toks[:-1])
        self._resolve_one(s, source, owner, field)

    def _resolve_one(self, t, source, owner, field, kind=None):
        """递归 resolve 单个类型串。失败登记 failures, 成功记 refgraph/edges。"""
        raw = str(t or '')
        if kind is None:
            kind = classify_kind(raw) if raw.strip() else 'ref'
        if isinstance(t, dict):
            # 内联 struct/union 对象: 递归其成员类型(内联=值)
            for mm in (t.get('struct') or t.get('union') or []):
                if isinstance(mm, dict):
                    self._resolve_one(mm.get('type'), source, owner, field,
                                      'value')
            return
        s = str(t or '').strip()
        if not s or s == 'skip':
            return
        s = re.sub(r'\s*&\s*$', '', s)   # 引用尾剥除(FP参数模板形实证)
        if not s:
            return
        # [functions.signature 豁免 2026-11-20] legacy 全渲染形签名串本就含
        # this 参数(hexrays 惯例, 消费方 section-6 自带 this 剥除)——该位点
        # 的 this 令牌非病; sig_model 参数表(全渲染形之外)的 this 仍=污染。
        if field == 'signature' and source == 'functions':
            s = re.sub(r'\bthis\b', '', s)
        if _THIS_POLLUTE_RE.search(s):
            self.failures.append((source, owner, field, s, s,
                                  '*this 污染(类型串含 this 令牌)'))
            return
        # 函数指针: RET (__cc *)(PARAMS)
        fm = _FP_RE.match(s)
        if fm and ('(' in s):
            ret, _cc, params = fm.group(1), fm.group(2), fm.group(3)
            self._resolve_one(ret, source, owner, field)
            for pt in _split_top(params):
                self._resolve_param(pt, source, owner, field)
            return
        # 模板: name<args...>
        tm = _TEMPLATE_RE.match(s)
        if tm:
            cname, args = tm.group(1), tm.group(2)
            short = cname.split('::')[-1]
            if short in _STD_CONTAINERS:
                for at in _split_top(args):
                    self._resolve_one(at, source, owner, field)
                return
            # 非标准模板: 基名须在 registry
            if cname not in self.reg:
                self.failures.append((source, owner, field, s, cname,
                                      '模板基名未resolve'))
            for at in _split_top(args):
                self._resolve_one(at, source, owner, field)
            return
        # 函数签名形(functions.json legacy): RET __cc Name(PARAMS) / RET(PARAMS)
        # ——函数名在串内, 与函数指针形(带*)不同源
        if '(' in s and not s.rstrip().endswith('*'):
            try:
                left, rest = s.rsplit('(', 1)
                params = rest.rsplit(')', 1)[0]
                # cc 剥除用正则('*__cdecl'粘连token实证)
                left_nocc = re.sub(r'\b(__\w+|virtual|static)\b', ' ', left)   # R1: virtual/static 关键字剥(nameless form 案)
                ltoks = left_nocc.split()
                if ltoks and re.match(r'^[A-Za-z_][\w:]*$', ltoks[-1]) and len(ltoks) > 1:
                    ltoks = ltoks[:-1]  # 尾函数名剥除
                self._resolve_one(' '.join(ltoks), source, owner, field)
                for pt in _split_top(params):
                    self._resolve_param(pt, source, owner, field)
                return
            except ValueError:
                pass
        base = _base_token(s)
        if not base:
            self.failures.append((source, owner, field, s, '', '空基型'))
            return
        if len(base.split()) > 1:
            # 复合 primitive (long double 等) 或污染
            if base in _BUILTIN:
                return
            self.failures.append((source, owner, field, s, base,
                                  '多令牌非修饰形(存储类/名字污染嫌疑)'))
            return
        if base in self.reg:
            if base[0].isupper() or base.startswith(('gb', 'tag', '_')):
                self.refgraph.setdefault(source, set()).add(base)
                self.edges.append((source, base, kind, field))
            return
        # [win32sdk 前缀信任] d3d9/d3dx/dinput 大族
        if base.startswith(_WIN32SDK_PREFIXES):
            self.refgraph.setdefault(source, set()).add(base)
            return
        # [嵌套限定名] Cls::Nested 与 Cls__Nested 双形混用实证
        # (SceneObj_Common_State.json 名=__形, SceneObj.json 引用=::形)——双向变体
        _bv = [base, base.replace('__', '::'), base.replace('::', '__'),
               base.replace('::', '_')]
        if any(v in self.reg for v in _bv):
            self.refgraph.setdefault(source, set()).add(base)
            return
        # 未 resolve —— 编辑距离提示(拼错侦察)
        hint = _near_miss(base, self.reg)
        self.failures.append((source, owner, field, s, base,
                              '未resolve' + (' (疑似 %s?)' % hint if hint else '')))


def _near_miss(token, reg):
    """编辑距离≤2 的已知名建议(仅侦察提示, 非裁决)。"""
    import difflib
    cand = difflib.get_close_matches(token, reg, n=1, cutoff=0.8)
    return cand[0] if cand else None


def collect():
    """[gate API 2026-11-20] 全量 resolve → (failures, warns, nrefs, nreg)。
    failures: (source, owner, field, type_str, base, reason)。"""
    warns = []
    fresh = freshness_check()
    if fresh:
        warns.append(fresh)
    r = Resolver()
    refs = []
    iter_type_refs(refs, {})
    for source, owner, field, t, kind in refs:
        r._resolve_one(t, source, owner, field, kind)
    return r.failures, warns, len(refs), len(r.reg), r.edges


def run(hard=False):
    failures, warns, nrefs, nreg, edges = collect()
    # [include优化语义·边统计] value边=必须include / ref边=前向声明候选
    from collections import Counter as _C2
    _ek = _C2(e[2] for e in edges)
    print('[边] value(必须include)=%d / ref(前向声明候选)=%d'
          % (_ek.get('value', 0), _ek.get('ref', 0)))
    # 汇总
    print('== ref resolve 普查 ==')
    print('类型引用位点: %d | 注册表条目: %d | 失败: %d'
          % (nrefs, nreg, len(failures)))
    for w in warns:
        print('WARN:', w)
    if failures:
        from collections import Counter
        by_reason = Counter(f[5] for f in failures)
        print('\n-- 失败分类:')
        for reason, n in by_reason.most_common():
            print('  %-40s x%d' % (reason[:40], n))
        multi = sorted(set(f[4] for f in failures
                           if '多令牌' in f[5]))
        if multi:
            print('\n-- 多令牌唯一基型 (%d):' % len(multi))
            for b in multi:
                print('   %r' % b)
        print('\n-- 逐项(前 %d):' % min(len(failures), 60))
        for f in failures[:60]:
            print('  %-10s %-12s %-10s %r -> %s' % (f[0], str(f[1])[:12],
                                                    f[2], f[3], f[5]))
        if len(failures) > 60:
            print('  ... 共 %d 项' % len(failures))
    nfails = len(failures)
    if hard and nfails:
        print('\nHARD: %d 项未 resolve — 终止(数据病不容错)。' % nfails)
        return 1
    print('\nreport 模式完成(--hard 升级终止语义)')
    return 0


if __name__ == '__main__':
    sys.exit(run(hard='--hard' in sys.argv))
