"""扫描"归属误判"候选：**方法 M 声明属于类 C，但其 `this->member` 被当作
另一个类的对象使用**（`CalcSpeed` / `ProcessAllCmds` 那一型）。

## 判据（已由两个真阳性验证）

对 decomp 里每个方法 M（声明为 `C::M`），找形态：
    `X::Y( (X *)this->m , ... )` 或  `X::Y( &this->m , ... )`
其中：
  · `m` 是 C 的成员，偏移 `off(m)`；
  · `X != 声明类型(m)`  ⇒ **类型不符**（第一个过滤）；
  · 再检查 `X::Y`（及其同族）访问的最小偏移需求是否 `> binary_size(声明类型(m))`
    ⇒ **物理不可能** ⇒ **误归属**（第二个过滤，需展开被调函数）。

## 为什么要两段
`X != 声明类型` 单独不够（有大量**正确**的跨类调用，例如 `m_pAttackSequen`
（CCBAttackSequen*）传给 `CCBSystem::*` 是合法的：它是派生/包含关系）。
**真正不可辩驳的是"物理放不下"**：被调函数读到声明类型尺寸之外。

## 用法（只读，不改任何东西）
    python3 tools/scan_misattribution.py [--limit N] [--only CLASS]
输出：候选清单（按置信度），并标注"是否物理不可能"。
"""
import argparse
import glob
import json
import os
import re
import struct
import subprocess
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANNO = os.path.join(ROOT, 'data', 'annotations', 'structs')
DECOMP = os.path.join(ROOT, 'asm', 'pal3', 'decomp')
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')


def load_structs():
    """name -> {'size': int|None, 'members': {mname: (off, type)}, 'methods': {va: name}}"""
    out = {}
    for p in glob.glob(os.path.join(ANNO, '*.json')):
        try:
            d = json.load(open(p, encoding='utf-8'))
        except Exception:
            continue
        n = d.get('name')
        if not n:
            continue
        offs = {}
        for k, m in (d.get('known_members') or {}).items():
            try:
                off = int(k, 16) if k.lower().startswith('0x') or not k.isdigit() else int(k)
            except Exception:
                continue
            offs[(m or {}).get('name')] = (off, str((m or {}).get('type') or ''))
        meths = {}
        for k, m in (d.get('methods') or {}).items():
            meths[k.upper()] = (m or {}).get('name')
        out[n] = {'size': d.get('binary_size'), 'members': offs, 'methods': meths}
    return out


def load_decomp():
    """VA(hex upper, no 0x) -> (name, code)"""
    out = {}
    for p in glob.glob(os.path.join(DECOMP, '*.json')):
        try:
            d = json.load(open(p, encoding='utf-8'))
        except Exception:
            continue
        a = (d.get('address') or '').upper().replace('0X', '')
        if a:
            out[a] = ((d.get('name') or ''), (d.get('decompiled_c') or ''))
    return out


# ---- 被调函数的"最小访问需求" ----------------------------------------------
_REQ_CACHE = {}


def min_required_span(va_hex):
    """反汇编 va 起的函数，返回它访问的 `this` 最大偏移 + 4（近似"最小所需尺寸"）。

    只要函数内出现 `[reg + disp]` 且 reg 是入口的 this 寄存器（ecx：__thiscall），
    或 `[reg + idx*scale + disp]`（数组访问），我们取 disp 作为所需下界。
    这是**下界**（保守）：真实需求只会更大。
    """
    va_hex = va_hex.upper().lstrip('0X')
    if va_hex in _REQ_CACHE:
        return _REQ_CACHE[va_hex]
    try:
        va = int(va_hex, 16)
    except Exception:
        _REQ_CACHE[va_hex] = None
        return None
    end = va + 0x400
    try:
        out = subprocess.run(['objdump', '-d', '--start-address=%d' % va,
                              '--stop-address=%d' % end, EXE],
                             capture_output=True, text=True, timeout=30).stdout
    except Exception:
        _REQ_CACHE[va_hex] = None
        return None
    # ⚠️ 只统计**入口 this 寄存器**的访问。
    # __thiscall 的 this 在 `%ecx` 入口。但函数体内 `%ecx` 会被**反复复用**
    # （如 `mov ecx,[esi+8]` 后 `ecx` 已是另一个对象）。
    # 若把"任何 `[ecx+disp]`"都算进来，会得到 514M 这类荒谬需求 ⇒ **大量假阳性**
    # （实测：把 `CCBAttackSequen::ProcessQueue` 这种**正确归属**也标成"物理不可能"）。
    # ⇒ 采用保守规则：**只认函数最前面的若干条指令**里对 `%ecx` 的访问
    #   （那时 `%ecx` 仍是入口 this），且**不接受被 `mov %ecx,<other>` 覆盖之后**的访问。
    req = 0
    this_reg = '%ecx'          # __thiscall 入口
    live = True                # %ecx 是否仍是入口 this
    n = 0
    for line in out.splitlines():
        if not re.match(r'\s+[0-9a-f]+:', line):
            continue
        n += 1
        body = line.split(':', 1)[1] if ':' in line else line
        # 覆盖检测：`mov <dst>,%ecx` 把 this 复制出去不改 %ecx；
        # 真正危险的是 `mov %ecx,<src>` 或 `pop %ecx` —— 之后 %ecx 不再是原 this
        if re.search(r'\bmov\s+' + re.escape(this_reg) + r'\s*,', body) or \
           re.search(r'\bpop\s+' + re.escape(this_reg), body) or \
           re.search(r'\b(xor|lea|add|sub)\s+' + re.escape(this_reg) + r'\s*,', body):
            live = False
        if live:
            m = re.search(r'0x([0-9a-f]+)\(' + re.escape(this_reg) +
                          r'(?:,([0-9a-f]+),([0-9a-f]))?\)', body)
            if m:
                req = max(req, int(m.group(1), 16))
    _REQ_CACHE[va_hex] = (req + 4) if req else None
    return _REQ_CACHE[va_hex]


_TY = re.compile(r'([A-Za-z_]\w*)')


def base_type(t):
    """`CCBControl *` -> `CCBControl`"""
    t = (t or '').replace('*', ' ')
    m = _TY.search(t)
    return m.group(1) if m else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--limit', type=int, default=40)
    ap.add_argument('--only', default=None, help='只扫这个类的方法')
    args = ap.parse_args()

    S = load_structs()
    D = load_decomp()
    print("  已加载 structs=%d  decomp=%d" % (len(S), len(D)))

    # 成员名 -> 声明类型（每个类各一份）
    cand = []
    pat = re.compile(
        r'(\w+)::(\w+)\(\s*(?:\(\s*(\w+)\s*\*\s*\)\s*)?'
        r'(?:&?this->(m_\w+))')
    for va, (nm, code) in D.items():
        if '::' not in nm:
            continue
        cls = nm.split('::')[0]
        if args.only and cls != args.only:
            continue
        if not code:
            continue
        for mm in pat.finditer(code):
            called_cls, called_m, cast_cls, mem = mm.groups()
            if not mem:
                continue
            info = S.get(cls, {}).get('members', {}).get(mem)
            if not info:
                continue
            off, mtype = info
            bt = base_type(mtype)
            tgt = cast_cls or called_cls
            if not bt or not tgt or bt == tgt:
                continue   # 类型相同 ⇒ 不是"类型不符"型
            sz = S.get(bt, {}).get('size')
            # 被调方法在 X 里的地址
            callee_va = None
            for k, v in (S.get(tgt, {}).get('methods') or {}).items():
                if v == called_m:
                    callee_va = k
                    break
            need = min_required_span(callee_va) if callee_va else None
            impossible = (sz is not None and need is not None and need > sz)
            cand.append({
                'method_va': va, 'method': nm, 'member': mem, 'member_off': off,
                'member_type': bt, 'member_size': sz,
                'called_class': tgt, 'called_method': called_m,
                'callee_va': callee_va, 'callee_min_need': need,
                'impossible': impossible,
            })

    cand.sort(key=lambda c: (not c['impossible'], c['method']))
    n_imp = sum(1 for c in cand if c['impossible'])
    print("  候选总数 %d；其中 **物理不可能 %d**" % (len(cand), n_imp))
    print()
    print("  === 物理不可能（高置信，建议迁移）===")
    seen = set()
    for c in cand[:args.limit]:
        if not c['impossible']:
            continue
        key = (c['method_va'], c['member'], c['called_method'])
        if key in seen:
            continue
        seen.add(key)
        print("    %-12s %-34s this->%-16s(%s=%sB, +0x%X) 当 %s 用，%s 需>=%sB"
              % (c['method_va'], c['method'][:34], c['member'][:16], c['member_type'],
                 c['member_size'], c['member_off'], c['called_class'],
                 c['called_method'], c['callee_min_need']))
    json.dump(cand, open(os.path.join(ROOT, 'data', 'status',
                                      '_scan_misattribution.json'), 'w',
                         encoding='utf-8'), ensure_ascii=False, indent=1)
    print()
    print("  完整清单 -> data/status/_scan_misattribution.json")


if __name__ == '__main__':
    main()