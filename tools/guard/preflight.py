#!/usr/bin/env python3
"""preflight — 管线并发占用检测（只读，零依赖）。

用途：在跑 `match` / `census` 之前（以及落位提交前）确认没有别的
`pipeline/cli.py <apply|export|codegen|probe|loop>` 或
`tools/census_struct_holes.py` 正在跑。有并发时读数会被污染
（obj 目录被重写、生成树短时缺失、语料/基线被另一条管线刷新）。

返回码契约：
  0 = 干净（可以出数）
  2 = 检测到并发占用（不得把本次读数当基线）
  1 = 自身错误（本工具没跑起来；读数同样不可信）

本模块只读 /proc（或 --proc-root 指定的替代根），不写任何文件。
"""
from __future__ import annotations

import argparse
import json
import os
import sys
import time
import traceback
from dataclasses import dataclass, field
from typing import Callable, Iterable, Sequence

#: pipeline/cli.py 里会读/写共享产物（annotation 语料、IDB、obj、基线）的子命令。
OCCUPYING_SUBCOMMANDS: tuple[str, ...] = ("apply", "export", "codegen", "probe", "loop")

#: 普查器单独匹配（它是脚本不是 cli.py 子命令）。
CENSUS_SCRIPT = "census_struct_holes.py"

#: 进程快照来源签名：返回 [(pid, [argv...]), ...]。测试可替换。
PopenSource = Callable[[], Iterable[tuple[int, Sequence[str]]]]

_CLK_TCK = os.sysconf("SC_CLK_TCK") if hasattr(os, "sysconf") else 100


@dataclass
class ProcessInfo:
    pid: int
    argv: list[str]
    start_iso: str = "unknown"

    @property
    def cmdline(self) -> str:
        return " ".join(self.argv)


@dataclass
class Occupant:
    pid: int
    argv: list[str]
    start_iso: str
    matched: str  # 命中的子命令名，或 CENSUS_SCRIPT

    @property
    def cmdline(self) -> str:
        return " ".join(self.argv)

    def line(self) -> str:
        return (
            f"pid={self.pid} start={self.start_iso} matched={self.matched} "
            f"cmd={self.cmdline}"
        )


@dataclass
class ProbeResult:
    rc: int
    occupants: list[Occupant] = field(default_factory=list)
    scanned: int = 0
    excluded: list[int] = field(default_factory=list)
    note: str = ""

    @property
    def clean(self) -> bool:
        return self.rc == 0


# --------------------------------------------------------------------------
# 进程快照
# --------------------------------------------------------------------------
def _btime_iso() -> float:
    try:
        with open("/proc/stat", "r", encoding="utf-8", errors="replace") as fh:
            for line in fh:
                if line.startswith("btime "):
                    return float(line.split()[1])
    except OSError:
        pass
    return time.time()


def _start_iso(stat_text: str, btime: float) -> str:
    """从 /proc/<pid>/stat 第 22 字段推进程启动时刻（本地时间）。"""
    # comm 里可能有空格与括号，从右括号后开始切。
    tail = stat_text.rsplit(")", 1)[-1].split()
    # tail[0] 是 state(field 3)，故 field 22 对应 tail[19]
    try:
        ticks = int(tail[19])
    except (IndexError, ValueError):
        return "unknown"
    started = btime + ticks / _CLK_TCK
    return time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(started))


def read_processes(proc_root: str = "/proc") -> list[ProcessInfo]:
    """读 /proc 下全部进程的 argv 与启动时间。读不到的进程静默跳过。"""
    btime = _btime_iso()
    procs: list[ProcessInfo] = []
    for name in os.listdir(proc_root):
        if not name.isdigit():
            continue
        pid = int(name)
        try:
            with open(os.path.join(proc_root, name, "cmdline"), "rb") as fh:
                raw = fh.read()
        except OSError:
            continue
        if not raw:
            continue  # kernel thread / 僵尸
        argv = [p.decode("utf-8", "replace") for p in raw.split(b"\0") if p]
        if not argv:
            continue
        start_iso = "unknown"
        try:
            with open(os.path.join(proc_root, name, "stat"), "r", encoding="utf-8", errors="replace") as fh:
                start_iso = _start_iso(fh.read(), btime)
        except OSError:
            pass
        procs.append(ProcessInfo(pid=pid, argv=argv, start_iso=start_iso))
    return procs


def ancestors_of(pid: int, proc_root: str = "/proc") -> set[int]:
    """自身 + 全部祖先 pid（避免把「在 cli.py 管线里调用守卫」误判成并发）。"""
    out: set[int] = set()
    cur = pid
    while cur and cur not in out:
        out.add(cur)
        try:
            with open(os.path.join(proc_root, str(cur), "stat"), "r", encoding="utf-8", errors="replace") as fh:
                tail = fh.read().rsplit(")", 1)[-1].split()
            cur = int(tail[1])  # field 4 = ppid
        except (OSError, IndexError, ValueError):
            break
    return out


# --------------------------------------------------------------------------
# 判定
# --------------------------------------------------------------------------
def classify(argv: Sequence[str], include_match: bool = False) -> str | None:
    """返回命中的占用名，否则 None。"""
    targets = set(OCCUPYING_SUBCOMMANDS)
    if include_match:
        targets.add("match")
    for i, tok in enumerate(argv):
        base = os.path.basename(tok)
        norm = tok.replace("\\", "/")
        is_cli = base == "cli.py" and (
            norm.endswith("pipeline/cli.py")
            or (i >= 1 and os.path.basename(argv[i - 1]) == "pipeline")
        )
        if is_cli:
            for nxt in argv[i + 1:]:
                if nxt.startswith("-"):
                    continue
                return nxt if nxt in targets else None
        if base == CENSUS_SCRIPT:
            return CENSUS_SCRIPT
    return None


def find_occupants(
    procs: Iterable[ProcessInfo],
    exclude_pids: Iterable[int] = (),
    include_match: bool = False,
) -> list[Occupant]:
    excluded = set(exclude_pids)
    out: list[Occupant] = []
    for proc in procs:
        if proc.pid in excluded:
            continue
        matched = classify(proc.argv, include_match=include_match)
        if matched:
            out.append(
                Occupant(
                    pid=proc.pid,
                    argv=list(proc.argv),
                    start_iso=proc.start_iso,
                    matched=matched,
                )
            )
    return sorted(out, key=lambda o: o.pid)


def preflight(
    source: PopenSource | None = None,
    proc_root: str = "/proc",
    include_match: bool = False,
    self_pid: int | None = None,
) -> ProbeResult:
    """执行一次检测。异常一律折算成 rc=1（自身错误），由调用方决定处置。"""
    me = os.getpid() if self_pid is None else self_pid
    try:
        own = ancestors_of(me, proc_root=proc_root)
        if source is None:
            procs: list[ProcessInfo] = read_processes(proc_root)
        else:
            procs = [
                ProcessInfo(pid=int(pid), argv=[str(a) for a in argv], start_iso="mock")
                for pid, argv in source()
            ]
        occupants = find_occupants(procs, exclude_pids=own, include_match=include_match)
        return ProbeResult(
            rc=2 if occupants else 0,
            occupants=occupants,
            scanned=len(procs),
            excluded=sorted(own),
        )
    except Exception as exc:  # noqa: BLE001 - 契约要求任何自身异常都折成 rc1
        return ProbeResult(
            rc=1,
            note=f"{type(exc).__name__}: {exc}",
        )


def render_report(result: ProbeResult, as_json: bool = False) -> str:
    if as_json:
        return json.dumps(
            {
                "rc": result.rc,
                "verdict": {0: "clean", 2: "concurrent", 1: "error"}.get(result.rc, "error"),
                "scanned": result.scanned,
                "excluded_pids": result.excluded,
                "occupants": [
                    {"pid": o.pid, "start": o.start_iso, "matched": o.matched, "cmd": o.cmdline}
                    for o in result.occupants
                ],
                "note": result.note,
            },
            ensure_ascii=False,
            indent=2,
        )
    if result.rc == 1:
        return f"[guard] 自身错误：{result.note} — 读数不可信，先修工具再出数"
    if result.rc == 2:
        head = (
            f"[guard] DETECTED 并发占用 {len(result.occupants)} 个"
            f"（扫描 {result.scanned} 个进程）— 读数不可比（并发窗口），拒绝作为基线"
        )
        body = "\n".join(f"[guard]   {o.line()}" for o in result.occupants)
        return head + "\n" + body
    return (
        f"[guard] OK 干净（扫描 {result.scanned} 个进程）— 未检测到并发管线，可以出数"
    )


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="preflight",
        description="检测是否有并发管线进程（apply/export/codegen/probe/loop 或 census）",
    )
    parser.add_argument("--json", action="store_true", help="输出机器可读 JSON")
    parser.add_argument(
        "--include-match",
        action="store_true",
        help="把另一条 pipeline/cli.py match 也算占用（默认不算，见 README）",
    )
    parser.add_argument(
        "--proc-root",
        default="/proc",
        help="procfs 根（默认 /proc；测试用替代目录）",
    )
    args = parser.parse_args(list(argv) if argv is not None else None)

    try:
        result = preflight(proc_root=args.proc_root, include_match=args.include_match)
    except Exception:  # noqa: BLE001 - 兜底，绝不让守卫自己崩成 0
        print(f"[guard] 自身错误：{traceback.format_exc(limit=1).strip()}", file=sys.stderr)
        return 1
    print(render_report(result, as_json=args.json))
    return result.rc


if __name__ == "__main__":
    sys.exit(main())
