"""寄存器级 provenance 扫描器 —— 基对象归属的确定性工具（TDD）。

解决的两条线（r24）：
① CScreenMode::InitEquipScreen 的 m_id 偏移裁定
② SceneObj/CCBRoleState 复用槽批的 ReleaseObject 矛盾裁定

模型（MSVC6 x86 __thiscall）：
- 入口 %ecx = this
- 调用方保存寄存器：%eax/%ecx/%edx 在 call 后失效 ✗
- 被调用方保存：%ebx/%esi/%edi/%ebp 跨 call 保持 ✓
- 栈参：mov 0xNN(%esp),%reg ⇒ ('arg', k)

运行：`python3 tests/test_provenance.py`
"""
import sys
from pathlib import Path
PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))

from provenance import scan  # noqa: E402

def insns(*pairs):
    return [(va, text) for va, (text,) in zip(range(0x1000, 0x1000 + 4 * len(pairs), 4), pairs)]

def test_thiscall_ecx_is_this():
    """入口 ecx=this；mov ecx,esi ⇒ esi 携带 this ✓"""
    code = insns(
        ('mov    %ecx,%esi',),
        ('mov    %eax,0x44(%esi)',),
    )
    r = scan(code, this_reg='%ecx')
    assert ('this', 0x44, 'w') in r['accesses'], r['accesses']

def test_lea_propagates_this_plus_disp():
    """lea 0x70(%esi),%ecx ⇒ ecx = this+0x70；随后 [ecx+4] ⇒ this+0x74 ✓"""
    code = insns(
        ('lea    0x70(%esi),%ecx',),
        ('mov    %eax,0x4(%ecx)',),
    )
    r = scan(code, this_reg='%esi')
    assert ('this', 0x74, 'w') in r['accesses']

def test_call_clobbers_caller_saved():
    """call 后 eax/ecx/edx 失效 ✗；ebx/esi 保持 ✓"""
    code = insns(
        ('call   0x12345',),        # eax/ecx/edx 失效；ebx（=this，被调用方保存）保持 ✓
        ('mov    %eax,0x44(%ebx)',),# 目的偏移恒可归属 ✓
    )
    r = scan(code, this_reg='%ebx')
    assert ('this', 0x44, 'w') in r['accesses'], r['accesses']

def test_stack_args():
    """mov 0x310(%esp),%ebx ⇒ ('arg', 1) ✓（sub 0x308 后首参）"""
    code = insns(
        ('sub    $0x308,%esp',),
        ('mov    0x310(%esp),%ebx',),
        ('mov    %ebx,0x4c(%esi)',),
    )
    r = scan(code, this_reg='%esi')
    # 写经由 this 基 ⇒ 归属 this；值来自 arg 寄存器（可从 regs 末态核实）
    assert ('this', 0x4c, 'w') in r['accesses']
    assert r['regs']['%ebx'] == ('arg', 0x310)

def test_xor_reg_reg_zeroes():
    """xor eax,eax ⇒ eax=常量 0（非 this）✓"""
    code = insns(
        ('xor    %eax,%eax',),
        ('mov    %eax,0x528(%esi)',),
    )
    r = scan(code, this_reg='%esi')
    assert all(off != 0x528 for _, off, _ in r['accesses'] if _ == 'this')

def test_reads_recorded():
    """读访问也记录（r=读）✓"""
    code = insns(
        ('mov    0x58(%esi),%eax',),
    )
    r = scan(code, this_reg='%esi')
    assert ('this', 0x58, 'r') in r['accesses']

def _run():
    ok = fail = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed' % (ok, fail))
    return fail

if __name__ == '__main__':
    sys.exit(1 if _run() else 0)
