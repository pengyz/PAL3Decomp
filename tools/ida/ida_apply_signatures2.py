"""
IDAPython: 批量应用 PDB 函数签名 (v2 - 使用 idc.SetType + 先命名)

改进策略:
  1. 先用 PDB 名给 sub_ 函数命名 (让 IDA 识别为类方法)
  2. 再用 idc.SetType 应用完整签名
  3. 对仍失败的, 退化为仅设返回类型

效果:
  - this 指针从 _DWORD* 变为 ClassName*
  - 参数从 int/char* 变为具体类型
  - 之前未命名的函数获得 PDB 名
"""

import ida_auto
import ida_typeinf
import ida_hexrays
import ida_funcs
import ida_name
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
TEXT_END = 0x00558000  # .text ends at 0x557C57, round up to .rdata start

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
    'bool': '_BOOL1',
    'BOOL': 'int',
    'BYTE': 'unsigned char',
    'WORD': 'unsigned short',
    'DWORD': 'unsigned long',
    'LONG': 'long',
    'UINT': 'unsigned int',
    'HWND': 'HWND',
    'HINSTANCE': 'HINSTANCE',
    'LPARAM': 'LPARAM',
    'WPARAM': 'WPARAM',
    'LRESULT': 'LRESULT',
    'HANDLE': 'HANDLE',
    'LPCSTR': 'LPCSTR',
    'LPSTR': 'LPSTR',
    'LPVOID': 'LPVOID',
    'HDC': 'HDC',
    'HRESULT': 'HRESULT',
}


def normalize_type(pdb_type):
    """将 PDB 类型转换为 IDA 可解析的 C 类型"""
    if not pdb_type:
        return None

    t = pdb_type.strip()
    t = t.replace('virtual ', '').replace('static ', '')

    if t in TYPE_MAP:
        return TYPE_MAP[t]

    # Pointer types
    if t.endswith(' *') or t.endswith(' **'):
        base = t
        stars = ''
        while base.endswith(' *'):
            base = base[:-2]
            stars += ' *'

        base = base.strip()
        if base.startswith('class '):
            base = base[6:]
        elif base.startswith('struct '):
            base = base[7:]
        elif base.startswith('const class '):
            base = base[12:]
            stars = ' const' + stars
        elif base.startswith('const struct '):
            base = base[13:]
            stars = ' const' + stars
        elif base.startswith('const '):
            base = base[6:]
            if base in TYPE_MAP:
                return 'const ' + TYPE_MAP[base] + stars
            if '<' in base:
                return 'void' + stars
            return base + stars

        if '<' in base:
            return 'void' + stars
        if base in TYPE_MAP:
            return TYPE_MAP[base] + stars
        if base.replace('_', '').replace('::', '').isalnum():
            return base + stars
        return 'void' + stars

    # Reference -> pointer
    if t.endswith(' &'):
        inner = t[:-2].strip()
        result = normalize_type(inner + ' *')
        return result

    # const without pointer
    if t.startswith('const '):
        inner = normalize_type(t[6:])
        if inner:
            return 'const ' + inner
        return None

    if t.startswith('class '):
        name = t[6:].strip()
        if '<' in name:
            return None
        return name

    if t.startswith('struct '):
        name = t[7:].strip()
        if '<' in name:
            return None
        return name

    if t.startswith('enum '):
        return 'int'

    # Template types
    if '<' in t:
        return None

    # Simple identifier
    if t.replace('_', '').isalnum() and not t[0].isdigit():
        if t in TYPE_MAP:
            return TYPE_MAP[t]
        return t

    return None


def build_ida_decl(func_name, ret_type_str, class_name, params, is_method):
    """构建 IDA SetType 格式的声明字符串

    类方法使用 __thiscall (this 通过 ECX 传递, 不出现在参数列表中):
      - 方法: ret __thiscall name(params...)
        IDA 内部知道 this 的类型通过函数所属结构体推断
    全局函数使用 __cdecl:
      - 全局: ret __cdecl name(params...)

    关键: __thiscall 时 this 不在显式参数列表里,
    IDA 会自动将 ECX 映射为 this 指针并使用结构体解析成员。
    但如果 IDA 无法推断 this 类型, 则退化为显式 this 参数 + __cdecl。
    """
    ret = normalize_type(ret_type_str) if ret_type_str else 'int'
    if not ret or ret == 'void *':
        ret = 'int'
    # Destructors always return void
    if '~' in func_name or 'destructor' in func_name.lower():
        ret = 'void'

    param_parts = []

    if is_method and class_name:
        # Use __thiscall: this is implicit (passed via ECX)
        # But we still need to tell IDA the this type via the function's
        # first parameter being "ClassName *this" in the declaration
        # IDA's SetType with __thiscall expects: ret __thiscall name(ClassName *this, ...)
        param_parts.append(f'{class_name} *this')
        callconv = '__thiscall'
    else:
        callconv = '__cdecl'

    for p in params:
        p_type = normalize_type(p.get('type', ''))
        p_name = p.get('name', '')
        if not p_type:
            p_type = 'int'
        if p_name and p_name.replace('_', '').isalnum() and not p_name[0].isdigit():
            param_parts.append(f'{p_type} {p_name}')
        else:
            param_parts.append(p_type)

    if not param_parts:
        params_str = 'void'
    else:
        params_str = ', '.join(param_parts)

    safe_name = func_name.replace('::', '_').replace('<', '_').replace('>', '_')
    safe_name = safe_name.replace('~', '_dtor_').replace(' ', '_')
    return f'{ret} {callconv} {safe_name}({params_str})'


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        funcs = pdb_data['functions']
        log(f"[*] PDB 函数总数: {len(funcs)}")

        # Filter targets - Phase 1: by PDB address
        targets = []
        name_only_targets = []  # PDB functions outside IDA text range
        for f in funcs:
            addr_str = f.get('address', '')
            if not addr_str:
                continue
            try:
                addr = int(addr_str, 16)
            except ValueError:
                continue
            name = f.get('name', '')
            if not name or '[thunk]' in name or '??' in name:
                continue
            if name.startswith('std::') or '<' in name.split('::')[0]:
                continue
            if "'" in name or '`' in name or 'adjustor' in name:
                continue
            if '<' in name or '>' in name:
                continue
            # Skip operator overloads and C keywords as function names
            base_name = name.split('::')[-1] if '::' in name else name
            if base_name.startswith('operator') or base_name.startswith('?') or base_name in (
                    'long', 'short', 'int', 'new', 'delete', 'char', 'bool',
                    'float', 'double', 'void', 'unsigned', 'signed'):
                continue
            if TEXT_START <= addr < TEXT_END:
                targets.append((addr, f))
            else:
                name_only_targets.append(f)

        log(f"[*] 目标函数 (地址匹配): {len(targets)}")
        log(f"[*] 目标函数 (需按名称查找): {len(name_only_targets)}")

        # Pre-declare types (scan all PDB functions, not just address-matched)
        til = ida_typeinf.get_idati()
        all_types = set()
        all_pdb_funcs = targets + [(0, fi) for fi in name_only_targets]
        for _, fi in all_pdb_funcs:
            name = fi.get('name', '')
            cls = name.split('::')[0] if '::' in name else ''
            if cls and '<' not in cls:
                all_types.add(cls)
            for p in fi.get('parameters', []):
                t = p.get('type', '').strip()
                for prefix in ('class ', 'struct '):
                    if t.startswith(prefix):
                        cname = t[len(prefix):].rstrip(' *&').strip()
                        if '<' not in cname and cname.replace('_', '').isalnum():
                            all_types.add(cname)

        new_decls = 0
        for tname in sorted(all_types):
            tif = ida_typeinf.tinfo_t()
            if not tif.get_named_type(til, tname):
                decl = f'struct {tname};'
                if idc.parse_decls(decl, idc.PT_TYP) == 0:
                    new_decls += 1
        log(f"[*] 新增前向声明: {new_decls}")

        # Phase A: Name unnamed functions using PDB names (address-matched)
        named_count = 0
        for addr, fi in targets:
            name = fi.get('name', '')
            if not name:
                continue
            ida_cur = ida_name.get_name(addr) or ""
            if ida_cur.startswith("sub_") or ida_cur.startswith("nullsub_"):
                safe = name.replace('::', '_').replace('~', '_dtor_')
                safe = safe.replace('<', '_').replace('>', '_').replace(' ', '_')
                if ida_name.set_name(addr, safe, ida_name.SN_NOWARN | ida_name.SN_NOCHECK):
                    named_count += 1
        log(f"[*] Phase A: 新命名 {named_count} 个函数 (地址匹配)")

        # Phase A2: DISABLED - PDB functions outside .text do NOT exist in release binary.
        # Name-matching them to IDA functions produces incorrect mappings.
        log(f"[*] Phase A2: 已禁用 (PDB 地址在 .text 外的函数在 release 版中不存在)")

        # Phase B: Apply signatures
        applied = 0
        skipped = 0
        errors = 0
        dbg_errors = []
        skip_no_sig = 0
        skip_no_func = 0
        skip_mid_func = 0

        for addr, fi in targets:
            name = fi.get('name', '')
            class_name = name.split('::')[0] if '::' in name else ''
            is_method = bool(class_name)
            params = fi.get('parameters', [])
            ret_type = fi.get('return_type', '')

            if not params and not ret_type:
                skip_no_sig += 1
                skipped += 1
                continue

            # Skip destructors with weird return types
            if 'deleting destructor' in ret_type:
                skipped += 1
                continue

            func = ida_funcs.get_func(addr)
            if not func:
                # Try to create function at this address
                if ida_funcs.add_func(addr):
                    func = ida_funcs.get_func(addr)
                if not func:
                    skip_no_func += 1
                    skipped += 1
                    continue
            # Skip if addr is NOT the function start (PDB addr is mid-function)
            if func.start_ea != addr:
                skip_mid_func += 1
                skipped += 1
                continue

            decl = build_ida_decl(name, ret_type, class_name, params, is_method)
            if not decl:
                skipped += 1
                continue

            # Clear any previously applied type info
            idc.SetType(addr, "")

            result = idc.SetType(addr, decl + ';')
            if result:
                applied += 1
                ida_hexrays.mark_cfunc_dirty(addr)
            else:
                # Fallback: parse + apply_tinfo with TINFO_DEFINITE
                tif = ida_typeinf.tinfo_t()
                parse_ok = ida_typeinf.parse_decl(tif, til, decl + ';', 0)
                if parse_ok is not None:
                    if ida_typeinf.apply_tinfo(addr, tif, ida_typeinf.TINFO_DEFINITE):
                        applied += 1
                        ida_hexrays.mark_cfunc_dirty(addr)
                    else:
                        errors += 1
                        if len(dbg_errors) < 20:
                            dbg_errors.append(f"  0x{addr:08X} {name} [apply fail]: {decl[:70]}")
                else:
                    errors += 1
                    if len(dbg_errors) < 20:
                        dbg_errors.append(f"  0x{addr:08X} {name} [parse fail]: {decl[:70]}")

            if (applied + skipped + errors) % 1000 == 0:
                log(f"  进度: applied={applied} skipped={skipped} errors={errors}")

        log("")
        log("[*] Phase B 完成!")
        log(f"  签名应用: {applied}")
        log(f"  跳过: {skipped} (无签名={skip_no_sig}, 无函数={skip_no_func}, 中间地址={skip_mid_func})")
        log(f"  错误: {errors}")

        if dbg_errors:
            log("[*] 失败样本:")
            for e in dbg_errors:
                log(e)

        # Mark all callers dirty for better propagation
        log("[*] 刷新调用者缓存...")
        dirty = 0
        for addr, _ in targets:
            for xref in idautils.CodeRefsTo(addr, 0):
                ida_hexrays.mark_cfunc_dirty(xref)
                dirty += 1
        log(f"  标记 {dirty} 个调用者")

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
