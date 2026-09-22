#!/usr/bin/env python3
"""**函数归属审计**（只读、证据分级、人工确认）—— 用"成员访问集合的唯一相容性"判归属。

## ⚠️ 状态：**判据已 TDD 验证，但证据提取器尚不可用于下结论**（实验性）
纯判据 `verdict_bounded` 有 20 项测试覆盖 ✓；但 `accessed_offsets` 的 **naive this-tracking 会过度归属** ✗：
实测 `SceneMgr::Create` 同时访问了 `this`(SceneMgr) 与**另一个对象**(`CEffMgr`，其字段 0xA91C… ≈ 0x0A930)
⇒ 把别人的字段算成自己的成员 ⇒ 得出"唯一相容 CEffMgr"这种**问题问错了**的结论 ✗✗
⇒ **要用于决策，必须先实现"按基对象分离"的寄存器来源分析（真 provenance）** ✓
在那之前：**只把本工具用于"contradiction"告警的线索，不得据其改归属** ✗

## 判据（本会话确立；可证性清晰）

取函数体内 `[this+off]` 的**成员访问集合**，与各候选类的成员偏移表比对：

| 情形 | 结论 | 含义 |
|---|---|---|
| **恰好一个类相容**（其成员表 ⊇ 访问集合）| `unique` | **归属可证** ✓ |
| **≥2 个类相容** | `ambiguous` | **不可证** ⇒ 只报警 ✓（多类布局重叠时常见）|
| **没有任何类相容** | `contradiction` | **最强告警**：归属错 或 成员表错 ✓ |
| **访问集合为空** | `no-evidence` | 不得下任何结论 ✓（未观测 ≠ 不存在）|

## 为什么需要它
仓规明令：**禁止仅凭 signature 里的 `this` 修正函数归属** —— 必须有"函数内访问的成员在目标类中存在、
且不在原类中存在"的证据 ✓。本工具把这条**机械化**：它不是看签名，而是看**成员集合的唯一相容性** ✓

## `this` 寄存器来源追踪（把本会话的 `mov esi,ecx ⇒ ESI ≡ this` 规则机械化）
入口处 `ECX` = `this`（`__thiscall`）；函数序言里任何 `mov R, ecx`（或 `mov R, <已知 this 寄存器>`）
⇒ `R` 也视为 `this` ✓；之后 `[R+disp]` 即成员访问 ✓

用法::

    python3 tools/audit_attribution.py --class SceneMgr      # 审该类方法
    python3 tools/audit_attribution.py --func 0x423500       # 审单个函数
    python3 tools/audit_attribution.py --class SceneMgr --json
只读、只报警、**不自动改归属** ✓
"""
import argparse
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, '/tmp')

import audit_type_layout as A  # noqa: E402  （复用**唯一**成员解析入口 ✓）

DISP_RX = re.compile(r'\[\s*(?!esp|ebp)([a-z][a-z0-9]*)\s*\+\s*(0x[0-9a-f]+|[0-9a-f]+h)\s*\]', re.I)
MOV_RX = re.compile(r'^\s*mov\s+([a-z][a-z0-9]*)\s*,\s*([a-z][a-z0-9]*)\s*$', re.I)
DISP8_RX = re.compile(r'\[\s*(?!esp|ebp)([a-z][a-z0-9]*)\s*\+\s*([0-9a-f]+)\s*\]', re.I)


# ==================== 纯核心（单测覆盖） ====================

def verdict(accessed, candidates):
    """→ ('unique', cls) | ('ambiguous', [cls…]) | ('contradiction', []) | ('no-evidence', None)

    `accessed`: set[int] 该函数访问的成员偏移；`candidates`: {cls: set[int]} 各候选类的成员偏移表。
    """
    if not accessed or not candidates:
        return ('no-evidence', None)
    ok = [c for c, offs in candidates.items() if accessed <= set(offs)]
    if len(ok) == 1:
        return ('unique', ok[0])
    if len(ok) > 1:
        return ('ambiguous', sorted(ok))
    return ('contradiction', [])


MATCH_MIN = 0.6      # 匹配率下限：低于此值说明多半落在 gap 里 ⇒ 不足以下结论 ✓
MARGIN_MIN = 0.2     # 领先第二名的幅度下限：太小 ⇒ 不可区分 ⇒ ambiguous ✓


def verdict_bounded(accessed, classes):
    """精化判据（尺寸边界 + 匹配率/领先幅度）→ 同 `verdict` 的四态

    `classes`: {cls: {'members': set[int], 'size': int}}

    **为什么不能用朴素包含判据**（2026-09-22 实测）：大类的成员表**稀疏**
    （SceneMgr 169 个成员 vs 数万字节），落在对象范围内但未声明的偏移应视为**相容**（gap/未知）；
    而小类只要"凑上"几个偏移就可能唯一 ⇒ 判别力必须来自 **① 尺寸边界 ② 匹配率 ③ 领先幅度** ✓
    （实测教训：朴素判据把 `SceneMgr::Create` 判成"唯一相容 CEffMgr" ✗）
    """
    if not accessed or not classes:
        return ('no-evidence', None)
    mx = max(accessed)
    cands = [c for c, d in classes.items() if mx < int(d.get('size') or 0)]
    if not cands:
        return ('contradiction', [])
    if len(cands) == 1:
        return ('unique', cands[0])
    rates = {}
    for c in cands:
        mem = set(classes[c].get('members') or ())
        rates[c] = len(accessed & mem) / float(len(accessed))
    order = sorted(rates.items(), key=lambda kv: (-kv[1], kv[0]))
    best, brate = order[0]
    second = order[1][1] if len(order) > 1 else 0.0
    if brate >= MATCH_MIN and (brate - second) >= MARGIN_MIN:
        return ('unique', best)
    return ('ambiguous', sorted(cands))


def render_line(func, cls, v):
    """人读一行 ✓"""
    kind, who = v
    if kind == 'unique':
        return '%-40s 现归 %-18s unique ⇒ 归属可证（唯一相容 %s）' % (func[:40], cls, who)
    if kind == 'ambiguous':
        return '%-40s 现归 %-18s ambiguous ⇒ 不可证（相容候选: %s）' % (func[:40], cls, ', '.join(who))
    if kind == 'contradiction':
        return '%-40s 现归 %-18s **contradiction** ⇒ 归属错或成员表错（无类相容）✗' % (func[:40], cls)
    return '%-40s 现归 %-18s no-evidence ⇒ 不做结论' % (func[:40], cls)


def candidate_offsets():
    """→ {cls: set(offset)}：从**生成头**读成员偏移（= 注解偏移 ✓）"""
    out = {}
    for cls, (hdr, mem) in A.load_annotation_members().items():
        offs = {int(o) for _, o in mem}
        if offs:
            out[cls] = offs
    return out


# ==================== `this` 来源追踪 + 访问集合提取 ====================

def _disp_val(raw):
    raw = raw.strip()
    try:
        return int(raw[:-1], 16) if raw.lower().endswith('h') else int(raw, 0)
    except Exception:
        return None


# 镜像数据段起始 VA（实测本 exe 的全局在 0x56F9B4 / 0xC04390 / 0xC057B8 一带）⇒
# disp ≥ 本阈值 ⇒ 不是"成员偏移"而是**绝对地址访问**（全局对象）⇒ 必须排除 ✓
# 依据：本仓所有类的成员偏移 < 0x40000（最大者 RoleStatePanel +0x2AFD8 ✓）
ABS_ADDR_MIN = 0x400000


def accessed_offsets(lines):
    """从反汇编行提取**经 this 寄存器**的成员访问偏移集合 ✓

    `lines`: [{'addr':…, 'instruction':…}]（顺序执行）
    """
    this_regs = {'ecx'}          # __thiscall 入口：ECX = this ✓
    offs = set()
    for l in lines:
        ins = (l.get('instruction') or '')
        m = MOV_RX.match(ins)
        if m:
            dst, src = m.group(1).lower(), m.group(2).lower()
            if src in this_regs:                     # mov R, ecx  ⇒ R ≡ this ✓
                this_regs.add(dst)
                continue
            if dst in this_regs:                     # 被覆盖 ⇒ 不再是 this
                this_regs.discard(dst)
            continue
        d = DISP_RX.search(ins) or DISP8_RX.search(ins)
        if d and d.group(1).lower() in this_regs:
            v = _disp_val(d.group(2))
            # ⚠️ 排除**绝对地址访问**（全局对象 g_X.member ⇒ disp = 全局地址+偏移 ✗）
            if v is not None and v < ABS_ADDR_MIN:
                offs.add(v)
    return offs


# ==================== MCP 驱动 ====================

def mcp_connect(session=None):
    try:
        import mcp  # noqa
        mcp.init()
    except Exception:
        return None
    sid = session
    if not sid:
        try:
            r = mcp.call('idb_list', {})
            d = json.loads(r[0]['result']['content'][0]['text'])
            items = d if isinstance(d, list) else (d.get('sessions') or [])
            if items:
                sid = items[0].get('session_id') or items[0].get('id')
        except Exception:
            return None
    if not sid:
        return None

    def call(tool, args):
        a = dict(args); a['database'] = sid
        r = mcp.call(tool, a)
        try:
            return r[0]['result']['content'][0]['text']
        except Exception:
            return json.dumps(r, ensure_ascii=False)[:200]
    return call


def func_insns(call, addr, limit=4000):
    """取函数反汇编（分行）✓"""
    try:
        txt = call('disasm', {'addr': addr if isinstance(addr, str) else '0x%X' % addr,
                              'max_instructions': limit})
        return json.loads(txt)['asm']['lines']
    except Exception:
        return []


def class_methods(cls):
    """→ [(addr, name)]（来自 IDA 导出的 methods ✓）"""
    try:
        IS = json.load(open(os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json'), encoding='utf-8'))
    except Exception:
        return []
    m = (IS.get(cls) or {}).get('methods') or {}
    out = []
    for a, v in m.items():
        nm = v.get('name') if isinstance(v, dict) else str(v)
        out.append((a, nm))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--class', dest='cls')
    ap.add_argument('--func')
    ap.add_argument('--session')
    ap.add_argument('--json', action='store_true')
    ap.add_argument('--limit', type=int, default=40)
    a = ap.parse_args()

    cands = candidate_offsets()
    classes = {}
    for c, offs in cands.items():
        try:
            sz = A.load_annotation_members()[c][0]
            import re as _re
            txt = open(sz, encoding='utf-8', errors='replace').read()
            m = _re.search(r'// total size: 0x([0-9A-F]+)', txt)
            size = int(m.group(1), 16) if m else (max(offs) + 4)
        except Exception:
            size = max(offs) + 4
        classes[c] = {'members': offs, 'size': size}
    print('=' * 92)
    print('函数归属审计（成员集合唯一相容性）· 候选类 %d · 判据: unique 可证 / ambiguous 不可证 / contradiction 最强告警'
          % len(cands))
    print('=' * 92)

    call = mcp_connect(a.session)
    if not call:
        print('MCP 不可用 ⇒ 只打印纯逻辑自检（见 tests/test_audit_attribution.py）')
        return 2

    if a.func:
        targets = [(a.func, a.cls or '?')]
    else:
        targets = [(ad, nm) for ad, nm in class_methods(a.cls)][:a.limit] if a.cls else []

    rows = []
    for addr, name in targets:
        lines = func_insns(call, addr)
        offs = accessed_offsets(lines)
        # 候选集：现归类 + 其它类（多类比对）✓
        v = verdict_bounded(offs, classes)
        rows.append({'func': name, 'addr': addr, 'class': a.cls,
                     'n_offsets': len(offs), 'verdict': v[0],
                     'who': v[1] if v[1] else None})
        print('  ' + render_line('%s@%s' % (name, addr), a.cls or '?', v))
    n_c = sum(1 for r in rows if r['verdict'] == 'contradiction')
    n_u = sum(1 for r in rows if r['verdict'] == 'unique')
    n_a = sum(1 for r in rows if r['verdict'] == 'ambiguous')
    n_n = sum(1 for r in rows if r['verdict'] == 'no-evidence')
    print('=' * 92)
    print('小结: unique（可证）%d · ambiguous（不可证）%d · **contradiction（告警）%d** · no-evidence %d'
          % (n_u, n_a, n_c, n_n))
    print('⇒ contradiction ⇒ 人工介入：查归属错还是成员表错 ✓')
    if a.json:
        print(json.dumps(rows, ensure_ascii=False, indent=1))
    return 1 if n_c else 0


if __name__ == '__main__':
    sys.exit(main())