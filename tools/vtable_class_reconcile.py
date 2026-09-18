#!/usr/bin/env python3
"""vtable ↔ 类 全局对账（**只读**）：用二进制证据判定每张虚表属于哪个 annotated 类。

## 为什么需要它

`data/annotations/structs/*.json` 的 `vtables` 是**手工记录**的（`export_full.py:678` 透传），
没有任何校验。已知 3 处错映射（本会话 F2 发现）：

| vtable | 现挂在 | 真实归属 |
|--------|--------|----------|
| `0x56AC20` | `UIProgressBar.json` | `UI3DCtrl`（槽 1 `0x439410` 访问 `0x124(%esi)`=292 > sizeof(UIProgressBar)=244）|
| `0x56AD64` | `UIButton.json` | `UIProgressBar` |
| `0x56ACFC` | `UI3DCtrl.json` | ? |

而 `emit_headers.class_vtable_slots()` 依赖该记录给类判定虚性 ⇒ 错映射会**污染生成的头文件**
（虚函数声明落在错误的类上），进而影响字节匹配。

## 判据（A 级证据）

虚函数入口 `this` 在 `%ecx`。函数序言把它复制到别的寄存器（`%esi`/`%ebp`/`%edi`/`%ebx`），
之后所有 `disp(%reg)` 访问都是**该对象的成员访问**。于是：

    required_span(vtable) = max over slots ( max this-offset + access_size )

若 `required_span > binary_size(声明类)` ⇒ **该函数不可能属于该类**（指令级证据，A 级）。
再对全 annotated 类做**布局覆盖度打分**（访问到的偏移是否落在该类的成员区间内），
给出真实归属的候选排序。

## 纪律

- **只读**：不改 annotation、不碰 IDB。
- 反汇编交给 `objdump`（自造解码器会制造假象 —— 见 vtable_scanner.py 的教训）。
- 表边界用 **ctor 实写的 vptr 存储目标**界定（相邻表起始之差 = 前表长度，精确），
  不用"遇到非 .text 指针即停"（多张表连续排布时失效）。
- 访问偏移只统计**入口 this 寄存器**，且该寄存器被写即视为不再可信（保守，宁可少算）。

用法：
  python3 tools/vtable_class_reconcile.py --all                 # 全量对账
  python3 tools/vtable_class_reconcile.py --vtable 0x56AC20     # 单表
  python3 tools/vtable_class_reconcile.py --all --out data/status/_vtable_reconcile.json
  python3 tools/vtable_class_reconcile.py --self-test           # 自检（已知 3 处反例）
"""
import argparse
import json
import os
import re
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')
DECOMP = os.path.join(ROOT, 'asm', 'pal3', 'decomp')

IMG_BASE = 0x400000
TEXT_LO, TEXT_HI = 0x401000, 0x56A000      # .text
RDATA_LO, RDATA_HI = 0x56A000, 0x580000    # .rdata

# **坑（2026-09-17 实测）**：`.rdata` 的 `VirtualSize=0x15178` 但 `SizeOfRawData=0x16000`，
# 加载器按 raw 大小映射 ⇒ 有效虚拟范围到 `0x580000` 而非 `0x56F178`。
# 若按 VirtualSize 判定，会把 `0x5704A8`/`0x57058C` 等**真实存在**的 vtable 误判为"未映射"，
# 从而产出"18 个注解 vtable 指向未映射地址"的**假发现**。取证工具读节必须用 max(vsz, rsz)。


# ---- PE 读取 ---------------------------------------------------------------
def _sections():
    f = open(EXE, 'rb').read()
    pe = struct.unpack_from('<I', f, 0x3C)[0]
    nsec = struct.unpack_from('<H', f, pe + 6)[0]
    opt = pe + 24
    off = opt + struct.unpack_from('<H', f, pe + 20)[0]
    secs = []
    for i in range(nsec):
        s = off + 40 * i
        name = f[s:s + 8].rstrip(b'\x00').decode('latin1')
        vsz, va, rsz, ptr = struct.unpack_from('<IIII', f, s + 8)
        secs.append((name, va + IMG_BASE, vsz, ptr, rsz))
    return f, secs


_F, _SECS = _sections()


def read_va(va, n):
    for _name, sva, vsz, ptr, rsz in _SECS:
        if sva <= va < sva + max(vsz, rsz):
            o = ptr + (va - sva)
            return _F[o:o + n]
    return None


def rd32(va):
    b = read_va(va, 4)
    return struct.unpack('<I', b)[0] if b and len(b) == 4 else None


def norm_va(s):
    if s is None:
        return None
    if isinstance(s, int):
        return s
    s = str(s).strip()
    return int(s, 16) if s.lower().startswith('0x') else int(s)


# ---- annotation ------------------------------------------------------------
def load_structs():
    S = {}
    for fn in sorted(os.listdir(STRUCTS)):
        if not fn.endswith('.json'):
            continue
        try:
            d = json.load(open(os.path.join(STRUCTS, fn), encoding='utf-8'))
        except Exception:
            continue
        if not isinstance(d, dict) or 'name' not in d:
            continue
        S[d['name']] = d
    return S


def chain(S, cls, _seen=None):
    """类 + 全部基类（沿 base_class 上溯）。base_class 可能是 str 或 list。"""
    out, seen = [], _seen if _seen is not None else set()
    while cls and cls in S and cls not in seen:
        seen.add(cls)
        out.append(cls)
        bc = S[cls].get('base_class')
        if isinstance(bc, list):
            nxt = None
            for b in bc:
                if isinstance(b, dict):
                    b = b.get('name')
                if b in S and b not in seen:
                    nxt = b
                    break
            cls = nxt
        else:
            cls = bc
    return out


def member_intervals(S, cls):
    """[(lo, hi, name, owner)]，绝对偏移（known_members 的 offset 即绝对偏移）。"""
    iv = []
    for k in chain(S, cls):
        for offs, m in (S[k].get('known_members') or {}).items():
            try:
                o = int(offs)
            except Exception:
                continue
            sz = 4
            iv.append((o, o + sz, m.get('name', '?'), k))
    return iv


# ---- 反汇编 ----------------------------------------------------------------
_ASM_CACHE = {}


def disasm(va, end):
    key = (va, end)
    if key not in _ASM_CACHE:
        try:
            out = subprocess.run(
                ['objdump', '-d', '--start-address=%d' % va, '--stop-address=%d' % end, EXE],
                capture_output=True, text=True, timeout=60).stdout
        except Exception:
            out = ''
        _ASM_CACHE[key] = out
    return _ASM_CACHE[key]


def asm_lines(va, end):
    out, lines = disasm(va, end), []
    for l in out.splitlines():
        if re.match(r'\s+[0-9a-f]+:', l):
            lines.append(l.split(':', 1)[1])
    return lines


def func_size(va):
    """函数体长度：优先 decomp JSON 的 size_bytes。"""
    _load_func_index()
    return _FUNC_SIZE.get(va)


_FUNC_SIZE = None
_FUNC_SIG = None


def _load_func_index():
    global _FUNC_SIZE, _FUNC_SIG
    if _FUNC_SIZE is not None:
        return
    _FUNC_SIZE, _FUNC_SIG = {}, {}
    if os.path.isdir(DECOMP):
        for fn in os.listdir(DECOMP):
            try:
                d = json.load(open(os.path.join(DECOMP, fn), encoding='utf-8'))
            except Exception:
                continue
            a = norm_va(d.get('address'))
            sz = d.get('size_bytes') or 0
            if a and sz:
                _FUNC_SIZE[a] = sz
                _FUNC_SIG[a] = d.get('signature') or ''


def is_thiscall(va):
    """只有签名声明 `__thiscall` 时 `%ecx` 才是 this。

    **没有这个闸门会产出垃圾**：非 thiscall 槽位（回调/`__cdecl`）的 `%ecx` 是任意值，
    实测把 `RenderTarget` 的 req 算成 307044（见 2026-09-17 全量对账的 v1 输出）。
    """
    _load_func_index()
    return '__thiscall' in (_FUNC_SIG.get(va) or '')


def this_regs(lines):
    """入口 `%ecx` 在第一次 call 之前被复制到哪些寄存器（不能假定 %esi）。"""
    regs = {'%ecx'}
    for l in lines:
        if re.search(r'\bcall\b', l):
            break
        m = re.search(r'\bmov\s+%ecx\s*,\s*(%[a-z]{2,3})\b', l)
        if m:
            regs.add(m.group(1))
    return regs


_SIZE_SUF = {'b': 1, 'w': 2, 'l': 4}
_OPSIZE = re.compile(r'^\s*([a-z][a-z0-9]*?)([bwl])\s')


def this_offsets(va):
    """返回 (offsets, req)：
      offsets = [(off, size, insn)] 入口 this 寄存器的访问；
      req     = max(off + size)（最小所需对象尺寸的下界）。
    只统计仍"存活"的 this 寄存器：被写即失效（`mov ...,%reg` / `pop %reg`）。
    """
    sz = func_size(va)
    if not sz:
        return None, None
    if not is_thiscall(va):
        return None, None          # %ecx 不是 this ⇒ 不出结论（宁缺勿假）
    lines = asm_lines(va, va + sz)
    # 跳转 thunk 跟随
    if len(lines) == 1 and re.search(r'\bjmp\b', lines[0]):
        m = re.search(r'\bjmp\s+([0-9a-f]+)', lines[0])
        if m:
            return this_offsets(int(m.group(1), 16))
    regs = this_regs(lines)
    live = set(regs)
    # `mov %ecx,%X` **建立** X 的那条指令不能当成"覆盖 X"（否则建立即失效）
    birth = {}
    for i, body in enumerate(lines):
        m = re.search(r'\bmov\s+%ecx\s*,\s*(%[a-z]{2,3})\b', body)
        if m:
            birth.setdefault(m.group(1), i)
    hits = []
    for i, body in enumerate(lines):
        if re.search(r'\bret\b', body):
            break
        if not live:
            break
        # 先算本指令的读（`mov 0x8(%ecx),%ecx` 的读要算进去）
        for reg in list(live):
            for m in re.finditer(r'(?:0x([0-9a-f]+))?\((' + re.escape(reg) + r')\)', body):
                off = int(m.group(1), 16) if m.group(1) else 0
                mo = _OPSIZE.match(body)
                asz = _SIZE_SUF.get(mo.group(2), 4) if mo else 4
                hits.append((off, asz, body.strip()))
        # 再判覆盖（建立该寄存器的那条指令除外）
        for reg in list(live):
            if birth.get(reg) == i:
                continue
            if re.search(r',\s*' + re.escape(reg) + r'\b', body) or \
               re.search(r'\bpop\s+' + re.escape(reg) + r'\b', body):
                live.discard(reg)
    req = max((o + s for o, s, _ in hits), default=0)
    return hits, req


# ---- 表边界：ctor 实写的 vptr 存储目标 --------------------------------------
_VPTR_STORES = None


def vptr_targets():
    """全量 .text 反汇编，收集 `movl $0x5xxxxx,(%reg)` 的立即数目标 = 表起始地址。"""
    global _VPTR_STORES
    if _VPTR_STORES is not None:
        return _VPTR_STORES
    out = disasm(TEXT_LO, TEXT_HI)
    tgt = set()
    for l in out.splitlines():
        m = re.search(r'movl?\s+\$0x([0-9a-f]{6,8}),', l)
        if m:
            a = int(m.group(1), 16)
            if RDATA_LO <= a < RDATA_HI:
                tgt.add(a)
    _VPTR_STORES = sorted(tgt)
    return _VPTR_STORES


def table_slots(addr):
    """按 ctor 实写的表起始界定边界，返回槽位函数地址列表。"""
    tg = vptr_targets()
    nxt = None
    for t in tg:
        if t > addr:
            nxt = t
            break
    end = nxt if nxt else min(addr + 0x400, RDATA_HI)
    slots = []
    for a in range(addr, end, 4):
        v = rd32(a)
        if v is None:
            break
        if TEXT_LO <= v < TEXT_HI:
            slots.append(v)
        else:
            break
    return slots, end


# ---- 对账 ------------------------------------------------------------------
def reconcile_vtable(S, addr):
    slots, end = table_slots(addr)
    owners = [c for c, d in S.items()
              if any(norm_va(v.get('addr')) == addr for v in (d.get('vtables') or []))]
    slotinfo = []
    for sv in slots:
        hits, req = this_offsets(sv)
        slotinfo.append({'va': '0x%08X' % sv, 'n_this_access': len(hits) if hits else 0,
                         'req': req, 'offsets': sorted({o for o, _, _ in (hits or [])})})
    reqs = [s['req'] for s in slotinfo if s['req']]
    total_req = max(reqs) if reqs else 0
    res = {'vtable': '0x%08X' % addr, 'declared_owner': owners,
           'n_slots': len(slots), 'end': '0x%08X' % end,
           'total_req': total_req, 'slots': slotinfo, 'verdict': {}, 'candidates': []}
    for c in owners:
        bs = S[c].get('binary_size') or 0
        if total_req > bs:
            res['verdict'][c] = 'IMPOSSIBLE (req %d > binary_size %d)' % (total_req, bs)
        else:
            res['verdict'][c] = 'consistent (req %d <= binary_size %d)' % (total_req, bs)
    # 候选打分：**最具体假设** —— 访问偏移精确命中成员偏移的比例，
    # 同比例时**取 binary_size 最小者**（成员多的类会平凡地"覆盖一切"）。
    all_off = sorted({o for s in slotinfo for o in s['offsets']})
    if all_off:
        scored = []
        for c, d in S.items():
            bs = d.get('binary_size') or 0
            if bs < total_req:
                continue
            exact = set()
            for k in chain(S, c):
                for offs in (S[k].get('known_members') or {}):
                    try:
                        exact.add(int(offs))
                    except Exception:
                        pass
            cov = sum(1 for o in all_off if o in exact)
            scored.append({'class': c, 'binary_size': bs,
                           'exact_member_hits': cov, 'n_off': len(all_off),
                           'ratio': round(cov / len(all_off), 3)})
        scored.sort(key=lambda x: (-x['ratio'], x['binary_size']))
        res['candidates'] = scored[:6]
    return res


def vptr_installs():
    """{vtable_addr: [安装点 VA, ...]} —— 全量扫描 `movl $0x5xxxxx,(%reg)`。

    这是**唯一**与 annotation 无关的"表 → ctor/dtor"证据：ctor 与 dtor 都会写自己的
    vptr，所以同一张表通常有 2 个安装点，且落在**相邻函数**里（ctor 紧邻 dtor）。
    """
    res = {}
    pat = re.compile(r'movl?\s+\$0x([0-9a-f]{6,8}),(?:0x([0-9a-f]+))?\((%[a-z]+)\)')
    for l in disasm(TEXT_LO, TEXT_HI).splitlines():
        if not re.match(r'\s+[0-9a-f]+:', l):
            continue
        body = l.split(':', 1)[1] if ':' in l else l
        m = pat.search(body)
        if m:
            a = int(m.group(1), 16)
            va = int(l.strip().split(':', 1)[0], 16)
            if RDATA_LO <= a < RDATA_HI:
                res.setdefault(a, []).append(va)
    return res


def owning_func(va):
    """含 va 的函数入口（用 decomp JSON 的 address/size_bytes 索引）。"""
    _load_func_index()
    for a, sz in _FUNC_SIZE.items():
        if a <= va < a + sz:
            return a
    return None


def _insn_lines():
    out = disasm(TEXT_LO, TEXT_HI)
    lines = []
    for l in out.splitlines():
        m = re.match(r'^\s*([0-9a-f]+):\t([0-9a-f ]+)\t(.*)$', l)
        if m:
            lines.append((int(m.group(1), 16), m.group(3).strip()))
    return lines


def ctor_stride(ctor_va, min_off=0):
    """**内嵌成员 stride** —— 判定 ctor 所属类尺寸的 A 级方法。

    同一个函数里若连续出现

        lea X(%reg),%ecx ; (SEH 状态标记 `mov[bwl] $imm,0xNN(%esp)`)? ; call <ctor>

    的两个成员，则 `X2 - X1 == sizeof(该类)`（成员在宿主对象里紧凑排布）。

    只接受**紧邻**的 `lea`（中间最多夹一条 SEH 状态标记）。放宽到"往回找 N 条"会借用
    前一个 `call` 的 `lea`，产出**假 stride**（实测把 548 当成了某类的尺寸）。
    返回 {stride: [(site1, site2, off1, off2), ...]}。
    """
    lines = _insn_lines()
    hits = []
    for i, (va, txt) in enumerate(lines):
        m = re.match(r'call\s+0x([0-9a-f]+)', txt)
        if not m or int(m.group(1), 16) != ctor_va:
            continue
        j = i - 1
        if j >= 0 and re.match(r'mov[bwl]?\s+\$0x[0-9a-f]+,0x[0-9a-f]+\(%esp\)$', lines[j][1]):
            j -= 1
        if j < 0:
            continue
        mm = re.match(r'lea\s+(?:0x([0-9a-f]+))?\((%[a-z]+)\),%ecx$', lines[j][1])
        if mm:
            off = int(mm.group(1), 16) if mm.group(1) else 0
            if off >= min_off:
                hits.append((va, off, mm.group(2)))
    by = {}
    for k in range(len(hits) - 1):
        if hits[k + 1][2] == hits[k][2] and hits[k + 1][1] > hits[k][1]:
            d = hits[k + 1][1] - hits[k][1]
            by.setdefault(d, []).append((hits[k][0], hits[k + 1][0], hits[k][1], hits[k + 1][1]))
    return by


def heap_size_of_ctor(ctor_va):
    """`push $IMM ; call <operator new 0x55353b> ; ... ; call <ctor>` ⇒ {size: n_sites}。

    **独立于 annotation 的 sizeof**：`new` 的实参就是完整对象尺寸。
    """
    lines = _insn_lines()
    allocs = {}
    for i, (va, t) in enumerate(lines):
        if re.match(r'call\s+0x55353b$', t) and i > 0:
            m = re.match(r'push\s+\$0x([0-9a-f]+)$', lines[i - 1][1])
            if m:
                allocs[i] = int(m.group(1), 16)
    res = {}
    for i, (va, t) in enumerate(lines):
        m = re.match(r'call\s+0x([0-9a-f]+)', t)
        if not m or int(m.group(1), 16) != ctor_va:
            continue
        for j in range(i - 1, max(-1, i - 40), -1):
            if j in allocs:
                res[allocs[j]] = res.get(allocs[j], 0) + 1
                break
    return res


# ---- 手工核验过的地面真值（A 级，见 data/status/_cleanup_vtable_class_reconcile.md）----
GROUND_TRUTH = [
    # (vtable, 正确归属, ctor, 三条独立证据)
    (0x56AC20, 'UI3DCtrl', 0x439030, 'stride 0x134=308 x2 (SaleUI::InitUI 0x5251f8/0x525208/0x525218); '
                                       'ctor this-writes 236..304, req=308; UI3DCtrl 自己的 '
                                       'LoadModel/UpdateRotation/UpdateTransform 访问同一块 228..294'),
    (0x56AD64, 'UIProgressBar', 0x43F7F0, 'new(0xF4=244) x2 -> call 0x43F7F0; stride 0xF4 (UITitle_BBTY); '
                                          'UILoadingFrm.m_LoadProgress(0x48) 声明 UIProgressBar 且 '
                                          'sizeof(UILoadingFrm)=new(0x14C=332) => 72+344>332 排除 UIButton'),
]


def run_self_test():
    """回归用例：把**手工核验过**的地面真值钉住。

    只断言工具**能证明**的东西（`IMPOSSIBLE` 判决、stride、`new` 尺寸、vptr 安装点归属），
    **不**断言 `candidates[0]` —— 候选打分只是启发式（低偏移人人命中，实测
    `_D3DCAPS9`/`ASISTAGE` 会靠 ratio 挤到榜首）。
    """
    S = load_structs()
    fails, total = [], 0

    def chk(name, ok, detail=''):
        nonlocal total
        total += 1
        print('[%s] %s %s' % ('OK' if ok else 'FAIL', name, detail))
        if not ok:
            fails.append(name)

    # ---- 证据链 1：stride 定尺寸 ----
    st = ctor_stride(0x439030)
    chk('ctor 0x439030 有 stride=308', 0x134 in st,
        'min=0x%x pairs=%s' % (min(st) if st else 0,
                               ', '.join('%s->%s 0x%x->0x%x' % (hex(x[0]), hex(x[1]), x[2], x[3])
                                         for x in st.get(0x134, [])[:2])))
    st2 = ctor_stride(0x43F7F0)
    chk('ctor 0x43F7F0 有 stride=244', 0xF4 in st2,
        'min=0x%x pairs=%s' % (min(st2) if st2 else 0,
                               ', '.join('%s->%s 0x%x->0x%x' % (hex(x[0]), hex(x[1]), x[2], x[3])
                                         for x in st2.get(0xF4, [])[:2])))

    # ---- 证据链 2：new(size) 定尺寸 ----
    hs = heap_size_of_ctor(0x43F7F0)
    chk('ctor 0x43F7F0 有 new(0xF4) x2', hs.get(0xF4) == 2,
        'sizes=%s' % {('0x%x' % k): v for k, v in hs.items()})
    chk('sizeof(UILoadingFrm)=new(0x14C)', _new_size_before_ctor(0x450710) == 0x14C)

    # ---- 证据链 3：vptr 安装点 -> ctor 归属（与 annotation 无关）----
    vi = vptr_installs()
    chk('vptr 安装点覆盖 >150 张表（rdata 上界=max(vsz,rsz)）', len(vi) > 150,
        'n=%d  0x5704A8 in? %s' % (len(vi), 0x5704A8 in vi))
    pair = {0x56AC20: 0x43F7F0, 0x56AD64: 0x43F7F0}   # 下面逐条断言，不用这个
    chk('0x56AC20 的安装点在 ctor 0x439030 内',
        any(owning_func(s) == 0x439030 for s in vi.get(0x56AC20, [])),
        'sites=%s -> %s' % ([hex(s) for s in vi.get(0x56AC20, [])],
                            [hex(owning_func(s) or 0) for s in vi.get(0x56AC20, [])]))
    chk('0x56AD64 的安装点在 ctor 0x43F7F0 内',
        any(owning_func(s) == 0x43F7F0 for s in vi.get(0x56AD64, [])),
        'sites=%s -> %s' % ([hex(s) for s in vi.get(0x56AD64, [])],
                            [hex(owning_func(s) or 0) for s in vi.get(0x56AD64, [])]))

    # ---- 不可变二进制事实（**不许编码注解状态**）----------------------------
    # 教训（独立复核 e1140ba4）: 原自检断言"0x56AC20 声明归属 UIProgressBar 被证伪"，
    # 落地后注解变了就必然 FAIL —— 那是"注解状态快照"，不是二进制回归用例。
    # 回归用例只能钉**与注解无关**的事实。
    hits, _rq = this_offsets(0x439410)
    offs = {o for o, _s, _b in (hits or [])}
    chk('0x439410 访问 this+292（4B）=> 296 > 244，故其表不属 244 字节类',
        292 in offs, 'offsets=%s' % sorted(o for o in offs if o >= 200))
    hits2, rq2 = this_offsets(0x439030)
    offs2 = {o for o, _s, _b in (hits2 or [])}
    chk('ctor 0x439030 的 this 写入最大 304 => req=308 且 %esi 全程未被改写',
        rq2 == 308 and 304 in offs2 and 300 in offs2,
        'req=%s has300=%s has304=%s' % (rq2, 300 in offs2, 304 in offs2))
    r3 = reconcile_vtable(S, 0x56AD64)
    chk('0x56AD64 槽位 req=228 <= 244 且 ctor(0x43F7F0) 实测 244 == new 实参',
        r3['total_req'] == 228 and hs.get(0xF4) == 2, 'req=%d' % r3['total_req'])
    # ICF：同一函数挂两张互不相关的表（复核 e1140ba4 发现）
    d1, d2 = rd32(0x56AD08), rd32(0x56AFBC)
    chk('0x43D920 同时是 0x56ACFC 与 0x56AFB0 的 slot3（/OPT:ICF 合并）',
        d1 == 0x43D920 and d2 == 0x43D920, '0x56AD08=%s 0x56AFBC=%s' % (hex(d1), hex(d2)))
    # cluster B 的两个成员方法语义判据（比"只碰 68..80"硬）
    callees = set()
    for (f, callee), hh in site_index()[0].items():
        pass
    lines = _insn_lines()
    calls = [va for va, t in lines
             if re.match(r'call\s+0x43dab0$', t) and 0x43D940 <= va < 0x43D940 + 400]
    chk('0x43DAB0 被 cluster B 的 Render 0x43D940 调用（>=3 次）', len(calls) >= 3,
        'sites=%s' % [hex(c) for c in calls])
    h4, _r4 = this_offsets(0x440740)
    chk('UIStatic ctor 0x440740 把 +76 写成整数 1（故 +76 是整数语义）',
        any(o == 76 for o, _s, _b in (h4 or [])), 'writes=%s' % sorted({o for o, _s, _b in (h4 or [])}))
    h5, r5 = this_offsets(0x43A770)
    hs2 = heap_size_of_ctor(0x43A770)
    st3 = ctor_stride(0x43A770)
    chk('ctor 0x43A770 new(0x158=344) x2 且 stride 0x158（UIButton/UICaption 之争的线索）',
        hs2.get(0x158) == 2 and 0x158 in st3,
        'new=%s stride_pairs=%s' % ({('0x%x' % k): v for k, v in hs2.items()},
                                    len(st3.get(0x158, []))))

    # ---- 证据链 4：0x56ACFC = UIFlexBar（真 ctor 是 0x43D830，不是 0x43D880）----
    hits, req = this_offsets(0x43D830)
    w = sorted({o for o, _, _ in (hits or [])})
    chk('ctor 0x43D830 的 this 写入 == {0,68,72,76,80} 且 req=84', w == [0, 68, 72, 76, 80] and req == 84,
        'writes=%s req=%s' % (w, req))
    uf = S.get('UIFlexBar') or {}
    own = sorted(int(k) for k in (uf.get('known_members') or {}))
    chk('UIFlexBar binary_size=84 且 own members == {0,68,72,76,80}',
        uf.get('binary_size') == 84 and own == [0, 68, 72, 76, 80],
        'bs=%s own=%s  (当前 vtables=%s methods=%d)' % (
            uf.get('binary_size'), own, [v.get('addr') for v in (uf.get('vtables') or [])],
            len(uf.get('methods') or {})))
    body = asm_lines(0x43D880, 0x43D880 + (func_size(0x43D880) or 11))
    chk('0x43D880 只是装 vptr 的 stub（无 ret，尾调基类）—— 不可用于推断尺寸',
        len(body) <= 2 and any('jmp' in b for b in body),
        'body=%s' % body)

    print('self-test: %d/%d passed' % (total - len(fails), total))
    return 0 if not fails else 1


def _new_size_before_ctor(ctor_va):
    for i, (va, t) in enumerate(_insn_lines()):
        m = re.match(r'call\s+0x([0-9a-f]+)', t)
        if m and int(m.group(1), 16) == ctor_va:
            for j in range(i - 1, max(-1, i - 40), -1):
                mm = re.match(r'push\s+\$0x([0-9a-f]+)$', _insn_lines()[j][1])
                if mm and j + 1 < len(_insn_lines()) and \
                        re.match(r'call\s+0x55353b$', _insn_lines()[j + 1][1]):
                    return int(mm.group(1), 16)
    return None


# ---- 全局审计：把 stride/new 方法从"单张表"推广到**全部已安装表** ----------------
_SITE_INDEX = None


def site_index():
    """**一次**遍历全 `.text`，抽取三类可复用事实（避免 189× 重复反汇编）：

      · `member[(func, ctor)] = [(site, off, last_new_size), ...]`
        —— `lea off(%reg),%ecx ; (SEH 标记)? ; call ctor`，即"在 func 里就地构造了一个
           ctor 类型的成员，偏移 off"（`last_new_size` = 该处之前最近一次 `new` 实参）；
      · `vptr[(func, table)] = [site, ...]` —— func 安装了这张表的 vptr；
      · `ctor_func[site] = func` —— 安装点所属函数。

    「相邻成员的偏移差 = 类尺寸」与「`new` 实参 = 类尺寸」都由它派生。
    """
    global _SITE_INDEX
    if _SITE_INDEX is not None:
        return _SITE_INDEX
    lines = _insn_lines()
    member = {}
    vptr = {}
    ctor_func = {}
    # 预扫：算子函数边界（用于把安装点归到 ctor/dtor）
    _load_func_index()
    fstarts = sorted(_FUNC_SIZE)
    import bisect

    def owner(va):
        i = bisect.bisect_right(fstarts, va) - 1
        if i >= 0 and fstarts[i] <= va < fstarts[i] + _FUNC_SIZE[fstarts[i]]:
            return fstarts[i]
        return None

    cur = None
    last_new = None
    vpat = re.compile(r'movl?\s+\$0x([0-9a-f]{6,8}),(?:0x([0-9a-f]+))?\((%[a-z]+)\)')
    for i, (va, t) in enumerate(lines):
        f = owner(va)
        if f != cur:
            cur, last_new = f, None
        if re.match(r'call\s+0x55353b$', t) and i > 0:
            m = re.match(r'push\s+\$0x([0-9a-f]+)$', lines[i - 1][1])
            if m:
                last_new = int(m.group(1), 16)
            continue
        m = vpat.search(t)
        if m:
            a = int(m.group(1), 16)
            if RDATA_LO <= a < RDATA_HI and cur is not None:
                vptr.setdefault((cur, a), []).append(va)
                ctor_func[va] = cur
            continue
        mm = re.match(r'call\s+0x([0-9a-f]+)$', t)
        if mm:
            callee = int(mm.group(1), 16)
            j = i - 1
            if j >= 0 and re.match(r'mov[bwl]?\s+\$0x[0-9a-f]+,0x[0-9a-f]+\(%esp\)$', lines[j][1]):
                j -= 1
            if j >= 0 and cur is not None:
                lm = re.match(r'lea\s+(?:0x([0-9a-f]+))?\((%[a-z]+)\),%ecx$', lines[j][1])
                if lm:
                    off = int(lm.group(1), 16) if lm.group(1) else 0
                    member.setdefault((cur, callee), []).append((va, off, last_new, lm.group(2)))
    _SITE_INDEX = (member, vptr, ctor_func)
    return _SITE_INDEX


def measured_size(ctor):
    """(min_stride, {new_size: n}) —— 该 ctor 所属类的实测尺寸证据。"""
    member, _v, _c = site_index()
    out = {}
    for (f, callee), hits in member.items():
        if callee == ctor:
            out.setdefault(f, hits)
    strides = []
    pairs = {}
    news = {}
    for f, hits in out.items():
        hits = sorted(hits, key=lambda x: x[0])
        for k in range(len(hits) - 1):
            # **必须同基址寄存器**：同一函数里两个不同宿主对象的成员构造
            # （`a.m1.Ctor(); b.m2.Ctor()`）偏移差与类尺寸无关，会产生假 stride。
            if hits[k + 1][3] != hits[k][3]:
                continue
            d = hits[k + 1][1] - hits[k][1]
            if d > 0:
                strides.append(d)
                pairs[d] = pairs.get(d, 0) + 1
        for _s, _o, n, _r in hits:
            if n:
                news[n] = news.get(n, 0) + 1
    ms = min(strides) if strides else None
    return ms, news, (pairs.get(ms, 0) if ms else 0)


def audit_all():
    """全部已安装表 × 注解声明的全局对账。返回 rows（每张表一行）。"""
    S = load_structs()
    member, vptr, _cf = site_index()
    declared = {}
    for c, d in S.items():
        for v in (d.get('vtables') or []):
            a = norm_va(v.get('addr'))
            if a:
                declared.setdefault(a, []).append(c)
    rows = []
    # 注意：`vptr` 的键是 (func, table) 元组，遍历它拿到的是元组 —— 必须先取表地址集合
    for table in sorted({t for (_f, t) in vptr}):
        ctors = {f for (f, t2) in vptr if t2 == table}
        # 去掉 dtor：选有 member 构造记录、或有 new 尺寸的那个
        best, best_ev = None, (None, {}, 0)
        for c in sorted(ctors):
            st, news, np_ = measured_size(c)
            if (st or news) and (best is None or (news and not best_ev[1])):
                best, best_ev = c, (st, news, np_)
            elif best is None:
                best, best_ev = c, (st, news, np_)
        st, news, npairs = best_ev
        ms = st if st else (min(news) if news else None)
        # 证据分级：`new` 实参是独立于 stride 的强证据；stride 需 ≥3 对才可信
        # （1~2 对可能是两个宿主对象/嵌套对象的巧合，实测 0x43bce0 给出互不一致的 272/280）
        if ms is None:
            tier = '-'
        elif news:
            tier = 'A(new)'
        elif st and npairs >= 3:
            tier = 'A(stride x%d)' % npairs
        else:
            tier = 'B(stride x%d)' % npairs
        dec = declared.get(table, [])
        dsizes = {S[c].get('binary_size') for c in dec}
        if not dec:
            verdict = 'UNASSIGNED'
        elif ms is None:
            verdict = 'NO_MEASUREMENT'
        elif ms in dsizes:
            verdict = 'SIZE_OK'
        else:
            verdict = 'SIZE_CONFLICT'
        rows.append({'table': '0x%08X' % table, 'ctors': ['0x%08X' % c for c in sorted(ctors)],
                     'measured_ctor': '0x%08X' % best if best else None,
                     'min_stride': st, 'stride_pairs': npairs, 'new_sizes': news,
                     'measured': ms, 'tier': tier,
                     'declared': dec, 'declared_size': sorted(x for x in dsizes if x),
                     'verdict': verdict})
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--vtable')
    ap.add_argument('--all', action='store_true')
    ap.add_argument('--out')
    ap.add_argument('--stride', help='ctor VA，测其类的内嵌成员 stride')
    ap.add_argument('--installs', action='store_true', help='列出 vptr 安装点统计')
    ap.add_argument('--writes', help='ctor VA，列出其 this 写入偏移（对照 known_members）')
    ap.add_argument('--self-test', action='store_true')
    ap.add_argument('--audit', action='store_true', help='全局：全部已安装表 vs 注解声明')
    ap.add_argument('--audit-out')
    a = ap.parse_args()

    if a.stride:
        c = norm_va(a.stride)
        print('ctor %s' % hex(c))
        print('  heap sizes: %s' % {('0x%x' % k): v for k, v in heap_size_of_ctor(c).items()})
        for d, ex in sorted(ctor_stride(c).items()):
            print('  stride 0x%x = %d  (%d pairs)  e.g. %s' % (
                d, d, len(ex), ', '.join('%s->%s off 0x%x->0x%x' % (hex(x[0]), hex(x[1]), x[2], x[3])
                                         for x in ex[:3])))
        return 0

    if a.installs:
        vi = vptr_installs()
        print('vptr 安装点覆盖 %d 张表' % len(vi))
        return 0

    if a.writes:
        c = norm_va(a.writes)
        hits, req = this_offsets(c)
        w = sorted({o for o, _, _ in (hits or [])})
        print('ctor %s  sz=%s  thiscall=%s  req=%d' % (hex(c), func_size(c), is_thiscall(c), req or 0))
        print('  this 写入/读取偏移: %s' % w)
        for S_ in (load_structs(),):
            for cls, d in sorted(S_.items()):
                own = set()
                for k in chain(S_, cls):
                    for offs in (S_[k].get('known_members') or {}):
                        try:
                            own.add(int(offs))
                        except Exception:
                            pass
                # **下界判据**：`req` 只是"最小所需跨度"的下界，**不能排除更大的类**
                # （复核 e1140ba4：用 `== req` 会把 UIStatic(152) 从 `0x43dab0`(req=84) 的候选里藏掉）
                if (d.get('binary_size') or 0) >= req and w and set(w) <= own:
                    print('  候选(下界判据, 不能排除更大类): %-24s binary_size=%s (own 覆盖 %d/%d)' % (
                        cls, d.get('binary_size'), len(set(w) & own), len(w)))
        return 0

    S = load_structs()
    known = []
    for c, d in S.items():
        for v in (d.get('vtables') or []):
            va = norm_va(v.get('addr'))
            if va:
                known.append(va)
    known = sorted(set(known))

    if a.self_test:
        return run_self_test()

    if a.audit:
        rows = audit_all()
        cnt = {}
        for r in rows:
            cnt[r['verdict']] = cnt.get(r['verdict'], 0) + 1
        for r in rows:
            if r['verdict'] in ('SIZE_CONFLICT', 'UNASSIGNED'):
                print('%-11s ctor=%-11s measured=%-6s %-14s declared=%-26s size=%-8s %s' % (
                    r['table'], r['measured_ctor'] or '-', r['measured'], r['tier'],
                    ','.join(r['declared']) or '(none)', r['declared_size'] or '-', r['verdict']))
        print('--- summary ---')
        for k in sorted(cnt):
            print('  %-16s %d' % (k, cnt[k]))
        at = {}
        for r in rows:
            if r['verdict'] in ('SIZE_CONFLICT', 'SIZE_OK'):
                at[r['tier'][:1]] = at.get(r['tier'][:1], 0) + 1
        print('  by tier: %s' % at)
        print('  total %d tables (installed by ctor/dtor)' % len(rows))
        if a.audit_out:
            json.dump(rows, open(a.audit_out, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
            print('written: %s' % a.audit_out)
        return 0

    targets = [norm_va(a.vtable)] if a.vtable else known
    out = []
    for t in targets:
        r = reconcile_vtable(S, t)
        out.append(r)
        bad = [c for c, v in r['verdict'].items() if v.startswith('IMPOSSIBLE')]
        top = r['candidates'][0]['class'] if r['candidates'] else '-'
        flag = '  <<< MISMATCH' if (bad or (r['declared_owner'] and top not in r['declared_owner'])) else ''
        print('%s  slots=%2d req=%4d 声明=%-28s top=%-24s%s' % (
            r['vtable'], r['n_slots'], r['total_req'],
            ','.join(r['declared_owner']) or '(none)', top, flag))
        for c, v in r['verdict'].items():
            if v.startswith('IMPOSSIBLE'):
                print('      !! %s: %s' % (c, v))
    if a.out:
        json.dump(out, open(a.out, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
        print('written: %s' % a.out)
    return 0


if __name__ == '__main__':
    sys.exit(main())