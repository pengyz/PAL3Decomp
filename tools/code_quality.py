#!/usr/bin/env python3
"""代码质量基线测量（**纯计量**，不改任何判据/不影响 L1/S2/总错误）。

## 第一性洞察（用户 2026-10-15）
> 不报错 + 字节一致 ≠ 代码还原度到位；**类型衰退本身无法被这两个指标度量**
> （`void*` vs `RoleSystem*` 编出同样字节）⇒ 类型衰退是**静默劣化**。

## 7 项可量化指标（每编译单元）
| # | 指标 | 判据（正则/计数） |
|---|------|------------------|
| 1 | 裸 cast 密度 | `(_DWORD)`/`(__int64)`/`(type*)` 等 IDA 型 C-style cast 数 / 千行 |
| 2 | 指针算术密度 | `*(_DWORD*)` 解引用铸 / `this±N` / `(char*)±N` 数 / 千行 |
| 3 | Hex-Rays 变量名率 | `v\\d+`/`p_\\w+`/`_\\w+` 形标识符占全部标识符比 |
| 4 | 未命名函数率 | 定义名 `sub_\\w+`/`_\\w+_\\w+`（地址后缀形）占全部函数定义比 |
| 5 | 魔法数字密度 | 代码位（非注释/串）裸数字字面量数 / 千行（0/1 除外） |
| 6 | 寄存器/栈注释率 | 含 eax..edi/esp/ebp/[esp 的注释数 / 千行 |
| 7 | TODO 未解决数 | `TODO:` 注释计数 |

R15：纯函数 `measure_text`（fixture 可测，不碰真 pal3/src）→ tests/test_code_quality.py。

用法：
    python tools/code_quality.py --all              # 全量测量 + 基线写盘 + 高密度清单
    python tools/code_quality.py --unit <相对路径>   # 单元明细
退出码：0（纯计量恒 0，除非输入不可读）。
"""
import argparse
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_ROOT = os.path.join(REPO, 'pal3', 'src')
BASELINE_PATH = os.path.join(REPO, 'data', 'status', 'quality_baseline.json')

# ── 判据正则（纯计量；集中定义便于审阅/单测）────────────────────────
# ① 裸 cast：IDA 型名的 C-style cast（含指针形）
_RE_CAST = re.compile(
    r'\(\s*(?:_DWORD|_BYTE|_WORD|_QWORD|_UNKNOWN|__int(?:8|16|32|64|128)|'
    r'unsigned\s+__int(?:8|16|32|64)|signed\s+__int(?:8|16|32|64)|'
    r'DWORD|BYTE|WORD|LONG|UINT|BOOL|HANDLE|HWND|LPSTR|LPCSTR|'
    r'int|char|short|long|float|double|void)\s*(\**)\s*\)')
# ② 指针算术：dword 解引用铸 / this±N / (T*)±N
_RE_PTR_ARITH = re.compile(
    r'\*\s*\(\s*(?:_DWORD|_BYTE|_WORD|_QWORD|unsigned int|unsigned long|int)\s*\*\)'
    r'|this\s*[+-]\s*0x[0-9A-Fa-f]+'
    r'|\(\s*char\s*\*\s*\)\s*[\w\)]+\s*[+-]\s*\d+')
# ③ Hex-Rays 变量名：v12 / p_fn / _x / _DWORD 系
_RE_HR_NAME = re.compile(r'^v\d+$|^p_[A-Za-z]\w*$|^_[A-Za-z]\w*$')
_RE_IDENT = re.compile(r'\b[A-Za-z_]\w*\b')
# ④ 未命名函数：sub_XXXX / _name_XXXX / foo_a1b2 地址后缀形
_RE_UNNAMED_FN = re.compile(r'^sub_[0-9A-Fa-f]+$|^\w+_[0-9A-Fa-f]{3,}$')
_RE_FNDEF = re.compile(r'\b([A-Za-z_][\w:]*)\s*\([^;]*?\)\s*\{', re.M)  # 非贪婪：防跨函数吞并
# ⑤ 魔法数字（代码位裸数字；0/1 除外）
_RE_NUM = re.compile(r'\b(?:0x[0-9A-Fa-f]+|\d+)\b')
# ⑥ 寄存器/栈注释
_RE_REG_COMMENT = re.compile(
    r'//.*\b(?:eax|ebx|ecx|edx|esi|edi|esp|ebp|r\d+)\b|//.*\[esp[+\]]')
# ⑦ TODO
_RE_TODO = re.compile(r'TODO:')

_RE_COMMENT = re.compile(r'//[^\n]*|/\*.*?\*/', re.S)
_RE_STRING = re.compile(r'"(?:[^"\\]|\\.)*"|\'(?:[^\'\\]|\\.)*\'')


def _mask_noncode(text):
    """把注释与字符串字面量掩成空格（保行号/列位）⇒ 只剩代码位。"""
    out = _RE_COMMENT.sub(lambda m: ' ' * len(m.group(0)), text)
    return _RE_STRING.sub(lambda m: ' ' * len(m.group(0)), out)


def measure_text(text):
    """纯函数：一段 C/C++ 源文本 → 7 指标 dict（R15 单测点）。"""
    lines = text.splitlines()
    n_lines = len(lines)
    code = _mask_noncode(text)
    kloc = max(n_lines, 1) / 1000.0

    casts = len(_RE_CAST.findall(code))
    ptr_arith = len(_RE_PTR_ARITH.findall(code))
    idents = _RE_IDENT.findall(code)
    hr = sum(1 for i in idents if _RE_HR_NAME.match(i))
    fndefs = [m.group(1).split('::')[-1] for m in _RE_FNDEF.finditer(code)]
    unnamed = sum(1 for f in fndefs if _RE_UNNAMED_FN.match(f))
    nums = sum(1 for m in _RE_NUM.finditer(code)
               if m.group(0) not in ('0', '1', '0x0', '0x1', '0x00', '0x01'))
    reg_comments = len(_RE_REG_COMMENT.findall(text))
    todos = len(_RE_TODO.findall(text))

    return {
        'lines': n_lines,
        'cast_per_kloc': round(casts / kloc, 2),
        'ptr_arith_per_kloc': round(ptr_arith / kloc, 2),
        'hexrays_name_rate': round(hr / max(len(idents), 1), 4),
        'unnamed_fn_rate': round(unnamed / max(len(fndefs), 1), 4),
        'magic_num_per_kloc': round(nums / kloc, 2),
        'reg_comment_per_kloc': round(reg_comments / kloc, 2),
        'todo_count': todos,
        '_raw': {'casts': casts, 'ptr_arith': ptr_arith, 'idents': len(idents),
                 'hr_names': hr, 'fndefs': len(fndefs), 'unnamed_fns': unnamed,
                 'magic_nums': nums, 'reg_comments': reg_comments},
    }


def bucket_of(n_lines):
    """按文件长度分桶：小 / 中 / 大 / 超大。"""
    if n_lines < 200:
        return '小(<200 行)'
    if n_lines < 1000:
        return '中(200-1000 行)'
    if n_lines < 5000:
        return '大(1000-5000 行)'
    return '超大(>=5000 行)'


def measure_tree(root):
    """root 下全部 .cpp/.h 逐文件测量 + 聚合（确定性：路径排序）。"""
    units = []
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames.sort()
        for fn in sorted(filenames):
            if not fn.endswith(('.cpp', '.h')):
                continue
            full = os.path.join(dirpath, fn)
            rel = os.path.relpath(full, root).replace(os.sep, '/')
            try:
                text = open(full, encoding='utf-8', errors='replace').read()
            except OSError:
                continue
            m = measure_text(text)
            m['unit'] = rel
            m['bucket'] = bucket_of(m['lines'])
            units.append(m)
    return units


def summarize(units):
    """7 项指标全仓均值（按行数加权）+ 分桶统计。"""
    total_lines = sum(u['lines'] for u in units) or 1

    def wavg(key):
        return round(sum(u[key] * u['lines'] for u in units) / total_lines, 2)

    def wrate(key):
        return round(sum(u[key] * u['lines'] for u in units) / total_lines, 4)

    buckets = {}
    for u in units:
        b = buckets.setdefault(u['bucket'], {'units': 0, 'lines': 0})
        b['units'] += 1
        b['lines'] += u['lines']
    return {
        'units': len(units),
        'total_lines': total_lines,
        'avg': {
            'cast_per_kloc': wavg('cast_per_kloc'),
            'ptr_arith_per_kloc': wavg('ptr_arith_per_kloc'),
            'hexrays_name_rate': wrate('hexrays_name_rate'),
            'unnamed_fn_rate': wrate('unnamed_fn_rate'),
            'magic_num_per_kloc': wavg('magic_num_per_kloc'),
            'reg_comment_per_kloc': wavg('reg_comment_per_kloc'),
            'todo_per_kloc': round(sum(u['todo_count'] for u in units) / total_lines * 1000, 2),
        },
        'buckets': buckets,
    }


def top_offenders(units, key, n=10):
    return [{'unit': u['unit'], key: u[key], 'lines': u['lines']}
            for u in sorted(units, key=lambda x: (-x[key], x['unit']))[:n]]


def main(argv=None):
    ap = argparse.ArgumentParser(description='代码质量基线测量（纯计量）')
    ap.add_argument('--root', default=DEFAULT_ROOT)
    ap.add_argument('--all', action='store_true', help='全量测量 + 写基线')
    ap.add_argument('--unit', help='单单元明细（相对路径）')
    args = ap.parse_args(argv)
    root = os.path.abspath(args.root)

    if args.unit:
        text = open(os.path.join(root, args.unit), encoding='utf-8',
                    errors='replace').read()
        print(json.dumps(measure_text(text), ensure_ascii=False, indent=2))
        return 0

    units = measure_tree(root)
    if not units:
        print('[code-quality] 无测量对象：%s' % root)
        return 1
    summary = summarize(units)
    print('=== 代码质量基线（纯计量）===')
    print('单元 %d · 总行 %d' % (summary['units'], summary['total_lines']))
    for k, v in summary['avg'].items():
        print('  %-22s %s' % (k, v))
    print('--- 分桶 ---')
    for b in sorted(summary['buckets']):
        v = summary['buckets'][b]
        print('  %-18s 单元 %-4d 行 %d' % (b, v['units'], v['lines']))
    print('--- 高密度 TOP10（改善优先级）---')
    for key in ('cast_per_kloc', 'hexrays_name_rate', 'magic_num_per_kloc'):
        print('  [%s]' % key)
        for row in top_offenders(units, key):
            print('    %-56s %8s  (%d 行)'
                  % (row['unit'][:56], row[key], row['lines']))
    if args.all:
        os.makedirs(os.path.dirname(BASELINE_PATH), exist_ok=True)
        with open(BASELINE_PATH, 'w', encoding='utf-8') as f:
            json.dump({'summary': summary,
                       'units': [{k: v for k, v in u.items() if k != '_raw'}
                                 for u in units]},
                      f, ensure_ascii=False, indent=2, sort_keys=True)
        print('基线已写入 %s' % BASELINE_PATH)
    return 0


if __name__ == '__main__':
    sys.exit(main())
