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


def main(argv):
    cmd = argv[1] if len(argv) > 1 else 'census'
    if cmd != 'census':
        print(__doc__)
        return 1
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


if __name__ == '__main__':
    sys.exit(main(sys.argv))
