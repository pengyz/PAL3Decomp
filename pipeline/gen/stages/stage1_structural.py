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


def _has_string_literal(node):
    """[T4-P2 守卫] 调用内含 string_literal → 不剥(字面量 '::~~' 形假阳)。"""
    if node.type == 'string_literal':
        return True
    return any(_has_string_literal(c) for c in node.children)


def _callee_is_dtor_call(call_node):
    """callee 是否析构调用: function 文本含 '::~~' 形, 或 ??_M 族
    (向量析构迭代器——tree-sitter 对 ?? 开头可能解析失败, 文本兜底)。"""
    fn = call_node.child_by_field_name('function')
    if fn is None:
        t = call_node.text.decode('utf-8', 'replace')
        return t.lstrip().startswith('??_M')
    ftext = fn.text.decode('utf-8', 'replace')
    # 注意: function 字段文本不含调用括号(括号属 call 层)——拼 '(' 适配尾部判定
    return ('::~' in ftext and re.search(r'~\w+\s*\(', ftext + '(')) or ftext.startswith('??_M')


def _stmt_span(stmt, code_bytes):
    """语句删除 span: 并吞前导空白/换行。"""
    _s = stmt.start_byte
    while _s > 0 and code_bytes[_s - 1:_s] in (b' ', b'\t'):
        _s -= 1
    if _s > 0 and code_bytes[_s - 1:_s] == b'\n':
        _s -= 1
    return (_s, stmt.end_byte)


def _dtor_implicit_strip_spans(body_node, code_bytes):
    """[C8 4d 纯函数] dtor 定义体的隐式析构剥离 span 集合(供单测)。

    形状守卫(T4-P2): ①整句剥仅限 单一直接析构调用; ②调用内含 string_literal
    不剥; ③逗号表达式=部分剥(析构部分+相邻逗号, 用户码保留); ④ERROR 节点
    ??_M 开头文本兜底剥。用户码调用(Reset/ClearAttackSequence 等)永不剥。
    """
    spans = []
    for stmt in body_node.children:
        if stmt.type == 'ERROR':
            # ??_M 形跨双节点: ERROR('??') + declaration(余行含';')——span 并入下一兄弟
            t = stmt.text.decode('utf-8', 'replace')
            if t.lstrip().startswith('??'):
                _s, _e = stmt.start_byte, stmt.end_byte
                nxt = stmt.next_sibling
                if nxt is not None and nxt.type == 'declaration':
                    _e = nxt.end_byte
                _ws = _s
                while _ws > 0 and code_bytes[_ws - 1:_ws] in (b' ', b'\t'):
                    _ws -= 1
                if _ws > 0 and code_bytes[_ws - 1:_ws] == b'\n':
                    _ws -= 1
                spans.append((_ws, _e))
            continue
        if stmt.type != 'expression_statement':
            continue
        exprs = [c for c in stmt.children if c.type != ';']
        if len(exprs) == 1 and exprs[0].type == 'call_expression':
            call = exprs[0]
            if _callee_is_dtor_call(call) and not _has_string_literal(call):
                spans.append(_stmt_span(stmt, code_bytes))
            continue
        if len(exprs) == 1 and exprs[0].type == 'comma_expression':
            cx = exprs[0]
            parts = [c for c in cx.children if c.type != ',']
            dtor_parts = [p for p in parts
                          if p.type == 'call_expression'
                          and _callee_is_dtor_call(p)
                          and not _has_string_literal(p)]
            keep = [p for p in parts if p not in dtor_parts]
            if dtor_parts and not keep:
                spans.append(_stmt_span(stmt, code_bytes))
            elif dtor_parts and keep:
                for p in dtor_parts:
                    prev_c, next_c = p.prev_sibling, p.next_sibling
                    if prev_c is not None and prev_c.type == ',':
                        spans.append((prev_c.start_byte, p.end_byte))
                    elif next_c is not None and next_c.type == ',':
                        spans.append((p.start_byte, next_c.end_byte))
                    else:
                        spans.append((p.start_byte, p.end_byte))
            continue
    return spans


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


def _ensure_stdcall_def(code, ctx):
    """[R92 2026-10-24] __stdcall 自由函数定义侧 cc 回填（幂等）。

    stage1 无条件剥定义行 cc（:105 树解析预剥 + :379 重建剥）——对成员无害
    （__thiscall 隐式、__cdecl 默认），但 **__stdcall 自由函数**的声明侧
    （data.py free_func_sigs）保留 cc ⇒ 定义侧缺修饰符 ⇒ MSVC6
    `C2373 redefinition; different type modifiers`（实测 ArraySort/EnumJoystick/
    WinProc/StrCopyRange/InputUpdate 5 处，free_functions.cpp）。
    判据：ctx.is_free_function 且 sig 明写 __stdcall ⇒ 定义行名字前回填。
    """
    if not getattr(ctx, 'is_free_function', False):
        return code
    if '__stdcall' not in (ctx.sig or ''):
        return code
    _fn = re.escape(getattr(ctx, 'method_name', '') or '')
    if not _fn:
        return code
    out = code.split('\n')
    for i, l in enumerate(out):
        if re.match(r'^\s*[A-Za-z_][\w \t\*&]*?\b%s\s*\(' % _fn, l) \
                and '__stdcall' not in l:
            out[i] = re.sub(r'(\b%s\s*\()' % _fn, r'__stdcall \1', l, count=1)
            break
    return '\n'.join(out)


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
        from pipeline.gen.normalization import strip_return_ptr as _srp
        code = _srp(code)  # 单点律收编(治理 2026-11-10)
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
        return _ensure_stdcall_def(_regex_fallback(code, ctx), ctx)

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
    _is_del_dtor = False          # [T23-F1] 标量删除析构（保留返型）

    if declarator and not ctx.is_free_function:
        # Get the function name node
        name_node = None
        for child in declarator.children:
            if child.type in ('qualified_identifier', 'identifier', 'field_identifier'):
                name_node = child
                break

        if name_node:
            current_name = name_node.text.decode('utf-8')
            # [N18 dtor 源级化 2026-11-19] deleting 形 dtor（??_G 产物，flags 含
            # deleting 或 sig 恰为 (this, 一标量 flags 形参)）不再改名 _sdtor_
            # call_dtor——按 VC6 dtor 规则集（六形态测试件实证），deleting 形=
            # 编译器织入物载体：剥 flags 形参/条件删尾/return this 织入物，还原
            # **源码唯一析构** ~Cls() 定义。头侧 virtual ~Cls()（槽位循环唯一
            # 所有者）与定义天然同形，T23-F1 的保参改名+头缺声明死锁（C2039/
            # C2673×45, Actor 0x4c9470 案）根消。MSVC6 自源再生 ??_G/??_E，
            # S4 字节匹配兜底。
            _is_del_dtor = False
            if ctx.is_dtor:
                # [N18 决策源修正 2026-11-19·用户质询] deleting 判定主源=注解
                # flags(ctx.flags, ida_structs 通道单向流); 语料 sig 推断仅作
                # 通道缺失(ctx.flags is None)降级——两层各判会造成头体分裂
                # (ParticleEffect 0x4bd850 实证: flags=['dtor'] 无 deleting 而
                # 语料呈 (this,int) → stage1 剥/其他层不剥)
                _fl = getattr(ctx, 'flags', None)
                if _fl is not None:
                    _is_del_dtor = 'deleting' in _fl
                else:
                    _sm = re.search(r'\((.*)\)\s*$', getattr(ctx, 'sig', '') or '')
                    _spl = [x.strip() for x in (_sm.group(1).split(',') if _sm else []) if x.strip()]
                    _nonthis = [x for x in _spl if not re.search(r'\bthis\s*$', x)]
                    _is_del_dtor = bool(_nonthis)
            _mname = ctx.method_name if ctx.method_name.startswith('~') else (
                '~' + ctx.cls_name if _is_del_dtor else ctx.method_name)
            expected_name = '%s::%s' % (ctx.cls_name, _mname)

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
                    # [T23-F1] dtor 路径与非 dtor **统一**：只剥 this 槽首参，
                    # **保留 params[1+]**（flags 形参是真栈实参——A 级：
                    # 0x411bd8 `test BYTE PTR [esp+0x8],0x1` 读栈槽 flags；
                    # 对照 Destroy_12(char a2) 形态，保留更符合字节语义）。
                    # 原「strip all params」整列表裸丢 ⇒ params[1+] 体内引用
                    # 绑到同名全局（nVal1 命中 globals.h:1157 `extern const int
                    # nVal1; // 0x56fd34`）= 活体静默腐蚀（T22 F1 blocker）。
                    # [T20] 首参（this 槽）名 → this 重命名（Block 案）：
                    # 只丢参不改名 ⇒ 体内引用落到同名全局/未声明——语义腐蚀。
                    # A 级：Block=register 16（ECX 槽）⇒ __thiscall this 实证。
                    # AST 标识符逐个改名：跳过成员/限定访问字段位、声明名字位、
                    # 首参声明自身（防遮蔽/声明误改）。
                    _pname_m = re.search(r'(\w+)\s*$', first_text)
                    _pname = _pname_m.group(1) if _pname_m else None
                    if _pname and _pname != 'this':
                        _rename_param_refs_to_this(func_def, first_param,
                                                   _pname, edits)
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

            # [T23-F1] 原「Dtor: strip all params」整列表裸丢已删——params[1+]
            # 是真栈实参（flags 形参），须保留（对照 Destroy_12 形态）。

    # 4. Remove return type for ctor/dtor
    # [N18 dtor 源级化 2026-11-19] deleting 形 dtor 同样发 dtor 语法（~Cls()），
    # 返型剥除——flags 形参织入物由 4c 段剥离
    if (ctx.is_ctor or ctx.is_dtor):
        # Remove everything before the function declarator (return type + CC)
        if declarator:
            # Remove from start of func_def to start of declarator
            pre_start = func_def.start_byte
            pre_end = declarator.start_byte
            if pre_end > pre_start:
                edits.append((pre_start, pre_end, b''))

    # 4d. [C8 源模型修正 2026-11-21] 隐式析构剥离（非删除式 dtor 定义）:
    #   源模型唯一析构体=仅用户代码——hexrays 渲染的显式析构调用
    #   (this->基::~基() / 成员 dtor 渲染 / ??_M 向量析构迭代器) 全为编译器
    #   隐式再生物: 保留在源=双重析构(字节+语义双错, UISceneMap/CCBUICtrl
    #   案实证)。删除判据: 语句为纯析构调用(整句 expression_statement 且
    #   callee 含 '::~~' 形或 ??_M 族)。用户代码调用(ClearAttackSequence/
    #   Reset 等)不受影响。删除式形(decl_only)不发射无需此剥。
    if ctx.is_dtor and not _is_del_dtor:
        _body_node = func_def.child_by_field_name('body')
        if _body_node is not None:
            for _s, _e in _dtor_implicit_strip_spans(_body_node, code_bytes):
                edits.append((_s, _e, b''))

    # Apply edits in reverse order
    result = code_bytes
    for start, end, replacement in sorted(edits, reverse=True):
        result = result[:start] + replacement + result[end:]

    code = result.decode('utf-8')

    # 4c. [N18 dtor 源级化 2026-11-19] deleting 形织入物剥离：
    #   ① flags 形参（params[1+]）整剥 + 体内引用改写为字面 flags 值
    #     （体内对形参的唯一合法消费 = test flags&1 → 条件 delete(this)；
    #      语料渲染为 `if ((a2 & 1) != 0) operator delete(this);`——改为
    #      独立 if 块删除，不保留 0/1 分支语义（源码本无此代码））
    #   ② `return this;` 尾（??_G 返回 this 织入物）→ 删
    #   ③ `if ((a2 & 1) != 0)` 独立语句块（源码本无）→ 删
    if _is_del_dtor:
        # 形参名（语料首非 this 参名，常见 a2/a2a/nVal）
        _sm = re.search(r'\((.*)\)\s*$', getattr(ctx, 'sig', '') or '')
        _spl = [x.strip() for x in (_sm.group(1).split(',') if _sm else []) if x.strip()]
        _nonthis_params = [x for x in _spl if not re.search(r'\bthis\s*$', x)]
        _flag_pnames = [re.search(r'(\w+)\s*$', p).group(1) for p in _nonthis_params
                        if re.search(r'(\w+)\s*$', p)]
        # ② return this 尾
        code = re.sub(r'\n?[ \t]*return this;\s*(?=\n)', '\n', code)
        code = re.sub(r'\n?[ \t]*return \(int\)this;\s*(?=\n)', '\n', code)
        # ③+① 条件 delete(this) 独立语句块（空格宽容: hexrays 渲染
        #   'if ( (a2 & 1) != 0 )' 双括号带空格 / 'if ((a2&1) != 0)' 紧凑两极）
        _flag_tests = [r'\(\s*\(\s*%s\s*&\s*1\s*\)\s*!=\s*0\s*\)' % re.escape(_fp)
                       for _fp in (_flag_pnames or ['a2'])]
        # 退化 this 形（IDA 丢指针型, 首参名恰为类名/Block）: `(*(_BYTE *)&Block & 1) != 0`
        _flag_tests.append(r'\(\s*\(\s*\*\s*\(\s*_BYTE\s*\*\s*\)\s*&\w+\s*&\s*1\s*\)\s*!=\s*0\s*\)')
        # [Blocka 案 2026-11-19] flags 槽渲染名任意化——hexrays saved lvar 消歧名
        #   （IDB 净节点陈旧 lvar 名 Block/Blocka 浮出: Block 全局(globals.json
        #   0x00D8E470)撞名 ⇒ 后缀消歧 Blocka）。织入物判据=结构形态非参数名:
        #   `((<可选 byte cast><任意标识符> & 1) != 0)`。域限制 _is_del_dtor +
        #   N18 裁定（flags 织入物源码本无）⇒ 不会误吞真源码条件删。
        _flag_tests.append(
            r'\(\s*\(\s*(?:\(\s*(?:unsigned\s+__int8|_BYTE)\s*\)\s*)?\w+\s*&\s*1\s*\)\s*!=\s*0\s*\)')
        for _fpr in _flag_tests:
            code = re.sub(
                r'\n?[ \t]*if %s\s*\n?[ \t]*operator delete\((?:this|\w+)\)[ \t]*;[ \t]*\n' % _fpr,
                '\n', code)
            code = re.sub(
                r'\n?[ \t]*if %s\s*\{\s*\n[ \t]*operator delete\((?:this|\w+)\);\s*\n[ \t]*\}[ \t]*\n' % _fpr,
                '\n', code)
        # ① flags 形参从签名剥除（多参逗号链）
        if _flag_pnames:
            def _strip_flag_params(_mc):
                inner = _mc.group(1)
                parts = [p for p in inner.split(',')]
                kept = []
                for ptxt in parts:
                    ptt = ptxt.strip()
                    if 'this' in ptt and '*' in ptt:
                        kept.append(ptt)  # this 槽（若 3 段未剥）
                        continue
                    pn = re.search(r'(\w+)\s*$', ptt)
                    if pn and pn.group(1) in _flag_pnames:
                        continue  # flags 形参剥除
                    # [Blocka 案 2026-11-19] 非 this 参**全剥**——deleting dtor
                    # 定义级签名 = ~Cls()（N18 源级律: ??_G ABI 参皆为织入物）。
                    # 旧按注解名匹配 ⇒ hexrays 消歧名(Blocka≠注解 Block/char)
                    # 失配残段( void *Blocka )= 半剥病灶。体内引用已由尾剥/②清。
                    continue
                return '(%s)' % ', '.join(kept)
            code = re.sub(r'\(([^()]*)\)', _strip_flag_params, code, count=1)

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

    return _ensure_stdcall_def(code, ctx)


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
            # [this@<reg>尾注 2026-11-18] hexrays形 'Cls *this@<ecx>,'——
            #   @<reg>剥除先于此行时this词已裸, 但旧序下@尾巴使\w+捕获'this'后
            #   残留'@<ecx>'→C2143链。正则放宽允许尾注。
            first = re.sub(r'\(\s*' + _cls_pat + r'\s*\*+\s*\w+(?:@<\w+>)?\s*,\s*', '(', first, count=1)
            first = re.sub(r'\(\s*' + _cls_pat + r'\s*\*+\s*\w+(?:@<\w+>)?\s*\)', '()', first, count=1)
        # Fallback: literal 'this' name
        first = re.sub(r'\(\s*\w[\w\s]*\*+\s*this\s*,\s*', '(', first)
        first = re.sub(r'\(\s*\w[\w\s]*\*+\s*this\s*\)', '()', first)
        # Catch 'int this' and other typed this params not matched above
        first = re.sub(r'\(\s*\w[\w\s]+\bthis\b\s*,\s*', '(', first)
        # [续行参数 2026-11-18] 多行签名的续行(2+)同款剥除——L329实错误行是续行
        #   (CreateWithTextures定义首行后), 旧逻辑只剥func_line_idx一行
        for _ci in range(func_line_idx + 1, min(func_line_idx + 12, len(lines))):
            _l2 = lines[_ci]
            if ')' in _l2 and '{' in ''.join(lines[_ci:_ci+3]):
                pass
            if _is_thiscall and ctx.cls_name:
                _cp = re.escape(ctx.cls_name)
                _l2 = re.sub(r'^\s*' + _cp + r'\s*\*+\s*\w+(?:@<\w+>)?\s*,\s*$', '', _l2)
            _l2 = re.sub(r'@<\w+>', '', _l2)
            lines[_ci] = _l2
        first = re.sub(r'\(\s*\w[\w\s]+\bthis\b\s*\)', '()', first)
        if ctx.is_dtor:
            first = re.sub(r'\([^)]*\)', '()', first)
        first = re.sub(r'  +', ' ', first).strip()
        lines[func_line_idx] = first

    return '\n'.join(lines)


