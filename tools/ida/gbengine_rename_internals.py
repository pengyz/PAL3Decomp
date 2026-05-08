"""
IDAPython: gbengine.dll 内部函数命名

通过编译后的 .obj 文件字节匹配来识别 DLL 中的内部函数 (sub_XXXXXXXX)，
并在 IDA 中应用正确的 mangled name。

用法 (在 IDA 中执行):
    idat.exe -A -S"gbengine_rename_internals.py" gbengine.dll.i64

原理:
1. 解析 tools/vc6/*.obj 中所有外部函数符号及其字节
2. 对每个 sub_ 函数，比较前 N 字节 (跳过重定位位置)
3. 如果高置信度匹配 (>90% 非重定位字节相同)，则重命名

注意事项:
- 只匹配大于 16B 的函数 (避免太短的函数误报)
- 重定位位置 (4字节对齐的地址引用) 跳过比较
- 多重匹配时不重命名 (需要人工确认)
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_name
import idautils
import idc
import struct
import os
import json
import time
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
OBJ_DIR = os.path.join(PROJECT_ROOT, "tools", "vc6")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "gbengine_rename_log.txt")

MIN_FUNC_SIZE = 20
MATCH_THRESHOLD = 0.85


def parse_coff_obj(obj_path):
    """Parse COFF .obj file, return dict of symbol_name -> {bytes, size, relocs}."""
    with open(obj_path, 'rb') as f:
        data = f.read()

    machine = struct.unpack_from('<H', data, 0)[0]
    num_sections = struct.unpack_from('<H', data, 2)[0]
    sym_table_offset = struct.unpack_from('<I', data, 8)[0]
    num_symbols = struct.unpack_from('<I', data, 12)[0]
    opt_hdr_size = struct.unpack_from('<H', data, 16)[0]

    sections = []
    sec_offset = 20 + opt_hdr_size
    for i in range(num_sections):
        name_bytes = data[sec_offset:sec_offset+8]
        raw_size = struct.unpack_from('<I', data, sec_offset+16)[0]
        raw_offset = struct.unpack_from('<I', data, sec_offset+20)[0]
        reloc_offset = struct.unpack_from('<I', data, sec_offset+24)[0]
        num_relocs = struct.unpack_from('<H', data, sec_offset+32)[0]
        characteristics = struct.unpack_from('<I', data, sec_offset+36)[0]

        if name_bytes[0:1] == b'/':
            str_offset = int(name_bytes[1:].rstrip(b'\x00').decode('ascii'))
            str_table_offset = sym_table_offset + num_symbols * 18
            end = data.index(b'\x00', str_table_offset + str_offset)
            sec_name = data[str_table_offset + str_offset:end].decode('ascii')
        else:
            sec_name = name_bytes.rstrip(b'\x00').decode('ascii')

        sec_data = data[raw_offset:raw_offset+raw_size] if raw_offset > 0 else b''

        relocs = set()
        if num_relocs > 0 and reloc_offset > 0:
            for r in range(num_relocs):
                roff = reloc_offset + r * 10
                r_vaddr = struct.unpack_from('<I', data, roff)[0]
                for b in range(4):
                    relocs.add(r_vaddr + b)

        sections.append({
            'name': sec_name,
            'data': sec_data,
            'raw_size': raw_size,
            'characteristics': characteristics,
            'relocs': relocs,
        })
        sec_offset += 40

    str_table_offset = sym_table_offset + num_symbols * 18
    symbols = []
    i = 0
    while i < num_symbols:
        sym_offset = sym_table_offset + i * 18
        name_field = data[sym_offset:sym_offset+8]
        value = struct.unpack_from('<I', data, sym_offset+8)[0]
        sec_num = struct.unpack_from('<h', data, sym_offset+12)[0]
        sym_type = struct.unpack_from('<H', data, sym_offset+14)[0]
        storage_class = data[sym_offset+16]
        num_aux = data[sym_offset+17]

        if name_field[0:4] == b'\x00\x00\x00\x00':
            str_off = struct.unpack_from('<I', name_field, 4)[0]
            end = data.index(b'\x00', str_table_offset + str_off)
            sym_name = data[str_table_offset + str_off:end].decode('ascii', errors='replace')
        else:
            sym_name = name_field.rstrip(b'\x00').decode('ascii', errors='replace')

        symbols.append({
            'name': sym_name,
            'value': value,
            'section': sec_num,
            'type': sym_type,
            'storage_class': storage_class,
        })
        i += 1 + num_aux

    functions = {}
    for sym in symbols:
        if sym['section'] <= 0:
            continue
        sec_idx = sym['section'] - 1
        if sec_idx >= len(sections):
            continue
        sec = sections[sec_idx]
        if not (sec['characteristics'] & 0x20):
            continue
        if sym['storage_class'] == 2 and (sym['type'] & 0x20):
            functions[sym['name']] = {
                'section_idx': sec_idx,
                'offset': sym['value'],
            }

    for name, info in functions.items():
        sec_idx = info['section_idx']
        offset = info['offset']
        sec = sections[sec_idx]

        next_offset = sec['raw_size']
        for other_name, other_info in functions.items():
            if other_info['section_idx'] == sec_idx and other_info['offset'] > offset:
                if other_info['offset'] < next_offset:
                    next_offset = other_info['offset']

        size = next_offset - offset
        info['size'] = size
        info['bytes'] = sec['data'][offset:offset+size]
        info['relocs'] = set()
        for r in sec['relocs']:
            rel_off = r - offset
            if 0 <= rel_off < size:
                info['relocs'].add(rel_off)

    return functions


def get_func_bytes(ea, size):
    """Read function bytes from IDA database."""
    return ida_bytes.get_bytes(ea, size)


def compare_func(compiled_bytes, compiled_relocs, ida_bytes_data, ida_size):
    """Compare compiled bytes against IDA bytes, skipping relocations.
    Returns match ratio (0.0 - 1.0)."""
    compare_len = min(len(compiled_bytes), ida_size)
    if compare_len < MIN_FUNC_SIZE:
        return 0.0

    matches = 0
    compared = 0
    for i in range(compare_len):
        if i in compiled_relocs:
            matches += 1
            compared += 1
        else:
            compared += 1
            if compiled_bytes[i] == ida_bytes_data[i]:
                matches += 1

    if compared == 0:
        return 0.0
    return matches / compared


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] gbengine.dll 内部函数命名脚本")
        log(f"[*] OBJ 目录: {OBJ_DIR}")

        # Step 1: Collect all sub_ functions from IDA
        sub_funcs = {}
        named_funcs = set()
        for ea in idautils.Functions():
            name = ida_name.get_name(ea) or ""
            func = ida_funcs.get_func(ea)
            if not func:
                continue
            if name.startswith("sub_"):
                sub_funcs[ea] = func.size()
            elif name and not name.startswith("nullsub_"):
                named_funcs.add(name)

        log(f"[*] IDA 中 sub_ 函数: {len(sub_funcs)}")
        log(f"[*] IDA 中已命名函数: {len(named_funcs)}")

        # Step 2: Parse all .obj files
        all_obj_funcs = {}  # mangled_name -> {bytes, size, relocs, obj_file}
        obj_files = [f for f in os.listdir(OBJ_DIR) if f.endswith('.obj')]
        for obj_file in sorted(obj_files):
            obj_path = os.path.join(OBJ_DIR, obj_file)
            try:
                funcs = parse_coff_obj(obj_path)
                for mangled, info in funcs.items():
                    if info['size'] >= MIN_FUNC_SIZE:
                        # Skip if already named in IDA (already matched by export)
                        if mangled in named_funcs:
                            continue
                        all_obj_funcs[mangled] = {
                            'bytes': info['bytes'],
                            'size': info['size'],
                            'relocs': info['relocs'],
                            'obj_file': obj_file,
                        }
            except Exception as e:
                log(f"  [WARN] 解析失败 {obj_file}: {e}")

        log(f"[*] OBJ 中待匹配函数: {len(all_obj_funcs)}")

        # Step 3: For each sub_ function, try to match against .obj functions
        renamed = 0
        ambiguous = 0
        t0 = time.time()

        # Pre-read all sub_ function bytes
        sub_bytes_cache = {}
        for ea, size in sub_funcs.items():
            b = get_func_bytes(ea, size)
            if b:
                sub_bytes_cache[ea] = b

        log(f"[*] 开始匹配 ({len(sub_bytes_cache)} sub_ vs {len(all_obj_funcs)} obj funcs)...")

        for mangled, obj_info in sorted(all_obj_funcs.items()):
            compiled_bytes = obj_info['bytes']
            compiled_relocs = obj_info['relocs']
            compiled_size = obj_info['size']

            candidates = []
            for ea, ida_size in sub_funcs.items():
                # Quick size filter: sizes should be within 20% or 32 bytes
                size_diff = abs(ida_size - compiled_size)
                if size_diff > max(compiled_size * 0.2, 32):
                    continue

                ida_data = sub_bytes_cache.get(ea)
                if not ida_data:
                    continue

                # Quick prefix check (first 4 non-reloc bytes)
                prefix_match = True
                checked = 0
                for i in range(min(8, len(compiled_bytes), len(ida_data))):
                    if i in compiled_relocs:
                        continue
                    if compiled_bytes[i] != ida_data[i]:
                        prefix_match = False
                        break
                    checked += 1
                    if checked >= 4:
                        break

                if not prefix_match:
                    continue

                # Full comparison
                ratio = compare_func(compiled_bytes, compiled_relocs, ida_data, ida_size)
                if ratio >= MATCH_THRESHOLD:
                    candidates.append((ea, ratio, ida_size))

            if len(candidates) == 1:
                ea, ratio, ida_size = candidates[0]
                # Apply the mangled name
                old_name = ida_name.get_name(ea)
                if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                    renamed += 1
                    demangled = idc.demangle_name(mangled, idc.get_inf_attr(idc.INF_SHORT_DN))
                    display = demangled if demangled else mangled
                    log(f"  [OK] 0x{ea:08X} {old_name} -> {display} ({ratio*100:.0f}%, {obj_info['obj_file']})")
                    # Remove from sub_funcs so it's not matched again
                    del sub_funcs[ea]
            elif len(candidates) > 1:
                ambiguous += 1
                if ambiguous <= 10:
                    addrs = [f"0x{c[0]:08X}({c[1]*100:.0f}%)" for c in candidates[:3]]
                    log(f"  [AMBIGUOUS] {mangled} -> {addrs}")

        elapsed = time.time() - t0
        log("")
        log("[*] 完成!")
        log(f"  重命名: {renamed}")
        log(f"  歧义(跳过): {ambiguous}")
        log(f"  耗时: {elapsed:.1f}s")

        # Save database
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
