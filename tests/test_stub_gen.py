"""stub_gen 纯函数判据（codegen+stub overlay 设计 §3.2）。
fixture 覆盖实测签名形态（2833 锚定函数普查）；R15：改工具必须跑其测试。
运行: python3 tests/test_stub_gen.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from stub_gen import (extract_includes, extract_functions, split_signature,  # noqa: E402
                      stub_body, render_stub, stub_path_for_unit, extract_data_items)

FIXTURE = '''#include "pal3/ida_defs.h"
#include "globals.h"

// Forward declarations for unnamed functions

// 0x004DB5C0
int CCBAttackSequen::ResetTimers()
{
  int v2;
  // inner comment with 0x00DEAD00 not at line start pattern
  return v2;
}

// 0x004DB620
#pragma inline_depth(0)
void __thiscall CCBAttackSequen::Tick(float fVal)
{
}

// 0x004DB700
// attributes: thunk
CCBAttackSequen::~CCBAttackSequen()
{
}

// 0x004DB800
_Texture_uv operator_(_Texture_uv *_this, _Texture_uv *a2)
{
  return *_this;
}

// 0x004DB900
char * CCBAttackSequen::GetName(int idx)
{
  return 0;
}
'''


def test_extract_includes_copies_head_block():
    inc = extract_includes(FIXTURE)
    assert inc.startswith('#include "pal3/ida_defs.h"\n#include "globals.h"'), repr(inc)
    # CCBStage 病灶回归锁（2026-10-31）：#define/#undef 夹序言不得截断
    tricky = ('// [T9] workaround\n#define private public\n#include <string>\n'
              '#undef private\n\n#include "globals.h"\n\nint f()\n{\n}\n')
    inc2 = extract_includes(tricky)
    assert '#define private public' in inc2 and '#undef private' in inc2
    assert '#include "globals.h"' in inc2
    assert 'int f()' not in inc2


def test_extract_functions_anchored_five_forms():
    fs = extract_functions(FIXTURE)
    assert [f['addr'] for f in fs] == ['0x004DB5C0', '0x004DB620', '0x004DB700',
                                      '0x004DB800', '0x004DB900']
    assert fs[0]['ret'] == 'int' and fs[0]['name'] == 'CCBAttackSequen::ResetTimers'
    # #pragma 行被跳过；__stdcall/__thiscall 修饰剥离
    assert fs[1]['ret'] == 'void' and fs[1]['name'] == 'CCBAttackSequen::Tick'
    # 注释行被跳过；无返回型 ctor/dtor
    assert fs[2]['ret'] == '' and fs[2]['name'] == 'CCBAttackSequen::~CCBAttackSequen'
    assert fs[3]['ret'] == '_Texture_uv' and fs[3]['name'] == 'operator_'
    assert fs[4]['ret'] == 'char *' and fs[4]['name'] == 'CCBAttackSequen::GetName'


def test_split_signature_conv_words_stripped():
    ret, name = split_signature('int __stdcall WinProc(HWND hWnd, UINT Msg)')
    assert ret == 'int' and name == 'WinProc'
    ret, name = split_signature('LRESULT __thiscall Foo::Bar(int a)')
    assert ret == 'LRESULT' and name == 'Foo::Bar'


def test_stub_body_three_rules():
    assert stub_body('', 'X::X') == '{ }'                       # ctor/dtor
    assert stub_body('void', 'X::f') == '{ }'                   # void
    assert stub_body('int', 'f') == '{ return 0; }'             # 元语
    assert stub_body('char *', 'f') == '{ return 0; }'          # 指针
    assert stub_body('int __stdcall', 'f') == '{ return 0; }'   # 修饰剥离后元语
    assert stub_body('_Texture_uv', 'operator_') == '{ return *(_Texture_uv *)0; }'  # 类值兜底
    # 回归锁（2026-10-31 C2562 连锁根因）：带调用约定的 void 必须落空体
    assert stub_body('void __cdecl', 'nullsub_17') == '{ }'
    assert stub_body('void __fastcall', 'PushMatrixStacks') == '{ }'


def test_render_stub_deterministic_and_paths():
    fs = extract_functions(FIXTURE)
    a = render_stub('pal3/src/Combat/CCBAttackSequen.cpp', extract_includes(FIXTURE), fs)
    b = render_stub('pal3/src/Combat/CCBAttackSequen.cpp', extract_includes(FIXTURE), fs)
    assert a == b
    assert 'AUTO-GENERATED' in a and a.count('\n') > 20
    p = stub_path_for_unit('pal3/src/Combat/CCBAttackSequen.cpp')
    assert p.name == 'CCBAttackSequen_stub.cpp' and p.parent.name == 'Combat'
    assert stub_path_for_unit('pal3/src/free_functions.cpp').name == 'free_functions_stub.cpp'


def test_extract_data_items_globals_form():
    """globals.cpp 形态（纯数据 3011 行）：';' 顶层数语句逐条收，函数体丢弃。"""
    t = ('#include "globals.h"\n'
         'float g_fScale[8] = {1.0f};\n'
         'unsigned __int8 g_bFlag = {0};\n'
         'int f()\n{\n  return g_bFlag;\n}\n'
         'char *const psz = {0};\n')
    items = extract_data_items(t)
    assert [d['label'] for d in items] == ['float g_fScale[8] = {1.0f};',
                                          'unsigned __int8 g_bFlag = {0};',
                                          'char *const psz = {0};'], items
    # 嵌套初始式不破深度
    t2 = 'int a[2][2] = { {1,2}, {3,4} };\nint b = 1;\n'
    assert len(extract_data_items(t2)) == 2


def test_parse_header_slots_class_context():
    """虚槽批量供给的声明提取：类上下文 + virtual/static 剥离 + 参数保留。"""
    from stub_gen import parse_header_slots
    h = ('class UIFrameWnd : public UIWnd\n'
         '{\n'
         'public:\n'
         '    virtual void slot_0(); // 0x445e70\n'
         '    virtual int slot_5(int a2); // 0x004C9ED0\n'
         '    static int slot_1(); // 0x004C5D80\n'
         '    void normal();\n'
         '};\n'
         'class Other\n{\n    virtual void slot_2();\n};\n')
    items = parse_header_slots(h)
    assert items == [('UIFrameWnd', 'void', 'slot_0', ''),
                     ('UIFrameWnd', 'int', 'slot_5', 'int a2'),
                     ('UIFrameWnd', 'int', 'slot_1', ''),
                     ('Other', 'void', 'slot_2', '')], items


def test_parse_link_display_forms():
    """按需供给解析（v2 D0-2）：显示名三形 + 裸 C 符号 + dllimport 识别。"""
    from stub_gen import parse_link_display
    k, ret, n, p = parse_link_display(
        'public: int __thiscall CCBSystem::F(int (__thiscall CCBSystem::*)(int),int)')
    assert k == 'func' and n == 'CCBSystem::F' and 'CCBSystem::*)(int)' in p
    k, ret, n, p = parse_link_display('char * g_Foo')
    assert k == 'data' and ret == 'char *' and n == 'g_Foo'
    k, ret, n, p = parse_link_display('_NtCurrentTeb')
    assert k == 'cfunc' and n == '_NtCurrentTeb'
    k = parse_link_display('__declspec(dllimport) public: void __thiscall X::f(void)')[0]
    assert k == 'dllimport'


def test_ledger_retired_and_defined_surface_skip():
    """退役复活闸（v2 D0-2.1）：retired 行不入供给；已定义面跳过（防 LNK2005 双定义）。"""
    import tempfile
    from stub_gen import generate_supply_from_log, defined_surface_names, sym_base_forms
    tmp = Path(tempfile.mkdtemp())
    log = tmp / 'demand_ledger.txt'
    log.write_text('active\tint __cdecl live_fn(int)\n'
                   'retired\tint __cdecl dead_fn(int)\n', encoding='utf-8')
    generate_supply_from_log([str(log)], out_root=tmp / 'out')
    body = ''.join(f.read_text(encoding='utf-8') for f in (tmp / 'out').glob('*.cpp'))
    assert 'live_fn' in body and 'dead_fn' not in body
    defined = defined_surface_names()
    assert isinstance(defined, set) and defined          # 名集（含 ArraySort 等）
    assert sym_base_forms('_WinMain@16') & {'_WinMain@16', 'WinMain'}


def test_rewrite_new_expression_ctor_only():
    """v2 审核修正：只匹配 T::T() 构造形，普通方法调用不改写（F2 BLOCKER 教训）。"""
    import re
    RESULT_ASSIGN = r'(?:(?P<result>\w+)\s*=\s*(?:\(\s*\w+\s*\*\s*\)\s*)?)?'
    pat = re.compile(
        r'(?P<indent>^\s+)(?P<ptr>\w+)\s*=\s*\(\s*(?P<cls>\w+)\s*\*\s*\)\s*operator new\s*\([^)]+\);\s*\n'
        r'(?:\s*\w+\s*=\s*-?\d+;\s*\n)?'
        r'\s*if\s*\(\s*(?P=ptr)\s*\)\s*\n'
        r'\s*' + RESULT_ASSIGN +
        r'(?:\(\s*)*(?:\(\s*\w+\s*\*\s*\)\s*)?(?P=ptr)(?:\s*\))*(?:\s*->)'
        r'\s*(?P=cls)::(?P=cls)\s*\((?P<args>[^;]*)\);\s*\n'
        r'\s*else\s*\n'
        r'\s*(?P<fallback>\w+)\s*=\s*0;\s*\n'
        r'(?:\s*\w+\s*=\s*-?\d+;\s*\n)?',
        re.MULTILINE)

    ctor = '  v2 = (CCBUI *)operator new(0x74u);\n  if ( v2 )\n    v2->CCBUI::CCBUI();\n  else\n    v3 = 0;\n'
    assert pat.search(ctor), 'ctor form T::T() should match'

    ctor_args = '  v2 = (gbCamera *)operator new(0x100u);\n  if ( v2 )\n    v2->gbCamera::gbCamera(1, 2);\n  else\n    v3 = 0;\n'
    m = pat.search(ctor_args)
    assert m and '1, 2' in m.group('args'), 'ctor args should be captured'

    method = '  v3 = (GRPinput *)operator new(0x24u);\n  if ( v3 )\n    v4 = v3->GRPinput::SetMousePos();\n  else\n    v4 = 0;\n'
    assert not pat.search(method), 'non-ctor form T::Method() should NOT match'

    m = pat.search(ctor)
    assert m and m.group('result') is None, 'result should be None when absent'


def test_iron_rule_no_stub_in_pal3src():
    """铁律棘轮（设计 §3.1）：stub 永不落 pal3/src（S2 量到 stub=假绿）。
    2026-10-31 实测教训：绝对路径进 stub_path_for_unit 会让 Path 连接失效
    （盘符绝对形替换基）⇒ 89 件误置 pal3/src，已清场+护栏。"""
    from stub_gen import STUB_ROOT
    bad = list((ROOT / 'pal3' / 'src').rglob('*_stub.cpp'))
    assert not bad, bad[:5]
    p = stub_path_for_unit('pal3/src/Combat/X.cpp')
    assert str(p).startswith(str(STUB_ROOT)), p
    if STUB_ROOT.exists():
        assert list(STUB_ROOT.rglob('*_stub.cpp'))   # 生成面在 phase2/stubs
