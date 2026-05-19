"""C++ file generation stage.

Transforms decomp output through the pipeline and emits .cpp files
organized by class and free functions.
"""
import os
import re
from pathlib import Path

from data import store
from stages.transform import run_transforms, make_context
from stages.collect import collect_functions, get_class_dir, CLASS_DIRS


def collect_sub_refs(code):
    """Find all sub_XXXXX and named function references needing forward declaration."""
    refs = set(re.findall(r'\b(sub_[0-9A-Fa-f]+)\b', code))
    # PascalCase game function calls (not preceded by . or -> or ::)
    for m in re.finditer(
        r'(?<![.>:])\b([A-Z][a-zA-Z0-9_]*'
        r'(?:Update|Init|Create|Destroy|Render|Sort|Check|Process|'
        r'SetState|GetState|Reset|Load|Save|Release|Free|Manager|Info))\s*\(',
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
    # IDA string constants: aXxxxx (exclude those replaced by literals)
    refs.update(r for r in re.findall(r'\b(a[A-Z]\w{3,})\b', code)
                if r not in store.literals)
    # IDA unnamed globals (only as identifiers, not those replaced by literals)
    refs.update(r for r in re.findall(r'\b(dword_[0-9A-Fa-f]+)\b', code)
                if r not in store.literals)
    refs.update(re.findall(r'\b(byte_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(word_[0-9A-Fa-f]+)\b', code))
    refs.update(r for r in re.findall(r'\b(flt_[0-9A-Fa-f]+)\b', code)
                if r not in store.literals)
    refs.update(re.findall(r'\b(off_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(unk_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(stru_[0-9A-Fa-f]+)\b', code))
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

    if subs:
        lines.append("// Forward declarations for unnamed functions")
        for s in sorted(subs):
            if s in atexit_funcs:
                lines.append("void __cdecl %s(void);" % s)
            elif s in store.free_func_sigs:
                lines.append("%s; // from annotations" % store.free_func_sigs[s])
            else:
                lines.append("int %s(...);" % s)
        lines.append("")

    # Known free functions referenced in code but not caught by collect_sub_refs
    for fname, decl in store.free_func_sigs.items():
        if fname not in subs and re.search(r'\b' + re.escape(fname) + r'\s*\(', all_code):
            if fname not in store.declared_globals:
                subs.add(fname)
                lines.append("%s; // from annotations" % decl)
    if lines and lines[-1] != '':
        lines.append("")

    undef = collect_undefined_refs(all_code)
    undef -= store.declared_globals

    # Detect off_ variables used as arrays
    off_as_array = set()
    for u in undef:
        if u.startswith('off_'):
            if re.search(r'\b' + re.escape(u) + r'\s*\[', all_code) or \
               re.search(r'&' + re.escape(u) + r'\s*\)\s*\[', all_code) or \
               re.search(r'&' + re.escape(u) + r'\s*\)\s*[<>]', all_code):
                off_as_array.add(u)

    if undef:
        lines.append("// Unnamed globals (extern)")
        for u in sorted(undef):
            if u in atexit_funcs:
                lines.append("void __cdecl %s(void);" % u)
                continue
            if u.startswith('nullsub_'):
                lines.append("void __cdecl %s(void);" % u)
                continue
            if u in store.global_types:
                gt = store.global_types[u]
                arr_m = re.match(r'^(.+?)(\[\d*\])$', gt)
                if arr_m:
                    lines.append("extern %s %s%s;" % (arr_m.group(1), u, arr_m.group(2)))
                else:
                    lines.append("extern %s %s;" % (gt, u))
            elif u.startswith('flt_'):
                lines.append("extern float %s;" % u)
            elif u.startswith('byte_'):
                lines.append("extern char %s;" % u)
            elif u.startswith('off_'):
                lines.append("extern void *%s;" % u)
                _undeclared_off_globals.add(u)
            elif u.startswith('a') and len(u) > 1 and u[1].isupper():
                lines.append('extern char %s[];' % u)
            else:
                lines.append("extern int %s;" % u)
        lines.append("")

    return '\n'.join(lines)


def _detect_needed_includes(cls_name, methods):
    """Auto-detect additional #include headers needed from code content."""
    header_dir = store.header_dir
    all_code_preview = '\n'.join(m['code'] for m in methods)
    needed_classes = set()

    # ClassName:: static calls
    for match in re.finditer(r'\b([A-Z]\w+)::', all_code_preview):
        c = match.group(1)
        if c != cls_name and (header_dir / ("%s.h" % c)).exists():
            needed_classes.add(c)

    # (ClassName *) casts -- accessing members requires full definition
    for match in re.finditer(r'\((\w+)\s*\*+\s*\)', all_code_preview):
        c = match.group(1)
        if c != cls_name and (header_dir / ("%s.h" % c)).exists():
            needed_classes.add(c)

    # Any word matching a known header file name in the code
    known_headers = {f.stem for f in header_dir.glob("*.h")}
    for match in re.finditer(r'\b([A-Za-z_]\w+)\b', all_code_preview):
        c = match.group(1)
        if c != cls_name and c in known_headers and c not in needed_classes:
            needed_classes.add(c)

    # Resolve indirect dependencies: if code dereferences a forward-declared
    # pointer member (ptr->field), include that type's header too.
    indirect = set()
    all_included = needed_classes | {cls_name}
    for inc_cls in list(all_included):
        hpath = header_dir / ("%s.h" % inc_cls)
        if not hpath.exists():
            continue
        with open(hpath, 'r', encoding='utf-8', errors='replace') as hf:
            for hline in hf:
                m = re.match(r'\s+(\w+)\s*\*\s*(\w+)\s*;', hline)
                if m:
                    ptr_type, ptr_name = m.group(1), m.group(2)
                    if ptr_type in known_headers and ptr_type not in all_included:
                        if re.search(r'\b' + re.escape(ptr_name) + r'\s*->', all_code_preview):
                            indirect.add(ptr_type)
    needed_classes |= indirect

    return needed_classes


def generate_class_cpp(cls_name, methods):
    """Generate .cpp content for a class."""
    lines = []
    header_dir = store.header_dir

    # Standard includes
    lines.append('#include "pal3/ida_defs.h"')
    lines.append('#include "pal3/globals.h"')
    header_path = header_dir / ("%s.h" % cls_name)
    if header_path.exists():
        lines.append('#include "pal3/gen/%s.h"' % cls_name)

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
        lines.append('#include "pal3/gen/%s.h"' % c)

    lines.append("")

    # Sort methods by address
    methods.sort(key=lambda m: m['addr'])

    # Transform all method code through the pipeline
    transformed = []
    for m in methods:
        ctx = make_context(cls_name, m['method'], sig=m['sig'])
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
    lines.append('#include "pal3/globals.h"')
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

    return '\n'.join(lines)


def run_cpp_generation(filter_classes=None):
    """Main entry point: generate .cpp files from decomp JSONs.

    Always performs full generation (no incremental caching).

    Args:
        filter_classes: If set, only generate these class names.
    """
    output_dir = store.output_dir

    print("Collecting functions from decomp...")
    by_class, free_funcs = collect_functions()

    print("  Classes with methods: %d" % len(by_class))
    print("  Free functions: %d" % len(free_funcs))

    output_dir.mkdir(parents=True, exist_ok=True)
    generated = 0
    total_funcs = 0

    for cls_name, methods in sorted(by_class.items()):
        if filter_classes and cls_name not in filter_classes:
            total_funcs += len(methods)
            continue

        subdir = get_class_dir(cls_name)
        out_dir = output_dir / subdir
        out_dir.mkdir(parents=True, exist_ok=True)

        out_path = out_dir / ("%s.cpp" % cls_name)
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


    # Clean stale .cpp files not in current generation set
    generated_files = set()
    for cls_name in by_class:
        subdir = get_class_dir(cls_name)
        generated_files.add(str((output_dir / subdir / ("%s.cpp" % cls_name)).resolve()))
    if free_funcs:
        generated_files.add(str((output_dir / "free_functions.cpp").resolve()))

    removed = 0
    for root, dirs, files in os.walk(output_dir):
        for fn in files:
            if fn.endswith('.cpp'):
                fpath = str(Path(root, fn).resolve())
                if fpath not in generated_files:
                    os.remove(os.path.join(root, fn))
                    removed += 1
    if removed:
        print("  Cleaned %d stale .cpp files" % removed)

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
