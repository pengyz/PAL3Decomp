#!/usr/bin/env python3
"""reading_guard — 给 match / census 读数打「可比/不可比」标记。

和 preflight 的分工：
  preflight     只回答「现在有没有并发」；
  reading_guard 接住一条具体读数（match 的 L1/matched、census 的洞字节），
                在并发窗口里把它标成「读数不可比（并发窗口）」并拒绝当基线。

输出证据行（stdout）：
  [guard] reading=match value="L1 196" verdict=not-comparable
  [guard] reason=并发占用 pid=123 ... start=... cmd=...
  [guard] baseline_allowed=false —— 不要写 s4_baseline / 不要据此归因

返回码：0=可比（可作基线）/ 2=不可比（并发窗口）/ 1=自身错误。
本工具只读、只打印，不写 data/ 任何文件。
"""
from __future__ import annotations

import argparse
import json
import sys
from dataclasses import dataclass
from typing import Sequence

try:  # 作为包导入（python -m tools.guard.reading_guard）
    from .preflight import PopenSource, ProbeResult, preflight, render_report
except ImportError:  # 直接当脚本跑（python3 tools/guard/reading_guard.py）
    import os
    import sys as _sys

    _sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
    from tools.guard.preflight import (  # type: ignore[no-redef]
        PopenSource,
        ProbeResult,
        preflight,
        render_report,
    )


@dataclass
class ReadingVerdict:
    reading: str
    value: str
    verdict: str  # comparable | not-comparable
    baseline_allowed: bool
    rc: int
    result: ProbeResult

    def evidence_lines(self) -> list[str]:
        lines = [f'[guard] reading={self.reading} value="{self.value}" verdict={self.verdict}']
        if self.result.rc == 2:
            lines.append(f"[guard] reason=并发窗口（{len(self.result.occupants)} 个占用进程）")
            lines.extend(f"[guard]   {o.line()}" for o in self.result.occupants)
        elif self.result.rc == 1:
            lines.append(f"[guard] reason=守卫自身错误：{self.result.note}")
        else:
            lines.append(f"[guard] reason=干净（扫描 {self.result.scanned} 个进程）")
        lines.append(
            f"[guard] baseline_allowed={'true' if self.baseline_allowed else 'false'}"
            + (
                ""
                if self.baseline_allowed
                else " —— 不要写基线 / 不要据此归因，等并发退出后重跑"
            )
        )
        return lines

    def to_json(self) -> str:
        return json.dumps(
            {
                "reading": self.reading,
                "value": self.value,
                "verdict": self.verdict,
                "baseline_allowed": self.baseline_allowed,
                "rc": self.rc,
                "occupants": [
                    {"pid": o.pid, "start": o.start_iso, "matched": o.matched, "cmd": o.cmdline}
                    for o in self.result.occupants
                ],
                "note": self.result.note,
            },
            ensure_ascii=False,
            indent=2,
        )


def guard_reading(
    reading: str,
    value: str,
    source: PopenSource | None = None,
    proc_root: str = "/proc",
    include_match: bool = False,
) -> ReadingVerdict:
    result = preflight(source=source, proc_root=proc_root, include_match=include_match)
    if result.rc == 0:
        verdict, allowed = "comparable", True
    elif result.rc == 2:
        verdict, allowed = "not-comparable", False
    else:
        verdict, allowed = "not-comparable", False
    return ReadingVerdict(
        reading=reading,
        value=value,
        verdict=verdict,
        baseline_allowed=allowed,
        rc=result.rc,
        result=result,
    )


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="reading_guard",
        description="给 match/census 读数打可比性标记，并发窗口内拒绝作为基线",
    )
    parser.add_argument("--reading", required=True, help="读数名，如 match / census")
    parser.add_argument("--value", required=True, help="读数原文，如 'L1 196'")
    parser.add_argument("--json", action="store_true", help="输出机器可读 JSON")
    parser.add_argument(
        "--include-match",
        action="store_true",
        help="把另一条 pipeline/cli.py match 也算占用（默认不算）",
    )
    parser.add_argument("--proc-root", default="/proc", help="procfs 根（默认 /proc）")
    parser.add_argument(
        "--preflight-only",
        action="store_true",
        help="只跑占用检测（等价于 preflight.py），不带读数",
    )
    args = parser.parse_args(list(argv) if argv is not None else None)

    try:
        if args.preflight_only:
            result = preflight(
                proc_root=args.proc_root, include_match=args.include_match
            )
            print(render_report(result, as_json=args.json))
            return result.rc
        verdict = guard_reading(
            args.reading,
            args.value,
            proc_root=args.proc_root,
            include_match=args.include_match,
        )
    except Exception as exc:  # noqa: BLE001 - 契约：自身错误必须 rc1
        print(f"[guard] 自身错误：{type(exc).__name__}: {exc}", file=sys.stderr)
        return 1

    if args.json:
        print(verdict.to_json())
    else:
        print("\n".join(verdict.evidence_lines()))
    return verdict.rc


if __name__ == "__main__":
    sys.exit(main())
