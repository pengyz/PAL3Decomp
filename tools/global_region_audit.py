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
        p = build_partition(anchors)
        with open(PARTITION_PATH, 'w', encoding='utf-8', newline='') as f:
            json.dump({'_meta': {'anchors': len(anchors)}, **p},
                      f, ensure_ascii=False, indent=1)
        # 分区结果回写 census
        census = build_census()
        update_census_buckets(census, p)
        with open(CENSUS_PATH, 'w', encoding='utf-8', newline='') as f:
            json.dump(census, f, ensure_ascii=False, indent=1)
        from collections import Counter
        print('anchors: %d' % len(anchors))
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
