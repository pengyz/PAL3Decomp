#!/usr/bin/env python3
"""**函数归属的"可证"证据审计**（只读、只报警）—— 与实验性的成员集合判据不同，这里用的是**决定性证据**。

## 三层证据（都是可证的，不做推断）
1. **vtable 槽位**：函数 F 出现在类 C 的 vtable 里 ⇒ 槽的 `from` 给出**声明/继承来源类** ✓
   （`from` 为空 ⇒ 归 owner C ✓；同一 F 出现在多个类的 vtable 里 ⇒ **保留全部**证据 ✓）
2. **祖先关系**：方法当前归 D，证据类 B 是 D 的**祖先** ⇒ `consistent` ✓；
   **无祖先关系** ⇒ `contradiction`（可证告警 ✓）
3. **ctor/dtor 的 vptr 存储**：函数体内 `mov [this], <C 的 vtable>` ⇒ 该函数属于 C ✓

## 为什么用这三层（2026-09-22 论证结论）
寄存器级 provenance 的精度被**内联**封顶（实测 IDB 有 21 个 `_inline_*` 类型 ⇒
函数体内合法含别的类的成员访问 ⇒ "唯一相容"结论可能按构造就错 ✗，已有反例）。
而 vtable/ctor 证据**便宜且决定性**（464 个函数地址有 vtable 槽位 ✓）⇒ **优先生效** ✓

用法::

    python3 tools/audit_attribution_evidence.py                 # 对账全部（本地数据，秒级）
    python3 tools/audit_attribution_evidence.py --json
    python3 tools/audit_attribution_evidence.py --ctor --session <id>   # 追加 ctor vptr 证据（需 MCP）
只读、只报警、**不自动改归属** ✓
"""
import argparse
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, '/tmp')

IDA_STRUCTS = os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json')

MOV_R_RX = re.compile(r'^\s*mov\s+([a-z][a-z0-9]*)\s*,\s*([a-z][a-z0-9]*)\s*$', re.I)
VPTR_STORE_RX = re.compile(
    r'^\s*mov\s+(?:dword\s+ptr\s+)?\[\s*([a-z][a-z0-9]*)\s*\]\s*,\s*offset\s+([^\s;]+)', re.I)


def load_ida():
    return json.load(open(IDA_STRUCTS, encoding='utf-8'))


# ==================== 纯逻辑（单测覆盖） ====================

def ancestors(cls, ida):
    """→ {cls} ∪ 其全部祖先（容错：未知类只返回自身；防环 ✓）"""
    out, stack = set(), [cls]
    while stack:
        c = stack.pop()
        if c in out:
            continue
        out.add(c)
        for b in ((ida.get(c) or {}).get('bases') or []):
            # ⚠️ 2026-09-22 实测：IDB 导出的 `bases` 是 **dict 列表**（[{'name':'UIWnd','offset':0}]）
            # ⇒ 只认字符串会让**祖先集恒为空** ✗ ⇒ 对账退化成 `src == current` ✗
            nm = b.get('name') if isinstance(b, dict) else b
            if isinstance(nm, str) and nm not in out:
                stack.append(nm)
    return out


def vtable_evidence(ida):
    """→ {func_addr:int: [(owner_cls, evidence_cls), …]}

    槽的 `from`（继承来源）优先；为空则归 owner ✓；多类主张**全部保留** ✓
    """
    out = {}
    for cls, v in (ida or {}).items():
        for vt in ((v or {}).get('vtables') or []):
            for s in (vt.get('slots') or []):
                a = s.get('addr')
                if not a:
                    continue
                try:
                    ai = int(str(a), 16)
                except Exception:
                    continue
                src = s.get('from')
                if not src:
                    src = cls
                out.setdefault(ai, []).append((cls, src))
    return out


def vtable_addr_to_class(ida):
    """→ {vtable_addr_str: cls}"""
    out = {}
    for cls, v in (ida or {}).items():
        for vt in ((v or {}).get('vtables') or []):
            a = vt.get('addr')
            if a:
                out[str(a)] = cls
    return out


def current_attribution(ida):
    """当前归属（来自 `methods` 表）→ {func_addr:int: cls}（同一地址多类时保留首个并标注）"""
    out = {}
    for cls, v in (ida or {}).items():
        for a in (((v or {}).get('methods') or {})).keys():
            try:
                ai = int(str(a), 16)
            except Exception:
                continue
            out.setdefault(ai, cls)
    return out


def reconcile(addr, current_cls, ida, ev=None):
    """→ (verdict, detail)

    `consistent`（证据类是当前类的祖先或自身）· `contradiction`（无祖先关系 ⇒ 可证告警）·
    `no-evidence`（无 vtable 槽）✓
    """
    ev = vtable_evidence(ida) if ev is None else ev
    try:
        ai = int(str(addr), 16) if not isinstance(addr, int) else addr
    except Exception:
        return ('no-evidence', '')
    claims = ev.get(ai) or []
    if not claims:
        return ('no-evidence', '')
    # **规则（2026-09-22 实测判定）**：`from` 是**槽的声明来源**，实现者是 **owner** ✓
    # 证据：`0x43A7F0` 只出现在 `UICaption` 的 vtable 里（UIScene 的 vtable 无此槽）
    #   ⇒ 它就是 UICaption 的实现 ⇒ 判据应为 `current ∈ ancestors(owner)` ✓
    #   （旧写法拿 `from` 与 current 的祖先比 ⇒ 把"重写基类虚函数"全误判 ✗）
    # owner==current 时不能用“current ∈ ancestors(current)”自比对直接放行；
    # 显式 from 的来源也必须位于 owner 继承链内，否则是槽级矛盾 ✓
    for owner, src in claims:
        if owner == current_cls and src not in ancestors(owner, ida):
            return ('contradiction', 'current=%s · slot-from=%s' % (current_cls, src))
    for owner, src in claims:
        if current_cls in ancestors(owner, ida):
            return ('consistent', 'owner=%s(from=%s)' % (owner, src))
    return ('contradiction', 'current=%s · evidence=%s' %
            (current_cls, ', '.join('%s(from %s)' % (o, s) for o, s in claims)))


def vptr_stores(lines):
    """→ 该函数往 `[this]` 存入的 vtable 目标集合（ctor/dtor 证据 ✓）"""
    this_regs = {'ecx'}
    out = set()
    for l in lines:
        ins = (l.get('instruction') or '')
        m = MOV_R_RX.match(ins)
        if m:
            dst, src = m.group(1).lower(), m.group(2).lower()
            if src in this_regs:
                this_regs.add(dst)
            elif dst in this_regs:
                this_regs.discard(dst)
            continue
        v = VPTR_STORE_RX.match(ins)
        if v and v.group(1).lower() in this_regs:
            out.add(v.group(2))
    return out


# ==================== 驱动 ====================

def mcp_connect(session=None):
    try:
        import mcp  # noqa
        mcp.init()
    except Exception:
        return None
    sid = session
    if not sid:
        try:
            d = json.loads(mcp.call('idb_list', {})[0]['result']['content'][0]['text'])
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


def ctor_evidence(call, ida, limit=400):
    """扫 ctor/dtor：往 `[this]` 存 vtable 的函数 ⇒ 归属 = 该 vtable 的类 ✓"""
    idx = vtable_addr_to_class(ida)
    out = {}
    for cls, v in ida.items():
        for a, m in ((v or {}).get('methods') or {}).items():
            nm = (m.get('name') if isinstance(m, dict) else str(m)) or ''
            if not (nm.startswith('ctor') or nm.startswith('dtor') or nm.startswith('~')
                    or 'ctor' in nm or 'dtor' in nm):
                continue
            try:
                txt = call('disasm', {'addr': str(a), 'max_instructions': 60})
                lines = json.loads(txt)['asm']['lines']
            except Exception:
                continue
            for tgt in vptr_stores(lines):
                c = idx.get(tgt) or idx.get(tgt.replace('off_', '0x'))
                if c:
                    out.setdefault(int(str(a), 16), ('ctor-vptr', c))
            if len(out) >= limit:
                return out
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--json', action='store_true')
    ap.add_argument('--ctor', action='store_true', help='追加 ctor vptr 证据（需 MCP）')
    ap.add_argument('--session')
    ap.add_argument('--limit', type=int, default=40)
    a = ap.parse_args()

    ida = load_ida()
    ev = vtable_evidence(ida)
    cur = current_attribution(ida)
    print('=' * 96)
    print('函数归属证据审计（vtable 槽位 + 祖先关系）· vtable 证据函数 %d · 现有归属 %d 个函数'
          % (len(ev), len(cur)))
    print('=' * 96)

    rows, n_c, n_ok, n_ne = [], 0, 0, 0
    for ai in sorted(ev):
        c = cur.get(ai)
        if not c:
            continue
        v, detail = reconcile(ai, c, ida, ev)
        if v == 'contradiction':
            n_c += 1
        elif v == 'consistent':
            n_ok += 1
        rows.append({'addr': '0x%X' % ai, 'current': c, 'verdict': v, 'detail': detail})
    for r in [x for x in rows if x['verdict'] == 'contradiction'][:a.limit]:
        print('  **contradiction** %-10s 现归 %-18s %s' % (r['addr'], r['current'], r['detail'][:60]))
    n_ne = sum(1 for x in cur if x not in ev)
    print('-' * 96)
    print('小结: consistent %d · **contradiction %d** · 无 vtable 证据 %d' % (n_ok, n_c, n_ne))

    if a.ctor:
        call = mcp_connect(a.session)
        if call:
            ce = ctor_evidence(call, ida)
            print('ctor/dtor vptr 证据: %d 个函数' % len(ce))
            bad = 0
            for ai, (_tag, c) in ce.items():
                cc = cur.get(ai)
                if cc and c not in ancestors(cc, ida):
                    bad += 1
                    print('  **contradiction(ctor)** 0x%-8X 现归 %-16s vtable 属 %s' % (ai, cc, c))
            print('ctor 证据中的矛盾: %d' % bad)

    print('⇒ contradiction 是**可证告警**：人工判断（可能是归属错，或 IDB 的 vtable 数据陈旧）✓')
    if a.json:
        print(json.dumps(rows, ensure_ascii=False, indent=1))
    return 1 if n_c else 0


if __name__ == '__main__':
    sys.exit(main())
