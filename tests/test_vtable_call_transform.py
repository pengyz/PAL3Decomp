"""虚调用转换（三形态识别）—— Task 7 的契约测试。

规格：`docs/superpowers/specs/2026-09-25-vtable-mapping-design.md` §4.3
计划：`docs/superpowers/plans/2026-09-25-vtable-mapping-plan.md` Task 7

# 目标形态

无论输入是三种形态中的哪一种，**输出必须恒为直接虚调用** `obj->MethodName(args)`：

| 形态 | 输入（stage3 解码时的文本） | 输出 |
|---|---|---|
| 1 inline | `(*(R (__thiscall **)(Cls *, ...))(*(_DWORD *)OBJ + N))(OBJ, args)` | `OBJ->Method(args)` |
| 2 局部 vftable 变量 | `v5 = *(T *)OBJ;` … `(*(R (__thiscall **)(Cls *, ...))(v5 + N))(OBJ, args)` | `OBJ->Method(args)` |
| 3 裸 vptr 读 | `(*(R (__thiscall **)(Cls *))(*(void **)(OBJ)))(OBJ)`（偏移 0） | `OBJ->Method(args)` |

形态 3 的**输入侧**由既有 regex（`_fix_ref_params` 的 `X->_tail_000 → *(void**)(X)`）产生，
本任务**保留**该转换，并让解码器认识它的产物（`*(void**)(obj)` 即 vptr 读）。

# 字节偏移语义（二进制实证，勿再引入 `//4`）

`*(_DWORD *)X + 8` 里的 **8 是字节偏移**，不是槽下标：

    二进制 asm（original/PAL3.exe.asm）        Hex-Rays 文本（asm/pal3/decomp/*.json）
    C2DSpark::C2DSpark @0x4D5AB0:
        mov  ecx, dword_BFDA60
        mov  edx, [ecx]                       ⇔   *(int (__thiscall **)(gbGfxManager *, char *))
        call dword ptr [edx+8]                     (*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, aTga)
    ⇒ 8 / 4 = 槽 2 = gbGfxManager::NewTexture(char const *) ✓（实参 aTga 与声明相符）

对照：`AStarPathFinder::TryExpand` @0x4012A0 的 `call dword ptr [eax+4]` ⇔ `*(_DWORD *)this + 4`
（槽 1 = `IsInBounds`，实参 `(this, nTileX, nTileY)` 相符）。

（另一族形态 `obj->__vftable + N` 里的 N 是**槽下标**——那是 vtable 结构体指针的指针运算，
由既有 `_decode_vtbl_call` / `_resolve_vtbl_method` 处理，本文件不改其语义。）

# 名称解析链（不用 mangling）

    类名(cast 首参) → 注解 vtables[0].addr → IDB `vtbl_<ADDR>.data_members` → methods[addr].name

- `vtables[]` 是唯一多态声明点（`vtables` 为空 ⇒ 该类未声明为多态 ⇒ 不转换、记账）；
- IDB 步（`asm/pal3/ida_structs.json` 的 `vtbl_<ADDR>`）必须走通，槽下标必须落在其 `data_members` 内；
- 方法名优先取注解 `methods[槽地址].name`，缺省回落 IDB `data_members[i].name`；
- **`::` 限定一律剥掉** ⇒ 绝不发射 `obj->Base::Method()`（限定调用会抑制虚派发 ⇒ 字节必不匹配）。

# 失败输出契约

识别为虚调用但**无法转换**时：**原文本逐字保留**（不伪造 `_tail_000+off` 之类的裸偏移形态），
并记账到 `data/status/vtable_transform_failures.md`（测试用 tmp 路径注入）。
既有 `__vftable` 路径的 stub 语义（`pal3_vtbl_unk_*`）**逐字不变**——见
`test_existing_vftable_stub_semantics_preserved`。

# 自带 runner

本机 pytest 在 collect 阶段可能崩（见
`docs/knowledge/gotcha_local_pytest_collect_crashes_use_self_runner.md`），
故文件尾自带 runner：`python3 tests/test_vtable_call_transform.py`
"""
import os
import re
import sys
import tempfile
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

from stages import stage3_cleanup as s3  # noqa: E402
from stages.stage3_cleanup import run as stage3_run  # noqa: E402

VTBL_ADDR = '0x0056a600'

# 真实槽名（AStarPathFinder 注解 vtables[0] @0x0056A600：槽0=~AStarPathFinder，
# 槽1(byte4)=IsInBounds，槽2(byte8)=GetHeuristicIdx）。测试把槽0换成 Destroy，
# 以便同一个夹具覆盖"偏移 0 的虚调用"。
FIXTURE_CLS = 'AStarPathFinder'
FIXTURE_BY_ADDR = {1: 'IsInBounds', 2: 'GetHeuristicIdx', 0: 'Destroy'}
FIXTURE_IDB = {0: 'Destroy', 1: 'IsInBounds', 2: 'GetHeuristicIdx'}
# 槽的**函数地址**（真实值：AStarPathFinder 注解 vtables[0] @0x0056A600）
FIXTURE_SLOT_ADDRS = {0: '0x00401030', 1: '0x004014e0', 2: '0x004014f0'}


def _members(v):
    """{slot: name} 或 [name] → 按槽下标排好的 list。"""
    if isinstance(v, dict):
        n = (max(v) + 1) if v else 0
        return [v.get(i, '') for i in range(n)]
    return list(v or [])


def _index(cls=FIXTURE_CLS, addr=VTBL_ADDR, by_addr=None, idb=None,
           class_addr=None, decl=None, slot_addrs=None):
    """构造注入用的 `_VTBL_INDEX`（形状见 `_load_vtbl_index`）。

    默认 `class_decl` / `class_slot_addrs` 由夹具自身派生 ⇒ 每个夹具名字都
    "声明在自己的槽地址上"（即头文件会发它的情形）；护栏用例显式传入冲突表。
    """
    if by_addr is None:
        by_addr = {addr: dict(FIXTURE_BY_ADDR)}
    if idb is None:
        idb = {addr: dict(FIXTURE_IDB)}
    if class_addr is None:
        class_addr = {cls: addr} if cls else {}
    idb = {k: _members(v) for k, v in idb.items()}
    if slot_addrs is None:
        slot_addrs = dict(FIXTURE_SLOT_ADDRS)
    if decl is None:
        decl = {}
        for members in idb.values():
            for i, nm in enumerate(members):
                if nm and i in slot_addrs:
                    decl.setdefault(nm, []).append(slot_addrs[i])
    known = bool(cls) and cls in class_addr
    return {
        'class_addr': class_addr,
        'by_addr': by_addr,
        'idb_members': idb,
        'class_slot_addrs': {cls: dict(slot_addrs)} if known else {},
        'class_decl': {cls: {k: list(v) for k, v in decl.items()}} if known else {},
    }


class _Ctx:
    """最小 ctx（约定同 tests/test_vtbl_stub_dedup.py）+ 台账路径注入。"""

    def __init__(self, cls='CCBSkillWindow', method='Create', log=None):
        self.cls_name = cls
        self.method_name = method
        self.sig = ''
        self.is_ctor = False
        self.is_dtor = False
        self.is_free_function = False
        self.stub_registry = set()
        # 显式路径注入 ⇒ 测试绝不写仓库真台账
        self.vtable_failure_log = log


class _Harness:
    """注入 `_VTBL_INDEX` + 每次换一个 tmp 台账路径。"""

    def __init__(self, index, tmpdir):
        self.index = index
        self.tmpdir = tmpdir
        self._n = 0

    def ctx(self, **kw):
        self._n += 1
        log = os.path.join(self.tmpdir, 'failures_%d.md' % self._n)
        kw.setdefault('log', log)
        ctx = _Ctx(**kw)
        ctx._log_path = log
        return ctx

    def __enter__(self):
        self._saved = s3._VTBL_INDEX
        s3._VTBL_INDEX = self.index
        return self

    def __exit__(self, *exc):
        s3._VTBL_INDEX = self._saved
        return False


def _ledger(ctx):
    try:
        return Path(ctx._log_path).read_text(encoding='utf-8')
    except OSError:
        return ''


def _wrap(body, cls='CCBSkillWindow', method='Create', extra_decls=''):
    return ("int %s::%s(int rc, int nVal)\n{\n%s\n%s\n  return 0;\n}\n"
            % (cls, method, extra_decls, body))


def _strip_cc(text):
    """复刻 `run()` 开头的调用约定剔除（`__thiscall ` → 空），用于比对"原文保留"。"""
    return re.sub(r'__thiscall\s+', '', text)


def _line_with(out, needle, skip_signature=True):
    for line in out.split('\n'):
        if needle in line:
            if skip_signature and line.strip().startswith('int '):
                continue
            return line.strip()
    return ''


# ============================================================
# 形态 1：inline vptr 读
# ============================================================

def test_form1_inline_vptr_offset_becomes_direct_virtual_call():
    """真实样本（AStarPathFinder::TryExpand @0x4012A0，`call [eax+4]`）。"""
    body = ("  (*(int (__thiscall **)(AStarPathFinder *, int, int))"
            "(*(_DWORD *)this + 4))(this, nTileX, nTileY);")
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        out = stage3_run(_wrap(body), h.ctx())
    line = _line_with(out, '->IsInBounds(')
    assert line == 'this->IsInBounds(nTileX, nTileY);', out


def test_form1_byte_offset_is_divided_by_four_to_get_slot():
    """`+8` ⇒ 槽 2（不是槽 8）。退化回 `//4` 之外的任何解释都会选错方法名。"""
    body = ("  (*(int (__thiscall **)(AStarPathFinder *, int, int))"
            "(*(_DWORD *)this + 8))(this, nGoalX, nGoalY);")
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        out = stage3_run(_wrap(body), h.ctx())
    assert 'this->GetHeuristicIdx(nGoalX, nGoalY);' in out, out
    assert 'IsInBounds' not in out, out


def test_form1_void_cast_and_parenthesized_object():
    """`*(void **)(obj)` 形态（形态 3 转换产物）+ 带括号的自身实参。"""
    body = ("  (*(void (__thiscall **)(AStarPathFinder *, int))"
            "(*(void **)(this->m_pFinder) + 4))(this->m_pFinder, 1);")
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        out = stage3_run(_wrap(body), h.ctx())
    assert 'this->m_pFinder->IsInBounds(1);' in out, out


def test_form1_vptr_member_tail_000():
    """真实样本（C2DSpark::C2DSpark @0x4D5AB0，`call [edx+8]`：槽2=NewTexture）。"""
    idx = _index(cls='gbGfxManager', addr='0x0056f824',
                 by_addr={'0x0056f824': {2: 'NewTexture'}},
                 idb={'0x0056f824': {0: '_gbGfxManager', 1: 'MsgProc', 2: 'NewTexture'}})
    body = ("  result = (gbTexture *)(*(int (__thiscall **)(gbGfxManager *, char *))"
            "(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, aTga);")
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td) as h:
        out = stage3_run(_wrap(body), h.ctx())
    assert 'gfxMgr->NewTexture(aTga)' in out, out


# ============================================================
# 形态 2：局部 vftable 变量
# ============================================================

def test_form2_local_vftable_variable():
    """`v5 = *(T *)obj;` … `(*(fn **)(Cls *, ...))(v5 + N))(obj, args)`。

    这是实测最大的一族（既有两条解码路径都锚定 `__vftable` 文本 ⇒ 全部落空）。
    """
    body = ("  (*(int (__thiscall **)(AStarPathFinder *, int, int))(v5 + 8))"
            "(this, nGoalX, nGoalY);")
    decls = "  int v5;\n  v5 = *(int *)this;"
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        out = stage3_run(_wrap(body, extra_decls=decls), h.ctx())
    assert 'this->GetHeuristicIdx(nGoalX, nGoalY);' in out, out
    # 非虚调用不得被改写
    assert 'v5 = *(int *)this;' in out, out


def test_form2_local_vftable_variable_offset_zero():
    """形态 2 的偏移 0 分支：`v5 + 0` 与裸 `v5` 等价。"""
    body = "  (*(void (__thiscall **)(AStarPathFinder *, int))(v5))(this, 7);"
    decls = "  int v5;\n  v5 = *(int *)this;"
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        out = stage3_run(_wrap(body, extra_decls=decls), h.ctx())
    assert 'this->Destroy(7);' in out, out


def test_form2_local_from_vftable_member_is_tracked():
    """形态 2 的源可以是 `obj->_tail_000`（形态 3 的输入侧），不是只有裸 deref。"""
    idx = _index(cls='gbGfxManager', addr='0x0056f824',
                 by_addr={'0x0056f824': {2: 'NewTexture'}},
                 idb={'0x0056f824': {0: '_gbGfxManager', 1: 'MsgProc', 2: 'NewTexture'}})
    body = ("  (*(int (__thiscall **)(gbGfxManager *, char *))(v3 + 8))(gfxMgr, aTga);")
    decls = "  int v3;\n  v3 = *(_DWORD *)gfxMgr->_tail_000;"
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td) as h:
        out = stage3_run(_wrap(body, extra_decls=decls), h.ctx())
    assert 'gfxMgr->NewTexture(aTga)' in out, out


# ============================================================
# 形态 3：裸 vptr 读（偏移 0）
# ============================================================

def test_form3_bare_vptr_read_slot_zero():
    """`(*(R (__thiscall **)(Cls *))(*(void **)(OBJ)))(OBJ)`（偏移 0）。"""
    body = ("  (*(void (__thiscall **)(AStarPathFinder *, int))"
            "(*(void **)(this)))(this, 3);")
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        out = stage3_run(_wrap(body), h.ctx())
    assert 'this->Destroy(3);' in out, out


def test_form3_existing_tail_000_fold_is_preserved():
    """既有 regex（`X->_tail_000 → *(void**)(X)`）必须原样保留（R11：不推倒重来）。"""
    out = s3._fix_ref_params('x = obj->_tail_000;\n')
    assert '*(void**)(obj)' in out, out


def test_form1_complex_object_chain():
    """真实样本（CCBUI 系）：对象链是数组成员访问，模板/`[]` 必须原样带出。"""
    body = ("  (*(void (__thiscall **)(AStarPathFinder *, int))"
            "(*(_DWORD *)this->m_Slots[17].m_Finder + 4))(this->m_Slots[17].m_Finder, 278);")
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        out = stage3_run(_wrap(body), h.ctx())
    assert 'this->m_Slots[17].m_Finder->IsInBounds(278);' in out, out


# ============================================================
# 名称解析链
# ============================================================

def test_name_chain_uses_methods_table_of_slot_address():
    """链：类 → vtables[0].addr → IDB `vtbl_<ADDR>.data_members` → `methods[addr].name`。"""
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        name, reason = s3._resolve_vtbl_name_chain('AStarPathFinder', 8)
    assert (name, reason) == ('GetHeuristicIdx', None), (name, reason)


def test_name_chain_falls_back_to_idb_data_member_name():
    """注解 methods 缺该槽名时，用 IDB `vtbl_<ADDR>.data_members[i].name`（链的第二步）。"""
    idx = _index(by_addr={VTBL_ADDR: {1: 'IsInBounds'}})
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td):
        name, reason = s3._resolve_vtbl_name_chain('AStarPathFinder', 8)
    assert (name, reason) == ('GetHeuristicIdx', None), (name, reason)


def test_name_chain_rejects_name_declared_at_other_address():
    """头文件一致性护栏（**真实反例**，2026-09-25 实测）。

    `UIWnd` 槽3（0x00442420）在 IDB `vtbl_0056AE2C` 里叫 `Destroy`，但该类的
    `Destroy` 声明在 0x0043BBB0 且**非 virtual**（`pal3/src/UI/UIWnd.h:45`），
    槽3 在头文件里是 `virtual void slot_3()` ⇒ 发射 `p->Destroy(...)` 会绑到
    **另一个非虚函数**（直接调用 ⇒ 字节必不匹配 + C2660）⇒ 必须拒绝并记账。
    """
    idx = _index(cls='UIWnd', addr='0x0056ae2c',
                 by_addr={'0x0056ae2c': {}},
                 idb={'0x0056ae2c': {0: 'ShowWindow', 1: 'Render', 2: 'Update_2ff0',
                                     3: 'Destroy'}},
                 slot_addrs={0: '0x00445e70', 1: '0x00443200',
                             2: '0x00442ff0', 3: '0x00442420'},
                 decl={'ShowWindow': ['0x00445e70'], 'Destroy': ['0x0043bbb0']})
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td):
        name, reason = s3._resolve_vtbl_name_chain('UIWnd', 12)
    assert name is None and reason == 'name_declared_at_other_address', (name, reason)


def test_name_chain_rejects_name_not_declared_for_class():
    """名字在本类完全没有声明 ⇒ 头文件只会发占位槽名 ⇒ 拒绝（不发射 C2039）。"""
    idx = _index(decl={})
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td):
        name, reason = s3._resolve_vtbl_name_chain('AStarPathFinder', 8)
    assert name is None and reason == 'name_not_declared_for_class', (name, reason)


def test_name_chain_accepts_idb_name_declared_at_slot_address():
    """IDB 槽名 + 该名字确实声明在本槽地址 ⇒ 放行（gbGfxManager（合成表）实测形状）。

    gbGfxManager 的注解 vtables 是**合成地址**（0x00010000…），IDB 有对应的
    `vtbl_00010000`；槽2 = NewTexture 在 `include/gbengine/gbGfxManager.h:146` 是 virtual。
    """
    idx = _index(cls='gbGfxManager', addr='0x00010000',
                 by_addr={'0x00010000': {}},
                 idb={'0x00010000': {0: '_gbGfxManager', 1: 'MsgProc', 2: 'NewTexture'}},
                 slot_addrs={0: '0x00010000', 1: '0x00010001', 2: '0x00010002'},
                 decl={'NewTexture': ['0x00010002'], 'MsgProc': ['0x00010001']})
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td):
        name, reason = s3._resolve_vtbl_name_chain('gbGfxManager', 8)
    assert (name, reason) == ('NewTexture', None), (name, reason)


def test_name_chain_requires_idb_vtbl_struct():
    """IDB 无 `vtbl_<ADDR>` ⇒ 链断（槽存在性无法在二进制侧确认）⇒ 失败并留原因。"""
    idx = _index(idb={})
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td):
        name, reason = s3._resolve_vtbl_name_chain('AStarPathFinder', 8)
    assert name is None and reason == 'no_idb_vtbl_struct', (name, reason)


def test_name_chain_reports_reasons():
    """四种失败原因必须可区分（台账要能指导注解补全）。"""
    cases = [
        (_index(class_addr={}), 'NoVtblClass', 8, 'no_vtables_declaration'),
        (_index(idb={}), 'AStarPathFinder', 8, 'no_idb_vtbl_struct'),
        (_index(), 'AStarPathFinder', 40, 'slot_out_of_range'),
        (_index(by_addr={VTBL_ADDR: {}},
                idb={VTBL_ADDR: {0: 'Destroy', 1: 'IsInBounds', 2: ''}}),
         'AStarPathFinder', 8, 'no_method_name'),
    ]
    with tempfile.TemporaryDirectory() as td:
        for idx, cls, off, want in cases:
            with _Harness(idx, td):
                name, reason = s3._resolve_vtbl_name_chain(cls, off)
            assert name is None and reason == want, (cls, off, name, reason)


def test_qualified_method_name_is_never_emitted():
    """禁止 `obj->Base::Method()`（限定调用抑制虚派发 ⇒ 字节必不匹配）。"""
    idx = _index(by_addr={VTBL_ADDR: {1: 'UIWnd::IsInBounds'}})
    body = ("  (*(int (__thiscall **)(AStarPathFinder *, int, int))"
            "(*(_DWORD *)this + 4))(this, nTileX, nTileY);")
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td) as h:
        out = stage3_run(_wrap(body), h.ctx())
    assert 'this->IsInBounds(nTileX, nTileY);' in out, out
    assert not re.search(r'->\s*\w+\s*::\s*\w+\s*\(', out), out
    assert '::IsInBounds(' not in out, out


# ============================================================
# 失败输出契约
# ============================================================

def test_failure_keeps_text_and_records_ledger():
    """识别为虚调用但无法解析 ⇒ 原文逐字保留 + 记账（不降级为裸偏移）。"""
    idx = _index(class_addr={})                     # 未声明 vtables[]
    call = ("  (*(int (__thiscall **)(UnknownCls *, int, int))"
            "(*(_DWORD *)this + 4))(this, nTileX, nTileY);")
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td) as h:
        ctx = h.ctx()
        out = stage3_run(_wrap(call), ctx)
        log = _ledger(ctx)
    # ① 原文本逐字保留（只少了 run() 开头统一剔除的 `__thiscall `）
    assert _strip_cc(call).strip() in out, out
    assert '_tail_' not in out, out
    # ② 记账：原因 + 位置 + 槽位
    assert 'no_vtables_declaration' in log, log
    assert 'UnknownCls' in log, log
    assert ' 4 ' in log or '`4`' in log or '| 4 |' in log, log
    # ③ 不发射任何限定调用
    assert not re.search(r'->\s*\w+\s*::\s*\w+\s*\(', out), out


def test_failure_ledger_is_idempotent_and_deduped():
    """同一站点重复记账只写一行（幂等）——台账是状态文件，不能被每次运行撑爆。"""
    idx = _index(class_addr={})
    body = ("  (*(int (__thiscall **)(UnknownCls *, int))"
            "(*(_DWORD *)this + 4))(this, 1);")
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td) as h:
        ctx = h.ctx()
        stage3_run(_wrap(body), ctx)
        first = _ledger(ctx)
        stage3_run(_wrap(body), ctx)
        second = _ledger(ctx)
    assert first.count('no_vtables_declaration') == 1, first
    assert second.count('no_vtables_declaration') == 1, second


def test_failure_not_recorded_for_non_dispatch_calls():
    """未识别为虚调用的间接调用**不得**污染台账（避免把 COM/函数指针成员当虚调用）。"""
    body = ("  (*(void (__stdcall **)(_DWORD))m_pData)(0, v29);\n"
            "  (*(void (__thiscall **)(int *, _DWORD))this->m_NewItem[7].fnHP)"
            "(&this->m_NewItem[7], 0);")
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        ctx = h.ctx()
        out = stage3_run(_wrap(body), ctx)
        log = _ledger(ctx)
    assert '(*(void (__stdcall **)(_DWORD))m_pData)(0, v29);' in out, out
    assert 'fnHP)(&this->m_NewItem[7], 0);' in out, out
    assert log == '', log


def test_failure_records_self_arg_mismatch():
    """vptr 读的持有者与自身实参不是同一表达式 ⇒ 不敢判定 this ⇒ 记账 + 不改写。"""
    body = ("  (*(void (__thiscall **)(AStarPathFinder *, int))"
            "(*(_DWORD *)v8 + 4))(v8 + 1024, 1);")
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        ctx = h.ctx()
        out = stage3_run(_wrap(body), ctx)
        log = _ledger(ctx)
    assert '(*(_DWORD *)v8 + 4))(v8 + 1024, 1);' in out, out
    assert 'self_arg_mismatch' in log, log


def test_existing_vftable_stub_semantics_preserved():
    """既有 `__vftable` 未解析路径必须**逐字不变**地继续产出合成 stub。"""
    body = ("  (*(int (__thiscall **)(UIStatic *, int))v3->__vftable)(v3, 1);")
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        out = stage3_run(_wrap(body, cls='CCBUI'), h.ctx(cls='CCBUI'))
    assert 'pal3_vtbl_unk_' in out, out
    assert '[VFTABLE-STUB]' in out, out


def test_failure_does_not_downgrade_to_bare_offset_form():
    """失败时不得引入 `_tail_00N` / 伪造成员访问之类的裸偏移形态。"""
    idx = _index(class_addr={})
    body = ("  (*(void (__thiscall **)(UnknownCls *, int))"
            "(*(_DWORD *)this + 4))(this, 1);")
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td) as h:
        out = stage3_run(_wrap(body), h.ctx())
    assert '_tail_' not in out, out
    assert not re.search(r'->\s*field_\w+', out), out
    assert '*(_DWORD *)this + 4' in out, out


def test_name_chain_rejects_placeholder_names():
    """`_tail_000` / `sub_XXXX` / `unknown*` 是 IDB 占位名，不是方法名 ⇒ 不得发射成调用。"""
    idx = _index(by_addr={VTBL_ADDR: {}},
                 idb={VTBL_ADDR: {0: 'Destroy', 1: 'IsInBounds', 2: '_tail_000'}})
    with tempfile.TemporaryDirectory() as td, _Harness(idx, td):
        name, reason = s3._resolve_vtbl_name_chain('AStarPathFinder', 8)
    assert name is None and reason == 'no_method_name', (name, reason)


def test_default_ledger_path_is_the_documented_one():
    """默认台账路径 = 规格指定的 `data/status/vtable_transform_failures.md`（注入可覆盖）。"""
    path = s3._vtable_failure_log_path(_Ctx(log=None))
    assert path.replace('\\', '/').endswith('data/status/vtable_transform_failures.md'), path


def test_double_deref_function_pointer_member_is_left_alone():
    """`(**fn***)MEMBER` 形态**不在三形态范围内**（cast 首参通常不是类）⇒ 原样保留。

    这是刻意划定的边界（保守优先）：语料里该形态多为函数指针数组/成员，
    误判成虚调用会改坏语义 ⇒ 只处理有**显式 vptr 读**的形态。
    """
    body = ("  (**(void (__thiscall ***)(char *, _DWORD))this->m_Slots[17].m_Widget)"
            "(this->m_Slots[17].m_Widget, 0);")
    with tempfile.TemporaryDirectory() as td, _Harness(_index(), td) as h:
        ctx = h.ctx()
        out = stage3_run(_wrap(body), ctx)
        log = _ledger(ctx)
    assert 'm_Slots[17].m_Widget)(this->m_Slots[17].m_Widget, 0);' in out, out
    assert 'm_Slots[17].m_Widget->' not in out, out
    assert log == '', log


# ===== 自带 runner（见模块 docstring） =====
if __name__ == '__main__':
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:                  # 契约被破坏常表现为非 AssertionError
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)