"""
IDAPython: Pure export - no modifications to IDB. Just export all functions.

Usage:
  idat.exe -A -S"pal3_export_only.py" original/PAL3.exe.i64
"""
import ida_auto, ida_funcs, ida_hexrays, ida_name, ida_typeinf, idautils, idc
import ida_segment as idaseg
import json, os, sys, time, glob, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
sys.path.insert(0, PROJECT_ROOT)
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")

from pipeline.gen.annotation_view import iter_struct_files, iter_structs, load_struct


def _strict_struct_entries(directory):
    for path in iter_struct_files(directory):
        struct_data = load_struct(path)
        if not isinstance(struct_data, dict):
            raise ValueError('%s: struct annotation must be a JSON object' % path)
    return list(iter_structs(directory))

# After apply_annotations changes types, Hex-Rays cache is stale — need dirty mark.
# After init --force (fresh IDB), no cache exists — dirty mark is harmless but redundant.
# Set to False for fast re-export when IDB hasn't changed (uses cached decompilation).
FORCE_REFRESH = os.environ.get("PAL3_EXPORT_NO_REFRESH", "") == ""
LOG_FILE = os.path.join(SCRIPT_DIR, "_logs", "pal3_export_only_log.txt")
TEXT_START = 0x00401000
TEXT_END = 0x005695D0

RDATA_START = 0x0056A000
RDATA_END = 0x0057F178

# ---------------------------------------------------------------------------
# [t4-DECLARED-EXCEPTION] export 读 data/annotations/ —— 有意取舍，本轮不迁移
#
# CLAUDE.md 红线：「export 不读 annotation：export_full.py 只能从 IDB 读取数据，
# 不能直接读 data/annotations/ JSON 文件」。本文件**仍有 8 处**直接读
# data/annotations/，全部带 [t4-DECLARED-EXCEPTION] 标记（grep 即得）。
# （第 9 处 :150 的 functions.json 死读已于 t4 删除，见 main() 内的存根注释。）
#
# 取舍结论与全部实测证据：
#   data/status/_cleanup_fix_export_redline.json              ← t4 交付物
#   data/status/_cleanup_fix_export_redline_decision_page.md  ← 决策页草稿
#     （待 captain→integrator 落盘到 docs/knowledge/；本轮不直接改知识库）
#
# 不迁移的三条实测理由（详细数字见交付物）：
#  1. 这些信息在当前 IDB 中**没有等价可查询形式**：apply_annotations.py 对
#     skip_functions.json 只做 set_name/add_func（无 skip 标记）；对 globals.json
#     的 type=="skip" 明确不写入 IDB（:1710 排除）；methods/vtables/known_members
#     的 JSON 形态与 skip 名单也未被 apply 持久化成任何磁盘产物（apply 只写
#     _logs/*.txt、gbengine_flat_ida.h、sig-fail log）。
#  2. 这些读取**承重**（对当前导出有可测量效果）：1955 个 skip 地址决定语料组成
#     （与 3594 个导出地址交集=0）；475 个 virtual 地址 → 442 个 signature 的
#     "virtual " 前缀；3276 个 VC6 mangled 名；686 个 struct 的 _variants（8979 条
#     条目）透传进 asm/pal3/ida_structs.json；1816 个 _skip_function_names
#     （pipeline/gen/data.py:188 消费）；188/808 个 globals 的 type=skip。
#  3. asm/pal3/ida_structs.json 的 vtables/methods/_variants 与注解**逐字段等值**
#     （761/761 个 struct 零不一致）→ 它们是"注解的复制"，不是 IDB 状态的证据；
#     改为纯 IDB 取数会改变导出产物，须用一次独占 export 窗口做 3594 个 decomp
#     JSON + ida_structs.json 的全量 diff 才能判等价（本轮窗口被 t3 apply 占用）。
#
# 迁移前置条件（见交付物 pending_window）：apply（或独立 IDB dumper）先把
# skip 集合 / globals skip / skip 名单 / structs 元数据以"从 IDB 状态生成"的形式
# 落盘，export 只读该产物，并给出上述全量 diff。本轮**不做**（inScope 只有
# export_full.py，且无法验证）。
# ---------------------------------------------------------------------------

_COMPILER_GENERATED_NAMES = (
    '??_L@',   # `eh vector constructor iterator'
    '??_M@',   # `eh vector destructor iterator'
    '??_G',    # `scalar deleting destructor'
    '??_E',    # `vector deleting destructor'
    '??_7',    # `vftable'
)

class PAL3Optimizer(ida_hexrays.optinsn_t):
    def __init__(self):
        ida_hexrays.optinsn_t.__init__(self)
        self.vftable_nops = 0
        self.compiler_call_nops = 0

    def func(self, blk, ins, optflags):
        n = 0
        n += self._nop_vftable_init(blk, ins)
        n += self._nop_compiler_calls(blk, ins)
        return n

    def _nop_vftable_init(self, blk, ins):
        if ins.opcode != ida_hexrays.m_stx:
            return 0
        src = ins.l
        if src.t != ida_hexrays.mop_a:
            return 0
        try:
            if src.a.t != ida_hexrays.mop_v:
                return 0
            addr = src.a.g
        except:
            return 0
        if not (RDATA_START <= addr <= RDATA_END):
            return 0
        if blk:
            blk.make_nop(ins)
        else:
            ins._make_nop()
        self.vftable_nops += 1
        return 1

    def _nop_compiler_calls(self, blk, ins):
        if ins.opcode != ida_hexrays.m_call:
            return 0
        if ins.l.t != ida_hexrays.mop_v:
            return 0
        try:
            addr = ins.l.g
            name = ida_name.get_name(addr) or ''
        except:
            return 0
        if not any(name.startswith(p) for p in _COMPILER_GENERATED_NAMES):
            return 0
        if blk:
            blk.make_nop(ins)
        else:
            ins._make_nop()
        self.compiler_call_nops += 1
        return 1

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)
    try:
        with open('/tmp/s1_diag.log', 'a') as _f:
            _f.write(str(msg) + '\n')
    except Exception:
        pass

_orphan_stats = {}  # Global stats for debugging

def resolve_orphan_ordinals(code_str):
    """
    替换 Hex-Rays 输出的 #ordinal 引用为实际类型名。

    原因：PDB 导入时，前向声明成功（分配 ordinal）但完整定义失败，
    导致 ordinal 成为孤儿。Hex-Rays 看到 ordinal 但找不到完整定义，输出 #N。

    解决：查询 ordinal 对应的类型名，如果有名字就替换；如果是匿名/孤儿，
    用 struct_N 占位符（保留序号用于后续修复）。
    """
    import re

    def replace_ordinal(match):
        ordinal_str = match.group(1)
        try:
            ordinal = int(ordinal_str)
            _orphan_stats[ordinal] = _orphan_stats.get(ordinal, 0) + 1

            til = ida_typeinf.get_idati()
            # 尝试从 TIL 获取类型名
            type_name = ida_typeinf.get_numbered_type_name(til, ordinal)
            if type_name:
                # 成功解析，使用实际名字
                return type_name
            # 无法解析，检查是否是前向声明
            tif = ida_typeinf.tinfo_t()
            if tif.get_numbered_type(til, ordinal):
                # 类型存在但没有名字，可能是孤儿前向声明
                dstr = tif.dstr()
                # 如果 dstr 本身不是 #ordinal，使用它
                if dstr and not dstr.startswith('#'):
                    return dstr
            # 完全无法解析，用占位符（保留 ordinal 供后续修复）
            return 'struct $Ord%d' % ordinal
        except Exception as e:
            # 异常时保留原始
            log("[!] Exception resolving #%s: %s" % (ordinal_str, str(e)))
            return match.group(0)

    # 匹配 #数字 模式（standalone 或在 struct #N 中）
    # 注意：不匹配 #include、#define 等预处理指令
    pattern = r'(?:struct\s+)?#(\d+)\b'
    resolved = re.sub(pattern, replace_ordinal, code_str)
    return resolved

def _write_header_facts_cache():
    import sys
    """S0（2026-10-09）：全量 export 末尾物化 decomp 派生的头决策事实。

    射程 export 只写 1 个 decomp JSON 会让 emit_headers 的 4 条决策点输入坍缩
    => 头决策被污染。缓存随全量 export 刷新，emit_headers 改读缓存即与
    「当前 decomp 目录有几个文件」解耦。
    """
    try:
        from pipeline.gen.stages.emit_headers import (
            save_header_facts, _get_scalar_dtor_classes_scan_impl,
            _get_underscore_aliases_scan_impl, _referenced_identifiers)
    except Exception as e:                       # IDA 内可能无 pipeline 包
        print('[S0] header-facts cache skipped: %s' % e)
        return
    # S0 修复（终审点名）：原 `import emit_headers as eh` 是**裸 import**，
    # 在 try/except 之外，且 sys.path 无任何条目含 pipeline/gen/stages/
    # => 必然 ModuleNotFoundError，缓存写入从未真正执行过。改为走
    # `from pipeline.gen.stages.emit_headers import ...`（在 try 内，可解析）。
    # ⚠️ 下面两行**不是死代码**（终审误判）：`_get_*_scan_impl()` 用模块级变量作累加器，
    # 不初始化会 AttributeError: 'NoneType' object has no attribute 'add'。
    _scan_mod = sys.modules['pipeline.gen.stages.emit_headers']
    _scan_mod._scalar_dtor_classes = set()
    _scan_mod._underscore_aliases = {}
    facts = {
        'scalar_dtor_classes': set(_get_scalar_dtor_classes_scan_impl()),
        'underscore_aliases': dict(_get_underscore_aliases_scan_impl()),
        'forced_global_names': set(_referenced_identifiers()),
        'vptr_inject_classes': set(_get_scalar_dtor_classes_scan_impl()),
    }
    save_header_facts(facts)
    print('[S0] header-facts cache written: %d scalar_dtor / %d aliases / %d forced'
          % (len(facts['scalar_dtor_classes']), len(facts['underscore_aliases']),
             len(facts['forced_global_names'])))


def main():
    import time as _t
    _T0 = _t.time()
    log('[S1-DIAG] main() start')
    try:
        ida_auto.auto_wait()
        log("[*] Pure export (no IDB modifications)")

        os.makedirs(OUTPUT_DIR, exist_ok=True)
        # 🔴 S1 破坏性 bug 修复（2026-10-10 端到端验证抓到）：
        # 此清理原本无条件删 OUTPUT_DIR/*.json，而它在**射程过滤之前**执行
        # （过滤在 targets.sort() 之后）=> 射程 export 会清空主 decomp 目录
        # （实测 3649 -> 1 个文件），随后 DECOMP_DIR 才被改指 scoped
        # => 主目录被清、产物写去别处、scoped 目录反而空。
        # 修法：射程模式下**跳过主目录清理**（主产物是共享资产，不得动），
        # 只清 scoped 目标目录。
        _sc_active = bool(os.environ.get('EXPORT_FUNC') or os.environ.get('EXPORT_CLASS'))
        # 🔴 S1 第 4 个 bug 修复（对抗复核实证 2026-10-10）：
        # EXPORT_FUNC/EXPORT_CLASS 设了但 EXPORT_OUTDIR 未设 => targets 被过滤
        # 但写入点仍指主 OUTPUT_DIR => **静默半污染主产物**（只重写被过滤到的
        # 那部分文件，无告警、无报错、退出码正常）。实测复现：EXPORT_CLASS=Object3D
        # 不设 EXPORT_OUTDIR 时，主目录 25 个文件被原地重写（mtime 变新鲜）。
        # 修法：射程过滤必须强制要求 EXPORT_OUTDIR，否则**拒绝运行**。
        if _sc_active and not os.environ.get('EXPORT_OUTDIR'):
            raise RuntimeError(
                '[S1] EXPORT_FUNC/EXPORT_CLASS 需要 EXPORT_OUTDIR：'
                '射程 export 必须写独立目录，否则会静默覆盖主 asm/pal3/decomp/ 产物。'
                '请设置 EXPORT_OUTDIR，或去掉 EXPORT_FUNC/EXPORT_CLASS 走全量。')
        if _sc_active:
            log("[S1] scoped mode: skip main OUTPUT_DIR cleanup (保护主 decomp 产物)")
            _sc_out2 = os.environ.get('EXPORT_OUTDIR')
            if _sc_out2:
                _scoped_d = os.path.join(_sc_out2, 'decomp')
                os.makedirs(_scoped_d, exist_ok=True)
                for f in glob.glob(os.path.join(_scoped_d, "*.json")):
                    if not os.path.basename(f).startswith('_'):
                        os.remove(f)
                log("[S1] scoped cleanup -> %s" % _scoped_d)
        else:
            for f in glob.glob(os.path.join(OUTPUT_DIR, "*.json")):
                if not os.path.basename(f).startswith('_'):
                    os.remove(f)

        # [t4] 已删除的死读（原 :148-154，读 data/annotations/functions.json）：
        # d827ebca6 引入"以注解 signature 为权威源"，71a2e09db（次日）删去其唯一
        # 使用点却留下 load。AST 取证：Name ann_funcs 仅在 :149/:153 被赋值、
        # 在 :154 打印计数，153 之后**无任何读取** → 删除对导出结果零影响。
        # 该处注释 "authoritative source for signatures" 是失实的化石（已随块删除）。

        # Load per-class methods to detect virtual functions and build class attribution.
        # [t4-DECLARED-EXCEPTION] structs/*.json: methods+vtables → _virtual_addrs/_addr_to_class
        # （离线复现 = 475/369/0，与 export 日志逐字一致）
        _virtual_addrs = set()    # int(addr) — appears in ANY vtable slot (own or inherited)
        _addr_to_class = {}       # int(addr) -> class_name (own slots only)
        _structs_dir = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")
        if os.path.isdir(_structs_dir):
            for _sf, _sd in _strict_struct_entries(_structs_dir):
                _sname = _sd.get('name', '')
                for _addr, _minfo in _sd.get('methods', {}).items():
                    if 'ordinal' in _minfo:
                        _virtual_addrs.add(int(_addr, 16))
                for _vt in _sd.get('vtables', []):
                    for _slot in _vt.get('slots', []):
                        _sa = _slot.get('addr', '')
                        if _sa:
                            _virtual_addrs.add(int(_sa, 16))
                for _vt in _sd.get('vtables', []):
                    for _slot in _vt.get('slots', []):
                        _sa = _slot.get('addr', '')
                        if _sa and _slot.get('from') is None:
                            _key = int(_sa, 16)
                            if _key not in _addr_to_class:
                                _addr_to_class[_key] = _sname
            # Also attribute non-virtual methods from annotation struct methods dict.
            # These have names like "ClassName::MethodName" that encode the class.
            _method_attributed = 0
            for _sf, _sd in _strict_struct_entries(_structs_dir):
                for _addr, _minfo in _sd.get('methods', {}).items():
                    if 'ordinal' in _minfo:
                        continue  # virtual methods already handled above
                    _mname = _minfo.get('name', '')
                    if '::' in _mname:
                        _cls = _mname.split('::')[0]
                        _key = int(_addr, 16)
                        if _key not in _addr_to_class:
                            _addr_to_class[_key] = _cls
                            _method_attributed += 1
            log("[*] Loaded %d virtual methods, %d class-attributable addresses (methods=%d)" % (
                len(_virtual_addrs), len(_addr_to_class), _method_attributed))

        # lvar 注解层（2026-09-25）：data/annotations/lvars.json — 函数 VA → lvar 规格
        # （栈变量按 stkoff 定位、寄存器变量按 reg 定位；name/type 可选）。export 在
        # 渲染前应用到 cfunc.lvars ⇒ 注解决定论，不依赖会被 init 清掉的 IDB 交互态。
        _LVAR_ANN = {}
        _lvar_ann_path = os.path.join(PROJECT_ROOT, 'data', 'annotations', 'lvars.json')
        if os.path.exists(_lvar_ann_path):
            try:
                with open(_lvar_ann_path, encoding='utf-8') as _lf:
                    _loaded = json.load(_lf)
                if not isinstance(_loaded, dict):
                    raise ValueError('top-level must be an object, got %s' % type(_loaded).__name__)
                _LVAR_ANN = _loaded
                log("[*] lvar annotations: %d functions" % sum(
                    1 for _k in _LVAR_ANN if not _k.startswith('_')))
            except Exception as _e:
                log("[!] lvar annotations load failed: %s" % _e)

        # Load skip list
        # [t4-DECLARED-EXCEPTION] skip_functions.json → skip_addrs(1955)；
        # apply 会为这些地址 add_func（apply:1686-1687）但**不留 skip 标记**，
        # 故 IDB 无法自证"哪些地址不该导出"。实测与 3594 个导出地址交集=0。
        skip_addrs = set()
        skip_file = os.path.join(PROJECT_ROOT, "data", "annotations", "skip_functions.json")
        if os.path.exists(skip_file):
            import json as _json
            skip_data = _json.load(open(skip_file, encoding='utf-8'))
            skip_addrs = set(int(a, 16) for a in skip_data.keys())

        # Pre-pass: set mangled names for class methods so export uses clean unique names.
        # This ensures function names like ?Create@UINote@@... are used, not Create_37.
        # [t4-DECLARED-EXCEPTION] structs/*.json + functions.json → VC6 mangled 名
        # （实测 ida_name.set_name 3276 次；3199/3594 个导出 name 含 "::"）。
        # 注：这段**写 IDB**（与文件头 "no modifications to IDB" 的自述不符）。
        try:
            import sys as _sys
            _sys.path.insert(0, SCRIPT_DIR)
            import vc6_mangler
            _ann_funcs = {}
            _funcs_file = os.path.join(PROJECT_ROOT, "data", "annotations", "functions.json")
            if os.path.exists(_funcs_file):
                _ann_funcs = _json.load(open(_funcs_file, encoding='utf-8'))
            _structs_dir = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")
            if os.path.isdir(_structs_dir):
                for _sf in sorted(os.listdir(_structs_dir)):
                    if not _sf.endswith('.json'): continue
                    with open(os.path.join(_structs_dir, _sf), 'r', encoding='utf-8') as _fh:
                        _sd = _json.load(_fh)
                    _sname = _sd.get('name', _sf.replace('.json', ''))
                    for _addr, _info in _sd.get('methods', {}).items():
                        # owner 加权（2026-10-08）：与 apply_annotations.load_annotations 一致。
                        # 否则首合并者胜 ⇒ export 的 mangler pre-pass 会用错误类名重新
                        # set_name，**覆盖 apply 的正确命名**（病灶：0x00445D10 被命名为
                        # CGameData::OnMessage 而非 UIWnd::OnMessage ⇒ ast_transform 落
                        # broken 形 ⇒ C2660）。实测 13 个 ok→fail 单元的根因。
                        if _addr not in _ann_funcs or _info.get('owner') == _sname:
                            _mn = _info.get('name', '')
                            # After method name migration (2026-06), names are short
                            # (no ClassName:: prefix). Reconstruct for mangler.
                            if _mn and '::' not in _mn:
                                _info['name'] = "%s::%s" % (_sname, _mn)
                            _ann_funcs[_addr] = _info
                    # Also merge nested type methods
                    for _nt_name, _nt_info in _sd.get('nested_types', {}).items():
                        _nt_full = "%s::%s" % (_sname, _nt_name)
                        for _addr, _info in _nt_info.get('methods', {}).items():
                            if _addr not in _ann_funcs:
                                _mn = _info.get('name', '')
                                # Reconstruct full name for mangler (ClassName::NestedType::Method)
                                if _mn:
                                    _info['name'] = "%s::%s" % (_nt_full, _mn)
                                _ann_funcs[_addr] = _info
            _set_count = 0
            for _addr_s, _info in _ann_funcs.items():
                _name = _info.get('name', '')
                _sig = _info.get('signature', '')
                if '::' not in _name or not _sig:
                    continue
                try:
                    _ea = int(_addr_s, 16)
                except:
                    continue
                if not (TEXT_START <= _ea <= TEXT_END):
                    continue
                _parts = _name.rsplit('::', 1)
                _cls = _parts[0]  # may contain :: for nested types
                _method = _parts[1]
                _mangled = vc6_mangler.mangle(_cls, _method, _sig)
                if _mangled:
                    ida_name.set_name(_ea, "", ida_name.SN_NOWARN)
                    if ida_name.set_name(_ea, _mangled, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                        _set_count += 1
            if _set_count:
                log("[*] Mangler: set %d mangled function names" % _set_count)
        except Exception as _me:
            log("[!] Mangler pre-pass error: %s" % str(_me)[:80])

        targets = []
        target_addrs = set()
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if not name or name.startswith("nullsub_") or name.startswith("j_"):
                continue
            if ea in skip_addrs:
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() <= 1:
                continue
            targets.append((ea, name, func.size()))
            target_addrs.add(ea)

        # Ensure all functions.json entries are in targets (fix for IDA undefine race)
        # [t4-DECLARED-EXCEPTION] functions.json 全地址表 → 未定义函数的 recover 补录。
        # 当前实测 recovered=0（2 条不可恢复），故对本轮产物零贡献；保留理由是
        # 换 IDB / 重建库时的稳健性（address 全表在 IDB 里无等价查询）。
        funcs_json = os.path.join(PROJECT_ROOT, "data", "annotations", "functions.json")
        _recovered = 0
        _missing = []
        if os.path.exists(funcs_json):
            import json as _fj
            import ida_bytes, ida_ua
            _ann_funcs = _fj.load(open(funcs_json, encoding='utf-8'))
            for _addr_str, _info in _ann_funcs.items():
                _ea = int(_addr_str, 16)
                if _ea in target_addrs or _ea in skip_addrs:
                    continue
                if not (TEXT_START <= _ea <= TEXT_END):
                    continue
                # Try to ensure function exists (aggressive recovery)
                if not ida_funcs.get_func(_ea):
                    # Step 1: ensure bytes are marked as code
                    ida_ua.create_insn(_ea)
                    # Step 2: try add_func with automatic size
                    if not ida_funcs.add_func(_ea):
                        # Step 3: try with explicit end (find next func)
                        _next_ea = _ea + 4
                        while _next_ea < TEXT_END:
                            if ida_funcs.get_func(_next_ea):
                                break
                            _next_ea += 1
                        ida_funcs.add_func(_ea, _next_ea)
                    ida_auto.auto_wait()
                _func = ida_funcs.get_func(_ea)
                if _func and _func.size() > 1:
                    _name = ida_name.get_name(_ea) or _info.get('name', '')
                    targets.append((_ea, _name, _func.size()))
                    target_addrs.add(_ea)
                    _recovered += 1
                else:
                    _missing.append((_ea, _info.get('name', '')))
        if _recovered:
            log("[*] Recovered %d functions from annotations (not in Functions())" % _recovered)
        if _missing:
            log("[!] %d annotation functions could not be recovered:" % len(_missing))
            for _ea, _n in _missing[:10]:
                log("    0x%08X %s" % (_ea, _n))

        log('[S1-DIAG] before targets.sort: %.1fs' % (_t.time()-_T0))
        targets.sort()

        # ---- S1 射程过滤（2026-10-09）----
        # 病灶层三问：①层=export 的函数遍历（纯过滤不改语义）
        #            ②消费者=codegen.py 读 asm/pal3/decomp/*.json
        #            ③报错还缺什么=无（地址/类名经环境变量显式传入）
        # 设计要点 3：只射程「函数反编译」这一步（148.5s 的大头）；
        # 非函数产物（ida_structs.json、_globals）保持全量。
        _sc_func = os.environ.get('EXPORT_FUNC')
        _sc_class = os.environ.get('EXPORT_CLASS')
        _sc_out = os.environ.get('EXPORT_OUTDIR')
        if _sc_func or _sc_class:
            try:
                from pipeline.gen.stages.scoped_targets import resolve_targets, scoped_decomp_dir
            except Exception as _e:
                log("[S1] scoped export unavailable: %s" % _e)
                resolve_targets = None
            if resolve_targets is not None:
                _addrs = None
                if _sc_func:
                    _addrs = {int(_sc_func, 16)} if _sc_func.startswith('0x') or _sc_func[:1].isdigit() else None
                    if _addrs is None:
                        _addrs = {int(x, 16) for x in _sc_func.split(',') if x.strip()}
                _want = resolve_targets(_addrs, _sc_class)
                _before = len(targets)
                targets = [t for t in targets if t[0] in _want]
                log("[S1] scoped export: %d -> %d targets (func=%s class=%s)"
                    % (_before, len(targets), _sc_func, _sc_class))
                if _sc_out:
                    _d = scoped_decomp_dir(_sc_out)
                    _d.mkdir(parents=True, exist_ok=True)
                    globals()['DECOMP_DIR'] = _d    # 兼容（emit_headers 侧用）
                    globals()['OUTPUT_DIR'] = str(_d)  # 🔴 关键：写入点 :658 用的是 OUTPUT_DIR 而非 DECOMP_DIR
                    globals()['LOG_FILE'] = os.path.join(str(_d), '_export.log')
                    log("[S1] scoped decomp dir -> %s" % _d)
                    log("[S1-DIAG] module DECOMP_DIR now = %r" % (globals().get('DECOMP_DIR'),))
                    import sys as _s
                    _mod = _s.modules[__name__] if __name__ in _s.modules else None
                    log("[S1-DIAG] module obj DECOMP_DIR = %r" % (getattr(_mod, 'DECOMP_DIR', 'NO-MODULE'),))

        opt = PAL3Optimizer()
        opt.install()
        log("[*] Microcode optimizer installed")

        named = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] Targets: %d (named: %d, sub_: %d)" % (len(targets), named, len(targets)-named))

        _T_DECOMP = _t.time()
        log('[S1-DIAG] decompile loop start: %.1fs (非函数产物+准备耗时)' % (_T_DECOMP-_T0))
        exported = 0
        t0 = time.time()
        for i, (ea, name, size) in enumerate(targets):
            if (i+1) % 1000 == 0:
                log("  [%d/%d]" % (i+1, len(targets)))
            try:
                # Clear Hex-Rays cache if requested (needed after apply_annotations changes types)
                if FORCE_REFRESH:
                    try:
                        ida_hexrays.mark_cfunc_dirty(ea)
                    except:
                        pass
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    # Retry without dirty mark
                    cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    log("[!] SKIP 0x%08X %s: decompile returned None" % (ea, name[:50]))
                    continue


                # Restore user lvar settings (index-based: deterministic order)
                try:
                    lvinf = ida_hexrays.lvar_uservec_t()
                    ida_hexrays.restore_user_lvar_settings(lvinf, ea)
                    for i, lv in enumerate(cfunc.lvars):
                        if i < lvinf.lvvec.size() and lvinf.lvvec[i].name:
                            lv.name = lvinf.lvvec[i].name
                except:
                    pass

                # lvar 注解应用（2026-09-25）：注解决定论——restore（IDB 交互态）
                # 之后应用 ⇒ 注解优先级最高（复核 R1：restore 按索引覆盖 name 会
                # 静默覆盖注解 name）。渲染前按注解设置局部变量的 name/type
                _ann_lvars = _LVAR_ANN.get('0x%08X' % ea)
                if _ann_lvars:
                    _applied = 0
                    for _spec in _ann_lvars:
                        # 单条 spec 的任何异常只丢弃该条，绝不传染函数导出
                        #（2026-09-25 事故：vdloc_t.reg() 不存在 ⇒ FindInOpen 整函数消失）
                        try:
                            if not isinstance(_spec, dict):
                                continue
                            for _lv in cfunc.lvars:
                                _hit = False
                                if 'stkoff' in _spec and _lv.location.is_stkoff():
                                    _hit = (_lv.location.stkoff() == int(_spec['stkoff']))
                                elif 'reg' in _spec and _lv.location.is_reg():
                                    # vdloc_t 无 regidx()（2026-09-25 事故遗留死代码，
                                    # 2026-09-26 FPU 探针实证）——真实 API 是 reg1()
                                    # （mreg_t；x87 st0-st7 = 160..175，st7=172）。
                                    _hit = (str(_lv.location.reg1()) == str(_spec['reg']))
                                elif 'name' in _spec and 'stkoff' not in _spec and 'reg' not in _spec:
                                    # 寄存器变量按名匹配（2026-09-26）：同一 reg1 被
                                    # Hex-Rays 顺序复用（st7 上 v3/v4/v7…多个变量），
                                    # reg 键会命中第一个并 break ⇒ 注错对象
                                    #（SceneProp CalculateWorldPos 事故）。函数内名唯一。
                                    _hit = (_lv.name == _spec['name'])
                                if _hit:
                                    if _spec.get('name'):
                                        _lv.name = _spec['name']
                                    if _spec.get('type'):
                                        import ida_typeinf as _ti
                                        _tif = _ti.tinfo_t()
                                        if _ti.parse_decl(_tif, _ti.get_idati(),
                                                          '%s __lv_ann;' % _spec['type'],
                                                          _ti.PT_SIL):
                                            if _lv.set_lvar_type(_tif):
                                                _applied += 1
                                            else:
                                                log("[!] lvar type set rejected @%08X %s: %s"
                                                    % (ea, _lv.name, _spec['type']))
                                        else:
                                            log("[!] lvar type parse failed @%08X: %r"
                                                % (ea, _spec['type']))
                                    elif _spec.get('name'):
                                        _applied += 1
                                    break
                        except Exception as _se:
                            log("[!] lvar ann spec failed @%08X %s: %s" % (
                                ea, json.dumps(_spec), _se))
                    log("  [lvar] %08X: %d/%d applied" % (ea, _applied, len(_ann_lvars)))
                code = str(cfunc)
                code = resolve_orphan_ordinals(code)
                code = _normalize_ida_type(code)
                sig = cfunc.type.dstr()
                sig = resolve_orphan_ordinals(sig)
                sig = _normalize_ida_type(sig)
                # Fix Hex-Rays ecx register elision: 'ClassName *vN; // ecx' where
                # vN is actually 'this' (assignment elided by Hex-Rays optimizer).
                # Only fix when vN is typed as the current class and never assigned.
                _m = re.search(r'(?:struct\s+)?(\w+)\s*\*\s*this\b', sig)
                if _m:
                    _cls = _m.group(1)
                    _ecx_vars = set(re.findall(
                        r'^\s*' + re.escape(_cls) + r'\s*\*\s*(\w+)\s*;\s*//\s*ecx',
                        code, re.MULTILINE
                    ))
                    for _v in _ecx_vars:
                        if not re.search(r'\b' + re.escape(_v) + r'\s*=', code):
                            code = re.sub(r'\b' + re.escape(_v) + r'\b', 'this', code)
                if ea in _virtual_addrs and not sig.startswith('virtual '):
                    sig = 'virtual ' + sig
                demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else name
                # Expose missing class attribution: inject ClassName:: from vtable data.
                # This triggers C2673 in .cpp bodies that call these as free functions —
                # those are real bugs that need IDA-side re-annotation.
                if '::' not in display_name and ea in _addr_to_class:
                    display_name = '%s::%s' % (_addr_to_class[ea], display_name)
                safe = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
                safe = safe.replace('*', '_').replace(' ', '_').replace('?', '_')
                safe = safe.replace('@', '_').replace('$', '_').replace(',', '_')
                safe = safe.replace('(', '').replace(')', '').replace('/', '_')
                safe = safe.replace('"', '').replace("'", '').replace('\\', '_')
                while '__' in safe: safe = safe.replace('__', '_')
                safe = safe.strip('_')
                if len(safe) > 100: safe = safe[:100]
                filename = '%s_%08x.json' % (safe, ea)

                # Collect local variable info (both stack and register variables)
                lvar_info = []
                try:
                    for lvar in cfunc.lvars:
                        try:
                            loc = lvar.location
                            type_str = lvar.type().dstr() if lvar.type() else ""
                            type_str = resolve_orphan_ordinals(type_str)
                            entry = {
                                "name": lvar.name,
                                "type": type_str,
                            }
                            if loc.is_stkoff():
                                entry["stack_offset"] = loc.stkoff()
                            elif loc.is_reg():
                                # vdloc_t 真实 API 是 reg1()（见上 lvar 应用处注释）
                                entry["register"] = loc.reg1()
                            lvar_info.append(entry)
                        except:
                            # Skip individual problematic variables
                            pass
                except:
                    pass

                data = {'name': display_name, 'address': '0x%08X' % ea,
                        'size_bytes': size, 'signature': sig,
                        'decompiled_c': code}
                if lvar_info:
                    data['local_vars'] = lvar_info

                with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                    json.dump(data, f, indent=2, ensure_ascii=False)
                exported += 1
            except Exception as _e:
                log("[!] FAIL 0x%08X %s: %s" % (ea, name[:40], str(_e)[:60]))

        opt.remove()
        log("[*] Optimizer: %d vftable inits, %d compiler calls NOPed" % (opt.vftable_nops, opt.compiler_call_nops))

        log("[*] Exported: %d (%.1fs)" % (exported, time.time()-t0))

        # Export struct definitions from IDB (authoritative source for gen_headers)
        export_structs(log)

        # Report orphan ordinal stats
        if _orphan_stats:
            log("[*] Orphan ordinal replacements: %d unique ordinals" % len(_orphan_stats))
            top_orphans = sorted(_orphan_stats.items(), key=lambda x: -x[1])[:10]
            for ord_num, count in top_orphans:
                log("    #%d: %d occurrences" % (ord_num, count))
        else:
            log("[*] No orphan ordinals found")

        log("[*] Done")
    except Exception as e:
        log("[!] %s" % str(e))

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)


def _normalize_ida_type(t):
    """Normalize IDA type strings to VC6-compatible C types."""
    t = t.replace('unsigned __int32', 'unsigned int')
    t = t.replace('signed __int32', 'int')
    t = t.replace('__int32', 'int')  # bare __int32 (after signed/unsigned handled)
    return t



# [named 顶替 synthetic 2026-10-17 analyzer] 治本规则：annotation 具名实体与已有具名替身的
# _inline_/$ 合成名不再导出 —— 消除「具名实体 + 合成名」双源并存发射（C2011 型重定义 921 根因：
# ida_structs ∩ annotation 具名 = 858 同名交集双发射实证）。A 级证据：probe_census C2011 直方
# （PtrArray/UIWnd/… 重定义）+ 858 交集计数。
_ANNOT_NAMED_CACHE = None
_SYNTH_SUBST_CACHE = None

def _named_supersede_decision(type_name, named_types, substitutes):
    """named 顶替跳过决策（纯函数，R15 单测点）——[task-8 修 2026-10-19]。

    原 BUG：named 分支 `continue` 写反——named 实体被跳过（应导出）·
    synthetic 保留（应跳过）。正置：**synthetic 被具名替身顶替才跳过**；
    named 实体=权威名 ⇒ 导出。
    返回 (skip: bool, reason: str)。
    """
    if not type_name:
        return (False, 'empty name')
    subst = substitutes or {}
    # [P0-B 修 2026-10-19] 分隔符归一：映射键 `::<$hash>` 形 vs 实名 `__<$hash>` 形
    # **分隔符不匹配致查表永不命中**（C2011 双产根因 ✓ _inline_PalScript_m_RoleSlotArray
    # ×214）——归一双向（::\$ ↔ __\$）后查表。
    def _norm_sep(nm):
        return (nm or '').replace('::$', '__$')
    _tn = _norm_sep(type_name)
    _lookup = { _norm_sep(k): v for k, v in subst.items() }
    # 精确 + **前缀容错**（_origin 键=截断 hash vs 实名全 hash ✗✗ 第三重不匹配——
    # prefix 匹配覆盖截断形 ✓ P0-B 根治）
    if _tn in _lookup:
        return (True, 'synthetic %s superseded by named %s' % (type_name, _lookup[_tn]))
    # [R85 修 2026-10-23·export 不对称根因] 收紧 prefix 匹配
    # 真机制（对抗复核 17495e5f）：_k.startswith(_tn) 让内层变体替身键
    # （_inline_X::$C73B...）把基 union _inline_X（864B）也误顶替
    # 修：prefix 仅限 __$hash 后缀形（基名须精确同名替身才 skip）
    for _k, _v in _lookup.items():
        # 只匹配 __$hash 后缀形（如 _inline_X__C73B... 匹配 _inline_X）
        if _tn.startswith(_k) and _tn[len(_k):].startswith('__$'):
            return (True, 'synthetic %s superseded by named %s (hash-suffix)'
                    % (type_name, _v))
        # 反向：_k 是 _tn 的 hash-suffix 形（_k = _tn + __$hash）
        if _k.startswith(_tn) and _k[len(_tn):].startswith('__$'):
            return (True, 'synthetic %s superseded by named %s (hash-suffix-rev)'
                    % (type_name, _v))
    # [task-8 修·名形推导内置] `_inline_<Name>_` / `_inline_<Name>__\$<hash>` 形
    # ⇒ 候选 <Name>（双形试配 rstrip）——**具名确认判据**（候选在 named_types 才立）。
    # （源实证：_inline_SceneMgr_ 只存于 IDB 非注解 ⇒ 推导须在决策点（IDB 侧名）非注解扫描 ✗）
    m = re.match(r'^_inline_(.+?)(?:__\$[0-9A-Fa-f]+)?$', type_name or '')
    if m and named_types:
        for cand in (m.group(1), m.group(1).rstrip('_')):
            if cand in named_types:
                return (True, 'synthetic %s superseded by named %s (name-form derivation)'
                        % (type_name, cand))
    # named 实体**导出**（权威名——原 BUG 此处误 continue）
    return (False, 'export (named-or-unrelated)')


def _idb_named_types():
    """IDB TIL 具名类型集（**红线归位**：export 不读 annotation ✓ task-8 修 2026-10-19）。

    名源=IDB TIL named-types 枚举（ida_typeinf.get_named_types）——原
    _annotation_named_types 直读 data/annotations/structs/ ✗ 违 CLAUDE.md
    「export 不读 annotation」绝对禁令（reviewer 对抗复核问题 1）。非 IDA 环境
    （单测）⇒ 返回空集（决策走名形推导+具名确认降级 ✓）。
    """
    global _ANNOT_NAMED_CACHE
    if _ANNOT_NAMED_CACHE is None:
        names = set()
        try:
            import ida_typeinf
            til = ida_typeinf.get_idati()
            # named-types 全枚举（含 struct/union/typedef 等具名体）
            _idx = 0
            while True:
                _n = ida_typeinf.get_named_type_name(til, _idx) if hasattr(ida_typeinf, 'get_named_type_name') else None
                if _n is None:
                    break
                names.add(_n)
                _idx += 1
                if _idx > 200000:
                    break
        except Exception:
            names = set()
        _ANNOT_NAMED_CACHE = names
    return _ANNOT_NAMED_CACHE


def _annotation_named_types():
    """[task-8 修 2026-10-19·红线归位] 兼容别名 → _idb_named_types（不再读 annotation）。"""
    return _idb_named_types()

def _synthetic_named_substitutes():
    """合成名 -> 具名替身（annotation _origin 字段记录的去 inline 化映射）。"""
    global _SYNTH_SUBST_CACHE
    if _SYNTH_SUBST_CACHE is None:
        subst = {}
        st_dir = os.path.join(PROJECT_ROOT, 'data', 'annotations', 'structs')
        if os.path.isdir(st_dir):
            for fn in os.listdir(st_dir):
                if not fn.endswith('.json'):
                    continue
                try:
                    with open(os.path.join(st_dir, fn), encoding='utf-8') as fh:
                        j = json.load(fh)
                    orig = str(j.get('_origin') or '')
                    m = re.search(r'原合成名 ((?:_inline_\S+?|\S+?::\$\S+?))(?=[\s。；;，、）)]|$)', orig)
                    if m and j.get('name'):
                        subst[m.group(1)] = j['name']
                except Exception:
                    continue
        _SYNTH_SUBST_CACHE = subst
    return _SYNTH_SUBST_CACHE


def export_structs(log):
    """Export ALL types (structs, unions, enums) from IDB TIL to ida_structs.json.
    
    This is the authoritative export of the merged PDB+Annotations type system.
    Codegen reads ONLY this file — never raw PDB data.
    """
    structs_path = os.path.join(PROJECT_ROOT, "asm", "pal3", "ida_structs.json")
    result = {}
    enums = {}  # collected under result['_enums']
    struct_count = 0
    enum_count = 0
    skipped_count = 0
    # [Task4 导出补 _inline_·修向② 2026-10-23] 被 named-supersede 跳过的 `_inline_*`
    # 合成名留存池（IDB 权威形状）；被成员型实际引用者由 post-pass 复出（见下）。
    _retained_synth = {}

    # Load annotation struct data for vtables/methods pass-through
    # [t4-DECLARED-EXCEPTION] structs/*.json → ida_structs.json 的
    # vtables/methods/_variants 透传（实测 761/761 struct 与注解逐字段等值，
    # 即"注解的复制"，不是 IDB 状态的证据）＋ :582 的 _BYTE[] 类型回退。
    _ann_structs = {}
    _ann_dir = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")
    if os.path.isdir(_ann_dir):
        import json as _aj, glob as _agl
        for _af in _agl.glob(os.path.join(_ann_dir, "*.json")):
            try:
                with open(_af, encoding='utf-8') as _f:
                    _ad = _aj.load(_f)
                _ann_structs[_ad.get('name', '')] = _ad
            except:
                pass

    # Types that should never be exported (CRT, Windows SDK, etc.)
    SKIP_NAMES = {
        'std', 'stdiobuf', 'exception', 'type_info', 'filebuf', 'string',
        'strstreambuf', 'ios_base', 'facet', 'codecvt_base',
        '_ThrowInfo', '_CatchableType', '_CatchableTypeArray',
        '_s_ThrowInfo', '_s__ThrowInfo',
        'DOUBLE', 'FLOAT', 'INT', 'CHAR', 'VOID', 'LONG', 'SHORT', 'BOOL',
        'BYTE', 'WORD', 'DWORD', 'UINT', 'ULONG',
        'RECT', 'POINT', 'SIZE', 'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG',
        '_iobuf', 'FILE', '_GUID', 'GUID', 'IID',
        'HICON__', 'HWND__', 'HDC__', 'HINSTANCE__', 'HBRUSH__',
        'HHOOK__', 'HKEY__', 'HMONITOR__', 'HWAVEOUT__',
        'WNDCLASSA', 'tagWNDCLASSA', 'tagOFNA',
        '_FILETIME', '_SYSTEMTIME', '_MEMORYSTATUS', '_SECURITY_ATTRIBUTES',
        '_OSVERSIONINFOA', '_STARTUPINFOA', '_WIN32_FIND_DATAA',
        'CURRENCY', 'tagCY', 'CY',
    }
    SKIP_PREFIXES = ('D3D', '_D3D', 'ID3D', 'IDirect', 'IUnknown')
    # System types that are primitives — skip
    PRIMITIVE_NAMES = {
        'int', 'char', 'float', 'double', 'long', 'short', 'void',
        'unsigned', 'signed', 'bool', 'wchar_t',
        '__int8', '__int16', '__int32', '__int64',
        'unsigned __int8', 'unsigned __int16', 'unsigned __int32', 'unsigned __int64',
        '_BYTE', '_WORD', '_DWORD', '_QWORD', '_UNKNOWN',
    }

    def should_skip(name):
        if not name or name in PRIMITIVE_NAMES or name in SKIP_NAMES:
            return True
        if name.startswith(SKIP_PREFIXES):
            return True
        if name.startswith('$') or name.startswith('__'):
            return True
        if '<' in name or '`' in name:
            return True
        # Skip ordinal-only names like '#123'
        if name.startswith('#') or name.startswith('Ord'):
            return True
        return False

    til = ida_typeinf.get_idati()
    ordinal_limit = ida_typeinf.get_ordinal_limit(til)

    for ordinal in range(1, ordinal_limit):
        type_name = ida_typeinf.get_numbered_type_name(til, ordinal)
        if not type_name or should_skip(type_name):
            skipped_count += 1
            continue

        tif = ida_typeinf.tinfo_t()
        if not tif.get_numbered_type(til, ordinal):
            continue

        # --- ENUM export ---
        if tif.is_enum():
            evec = ida_typeinf.enum_type_data_t()
            if tif.get_enum_details(evec):
                values = {}
                for ei in range(evec.size()):
                    em = evec[ei]
                    values[em.name] = em.value
                enums[type_name] = {'values': values}
                enum_count += 1
            continue

        # --- STRUCT/UNION export ---
        if not tif.is_struct() and not tif.is_union():
            continue  # skip other types (typedefs, etc.)

        size = tif.get_size()
        _ann_cur = _ann_structs.get(type_name, {}) if isinstance(_ann_structs, dict) else {}
        if size <= 0 or size == 0xFFFFFFFFFFFFFFFF:
            # [i]-form 定案（apply 日志实证：get_size()==-1 但 members 全 pushed、readable layout）
            # —— annotation binary_size 权威回退（与 apply 同径），不再 continue 跳过。
            if _ann_cur.get('binary_size'):
                size = int(_ann_cur['binary_size'])
                log('  [ann-size-fallback] %s: get_size()=-1 → binary_size=%d（annotation 权威）' % (type_name, size))
            else:
                continue

        members = []
        udt = ida_typeinf.udt_type_data_t()
        if tif.get_udt_details(udt):
            for mi in range(udt.size()):
                um = udt[mi]
                mname = um.name if um.name is not None else '_field_%X' % (um.offset // 8)
                mtype_str = um.type.dstr() if um.type else 'int'
                # Normalize __int32 → int (VC6 treats them as distinct types)
                mtype_str = _normalize_ida_type(mtype_str)
                # TAUDT_FIXED with per-member union (same offset, multiple types)
                # can cause IDA to serialize some member types as _BYTE[]/_BYTE[1].
                # Fall back to annotation known_members for the correct type.
                if mtype_str in ('_BYTE[]', '_BYTE[1]', '_BYTE'):
                    _ann_members = _ann_structs.get(type_name, {}).get('known_members', {})
                    for _k, _v in _ann_members.items():
                        if _v.get('name') == mname and _v.get('type', '') != mtype_str:
                            mtype_str = _v['type']
                            break
                members.append({'name': mname, 'type': mtype_str, 'offset': um.offset // 8})
        if not members and _ann_cur.get('known_members'):
            # get_udt_details 读回失败（带成员函数 UDT 合法失败 / [i]-form）⇒ annotation 成员面权威回退
            for _k, _v in _ann_cur['known_members'].items():
                try:
                    _off = int(str(_k).split('_')[0])
                except Exception:
                    continue
                _t = _v.get('type', 'int')
                members.append({'name': _v.get('name', '_field_%X' % _off),
                                'type': _t if isinstance(_t, str) else 'int',
                                'offset': _off})
            if members:
                log('  [ann-members-fallback] %s: 读回 0 员 → annotation %d 员（权威回退）' % (type_name, len(members)))

        # Detect base classes from UDT members.
        #
        # ROOT CAUSE (fixed 2026-08-29): this used to infer "is this member a
        # base class?" from `umoffset == 0` (plus a name-based fallback for
        # 'baseclass'/'__parent' names), instead of asking IDA's own
        # udm_t.is_baseclass() flag. That heuristic is only correct for the
        # FIRST base class (offset 0); any additional base in a multi-
        # inheritance struct sits at a non-zero offset and was silently
        # reclassified as an anonymous inline-union/struct data member,
        # which emit_headers.py then rendered as an untyped struct field
        # (C2208 cascade). is_baseclass() is independent of offset/name and
        # is the authoritative signal — use it directly.
        # See docs/knowledge/gotcha_codegen_multi_inheritance_anon_member.md.
        kind = 'struct'
        if tif.is_union():
            kind = 'union'

        import udt_classify

        _udt_members_raw = []
        for mi in range(udt.size()):
            um = udt[mi]
            base_type = um.type.dstr() if um.type else ''
            for prefix in ('struct ', 'class '):
                if base_type.startswith(prefix):
                    base_type = base_type[len(prefix):]
            _udt_members_raw.append({
                'name': um.name or '',
                'offset': um.offset // 8,
                'type': base_type,
                'is_baseclass': um.is_baseclass(),
            })

        bases, filtered = udt_classify.classify_bases_and_members(_udt_members_raw, members, type_name)

        _entry = {
            'size': size,
            'kind': kind,
            'data_members': filtered,
            'bases': bases,
            # Pass through annotation vtables/methods for codegen
            'vtables': _ann_structs.get(type_name, {}).get('vtables', []),
            'methods': _ann_structs.get(type_name, {}).get('methods', {}),
            # Pass through _variants (union views) for codegen
            '_variants': _ann_structs.get(type_name, {}).get('known_members', {}),
        }
        # [named 顶替 synthetic·task-8 修 2026-10-19] 正置：synthetic 被具名替身
        # 顶替才跳过；named 实体=权威名 ⇒ 导出（原 named 分支 continue 写反 ✗ 已修）。
        # ⚠️ 边界注记：_annotation_named_types 读 annotation（export 不读 annotation
        # 边界待评估——本修仅正置跳过逻辑，读源迁移另册）。
        _skip, _reason = _named_supersede_decision(
            type_name, _annotation_named_types(), _synthetic_named_substitutes())
        if _skip:
            log('  [named-supersede] %s: %s' % (type_name, _reason))
            # [Task4 导出补 _inline_·修向② 2026-10-23] 合成名被顶替跳过 ⇒ 先留存
            # （不进 result）；被成员型**实际引用**时由循环后 [inline-supplement]
            # 复出。仅 `_inline_*` 形留存（含 `::$hash` 嵌套合成名，其键同样以
            # _inline_ 起）。未被引用者维持跳过（最小 churn，C2011 发射面不扩）。
            if type_name.startswith('_inline_'):
                _retained_synth[type_name] = _entry
            continue
        result[type_name] = _entry
        struct_count += 1

    # [Task4 导出补 _inline_·修向② 2026-10-23·对抗复核 3dbf35d2 定谳] 合成名对称复出。
    # 病灶：成员型引用 `_inline_<Cls>_<member>`（如 PalScript.m_RoleSlotArray →
    # `_inline_PalScript_m_RoleSlotArray`），named-supersede 把整类跳过 ⇒ ida_structs
    # 缺该键 ⇒ emit 走 `_emit_member` 字符串路（supersede 坍成具名单型）⇒ union
    # 变体层丢 ⇒ C2039（script_state ×19 + m_state ×17）。
    # 修法：被成员型**实际引用**的留存合成名复出（union/struct 全形状，IDB 权威），
    # 递归含其成员引用的 `::$hash` 嵌套合成名 ⇒ emit 走已 work 的 inline-UDT +
    # hoist 路（与 `_inline_RoleSystem_m_teamSlotsB`/`_inline_MUIDialog_m_btRc` 对称）。
    # 未被引用的合成名维持跳过（最小 churn）。纯 IDB 留存数据回填，不读 annotation ✓。
    def _collect_synth_refs(_t, _out):
        if isinstance(_t, str):
            for _nm in re.findall(r'_inline_[A-Za-z0-9_]+(?:::\$[0-9A-Fa-f]+)?', _t):
                _out.add(_nm)
    _referenced = set()
    for _e in result.values():
        if not isinstance(_e, dict):
            continue
        for _m in (_e.get('data_members') or []):
            if isinstance(_m, dict):
                _collect_synth_refs(_m.get('type', ''), _referenced)
    _queue = sorted(_referenced & set(_retained_synth))
    _supplemented = []
    while _queue:
        _nm = _queue.pop(0)
        if _nm in result:
            continue
        result[_nm] = _retained_synth[_nm]
        struct_count += 1
        _supplemented.append(_nm)
        for _m in (result[_nm].get('data_members') or []):
            if isinstance(_m, dict):
                _sub = set()
                _collect_synth_refs(_m.get('type', ''), _sub)
                for _r in sorted(_sub):
                    if _r not in result and _r in _retained_synth and _r not in _queue:
                        _queue.append(_r)
    if _supplemented:
        log('[inline-supplement] %d 个被引用合成名复出（修向② hoist 路）: %s'
            % (len(_supplemented), ', '.join(_supplemented)))

    # Attach enums as a special section
    if enums:
        result['_enums'] = enums

    # Export globals from the IDB (names and types set by apply_annotations.py)
    _globals = {}
    for _seg in range(idaseg.get_segm_qty()):
        _s = idaseg.getnseg(_seg)
        if not _s:
            continue
        _sclass = idaseg.get_segm_class(_s)
        if _sclass not in ('DATA', 'CONST', 'BSS'):
            continue
        _ea = _s.start_ea
        while _ea < _s.end_ea:
            _name = idc.get_name(_ea)
            if _name:
                # Skip non-C-identifier names: mangled C++ (??..., ?...@...),
                # decorated imports (...@...), RTTI data (__TI...), etc.
                # These are linker artifacts, not source-level global variables.
                if not re.match(r'^[A-Za-z_][A-Za-z0-9_]*$', _name):
                    _ea += 1
                    continue
                _type = idc.get_type(_ea)
                if _type:
                    _globals[hex(_ea)] = {'name': _name, 'type': _type}
                    _ea += idc.get_item_size(_ea)
                    continue
            _ea += 1
    if _globals:
        result['_globals'] = _globals

    # Mark anonymous .rdata globals as skip at export layer
    # (dword_/byte_/etc. names in .rdata are compiler-generated, not game globals)
    _RDATA_VA = 0x56A000
    _RDATA_END = 0x57F000
    _rdata_skip_names = ('dword_', 'byte_', 'word_', 'off_', 'stru_', 'unk_', 'flt_', 'asc_', 'a')
    for _a_s in list(result.get('_globals', {}).keys()):
        _addr = int(_a_s, 16) if isinstance(_a_s, str) else _a_s
        if _RDATA_VA <= _addr < _RDATA_END:
            _info = result['_globals'][_a_s]
            _name = _info.get('name', '')
            if _name.startswith(_rdata_skip_names):
                _info['type'] = 'skip'
                _info['skip_reason'] = 'rdata:compiler_generated'

    # Merge annotation-skipped globals into export (closing the annotation→export→codegen gap)
    # Two cases:
    # 1. Annotation entry has no name → skip the address regardless of IDB name
    # 2. Annotation entry has a name → only skip if name matches IDB name (avoid name mismatch)
    # [t4-DECLARED-EXCEPTION] globals.json 的 type=="skip"：apply 明确不把它写进 IDB
    # （apply:1710），故 IDB 无 skip 标记；实测 196 条注解 skip → 188 条落进
    # _globals 的 type=skip（另 620 条 skip 来自本文件的 .rdata 过滤）。
    _ann_path = os.path.join(os.path.dirname(structs_path), "..", "..", "data", "annotations", "globals.json")
    if os.path.exists(_ann_path):
        import json as _ann_json
        try:
            _ann_data = _ann_json.load(open(_ann_path, encoding='utf-8'))
            # Build address-keyed view of _globals for normalized matching
            _globals_by_addr = {}
            for _gk, _gv in _globals.items():
                _ga = int(_gk, 16) if isinstance(_gk, str) else _gk
                _globals_by_addr[_ga] = _gk
            for _a_s, _ainfo in _ann_data.items():
                if _ainfo.get('type') == 'skip':
                    _addr = int(_a_s, 16) if isinstance(_a_s, str) else int(_a_s, 0)
                    _ann_name = _ainfo.get('name', '')
                    _reason = _ainfo.get('reason', '') or 'annotation'
                    if _addr in _globals_by_addr:
                        _existing_name = _globals[_globals_by_addr[_addr]].get('name', '')
                        # Update as skip only if:
                        # - annotation has no name (skip the address regardless), OR
                        # - annotation name matches the existing global name
                        if not _ann_name or _ann_name == _existing_name:
                            _globals[_globals_by_addr[_addr]]['type'] = 'skip'
                            _globals[_globals_by_addr[_addr]]['skip_reason'] = _reason
                    elif _ann_name:
                        _globals[_a_s] = {'name': _ann_name, 'type': 'skip', 'skip_reason': _reason}
        except:
            pass

    # Export skip_functions.json names (non-thunk) as _skip_function_names metadata
    # so codegen knows which functions to exclude from forward declarations.
    # [t4-DECLARED-EXCEPTION] 实测导出 1816 个名字 == (1955 - 139 thunk) 的非 thunk
    # 名单（集合相等），下游消费者 pipeline/gen/data.py:188。
    _skip_funcs_path = os.path.join(os.path.dirname(structs_path), "..", "..", "data", "annotations", "skip_functions.json")
    if os.path.exists(_skip_funcs_path):
        try:
            _skip_data = _ann_json.load(open(_skip_funcs_path, encoding='utf-8'))
            _skip_names = []
            for _info in _skip_data.values():
                if _info.get('reason') == 'thunk':
                    continue
                _n = _info.get('name')
                if _n:
                    _skip_names.append(_n)
            result['_skip_function_names'] = {'_names': _skip_names}
        except:
            pass

    with open(structs_path, 'w', encoding='utf-8') as f:
        json.dump(result, f, indent=2, ensure_ascii=False)
    log("[*] Types exported: %d structs, %d enums (skipped %d) → ida_structs.json" %
        (struct_count, enum_count, skipped_count))

    # Validate: key structs must have data_members (0 members = TAUDT_FIXED/export bug)
    _critical_structs = ['SceneMgr', 'RoleSystem', 'CCBRoleState', 'CEffMgr']
    _zero_member = []
    for _cn in _critical_structs:
        _cm = result.get(_cn, {})
        _am = _ann_structs.get(_cn, {}) if isinstance(_ann_structs, dict) else {}
        # [named 顶替后门语义更新 2026-10-17] 具名实体由 annotation 权威承载（supersede 不再进
        # ida_structs）⇒ 双源皆空才算 0 员失效；任一源有成员即有效。
        if not _cm.get('data_members') and not _am.get('known_members'):
            # [幻影清账豁免 2026-10-17] CEffMgr 等成员全清系容器级幻影定谳（根容器=字符串表
            # A 级铁证）⇒ _phantom_clear 注记 = 故意空，非遗漏。
            if _am.get('_phantom_clear'):
                log('  [phantom-exempt] %s: _phantom_clear 注记（幻影清账故意空）——门豁免' % _cn)
            else:
                _zero_member.append(_cn)
    if _zero_member:
        log("[FATAL] %d critical structs have 0 exported members: %s" % (
            len(_zero_member), ', '.join(_zero_member)))
        log("[FATAL] This indicates TAUDT_FIXED or export failure. Fix struct annotations first.")
        import os as _os
        _os._exit(1)

if __name__ == '__main__':
    main()
    # S0（2026-10-09）：全量 export 末尾物化 decomp 派生的头决策事实
    log('[S1-DIAG] main() end: %.1fs total; decompile loop = %.1fs' % (_t.time()-_T0, _t.time()-_T_DECOMP if '_T_DECOMP' in dir() else -1))
    _write_header_facts_cache()
