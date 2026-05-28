"""
IDAPython: Pure export - no modifications to IDB. Just export all functions.

Usage:
  idat.exe -A -S"pal3_export_only.py" original/PAL3.exe.i64
"""
import ida_auto, ida_funcs, ida_hexrays, ida_name, ida_typeinf, idautils, idc
import json, os, time, glob

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

        # Load skip list
        skip_addrs = set()
        skip_file = os.path.join(PROJECT_ROOT, "data", "annotations", "skip_functions.json")
        if os.path.exists(skip_file):
            import json as _json
            skip_data = _json.load(open(skip_file))
            skip_addrs = set(int(a, 16) for a in skip_data.keys())

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

                # Restore user lvar settings (index-based: lvar list order is deterministic)
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
                sig = cfunc.type.dstr()
                sig = resolve_orphan_ordinals(sig)
                demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else name
                safe = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
                safe = safe.replace('*', '_').replace(' ', '_').replace('?', '_')
                safe = safe.replace('@', '_').replace('$', '_').replace(',', '_')
                safe = safe.replace('(', '').replace(')', '').replace('/', '_')
                safe = safe.replace('"', '').replace("'", '').replace('\\', '_')
                while '__' in safe: safe = safe.replace('__', '_')
                safe = safe.strip('_')
                if len(safe) > 100: safe = safe[:100]
                filename = '%s_%08x.json' % (safe, ea)

                # Collect local variable info
                lvar_info = []
                try:
                    for lvar in cfunc.lvars:
                        loc = lvar.location
                        if loc.is_stkoff():
                            type_str = lvar.type().dstr() if lvar.type() else ""
                            type_str = resolve_orphan_ordinals(type_str)
                            lvar_info.append({
                                "name": lvar.name,
                                "type": type_str,
                                "stack_offset": loc.stkoff(),
                            })
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


def export_structs(log):
    """Export struct definitions from TIL (not IDB Structs - apply_annotations writes to TIL)."""
    import glob
    structs_path = os.path.join(PROJECT_ROOT, "asm", "pal3", "ida_structs.json")
    result = {}
    count = 0

    # Read struct names from annotations (authoritative source)
    ann_structs_dir = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")
    struct_names = []
    for f in glob.glob(os.path.join(ann_structs_dir, "*.json")):
        if os.path.basename(f).endswith('.disabled'):
            continue
        try:
            import json as _json
            with open(f, encoding='utf-8') as fp:
                sdata = _json.load(fp)
            sname = sdata.get('name', os.path.basename(f).replace('.json', ''))
            struct_names.append(sname)
        except:
            pass

    til = ida_typeinf.get_idati()
    for name in sorted(struct_names):
        stinfo = ida_typeinf.tinfo_t()
        if not stinfo.get_named_type(til, name):
            continue

        size = stinfo.get_size()
        if size <= 0 or size == 0xFFFFFFFFFFFFFFFF:
            continue

        members = []
        udt = ida_typeinf.udt_type_data_t()
        if stinfo.get_udt_details(udt):
            for mi in range(udt.size()):
                um = udt[mi]
                mname = um.name or '_field_%X' % (um.offset // 8)
                mtype_str = um.type.dstr() if um.type else 'int'
                members.append({'name': mname, 'type': mtype_str, 'offset': um.offset // 8})

        # Detect base class and type kind
        bases = []
        kind = 'struct'  # default
        # 检测实际类型kind
        if stinfo.is_union():
            kind = 'union'
        elif stinfo.is_struct():
            kind = 'struct'  # struct和class在IDA中都是is_struct()=true

        # Detect base classes from UDT members
        for mi in range(udt.size()):
            um = udt[mi]
            umname = um.name or ''
            if umname and ('baseclass' in umname.lower() or umname.startswith('__parent') or umname == ''):
                # Anonymous member = base class
                if umname == '' or 'baseclass' in umname.lower() or umname.startswith('__parent'):
                    base_type = um.type.dstr() if um.type else ''
                    for prefix in ('struct ', 'class '):
                        if base_type.startswith(prefix):
                            base_type = base_type[len(prefix):]
                    if base_type and base_type != name:
                        bases.append({'name': base_type, 'offset': um.offset // 8})

        # Filter out baseclass/vtable from members
        filtered = [m for m in members
                    if not any(x in m['name'].lower() for x in ('baseclass', '__parent', '__vftable', 'vtbl'))]

        result[name] = {
            'size': size,
            'kind': kind,
            'data_members': filtered,
            'bases': bases,
        }
        count += 1

    with open(structs_path, 'w', encoding='utf-8') as f:
        json.dump(result, f, indent=2, ensure_ascii=False)
    log("[*] Structs exported: %d → ida_structs.json" % count)

if __name__ == '__main__':
    main()
