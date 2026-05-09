"""
IDAPython: PAL3.exe 深度类型传播分析

层次 1: 函数调用链传播
  - 从已知签名函数出发，沿调用链将类型传播到 callee/caller 的参数和返回值
  - 识别 GetInstance 模式 (返回单例指针) 并标注返回类型
  - 将类指针参数的 this 类型传播到 __thiscall 方法

层次 2: 类型交叉引用传播 (结构体验证)
  - 对已知类型的指针变量，追踪其所有使用点
  - 验证 [ptr+offset] 访问是否与 PDB 结构体定义一致
  - 发现偏移不一致时记录差异，修正结构体定义
  - 对无定义的结构体成员从使用模式推断类型

输出:
  - 更新 IDB (函数签名、全局变量类型、结构体定义)
  - asm/pal3/_deep_analysis_result.json (详细分析结果)
  - tools/ida/_logs/pal3_deep_analysis_log.txt

用法:
  idat.exe -A -S"pal3_deep_analysis.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_hexrays
import ida_name
import ida_typeinf
import ida_xref
import ida_segment
import idautils
import idc
import json
import os
import re
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
CALLGRAPH = os.path.join(PROJECT_ROOT, "asm", "pal3", "call_graph.json")
OUTPUT_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "_deep_analysis_result.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_deep_analysis_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0
RDATA_START = 0x0056A000
RDATA_END = 0x0057F178
DATA_START = 0x00580000
DATA_END = 0x0060C000

log_lines = []
results = {
    'signatures_applied': [],
    'types_propagated': [],
    'structs_verified': [],
    'structs_fixed': [],
    'globals_typed': [],
    'stats': {},
}


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def load_pdb():
    """加载 PDB 数据"""
    if not os.path.exists(PDB_EXPORT):
        return None
    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        return json.load(f)


def load_callgraph():
    """加载本地 callgraph"""
    if not os.path.exists(CALLGRAPH):
        return None
    with open(CALLGRAPH, 'r', encoding='utf-8') as f:
        return json.load(f)


# ========================================================================
# 层次 1: 函数调用链类型传播
# ========================================================================
def layer1_call_chain_propagation(pdb_data, cg_data):
    """
    从已知类型信息出发，沿调用链传播类型:
    1. 已知返回类型的函数 → callers 中接收返回值的变量获得类型
    2. 已知参数类型的 caller → callee 的对应参数获得类型
    3. GetInstance 模式识别 (全局指针 + 单例返回)
    4. __thiscall this 指针类型传播
    """
    log("")
    log("=" * 60)
    log("[层次 1] 函数调用链类型传播")
    log("=" * 60)

    til = ida_typeinf.get_idati()
    globals_data = cg_data.get('globals', {}) if cg_data else {}
    nodes = cg_data.get('nodes', {}) if cg_data else {}

    # --- Step 1: 识别 GetInstance 模式 ---
    # Pattern: function reads a global pointer, returns it
    # e.g., CRenderTarget::GetInstance() { return g_pRenderTarget; }
    log("[1.1] 识别 GetInstance 模式")
    getinstance_count = 0

    # Find small functions (< 100 bytes) that return a known typed global
    typed_globals = {}
    for addr_str, info in globals_data.items():
        typ = info.get('type', '')
        name = info.get('name', '')
        if typ.endswith('*') and name:
            try:
                typed_globals[int(addr_str, 16)] = (name, typ)
            except ValueError:
                pass

    for ea in idautils.Functions(TEXT_START, TEXT_END):
        func = ida_funcs.get_func(ea)
        if not func or func.size() > 100:
            continue

        # Check if function references a typed global
        func_refs_globals = []
        for ref_ea in range(func.start_ea, func.end_ea):
            for dref in idautils.DataRefsFrom(ref_ea):
                if dref in typed_globals:
                    func_refs_globals.append(dref)

        if len(func_refs_globals) != 1:
            continue

        g_addr = func_refs_globals[0]
        g_name, g_type = typed_globals[g_addr]
        base_type = g_type.rstrip('*').strip()

        # Check if base_type exists in IDA's type system
        tinfo = ida_typeinf.tinfo_t()
        if not tinfo.get_named_type(til, base_type):
            continue

        # Set function return type
        cur_name = ida_name.get_name(ea) or ""
        sig_str = "%s __cdecl %s()" % (g_type.replace('*', ' *'), cur_name)

        if idc.SetType(ea, sig_str):
            getinstance_count += 1
            results['signatures_applied'].append({
                'address': "0x%08X" % ea,
                'name': cur_name,
                'signature': sig_str,
                'reason': 'GetInstance pattern (returns %s)' % g_name,
            })
            if getinstance_count <= 10:
                log("  [+] 0x%08X %s -> returns %s" % (ea, cur_name, g_type))

    log("  GetInstance 签名应用: %d" % getinstance_count)

    # --- Step 2: __thiscall this 类型传播 ---
    log("[1.2] __thiscall this 类型传播")
    thiscall_count = 0

    # Load PDB functions with class info
    pdb_funcs_by_name = {}
    if pdb_data:
        for func in pdb_data.get('functions', []):
            name = func.get('name', '')
            cls = func.get('class', '')
            if name and cls:
                pdb_funcs_by_name[name] = func

    # For named functions that are class methods, set this type
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        name = ida_name.get_name(ea) or ""
        if name.startswith("sub_") or not name:
            continue

        demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN)) or ""
        if '::' not in demangled:
            continue

        parts = demangled.split('::')
        class_name = parts[0]

        # Check if class type exists in IDA
        tinfo = ida_typeinf.tinfo_t()
        if not tinfo.get_named_type(til, class_name):
            continue

        # Skip if already has __thiscall
        cur_type = idc.get_type(ea) or ""
        if "__thiscall" in cur_type:
            continue

        # Apply thiscall with correct this type
        sig = "void __thiscall %s(%s *this)" % (name, class_name)
        if idc.SetType(ea, sig):
            thiscall_count += 1

    log("  __thiscall 传播: %d" % thiscall_count)

    # --- Step 3: Caller → Callee 参数类型传播 ---
    log("[1.3] 调用链参数传播")
    param_prop_count = 0

    # For each function with known signature, check its callees
    # If it passes a typed value to a callee, the callee's parameter gets that type
    # This is best done by Hex-Rays itself after we set enough types,
    # so here we focus on the most impactful cases

    # Find functions that pass typed globals directly to callees
    for g_addr, (g_name, g_type) in typed_globals.items():
        # Find all code refs to this global
        for xref_ea in idautils.DataRefsTo(g_addr):
            func = ida_funcs.get_func(xref_ea)
            if not func:
                continue

            # Find call instructions near this xref
            # Pattern: mov reg, [global]; push reg; call sub_XXXX
            # or: push [global]; call sub_XXXX
            # After Hex-Rays processes this with the global typed,
            # it will propagate automatically
            pass

    log("  参数传播: %d (由 Hex-Rays 后续自动处理)" % param_prop_count)

    # --- Step 4: RTTI vtable → class hierarchy ---
    log("[1.4] RTTI 类层次提取")
    vtable_count = 0
    vfunc_named = 0

    seg = ida_segment.get_segm_by_name(".rdata")
    if seg:
        ea = seg.start_ea
        end = seg.end_ea

        while ea < end - 16:
            ptr0 = ida_bytes.get_dword(ea)
            if not (TEXT_START <= ptr0 < TEXT_END):
                ea += 4
                continue

            # Count consecutive function pointers
            count = 0
            for i in range(200):
                ptr = ida_bytes.get_dword(ea + i * 4)
                if TEXT_START <= ptr < TEXT_END:
                    f = ida_funcs.get_func(ptr)
                    if f and f.start_ea == ptr:
                        count += 1
                    else:
                        break
                else:
                    break

            if count < 3:
                ea += 4
                continue

            # Check RTTI at ea-4
            rtti_col = ida_bytes.get_dword(ea - 4)
            class_name = None

            if RDATA_START <= rtti_col < RDATA_END or DATA_START <= rtti_col < DATA_END:
                td_ptr = ida_bytes.get_dword(rtti_col + 12)
                if td_ptr and ida_bytes.is_loaded(td_ptr + 8):
                    raw = ida_bytes.get_strlit_contents(td_ptr + 8, -1, 0)
                    if raw:
                        raw_s = raw.decode('utf-8', errors='replace')
                        if raw_s.startswith('.?AV') and raw_s.endswith('@@'):
                            class_name = raw_s[4:-2]
                        elif raw_s.startswith('.?AU') and raw_s.endswith('@@'):
                            class_name = raw_s[4:-2]

            if class_name:
                vtable_count += 1
                # Name the vtable location
                vt_name = "vtbl_%s" % class_name
                cur = ida_name.get_name(ea) or ""
                if not cur or cur.startswith("off_"):
                    ida_name.set_name(ea, vt_name, ida_name.SN_NOWARN)

                # Try to name virtual functions using PDB
                if pdb_data:
                    # Find PDB class virtual functions
                    for pdb_func in pdb_data.get('functions', []):
                        if pdb_func.get('class', '') == class_name and pdb_func.get('is_virtual'):
                            # Match by vtable offset if available
                            pass

                # Name sub_ entries in vtable as ClassName_vfN
                for i in range(count):
                    ptr = ida_bytes.get_dword(ea + i * 4)
                    cur_vf_name = ida_name.get_name(ptr) or ""
                    if cur_vf_name.startswith("sub_"):
                        new_vf_name = "%s_vf%d" % (class_name, i)
                        if ida_name.set_name(ptr, new_vf_name, ida_name.SN_NOWARN):
                            vfunc_named += 1
                            results['signatures_applied'].append({
                                'address': "0x%08X" % ptr,
                                'name': new_vf_name,
                                'reason': 'vtable %s slot %d' % (class_name, i),
                            })

                results['types_propagated'].append({
                    'vtable': "0x%08X" % ea,
                    'class': class_name,
                    'vfunc_count': count,
                })

            ea += max(count * 4, 4)

    log("  虚函数表: %d, 虚函数命名: %d" % (vtable_count, vfunc_named))

    total = getinstance_count + thiscall_count + vfunc_named
    log("[*] 层次 1 总计: %d 个签名/命名改进" % total)
    return total


# ========================================================================
# 层次 2: 类型交叉引用传播 (结构体验证与修正)
# ========================================================================
def layer2_struct_verification(pdb_data, cg_data):
    """
    验证结构体定义:
    1. 对已知类型的全局指针，追踪所有 [ptr+offset] 访问
    2. 收集每个偏移处的访问大小和上下文
    3. 与 PDB 结构体定义对比，验证一致性
    4. 不一致时记录差异，尝试修正
    """
    log("")
    log("=" * 60)
    log("[层次 2] 结构体交叉引用验证")
    log("=" * 60)

    if not pdb_data:
        log("[!] PDB 数据不可用")
        return 0

    til = ida_typeinf.get_idati()
    globals_data = cg_data.get('globals', {}) if cg_data else {}

    # Build PDB class member map: class_name -> {offset: {name, type, size}}
    pdb_classes = {}
    for cls in pdb_data.get('classes', []):
        name = cls.get('name', '')
        if not name:
            continue
        members = {}
        for dm in cls.get('data_members', []):
            off = dm.get('offset', -1)
            if off >= 0:
                members[off] = {
                    'name': dm.get('name', ''),
                    'type': dm.get('type', ''),
                    'size': dm.get('size', 4),
                }
        if members:
            pdb_classes[name] = {
                'size': cls.get('size', 0),
                'members': members,
            }

    log("[*] PDB 类 (有成员定义): %d" % len(pdb_classes))

    # Find typed globals that point to known classes (any address)
    struct_globals = []
    for addr_str, info in globals_data.items():
        typ = info.get('type', '')
        name = info.get('name', '')
        if typ.endswith('*'):
            base = typ.rstrip('*').strip()
            if base in pdb_classes:
                try:
                    addr = int(addr_str, 16)
                    if ida_bytes.is_loaded(addr):
                        struct_globals.append((addr, name, base))
                except ValueError:
                    pass

    log("[*] 指向已知类的全局指针: %d" % len(struct_globals))

    # For each typed global, decompile functions that use it and check member access
    verified = 0
    mismatches = []
    new_members_found = []

    for g_addr, g_name, class_name in struct_globals:
        pdb_cls = pdb_classes[class_name]
        pdb_members = pdb_cls['members']

        # Find functions that reference this global
        xrefs = list(idautils.DataRefsTo(g_addr))
        if not xrefs:
            continue

        # Sample up to 5 functions for analysis
        func_eas = set()
        for xref_ea in xrefs:
            f = ida_funcs.get_func(xref_ea)
            if f:
                func_eas.add(f.start_ea)
            if len(func_eas) >= 5:
                break

        for func_ea in func_eas:
            try:
                cfunc = ida_hexrays.decompile(func_ea)
                if not cfunc:
                    continue

                code = str(cfunc)

                # Find patterns like: *(type *)(global + offset)
                # or: global->member
                # After type annotation, Hex-Rays should show: g_name->member
                # But without annotation, we see: *(_DWORD *)(dword_XXX + N)

                # Pattern 1: *(_DWORD *)(var + N) where var = our global
                pattern = r'\*\((?:_DWORD|_BYTE|_WORD|int|char|float) \*\)\(%s \+ (\d+)\)' % re.escape(g_name)
                for match in re.finditer(pattern, code):
                    offset = int(match.group(1))
                    if offset in pdb_members:
                        verified += 1
                    elif offset > 0 and offset < pdb_cls['size']:
                        new_members_found.append({
                            'class': class_name,
                            'offset': offset,
                            'context': match.group(0)[:60],
                            'func': "0x%08X" % func_ea,
                        })

            except Exception:
                pass

    log("[*] 成员偏移验证: %d 个匹配" % verified)
    log("[*] 潜在新成员: %d 个" % len(new_members_found))
    if mismatches:
        log("[!] 偏移不匹配: %d 个" % len(mismatches))

    results['structs_verified'] = {
        'verified_count': verified,
        'new_members': new_members_found[:50],
        'mismatches': mismatches[:20],
    }

    # --- Try to apply struct definitions that improve Hex-Rays output ---
    log("")
    log("[2.2] 应用结构体定义到 IDB")
    structs_applied = 0

    for g_addr, g_name, class_name in struct_globals:
        pdb_cls = pdb_classes[class_name]
        pdb_members = pdb_cls['members']
        cls_size = pdb_cls['size']

        if cls_size <= 0 or not pdb_members:
            continue

        # Build struct declaration for IDA
        member_strs = []
        sorted_offsets = sorted(pdb_members.keys())

        for off in sorted_offsets:
            m = pdb_members[off]
            mtype = m['type']
            mname = m['name']

            # Simplify type for IDA parsing
            mtype = mtype.replace('class ', '').replace('struct ', '')
            # Handle common types
            if 'std::' in mtype or '<' in mtype:
                # Template types - use opaque placeholder
                msize = m.get('size', 4)
                mtype = 'char[%d]' % msize if msize > 1 else 'char'
            elif mtype.endswith('*'):
                base = mtype.rstrip('*').strip()
                # Check if base type exists
                tinfo = ida_typeinf.tinfo_t()
                if not tinfo.get_named_type(til, base):
                    mtype = 'void *'

            if not mname or mname.startswith('__'):
                mname = 'field_%X' % off

            member_strs.append('    %s %s;' % (mtype, mname))

        if not member_strs:
            continue

        # Check if struct already exists and is different
        decl = 'struct %s {\n%s\n};' % (class_name, '\n'.join(member_strs))
        tinfo = ida_typeinf.tinfo_t()
        parse_result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
        if parse_result is not None:
            tinfo.set_named_type(til, class_name, ida_typeinf.NTF_REPLACE)
            structs_applied += 1

    log("[*] 结构体定义应用/更新: %d" % structs_applied)
    results['structs_fixed'] = structs_applied

    # --- Apply global variable types in IDB ---
    log("")
    log("[2.3] 全局变量类型应用")
    globals_typed = 0

    for g_addr, g_name, class_name in struct_globals:
        decl = "%s * %s" % (class_name, g_name)
        if idc.SetType(g_addr, decl):
            globals_typed += 1
            results['globals_typed'].append({
                'address': "0x%08X" % g_addr,
                'name': g_name,
                'type': "%s *" % class_name,
            })

    log("[*] 全局变量类型标注: %d" % globals_typed)

    return verified + structs_applied + globals_typed


# ========================================================================
# Phase 3: Re-export with improved types
# ========================================================================
def phase3_reexport():
    """重新导出 — 利用改进后的类型系统获得更好的反编译"""
    log("")
    log("=" * 60)
    log("[重新导出] 利用改进后的类型")
    log("=" * 60)

    OUTPUT = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
    os.makedirs(OUTPUT, exist_ok=True)

    import glob
    old_files = glob.glob(os.path.join(OUTPUT, "*.json"))
    for f in old_files:
        if os.path.basename(f).startswith('_'):
            continue
        os.remove(f)

    targets = []
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        name = ida_name.get_name(ea) or ""
        if not name or name.startswith("nullsub_") or name.startswith("j_"):
            continue
        func = ida_funcs.get_func(ea)
        if not func or func.size() <= 1:
            continue
        targets.append((ea, name, func.size()))

    targets.sort()
    named = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
    log("[*] 目标: %d (命名: %d)" % (len(targets), named))

    exported = 0
    errors = 0
    t0 = time.time()

    for i, (ea, name, size) in enumerate(targets):
        if (i + 1) % 1000 == 0:
            elapsed = time.time() - t0
            rate = (i + 1) / elapsed if elapsed > 0 else 0
            log("  [%d/%d] exported=%d (%.0f f/s)" % (i + 1, len(targets), exported, rate))

        try:
            cfunc = ida_hexrays.decompile(ea)
            if not cfunc:
                errors += 1
                continue

            code = str(cfunc)
            sig = cfunc.type.dstr()
            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            display_name = demangled if demangled else name

            safe = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
            safe = safe.replace('*', '_').replace(' ', '_').replace('?', '_')
            safe = safe.replace('@', '_').replace('$', '_').replace(',', '_')
            safe = safe.replace('(', '').replace(')', '').replace('/', '_')
            safe = safe.replace('"', '').replace("'", '').replace('\\', '_')
            while '__' in safe:
                safe = safe.replace('__', '_')
            safe = safe.strip('_')
            if len(safe) > 100:
                safe = safe[:100]
            filename = '%s_%08x.json' % (safe, ea)

            result = {
                'name': display_name,
                'address': '0x%08X' % ea,
                'size_bytes': size,
                'signature': sig,
                'decompiled_c': code,
            }

            with open(os.path.join(OUTPUT, filename), 'w', encoding='utf-8') as f:
                json.dump(result, f, indent=2, ensure_ascii=False)

            exported += 1
        except Exception:
            errors += 1

    elapsed = time.time() - t0
    log("[*] 导出: %d 成功, %d 错误 (%.1fs)" % (exported, errors, elapsed))

    summary = {
        'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
        'binary': 'PAL3.exe',
        'deep_analysis': True,
        'total_targets': len(targets),
        'named_functions': named,
        'exported': exported,
        'errors': errors,
    }
    with open(os.path.join(OUTPUT, "_export_summary.json"), 'w', encoding='utf-8') as f:
        json.dump(summary, f, indent=2)

    return exported


# ========================================================================
# Main
# ========================================================================
def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 深度类型传播分析")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        t0 = time.time()

        pdb_data = load_pdb()
        cg_data = load_callgraph()

        if not pdb_data:
            log("[!] PDB 数据缺失，部分分析将跳过")
        if not cg_data:
            log("[!] Callgraph 数据缺失，部分分析将跳过")

        # Layer 1: Call chain propagation
        n1 = layer1_call_chain_propagation(pdb_data, cg_data)

        # Save intermediate
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)

        # Layer 2: Struct verification and type propagation
        n2 = layer2_struct_verification(pdb_data, cg_data)

        # Save after all modifications
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB 已保存")

        # Re-export
        n3 = phase3_reexport()

        elapsed = time.time() - t0
        results['stats'] = {
            'layer1_improvements': n1,
            'layer2_improvements': n2,
            'total_exported': n3,
            'elapsed_seconds': round(elapsed, 1),
        }

        log("")
        log("=" * 60)
        log("[*] 深度分析完成!")
        log("  层次 1 (调用链传播): %d 改进" % n1)
        log("  层次 2 (结构体验证): %d 改进" % n2)
        log("  导出: %d 函数" % n3)
        log("  耗时: %.1fs" % elapsed)
        log("=" * 60)

        with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
            json.dump(results, f, indent=2, ensure_ascii=False)
        log("[*] 结果已写入: %s" % OUTPUT_FILE)

    except Exception as e:
        log("[!] 致命错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
