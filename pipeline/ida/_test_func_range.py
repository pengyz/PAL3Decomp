"""函数范围标注机制的**行为测试台**——验证 IDA API 的拆分语义。

## 目的（用户要求："写测试用例确保机制有效"）

在**落地 annotation 的 `end` 字段**之前，先确认三个决定实现顺序的未知行为：

1. `set_func_end(addr, split)` 是否会因"与下一个函数重叠"而失败？
2. `add_func(split, end)` 在"已有函数覆盖该地址"时的行为（失败？需先 `del_func`？）？
3. 把 `end` 调大（延长）是否也受重叠约束？

## 用法（**只在 /tmp 的 IDB 副本上跑**）

    cp original/PAL3.exe.i64 /tmp/range_test.i64
    idat -A -S"pipeline/ida/_test_func_range.py" /tmp/range_test.i64

脚本**会修改传入的 IDB**（这正是必须在副本上跑的原因），
并在每个实验后**复原**。内置安全闸：路径含生产 IDB 且不在 /tmp 下则拒绝运行。

输出：`pipeline/ida/_logs/func_range_test.json`
（`-A` 模式下 `print()` 不落盘，故用 `idaapi.msg()`。）
"""
import json
import os

import ida_funcs
import idaapi
import idautils
import idc

idaapi.auto_wait()


def _dump_err():
    with open(_ERR, "w", encoding="utf-8") as fh:
        fh.write(_tb.format_exc())


def say(msg):
    idaapi.msg("[range_test] %s\n" % msg)


SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
os.makedirs(LOG_DIR, exist_ok=True)
OUT = os.path.join(LOG_DIR, "func_range_test.json")

cur = idc.get_idb_path() or ""
if "PAL3.exe.i64" in cur and "/tmp/" not in cur:
    say("ABORT: refusing to run on the production IDB: %s" % cur)
    say("usage: cp original/PAL3.exe.i64 /tmp/range_test.i64, then pass the /tmp path")
    idc.qexit(2)

results = {"idb": cur, "tests": []}

import traceback as _tb
_ERR = os.path.join(LOG_DIR, "func_range_test_error.txt")


def rec(_tname, **kw):
    kw["test"] = _tname
    results["tests"].append(kw)
    say("%-36s %s" % (_tname, {k: v for k, v in kw.items() if k != "test"}))


def fend(ea):
    f = ida_funcs.get_func(ea)
    return f.end_ea if f else None


def _main():
    # ---- 选目标：大函数 + 后面紧跟另一个函数 ----
  cands = []
  for ea in idautils.Functions():
      f = ida_funcs.get_func(ea)
      if not f:
          continue
      nxt = ida_funcs.get_next_func(f.start_ea)
      if nxt is not None and (f.end_ea - f.start_ea) > 0x400:
          cands.append((f.end_ea - f.start_ea, f.start_ea, f.end_ea, nxt.start_ea))
  cands.sort(reverse=True)

  if not cands:
      rec("select_target", ok=False, why="no large function with a following function")
      with open(OUT, "w", encoding="utf-8") as fh:
          json.dump(results, fh, ensure_ascii=False, indent=1)
      idc.qexit(1)

  size, start, end, next_start = cands[0]
  rec("select_target", ok=True, start=hex(start), end=hex(end), size=size,
      next_start=hex(next_start), name=idc.get_func_name(start))


  def align_down(ea):
      """取 <= ea 的最近指令头部（截断点必须在指令边界）。"""
      h = idc.prev_head(ea)
      return h if h and h > start else ea


  # ---- 测试 1：截断到中点，观察是否成功，然后复原 ----
  mid = align_down(start + size // 2)
  ok1 = bool(ida_funcs.set_func_end(start, mid))
  rec("T1_set_func_end_truncate", ok=ok1, want=hex(mid), got=hex(fend(start) or 0))
  ok_r = bool(ida_funcs.set_func_end(start, end))
  rec("T1_restore", ok=ok_r, got=hex(fend(start) or 0), want=hex(end))

  # ---- 测试 2：延长到"下一个函数起点之后"，看是否被拒（重叠约束） ----
  probe = next_start + 0x20
  ok2 = bool(ida_funcs.set_func_end(start, probe))
  got2 = fend(start)
  rec("T2_extend_past_next_func", ok=ok2, want=hex(probe), got=hex(got2 or 0),
      note="ok=False -> overlap rejected; ok=True -> would swallow the next function")
  if ok2 and got2 and got2 != end:
      ida_funcs.set_func_end(start, end)

  # ---- 测试 3a：不截断父函数，直接在体内 add_func ----
  m2 = align_down(start + size // 3)
  ok3a = bool(ida_funcs.add_func(m2, m2 + 0x40))
  rec("T3a_add_func_inside_no_truncate", ok=ok3a, at=hex(m2),
      note="False -> must truncate or del_func first")
  if ok3a:
      ida_funcs.del_func(m2)

  # ---- 测试 3b：先截断，再 add_func（预期正确顺序） ----
  ida_funcs.set_func_end(start, m2)
  ok3b = bool(ida_funcs.add_func(m2, m2 + 0x40))
  rec("T3b_add_func_after_truncate", ok=ok3b, at=hex(m2),
      note="True -> correct order is set_func_end -> add_func")
  if ok3b:
      ida_funcs.del_func(m2)
  ida_funcs.set_func_end(start, end)
  rec("final_restore", got=hex(fend(start) or 0), want=hex(end))

  with open(OUT, "w", encoding="utf-8") as fh:
      json.dump(results, fh, ensure_ascii=False, indent=1)
  say("done -> %s" % OUT)


try:
    _main()
except Exception:
    _dump_err()
    say("EXCEPTION -> see func_range_test_error.txt")
    idc.qexit(3)
idc.qexit(0)