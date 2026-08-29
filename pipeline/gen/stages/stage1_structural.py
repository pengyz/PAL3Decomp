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
                # Check if first param is the 'this' pointer
                # For __thiscall, first pointer param is always 'this' regardless of name/type
                is_this_param = ('this' in first_text and '*' in first_text)
                if not is_this_param and '*' in first_text and ctx.cls_name:
                    is_this_param = ctx.cls_name in first_text
                if not is_this_param and '*' in first_text and not ctx.is_free_function:
                    is_this_param = True
                # Also catch degraded this: "int this" (IDA lost pointer type)
                if not is_this_param and 'this' in first_text and not ctx.is_free_function:
                    is_this_param = True
                if is_this_param:
                    if len(params) > 1:
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
                    else:
                        # Only param is 'this' → replace with empty parens content
                        edits.append((first_param.start_byte, first_param.end_byte, b''))

            # Dtor: strip all params
            if ctx.is_dtor and params:
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
        # For __thiscall, first param is always this — match 'ClsName *name'
        if ctx.cls_name:
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


