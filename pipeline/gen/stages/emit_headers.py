#!/usr/bin/env python3
"""
Generate C++ header files from IDB struct export + IDA function signatures.

For each class, generates include/pal3/gen/<ClassName>.h containing:
  - Base class inheritance
  - Data members with correct types and offsets (as comments)
  - Method declarations from IDA decomp signatures

Sources:
  - asm/pal3/ida_structs.json: struct/enum definitions (exported from IDB)
  - asm/pal3/decomp/*.json: method signatures
  - data/annotations/: field name overrides and template mappings

NO raw PDB data is read. The IDB export is the single source of truth.
"""

from annotation_view import base_names as _base_names, base_entries as _base_entries
import json
import os
import re
import sys
from collections import defaultdict
from pathlib import Path

from pipeline.gen.stages.scope_tree import ScopeTree
from pipeline.gen.stages.collect import get_class_dir

# Module-level cache for _scalar_dtor detection (populated lazily)
_scalar_dtor_classes = None


# [C2501 修 2026-10-19·P2] 合成名→具名顶替映射（渲染层型名置换）
# 机理：export 跳过合成名（task-8 ✓）但成员型仍引旧名 ⇒ C2501 'missing storage-class'
# ×1534 ✗✗ 顶替半闭环——渲染层置换：_inline_X → 具名替身（_origin 源 ✓ 前缀容错）。
_SUPERSEDE_MAP = None


def _get_supersede_map():
    """合成名→具名替身映射（annotation _origin 注记源 ✓ codegen 读注解=已声明例外）。"""
    global _SUPERSEDE_MAP
    if _SUPERSEDE_MAP is None:
        _SUPERSEDE_MAP = {}
        try:
            for _p, _d in _annview.iter_structs(None):
                _orig = str(_d.get('_origin') or '')
                _m = re.search(r'原合成名 ((?:_inline_\S+?|\S+?::\$\S+?))(?=[\s。；;，、）)]|$)', _orig)
                if _m and _d.get('name'):
                    _SUPERSEDE_MAP[_m.group(1)] = _d['name']
                    _SUPERSEDE_MAP[_m.group(1).replace('::$', '__$')] = _d['name']
                    # [C2501 修·基名坍缩] `_inline_X::$hash` 键 ⇒ 亦立 `_inline_X` 基名键
                    # （_origin 只记 hash 形 ✗ 基名形（无 hash）引用于成员型 ⇒ 须坍缩映射 ✓）
                    _base = re.sub(r'::\$[0-9A-Fa-f]+$', '', _m.group(1))
                    _base = re.sub(r'__\$[0-9A-Fa-f]+$', '', _base)
                    if _base and _base not in _SUPERSEDE_MAP:
                        _SUPERSEDE_MAP[_base] = _d['name']
        except Exception:
            pass
    return _SUPERSEDE_MAP


def _supersede_type_name(t):
    """型名顶替（纯函数形）：合成名 → 具名替身（精确+前缀容错）。"""
    if not t:
        return t
    _m = _get_supersede_map()
    _tn = t.replace('::$', '__$')
    if _tn in _m:
        return _m[_tn]
    for _k, _v in _m.items():
        if _tn.startswith(_k.replace('::$', '__$')):
            return _v
    return t


# [C2011 修 2026-10-19·P0-A] ns-decl 声明唯一化登记表（跨头共享）
# 机理：hoist 每头各插同型 decl ⇒ 双头同 TU include ⇒ 'union _inline_X' C2011
# type redefinition ×2081 ✗✗ —— 声明层去重：登记表+共享头（_ns_udts.h）。
_NS_DECL_REGISTRY = {}   # type_name -> (decl_lines, member_line_form)
_NS_REGISTERED_BLOCKS = set()  # [P0-A 修 2026-10-19·更优案] 注册侧块去重（纵深防御）


def named_udt_scope_form(type_name, kind, member_name, body_lines):
    """命名内联 UDT 的命名空间作用域提升形（纯函数，R15 单测点）→ (ns_lines, member_line)。

    病灶（2026-10-16 C2228×15）：decomp 局部声明用 IDA 合成名 `union _inline_tagCam_yaw`
    （TU 全局作用域），而发射把同名 UDT **嵌套在类内** ⇒ 跨 TU 裸名解析失败（C2228/C2059）。
    修法=定义提升到命名空间作用域（布局不变等价变换）：类前出 `union _inline_X {…};`
    类内成员改引用 `union _inline_X name;`。仅 `_inline_*` 合法标识符形可提升；
    `Cls::$123` 等合成名/普通类型名维持原渲染（最小 churn）。

    返回 (None, None) 表示不适用（调用方回退现行类内渲染）。
    """
    if not type_name or not type_name.startswith('_inline_'):
        return None, None
    if '::' in type_name or '$' in type_name or not type_name.replace('_', '').isalnum():
        return None, None
    if kind not in ('union', 'struct'):
        return None, None
    ns = ['%s %s {' % (kind, type_name)]
    ns.extend(body_lines)
    ns.append('};')
    member = '%s %s %s;' % (kind, type_name, member_name)
    return ns, member


def hoist_udt_block(block_lines, member_name, cls_name=None):
    """类内命名 UDT 块文本 ⇒ (命名空间 decl 行, 成员行)（纯函数，R15 单测点）。

    输入为发射器产出的类内块（首行 `    <kind> <name>{ // +0x..`，尾行 `    } member;`）。
    布局不变等价变换：body 缩进 8→4，定义包 #pragma pack(push,1)/pop（打包尺寸语义随行）。
    未命名块返回 (None, None)——调用方维持原渲染。
    """
    if not block_lines or len(block_lines) < 3:
        return None, None
    m = re.match(r'^\s+(union|struct)\s+(\S+)\s*\{', block_lines[0])
    if not m:
        return None, None
    kind, type_name = m.group(1), m.group(2)
    body = [re.sub(r'^        ', '    ', l) for l in block_lines[1:-1]]
    ns, member = named_udt_scope_form(type_name, kind, member_name, body)
    if ns is None:
        return None, None
    fwd = []
    # 自引用（body 含本类指针）⇒ hoist 到类前后向引用断裂（2026-10-16 全树 L76 误伤
    # 实锤：`PalScript *` 在 class PalScript 前未声明 ⇒ C2143/C2501 ×140 单元）⇒ 补前向声明
    if cls_name and re.search(r'\b%s\s*\*' % re.escape(cls_name), '\n'.join(body)):
        fwd = ['class %s;' % cls_name]
    return (['#pragma pack(push,1)'] + fwd + ns + ['#pragma pack(pop)'],
            '    ' + member)

def _get_scalar_dtor_classes():
    """Detect classes with _scalar_dtor.

    S0（2026-10-09）：改读缓存 —— 原为扫描 decomp 目录，射程 export 会让输入从全量
    坍缩到 1，导致大量类被误判为「无 _scalar_dtor」，漏插 virtual ~Cls()，
    编译器不发 ??_G，match 匹配不到该符号，L1 静默丢失。
    """
    # S0 修复（对抗复核实证）：原写法 `_scalar_dtor_classes = set()` 后再
    # `return load_header_facts()[...]` 会把模块级缓存**清空为 set()**，
    # 而守卫 `is not None` 对空 set 也为真 ⇒ 第二次调用起永久返回空集
    # ⇒ 30 个生成头丢虚析构（比 v1 缺陷更严重）。正确做法：结果写回模块变量。
    global _scalar_dtor_classes
    if _scalar_dtor_classes is not None:
        return _scalar_dtor_classes
    _scalar_dtor_classes = set(load_header_facts()['scalar_dtor_classes'])
    return _scalar_dtor_classes


def _get_scalar_dtor_classes_scan_impl():
    """S0 前的原扫描实现，保留备查（等价性对照用）。"""
    decomp_dir = PROJECT_ROOT / "asm" / "pal3" / "decomp"
    if not decomp_dir.exists():
        return _scalar_dtor_classes
    for f in sorted(decomp_dir.glob("*.json")):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except:
            continue
        name = d.get('name', '')
        if '::' not in name:
            continue
        cls = name.split('::')[0]
        method = name.split('::', 1)[1].split('(')[0]
        # 【2026-09-15 修】Hex-Rays 的**反引号特名**必须先归一化，否则漏判：
        #   `` `scalar deleting destructor' `` → `_scalar_dtor`
        #   `` `vector deleting destructor' `` → `_vector_dtor`
        # 为什么必须做：`collect.py` 的跳过判据、以及本函数下游的
        # `if cls_name in _get_scalar_dtor_classes() and not _has_dtor:
        #      lines.append("virtual ~%s() {}")` 都依赖这个判定。
        # 漏判的后果（实测）：该类的**显式非虚析构**保留 ⇒ 编译器**不发射 `??_G`**
        #   ⇒ `match` 匹配不到该符号 ⇒ **该类的 L1（字节全同函数）丢失**。
        # 实例：`UIStatic`（其 vtable 槽 5 = 0x004407A0 `` UIStatic::`scalar deleting destructor' ``；
        #   生成头里却是 `~UIStatic();` 非虚 ⇒ 无 `??_G`）。
        method = re.sub(r'`?\s*scalar deleting destructor\s*\'?', '_scalar_dtor', method)
        method = re.sub(r'`?\s*vector deleting destructor\s*\'?', '_vector_dtor', method).strip()
        if '_scalar_dtor' in method or '_vector_dtor' in method or method.startswith('_sdtor'):
            _scalar_dtor_classes.add(cls)
    return _scalar_dtor_classes


# Module-level cache for underscore-to-bare typedef aliases (populated lazily)
_underscore_aliases = None  # dict: '_Texture_Info' -> 'Texture_Info', etc.
# 批B 2026-10-06：模块级白名单（_Console 等真类型——方法发射路径（:909）与类型路径（:2813）共用）
_UNDERSCORE_TYPES = {
    '_Texture_Info', '_Console', '_Texture_uv', '_Tex_uv',
    '_Item_List_Info', '_MapElement', '_Item', '_UIPOS',
    '_PlugInfo', '_FLOORPARAM', '_PURGE_INFO', '_TimeMgr',
    '_btnOPTDATA', '_CLOUD', '_CONTEXT', '_SAMPLE',
    '_STREAM', '_SUBMAP', '_FLTPROVIDER', '_DIG_DRIVER',
    '_Collvec', '_Console__ConCmd', '_Btn_BtnID',
}

def _get_underscore_aliases():
    """Detect _X -> X typedef aliases from decomp filename/signal evidence.

    In MSVC 6.0 projects, internal types often carry an underscore prefix
    (e.g. struct _Texture_Info) with a project-level typedef to the bare
    name (typedef _Texture_Info Texture_Info).  The decomp export uses the
    bare name because Hex-Rays resolves the typedef.  We need to emit the
    typedef in the generated header so the code compiles with the same
    naming convention as the original project.
    """
    # S0 修复：同上 —— 结果必须写回模块变量，否则第二次调用起返回空 dict
    global _underscore_aliases
    if _underscore_aliases is not None:
        return _underscore_aliases
    _underscore_aliases = dict(load_header_facts()['underscore_aliases'])
    return _underscore_aliases


def _get_underscore_aliases_scan_impl():
    """S0 前的原扫描实现，保留备查。"""
    ida_structs_file = PROJECT_ROOT / "asm" / "pal3" / "ida_structs.json"
    if not ida_structs_file.exists():
        return _underscore_aliases
    try:
        ida = json.load(open(ida_structs_file, encoding='utf-8'))
    except:
        return _underscore_aliases
    decomp_dir = PROJECT_ROOT / "asm" / "pal3" / "decomp"
    if not decomp_dir.exists():
        return _underscore_aliases
    # Collect bare names from decomp filenames: "Texture_Info_CalculateUV..." -> "Texture_Info"
    bare_in_decomp = set()
    for f in decomp_dir.glob("*.json"):
        fname = f.stem  # e.g. "Texture_Info_CalculateUVint_0053fcf0"
        parts = fname.split('_')
        # Try progressively longer prefixes as the class name
        for i in range(1, min(5, len(parts))):
            candidate = '_'.join(parts[:i])
            if candidate and len(candidate) >= 3:
                bare_in_decomp.add(candidate)
    # Match: for each _-prefixed type in ida_structs, check if bare name appears in decomp
    for type_name in ida:
        if not type_name.startswith('_') or len(type_name) < 4:
            continue
        bare = type_name[1:]  # strip leading underscore
        if bare in bare_in_decomp:
            # Verify it's not a system type (would be blocked by SKIP_PREFIXES)
            if not should_skip_class(type_name):
                _underscore_aliases[type_name] = bare
    return _underscore_aliases


PIPELINE_ROOT = Path(__file__).parent.parent.parent  # pipeline/
PROJECT_ROOT = PIPELINE_ROOT.parent
ANNOTATIONS_DIR = PROJECT_ROOT / "data" / "annotations"

# 2026-09-20 审计 P1-5：注解直读的**单一读点**。
# 别名用 `_annview`（**不是 `_av`**）：本文件多处函数体内曾有 `import ... as _av`
# 形式的局部导入，会使 `_av` 变成**函数局部名**并遮蔽模块级别名 ⇒ 在函数内更早的位置
# 引用它就会 `UnboundLocalError`（2026-09-20 实测：该错误被 `except Exception: pass`
# 静默吞掉，导致 635 个类的 known_members 覆盖整体失效）。
try:
    import annotation_view as _annview
except ImportError:
    from pipeline.gen import annotation_view as _annview
IDA_STRUCTS_FILE = PROJECT_ROOT / "asm" / "pal3" / "ida_structs.json"
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
OUTPUT_DIR = PROJECT_ROOT / "pal3" / "src"
OVERRIDES_DIR = PROJECT_ROOT / "include" / "pal3" / "overrides"

# ---------------------------------------------------------------------------
# S0：decomp 派生的头决策事实缓存
# ---------------------------------------------------------------------------
# 动机（对抗复核实证 2026-10-09）：本模块有 **4 条** decomp 依赖会「决定头内容」：
#   1) _get_scalar_dtor_classes()  虚析构判定（漏判 => 不发 ??_G => L1 静默丢）
#   2) _get_underscore_aliases()  _X->X typedef 别名
#   3) :2386 虚析构注入的独立复算路径
#   4) _referenced_identifiers() -> _forced_global_entries() 「全局须定义」
# 射程 export 只写 1 个 decomp JSON 会让这 4 条的输入从全量坍缩 => 头决策被污染。
# => 物化成缓存（随全量 export 刷新），本模块改读缓存，与「当前 decomp 目录有几个文件」解耦。
_HEADER_FACTS_PATH = PROJECT_ROOT / "data" / "status" / "_decomp_derived_header_facts.json"


def save_header_facts(facts, path=None):
    """物化 decomp 派生的头决策事实（随全量 export 刷新）。

    facts: {'scalar_dtor_classes': set[str], 'underscore_aliases': dict[str,str],
            'forced_global_names': set[str], 'vptr_inject_classes': set[str]}
    落盘为确定性 JSON（set 排序 + sort_keys）=> 可 diff、可复现。
    """
    p = Path(path) if path else _HEADER_FACTS_PATH
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(json.dumps({
        'scalar_dtor_classes': sorted(facts['scalar_dtor_classes']),
        'underscore_aliases': facts['underscore_aliases'],
        'forced_global_names': sorted(facts['forced_global_names']),
        'vptr_inject_classes': sorted(facts['vptr_inject_classes']),
    }, indent=2, sort_keys=True), encoding='utf-8')


def load_header_facts(path=None):
    """读缓存。缺失时**报错退出，不静默回退到目录扫描**。

    回退会掩盖 v1 缺陷：射程 export 只写 1 个 decomp JSON 时，目录扫描会从全量
    坍缩到 1，头决策被污染且无任何告警。
    """
    p = Path(path) if path else _HEADER_FACTS_PATH
    if not p.exists():
        raise RuntimeError(
            '缺少 %s —— 请先跑全量 export 生成缓存（S0）。'
            '禁止回退到 decomp 目录扫描：会让射程 export 污染头决策。' % p)
    d = json.loads(p.read_text(encoding='utf-8'))
    return {
        'scalar_dtor_classes': set(d['scalar_dtor_classes']),
        'underscore_aliases': d['underscore_aliases'],
        'forced_global_names': set(d['forced_global_names']),
        'vptr_inject_classes': set(d['vptr_inject_classes']),
    }


_ida_structs_cache = None  # ida_structs.json (export output, primary source)

def _get_ida_structs():
    global _ida_structs_cache
    if _ida_structs_cache is not None:
        return _ida_structs_cache
    if IDA_STRUCTS_FILE.exists():
        with open(IDA_STRUCTS_FILE, encoding='utf-8') as f:
            _ida_structs_cache = json.load(f)
    else:
        _ida_structs_cache = {}
    return _ida_structs_cache


# SDK 类型尺寸（`data/annotations/sdk_types.json`）。
#
# 为什么需要单独一源：`_estimate_member_size` 原先只查 ida_structs.json，
# 而 SDK 类型（`tagRECT` / `tagPOINT` / `_D3DFORMAT` …）**不在** ida_structs 里
# —— 它们由 sdk_types.json 定义（`apply_annotations.py` 的 2b 步消费）。
# 实测：`tagRECT` 在 sdk_types 里 `binary_size=16`，在 ida_structs 里**不存在**，
# 于是 UIWnd 的 `m_rect` 被估成 4 字节、生成头出现错误的 `_gap_014[12]`。
# 2026-09-15 由独立复核 `761ba967` 指出（其 F1），captain 定位到具体缺口。
#
# 本缓存只用于**尺寸估计**，不参与类型发射 ⇒ 修复风险局部化。
_sdk_type_sizes_cache = None

def _get_sdk_type_sizes():
    """返回 {类型名: 字节数}，来源 data/annotations/sdk_types.json。"""
    global _sdk_type_sizes_cache
    if _sdk_type_sizes_cache is not None:
        return _sdk_type_sizes_cache
    out = {}
    # P1-5（第九批）：路径收敛到单一读点；**精确 try 保持原样**（不换成宽捕获原语）
    path = _annview.annotation_json_path('sdk_types.json')
    if os.path.exists(path):
        try:
            with open(path, encoding='utf-8') as f:
                data = json.load(f)
            # 兼容 list-of-dict 与 dict 两种形态
            entries = data if isinstance(data, list) else list(data.values())
            for e in entries:
                if not isinstance(e, dict):
                    continue
                nm = e.get('name')
                sz = e.get('binary_size') or e.get('size')
                if nm and isinstance(sz, int) and sz > 0:
                    out[nm] = sz
        except (OSError, json.JSONDecodeError, TypeError):
            out = {}
    _sdk_type_sizes_cache = out
    return out

_header_errors = []
# Map IDA ordinal types to their actual type names
ORDINAL_MAP = {
    '#1472': 'gbTexture',
    '#1461': 'gbGeomNode',
    '#1455': 'gbAudioManager',
    '#1465': 'gbRenderEffect',
}


ORDINAL_MAP = {
    '#1472': 'gbTexture',
    '#1461': 'gbGeomNode',
    '#1455': 'gbAudioManager',
    '#1465': 'gbRenderEffect',
}

def _resolve_ordinal_type(t):
    for k, v in ORDINAL_MAP.items():
        t = t.replace(k, v)
    return t


def _sanitize_filename(name):
    """Sanitize a C++ type name for use as a cross-platform filename."""
    name = name.replace('<', '_').replace('>', '_')
    name = name.replace(':', '_').replace('"', '_')
    name = name.replace('?', '_').replace('*', '_')
    name = name.replace('|', '_').replace('\\', '_').replace('/', '_')
    # Template argument lists introduce commas/spaces/parens — all illegal
    # (and colliding) in filenames; both the file and its #include refs go
    # through here so they stay consistent.
    name = name.replace(',', '_').replace(' ', '_')
    name = name.replace('(', '_').replace(')', '_')
    return name


# Primitives that cannot be forward-declared as class in C++
_GLOBALS_PRIMITIVES = {
    'int', 'char', 'float', 'double', 'void', 'long', 'short', 'bool',
    'unsigned', 'signed', 'wchar_t',
    '__int8', '__int16', '__int32', '__int64',
    'unsigned __int8', 'unsigned __int16', 'unsigned __int32', 'unsigned __int64',
    'BYTE', 'WORD', 'DWORD', 'QWORD', 'UINT', 'ULONG', 'BOOL',
    'INT8', 'INT16', 'INT32', 'INT64', 'UINT8', 'UINT16', 'UINT32', 'UINT64',
    'DOUBLE', 'FLOAT', 'LONG', 'SHORT', 'CHAR', 'VOID',
}


def _ann_struct_path(name):
    """Check if a struct exists in ida_structs.json (export output)."""
    return _get_ida_structs().get(name, None)


# 2026-09-20 审计（P1-5 收尾）：此处原有 `load_annotations_data()` —— 一道
# "调用即抛 RuntimeError"的**绊线**，用来宣称"codegen 禁止读 annotation"。
# 但它**从未被任何代码调用**（全仓 grep 只有定义本身）⇒ 是**永远不会触发的假防护**，
# 且其宣称的"绝对禁止"与事实相反：本文件确有 10 处注解直读（审计 §2/§3），
# 属于**已声明的例外**（取舍理由见 `pipeline/ida/export_full.py` 头部的
# `[t4-DECLARED-EXCEPTION]` 声明块）。
#
# **实际生效的规则（可检查、非假防护）**：
#   codegen 侧对 `data/annotations/**` 的读取**必须经单一读点**
#   `pipeline/gen/annotation_view.py`（`iter_structs` / `struct_by_class` /
#   `template_bases` / `annotation_json_path` / `load_annotation_json` …）。
#   该文件的 10 处直读已于 2026-09-20 全部收敛到它，且每处都过了
#   "逻辑/路径等价 + `codegen all` 产物 `diff -r` 字节相同"两道验证。
# 旧绊线已删除：留着它只会给人"红线已被机械封死"的错觉。


def class_vtable_slots(cls_name, with_addr=False, vtables=None, methods=None):
    """返回该类的虚表 slot 短名列表（按 vtable 顺序，跨多张表去重）。

    名字按 slot 地址从该类 methods -> functions 解析（Trust by address）。
    当 with_addr=True 时，返回 list of (addr_hex_str, short_name) 对。
    
    vtables/methods: from ida_structs.json (export output).
    If not provided, fallback to annotation data (architecture debt path).
    """
    if vtables is None or methods is None:
        _is = _get_ida_structs().get(cls_name)
        if not _is or not _is.get('vtables'):
            return [] if not with_addr else []
        vtables = _is['vtables']
        methods = _is.get('methods', {})
        functions = {}
    else:
        functions = {}
    if with_addr:
        items = []
        seen_addrs = set()
        for vt in vtables:
            for slot in vt.get('slots', []):
                addr = slot.get('addr', '')
                if addr in seen_addrs:
                    continue
                seen_addrs.add(addr)
                entry = methods.get(addr) or functions.get(addr) or {}
                raw = entry.get('name', '')
                short = raw.split('::')[-1] if '::' in raw else raw
                if short and addr:
                    items.append((addr, short))
        return items
    names = []
    for vt in vtables:
        for slot in vt.get('slots', []):
            addr = slot.get('addr', '')
            entry = methods.get(addr) or functions.get(addr) or {}
            raw = entry.get('name', '')
            short = raw.split('::')[-1] if '::' in raw else raw
            if short:
                names.append(short)
    return names


# Skip STL/CRT/Windows types (already defined by system headers)
SKIP_CLASSES = {
    'std', 'stdiobuf', 'exception', 'type_info', 'filebuf', 'string',
    'strstreambuf', 'ios_base', 'facet', 'codecvt_base',
    '_ThrowInfo', '_CatchableType', '_CatchableTypeArray',
    # C/C++ reserved words that IDA may use as class names
    'float', 'int', 'char', 'void', 'double', 'long', 'short', 'bool',
    # Windows SDK typedefs that clash with IDA struct names
    'DOUBLE', 'FLOAT', 'INT', 'CHAR', 'VOID', 'LONG', 'SHORT', 'BOOL',
    'BYTE', 'WORD', 'DWORD', 'UINT', 'ULONG',
    # Windows types
    'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG', 'RECT', 'POINT', 'SIZE',
    'tagRGBQUAD', 'RGBQUAD',
    'WNDCLASSA', 'tagWNDCLASSA', 'tagOFNA',
    '_FILETIME', '_SYSTEMTIME', '_MEMORYSTATUS', '_SECURITY_ATTRIBUTES',
    '_OSVERSIONINFOA', '_STARTUPINFOA', '_WIN32_FIND_DATAA',
    '_GUID', 'GUID', 'IID',
    'tagNMHDR', 'tagNMITEMACTIVATE', 'tagLVCOLUMNA', 'tagLVITEMA',
    'tagTCITEMA', 'tagCOPYDATASTRUCT', 'tagPALETTEENTRY',
    'tagKBDLLHOOKSTRUCT',
    # Windows handle types (HXXX__)
    'HICON__', 'HWND__', 'HDC__', 'HINSTANCE__', 'HBRUSH__',
    'HHOOK__', 'HKEY__', 'HMONITOR__', 'HWAVEOUT__',
    # COM/OLE enums and types (defined by platform SDK)
    'tagCLSCTX', 'tagCOINIT', 'tagCALLCONV', 'tagCALLTYPE',
    'tagFUNCKIND', 'tagFUNCFLAGS', 'tagINVOKEKIND', 'tagVARKIND',
    'tagVARFLAGS', 'tagTYPEKIND', 'tagTYPEFLAGS', 'tagSYSKIND',
    'tagLIBFLAGS', 'tagDESCKIND', 'tagCHANGEKIND', 'tagTYMED',
    'tagDVASPECT', 'tagSTGTY', 'tagSTGC', 'tagSTGMOVE',
    'tagSTATFLAG', 'tagLOCKTYPE', 'tagSTREAM_SEEK', 'tagBIND_FLAGS',
    'tagMKSYS', 'tagMKREDUCE', 'tagADVF', 'tagSF_TYPE',
    'tagREGCLS', 'tagPENDINGMSG', 'tagPENDINGTYPE', 'tagSERVERCALL',
    'tagMEMCTX', 'tagMSHCTX', 'tagMSHLFLAGS', 'tagSTDMSHLFLAGS',
    'tagEXTCONN', 'tagBINDSPEED', 'tagBINDSTATUS', 'tagBINDSTRING',
    'tagOLERENDER', 'tagOLEUPDATE', 'tagOLEVERBATTRIB', 'tagOLEMISC',
    'tagOLECLOSE', 'tagOLECONTF', 'tagOLEGETMONIKER', 'tagOLEWHICHMK',
    'tagOLELINKBIND', 'tagUSERCLASSTYPE', 'tagDISCARDCACHE',
    'tagURLZONE', 'tagURLTEMPLATE', 'tagCOWAIT_FLAGS',
    'tagDCOM_CALL_STATE', 'tagDATADIR',
    'tagEOLE_AUTHENTICATION_CAPABILITIES', 'tagExtendedErrorParamTypes',
    'tagDOMNodeType', 'tagXMLEMEM_TYPE', 'tagShutdownType',
    'tagApplicationType',
    'HandlerType',
    # CRT / Runtime
    '_iobuf', 'FILE', '_cpinfo', '_EXCEPTION_RECORD', 'EXCEPTION_RECORD',
    'Concurrency',
    # DirectX / DirectInput
    '_DIMOUSESTATE2',
    # IDA template instantiation artifacts
    'primitive', 'uint',
    # gbengine (separate library) — auto-populated below
}

# Auto-detect classes defined in gbengine headers
_GBENGINE_DIR = Path(__file__).parent.parent.parent.parent / "include" / "gbengine"

# F53（第 105 轮）：gbengine 头用 `class GBAPI Foo` / `struct __declspec(dllimport) Foo`
# 声明导出类型。扫描类型名时必须跳过导出宏/declspec，否则该类型不再被认作 gbengine 类型，
# codegen 会为它再生成一份 pal3 侧头文件 ⇒ 与 include/gbengine 里的定义冲突（C2011）。
_EXPORT_MACROS = ('GBAPI', 'DLLAPI', 'DLLEXPORT', 'DECLSPEC', 'EXPORT', 'API')
_CLASS_DECL_RE = re.compile(r'^(?:class|struct|enum)\s+(\w+)')




def _get_vtable_addr(cls_name):
    """从 annotation vtables[0].addr 获取 vtable 地址。"""
    try:
        _d = _get_ida_structs().get(cls_name, {})
        vts = _d.get('vtables') or []
        if vts and isinstance(vts[0], dict):
            return vts[0].get('addr')
    except: pass
    # 回退到 annotation 文件
    try:
        _p = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(
            os.path.abspath(__file__))), '..', '..', 'data', 'annotations', 'structs', f'{cls_name}.json'))
        import json as _json
        _d = _json.load(open(_p, encoding='utf-8'))
        vts = _d.get('vtables') or []
        if vts and isinstance(vts[0], dict):
            return vts[0].get('addr')
    except: pass
    return None

def _read_vtable_from_binary(vt_addr, max_slots=64):
    """直接从二进制读 vtable 槽位（不依赖 annotation/IDB 完整性）。
    返回 [(addr_hex, name_or_None), ...]。"""
    import struct
    _d = os.path.dirname(os.path.abspath(__file__))
    _bin = os.path.join(_d, '..', '..', '..', 'original', 'PAL3.exe')
    _bin = os.path.normpath(_bin)
    if not os.path.exists(_bin):
        return []
    def _va2off(va):
        if va >= 0x56A000: return va - 0x56A000 + 0x16A000
        if va >= 0x401000: return va - 0x401000 + 0x1000
        return va
    if isinstance(vt_addr, str):
        vt_addr = int(vt_addr, 16)
    slots = []
    try:
        with open(_bin, 'rb') as f:
            f.seek(_va2off(vt_addr))
            for i in range(max_slots):
                data = f.read(4)
                if len(data) < 4: break
                a = struct.unpack('<I', data)[0]
                if 0x401000 <= a < 0x56A000:
                    slots.append((hex(a), None))
                else:
                    break
    except Exception:
        pass
    return slots


def _class_decl_name(line):
    """`line` 声明的类型名；容忍 `__declspec(...)` 与导出宏前缀。"""
    s = re.sub(r'__declspec\s*\([^)]*\)\s*', '', line)
    for _mac in _EXPORT_MACROS:
        s = re.sub(r'^(class|struct|enum)\s+%s\s+' % _mac, r'\1 ', s)
    _m = _CLASS_DECL_RE.match(s)
    return _m.group(1) if _m else None


if _GBENGINE_DIR.exists():
    for _hf in _GBENGINE_DIR.glob("*.h"):
        with open(_hf, 'r', encoding='utf-8', errors='replace') as _fh:
            for _line in _fh:
                _nm = _class_decl_name(_line)
                if _nm:
                    SKIP_CLASSES.add(_nm)

# 枚举识别（2026-09-23）：MSVC6 无 sized enum ⇒ **枚举恒为 int（4 字节）**。
# `ida_structs.json` 把枚举记为 size=1 是 **IDB 枚举导入伪影** ✗（实测：UIStaticFlex 的
# `gbFontType m_fonttype@0xA0` 被当成 1 字节后插 `_gap_0A1[3]` ⇒ 与 4 字节枚举本体碰撞
# ⇒ 后续成员整体 +4 ✗ 并沿 DAG 传播）。知识源（数据层，非估计器特判 ✓）：
#   ① `data/annotations/enums.json`（66 项，values 已登记）
#   ② `include/gbengine/*.h` 的 `enum` 声明（gbengine 是独立项目，源码在本仓 ✓✓）
# 证据：W4 mangled（`?SetFontType@UIPushButton@@QAEXW4gbFontType@@@Z`）+ 步长
# （m_fonttype@0x4C → m_state@0x50 → m_texarray@0x54 均为 4）+ MSVC6 ABI。
_ANNOTATION_ENUMS_PATH = _GBENGINE_DIR.parent.parent / "data" / "annotations" / "enums.json"
_ANNOTATION_ENUMS = None

_GBENGINE_ENUMS = set()
if _GBENGINE_DIR.exists():
    for _hf in _GBENGINE_DIR.glob("*.h"):
        with open(_hf, 'r', encoding='utf-8', errors='replace') as _fh:
            for _line in _fh:
                _m = re.match(r'enum\s+(\w+)', _line.strip())
                if _m:
                    _GBENGINE_ENUMS.add(_m.group(1))


def _get_annotation_enums():
    global _ANNOTATION_ENUMS
    if _ANNOTATION_ENUMS is None:
        try:
            import json as _json
            with open(_ANNOTATION_ENUMS_PATH, 'r', encoding='utf-8') as _f:
                _ANNOTATION_ENUMS = set(_json.load(_f).keys())
            # 嵌套枚举键（`Cls::ENUM`）同时按 `::` 后缀索引 ⇒ 成员类型只写短名也能命中 ✓
            _ANNOTATION_ENUMS |= {k.rsplit('::', 1)[-1] for k in _ANNOTATION_ENUMS if '::' in k}
        except Exception:
            _ANNOTATION_ENUMS = set()
    return _ANNOTATION_ENUMS


def _is_known_enum(t):
    """该类型名是否为已知枚举（enums.json 或 gbengine 头）✓"""
    t = (t or '').strip()
    if '::' in t:
        t = t.rsplit('::', 1)[-1].strip()
    return t in _get_annotation_enums() or t in _GBENGINE_ENUMS


def _packed_inline_size(data, _depth=0):
    """inline union/struct 的 **pack(1) 打包尺寸**（W4-C0b；复核 c34f38aa A1 公式，
    复核 6dc45d18 全语料 A/B：953/956 逐字节等价 + SceneMgr 404→402 唯一修正 + 21 记录全表）：
    - union = max(子打包尺寸)；struct = **max(offset + 子打包尺寸)**（非求和——
      内部空洞由发射器 _gap 填充后等价）；
    - 数组 = 各维积 × 元素（hex 维含 0X 大写）；
    - **具名类型查自身 size**（禁递归求和：tagTeamSlotsBOverlay 成员和 607 vs 真实 800 实证）；
    - `_inline_*`/`::$` 合成类型按 data_members 递归打包（export size 可能是自然对齐值：
      _inline_SceneMgr_ 404 vs 402 ⇒ `_gap_C812[54]` 虚报 2B）；dict 型 type 直接递归（P1-1）。
    返回整数字节；无 data_members ⇒ None（调用方回退 export size）。
    共享承诺（复核 6dc45d18 Q8 修订为将来时）：**待守卫 add_member 落地时须复用本函数**
    （推荐抽叶子模块 pipeline/gen/inline_size.py + ida 表参数注入 + 同函数断言测试；
    现在时承诺已撤——tools 反向 import 有双模块身份分裂风险）。"""
    if _depth > 8:                      # P2-3 递归护栏（真实 synth 引用图无环，防御性）
        return None
    dms = (data or {}).get('data_members') or []
    if not dms:
        return None
    is_union = (data or {}).get('kind') == 'union'
    ida = _get_ida_structs()
    total = 0
    for d in dms:
        if not isinstance(d, dict):     # P1-2 附件（6dc45d18）：非 dict 成员项防崩
            continue
        off = d.get('offset', 0) or 0
        t_raw = d.get('type') or 'int'
        if isinstance(t_raw, dict):     # P1-1：dict 型 type = 注解 inline union 形态，直接递归
            sub0 = _packed_inline_size(t_raw, _depth + 1)
            sz0 = sub0 if sub0 is not None else 4
            total = max(total, sz0) if is_union else max(total, off + sz0)
            continue
        t = str(t_raw).strip()
        n = 1
        dims = re.findall(r'\[(?:0[xX][0-9a-fA-F]+|\d+)\]', t)   # P3-2：0X 大写维
        if dims:
            t = re.sub(r'\[(?:0[xX][0-9a-fA-F]+|\d+)\]', '', t).strip()
            for dd in dims:
                n *= int(dd[1:-1], 0)
        # P1-2（6dc45d18）：查表前去 `struct `/`union `/`class ` 前缀；键序=精确→
        # 展平(X::Y→X_Y，真实语料 C2DSpark_tagSpark 是展平键)→base 后缀。
        t_norm = re.sub(r'^(?:struct|union|class)\s+', '', t).strip()
        base_norm = t_norm.rsplit('::', 1)[-1] if '::' in t_norm else t_norm
        rec = ida.get(t_norm) or ida.get(t_norm.replace('::', '_')) \
            or ida.get(base_norm) or {}
        synth = t_norm.startswith('_inline_') or '::$' in t_norm
        _sz_raw = rec.get('size')
        _sz_ok = isinstance(_sz_raw, int) or (isinstance(_sz_raw, str) and _sz_raw.isdigit())
        if _sz_ok and not synth:
            sz = int(_sz_raw) * n            # 具名类型查表（禁递归求和）
        elif rec.get('data_members'):
            sub = _packed_inline_size(rec, _depth + 1)
            sz = (int(_sz_raw) if (_sz_ok and sub is None) else (sub or 4)) * n
        elif _sz_ok:                         # P2-1：synth 有 size 无成员 ⇒ size 回退
            sz = int(_sz_raw) * n
        else:
            sz = _type_extent(t_raw)         # P3-1：'?' 等非法 size 不进 int()（_sz_ok 拦）
        total = max(total, sz) if is_union else max(total, off + sz)
    return total or None


def _type_extent(t):
    """类型的**完整字节数**（含数组维度）✓

    2026-09-23（PalScript +224 漂移根因）：内联体记账原先用 `_estimate_member_size(t)`，
    它对 `float[48]` 只返回元素尺寸 4 ⇒ 记账超前 ⇒ 之后的 gap 与数组尾部**重叠**
    ⇒ pack(1) 顺序布局被撑大 ✗。这里必须乘上全部数组维度。
    """
    t = (t or '').strip()
    n = 1
    dims = re.findall(r'\[(?:0x[0-9a-fA-F]+|\d+)\]', t)
    if dims:
        t = re.sub(r'\[(?:0x[0-9a-fA-F]+|\d+)\]', '', t).strip()
        for d in dims:
            n *= int(d[1:-1], 0)
    return _estimate_member_size(t) * n


# Prefix patterns for system/library types that should never be generated
SKIP_PREFIXES = (
    'D3D', '_D3D', 'ID3D', 'IDirect', 'IUnknown',
    'CD3D',  # D3D helper classes from SDK samples
    'D3DX',  # D3DX math types
    # 'gb' removed: gbengine types have no external headers in this project;
    # generating them here prevents C2039 'not a member' errors from cpp files
    # that reference gb* struct members/methods. 2026-08-31.
    'vtbl_', # IDA vtable structs (not real C++ types)
    '_DI',   # DirectInput internal structs (defined by dinput.h)
    '_IMAGE',# PE header structs (defined by winnt.h)
    '_Crt',  # CRT debug internals
    'std',   # C++ standard library (provided by MSVC CRT)
)


# Platform types leaking from PDB/IDA TIL into the struct export table.
# Never emit headers for them: <windows.h> (via ida_types.h) and the VC6
# headers define the real layouts the original binary was built against.
SDK_PLATFORM_TYPES = {
    'CONTEXT', 'CPPEH_RECORD', 'EH3_EXCEPTION_REGISTRATION', 'FILETIME',
    'FLOATING_SAVE_AREA', 'IMAGE_DATA_DIRECTORY', 'IMAGE_FILE_HEADER',
    'IMAGE_OPTIONAL_HEADER32', 'LARGE_INTEGER', 'NMHDR', 'RGNDATAHEADER',
    'WAVEFORMAT', '_CONTEXT', '_EH3_EXCEPTION_REGISTRATION',
    '_EXCEPTION_POINTERS', '_FLOATING_SAVE_AREA', '_LARGE_INTEGER', '_PMD',
    '_RGNDATA', '_RGNDATAHEADER', '_TypeDescriptor', '_s__CatchableType',
    '_s__CatchableTypeArray', 'pcmwaveformat_tag', 'waveformat_tag',
    'wavehdr_tag',
}


def _nested_kind(cls_name, nested_name):
    """[R76 修 2026-10-22] 查嵌套类型 kind（enum/struct/union）。

    用于嵌套前向声明按 kind 分派（enum 发 enum，struct/union 发 struct）。
    数据源：data/annotations/structs/<cls>.json 的 nested_types.<name>.kind
    """
    try:
        import annotation_view as _annview
    except ImportError:
        from pipeline.gen import annotation_view as _annview
    try:
        _d = _annview.struct_by_class(cls_name) or {}
        _nt = (_d.get('nested_types') or {}).get(nested_name) or {}
        return _nt.get('kind') or 'struct'
    except Exception:
        return 'struct'


def should_skip_class(name):
    """Check if a class name should be skipped (system/library type).

    Note: :: names are NOT skipped here — they are nested types handled
    by the scope tree and filtered in the main generation loop.
    """
    if not name or len(name) <= 1:
        return True
    if name in SKIP_CLASSES:
        return True
    if name in SDK_PLATFORM_TYPES:
        # Provided by <windows.h>/VC6 headers (ida_types.h includes it).
        # Re-emitting them collides with the real definitions (C2371/C2011);
        # the SDK versions are ground truth for code MSVC6 built.
        return True
    if name.startswith(SKIP_PREFIXES):
        return True
    # 2026-09-26：IDA 侧伪类工件，非真实 C++ 类型（无任何消费方）：
    # ① `*_vtbl` 后缀 = vtable 基建批次写入 IDB 的每类 vtable 辅助结构体
    #    （成员类型带 `__hidden this` 等 IDA 伪语法，VC6 无法编译）；
    # ② `gbSingleton*` = 模板特化结构体（PDB/vtable 导入产物），
    #    生成的显式特化语法 MSVC6 报 C2913。
    if name.endswith('_vtbl'):
        return True
    if name.startswith('gbSingleton'):
        return True
    if name.startswith('_inline_'):
        return True
    return False

# Type mapping for header output (includes IDA internal type names)
TYPE_REMAP = {
    'unsigned char': 'BYTE',
    'unsigned int': 'UINT',
    'unsigned long': 'DWORD',
    'signed __int8': 'char',
    '__int8': 'char',
    'signed __int16': 'short',
    '__int16': 'short',
    'signed __int32': 'int',
    '__int32': 'int',
    '__int64': '__int64',
    'unsigned __int8': 'unsigned char',
    'unsigned __int16': 'unsigned short',
    'unsigned __int32': 'unsigned int',
    'unsigned short': 'WORD',
    '_iobuf *': 'FILE *',
    '__int128': 'unsigned char _val_16[16]',
}


def parse_signature(sig):
    """Parse IDA signature into (return_type, calling_conv, params_str, ret_right).

    For normal functions: ret_right is ''.
    For functions returning function pointers (e.g.
      "int (__thiscall *__thiscall(Class *this, int a2))(char *, int)"),
    ret_right contains the trailing parameter list of the returned fp type.
    """
    if not sig:
        return 'int', '', '', ''
    # F69（第 121 轮）：IDA/PDB 的 **thunk 渲染**会带反引号包装，例如
    #   "[thunk]:class GetCGEntry `public: static class GetCGEntry * ()"
    # 原样发射 ⇒ 生成头里出现**非法声明行**（含 `[thunk]:`、反引号 0x60、`public:`）
    # 实测代价（对发布基线）：PalScriptMgr.cpp +18、ScriptVM.cpp +6 条
    #   `C2039 'GetCGEntry' : is not a member of 'CG_Entry'`，
    # 外加同一行的解析连锁错误 C2059 syntax error '['、C2334、C2018 unknown character 0x60、
    # C2146、C2501 —— 单行合计约 30 条（这正是共享单元错误数 +21 的主要来源）。
    # 处理：取最后一个反引号之后的部分（真正的声明），再去掉访问修饰与 [thunk]: 前缀。
    if '`' in sig:
        sig = sig.rsplit('`', 1)[-1]
    sig = re.sub(r'^\s*\[thunk\]\s*:[^ ]*\s*', '', sig)
    sig = re.sub(r'^\s*(public|protected|private)\s*:\s*', '', sig)
    # Normalize IDA __hidden this marker: apply_annotations writes method types as
    # `Cls *__hidden this` (IDA's official this-argument spelling, adopted as
    # definite by Hex-Rays). Codegen consumes the equivalent `Cls *this` form.
    sig = re.sub(r'\b__hidden\s+', '', sig)
    # Normalize Hex-Rays struct-return sret param: `Cls *__return_ptr retstr`
    # (VC6 struct returns use the hidden pointer implicitly — the sret spelling
    # is an IDA type-system artifact, not a real parameter).
    if '__return_ptr' in sig:
        sig = re.sub(r'\s*,?\s*[A-Za-z_][\w:]*(?:\s*\*+)?\s*__return_ptr\s+\w+\s*,?', ' ', sig)
        sig = re.sub(r'\(\s*,', '(', sig)
        sig = re.sub(r',\s*\)', ')', sig)
        # The sret spelling means the function returns `Cls` BY VALUE:
        # Hex-Rays shows the return as `Cls *` pointing at the sret buffer.
        # Drop exactly one '*' from the return type (segment before first '(').
        p0 = sig.find('(')
        ret_seg = sig[:p0]
        j = ret_seg.rstrip().rfind('*')
        if j != -1:
            sig = sig[:j] + sig[j+1:]
    # Strip IDA __attribute__ annotations from signature
    sig = re.sub(r'\s*__attribute__\s*\(\([^()]*(?:\([^()]*\)[^()]*)*\)\)', '', sig)
    # Strip __noreturn (VC6 doesn't support it; functions are noreturn by analysis)
    # 2026-10-14 T145：原正则 `\b__noreturn\s*(?=\()` **只匹配 `__noreturn(` 形**，
    # 漏掉 `void __noreturn Cls::M()` 声明符形 ⇒ RenderTarget2.cpp:3260
    # C2143/C2182/C1004 三错（同族遮蔽）。实测 `\b__noreturn\b\s*` 后三错消失。
    sig = re.sub(r'\b__noreturn\b\s*', '', sig)

    # Detect function-pointer return type: "... *CC(params)(fp_params)"
    fp_match = re.search(r'\*\s*(__thiscall|__cdecl|__stdcall|__fastcall)\s*\(', sig)
    if fp_match:
        cc = fp_match.group(1)
        ret_left = sig[:fp_match.start()+1]  # up to and including '*'
        # Find matching ')' for the '(' at end of fp_match
        paren_start = fp_match.end() - 1
        depth = 0
        paren_end = paren_start
        for i in range(paren_start, len(sig)):
            if sig[i] == '(':
                depth += 1
            elif sig[i] == ')':
                depth -= 1
                if depth == 0:
                    paren_end = i
                    break
        params = sig[paren_start+1:paren_end]
        ret_right = sig[paren_end+1:]
        return ret_left, cc, params, ret_right

    cc_match = re.search(r'(__thiscall|__cdecl|__stdcall|__fastcall)', sig)
    paren_match = re.search(r'\(', sig)

    if cc_match and paren_match:
        cc = cc_match.group(1)
        ret = sig[:cc_match.start()].rstrip()
        if not ret:
            ret = 'int'
        params = sig[paren_match.start()+1:sig.rfind(')')]
        return ret, cc, params, ''

    if paren_match:
        ret = sig[:paren_match.start()].rstrip()
        if not ret:
            ret = 'int'
        params = sig[paren_match.start()+1:sig.rfind(')')]
        return ret, '__cdecl', params, ''

    return 'int', '', '', ''


def split_params(params_str):
    """Split comma-separated params respecting nested parens/templates."""
    result = []
    depth = 0
    current = ''
    for ch in params_str:
        if ch == ',' and depth == 0:
            result.append(current.strip())
            current = ''
        else:
            if ch in '(<':
                depth += 1
            elif ch in ')>':
                depth -= 1
            current += ch
    if current.strip():
        result.append(current.strip())
    return result


def _parse_mangled_class_qual(rest):
    """Extract qualified class name from MSVC mangled qualifier chain.
    
    'NODE@AStarPathFinder@@...' -> 'AStarPathFinder::NODE'
    'UIWnd@@...' -> 'UIWnd'
    """
    qual_end = rest.find('@@')
    if qual_end <= 0:
        return None
    class_qual = rest[:qual_end]
    classes = [c for c in class_qual.split('@') if c]
    if not classes:
        return None
    classes.reverse()  # innermost first → outermost first
    return '::'.join(classes)


def demangle_name(mangled):
    """Extract (ClassName, MethodName) from MSVC mangled name.

    Formats:
      ?Method@Class@@...               -> (Class, Method)
      ?Method@Inner@Outer@@...         -> (Outer::Inner, Method)
      ??0Class@@...                    -> (Class, Class)   [ctor]
      ??0Inner@Outer@@...              -> (Outer::Inner, Outer::Inner) [nested ctor]
      ??1Class@@...                    -> (Class, ~Class)  [dtor]
    """
    if not mangled.startswith('?'):
        return None

    inner = mangled[1:]  # strip leading ?

    # Ctor/dtor: starts with ?0 or ?1 after the leading ?
    if inner.startswith('?0') or inner.startswith('?1'):
        code = inner[1]
        rest = inner[2:]
        cls = _parse_mangled_class_qual(rest)
        if not cls:
            return None
        if any(c in cls for c in ('$', '<', '?')):
            return None
        if code == '0':
            return cls, cls.split('::')[-1]  # short name (NODE for AStarPathFinder::NODE)
        else:
            return cls, '~' + cls.split('::')[-1]

    # Regular method: Method@Class(s)@...
    at_pos = inner.find('@')
    if at_pos <= 0:
        return None
    method = inner[:at_pos]
    rest = inner[at_pos+1:]

    cls = _parse_mangled_class_qual(rest)
    if not cls:
        return None

    if not method or '$' in method or '<' in method:
        return None
    # Strip leading ? from mangled method names (e.g. ??_CEffGrid -> _CEffGrid)
    method = method.lstrip('?')
    if not method or not (method[0].isalpha() or method[0] in ('~', '_')):
        return None

    return cls, method


def collect_methods():
    """Collect all class methods from decomp JSONs."""
    classes = defaultdict(list)
    seen_addrs = set()

    # Primary source: decomp JSONs
    for f in sorted(DECOMP_DIR.glob("*.json")):
        try:
            with open(f, 'r', encoding='utf-8') as fh:
                d = json.load(fh)
        except:
            continue

        name = d.get('name', '')
        sig = d.get('signature', '')
        addr = d.get('address', '')


        cls = None
        method = None

        # Try demangling first (handles ?Method@Class@@ format)
        if name.startswith('?'):
            result = demangle_name(name)
            if result:
                cls, method = result
        # Then try ClassName::Method format
        elif '::' in name and not name.startswith('sub_'):
            if '`' not in name:
                parts = name.rsplit('::', 1)
                cls = parts[0]
                method = parts[1].split('(')[0] if '(' in parts[1] else parts[1]
                if '?' in method:
                    # Mangled name (destructor/constructor with @ chars).
                    # Demangle instead of skipping so the header gets the clean name.
                    _result = demangle_name(method if method.startswith('?') else '?' + method.lstrip('?'))
                    if _result:
                        _, method = _result

        if (not cls or not method) and addr:
            # [R91 2026-10-24·重归属战役 1b-头侧] 裸名收编：地址已路由（reattrib 门
            # 通过）⇒ 按归属类发头声明，**sig 用 decomp 形**；ida_structs 补充经下方
            # seen_addrs 让位 ⇒ 消除复核 A 实证的 ~30/59 头-体签名冲突（C2371/C2556 根）。
            try:
                from data import store as _store_r91
                _r91 = (getattr(_store_r91, 'routed_free', None) or {}).get(int(str(addr), 16))
            except (ValueError, ImportError, AttributeError):
                _r91 = None
            if _r91:
                cls, method = _r91
        if not cls or not method:
            continue
        # [T23-F1] 标量删除析构（dtor 名 + sig 含 this 外形参）⇒ _sdtor_call_dtor
        # 形（与 stage1 定义侧一致；MSVC6 拒绝 ~X(int)（C2524 实测））。保留
        # flags 形参（A 级：0x411bd8 test BYTE PTR [esp+0x8],0x1 读栈槽）。
        _is_del_dtor = False
        if method.startswith('~'):
            _sm = re.search(r'\((.*)\)\s*$', sig or '')
            _spl = [x.strip() for x in (_sm.group(1).split(',') if _sm else []) if x.strip()]
            _nonthis = [x for x in _spl if not re.search(r'\bthis\s*$', x)]
            if _nonthis:
                method = '_sdtor_call_dtor'
                _is_del_dtor = True
        # Strip _misattrib_ prefix (same as collect.py)
        if cls.startswith('_misattrib_'):
            cls = cls[len('_misattrib_'):]
        # Skip only invalid/synthetic names; class filtering (system types,
        # nested types) is handled at output time in main().
        if not cls or '$' in cls or '<' in cls or not (cls[0].isalpha() or cls[0] == '_'):
            continue
        # Skip compiler-generated _scalar_dtor functions (handled by virtual ~ClassName())
        if not _is_del_dtor and ('_scalar_dtor' in method or method.startswith('_sdtor')):
            seen_addrs.add(addr)
            continue
        if ' ' in method or '`' in method:
            continue
        # Strip __ovl_XXXX suffix for overloading, but only if sig differs
        # from existing functions with same stripped name
        ovl_stripped = re.sub(r'__ovl_[0-9a-fA-F]+$', '', method)
        if ovl_stripped != method:
            collides = False
            for existing_method, existing_sig, _ in classes.get(cls, []):
                if existing_method != ovl_stripped:
                    continue
                # Compare params only (strip return type + calling conv + func name)
                # C++ can't overload by return type alone
                def _params(s):
                    # Extract just the parameter types from a signature.
                    # Strip return type, calling convention, and 'this' parameter.
                    p = re.sub(r'^.*?__thiscall\(', '', s)  # everything before params
                    p = re.sub(r'\)\s*$', '', p).strip()    # trailing paren
                    # Strip the 'this' parameter (always first for __thiscall)
                    # Handle 'this', 'Block', namespace types (std::ios_base), and $
                    p = re.sub(r'^(?:struct\s+)?[\w$][\w$:]*(?:\s*\*+\s*)?\s*\w+\s*,?\s*', '', p)
                    p = re.sub(r'\bstruct\s+', '', p)       # struct keyword optional
                    return p.strip()
                if _params(existing_sig) == _params(sig):
                    collides = True
                    break
            if not collides:
                method = ovl_stripped
        classes[cls].append((method, sig, addr))
        seen_addrs.add(addr)

    # Supplement: add methods from ida_structs.json that lack decomp JSONs
    # (tiny helpers like PopStack whose Hex-Rays decomp is too small to export)
    _ida_s = _get_ida_structs()
    for _sname, _sinfo in _ida_s.items():
        if not _sinfo.get('methods'):
            continue
        # Filter out system/nested types (same critera as collect.py)
        # 批B 修 2026-10-06：白名单豁免（_Console 等真类型——:2813 同名单）
        if _sname.startswith('_') and _sname not in _UNDERSCORE_TYPES:
            continue
        if '<' in _sname or '$' in _sname:
            continue
        for _addr_str, _minfo in _sinfo['methods'].items():
            if _addr_str in seen_addrs:
                continue
            _method = _minfo.get('name', '')
            if '::' in _method:
                _method = _method.rsplit('::', 1)[-1]
            _sig = _minfo.get('signature', '')
            # Skip vtable-only (destructor-style) placeholders
            if not _method or '__vec_dtor' in _method:
                continue
            classes[_sname].append((_method, _sig, _addr_str))
            seen_addrs.add(_addr_str)

    # Supplement: add methods from annotation known_methods
    # (virtual methods that lack decomp JSONs, e.g. UIWnd::OnMessage)
    # NOTE: Don't check seen_addrs — annotation known_methods are manually
    # curated and may reference the same address as a different class's method
    # (e.g. UIWnd::OnMessage at 0x445D10 = CGameData::OnMessage impl).
    # P1-5（第九批）：路径枚举收敛到 _annview.iter_structs（同样"排序 + 静默跳过坏文件"）
    _ann_dir = _annview.structs_dir()
    if os.path.isdir(_ann_dir):
        for _jf, _ad in _annview.iter_structs(directory=_ann_dir):
            _ann_cls = _ad.get('name', '')
            if not _ann_cls:
                continue
            _km = _ad.get('known_methods', {})
            if not _km:
                continue
            for _slot, _minfo in _km.items():
                if not isinstance(_minfo, dict):
                    continue
                _method = _minfo.get('name', '')
                _sig = _minfo.get('signature', '')
                _addr = _minfo.get('address', '')
                if not _method or not _addr:
                    continue
                # Check if this method already exists in this class
                _existing = [m for m, _, _ in classes.get(_ann_cls, []) if m == _method]
                if _existing:
                    continue
                classes[_ann_cls].append((_method, _sig, _addr))

    return classes


def simplify_stl_type(t, cls_name=None):
    """Simplify IDA-exported full STL type to short compilable form.

    std::vector<T,std::allocator<T>> → vector<T>
    std::queue<T,std::deque<T,std::allocator<T>>> → queue<T>
    std::basic_string<char,std::char_traits<char>,std::allocator<char>> → string
    """
    # Iteratively simplify until stable
    for _ in range(5):
        prev = t
        # Remove std::allocator<...> parameter (always default)
        t = re.sub(r',\s*std::allocator<[^<>]*(?:<[^<>]*>)?[^<>]*>\s*', '', t)
        # Remove std::deque<T> second param in queue/stack (default container)
        t = re.sub(r',\s*std::deque<([^<>]+)>\s*', '', t)
        # std::basic_string<char,std::char_traits<char>> → std::string
        t = re.sub(r'std::basic_string<char,\s*std::char_traits<char>\s*>', 'std::string', t)
        t = re.sub(r'std::basic_string<char>', 'std::string', t)
        if t == prev:
            break
    # Strip std:: prefix (pal3_stl.h has 'using namespace std')
    t = t.replace('std::', '')
    # Strip own class prefix for nested types inside class body
    if cls_name:
        t = re.sub(r'\b%s::' % re.escape(cls_name), '', t)
    # [C2501 修 2026-10-19·P2] 合成名→具名顶替（渲染层置换 ✓ 闭环收口）
    t = _supersede_type_name(t)
    # Clean up extra spaces
    t = re.sub(r'\s+', ' ', t).strip()
    # Remove trailing space before >
    t = re.sub(r'\s+>', '>', t)
    return t


# STL/模板成员尺寸 —— **本工具链实测**（2026-09-22；不是猜）
# 为什么必须：`_estimate_member_size` 原先对无法识别的类型一律 `return 4` ✗
#   ⇒ `std::vector<int>`（真实 16）被当 4 ⇒ tail/gap 链错位
#   ⇒ 实测 `UIListBox` 尺寸 1220 vs 注解 1208（**+12**），而它**被 26 个类按值内嵌** ⇒ 沿 DAG 传播 ✗
# 实测命令与结果（MSVC6 SP0 + 本仓 `pal3_stl.h` shim）：
#   vector<int>=16 · string=16 · stack<int>=48 · queue<int>=48 · deque<int>=48 · list<int>=12 ·
#   map<int,int>=4096 · set<int>=4096（map/set 是 shim 的自定义实现 ⇒ 大但真实 ✓）
_STL_MEMBER_SIZES = {
    'vector': 16, 'string': 16, 'basic_string': 16,
    'list': 12, 'stack': 48, 'queue': 48, 'deque': 48,
    'map': 4096, 'set': 4096, 'multimap': 4096, 'multiset': 4096,
}


def _estimate_member_size(mtype):
    """Estimate size of a member from its type string."""
    # F68（第 120 轮）：**数组必须先于指针判断**。
    # 原实现首行是 `if '*' in mtype: return 4`，于是 `gbTexture *[16]` 被判成 4 字节
    # （只算一个指针，忽略 16 个元素）⇒ 循环的 gap 决策据此多补 60 字节。
    # 实测（编译期探针 + 生成头）：`UITextureArray` 的 `m_ptex[16]`（64 字节）后又被补了
    # `char _gap_004[60]; // +0x4`，使其 `m_num` 由注解 0x40 被推到 0x7C（+60）、
    # 类尺寸 0x80（注解 0x44）—— 这就是本会话最后追到的"尺寸错类型级联链"的**唯一根**：
    # UIListBox +96 ⇐ UIScrollBar +96 ⇐ `m_texarray`(UITextureArray) +96 ⇐ 本行。
    # 数组分支内部会 `_estimate_member_size(base)` 递归，指针基类型仍返回 4 ✓。
    arr_match = re.search(r'\[((?:0x[0-9a-fA-F]+|\d+))\](?:\[((?:0x[0-9a-fA-F]+|\d+))\])?$', mtype)
    if arr_match:
        base = mtype[:arr_match.start()].strip()
        count_str = arr_match.group(1)
        count = int(count_str, 16) if count_str.startswith('0x') else int(count_str)
        count2_str = arr_match.group(2)
        count2 = int(count2_str, 16) if count2_str and count2_str.startswith('0x') else (int(count2_str) if count2_str else 1)
        return _estimate_member_size(base) * count * count2
    # Pointer types (after arrays: `T *[N]` is an array of pointers, not a pointer)
    if '*' in mtype:
        return 4
    # Known sizes
    t = mtype.strip()
    if t in ('char', 'unsigned char', 'BYTE', '_BYTE', 'bool'):
        return 1
    if t in ('short', 'unsigned short', 'signed short', 'WORD', '_WORD', 'wchar_t'):
        return 2
    if t in ('int', 'unsigned int', 'signed int', 'long', 'unsigned long', 'DWORD',
             '_DWORD', 'UINT', 'LONG', 'BOOL', 'HRESULT', 'float', 'HWND',
             'HANDLE', 'HINSTANCE', 'HDC', 'LPVOID'):
        return 4
    if t in ('double', '__int64', 'LONGLONG', 'ULONGLONG'):
        return 8
    # Strip nested class prefix: C2DSpark::tagSpark -> tagSpark
    if '::' in t:
        t = t.rsplit('::', 1)[-1]
    # 枚举恒 4 字节（MSVC6 ABI；ida_structs 的 size=1 是 IDB 导入伪影 ✗，见 _GBENGINE_ENUMS 处注释）
    if _is_known_enum(t):
        return 4
    # Struct/class 尺寸来源必须**穷尽**，否则 gap 决策会系统性错。
    #
    # F1（2026-09-15 独立复核 `761ba967` 发现，captain 定位并修正）：
    # 本处原先**只**查 `_get_ida_structs()`（= `asm/pal3/ida_structs.json`），有两个缺口：
    #   ① 键名失配：该文件用的是 `'size'`，而这里读 `'binary_size'` ⇒ 即便命中该文件也拿不到值；
    #   ② 来源不全：**全管线没有任何地方读 `data/annotations/sdk_types.json`**
    #      ⇒ SDK 类型（如 `tagRECT`，sdk_types 里 `binary_size=16`）在此无处可查，返回 4。
    # 实证（UIWnd）：注解成员偏移 `[0,4,8,12,16,32,...]`（与 ida_structs 完全一致），
    # `m_rect` 为 `tagRECT` 且下一成员在 +32 ⇒ 它实占 16 字节；但因②被判为 4 字节，
    # 生成头里出现 `char _gap_014[12]; // +0x14` 这种**错误补齐**，后续 gap 链随之错位。
    #
    # 修复：按 `ida_structs['size']` → 注解 `binary_size` → `sdk_types['binary_size']` 依次查。
    # 仅影响 **尺寸估计**（gap/偏移决策），不改变类型发射，故风险局部化。
    try:
        ann = _get_ida_structs()
        ann_s = ann.get(t, {})
        sz = ann_s.get('size') or ann_s.get('binary_size')
        if sz and sz != '?':
            return int(sz)
    except Exception:
        pass
    try:
        sdk = _get_sdk_type_sizes()
        sz = sdk.get(t)
        if sz:
            return int(sz)
    except Exception:
        pass
    # STL/模板成员：用**实测**尺寸（见 `_STL_MEMBER_SIZES` 注释）✓
    _base = t.split('<')[0].strip().split('::')[-1].strip()
    if _base in _STL_MEMBER_SIZES:
        return _STL_MEMBER_SIZES[_base]
    # Default: assume 4 bytes (int-sized)
    return 4


def _emit_nested_struct(scope_node, nested_methods, is_data, parent_name, indent=4, ida_enums=None):
    """Recursively emit nested struct/enum definition with members + methods.
    
    Args:
        scope_node: ScopeNode whose children to emit
        nested_methods: dict of {short_name: [(method_name, sig, addr), ...]}
        is_data: ida_structs.json data dict
        parent_name: parent class name (for this param stripping)
        indent: base indentation level (4 per nesting level)
        ida_enums: _enums dict from ida_structs.json
    
    Returns:
        list of lines (str) for the nested struct/enum definition(s)
    """
    if ida_enums is None:
        _ida_enums_local = _get_ida_structs().get('_enums', {})
        ida_enums = _ida_enums_local
    lines = []
    for _child in scope_node.children:
        _nt_full = _child.full_name
        _indent = " " * indent
        
        # Check if this is an enum
        _enum_data = ida_enums.get(_nt_full, {})
        if _enum_data.get('values'):
            # Emit as enum
            lines.append("")
            lines.append("%senum %s {" % (_indent, _child.short_name))
            for _vk in sorted(_enum_data['values'].keys(),
                             key=lambda k: int(_enum_data['values'][k])):
                _vv = _enum_data['values'][_vk]
                lines.append("%s    %s = %s," % (_indent, _vk, _vv))
            lines.append("%s};" % _indent)
        else:
            # Emit as struct (original logic)
            _nt_struct = is_data.get(_nt_full, {})
            _nt_members = _nt_struct.get('data_members', [])
            _nt_methods = (nested_methods or {}).get(_child.short_name, [])
            
            lines.append("")
            lines.append("%sstruct %s {" % (_indent, _child.short_name))
            
            # Members
            if _nt_members:
                for _dm in _nt_members:
                    _t = _dm.get('type', 'int')
                    _n = _dm.get('name', '')
                    _t = re.sub(r'\b' + re.escape(parent_name) + r'::', '', _t)
                    _arr = re.search(r'(\[.*\])$', _t)
                    if _arr:
                        _t = _t[:_arr.start()].strip()
                        _n = _n + _arr.group(1)
                    lines.append("%s    %s %s;" % (_indent, _t, _n))
            elif _nt_struct.get('size'):
                _sz = _nt_struct['size']
                lines.append("%s    unsigned char _pad[%d];" % (_indent, _sz))
            
            # Methods
            if _nt_methods:
                if _nt_members or _nt_struct.get('size'):
                    lines.append("")
                _seen = set()
                for _mname, _msig, _maddr in _nt_methods:
                    _mn = _mname.split('::')[-1]
                    _ret, _cc, _params, _ret_right = parse_signature(_msig)
                    if '__thiscall' in _cc and _params:
                        _plist = split_params(_params)
                        if _plist and (re.search(r'\*(\w+\s+)?this\b', _plist[0])
                                       or _plist[0].startswith(parent_name + ' ')):
                            _plist = _plist[1:]
                        _params = ', '.join(_plist)
                    if _ret:
                        _d = "%s %s(%s)" % (_ret, _mn, _params)
                        if _ret_right:
                            _d = "%s %s(%s)%s" % (_ret, _mn, _params, _ret_right)
                    else:
                        _d = "%s(%s)" % (_mn, _params)
                    if _d not in _seen:
                        _seen.add(_d)
                        lines.append("%s    %s; // %s" % (_indent, _d, _maddr))
                lines.append("")
            
            # Recursive
            if _child.children:
                lines.extend(_emit_nested_struct(_child, nested_methods, is_data,
                                                  parent_name, indent + 4, ida_enums))
            
            lines.append("%s};" % _indent)
    
    return lines



# vptr 成员的命名（注解用 `__vftable`；IDA 导出里有的是 `_vftable`）—— 2026-09-21
_VPTR_MEMBER_NAMES = ('__vftable', '_vftable', '__vfptr', '_vfptr')


def _offset0_is_vptr_member(cls_name):
    """注解是否**已在 offset 0 计入 vptr**（即 offset0 的成员是 vptr 本身）。

    为什么需要（2026-09-21 实测，`tools/audit_type_layout.py` 的编译器裁判发现）：
      * `vtables` 存在、offset0 = `__vftable`/`_vftable` ⇒ 注入虚析构**正确**
        （`CGameData`/`RoleSystem`/`UIWnd` 等 30 个类：审计 **0 冲突** ✓）
      * `vtables` 缺失、offset0 是**数据成员**（`SceneMgr.m_pGfxMgr` / `CCBCamControl.m_CCT` /
        `CCBRoleState.m_sCombatDialog`）⇒ 注入虚析构会**引入 vptr 并覆盖该成员**，
        使**全部成员偏移 +4** ✗（审计显示 `N/N` 全成员冲突）
    实测因果：删掉 `SceneMgr` 那行注入后 `SceneMgr::Create` 字节匹配 **25.5% → 80.6%** ✓
    """
    s = _get_ida_structs().get(cls_name) or {}
    # ① 注解声明了 vtables ⇒ 布局已计入 vptr ✓
    if s.get('vtables'):
        return True
    # ② offset0 本身是 vptr 成员（`data_members` 不含 vptr，真正的 vptr 在 `_variants['0']`）
    for dm in (s.get('data_members') or []):
        if isinstance(dm, dict):
            try:
                off = int(dm.get('offset') or -1)
            except (TypeError, ValueError):
                off = -1
            if off == 0 and str(dm.get('name') or '') in _VPTR_MEMBER_NAMES:
                return True
    v = (s.get('_variants') or {}).get('0')
    if isinstance(v, dict) and str(v.get('name') or '') in _VPTR_MEMBER_NAMES:
        return True
    return False


import os as _os_annotations

def _vfptr_slot_marked(cls_name):
    """注解 offset0 成员是否带 vfptr_slot 标记（取证后的显式声明，优先级最高）✓"""
    try:
        _p = _os_annotations.path.join(
            _os_annotations.path.dirname(_os_annotations.path.dirname(
                _os_annotations.path.dirname(_os_annotations.path.dirname(
                    _os_annotations.path.abspath(__file__))))),
            'data', 'annotations', 'structs', cls_name + '.json')
        ann = json.load(open(_p, encoding='utf-8'))
        for k, v in (ann.get('known_members') or {}).items():
            if int(k, 0) == 0 and isinstance(v, dict) and v.get('vfptr_slot'):
                return True
    except Exception:
        pass
    return False


def _offset0_vptr_placeholder(cls_name):
    """offset0 成员是否恰为**标准 vptr 占位**（vptr 名 ∧ void* ∧ 无 vtable 槽）✓

    2026-09-23（CEff* 家族注入门）：只对"占位可被 F59 幻影清除机制精确移除"的类注入
    虚析构 —— 上一轮宽门把 +0 成员不是 void* 型 vptr 占位的类也注入了 ⇒ 占位数据 +
    隐式 vptr 双占 ⇒ S2 0/205 灾难 ✗（已回退）。影响面实测 52 类，全为 CEff* 家族 ✓
    """
    s = _get_ida_structs().get(cls_name) or {}
    if s.get('vtables'):
        return False
    cand = None
    for dm in (s.get('data_members') or []):
        if isinstance(dm, dict) and int(dm.get('offset') or -1) == 0:
            cand = dm
            break
    if cand is None:
        v = (s.get('_variants') or {}).get('0')
        if isinstance(v, dict):
            cand = v
    return bool(cand) and str(cand.get('name') or '') in _VPTR_MEMBER_NAMES \
        and str(cand.get('type') or '') == 'void *'


def generate_header(cls_name, ida_struct, methods, known_classes=None, enum_names=None,
                    colliding_enums=None, template_expr=None, template_param_count=0,
                    nested_types=None, nested_methods=None, scope_node=None):
    """Generate a complete header for one class.
    
    ida_struct: struct definition from ida_structs.json (export output, NOT raw PDB).
                Contains data_members, size, bases from IDB after annotation apply.
    methods:    function definitions collected from decomp JSONs.
    """
    seen_methods = set()  # populated by the method-decl loop below; also read by the scalar-wrapper ctor block
    lines = ["#pragma once"]
    lines.append('// Auto-generated: %s' % (
        template_expr if template_expr else cls_name))
    # standalone-compile base: Win32 primitives + Hex-Rays ttl aliases
    lines.append('#include "pal3/ida_types.h"')
    lines.append("")

    # Overlay annotation known_members on top of ida_struct data for naming AND
    # typing (annotations are the source of truth for usage-evidenced member
    # retypes). Default ON after the 2026-09-13 reconciliation pass (NameSys
    # bitset/UIStatic.m_text aligned to export; rich union specs guarded);
    # opt out with PAL3_HEADER_OVERLAY=0. Str type/name specs only — rich
    # dict specs (union/nested layouts) belong to apply_annotations/IDA.
    _overlaid = None
    if os.environ.get('PAL3_HEADER_OVERLAY', '1') != '0' \
            and ida_struct and ida_struct.get('data_members'):
        _overlaid = list(ida_struct['data_members'])
        try:
            _ann_json = _annview.struct_by_class(cls_name)
            _ann_km = {}
            if _ann_json:
                _ann_km = _ann_json.get('known_members', {}) or {}
            if _ann_km:
                _ann_sinfo = ida_struct
                _base_size = _ann_sinfo.get('base_size', 0) or 0
                # Annotation offsets are absolute, ida_struct offsets are relative
                # to derived start. Union variants use '<off>_<n>' keys (12, 12_1,
                # ...) — match them to same-offset export members in variant order
                # instead of int()ing the whole key ('12_1' would parse as 121).
                _ann_by_off = defaultdict(list)
                for k, v in _ann_km.items():
                    _km = re.match(r'^(\d+)(?:_(\d+))?$', str(k))
                    if not _km:
                        continue
                    _off = max(0, int(_km.group(1)) - _base_size)
                    _vi = int(_km.group(2)) if _km.group(2) else 0
                    _ann_by_off[_off].append((_vi, v))
                for _off in _ann_by_off:
                    _ann_by_off[_off].sort(key=lambda t: t[0])
                for _m in _overlaid:
                    _moff = _m.get('offset', -1)
                    _entries = _ann_by_off.get(_moff)
                    if _entries:
                        _vi, _ao = _entries.pop(0)
                        # Rich annotation specs (union dicts, nested struct
                        # lists, template idioms like std::bitset<>) belong to
                        # apply_annotations/IDA, not the simple header emitter
                        # — applying them here renders invalid C++.
                        if not isinstance(_ao, dict):
                            continue
                        if isinstance(_ao.get('type'), str):
                            _m['type'] = _ao['type']
                        if isinstance(_ao.get('name'), str) and _ao['name']:
                            _m['name'] = _ao['name']
        except Exception as _ovl_e:
            # P1-5 诊断（临时）：原先这里是 `except Exception: pass`，
            # 会把"覆盖逻辑整体失效"这类事故**静默吞掉**。改为出声以定位。
            import sys as _ovl_sys
            print('[OVERLAY-DIAG] %s: overlay block raised %s: %s'
                  % (cls_name, type(_ovl_e).__name__, _ovl_e), file=_ovl_sys.stderr)

    # Embed colliding enums (case-insensitive FS collision) before class definition
    if colliding_enums:
        for ename, edata in colliding_enums:
            values = edata.get('values', {})
            lines.append('enum %s {' % ename)
            for vname, vval in sorted(values.items(), key=lambda x: int(x[1])):
                lines.append('    %s = %s,' % (vname, vval))
            lines.append('};')
            lines.append('')

    # Analyze references: include vs forward declare
    include_types = set()  # need full definition (value members, inheritance)
    fwd_types = set()      # pointer only, forward declare suffices

    PRIMITIVES = {'int', 'char', 'float', 'double', 'unsigned', 'void', 'long',
                  'short', 'bool', 'BYTE', 'WORD', 'DWORD', 'UINT', 'HRESULT',
                  '__int64', 'unsigned char', 'unsigned int', 'unsigned long',
                  'unsigned short', 'unsigned __int64', 'wchar_t',
                  '__int8', '__int16', '__int32', 'unsigned __int8',
                  'unsigned __int16', 'unsigned __int32',
                  '_BYTE', '_WORD', '_DWORD', '_QWORD', '_UNKNOWN',
                  'CHAR', 'WCHAR', 'LONG', 'ULONG', 'INT', 'UINT',
                  'BOOL', 'SIZE_T', 'size_t', 'LPCSTR', 'LPSTR',
                  'LPCWSTR', 'LPWSTR', 'LPVOID',
                  'const', 'signed', 'unsigned __int8',
                  'struct', 'class', 'enum', 'union', 'static', 'extern',
                  'virtual', 'inline', 'register', 'volatile', 'mutable',
                  '__thiscall', '__cdecl', '__stdcall', '__fastcall'}

    # Types provided by windows.h / CRT — already available, no include/fwd needed
    # NOTE: Do NOT include gbengine types here — they need include/fwd-declare
    WINDOWS_CRT_TYPES = {
        'std', 'stdiobuf', 'exception', 'type_info', 'filebuf',
        'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG', 'RECT', 'POINT', 'SIZE',
        'HWND', 'HINSTANCE', 'HICON', 'HBRUSH', 'HDC', 'HANDLE', 'LPVOID',
        'WNDCLASSA', 'tagWNDCLASSA', 'tagOFNA', '_GUID', 'GUID', 'IID',
        '_iobuf', 'FILE', '_cpinfo', '_EXCEPTION_RECORD', 'EXCEPTION_RECORD',
        '_DIMOUSESTATE2', '_FILETIME', '_SYSTEMTIME', '_MEMORYSTATUS',
        '_SECURITY_ATTRIBUTES', '_OSVERSIONINFOA', '_STARTUPINFOA',
        '_WIN32_FIND_DATAA',
        'CRITICAL_SECTION', 'HRESULT', 'BOOL', 'LPCSTR', 'LPSTR',
        'HICON__', 'LRESULT', 'HCURSOR', 'LPARAM', 'WPARAM', 'LCID',
        'IDirectInput8A', 'IDirectInputDevice8A',
        'INT_PTR', 'UINT_PTR', 'LONG_PTR', 'ULONG_PTR', 'DWORD_PTR',
    }
    SYSTEM_TYPES = WINDOWS_CRT_TYPES

    # gbengine types — have headers in include/gbengine/, need include or fwd-declare
    # Build mapping: type_name -> header file path (relative to include/)
    GBENGINE_HEADER_DIR = PROJECT_ROOT / "include" / "gbengine"
    _gbengine_type_to_header = {}
    if GBENGINE_HEADER_DIR.exists():
        for hf in GBENGINE_HEADER_DIR.glob("*.h"):
            with open(hf, 'r', encoding='utf-8', errors='replace') as fh:
                for line in fh:
                    name = _class_decl_name(line)
                    if name:
                        header_path = "gbengine/%s" % hf.name
                        is_definition = ('{' in line or ':' in line)
                        # Prefer headers with full definitions over forward declarations
                        if name not in _gbengine_type_to_header or is_definition:
                            _gbengine_type_to_header[name] = header_path

    # Inheritance -> include (simplify template names same as in class declaration)
    try:
        _ann_base_ref = _get_ida_structs()
        _ann_base_info = _ann_base_ref.get(cls_name, {})
        # [真相源迁移 2026-10-20] 只读 `bases`（base_class 已废弃删除）
        _base_list = _base_names(_ann_base_info)
        for b in _base_list:
            bname = b.split('<')[0] if '<' in b else b
            if '::' not in bname:
                include_types.add(bname)
    except:
        pass



    # Load template map early — needed for data member analysis below
    _template_map = {}
    # 2026-09-20 审计 P1-5（第七批）：收敛到单一读点 annotation_view。
    # 语义保持：同样先 `exists` 守卫、同样**不捕获异常**（损坏时抛出）。
    if os.path.exists(_annview.template_bases_path()):
        _tpl_data = _annview.template_bases()
        for _k, _v in _tpl_data.items():
            if not _k.startswith('_'):
                _template_map[_k] = _v['template']

    # Scan annotation data_members for type references (includes/forward-decls)
    needs_stl = False
    try:
        ann_data_ref = _get_ida_structs()
        ann_struct_ref = ann_data_ref.get(cls_name, {})
        ann_variants = ann_struct_ref.get('_variants', {})
        for m in ann_struct_ref.get('data_members', []):
            mtype = m.get('type', '')
            # Restore annotation-preserved array type for include scanning
            _restored = ann_variants.get(str(m.get('offset','')), {}).get('type', '') if m.get('offset') is not None else ''
            if _restored and '[' in _restored and _restored.count('[') <= 1:
                _elem = _restored.split('[')[0].strip()
                if _elem not in PRIMITIVES and _elem not in SYSTEM_TYPES and _get_ida_structs().get(_elem, {}).get('data_members'):
                    mtype = _restored
            is_ptr = '*' in mtype
            # Detect STL template usage → need pal3_stl.h
            if '<' in mtype and ('std::' in mtype or any(
                    kw in mtype for kw in ('vector<', 'queue<', 'deque<', 'list<',
                                           'stack<', 'map<', 'string<', 'bitset<'))):
                needs_stl = True
                # Extract template argument types for include/fwd-declare
                # e.g. std::vector<ArcScene,...> → ArcScene needs include
                arg_types = re.findall(r'<\s*([A-Za-z_]\w*)', mtype)
                for at in arg_types:
                    if at == cls_name or at in PRIMITIVES or at in SYSTEM_TYPES:
                        continue
                    if at in ('std', 'char', 'float', 'int', 'unsigned'):
                        continue
                    # Template args used by value inside container → need full def
                    if at + ' *' not in mtype:
                        include_types.add(at)
                    else:
                        fwd_types.add(at)
                continue
            base = re.sub(r'\[(?:0x[0-9a-fA-F]+|\d+)\]', '', mtype).replace('*', '').strip()
            base = _resolve_ordinal_type(base)
            # [C2501 修 2026-10-19·include 面] 顶替前置：合成名→具名后再分类
            # （原按合成名分类 ⇒ 顶替后名**未入 include 面** ✗ C2501 missing
            # storage-class ×1534——值员需全定义非前向 ✓ include_types 走）
            base = _supersede_type_name(base)
            if not base or base == cls_name or base in PRIMITIVES or base in SYSTEM_TYPES:
                continue
            # 2026-09-26：嵌套限定类型（如 CParticleSystem::EmitterAttribute、
            # PlayerMgr::PoisonState）此前被直接跳过——既不 include 也不前向声明，
            # 导致 CEmitter.h/KeyFrame.h/ArcLocale.h S1 失败（C2146/C2501）。
            # 嵌套类型必须随容器完整定义（值成员需要定义，指针成员的
            # `struct Cls::Nested;` 前向声明语法也不可用）⇒ include 容器头。
            # 注意：此处不能调用 _valid_type_name（它在本函数后段才定义，
            # NameError 会被外层 except: pass 静默吞掉整个扫描）⇒ 内联校验。
            if '::' in base:
                cont = base.split('::')[0].strip()
                if (cont and cont != cls_name and cont not in PRIMITIVES
                        and cont not in SYSTEM_TYPES
                        and re.match(r'^[A-Za-z_][A-Za-z0-9_]*$', cont)
                        and '$' not in cont):
                    include_types.add(cont)
                continue
            if '<' in base:
                continue
            if base.startswith('_inline_'):
                continue
            if is_ptr:
                fwd_types.add(base)
            else:
                if base.startswith('_inline_'):
                    continue
                include_types.add(base)
        # Also scan _variants type references for include resolution
        for _v_off, _v_info in ann_variants.items():
            for _vv in _v_info.get('_variants', []):
                _vt = _vv.get('type', '')
                if _vt and _vt != 'struct' and _vt not in PRIMITIVES and _vt not in SYSTEM_TYPES and _valid_type_name(_vt):
                    include_types.add(_vt)
        # Also scan _inline_ types for member type references (for inline rendering)
        for m in ann_struct_ref.get('data_members', []):
            mtype = m.get('type', '')
            if not mtype.startswith('_inline_'):
                continue
            _inline_data = _get_ida_structs().get(mtype, {})
            for _idm in _inline_data.get('data_members', []):
                _it = _idm.get('type', '')
                if _it.startswith('$') or _it.startswith('_inline_'):
                    continue
                _base = re.sub(r'\[(?:0x[0-9a-fA-F]+|\d+)\]', '', _it).replace('*', '').strip()
                if _base and _base not in PRIMITIVES and _base not in SYSTEM_TYPES and _valid_type_name(_base):
                    include_types.add(_base)
    except:
        pass

    # Also scan method signatures for type references (all pointer/ref -> fwd_types)
    # Use annotation-overridden signatures when available, since decomp JSON signatures
    # may be stripped/simplified (e.g. "virtual void(char*)" losing original types).
    _ann_sigs_by_addr = {}
    try:
        _ann_md = _get_ida_structs()
        _ann_ms = _ann_md.get(cls_name, {}).get('methods', {})
        for _k, _v in _ann_ms.items():
            _ann_sigs_by_addr[_k] = _v.get('signature', '')
    except:
        pass

    if methods:
        for method_name, sig, addr in methods:
            # Scan BOTH signature sources: the collected (decomp) sig that the
            # renderer will actually print, and the annotation override. They
            # can diverge; scanning only one risks missing a type that the
            # other source renders (e.g. RunEffGroup's CEffSParticle param).
            # Extra forward declarations are legal C++ — a superset is safe.
            _sigs_to_scan = [sig]
            _ann_s = _ann_sigs_by_addr.get(addr, '')
            if _ann_s:
                _sigs_to_scan.append(_ann_s)
            for _scan_sig in _sigs_to_scan:
                all_types_in_sig = re.findall(r'\b([A-Za-z_][A-Za-z0-9_]*)\b\s*\*', _scan_sig)
                for t in all_types_in_sig:
                    if t == cls_name or t in PRIMITIVES or t in SYSTEM_TYPES:
                        continue
                    if '::' in t or '<' in t:
                        continue
                    fwd_types.add(t)
                # Also check return type (non-pointer custom types)
                ret_match = re.match(r'^(?:static\s+)?(\w+)\s', _scan_sig)
                if ret_match:
                    rt = ret_match.group(1)
                    if rt not in PRIMITIVES and rt not in SYSTEM_TYPES and rt != cls_name and rt != 'void':
                        fwd_types.add(rt)

    # Don't forward-declare what we're including
    fwd_types -= include_types
    # Remove system types from both sets
    include_types -= SYSTEM_TYPES
    fwd_types -= SYSTEM_TYPES
    # Remove invalid identifiers (anonymous PDB types like $S28, keywords, etc.)
    def _valid_type_name(t):
        return bool(re.match(r'^[A-Za-z_][A-Za-z0-9_]*$', t)) and '$' not in t
    include_types = {t for t in include_types if _valid_type_name(t)}
    fwd_types = {t for t in fwd_types if _valid_type_name(t)}

    # Resolve include paths: gbengine types -> "gbengine/xxx.h", pal3 gen types -> "xxx.h"
    # Types needing full definition but no header -> demote to fwd_types
    if known_classes is not None:
        resolved_includes = set()
        header_dir = OUTPUT_DIR
        for t in include_types:
            if t in _gbengine_type_to_header:
                resolved_includes.add(t)
            elif t in known_classes:
                resolved_includes.add(t)
            elif (header_dir / ('%s.h' % t)).exists():
                resolved_includes.add(t)
            elif (header_dir / get_class_dir(t) / ('%s.h' % t)).exists():
                resolved_includes.add(t)
            else:
                fwd_types.add(t)
        include_types = resolved_includes

    # gbengine types: always include full header instead of forward-declaring
    # This ensures the generated code can access gbengine struct members.
    for _t in list(fwd_types):
        if _t in _gbengine_type_to_header:
            fwd_types.discard(_t)
            include_types.add(_t)

    # Emit includes
    if needs_stl:
        lines.append('#include "pal3/pal3_stl.h"')
    for t in sorted(include_types):
        if t in _gbengine_type_to_header:
            lines.append('#include "%s"' % _gbengine_type_to_header[t])
        else:
            _sub = get_class_dir(t)
            if _sub:
                lines.append('#include "%s/%s.h"' % (_sub, t))
            else:
                lines.append('#include "%s.h"' % t)
    if include_types or needs_stl:
        lines.append("")

    # Enums can't be forward-declared in VC6 — promote to include
    if enum_names:
        enum_fwd = fwd_types & enum_names
        for t in sorted(enum_fwd):
            if t in _gbengine_type_to_header:
                lines.append('#include "%s"' % _gbengine_type_to_header[t])
            else:
                _sub = get_class_dir(t)
                if _sub:
                    lines.append('#include "%s/%s.h"' % (_sub, t))
                else:
                    lines.append('#include "%s.h"' % t)
        fwd_types -= enum_fwd

    # DirectX D3DX system types: extern SDK types, not game classes.
    # Forward-declaring them is wrong (by-value members need full
    # definitions) — include the SDK header instead.
    _D3DX_TYPES = {'D3DXVECTOR2', 'D3DXVECTOR3', 'D3DXVECTOR4', 'D3DXMATRIX',
                   'D3DXCOLOR', 'D3DXQUATERNION', 'D3DXPLANE',
                   'D3DCOLORVALUE', 'D3DCOLOR'}
    _d3dx_needed = (fwd_types | include_types) & _D3DX_TYPES
    fwd_types -= _D3DX_TYPES
    include_types -= _D3DX_TYPES
    if _d3dx_needed:
        lines.append('#include <d3dx9.h>')

    # Emit forward declarations for class types
    # [C2143 修 2026-10-19] **嵌套型排除**：类内嵌套定义（如 AStarPathFinder::NODE）
    # 不得全局前向声明——MSVC6 不允许同名 class/struct 前向声明与嵌套定义混用
    # （`class NODE;` 全局 vs `struct NODE` 嵌套 ⇒ NODE* 解析失败 C2143 · 213 文件 L7）。
    _nested_names = {n.split('::')[-1] for n in (nested_types or [])}
    fwd_types = {t for t in fwd_types if t.split('::')[-1] not in _nested_names}
    for t in sorted(fwd_types):
        lines.append("class %s;" % t)
    if fwd_types:
        lines.append("")

    # Class declaration with inheritance
    # Source 1: PDB base_classes (supports MI, with template reverse-mapping)
    # Source 2: annotations.json base_class field (fallback)
    bases_str = ""
    base_names = []

    # Load template reverse map: concrete_name → template_expression
    # (may already be populated early for data member analysis)
    try:
        template_map = _template_map
    except NameError:
        template_map = {}
        # 2026-09-20 审计 P1-5（第七批）：同上，收敛到 annotation_view（语义保持）。
        if os.path.exists(_annview.template_bases_path()):
            _tpl_data = _annview.template_bases()
            for _k, _v in _tpl_data.items():
                if not _k.startswith('_'):
                    template_map[_k] = _v['template']

    # Load annotation base_class (primary source for inheritance)
    _ann_base = None
    try:
        _ann_data = _get_ida_structs()
        _is_entry = _ann_data.get(cls_name, {})
        _ann_base = _is_entry.get('bases')
        if isinstance(_ann_base, list) and _ann_base and isinstance(_ann_base[0], dict):
            _ann_base = [b['name'] for b in _ann_base if 'name' in b]
    except:
        pass

    # Guard: IDB-side base names drift (e.g. '_BYTE[7676]' when the TIL
    # mislabels a base type). Only accept valid C++ identifiers that name a
    # known emitted class — anything else came from IDB type pollution and
    # would produce unresolvable includes.
    def _classify_base_kind(b):
        """基类名 kind 分派（纯函数，R15 单测点）——2026-10-17 codegen 结构生成修复。

        病灶：`_inline_*` 型（内联 union/struct）被误渲染为基类 `: public _inline_X`
        （_known_base_name 护不住——_inline_X.h 生成头存在 ✓ 蒙混过检）。
        kind 分派：`_inline_` 前缀 ⇒ **overlay 成员形**（`union {...} name;` 包装）
        非基类 ⇒ 其余 ⇒ base 继承形 ✓ 等价变换（同布局）。
        """
        if not b:
            return 'invalid'
        if b.startswith('_inline_'):
            return 'inline-overlay'
        return 'base'

    def _known_base_name(b):
        # Deterministic: consult the in-memory class universe (export +
        # annotations), never disk state. The old file-existence check made
        # emission depend on generation order (UIStatic sorts before UIWnd;
        # whether UIWnd.h existed on disk at that moment decided the base),
        # producing run-to-run flapping headers.
        if not b or not re.match(r'^[A-Za-z_]\w*$', b):
            return False
        if b in _get_ida_structs() or _ann_struct_path(b) is not None:
            return True
        return any((OUTPUT_DIR / d / ('%s.h' % b)).exists()
                   for d in ('', 'Misc', 'Combat', 'UI', 'Effect', 'Scene',
                             'Role', 'GameBase', 'Render', 'Data',
                             'MiniGame', 'Script'))

    if _ann_base:
        if isinstance(_ann_base, list):
            resolved = []
            for b in _ann_base:
                if _classify_base_kind(b) == 'inline-overlay':
                    continue  # [kind 分派 2026-10-17] _inline_* 走 overlay 成员形（非基类）
                if b in template_map:
                    resolved.append(template_map[b])
                elif _known_base_name(b):
                    resolved.append(b)
            base_names.extend(resolved)
        else:
            if _classify_base_kind(_ann_base) != 'inline-overlay':
                if _ann_base in template_map:
                    base_names.append(template_map[_ann_base])
                elif _known_base_name(_ann_base):
                    base_names.append(_ann_base)
                gb_path = _gbengine_type_to_header.get(_ann_base)
                if gb_path:
                    inc_line = '#include "%s"' % gb_path

    # Annotation-layer base_class fallback: annotations are the source of
    # truth — the export 'bases' field drifts (TIL mislabels like
    # '_BYTE[7676]') and loses relationships the annotations record. This
    # is emission-side inheritance only: no IDB derivatization, no
    # apply/export roundtrip, so the flattened-member shift risk of the
    # apply path does not apply here.
    try:
        _ann_json_base = None
        # P1-5（第八批）：收敛到 _annview.struct_by_class（exists 由原语内部处理）
        _cls_ann = _annview.struct_by_class(cls_name)
        if _cls_ann:
            _ann_json_base = _base_names(_cls_ann) or None
        if _ann_json_base and not base_names:
            for _b in _ann_json_base:
                if _classify_base_kind(_b) == 'inline-overlay':
                    continue  # [kind 分派 2026-10-17·第三路补] _inline_* 走 overlay 成员形
                if _b in template_map:
                    _b = template_map[_b]
                if _b in base_names:
                    continue
                _gb = _gbengine_type_to_header.get(_b)
                if _known_base_name(_b) or _gb:
                    # _known_base_name covers classes we emit ourselves;
                    # _gbengine_type_to_header covers external gbengine
                    # bases whose headers live in include/gbengine/
                    base_names.append(_b)
                    if _gb:
                        _inc = '#include "%s"' % _gb
                        if _inc not in lines:
                            lines.insert(0, _inc)
    except Exception:
        pass

    def _sanitize_template_base(name, _cls, allow_alias=True):
        if '<' not in name:
            return name
        # Reverse-lookup first: an exact template_bases.json form has a
        # concrete typedef alias whose wrapper header declares it via a
        # pre-declared callback typedef (_X_cb). Using the alias keeps the
        # base a real instantiation (decomp qualified names resolve) instead
        # of the void* form (which is a DIFFERENT type -> C2039/C2653 on
        # this->Alias::member access).
        if allow_alias:
            for _k, _v in template_map.items():
                # template_map membership implies the wrapper gets generated
                # in this same run — do NOT consult disk: 'codegen all' wipes
                # pal3/src first, so a disk check fails for every class
                # sorting before the wrapper.
                if _v == name:
                    return _k
        p = (r'[\w\s]+\s*\(\s*__thiscall\s+' + re.escape(_cls)
             + r'\s*::\s*\*\s*\)\s*\([\w\s,]*\)')
        return re.sub(p, 'void*', name)

    # Generate includes for all base classes
    for _b_i, _b_raw in enumerate(base_names):
        # normalize raw template forms to their concrete alias BEFORE use —
        # this loop runs before the dedup-stage normalization below, and the
        # alias (not the raw form) is what has a wrapper header defining it
        if '<' in _b_raw:
            base_names[_b_i] = _sanitize_template_base(_b_raw, cls_name)
    for b in base_names:
        if b in SYSTEM_TYPES:
            continue
        # Template alias bases (from template_bases.json) need their WRAPPER
        # header — it declares the _X_cb typedef + the specialization; the
        # bare primary template header does not define the alias identifier.
        if b in template_map:
            # wrapper is generated later in this same run — include by name,
            # resolving the subdir from the class-dir mapping (default Misc)
            _sub = get_class_dir(b) or 'Misc'
            _alias_inc = '#include "%s/%s.h"' % (_sub, b)
            if _alias_inc not in lines:
                lines.insert(0, _alias_inc)
        if '<' in b:
            base_inc = b.split('<')[0]
            if '$' in base_inc or ':' in base_inc:
                continue
            # Also resolve template parameter types
            inner = b[b.find('<')+1:b.rfind('>')]
            for param in re.findall(r'[A-Za-z_]\w+', inner):
                if len(param) > 1 and param not in PRIMITIVES and param not in SYSTEM_TYPES and param != cls_name:
                    gb_path = _gbengine_type_to_header.get(param, '')
                    if gb_path:
                        inc_line = '#include "%s"' % gb_path
                        if inc_line not in lines:
                            lines.insert(0, inc_line)
                    elif param in known_classes or _ann_struct_path(param):
                        _sub = get_class_dir(param)
                        if _sub:
                            inc_line = '#include "%s/%s.h"' % (_sub, param)
                        else:
                            inc_line = '#include "%s.h"' % param
                        if inc_line not in lines:
                            lines.insert(0, inc_line)
                    else:
                        fwd_line = 'class %s;' % param
                        if fwd_line not in lines:
                            lines.insert(0, fwd_line)
        else:
            base_inc = b
        if '$' in base_inc or ':' in base_inc:
            continue
        gb_path = _gbengine_type_to_header.get(base_inc, '')
        if gb_path:
            inc_line = '#include "%s"' % gb_path
        else:
            _sub = get_class_dir(base_inc)
            if _sub:
                inc_line = '#include "%s/%s.h"' % (_sub, base_inc)
            else:
                inc_line = '#include "%s.h"' % base_inc
        if inc_line not in lines:
            lines.insert(0, inc_line)

    # Sanitize template base class expressions for MSVC6 compatibility.
    # MSVC6 cannot parse member function pointer types that reference the
    # class being defined (incomplete type) when used as template arguments
    # in base class specs. Replace such self-referencing types with void*.
    # These callback types are only forwarded to forward-declared template
    # pointers (e.g. MainTask<T, Callback>*), so void* is ABI-safe.

    if base_names:
        # Normalize base_names FIRST: raw template forms reverse-map to
        # their concrete alias (wrapper header declares the _X_cb typedef).
        # Both the class declaration AND the include loop must see the
        # alias — previously only the display string was sanitized, so
        # includes pulled the bare primary template header and TUs could
        # not resolve this->Alias::member (C2653/C2039).
        _norm = []
        for b in base_names:
            if '<' in b:
                b = _sanitize_template_base(b, cls_name)
            _norm.append(b)
        base_names = _norm
        # Deduplicate base classes after sanitization (PDB + annotation
        # may list the same template instantiation under different names).
        seen = set()
        unique_bases = []
        for b in base_names:
            s = _sanitize_template_base(b, cls_name)
            if s not in seen:
                seen.add(s)
                unique_bases.append(b)
        base_names = unique_bases

        bases_str = " : " + ", ".join(
            "public %s" % _sanitize_template_base(b, cls_name) for b in base_names
        )

    # [ALIGN 修 2026-10-19] 类级 pack(1) 自动判定
    # 病灶：注解忠实于 IDA 字节级布局（实测 tagCmdDataDestRoleView：binary_size=11，
    #   成员 `_pad_7 _BYTE[7]` @0 后紧跟 `void * pDestRoleOverlay` @+7），但生成器默认
    #   按 MSVC 自然对齐发射 ⇒ 指针被推到 +8 ⇒ 实际 sizeof=12 ≠ 注解/二进制 11 ✗✗
    #   （该 struct 由 `_inline_` 合成型「去 inline 化」搬移而来，原有 pack(1) 上下文丢失）。
    # 修法：判定存在「非自然对齐成员」时，在类定义外层发 #pragma pack(push,1)/pop
    #   ⇒ 发射偏移与注解字节偏移一致（等价变换：仅恢复原打包语义，不改任何成员/偏移）。
    _need_pack = False
    try:
        _pk_ann = _annview.struct_by_class(cls_name) or {}
        # 显式声明优先（与 check_annotations 同源判据，避免两处分叉）
        _decl_pack = _pk_ann.get('pack')
        if isinstance(_decl_pack, int) and _decl_pack <= 1:
            _need_pack = True
        for _off_s, _m in (_pk_ann.get('known_members') or {}).items():
            if _need_pack:
                break
            if not str(_off_s).isdigit() or not isinstance(_m, dict):
                continue
            _o = int(_off_s)
            if _o == 0:
                continue
            _nm = str(_m.get('name') or '')
            if _nm.startswith('_pad_') or _nm.startswith('_gap_'):
                continue
            _ty = _m.get('type')
            if isinstance(_ty, dict):
                continue  # type=object：对齐由内层自带 pack 处理
            if 'overlap' in str(_m.get('source', '')).lower():
                continue
            _ts = str(_ty)
            if ('*' in _ts and _o % 4 != 0) or (
                    any(_ts.startswith(_p) for _p in
                        ('short', 'unsigned short', 'WORD', '_WORD'))
                    and _o % 2 != 0):
                _need_pack = True
                break
    except Exception:
        _need_pack = False
    _pk_open_idx = len(lines)

    # Determine keyword: union only if ANNOTATION explicitly marks is_union
    # (IDA TIL may misdetect some PDB types as union)
    _ann_is_union = False
    try:
        _ann_check = _get_ida_structs()
        _ann_is_union = _ann_check.get(cls_name, {}).get('is_union', False)
    except:
        pass
    if _ann_is_union:
        lines.append("union %s {" % cls_name)
    elif template_expr:
        # MSVC6 can't parse member function pointer types inline in template args.
        # Use a typedef + forward decl to make the argument a simple identifier.
        _td_mfp = re.search(r'__thiscall\s+(\w+)\s*::\s*\*', template_expr)
        if _td_mfp:
            _td_cls = _td_mfp.group(1)
            # Extract the full member function pointer type string
            _td_full = re.search(r'[\w\s]+\s*\(\s*__thiscall\s+\w+\s*::\s*\*\s*\)\s*\([\w\s,]*\)', template_expr)
            if _td_full:
                _td_type_raw = _td_full.group(0).strip()
                _td_name = '_{}_cb'.format(_td_cls)
                # Replace the raw form (WITH __thiscall) BEFORE stripping —
                # the stripped form no longer appears in template_expr, so
                # strip-then-replace silently misses and the class line keeps
                # the raw member-pointer (C4234 on MSVC6).
                _td_expr = template_expr.replace(_td_type_raw, _td_name)
                # MSVC6 rejects explicit __thiscall on member-pointer
                # declarators (C4234); member functions already default to
                # __thiscall so dropping it is semantics-preserving.
                _td_type = re.sub(r'\b__thiscall\s+', '', _td_type_raw)
                _td_type_named = re.sub(r'\*\)', '*%s)' % _td_name, _td_type, 1)
                lines.append('class %s;' % _td_cls)
                lines.append('typedef %s;' % _td_type_named)
                _base_tpl = template_expr.split('<')[0]
                _sub = get_class_dir(_base_tpl)
                if _sub:
                    _inc = '#include "%s/%s.h"' % (_sub, _base_tpl)
                else:
                    _inc = '#include "%s.h"' % _base_tpl
                if _inc not in lines:
                    lines.insert(0, _inc)
                # Include simple template parameter types (e.g. tagEffTaskParam)
                for _tp in re.findall(r'\w+', template_expr.split('<', 1)[1].split(',')[0]):
                    if _tp and _tp != _base_tpl and _tp not in PRIMITIVES and _tp not in SYSTEM_TYPES:
                        _sub = get_class_dir(_tp)
                        if _sub:
                            _inc2 = '#include "%s/%s.h"' % (_sub, _tp)
                        else:
                            _inc2 = '#include "%s.h"' % _tp
                        if _inc2 not in lines:
                            lines.insert(0, _inc2)
                lines.append("template<>")
                lines.append("class %s%s {" % (_sanitize_template_base(_td_expr, cls_name, allow_alias=False), bases_str))
            else:
                lines.append("template<>")
                lines.append("class %s%s {" % (_sanitize_template_base(template_expr, cls_name, allow_alias=False), bases_str))
        else:
            lines.append("template<>")
            lines.append("class %s%s {" % (_sanitize_template_base(template_expr, cls_name, allow_alias=False), bases_str))
    elif template_param_count > 0:
        _params = ', '.join('typename T%d' % (i+1) for i in range(template_param_count))
        lines.append("template<%s>" % _params)
        lines.append("class %s%s {" % (cls_name, bases_str))
    else:
        lines.append("class %s%s {" % (cls_name, bases_str))
    # [C2143 修·T56 #14 收口 2026-10-19] **类内嵌套前向**（全局排除+类内补发双满足 ✓）
    # ——C2143 禁的是**全局** class X; 与嵌套 struct X 混用 ✗；类内 `struct X;` 前向合法 ✓
    # （test_emit_nested 规格 ✓ 代码回归修复）。
    # [R76 修 2026-10-22·C2079 根因] 嵌套前向声明按 kind 分派
    # 原恒发 struct %s; => enum CDState 定义与 struct CDState 前向冲突（C2011/C2079）
    # 修：enum kind 发 enum %s;，其余发 struct %s;
    for _nt in (nested_types or []):
        _nt_name = _nt.split('::')[-1]
        _nt_kind = _nested_kind(cls_name, _nt_name) or 'struct'
        lines.append("    %s %s;" % (_nt_kind, _nt_name))
    if nested_types:
        lines.append("")
    lines.append("public:")

    # Virtual methods from vtable (must be first, order matches vtable layout)
    vtable_method_names = set()  # track names declared via vtable (including inherited)
    try:
        def _collect_base_vtable_names(class_name, visited=None):
            if visited is None:
                visited = set()
            if class_name in visited:
                return set()
            visited.add(class_name)
            names = set(re.sub(r'[^a-zA-Z0-9_]', '_', n) for n in class_vtable_slots(class_name))
            # Get base_class from ida_structs (primary) or annotation (fallback)
            _is_entry = _get_ida_structs().get(class_name, {})
            # [真相源迁移 2026-10-20] 只读 `bases`
            base = _base_names(_is_entry)
            if not base:
                try:
                    base = _base_names(_get_ida_structs().get(class_name, {}))
                except Exception:
                    pass
            if base:
                for b in base:
                    names |= _collect_base_vtable_names(b, visited)
            return names

        for bn in base_names:
            vtable_method_names |= _collect_base_vtable_names(bn)

        # Also include known_methods from annotation as vtable methods
        # P1-5（第八批）：收敛到 _annview.struct_by_class（保留本处 try 容错）
        _ann_data = _annview.struct_by_class(cls_name)
        if _ann_data:
            try:
                for _slot, _minfo in _ann_data.get('known_methods', {}).items():
                    if isinstance(_minfo, dict) and _minfo.get('name'):
                        vtable_method_names.add(_minfo['name'])
            except:
                pass

        own_slots = class_vtable_slots(cls_name)
        if own_slots and not base_names:
            lines.append("    // vtable (%d methods, order matches binary layout)" % len(own_slots))
            seen_vnames = set()
            for raw in own_slots:
                short = re.sub(r'[^a-zA-Z0-9_]', '_', raw)
                if short in seen_vnames:
                    continue
                seen_vnames.add(short)
                vtable_method_names.add(short)
            lines.append("")
    except:
        pass

    # Forward-declare nested types used as pointer members
    if scope_node and scope_node.children:
        for _child in scope_node.children:
            _nt_full = _child.full_name
            _enum_data = _get_ida_structs().get('_enums', {}).get(_nt_full, {})
            if _enum_data.get('values'):
                continue  # can't forward-declare enums in VC6
            # [C1001 修] 去重：nested_types 已生成的不再重复
            if _child.short_name in _nested_names:
                continue
            _ck = _nested_kind(cls_name, _child.short_name) or 'struct'
            lines.append("    %s %s;" % (_ck, _child.short_name))
        lines.append("")

    # Nested type definitions (before data members so types are known)
    if scope_node and scope_node.children:
        _is_data_for_nested = _get_ida_structs()
        lines.extend(_emit_nested_struct(scope_node, nested_methods,
                                          _is_data_for_nested, cls_name, indent=4))

    # Data members
    # Determine base class size to skip inherited members
    base_size = 0
    ann_data = {}
    if base_names:
        try:
            ann_data = _get_ida_structs()
            ann_struct = ann_data.get(cls_name, {})
            base_size = ann_struct.get('base_size', 0)
            # F18 修正（2026-09-19）：`base_size` 在**导出数据里恒不存在**
            # （实测 1031 个条目 **0 个**有该键）⇒ 原实现等于恒 0 ⇒ 把真实基类子对象当成
            # "只有 vptr(4 字节)"，在其上重复补 `char _gap_00X[base_size-4]`，
            # 其后每个成员实际偏移 = 注解值 + (base_size-4)。
            # 唯一可靠来源是导出里的 `bases[]`（176 个类都有）+ 各基类自身的 `size`：
            #     base_size = max(b.offset + size(b.name))
            for _b in (ann_struct.get('bases') or []):
                _bn = _b.get('name', '')
                _bo = int(_b.get('offset', 0) or 0)
                _bsz = int((ann_data.get(_bn, {}) or {}).get('size', 0) or 0)
                base_size = max(base_size, _bo + _bsz)
        except:
            pass
        # （原 F18 的注解回退块已删除：① codegen 不应读 data/annotations/；
        #   ② 其中的 `binary_size` 回退是死代码——导出里没有该键。改用上面的 `bases[]` 推导。）

    # ida_structs.json 已经是 PDB + annotation 合并后的 IDB 导出，
    # 字段名已由 apply_annotations.py 写入 IDB。codegen 不应跨阶段
    # 重新读取 annotation——idb_structs.json 就是权威数据源。
    # 仅当 IDB 没有 data_members（巨型稀疏结构体，IDA 无法创建所有成员）
    # 时，回退到 annotation known_members。
    try:
        _ann_d = _get_ida_structs()
        _ann_s = _ann_d.get(cls_name, {})
    except:
        _ann_s = {}

    # dtor 存在性（尾部 vptr 预留与虚析构注入共用；必须在 try 块之前定义 ✓）
    _has_dtor = any(m for m, _, _ in (methods or []) if m == '~' + cls_name)
    # 注入判定提前（成员循环需要用它决定 +0 成员是否走 static 槽位形式 ✓）。
    # ⚠️ 模板特化（template_expr）跳过注入：`virtual ~扁平名()` 与特化类名不匹配 ⇒ C2523 ✗
    _will_inject_vptr = (not _has_dtor) and not template_expr and (
        _vfptr_slot_marked(cls_name)
        or (_offset0_is_vptr_member(cls_name) and (
            cls_name in _get_scalar_dtor_classes()
            or _offset0_vptr_placeholder(cls_name))))
    # [R94c 2026-10-25·门拆分] _vfptr_reserved：static 占位 + 尾部预留用；
    # 与 dtor 注入正交——_has_dtor 本意管虚析构注入（防 C2535），
    # 不该连带否决占位/预留（CEffect 实证：~CEffect 短路 vfptr_slot 标记）。
    # Generate members from annotation known_members (sole source of truth)
    try:
        ann_data_fb = _get_ida_structs()
        ann_struct_fb = ann_data_fb.get(cls_name, {})
        # ★ 枚举尺寸修正（2026-09-24）：MSVC6 enum = int(4B)；ida size=1 是 IDB 导入伪影 ✗
        # （实测 EffModeParam.ePos/tagShowItem.eKind：1 字节枚举类 ⇒ 后续成员整体 −3 ✗）
        if _is_known_enum(cls_name) and ann_struct_fb.get('size') == 1:
            ann_struct_fb = dict(ann_struct_fb, size=4)
        # Convert data_members list to offset-keyed dict of lists for member iteration
        # (same-offset members = union variants)
        ann_members = {}
        if os.environ.get('PAL3_DEBUG_MERGE'):
            sys.stderr.write('DEBUG_MERGE %s ann_struct=%s ann_struct_fb=%s\n' % (
                cls_name, str(ann_struct)[:80] if ann_struct else 'None',
                str(ann_struct_fb)[:80] if ann_struct_fb else 'None'))
            sys.stderr.write('DEBUG_MERGE known_members=%s data_members=%s\n' % (
                len(ann_struct.get('known_members') or {}) if ann_struct else 0,
                len(ann_struct_fb.get('data_members') or []) if ann_struct_fb else 0))
        for _dm in ann_struct_fb.get('data_members', []):
            _off = str(_dm.get('offset', 0))
            ann_members.setdefault(_off, []).append(_dm)
        ann_size = ann_struct_fb.get('size')
        if ann_members or ann_size:
            start_off = base_size
            # P1（2026-09-19，长线计划）：**补发射 +0 的 vptr**。
            # 实测链条：注解在 `known_members['0']` 标了 `__vftable`（source=vtable_fix），
            # 但 IDB 结构的 `data_members` 里**没有** offset 0（UIWnd 从 offset 4 起）⇒ 这里只能
            # 填 `char _gap_000[4]`，而 `stage3_cleanup` 仍在 .cpp 里发射 `__vftable` 访问
            # ⇒ 80 个类的头都缺 vptr、29 个文件 150 行编译失败（C2039/C2227）。
            # 判据：该类有 vtable 槽 **且** 首个成员不在 +0（若 +0 已有真实成员则不动）。
            # 这是**加性**改动：填掉原本的 gap，类尺寸不变。
            if base_size < 8 and class_vtable_slots(cls_name) and \
                    (not ann_members or min(int(o) for o in ann_members) > 0):
                # vfptr 由编译器隐式提供（virtual 方法 ⇒ 自动 vptr@0）——不手动声明 ✗
                start_off = max(start_off, 4)
            sorted_offsets = sorted(ann_members, key=lambda x: int(x))

            def _emit_member(m, off, mname, mtype):
                # [P1 dict 分派 2026-10-19] **变体层发射**（C2039 ×54 根因 ✓）：
                # `type: {"struct": [...]}`/`{"union": [...]}` dict 形须展开为 inline
                # 结构体发射——原走字符串路（dict 当型名 ✗✗ 变体层丢 ⇒ C2039）。
                # 参考 L2362（同偏移多员 union 发射 pack(1)）+ L2422（kind 分派）。
                if isinstance(mtype, dict):
                    _vk = 'union' if 'union' in mtype else 'struct'
                    _variants = mtype.get(_vk) or []
                    if os.environ.get('PAL3_DEBUG_UNION'):
                        sys.stderr.write('DEBUG_UNION %s off=0x%X name=%s vk=%s variants=%d\n' % (
                            cls_name, off, mname, _vk, len(_variants)))
                        for _vi, _vv in enumerate(_variants):
                            sys.stderr.write('  [%d] name=%s type=%s=%s\n' % (
                                _vi, _vv.get('name') if isinstance(_vv,dict) else '?',
                                type(_vv.get('type')).__name__ if isinstance(_vv,dict) else '?',
                                str(_vv.get('type'))[:60] if isinstance(_vv,dict) else '?'))
                    _out = []
                    _out.append("    %s {" % _vk)
                    for _v in _variants:
                        _vn = _v.get('name', '')
                        _vt = _v.get('type', 'int')
                        if isinstance(_vt, dict):
                            # 嵌套（R15 例三）：递归展开
                            _nk = 'union' if 'union' in _vt else 'struct'
                            _out.append("        %s {" % _nk)
                            for _nv in _vt.get(_nk) or []:
                                _out.append("            %s %s;" % (_nv.get('type', 'int'), _nv.get('name', '')))
                            _out.append("        } %s;" % _vn)
                        else:
                            _out.append("        %s %s;" % (_vt, _vn))
                    _out.append("    } %s; // +0x%X" % (mname, off))
                    return '\n'.join(_out)
                # [C2501 修 2026-10-19·P2] 员型合成名→具名顶替（单点覆盖 ✓）
                mtype = _supersede_type_name(mtype)
                """Emit a single member line (with type remap + function pointer fix)."""
                # Remap IDA internal types to C types
                for ida_type, c_type in TYPE_REMAP.items():
                    if re.search(r'(?:^|\s)' + re.escape(ida_type) + r'(?=\s|$|\[|\*)', mtype):
                        mtype = mtype.replace(ida_type, c_type)
                # Fix C99 flexible array
                mtype = re.sub(r'\[\]', '[1]', mtype)
                # MSVC6 拒绝函数指针声明符上的显式 __thiscall（C4234）——
                # 与下方 template_expr 路径同款规则：剥掉即语义保持
                # （指针尺寸/ABI 不变，调用点自带约定）。2026-09-26：
                # tagNewItem.h/CCBEditor.h S1 失败根因。置于 arr_match 之前
                # ⇒ 数组型函数指针成员（`int (__thiscall *fn[4])(...)`）同样覆盖。
                mtype = re.sub(r'\b__thiscall\s+\*', '*', mtype)
                comment = m.get('comment', '') or m.get('description', '')
                if comment:
                    lines.append("    // %s" % comment)
                arr_match = re.search(r'(\[(?:0x[0-9a-fA-F]+|\d+)\](?:\[(?:0x[0-9a-fA-F]+|\d+)\])*)$', mtype)
                if arr_match:
                    arr_part = arr_match.group(1)
                    base_type = mtype[:arr_match.start()].rstrip()
                    lines.append("    %s %s%s; // +0x%X" % (base_type, mname, arr_part, off))
                else:
                    # Fix function pointer member syntax:
                    # "int (__thiscall *)(void)" → "int (*name)(void)"
                    _fp_match = re.search(r'\(([^)]*\*)\)\s*\(', mtype)
                    if _fp_match:
                        _inner = _fp_match.group(1)
                        _star_pos = _inner.rfind('*')
                        mtype = mtype[:_fp_match.start(1)] + _inner[:_star_pos] + '*' + mname + mtype[_fp_match.end(1):]
                        lines.append("    %s; // +0x%X" % (mtype, off))
                    else:
                        lines.append("    %s %s; // +0x%X" % (mtype, mname, off))
                return _estimate_member_size(mtype)

            # ===== 单一记账 + 补白提顶（2026-09-21，第 4 次尝试；F63/F65 均因"在分支里补"而失败）=====
            # 原状：补白逻辑在循环中部、其后还有三条 `continue` 分支 ⇒ 走分支的成员**跳过补白** ✗；
            # 且 `if off < start_off: continue` 会在**前一个成员估算尺寸偏大**时把成员**整条丢掉** ✗
            #（实测：RoleSystem 的按值 `UIWnd` 之后未补 pad ⇒ 其后全部成员 −16；SceneMgr 继承 −16 且尾部再 −24）
            # 现改为**在循环顶部统一补白**（任何分支之前）⇒ 三类分支都不再绕过 ✓
            # 并**不再跳过**任何成员（估算偏大只告警，不丢成员）✓
            _vfptr_reserved = _will_inject_vptr or (
                _vfptr_slot_marked(cls_name) and not template_expr)
            _skip_vptr_gap = False
            for off_str in sorted_offsets:
                group = ann_members[off_str]
                off = int(off_str)
                # ★ static 槽位形式（2026-09-23，CEff* 家族）：注入虚析构的类，其 +0 的
                # vptr 占位成员改为 static（不占对象字节）⇒ 编译器隐式 vptr 独占 +0，
                # 既有 `X->__vftable` 引用仍可编译（F59 同型先例 ✓）
                if _vfptr_reserved and off == 0 and len(group) == 1 and (
                        str(group[0].get('name')) in _VPTR_MEMBER_NAMES
                        or str(group[0].get('name')).startswith(('m_nTodo_', '_todo_'))
                        or _vfptr_slot_marked(cls_name)):
                    lines.append("    static %s %s; // +0x0 (vfptr slot; 布局由编译器隐式 vfptr 提供)"
                                 % (group[0].get('type', 'void *'), group[0].get('name')))
                    start_off = max(start_off, 4)
                    # [R70 P0-1 修法 2026-10-21] 承认隐式 vptr 4 字节，**跳过冗余 gap**
                    # 机理（verifier R69 wine cl 隔离 5 结构）：
                    #   static 占位=0 · 隐式 vptr=+4 · gap_001[3]=+3 ⇒ 编译前区 7 vs 声明 4
                    #   「static 排除⇒−4」方向错，膨胀主导=隐式 vptr(+4)
                    # 修法：static 占位后，跳过 off<4 的 gap 成员（隐式 vptr 已覆盖 +0..+3）
                    _skip_vptr_gap = True
                    continue
                # [R70 P0-1 修法] 跳过隐式 vptr 区的冗余 gap
                if _skip_vptr_gap and off < 4 and (
                        str(group[0].get('name', '')).startswith(('_gap_', '_pad_'))):
                    continue  # 隐式 vptr 已覆盖 +0..+3，gap 冗余
                _skip_vptr_gap = False
                if off > start_off:
                    _gap = off - start_off
                    lines.append("    char _gap_%03X[%d]; // +0x%X" % (start_off, _gap, start_off))
                    start_off = off
                elif off < start_off:
                    # 估算尺寸偏大 ⇒ 记账超前。**不丢成员**；告警留痕，交由审计工具裁决 ✓
                    sys.stderr.write('[emit] %s: member at +0x%X is behind bookkeeping '
                                     '(start_off=0x%X, +0x%X) — 不跳过，交由布局审计裁决\n'
                                     % (cls_name, off, start_off, start_off - off))
                # F65（第 113 轮）调试开关：`PAL3_EMIT_TRACE=<ClassName>` 时打印每个成员的
                # (注解偏移 off, 记账起点 start_off)，用来定位"记账与实际发射字节不一致"的成员
                # —— SceneMgr 的 `_variants` 联合（注解 +0xC67E）被发射到 +0xC664 且 gap 未补，
                # 说明某个成员的估计尺寸 > 实际发射尺寸（start_off 被提前推到 off 之上）。
                if os.environ.get('PAL3_EMIT_TRACE') == cls_name:
                    sys.stderr.write('TRACE %-16s off=0x%-5X start_off=0x%-5X %s\n' % (
                        cls_name, off, start_off,
                        (group[0].get('name') or '')[:32]))

                if len(group) > 1:
                    # Union: multiple variants at same offset
                    if off > start_off:
                        gap_size = off - start_off
                        lines.append("    char _gap_%03X[%d]; // +0x%X" % (start_off, gap_size, start_off))
                    # 2026-09-21：注解的内联 union/struct 描述的是**字节级布局**（IDA 视图），
                    # 其成员偏移可能不满足 C++ 的自然对齐（实测 SceneMgr 的 +0xC67E：
                    # `int[100]` 相对偏移 2 ⇒ 编译器把联合体推到 0xC680 并内部补白 ⇒ 其后全部 +4）。
                    # 按 1 字节打包才能复现注解的字节级偏移 ✓（外层中央补白会吸收余量）
                    lines.append("#pragma pack(push,1)")
                    lines.append("    union { // +0x%X" % off)
                    union_sizes = []
                    for m in group:
                        mname = (m.get('name') or ('' if _keep_anonymous(m)
                                                   else '_field_%04X' % off))   # 匿名 union/struct 保持匿名（内层名提升）
                        _sz = _emit_member(m, off, mname, m.get('type', 'int'))
                        _mt = str(m.get('type', 'int'))
                        if _mt.startswith('_inline_') or '::$' in _mt:
                            # 2073 顺带对齐（复核 c34f38aa）：合成类型的打包尺寸
                            _sz = _packed_inline_size(_get_ida_structs().get(_mt, {})) or _sz
                        union_sizes.append(_sz)
                    lines.append("    };")
                    lines.append("#pragma pack(pop)")
                    member_size = max(union_sizes, default=4)
                    start_off = off + member_size
                    continue

                m = group[0]
                mname = (m.get('name') or ('' if _keep_anonymous(m)
                                           else '_field_%04X' % int(off_str)))   # 匿名 union/struct 保持匿名（tagCmdData bDestRole 提升实证）
                mtype = m.get('type', 'int')
                _ann_var = _get_ida_structs().get(cls_name, {}).get('_variants', {}).get(off_str, {}).get('type', '')
                if _ann_var and '[' in _ann_var and _ann_var.count('[') <= 1:
                    _elem = _ann_var.split('[')[0].strip()
                    if _elem not in PRIMITIVES and _elem not in SYSTEM_TYPES:
                        if _get_ida_structs().get(_elem, {}).get('data_members'):
                            mtype = _ann_var
                off = int(off_str)
                # Inline UDTs: render union/struct definition inline
                if mtype.startswith('_inline_') or '::_inline_' in mtype or '::$' in mtype:
                    _inline_type_name = mtype.split('::')[0] if '::' in mtype else mtype
                    _inline_data = _get_ida_structs().get(_inline_type_name, {})
                    _inline_dms = _inline_data.get('data_members', [])
                    _inline_includes = set()
                    def _collect_includes(t, s):
                        if t and not t.startswith('$') and not t.startswith('_inline_') and '::' not in t:
                            _b = re.sub(r'\[(?:0x[0-9a-fA-F]+|\d+)\]', '', t).replace('*', '').strip()
                            if _b and _b not in PRIMITIVES and _b not in SYSTEM_TYPES and _valid_type_name(_b):
                                s.add(_b)
                        elif isinstance(t, str) and '::' in t:
                            _inner = _get_ida_structs().get(t, {})
                            for _im in _inner.get('data_members', []):
                                _collect_includes(_im.get('type', ''), s)
                    for _idm in _inline_dms:
                        _collect_includes(_idm.get('type', ''), _inline_includes)
                    if _inline_includes:
                        _insert_at = 0
                        for _i, _l in enumerate(lines):
                            if _l.startswith('#include') or _l.startswith('#pragma') or _l.strip() == '':
                                continue
                            if _l.strip().startswith('class ') or _l.strip().startswith('struct ') or _l.strip().startswith('union '):
                                _insert_at = _i
                                break
                            _insert_at = _i + 1
                        for _inc in sorted(_inline_includes):
                            _sub = get_class_dir(_inc)
                            _il = '#include "%s/%s.h"' % (_sub, _inc)
                            if _il not in lines:
                                lines.insert(_insert_at, _il)
                    if _inline_dms:
                        _kind = "union" if _inline_data.get('kind') == 'union' else "struct"
                        # F65（第 113 轮，**已回退**）：本 inline UDT 分支原先不补 gap（其余 union/struct
                        # 分支都有），实测补齐后**确实把 SceneMgr 的 −26 修掉了**（头里出现
                        # `char _gap_C664[26]; // +0xC664`），但**同时把更早的区域推多了**：
                        # offset 工具复测 deltas 由 {−22,−20,+4} 变成 **{4,20,22,24}**、sizeof 0xE55C
                        # （注解 0xE544，+24），首个漂移 `m_pCCBStageRoleFind` ann=0x2B54 → 0x2B68(+20)。
                        # ⇒ 本分支的**尺寸记账另有问题**（内联体的 `member_size`/`start_off` 推进方式），
                        # 必须与 gap 一起解决，否则按下葫芦浮起瓢。第 114 轮从这里继续。
                        lines.append("#pragma pack(push,1)")   # 同上：按字节级布局打包
                        # [F-CG#21 2026-10-15] 内联 struct 带类型名：decomp 的 cast 用
                        # 类型名 `_inline_MUIDialog_m_btRc`（ida_structs 里该成员 type 实名）
                        # ⇒ 匿名内联 struct 在 TU 里无此名 ⇒ C2059（MUIDialog.h:28 族）。
                        # 等价变换（布局不变）：`struct _inline_MUIDialog_m_btRc {…} m_btRc;`。
                        # 仅对**合法标识符**名（纯 `_inline_*` 无 `::`/`$`）加名——
                        # 合成名（`Cls::$123` 等）保持匿名（最小 churn）。
                        _tn = _inline_type_name if (
                            _inline_type_name.startswith('_inline_')
                            and '::' not in _inline_type_name
                            and '$' not in _inline_type_name) else ''
                        _blk_start = len(lines)
                        lines.append("    %s %s{ // +0x%X"
                                     % (_kind, (_tn + ' ') if _tn else '', off))
                        _inner_prev = off
                        for _idm in _inline_dms:
                            _ioff = _idm.get('offset', 0)
                            _iab = off + _ioff
                            if _iab > _inner_prev:
                                lines.append("        char _gap_%03X[%d]; // +0x%X" % (_inner_prev, _iab - _inner_prev, _inner_prev))
                            _it = _idm.get('type', 'int')
                            _in = (_idm.get('name') or ('' if _keep_anonymous(_idm)
                                                         else '_in_%03X' % (_idm.get('offset', 0))))   # 匿名变体保持匿名
                            _it_full = _it
                            if isinstance(_it, str) and ('::' in _it):
                                _inner_data = _get_ida_structs().get(_it, {})
                                _inner_dms = _inner_data.get('data_members', [])
                                if _inner_dms:
                                    _ink = "union" if _inner_data.get('kind') == 'union' else "struct"
                                    lines.append("        %s {" % _ink)
                                    _iip = _iab
                                    for _iidm in _inner_dms:
                                        _iio = _iidm.get('offset', 0)
                                        _iiab = _iab + _iio
                                        if _iiab > _iip:
                                            lines.append("            char _gap_%03X[%d];" % (_iip, _iiab - _iip))
                                        _iit = _iidm.get('type', 'int')
                                        _iin = (_iidm.get('name') or ('' if _keep_anonymous(_iidm)
                                                                      else '_iin_%03X' % (_iidm.get('offset', 0))))   # 匿名变体保持匿名
                                        _iit_full = _iit
                                        _iarr = re.search(r'^(.*?)((?:\[(?:0x[0-9a-fA-F]+|\d+)\])+)$', _iit)
                                        if _iarr:
                                            _iit = _iarr.group(1).strip()
                                            _ia = _iarr.group(2)
                                            lines.append("            %s %s%s; // +0x%X" % (_iit, _iin, _ia, _iiab))
                                        else:
                                            lines.append("            %s %s; // +0x%X" % (_iit, _iin, _iiab))
                                        _iip = _iiab + _type_extent(_iit_full)
                                    lines.append("        } %s;" % _in)
                                    _inner_prev = _iab + (_packed_inline_size(_inner_data)
                                                         or _inner_data.get('size', 4))   # W4-C0b
                                    continue
                            _arr = re.search(r'^(.*?)((?:\[(?:0x[0-9a-fA-F]+|\d+)\])+)$', _it)
                            if _arr:
                                _it = _arr.group(1).strip()
                                _ia = _arr.group(2)
                                lines.append("        %s %s%s; // +0x%X" % (_it, _in, _ia, _iab))
                            else:
                                lines.append("        %s %s; // +0x%X" % (_it, _in, _iab))
                            _inner_prev = _iab + _type_extent(_it_full)
                        lines.append("    } %s;" % mname)
                        # [CCCTData emit 命名 2026-10-16 verifier] 命名 UDT 提升到命名
                        # 空间作用域（R15 纯函数 hoist_udt_block）：decomp 局部声明在 TU
                        # 全局作用域引用 `union _inline_tagCam_yaw`，类内嵌套名解析失败
                        # （C2228×15）；布局不变等价变换（pack(1) 语义随行）。
                        if _tn:
                            _ns_lines, _mem_line = hoist_udt_block(lines[_blk_start:], mname, cls_name=cls_name)
                            # [C2501 修·P2 hoist 面] 合成名→具名顶替（ns decl+员行双置换 ✓
                            # 纯函数保持净——顶替在调用点应用）
                            if _ns_lines:
                                _ns_lines = [_supersede_type_name(_l) for _l in _ns_lines]
                                _mem_line = _supersede_type_name(_mem_line)
                            if _ns_lines:
                                del lines[_blk_start:]
                                lines.append(_mem_line)
                                # [C2011 修·P0-A] **登记不插入**：decl 入登记表（跨头共享
                                # _ns_udts.h）——原每头各插 ⇒ C2011 type redefinition ✗
                                # [P0-A 注册侧去重] 同块只注册一次（第一键持块 ✓）
                                _blk_key = tuple(_ns_lines)
                                if _blk_key not in _NS_REGISTERED_BLOCKS:
                                    _NS_REGISTERED_BLOCKS.add(_blk_key)
                                    for _dl in _ns_lines:
                                        _dm = re.match(r'^(?:class|union|struct)\s+(\w+)', _dl)
                                        if _dm and _dm.group(1) not in _NS_DECL_REGISTRY:
                                            _NS_DECL_REGISTRY[_dm.group(1)] = _ns_lines
                                # 本头改 include 共享头（decl 唯一 ✓ #pragma once 防重）
                                if '#include "pal3/gen/_ns_udts.h"' not in lines:
                                    _ins_at = 0
                                    for _j2, _l2 in enumerate(lines):
                                        if _l2.startswith('#include'):
                                            _ins_at = _j2 + 1
                                    lines.insert(_ins_at, '#include "pal3/gen/_ns_udts.h"')
                        lines.append("#pragma pack(pop)")
                        member_size = _packed_inline_size(_inline_data) \
                            or _inline_data.get('size', 4)   # W4-C0b：打包尺寸（402 非 404）
                        start_off = off + member_size
                        continue
                # Skip vfptr at +0 for classes with vtables (compiler-generated)
                if mname == 'vfptr' and off == 0 and class_vtable_slots(cls_name):
                    start_off = off + 4
                    continue
                # Insert gap padding before this member if needed
                if off > start_off:
                    gap_size = off - start_off
                    lines.append("    char _gap_%03X[%d]; // +0x%X" % (start_off, gap_size, start_off))
                # Full type restoration: annotation stores real C++ types,
                # codegen outputs them directly (no flatten for IDA limitations)
                if '<' in mtype or 'std::' in mtype:
                    simplified = simplify_stl_type(mtype, cls_name)
                    # Self-referencing nested types (e.g. queue<Common_State> inside
                    # SceneObj where Common_State = SceneObj::Common_State) need the
                    # nested type declared first. Since we don't have its layout,
                    # fall back to char[N] for these cases only.
                    original_has_self_ref = (cls_name + '::') in mtype
                    if original_has_self_ref:
                        _skeys = sorted(ann_members, key=lambda x: int(x))
                        try:
                            _idx = _skeys.index(off_str)
                        except ValueError:
                            _idx = -1
                        if _idx >= 0 and _idx + 1 < len(_skeys):
                            next_off = int(_skeys[_idx + 1])
                        else:
                            next_off = int(ann_size) if ann_size and ann_size != '?' else off + 4
                        msize = next_off - off
                        if msize > 0:
                            lines.append("    char %s[%d]; // +0x%X %s" % (mname, msize, off, simplified))
                        else:
                            lines.append("    int %s; // +0x%X %s" % (mname, off, simplified))
                        member_size = msize if msize > 0 else 4
                        start_off = off + member_size
                        continue
                    mtype = simplified
                elif '::' in mtype:
                    # Strip own class prefix for nested types
                    mtype = re.sub(r'^%s::' % re.escape(cls_name), '', mtype)
                    # After stripping, check if inner type name matches a flattened
                    # nested type (ClassName_InnerType). If the annotation stores it
                    # as SimpleName, the flattened type used for the generated header
                    # is ClassName_SimpleName.
                    _inner = mtype.strip()
                    _flat = '%s_%s' % (cls_name, _inner)
                    if (OUTPUT_DIR / ('%s.h' % _flat)).exists() or any((OUTPUT_DIR / d / ('%s.h' % _flat)).exists() for d in ('', 'Misc', 'Combat', 'UI', 'Effect', 'Scene', 'Role', 'GameBase', 'Render', 'Data', 'MiniGame', 'Script')):
                        mtype = _flat
                # Check for _variants (union with alternative views)
                # Read from ida_structs.json (passed through by export_full.py)
                _ida_variants = _get_ida_structs().get(cls_name, {}).get('_variants', {})
                _field_variants = _ida_variants.get(off_str, {}).get('_variants', [])
                if not _field_variants:
                    _field_variants = _ida_variants.get(str(off), {}).get('_variants', [])
                if not _field_variants:
                    _field_variants = _ida_variants.get('0x%X' % off, {}).get('_variants', [])
                if _field_variants:
                    # F63（第 111 轮，**未生效/已回退**）：本分支与上面的多成员 union 分支不同，
                    # 原先不补 gap。按 sibling 分支的写法补了 `if off > start_off` 的 gap，
                    # 但对 SceneMgr **没有生效**（`m_nRoleCount` 仍编到 0xE0CC，注解 0xE0E0，−20）。
                    # 进一步定位：SceneMgr.json 的 `known_members` 在 0xC660..0xC6A0 只有 `m_nTodo_C660`
                    # (0xC660)，而 +0xC67E 的联合只存在于 IDA `_variants`；且该分支发射的内部 gap 名是
                    # **十进制**（`char _gap_50814[2]` = 0xC67E），说明 offset **键格式混用（十进制/十六进制）**，
                    # 外层的 `sorted_offsets` 与 `_variants.get(off_str)` 都按**字符串**处理
                    # ⇒ 排序/查找会错位，`start_off` 记账随之漂移。正解是把所有 offset 键统一成 int
                    # （排序 + 查找都用 int），再用 offsetof 探针复核。**本轮不做**（需整段重构 + 全量回归）。
                    lines.append("    union { // +0x%X" % off)
                    _emit_member(m, off, mname, mtype)
                    for v in _field_variants:
                        ref_type = v.get('type', '')
                        if ref_type == 'struct':
                            lines.append("        struct {")
                            _inner_prev = off
                            for mem in sorted(v.get('_members', []), key=lambda x: int(x['offset'], 0)):
                                _abs = int(mem['offset'], 0)
                                if _abs > _inner_prev:
                                    lines.append("            char _gap_%03X[%d];" % (_inner_prev, _abs - _inner_prev))
                                _t = mem.get('type', 'int')
                                _n = mem.get('name', '?')
                                _t_full = _t
                                _arr = re.search(r'^(.*?)((?:\[(?:0x[0-9a-fA-F]+|\d+)\])+)$', _t)
                                if _arr:
                                    _t = _arr.group(1).strip()
                                    _a = _arr.group(2)
                                    lines.append("            %s %s%s; // +0x%X" % (_t, _n, _a, _abs))
                                else:
                                    lines.append("            %s %s; // +0x%X" % (_t, _n, _abs))
                                _inner_prev = _abs + _type_extent(_t_full)
                            lines.append("        };")
                        else:
                            lines.append("        %s __%s;" % (ref_type, ref_type))
                    lines.append("    };")
                    # Union takes max space of all variants
                    _union_sizes = [_estimate_member_size(mtype)]
                    for v in _field_variants:
                        if v.get('type') == 'struct':
                            vs = 0
                            for mem in v.get('_members', []):
                                e = int(mem['offset'], 0) + _estimate_member_size(mem.get('type','int'))
                                vs = max(vs, e - off)
                            _union_sizes.append(vs)
                        else:
                            rd = _get_ida_structs().get(v['type'], {})
                            _union_sizes.append(rd.get('size', 0))
                    member_size = max(_union_sizes)
                    start_off = off + member_size
                    continue
                member_size = _emit_member(m, off, mname, mtype)
                start_off = off + member_size
            # Tail padding to reach total size
            if ann_size and ann_size != '?' and int(ann_size) > start_off:
                # ★ vptr 预留（2026-09-23）：注入虚析构的类，编译器隐式 vptr 独占 +0
                # ⇒ 尾部从 4 起算（total−4），否则类尺寸 +4 ✗（CEff* 家族实测）
                if _vfptr_reserved:
                    start_off = max(start_off, 4)
                if template_expr and _offset0_vptr_placeholder(cls_name):
                    lines.append("    static void * __vftable; // +0x0 (vfptr slot; 引用兼容，无存储)")
                tail_size = int(ann_size) - start_off
                if tail_size > 0:
                    lines.append("    char _tail_%03X[%d]; // +0x%X" % (start_off, tail_size, start_off))
            if ann_size and ann_size != '?':
                lines.append("    // total size: 0x%X (%d)" % (int(ann_size), int(ann_size)))
            lines.append("")
    except Exception as e:
        import traceback; traceback.print_exc()

    # Auto-generate virtual destructor for classes that had _scalar_dtor
    # filtered out (compiler generates it automatically from the declaration).
    # Scan decomp JSONs to detect _scalar_dtor (same logic as data.py)
    # BUT only if the class doesn't already have an explicit destructor.
    # ⚠️ 2026-09-21：注入虚析构会**引入 vptr** ⇒ 只有注解**已计入 vptr**（offset0 是 vptr 成员）
    # 时才允许注入；否则会覆盖 offset0 的数据成员、把全部成员偏移推 +4 ✗
    # （实测：SceneMgr 删掉注入后 Create 25.5%→80.6%；审计 N/N 全成员冲突即此症）
    # 2026-09-23：拓宽 ②——offset0 恰为 void* 型 vptr 占位（无 vtable 槽）的纯载体类
    # （CEff* 家族）也注入；占位行由 F59 幻影清除机制移除，vptr 独占 +0 ✓
    # ⚠️ 模板特化类（template_expr 非空）跳过注入：注入的 `virtual ~扁平名()`
    # 与特化类名（CTaskTpl<...>）不匹配 ⇒ C2523 ×446 全库崩 ✗（2026-09-23 实测）。
    # 特化类的 36 字节按数据发射本就与二进制布局等价（其虚调用经 ret-N 槽号机制发射）✓
    if _will_inject_vptr:
        lines.append("    virtual ~%s() {}" % cls_name)
        lines.append("")

    # Methods (deduplicate by name+params to avoid C2535)
    # Pre-compute opaque type info (needed before method loop to suppress ctor decl)
    _is_opaque = False
    _ann_for_check = _get_ida_structs()
    _check_struct = _ann_for_check.get(cls_name, {})
    _check_size = _check_struct.get('binary_size') or 0
    _check_members = _check_struct.get('data_members', [])
    if _check_size and _check_size <= 16 and len(_check_members) == 0:
        _is_opaque = True
    if methods:
        # Sort: vtable methods first (in slot order by address), then non-vtable by addr
        _vtable_addr_order = {}
        # ★ 用二进制完整 vtable 替代 annotation 记录（annotation 可能不完整）
        _vt_addr = _get_vtable_addr(cls_name)
        if _vt_addr:
            _all_vtable_slots = _read_vtable_from_binary(_vt_addr)
        else:
            _all_vtable_slots = class_vtable_slots(cls_name, with_addr=True)
        for _vi, _sn in enumerate(_all_vtable_slots):
            _vtable_addr_order[int(_sn[0], 16)] = _vi

        # ★ vtable 映射完整性：确保每个 vtable 槽位都有对应的 virtual 声明。
        # 缺失的槽位（地址不在 methods 列表中）补占位条目，
        # 否则编译器 vtable 槽位数 < 二进制 vtable 槽位数 ⇒ 布局/调用不匹配 ✗
        _method_addrs = set()
        for _mn, _ms, _ma in methods:
            try:
                _method_addrs.add(int(_ma, 16) if isinstance(_ma, str) else _ma)
            except (ValueError, TypeError):
                pass
        # ★ 按唯一地址生成占位（同一函数在多个槽位出现 = MSVC 析构对/继承别名）
        _seen_slot_addrs = set()
        for _vi, _sn in enumerate(_all_vtable_slots):
            _slot_addr = int(_sn[0], 16)
            if _slot_addr in _seen_slot_addrs:
                continue  # 重复地址：同一函数的另一个槽位，不重复声明
            _seen_slot_addrs.add(_slot_addr)
            if _slot_addr not in _method_addrs:
                methods.append(
                    (f'slot_{_vi}', 'void __thiscall()', hex(_slot_addr)))
        def _method_sort_key(item):
            _addr = int(item[2], 16) if isinstance(item[2], str) else item[2]
            if _addr in _vtable_addr_order:
                return (0, _vtable_addr_order[_addr], _addr)
            return (1, 0, _addr)
        # Add undef guards for Windows API macros that conflict with method names
        _MACRO_CONFLICTS = {'CreateDialog', 'CreateWindow', 'DestroyWindow',
                            'LoadMenu', 'LoadBitmap', 'LoadImage', 'LoadCursor',
                            'PostMessage', 'SendMessage', 'DefWindowProc'}
        _conflict_undefs = []
        for _mn, _ms, _ma in methods:
            if _mn in _MACRO_CONFLICTS:
                _ul = '#ifdef %s\n#undef %s\n#endif' % (_mn, _mn)
                if _ul not in _conflict_undefs:
                    _conflict_undefs.append(_ul)
        if _conflict_undefs:
            for _ul in reversed(_conflict_undefs):
                lines.insert(1, '')
                lines.insert(1, _ul)

        seen_methods = set()
        for method_name, sig, addr in sorted(methods, key=_method_sort_key):
            # Strip Hex-Rays annotations before parsing: __userpurge/@<eax>/@<ecx>
            sig = re.sub(r'@<\w+>', '', sig)
            sig = re.sub(r'\s*__userpurge\s*', ' ', sig)
            sig = re.sub(r'\s*__usercall\s*', ' ', sig)
            # NOTE: signature comes from decomp JSON (cfunc.type.dstr()).
            # Do NOT override with annotation pass-through — that would
            # reintroduce .h/.cpp type mismatches (C2556).
            # Type corrections must go through: annotate→SetType→IDB→re-export.
            ret, cc, params, ret_right = parse_signature(sig)

            is_ctor = (method_name == cls_name)
            is_dtor = (method_name.startswith('~') or method_name == '~%s' % cls_name)
            _has_ovl = re.search(r'__ovl_[0-9a-fA-F]+$', method_name)
            is_thiscall = '__thiscall' in cc
            # Also treat as thiscall if params contain '*this' (IDA sometimes omits __thiscall)
            if not is_thiscall and '*this' in params:
                is_thiscall = True
            is_static = not is_thiscall and not is_ctor and not is_dtor

            # Strip register annotations
            # ★ vtable 槽位方法必须 virtual（2026-09-25）
            _addr_int_vt = int(addr, 16) if isinstance(addr, str) else addr
            _is_vt_method = _addr_int_vt in _vtable_addr_order
            if _is_vt_method:
                is_static = False  # vtable 方法不可能是 static

            params = re.sub(r'@<\w+>', '', params)

            # Remove this pointer from params (always first param for __thiscall)
            # Only if params actually contain 'ClassName *this' — annotation sigs now omit it.
            if is_thiscall and params:
                param_list = split_params(params)
                if param_list and (re.search(r'\*(\w+\s+)?this\b', param_list[0])
                                   or param_list[0].startswith(cls_name + ' ')):
                    param_list = param_list[1:]
                params = ', '.join(param_list)

            # Fix invalid parameter names (starting with digit or 'this' keyword)
            if params:
                from stages.stage4_substitution import rewrite_thiscall_fnptr_param
                def _fix_param(p):
                    p = p.strip()
                    # thiscall fn-ptr params → member-pointer form (VC6
                    # cannot spell the fn-ptr form; callback class is the
                    # enclosing method's class per binary evidence)
                    if '__thiscall' in p:
                        p = rewrite_thiscall_fnptr_param(p, cls_name)
                    m = re.match(r'^(.+?[\s\*])(\d\w*)$', p)
                    if m:
                        return '%s a_%s' % (m.group(1), m.group(2))
                    # 'this' is a C++ keyword — rename to '_this'
                    if re.match(r'^(.+[\s\*])this$', p):
                        return '%s_this' % p
                    return p
                param_list = split_params(params)
                param_list = [_fix_param(p) for p in param_list]
                # Deduplicate parameter names (IDA sometimes gives same name to different params)
                seen_names = {}
                for idx, p in enumerate(param_list):
                    m = re.match(r'^(.+[\s\*])(\w+)$', p.strip())
                    if m:
                        pname = m.group(2)
                        if pname in seen_names:
                            param_list[idx] = '%s%s%d' % (m.group(1), pname, idx)
                        seen_names[pname] = idx
                params = ', '.join(param_list)

            # Skip invalid method names and calling conventions
            if '`' in method_name or ' ' in method_name or '?' in method_name:
                continue
            if 'vtbl_' in ret or 'vtbl_' in params or '__vftable' in sig:
                lines.append("    // [IDA_VTABLE] %s; // %s" % (method_name, addr))
                continue
            if '__userpurge' in sig or '__usercall' in sig:
                lines.append("    // [IDA_USERPURGE] %s; // %s" % (method_name, addr))
                continue
            if '@<' in sig:
                lines.append("    // [IDA_REGPARAM] %s; // %s" % (method_name, addr))
                continue

            # VC6 supports __thiscall in function pointer type declarations.
            # Keep calling conventions intact. Only rename 'this' to '_this'.
            if sig.count('(') > 2:
                def _fix_nested_this(m):
                    return m.group(0).replace(' this', ' _this').replace('*this', '*_this')
                params = re.sub(r'\([^)]*\bthis\b[^)]*\)', _fix_nested_this, params)

            # Build declaration, wrapping method name in () when it conflicts
            # with a Windows function-like macro (e.g. CreateDialog) to prevent
            # preprocessor expansion. Wrap in a separate function for clarity.
            def _safe_method_name(name):
                _MACRO_CONFLICTS = {'CreateDialog', 'CreateWindow', 'DestroyWindow',
                                    'LoadMenu', 'LoadBitmap', 'LoadImage', 'LoadCursor',
                                    'PostMessage', 'SendMessage', 'DefWindowProc'}
                return '(%s)' % name if name in _MACRO_CONFLICTS else name
            _mn = _safe_method_name(method_name)
            if is_ctor:
                if _is_opaque:
                    continue  # opaque type generates its own ctor body
                decl = "    %s(%s);" % (cls_name, params)
            elif is_dtor:
                if _has_ovl:
                    decl = "    %s();" % method_name
                else:
                    decl = "    ~%s();" % cls_name
            elif ret_right:
                if is_static:
                    ret = re.sub(r'\bvirtual\b', '', ret).strip()
                    # IDA [thunk] 签名自带 'static'（如 GetCGEntry）——is_static 分支
                    # 已显式加 static，不剥会成 `static static`（C2159，CG_Entry.h）。
                    ret = re.sub(r'\bstatic\b\s*', '', ret).strip()
                    decl = "    static %s %s(%s)%s;" % (ret, _mn, params, ret_right)
                else:
                    if _addr_int_vt in _vtable_addr_order and not ret.startswith('virtual'):
                        decl = "    virtual %s %s(%s)%s;" % (ret, _mn, params, ret_right)
                    else:
                        decl = "    %s %s(%s)%s;" % (ret, _mn, params, ret_right)
            elif is_static:
                ret = re.sub(r'\bvirtual\b', '', ret).strip()
                ret = re.sub(r'\bstatic\b\s*', '', ret).strip()
                decl = "    static %s %s(%s);" % (ret, _mn, params)
            else:
                # ★ vtable 方法强制 virtual（编译器 vptr 分发）
                if _addr_int_vt in _vtable_addr_order and not ret.startswith('virtual'):
                    decl = "    virtual %s %s(%s);" % (ret, _mn, params)
                else:
                    decl = "    %s %s(%s);" % (ret, _mn, params)

            # Virtual override: method inherited from base vtable but this class has its own impl.
            # Don't add virtual keyword — subclasses may have different return types (C2555 risk).
            if method_name in vtable_method_names:
                pass

            # Detect duplicate declarations
            def _strip_param_names(p_str):
                parts = split_params(p_str)
                stripped = []
                for p in parts:
                    p = p.strip()
                    m2 = re.match(r'^(.+[\s\*])(\w+)$', p)
                    stripped.append(m2.group(1).strip() if m2 else p)
                return ', '.join(stripped)

            # Dtor with address suffix (e.g. ~UIWnd_ef50): compiler-generated sdtor thunk, skip
            if is_dtor and method_name != '~%s' % cls_name:
                continue

            if is_dtor:
                if _has_ovl:
                    method_key = "%s()" % method_name
                else:
                    method_key = "~%s()" % cls_name
            elif is_ctor:
                method_key = "%s(%s)" % (cls_name, _strip_param_names(params))
            else:
                method_key = "%s(%s)" % (method_name, _strip_param_names(params))
            if method_key in seen_methods:
                _header_errors.append(
                    "DUPLICATE METHOD: %s::%s (addr=%s)" % (cls_name, method_key, addr))
                continue
            seen_methods.add(method_key)

            # Fix IDA type misidentification in method declarations
            decl = decl.replace('stdiobuf *', 'UIWnd *')
            decl = decl.replace('stdiobuf', 'UIWnd')
            decl = decl.replace('std::ios_base *', 'UIWnd *')
            lines.append("%s // %s" % (decl, addr))

    # If class has parameterized ctor but no default ctor, add one
    # (skip for opaque structs which get their own ctor below)
    _ann_for_ctor = _get_ida_structs()
    _ctor_struct = _ann_for_ctor.get(cls_name, {})
    _ctor_size = _ctor_struct.get('binary_size') or 0
    _ctor_members = _ctor_struct.get('data_members', [])
    _is_opaque = (_ctor_size and _ctor_size <= 16 and len(_ctor_members) == 0)
    if methods and not _is_opaque:
        has_param_ctor = any(k.startswith(cls_name + '(') and k != cls_name + '()' for k in seen_methods)
        has_default_ctor = (cls_name + '()') in seen_methods
        if has_param_ctor and not has_default_ctor:
            # Not auto-generating a default constructor — if a class has parameterized
            # constructors only, there's a reason (e.g. gbCamera needs gbGfxManager*).
            # An empty default ctor would silently construct an invalid object.
            pass

    # For opaque scalar-wrapper structs (size <= 16, no real members —
    # _tail_* fill entries don't count), emit converting constructors.
    # Hex-Rays renders enum-like 1/2/4-byte IDA structs as classes, and its
    # output contains C-style casts like (tagEffClass)nVal which MSVC6 only
    # accepts when Cls has a Cls(int) constructor.
    # The default ctor body is EMPTY (zero codegen at /Od) — it exists only
    # because the user ctor suppresses the implicit one, which would break
    # local/array decls like `UIManager v[4];`. NO memset — that would inject
    # real initialization code at every declaration site.
    _isd_opaque = _get_ida_structs().get(cls_name, {})
    _isd_size = _isd_opaque.get('size') or 0
    if _isd_size == 1 and _is_known_enum(cls_name):
        _isd_size = 4   # MSVC6 enum = int(4B)；IDA size=1 伪影 ✗
    _isd_real_members = [m for m in (_isd_opaque.get('data_members') or [])
                         if not str(m.get('name', '')).startswith('_tail')]
    if _isd_size and _isd_size <= 16 and not _isd_real_members:
        _ctor_body = {
            1: "*(char*)this = (char)v",
            2: "*(short*)this = (short)v",
            4: "*(int*)this = v",
            8: "*(__int64*)this = (__int64)v",
        }.get(_isd_size)
        if _ctor_body:
            if (cls_name + '()') not in seen_methods:
                lines.append("    // Scalar-wrapper: ctors for IDA (Cls)int casts (no init code)")
                lines.append("    %s() {}" % cls_name)
            if (cls_name + '(int)') not in seen_methods:
                lines.append("    %s(int v) { %s; }" % (cls_name, _ctor_body))
            lines.append("")

    # Emit annotated operators (known_methods).
    # NOTE: the scalar-wrapper block above no longer emits operator int/=, so
    # no cross-block dedup flags are needed — the flags below only dedupe
    # within this loop.
    # P1-5（第八批）：收敛到 _annview.struct_by_class
    _ann_file_data = _annview.struct_by_class(cls_name)
    _has_op_int = False
    _has_op_assign = False
    _has_op_subscript = False
    if _ann_file_data:
        try:
            _ann_data = _ann_file_data
            for _slot, _minfo in _ann_data.get('known_methods', {}).items():
                if not isinstance(_minfo, dict):
                    continue
                if _minfo.get('name') == 'operator int' and not _has_op_int:
                    _first_member = None
                    for _off, _mi in _ann_data.get('known_members', {}).items():
                        if _off == '0' or _off == '0x0':
                            _first_member = _mi.get('name', 'Data')
                            break
                    if _first_member:
                        lines.append("    operator int() const { return %s; }" % _first_member)
                    else:
                        lines.append("    operator int() const { return *(int*)this; }")
                    _has_op_int = True
                elif _minfo.get('name') == 'operator=' and not _has_op_assign:
                    _first_member = None
                    for _off, _mi in _ann_data.get('known_members', {}).items():
                        if _off == '0' or _off == '0x0':
                            _first_member = _mi.get('name', 'Data')
                            break
                    if _first_member:
                        lines.append("    void operator=(int v) { %s = v; }" % _first_member)
                    else:
                        lines.append("    void operator=(int v) { *(int*)this = v; }")
                    _has_op_assign = True
                elif _minfo.get('name') == 'operator[]' and not _has_op_subscript:
                    # Find a pointer member to use as array base
                    _ptr_member = None
                    for _off, _mi in _ann_data.get('known_members', {}).items():
                        _mt = str(_mi.get('type', ''))
                        if '*' in _mt and 'char' not in _mt:
                            _ptr_member = _mi.get('name')
                            break
                    if _ptr_member:
                        lines.append("    int& operator[](int i) { return ((int*)%s)[i]; }" % _ptr_member)
                    else:
                        lines.append("    int& operator[](int i) { return ((int*)this)[i]; }")
                    _has_op_subscript = True
        except:
            pass

    lines.append("};")
    lines.append("")

    # [ALIGN 修 2026-10-19] 类级 pack(1) 收口（判定见本函数上方 _need_pack）
    if _need_pack:
        lines.insert(_pk_open_idx, '#pragma pack(push,1)')
        lines.append('#pragma pack(pop)')

    # Emit typedef for underscore-prefixed types that had a bare-name alias
    # in the original project (e.g. typedef _Texture_Info Texture_Info;).
    _aliases = _get_underscore_aliases()
    if cls_name in _aliases:
        lines.append("typedef %s %s;" % (cls_name, _aliases[cls_name]))
        lines.append("")

    # P1(a) 修正（2026-09-19，长线计划第 1 条）：**声明了 virtual 方法的类不能再有 +0 占位**。
    # MSVC 会为有虚函数的类在 +0 隐式放入 vfptr；此时再显式发射一个 4 字节占位
    # （`void * __vftable;` 或 `char _gap_000[4];`），它会被挤到 +4，**其后每个成员都偏 4 字节**。
    # 实测（独立复核）：编译 `pal3/src/Misc/AStarPathFinder.cpp` 与二进制对比，
    # `AStarPathFinder::FindInOpen` 只差 2/34 字节（`8B 49 08` vs `8B 49 04`）= 94.1%，
    # 与 registry 记录的 94.1% 完全吻合。
    # 占位当初是为了让 `.cpp` 里残留的 `X->__vftable` 能编译；但那些站点本来就产不出字节忠实的
    # 代码（真修法是按二进制槽号发射虚调用），按"字节匹配 > 编译通过"的优先级，此处以布局正确为准。
    if any('virtual ' in _l for _l in lines):
        # 2026-09-23（CEff* 家族）：占位行不再**删除**而改为 **static 化** ——
        # 删除会让 .cpp 里既有 `X->__vftable` 引用编译失败（C2039，实测 +69 ✗）；
        # static 成员不占对象字节 ⇒ 布局效果与删除相同，且引用可编译（F59 先例 ✓）
        _ph = re.compile(r'^(\s*)(void \* __vftable;|char _gap_000\[4\];)\s*// \+0x0\s*$')
        _rewritten = []
        for _l in lines:
            _m = _ph.match(_l)
            _rewritten.append(
                '%sstatic %s // +0x0 (vfptr slot; 布局由编译器隐式 vfptr 提供)' % (_m.group(1), _m.group(2))
                if _m else _l)
        lines = _rewritten

        # F59（第 108 轮）：同型错位的**另一半**——注解在 +0 标的是一个"真实成员"（不是占位符）。
        # 有虚函数 + 注解带 vtable（本函数自己会发射 `// vtable (N methods…)`）⇒ 二进制里 +0 就是
        # 编译器隐式 vfptr；若头里再声明一个 +0 数据成员，它会被挤到 +4，**其后每个成员整体偏 4**。
        # 实测（编译期 offsetof 探针）：TextureLib `m_szPathBuf` 0xC→0x10、`m_nTexWidth` 0xB8→0xBC、
        # `m_Image` 0xCC→0xD0、`sizeof` 0x214→0x218；而二进制 `TextureLib::LoadTexture` @0x4A6930
        # 首条即 `8B B1 CC 00 00 00`（lea esi,[ecx+0xcc]）⇒ 注解偏移是**绝对**的。
        # 直接删该成员会让生成代码里大量 `X->成员` 引用编译不过（实测 S2 73→72、L1 37→36），
        # 因此改为把它声明成 **static 成员**：C++ 允许 `obj->静态成员`（VC6 实测可编译），
        # 而静态成员**不占对象字节** ⇒ 编译器隐式 vfptr 独占 +0，其后成员偏移全部归位，
        # 且所有既有引用仍可编译。语义上那些站点本来就是 vfptr 访问（真修法是按槽号发射虚调用）。
        # F62（第 110 轮）：尝试把门放宽到"类声明了 virtual"（理由：只要类有虚函数，MSVC 必然在 +0
        # 插入 vfptr，与注解是否带 vtable 无关；实测 SceneMgr 的 `_scalar_dtor` @0x004CD930 里有
        # `mov dword ptr [esi], 0x56f9b4`（写 .rdata vtable）⇒ 它确实是多态类）。
        # **但实测该放宽会让成员偏移更差**：`SceneMgr::ClearInactiveRoles` 里 `m_nRoleCount` 的
        # 读偏移由 −4（0xe0cc vs 原始 0xe0e0）恶化到 **−24（0xe0c8）** ⇒ 说明 `static` 别名会打乱
        # 生成器的 `_gap_` 记账（后续 gap 填充少算/多算），必须先修 gap 记账才能真正放宽。
        # 故本轮回退到 F59 的窄门（仅"注解带 vtable"的类），F63 待做。
        if any('// vtable (' in _l for _l in lines):
            _m0 = re.compile(r'^(\s+)([A-Za-z_][\w:<>,\*&\s]*?[\w\]\*&])\s*(;\s*// \+0x0\s*)$')
            _rewritten = []
            _static_rewritten = False
            for _l in lines:
                _m = _m0.match(_l)
                if _m and not _l.lstrip().startswith('static '):
                    _l = '%sstatic %s; // +0x0 (vfptr slot; 布局由编译器隐式 vfptr 提供)' % (
                        _m.group(1), _m.group(2))
                    _static_rewritten = True
                # [R71 P0-1 修法 2026-10-22] 删冗余 gap（隐式 vptr 已覆盖 +0..+3）
                # 机理（verifier R69 wine cl 隔离 5 结构）：
                #   static 占位=0 · 隐式 vptr=+4 · gap_001[3]=+3 ⇒ 编译前区 7 vs 声明 4
                # 修法：只要类有 static vptr 行，就删 +0x1..+0x3 的 gap
                if any('vfptr slot' in _x for _x in _rewritten):
                    _gap_re = re.compile(r'^\s+char _gap_00[123]\[\d+\];\s*// \+0x[123]\s*$')
                    if _gap_re.match(_l):
                        continue  # 删冗余 gap
                _rewritten.append(_l)
            lines = _rewritten

    return '\n'.join(lines)


def main():
    # Load export data (ida_structs.json) — the ONLY legitimate source for struct info
    _is_data = _get_ida_structs()
    vtable_classes = set(name for name, sinfo in _is_data.items()
                         if sinfo.get('vtables'))
    ann_structs = set(name for name, sinfo in _is_data.items()
                      if sinfo.get('data_members') or sinfo.get('size', 0))

    # Collect methods from decomp JSONs (function bodies with class attribution)
    methods_by_class = collect_methods()

    # Load struct definitions from export output (ida_structs.json).
    # This is the legitimate data source for codegen — it's the export stage's output,
    # containing IDB type information after annotations have been applied.
    ida_classes = {}
    ida_enums = {}
    if IDA_STRUCTS_FILE.exists():
        ida_data = json.load(open(IDA_STRUCTS_FILE, encoding='utf-8'))

    # Extract enums from special _enums section
    if '_enums' in ida_data:
        ida_enums = ida_data.get('_enums', {})

        if isinstance(ida_data, dict):
            for sname, s in ida_data.items():
                if not isinstance(s, dict):
                    continue
                size = s.get('size', 0)
                if not sname:
                    continue
                # Underscore-prefixed types: most are Win32 SDK internals
                # (_D3D*, _DI*, _IMAGE*, _EXCEPTION_*, etc.) that should
                # NOT get generated headers. Project-internal types like
                # _Texture_Info and _Console DO need headers — whitelist.
                _UNDERSCORE_WHITELIST = _UNDERSCORE_TYPES   # 批B：模块级共用（去重）
                if sname.startswith('_') and sname not in _UNDERSCORE_WHITELIST:
                    continue
                if size <= 0 or size == 0xFFFFFFFFFFFFFFFF:
                    continue
                if should_skip_class(sname):
                    continue
                if '$' in sname or ':' in sname or '?' in sname or '<' in sname:
                    continue
                if not sname[0].isalpha() and sname[0] != '_':
                    continue
                ida_classes[sname] = s

    # Generate headers
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    # Build scope tree from ida_structs.json for type-to-header mapping.
    scope_tree = ScopeTree()
    scope_tree.build(_is_data if isinstance(_is_data, dict) else {},
                     SKIP_CLASSES, SKIP_PREFIXES, ida_enums=ida_enums)

    # Build all_classes from export + decomp + annotation (for complete coverage)
    all_classes = set(ida_classes.keys()) | set(methods_by_class.keys()) | vtable_classes | ann_structs
    # Filter: only non-skipped roots (skip :: names they belong in parent scope tree)
    all_classes = {c for c in all_classes
                   if '::' not in c          # nested types handled by scope tree
                   or scope_tree.find(c) is None}  # safety: not in tree? let it pass

    # Counters
    generated = 0

    def colliding_enums_for(cls_name, enum_names, enum_by_lower, embedded_enums):
        """Check for enum name collisions with this class."""
        result = []
        for ename, edata in enum_by_lower.get(cls_name.lower(), []):
            if ename in embedded_enums:
                continue
            if ename == cls_name:
                if cls_name in methods_by_class:
                    result.append((ename, edata))
            else:
                result.append((ename, edata))
                embedded_enums.add(ename)
        return result

    # Load template reverse map: concrete class -> template expression
    # Classes in this map are template instantiations whose headers should NOT
    # be generated (they use the template definition instead).
    _template_concrete = set()
    # 2026-09-20 审计 P1-5（第七批）：收敛到单一读点 annotation_view。
    # 语义保持：同样先 `exists` 守卫、同样**不捕获异常**（损坏时抛出）。
    if os.path.exists(_annview.template_bases_path()):
        _tpl_data = _annview.template_bases()
        for _k, _v in _tpl_data.items():
            if not _k.startswith('_'):
                _template_concrete.add(_k)

    # Build template_classes from ida_structs (export output, has template instantiations)
    template_classes = {}
    for sname, s in ida_classes.items():
        if '<' in sname:
            base_name = sname.split('<')[0]
            if base_name and '::' not in base_name and s.get('size', 0) > 1:
                template_classes[base_name] = s

    # Build template param count for base template names
    _tpl_param_count = {}
    for _k, _v in _tpl_data.items():
        if _k.startswith('_') or not isinstance(_v, dict):
            continue
        _t = _v.get('template', '')
        if '<' in _t:
            _base = _t.split('<')[0]
            _inner = _t[_t.find('<')+1:_t.rfind('>')]
            _depth = 0
            _count = 1
            for _c in _inner:
                if _c == '<': _depth += 1
                elif _c == '>': _depth -= 1
                elif _c == ',' and _depth == 0: _count += 1
            _tpl_param_count[_base] = _count

    # Pre-compute set of all class names that will have headers generated
    classes_with_headers = set()
    for cls_name in all_classes:
        if should_skip_class(cls_name):
            continue
        if '<' in cls_name or '::' in cls_name:
            continue
        ann_for_cls = _is_data.get(cls_name, {})
        methods_list = methods_by_class.get(cls_name, [])
        has_members = bool(ann_for_cls.get('data_members')) and bool(ann_for_cls.get('size'))
        has_methods = len(methods_list) >= 1
        ann_s = _is_data.get(cls_name, {})
        has_ann = bool(ann_s.get('data_members'))
        has_ann_sz = bool(ann_s.get('size'))
        if has_members or has_methods or has_ann or has_ann_sz:
            classes_with_headers.add(cls_name)
    # Also include template stubs and enums
    for base_name in template_classes:
        if not should_skip_class(base_name):
            classes_with_headers.add(base_name)
    enum_names = set()
    enum_by_name = {}  # name -> {values: {name: val}}
    for ename, edata in ida_enums.items():
        values = edata.get('values', {})
        if not values:
            continue
        if ename and (ename[0].isalpha() or ename[0] == '_') and '<' not in ename and '::' not in ename:
            classes_with_headers.add(ename)
            enum_names.add(ename)
            enum_by_name[ename] = {'name': ename, 'values': values}

    # Build case-insensitive enum lookup for collision detection
    enum_by_lower = {}
    for ename, edata in enum_by_name.items():
        enum_by_lower.setdefault(ename.lower(), []).append((ename, edata))

    embedded_enums = set()  # enum names already embedded in a class header

    for cls_name in sorted(all_classes):
        if should_skip_class(cls_name):
            continue
        # :: names are nested types — emitted inside parent via scope tree
        if '::' in cls_name:
            continue
        # Generate template specialization headers for concrete template instantiations
        if cls_name in _template_concrete:
            _tpl_expr = _tpl_data.get(cls_name, {}).get('template', '')
            if _tpl_expr:
                methods = methods_by_class.get(cls_name, [])
                ann_struct = _is_data.get(cls_name, {})
                has_members = bool(ann_struct.get('data_members'))
                has_vtable = bool(ann_struct.get('vtables'))
                has_size = bool(ann_struct.get('size'))
                if has_members or has_vtable or has_size:
                    content = generate_header(cls_name, ann_struct, methods,
                        classes_with_headers, enum_names, template_expr=_tpl_expr,
                        colliding_enums=colliding_enums_for(cls_name, enum_names, enum_by_lower, embedded_enums))
                    _tpl_subdir = get_class_dir(cls_name)
                    _tpl_subdir_path = OUTPUT_DIR / _tpl_subdir
                    _tpl_subdir_path.mkdir(parents=True, exist_ok=True)
                    output_path = _tpl_subdir_path / ("%s.h" % _sanitize_filename(_tpl_expr))
                    with open(output_path, 'w', encoding='utf-8') as f:
                        f.write(content)
                    generated += 1
                    _fallback = _tpl_subdir_path / ("%s.h" % _sanitize_filename(cls_name))
                    if not _fallback.exists():
                        with open(_fallback, 'w', encoding='utf-8') as f:
                            f.write('#pragma once\n')
                            f.write('#include "%s"\n' % output_path.name)
                            # Provide concrete typedef for the specialization
                            # e.g. typedef CTaskTpl<tagEffTaskParam, _CEffModel_cb> CTaskTpl_tagEffTaskParam_CEffModel;
                            _fb_mfp = re.search(r'__thiscall\s+(\w+)\s*::\s*\*', _tpl_expr)
                            if _fb_mfp:
                                _fb_cls = _fb_mfp.group(1)
                                _fb_name = '_{}_cb'.format(_fb_cls)
                                _fb_tpl_name = _tpl_expr.split('<')[0]
                                _fb_params = _tpl_expr.split('<', 1)[1].rsplit('>', 1)[0]
                                _fb_full = re.search(r'[\w\s]+\s*\(\s*__thiscall\s+\w+\s*::\s*\*\s*\)\s*\([\w\s,]*\)', _tpl_expr)
                                if _fb_full:
                                    _fb_type = _fb_full.group(0)
                                    _fb_params_san = _fb_params.replace(_fb_type, _fb_name)
                                    f.write('typedef %s<%s> %s;\n' % (_fb_tpl_name, _fb_params_san, cls_name))
                    continue
            continue
        ann_struct = _is_data.get(cls_name, {})
        methods = methods_by_class.get(cls_name, [])

        # Collect nested type methods via scope tree (recursive depth walk)
        _nested_type_methods = {}
        _root = scope_tree.find(cls_name)
        if _root:
            def _collect_deep(node):
                for _child in node.children:
                    _nt_full = _child.full_name
                    _nt_m = methods_by_class.get(_nt_full, [])
                    if _nt_m:
                        _nested_type_methods[_child.short_name] = _nt_m
                    _collect_deep(_child)  # recurse deeper
            _collect_deep(_root)

        # Skip if no useful content (but keep if has vtable or annotation members)
        has_members = bool(ann_struct.get('data_members')) and bool(ann_struct.get('size'))
        has_methods = len(methods) >= 1
        has_vtable = bool(ann_struct.get('vtables'))
        has_ann_members = bool(ann_struct.get('data_members'))
        has_ann_size = bool(ann_struct.get('size'))
        if not has_members and not has_methods and not has_vtable and not has_ann_members and not has_ann_size:
            continue

        # Skip class generation if name conflicts with an enum and class is just an enum wrapper
        if cls_name in enum_names:
            ann_size = ann_struct.get('size', 0)
            if ann_size and ann_size <= 4 and not has_ann_members:
                continue

        # Embed enums that would collide with this class header on disk:
        # - case-insensitive match (UIEMOTE vs UIEmote) — Windows FS collision
        # - exact same name but class has real content (ECBRoleSpecState)
        colliding_enums = []
        for ename, edata in enum_by_lower.get(cls_name.lower(), []):
            if ename == cls_name:
                # Same name: only embed if class has methods (otherwise let enum win)
                if has_methods:
                    colliding_enums.append((ename, edata))
                    embedded_enums.add(ename)
            else:
                # Case-insensitive collision: always embed
                colliding_enums.append((ename, edata))
                embedded_enums.add(ename)

        content = generate_header(cls_name, _is_data.get(cls_name, {}), methods, classes_with_headers, enum_names,
                                  colliding_enums=colliding_enums,
                                  nested_types=[c.short_name for c in _root.children] if _root else [],
                                  nested_methods=_nested_type_methods,
                                  scope_node=_root,
                                  template_param_count=_tpl_param_count.get(cls_name, 0))
        _subdir = get_class_dir(cls_name)
        _subdir_path = OUTPUT_DIR / _subdir
        _subdir_path.mkdir(parents=True, exist_ok=True)
        output_path = _subdir_path / ("%s.h" % _sanitize_filename(cls_name))
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(content)
        # [C2143 根治·T56 #13 修 2026-10-19] **include 垫片**（非全副本！）
        # 全副本镜像=C2011 新源（双定义 ×213 TU ×20 类 ✗✗ 我的 C2143 修引入）——
        # 垫片形：include/pal3/gen/X.h = `#include` 指向 pal3/src/ 权威件（单定义 ✓）。
        _mirror_dir = PROJECT_ROOT / 'include' / 'pal3' / 'gen'
        try:
            _mirror_dir.mkdir(parents=True, exist_ok=True)
            _mirror_path = _mirror_dir / ("%s.h" % _sanitize_filename(cls_name))
            _rel = os.path.relpath(output_path, _mirror_dir).replace(os.sep, '/')
            with open(_mirror_path, 'w', encoding='utf-8') as f:
                f.write('#pragma once\n')
                f.write('// C2143 shim: canonical = pal3/src (single-definition guard)\n')
                f.write('#include "%s"\n' % _rel)
        except Exception:
            pass  # 垫片失败不阻主产物（pal3/src/ 权威 ✓）
        generated += 1

    # Generate enum headers from ida_structs.json._enums
    enum_count = 0
    for name, edata in sorted(ida_enums.items()):
        values = edata.get('values', {})
        if not values:
            continue
        if '<' in name or '::' in name:
            continue
        # Allow _-prefixed game enums, skip system _-prefixed ones
        GAME_ENUMS_UNDERSCORE = {'_BGM', '_FLIP', '_BIGMAP_ELEMENT', '_MU_R_STATE'}
        if not name[0].isalpha() and name not in GAME_ENUMS_UNDERSCORE:
            continue
        if should_skip_class(name):
            continue

        lines = ['#pragma once', '// Auto-generated: %s enum' % name, '',
                 '#include "pal3/ida_types.h"', '']
        lines.append('enum %s {' % name)
        sorted_vals = sorted(values.items(), key=lambda x: int(x[1]))
        for vname, vval in sorted_vals:
            lines.append('    %s = %s,' % (vname, vval))
        lines.append('};')
        lines.append('')

        out_path = OUTPUT_DIR / ('%s.h' % name)
        # Skip if already embedded in a class header during class generation
        if name in embedded_enums:
            enum_count += 1
            continue
        with open(out_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))
        enum_count += 1

    # Generate template class stubs (simplified, non-template version)
    tmpl_count = 0
    for base_name, tc in sorted(template_classes.items()):
        if should_skip_class(base_name):
            continue
        # Skip if already generated as a normal class
        out_path = OUTPUT_DIR / ('%s.h' % base_name)
        if out_path.exists():
            continue

        members = tc.get('data_members', [])
        size = tc.get('size', 0)
        if not members or size <= 1:
            continue

        lines = ['#pragma once']
        lines.append('// Auto-generated: %s (template class, simplified)' % base_name)
        lines.append('#include "pal3/ida_types.h"')
        lines.append('// Original: %s' % tc.get('name', base_name))
        lines.append('// Size: 0x%X (%d bytes) from IDB' % (size, size))
        lines.append('')
        lines.append('class %s {' % base_name)
        lines.append('public:')
        for m in members:
            mname = (m.get('name') or ('' if _keep_anonymous(m)
                                       else '_unk_%04X' % m.get('offset', 0)))   # 匿名 union/struct 保持匿名
            mtype = m.get('type', 'int')
            moffset = m.get('offset', 0)
            # Simplify template types in members
            if '<' in mtype:
                mtype = 'void *'
            lines.append('    %s %s; // +0x%X' % (mtype, mname, moffset))
        lines.append('    // total size: 0x%X (%d)' % (size, size))
        lines.append('};')
        lines.append('')

        with open(out_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))
        tmpl_count += 1

    # Clean stale headers.
    # [清理判据修正 2026-10-20] 原判据「类名在 SKIP_CLASSES」只清「类被跳过」的文件，
    # 不清「已不在产出地址/已不产出」的文件 ⇒ 旧版双址镜像残留的
    # `include/pal3/*.h`（791 个同类陈旧副本）永不清理 ⇒ 三副本分叉：
    # 同一类在 `include/pal3/X.h`（旧·class）与 `pal3/src/Misc/X.h`（新·typedef）
    # 冲突，2026-10-20 实测引发 S2 121→0 的级联。
    # 正判据：**本次未产出的 .h 一律清掉**（产出地址由 codegen 全权拥有）。
    # 基础设施头（手写、非产出）须排除。
    # [保守回退 2026-10-20·当场读] 用「本次未产出」判据会误删**模板实例化头**
    #   （CTaskTpl_tagEffTaskParam__unsigned_long_… 由 tmpl 路径产出、不在 all_classes）
    #   ⇒ C1083 ×214 全线打不开头文件。判据回退为保守的 SKIP_CLASSES 形；
    #   旧地址孤儿问题已用**手动清理 include/pal3/*.h 791 个**解决。
    stale_removed = 0
    for hf in OUTPUT_DIR.rglob("*.h"):
        stem = hf.stem
        if should_skip_class(stem) and stem not in (enum_names or ()):
            hf.unlink()
            stale_removed += 1

    # [C2011 修 2026-10-19·P0-A] 共享 ns-decl 头写出（声明层唯一化收口）
    try:
        if _NS_DECL_REGISTRY:
            # [C2501/C2143 修 2026-10-19] 前向声明补齐
            # 病灶：ns-UDT 块内指针引用外部类（RoleSystem/CEffMgr…）而本头无前向声明
            #   ⇒ 全局作用域解析失败 ⇒ C2501 missing type specifiers ×214 +
            #      C2143 missing ';' before '*' ×214（全 214 TU 同点 L100）。
            # 修法：序列化块文本 → 扫描 `Type *` 引用 → 排除本文件已定义型/builtin
            #   ⇒ 头首写 `class X;`（声明层补全，不改任何布局/语义 · 等价变换 ✓）
            _written = set()
            _ordered_blocks = []
            for _k in sorted(_NS_DECL_REGISTRY):
                _block = tuple(_NS_DECL_REGISTRY[_k])
                if _block in _written:
                    continue
                _written.add(_block)
                _ordered_blocks.append(_NS_DECL_REGISTRY[_k])
            _all_lines = [x for _b in _ordered_blocks for x in _b]

            import re as _re_fwd
            _defined_here = set(_re_fwd.findall(
                r'^\s*(?:struct|union)\s+(\w+)\s*\{', '\n'.join(_all_lines), _re_fwd.M))
            _ptr_types = set(_re_fwd.findall(r'\b(\w+)\s*\*', '\n'.join(_all_lines)))
            _builtin = {
                'void', 'char', 'int', 'float', 'double', 'short', 'long',
                'unsigned', 'signed', 'bool', '_BYTE', '_WORD', '_DWORD',
                '_QWORD', '__int8', '__int16', '__int32', '__int64', 'wchar_t',
            }
            _fwd_needed = sorted(
                t for t in ((_ptr_types - _defined_here) - _builtin)
                if not should_skip_class(t))   # SDK 型来自 ida_types.h，勿再声明
            _fwd_lines = ['class %s;' % _t for _t in _fwd_needed]

            # [C2146 修 2026-10-19] 按值引用类型须**完整定义**（前向声明不够）
            # 病灶：块内 `tagTeamSlotsBOverlay combat;`（按值 union 员）而本头无其定义
            #   ⇒ C2146 missing ';' before identifier 'combat' ×218 + 后续 C2501 级联。
            # 修法：扫描 `Type name;`（无 `*`）→ 排除本文件已定义型/builtin
            #   ⇒ 头首 `#include "<sub>/<Type>.h"`（含 #pragma once 防重 ✓）。
            # [C1083 修 2026-10-23·Task4 实测] 前向声明行 `class X;` 被本扫描误读为
            #   **型名 class** ⇒ 生成 `#include "Misc/class.h"` ⇒ C1083 ×214（全 TU）。
            #   修：剔除声明关键字（class/struct/union/enum）。
            _byval_types = (set(_re_fwd.findall(
                r'^\s*([A-Za-z_]\w*)\s+[A-Za-z_]\w*\s*;', '\n'.join(_all_lines), _re_fwd.M))
                - {'class', 'struct', 'union', 'enum'})
            # SDK/系统型（tagRECT 等）定义在 ida_types.h 链上 ⇒ 无需生成头 include
            _byval_needed = sorted(
                t for t in (((_byval_types - _defined_here) - _builtin) - set(_fwd_needed))
                if not should_skip_class(t))
            _byval_inc = []
            for _t in _byval_needed:
                # [R88 修 2026-10-23·修②②] member 型去 struct/class 前缀
                # 对抗复核 54c89355：struct gbNodeMsgObj::$X 等异形产生假 include
                _t_clean = _t
                for _p in ('struct ', 'class ', 'union ', 'enum '):
                    if _t_clean.startswith(_p):
                        _t_clean = _t_clean[len(_p):]
                        break
                _sub = get_class_dir(_t_clean)
                if _sub:
                    _byval_inc.append('#include "%s/%s.h"' % (_sub, _t_clean))
                else:
                    _byval_inc.append('#include "%s.h"' % _t_clean)

            # [C2079 修 2026-10-23·Task4 实测] include↔hoist 循环序。
            # 病灶：byval include（Misc/RoleAttRemarkSkills.h）置头，而被 include 的类头
            #   自身引用**后置** hoist 块型（RoleAttRemarkSkills.skillCount →
            #   `_inline_RoleAttRemarkSkills_skillCount`）⇒ include 先于块体 ⇒
            #   C2079 'skillCount' uses undefined struct ×214（全 TU）。
            # 修法：分层发射——自含块（byval 依赖 ∉ include 集）→ byval includes → 依赖块。
            #   约束：include 目标只可依赖自含块（现语料唯一环 RoleAttRemarkSkills ✓ 实测
            #   清零）；更深环（include 目标依赖非自含块）不在本层覆盖，由 probe C2079 门禁暴露。
            def _block_byval_deps(_blk):
                return {
                    _m.group(1)
                    for _bl in _blk
                    for _m in [_re_fwd.match(r'^\s*([A-Za-z_]\w*)\s+[A-Za-z_]\w*\s*;', _bl)]
                    if _m and _m.group(1) in set(_byval_needed)}
            _leaf_blocks = [b for b in _ordered_blocks if not _block_byval_deps(b)]
            _dep_blocks = [b for b in _ordered_blocks if _block_byval_deps(b)]
            _head = ['#pragma once',
                     '// Auto-generated: shared ns-scope UDT declarations (C2011 dedup)']
            if _fwd_lines:
                _head.append('// Forward declarations for types referenced by pointer below')
                _head.extend(_fwd_lines)
            _payload = _head + [x for _b in _leaf_blocks for x in _b]
            if _byval_inc:
                _payload.append('// Full definitions required by by-value members below')
                _payload.extend(_byval_inc)
            _payload += [x for _b in _dep_blocks for x in _b]

            # 双址写出（主子 include/pal3/gen + 镜像 pal3/src，C2143 根治同法 ✓）
            for _target in (PROJECT_ROOT / 'include' / 'pal3' / 'gen' / '_ns_udts.h',
                            OUTPUT_DIR / '_ns_udts.h'):
                _target.parent.mkdir(parents=True, exist_ok=True)
                with open(_target, 'w', encoding='utf-8') as _f:
                    _f.write('\n'.join(_payload) + '\n')
            print("[C2011] ns-decls: %d unique blocks, %d byval-inc, %d fwd-decls -> _ns_udts.h"
                  % (len(_ordered_blocks), len(_byval_inc), len(_fwd_lines)))
    except Exception as _e:
        print("[C2011] ns-decl shared header write failed: %s" % _e)
    print("Generated %d header files in %s" % (generated, OUTPUT_DIR))
    print("  With annotation layout: %d" % len(all_classes))
    print("  With methods: %d" % sum(1 for c in all_classes if c in methods_by_class and methods_by_class[c]))
    print("  Enums: %d" % enum_count)
    print("  Template stubs: %d" % tmpl_count)
    if stale_removed:
        print("  Cleaned %d stale headers" % stale_removed)

    # --- Generate globals.h from annotations ---
    generate_globals()

    # 【2026-09-15 撤除】vtbl_defs.h 方案已废弃（方向错误：vtable 是编译器内部机制，
    # 不应在反编译产物里暴露）。不留生成调用，避免它重新生成残留文件。
    # 正确的方向见 data/status/_cleanup_a2_vtable_dispatch_feasibility.md：
    # 把 `vftable->Method(...)` 解析回源码级方法调用（复用 stage3 既有的
    # _decode_vtbl_call / _resolve_vtbl_method / _vtbl_stub_names）。

    # --- Generate globals.cpp from annotations ---
    generate_globals_cpp()


_DECOMP_SCAN_DIR = PROJECT_ROOT / 'asm' / 'pal3' / 'decomp'
_REFERENCED_CACHE = None
_IDA_NAME_ADDR_RE = re.compile(r'^(?:dword|byte|word|qword|off|unk|flt)_([0-9A-Fa-f]{6,8})$')


def _keep_anonymous(m):
    """匿名聚合体判定（2026-09-28 tagCmdData bDestRole 回归实证）：
    空名的 inline union/struct 成员是**故意匿名**（内层名提升到外层类作用域）——
    合成名字会切断提升。聚合体形态：type 是 dict，或 `_inline_*`/`::$` 递归引用名
    （导出把 dict 归一成字符串引用形，isinstance 判不出）。"""
    t = m.get('type')
    return isinstance(t, dict) or (isinstance(t, str) and
                                   (t.startswith('_inline_') or '::$' in t))


def _prefix_type(name):
    """Type for IDA-convention data names (used when resurrecting silenced
    globals the decompiler still references)."""
    if re.match(r'^a[A-Z]', name):
        return 'char[]'
    if name.startswith('dword_'):
        return 'int'
    if name.startswith('byte_'):
        return 'unsigned char'
    if name.startswith('word_'):
        return 'unsigned short'
    if name.startswith('qword_'):
        return '__int64'
    if name.startswith('off_'):
        return 'void *'
    if name.startswith('flt_'):
        return 'float'
    if name.startswith('unk_'):
        return 'int'
    return None


def _referenced_identifiers():
    """All identifiers appearing in decomp bodies (upstream truth of what the
    emitted sources will reference)."""
    global _REFERENCED_CACHE
    if _REFERENCED_CACHE is not None:
        return _REFERENCED_CACHE
    import glob as _glob
    tok = re.compile(r'\b[a-zA-Z_]\w*\b')
    names = set()
    for f in _glob.glob(str(_DECOMP_SCAN_DIR / '*.json')):
        try:
            d = json.loads(Path(f).read_text(encoding='utf-8', errors='replace'))
        except (json.JSONDecodeError, OSError):
            continue
        names.update(tok.findall(d.get('decompiled_c', '')))
    _REFERENCED_CACHE = names
    return names


def _interior_member_resolvable(addr, name=None):
    """stage4 会把该名字改写成容器成员路径吗？（= 外部可退役判据）

    v2 修正：不再自判 offset 命中（那比 stage4 的真实解析弱——byte 前缀 ×
    int 成员等前缀语义不匹配时 stage4 返回 None，退役过冲产生 C2065），
    直接调用 stage4 自己的解析器。解析成功 ⇒ 改写后裸名不再被引用 ⇒ 可退役。
    """
    # 与同文件 stage4 引用（:2419）同款导入路径——双路径 import 会创建
    # 第二个模块实例（store 空载）⇒ 解析恒 None ⇒ 退役全停摆
    from stages.stage4_substitution import _try_struct_member_resolution
    # name 提供 prefix 语义（byte_/dword_/…）；仅有地址时按 dword_ 保守尝试
    prefix_name = name or ('dword_%X' % addr)
    return _try_struct_member_resolution(prefix_name) is not None


_ANN_GLOBAL_TYPE_CACHE = None


def _ann_global_type_map(data):
    """[F-TAB 2026-10-15] globals.json → {addr: 复活型}（纯函数，R15 单测点）。

    规则（W3 类型源律的合成路径扩展）：`orig_type`（墓碑原类型）优先，
    其次非 skip 的 `type`；skip 无 orig_type ⇒ 不入表（回退名字启发）。
    """
    out = {}
    for _a, _e in (data or {}).items():
        if not isinstance(_e, dict):
            continue
        _t = _e.get('orig_type') or _e.get('type')
        if _t and _t != 'skip':
            try:
                out[int(_a, 16)] = _t
            except (ValueError, TypeError):
                pass
    return out


def _ann_global_type(addr):
    """globals.json 显式型（复活型解析源 · W3 类型源律扩展）。

    合成路径（_forced_global_entries）此前对 IDA 式名字一律 `_prefix_type`
    ⇒ `off_*`→**void\\* 标量**，吞掉注解里的数组形（实测 off_5AC098 标量
    `extern void *` 与就地 `extern void *off_5AC098[]` 相撞 C2372 + 下标
    C2036/C2664 共 3 错）。查不到 ⇒ None（调用方回退 _prefix_type）。
    """
    global _ANN_GLOBAL_TYPE_CACHE
    if _ANN_GLOBAL_TYPE_CACHE is None:
        try:
            _p = _annview.annotation_json_path('globals.json')
            _data = json.loads(open(_p, encoding='utf-8').read()) if os.path.exists(_p) else {}
        except Exception:
            _data = {}
        _ANN_GLOBAL_TYPE_CACHE = _ann_global_type_map(_data)
    return _ANN_GLOBAL_TYPE_CACHE.get(addr)


def _forced_global_entries():
    """Decomp-referenced globals that current skip filters would silence.

    Policy: skip governs *renaming* and annotation semantics, not
    *silencing* — if Hex-Rays emitted a name into a function body, the
    generated TU references it and needs an extern + definition (observed
    C2065 cascades: aDProjectPal3Co_7 annotation-skipped as 'within
    g_EffMgr', dword_573810 export-skipped as 'compiler_generated', both
    referenced by live code).

    Returns (forced_names, extra_entries): extra_entries are synthesized
    (addr, info) pairs for IDA-pattern names absent from the export.
    """
    _glbs = _get_ida_structs().get('_globals', {})
    # S0（2026-10-09）：forced 名改读缓存（第 4 条决策点）——
    # 原 `ref = _referenced_identifiers()` 是全量 decomp body 标识符扫描，
    # 射程 export 下集合漂移 => forced 集合漂移 => 全局被错误静默。
    ref = load_header_facts()['forced_global_names']
    forced = set()
    extra = []
    for nm in ref:
        if nm in {g.get('name') for g in _glbs.values()}:
            # 2026-09-27 全局退役机制：stage4 能解析成成员路径的名字，
            # 改写后裸名不再被引用 ⇒ 放行幻影过滤退役（extern 数棘轮递减）。
            _ga = None
            for _as_, _gi in _glbs.items():
                if _gi.get('name') == nm:
                    _ga = int(_as_, 16)
                    break
            if _ga is not None and _interior_member_resolvable(_ga, nm):
                continue
            forced.add(nm)
            continue
        m = _IDA_NAME_ADDR_RE.match(nm)
        if m:
            addr = int(m.group(1), 16)
            if _interior_member_resolvable(addr, nm):
                continue
            # [F-TAB 2026-10-15] 注解显式型优先于名字启发（off_*→void* 吞数组形
            # ⇒ C2372/C2036/C2664 实测 3 错；W3 类型源律的合成路径扩展）
            t = _ann_global_type(addr) or _prefix_type(nm)
            if t and 0x401000 <= addr < 0x580000 + 0x900000:
                forced.add(nm)
                extra.append(('0x%08X' % addr,
                              {'name': nm, 'type': t, '_synthesized': True}))
    # ------------------------------------------------------------------
    # S-1 生成确定性修复（等价变换：只改顺序，不改内容）
    # ------------------------------------------------------------------
    # 病灶：`for nm in ref` 遍历 `ref = _referenced_identifiers()` 这个 **set**，
    # 其迭代序由 PYTHONHASHSEED 决定 ⇒ `extra` 逐进程漂移。
    # 下游 generate_globals_cpp() 的消费点是
    #   `sorted(_glbs.items(), ...) + _extra_entries`
    # —— `_extra_entries` **未排序**追加 ⇒ globals.cpp 尾块行序逐进程漂移。
    # 同态双跑实证（2026-10-09）：两次尾块重排、排序后多重集全同、均 2889 行
    # ⇒ 内容无误，只有顺序漂移。
    #
    # 修法：**在源头排序**（而非两处消费点各排一次），使两个消费者自动一致。
    # 等价性前提（由 tests/codegen/test_codegen_determinism.py::
    # test_extra_entries_are_pod_only 断言）：extra 全是 POD 标量
    # ⇒ globals.cpp 定义序 = CRT/静态初始化序（见 generate_globals() 注释）
    # ⇒ 排序不改变构造序，只改变文本行序 = 等价变换。
    extra.sort(key=lambda e: int(e[0], 16))
    return forced, extra


def _read_c_string(exe_data, addr):
    """NUL-terminated string at VA (image base 0x400000, identity mapping)."""
    if exe_data is None:
        return None
    off = addr - 0x400000
    if off < 0 or off >= len(exe_data):
        return None
    end = exe_data.find(b'\x00', off)
    if end < 0 or end - off > 4096:
        return None
    raw = exe_data[off:end]
    out = []
    for b in raw:
        if b == 0x22:
            out.append('\\"')
        elif b == 0x5C:
            out.append('\\\\')
        elif b == 0x0A:
            out.append('\\n')
        elif 0x20 <= b < 0x7F:
            out.append(chr(b))
        else:
            out.append('\\x%02X' % b)
    return ''.join(out)


def generate_globals():
    """Generate include/pal3/globals.h from ida_structs.json globals + binary initial values."""
    import struct as _st

    _is_data = _get_ida_structs()
    globs = _is_data.get('_globals', {})
    if not globs:
        return

    exe_path = PROJECT_ROOT / "original" / "PAL3.exe"
    exe_data = open(exe_path, 'rb').read() if exe_path.exists() else None

    # PE section info for reading initial values
    DATA_VA = 0x580000
    RDATA_VA = 0x56A000
    RDATA_END = 0x57F178
    BSS_START = 0xBF0000  # approximate: .bss starts around here (uninitialized)

    def read_init_value(addr, typ):
        """Read initial value from .data section of binary."""
        if exe_data is None:
            return None
        foff = addr - 0x400000
        if foff < 0 or foff + 8 > len(exe_data):
            return None
        # .rdata and .data have file backing; .bss does not
        if addr >= BSS_START:
            return None  # uninitialized, default 0
        if 'float' in typ:
            val = _st.unpack_from('<f', exe_data, foff)[0]
            if val == 0.0:
                return None  # skip zero-init (default)
            if val == int(val) and abs(val) < 1e6:
                return '%d.0f' % int(val)
            return '%.7gf' % val
        if 'double' in typ:
            val = _st.unpack_from('<d', exe_data, foff)[0]
            if val == 0.0:
                return None
            return '%.15g' % val
        if any(t in typ for t in ['int', 'DWORD', 'LONG', 'UINT', 'BOOL', 'unsigned long']):
            val = _st.unpack_from('<I', exe_data, foff)[0]
            if val == 0:
                return None
            if val > 0x7FFFFFFF:
                return '0x%X' % val
            return str(val)
        return None

    # Sort by address
    sorted_globs = sorted(globs.items(), key=lambda x: int(x[0], 16))

    # Filter out "phantom" globals that fall within a larger struct's range
    # (they're actually struct fields, not independent variables)
    _phantom_count = 0
    _phantom_log = []
    _instances = []  # (base, end, name, type) from _globals with known struct types
    for _addr_s, _ginfo in globs.items():
        _gtype = _ginfo.get('type', '')
        _stinfo = _is_data.get(_gtype, {})
        _sz = _stinfo.get('size', 0)
        if _sz > 0:
            _dms = _stinfo.get('data_members', [])
            _instances.append((int(_addr_s, 16), int(_addr_s, 16) + _sz, _ginfo.get('name', ''), _gtype, _dms))
    _phantom_forced, _phantom_extra = _forced_global_entries()
    _filtered = []
    for _addr_s, _ginfo in sorted_globs:
        _addr = int(_addr_s, 16)
        if _ginfo.get('name') in _phantom_forced:
            _filtered.append((_addr_s, _ginfo))
            continue
        _phantom = False
        for _base, _end, _pname, _ptype, _dms in _instances:
            if _base < _addr < _end:
                # Skip if the global has its own struct_instance (not a phantom)
                if any(b == _addr for b, e, _, _, _ in _instances):
                    break
                _offset = _addr - _base
                for _dm in _dms:
                    if _dm.get('offset') == _offset:
                        _phantom = True
                        break
                if _phantom:
                    _phantom_count += 1
                    _phantom_log.append(_ginfo.get('name', _addr_s))
                    break
        if not _phantom:
            _filtered.append((_addr_s, _ginfo))
    sorted_globs = _filtered
    if _phantom_count:
        print("  Phantom globals skipped: %d (%s)" % (_phantom_count, ', '.join(_phantom_log[:10])))
        if _phantom_count > 10:
            print("    ... and %d more" % (_phantom_count - 10))

    # Filter out .rdata vtable/offset/string entries (compiler-generated)
    # Done at export layer (export_full.py marks them type=skip)
    _vtable_filtered = list(sorted_globs)

    # Load annotations to filter type=skip entries — unless the decompiler
    # still references the name (skip governs renaming, not silencing)
    _forced_names, _extra_entries = _forced_global_entries()
    # P1-5（第九批）：路径收敛到单一读点；**保留原语义**（此处无 try ⇒ 出错即抛）
    _ann_path = _annview.annotation_json_path('globals.json')
    if os.path.exists(_ann_path):
        _ann_data = json.loads(open(_ann_path, encoding='utf-8').read())
        _ann_skipped = 0
        _ann_filtered = []
        for _addr_s, _ginfo in sorted_globs:
            _addr = int(_addr_s, 16)
            _ann_key = '0x%08X' % _addr
            _ann_entry = _ann_data.get(_ann_key, {})
            if _ann_entry.get('type') == 'skip' \
                    and _ginfo.get('name') not in _forced_names:
                _ann_skipped += 1
                continue
            # Override name from globals.json if available (but not type - too risky)
            if _ann_entry.get('name'):
                _ginfo['name'] = _ann_entry['name']
            # [R93 2026-10-25] ptr_table 类目放开类型覆盖（scoped opt-in）：
            # off_* 表全局被兜成 void* 标量 ⇒ off_X[0] 取 void 元素 ⇒ C2440
            # 'void'→'char*' ×12（8 表，2026-10-25 普查）。skip 型走 orig_type
            # 复活路径（W3，无需此处）；仅非 skip 且 category=ptr_table 且
            # 注解显式 type 时覆盖（0x005707D0 const char * 策展形场景）。
            if _ann_entry.get('category') == 'ptr_table':
                # 统一取型：orig_type（墓碑）优先；非 skip 的策展 type 次之；
                # 注解 skip 但 export 非 skip（兜底 void* 形）也用 orig_type 覆盖
                # （两域 skip 不同源：export 的 void* ≠ 注解 skip 语义，0x0056C548 实证）
                _t93 = _ann_entry.get('orig_type') or (
                    _ann_entry.get('type') if _ann_entry.get('type') != 'skip' else None)
                if _t93:
                    _ginfo['type'] = _t93
            # G1 分区：category 字段随注解流入（发射分区用；globals.cpp 不消费）
            if _ann_entry.get('category'):
                _ginfo['category'] = _ann_entry['category']
            # 墓碑原类型传导（复活型解析源——W3 类型源律）
            if _ann_entry.get('orig_type'):
                _ginfo['orig_type'] = _ann_entry['orig_type']
            _ann_filtered.append((_addr_s, _ginfo))
        sorted_globs = _ann_filtered
        if _ann_skipped:
            print("  Annotation-skipped globals: %d" % _ann_skipped)

    # Merge synthesized entries for referenced IDA-pattern names missing
    # from the export entirely (byte_C11748, off_5D8A3C, ...)
    _have = {g.get('name') for _, g in sorted_globs}
    for _addr_s, _ginfo in _extra_entries:
        if _ginfo['name'] not in _have:
            sorted_globs.append((_addr_s, _ginfo))
            _have.add(_ginfo['name'])
    # same-name globals at multiple addresses would emit conflicting externs
    # (C2040): first address wins
    _dedup, _seen_names = [], set()
    for _addr_s, _ginfo in sorted_globs:
        _nm = _ginfo.get('name')
        if _nm in _seen_names:
            continue
        _seen_names.add(_nm)
        _dedup.append((_addr_s, _ginfo))
    sorted_globs = _dedup
    # N2（fcce0c24）：类别图回退**在 _extra_entries 合成之后**——否则合成条目永远拿不到类别
    # （UNCLASSIFIED 364 事故根因）；顺序=注解 category → 合成合并 → 类别图回退 → 分区。
    _catmap_path = os.path.join(os.path.dirname(_ann_path), '..', 'status', 'global_categories.json')
    _catmap = {}
    if os.path.exists(_catmap_path):
        try:
            _catmap = json.loads(open(_catmap_path, encoding='utf-8').read())
        except Exception:
            _catmap = {}
    if _catmap:
        for _addr_s, _ginfo in sorted_globs:
            if not _ginfo.get('category'):
                _c = _catmap.get('0x%08X' % int(_addr_s, 16))
                if _c:
                    _ginfo['category'] = _c
    # **组内保持地址序**；globals.cpp 定义序不动（:3763 地址序）⇒ CRT/静态初始化序不变。
    _SECTION_ORDER = {'game_state': 0, 'anchor_object': 1, 'function_static': 2,
                      'const_data': 3, 'ptr_table': 4, 'string_literal': 5,
                      'unreferenced': 6, 'object_interior': 6, 'pending': 7}
    _SECTION_NAMES = {0: 'GAME STATE（可变全局——真变量面）', 1: 'GLOBAL OBJECTS（锚对象本体）',
                      2: 'FUNCTION STATICS', 3: 'CONST DATA（只读数据/初值）',
                      4: 'POINTER TABLES（vtable/跳转/导入槽）', 5: 'STRING LITERALS（字面量）',
                      6: 'UNREFERENCED / TABLE FRAGMENTS', 7: 'UNCLASSIFIED'}

    def _sect_of(gi):
        return _SECTION_ORDER.get(gi.get('category'), 8)
    sorted_globs = sorted(sorted_globs, key=lambda x: (_sect_of(x[1]), int(x[0], 16)))
    _cur_sect = [None]

    # Generate globals.h (extern declarations)
    h_lines = [
        '#pragma once',
        '// PAL3 global variables with known types',
        '// Auto-generated from pipeline/data/annotations/globals.json',
        '',
        '#include <windows.h>',
        '#include "pal3/ida_types.h"',
        '#ifndef _PVFV',
        'typedef void (__cdecl *_PVFV)(void);',
        '#endif',
        '',
        '// %d typed globals' % len(sorted_globs),
        '',
    ]

    # includes_needed: types that need full definition (#include header)
    # fwd_classes: types that only need forward declaration (pointers only)
    includes_needed = set()
    fwd_classes = set()
    gen_header_dir = OUTPUT_DIR

    def extract_base_type(t):
        """Extract base type name from a type string."""
        b = t.replace('const ', '').replace('*', '').replace('[]', '').strip()
        return re.sub(r'\[(?:0x[0-9a-fA-F]+|\d+)\]', '', b).strip()

    for addr_str, g in sorted_globs:
        name = g.get('name', '')
        typ = g.get('type', 'int')
        if not name:
            continue
        _s = _sect_of(g)
        if _s != _cur_sect[0]:
            _cur_sect[0] = _s
            h_lines.append('')
            h_lines.append('// ==== %s ====' % _SECTION_NAMES.get(_s, 'UNCLASSIFIED'))
        if typ == 'skip':
            # export-layer skip — resurrect when the decompiler references
            # the name（W3 类型源律：墓碑 orig_type 优先 → 名字启发仅最后回退——
            # 头/定义两侧必须同源解析，否则 extern int vs 定义 void*/int[5] 相撞 C2040）
            if name in _forced_names:
                typ = g.get('orig_type') or _prefix_type(name) or 'int'
                g = dict(g, type=typ)
            else:
                continue  # known-unnameable: don't emit extern declaration
        # Skip globals with :: in type (PDB artifacts like Concurrency::details::VirtualProcessor)
        # These types don't exist in VC6 and cause C2653 errors
        if '::' in typ:
            continue

        # Skip WinAPI function pointer globals (loaded via GetProcAddress) that are
        # already declared in <windows.h>. Re-declaring them causes C2372 redefinition.
        # Also avoids VC6-incompatible types like LSTATUS, __noreturn in these decls.
        # (Mangled/non-C-identifier names are already filtered at export layer.)
        if '__stdcall' in typ and '*)' in typ:
            continue

        base_typ = extract_base_type(typ)
        is_pointer_only = '*' in typ and '[' not in typ
        has_header = any((gen_header_dir / d / ("%s.h" % base_typ)).exists()
                         for d in ('', 'Misc', 'Combat', 'UI', 'Effect', 'Scene',
                                   'Role', 'GameBase', 'Render', 'Data', 'MiniGame', 'Script'))
        has_struct = _ann_struct_path(base_typ) is not None

        # Track types needing full definition vs forward declaration
        # Skip primitive types — they cannot be forward-declared as class
        if not (base_typ in _GLOBALS_PRIMITIVES):
            if has_struct and not is_pointer_only:
                if has_header:
                    includes_needed.add(base_typ)
                else:
                    fwd_classes.add(base_typ)
            elif has_struct and is_pointer_only:
                if base_typ not in includes_needed:
                    fwd_classes.add(base_typ)

        # Emit extern declaration with correct C syntax
        # Split array type: "unsigned __int8[768]" -> base="unsigned __int8", arr="[768]"
        arr_match = re.match(r'^([\w\s]+?)((?:\[[^\]]*\])+)$', typ)
        ptr_arr_match = re.match(r'^(.+\*)\s*(\[\d+\])$', typ)

        if ptr_arr_match:
            base, arr = ptr_arr_match.group(1).strip(), ptr_arr_match.group(2)
            h_lines.append('extern %s %s%s; // %s' % (base, name, arr, addr_str))
        elif arr_match and '*' not in typ:
            base, arr = arr_match.group(1).strip(), arr_match.group(2)
            h_lines.append('extern %s %s%s; // %s' % (base, name, arr, addr_str))
        elif '[]' in typ:
            base = typ.replace('[]', '').strip()
            h_lines.append('extern %s %s[]; // %s' % (base, name, addr_str))
        elif '*' in typ:
            h_lines.append('extern %s %s; // %s' % (typ, name, addr_str))
        else:
            h_lines.append('extern %s %s; // %s' % (typ, name, addr_str))

    # NOTE: Globals from annotations globals.json that are not in _globals
    # (because they overlap with larger struct instances like g_SceneMgr)
    # are intentionally NOT declared here as standalone externs.
    # They are "artifacts" — memory that belongs to a containing struct.
    # The overlap resolution in stage4_substitution.py (_resolve_stru_overlap)
    # converts accesses to them into offset expressions at the codegen level.

    # Remove from fwd_classes anything already in includes_needed
    fwd_classes -= includes_needed

    # Insert #include for types needing full definition
    insert_pos = 8  # after #include <windows.h> and blank line
    if includes_needed:
        for cls in sorted(includes_needed):
            _sub = get_class_dir(cls)
            if _sub:
                h_lines.insert(insert_pos, '#include "%s/%s.h"' % (_sub, cls))
            else:
                h_lines.insert(insert_pos, '#include "%s.h"' % cls)
            insert_pos += 1
        h_lines.insert(insert_pos, '')
        insert_pos += 1
    # Insert forward declarations for pointer-only types
    if fwd_classes:
        for cls in sorted(fwd_classes):
            h_lines.insert(insert_pos, 'class %s;' % cls)
            insert_pos += 1
        h_lines.insert(insert_pos, '')

    globals_h = OUTPUT_DIR / "globals.h"
    with open(globals_h, 'w', encoding='utf-8') as f:
        f.write('\n'.join(h_lines) + '\n')

    print("  Globals: %d in globals.h" % (len(h_lines) - 6))

    if _header_errors:
        print("\n[WARN] Header generation found %d annotation conflicts (deduplicated):" % len(_header_errors))
        for e in _header_errors:
            print("  %s" % e)

_POD_TYPES = {'int', 'float', 'double', 'char', 'short', 'long', 'unsigned',
    'DWORD', 'WORD', 'BYTE', 'BOOL', 'LONG', 'UINT', 'LPCSTR', 'LPVOID',
    'HANDLE', 'HWND', 'HDC', 'HINSTANCE', 'HRESULT', 'LSTATUS',
    'unsigned char', 'unsigned int', 'unsigned long', 'unsigned short',
    'signed char', '__int8', '__int16', '__int32', '__int64',
    'unsigned __int8', 'unsigned __int16', 'unsigned __int32', 'unsigned __int64',
    'size_t', 'wchar_t', 'LPSTR', 'LPBYTE', 'LPDWORD', 'LPCWCH',
    'CHAR', 'TCHAR', 'UCHAR', 'UINT8', 'UINT16', 'UINT32',
    'bool', 'void *', 'const char *', 'const void *',
    '_PVFV', 'COLORREF',
}

def _is_pod_type(tp):
    """Check if a type string represents a POD/fundamental type (not a struct/class)."""
    tp_clean = tp.strip()
    # Strip const/volatile qualifiers
    base = tp_clean
    for q in ('const ', 'volatile ', 'signed '):
        if base.startswith(q):
            base = base[len(q):]
    # Check exact match
    if base in _POD_TYPES or tp_clean in _POD_TYPES:
        return True
    # Check pointer types (T *)
    if tp_clean.endswith('*') or tp_clean.endswith('*const'):
        return True
    # Check function pointer types (contain ( and ))
    if '(' in tp_clean and ')' in tp:
        return True
    # Check if it starts with a known base type
    for prefix in ('unsigned', 'signed', 'int', 'float', 'double', 'char', 'short', 'long',
                   'const char', 'const int', 'const float', 'const double'):
        if tp_clean.startswith(prefix):
            return True
    # Handle pattern: "const TYPE[]" where TYPE is in POD set
    if '[' in tp_clean and tp_clean.endswith(']'):
        no_arr = tp_clean.split('[')[0].strip()
        no_arr = no_arr.replace('const ', '').replace('volatile ', '').strip()
        if no_arr in _POD_TYPES:
            return True
    return False

def _read_init_value(addr, typ, exe_data):
    """Read initial value for a global from PE binary data section.
    Type checks are ordered by size (smallest first) to avoid false matches."""
    import struct as _st
    foff = addr - 0x400000
    bss_start = 0xBF0000
    if foff < 0 or foff + 8 > len(exe_data):
        return None
    if addr >= bss_start:
        return None
    # 1-byte types - check before int/short to avoid 'int' in '__int8' false match
    if ('char' in typ and '*' not in typ and 'unsigned' in typ) or '__int8' in typ:
        val = exe_data[foff]
        if val == 0: return None
        return '0x%02X' % val
    # 2-byte types
    if ('short' in typ or '__int16' in typ or 'WORD' in typ) and '*' not in typ:
        val = _st.unpack_from('<H', exe_data, foff)[0]
        if val == 0: return None
        return '0x%X' % val if val > 255 else str(val)
    # 4-byte float
    if 'float' in typ and '*' not in typ:
        val = _st.unpack_from('<f', exe_data, foff)[0]
        if val == 0.0: return None
        if val == int(val):
            return '%d.0f' % int(val)
        return '%.7gf' % val
    # 8-byte double
    if 'double' in typ:
        val = _st.unpack_from('<d', exe_data, foff)[0]
        if val == 0.0: return None
        return '%.15g' % val
    # 4-byte integer types
    if any(t in typ for t in ['int', 'DWORD', 'LONG', 'UINT', 'BOOL', 'unsigned long']):
        val = _st.unpack_from('<I', exe_data, foff)[0]
        if val == 0: return None
        if val > 0x7FFFFFFF: return '0x%X' % val
        return str(val)
    # Char array (string) — read actual content from .data section
    # [F-TAB 修 2026-10-15] `*` 必须排除：指针数组型（const char *[]）此前也
    # 命中本路径 ⇒ 定义发成 `T* X[] = "字节串"` ⇒ C2440 ×4（globals.cpp L61/62/
    # 1944/1948，实测 off_56F314/56F328/56BA1C/56D5D8 全中）。
    if 'char' in typ.lower() and ('[' in typ or '[]' in typ) and '*' not in typ:
        raw = exe_data[foff:foff+256]
        null_pos = raw.find(b'\x00')
        if null_pos > 0:
            s = raw[:null_pos]
            if all(32 <= b < 127 for b in s):
                decoded = s.decode('ascii')
                decoded = decoded.replace('\\', '\\\\')
                return '"%s"' % decoded
            else:
                # Mixed content: escape non-printable bytes individually
                esc_map = {ord('\r'): '\\r', ord('\n'): '\\n', ord('\t'): '\\t',
                           ord('\\'): '\\\\', ord('"'): '\\"'}
                result = []
                all_ascii_ctrl = True
                for b in s:
                    if 32 <= b < 127:
                        result.append(chr(b))
                    elif b in esc_map:
                        result.append(esc_map[b])
                    else:
                        all_ascii_ctrl = False
                        result.append('\\x%02X' % b)
                if all_ascii_ctrl:
                    # Only regular ASCII + \r \n \t — keep readable
                    return '"%s"' % ''.join(result)
                # Has non-ASCII bytes: use \x escape with GB2312 comment
                escaped = ''.join('\\x%02X' % b for b in s)
                comment = ''
                try:
                    gb = s.decode('gb2312', errors='replace')
                    if any(ord(c) > 127 for c in gb):
                        comment = ' /* "%s" */' % gb
                except:
                    pass
                return '"%s"%s' % (escaped, comment)
        elif null_pos == 0:
            return None
        return None
    # Pointer / function pointer types — semantic correctness > byte matching
    # Absolute addresses from original binary are invalid in our build.
    if '*' in typ or '(' in typ:
        return None  # always init to NULL / {0}

def _read_crt_init_data():
    """Load pre-computed CRT init values."""
    import json as _json
    paths = [
        PROJECT_ROOT / "asm" / "pal3" / "crt_init_data.json",
        PROJECT_ROOT / "tmp" / "crt_init_values.json",
    ]
    for p in paths:
        if p.exists():
            data = _json.loads(p.read_text(encoding='utf-8'))
            result = {}
            for category in data.values():
                if isinstance(category, dict):
                    for a_s, writes in category.items():
                        if isinstance(writes, list) and writes:
                            w = writes[0]
                            v = w.get('value')
                            if v is not None:
                                result[int(a_s, 16)] = v
            return result
    return {}

def generate_globals_cpp():
    """Generate globals.cpp from ida_structs.json + PE binary + CRT init data."""
    import json as _json, re as _re
    import struct as _st

    _is_data = _get_ida_structs()
    _glbs = _is_data.get('_globals', {})
    if not _glbs:
        return

    exe_path = PROJECT_ROOT / "original" / "PAL3.exe"
    exe_data = open(exe_path, 'rb').read() if exe_path.exists() else None
    
    # Load CRT init data
    crt_iv = _read_crt_init_data()

    # Load annotations for skip filtering
    ann_path = PROJECT_ROOT / "data" / "annotations" / "globals.json"
    ann_raw = _json.loads(ann_path.read_text(encoding='utf-8')) if ann_path.exists() else {}
    # Normalize annotation keys: lowercase hex with 8-digit format
    ann = {}
    for a_s, info in ann_raw.items():
        try:
            ann[f'0x{int(a_s, 16):08x}'] = info
        except:
            ann[a_s] = info
    
    # Determine globals to include
    # Same logic as generate_globals() for filtering
    DATA_VA = 0x580000
    RDATA_VA = 0x56A000
    RDATA_END = 0x57F178
    BSS_START = 0xBF0000

    _forced_names, _extra_entries = _forced_global_entries()

    def _should_skip_global(addr, name, typ, ann_info):
        if name in _forced_names:
            return False  # referenced by decomp bodies: must be defined
        if ann_info.get('type') == 'skip':
            return True
        # [task-9 2026-10-19·确保生成] **DATA_VA 启发跳撤除**：.rdata 标量（flt_/dword_
        # 等）被代码引用者必声明——原启发跳致 flt_D90060 等被跳 ✗✗ C2065 面
        # （超集安全 ✓ 码内既有原则「Extra forward declarations are legal」）。
        # 仅保留：ann_info type=='skip'（导出层跳 ✓）· 强制名（引用 ✓ 必发）。
        return False
    
    lines = [
        '// Auto-generated globals.cpp',
        '// Generated from ida_structs.json _globals + PE binary + CRT init data',
        '#include "globals.h"',
    ]
    inc = 0
    _emitted_names = set()

    for addr_s, info in sorted(_glbs.items(), key=lambda x: int(x[0], 16)) + _extra_entries:
        addr = int(addr_s, 16)
        nm = info.get('name', '')
        tp = info.get('type', '')
        ann_key = f'0x{addr:08x}'
        ann_info = ann.get(ann_key, {})
        if info.get('_synthesized'):
            ann_info = {}

        if not nm or not tp:
            continue
        if '__stdcall' in tp and '*)' in tp:
            continue  # WinAPI GetProcAddress pointers: windows.h declares
        if tp == 'skip':
            if nm not in _forced_names:
                continue
            # 复活型解析（W3 类型源律）：注解 orig_type（墓碑原类型）优先 →
            # 名字启发仅最后回退（pEnd/dword_C057EC 曾被 int 吞 void*/int[5] ⇒ C2664/C2109）
            tp = (ann_info or {}).get('orig_type') or _prefix_type(nm) or 'int'
            info = dict(info, type=tp)
        if _should_skip_global(addr, nm, tp, ann_info):
            continue
        if nm in _emitted_names:
            continue  # same name at another address: one definition wins
        _emitted_names.add(nm)
        # string globals: define from the exe bytes at the address
        if re.match(r'^a[A-Z]', nm) or tp.startswith('char['):
            s = _read_c_string(exe_data, addr)
            if s is not None:
                # `const` 必须与 globals.h 的 extern 声明**一致**：声明侧用注解的
                # 类型原样发（`extern const char X[];`），定义侧过去硬编码成
                # `char X[] = "..."` ⇒ C2373: redefinition; different type modifiers。
                # 实测 45 对不一致（globals.cpp 共 96 个错误）。
                # 判据与声明侧同源：都看注解类型是否带 const。
                _cq = 'const ' if tp.strip().startswith('const') else ''
                lines.append(f'{_cq}char {nm}[] = "{s}";')
                inc += 1
                continue
        if not _is_pod_type(tp.split('[')[0].strip()):
            # 2026-09-28 实测：非 POD 路径漏数组拆分 ⇒ `_DWORD[1] dword_X;` 语法错（C2143）
            # ——与下方 POD 路径（:3797）同款拆分对齐。
            _am = _re.match(r'(.+?)((?:\[[^\]]*\])+)$', tp)
            if _am:
                lines.append(f'{_am.group(1).strip()} {nm}{_am.group(2)};')
            else:
                lines.append(f'{tp} {nm};')
            inc += 1
            continue

        # Determine initial value
        iv = None
        if addr in crt_iv:
            iv = '0x%X' % crt_iv[addr]
        elif exe_data:
            iv = _read_init_value(addr, tp, exe_data)

        # Apply to type
        m = _re.match(r'(.+?)((?:\[[^\]]*\])+)$', tp)
        if m:
            base_t = m.group(1).strip()
            arr_t = m.group(2)
            tp_out = f'{base_t} {nm}{arr_t}'
            if iv:
                # [C2440 修 2026-10-19] 数组型全局的标量初值必须**花括号包裹**
                # 病灶：`float g_fHeuristicScale[8] = 1.0f;`（数组 + 标量）
                #   ⇒ C2440 'initializing' cannot convert from 'const float' to 'float [8]' ✗✗
                # 实测 globals.cpp 19 条同族（另 int[] = 0xAC0CAB00 等）。
                # 修法：`{v}`（元素0=已知初值；其余按 C 规则零填充，
                #   与未初始化数据段语义一致 —— 不编造未知元素值 ✓）
                lines.append(f'{tp_out} = {{{iv}}};')
            else:
                lines.append(f'{tp_out} = {{0}};')
        else:
            tp_out = f'{tp} {nm}'
            if iv:
                lines.append(f'{tp_out} = {iv};')
            else:
                lines.append(f'{tp_out} = {{0}};')
        inc += 1
    
    lines.append('')
    out_path = OUTPUT_DIR / "globals.cpp"
    out_path.write_text('\n'.join(lines) + '\n', encoding='utf-8')
    print("  Globals: %d in globals.cpp" % inc)
    lines.append(f'// {inc} globals defined')
    out_path = OUTPUT_DIR / "globals.cpp"
    out_path.write_text('\n'.join(lines) + '\n', encoding='utf-8')
    print("  Globals: %d in globals.cpp" % inc)


def run_header_generation():
    main()

if __name__ == '__main__':
    main()
