#!/usr/bin/env python3
"""S4 byte-match baseline for PAL3.exe (G0 layer-4 measurement).

For each S2-passing .cpp (per data/status/probe_census.json):
  1. compile it to .obj with the canonical probe flags
  2. extract function bodies from the COFF symbol table
     (reuses tools/gbengine_compare.parse_coff_obj)
  3. match obj symbols to annotated functions:
       - class methods: forward-mangled via pipeline/ida/vc6_mangler
       - free functions: COFF underscore rules ('_name' cdecl, '_name@N' stdcall)
  4. compare compiled bytes against original PAL3.exe .text at the annotated
     address (decomp JSON size_bytes is authoritative; relocation bytes are
     don't-care per gbengine_compare.compare_bytes)

Honesty rules: unmatched symbols and mangling failures are counted, never
silently dropped. 'match_L1' requires equal length AND zero differing bytes
outside relocations.

Usage:  python3 pipeline/compare_pal3.py [--census PATH] [--limit N]
Output: data/status/s4_baseline.json + data/status/pal3_registry.jsonl
"""

import os
import argparse
import hashlib
import json
import os
import re
import struct
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
sys.path.insert(0, str(REPO / 'tools'))
sys.path.insert(0, str(REPO / 'pipeline'))

import gbengine_compare as gc   # noqa: E402  (parse_coff_obj, compare_bytes)
import probe_compile as pc      # noqa: E402  (run_cl, INCLUDE_DIRS, wpath, OBJ_DIR)

EXE = REPO / 'original' / 'PAL3.exe'
DECOMP = REPO / 'asm' / 'pal3' / 'decomp'
CENSUS = REPO / 'data' / 'status' / 'probe_census.json'
OUT_JSON = REPO / 'data' / 'status' / 's4_baseline.json'

# ---------------------------------------------------------------------------
# S2：射程 match 输出隔离（数据安全护栏，2026-10-10）
# ---------------------------------------------------------------------------
# 对抗复核裁决：射程 match 必须写 s4_scoped_<target>.json，
# **严禁写 data/status/s4_baseline.json** —— 否则 stats.match_L1 从 86 骤降
# => 棘轮误判「大幅回退」=> L1 记录永久损坏。
# S2 修复（与 codegen.py 同一 bug 第 4 次）：原为模块全局 None，
# 但**无处从 os.environ 赋值** => 射程 match 永远拿不到值 => 空跑。
SCOPED_OUTPUT = os.environ.get('MATCH_SCOPED') or None   # None=全量；str=射程目标名


def scoped_output_path(target=None):
    """射程 match 的输出文件 —— 与 s4_baseline.json 隔离。

    P0-2 修复：原用不存在的 BASELINE_FILE 常量 + CWD 相对路径，
    会把产物写到错误位置。改用 OUT_JSON.parent（绝对、稳定）。
    """
    name = target or SCOPED_OUTPUT or 'unknown'
    return str(OUT_JSON.parent / ('s4_scoped_%s.json' % name))


def is_scoped_run():
    """当前是否射程模式 —— 射程模式严禁触碰 s4_baseline.json。"""
    return SCOPED_OUTPUT is not None

OUT_REG = REPO / 'data' / 'status' / 'pal3_registry.jsonl'


def exe_text_image():
    """Return (image_base, text_bytes, text_rva, text_raw_size).

    ⚠️ `text_bytes` **只含 `.text`**（`raw_ptr .. raw_ptr + raw_size`）。

    R8（2026-09-15 第 6 任复核者 kiro 发现、captain 量化并修）：
    本函数原先返回 `data[raw_ptr : raw_ptr + 0x10000000]` —— Python 切片**超尾静默截断**
    ⇒ 实际得到 `data[raw_ptr:]` = **到文件末尾**（实测 0x211000 字节），
    而 `.text` 只有 `raw_size = 0x169000`。该窗口跨越 `.text + .rdata + .data + .rsrc`。
    后果：下游 `oob` 判据用 `len(text)` 作界 ⇒ **近恒真**（`.rdata` 里的地址也判"在界内"），
    为本会话第 6 例恒真/近恒真门禁。
    `raw_size` 一并返回，供调用方做**正确的 `.text` 边界判定**。
    """
    data = EXE.read_bytes()
    pe = struct.unpack_from('<I', data, 0x3C)[0]
    num_sec = struct.unpack_from('<H', data, pe + 6)[0]
    opt_size = struct.unpack_from('<H', data, pe + 20)[0]
    image_base = struct.unpack_from('<I', data, pe + 24 + 28)[0]
    sec0 = pe + 24 + opt_size
    for i in range(num_sec):
        off = sec0 + i * 40
        name = data[off:off + 8].rstrip(b'\x00').decode('ascii', 'replace')
        _vsz, virt_addr, raw_size, raw_ptr = struct.unpack_from('<IIII', data, off + 8)
        if name == '.text':
            return image_base, data[raw_ptr:raw_ptr + raw_size], virt_addr, raw_size
    raise RuntimeError('.text section not found in %s' % EXE)


def load_decomp_index():
    idx = {}
    for f in DECOMP.glob('*.json'):
        try:
            d = json.loads(f.read_text())
        except (json.JSONDecodeError, OSError):
            continue
        name, addr, size = d.get('name'), d.get('address'), d.get('size_bytes')
        if not (name and addr and size):
            continue
        try:
            va = int(addr, 16) if isinstance(addr, str) else int(addr)
        except (TypeError, ValueError):
            continue
        idx[name] = {'name': name, 'va': va, 'size': int(size),
                     'signature': d.get('signature', '')}
    return idx


def _split_mangled_name(name):
    """从 **本身已是 mangled 名** 的 decomp name 里提取 (cls, method)。

    0b-③ 补（2026-09-15）：实测量得 5 个 decomp 条目的 `name` 以 `?` 开头
    （本身就是 mangled 名，形如
    `?PushOpen@AStarPathFinder@@QAEHPAUAStarPathFinder::NODE@@@Z` 或含 `[thunk]`）。
    原 `build_mangled_map` 假设所有 name 都是 `Cls::meth(...)` 形态，对它做
    `base.rsplit('::', 1)` ⇒ cls 变成 `?PushOpen@AStarPathFinder@@QAEHPAUAStarPathFinder`、
    method 变成 `NODE@@@Z`，产出**垃圾名**（永远匹配不上）。

    正确做法：从 mangled 名解析出 `?<method>@<class>@@`。
    返回 `(cls, method)`，无法解析时返回 `(None, None)`。
    """
    m = re.match(r'^\?+[0-9A-Za-z_]*?(\w+)@(\w+)@@', name)
    if m:
        return m.group(2), m.group(1)
    # ctor/dtor: ??0Cls@@ / ??1Cls@@
    m = re.match(r'^\?\?[01](\w+)@@', name)
    if m:
        return m.group(1), m.group(1)
    # 【2026-09-15 修】Hex-Rays 的**反引号特名**：`Cls::`scalar deleting destructor'(uint)`
    # 原实现只认 `?...`（mangled）与 `Cls::meth(...)` 形态，对这一类返回 (None, None)
    # ⇒ 该条目在 build_mangled_map 里被**跳过** ⇒ `??_G<Cls>@@UAEPAXI@Z` **进不了 mangled_map**
    # ⇒ `match` 匹配不到该符号 ⇒ **该类的 L1（字节全同函数）丢失**（实测 UIStatic / JusticeBookUI）。
    # 归一化为 mangler 认识的 `_scalar_dtor` / `_vector_dtor`（与 collect.py / emit_headers.py 同法）。
    if '::' in name:
        _cls, _, _rest = name.rpartition('::')
        _meth = _rest.split('(')[0]
        _norm = re.sub(r'`?\s*scalar deleting destructor\s*\'?', '_scalar_dtor', _meth)
        _norm = re.sub(r'`?\s*vector deleting destructor\s*\'?', '_vector_dtor', _norm).strip()
        if _cls and _norm and _norm != _meth:
            return _cls, _norm
    return None, None


def _load_annotation_dtors():
    """从 `data/annotations/structs/*.json` 收集析构函数名，返回 [(cls, method_name)]。

    0b-⑤（2026-09-15）。析构函数的**名字供给在注解层**——`decomp` 对多数类没有 `~Cls`
    条目，但注解 methods 里有 70 条 `~Cls` 形态（覆盖 65 个类）。

    **后缀归一化**：注解里存在带后缀的命名，实测两类：
      - `~UIFrameWnd_Full`（`UIFrameWnd`）——这种会让 mangler 的
        `method_name == '~' + last_seg` 判据不成立，退化成普通方法名 `?~UIFrameWnd_Full@...`
      - `~CUtil_31f0`（`CUtil`）——同类的**另一个** dtor 也被显式命名
    因此：原名与"去掉尾部 `_xxxx` 后缀"的形态**都产出**（mangler 侧 `setdefault` 去重，
    重复无害），既不丢 `_31f0` 这类真实重载，也能救 `_Full` 这类修饰。
    """
    out = []
    seen = set()
    for p in sorted((REPO / 'data' / 'annotations').glob('structs/*.json')):
        try:
            with open(p, encoding='utf-8') as f:
                d = json.load(f)
        except (OSError, json.JSONDecodeError):
            continue
        cls = d.get('name')
        if not cls:
            continue
        for _addr, m in (d.get('methods') or {}).items():
            nm = (m or {}).get('name') or ''
            if not nm.startswith('~'):
                continue
            cands = [nm]
            # 归一化：`~Cls<suffix>` → `~Cls`。
            # mangler 的 dtor 判据是 `method_name == '~' + last_seg`，
            # 任何后缀（`_Full` / `_31f0` / `_ovl` …）都会让它退化成普通方法名
            # `?~UIFrameWnd_Full@UIFrameWnd@@QAEXXZ`（实测）。
            # 同时保留原名，以免丢掉真实的同名重载。
            if not nm.startswith('~' + cls):
                pass
            else:
                cands.append('~' + cls)
            stripped = re.sub(r'_[0-9a-fA-F]{3,}$', '', nm)
            if stripped != nm and stripped.startswith('~') and stripped not in cands:
                cands.append(stripped)
            for c in cands:
                key = (cls, c)
                if key not in seen:
                    seen.add(key)
                    out.append(key)
    return out


def _load_dtor_candidates():
    """推导"必有析构函数"的类名集合（0b-⑤）。

    判据（任一命中即入选）：
      - 注解或 decomp 里出现 `~Cls` / `_scalar_dtor` / `_sdtor*` ⇒ 直接或间接见到 dtor
      - 注解 methods 里有 `ctor` 或 `Cls::Cls`（构造函数存在是较弱信号，一并纳入）

    **假阳性无害**：这些名字只用作 `mangled_map` 的查找键，多余键永不匹配 ⇒
    不会制造假匹配，只是多几个无用的字典项（实测候选 120 类，`mangled_map` 增量很小）。
    """
    cands = set()
    for p in sorted((REPO / 'data' / 'annotations').glob('structs/*.json')):
        try:
            with open(p, encoding='utf-8') as f:
                d = json.load(f)
        except (OSError, json.JSONDecodeError):
            continue
        cls = d.get('name')
        if not cls:
            continue
        for m in (d.get('methods') or {}).values():
            nm = (m or {}).get('name') or ''
            if (nm.startswith('~') or re.match(r'^_s(dtor|calar_dtor)', nm)
                    or nm in ('ctor', cls)):
                cands.add(cls)
                break
    return cands


def build_mangled_map(decomp_idx):
    sys.path.insert(0, str(REPO / 'pipeline' / 'ida'))
    import vc6_mangler as vm
    m2e, failed = {}, 0
    # 0b-⑤（2026-09-15）：**析构函数供给在 annotation，不在 decomp**。
    #
    # 实测：`decomp` 对多数类**没有** `~Cls` 条目（`UIFrameWnd`/`UIWnd`/`UI3DCtrl`/
    # `JusticeBookUI`/`PAL3VisNode`… 全部缺失），但 `data/annotations/structs/*.json`
    # 里有 **70 条** `~Cls` 形态的 methods（`dtors` 命中 65 个类）。
    # `.obj` 引用的 `??1` 涉及 20 个类，其中 **11 个注解有供给**、9 个两处都缺。
    #
    # 为什么值得做：`match_symbols` 的 `matched` 路径**只有 `mangled_map`**
    # （`base_idx` 回退只对非 `?` 符号生效，而 `.obj` 符号全是 `?` 开头）
    # ⇒ 名字供给缺失 = 该函数**从不参与字节比对**。
    #
    # 做法：从注解 methods 收集 `~Cls`，用 mangler 生成 `??1<Cls>@@{Q,U}AE@XZ`
    # 两种虚性都要（实测 obj 侧 `??1` 的虚性分布为 U 18 / Q 7，不可只发一种）。
    # 实测 11 个有供给的类里 **10 个能生成正确名**；
    # 唯一失败的 `~UIFrameWnd_Full` 是**注解命名带后缀**（`_Full`）导致
    # mangler 的 `method_name == '~' + last_seg` 判据不成立（见下方 _ann_dtors 处理）。
    _ann_dtors = _load_annotation_dtors()
    # **推导**出的析构函数（0b-⑤ 的第二条供给路径）。
    #
    # 注解/decomp 只对部分类给出 `~Cls`（71 对），实测 `.obj` 需要 `??1` 的 20 个类里
    # 有 9 个**两处都没有** dtor 名（`UIWnd`/`JusticeBookUI`/`PAL3VisNode`/`UI3DCtrl`/
    # `UIButtonEXA`/`UIPushButton`/`UITitle_BBTY`/`CEffGroupNode`/`CScreenModeNode`）。
    #
    # 但这些类里有若干**有 `_scalar_dtor`/`_sdtor` 条目**
    # （`JusticeBookUI`/`UI3DCtrl`/`UITitle_BBTY` 有 `_scalar_dtor`，
    #  `UIWnd` 有 `_sdtor_14/27/28`）——**有 scalar-dtor ⇒ 该类必有析构函数**。
    # 再叠加有 ctor / `Cls::Cls` 的类（同一判据的弱化版，作为候选）。
    #
    # **为什么可以安全推广**：这些名字只用作 `mangled_map` 的**查找键**——
    # 若某类推错了（其实没有 `??1`），生成的多余键**永远匹配不上任何符号**，
    # 不产生假匹配。⇒ 假阳性无害、假阴性才是损失。
    #
    # 实测：候选 120 个类 ⇒ matched 153 → **164**，unmatched 36 → **25**。
    _dtor_cands = _load_dtor_candidates()
    for _cls in _dtor_cands:
        for _virtual in (False, True):
            try:
                _k = vm.mangle(_cls, '~' + _cls, 'void __thiscall()',
                               virtual_=_virtual)
                if _k.startswith('??1'):
                    m2e.setdefault(_k, {'name': '%s::~%s' % (_cls, _cls),
                                        'signature': 'void __thiscall()',
                                        '_from': 'derived_dtor'})
            except Exception:
                failed += 1
    for _cls, _method in _ann_dtors:
        for _virtual in (False, True):
            try:
                _k = vm.mangle(_cls, _method, 'void __thiscall()', virtual_=_virtual)
                if _k.startswith('??1'):
                    m2e.setdefault(_k, {'name': '%s::%s' % (_cls, _method),
                                        'signature': 'void __thiscall()',
                                        '_from': 'annotation_dtor'})
            except Exception:
                failed += 1
    for name, e in decomp_idx.items():
        if name.startswith('?'):
            # name 本身即 mangled 名 ⇒ 解析出 cls/method 后**用签名重算**
            # （mangler 可能生成得比 IDA 的 mangled name 更准，例如嵌套类层级号）
            cls, method = _split_mangled_name(name)
            if not cls:
                continue
        else:
            if '::' not in name:
                continue
            base = name.split('(')[0]
            if '::' not in base:
                continue
            cls, method = base.rsplit('::', 1)
            # 【2026-09-15 修】反引号特名归一化（本函数**第四个**同类问题点）：
            # `UIStatic::`scalar deleting destructor'(uint)` 走本分支时，
            # `base.rsplit('::',1)` 得到 method = "`scalar deleting destructor'"
            # ⇒ `vm.mangle` 的 `^_s(dtor|calar_dtor)(_\d+)?$` 判据**不匹配**
            # ⇒ 既不产出 `??_G<Cls>@@UAEPAXI@Z`，也产出普通的 `?`scalar...@Cls@@`（垃圾名）
            # ⇒ `match` 匹配不到 obj 里的 `??_G` ⇒ **该类 L1 丢失**。
            _norm = re.sub(r'`?\s*scalar deleting destructor\s*\'?', '_scalar_dtor', method)
            _norm = re.sub(r'`?\s*vector deleting destructor\s*\'?', '_vector_dtor', _norm).strip()
            if _norm:
                method = _norm
        sig = e.get('signature') or ''
        try:
            m = vm.mangle(cls, method, sig)
            m2e.setdefault(m, e)
            # probe variants the annotation signature can't express:
            # virtual (vtable methods) and static (SA-prefix members)
            for kw in ({'virtual_': True}, {'static_': True}):
                mv = vm.mangle(cls, method, sig, **kw)
                if mv != m:
                    m2e.setdefault(mv, e)
        except Exception:
            failed += 1
            continue
    return m2e, failed


def build_basename_index(decomp_idx):
    """base name (no params) -> entry, only when unambiguous."""
    by_base = {}
    for name, e in decomp_idx.items():
        by_base.setdefault(name.split('(')[0], []).append(e)
    return {k: v[0] for k, v in by_base.items() if len(v) == 1}


def match_symbols(funcs, mangled_map, base_idx):
    matched = {}
    for sym in funcs:
        if sym in mangled_map:
            matched[sym] = mangled_map[sym]
            continue
        if sym.startswith('?'):
            # [T80/P0b] mangled 名解码兜底（N2 根因：修饰名返回型写法差异
            # 致 mangler 匹配失败——`?Name@Cls@@...` 的 Name/Cls 与 decomp 的
            # `Cls::Name` 键唯一对应 ✓ 等价地址映射）：139 未匹配中 78 可对上。
            m = re.match(r'^\?(\w+)@(\w+)@@', sym)
            if m:
                key = '%s::%s' % (m.group(2), m.group(1))
                if key in base_idx:
                    matched[sym] = base_idx[key]
                    continue
            continue  # mangled but no mangler match
        cand = sym[1:] if sym.startswith('_') else sym
        cand = re.sub(r'@\d+$', '', cand)
        if cand in base_idx:
            matched[sym] = base_idx[cand]
    return matched


# ─── [mismatch 修法 1+2 · 2026-10-15] rsite 目标名字比对归一 + 析构/构造族容差 ───
# 实测 77 mismatch（41 唯一对）分拣：①纯格式差 7（`X::~X(void)` vs `X::~X`）·
# ②ctor/dtor 命名互换族 11（含跨类 4，IDB ctor/dtor 互换+归属名实不符）·
# ③真差异 23。比对器此前是**裸字符串相等** ⇒ 前两类 = 纯比对器噪声（~85%）。
# ⚠️ 精确定性（T66-F1 族措辞纪律）：不是「析构折叠」（非 COMDAT/ICF）——
# 差异全在**名字层**，我方析构/删除析构语义正确（analyzer 逐站点裁定）。
# 修法 3（IDB 命名修正 12 条）挂账 Phase 2 命名阶段——工具侧容差即恢复判别力。
_DTOR_NAME_RE = re.compile(r'::~|deleting destructor|_scalar_dtor|_sdtor')


def _norm_name(n):
    """修法 1：名字归一——剥尾参表 `(void)`/`(uint)`/`(unsigned int)` + 空白折叠。"""
    n = re.sub(r'\s*\(\s*(?:void|uint|unsigned int)\s*\)\s*$', '',
               (n or '').strip())
    return re.sub(r'\s+', ' ', n).strip()


def _ctor_dtor_family(n):
    """修法 2：ctor/dtor 族判定（同族候选——仅当两侧都属析构/构造链名字时）。

    形：`X::~X` · `X::\`scalar deleting destructor'` · `X::_scalar_dtor*` ·
        `X::_sdtor*` · `X::X`（类名重复=ctor）· `X::ctor*`。
    跨类也认族（IDB ctor/dtor 命名互换 + 归属名实不符时我方符号对，
    analyzer 逐 VA 体证实为析构/构造链）；非族名一律不放行。
    """
    nn = _norm_name(n)
    if _DTOR_NAME_RE.search(nn):
        return True
    m = re.match(r'^([\w:]+)::(\w+)', nn)
    if m:
        cls = m.group(1).split('::')[-1]
        fn = m.group(2).lstrip('_')   # `_UIFrameWnd` 形（前导下划线 ctor 别名）
        if fn == cls or fn.startswith('ctor'):
            return True
    return False


def _rsite_names_match(exp_name, got_name):
    """rsite 目标名比对（纯函数，R15 单测点）：归一相等 或 双侧 ctor/dtor 族。"""
    if _norm_name(exp_name) == _norm_name(got_name):
        return True
    return _ctor_dtor_family(exp_name) and _ctor_dtor_family(got_name)


PROBE_FLAGS = ['/nologo', '/TP', '/c', '/W3']
# docs/compiler_setup.md hypothesis flag set (needs byte-compare calibration —
# that is exactly what --flags-matrix does)
HYPOTHESIS_FLAGS = ['/O2', '/Ob2', '/Oi', '/Ot', '/Oy', '/GF', '/Gy',
                    '/GX', '/GR', '/MT', '/Gd']  # [T79/P0a 补] N1 证据同（导入表无 MSVCRT）


def compare_units(passing, flags, decomp_idx, mangled_map, base_idx,
                  image_base, text, text_rva, text_raw_size=None):
    """Run the S4 byte-match over `passing` units with the given CL flags.

    `text_raw_size` = `.text` 的 `raw_size`，用作**正确的越界界**（R8）。
    None 时退回 `len(text)`（仅为向后兼容，会退化为近恒真的旧行为）。"""
    os.makedirs(pc.OBJ_DIR, exist_ok=True)
    rows = []
    stats = {'symbols': 0, 'matched': 0, 'unmatched': 0,
             'match_L1': 0, 'partial': 0, 'oob': 0, 'compile_skip': 0,
            # R8：两种越界语义**不得合并计数**。
            #   oob_text_end —— 越过 `.text` 尾（真实代码区之外）⇒ 比对数据不可信
            #   oob_file_end —— 越过文件末尾 ⇒ 连字节都取不到
            'oob_text_end': 0, 'oob_file_end': 0,
            # 0b-⑤：名字命中但**无 `va`** 的合成条目（dtor 名字供给），无法定位原始字节 ⇒ 未参与比对。
            # 显式计数，避免它被静默算进「可比对」的 matched 里。
            'unresolved_synth': 0}

    # ROI-1（2026-09-19）：每个 partial 的字节差异明细。**写入独立文件**，
    # 不改 `s4_baseline.json` / `pal3_registry.jsonl` 的形状（ratchet 必须保持可比）。
    detail = {}
    # [T146/P2] 目标核对用：VA → decomp name（原函数重定位目标的语义名）
    va_idx = {e['va']: n for n, e in decomp_idx.items() if isinstance(e, dict) and 'va' in e}
    for n, unit in enumerate(passing, 1):
        src = str(REPO / unit)
        # ROI-1：`.obj` 名改用**稳定哈希**。原来用内建 `hash(unit)`，受 PYTHONHASHSEED 影响
        # ⇒ 跨进程找不到同一个 .obj，任何"事后解释某个 partial"的工具都无法复用产物。
        obj = os.path.join(pc.OBJ_DIR, 's4_%s.obj' % hashlib.md5(unit.encode('utf-8')).hexdigest()[:8])
        out, hard = pc.run_cl(
            ['/Fo' + pc.wpath(obj), pc.wpath(src)]
            + ['/I' + pc.wpath(d) for d in pc.INCLUDE_DIRS],
            timeout=180, flags=flags)
        if hard or not os.path.exists(obj):
            stats['compile_skip'] += 1
            print('  [%3d] COMPILE-SKIP %s (%s)' % (n, unit, hard or 'no obj'))
            continue
        funcs = gc.parse_coff_obj(obj)
        matched = match_symbols(funcs, mangled_map, base_idx)
        stats['symbols'] += len(funcs)
        stats['unmatched'] += len(funcs) - len(matched)
        stats['matched'] += len(matched)
        p1 = pp = 0
        for sym, e in matched.items():
            info = funcs[sym]
            # 0b-⑤ 修正（2026-09-15）：**合成条目**（`_from` 标记的 dtor 名字供给）
            # 只携带 name/signature，**没有 `size`/`va`**（真实 decomp 条目由
            # `load_decomp_index` 提供 `va`/`size` 两键）。
            # ⇒ 原先直接 `e['size']` 会 `KeyError`（实测：match 在第 2 个单元即崩）。
            # 此处用**编译产物**的字节长度作 size（`info['bytes']` 就是该符号的机器码），
            # 这是语义正确的：字节比对要的就是"该函数在 .obj 里的字节数"。
            # `va`（原始二进制地址）合成条目不携带 ⇒ 无法定位原始字节，**跳过比对**
            # 并计入新计数器 `unresolved_synth`（不静默丢弃）。
            if 'va' not in e:
                stats['unresolved_synth'] = stats.get('unresolved_synth', 0) + 1
                continue
            size = e['size'] if 'size' in e else len(info['bytes'])
            idx0 = e['va'] - image_base - text_rva
            # R8：界的语义必须正确 —— 用 **`.text` 的 raw_size**，不是缓冲区长度。
            # 缓冲区长度曾是"文件末尾到 .text 起点"（0x211000），比 .text（0x169000）大一截，
            # 使该判据近恒真（`.rdata` 里的地址也判"在界内"）。本会话第 6 例恒真门禁。
            _limit = text_raw_size if text_raw_size is not None else len(text)
            if idx0 < 0 or idx0 + size > _limit:
                stats['oob'] += 1
                if idx0 < 0 or idx0 + size > len(text):
                    stats['oob_file_end'] += 1
                else:
                    stats['oob_text_end'] += 1
                rows.append({'file': unit, 'symbol': sym, 'name': e['name'],
                             'va': '0x%08X' % e['va'], 'status': 'out_of_range', 'size': size})
                continue
            compiled = info['bytes'][:size]
            relocs = {r for r in info['relocs'] if r < size}
            # [T146/P2] reloc type 映射（DIR32/REL32 目标地址计算方式不同）
            reloc_type_map = {rel_off: r_type
                              for (rel_off, r_type, _sym, _add) in info.get('reloc_sites', ())
                              if rel_off < size}
            res = gc.compare_bytes(compiled, text[idx0:idx0 + size], e['name'],
                                   verbose=False, relocs=relocs,
                                   reloc_type_map=reloc_type_map, va=e['va'])
            status = 'match_L1' if res['perfect'] else 'partial'
            # ---- [T146/P2 度量校正] 重定位核对（纯计量，不影响完美性判据）-----
            # ①站点级值核对（compare_bytes 内部已按站点聚合）——按 L1/全体分账；
            # ②**目标核对（符号法）**：我方 reloc 符号 ↔ 原函数该站点目标 VA 的
            #   名字。REL32（type 0x14）目标 = va+off+4+rel32(原字节)；
            #   DIR32（type 0x06）目标 = 原 4 字节值本身。双侧都解出名字 ⇒ 比对；
            #   任一侧不可解 ⇒ unresolved（导入/字符串/表，不猜）。
            _rt = res['reloc_target']
            for k in ('total', 'ok', 'mismatch', 'unresolved'):
                stats['reloc_' + k] = stats.get('reloc_' + k, 0) + _rt[k]
            if status == 'match_L1':
                stats['l1_bytes'] = stats.get('l1_bytes', 0) + res['total']
                stats['l1_hidden_reloc_bytes'] = (
                    stats.get('l1_hidden_reloc_bytes', 0) + res['reloc_diffs'])
                stats['l1_reloc_covered_bytes'] = (
                    stats.get('l1_reloc_covered_bytes', 0) + len(relocs))
            _orig = text[idx0:idx0 + size]
            for (off, rtype, sym_name, _add) in info.get('reloc_sites', ()):
                if off + 4 > size:
                    continue
                stats['rsite_total'] = stats.get('rsite_total', 0) + 1
                tgt = None
                if rtype == 0x14:      # IMAGE_REL_I386_REL32
                    # [task-6 修 2026-10-15] 读数错位 1 字节：off = COFF reloc
                    # VirtualAddress = rel32 **操作数字段**偏移 ⇒ 读 [off:off+4]。
                    # 原 [off+1:off+5] 把指令首字节并进读数（实测 0x40105A 站点读出
                    # 0x8B000007 垃圾值）⇒ 目标恒查不到 ⇒ rsite 全 unresolved。
                    rel = int.from_bytes(_orig[off:off + 4], 'little', signed=True)
                    tgt = e['va'] + off + 4 + rel
                elif rtype == 0x06:    # IMAGE_REL_I386_DIR32
                    tgt = int.from_bytes(_orig[off:off + 4], 'little')
                exp_name = va_idx.get(tgt) if tgt is not None else None
                got_entry = mangled_map.get(sym_name)
                got_name = got_entry['name'] if got_entry else None
                if exp_name and got_name:
                    if _rsite_names_match(exp_name, got_name):
                        stats['rsite_ok'] = stats.get('rsite_ok', 0) + 1
                    else:
                        stats['rsite_mismatch'] = stats.get('rsite_mismatch', 0) + 1
                        stats.setdefault('rsite_mismatch_samples', []).append(
                            {'va': '0x%08X' % e['va'], 'off': off,
                             'orig': exp_name, 'ours': got_name, 'sym': sym_name[:60]})
                else:
                    stats['rsite_unresolved'] = stats.get('rsite_unresolved', 0) + 1
            if status == 'match_L1':
                p1 += 1
            else:
                pp += 1
            rows.append({'file': unit, 'symbol': sym[:80], 'name': e['name'],
                         'va': '0x%08X' % e['va'], 'status': status,
                         'match_pct': round(res['match_pct'], 1), 'size': size})
            if not res['perfect']:
                detail.setdefault(unit, []).append({
                    'symbol': sym[:80], 'name': e['name'], 'va': '0x%08X' % e['va'],
                    'size': size, 'obj': obj, 'compiled_len': res['compiled_size'],
                    'n_diff': len(res['diffs']), 'first_diff': res['first_diff'],
                    'reloc_skipped': res['reloc_diffs'], 'diffs': res['diffs'][:64]})
        stats['match_L1'] += p1
        stats['partial'] += pp
        print('  [%3d] %-45s funcs=%3d matched=%3d L1=%2d partial=%2d'
              % (n, unit, len(funcs), len(matched), p1, pp))

    print('matched %d/%d symbols | L1 %d | partial %d | oob %d (text_end %d / file_end %d) '
          '| unmatched %d | compile-skip %d | unresolved-synth %d'
          % (stats['matched'], stats['symbols'], stats['match_L1'],
             stats['partial'], stats['oob'], stats['oob_text_end'], stats['oob_file_end'],
             stats['unmatched'], stats['compile_skip'], stats.get('unresolved_synth', 0)))
    total = stats['match_L1'] + stats['partial']
    if total:
        print('L1 rate over matched: %d/%d = %.1f%%'
              % (stats['match_L1'], total, 100.0 * stats['match_L1'] / total))
    # ---- [T146/P2 度量校正] 「字节全同」的隐藏面（当场读，纯计量，不改判据）----
    _lb = stats.get('l1_bytes', 0)
    if _lb:
        print('[metric] L1 字节 %d | 重定位覆盖字节 %d (%.1f%%) | '
              '被跳过且双侧不同的隐藏差异字节 %d (%.1f%% 的 L1 字节 / %.1f%% 的重定位字节)'
              % (_lb, stats.get('l1_reloc_covered_bytes', 0),
                 100.0 * stats.get('l1_reloc_covered_bytes', 0) / _lb,
                 stats.get('l1_hidden_reloc_bytes', 0),
                 100.0 * stats.get('l1_hidden_reloc_bytes', 0) / _lb,
                 100.0 * stats.get('l1_hidden_reloc_bytes', 0)
                 / max(1, stats.get('l1_reloc_covered_bytes', 0))))
    print('[metric] 重定位站点值核对：total=%d ok=%d mismatch=%d unresolved=%d'
          % (stats.get('reloc_total', 0), stats.get('reloc_ok', 0),
             stats.get('reloc_mismatch', 0), stats.get('reloc_unresolved', 0)))
    print('[metric] 重定位目标核对（符号法）：total=%d ok=%d mismatch=%d unresolved=%d'
          % (stats.get('rsite_total', 0), stats.get('rsite_ok', 0),
             stats.get('rsite_mismatch', 0), stats.get('rsite_unresolved', 0)))
    for s in stats.get('rsite_mismatch_samples', [])[:8]:
        print('    [mismatch] %s off=%d orig=%s ours=%s (%s)'
              % (s['va'], s['off'], s['orig'], s['ours'], s['sym']))

    return stats, rows, detail


def _flags_matrix(units, decomp_idx, mangled_map, base_idx, image_base, text, text_rva,
                  text_raw_size=None):
    """Calibrate CL flags: probe defaults vs the hypothesis set vs
    leave-one-out perturbations of the hypothesis. Ranks combos by L1."""
    combos = [('probe-defaults', PROBE_FLAGS), ('hypothesis', list(HYPOTHESIS_FLAGS))]
    for f in HYPOTHESIS_FLAGS:
        combos.append(('hypothesis-minus-' + f.lstrip('/'),
                       [x for x in HYPOTHESIS_FLAGS if x != f]))

    results = []
    for label, flags in combos:
        print('\n--- %s: %s ---' % (label, ' '.join(flags)))
        stats, _ = compare_units(units, flags, decomp_idx, mangled_map,
                                 base_idx, image_base, text, text_rva, text_raw_size)
        results.append({'label': label, 'flags': flags, 'stats': stats})

    results.sort(key=lambda r: (-r['stats']['match_L1'],
                                -r['stats']['match_L1'] - r['stats']['partial']))
    print('\n=== flags matrix (sorted by L1) ===')
    for r in results:
        s = r['stats']
        print('%-28s L1 %3d | partial %3d | matched %3d/%3d' % (
            r['label'], s['match_L1'], s['partial'], s['matched'], s['symbols']))

    out = REPO / 'data' / 'status' / 'flags_matrix.json'
    # S2 接线（接线审计定论）：射程 match 写 s4_scoped_<target>.json，
    # **严禁写 s4_baseline.json**（否则 stats.match_L1 从 86 骤降 => 棘轮误判 => 数据损坏）
    _out_path = scoped_output_path() if is_scoped_run() else OUT_JSON
    if is_scoped_run():
        print('[S2] scoped match output -> %s (baseline untouched)' % _out_path)
    _out = open(_out_path, 'w', encoding='utf-8')
    _out.write_text = _out.write   # 兼容下方 write_text 调用
    out = _out
    # P0-3（多路分析合成）：三个写入点全部射程感知，严禁写 s4_baseline.json
    _scoped = is_scoped_run()
    if _scoped:
        _base = scoped_output_path()
        print('[S2] scoped match: baseline untouched -> %s' % _base)
        _out = open(_base, 'w', encoding='utf-8')
        _out.write_text = _out.write
        out = _out
    out.write_text(json.dumps({'generated_by': 'pipeline/compare_pal3.py',
                               'units': units, 'results': results},
                              indent=1, ensure_ascii=False))
    print('matrix -> %s' % out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--census', default=str(CENSUS))
    ap.add_argument('--limit', type=int, default=0)
    ap.add_argument('--flags', default=None,
                    help='override CL flags, e.g. --flags "/TP /c /O2 /Gy"')
    ap.add_argument('--flags-matrix', action='store_true',
                    help='compile+compare a unit sample under probe defaults, '
                         'the hypothesis set, and leave-one-out perturbations; '
                         'ranks flag combos by L1 match rate')
    args = ap.parse_args()

    census_path = Path(args.census)
    if not census_path.exists():
        # Prerequisite guard: this used to die with a bare FileNotFoundError
        # traceback, and `cli.py match` (which must enforce the L1 ratchet)
        # would then report nothing useful about why.
        print('[ERROR] probe census not found: %s' % census_path, file=sys.stderr)
        print('  data/status/probe_census.json is produced by the S2 probe:', file=sys.stderr)
        print('      python pipeline/cli.py probe all', file=sys.stderr)
        print('  Refusing to run: byte-match L1 cannot be computed without the S2 list.',
              file=sys.stderr)
        sys.exit(2)
    try:
        census = json.loads(census_path.read_text(encoding='utf-8'))
    except (json.JSONDecodeError, UnicodeDecodeError, OSError) as e:
        print('[ERROR] probe census is unreadable/invalid: %s' % census_path, file=sys.stderr)
        print('  %s' % e, file=sys.stderr)
        print('  Re-run: python pipeline/cli.py probe all', file=sys.stderr)
        sys.exit(2)
    s2 = census.get('s2') if isinstance(census, dict) else None
    if not isinstance(s2, dict) or not isinstance(s2.get('results'), list):
        print('[ERROR] probe census has no usable s2.results list: %s' % census_path,
              file=sys.stderr)
        print('  Expected a census written by pipeline/probe_compile.py.', file=sys.stderr)
        print('  Re-run: python pipeline/cli.py probe all', file=sys.stderr)
        sys.exit(2)
    malformed = [i for i, r in enumerate(s2['results'])
                 if not isinstance(r, dict) or 'unit' not in r or 'status' not in r]
    if malformed:
        # Never silently skip an entry: a dropped S2-passing unit would silently
        # shrink the byte-match denominator and inflate the L1 rate.
        print('[ERROR] probe census has %d malformed s2.results entr(ies) (first idx %d): %s'
              % (len(malformed), malformed[0], census_path), file=sys.stderr)
        print('  Every entry needs "unit" and "status". Re-run: '
              'python pipeline/cli.py probe all', file=sys.stderr)
        sys.exit(2)
    passing = [r['unit'] for r in census['s2']['results'] if r['status'] == 'ok']
    if args.limit:
        passing = passing[:args.limit]
    print('S2-passing units: %d' % len(passing))

    decomp_idx = load_decomp_index()
    mangled_map, mangle_failed = build_mangled_map(decomp_idx)
    base_idx = build_basename_index(decomp_idx)
    print('decomp entries: %d | mangled methods: %d (mangle-fail %d) | unambiguous bases: %d'
          % (len(decomp_idx), len(mangled_map), mangle_failed, len(base_idx)))

    image_base, text, text_rva, text_raw_size = exe_text_image()
    print('exe .text: base 0x%X rva 0x%X captured %d bytes' % (image_base, text_rva, len(text)))

    if args.flags_matrix:
        sample = passing[:5] if args.limit == 0 else passing
        return _flags_matrix(sample, decomp_idx, mangled_map, base_idx,
                             image_base, text, text_rva, text_raw_size)

    flags = args.flags.split() if args.flags else PROBE_FLAGS
    stats, rows, detail = compare_units(passing, flags, decomp_idx, mangled_map,
                                        base_idx, image_base, text, text_rva, text_raw_size)

    total = stats['match_L1'] + stats['partial']
    if total:
        print('L1 rate over matched: %d/%d = %.1f%%'
              % (stats['match_L1'], total, 100.0 * stats['match_L1'] / total))

    # P0-3（多路分析，v2）：**三个生产写入点全部射程感知**
    # 射程写 s4_scoped_<name>{,_registry.jsonl,_diff_detail.json}，
    # 严禁写 s4_baseline.json / pal3_registry.jsonl / s4_diff_detail.json
    # （否则 stats.match_L1 从 86 骤降 => 棘轮误判 => 数据损坏）
    _sc = is_scoped_run()
    _tag = SCOPED_OUTPUT if _sc else None
    _base_p = Path(scoped_output_path()) if _sc else OUT_JSON
    _reg_p = (OUT_JSON.parent / ('s4_scoped_%s_registry.jsonl' % _tag)) if _sc else OUT_REG
    _det_p = (OUT_JSON.parent / ('s4_scoped_%s_diff_detail.json' % _tag)) if _sc \
             else (OUT_JSON.parent / 's4_diff_detail.json')
    if _sc:
        print('[S2] scoped match outputs -> %s / %s / %s' % (_base_p.name, _reg_p.name, _det_p.name))
    _base_p.parent.mkdir(parents=True, exist_ok=True)
    _base_p.write_text(json.dumps(
        {'generated_by': 'pipeline/compare_pal3.py', 'flags': flags,
         'stats': stats, 'rows': rows},
        indent=1, ensure_ascii=False))
    with open(_reg_p, 'w') as f:
        for r in rows:
            f.write(json.dumps({'addr': r['va'], 'name': r['name'], 'file': r['file'],
                                'status': r['status'],
                                'match_pct': r.get('match_pct'),
                                'size': r.get('size')}, ensure_ascii=False) + '\n')
    print('report -> %s' % _base_p)
    print('registry -> %s' % _reg_p)
    _detail_out = _det_p
    _detail_out.write_text(json.dumps(
        {'generated_by': 'pipeline/compare_pal3.py (ROI-1 byte-diff detail)',
         'flags': flags, 'l1': stats['match_L1'], 'partial': stats['partial'],
         'units': detail}, indent=1, ensure_ascii=False))
    print('diff detail -> %s (%d partial rows in %d units)'
          % (_detail_out, sum(len(v) for v in detail.values()), len(detail)))


if __name__ == '__main__':
    main()



