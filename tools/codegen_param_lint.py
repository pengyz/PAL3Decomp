#!/usr/bin/env python3
"""门禁：生成源码里的函数定义形参名**不得为纯数字**。

缘起（2026-09-15 独立复核 M1）：`pipeline/gen/stages/stage5_fixup.py` 的 H 块
缺 `ctx.is_dtor` 守卫，把**任何**「恰好 1 个 int/char 类形参」的普通函数的形参名
在整段函数体里替换成常量 `1`，产出 `int CEffCylinder::Update(int 1)` 这类**非法且语义损坏**
的签名（实测 30 处签名 / 17 个文件）。

为什么需要**独立**门禁：受害文件**本来就全是 fail**，而
`tools/compile_regression.py` 只比较 ok/fail 集合 ⇒ 该类损坏**在既有门禁下不可见**；
更危险的是它让受害文件的 error_count **下降**（解析崩塌），度量反而变"好看"。

判据（刻意做窄，避免误报）：
  形参列表里出现「类型 数字」形态，即形参名为纯十进制数字。
  只扫 `pal3/src/**/*.cpp` 的**函数定义行**（形如 `Ret Cls::Name(` 或 `Ret Name(`），
  不扫调用点、不扫宏、不扫字符串。

用法：
  python3 tools/codegen_param_lint.py            # 扫描 pal3/src
  python3 tools/codegen_param_lint.py --quiet    # 只在出错时输出

退出码：0 = 无命中；1 = 命中（视为门禁失败）；2 = 前置产物缺失（也是失败）。
"""
import argparse
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
SRC_DIR = os.path.join(ROOT, "pal3", "src")

# 形参名为纯数字：<type> <digits>
# type 允许指针/引用/const 与常见内建类型；只匹配**纯数字**名，故误报面极小。
_NUMERIC_PARAM = re.compile(
    r"(?:^|[,\(])\s*"                       # 形参边界
    r"(?:const\s+)?"
    r"(?:unsigned\s+|signed\s+)?"
    r"(?:void|char|short|int|long|float|double|bool|"
    r"__int8|__int16|__int32|__int64|"
    r"_BYTE|_WORD|_DWORD|BYTE|WORD|DWORD)"
    r"\s*\*?\s*"                            # 可选指针
    r"(\d+)"                                # ← 形参名是数字
    r"\s*(?=[,\)])"
)

# 函数定义行：必须含 '(' 与 ')'，且以 '{' 结束或行尾即参数表（定义体在下一行）
_DEF_LINE = re.compile(r"^\s*[A-Za-z_~][\w:<>,*&\s]*\([^;]*\)\s*\{?\s*$")


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--quiet", action="store_true", help="只在出错时输出")
    ap.add_argument("--src", default=SRC_DIR, help="源码目录（默认 pal3/src）")
    args = ap.parse_args()

    src = args.src
    if not os.path.isdir(src):
        print("[ERROR] source dir not found: %s" % src)
        print("  Run 'python pipeline/cli.py codegen all' first.")
        return 2

    hits = []
    n_files = 0
    for dirpath, _dirs, files in os.walk(src):
        for fn in files:
            if not fn.endswith(".cpp"):
                continue
            n_files += 1
            p = os.path.join(dirpath, fn)
            try:
                with open(p, "r", encoding="utf-8", errors="replace") as f:
                    for ln, line in enumerate(f, 1):
                        if "(" not in line:
                            continue
                        if not _DEF_LINE.match(line.rstrip("\n")):
                            continue
                        m = _NUMERIC_PARAM.search(line)
                        if m:
                            rel = os.path.relpath(p, ROOT)
                            hits.append("%s:%d: parameter name is a bare number "
                                        "('%s')" % (rel, ln, m.group(0).strip()))
            except OSError as e:
                print("[WARN] unreadable %s: %s" % (p, e))

    if hits:
        print("❌ GENERATED-SOURCE LINT FAILED: %d function definition(s) have a "
              "numeric parameter name." % len(hits))
        print("   This means a codegen stage replaced a parameter name with a "
              "constant — the function body's semantics are corrupted, not just "
              "its syntax. See data/status/_cleanup_review_next_step.json (M1).")
        for h in hits[:40]:
            print("   " + h)
        if len(hits) > 40:
            print("   ... and %d more" % (len(hits) - 40))
        return 1

    if not args.quiet:
        print("✅ generated-source lint OK (%d .cpp scanned, 0 numeric parameter names)"
              % n_files)
    return 0


if __name__ == "__main__":
    sys.exit(main())