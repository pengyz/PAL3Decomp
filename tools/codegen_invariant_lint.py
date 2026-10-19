#!/usr/bin/env python3
"""生成源「跨变换不变量」门禁（codegen invariant lint）。

## 为什么需要这个门禁（2026-10-19 复盘结论）

本仓 codegen 的缺陷不是零散 bug，而是**同构的机制缺陷**：每个变换把构造
"搬进新上下文"，只保局部正确，不保旧上下文的不变量。本次会话亲历 4 例连环：

| 修复 | 搬动 | 丢失的不变量 | 后果 |
|---|---|---|---|
| C2011 hoist | 定义 → 共享头 | 声明依赖（fwd/include）| C2501 430 + C2143 224 + C2146 218 |
| C2273 限定 this | `Cls()` → `this->Cls::Cls()` | C++ 合法性 | C2059 585 |
| C2039 union 包裹 | 数组成员 → union 值成员 | 可索引性 | C2440 + C2228 |
| F83 reg 提升 | 寄存器 → `unsigned long` 变量 | 值的种类（可作指针）| C2227 33 |

共同形式：`变换 T` 在旧上下文 C 中正确，但 T 的产物被放进新上下文 C′，
C′ 缺少 C 提供的性质 P ⇒ 不成立。**管线只校验 T 的局部正确性，从不校验 P 保持。**

本门禁把 P 显式化并自动校验，让新形态在**到达编译器之前**被拦下，
而不是靠 MSVC 报错后逐个形态打补丁。

## 不变量（当前两条，均可加）

I1. `reg_XXX` 若声明为标量（`unsigned long reg_X = 0;`），则不得被当指针使用
    （`reg_X->member` / `*reg_X`）。寄存器伪值可以是整数或地址，声明成标量后
    指针用法必然非法 ⇒ C2227 / C2100。
I2. 类型名不得出现在成员位（`x->ClassName`）。合法例外：`x->Cls::Method()`
    （限定调用）与 `x->~Cls()`（dtor）。

## 制式

- **棘轮**：不追溯存量，只禁止新增（与 compile_regression / link_probe 一致）
- `--baseline` 打印/刷新基线；`--advisory` 恒 exit 0（存量清零前的过渡态）
- 纯函数实现（R15：tests/test_codegen_invariant_lint.py 覆盖各形态）
"""
import argparse
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(HERE)
SRC_DIR = os.path.join(PROJECT_ROOT, 'pal3', 'src')
BASELINE = os.path.join(PROJECT_ROOT, 'data', 'status',
                        'codegen_invariant_baseline.json')

# ---------------------------------------------------------------- 纯函数部分

# I1: reg_ 变量的标量声明
_RE_REG_SCALAR_DECL = re.compile(
    r'\b(?:unsigned\s+long|int|_DWORD|unsigned\s+int)\s+(reg_[A-Z]\w*)\s*=\s*0\s*;')
# I1: reg_ 变量被当指针用 —— `reg_X->` 或明确解引用 `*reg_X`
_RE_REG_ARROW = re.compile(r'\b(reg_[A-Z]\w*)\s*->')
# 解引用：`*reg_X` —— 是否真为解引用由 prev_nonspace() 判定（排除乘法）
_RE_REG_DEREF = re.compile(r'\*\s*(reg_[A-Z]\w*)\b')

# I2: `->TypeName` 且后面不是 `::` 也不是 `~`（限定调用/dtor 合法）
_RE_ARROW_TYPE = re.compile(r'->\s*([A-Z]\w*)\s*(?!::)')


def mask_strings_comments(src):
    """把字符串/字符字面量与注释替换成等长占位（保持偏移不变）。

    等价变换：只抹内容不改长度 ⇒ 报错行列号仍准确。
    """
    out = list(src)
    n = len(src)
    i = 0
    while i < n:
        c = src[i]
        # 行注释
        if c == '/' and i + 1 < n and src[i + 1] == '/':
            j = src.find('\n', i)
            j = n if j == -1 else j
            for k in range(i, j):
                out[k] = ' '
            i = j
            continue
        # 块注释
        if c == '/' and i + 1 < n and src[i + 1] == '*':
            j = src.find('*/', i + 2)
            j = n if j == -1 else j + 2
            for k in range(i, j):
                if out[k] != '\n':
                    out[k] = ' '
            i = j
            continue
        # 字符串 / 字符字面量
        if c in ('"', "'"):
            q = c
            j = i + 1
            while j < n:
                if src[j] == '\\':
                    j += 2
                    continue
                if src[j] == q:
                    j += 1
                    break
                j += 1
            for k in range(i, min(j, n)):
                if out[k] != '\n':
                    out[k] = ' '
            i = j
            continue
        i += 1
    return ''.join(out)


def prev_nonspace(masked, pos):
    """返回 pos 之前最近的**非空白**字符（跳过行内空白），行首返回 ''。"""
    i = pos - 1
    while i >= 0 and masked[i] in ' \t':
        i -= 1
    return masked[i] if i >= 0 else ''


def is_deref_context(masked, star_pos):
    """`*` 是否为解引用（而非乘法）。

    判据：前一个非空白字符若为标识符字符 / `)` / `]`，说明左边有操作数
    ⇒ 是二元乘法；否则是前缀解引用。
    """
    ch = prev_nonspace(masked, star_pos)
    if ch == '' :
        return True                 # 行首/块首 ⇒ 解引用
    if ch in ')]':
        return False
    if ch.isalnum() or ch == '_':
        return False
    return True


def find_reg_ptr_use_violations(src):
    """I1：返回 [(line, kind, name)]，kind ∈ {'arrow','deref'}。

    只对**标量声明**的 reg_ 变量报；`Cls *reg_X = this;` 的指针声明不报
    （F83 的类特化路径本就声明成指针）。
    """
    masked = mask_strings_comments(src)
    scalar = set(_RE_REG_SCALAR_DECL.findall(masked))
    if not scalar:
        return []
    hits = []
    for m in _RE_REG_ARROW.finditer(masked):
        nm = m.group(1)
        if nm in scalar:
            hits.append((masked.count('\n', 0, m.start(1)) + 1, 'arrow', nm))
    for m in _RE_REG_DEREF.finditer(masked):
        nm = m.group(1)
        if nm not in scalar:
            continue
        if not is_deref_context(masked, m.start()):
            continue                # 二元乘法，非解引用 ⇒ 不报
        hits.append((masked.count('\n', 0, m.start(1)) + 1, 'deref', nm))
    return hits


def find_type_in_member_position(src, type_names):
    """I2：返回 [(line, type_name)] —— `x->TypeName` 且 TypeName 是已知类型名。

    合法例外：`x->Cls::Method()`（后跟 `::`）与 `x->~Cls()`（前置 `~`）。
    """
    if not type_names:
        return []
    masked = mask_strings_comments(src)
    hits = []
    for m in _RE_ARROW_TYPE.finditer(masked):
        nm = m.group(1)
        if nm not in type_names:
            continue
        # dtor：`->~Cls`
        if m.start() >= 1 and masked[m.start() - 1] == '~':
            continue
        # 限定调用：`->Cls::Method`
        tail = masked[m.end(1):m.end(1) + 2]
        if tail.startswith('::'):
            continue
        hits.append((masked.count('\n', 0, m.start(1)) + 1, nm))
    return hits


def collect_type_names(hdr_dirs):
    """从生成头收集类/结构/联合/typedef 名（供 I2 判定）。"""
    names = set()
    pat_def = re.compile(r'^\s*(?:class|struct|union)\s+([A-Za-z_]\w*)\s*(?::|\{)', re.M)
    pat_td = re.compile(r'^\s*typedef\s+[^;]*?\b([A-Za-z_]\w*)\s*;', re.M)
    for d in hdr_dirs:
        for root, _dirs, files in os.walk(d):
            for f in files:
                if not f.endswith('.h'):
                    continue
                try:
                    with open(os.path.join(root, f), encoding='utf-8',
                              errors='replace') as fh:
                        txt = fh.read()
                except OSError:
                    continue
                names.update(pat_def.findall(txt))
                names.update(pat_td.findall(txt))
    return names


# ---------------------------------------------------------------- 扫描部分

def scan_files(src_dir, type_names):
    """返回 {'reg_ptr_use': [...], 'type_in_member': [...]}（每条含 file/line）。"""
    out = {'reg_ptr_use': [], 'type_in_member': []}
    for root, _dirs, files in os.walk(src_dir):
        for f in files:
            if not f.endswith('.cpp'):
                continue
            path = os.path.join(root, f)
            try:
                with open(path, encoding='utf-8', errors='replace') as fh:
                    src = fh.read()
            except OSError:
                continue
            rel = os.path.relpath(path, PROJECT_ROOT)
            for line, kind, nm in find_reg_ptr_use_violations(src):
                out['reg_ptr_use'].append(
                    {'file': rel, 'line': line, 'kind': kind, 'name': nm})
            for line, nm in find_type_in_member_position(src, type_names):
                out['type_in_member'].append(
                    {'file': rel, 'line': line, 'type': nm})
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--quiet', action='store_true')
    ap.add_argument('--advisory', action='store_true',
                    help='恒 exit 0（存量清零前的过渡态）')
    ap.add_argument('--baseline', action='store_true',
                    help='刷新棘轮基线（只在确认不是退化后手工执行）')
    ap.add_argument('--json', action='store_true')
    args = ap.parse_args()

    type_names = collect_type_names([
        os.path.join(PROJECT_ROOT, 'pal3', 'src'),
        os.path.join(PROJECT_ROOT, 'include', 'pal3'),
    ])
    res = scan_files(SRC_DIR, type_names)

    cur = {
        'reg_ptr_use': len(res['reg_ptr_use']),
        'type_in_member': len(res['type_in_member']),
    }
    cur['total'] = cur['reg_ptr_use'] + cur['type_in_member']

    base = {}
    if os.path.exists(BASELINE):
        try:
            with open(BASELINE, encoding='utf-8') as fh:
                base = json.load(fh).get('counts') or {}
        except (OSError, ValueError):
            base = {}

    if args.baseline:
        os.makedirs(os.path.dirname(BASELINE), exist_ok=True)
        with open(BASELINE, 'w', encoding='utf-8') as fh:
            json.dump({'counts': cur,
                       'note': 'codegen invariant lint ratchet baseline; '
                               'refresh only after confirming no real regression'},
                      fh, ensure_ascii=False, indent=2)
        print('baseline written: %s' % json.dumps(cur, ensure_ascii=False))
        return 0

    if args.json:
        print(json.dumps({'current': cur, 'baseline': base, 'detail': res},
                         ensure_ascii=False, indent=2))
    else:
        if not args.quiet:
            print('[I1] reg_ 标量声明被当指针用: %d' % cur['reg_ptr_use'])
            for it in res['reg_ptr_use'][:10]:
                print('     %s:%d  %s (%s)' % (it['file'], it['line'],
                                               it['name'], it['kind']))
            print('[I2] 类型名出现在成员位: %d' % cur['type_in_member'])
            for it in res['type_in_member'][:10]:
                print('     %s:%d  ->%s' % (it['file'], it['line'], it['type']))

    # 棘轮判定：任一不变量计数超过基线 ⇒ 新增（fail）
    regressed = []
    for k in ('reg_ptr_use', 'type_in_member', 'total'):
        old = base.get(k)
        if old is None:
            continue
        if cur[k] > old:
            regressed.append((k, old, cur[k]))

    if regressed and not args.advisory:
        print('\n[codegen-invariant] FAIL: 新增不变量破坏（棘轮基线被突破）')
        for k, old, new in regressed:
            print('  %s: %s -> %s (+%d)' % (k, old, new, new - old))
        print('  修好再跑；确属视野扩大（如新增编译单元）请显式 --baseline 重锚并写明理由。')
        return 1

    if regressed:
        print('\n[codegen-invariant] ADVISORY：棘轮被突破但不阻断（--advisory 模式）')
    else:
        print('\n[codegen-invariant] OK（无新增不变量破坏）')
    return 0


if __name__ == '__main__':
    sys.exit(main())
