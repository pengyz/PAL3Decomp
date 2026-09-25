#!/usr/bin/env python3
"""函数级字节 diff 检视器：编译产物 vs 原始二进制，逐函数并排对照。

用法:
  python tools/fdiff.py <unit.cpp 路径或子串> <函数名子串或 mangled 名>
  python tools/fdiff.py pal3/src/Misc/AStarPathFinder.cpp FindInOpen

输出: 双侧十六进制 + capstone 反汇编并排（按函数入口对齐），差异行标注 `<>`；
reloc 字节标注 `[r]`（与 compare_pal3 的 reloc_skipped 同语义）。

数据源:
  - 我方: data/obj 产物（compare_pal3 的稳定哈希名），经
    gbengine_compare.parse_coff_obj 提取（与 n_diff 计数同源）
  - 二进制: original/PAL3.exe .text 切片（VA → 文件偏移，R8 边界语义）
管线工具（tools/，复用）。
"""
import hashlib, json, os, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'pipeline'))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import probe_compile as pc                                    # noqa: E402
from compare_pal3 import exe_text_image                       # noqa: E402
import gbengine_compare as gc                                 # noqa: E402

OBJ_DIR = pc.OBJ_DIR
DETAIL = os.path.join(ROOT, 'data', 'status', 's4_diff_detail.json')

try:
    import capstone
    _md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
except ImportError:
    _md = None


def _load_detail_row(unit_sub, fn_sub):
    """返回 (unit, row)。精确名匹配优先；子串命中多于一个时列出让用户消歧。"""
    d = json.load(open(DETAIL, encoding='utf-8'))
    exact, hits = None, []
    for u, rows in d['units'].items():
        if unit_sub not in u:
            continue
        for fn in rows:
            hay = fn.get('name', '') + ' ' + fn.get('symbol', '')
            if fn_sub.lower() in hay.lower():
                hits.append((u, fn))
                if fn.get('name', '') == fn_sub or fn.get('symbol', '') == fn_sub:
                    exact = (u, fn)
    if exact:
        return exact
    if len(hits) == 1:
        return hits[0]
    if not hits:
        print('[fdiff] no detail row for (%r, %r)' % (unit_sub, fn_sub))
        return None, None
    print('[fdiff] %d candidate rows for %r — refine the name:' % (len(hits), fn_sub))
    for u, fn in hits[:10]:
        print('   %s  %s' % (u, fn.get('name')))
    return None, None


def _ours_bytes(unit, row):
    obj_path = os.path.join(OBJ_DIR, 's4_%s.obj' % hashlib.md5(unit.encode('utf-8')).hexdigest()[:8])
    if not os.path.exists(obj_path):
        print('[fdiff] obj artifact missing: %s\n'
              '  产物随 match 运行重新生成 —— 先跑 `python pipeline/cli.py match`。' % obj_path)
        return None, None
    funcs = gc.parse_coff_obj(obj_path)
    info = funcs.get(row.get('symbol', ''))
    if not info:
        print('[fdiff] symbol %r not in obj (functions=%d)' % (row.get('symbol'), len(funcs)))
        return None, None
    return obj_path, info


def _disasm(blob, base):
    if not _md:
        return None
    out = []
    for ins in _md.disasm(blob, base):
        out.append((ins.address - base, ins.bytes.hex(),
                    '%s %s' % (ins.mnemonic, ins.op_str)))
    else:
        if sum(len(h) for _, h, _ in out) // 2 < len(blob):
            out.append((-1, '', '[capstone 停止@+%d，剩余 %d 字节不可解码]'
                        % (sum(len(h) for _, h, _ in out) // 2, len(blob) - sum(len(h) for _, h, _ in out) // 2)))
    return out


def _hexline(blob):
    return ' '.join('%02x' % b for b in blob)


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return
    unit_sub, fn_sub = sys.argv[1], sys.argv[2]
    if not os.path.exists(DETAIL):
        print('[fdiff] missing %s — run `python pipeline/cli.py match` first' % DETAIL)
        return
    u, row = _load_detail_row(unit_sub, fn_sub)
    if not row:
        return
    obj_path, info = _ours_bytes(u, row)
    if info is None:
        return
    ours = info['bytes'][:int(row.get('size', 0))] if row.get('size') else info['bytes']
    relocs = set(info.get('relocs', ()))

    imgbase, text, text_rva, tsz = exe_text_image()
    va = int(row['va'], 16)
    off = va - imgbase - text_rva
    if off < 0 or off + len(ours) > tsz:
        print('[fdiff] ORIG slice out of .text bounds: off=%d len=%d tsz=%d' % (off, len(ours), tsz))
        return
    orig = text[off:off + len(ours)]

    print('== %s ==\n    %s\n    VA %s  size %d (ours %d)  n_diff %s  first_diff %s\n'
          % (row.get('name'), row.get('symbol'), row['va'], row.get('size'),
             len(ours), row.get('n_diff'), row.get('first_diff')))
    print('  obj: %s' % obj_path)

    da = _disasm(orig, va)
    db = _disasm(ours, va)
    diffs = set(row.get('diffs', []))
    diffs_full = row.get('n_diff', 0) > len(diffs)
    # capstone 截断标注（-1 哨兵）先行输出（复核确认：dict 过滤会丢弃它）
    for tag, lst in (('ORIG', da), ('OURS', db)):
        for a, hx, txt in (lst or []):
            if a < 0:
                print('  [%s] %s' % (tag, txt))
    if da and db:
        da_m = {a: (hx, txt) for a, hx, txt in da if a >= 0}
        db_m = {a: (hx, txt) for a, hx, txt in db if a >= 0}
        for o in sorted(set(da_m) | set(db_m)):
            a = da_m.get(o)
            b = db_m.get(o)
            # span 用真实指令长度（复核确认：16 字节窗口过标）
            alen = (len(a[0]) // 2) if a else 0
            span_diff = any(o <= d < o + max(alen, 1) for d in diffs)
            if a:
                rl = ''.join('[r]' if (o + k) in relocs else '' for k in range(alen))
                print('  -%3d  ORIG %-26s %-12s %s%s' % (o, a[0], a[1], rl,
                                                         '  <>' if span_diff else ''))
            if (a and b and a[0] != b[0]) or (b and not a):
                rl = ''.join('[r]' if (o + k) in relocs else '' for k in range(len(b[0] if b else '') // 2))
                print('        OURS %-26s %-12s %s%s' % (b[0] if b else '', b[1] if b else '', rl,
                                                         '  <>' if (a and b and a[0] != b[0]) else ''))
        if diffs_full:
            print('  (注: detail 的 diffs 数组被截断到 %d 条 / 实际 n_diff %s —— <>' % (len(diffs), row.get('n_diff')),
                  '标注可能不全)')
    else:
        n = max(len(orig), len(ours))
        for o in range(0, n, 16):
            ob = orig[o:o + 16]
            mb = ours[o:o + 16]
            print('  -%3d  ORIG %-48s %s' % (o, _hexline(ob), '  <> diff' if ob != mb else ''))
            if ob != mb:
                print('        OURS %-48s' % _hexline(mb))
    print('\nn_diff=%s first_diff=%s' % (row.get('n_diff'), row.get('first_diff')))


if __name__ == '__main__':
    main()
