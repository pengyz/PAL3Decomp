"""Stage 1: Function signature modification using tree-sitter AST.

Modifies the function definition line (before OOP transform runs on body).
Uses AST to precisely identify and remove:
- Calling conventions (ms_call_modifier)
- 'this' parameter (first parameter_declaration)
- Return type for ctor/dtor
"""
import re

import tree_sitter_cpp as tscpp
import tree_sitter

_lang = tree_sitter.Language(tscpp.language())
_parser = tree_sitter.Parser(_lang)


def free_function_has_this_param(code):
    """函数头（首个 `{` 之前）里是否出现 **`this` 标识符**（纯函数，供单测）。

    只对**自由函数**有意义（成员函数的 `Cls *this` 由各自的剥离逻辑处理）。
    `_this`/`this_`/`this2` 都不匹配 ✓（`(?<![\w_])` / `(?![\w_])`）。
    """
    head = code.split('{', 1)[0]
    return bool(re.search(r'(?<![\w_])this(?![\w_])', head))


def rename_this_identifier(code, new='_this'):
    """把 `this` **标识符**改名为 `new`，**跳过字符串/字符字面量与注释**（纯函数）。

    为什么必须跳过：字符串里的 `"this"` 被改会**改数据** ⇒ 破坏字节匹配 ✗。
    为什么整体改名是安全的：自由函数里 `this` 不是可用表达式，任何该标识符必指那个形参 ✓。
    """
    out, i, n = [], 0, len(code)
    while i < n:
        ch = code[i]
        if ch == '"' or ch == "'":
            q, j = ch, i + 1
            while j < n:
                if code[j] == '\\':
                    j += 2
                    continue
                if code[j] == q:
                    j += 1
                    break
                j += 1
            out.append(code[i:j]); i = j; continue
        if code.startswith('//', i):
            j = code.find('\n', i)
            j = n if j < 0 else j
            out.append(code[i:j]); i = j; continue
        if code.startswith('/*', i):
            j = code.find('*/', i)
            j = n if j < 0 else j + 2
            out.append(code[i:j]); i = j; continue
        if code.startswith('this', i) and \
                (i == 0 or not (code[i-1].isalnum() or code[i-1] == '_')) and \
                (i + 4 >= n or not (code[i+4].isalnum() or code[i+4] == '_')):
            out.append(new); i += 4; continue
        out.append(ch); i += 1
    return ''.join(out)


def _rename_param_refs_to_this(func_def, first_param, pname, edits):
    """[T20/T21] 被剥 this 槽首参的体内引用改名 → this（AST 标识符逐个）。

    为什么必须改名：只丢参不改名 ⇒ 引用落到同名全局（Block 案：globals.h
    `extern void * Block; // 0x00D8E470`）= 静默语义腐蚀（delete/return 到
    全局而非对象）。跳过：限定访问 name 位（成员位是 field_identifier 不同型）、
    声明名字位（防遮蔽声明误改）、首参声明自身。
    """
    def _rn(node):
        for ch in node.children:
            if ch.type == 'identifier' and ch.text.decode('utf-8') == pname:
                par = ch.parent
                skip = (first_param.start_byte <= ch.start_byte
                        < first_param.end_byte)
                if par is not None:
                    if par.type in ('declaration', 'init_declarator',
                                    'parameter_declaration',
                                    'function_declarator',
                                    'pointer_declarator',
                                    'array_declarator'):
                        skip = True
                    elif par.type == 'qualified_identifier':
                        nm = par.child_by_field_name('name')
                        if nm is ch:
                            skip = True
                if not skip:
                    edits.append((ch.start_byte, ch.end_byte, b'this'))
            _rn(ch)
    _rn(func_def)


def run(code, ctx):
    """Apply structural transforms to function code."""
    # Filter IDA header comments
    lines = code.split('\n')
    lines = [l for l in lines if not l.strip().startswith('// between_std_methods')]
    code = '\n'.join(lines)

    # Pre-strip calling conventions from first line so tree-sitter can parse
    first_lines = code.split('\n', 1)
    if first_lines:
        first_lines[0] = re.sub(r'\b(__thiscall|__cdecl|__stdcall|__fastcall)\b', '', first_lines[0])
        code = '\n'.join(first_lines)

    # 自由函数的形参名**不得是 `this`**（C++ 关键字 ⇒ MSVC 报
    # `C2143 syntax error : missing ')' before 'this'`）。
    # 声明侧 `emit_headers:2128` 早已把 `this`→`_this`，**体侧此前漏了** ⇒ 实测
    # 34 处非法定义（全在 `pal3/src/free_functions.cpp`），而普查里只见 3 处
    # （其余 31 处被 C1003 截断挡住，见 gotcha_c1003_truncation_blinds_metric）。
    # 安全性：自由函数里 `this` **不是可用表达式** ⇒ 出现的该标识符必指那个形参
    # ⇒ 改名是等价变换；但**必须跳过字符串/字符字面量与注释**（改了会改数据 ✗）。
    # 审核工具：tools/audit_this_in_free_functions.py（[A] 段）；守卫：tests/test_free_function_this_rename.py
    if getattr(ctx, 'is_free_function', False) and free_function_has_this_param(code):
        code = rename_this_identifier(code)

    # Normalize Hex-Rays struct-return sret form so tree-sitter can parse the
    # definition: `RET *Cls::Method(RET *__return_ptr retstr, Cls *this, rest)`
    # → `RET Cls::Method(rest)`. VC6's struct-return ABI is implicit and
    # byte-identical; the sret spelling is an IDA type-system artifact. The
    # body may still reference `retstr` — such functions are queued for
    # Phase-2 manual by-value translation (body rewrites are not mechanical).
    if '__return_ptr' in code.split('{', 1)[0]:
        code = re.sub(
            r'\s*,?\s*[A-Za-z_][\w:]*(?:\s*\*+)?\s*__return_ptr\s+\w+\s*,?',
            ' ', code, count=1)
        code = re.sub(r'\(\s*,', '(', code, count=1)
        code = re.sub(r',\s*\)', ')', code, count=1)
        p0 = code.find('(')
        if p0 > 0:
            j = code[:p0].rstrip().rfind('*')
            if j != -1:
                code = code[:j] + code[j+1:]
        # a `Cls *this` param in sret defs duplicates the implicit this — drop it
        code = re.sub(r'(\([^)]*?),\s*[A-Za-z_][\w:]*(?:\s*\*+)?\s*this(\s*\))',
                      r'\1\2', code, count=1)
        code = re.sub(r'(\(\s*)[A-Za-z_][\w:]*(?:\s*\*+)?\s*this\s*,\s*',
                      r'\1', code, count=1)

    # Parse with tree-sitter
    code_bytes = code.encode('utf-8')
    tree = _parser.parse(code_bytes)

    # Find function_definition node
    func_def = None
    for child in tree.root_node.children:
        if child.type == 'function_definition':
            # Only accept func_def that starts at/near the beginning (row 0-2)
            if child.start_point[0] <= 2:
                func_def = child
            break

    if not func_def:
        # Fallback: try regex approach for unusual formats
        return _regex_fallback(code, ctx)

    # Collect byte-range edits
    edits = []  # [(start_byte, end_byte, replacement)]

    # 1. Remove calling convention (ms_call_modifier or ERROR node with CC text)
    # Skip for ctor/dtor: step 4 removes the entire prefix including CC
    if not (ctx.is_ctor or ctx.is_dtor):
        def _find_cc_nodes(node):
            for child in node.children:
                if child.type == 'ms_call_modifier':
                    edits.append((child.start_byte, child.end_byte, b''))
                elif child.type == 'ERROR' and child.text in (b'__thiscall', b'__cdecl', b'__stdcall', b'__fastcall'):
                    edits.append((child.start_byte, child.end_byte, b''))
                _find_cc_nodes(child)
        _find_cc_nodes(func_def)

    # 2. Fix function name: sub_XXXXX → ClassName::Method
    def _find_declarator(node):
        for child in node.children:
            if child.type == 'function_declarator':
                return child
            found = _find_declarator(child)
            if found:
                return found
        return None
    declarator = _find_declarator(func_def)

    if declarator and not ctx.is_free_function:
        # Get the function name node
        name_node = None
        for child in declarator.children:
            if child.type in ('qualified_identifier', 'identifier', 'field_identifier'):
                name_node = child
                break

        if name_node:
            current_name = name_node.text.decode('utf-8')
            expected_name = '%s::%s' % (ctx.cls_name, ctx.method_name)

            # Replace sub_XXXXX with correct name
            if current_name.startswith('sub_') or current_name != expected_name:
                # Handle IDA stripping leading underscore
                cls_variants = [ctx.cls_name]
                if ctx.cls_name.startswith('_'):
                    cls_variants.append(ctx.cls_name[1:])
                needs_fix = current_name.startswith('sub_')
                for cv in cls_variants:
                    if cv + '::' in current_name and cv != ctx.cls_name:
                        needs_fix = True
                # Also fix when name lacks class prefix entirely
                if not needs_fix and ctx.cls_name + '::' not in current_name:
                    needs_fix = True
                if needs_fix:
                    edits.append((name_node.start_byte, name_node.end_byte,
                                  expected_name.encode('utf-8')))

        # 3. Remove 'this' parameter
        param_list = None
        for child in declarator.children:
            if child.type == 'parameter_list':
                param_list = child
                break

        if param_list:
            params = [c for c in param_list.children if c.type == 'parameter_declaration']
            if params:
                first_param = params[0]
                first_text = first_param.text.decode('utf-8')
                # Check if first param is the 'this' pointer.
                # The decomp signature carries the calling convention: only a
                # __thiscall member has an implicit this to strip. For plain or
                # __cdecl (static) members the first pointer param is a real
                # argument — stripping it desynchronizes the definition from the
                # annotated header declaration (C2511) and misaligns call sites.
                is_thiscall = '__thiscall' in (ctx.sig or '')
                is_this_param = ('this' in first_text and '*' in first_text)
                if not is_this_param and is_thiscall and '*' in first_text and ctx.cls_name:
                    is_this_param = ctx.cls_name in first_text
                if not is_this_param and is_thiscall and '*' in first_text and not ctx.is_free_function:
                    is_this_param = True
                # Also catch degraded this: "int this" (IDA lost pointer type)
                if not is_this_param and 'this' in first_text and not ctx.is_free_function:
                    is_this_param = True
                if is_this_param:
                    # Skip for dtors: line 166+ strips ALL params, producing
                    # the same byte-range edit. Two identical edits corrupt
                    # the output when applied in reverse (second edit deletes
                    # body content after the first shifted the bytes).
                    if ctx.is_dtor:
                        pass
                    else:
                        # [T20] 首参（this 槽）名 → this 重命名（Block 案）：
                        # 只丢参不改名 ⇒ 体内引用落到同名全局/未声明——语义腐蚀
                        # （CCBSkillWindow::Destroy_12 的 Block 命中 0x00D8E470
                        # 全局 `extern void * Block`，delete/return 到全局而非对象）。
                        # A 级：Block=register 16（ECX 槽）⇒ __thiscall this 实证。
                        # AST 标识符逐个改名：跳过成员/限定访问字段位、声明名字位、
                        # 首参声明自身（防遮蔽/声明误改）。
                        _pname_m = re.search(r'(\w+)\s*$', first_text)
                        _pname = _pname_m.group(1) if _pname_m else None
                        if _pname and _pname != 'this':
                            _rename_param_refs_to_this(func_def, first_param,
                                                       _pname, edits)
                    if not ctx.is_dtor and len(params) > 1:
                        # Remove first param + following comma
                        # Find the comma after first param
                        end = first_param.end_byte
                        for sib in param_list.children:
                            if sib.type == ',' and sib.start_byte >= first_param.end_byte:
                                end = sib.end_byte
                                # Also skip whitespace after comma
                                while end < len(code_bytes) and code_bytes[end:end+1] == b' ':
                                    end += 1
                                break
                        edits.append((first_param.start_byte, end, b''))
                    elif not ctx.is_dtor:
                        # Only param is 'this' → replace with empty parens content
                        edits.append((first_param.start_byte, first_param.end_byte, b''))

            # Dtor: strip all params
            if ctx.is_dtor and params:
                # [T21] dtor 路径同族缺口（潜伏）：复用 T20 修法——丢参同步
                # 改名 this（语料现 0 例撞全局，但同名遮蔽即静默绑错）。
                _dfp = params[0]
                _dpm = re.search(r'(\w+)\s*$', _dfp.text.decode('utf-8'))
                _dpn = _dpm.group(1) if _dpm else None
                if _dpn and _dpn != 'this':
                    _rename_param_refs_to_this(func_def, _dfp, _dpn, edits)
                # Replace entire param list content with ()
                open_paren = None
                close_paren = None
                for child in param_list.children:
                    if child.type == '(' and not open_paren:
                        open_paren = child
                    if child.type == ')':
                        close_paren = child
                if open_paren and close_paren:
                    edits.append((open_paren.end_byte, close_paren.start_byte, b''))

    # 4. Remove return type for ctor/dtor
    if ctx.is_ctor or ctx.is_dtor:
        # Remove everything before the function declarator (return type + CC)
        if declarator:
            # Remove from start of func_def to start of declarator
            pre_start = func_def.start_byte
            pre_end = declarator.start_byte
            if pre_end > pre_start:
                edits.append((pre_start, pre_end, b''))

    # Apply edits in reverse order
    result = code_bytes
    for start, end, replacement in sorted(edits, reverse=True):
        result = result[:start] + replacement + result[end:]

    code = result.decode('utf-8')

    # Clean up: collapse multiple spaces, strip leading space on def line
    lines = code.split('\n')
    for i, line in enumerate(lines):
        if '(' in line and (not line.strip().startswith('//')) and (not line.strip().startswith('*')):
            cleaned = re.sub(r'  +', ' ', line).strip()
            if cleaned != line.strip():
                lines[i] = cleaned
            break
    code = '\n'.join(lines)

    # 4b. Fix invalid parameter names (starting with digit)
    lines = code.split('\n')
    if lines:
        # Match "type name" or "type *name" where name starts with digit
        lines[0] = re.sub(r'([\w\s]+[\s\*])(\d[0-9A-Fa-f]*)\s*([,\)])',
                          lambda m: m.group(1) + 'a_' + m.group(2) + m.group(3), lines[0])
        code = '\n'.join(lines)

    # 5. Ctor/dtor: remove 'return expr;' from body
    if ctx.is_ctor or ctx.is_dtor:
        lines = code.split('\n')
        for i in range(len(lines)):
            lines[i] = re.sub(r'^\s*return\s+(.+);', r'  \1;', lines[i])
        code = '\n'.join(lines)

    return code


def _regex_fallback(code, ctx):
    """Fallback for code that doesn't parse as a standard function_definition."""
    lines = code.split('\n')
    cls_name = ctx.cls_name
    method_name = ctx.method_name

    cls_variants = [cls_name]
    if cls_name.startswith('_'):
        cls_variants.append(cls_name[1:])

    func_line_idx = 0
    for idx, l in enumerate(lines):
        if '(' in l and (any(cv + '::' in l for cv in cls_variants) or 'sub_' in l
                         or (method_name and re.search(r'\b' + re.escape(method_name) + r'\s*\(', l))):
            func_line_idx = idx
            break

    if lines and method_name:
        first_line = lines[func_line_idx]
        full_method = '%s::%s' % (cls_name, method_name)
        first_line = re.sub(r'\bsub_[0-9A-Fa-f]+\b', full_method, first_line, count=1)
        # If function already has a proper name but missing class prefix, add it
        if cls_name and cls_name + '::' not in first_line:
            first_line = re.sub(
                r'\b' + re.escape(method_name) + r'(?=\s*\()',
                full_method, first_line, count=1
            )
        for cv in cls_variants:
            if cv != cls_name and re.search(r'(?<!_)' + re.escape(cv) + r'::', first_line):
                first_line = re.sub(r'(?<!_)' + re.escape(cv) + r'::', cls_name + '::', first_line)
                first_line = first_line.replace(cv + '::', cls_name + '::')
        if ctx.is_ctor or ctx.is_dtor:
            first_line = re.sub(r'^.*?\b(%s::%s)' % (re.escape(cls_name), re.escape(method_name)),
                                r'\1', first_line)
        lines[func_line_idx] = first_line

    if ctx.is_ctor or ctx.is_dtor:
        for i in range(len(lines)):
            lines[i] = re.sub(r'^\s*return\s+(.+);', r'  \1;', lines[i])

    if lines:
        first = lines[func_line_idx]
        first = re.sub(r'\s*__thiscall\s*', ' ', first)
        first = re.sub(r'\s*__cdecl\s*', ' ', first)
        first = re.sub(r'\s*__stdcall\s*', ' ', first)
        first = re.sub(r'\s*__fastcall\s*', ' ', first)
        first = re.sub(r'\s*__userpurge\s*', ' ', first)
        first = re.sub(r'\s*__usercall\s*', ' ', first)
        # Strip @<reg> annotations from names and params (Hex-Rays userpurge/usercall artifact)
        first = re.sub(r'@<\w+>', '', first)
        # Remove this param: 'ClassName *this' or 'ClassName *Block' etc.
        # Only __thiscall members carry an implicit this (see AST path above);
        # static/cdecl members keep their real first pointer param.
        _is_thiscall = '__thiscall' in (ctx.sig or '')
        if ctx.cls_name and _is_thiscall:
            _cls_pat = re.escape(ctx.cls_name)
            first = re.sub(r'\(\s*' + _cls_pat + r'\s*\*+\s*\w+\s*,\s*', '(', first, count=1)
            first = re.sub(r'\(\s*' + _cls_pat + r'\s*\*+\s*\w+\s*\)', '()', first, count=1)
        # Fallback: literal 'this' name
        first = re.sub(r'\(\s*\w[\w\s]*\*+\s*this\s*,\s*', '(', first)
        first = re.sub(r'\(\s*\w[\w\s]*\*+\s*this\s*\)', '()', first)
        # Catch 'int this' and other typed this params not matched above
        first = re.sub(r'\(\s*\w[\w\s]+\bthis\b\s*,\s*', '(', first)
        first = re.sub(r'\(\s*\w[\w\s]+\bthis\b\s*\)', '()', first)
        if ctx.is_dtor:
            first = re.sub(r'\([^)]*\)', '()', first)
        first = re.sub(r'  +', ' ', first).strip()
        lines[func_line_idx] = first

    return '\n'.join(lines)


