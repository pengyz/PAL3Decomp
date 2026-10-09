"""`tools/audit_callsite_evidence.py` 的测试 —— 调用点实参取证（只读前置工具）。

覆盖范围 = 任务 0 简报用例 + 控制器补充裁决：

* 简报用例 1：`0x440960` 的调用点 `0x4b0b34` 窗口内同时存在 `imm` 与 `reg` 形态的 push
* 简报用例 2：`0x43d890` 是 virtual ⇒ 无静态调用点，`verdict` 含 virtual，不崩
* 补裁决 ②：**`imm_str` 分支** —— `0x4b0b2f push 0x5d37f8` 落在数据节且内容为可打印 ASCII
  字符串 `UI\\GameMainUI\\System\\Saveon.tga` ⇒ 必须标 `kind='imm_str'` 并附字符串
* 补裁决 ①：**宽度取证**（任务 5 依赖）—— `mov` 4B / `movzx` 1B / `lea` 取址（`addr`）
* 修复轮 1（评审 Important）：**pushes 不携带 width 字段**、CLI push 行不打印 `width=`
  —— 16-bit 前缀下 push 是 2B，硬编码 4 会误导读者；宽度契约只在 `regs`（任务 5）
* 补裁决 ③：**反汇编边界对齐** —— 必须全量反汇编后按 VA 定位（禁止手拼 `--start-address`），
  `0x4b0b2f` 必须恰是 `push 0x5d37f8` 这条真实指令，而不是落在指令中间的错位解码

运行方式（本机 pytest 默认断言重写坏死，见 task-0-report.md「疑虑」；两种方式都可）::

    python -m pytest --assert=plain tests/tools/test_audit_callsite_evidence.py -v
    python3 tests/tools/test_audit_callsite_evidence.py
"""
import os
import subprocess
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PROJECT_ROOT))
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))

from audit_callsite_evidence import audit_callsite, instr_width  # noqa: E402

TOOL = str(PROJECT_ROOT / 'tools' / 'audit_callsite_evidence.py')

CALLSITE = 0x4b0b34          # `call 0x440960` 之一
PUSH_STR = 0x4b0b2f          # `push 0x5d37f8`
STRING_VA = 0x5d37f8
STRING_TXT = 'UI\\GameMainUI\\System\\Saveon.tga'


def _callsite(r, va):
    hits = [c for c in r['callsites'] if c['va'] == va]
    assert hits, 'no callsite 0x%x in %r' % (va, [c['va'] for c in r['callsites']])
    return hits[0]


# ---------------------------------------------------------------- 简报用例（逐字）
def test_pushed_literal_is_flagged():
    # 0x4b0b2f push 0x5d37f8 是字符串字面量（"UI\GameMainUI\System\Saveon.tga"）
    r = audit_callsite(0x440960)
    one = [c for c in r['callsites'] if c['va'] == 0x4b0b34][0]
    assert any(p['kind'] == 'imm' for p in one['pushes'])
    assert any(p['kind'] == 'reg' for p in one['pushes'])


def test_no_callsite_is_verdict_not_crash():
    # 0x43d890 是 virtual ⇒ 无静态调用点
    r = audit_callsite(0x43d890)
    assert r['callsites'] == []
    assert 'virtual' in r['verdict'].lower()


# ------------------------------------------------- 补裁决 ②：imm_str 分支必须覆盖
def test_imm_str_branch_flags_string_literal():
    r = audit_callsite(0x440960)
    one = _callsite(r, CALLSITE)
    p = [x for x in one['pushes'] if x['va'] == PUSH_STR]
    assert len(p) == 1, one['pushes']
    p = p[0]
    assert p['kind'] == 'imm_str', p
    assert p['value'] == STRING_VA, p
    assert p['string'] == STRING_TXT, p


# ------------------------------------- 补裁决 ③：全量反汇编定位（边界不许错位）
def test_instruction_boundaries_come_from_full_disasm():
    r = audit_callsite(0x440960)
    one = _callsite(r, CALLSITE)
    raw = '\n'.join(one['raw'])
    # 若起点错位，0x4b0b2f 处会解码成别的指令（此前两次手搓 objdump 即败于此）
    p = [x for x in one['pushes'] if x['va'] == PUSH_STR][0]
    assert p['text'] == '0x5d37f8', p
    assert '4b0b2f:' in raw and 'push   0x5d37f8' in raw, raw
    assert '4b0b34:' in raw and 'call   0x440960' in raw, raw


# ------------------------------------------------ 补裁决 ①：--width 宽度取证接口
def test_width_mov_movzx_lea():
    # 纯分类：mov 4B / movzx 1B / lea 取址（附带 byte/word 真实尺寸）
    assert instr_width('mov', 'ecx,edi') == 4
    assert instr_width('mov', 'dl,BYTE PTR ds:0x5cefa8') == 1
    assert instr_width('mov', 'DWORD PTR [esp+0x50],0x5') == 4
    assert instr_width('movzx', 'eax,BYTE PTR [esi+0x5c]') == 1
    assert instr_width('movzx', 'eax,WORD PTR [esi+0x5c]') == 2
    assert instr_width('lea', 'ecx,[esp+0x40]') == 'addr'
    assert instr_width('push', 'edx') is None   # push 不是 mov/lea，无宽度分类


def test_width_reported_per_callsite():
    r = audit_callsite(0x440960)
    one = _callsite(r, CALLSITE)
    widths = {e['va']: e['width'] for e in one['regs']}
    assert widths.get(0x4b0b2c) == 4, one['regs']     # mov ecx,edi
    assert widths.get(0x4b0b26) == 1, one['regs']     # mov dl,BYTE PTR ds:0x5cefa8
    assert 4 in one['widths'] and 1 in one['widths'], one['widths']


def test_cli_width_flag_reports_widths():
    r = subprocess.run([sys.executable, TOOL, '0x440960', '--width'],
                       capture_output=True, text=True, timeout=600)
    assert r.returncode == 0, (r.returncode, r.stdout[-500:], r.stderr[-500:])
    out = r.stdout
    assert 'verdict=direct' in out, out[-800:]
    assert 'imm_str' in out and STRING_TXT in out, out[-800:]
    assert 'width=4B' in out and 'width=1B' in out, out[-800:]
    # width=4B/1B 必须来自 regs 行（mov ecx,edi / mov dl,BYTE PTR ds:0x5cefa8）
    reg_lines = [l for l in out.splitlines() if l.strip().startswith('regs')]
    assert any('width=4B' in l for l in reg_lines), out[-800:]
    assert any('width=1B' in l for l in reg_lines), out[-800:]


# ------------------------- 修复轮 1（评审 Important）：push 不得携带/打印 width
def test_pushes_have_no_width_field():
    # 16-bit 前缀下 push 是 2B ⇒ 硬编码 width=4 会误导；宽度契约只在 regs（任务 5）
    r = audit_callsite(0x440960)
    for one in r['callsites']:
        for p in one['pushes']:
            assert 'width' not in p, p
    # CLI 同步：push 行不得打印 width=，regs 行（--width）仍打印
    r = subprocess.run([sys.executable, TOOL, '0x440960', '--width'],
                       capture_output=True, text=True, timeout=600)
    assert r.returncode == 0, (r.returncode, r.stdout[-500:], r.stderr[-500:])
    push_lines = [l for l in r.stdout.splitlines() if l.strip().startswith('push')]
    assert push_lines, r.stdout[-800:]
    for l in push_lines:
        assert 'width=' not in l, l


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
