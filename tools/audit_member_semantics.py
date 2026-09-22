#!/usr/bin/env python3
"""**字段语义/类型审计**（只读、证据分级、人工确认）—— 回答"这个名字/类型有没有证据？"

## 为什么（2026-09-21 使用者指令 + 实测）

使用者指出 `m_nTodo_C660` 这类名字"需要更明确的语义命名，类型也需要确认和修正"。
**实测反转了定性**：该成员的偏移 +0xC660 的 disp32 小端模式在整个二进制**命中 0 次** ⇒
**没有任何指令直接访问它** ⇒ 它**很可能根本不是字段** ⇒ 给它 `int` + `m_nTodo_` **本身就是编造** ✗
（阳性对照：`m_nRoleCount` +0xE0E0 ⇒ 命中 8 处 ✓）

## 判据（每一步都可机械执行、可否证）

1. **disp32 扫描**：把成员偏移写成小端 4 字节，全二进制搜（MCP `find_bytes`）
   * **0 命中** ⇒ `NO-EVIDENCE` ⇒ **不得给类型、不得给语义名** ⇒ 建议降级为 padding/未知空间
   * 有命中 ⇒ 进入第 2 步（命中含**假阳性**：栈偏移、立即数 ✓ 实测）
2. **确认承载指令**：`disasm` 命中点附近的指令，找到真正包含该 disp32 的指令
3. **类型证据（可证）**：宽度（BYTE/WORD/DWORD/QWORD · `fld dword/qword` · XMM）+ 运算
   （`fdiv`⇒float · `imul`⇒整型数组步长 · `cmp`+`jl`/`jb`⇒有/无符号）
   ⇒ 可证 **宽度 + int/float/指针 + 有/无符号**；**不可证**精确源码类型、struct vs class ✗
4. **名字证据**：仅在**语义把手**存在时可给（字符串/诊断 · RTTI · 传给已知 API 的实参 · mangled 符号 ·
   PDB 仅参考）；**无把手 ⇒ 保留 `_todo_`** ✓（仓规：不确定含义时保留 `_todo_`；禁止伪语义命名）

用法::

    python3 tools/audit_member_semantics.py --class SceneMgr            # 只审伪语义命名成员
    python3 tools/audit_member_semantics.py --class SceneMgr --all      # 全部成员
    python3 tools/audit_member_semantics.py --class SceneMgr --session <id> --json

只读、只报警（**不自动改注解**）⇒ 人工确认后再改，且每处必须带证据指针 ✓
"""
import argparse
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, os.path.join(ROOT, 'pipeline'))
sys.path.insert(0, '/tmp')          # headless MCP helper（mcp.py）

import audit_type_layout as A       # 复用**唯一**成员解析入口与 include 集推导 ✓

# 伪语义命名（与仓规"禁止伪语义命名"一致）
PSEUDO_RX = [
    ('addr-suffix', re.compile(r'_[0-9A-F]{3,}$')),
    ('todo', re.compile(r'(^|_)todo(_|$)', re.I)),
    ('field', re.compile(r'^m_[npf]?Field_|_field_', re.I)),
    ('param', re.compile(r'^m_[npf]?Param_', re.I)),
    ('unk', re.compile(r'un[ck]', re.I)),
]

# 宽度/运算 ⇒ 类型线索
WIDTH_RX = [
    (re.compile(r'\bmovzx\b|\bmovsx\b'), '整型（零/符号扩展 ⇒ 窄于 32 位）'),
    (re.compile(r'\bfld\s+dword\b|\bfstp?\s+dword\b|\bfadd\s+dword\b'), 'float（32 位浮点）'),
    (re.compile(r'\bfld\s+qword\b|\bfstp?\s+qword\b'), 'double（64 位浮点）'),
    (re.compile(r'\bmovss\b|\bmovaps\b|\bmovups\b|xmm'), 'SIMD（16 字节向量）'),
    (re.compile(r'\bmov\s+[a-z]*[abcd]l\b|\bmov\s+byte\b|\bcmp\s+byte\b'), 'byte'),
    (re.compile(r'\bmov\s+[a-z]*[abcd]x\b|\bmov\s+dword\b|\bcmp\s+dword\b'), 'dword/指针/整型'),
    (re.compile(r'\blea\b'), '地址/数组（lea ⇒ 取址/索引）'),
    (re.compile(r'\bimul\b|\bshl\b|\bmul\b'), '整型数组（步长/索引运算）'),
    (re.compile(r'\bfdiv\b|\bfmul\b|\bfsub\b|\bfadd\b'), '浮点运算'),
]



# ===== 主证据源：本地 decomp 语料（高精度、快、覆盖游戏已反编译函数）=====
# ⚠️ 为什么不用 disp32 字节扫描作主证据：小偏移的模式（如 +0x20 → `20 00 00 00`）**过于通用** ⇒
#    假阳性泛滥（实测把 `[esp+68h+var_48]` 这类**栈**指令报成"访问证据" ✗）。
#    字节扫描仅在偏移的高位字节携带信息（如 0xC660 → `60 C6 00 00`）时才有判别力 ⇒ 降为**次要**并标注。
CORPUS_DIR = os.path.join(ROOT, 'asm', 'pal3', 'decomp')



def _anno_type(cls, name):
    """从注解里取该成员的 type（用于复合成员守卫）"""
    try:
        d = json.load(open(os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % cls),
                           encoding='utf-8'))
        for k, v in (d.get('known_members') or {}).items():
            if isinstance(v, dict) and v.get('name') == name:
                return v.get('type')
    except Exception:
        pass
    return None


def class_method_files(cls):
    """该类的**方法文件**列表（decomp 语料文件名含方法地址）—— 把证据搜索**限定在本类自己的代码**里 ✓

    为什么必须限定：全语料搜索会把**别的类**里同偏移/同小数字的巧合当成证据 ✗
    （实测：`m_nTodo_020` 匹配到 `v20`、`_gap_120` 匹配到栈注释 `[ebp-130h]`）。
    """
    import glob
    out = []
    try:
        IS = json.load(open(os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json'), encoding='utf-8'))
        methods = (IS.get(cls) or {}).get('methods') or {}
        addrs = set()
        for a in methods:
            try:
                addrs.add('%08x' % int(str(a), 0))
            except Exception:
                pass
        for fn in sorted(os.listdir(CORPUS_DIR)):
            low = fn.lower()
            if fn.endswith('.json') and any(a in low for a in addrs):
                out.append(fn)
    except Exception:
        out = []
    return out


# 偏移模式：必须是 `[reg+0xNNN]` / `[reg+NNNh]` 形态；**排除栈帧**（esp/ebp/var_/local）
BASE_DISP_RX = re.compile(r'\[\s*(?!esp|ebp)[a-z][a-z0-9]*\s*\+\s*(0x0*%s|0*%sh)\s*\]', re.I)
STACK_RX = re.compile(r'\b(esp|ebp)\b|var_[0-9A-F]+|\[ebp-', re.I)


def corpus_evidence(cls, name, off, files=None):
    """本类方法文件里的**使用证据** → [(文件, 上下文)]（最多 5 条）

    只认两种形态：① **成员名**（IDB 已 apply 时伪代码会用名字 ✓）② `[reg+0xNNN]` 的**基址+位移**形态（且非栈）✓
    """
    if not os.path.isdir(CORPUS_DIR):
        return []
    # ⚠️ 2026-09-22 反证修正：**成员名必须全局搜**（名字在全语料唯一；此前限定本类方法 ⇒
    # 漏掉来自**其它单元**的访问 ⇒ 假阴性：`m_nTodo_1428` 实际在 PAL3.cpp 里被赋值 ✗）。
    # 偏移模式仍是**本类范围**（避免跨类的偏移碰撞 ✗）。
    files = files if files is not None else None
    scan_files = files if files is not None else sorted(f for f in os.listdir(CORPUS_DIR) if f.endswith('.json'))
    if not scan_files:
        return []
    hx = '%X' % off
    name_rx = re.compile(r'\b%s\b' % re.escape(name)) if name else None
    off_rx = None
    if off > 0xFF:
        off_rx = re.compile(BASE_DISP_RX.pattern % (hx, hx), re.I)
    hits = []
    class_files = set(class_method_files(cls))
    for fn in scan_files:
        # 名字证据：全语料；偏移证据：只在本类方法文件里认（防跨类碰撞）
        allow_disp = (files is not None) or (fn in class_files)
        if not allow_disp and not name:
            continue
        try:
            txt = open(os.path.join(CORPUS_DIR, fn), encoding='utf-8', errors='replace').read()
        except Exception:
            continue
        found = None
        if name_rx:
            m = name_rx.search(txt)
            if m:
                found = (m, 'name')
        if not found and off_rx and allow_disp:
            for m in off_rx.finditer(txt):
                a = max(0, m.start() - 50)
                if STACK_RX.search(txt[a:m.end() + 10]):
                    continue
                found = (m, 'disp')
                break
        if found:
            m = found[0]
            a = max(0, m.start() - 55); b = min(len(txt), m.end() + 55)
            hits.append((fn[:-5], '[%s] %s' % (found[1], txt[a:b].replace('\n', ' ').replace('\\', ''))))
        if len(hits) >= 5:
            break
    return hits



# ===== 证据源③：经**全局对象**的成员访问（形态②，2026-09-22 反证后补）=====
# 为什么必须有：`g_X.member` 编译成**绝对地址** `[g_X_addr + off]` ⇒ off **不作为独立 disp32 出现** ✗
# ⇒ 仅靠"偏移模式扫描"与"语料名字搜索"都看不见（实测 `m_nTodo_1428` 被 PAL3.cpp 赋值却判"无证据" ✗）。
# 补法：枚举**类型为该类**的全局对象，扫 `global_addr + off` 的 disp32 ✓
# 优点：模式含**完整 32 位绝对地址** ⇒ 判别力极高、几乎无假阳性 ✓
def globals_of_type(cls):
    """→ [(addr, name)]：类型恰好是 cls 的**全局对象**（按值，非指针）"""
    out = []
    try:
        d = json.load(open(os.path.join(ROOT, 'data', 'annotations', 'globals.json'), encoding='utf-8'))
    except Exception:
        return out
    for a, v in (d.items() if isinstance(d, dict) else []):
        if not isinstance(v, dict):
            continue
        t = str(v.get('type') or '').strip()
        base = t.replace('struct ', '').replace('class ', '').strip()
        if base == cls:
            try:
                out.append((int(str(a), 0), v.get('name')))
            except Exception:
                pass
    return out


def confirm_abs_access(instr, val):
    """承载指令是否引用**绝对地址** val（形态②）✓

    ⚠️ 实测（2026-09-22）：IDA 把绝对地址渲染成**符号名**（`dword_C057B4` / `off_xxxxxx`），
    而不是 `0xC057B4` ⇒ 只查 `0x...` 形态**必然失配** ✗（曾据此误判 `m_nTodo_1428` 为"无证据"）。
    因此必须同时接受：① `0x...` 十六进制形态 ② **内嵌该地址十六进制数字的符号名** ✓
    """
    t = (instr or '')
    tl = t.lower()
    forms = ['0x%x' % val, '%xh' % val, '0%xh' % val]
    if any(f in tl for f in forms):
        return True
    # IDA 符号名内嵌地址（大小写两种都试；要求 ≥6 位十六进制，避免短数字误配 ✓）
    for hx in ('%X' % val, '%08X' % val, '%x' % val):
        if len(hx) >= 6 and hx in t:
            return True
    return False


def pseudo_tag(name):
    for tag, rx in PSEUDO_RX:
        if rx.search(name or ''):
            return tag
    return None


def mcp_connect(session=None):
    """→ (call, session_id) 或 (None, None)（MCP 不可用时应诚实跳过）"""
    try:
        import mcp  # noqa
        mcp.init()          # headless MCP helper 需要先握手
    except Exception:
        return None, None
    sid = session
    if not sid:
        try:
            r = mcp.call('idb_list', {})
            txt = r[0]['result']['content'][0]['text']
            d = json.loads(txt)
            items = d if isinstance(d, list) else (d.get('sessions') or [])
            if items:
                sid = items[0].get('session_id') or items[0].get('id')
        except Exception:
            return None, None
    if not sid:
        return None, None

    def call(tool, args):
        a = dict(args)
        a['database'] = sid
        r = mcp.call(tool, a)
        try:
            return r[0]['result']['content'][0]['text']
        except Exception:
            return json.dumps(r, ensure_ascii=False)[:200]
    return call, sid


def disp32_pattern(off):
    return ' '.join('%02X' % b for b in off.to_bytes(4, 'little', signed=False))


def _bin_oracle():
    """**O2（IDB-无关）** 二进制裁判 —— 取代 MCP 的字节路径 ✓（去会话脆弱性 + 不再占 IDB ✓）"""
    try:
        sys.path.insert(0, os.path.join(ROOT, 'tools'))
        import bin_oracle
        return bin_oracle
    except Exception:
        return None


def find_hits_batch(call, values, limit=1):
    """**权威批量否定证据**：一次调用扫多个完整 disp32（成员偏移 + 各全局对象地址+偏移）✓

    ⚠️ 2026-09-22 教训：单值 `find_hits` + "承载指令确认"会把**命中但未能确认指令**的情况
    误当"无证据" ✗（实测 `m_nTodo_C660` 的全局形态 `0xC109F0` 在 .text 命中 1 次却被报无证据，
    导致错误撤类型）。⇒ **否定结论必须来自本函数**（只要命中就不算"无证据"）✓
    性能：12 个模式 0.06s ⇒ 每类一次调用即可覆盖全部成员 ✓
    """
    if not values:
        return {}
    pats = [' '.join('%02X' % b for b in int(v).to_bytes(4, 'little', signed=False)) for v in values]
    out = {}
    bo = _bin_oracle()
    if bo is not None:
        # O2 路径（首选）：直接扫原始 EXE ✓ 不需要 MCP ✓
        for pat in pats:
            try:
                hits = bo.scan(bytes.fromhex(pat.replace(' ', '')), limit=limit)
            except Exception:
                hits = []
            if hits:
                out[pat] = ['0x%X' % h for h in hits]
        return out
    if not call:
        return out
    txt = call('find_bytes', {'patterns': pats, 'limit': limit})
    try:
        d = json.loads(txt)
        for x in d:
            out[x['pattern']] = x.get('matches') or []
    except Exception:
        pass
    return out


def find_hits(call, off, limit=8):
    txt = call('find_bytes', {'patterns': [disp32_pattern(off)], 'limit': limit})
    try:
        d = json.loads(txt)
        return (d[0].get('matches') or d[0].get('data') or [])[:limit]
    except Exception:
        return []


def disasm_around(call, hit, back=24, count=8):
    """命中点落在指令**内部** ⇒ 需要往前找承载指令的起点（近似：从 hit-back 起 disasm 再取覆盖 hit 的那条）"""
    try:
        addr = int(str(hit), 16)
    except Exception:
        return []
    start = max(0x401000, addr - back)
    txt = call('disasm', {'addr': '0x%X' % start, 'max_instructions': count})
    try:
        lines = json.loads(txt)['asm']['lines']
    except Exception:
        return []
    out = []
    for i, l in enumerate(lines):
        try:
            a = int(str(l['addr']), 16)
        except Exception:
            continue
        nxt = None
        if i + 1 < len(lines):
            try:
                nxt = int(str(lines[i + 1]['addr']), 16)
            except Exception:
                nxt = None
        if a <= addr and (nxt is None or addr < nxt):
            out.append(l)
    return out


DISP_RX = re.compile(r'\[\s*(?!esp|ebp)([a-z][a-z0-9]*)\s*\+\s*(0x[0-9a-f]+|[0-9a-f]+h)\s*\]', re.I)


def confirm_disp_access(instr, off):
    """承载指令是否是 `[reg+**该偏移**]` 且**非栈** ✓

    ⚠️ 必须**核对位移等于 off**：只判"是 [reg+disp]"会把 `[esi+40h]` 这类**别的偏移**当成证据 ✗
    （实测：`_gap_120` 曾被 `mov [esi+40h], edi` 蒙过）
    """
    m = DISP_RX.search(instr or '')
    if not m:
        return False
    raw = m.group(2)
    try:
        val = int(raw[:-1], 16) if raw.lower().endswith('h') else int(raw, 0)
    except Exception:
        return False
    return val == off


def type_hint(instr):
    t = (instr or '').lower()
    for rx, hint in WIDTH_RX:
        if rx.search(t):
            return hint
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--class', dest='cls', required=True)
    ap.add_argument('--all', action='store_true', help='审全部成员（默认只审伪语义命名成员）')
    ap.add_argument('--limit', type=int, default=40)
    ap.add_argument('--session')
    ap.add_argument('--source', choices=['corpus', 'bytes', 'both'], default='both',
                    help='证据源：both=语料+字节（默认，两源互补）· corpus=只用本地语料 · bytes=只用字节扫描')
    ap.add_argument('--json', action='store_true')
    a = ap.parse_args()

    # 复合成员守卫（2026-09-21 实测教训）：**按值内嵌的类成员**，其内部成员是经
    # `[base + 外层偏移 + 内层偏移]` 访问的，本工具的"单偏移扫描"**看不见** ⇒ 会假阴性 ✗
    # 例如 SceneMgr 的 `stru_C059A0`（按值 RoleSystem）绝不能因"无证据"被降级 ✗
    # ⇒ 对这类成员只给 `COMPOSITE-SKIP`，交给专门的复合扫描（或人工）。
    _IS = {}
    try:
        _IS = json.load(open(os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json'), encoding='utf-8'))
    except Exception:
        pass
    _KNOWN = set(_IS) | set(A.load_annotation_members())

    def is_composite(t):
        t = str(t or '').strip()
        if not t or '*' in t or '[' in t or t in ('int', 'unsigned int', 'float', 'double', 'void *',
                                                  'char', 'unsigned char', '_BYTE', 'BYTE', 'bool', 'short'):
            return False
        return (t.replace('struct ', '').replace('class ', '').strip() in _KNOWN)

    members = A.load_annotation_members()
    if a.cls not in members:
        print('未找到类或其成员注释: %s' % a.cls)
        return 2
    header, declared = members[a.cls]
    todo = [(n, o) for n, o in declared if a.all or pseudo_tag(n)]
    todo = todo[:a.limit]

    use_bytes = a.source in ('bytes', 'both')
    call, sid = (mcp_connect(a.session) if use_bytes else (None, None))
    print('=' * 84)
    print('字段语义/类型审计（只报警，不自动改）· 类 %s · 成员 %d · MCP %s'
          % (a.cls, len(todo), ('session %s' % sid) if call else '**不可用（只列名与偏移）**'))
    print('=' * 84)
    rows = []
    for name, off in todo:
        tag = pseudo_tag(name) or '-'
        # 语料证据**不需要 MCP** ⇒ 无 MCP 时也要照常出结论 ✓
        if is_composite(_anno_type(a.cls, name)):
            rows.append({'member': name, 'off': hex(off), 'tag': tag,
                         'verdict': 'COMPOSITE-SKIP',
                         'evidence': '按值复合成员：内部访问不可见 ⇒ 不做"无证据"结论'})
            print('  %-26s +0x%-6X %-12s ⊘ 复合成员（不做无证据结论）' % (name, off, tag))
            continue
        ce = corpus_evidence(a.cls, name, off)
        hits = find_hits(call, off) if call else []
        b_instr = None
        if hits:
            for h in hits[:3]:
                for l in disasm_around(call, h):
                    if confirm_disp_access(l.get('instruction'), off):
                        b_instr = l.get('instruction'); break
                if b_instr:
                    break
        g_evid = None
        g_raw = []
        if off is not None:      # ← 不再要求 MCP：O2(bin_oracle) 可独立完成 ✓
            gl = globals_of_type(a.cls)
            vals = [off] + [gaddr + off for gaddr, _ in gl]
            batch = find_hits_batch(call, vals)
            pat = lambda v: ' '.join('%02X' % b for b in int(v).to_bytes(4, 'little', signed=False))
            g_raw = batch.get(pat(off), []) + [h for gaddr, _ in gl for h in batch.get(pat(gaddr + off), [])]
            for gaddr, gname in gl:
                gval = gaddr + off
                gh = batch.get(pat(gval)) or []
                if not gh:
                    continue
                bo = _bin_oracle()
                for h in gh[:2]:
                    if bo is not None:
                        # O2 路径：objdump 给的是**十六进制绝对地址** ✓（比 IDA 的符号名更直接 ✓）
                        if bo.confirm_abs_access(int(str(h), 16) if isinstance(h, str) else h, gval):
                            g_evid = 'g_%s(0x%X)+0x%X = 0x%X :: [O2] objdump 绝对地址命中' % (
                                str(gname).replace('g_', ''), gaddr, off, gval)
                            break
                        continue
                    for l in disasm_around(call, h):
                        if confirm_abs_access(l.get('instruction'), gval):
                            g_evid = 'g_%s(0x%X)+0x%X = 0x%X :: %s' % (
                                str(gname).replace('g_', ''), gaddr, off, gval,
                                (l.get('instruction') or '')[:46])
                            break
                    if g_evid:
                        break
                if g_evid:
                    break
        if g_evid:
            verdict = 'EVIDENCE-GLOBAL(全局对象)'
            evid = g_evid
            hint = type_hint(g_evid)
        elif ce:
            verdict = 'EVIDENCE-CODE(本类代码)'
            evid = ce[0][0] + ' :: ' + ce[0][1][:60]
            hint = type_hint(evid)
        elif b_instr:
            verdict = 'EVIDENCE-BYTES(O2 原始字节·独立)'
            evid = '%s :: %s' % (hits[0], b_instr[:52])
            hint = type_hint(b_instr)
        elif g_raw or hits:
            # ⚠️ 有权威批量扫描的命中 ⇒ **不得**判"无证据"（未确认 ≠ 不存在）✓
            verdict, hint, evid = 'HITS-UNCONFIRMED(有命中未确认)', None, 'raw-hit %s' % (g_raw or hits)[:1]
        else:
            verdict, hint, evid = 'NO-EVIDENCE', None, ''
        rows.append({'member': name, 'off': hex(off), 'tag': tag,
                     'verdict': verdict, 'type_hint': hint, 'evidence': evid,
                     'corpus_hits': len(ce), 'byte_hits': len(hits)})
        mark = {'EVIDENCE-GLOBAL(全局对象)': '✓ 经全局对象访问 [O2 独立]',
                'NO-EVIDENCE': '✗ 无证据（不得给类型/语义名）',
                'EVIDENCE-CODE(O4 语料·非独立)': '? 语料命中（O4 非独立）',
                'EVIDENCE-BYTES(O2 原始字节·独立)': '✓ 原始字节命中 [O2 独立]',
                'HITS-UNCONFIRMED(疑似假阳性)': '? 命中未确认'}.get(verdict, '?')
        print('  %-26s +0x%-6X %-12s %s %s'
              % (name, off, tag, mark, ('%s | %s' % (evid, hint or ''))[:56]))

    n_no = sum(1 for r in rows if r['verdict'] == 'NO-EVIDENCE')
    n_ev = sum(1 for r in rows if r['verdict'].startswith('EVIDENCE'))
    n_by = sum(1 for r in rows if r['verdict'].startswith('HITS'))
    print('=' * 84)
    n_cs = sum(1 for r in rows if r['verdict'] == 'COMPOSITE-SKIP')
    print('小结: 有证据 %d（本类代码 + 他处代码）· **无任何证据 %d**（应降级为 padding/未知，不得给类型与语义名）· 疑似假阳性 %d · 复合成员跳过 %d'
          % (n_ev, n_no, n_by, n_cs))
    print('⇒ 人工确认后再改注解；每处必须带证据指针（VA:指令）✓')
    if a.json:
        print(json.dumps(rows, ensure_ascii=False, indent=1))
    return 0


if __name__ == '__main__':
    sys.exit(main())