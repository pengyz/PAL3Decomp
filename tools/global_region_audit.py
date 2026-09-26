#!/usr/bin/env python3
"""全局变量归属审计：地址轴 census → 非重叠分区 → 锚定 → 成员化建议。

完备性方案（2026-09-27 对抗复核定稿，全文 data/status/_globals_attribution_review.md）：
  分母 = pal3/src/globals.h 全部带址 extern（当前 2,734，7 阶段方案每阶段有门禁）。
  阶段 1（本文件 `census` 子命令）：解析 + PE 节分类 + 初步 bucket（B7=rdata，余 pending）。

用法:
  python tools/global_region_audit.py census     # 产出 data/status/globals_census.json
"""
import json
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GLOBALS_H = os.path.join(ROOT, 'pal3', 'src', 'globals.h')
PAL3_EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
CENSUS_PATH = os.path.join(ROOT, 'data', 'status', 'globals_census.json')
PARTITION_PATH = os.path.join(ROOT, 'data', 'status', 'globals_partition.json')

# extern 行形态：extern <type...> <name>[K][M]; // 0xADDR（多维数组含在内）
_EXTERN_RE = re.compile(
    r'^extern\s+(?P<type>.+?)\s+(?P<name>\w+)'
    r'(?P<dims>(?:\[\d*\])+)?\s*;\s*//\s*(?P<addr>0x[0-9A-Fa-f]+)\s*$')

# 分母口径常量（完备性门禁——漂移即测试红）
DENOMINATOR = 2734

# 基型字节数（size_bytes 估算用；未知基型 → None）
_BASE_SIZES = {
    'int': 4, 'unsigned int': 4, 'long': 4, 'unsigned long': 4, 'float': 4,
    'BOOL': 4, 'DWORD': 4, 'UINT': 4, 'LONG': 4, 'char': 1, 'BYTE': 1,
    'unsigned char': 1, 'signed char': 1, 'short': 2, 'unsigned short': 2,
    'WORD': 2, 'bool': 1, '__int64': 8, 'unsigned __int64': 8,
    'double': 8, 'void *': 4, 'LPCSTR': 4, 'LPSTR': 4, 'const char *': 4,
    'CHAR': 1, 'WCHAR': 2,
}


def _parse_globals_json(path=None):
    """data/annotations/globals.json → {addr_int: entry}（交叉字段源）。"""
    path = path or os.path.join(ROOT, 'data', 'annotations', 'globals.json')
    if not os.path.exists(path):
        return {}
    raw = json.load(open(path, encoding='utf-8'))
    out = {}
    for k, v in raw.items():
        try:
            out[int(k, 16)] = v
        except (ValueError, TypeError):
            continue
    return out


def _size_bytes(type_text, dims):
    """已知基型 × 维度积 → 字节；[] 无长度或未知基型 → None（保守）。"""
    if not dims:
        return None
    base = type_text.strip()
    unit = _BASE_SIZES.get(base)
    if unit is None:
        return None
    n = 1
    for d in dims:
        if d is None:
            return None
        n *= d
    return unit * n


def parse_globals_h(path=GLOBALS_H):
    """解析全部带址 extern。数组形态（[N]/[]）必须覆盖——它们占分母的 754 行。

    返回按地址升序的 entry 列表：{addr, name, type, array}。
    array: 元素数 int；无长度数组 None；标量 None。
    """
    entries = []
    for ln in open(path, encoding='utf-8', errors='replace'):
        m = _EXTERN_RE.match(ln.rstrip('\n'))
        if not m:
            continue
        dims = [int(d) if d else None
                for d in re.findall(r'\[(\d*)\]', m.group('dims') or '')]
        entries.append({
            'addr': int(m.group('addr'), 16),
            'name': m.group('name'),
            'type': m.group('type').strip(),
            'array': dims[0] if dims else None,
            'dims': dims if dims else None,
        })
    entries.sort(key=lambda e: e['addr'])
    return entries


def load_pe_sections(exe_path=PAL3_EXE):
    """PE 节表：[{name, va, vsz, rsz, roff}]（va 为含 imagebase 的 VA）。"""
    data = open(exe_path, 'rb').read()
    e_lfanew = struct.unpack_from('<I', data, 0x3C)[0]
    nsec = struct.unpack_from('<H', data, e_lfanew + 6)[0]
    optsz = struct.unpack_from('<H', data, e_lfanew + 20)[0]
    sect = e_lfanew + 24 + optsz
    imagebase = struct.unpack_from('<I', data, e_lfanew + 24 + 28)[0]
    secs = []
    for s in range(nsec):
        h = sect + s * 40
        nm = data[h:h + 8].rstrip(b'\0').decode('ascii', 'replace')
        vsz, vaddr, rsz, roff = struct.unpack_from('<IIII', data, h + 8)
        secs.append({'name': nm, 'va': imagebase + vaddr, 'vsz': vsz,
                     'rsz': rsz, 'roff': roff})
    return secs


def classify_section(addr, secs):
    """三类判定：初始化 .data（raw 覆盖内）/ BSS（.data 虚拟区内 raw 外）/ .rdata。"""
    for s in secs:
        if not (s['va'] <= addr < s['va'] + s['vsz']):
            continue
        in_raw = (addr - s['va']) < s['rsz']
        if s['name'] == '.data':
            return 'data_init' if in_raw else 'bss'
        if s['name'] == '.rdata':
            return 'rdata'
        return 'other'
    return 'other'


def build_census(globals_h=GLOBALS_H, exe_path=PAL3_EXE):
    """阶段 1 census：分母全量行 + PE 节分类 + 初步 bucket + 注解交叉。确定性输出。"""
    import hashlib
    secs = load_pe_sections(exe_path)
    ann = _parse_globals_json()
    rows = []
    for e in parse_globals_h(globals_h):
        sec = classify_section(e['addr'], secs)
        bucket = 'B7' if sec == 'rdata' else 'pending'
        av = ann.get(e['addr'])
        anno_name = av.get('name') if av else None
        rows.append({
            'addr': e['addr'],
            'name': e['name'],
            'type': e['type'],
            'array': e['array'],
            'dims': e['dims'],
            'size_bytes': _size_bytes(e['type'], e['dims']),
            'section': sec,
            'bucket': bucket,
            'evidence_refs': [],
            'in_annotations': av is not None,
            'anno_skip': bool(av and av.get('type') == 'skip'),
            # 名字一致性：两侧都有名时比对（anno 无名视为一致不告警）
            'anno_name_matches': (anno_name == e['name']) if av is not None else True,
        })
    md5 = lambda p: hashlib.md5(open(p, 'rb').read()).hexdigest()
    return {
        '_meta': {
            'denominator': len(rows),
            'globals_h': os.path.relpath(globals_h, ROOT),
            'md5_globals_h': md5(globals_h),
            'md5_pal3_exe': md5(exe_path),
            'note': '阶段 1 census；bucket 细分见后续阶段',
        },
        'rows': rows,
    }


def _load_class_sizes():
    """类名 → 字节尺寸：ida_structs 的 IDB UDT size 优先，structs 注解 binary_size 兜底。"""
    sizes = {}
    ida_path = os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json')
    if os.path.exists(ida_path):
        ida = json.load(open(ida_path, encoding='utf-8'))
        for sname, sinfo in ida.items():
            if sname.startswith('_'):
                continue
            sz = sinfo.get('size', 0)
            if sz:
                sizes[sname] = int(sz)
    sdir = os.path.join(ROOT, 'data', 'annotations', 'structs')
    if os.path.isdir(sdir):
        for fn in sorted(os.listdir(sdir)):
            if not fn.endswith('.json'):
                continue
            d = json.load(open(os.path.join(sdir, fn), encoding='utf-8'))
            cls = d.get('name') or fn[:-5]
            sz = d.get('binary_size')
            if sz and cls not in sizes:
                sizes[cls] = int(sz)
    return sizes


def class_size(cls):
    return _load_class_sizes().get(cls)


def _vtable_to_class_map():
    """vtable 地址 → 类名（data/annotations/structs/*.json 的 vtables[].addr）。"""
    m = {}
    sdir = os.path.join(ROOT, 'data', 'annotations', 'structs')
    for fn in sorted(os.listdir(sdir)):
        if not fn.endswith('.json'):
            continue
        d = json.load(open(os.path.join(sdir, fn), encoding='utf-8'))
        cls = d.get('name') or fn[:-5]
        for vt in d.get('vtables', []) or []:
            va = vt.get('addr')
            if va:
                m.setdefault(int(va, 16) if isinstance(va, str) else va, cls)
    return m


_SELF_CTOR_RE = re.compile(r'\b(\w+)::\1\(\s*&?([A-Za-z_]\w*)')
_ATEXIT_RE = re.compile(r'atexit\(\s*(\w+)\s*\)')


def scan_singleton_triplets(decomp_dir=None):
    """E 类：函数内静态对象的三元组（guard&1 + Cls::Cls(&global) + atexit）。

    证据形态（CCBStage::DoTask 实例）：
        if ( (g_nCBRoleHitTable[0] & 1) == 0 ) {
            gbMatrix4::gbMatrix4(&stru_17AB828);
            atexit(nullsub_37);
        }
    ctor 首参 &global 的名字必须能在 census 分母里对到地址（局部变量跳过）。
    返回 [{global_name, global_addr, class, atexit_target, func_file}]。
    """
    decomp_dir = decomp_dir or os.path.join(ROOT, 'asm', 'pal3', 'decomp')
    census_names = {r['name']: r['addr'] for r in build_census()['rows']}
    out = []
    for fn in sorted(os.listdir(decomp_dir)):
        if not fn.endswith('.json'):
            continue
        try:
            d = json.load(open(os.path.join(decomp_dir, fn), encoding='utf-8'))
        except Exception:
            continue
        body = d.get('decompiled_c', '')
        if 'atexit(' not in body:
            continue
        atexit_target = None
        ma = _ATEXIT_RE.search(body)
        if ma:
            atexit_target = ma.group(1)
        for m in _SELF_CTOR_RE.finditer(body):
            cls, gname = m.group(1), m.group(2)
            addr = census_names.get(gname)
            if addr is None:
                continue          # 局部变量/未知名——非全局静态
            out.append({'global_name': gname, 'global_addr': addr,
                        'class': cls, 'atexit_target': atexit_target,
                        'func_file': fn})
    # 同名去重（多函数初始化同一静态：取首个）
    dedup = {}
    for t in out:
        dedup.setdefault(t['global_name'], t)
    return sorted(dedup.values(), key=lambda t: t['global_addr'])


def scan_xcu_initializers(exe_path=PAL3_EXE):
    """D 类：动态初始化/析构的二进制指纹（thunk 三元组，2026-09-27 实证形态）。

    g_palScript 样本（0x4086C0/0x4086D0/0x4086E0 三连）：
        mov ecx, 0xc10968 ; jmp ctor        ← 初始化 thunk（ Placement ctor 转发）
        push 0x4086e0 ; call 0x553041 ; pop ecx ; ret   ← atexit 注册桩
        mov ecx, 0xc10968 ; jmp dtor        ← 析构 thunk
    检测链：
      A) atexit 注册桩指纹 `push imm32; call CRT_HELPER; pop ecx; ret`
         （CRT_HELPER 取同形态 call 目标的众数，0x553041 实证）→ callback 地址
      B) callback 体 = `mov ecx, <全局>; jmp <dtor>` ⇒ 全局地址 + 析构目标
      C) 类身份 = dtor 体开头写自身 vtable（mov dword ptr [ecx], imm ∈ .rdata）
         经 vtables 注解反解
    另收直呼形态 `mov ecx, <全局>; call <目标>` 且【目标体写自身 vtable】
    （无 vtable 写 = 普通方法调用，剔除——此前 47 伪站点即此污染）。
    返回 [{global_addr, target, vtable, class, via}]。
    """
    import capstone
    import hashlib
    secs = load_pe_sections(exe_path)
    text = [s for s in secs if s['name'] == '.text'][0]
    data_sec = [s for s in secs if s['name'] == '.data'][0]
    rd = [s for s in secs if s['name'] == '.rdata'][0]
    data = open(exe_path, 'rb').read()
    code = data[text['roff']:text['roff'] + text['rsz']]
    base = text['va']
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def rdata_va(x):
        return rd['va'] <= x < rd['va'] + rd['rsz']

    # A) atexit 注册桩：68 imm32 / E8 rel32 / 59 / C3
    atexit_calls = {}
    callbacks = []
    for i, ins in enumerate(md.disasm(code, base)):
        if ins.mnemonic != 'push' or not ins.op_str.startswith('0x'):
            continue
        win = code[ins.address - base: ins.address - base + 12]
        if len(win) < 12 or win[0] != 0x68:
            continue
        cb = struct.unpack_from('<I', win, 1)[0]
        if win[5] != 0xE8:
            continue
        rel = struct.unpack_from('<i', win, 6)[0]
        callee = ins.address + 5 + rel
        nxt = win[10:12]
        if nxt != b'\x59\xc3':
            continue
        atexit_calls[callee] = atexit_calls.get(callee, 0) + 1
        callbacks.append((ins.address, cb, callee))
    helper = max(atexit_calls, key=atexit_calls.get) if atexit_calls else None

    # B) thunk 体解析：B9 imm32 (global) + E9 rel32 (jmp target)
    def thunk_body(addr):
        off = addr - base
        if off < 0 or off + 6 > len(code) or code[off] != 0xB9 or code[off+5] != 0xE9:
            return None
        g = struct.unpack_from('<I', code, off + 1)[0]
        rel = struct.unpack_from('<i', code, off + 6)[0]
        tgt = addr + 10 + rel
        return g, tgt

    _VTBL_STORE = re.compile(r'^dword ptr \[\w+\], 0x([0-9A-Fa-f]+)')

    def first_vtable_store(addr, max_insns=16):
        off = addr - base
        if off < 0:
            return None
        for k, ci in enumerate(md.disasm(code[off:off + 96], addr)):
            if k >= max_insns:
                break
            # dtor/ctor 的 vtable 写可经任意寄存器（PalScript dtor 用 [esi]；
            # SEH 序言的 fs:[0]/[esp+..] 无 imm 不误报）
            mvt = _VTBL_STORE.match(ci.op_str) if ci.mnemonic == 'mov' else None
            if mvt:
                vt = int(mvt.group(1), 16)
                return vt if rdata_va(vt) else None
        return None

    vt2cls = _vtable_to_class_map()
    sites = []
    seen = set()

    def emit(gaddr, target, via):
        key = (gaddr, target, via)
        if key in seen:
            return
        seen.add(key)
        vt = first_vtable_store(target)
        sites.append({'global_addr': gaddr, 'target': target,
                      'vtable': vt, 'class': vt2cls.get(vt) if vt else None,
                      'via': via})

    for addr, cb, callee in callbacks:
        if helper is not None and callee != helper:
            continue
        body = thunk_body(cb)
        if body:
            g, dtor = body
            if data_sec['va'] <= g < data_sec['va'] + data_sec['vsz']:
                emit(g, dtor, 'atexit_thunk')
    # 直呼形态：mov ecx,imm + call target 且目标体写自身 vtable（非方法调用）
    insns = list(md.disasm(code, base))
    for i, ins in enumerate(insns):
        if not (ins.mnemonic == 'mov' and ins.op_str.startswith('ecx, 0x')):
            continue
        try:
            g = int(ins.op_str.split(', ')[1], 16)
        except (ValueError, IndexError):
            continue
        if not (data_sec['va'] <= g < data_sec['va'] + data_sec['vsz']):
            continue
        for j in range(i + 1, min(i + 4, len(insns))):
            if insns[j].mnemonic == 'call':
                try:
                    tgt = int(insns[j].op_str, 16)
                except ValueError:
                    break
                if first_vtable_store(tgt) is not None:
                    emit(g, tgt, 'direct_call')
                break
            if insns[j].mnemonic in ('ret', 'jmp'):
                break
    sites.sort(key=lambda s: (s['global_addr'], s['target']))
    return sites


def collect_evidence_anchors():
    """E/D 证据锚并入统一形态（与容器锚同结构），类尺寸可解者才产出。"""
    sizes = _load_class_sizes()
    census_names = {r['name']: r['addr'] for r in build_census()['rows']}
    anchors = []
    for t in scan_singleton_triplets():
        sz = sizes.get(t['class'])
        if not sz:
            continue
        anchors.append({'base': t['global_addr'], 'end': t['global_addr'] + sz,
                        'name': t['global_name'], 'type': t['class'],
                        'evidence': 'E:singleton:%s' % t['func_file']})
    for s in scan_xcu_initializers():
        nm = None
        for r_name, r_addr in census_names.items():
            if r_addr == s['global_addr']:
                nm = r_name
                break
        if nm is None:
            nm = 'g_xcu_%08X' % s['global_addr']
        cls = s.get('class')
        sz = sizes.get(cls) if cls else None
        anchors.append({'base': s['global_addr'],
                        'end': s['global_addr'] + (sz or 4),
                        'name': nm, 'type': cls or 'int',
                        'evidence': 'D:xcu:target_%X' % s['target']})
    return anchors


def merge_anchors(base_anchors, evidence_anchors):
    """容器锚 ∪ 证据锚：按名去重（容器锚优先），证据锚带 evidence 字段。"""
    seen = {a['name'] for a in base_anchors}
    merged = [dict(a) for a in base_anchors]
    for a in evidence_anchors:
        if a['name'] not in seen:
            merged.append(a)
            seen.add(a['name'])
    merged.sort(key=lambda a: (a['base'], -a['end'], a['name']))
    return merged


def collect_anchor_containers():
    """容器锚收集：globals.json 条目 type 命中 IDB UDT size 者 + 结构数组整体跨度。

    【与 stage4 并非同源——2026-09-27 复核修正】stage4 的 struct_instances
    （pipeline/gen/data.py:112,163-188）取 ida_structs['_globals']（2,621 条，
    含无注解幽灵锚 aShock/aBink/unk_C05F30/byte_D8C2B8 等 76 条源条目）；
    本函数取 data/annotations/globals.json（1,306 条）——是 ida 侧 76 条源的
    38 条子集，刻意排除无注解幽灵锚（byte_D8C2B8 GRPinput 10,584B 与
    g_ScriptSystemData 真部分重叠，纳入即触发 B9）。阶段 3 引入 E/D 锚后
    必须全量重跑分区并重估幽灵锚的锚定资格。

    返回按 (base, -end, name) 排序的锚列表。
    """
    ann = _parse_globals_json()
    ida_structs = json.load(open(
        os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json'), encoding='utf-8'))
    struct_sizes = {
        sname: sinfo.get('size', 0)
        for sname, sinfo in ida_structs.items()
        if not sname.startswith('_') and sinfo.get('size', 0)
    }
    anchors = []
    for addr_str, ginfo in ann.items():
        gtype = ginfo.get('type', '')
        gname = ginfo.get('name', '')
        if not gname or not gtype or gtype == 'skip':
            continue
        try:
            # _parse_globals_json 的键已是 int；容忍字符串键（与 data.py 同防御）
            base = int(addr_str, 16) if isinstance(addr_str, str) else int(addr_str)
        except (ValueError, TypeError):
            continue
        if gtype in struct_sizes:
            anchors.append({'base': base, 'end': base + struct_sizes[gtype],
                            'name': gname, 'type': gtype})
        else:
            m = re.match(r'^(\w+)\[(\d+)\]$', gtype)
            if m:
                elem_type, count = m.group(1), int(m.group(2))
                elem_size = struct_sizes.get(elem_type, 0)
                if elem_size:
                    anchors.append({'base': base, 'end': base + elem_size * count,
                                    'name': gname, 'type': gtype})
    anchors.sort(key=lambda a: (a['base'], -a['end'], a['name']))
    return anchors


def build_partition(anchors):
    """非重叠分区树（复核报告 §3.3；v2 修 S1/S3/S4）。

    语义：
    - 顶层区间互不重叠；包含关系 → 成员挂【最紧包含者】（成员可嵌套，S4）；
    - 部分重叠/相同 extent → 双方冻结进 conflicts（B9，只报警不自动改）；
    - 冻结区间持续参与后续 overlap 判定（S1：链式重叠的第三方也被冻结，
      不得无声顶层化——B9 安全网不漏报）；
    - 顶层被冻结时其成员随父挂起（S3：conflicts kind=parent_frozen）；
    - 包含吸收与到达顺序无关（后到的大锚吸收先到的顶层，§3.3 规则 1）。
    确定性：输出各列表均排序。
    """
    # 区间状态：{name: {'base','end','type','state','parent'}}
    # state: 'top' | 'member' | 'frozen'
    ivs = {}
    conflicts = []
    frozen_conflict = set()

    def _overlaps(a, b):
        return a['base'] < b['end'] and b['base'] < a['end']

    for a in sorted(anchors, key=lambda x: (x['base'], -x['end'], x['name'])):
        if a['name'] in ivs:
            continue
        rel = {}   # name -> (kind, iv)
        for nm, iv in ivs.items():
            identical = a['base'] == iv['base'] and a['end'] == iv['end']
            i_contains = a['base'] <= iv['base'] and a['end'] >= iv['end']
            iv_contains = iv['base'] <= a['base'] and iv['end'] >= a['end']
            if identical:
                kind = 'identical'
            elif i_contains:
                kind = 'contains'
            elif iv_contains:
                kind = 'contained'
            elif _overlaps(a, iv):
                kind = 'partial'
            else:
                continue
            rel[nm] = (kind, iv)
        clashes = [(nm, iv) for nm, (k, iv) in rel.items()
                   if k in ('partial', 'identical')]
        hosts = [(nm, iv) for nm, (k, iv) in rel.items() if k == 'contained']
        absorbs = [(nm, iv) for nm, (k, iv) in rel.items() if k == 'contains']
        if clashes:
            for nm, iv in clashes:
                conflicts.append({'name': a['name'], 'base': a['base'],
                                  'end': a['end'], 'with': nm, 'kind': iv['state']})
                frozen_conflict.add(a['name'])
                if iv['state'] == 'top':
                    conflicts.append({'name': nm, 'base': iv['base'],
                                      'end': iv['end'], 'with': a['name'],
                                      'kind': iv['state']})
                    frozen_conflict.add(nm)
            # 顶层被冻结 ⇒ 其成员随父挂起（S3）：转入 frozen 态，
            # 不再出现在 members（dangling parent 指向已不存在的顶层）
            for nm, iv in list(ivs.items()):
                if iv['state'] == 'member' and iv.get('parent') in frozen_conflict:
                    conflicts.append({'name': nm, 'base': iv['base'],
                                      'end': iv['end'],
                                      'with': iv.get('parent'),
                                      'kind': 'parent_frozen'})
                    frozen_conflict.add(nm)
                    iv['state'] = 'frozen'
            for nm, iv in clashes:
                if iv['state'] == 'top':
                    ivs[nm]['state'] = 'frozen'
            ivs[a['name']] = {'base': a['base'], 'end': a['end'],
                              'type': a['type'], 'state': 'frozen',
                              'parent': None}
            continue
        ivs[a['name']] = {'base': a['base'], 'end': a['end'], 'type': a['type'],
                          'state': 'top', 'parent': None}
        # 包含吸收：被本锚包含的既有区间降为本锚的成员（S4：挂最紧者）
        for nm, iv in sorted(absorbs, key=lambda x: -(x[1]['end'] - x[1]['base'])):
            ivs[nm]['state'] = 'member'
            ivs[nm]['parent'] = a['name']
        # 宿主选择：最紧包含者（top/member 皆可，S4）
        if hosts:
            nm, iv = min(hosts, key=lambda x: (x[1]['end'] - x[1]['base'], x[0]))
            ivs[a['name']]['state'] = 'member'
            ivs[a['name']]['parent'] = nm

    top_levels = [{'base': v['base'], 'end': v['end'], 'name': nm, 'type': v['type']}
                  for nm, v in ivs.items() if v['state'] == 'top']
    members = [{'base': v['base'], 'end': v['end'], 'name': nm, 'type': v['type'],
                'parent': v['parent']}
               for nm, v in ivs.items() if v['state'] == 'member']
    seen_c = set()
    conflicts_out = []
    for c in sorted(conflicts, key=lambda c: (c['name'], c['base'], c['with'])):
        key = (c['name'], c['base'], c['with'], c['kind'])
        if key in seen_c:
            continue
        seen_c.add(key)
        conflicts_out.append(c)
    return {'top_levels': top_levels, 'members': members,
            'conflicts': conflicts_out}


def update_census_buckets(census, partition):
    """分区结果回写 census bucket：容器基址→B1、容器内→B2、冲突→B9。"""
    tops = partition['top_levels']
    member_names = {m['name'] for m in partition['members']}
    conflict_names = {c['name'] for c in partition['conflicts']}
    for r in census['rows']:
        if r['name'] in conflict_names:
            r['bucket'] = 'B9'
            continue
        host = None
        for t in tops:
            if t['base'] <= r['addr'] < t['end']:
                host = t
                break
        if host is None:
            continue
        if r['addr'] == host['base']:
            r['bucket'] = 'B1'
            r['evidence_refs'].append('container:%s' % host['name'])
        else:
            r['bucket'] = 'B2'
            r['evidence_refs'].append('inside:%s+0x%X' % (host['name'],
                                                          r['addr'] - host['base']))
    return census


def main(argv):
    cmd = argv[1] if len(argv) > 1 else 'census'
    if cmd == 'census':
        census = build_census()
        with open(CENSUS_PATH, 'w', encoding='utf-8', newline='') as f:
            json.dump(census, f, ensure_ascii=False, indent=1)
        from collections import Counter
        by_sec = Counter(r['section'] for r in census['rows'])
        by_bucket = Counter(r['bucket'] for r in census['rows'])
        print('census -> %s' % os.path.relpath(CENSUS_PATH, ROOT))
        print('分母: %d（口径常量 %d）' % (census['_meta']['denominator'], DENOMINATOR))
        if census['_meta']['denominator'] != DENOMINATOR:
            print('[!] 分母漂移——口径常量 DENOMINATOR 需人工确认后更新')
        print('section:', dict(by_sec))
        print('bucket:', dict(by_bucket))
        assert sum(by_bucket.values()) == census['_meta']['denominator']
        return 0
    if cmd == 'partition':
        anchors = collect_anchor_containers()
        ev = collect_evidence_anchors()
        merged = merge_anchors(anchors, ev)
        p = build_partition(merged)
        with open(PARTITION_PATH, 'w', encoding='utf-8', newline='') as f:
            json.dump({'_meta': {'container_anchors': len(anchors),
                                 'evidence_anchors': len(ev)},
                       **p},
                      f, ensure_ascii=False, indent=1)
        # 分区结果回写 census
        census = build_census()
        update_census_buckets(census, p)
        with open(CENSUS_PATH, 'w', encoding='utf-8', newline='') as f:
            json.dump(census, f, ensure_ascii=False, indent=1)
        from collections import Counter
        print('anchors: container=%d evidence=%d merged=%d' % (
            len(anchors), len(ev), len(merged)))
        print('top_levels: %d  members: %d  conflicts: %d' % (
            len(p['top_levels']), len(p['members']), len(p['conflicts'])))
        print('bucket:', dict(Counter(r['bucket'] for r in census['rows'])))
        # 门禁：顶层零重叠
        tops = sorted(p['top_levels'], key=lambda t: t['base'])
        for a, b in zip(tops, tops[1:]):
            assert a['end'] <= b['base'], (a['name'], b['name'])
        if p['conflicts']:
            print('conflicts:')
            for c in p['conflicts'][:10]:
                print('  ', c)
        print('partition -> %s' % os.path.relpath(PARTITION_PATH, ROOT))
        return 0
    print(__doc__)
    return 1


if __name__ == '__main__':
    sys.exit(main(sys.argv))
