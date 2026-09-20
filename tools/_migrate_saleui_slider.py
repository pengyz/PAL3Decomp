"""Migrate PAL3::SetValue/GetValue/SetRange to SaleUI (MCP round 2 verdict).

Evidence (data/status/_saleui_slider_verdict.json, 2026-09-14):
- Call sites in SaleUI/PAL_GDB/PlayerMgr methods all pass their own `this`.
- The three functions access this+0x1795C..0x196C4 (>=104,132 bytes) but the
  PAL3 class is 91,024 bytes — cannot be the owner.
- CScreenMode::InitGameUI allocates operator new(0x19DB8)=105,656 and calls
  the PDB-mangled ctor ??0SaleUI@@QAE@XZ at 0x45A7B0, which initializes the
  exact offsets these functions access (+0x18E70, +0x192AC, ...).
- The IDB name ?SetValue@PAL3@@ was written by our own annotation pipeline
  (circular self-confirmation), not PDB-authoritative.
"""
import json
from pathlib import Path


# ---- 2026-09-20 审计 P2-4：无参数解析工具的统一护栏 ----------------------------
# 本工具**会写盘**且**没有任何 argparse/sys.argv 处理** ⇒ 传任何 `-` 开头的参数
# （最典型的是 `--help`）此前会被当作普通输入，**执行全流程并覆盖产物**。
# 本次审计期间已因此发生 **2 起事故**（`sig_evidence.py` 删掉 6020 行、
# `misattribution_ledger.py` 把 197 cluster 改写成 3）。
# 统一护栏：见到任何以 `-` 开头的参数即打印用法并**退出，不执行任何工作**。
import sys as _sys_guard
if any(_a.startswith('-') for _a in _sys_guard.argv[1:]):
    print('[%s] 本工具不接受命令行开关；收到 %r ⇒ 不执行任何操作。'
          % (__file__.rsplit('/', 1)[-1], _sys_guard.argv[1:]))
    print('用法: python3 %s    # 无参数，直接运行' % __file__)
    _sys_guard.exit(0)
# ---------------------------------------------------------------------------

ROOT = Path(__file__).parent.parent
SDIR = ROOT / 'data' / 'annotations' / 'structs'
FNS = ROOT / 'data' / 'annotations' / 'functions.json'

MOVES = {
    '0x00461FD0': ('SetValue', 'int __thiscall(unsigned char nValue)',
                   'alloc 0x19DB8 + ??0SaleUI ctor inits +0x18E70/+0x192AC; '
                   'SetValue vcalls sub-objects +0x19414/+0x1956C/+0x196C4; PAL3(91024B) too small'),
    '0x00462220': ('GetValue', 'int __thiscall(unsigned char nIndex)',
                   'accesses +0x1795C(96,604) > PAL3 size; SaleUI ctor inits same layout'),
    '0x00462080': ('SetRange', 'int __thiscall(unsigned char nMax)',
                   'accesses +0x192AC/+0x18E70 — exactly the offsets SaleUI ctor initializes'),
}


def main():
    pal3_p = SDIR / 'PAL3.json'
    sale_p = SDIR / 'SaleUI.json'
    pal3 = json.loads(pal3_p.read_text(encoding='utf-8'))
    sale = json.loads(sale_p.read_text(encoding='utf-8'))

    pm = pal3.get('methods') or {}
    sm = sale.get('methods') or {}
    moved = 0
    for al, (name, sig, evidence) in MOVES.items():
        key = next((k for k in pm if k.lower() == al), None)
        if key is None:
            print('already moved or missing:', al)
            continue
        entry = dict(pm.pop(key))
        entry['name'] = name
        entry['_misattrib_evidence'] = 'saleui-slider: %s' % evidence
        sm[al] = entry
        moved += 1
    pal3['methods'] = pm

    # alloc evidence trumps the stale estimate
    sale['binary_size'] = 105656
    sale['size_evidence'] = ('operator new(0x19DB8) at CScreenMode::InitGameUI+0x459724 '
                             'followed by ??0SaleUI@@QAE@XZ (PDB-mangled ctor 0x45A7B0)')

    pal3_p.write_text(json.dumps(pal3, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
    sale_p.write_text(json.dumps(sale, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
    print('moved %d methods PAL3 -> SaleUI; SaleUI.binary_size 111488 -> 105656' % moved)

    # functions.json flat renames (entries were absent; add only if present under other names)
    fns = json.loads(FNS.read_text(encoding='utf-8'))
    ren = 0
    for k, v in fns.items():
        if isinstance(v, dict) and k.lower() in MOVES and not str(v.get('name', '')).startswith('SaleUI'):
            v['name'] = 'SaleUI_%s' % MOVES[k.lower()][0]
            ren += 1
    FNS.write_text(json.dumps(fns, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
    print('functions.json renamed:', ren)


if __name__ == '__main__':
    main()
