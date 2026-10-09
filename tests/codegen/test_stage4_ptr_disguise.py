"""任务 1（UIPushButton ③ tagRECT* 错误 cast）：stage4 指针伪装改写单元测试。

判据**三条合取**（计划写死；宁可漏，不可错），缺一不改：
  ① 左值是 tagRECT 字段（`->left`/`->top`/`->right`/`->bottom`，且 base 静态类型 `tagRECT *`）
  ② 右值类型是类指针（如 `gbTexture *`；整数/char*/void* 不算）
  ③ 同一局部变量在二进制步长为 4 —— objdump 实证白名单（stage4 内 `_PTR_DISGUISE_STRIDE4`）
     + 同名变量在本函数有 `v = (T *)((char *)v + 4)` 步进形

改写形（等价变换：地址与写入值逐位不变）：
  `p->left = X;`  ⇒  `*(DWORD *)((char *)p + 0*4) = (DWORD)X;`
  （字段序号 n：left=0 / top=1 / right=2 / bottom=3 ⇒ `+ n*4` = tagRECT 字段字节偏移）

两条绿路都要跑：
  python -m pytest --assert=plain tests/codegen/test_stage4_ptr_disguise.py -v
  python3 tests/codegen/test_stage4_ptr_disguise.py
"""
import sys
from pathlib import Path

# Setup import paths（与 tests/codegen/test_stage5.py 同法）
PROJECT_ROOT = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(PROJECT_ROOT / "pipeline" / "gen"))
sys.path.insert(0, str(PROJECT_ROOT / "pipeline"))
sys.path.insert(0, str(PROJECT_ROOT))

from stages.stage4_substitution import _collect_ptr_disguise_edits, _parser


class _Ctx:
    """已核证站点的最小 ctx —— 判据③白名单键 = (cls_name, method_name, 变量名)。"""
    cls_name = 'UIPushButton'
    method_name = 'CreateWithTextures'
    sig = ''
    is_free_function = False


_STMT_LINE = 4  # harness 内目标语句行号（0 起；改写不新增换行 ⇒ 抽取稳定）


def rewrite(src):
    """把语句放进**已核证站点**（UIPushButton::CreateWithTextures / p_m_rect）语境后改写。

    harness = 函数签名 + `tagRECT *p_m_rect;`（判据①需要静态类型）
            + `p_m_rect = (tagRECT *)((char *)p_m_rect + 4);`（判据③的步长 4 步进形）
            + 目标语句。返回**目标语句**改写后的文本。
    """
    code = (
        "void UIPushButton::CreateWithTextures(int id, void *pRect, "
        "gbVFileSystem *parent, const char *pszName, char pData)\n"
        "{\n"
        "  tagRECT *p_m_rect; // esi\n"
        "  p_m_rect = (tagRECT *)((char *)p_m_rect + 4);\n"
        "  %s\n"
        "}\n" % src
    )
    code_bytes = code.encode('utf-8')
    tree = _parser.parse(code_bytes)
    edits = _collect_ptr_disguise_edits(code_bytes, tree, _Ctx())
    out = code_bytes
    for start, end, replacement in sorted(edits, reverse=True):
        out = out[:start] + replacement + out[end:]
    return out.decode('utf-8').splitlines()[_STMT_LINE].strip()


def test_tagrect_disguise_on_pointer_array():
    """简报步骤 1（计划裁决：原文 `or` 太宽会让错误实现通过 ⇒ 改精确断言）。"""
    src = "p_m_rect->left = gfxMgr->NewTexture(v11);"
    out = rewrite(src)
    assert '->left' not in out          # 不得再有 tagRECT 字段访问
    assert '(DWORD)' in out             # 必须是精确的 DWORD 形（不用 or）


def test_tagrect_field_with_non_pointer_rhs_untouched():
    """判据②不全：右值非类指针 ⇒ 原样不动（宁可漏，不可错）。"""
    src = "p_m_rect->left = 3;"
    assert rewrite(src) == src


def test_tagrect_disguise_exact_dword_double_slot_form():
    """改写形钉死：左值 `*(DWORD *)((char *)p + n*4)`（双槽形，步长 4 与二进制一致），
    右值 `(DWORD)` 显式转换（指针→DWORD 不产码；缺它 C2440 只是换了个说法）。"""
    assert rewrite("p_m_rect->left = gfxMgr->NewTexture(v11);") == (
        "*(DWORD *)((char *)p_m_rect + 0*4) = (DWORD)gfxMgr->NewTexture(v11);")
    # `->right` = tagRECT 字段序号 2（字节偏移 +8）⇔ 二进制 `mov [esi+0x8],eax` 槽位
    assert rewrite("p_m_rect->right = gfxMgr->NewTexture(v11);") == (
        "*(DWORD *)((char *)p_m_rect + 2*4) = (DWORD)gfxMgr->NewTexture(v11);")


def test_b_family_form_untouched():
    """B 族形（`LoadTextureByName`@0x442480 的 `*(_DWORD *)this->m_caption = ...`）原样保留：
    判据①不全（非 tagRECT 字段访问，是 DWORD 指针解引用 lvalue）⇒ 不改；
    其真根因在 stage3 虚表改名丢补偿转换（另立 Task 1b），不在本分支越界处理。"""
    src = "*(_DWORD *)this->m_caption = gfxMgr->NewTexture(v);"
    assert rewrite(src) == src


def test_non_tagrect_base_untouched():
    """判据①不全：base 静态类型不是 `tagRECT *`（如 `AStarPathFinder::STACK *Stack`
    的 `Stack->top = ...`）⇒ 原样不动 —— 字段名同名也不改。"""
    src = "Stack->top = v;"
    assert rewrite(src) == src


def test_non_call_integral_rhs_untouched():
    """判据②不全的另一形：右值是显式整数转换（如 `p_m_rect->right = (LONG)ParentData;`
    —— 现编译通过、无 C2440）⇒ 原样不动。"""
    src = "p_m_rect->right = (LONG)ParentData;"
    assert rewrite(src) == src


if __name__ == '__main__':
    _fns = [(n, f) for n, f in sorted(globals().items())
            if n.startswith('test_') and callable(f)]
    for _name, _fn in _fns:
        _fn()
        print('PASS', _name)
    print('ALL PASS (%d tests)' % len(_fns))
