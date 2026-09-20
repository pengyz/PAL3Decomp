#!/usr/bin/env python3
"""只读：从 original/PAL3.exe.asm 抽 ??_L/??_M 的元素尺寸证据（Spike 用）。

**本工具除显式 `--json <path>` 外不写任何文件**；不读注解、不改注解、不接硬门禁。

已确认的实参语义（本任务输入约束，勿再论证）：
- `??_L`（eh vector constructor iterator）五元组 `(ptr, size, count, ctor, dtor)`；
- `??_M`（eh vector destructor iterator）四元组 `(ptr, size, count, dtor)`，**无 ctor**
  ⇒ 不得与 `??_L` 共用五元组描述。

x86 cdecl 从右往左压栈，故 asm 里的**源序**是
`push dtor; push ctor; push count; push size; push ptr`（`??_L`）与
`push dtor; push count; push size; push ptr`（`??_M`）
⇒ **最后一个 push 才是第一个实参 `ptr`**，抽参必须把窗口反向映射（见 `_tuple_from_pushes`）。

字段类型（任务 3/4 依赖）：
- `size`/`count`: `int|None` —— 只接受 `push 2200h` 这类**字面量**；寄存器/内存操作数等
  非字面量一律 `None`（**绝不**漏出 str）；
- `ptr`/`ctor`/`dtor`: `str|None` —— 归一化地址串 `'0x…'`（`push offset sub_XXXX` 与
  `push 411900h` 字面量统一为该形态）；寄存器/局部符号（如 `eax`、`[esi+4]` 的中间指针）
  原样回填字符串 —— 属**已知漏采**，只能作 candidate/signal，不得当 A 级证据；
  `??_M` 无 ctor ⇒ `ctor is None`；
- 抽取不全的条目只有 `site/kind/incomplete/line`，**没有** `size/count/…` 键。

上述契约由站点构造出口的 `_norm_int`/`_norm_addr` 统一保证（下游 `a0.lower()` / 算术不会崩）。
"""
import argparse
import datetime
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM_PATH = os.path.join(ROOT, 'original', 'PAL3.exe.asm')

PARSER_VERSION = 1

# 抽取前的注释剥离：本仓 asm 有 16601 行 push 带 `; comment` 尾注，
# 不剥离则 `\s*$` 锚点全部失配 ⇒ 每个站点都会被误判为 incomplete。
#
# 操作数用 `.+?`（剥离注释后的整段）而非 `\w+`：`??_L/??_M` 的 dtor 实参可能是
# **名字改编符号**（如 `??1stdiobuf@@UAE@XZ_2`、`__TI1?AV_Exception@@`）或内存操作数
# （`[ebp+arg_0]`、`dword ptr [esp+4]`），`\w+` 匹配不到 `@`/`?`/`[` ⇒ 该 push 被静默丢弃
# ⇒ 站点被误判 incomplete（实测：不放宽则 466 站点里有 6 个假 incomplete；
# 放宽后 ehl=133 / ehm=333 / 不完整=0，与计划任务 3 的成功判据 ① 一致）。
_PUSH = re.compile(r'^\s*push\s+(?:offset\s+)?(.+?)\s*$')
_CALL_L = re.compile(r'^\s*call\s+(\?\?_L@\S+)')
_CALL_M = re.compile(r'^\s*call\s+(\?\?_M@\S+)')
_PROC = re.compile(r'^([A-Za-z_]\w*)\s+proc near')
# SEH unwind funclet 的开头标记本身是**注释行**
# （`; START OF FUNCTION CHUNK FOR sub_XXXX`）：这类 chunk 属于 sub_XXXX，
# 但它们**没有自己的 `proc near`** ⇒ 不处理就会被挂到文件中最后一个 proc 名下。
# ⚠️ 必须在**剥尾注之前**的 raw_line 上匹配：该行以 `;` 起头，剥注释后只剩空串 ⇒ 永不命中。
_CHUNK = re.compile(r'^;\s*START OF FUNCTION CHUNK FOR\s+(\S+)')
_HEX_LIT = re.compile(r'^[0-9A-F][0-9A-Fa-f]*h$')
_SYM_ADDR = re.compile(r'^([A-Za-z]\w*_)([0-9A-Fa-f]{4,})$')


def _norm_int(v):
    """size/count 对外契约：`int|None`。非 int（寄存器/内存操作数/改编符号）⇒ `None`。

    修复前 `push ecx` 这类操作数会让 `count` 漏出 str（实测 2/466 行），违反 docstring 契约。
    """
    return v if isinstance(v, int) else None


def _norm_addr(v):
    """ptr/ctor/dtor 对外契约：`str|None`。int（`push 411900h` 字面量）⇒ `'0x%X'`。

    修复前字面量会以 int 漏出（本 asm 上 0/466，但下游 `a0.lower()` 会 AttributeError
    —— 属"上膛的枪"）。
    """
    if v is None:
        return None
    if isinstance(v, int):
        return '0x%X' % v
    return v


def _val(tok):
    """把 push 操作数归一化：字面量 -> int；`sub_XXXX`/`unk_XXXX` -> '0xXXXX'；其余原样。

    "其余原样" 覆盖寄存器（`eax`）、内存操作数（`[ebp+arg_0]`）与名字改编符号
    （`??1stdiobuf@@UAE@XZ_2`）——它们**不是地址**，属已知漏采，只能作 candidate/signal。

    ⚠️ 本函数返回值**尚未**满足对外契约（字面量是 int）；对外 `size/count:int|None`、
    `ptr/ctor/dtor:str|None` 由站点构造出口的 `_norm_int`/`_norm_addr` 统一保证。
    """
    tok = tok.strip()
    if _HEX_LIT.match(tok):                      # 2200h / 0A4h -> int（size/count 用）
        return int(tok[:-1], 16)
    if re.fullmatch(r'\d+', tok):                # 5 / 64 -> int
        return int(tok)
    m = _SYM_ADDR.match(tok)                     # sub_411900 / unk_C05F60 -> '0x411900'
    if m:
        return '0x%X' % int(m.group(2), 16)
    return tok                                   # 寄存器/内存操作数/改编符号（非地址）


def _tuple_from_pushes(pushes, kind):
    """把 push 窗口反向映射成实参元组；不足则返回 None。"""
    need = 5 if kind == 'ehl' else 4
    if len(pushes) < need:
        return None
    w = pushes[-need:]                           # 源序，最后一个是 ptr
    ptr, size, count = w[-1], w[-2], w[-3]
    if kind == 'ehl':
        return ptr, size, count, w[-4], w[-5]    # ctor, dtor
    return ptr, size, count, None, w[-4]         # 无 ctor；w[-4] 即 dtor


def parse_sites(asm_text):
    """按函数边界抽 ??_L/??_M 站点。

    宿主 `site` 的判定边界（**实测**，不再声称未实现的 `endp` 处理）：
    1. `NAME proc near` ⇒ 宿主 NAME；
    2. `; START OF FUNCTION CHUNK FOR NAME` ⇒ 宿主 NAME —— SEH unwind funclet
       属于 NAME 但**没有自己的 `proc near`**，不显式处理就会被挂到文件中最后一个
       proc 名下（修复前实测 213/466 条全被错挂到 `sub_55D67E`）；
    3. 进入新边界时清空 push 窗口（`buf = []`），避免跨函数串参。
    """
    sites, cur, buf = [], None, []
    for i, raw_line in enumerate(asm_text.split('\n'), 1):
        line = raw_line.split(';', 1)[0]         # 剥离尾注后再匹配
        c = _CHUNK.match(raw_line)               # funclet chunk：host 取自 chunk 头（raw_line！）
        if c:
            cur, buf = c.group(1), []
            continue
        m = _PROC.match(raw_line)
        if m:
            cur, buf = m.group(1), []
            continue
        if _CALL_L.match(line) or _CALL_M.match(line):
            kind = 'ehl' if _CALL_L.match(line) else 'ehm'
            vals = _tuple_from_pushes(buf, kind)
            if vals is None:
                sites.append({'site': cur, 'kind': kind, 'incomplete': True, 'line': i})
                buf = []
                continue
            ptr, size, count, ctor, dtor = vals
            # 站点构造出口统一归一化 ⇒ `size/count:int|None`、`ptr/ctor/dtor:str|None`
            # （下游 T4 的 `a0.lower()` 与 size 算术不会因 int/str 混型而崩）。
            sites.append({'site': cur, 'kind': kind,
                          'ptr': _norm_addr(ptr), 'size': _norm_int(size),
                          'count': _norm_int(count), 'ctor': _norm_addr(ctor),
                          'dtor': _norm_addr(dtor), 'line': i})
            buf = []
            continue
        p = _PUSH.match(line)
        if p:
            buf.append(_val(p.group(1)))
    return sites


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    # 护栏（防重演已发生 2 起的 `--help` 覆盖产物事故）：任何以 `-` 开头且不是已知开关的
    # 参数 ⇒ 打印提示并返回 0，且**不执行任何操作**。
    known = {'--asm', '--json'}
    unknown = [a for a in argv if a.startswith('-') and a.split('=')[0] not in known]
    if unknown:
        print('[audit_element_sizes] 未知开关 %r ⇒ 不执行任何操作' % unknown)
        print('用法: --asm <path> [--json <path>]')
        return 0
    ap = argparse.ArgumentParser()
    ap.add_argument('--asm', default=ASM_PATH)
    ap.add_argument('--json', default=None)
    args = ap.parse_args(argv)
    if not os.path.exists(args.asm):
        print('[ERROR] 缺 asm: %s（gitignored，需本机存在）' % args.asm, file=sys.stderr)
        return 2
    with open(args.asm, encoding='utf-8', errors='replace') as fh:
        sites = parse_sites(fh.read())
    inc = [s for s in sites if s.get('incomplete')]
    print('站点 %d（完整 %d / 不完整 %d）'
          % (len(sites), len(sites) - len(inc), len(inc)))
    if args.json:
        # 产物记录输入参数与来源（算法版本/输入路径/生成时刻）——全局约束要求。
        payload = {'asm': args.asm,
                   'generated_at': datetime.datetime.now(datetime.timezone.utc)
                                                  .strftime('%Y-%m-%dT%H:%M:%SZ'),
                   'parser_version': PARSER_VERSION,
                   'sites': sites}
        with open(args.json, 'w', encoding='utf-8') as fh:
            json.dump(payload, fh, indent=1)
        print('-> %s' % args.json)
    return 0


if __name__ == '__main__':
    sys.exit(main())