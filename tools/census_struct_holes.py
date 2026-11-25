#!/usr/bin/env python3
"""census_struct_holes.py — 结构体空洞普查（W2 字段普查目标面，常备审计器）。

用户裁定（2026-11-25）：
  1. **对齐 pad 是默认**：VC6 编译器在成员间自动插的对齐填充不是空洞，
     不需要手动 _gap_ 填充，也不计入普查目标面。空洞 = 超出自然对齐
     填充的溢出部分（自然对齐语义实测与字面"4B 对齐"读法总差仅 4B——
     对抗复核 2026-11-25 #10 定谳）。
  2. **无名字豁免**：dword_/byte_/unk_ 型成员照常计入覆盖面——它们正是
     语义化欠账，不是豁免对象。（"豁免"仅指语义词+序号后缀名
     （m_pSubTab1 / m_btnPar2 / tab1 形，约 300 员）在伪语义分类时算
     语义名——那是分类器判定规则，与本普查无关。）

空洞判据（v3，含对抗复核四修）：
  - 成员间 gap = next.offset - prev_end；自然 pad = 对齐 next 成员所需
    字节数（VC6: char 族 1 / short 族 2 / 其余含指针 4 / double·__int64 8）；
    hole = gap - pad（仅溢出计洞，区间起点 = prev_end + pad）。
  - 尾洞 = 最后覆盖末端 → binary_size；先扣 struct 自身对齐取整
    （**含 bases 对齐**——gbSnow 案：基类 double 成员抬派生类对齐到 8）。
  - **已知拼写表**：Win32 ABI 定尺寸拼写（tagRECT16/tagPOINT8/_GUID16/
    ULONG 等）直接解析——GRPinput ULONG[270] 案 154 成员 16KB 伪洞根源。
  - **offset 闭合兜底**：类型仍不可估的成员用下一已知成员偏移闭合作业
    面积（注解偏移=真值，非猜测）；成员记入 meta.unresolved（欠账可见）。
  - **vptr 槽**：有 vtables 注解（多态确证）的类 [0,4) 是 vptr 槽不计洞。
  - bases 基类子对象区计覆盖；overlay 孪生（union 变体类）单列不计目标面。
  - 已注解 _gap_* 成员 = 显式填充声明，计入覆盖。

用法:
  python3 tools/census_struct_holes.py                 # 全量普查
  python3 tools/census_struct_holes.py --class RoleSystem
输出: data/status/struct_holes_20261125.json（≥4B 洞才入清单；含 _meta）
"""
import json
import re
import glob
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STRUCT_DIR = os.path.join(ROOT, 'data', 'annotations', 'structs')
OUT_PATH = os.path.join(ROOT, 'data', 'status', 'struct_holes_20261125.json')

# ---- VC6 类型尺寸/对齐（#pragma pack 默认 8，32 位指针/整型 4B） ----
_SIZE1 = {'char', 'signed char', 'unsigned char', 'int8', 'uint8', 'bool',
          'BYTE', '_BYTE', 'unchar', 'boolean', 'UINT8', 'BOOLEAN'}
_SIZE2 = {'short', 'unsigned short', '__int16', 'WORD', '_WORD', 'wchar_t',
          'int16', 'uint16', 'ATOM'}
_SIZE8 = {'__int64', 'unsigned __int64', 'double', 'LONGLONG', 'ULONGLONG',
          '_QWORD', 'long double'}
# 4B 定尺寸拼写：Win32 ABI 固定别名（ULONG 案对抗复核 #2）
_SIZE4 = {'int', 'unsigned int', 'signed int', 'long', 'unsigned long',
          'signed long', 'int32', 'uint32', 'DWORD', '_DWORD', 'uint', 'UINT',
          'UINT32', 'ULONG', 'ULONG32', 'DWORD32', 'HANDLE', 'HMODULE',
          'HINSTANCE', 'HWND', 'HDC', 'HBITMAP', 'HRESULT', 'SCODE',
          'WPARAM', 'LPARAM', 'LRESULT', 'COLORREF', 'BOOL', 'FLOAT',
          'float', 'PVOID', 'LPVOID', 'LONG', 'ULONG_PTR', 'DWORD_PTR',
          'SIZE_T', 'SSIZE_T', 'ENUMTYPE'}
# Win32 ABI 定尺寸结构
_FIXED_STRUCT = {'tagRECT': 16, 'RECT': 16, '_GUID': 16, 'GUID': 16,
                 'IID': 16, 'CLSID': 16, 'tagPOINT': 8, 'POINT': 8,
                 'tagSIZE': 8, 'SIZE': 8, 'FILETIME': 8,
                 'LARGE_INTEGER': 8, 'ULARGE_INTEGER': 8}
# 枚举名数据源 = data/annotations/enums.json（禁前缀猜——tag* 是结构前缀
# 非枚举，v3 自伤案：'tag' 入枚举正则令 tagCPKTable 4×32768 → CPK 768KB 伪洞）
_ENUMS_PATH = os.path.join(ROOT, 'data', 'annotations', 'enums.json')
_ENUM_NAMES = None    # 惰性加载


def _enum_names():
    global _ENUM_NAMES
    if _ENUM_NAMES is None:
        names = set()
        try:
            d = json.load(open(_ENUMS_PATH, encoding='utf-8'))
            names.update(d.keys())
        except Exception:
            pass
        _ENUM_NAMES = names
    return _ENUM_NAMES

_ARRAY_RX = re.compile(r'\[\s*(0x[0-9a-fA-F]+|\d+)\s*\]\s*$')
_VARIANT_KEYS = ('union', 'variants', 'oneof')
_STRUCT_KEYS = ('struct', 'layout')


def _type_table():
    """名字 → binary_size（注解结构全量）。"""
    table = {}
    for f in glob.glob(os.path.join(STRUCT_DIR, '*.json')):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        bs = d.get('binary_size')
        name = d.get('name') or os.path.basename(f)[:-5]
        if isinstance(bs, int) and bs > 0:
            table[name] = bs
    return table


def _prim_size(t):
    if '*' in t:
        return 4
    base = t.strip()
    if base in _SIZE1:
        return 1
    if base in _SIZE2:
        return 2
    if base in _SIZE8:
        return 8
    if base in _SIZE4:
        return 4
    if base in _FIXED_STRUCT:
        return _FIXED_STRUCT[base]
    if base.startswith('enum ') or base in _enum_names():
        return 4                            # 枚举：enums.json 权威（禁前缀猜）
    return None


def _inline_struct_size(entries, table, stack):
    """{'struct':[{offset,name,type},...]} 内联布局尺寸（offset 精确闭合）。"""
    end = 0
    for e in entries:
        if not isinstance(e, dict):
            continue
        off = e.get('offset', 0) or 0
        n = type_size(e.get('type'), table, stack)
        if n is None:
            return None
        end = max(end, int(off) + n)
    return end if end else None


def type_size(t, table, stack=()):
    """注解类型表达式 → 字节数。None = 不可估（调用方走 offset 闭合兜底）。"""
    if isinstance(t, dict):
        for k in _VARIANT_KEYS:
            if k in t:
                sizes = [type_size(v.get('type'), table, stack + ('U',))
                         for v in t[k] if isinstance(v, dict)]
                sizes = [s for s in sizes if s is not None]
                return max(sizes) if sizes else None
        for k in _STRUCT_KEYS:
            if k in t:
                return _inline_struct_size(t[k], table, stack + ('S',))
        if 'type' in t:                       # 嵌套包装
            return type_size(t['type'], table, stack)
        return None
    if not isinstance(t, str):
        return None
    t = t.strip()
    m = _ARRAY_RX.search(t)
    if m:
        n = int(m.group(1), 0)
        base = t[:m.start()].strip()
        el = type_size(base, table, stack)
        return el * n if el is not None else None
    p = _prim_size(t)
    if p is not None:
        return p
    if t in table:
        if t in stack:
            return 4                          # 循环引用守卫
        return table[t]
    return None


def type_align(t, table, stack=()):
    """VC6 成员对齐：char 族 1 / short 族 2 / double·__int64 8 / 其余 4。
    数组继承元素对齐；注解结构取其成员+基类最大对齐（含循环守卫）。"""
    if t in stack:
        return 4
    if isinstance(t, dict):
        for k in _VARIANT_KEYS:
            if k in t:
                als = [type_align(v.get('type'), table, stack)
                       for v in t[k] if isinstance(v, dict)]
                als = [a for a in als if a]
                return max(als) if als else 4
        for k in _STRUCT_KEYS:
            if k in t:
                als = [type_align(e.get('type'), table, stack + (t,))
                       for e in t[k] if isinstance(e, dict)]
                als = [a for a in als if a]
                return max(als) if als else 4
        if 'type' in t:
            return type_align(t['type'], table, stack)
        return 4
    if not isinstance(t, str):
        return 4
    t = t.strip()
    m = _ARRAY_RX.search(t)
    if m:
        return type_align(t[:m.start()].strip(), table, stack)
    base = t.rstrip('*').strip()
    if '*' in t:
        return 4
    if base in _SIZE1:
        return 1
    if base in _SIZE2:
        return 2
    if base in _SIZE8:
        return 8
    if base in table:
        if base in stack:
            return 4
        sub = _load_struct(base)
        if sub is not None:
            al = 1
            for off, mem in _member_list(sub, table):
                a = type_align(mem.get('type'), table, stack + (base,))
                al = max(al, a)
            for b in sub.get('bases') or []:   # 基类对齐可抬派生类对齐
                al = max(al, type_align(b.get('name'), table,
                                        stack + (base,)))
            return al
    return 4


_STRUCT_CACHE = {}


def _load_struct(name):
    if name not in _STRUCT_CACHE:
        path = os.path.join(STRUCT_DIR, name + '.json')
        _STRUCT_CACHE[name] = json.load(open(path, encoding='utf-8')) \
            if os.path.exists(path) else False
    return _STRUCT_CACHE[name] or None


def _member_list(d, table):
    """known_members → [(offset, entry)] 排序。"""
    out = []
    for k, v in (d.get('known_members') or {}).items():
        try:
            off = int(k, 16) if isinstance(k, str) else int(k)
        except ValueError:
            continue
        if isinstance(v, dict):
            out.append((off, v))
    return sorted(out, key=lambda x: x[0])


def member_end(off, mem, table):
    """成员末端（None=类型不可估，由调用方 offset 闭合）。"""
    return type_size(mem.get('type'), table)


def _overlay_twins():
    """union 变体引用的类名集合——overlay 视图类，其全跨度字节由宿主
    union 兄弟成员覆盖（tagCpkAudioOvl 案例），不计入目标面。"""
    twins = set()
    for f in glob.glob(os.path.join(STRUCT_DIR, '*.json')):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        for _, mem in _member_list(d, {}):
            t = mem.get('type')
            if isinstance(t, dict):
                for k in _VARIANT_KEYS:
                    for v in t.get(k) or []:
                        if isinstance(v, dict) and isinstance(v.get('type'), str):
                            twins.add(v['type'].split('[')[0].strip())
    return twins


def census_class(d, table, only=None):
    """→ dict（holes=[[start,end,bytes],...] 对齐 pad 已扣除）或 None。

    覆盖面 = 成员区间 ∪ bases 基类子对象区间；未知类型成员用下一已知
    成员偏移闭合（注解偏移=真值），成员记入 unresolved。
    """
    name = d.get('name') or '?'
    if only and name != only:
        return None
    bs = d.get('binary_size')
    if not isinstance(bs, int) or bs <= 0:
        return None
    mems = _member_list(d, table)
    unresolved = []
    ivals = []
    for i, (off, mem) in enumerate(mems):
        n = member_end(off, mem, table)
        if n is None or n <= 0:
            # offset 闭合兜底：下一已知成员偏移（或 binary_size）
            nxt = mems[i + 1][0] if i + 1 < len(mems) else bs
            end = min(nxt, bs)
            unresolved.append('%s@%s %s' % (
                mem.get('name') or '?', hex(off), json.dumps(mem.get('type'))[:60]))
        else:
            end = off + n
        ivals.append((off, end, type_align(mem.get('type'), table)))
    n_base = 0
    base_aligns = []
    for b in d.get('bases') or []:
        bn, boff = b.get('name'), b.get('offset', 0)
        bsz = table.get(bn)
        if bsz:
            ivals.append((int(boff), int(boff) + bsz, 4))
            base_aligns.append(type_align(bn, table))
            n_base += 1
    # vptr 槽：多态确证（vtables 注解在册）类 [0,4) 不计洞
    has_vtable = bool(d.get('vtables'))
    holes = []
    if not ivals:
        holes.append(['0x0', hex(bs), bs])
    else:
        ivals.sort()
        prev_end = 0
        for off, end, align in ivals:
            if off > prev_end:
                pad = (align - (prev_end % align)) % align
                hole = off - prev_end - pad
                if hole > 0:
                    holes.append([hex(prev_end + pad), hex(off), hole])
            prev_end = max(prev_end, end)
        # 尾洞：先扣 struct 对齐取整（成员∪基类对齐最大值）
        aligns = base_aligns + [type_align(mem.get('type'), table)
                                for _, mem in mems]
        sa = max(aligns) if aligns else 4
        tail_pad = (sa - (prev_end % sa)) % sa
        if bs > prev_end + tail_pad:
            holes.append([hex(prev_end + tail_pad), hex(bs),
                          bs - prev_end - tail_pad])
    if has_vtable:                             # vptr 槽扣除
        holes = [h for h in holes
                 if not (h[0] in ('0x0', '0') and int(h[1], 16) == 4)]
    hb = sum(h[2] for h in holes)
    if not holes or hb < 4:
        return None
    r = {'cls': name, 'size': bs, 'members': len(mems), 'bases': n_base,
         'holes': holes, 'hole_bytes': hb, 'total_holes': len(holes)}
    if unresolved:
        r['unresolved_types'] = unresolved
    if has_vtable:
        r['vptr_slot_exempt'] = True
    return r


def main():
    only = None
    if '--class' in sys.argv:
        only = sys.argv[sys.argv.index('--class') + 1]
    table = _type_table()
    twin_names = _overlay_twins()
    results = []
    for f in sorted(glob.glob(os.path.join(STRUCT_DIR, '*.json'))):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        r = census_class(d, table, only)
        if r:
            results.append(r)
    results.sort(key=lambda x: -x['hole_bytes'])
    twin_rows = [r for r in results if r['cls'] in twin_names]
    results = [r for r in results if r['cls'] not in twin_names]
    total_hb = sum(r['hole_bytes'] for r in results)
    n_unresolved = sum(len(r.get('unresolved_types') or []) for r in results)
    n_vptr = sum(1 for r in results if r.get('vptr_slot_exempt'))
    out = {'_meta': {
        'rule': 'v3 对齐感知+四修：成员间/尾部 pad（VC6 char1/short2/其余4/'
                'double8）扣除后仅溢出计洞；尾部对齐含 bases；Win32 定尺寸'
                '拼写表；未知类型 offset 闭合兜底（unresolved 记账）；多态'
                '确证类 vptr 槽 [0,4) 豁免；无名字豁免；overlay 孪生单列',
        'classes_with_holes': len(results),
        'total_hole_bytes': total_hb,
        'total_holes': sum(r['total_holes'] for r in results),
        'unresolved_type_members': n_unresolved,
        'vptr_exempt_classes': n_vptr,
        'overlay_twin_bytes': sum(r['hole_bytes'] for r in twin_rows),
        'overlay_twins': [r['cls'] for r in twin_rows],
    }}
    out.update({'classes': results})
    os.makedirs(os.path.dirname(OUT_PATH), exist_ok=True)
    json.dump(out, open(OUT_PATH, 'w', encoding='utf-8'),
              ensure_ascii=False, indent=1)
    print('-> %s' % OUT_PATH)
    print('含洞类 %d | 总空洞 %d 处 | %d KB (%.2f MB) | unresolved=%d vptr豁免=%d' % (
        len(results), out['_meta']['total_holes'],
        total_hb // 1024, total_hb / 1048576, n_unresolved, n_vptr))
    if twin_rows:
        print('overlay 孪生(单列): %s = %d KB' % (
            ','.join(r['cls'] for r in twin_rows),
            out['_meta']['overlay_twin_bytes'] // 1024))
    for r in results[:20]:
        print('  %-24s size=%-9d holes=%-3d %6d KB%s' % (
            r['cls'], r['size'], r['total_holes'], r['hole_bytes'] // 1024,
            ' (unresolved:%d)' % len(r['unresolved_types'])
            if r.get('unresolved_types') else ''))


if __name__ == '__main__':
    main()
