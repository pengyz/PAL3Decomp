"""基类子对象投影回归测试（#8 2026-11-26）。

病灶（有实测证据，勿改写）：`data/annotations/structs/RoleStatePanel.json` /
`UIFrameContainer.json` 声明了 `bases` 但缺 `base_size`，而
`pipeline/ida/apply_annotations.py:1047` 只在 `base_size > 0` 时把基类子对象 push 进 IDB
⇒ `asm/pal3/ida_structs.json` 的 `bases=[]` ⇒ `pipeline/gen/stages/emit_headers.py:2747-2768`
推出 `base_size=0`，成员从 +4 起排 ⇒ 全类偏移 +0x2A8（另 UIFrameContainer 自身 +0x44）。

数值全部来自原始二进制/编译器实测：
* 原始 0x4A618D/0x4A618F `mov [esi],eax; mov [esi+4],eax` 的基址 0x25B78 = `m_bRtVisible`
* `m_unk_0x174` 在 InitUI/OnMessage 都被写 +0x174
* `m_nRtIndex` = 0x25B80（vtable 槽 0x4A6120 的计数读点）
* `UIFrameContainer` 152B（EquipUI `??_L` 元素 stride 0x98 实证）
* `RoleStatePanel` 176256B（ctor `operator new(0x2B080)`）

两层：
* A. 注解层（秒级，无需编译器）：两个类必须有 bases + base_size=72。
* B. 编译器裁判（需 MSVC6/wine）：真实生成头上 `offsetof`/`sizeof` 静态断言编译通过。
  修复前这些断言必然报 C2057/C2118 类错误（实测 m_bRtVisible 落 +0x25E20、sizeof 220）。

运行：``python3 tests/test_base_size_projection.py``（pytest 在 collect 阶段崩，见仓内约定）
"""
import json
import os
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))

CL = PROJECT_ROOT / 'tools' / 'compilers' / 'msvc6.0' / 'Bin' / 'CL.EXE'
HAVE_CL = os.path.exists(str(CL))


def _ann(cls):
    return json.loads((PROJECT_ROOT / 'data' / 'annotations' / 'structs' / ('%s.json' % cls))
                      .read_text(encoding='utf-8'))


# ===================== A. 注解层 =====================

def test_annotations_declare_base_size():
    """两个类必须显式声明 base_size=72（= UIListBox/UIFrameWnd 完整尺寸含 vptr）。"""
    for cls, base in (('RoleStatePanel', 'UIListBox'), ('UIFrameContainer', 'UIFrameWnd')):
        d = _ann(cls)
        assert d.get('base_size') == 72, (cls, d.get('base_size'))
        assert [b['name'] for b in d.get('bases') or []] == [base], (cls, d.get('bases'))


def test_base_size_equals_base_class_size():
    """base_size 必须等于基类自身的 binary_size（防手滑写成 UIWnd 的 68）。"""
    for cls in ('RoleStatePanel', 'UIFrameContainer'):
        d = _ann(cls)
        base = d['bases'][0]['name']
        assert d['base_size'] == _ann(base)['binary_size'], (cls, base)


# ===================== B. 编译器裁判 =====================

_PROBE = r'''
#include <stddef.h>
#include "Misc/RoleStatePanel.h"
#include "Misc/UIFrameContainer.h"

typedef char chk_rt_visible[(offsetof(RoleStatePanel, m_bRtVisible) == 0x25B78) ? 1 : -1];
typedef char chk_unk_174[(offsetof(RoleStatePanel, m_unk_0x174) == 0x174) ? 1 : -1];
typedef char chk_rt_index[(offsetof(RoleStatePanel, m_nRtIndex) == 0x25B80) ? 1 : -1];
typedef char chk_frame_flag[(offsetof(UIFrameContainer, m_bFlag96) == 0x60) ? 1 : -1];
typedef char chk_sizeof_frame[(sizeof(UIFrameContainer) == 152) ? 1 : -1];
typedef char chk_sizeof_panel[(sizeof(RoleStatePanel) == 176256) ? 1 : -1];
'''


def _compile_probe(src):
    d = tempfile.mkdtemp(prefix='basefix_')
    cpp = os.path.join(d, 'probe.cpp')
    Path(cpp).write_text(src, encoding='utf-8')
    includes = ['/I' + str(PROJECT_ROOT / 'include'),
                '/I' + str(PROJECT_ROOT / 'pal3' / 'src'),
                '/I' + str(PROJECT_ROOT / 'tools' / 'compilers' / 'msvc6.0' / 'Include'),
                '/I' + str(PROJECT_ROOT / 'tools' / 'vc6' / 'Include')]
    cmd = ['wine', 'Z:' + str(CL).replace('/', '\\'), '/nologo', '/TP', '/c',
           '/W3', '/O2', '/MT'] + includes + \
          ['/Fo' + 'Z:' + os.path.join(d, 'probe.obj').replace('/', '\\'),
           'Z:' + cpp.replace('/', '\\')]
    r = subprocess.run(cmd, capture_output=True, text=True, errors='replace',
                       timeout=300, cwd=str(PROJECT_ROOT))
    return r.returncode, (r.stdout + r.stderr)


def test_generated_header_offsets_match_binary():
    """生成头的 offsetof/sizeof 必须回到原始二进制值（编译器静态断言）。"""
    if not HAVE_CL:
        raise unittest.SkipTest('本机无 MSVC6/wine，跳过编译器测试')
    rc, out = _compile_probe(_PROBE)
    assert rc == 0, '编译失败（布局仍漂移）:\n' + out[-2000:]


if __name__ == '__main__':
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)
