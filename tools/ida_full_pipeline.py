"""
IDAPython (IDA 9.x): 完整 pipeline - 导入类型 + 应用函数签名 + 高质量反编译

一个脚本完成所有步骤:
1. 导入 pal3a_types.h 中的结构体
2. 导入枚举
3. 为所有已命名函数设置正确的函数类型 (this 用结构体指针)
4. 清除 Hex-Rays 缓存
5. 反编译导出

用法:
  idat.exe -A -S"此脚本" "PAL3A.exe.i64"
"""

import json
import os
import time
import traceback

PDB_EXPORT = r"D:\workspace\project-x\asm\pal3a\pdb_export.json"
HEADER_FILE = r"D:\workspace\project-x\tools\fulldump\pal3a_types.h"
OUTPUT_DIR = r"D:\workspace\project-x\asm\pal3a\decomp"
LOG_FILE = r"D:\workspace\project-x\tools\fulldump\ida_pipeline_log.txt"

TYPE_MAP = {
    'int': 'int', 'uint': 'unsigned int', 'unsigned int': 'unsigned int',
    'float': 'float', 'double': 'double', 'char': 'char',
    'uchar': 'unsigned char', 'unsigned char': 'unsigned char',
    'short': 'short', 'ushort': 'unsigned short',
    'unsigned short': 'unsigned short',
    'long': 'long', 'ulong': 'unsigned long', 'unsigned long': 'unsigned long',
    'bool': 'bool', '__int64': '__int64',
    'unsigned __int64': 'unsigned __int64', 'void': 'void',
    'BOOL': 'int', 'BYTE': 'unsigned char', 'WORD': 'unsigned short',
    'DWORD': 'unsigned int', 'UINT': 'unsigned int', 'HRESULT': 'long',
    'HWND': 'void*', 'HANDLE': 'void*', 'HINSTANCE': 'void*',
    'HDC': 'void*', 'LPSTR': 'char*', 'LPCSTR': 'const char*',
    'LPVOID': 'void*', 'WPARAM': 'unsigned int', 'LPARAM': 'long',
    'LRESULT': 'long', 'SIZE_T': 'unsigned int',
    'D3DCOLOR': 'unsigned int', 'COLORREF': 'unsigned int',
    'size_t': 'unsigned int', 'wchar_t': 'unsigned short',
}


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        import ida_auto
        import ida_typeinf
        import ida_hexrays
        import ida_name
        import ida_funcs
        import idautils
        import idc

        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        if not ida_hexrays.init_hexrays_plugin():
            log("[!] Hex-Rays not available!")
            _save_log(log_lines)
            return

        # ==========================================
        # 第1步: 导入结构体
        # ==========================================
        log("\n[STEP 1] 导入结构体...")
        with open(HEADER_FILE, 'r', encoding='utf-8') as f:
            header = f.read()
        log(f"  头文件大小: {len(header)} bytes")

        errors = ida_typeinf.idc_parse_types(header, 0)
        log(f"  解析结果: {errors} (0=成功)")

        # 验证: 通过 tinfo_t.get_named_type 直接测试
        til = ida_typeinf.get_idati()

        # 从头文件中提取所有 struct 名称
        class_names_in_ida = set()
        import re
        for m in re.finditer(r'^struct\s+(\w+)\s*\{', header, re.MULTILINE):
            sname = m.group(1)
            # 验证 IDA 确实有这个类型
            tif = ida_typeinf.tinfo_t()
            if tif.get_named_type(til, sname):
                class_names_in_ida.add(sname)
        log(f"  IDA 验证可用结构体: {len(class_names_in_ida)}")
        if class_names_in_ida:
            samples = list(class_names_in_ida)[:5]
            log(f"  示例: {samples}")

        # ==========================================
        # 第2步: 导入枚举
        # ==========================================
        log("\n[STEP 2] 导入枚举...")
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        enums_created = 0
        for enum_info in pdb_data.get('enums', []):
            ename = enum_info.get('name', '')
            values = enum_info.get('values', {})
            if not ename or not values or '<' in ename:
                continue
            sn = safe_id(ename)
            vals = ', '.join(f"{safe_id(k)}={v}" for k, v in values.items()
                            if k and safe_id(k))
            if vals:
                enum_decl = f"enum {sn} {{ {vals} }};"
                r = ida_typeinf.idc_parse_types(enum_decl, 0)
                if r == 0:
                    enums_created += 1
        log(f"  枚举导入: {enums_created}")

        # 枚举名也加入已知类型集合
        for enum_info in pdb_data.get('enums', []):
            ename = enum_info.get('name', '')
            if ename and '<' not in ename:
                class_names_in_ida.add(safe_id(ename))
        log(f"  更新后可用类型: {len(class_names_in_ida)}")

        # ==========================================
        # 第3步: 应用函数类型
        # ==========================================
        log("\n[STEP 3] 应用函数类型...")

        # 构建索引
        ida_func_names = {}
        for ea in idautils.Functions():
            name = ida_name.get_name(ea)
            if name and not name.startswith("sub_"):
                ida_func_names[name] = ea

        pdb_by_name = {}
        for func in pdb_data['functions']:
            name = func.get('name', '')
            if name:
                pdb_by_name[name] = func

        log(f"  IDA 已命名函数: {len(ida_func_names)}")
        log(f"  PDB 函数索引: {len(pdb_by_name)}")

        applied = 0
        failed = 0
        for func_name, ea in ida_func_names.items():
            pdb_info = pdb_by_name.get(func_name)
            if not pdb_info:
                continue

            params = pdb_info.get('parameters', [])
            ret_type = pdb_info.get('return_type', 'void')
            this_type = pdb_info.get('this_type', '')
            cls_name = pdb_info.get('class', '')

            if '[thunk]' in ret_type:
                continue

            ret = ret_type
            for prefix in ('virtual ', 'static ', 'public: ', 'private: ',
                           'protected: ', 'inline '):
                ret = ret.replace(prefix, '')
            ret_c = pdb_type_to_c(ret, class_names_in_ida)

            param_parts = []
            if this_type and cls_name:
                safe_cls = safe_id(cls_name)
                if safe_cls in class_names_in_ida:
                    param_parts.append(f"{safe_cls} *this")
                else:
                    param_parts.append("void *this")

            for p in params:
                p_type = p.get('type', 'int')
                p_name = p.get('name', 'a')
                p_name_safe = make_safe_param_name(p_name)
                p_type_c = pdb_type_to_c(p_type, class_names_in_ida)
                param_parts.append(f"{p_type_c} {p_name_safe}")

            cc = '__thiscall' if this_type else '__cdecl'
            if not param_parts:
                proto = f"{ret_c} {cc} func(void);"
            else:
                proto = f"{ret_c} {cc} func({', '.join(param_parts)});"

            try:
                if idc.SetType(ea, proto):
                    applied += 1
                else:
                    failed += 1
            except:
                failed += 1

        log(f"  成功: {applied}, 失败: {failed}")

        # ==========================================
        # 第4步: 清除 Hex-Rays 缓存
        # ==========================================
        log("\n[STEP 4] 清除 Hex-Rays 缓存...")
        cleared = 0
        for func_name, ea in ida_func_names.items():
            if func_name in pdb_by_name:
                try:
                    ida_hexrays.mark_cfunc_dirty(ea)
                    cleared += 1
                except:
                    pass
        log(f"  已清除: {cleared}")

        # ==========================================
        # 第5步: 反编译导出
        # ==========================================
        log("\n[STEP 5] 高质量反编译导出...")
        os.makedirs(OUTPUT_DIR, exist_ok=True)

        targets = []
        for ea in idautils.Functions():
            func = ida_funcs.get_func(ea)
            if not func:
                continue
            if func.size() < 4:
                continue
            if func.flags & ida_funcs.FUNC_THUNK:
                continue
            if func.flags & ida_funcs.FUNC_LIB:
                continue
            name = ida_name.get_name(ea) or f"sub_{ea:08X}"
            targets.append((ea, name, func.size()))

        log(f"  目标函数: {len(targets)}")

        exported = 0
        errors = 0
        with_struct_access = 0
        start_time = time.time()

        for i, (ea, name, size) in enumerate(targets):
            if (i + 1) % 500 == 0:
                elapsed = time.time() - start_time
                rate = (i + 1) / elapsed if elapsed > 0 else 0
                log(f"  [{i+1}/{len(targets)}] exported={exported} "
                    f"struct_access={with_struct_access} errors={errors} "
                    f"({rate:.0f} f/s)")

            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    continue
            except:
                errors += 1
                continue

            code = str(cfunc)
            if not code:
                errors += 1
                continue

            # 检查是否有结构体成员访问 (this->xxx)
            if 'this->' in code or '->m_' in code:
                with_struct_access += 1

            sig = idc.get_type(ea) or ""

            data = {
                "name": name,
                "address": f"0x{ea:08X}",
                "size_bytes": size,
                "signature": sig,
                "decompiled_c": code,
            }

            filename = make_safe_filename(name, ea)
            try:
                filepath = os.path.join(OUTPUT_DIR, filename)
                with open(filepath, 'w', encoding='utf-8') as f:
                    json.dump(data, f, indent=2, ensure_ascii=False)
                exported += 1
            except:
                errors += 1

        elapsed = time.time() - start_time
        log(f"\n[*] 导出完成!")
        log(f"  导出: {exported}")
        log(f"  有结构体访问: {with_struct_access}")
        log(f"  错误: {errors}")
        log(f"  耗时: {elapsed:.1f}s")

        # 保存摘要
        summary = {
            "types_imported": type_count,
            "enums_imported": enums_created,
            "func_types_applied": applied,
            "total_targets": len(targets),
            "exported": exported,
            "with_struct_access": with_struct_access,
            "errors": errors,
            "elapsed_seconds": round(elapsed, 1),
        }
        with open(os.path.join(OUTPUT_DIR, "_export_summary.json"), 'w') as f:
            json.dump(summary, f, indent=2)

        # 保存数据库
        log("[*] 保存数据库...")
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 完成!")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    _save_log(log_lines)
    try:
        idc.qexit(0)
    except:
        pass


def _save_log(log_lines):
    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))


def safe_id(name):
    s = name.replace('::', '_').replace('<', '_').replace('>', '_')
    s = s.replace(',', '_').replace(' ', '_').replace('*', 'p')
    s = s.replace('&', 'r').replace('[', '_').replace(']', '_')
    s = s.replace('(', '_').replace(')', '_').replace('-', '_')
    s = s.replace('.', '_').replace('+', '_').replace('~', 'd')
    s = s.replace('/', '_').replace('\\', '_')
    while '__' in s:
        s = s.replace('__', '_')
    s = s.strip('_')
    if s and s[0].isdigit():
        s = '_' + s
    return s[:120] if s else 'unknown'


def make_safe_param_name(name):
    s = name.replace(' ', '_').replace('.', '_').replace('-', '_')
    s = s.replace('(', '').replace(')', '').replace('*', '')
    if not s or s[0].isdigit():
        s = '_' + s
    # 避免 C 关键字冲突
    keywords = {'int', 'float', 'double', 'char', 'void', 'bool',
                'short', 'long', 'unsigned', 'signed', 'const',
                'class', 'struct', 'enum', 'union', 'return',
                'if', 'else', 'while', 'for', 'do', 'switch', 'case',
                'break', 'continue', 'default', 'this', 'new', 'delete'}
    if s in keywords:
        s = s + '_'
    return s if s else 'param'


def pdb_type_to_c(pdb_type, known_types):
    if not pdb_type:
        return 'int'
    t = pdb_type.strip()
    for prefix in ('class ', 'struct ', 'enum ', 'union '):
        if t.startswith(prefix):
            t = t[len(prefix):]
    if t.endswith('*'):
        base = t[:-1].strip()
        for prefix in ('class ', 'struct ', 'enum '):
            if base.startswith(prefix):
                base = base[len(prefix):]
        safe_base = safe_id(base)
        if safe_base in known_types:
            return f"{safe_base} *"
        if base in TYPE_MAP:
            return f"{TYPE_MAP[base]} *"
        return 'void *'
    if t.endswith('&'):
        base = t[:-1].strip()
        for prefix in ('class ', 'struct ', 'enum '):
            if base.startswith(prefix):
                base = base[len(prefix):]
        safe_base = safe_id(base)
        if safe_base in known_types:
            return f"{safe_base} *"
        if base in TYPE_MAP:
            return f"{TYPE_MAP[base]} *"
        return 'void *'
    if t.startswith('const '):
        return pdb_type_to_c(t[6:], known_types)
    if t in TYPE_MAP:
        return TYPE_MAP[t]
    safe_t = safe_id(t)
    if safe_t in known_types:
        return safe_t
    return 'int'


def make_safe_filename(name, addr):
    safe = name.replace("::", "_").replace("<", "_").replace(">", "_")
    safe = safe.replace("*", "_ptr").replace(" ", "_").replace(",", "_")
    safe = safe.replace("(", "").replace(")", "").replace("&", "_ref")
    safe = safe.replace("/", "_").replace("\\", "_").replace("?", "_")
    safe = safe.replace("~", "dtor_").replace("'", "")
    if len(safe) > 80:
        safe = safe[:80]
    return f"{safe}_{addr:08X}.json"


main()
