"""vtable 派发改写的**验收测试**（自门控：未开始修 ⇒ SKIP；修了一半 ⇒ FAIL）。

# 缺陷（2026-09-21 定位，双层证据）

## ① 接收者解引用层级被丢掉

`pipeline/gen/stages/stage3_cleanup.py` 的 `run()` 里有一段"去掉冗余自身实参"的替换，
注释自述意图为 `(*ptr)->__vftable->Method(*ptr, extra_args) → ptr->Method(extra_args)`，
repl 是 `\\1->\\2(\\3)` —— **丢掉了 `(*...)` 的解引用**。

定位手段（两层，均不依赖推断）：
* `sys.settrace` 行级追踪 → 变更发生在该 `re.sub` 语句；
* 代理 `stages.stage3_cleanup.re` 记录每次 `sub` 的入参/产出 → 打印出确实生效的 pattern。

`ptr` 在此形态里必然是**多级指针或数组**（否则 Hex-Rays 不会写 `(*ptr)->`）：
`UIStatic **p_m_pBack`（局部，取自 `&this->m_pBack`）、`UIListBox *m_pMagicList[6]`（数组成员）。
丢掉 `*` 后接收者是 `T**`/数组 ⇒ MSVC `C2227`
`left of '->ShowWindow' must point to class/struct/union`。

规模（decomp 语料实测）：**76 站点 / 29 文件** —— `ShowWindow` 53、`Create` 16、`_sdtor_call_dtor` 7。

## ② 仅修 ① 会被门禁拦下（单变量 A/B 实测，2026-09-21）

```
C2227      -41   ✓  意图中的收益
C2039      +22   ✗  Create 16 + _sdtor_call_dtor 7（与 decomp 计数吻合）
S2 ok   75 → 74  ✗  1 个 ok→fail（Combat/CCBProtectWindow.cpp）
L1      35 → 34  ✗  matched 265/319 → 256/309
```

原因：① 只解决**接收者类型**，不解决**方法是否是该类成员**。

* `(*p)->ShowWindow(1)` 可编译 —— `class UIStatic : public UIWnd`，继承到 `virtual int ShowWindow(int)`；
* `(*p)->Create(1)` 仍 `C2039` —— `Create` 未在 UIStatic/UIPushButton/UIListBox/UIScene 中声明。
  ⚠️ UIStatic 的 `methods`/`vtables` 系**上一会话因真实 vtable(0x56B018) 未定而刻意剥离**，
  **不得凭猜测恢复**（CLAUDE.md 禁止猜测性修改）；
* `(*p)->_sdtor_call_dtor(1)` 仍 `C2039` —— 它依赖 `stage5_fixup.py:892-898` 的 `delete \\1` 规则，
  而该规则只接受**裸标识符**接收者 ⇒ `(*ptr)->_sdtor_call_dtor(1)` 不再被转成 `delete`。
  **这正是那个 ok→fail 单元**（基线该行是 `delete p_m_pWHFace;`）。

⇒ 本缺陷的完整批次 = ① 保留解引用 **+** ② `stage5_fixup` 接受 `(*ident)` 形态
  **+** ③ 目标类对槽位方法名的声明，或"目标类没有该方法时回退到既有 stub 路径"
  （后者即 `docs/specs/2026-09-21-vtable-resolver-refactor-design.md` 的 S2/S3 内容）。

# 自门控

`_BATCH_LANDED` 以**源码标记**判定（不是行为判定 —— 避免"改坏了就静默跳过"）：
`stage3_cleanup.py` 里出现 `(*\\1)->` 与 `stage5_fixup.py` 里出现 `(*` 接收者形态，
才视为批次已落地，Behaviour 断言才生效；否则 SKIP 并给出上述实测代价。
"""
import re
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

from stages.stage3_cleanup import run as stage3_run  # noqa: E402

_STAGE3 = PROJECT_ROOT / 'pipeline' / 'gen' / 'stages' / 'stage3_cleanup.py'
_STAGE5 = PROJECT_ROOT / 'pipeline' / 'gen' / 'stages' / 'stage5_fixup.py'


def _batch_landed():
    """批次是否已落地（源码标记判定，见模块 docstring）。"""
    try:
        s3 = _STAGE3.read_text(encoding='utf-8')
        s5 = _STAGE5.read_text(encoding='utf-8')
    except OSError:
        return False
    # ① 保留解引用：repl 里出现 `(*\1)`
    if r'(*\1)->\2(\3);' not in s3:
        return False
    # ② stage5 的 dtor 规则必须能匹配 `(*ident)` 接收者
    if not re.search(r"\(\s*\\\*\s*\(\\w\+\)\s*\\\)\s*\)\s*\\s\*->", s5):
        return False
    return True


_BATCH_LANDED = _batch_landed()
_SKIP = unittest.SkipTest(
    '缺陷批次未落地（stage3 仍丢解引用 / stage5 的 dtor 规则仍只认裸标识符）。'
    '单修 ① 的实测代价：C2227 -41 但 C2039 +22、S2 ok 75→74、L1 35→34 ⇒ 门禁拦下。')


class _Ctx:
    """最小 ctx（同 tests/test_vtbl_stub_dedup.py 的约定）。"""

    def __init__(self, cls_name='CCBSkillWindow'):
        self.cls_name = cls_name
        self.is_free_function = False
        self.sig = ''
        self.stub_registry = set()


def _line_with(out, needle):
    for line in out.split('\n'):
        if needle in line:
            return line.strip()
    return ''


def _wrap(body, cls='CCBSkillWindow', method='Create'):
    return ("int %s::%s(int rc, int nVal)\n{\n%s\n  return 0;\n}\n"
            % (cls, method, body))


def _require_batch():
    if not _BATCH_LANDED:
        raise _SKIP


def test_deref_preserved_for_double_pointer_local():
    """真实样本：`UIStatic **p_m_pBack`（from CCBSkillWindow_Create 的 decomp）。"""
    _require_batch()
    code = _wrap("  UIStatic **p_m_pBack; // ebx\n"
                 "  p_m_pBack = &this->m_pBack;\n"
                 "  ((void (__thiscall *)(UIStatic *, int))"
                 "(*p_m_pBack)->__vftable->ShowWindow)(*p_m_pBack, 1);")
    out = stage3_run(code, _Ctx())
    line = _line_with(out, 'ShowWindow')
    assert line, out
    # 精确断言：保留解引用层级 + 冗余自身实参已去掉
    assert line == '(*p_m_pBack)->ShowWindow(1);', line


def test_deref_preserved_for_array_member_receiver():
    """`UIListBox *m_pMagicList[6]` —— 数组成员，`*arr` 才是 `UIListBox *`。"""
    _require_batch()
    code = _wrap("  ((void (__thiscall *)(UIListBox *, int))"
                 "(*m_pMagicList)->__vftable->ShowWindow)(*m_pMagicList, 1);",
                 cls='CCBMagicWindow', method='Reset')
    out = stage3_run(code, _Ctx('CCBMagicWindow'))
    line = _line_with(out, 'ShowWindow')
    assert line.startswith('(*m_pMagicList)->ShowWindow(1'), line


def test_extra_args_are_kept():
    """去掉的只能是**自身实参**，其余实参必须原样保留。"""
    _require_batch()
    code = _wrap("  ((void (__thiscall *)(UIStatic *, int, int *, CCBSkillWindow *))"
                 "(*p_m_pBack)->__vftable->Create)(*p_m_pBack, 513, &v8, this);")
    out = stage3_run(code, _Ctx())
    line = _line_with(out, '->Create(')      # 不能匹配函数签名行 `...::Create(int rc, ...)`
    assert '(*p_m_pBack)->Create(513, &v8, this)' in line, line


def test_dtor_of_deref_receiver_becomes_delete():
    """批次 ②：`(*ptr)->_sdtor_call_dtor(1)` 必须转成 `delete *ptr;`。

    ⚠️ 若只落地 ① 而未落地 ②，这里会 FAIL —— 这正是基线里那个 ok→fail 单元的成因。
    """
    _require_batch()
    code = _wrap("  UIStatic **p_m_pWHFace;\n"
                 "  if ( *p_m_pWHFace )\n  {\n"
                 "    ((void (__thiscall *)(UIStatic *, int))"
                 "(*p_m_pWHFace)->__vftable->_sdtor_call_dtor)(*p_m_pWHFace, 1);\n"
                 "    *p_m_pWHFace = 0;\n  }")
    out = stage3_run(code, _Ctx('CCBProtectWindow'))
    assert 'delete *p_m_pWHFace' in out, out


def test_positive_control_self_arg_still_dropped():
    """阳性对照：同族"去冗余自身实参"规则对**已转换**的普通链始终必须生效。

    （不门控 —— 这条与缺陷无关，任何时候都必须通过，防止"修好一类、弄坏另一类"。）
    """
    code = _wrap("  this->m_pBack->ShowWindow(this->m_pBack, 1);")
    out = stage3_run(code, _Ctx())
    line = _line_with(out, 'ShowWindow')
    assert line.startswith('this->m_pBack->ShowWindow(1'), line


# ===== 自带 runner（本机 pytest 在 collect 阶段即崩，见
#   docs/knowledge/gotcha_local_pytest_collect_crashes_use_self_runner.md）
# 运行方式: python3 tests/test_vftable_deref_preserved.py
if __name__ == '__main__':
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:                      # 契约被破坏常表现为非 AssertionError
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)