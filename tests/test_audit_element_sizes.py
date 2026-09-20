# tests/test_audit_element_sizes.py
"""任务2 测试：只读 ??_L/??_M 站点抽取器。

用例集（A–G 为评审补充的代表性用例，全部用**真实 asm 行**或贴近真实形态的 fixture）：
- A 真实尾注 `; comment` 剥离（本仓 16601 行 push 带尾注 —— 计划原正则的致命盲点）；
- B 名字改编符号（`??1stdiobuf@@UAE@XZ_2`）作 dtor 必须保留、不得静默丢弃；
- C `??_M` 四元组：**无 ctor**（`ctor is None`），窗口比 `??_L` 短一位；
- D 寄存器/内存操作数（`push ecx`）与 `lea` 交错：原样保留且不污染 size/count；
- E 抽取不全 ⇒ `incomplete` 条目且**不带**实参键（下游 `.get` 安全）；
- F `count` 契约 `int|None`（修复前 `push ecx` 会让 count 漏出 str，实测 2/466）；
- G SEH unwind funclet（`; START OF FUNCTION CHUNK FOR sub_XXXX`）里的站点必须挂到
  **chunk owner**，不得挂到文件中最后一个 proc（修复前实测 213/466 全错挂 sub_55D67E）。
- H/I 契约回归断言：`size` 恒为 `int|None`；`count:int|None`、`ptr/ctor/dtor:str|None`。
- J 真实 asm 端到端归属回归（asm 缺失则 SKIP）：`sub_55D67E` 站点必须为 0。

fixture 说明：A/C/D/J 用的 asm 片段是从 `original/PAL3.exe.asm` **逐字拷出**的真实行
（11956-11962 / 47085-47092 / 514945-514955），内联为字符串 ⇒ 测试不依赖 gitignored 的 asm 文件。

本机 pytest 在 collect 阶段即崩（未安装/不可用）⇒ 本文件自带 `__main__` runner（仓内既有约定）。
"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'tools'))
import audit_element_sizes as a

ASM = """
sub_408740      proc near
                push    offset sub_411CA0
                push    offset sub_411900
                push    5
                push    2200h
                push    offset unk_C05F60
                call    ??_L@YGXPAXIHP6EX0@Z1@Z
sub_408740      endp
"""

# A/J：真实行 11956-11962（尾注 `; comment` + `↑p` 箭头字符）
ASM_REAL_L = """sub_408740      proc near               ; CODE XREF: sub_408730\u2191p
                push    offset sub_411CA0 ; void (__thiscall *)(void *)
                push    offset sub_411900 ; void (__thiscall *)(void *)
                push    5               ; int
                push    2200h           ; unsigned int
                push    offset dword_C05F60 ; void *
                call    ??_L@YGXPAXIHP6EX0@Z1@Z ; `eh vector constructor iterator'(void *,uint,int,void (*)(void *),void (*)(void *))
"""

# C：真实行 514945-514955 —— SEH unwind funclet（chunk for sub_403370）里的 ??_M 站点
ASM_CHUNK_REAL = """; START OF FUNCTION CHUNK FOR sub_403370

loc_55F050:                             ; DATA XREF: .rdata:stru_573ED8\u2193o
; __unwind { // SEH_403370              ; void (__thiscall *)(void *)
                push    offset sub_4034B0
                push    2               ; int
                push    0A4h            ; unsigned int
                mov     eax, [ebp-10h]
                add     eax, 4
                push    eax             ; void *
                call    ??_M@YGXPAXIHP6EX0@Z@Z ; `eh vector destructor iterator'(void *,uint,int,void (*)(void *))
"""

# D：真实行 47085-47092 —— `lea`/`mov` 与 push 交错，ptr 是寄存器 ecx
ASM_REAL_MEM = """                push    offset sub_423880 ; void (__thiscall *)(void *)
                push    offset sub_4236D0 ; void (__thiscall *)(void *)
                push    40h ; '@'       ; int
                lea     ecx, [esi+0E0h]
                push    380h            ; unsigned int
                push    ecx             ; void *
                mov     byte ptr [esp+2Ch+var_4], 1
                call    ??_L@YGXPAXIHP6EX0@Z1@Z ; `eh vector constructor iterator'(void *,uint,int,void (*)(void *),void (*)(void *))
"""

# B：名字改编符号作 dtor（真实 asm 有 11(ehl)+22(ehm) 条）
ASM_MANGLED = """
sub_498820      proc near
                push    offset ??1stdiobuf@@UAE@XZ_2 ; void (__thiscall *)(void *)
                push    offset sub_440740 ; void (__thiscall *)(void *)
                push    6               ; int
                push    0F8h            ; unsigned int
                push    esi             ; void *
                call    ??_L@YGXPAXIHP6EX0@Z1@Z
sub_498820      endp
"""

# E：抽取不全（只有 2 个 push，`??_L` 需 5 个）
ASM_SHORT = """
sub_Y            proc near
                push    10h
                push    eax
                call    ??_L@YGXPAXIHP6EX0@Z1@Z
sub_Y            endp
"""

# F：count 位置是寄存器操作数 ⇒ 修复前漏出 str 'ecx'
ASM_COUNT_REG = """
sub_Z            proc near
                push    offset sub_4CD0A0
                push    ecx             ; int
                push    38h ; '8'       ; unsigned int
                push    eax             ; void *
                call    ??_M@YGXPAXIHP6EX0@Z@Z
sub_Z            endp
"""

# G：funclet chunk 出现在一个**无关 proc 之后** ⇒ 修复前被错挂到 sub_AAA
ASM_CHUNK = """
sub_AAA          proc near
                push    offset sub_411CA0
                push    offset sub_411900
                push    5
                push    2200h
                push    eax
                call    ??_L@YGXPAXIHP6EX0@Z1@Z
sub_AAA          endp
; START OF FUNCTION CHUNK FOR sub_BBB
loc_55F000:
                push    offset sub_4034B0
                push    2
                push    0A4h
                push    eax
                call    ??_M@YGXPAXIHP6EX0@Z@Z
"""

_SKIP = object()          # runner 用：测试返回值为此 ⇒ 记为 SKIP
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM_FILE = os.path.join(ROOT, 'original', 'PAL3.exe.asm')


def _real_sites():
    """非 gitignored asm 存在时返回全量站点，否则 None（调用方 SKIP）。"""
    if not os.path.exists(ASM_FILE):
        return None
    with open(ASM_FILE, encoding='utf-8', errors='replace') as fh:
        return a.parse_sites(fh.read())


def test_parse_l_pushes_tuple():
    sites = a.parse_sites(ASM)
    assert len(sites) == 1
    s = sites[0]
    assert s['kind'] == 'ehl'
    assert s['size'] == 0x2200          # 来自 push 2200h 字面量
    assert s['count'] == 5
    assert s['ctor'] == '0x411900'
    assert s['dtor'] == '0x411CA0'


# ---------------------------------------------------------------- A
def test_A_real_lines_with_trailing_comments_are_stripped():
    ss = a.parse_sites(ASM_REAL_L)
    assert len(ss) == 1, ss
    s = ss[0]
    assert s['site'] == 'sub_408740', s
    assert s['kind'] == 'ehl', s
    assert (s['size'], s['count']) == (0x2200, 5), s          # size=8704 fixture
    assert (s['ctor'], s['dtor']) == ('0x411900', '0x411CA0'), s
    assert s['ptr'] == '0xC05F60', s
    assert not s.get('incomplete'), s                          # 尾注不得导致假 incomplete


# ---------------------------------------------------------------- B
def test_B_mangled_symbol_dtor_is_preserved_not_dropped():
    s = a.parse_sites(ASM_MANGLED)[0]
    assert s['dtor'] == '??1stdiobuf@@UAE@XZ_2', s
    assert (s['size'], s['count'], s['ctor']) == (0xF8, 6, '0x440740'), s
    assert s['ptr'] == 'esi', s


# ---------------------------------------------------------------- C
def test_C_ehm_funclet_is_four_tuple_without_ctor():
    s = a.parse_sites(ASM_CHUNK_REAL)[0]
    assert s['kind'] == 'ehm', s
    assert s['ctor'] is None, s                                # ??_M 无 ctor
    assert (s['size'], s['count'], s['dtor']) == (0xA4, 2, '0x4034B0'), s
    assert s['ptr'] == 'eax', s
    assert s['site'] == 'sub_403370', s                        # 真实 funclet 归属


# ---------------------------------------------------------------- D
def test_D_register_operand_and_lea_interleave():
    s = a.parse_sites(ASM_REAL_MEM)[0]
    assert s['ptr'] == 'ecx', s                                # 寄存器操作数原样保留
    assert (s['size'], s['count']) == (0x380, 0x40), s         # size=896 fixture
    assert (s['ctor'], s['dtor']) == ('0x4236D0', '0x423880'), s
    assert s['kind'] == 'ehl', s


# ---------------------------------------------------------------- E
def test_E_incomplete_row_has_no_arg_keys():
    ss = a.parse_sites(ASM_SHORT)
    assert len(ss) == 1, ss
    s = ss[0]
    assert s['incomplete'] is True and s['kind'] == 'ehl', s
    assert s['site'] == 'sub_Y', s
    for k in ('size', 'count', 'ptr', 'ctor', 'dtor'):
        assert k not in s, '不完整条目不得带 %s 键: %r' % (k, s)
    assert s.get('size', 'DEFAULT') == 'DEFAULT'                # 下游 .get 安全


# ---------------------------------------------------------------- F
def test_F_count_contract_is_int_or_none():
    s = a.parse_sites(ASM_COUNT_REG)[0]
    assert s['count'] is None or isinstance(s['count'], int), \
        'count 违反 int|None 契约: %r (%s)' % (s['count'], type(s['count']).__name__)
    assert s['count'] is None, s          # count 位是 push ecx ⇒ 必须是 None 而非 'ecx'
    assert s['size'] == 0x38, s           # size 仍是字面量 int，不受影响


# ---------------------------------------------------------------- G
def test_G_site_in_funclet_chunk_uses_chunk_owner():
    ss = a.parse_sites(ASM_CHUNK)
    assert len(ss) == 2, ss
    assert ss[0]['site'] == 'sub_AAA', 'proc 内站点归属被破坏: %r' % (ss[0]['site'],)
    assert ss[1]['kind'] == 'ehm', ss[1]
    assert ss[1]['site'] == 'sub_BBB', 'funclet 站点被误挂到 %r' % (ss[1]['site'],)


# ---------------------------------------------------------------- H/I 契约回归
def test_H_size_is_always_int_or_none():
    for name, fx in (('ASM', ASM), ('REAL_L', ASM_REAL_L), ('CHUNK_REAL', ASM_CHUNK_REAL),
                     ('REAL_MEM', ASM_REAL_MEM), ('MANGLED', ASM_MANGLED),
                     ('COUNT_REG', ASM_COUNT_REG), ('CHUNK', ASM_CHUNK)):
        for s in a.parse_sites(fx):
            if 'size' in s:
                assert s['size'] is None or isinstance(s['size'], int), \
                    '%s: size 违反 int|None 契约: %r' % (name, s['size'])
    sites = _real_sites()
    if sites is None:
        return _SKIP
    for s in sites:
        assert 'size' not in s or s['size'] is None or isinstance(s['size'], int), \
            'line %s: size 违反 int|None 契约: %r' % (s['line'], s.get('size'))


def test_I_count_and_addr_contracts():
    sites = _real_sites()
    if sites is None:
        return _SKIP
    for s in sites:
        assert 'count' not in s or s['count'] is None or isinstance(s['count'], int), \
            'line %s: count 违反契约: %r' % (s['line'], s.get('count'))
        for k in ('ptr', 'ctor', 'dtor'):
            v = s.get(k, None)
            assert v is None or isinstance(v, str), \
                'line %s: %s 违反 str|None 契约: %r' % (s['line'], k, v)
    # 字面量地址（`push 411900h`）必须归一化为 str，否则下游 a0.lower() 会 AttributeError
    gun = a.parse_sites("""
sub_GUN          proc near
                push    411900h
                push    5
                push    2200h
                push    offset unk_C05F60
                call    ??_M@YGXPAXIHP6EX0@Z@Z
sub_GUN          endp
""")[0]
    assert gun['dtor'] == '0x411900' and isinstance(gun['dtor'], str), gun
    assert gun['dtor'].lower() == '0x411900'            # T4 的实际用法，不得崩


# ---------------------------------------------------------------- J 真实 asm 端到端
def test_J_real_asm_ownership_and_census():
    sites = _real_sites()
    if sites is None:
        return _SKIP
    inc = [s for s in sites if s.get('incomplete')]
    kinds = {}
    for s in sites:
        kinds[s['kind']] = kinds.get(s['kind'], 0) + 1
    assert (len(sites), kinds.get('ehl'), kinds.get('ehm'), len(inc)) == (466, 133, 333, 0), \
        (len(sites), kinds, len(inc))
    assert sum(1 for s in sites if s.get('site') == 'sub_55D67E') == 0, \
        'SEH funclet 站点仍被错挂到 sub_55D67E'
    assert not any(s.get('site') is None for s in sites), '仍有站点无宿主'
    by_line = {s['line']: s['site'] for s in sites}
    assert by_line.get(514955) == 'sub_403370', by_line.get(514955)
    assert by_line.get(515537) == 'sub_41F6F0', by_line.get(515537)


def test_missing_asm_returns_2(tmp_path, monkeypatch):
    monkeypatch.setattr(a, 'ASM_PATH', str(tmp_path / 'nope.asm'))
    assert a.main([]) == 2


def test_unknown_flag_is_rejected(monkeypatch):
    monkeypatch.setattr(sys, 'argv', ['audit_element_sizes.py', '--help'])
    assert a.main(['--help']) == 0   # 护栏：拒绝执行而非跑全流程


if __name__ == '__main__':
    import inspect, shutil, tempfile, pathlib

    class _MonkeyPatch:
        """够用的 monkeypatch 替身（pytest 未安装时直接跑本文件的兜底）。"""
        def __init__(self):
            self._undo = []

        def setattr(self, obj, name, value):
            self._undo.append((obj, name, getattr(obj, name)))
            setattr(obj, name, value)

        def undo(self):
            for obj, name, old in reversed(self._undo):
                setattr(obj, name, old)
            self._undo = []

    ok = fail = skip = 0
    for name, fn in sorted(globals().items()):
        if name.startswith('test_') and callable(fn):
            params = inspect.signature(fn).parameters
            kwargs, tmpdir, mp = {}, None, _MonkeyPatch()
            if 'tmp_path' in params:
                tmpdir = tempfile.mkdtemp(prefix='aes_test_')
                kwargs['tmp_path'] = pathlib.Path(tmpdir)
            if 'monkeypatch' in params:
                kwargs['monkeypatch'] = mp
            try:
                # 捕获 Exception（不止 AssertionError）：契约被破坏时可能是
                # AttributeError/TypeError，用例崩掉不应连带隐藏后续用例结果。
                res = fn(**kwargs)
                if res is _SKIP:
                    print('  SKIP %s（asm 缺失）' % name)
                    skip += 1
                else:
                    print('  PASS %s' % name)
                    ok += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (name, type(e).__name__, e))
                fail += 1
            finally:
                mp.undo()
                if tmpdir:
                    shutil.rmtree(tmpdir, ignore_errors=True)
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)