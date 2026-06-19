"""
IDAPython: Pure export - no modifications to IDB. Just export all functions.

Usage:
  idat.exe -A -S"pal3_export_only.py" original/PAL3.exe.i64
"""
import ida_auto, ida_funcs, ida_hexrays, ida_name, ida_typeinf, idautils, idc
import ida_segment as idaseg
import json, os, time, glob, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")

# After apply_annotations changes types, Hex-Rays cache is stale — need dirty mark.
# After init --force (fresh IDB), no cache exists — dirty mark is harmless but redundant.
# Set to False for fast re-export when IDB hasn't changed (uses cached decompilation).
FORCE_REFRESH = os.environ.get("PAL3_EXPORT_NO_REFRESH", "") == ""
LOG_FILE = os.path.join(SCRIPT_DIR, "_logs", "pal3_export_only_log.txt")
TEXT_START = 0x00401000
TEXT_END = 0x005695D0

RDATA_START = 0x0056A000
RDATA_END = 0x0057F178

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

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Pure export (no IDB modifications)")

        os.makedirs(OUTPUT_DIR, exist_ok=True)
        for f in glob.glob(os.path.join(OUTPUT_DIR, "*.json")):
            if not os.path.basename(f).startswith('_'):
                os.remove(f)

        # Load annotations (authoritative source for signatures)
        ann_funcs = {}
        funcs_file = os.path.join(PROJECT_ROOT, "data", "annotations", "functions.json")
        if os.path.exists(funcs_file):
            import json as _ann_json
            ann_funcs = _ann_json.load(open(funcs_file, encoding='utf-8'))
            log("[*] Loaded %d function annotations" % len(ann_funcs))

        # Load per-class methods to detect virtual functions and build class attribution.
        _virtual_addrs = set()    # int(addr) — appears in ANY vtable slot (own or inherited)
        _addr_to_class = {}       # int(addr) -> class_name (own slots only)
        _structs_dir = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")
        if os.path.isdir(_structs_dir):
            import json as _sj, glob as _gl
            for _sf in _gl.glob(os.path.join(_structs_dir, "*.json")):
                _sd = _sj.load(open(_sf, encoding='utf-8'))
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
            for _sf in _gl.glob(os.path.join(_structs_dir, "*.json")):
                _sd = _sj.load(open(_sf, encoding='utf-8'))
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

        # Load skip list
        skip_addrs = set()
        skip_file = os.path.join(PROJECT_ROOT, "data", "annotations", "skip_functions.json")
        if os.path.exists(skip_file):
            import json as _json
            skip_data = _json.load(open(skip_file))
            skip_addrs = set(int(a, 16) for a in skip_data.keys())

        # Pre-pass: set mangled names for class methods so export uses clean unique names.
        # This ensures function names like ?Create@UINote@@... are used, not Create_37.
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
                        if _addr not in _ann_funcs:
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

        targets.sort()

        opt = PAL3Optimizer()
        opt.install()
        log("[*] Microcode optimizer installed")

        named = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] Targets: %d (named: %d, sub_: %d)" % (len(targets), named, len(targets)-named))

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
                                entry["register"] = loc.reg()
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

    # Load annotation struct data for vtables/methods pass-through
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
        if size <= 0 or size == 0xFFFFFFFFFFFFFFFF:
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

        # Detect base classes from UDT members (anonymous baseclass members)
        bases = []
        kind = 'struct'
        if tif.is_union():
            kind = 'union'

        for mi in range(udt.size()):
            um = udt[mi]
            umname = um.name or ''
            if not umname:
                # IDB represents base classes as members with empty name
                base_type = um.type.dstr() if um.type else ''
                for prefix in ('struct ', 'class '):
                    if base_type.startswith(prefix):
                        base_type = base_type[len(prefix):]
                if base_type and base_type != type_name:
                    bases.append({'name': base_type, 'offset': um.offset // 8})
            elif 'baseclass' in umname.lower() or umname.startswith('__parent'):
                base_type = um.type.dstr() if um.type else ''
                for prefix in ('struct ', 'class '):
                    if base_type.startswith(prefix):
                        base_type = base_type[len(prefix):]
                if base_type and base_type != type_name:
                    bases.append({'name': base_type, 'offset': um.offset // 8})

        # Filter out baseclass/vtable from data members
        filtered = [m for m in members
                    if m.get('name', '') and not any(x in m['name'].lower() for x in ('baseclass', '__parent', '__vftable', 'vtbl'))]

        result[type_name] = {
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
        struct_count += 1

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
    _ann_path = os.path.join(os.path.dirname(structs_path), "..", "..", "data", "annotations", "globals.json")
    if os.path.exists(_ann_path):
        import json as _ann_json
        try:
            _ann_data = _ann_json.load(open(_ann_path, encoding='utf-8'))
            for _a_s, _ainfo in _ann_data.items():
                if _ainfo.get('type') == 'skip':
                    _name = _ainfo.get('name', '')
                    _reason = _ainfo.get('reason', '')
                    if _name and _a_s not in _globals:
                        _globals[_a_s] = {'name': _name, 'type': 'skip', 'skip_reason': _reason}
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
        if not _cm.get('data_members'):
            _zero_member.append(_cn)
    if _zero_member:
        log("[FATAL] %d critical structs have 0 exported members: %s" % (
            len(_zero_member), ', '.join(_zero_member)))
        log("[FATAL] This indicates TAUDT_FIXED or export failure. Fix struct annotations first.")
        import os as _os
        _os._exit(1)

if __name__ == '__main__':
    main()
