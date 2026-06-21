"""C++ file generation stage.

Transforms decomp output through the pipeline and emits .cpp files
organized by class and free functions.
"""
import re
from pathlib import Path

from data import store
from stages.transform import run_transforms, make_context
from stages.collect import collect_functions, get_class_dir, CLASS_DIRS

# nullsub functions that are referenced in code but skipped from codegen.
# These need empty function bodies generated in free_functions.cpp.
_nullsub_stubs = set()


def collect_sub_refs(code):
    """Find all sub_XXXXX and named function references needing forward declaration."""
    # _todo_/todo_ after . or -> are FIELD references, not functions — skip them
    refs = set(re.findall(r'(?<![.>])\b(_todo_[0-9A-Fa-f]+|todo_[0-9A-Fa-f]+)\b', code))
    # sub_ after . or -> are method calls, not free functions — skip them
    refs.update(re.findall(r'(?<![.>])\b(sub_[0-9A-Fa-f]+)\b', code))
    # PascalCase game function calls (not preceded by . or -> or ::)
    for m in re.finditer(
        r'(?<![.>:])\b([A-Z][a-zA-Z0-9_]*'
        r'(?:Update|Init|Create|Destroy|Render|Sort|Check|Process|'
        r'SetState|GetState|Reset|Load|Save|Release|Free|Manager|Info|Cleanup))\s*\(',
        code
    ):
        refs.add(m.group(1))
    # Specific patterns: UIObj_XXX, GetXxxManager_N, etc.
    for m in re.finditer(
        r'(?<![.>:])(?<!\w)\b((?:UIObj_\w+|Get\w+Manager(?:_\d+)?|Texture_Info_\w+|GetGfxManager_\d+))\s*\(',
        code
    ):
        refs.add(m.group(1))
    return refs


def collect_undefined_refs(code):
    """Find likely undefined identifiers that need extern/forward decl."""
    refs = set()
    # IDA string constants: aXxxxx and asc_XXXXX (exclude those replaced by literals)
    refs.update(r for r in re.findall(r'\b(a[A-Z]\w{3,})\b', code)
                if r not in store.literals)
    refs.update(r for r in re.findall(r'\b(asc_[0-9A-Fa-f]+)\b', code)
                if r not in store.literals)
    # IDA unnamed globals (only as identifiers, not those replaced by literals)
    refs.update(r for r in re.findall(r'\b(dword_[0-9A-Fa-f]+)\b', code)
                if r not in store.literals)
    refs.update(r for r in re.findall(r'\b(byte_[0-9A-Fa-f]+)\b', code)
                if r not in store.literals)
    refs.update(re.findall(r'\b(word_[0-9A-Fa-f]+)\b', code))
    refs.update(r for r in re.findall(r'\b(flt_[0-9A-Fa-f]+)\b', code)
                if r not in store.literals)
    refs.update(re.findall(r'\b(off_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(unk_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(stru_[0-9A-Fa-f]+)\b', code))
    # pTarget: Hex-Rays synthesized local, NOT declared in decomp JSON's local_vars
    refs.update(re.findall(r'\b(pTarget)\b', code))
    # IDA named but unresolved
    refs.update(re.findall(r'\b(nullsub_\d+)\b', code))
    refs.update(re.findall(r'\b(unknown_libname_\d+)\b', code))
    return refs


_undeclared_off_globals = set()


def generate_forward_decls(all_code):
    """Generate minimal forward declarations: only what this file actually references."""
    lines = []
    subs = collect_sub_refs(all_code)
    # Detect functions passed to atexit (need void __cdecl(void) signature)
    atexit_funcs = set(re.findall(r'atexit\(\s*(\w+)\s*\)', all_code))

    # free_functions.h is included when free_func_sigs is non-empty,
    # so skip per-file forward declarations for functions already declared there.
    _skip_free_funcs = bool(store.free_func_sigs)

    if subs:
        lines.append("// Forward declarations for unnamed functions")
        for s in sorted(subs):
            if _skip_free_funcs and s in store.free_func_sigs:
                continue
            # Skip if the function has a definition in this file (::sub_XXXX)
            if re.search(r'(?:\w+::)?\b' + re.escape(s) + r'\s*\(', all_code):
                if re.search(r'::' + re.escape(s) + r'\s*\(', all_code):
                    continue
            # Filter out decompiler artifacts: addresses below .text section
            _saddr = None
            _sm = re.match(r'(?:sub|todo|_todo)_([0-9A-Fa-f]+)', s)
            if _sm:
                _saddr = int(_sm.group(1), 16)
            if _saddr is not None and _saddr < 0x401000:
                continue
            # Skip if the function has a definition in this file (::sub_XXXX)
            if re.search(r'(?:\w+::)?\b' + re.escape(s) + r'\s*\(', all_code):
                # Check if there's a definition (:: prefix) not just a declaration
                if re.search(r'::' + re.escape(s) + r'\s*\(', all_code):
                    continue
            if s in atexit_funcs:
                lines.append("void __cdecl %s(void);" % s)
            elif s in store.free_func_sigs:
                lines.append("%s; // from annotations" % store.free_func_sigs[s])
            else:
                lines.append("int %s(...);" % s)
        lines.append("")

    # Known free functions referenced in code but not caught by collect_sub_refs
    if not _skip_free_funcs:
        for fname, decl in store.free_func_sigs.items():
            if fname not in subs and re.search(r'\b' + re.escape(fname) + r'\s*\(', all_code):
                if fname not in store.declared_globals:
                    subs.add(fname)
                    lines.append("%s; // from annotations" % decl)
    if lines and lines[-1] != '':
        lines.append("")

    undef = collect_undefined_refs(all_code)
    undef -= store.declared_globals

    _seen_addrs = {}
    for _u in list(undef):
        if _u.startswith('unknown_libname'):
            undef.discard(_u)
            continue
        _ua = store.global_addrs.get(_u)
        if _ua is None:
            _m = re.match(r'(?:dword|byte|word|flt|unk|off|stru)_([0-9a-fA-F]+)', _u)
            if _m:
                _ua = int(_m.group(1), 16)
        if _ua is not None:
            if _ua < 0x580000:
                undef.discard(_u)
                continue
            if _ua >= 0x1897000:
                undef.discard(_u)
                continue
            if _ua in (0x01010101, 0x00FFFFFF, 0x01234567):
                undef.discard(_u)
                continue
            for _base, _end, _, _ in store.struct_instances:
                if _base < _ua < _end:
                    undef.discard(_u)
                    break
        if _u in undef:
            if _ua and any(ga == _ua for gn, ga in store.skip_globals.items()):
                undef.discard(_u)
                continue
            if _u in store.skip_globals:
                undef.discard(_u)
                continue
            if _u in store.globals_map:
                undef.discard(_u)
                continue
        if _ua is not None:
            for _base, _end, _, _ in store.struct_instances:
                if _base < _ua < _end:
                    undef.discard(_u)
                    break

    # Detect off_ variables used as arrays
    off_as_array = set()
    for u in undef:
        if u.startswith('off_'):
            if re.search(r'\b' + re.escape(u) + r'\s*\[', all_code) or \
               re.search(r'&' + re.escape(u) + r'\s*\)\s*\[', all_code) or \
               re.search(r'&' + re.escape(u) + r'\s*\)\s*[<>]', all_code):
                off_as_array.add(u)

    # Collect nullsub references for stub body generation in free_functions.cpp
    # Keep them in undef so per-file forward declarations are still emitted.
    for u in list(undef):
        if u.startswith('nullsub_') and u in store.skip_funcs:
            _nullsub_stubs.add(u)

    if undef:
        lines.append("// Unnamed globals (extern)")
        for u in sorted(undef):
            if u in atexit_funcs:
                lines.append("void __cdecl %s(void);" % u)
                continue
            if u.startswith('nullsub_'):
                lines.append("void __cdecl %s(...);" % u)
                continue
            # Check if annotated in globals.json (non-IDA globals with semantic names)
            if u in store.annotated_globals:
                _ann_name, _ann_type = store.annotated_globals[u]
                lines.append("extern %s %s;" % (_ann_type, _ann_name))
                continue
            if u in store.global_types:
                gt = store.global_types[u]
                arr_m = re.match(r'^(.+?)(\[\d*\])$', gt)
                if arr_m:
                    lines.append("extern %s %s%s;" % (arr_m.group(1), u, arr_m.group(2)))
                else:
                    lines.append("extern %s %s;" % (gt, u))
            elif u.startswith('flt_'):
                if re.search(r'\b' + re.escape(u) + r'\s*\[', all_code):
                    lines.append("extern float %s[];" % u)
                else:
                    lines.append("extern float %s;" % u)
            elif u.startswith('asc_'):
                lines.append("extern char %s[];" % u)
            elif u.startswith('byte_'):
                if re.search(r'\b' + re.escape(u) + r'\s*\[', all_code):
                    lines.append("extern char %s[];" % u)
                else:
                    lines.append("extern char %s;" % u)
            elif u.startswith('off_'):
                lines.append("extern void *%s;" % u)
                _undeclared_off_globals.add(u)
            elif u.startswith('a') and len(u) > 1 and u[1].isupper():
                lines.append('extern char %s[];' % u)
            elif re.search(r'\b' + re.escape(u) + r'\s*\[', all_code):
                lines.append("extern int %s[];" % u)
            else:
                lines.append("extern int %s;" % u)
        lines.append("")

    return '\n'.join(lines)


def _detect_needed_includes(cls_name, methods):
    """Auto-detect additional #include headers needed from code content."""
    header_dir = store.header_dir
    all_code_preview = '\n'.join(m['code'] for m in methods)
    needed_classes = set()

    def _header_exists(name):
        """Check if a class header exists, searching subdirectories."""
        _sub = get_class_dir(name)
        if _sub:
            return (header_dir / _sub / ("%s.h" % name)).exists()
        return (header_dir / ("%s.h" % name)).exists()

    # ClassName:: static calls
    for match in re.finditer(r'\b([A-Z]\w+)::', all_code_preview):
        c = match.group(1)
        if c != cls_name and _header_exists(c):
            needed_classes.add(c)

    # (ClassName *) casts -- accessing members requires full definition
    for match in re.finditer(r'\((\w+)\s*\*+\s*\)', all_code_preview):
        c = match.group(1)
        if c != cls_name and _header_exists(c):
            needed_classes.add(c)

    # Any word matching a known header file name in the code
    known_headers = {f.stem for f in header_dir.rglob("*.h")}
    for match in re.finditer(r'\b([A-Za-z_]\w+)\b', all_code_preview):
        c = match.group(1)
        if c != cls_name and c in known_headers and c not in needed_classes:
            needed_classes.add(c)

    # Resolve indirect dependencies: check EACH header we're about to include
    # for forward-declared types. If a type is forward-declared in a header
    # we include AND that type name appears in the code, include its header too.
    # This handles the case where a->b->c needs c.h but only b is directly included.
    fwd_types = set()
    all_included = needed_classes | {cls_name}
    # Also scan globals.h for forward-declared types (included by all .cpp files)
    # AND for extern variable declarations (var name → type mapping)
    _globals_h = header_dir / "globals.h"
    if _globals_h.exists():
        with open(_globals_h, 'r', encoding='utf-8', errors='replace') as _gh:
            _extern_map = {}  # var_name → type_name
            for _hl in _gh:
                # Scan forward declarations: class X;
                _fwd = re.match(r'^\s*class\s+(\w+)\s*;\s*', _hl)
                if _fwd:
                    _t = _fwd.group(1)
                    if _t in known_headers and not _t.startswith('gb'):
                        # Check: exact class name, g_p+Name, or g_+Name in code
                        _in_code = _t in all_code_preview
                        _in_code = _in_code or ('g_p' + _t in all_code_preview)
                        _in_code = _in_code or ('g_' + _t in all_code_preview)
                        # Also check for common shortened prefixes: g_pCBSystem → CCBSystem
                        if _t.startswith('CCB') and 'g_pCB' + _t[3:] in all_code_preview:
                            _in_code = True
                        if _in_code:
                            all_included.add(_t)
                            needed_classes.add(_t)
                # Scan extern declarations: extern Type var_name;
                _ext = re.match(r'^\s*extern\s+(?:(?:class|struct)\s+)?(\w+)\s+(\w+)\s*;', _hl)
                if _ext:
                    _ext_type = _ext.group(1)
                    _ext_var = _ext.group(2)
                    if _ext_type in known_headers and not _ext_type.startswith('gb'):
                        _extern_map[_ext_var] = _ext_type
            # Check if any extern variable is used in the code with member access
            for _var, _typ in _extern_map.items():
                if _typ not in all_included and _var in all_code_preview:
                    all_included.add(_typ)
                    needed_classes.add(_typ)
    # Also add headers included by the class's own header
    _cls_sub = get_class_dir(cls_name)
    cls_hpath = (header_dir / _cls_sub / ("%s.h" % cls_name)) if _cls_sub else (header_dir / ("%s.h" % cls_name))
    if cls_hpath.exists():
        with open(cls_hpath, 'r', encoding='utf-8', errors='replace') as hf:
            for hline in hf:
                inc_m = re.match(r'#include\s+"([^"]*)"', hline)
                if inc_m:
                    inc_stem = inc_m.group(1).split('/')[-1].replace('.h', '')
                    if inc_stem in known_headers:
                        all_included.add(inc_stem)
    # One-level BFS: scan headers we're including for forward-declared types
    for inc_cls in list(all_included):
        _inc_sub = get_class_dir(inc_cls)
        hpath = (header_dir / _inc_sub / ("%s.h" % inc_cls)) if _inc_sub else (header_dir / ("%s.h" % inc_cls))
        if not hpath.exists():
            continue
        with open(hpath, 'r', encoding='utf-8', errors='replace') as hf:
            for hline in hf:
                fwd_m = re.match(r'^\s*class\s+(\w+)\s*;\s*(?://.*)?$', hline)
                if fwd_m:
                    fwd_type = fwd_m.group(1)
                    if fwd_type in known_headers and fwd_type not in all_included \
                            and not fwd_type.startswith('gb'):
                        # Check if the type is used: exact name, member access, or field type
                        _used = fwd_type in all_code_preview
                        # Check if any struct member type matches (e.g., ObjectCamera as field type)
                        if not _used:
                            for _sn, _sm in store.struct_members.items():
                                for _so, (_sfn, _sft) in _sm.items():
                                    if fwd_type in _sft and _sfn in all_code_preview:
                                        _used = True
                                        break
                                if _used:
                                    break
                        if _used:
                            fwd_types.add(fwd_type)
                            all_included.add(fwd_type)
    needed_classes |= fwd_types

    return needed_classes


def generate_class_cpp(cls_name, methods):
    """Generate .cpp content for a class."""
    lines = []
    header_dir = store.header_dir

    # Standard includes
    lines.append('#include "pal3/ida_defs.h"')
    lines.append('#include "globals.h"')
    lines.append('#include "pal3/pal3_constants.h"')
    _cls_subdir = get_class_dir(cls_name)
    _cls_header_subdir = header_dir / _cls_subdir
    header_path = _cls_header_subdir / ("%s.h" % cls_name)
    if header_path.exists():
        if _cls_subdir:
            lines.append('#include "%s/%s.h"' % (_cls_subdir, cls_name))
        else:
            lines.append('#include "%s.h"' % cls_name)

    # Auto-detect additional includes
    needed_classes = _detect_needed_includes(cls_name, methods)

    # CRT/system types that should never be included
    _SKIP_INCLUDE = {
        '_ThrowInfo', '_CatchableType', '_CatchableTypeArray',
        '_s_ThrowInfo', '_s__ThrowInfo',
        'string', 'exception', 'type_info', 'stdiobuf', 'filebuf',
        'ios_base', 'facet', 'codecvt_base', 'strstreambuf',
    }
    for c in sorted(needed_classes):
        if c.startswith('vtbl_') or c in _SKIP_INCLUDE:
            continue
        _c_subdir = get_class_dir(c)
        if _c_subdir:
            lines.append('#include "%s/%s.h"' % (_c_subdir, c))
        else:
            lines.append('#include "%s.h"' % c)

    # Include free_functions.h if any free function is called or referenced
    free_func_h = header_dir / "free_functions.h"
    if free_func_h.exists() and cls_name != 'free_functions':
        all_code = '\n'.join(m['code'] for m in methods)
        if store.free_func_sigs:
            import re as _re_inc
            for fname in store.free_func_sigs:
                if _re_inc.search(r'\b' + _re_inc.escape(fname) + r'\b', all_code):
                    lines.append('#include "free_functions.h"')
                    break

    lines.append("")

    # Sort methods by address
    methods.sort(key=lambda m: m['addr'])

    # Transform all method code through the pipeline
    transformed = []
    for m in methods:
        ctx = make_context(cls_name, m['method'], sig=m.get('sig', ''))
        code = run_transforms(m['code'].strip(), ctx)
        transformed.append((m['addr'], code))

    # Generate forward declarations based on all code in this file
    all_code = '\n'.join(code for _, code in transformed)
    fwd = generate_forward_decls(all_code)
    if fwd:
        lines.append(fwd)

    # Emit transformed code
    for addr, code in transformed:
        lines.append("// %s" % addr)
        lines.append(code)
        lines.append("")

    return '\n'.join(lines)


def generate_free_funcs_cpp(funcs):
    """Generate .cpp for free functions."""
    lines = []
    lines.append('#include "pal3/ida_defs.h"')
    lines.append('#include "globals.h"')
    lines.append('#include "free_functions.h"')

    # Scan all function bodies for ClassName:: and (ClassName *) references, add includes
    import re
    all_code_text = '\n'.join(f.get('code', '') for f in funcs)
    referenced_classes = set(re.findall(r'\b([A-Z][A-Za-z0-9_]+)::', all_code_text))
    # Also detect (ClassName *) casts — casting to a class pointer requires full definition
    for m in re.finditer(r'\((\w+)\s*\*+\s*\)', all_code_text):
        c = m.group(1)
        if c[0].isupper():
            referenced_classes.add(c)
    header_dir = store.project_root / "pal3" / "src"
    for cls in sorted(referenced_classes):
        _subdir = get_class_dir(cls)
        hpath = (header_dir / _subdir / ("%s.h" % cls)) if _subdir else (header_dir / ("%s.h" % cls))
        if hpath.exists():
            if _subdir:
                lines.append('#include "%s/%s.h"' % (_subdir, cls))
            else:
                lines.append('#include "%s.h"' % cls)
    lines.append("")
    lines.append("// Free functions (not belonging to any class)")
    lines.append("")

    funcs.sort(key=lambda f: f['addr'])

    # Transform all through the pipeline (as free functions)
    transformed = []
    for f in funcs:
        ctx = make_context('', f['name'], sig=f.get('sig', ''), is_free=True)
        code = run_transforms(f['code'].strip(), ctx)
        transformed.append((f['addr'], code))

    # Forward declarations
    all_code = '\n'.join(code for _, code in transformed)
    fwd = generate_forward_decls(all_code)
    if fwd:
        lines.append(fwd)

    for addr, code in transformed:
        lines.append("// %s" % addr)
        lines.append(code)
        lines.append("")

    # Nullsub stubs for compiler-generated nop functions referenced in code
    if _nullsub_stubs:
        lines.append("")
        lines.append("// Nullsub stubs (compiler-generated empty bodies)")
        lines.append("")
        for ns in sorted(_nullsub_stubs):
            lines.append("void __cdecl %s(...) {}" % ns)
        lines.append("")

    return '\n'.join(lines)


def run_cpp_generation(filter_classes=None):
    """Main entry point: generate .cpp files from decomp JSONs.

    Always performs full generation (no incremental caching).

    Args:
        filter_classes: If set, only generate these class names.
    """
    output_dir = store.project_root / "pal3" / "src"

    print("Collecting functions from decomp...")
    by_class, free_funcs = collect_functions()

    print("  Classes with methods: %d" % len(by_class))
    print("  Free functions: %d" % len(free_funcs))

    output_dir.mkdir(parents=True, exist_ok=True)
    generated = 0
    total_funcs = 0

    # Pre-generate free_functions.h so .cpp files can include it (needed for include check)
    _header_dir = store.header_dir
    _h_lines = ['#pragma once',
                '// Auto-generated: free function forward declarations',
                '#include "pal3/ida_defs.h"', '']
    for _fname, _decl in sorted(store.free_func_sigs.items()):
        _h_lines.append('%s;' % _decl)
    _h_lines.append('')
    with open(_header_dir / "free_functions.h", 'w', encoding='utf-8') as _f:
        _f.write('\n'.join(_h_lines))

    for cls_name, methods in sorted(by_class.items()):
        if filter_classes and cls_name not in filter_classes:
            total_funcs += len(methods)
            continue

        subdir = get_class_dir(cls_name)
        out_dir = output_dir / subdir
        out_dir.mkdir(parents=True, exist_ok=True)

        safe_name = cls_name.replace('<', '_').replace('>', '_').replace(':', '_').replace('"', '_').replace('?', '_').replace('*', '_').replace('|', '_').replace('\\', '_').replace('/', '_').strip()
        out_path = out_dir / ("%s.cpp" % safe_name)
        content = generate_class_cpp(cls_name, methods)
        with open(out_path, 'w', encoding='utf-8') as f:
            f.write(content)
        generated += 1
        total_funcs += len(methods)

    # Free functions
    if free_funcs and not filter_classes:
        out_path = output_dir / "free_functions.cpp"
        content = generate_free_funcs_cpp(free_funcs)
        with open(out_path, 'w', encoding='utf-8') as f:
            f.write(content)
        generated += 1
        total_funcs += len(free_funcs)

        # Generate free_functions.h from free_func_sigs
        header_dir = store.header_dir
        h_lines = ['#pragma once',
                   '// Auto-generated: free function forward declarations',
                   '#include "pal3/ida_defs.h"', '']
        # Forward declare game struct types used as pointers in signatures
        _SYSTEM_TYPES = {'int', 'void', 'char', 'float', 'double', 'short', 'long',
                         'unsigned', 'const', 'BYTE', 'WORD', 'DWORD', 'UINT', 'BOOL',
                         'LPCSTR', 'LPSTR', 'CHAR', 'HRESULT', 'HANDLE', 'HWND', 'RECT',
                         'FILE', '_DWORD', '_BYTE', '_WORD', 'POINT', 'SIZE',
                         'WPARAM', 'LPARAM', 'LRESULT', 'LCID',
                         'INT_PTR', 'UINT_PTR', 'LONG_PTR', 'ULONG_PTR', 'DWORD_PTR',
                         '__int8', '__int16', '__int32', '__int64',
                         'unsigned __int8', 'unsigned __int16', 'unsigned __int32', 'unsigned __int64'}
        fwd_types = set()
        for fname, decl in store.free_func_sigs.items():
            for m in re.finditer(r'\b(\w+)\s*\*', decl):
                t = m.group(1)
                if t not in _SYSTEM_TYPES:
                    fwd_types.add(t)
        if fwd_types:
            for t in sorted(fwd_types):
                h_lines.append('struct %s;' % t)
            h_lines.append('')
        for fname, decl in sorted(store.free_func_sigs.items()):
            h_lines.append('%s;' % decl)
        h_lines.append('')
        h_path = header_dir / "free_functions.h"
        with open(h_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(h_lines))


    print("\nGenerated %d .cpp files (%d functions) in %s" % (
        generated, total_funcs, output_dir))

    # Summary by directory
    for subdir in sorted(set(CLASS_DIRS.values()) | {'Misc'}):
        d = output_dir / subdir
        if d.exists():
            count = len(list(d.glob("*.cpp")))
            if count > 0:
                print("  %s/: %d files" % (subdir, count))

    if _undeclared_off_globals:
        print("\n  [WARN] %d off_ globals without type annotation (undeclared)" % len(_undeclared_off_globals))
