"""
IDAPython: 批量应用 PDB 函数签名（参数类型+返回类型）

从 pdb_export.json 读取函数的精确签名信息,
使用 ida_typeinf 为每个函数设置正确的参数和返回类型。

效果:
  - this 指针从 _DWORD* 变为 ClassName*
  - 参数从 int/char* 变为具体类型 (Role*, SceneObj*, float 等)
  - 返回类型从 int 变为具体类型

用法:
  idat.exe -A -S"ida_apply_signatures.py" PAL3A.exe.i64
"""

import ida_auto
import ida_typeinf
import ida_hexrays
import ida_funcs
import ida_name
import ida_nalt
import idautils
import idc
import json
import os
import traceback
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "ida_apply_signatures_log.txt")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
TEXT_START = 0x00401000
TEXT_END = 0x00608000

# PDB type -> IDA C type mapping
TYPE_MAP = {
    'void': 'void',
    'int': 'int',
    'uint': 'unsigned int',
    'long': 'long',
    'ulong': 'unsigned long',
    'short': 'short',
    'ushort': 'unsigned short',
    'char': 'char',
    'uchar': 'unsigned char',
    'float': 'float',
    'double': 'double',
    'bool': 'bool',
    'BOOL': 'int',
    'BYTE': 'unsigned char',
    'WORD': 'unsigned short',
    'DWORD': 'unsigned long',
    'LONG': 'long',
    'UINT': 'unsigned int',
    'HWND': 'void *',
    'HINSTANCE': 'void *',
    'LPARAM': 'long',
    'WPARAM': 'unsigned int',
    'LRESULT': 'long',
    'HANDLE': 'void *',
    'LPCSTR': 'const char *',
    'LPSTR': 'char *',
    'LPCWSTR': 'const unsigned short *',
    'LPVOID': 'void *',
    'SIZE_T': 'unsigned int',
    'HDC': 'void *',
    'HRESULT': 'long',
}


def normalize_type(pdb_type):
    """将 PDB 类型转换为 IDA 可解析的 C 类型字符串"""
    if not pdb_type:
        return None

    t = pdb_type.strip()

    # Remove leading qualifiers
    t = t.replace('virtual ', '').replace('static ', '')

    # Direct mapping
    if t in TYPE_MAP:
        return TYPE_MAP[t]

    # Pointer types: "class ClassName *" -> "ClassName *"
    if t.startswith('class ') and t.endswith('*'):
        cls_name = t[6:].rstrip(' *').strip()
        # Skip complex template types
        if '<' in cls_name:
            return 'void *'
        return cls_name + ' *'

    if t.startswith('struct ') and t.endswith('*'):
        s_name = t[7:].rstrip(' *').strip()
        if '<' in s_name:
            return 'void *'
        return s_name + ' *'

    if t.startswith('enum '):
        return 'int'

    # Simple pointer
    if t.endswith(' *') or t.endswith(' **'):
        base = t.rstrip(' *').strip()
        ptr_suffix = t[len(base):]
        if base.startswith('class '):
            base = base[6:]
        elif base.startswith('struct '):
            base = base[7:]
        if '<' in base:
            return 'void' + ptr_suffix
        if base in TYPE_MAP:
            return TYPE_MAP[base] + ptr_suffix
        return base + ptr_suffix

    # References -> pointers
    if t.endswith(' &'):
        base = t[:-2].strip()
        normalized = normalize_type(base)
        if normalized:
            return normalized + ' *'
        return 'void *'

    # const variants
    if t.startswith('const '):
        inner = normalize_type(t[6:])
        if inner:
            return 'const ' + inner
        return None

    # Template types -> void*
    if '<' in t:
        if '*' in t:
            return 'void *'
        return None

    # Known class/struct names (assume pointer if used as param)
    if t in TYPE_MAP:
        return TYPE_MAP[t]

    # If it looks like a simple identifier, it might be a struct name
    if t.replace('_', '').isalnum() and not t[0].isdigit():
        return t

    return None


def build_func_signature(func_info, class_name):
    """构建 IDA 可解析的函数类型字符串"""
    ret_type = normalize_type(func_info.get('return_type', 'void'))
    if not ret_type:
        ret_type = 'int'

    params = func_info.get('parameters', [])
    param_strs = []

    # For class methods, add this pointer
    is_method = '::' in func_info.get('name', '')
    if is_method and class_name:
        param_strs.append(class_name + ' *this')

    for p in params:
        p_type = normalize_type(p.get('type', ''))
        p_name = p.get('name', '')
        if not p_type:
            p_type = 'int'
        # Sanitize param name
        if p_name and p_name.replace('_', '').isalnum():
            param_strs.append(f'{p_type} {p_name}')
        else:
            param_strs.append(p_type)

    if not param_strs:
        param_strs = ['void']

    # Calling convention - always use __cdecl with explicit this parameter
    # because __thiscall requires IDA to know the function's class membership
    cc = '__cdecl'

    sig = f'{ret_type} {cc} func({", ".join(param_strs)})'
    return sig


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        # Load PDB data
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        funcs = pdb_data['functions']
        log(f"[*] PDB 函数总数: {len(funcs)}")

        # Filter: only functions in .text with parameters
        targets = []
        for f in funcs:
            addr_str = f.get('address', '')
            if not addr_str:
                continue
            try:
                addr = int(addr_str, 16)
            except ValueError:
                continue
            if addr < TEXT_START or addr >= TEXT_END:
                continue
            if not f.get('parameters') and not f.get('return_type'):
                continue
            # Skip thunks and weird names
            name = f.get('name', '')
            if '[thunk]' in name or '??' in name:
                continue
            targets.append((addr, f))

        log(f"[*] .text 区有签名信息的函数: {len(targets)}")

        # Pre-declare all referenced class/struct types as forward declarations
        til = ida_typeinf.get_idati()
        fwd_declared = set()
        for _, func_info in targets:
            name = func_info.get('name', '')
            cls = name.split('::')[0] if '::' in name else ''
            if cls and '<' not in cls and not cls.startswith('std::'):
                fwd_declared.add(cls)
            for p in func_info.get('parameters', []):
                t = p.get('type', '').strip()
                # Extract class/struct names from pointer types
                for prefix in ('class ', 'struct '):
                    if t.startswith(prefix):
                        cname = t[len(prefix):].rstrip(' *&').strip()
                        if '<' not in cname and cname.replace('_','').isalnum():
                            fwd_declared.add(cname)

        # Declare missing types
        new_decls = 0
        for tname in sorted(fwd_declared):
            tif = ida_typeinf.tinfo_t()
            if not tif.get_named_type(til, tname):
                decl = f'struct {tname};'
                if idc.parse_decls(decl, idc.PT_TYP) == 0:
                    new_decls += 1
        log(f"[*] 新增前向声明: {new_decls} 个类型")

        applied = 0
        skipped = 0
        errors = 0

        for addr, func_info in targets:
            name = func_info.get('name', '')
            class_name = name.split('::')[0] if '::' in name else ''

            # Skip std::, complex templates, and truncated names
            if class_name.startswith('std') or '<' in class_name or '>' in name:
                skipped += 1
                continue

            sig_str = build_func_signature(func_info, class_name)
            if not sig_str:
                skipped += 1
                continue

            try:
                func = ida_funcs.get_func(addr)
                if not func:
                    skipped += 1
                    continue

                # Use apply_tinfo which is more reliable for named functions
                tif = ida_typeinf.tinfo_t()
                result = ida_typeinf.parse_decl(tif, til, sig_str + ';', 0)
                if result is None:
                    skipped += 1
                    continue

                if ida_typeinf.apply_tinfo(addr, tif, ida_typeinf.TINFO_DEFINITE):
                    applied += 1
                    ida_hexrays.mark_cfunc_dirty(addr)
                    for xref in idautils.CodeRefsTo(addr, 0):
                        ida_hexrays.mark_cfunc_dirty(xref)
                else:
                    if errors < 10:
                        log(f"  [DBG] apply failed @ 0x{addr:08X} ({ida_func_name}): {sig_str[:60]}")
                    errors += 1

            except Exception:
                errors += 1

            if (applied + skipped + errors) % 500 == 0:
                log(f"  进度: applied={applied} skipped={skipped} errors={errors}")

        log("")
        log("[*] 签名应用完成!")
        log(f"  成功应用: {applied}")
        log(f"  跳过: {skipped}")
        log(f"  错误: {errors}")

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
