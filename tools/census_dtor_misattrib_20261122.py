#!/usr/bin/env python3
"""[全量普查 2026-11-22] CPK 错判族同型问题扫描。

CPK 错判模式(复合, 本日实证):
  P1 成员包含误判: 内嵌 T 成员的类 X, 其 dtor 调 T 的 dtor(跨DLL成员析构)
     → D1 调用链判据失效("调 T::~T"≠"T 的完全形")
  P2 表归属未闭环: "删除式地址∈表slot5"→推"表=X类"——未闭环验证表∈X注解vtables
  P3 IAT 边界忽视: T 实现符号在 GBENGINE IAT(249 导入)=T 实现域外(DLL 提供)

四项普查:
  Q1 (P1) 冒名定义: 发射中的删除式/完全形定义, 体内调用的 ~X 形目标类名≠本类
  Q2 (P3) IAT 漏网: 注解 methods 地址 ∈ IAT thunk 地址集(实现域外却已注册)
  Q3 (P2) slot5 表归属闭环: 注解删除式地址∈slot5 的表 ∈ 该类注解 vtables?
  Q4 (P1 引申) CPK.json 剩余方法身份

用法: python3 tools/census_dtor_misattrib_20261122.py
"""
import json
import glob
import re
from pathlib import Path

REPO = Path(__file__).parent.parent
DECOMP = REPO / 'asm' / 'pal3' / 'decomp'


def norm(a):
    try:
        return '0x%08X' % int(str(a), 16)
    except (ValueError, TypeError):
        return a


# ── 数据装载 ─────────────────────────────────────────────
units = {}   # addr → (name, code)
for f in DECOMP.glob('*.json'):
    try:
        d = json.load(open(f, encoding='utf-8'))
        a = norm(d.get('address', ''))
        if a:
            units[a] = (d.get('name', ''), d.get('decompiled_c', ''))
    except Exception:
        pass

dtor_entries = []   # (cls, addr, entry)
for fp in sorted((REPO / 'data' / 'annotations' / 'structs').glob('*.json')):
    d = json.load(open(fp, encoding='utf-8'))
    cls = d.get('name') or fp.stem
    vts = set()
    for vt in (d.get('vtables') or []):
        for sl in (vt.get('slots') or []):
            try:
                vts.add(int(str(sl.get('addr')), 16))
            except (ValueError, TypeError):
                pass
    for a, m in (d.get('methods') or {}).items():
        fl = m.get('flags') or []
        nm = str(m.get('name') or '')
        if 'dtor' in fl or nm.startswith('~'):
            dtor_entries.append((cls, norm(a), m, vts))

print('== 装载: 单元 %d, dtor 条目 %d ==' % (len(units), len(dtor_entries)))

# ── Q1: 冒名定义(体内调用他人 dtor + wrapper 形) ─────────
# 检测: 发射在册的 dtor 单元, 体含 `X::~X(` 且 X≠本类, 且体呈 wrapper 形
# (短体+条件 operator delete——deleted-form ABI 的 stub 调用形名非 ~ 不误伤)
issues_q1 = []
for cls, addr, m, vts in dtor_entries:
    u = units.get(addr)
    if not u:
        continue
    code = u[1]
    if len(code) > 400:
        continue
    if 'operator delete' not in code:
        continue
    # 体内 ~X:: 调用(他人类名)
    others = set(re.findall(r'(\w+)::~\w*\s*\(', code))
    others = {x for x in others if x != cls}
    if others:
        issues_q1.append((cls, addr, sorted(others), len(code)))

print('\n== Q1 冒名定义(wrapper体含他人dtor调用) %d ==' % len(issues_q1))
for cls, addr, others, ln in sorted(issues_q1):
    print('  %-16s %s 体%dB 调用他人dtor: %s' % (cls, addr[-8:], ln, ','.join(others)))

# ── Q2: IAT 漏网(注解地址∈导入thunk) ─────────────────────
# 导入 thunk 地址: IDB 内 .idata 段 adjacent; 简化: 用 ida 不便——改用
# decomp 单元名含 __imp_ 或单元极短(≤8字节 jmp)间接判定 + 用户可见性留待
# idalib 复核(此处先做注解侧静态普查: 已知 IAT 槽址表由 match 侧提供)
# 快查: CPK.json 剩余方法(Q4)
print('\n== Q4 CPK.json 剩余方法 ==')
cpk = json.load(open(REPO / 'data' / 'annotations' / 'structs' / 'CPK.json', encoding='utf-8'))
for a, m in sorted((cpk.get('methods') or {}).items()):
    u = units.get(norm(a))
    nm = u[0] if u else '(无单元)'
    body_head = (u[1][:60].replace('\n', ' ') if u else '')
    print('  %s %-18s 单元名: %s' % (a[-8:], m.get('name'), nm[:40]))
    print('      体头: %s' % body_head)

# ── Q3: slot5 表归属闭环 ────────────────────────────────
print('\n== Q3 slot5 表归属闭环(抽样: 注解删除式地址出现在某表slot5, 表∈该类vtables?) ==')
# 表地址集(全注解 vtables)
tables_by_cls = {}
for fp in sorted((REPO / 'data' / 'annotations' / 'structs').glob('*.json')):
    d = json.load(open(fp, encoding='utf-8'))
    cls = d.get('name') or fp.stem
    for vt in (d.get('vtables') or []):
        try:
            ta = int(str(vt.get('addr')), 16)
            tables_by_cls.setdefault(ta, []).append(cls)
        except (ValueError, TypeError):
            pass
unclosed = []
for cls, addr, m, vts in dtor_entries:
    if 'deleting' not in (m.get('flags') or []):
        continue
    ai = int(addr, 16)
    # 在 .rdata 找引用该址的表(需 idalib——此处用已知案+回归两个已闭环案作代表性说明)
    if vts and ai in vts:
        continue   # 槽证据在册=闭环 ✓
    unclosed.append((cls, addr))
print('删除式条目 %d, 其中槽证据在册(vtables含本址) %d, 未闭环 %d' % (
    len([1 for c, a, m, v in dtor_entries if 'deleting' in (m.get('flags') or [])]),
    len(dtor_entries) - len(unclosed), len(unclosed)))
print('(未闭环=槽证据依赖外部表扫描, 本普查列出欠账清单供 idalib 复核)')
for cls, addr in sorted(unclosed)[:12]:
    print('  %-16s %s' % (cls, addr))
