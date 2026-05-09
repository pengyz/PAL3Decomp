"""
IDAPython: PAL3.exe 扩展匹配 - 利用新锚点继续

上一轮结果: 776/5508 命名 (14.1%)
新增锚点:
  - PAL3::Create (0x404800) 调用 sub_406310, sub_404FF0, sub_405330
  - PalScript 系列已全部命名
  - basedata.cpk → sub_401C70 (文件系统初始化)
  - .cpk → sub_401DF0

策略:
  1. 利用 PAL3::Create 的 callees 在 PDB 中已知的调用关系来匹配
  2. 扩展到 cbsystem.cpp, cbstagescene.cpp 等大文件
  3. 找到 CCBSystem, CCBStage 等核心类的锚点

运行环境: PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_name
import idautils
import idc
import json
import os
import struct
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_expand_match_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0
DATA_START = 0x00580000
DATA_END = 0x0060C000
RDATA_START = 0x0056A000
RDATA_END = 0x0057F178

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def get_func_size(ea):
    func = ida_funcs.get_func(ea)
    return func.end_ea - func.start_ea if func else 0


def get_callees_ordered(func_ea, text_bytes):
    func = ida_funcs.get_func(func_ea)
    if not func:
        return []
    callees = []
    seen = set()
    start_off = func.start_ea - TEXT_START
    end_off = func.end_ea - TEXT_START
    if start_off < 0 or end_off > len(text_bytes):
        return callees
    i = start_off
    while i < end_off - 4:
        if text_bytes[i] == 0xE8:
            rel = struct.unpack_from('<i', text_bytes, i + 1)[0]
            target = (TEXT_START + i + 5 + rel) & 0xFFFFFFFF
            if TEXT_START <= target < TEXT_END and target not in seen:
                callees.append(target)
                seen.add(target)
            i += 5
        else:
            i += 1
    return callees


def find_string_refs(text_bytes, data_bytes, rdata_bytes, search_str):
    """Find functions that reference a string."""
    if isinstance(search_str, str):
        search_bytes = search_str.encode('ascii')
    else:
        search_bytes = search_str
    results = set()
    for seg_bytes, seg_start in [(data_bytes, DATA_START), (rdata_bytes, RDATA_START)]:
        if not seg_bytes:
            continue
        pos = 0
        while True:
            pos = seg_bytes.find(search_bytes, pos)
            if pos == -1:
                break
            va = seg_start + pos
            needle = struct.pack('<I', va)
            tpos = 0
            while True:
                tpos = text_bytes.find(needle, tpos)
                if tpos == -1:
                    break
                code_ea = TEXT_START + tpos
                func = ida_funcs.get_func(code_ea)
                if func:
                    results.add(func.start_ea)
                tpos += 1
            pos += 1
    return sorted(results)


def try_order_match(pdb_sorted_funcs, idb_funcs, anchor_pdb_idx, anchor_idb_idx,
                    filename, size_ratio_min=0.25, size_ratio_max=4.0):
    """Try to match functions by order using an anchor point."""
    offset = anchor_idb_idx - anchor_pdb_idx
    matches = []

    # Calculate PDB sizes
    pdb_with_sizes = []
    for i, f in enumerate(pdb_sorted_funcs):
        addr = f.get('address', '0')
        if isinstance(addr, str):
            addr = int(addr, 16)
        if i + 1 < len(pdb_sorted_funcs):
            next_addr = pdb_sorted_funcs[i+1].get('address', '0')
            if isinstance(next_addr, str):
                next_addr = int(next_addr, 16)
            size = next_addr - addr
        else:
            size = 200
        pdb_with_sizes.append((f, size))

    for pdb_idx, (pdb_func, pdb_size) in enumerate(pdb_with_sizes):
        idb_idx = pdb_idx + offset
        if idb_idx < 0 or idb_idx >= len(idb_funcs):
            continue

        ea, idb_size, existing_name = idb_funcs[idb_idx]
        pdb_name = pdb_func['name']
        mangled = pdb_func.get('mangled_name', '')

        if not existing_name.startswith("sub_") and not existing_name.startswith("maybe_"):
            continue
        if not mangled:
            continue

        # Size check
        if pdb_size > 20 and idb_size > 20:
            ratio = float(idb_size) / pdb_size
            if ratio < size_ratio_min or ratio > size_ratio_max:
                continue

        matches.append((ea, pdb_name, mangled, pdb_idx, idb_size, pdb_size))

    return matches


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 扩展匹配")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        pdb_functions = pdb_data.get('functions', [])
        pdb_by_file = {}
        pdb_by_name = {}
        pdb_by_class = {}
        for func in pdb_functions:
            name = func.get('name', '')
            mangled = func.get('mangled_name', '')
            src = func.get('source_file', '')
            if name and mangled:
                pdb_by_name[name] = func
            if src:
                bn = os.path.basename(src).lower()
                if bn not in pdb_by_file:
                    pdb_by_file[bn] = []
                pdb_by_file[bn].append(func)
            if '::' in name:
                cls = name.split('::')[0]
                if cls not in pdb_by_class:
                    pdb_by_class[cls] = []
                pdb_by_class[cls].append(func)

        text_bytes = ida_bytes.get_bytes(TEXT_START, TEXT_END - TEXT_START)
        data_bytes = ida_bytes.get_bytes(DATA_START, DATA_END - DATA_START)
        rdata_bytes = ida_bytes.get_bytes(RDATA_START, RDATA_END - RDATA_START)

        if not text_bytes:
            log("[!] Cannot read .text")
            return

        applied = 0
        all_matches = []

        # ============================================================
        # Phase 1: Find more anchors using unique strings
        # ============================================================
        log("")
        log("[Phase 1] 寻找新锚点")

        # Strings that uniquely identify a source file or class
        anchor_searches = [
            # (string, expected_file, expected_class_method)
            ("cbsystem.cpp", "cbsystem.cpp", None),
            ("cbstage.cpp", "cbstage.cpp", None),
            ("cbstagescene.cpp", "cbstagescene.cpp", None),
            ("cbstagerole.cpp", "cbstagerole.cpp", None),
            ("cbstagecam.cpp", "cbstagecam.cpp", None),
            ("cbstageeffect.cpp", "cbstageeffect.cpp", None),
            ("cbui.cpp", "cbui.cpp", None),
            ("cb2deffect.cpp", "cb2deffect.cpp", None),
            ("cb3deffect.cpp", "cb3deffect.cpp", None),
            ("cbrolestate.cpp", "cbrolestate.cpp", None),
            ("effectsystem.cpp", "effectsystem.cpp", None),
            ("effmodel.cpp", "effmodel.cpp", None),
            ("loaddata.cpp", "loaddata.cpp", None),
            ("filesys.cpp", "filesys.cpp", None),
            ("palscript.cpp", "palscript.cpp", None),
            ("rendertarget.cpp", "rendertarget.cpp", None),
            ("uilistbox.cpp", "uilistbox.cpp", None),
            ("ui_textureinfo.cpp", "ui_textureinfo.cpp", None),
            ("encampment_scene.cpp", "encampment_scene.cpp", None),
        ]

        new_anchors = {}  # filename → [(func_ea, confidence), ...]
        for search_str, filename, _ in anchor_searches:
            funcs = find_string_refs(text_bytes, data_bytes, rdata_bytes, search_str)
            if funcs:
                unnamed = [ea for ea in funcs if (ida_name.get_name(ea) or "").startswith("sub_")]
                new_anchors[filename] = funcs
                log("    %s → %d funcs: %s" % (
                    search_str, len(funcs),
                    ['0x%X(%s)' % (ea, ida_name.get_name(ea) or '?') for ea in funcs[:5]]))

        # ============================================================
        # Phase 2: CBSystem via source path
        # ============================================================
        log("")
        log("[Phase 2] cbsystem.cpp 匹配")

        cbsystem_funcs = new_anchors.get('cbsystem.cpp', [])
        if cbsystem_funcs:
            # cbsystem.cpp in PDB
            pdb_cbsystem = sorted(pdb_by_file.get('cbsystem.cpp', []),
                                 key=lambda f: int(f['address'], 16)
                                 if isinstance(f.get('address'), str)
                                 else f.get('address', 0))
            log("[*] PDB cbsystem.cpp: %d functions" % len(pdb_cbsystem))

            # The functions referencing "cbsystem.cpp" are assert/error functions in that file
            # They give us anchors into the file's address range
            # Known range: 0x5125E0-0x515D10 (from Strategy 1 in advanced_match)
            cbsys_range_start = 0x5125E0
            cbsys_range_end = 0x5177B0  # before cbui.cpp

            idb_cbsys = []
            for ea in idautils.Functions(cbsys_range_start, cbsys_range_end):
                size = get_func_size(ea)
                name = ida_name.get_name(ea) or ""
                idb_cbsys.append((ea, size, name))
            log("[*] IDB cbsystem range: %d functions" % len(idb_cbsys))

            # Try to find an anchor: which cbsystem function references the source path?
            # The functions that reference "cbsystem.cpp" are likely assert-containing functions
            for anchor_ea in cbsystem_funcs:
                if cbsys_range_start <= anchor_ea < cbsys_range_end:
                    # Found an anchor in the right range
                    anchor_idb_idx = -1
                    for i, (ea, _, _) in enumerate(idb_cbsys):
                        if ea == anchor_ea:
                            anchor_idb_idx = i
                            break
                    if anchor_idb_idx >= 0:
                        log("[*] cbsystem.cpp anchor: 0x%08X at IDB[%d]" % (anchor_ea, anchor_idb_idx))
                        # Need to figure out which PDB function this is
                        # Look at what this function does (size, callees)
                        anchor_size = get_func_size(anchor_ea)
                        log("    Anchor size: %d" % anchor_size)
                        # Check PDB for functions of similar size
                        for i, f in enumerate(pdb_cbsystem):
                            addr = f.get('address', '0')
                            if isinstance(addr, str):
                                addr_int = int(addr, 16)
                            else:
                                addr_int = addr
                            if i + 1 < len(pdb_cbsystem):
                                next_addr = pdb_cbsystem[i+1].get('address', '0')
                                if isinstance(next_addr, str):
                                    next_addr = int(next_addr, 16)
                                else:
                                    next_addr = next_addr
                                pdb_size = next_addr - addr_int
                            else:
                                pdb_size = 0
                            # If this PDB function contains an assert with file path,
                            # it should reference "cbsystem.cpp"
                            # CCBSystem::Create is often the first large function
                        break

        # ============================================================
        # Phase 3: Use PAL3::Create's callee structure
        # ============================================================
        log("")
        log("[Phase 3] PAL3::Create 调用分析")

        # PAL3::Create (0x404800) calls:
        # sub_406310 (size=722), sub_404FF0 (size=786), sub_405330 (size=546) in pal3.cpp range
        # sub_4065F0 (size=249) - just outside pal3.cpp range
        # PalScript::Update (0x431FB0) - already matched
        # sub_53CF80, sub_401C70, etc.

        # In PDB, PAL3::Create calls:
        # PAL3::CreateGfxWindow, PAL3::InitGFX, PAL3::CreateEffectSystem
        # PDB sizes: CreateGfxWindow~X, InitGFX~1466, CreateEffectSystem~815
        # InitGFX is at PDB 0x427DB4 (after Create 0x427135, ~1700 bytes gap)
        # CreateEffectSystem at 0x428177 (after InitGFX, ~965 bytes gap)

        # pal3.cpp PDB order (starting from Create):
        # Create(0x427135), WinProc(0x427A0E), InitGFX(0x427DB4), CreateEffectSystem(0x428177),
        # DestroyEffectSystem(0x4284B0), Update(0x42855F), Render(0x428AAE), Destroy(0x42916E)

        # In IDB, pal3.cpp range functions:
        # 0x404800 (Create), 0x404D60, 0x404FF0, 0x405330, 0x4055A0, 0x4055D0, 0x405C00, 0x406230, 0x406310

        # PAL3::Create calls sub_406310, sub_404FF0, sub_405330 within pal3.cpp
        # In PDB, PAL3::Create calls CreateGfxWindow, InitGFX, CreateEffectSystem
        # CreateGfxWindow is PDB index 12 (after WinProc)
        # InitGFX is PDB index 13
        # CreateEffectSystem is PDB index 14

        # IDB pal3.cpp functions in order:
        pal3_idb = []
        for ea in idautils.Functions(0x404800, 0x406400):
            size = get_func_size(ea)
            name = ida_name.get_name(ea) or ""
            pal3_idb.append((ea, size, name))

        log("[*] pal3.cpp IDB 函数:")
        for ea, size, name in pal3_idb:
            log("    0x%08X size=%4d %s" % (ea, size, name[:50]))

        # PDB pal3.cpp sorted
        pdb_pal3 = sorted(pdb_by_file.get('pal3.cpp', []),
                         key=lambda f: int(f['address'], 16)
                         if isinstance(f.get('address'), str)
                         else f.get('address', 0))

        log("[*] PDB pal3.cpp 函数 (从 Create 开始):")
        create_pdb_idx = -1
        for i, f in enumerate(pdb_pal3):
            if f['name'] == 'PAL3::Create':
                create_pdb_idx = i
                break

        if create_pdb_idx >= 0:
            for i in range(create_pdb_idx, min(create_pdb_idx + 12, len(pdb_pal3))):
                f = pdb_pal3[i]
                addr = f.get('address', '0')
                log("    [%d] %s  %s" % (i, addr, f['name']))

        # IDB: Create is at index 0
        # PDB: Create is at index create_pdb_idx
        # The functions AFTER Create in both should align

        if create_pdb_idx >= 0 and len(pal3_idb) > 0:
            # anchor: Create = PDB[create_pdb_idx], IDB[0]
            matches = try_order_match(pdb_pal3, pal3_idb, create_pdb_idx, 0, 'pal3.cpp')
            log("[*] pal3.cpp order matches: %d" % len(matches))
            for ea, name, mangled, idx, idb_sz, pdb_sz in matches:
                if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                    applied += 1
                    all_matches.append({'addr': '0x%08X' % ea, 'name': name})
                    log("    MATCH: 0x%08X = %s (idb=%d, pdb=%d)" % (ea, name, idb_sz, pdb_sz))

        # ============================================================
        # Phase 4: Expand from PalScript to adjacent files
        # ============================================================
        log("")
        log("[Phase 4] PalScript 邻域 → palscriptwaitobj/palscriptidleobj")

        # PalScriptWaitObj and PalScriptIdleObj are in separate files per PDB
        # PalScriptWaitObj::~PalScriptWaitObj at PDB 0x44DEF0 (palscriptwaitobj.cpp?)
        # PalScriptIdleObj at PDB 0x4B2CC0-0x4B2DC0

        # Search for these in the IDB near PalScript area
        # PalScriptIdleObj functions in PDB:
        pdb_idle = [f for f in pdb_functions
                   if 'PalScriptIdleObj' in f.get('name', '')]
        log("[*] PDB PalScriptIdleObj functions:")
        for f in pdb_idle:
            log("    %s  %s" % (f.get('address', '?'), f['name']))

        pdb_wait = [f for f in pdb_functions
                   if f.get('name', '').startswith('PalScriptWaitObj')]
        log("[*] PDB PalScriptWaitObj functions:")
        for f in pdb_wait:
            log("    %s  %s" % (f.get('address', '?'), f['name']))

        # ============================================================
        # Phase 5: effectsystem.cpp matching
        # ============================================================
        log("")
        log("[Phase 5] effectsystem.cpp 匹配")

        effectsys_funcs = new_anchors.get('effectsystem.cpp', [])
        pdb_effectsys = pdb_by_file.get('effectsystem.cpp', [])
        if effectsys_funcs and pdb_effectsys:
            log("[*] effectsystem.cpp 引用: %s" % [hex(ea) for ea in effectsys_funcs])
            log("[*] PDB effectsystem.cpp: %d functions" % len(pdb_effectsys))
            for f in pdb_effectsys[:10]:
                log("    %s  %s" % (f.get('address', '?'), f['name']))

        # ============================================================
        # Phase 6: Match more CEffXxx files using file-internal structure
        # ============================================================
        log("")
        log("[Phase 6] 已匹配 CEffXxx 扩展")

        # effmodel.cpp has known reference
        effmodel_funcs = new_anchors.get('effmodel.cpp', [])
        pdb_effmodel = pdb_by_file.get('effmodel.cpp', [])
        if effmodel_funcs and pdb_effmodel:
            log("[*] effmodel.cpp 引用: %s" % [hex(ea) for ea in effmodel_funcs])
            log("[*] PDB effmodel.cpp: %d functions" % len(pdb_effmodel))

            # If only one function references effmodel.cpp, it's a strong anchor
            if len(effmodel_funcs) == 1:
                anchor_ea = effmodel_funcs[0]
                anchor_name = ida_name.get_name(anchor_ea) or ""
                log("    Unique anchor: 0x%08X %s" % (anchor_ea, anchor_name[:40]))

                # This anchor should correspond to one of the functions that have
                # assert/error with the file path
                # In PDB, which effmodel.cpp function would have an assert?
                # Typically Create() or a complex function
                pdb_effmodel_sorted = sorted(pdb_effmodel,
                                            key=lambda f: int(f['address'], 16)
                                            if isinstance(f.get('address'), str)
                                            else f.get('address', 0))
                log("    PDB effmodel.cpp:")
                for f in pdb_effmodel_sorted:
                    log("      %s  %s" % (f.get('address', '?'), f['name']))

        # ============================================================
        # Phase 7: loaddata.cpp (core data loading)
        # ============================================================
        log("")
        log("[Phase 7] loaddata.cpp 匹配")

        loaddata_funcs = new_anchors.get('loaddata.cpp', [])
        pdb_loaddata = pdb_by_file.get('loaddata.cpp', [])
        if loaddata_funcs and pdb_loaddata:
            log("[*] loaddata.cpp 引用: %s" % [hex(ea) for ea in loaddata_funcs])
            log("[*] PDB loaddata.cpp: %d functions" % len(pdb_loaddata))
            pdb_loaddata_sorted = sorted(pdb_loaddata,
                                        key=lambda f: int(f['address'], 16)
                                        if isinstance(f.get('address'), str)
                                        else f.get('address', 0))
            for f in pdb_loaddata_sorted[:10]:
                log("      %s  %s" % (f.get('address', '?'), f['name']))

        # ============================================================
        # Phase 8: rendertarget.cpp (only 1 reference)
        # ============================================================
        log("")
        log("[Phase 8] rendertarget.cpp 匹配")

        # RenderTarget::Create is already named (from earlier runs)
        # Check what's around it
        rt_ea = None
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if 'RenderTarget' in name:
                rt_ea = ea
                log("[*] RenderTarget found: 0x%08X %s" % (ea, name))
                break

        if rt_ea:
            pdb_rt = pdb_by_file.get('rendertarget.cpp', [])
            if pdb_rt:
                pdb_rt_sorted = sorted(pdb_rt,
                                      key=lambda f: int(f['address'], 16)
                                      if isinstance(f.get('address'), str)
                                      else f.get('address', 0))
                log("[*] PDB rendertarget.cpp: %d functions" % len(pdb_rt_sorted))
                for f in pdb_rt_sorted:
                    log("    %s  %s" % (f.get('address', '?'), f['name']))

                # Find RenderTarget::Create in PDB
                rt_pdb_idx = -1
                for i, f in enumerate(pdb_rt_sorted):
                    if 'Create' in f['name'] and 'RenderTarget' in f['name']:
                        rt_pdb_idx = i
                        break

                if rt_pdb_idx >= 0:
                    # Get IDB functions near RenderTarget
                    rt_range_start = rt_ea - 0x500
                    rt_range_end = rt_ea + 0x2000
                    idb_rt = []
                    for ea in idautils.Functions(max(TEXT_START, rt_range_start), min(TEXT_END, rt_range_end)):
                        size = get_func_size(ea)
                        name = ida_name.get_name(ea) or ""
                        idb_rt.append((ea, size, name))

                    rt_idb_idx = -1
                    for i, (ea, _, _) in enumerate(idb_rt):
                        if ea == rt_ea:
                            rt_idb_idx = i
                            break

                    if rt_idb_idx >= 0:
                        matches = try_order_match(pdb_rt_sorted, idb_rt,
                                                rt_pdb_idx, rt_idb_idx, 'rendertarget.cpp')
                        for ea, name, mangled, idx, idb_sz, pdb_sz in matches:
                            if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                                applied += 1
                                all_matches.append({'addr': '0x%08X' % ea, 'name': name})
                                log("    MATCH: 0x%08X = %s" % (ea, name))

        # ============================================================
        # Phase 9: filesys.cpp
        # ============================================================
        log("")
        log("[Phase 9] filesys.cpp")

        filesys_funcs = new_anchors.get('filesys.cpp', [])
        pdb_filesys = pdb_by_file.get('filesys.cpp', [])
        if filesys_funcs and pdb_filesys:
            log("[*] filesys.cpp 引用: %s" % [hex(ea) for ea in filesys_funcs])
            log("[*] PDB filesys.cpp: %d functions" % len(pdb_filesys))
            pdb_filesys_sorted = sorted(pdb_filesys,
                                       key=lambda f: int(f['address'], 16)
                                       if isinstance(f.get('address'), str)
                                       else f.get('address', 0))
            for f in pdb_filesys_sorted[:10]:
                log("      %s  %s" % (f.get('address', '?'), f['name']))

            # If single reference, try as anchor for first assert-containing function
            if len(filesys_funcs) == 1:
                anchor_ea = filesys_funcs[0]
                log("    Unique anchor: 0x%08X" % anchor_ea)
                # Determine neighborhood
                nearby = []
                for ea in idautils.Functions(anchor_ea - 0x2000, anchor_ea + 0x2000):
                    size = get_func_size(ea)
                    name = ida_name.get_name(ea) or ""
                    nearby.append((ea, size, name))
                log("    Nearby functions: %d" % len(nearby))

        # ============================================================
        # Summary
        # ============================================================
        log("")
        log("[*] === 总结 ===")
        named = sum(1 for ea in idautils.Functions(TEXT_START, TEXT_END)
                   if not (ida_name.get_name(ea) or "").startswith("sub_"))
        total = sum(1 for _ in idautils.Functions(TEXT_START, TEXT_END))
        log("[*] 命名: %d / %d (%.1f%%)" % (named, total, 100.0*named/total))
        log("[*] 本次新增: %d" % applied)
        if all_matches:
            log("[*] 匹配列表:")
            for m in all_matches:
                log("    %s = %s" % (m['addr'], m['name']))

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
