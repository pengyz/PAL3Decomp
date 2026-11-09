#!/usr/bin/env python3
"""VC6 DBCS 注释吞行修复/检查（2026-11-09，probe s2 0/215 根因治理）。

根因（编译器-as-oracle 实证标定，16/16 用例全过）：
  VC6 预处理器在 CP936 下扫描 `//` 与 `/*` 注释时做 DBCS 配对——
  lead 字节 ∈ [0x81,0xFE] **无条件**吞掉下一字节（不校验 trail、包括 \n）。
  行尾恰为 lead 时换行被吞 ⇒ 注释续行吞掉下一逻辑行（如 `class X {`），
  解析灾难级联（gbChain.h 15 行吞掉 class 行 → 215 TU 全灭）。
  特例：UTF-8 全角句号 `。`(\xe3\x80\x82) 中间字节 \x80 非 GBK lead，
  会打断配对链——朴素"奇数高位字节"判据不可靠，必须逐步模拟。

修复：给毒行行尾补一个 ASCII 空格（lead 配对空格、\n 释放、注释内容零改动）。
  行尾空格易被未来 trim 工具剥掉而无声复活 ⇒ 本工具同时是 CI 检查器。

用法:
  python3 tools/fix_vc6_dbcs_comment_splice.py          # 修复(默认扫描 include/ pal3/src)
  python3 tools/fix_vc6_dbcs_comment_splice.py --check  # 只检查, 有毒行 exit 1
"""
import os, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ROOTS = [os.path.join(REPO, 'include'), os.path.join(REPO, 'pal3', 'src')]

def vc6_splice(line_bytes):
    """模拟 VC6 CP936 注释扫描: lead∈[0x81,0xFE] 无条件吞下一字节。
    返回 True = 行尾 lead 吞掉 \\n(续行吞掉下一逻辑行)。"""
    i, n = 0, len(line_bytes)
    while i < n:
        if 0x81 <= line_bytes[i] <= 0xFE:
            i += 2
        else:
            i += 1
    return i > n

def iter_files():
    for root in ROOTS:
        for dp, _, fns in os.walk(root):
            for fn in fns:
                if fn.endswith(('.h', '.cpp')):
                    yield os.path.join(dp, fn)

def main():
    check_only = '--check' in sys.argv
    fixed_files, poison_total = [], 0
    for p in iter_files():
        with open(p, 'rb') as f:
            data = f.read()
        lines = data.split(b'\n')
        hits = [i for i, l in enumerate(lines) if vc6_splice(l.rstrip(b'\r'))]
        if not hits:
            continue
        poison_total += len(hits)
        rel = os.path.relpath(p, REPO)
        if check_only:
            print(f'[POISON] {rel}: lines {[i+1 for i in hits]}')
            continue
        for i in hits:
            if lines[i].endswith(b'\r'):
                lines[i] = lines[i][:-1] + b' \r'   # CRLF 行: 空格插在 \r 前
            else:
                lines[i] = lines[i] + b' '
        with open(p, 'wb') as f:
            f.write(b'\n'.join(lines))
        fixed_files.append(rel)
        print(f'[FIXED]  {rel}: {len(hits)} 行补防御空格')
    if check_only:
        if poison_total:
            print(f'--check: {poison_total} 毒行存在 → exit 1')
            return 1
        print('--check: 无毒行')
        return 0
    print(f'--- 修复 {len(fixed_files)} 文件 / {poison_total} 毒行')
    return 0

if __name__ == '__main__':
    sys.exit(main())
