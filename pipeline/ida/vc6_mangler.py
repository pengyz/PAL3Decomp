"""VC6 mangled name generator for PAL3 decompilation pipeline.
Shared between apply_annotations.py and export_full.py."""
import re

_TC = {
    'void': 'X', 'char': 'D', 'unsigned char': 'E',
    'short': 'F', 'unsigned short': 'G',
    'int': 'H', 'unsigned int': 'I',
    'long': 'J', 'unsigned long': 'K',
    'float': 'M', 'double': 'N', 'bool': '_N',
    'BYTE': 'E', 'WORD': 'G', 'DWORD': 'K', 'BOOL': 'I', 'UINT': 'I',
}
_CC = {'__thiscall': 'A', '__cdecl': 'C', '__stdcall': 'G', '__fastcall': 'I'}

# 0b-②（2026-09-15）：**指针类 typedef** 没有 `*` 后缀，无法走 `ptr > 0` 分支，
# 必须直接给出完整编码。
#
# `LPCSTR` = `const char *` ⇒ `PBD`。
# 实测依据（`tools/mangler_bench.py`，离线复测 56 个 `.obj`）：
#   真实符号 `?LoadResource@UIStatic@@QAEPAVgbVFileSystem@@PBDD@Z` /
#            `?_CalculateUV@_Texture_Info@@QAEPADPBD@Z`
#   签名里是 `LPCSTR lpString`（无 `*`）⇒ 原先走 `ptr == 0` 的兜底 `'H'`（int）。
#   加入后 matched 136 → **139**。
#
# ⚠️ 同族的 `_BYTE`/`CHAR`/`LPSTR`/`_DWORD`/`_WORD` **实测均 +0**
# （captain 试过 `_BYTE=E`/`CHAR=D` 等编码，全部无增益 ⇒ 未落地，避免无证据改动）。
_PTR_TYPEDEF = {
    'LPCSTR': 'PBD',
}
_TC.update(_PTR_TYPEDEF)

# tokens that are part of a type, never a parameter name
_TYPE_WORDS = {
    'int', 'char', 'short', 'long', 'unsigned', 'signed', 'float', 'double',
    'void', 'bool', 'const', 'volatile', 'struct', 'class', 'union', 'enum',
    '__int8', '__int16', '__int32', '__int64', '__wchar_t',
}


def encode_type(t):
    t = t.strip()
    # normalize qualifier placement: the IDA demangler emits trailing forms
    # ('char const * *'); rotate const/volatile tokens to the front so the
    # const-pointer chain encodes correctly ('PBD')
    toks = t.split()
    if 'const' in toks or 'volatile' in toks:
        head = [t2 for t2 in toks if t2 in ('const', 'volatile')]
        rest_toks = [t2 for t2 in toks if t2 not in ('const', 'volatile')]
        t = ' '.join(head + rest_toks)
    is_const = t.startswith('const ')
    if is_const: t = t[6:].strip()
    is_volatile = t.startswith('volatile ')
    if is_volatile: t = t[9:].strip()
    is_ref = t.endswith('&')
    if is_ref: t = t[:-1].strip()
    ptr = 0
    while t.endswith('*'):
        t = t[:-1].strip(); ptr += 1
    tag = None
    if t.startswith('struct ') or t == 'struct':
        tag = 'U'; t = t[7:].strip()
    elif t.startswith('class ') or t == 'class':
        tag = 'V'; t = t[6:].strip()
    code = _TC.get(t)
    # 0b-③（2026-09-15）：**嵌套类**编码。限定名不能原样嵌入。
    # 实测：签名 `AStarPathFinder::NODE *pNode`，真实符号 `?PushOpen@AStarPathFinder@@QAEHPAUNODE@1@@Z`
    # ⇒ 正确编码是 `PAU` + `NODE` + `@1@`（`U`=struct、`1`=嵌套深度），
    #    而原先产出 `PAVAStarPathFinder::NODE@@`（限定名原样嵌入 + 前缀错）。
    # 必须放在 `ptr > 0` 分支**之前**：限定名不在 `_TC` 里，
    # 若先走 `ptr > 0` 就永远到不了这里。
    if code is None and '::' in t and ptr > 0:
        _parts = t.split('::')
        _depth = len(_parts) - 1
        code = 'U' + _parts[-1] + '@%d@' % _depth
    elif code is None and ptr > 0:
        # 0b-①（2026-09-15）：原先一律用 struct 前缀 'U'。
        # MSVC 对 class 用 'V'、对 struct 用 'U'，而 **decomp 签名里拿不到这个区分**：
        # `ida_structs.json` 的 kind **全是 'struct'**（实测 1016/1016，0 个 class），
        # 且 `gbOBBox` 这类真 struct 在签名里也是**裸名**（`gbOBBox *`，无 `struct` 关键字）。
        # ⇒ 只能按多数投票。实测 real `.obj` 符号里 `PAV` : `PAU` = 8 : 2
        #   （PAV: UIListBox/CCBUI/CCBControlWindow/gbRenderEffect/gbGfxManager/
        #          gbVFileSystem/gbMatrixStack + 嵌套反向引用 PAV1@/PAV2@；
        #     PAU: gbOBBox + 嵌套 NODE@1@）。
        # 离线复测（tools/mangler_bench.py）：matched 129 → **136**（+7）。
        # `struct `/`class ` 关键字仍走上面的 tag 分支（优先于此处）。
        code = 'V' + t + '@@'
    elif code is None and tag:
        code = tag + t + '@@'
    elif code is None:
        if t.startswith('unsigned '):
            code = _TC.get(t[9:].strip())
        if code is None:
            code = 'H'
    if is_ref:
        code = 'A' + code
    for _ in range(ptr):
        code = 'P' + ('B' if (is_const and _ == 0) else 'A') + code
    return code


def strip_param_name(p):
    """Strip a trailing parameter name, but only when the last token can
    actually be a name ('unsigned short', 'char const *' etc. are types)."""
    toks = p.strip().rstrip('*').split()
    if toks and toks[-1] in _TYPE_WORDS:
        return p.strip()  # trailing token is a type word — no name present
    m = re.match(r'^(.+\*)\s*\w*$', p)
    if m: return m.group(1).strip()
    m = re.match(r'^(.+?)\s+\w+$', p)
    if m: return m.group(1).strip()
    return p.strip()


def _mangle_class_chain(cls_name):
    """Convert 'AStarPathFinder::NODE' to 'NODE@AStarPathFinder' (MSVC format)."""
    parts = cls_name.split('::')
    return '@'.join(reversed(parts))


def _self_ref_backref(code, cls_name):
    """VC6 对"当前类自身"的类型引用用**回指**编码（`1@`），而不是把类名写全。

    实测（F61，第 109 轮）：`static SceneMgr *SceneMgr::ClearInactiveRoles()` 的真实 obj 符号是
    `?ClearInactiveRoles@SceneMgr@@SAPAV1@XZ`（返回类型 = `PAV1@`），而本 mangler 原先产出
    `?ClearInactiveRoles@SceneMgr@@SAPAVSceneMgr@@XZ` ⇒ `compare_pal3.build_mangled_map` 的键
    对不上 obj 符号 ⇒ 该函数被判 unmatched（实测 matched 249→248、unmatched 40→41）。
    只处理**当前类自身**（`cls_name` 最后一段）：父类/嵌套类引用的编号语义无实测证据，保持原样。
    """
    if not cls_name:
        return code
    last = cls_name.split('::')[-1]
    for tag in ('V', 'U'):
        old = tag + last + '@@'
        if code.endswith(old):
            return code[:-len(old)] + tag + '1@'
    return code


def mangle(cls_name, method_name, sig, cv='', virtual_=False, static_=False):
    """Compute VC6 mangled name for a class method.

    Args:
        cls_name: Class name — may include :: for nested (e.g. 'AStarPathFinder::NODE')
        method_name: Method name (e.g. 'FindInOpen'); a name equal to the
            last class segment mangles as a ctor ('??0'), '~Name' as dtor ('??1')
        sig: Signature string (e.g. 'int __thiscall(int nTileIdx)')
        cv: '' | 'const' | 'volatile' | 'const volatile' — method cv-qualifier
        virtual_: virtual method (prefix letter 'U' instead of 'Q')
        static_: static method (prefix 'SA'; no cv, no thiscall marker)

    Returns:
        Mangled name string (e.g. '?FindInOpen@NODE@AStarPathFinder@@QAEHH@Z')
    """
    cls_chain = _mangle_class_chain(cls_name)

    paren = sig.find('(') if sig else -1
    if paren == -1:
        return '?' + method_name + '@' + cls_chain + '@@QAEXXZ'

    prefix = sig[:paren].strip()
    pstr = sig[paren + 1:sig.rfind(')')] if sig.rfind(')') > paren else ''

    # IDA signatures may carry 'virtual'/'static' keywords — not part of
    # the type encoding (virtuality is the virtual_/static_ flags)
    for kw in ('virtual', 'static'):
        prefix = re.sub(r'\b%s\s+' % kw, '', prefix)

    cc = '__thiscall'
    for c in ['__thiscall', '__cdecl', '__stdcall', '__fastcall']:
        if c in prefix: cc = c; break

    ret = prefix.replace(cc, '').strip()
    ret = re.sub(r'\w+::\w+', '', ret).strip()
    pstr = re.sub(r'\w+\s*\*\s*(?:__hidden\s+)?this\s*,?\s*', '', pstr)

    params = []
    if pstr and pstr.strip() not in ('', 'void'):
        depth = 0; cur = ''
        for ch in pstr:
            if ch in '<([': depth += 1; cur += ch
            elif ch in '>)]': depth -= 1; cur += ch
            elif ch == ',' and depth == 0:
                if cur.strip(): params.append(cur.strip()); cur = ''
            else: cur += ch
        if cur.strip(): params.append(cur.strip())

    # special member names: ctor ??0 / dtor ??1 — chain only, no return code
    last_seg = cls_name.split('::')[-1]
    special = None
    if method_name == last_seg:
        special = '0'
    elif method_name == '~' + last_seg:
        special = '1'

    # 0b-④（2026-09-15）：**scalar deleting destructor**（`??_G<Cls>@@UAEPAXI@Z`）。
    # decomp 用 `_scalar_dtor` / `_sdtor` / `_sdtor_NN` 命名表示它
    # （实测 UIWnd 有 `_sdtor_14/_sdtor_27/_sdtor_28`，UIButton 有 `_scalar_dtor`）。
    # 形态完全一致：15/15 个 obj 符号都是 `??_G<Cls>@@UAEPAXI@Z`
    #   `U`=virtual、`AE`=__thiscall(虚)、`PAX`=void*、`I`=unsigned int(flags)
    # ⇒ 可直接机械生成，无需从签名推导。
    # ⚠️ 供给限制：decomp 只对部分类给出了 `_scalar_dtor`/`_sdtor` 名
    # （UIWnd 有、CEffGroupNode/CScreenModeNode/UIPushButton **没有**）
    # ⇒ 本规则只能覆盖有供给的那些（captain 实测），无供给的属**数据缺口**。
    if re.match(r'^_s(dtor|calar_dtor)(_\d+)?$', method_name):
        return '??_G' + '@'.join(reversed(cls_name.split('::'))) + '@@UAEPAXI@Z'

    if special:
        r = '??' + special + '@'.join(reversed(cls_name.split('::'))) + '@@'
    else:
        r = '?' + method_name + '@' + cls_chain + '@@'

    if static_:
        r += 'SA'
    else:
        cvl = {'': 'A', 'const': 'B', 'volatile': 'C',
               'const volatile': 'D'}.get(cv, 'A')
        r += ('U' if virtual_ else 'Q') + cvl + 'E'

    if special:
        r += '@'                       # ctors/dtors carry no return type
        if not params:
            r += 'XZ'                  # void parameter list
        else:
            r += ''.join(encode_type(strip_param_name(p)) for p in params) + '@Z'
        return r

    r += _self_ref_backref(encode_type(ret), cls_name)
    if not params:
        r += 'XZ'   # void parameter list: 'X' + 'Z' (no '@' terminator)
    else:
        r += ''.join(_self_ref_backref(encode_type(strip_param_name(p)), cls_name)
                     for p in params) + '@Z'
    return r
