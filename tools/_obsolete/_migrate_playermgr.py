"""Round 5 surgery: dissolve phantom PlayerMgr into SaleUI (2026-09-14).

Evidence (data/status/_round5_verdict.json):
- vtable 0x56B5CC installed by BOTH 0x45acde (inside ??0SaleUI ctor) and
  0x45ae81 (inside the function mislabeled ?ctor@PlayerMgr) — same table,
  same class.
- 0x45AE60's only caller is ?_scalar_dtor@SaleUI@@ (0x45ae43); it walks
  members in DESCENDING order (+0x19DB4 first = last dword of the
  0x19DB8 allocation) — it is ~SaleUI, not a ctor.
- 0 PDB-mangled PlayerMgr names exist (17 IDA pseudo-names only);
  PDB-attested SaleUI methods (12) are physically interleaved with the
  pseudo-named PlayerMgr ones.
- All 6 spot-checked PlayerMgr-named methods access offsets <= 0x19DB4,
  inside SaleUI's 0x19DB8 allocation.
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


def main():
    pm_p = SDIR / 'PlayerMgr.json'
    su_p = SDIR / 'SaleUI.json'
    pal_p = SDIR / 'PAL_GDB.json'
    pm = json.loads(pm_p.read_text(encoding='utf-8'))
    su = json.loads(su_p.read_text(encoding='utf-8'))
    pal = json.loads(pal_p.read_text(encoding='utf-8'))

    sm = su.get('methods') or {}
    moved = []

    # 1. methods: PlayerMgr -> SaleUI (ctor entry becomes ~SaleUI)
    for a, m in sorted(pm.get('methods', {}).items()):
        e = dict(m)
        name = e.get('name')
        if a.lower() == '0x0045ae60' or name == 'ctor':
            e['name'] = '~SaleUI'
            e['_misattrib_evidence'] = ('round5: installs vtable 0x56B5CC at 0x45ae81 and tears '
                                        'members down descending (+0x19DB4 first); sole caller is '
                                        '?_scalar_dtor@SaleUI@@ 0x45ae43 - this is ~SaleUI, IDA had '
                                        'it as ?ctor@PlayerMgr (no PDB mangled PlayerMgr exists)')
        else:
            e['_misattrib_evidence'] = ('round5: PlayerMgr is a phantom pseudo-name (0 PDB mangled); '
                                        'physically interleaved with PDB SaleUI methods; offsets fit '
                                        'SaleUI 0x19DB8')
        sm[a.lower()] = e
        moved.append((a, name, 'SaleUI' if name != 'ctor' else '~SaleUI'))
    pm['methods'] = {}

    # 2. UpdateSkillPanel: PAL_GDB -> SaleUI
    pal_methods = pal.get('methods') or {}
    key = next((k for k in pal_methods if k.lower() == '0x00460a90'), None)
    if key:
        e = dict(pal_methods.pop(key))
        e['name'] = 'UpdateSkillPanel'
        e['_misattrib_evidence'] = ('round5: max this-offset 0x19DA8 fits SaleUI 0x19DB8; block-'
                                    'adjacent to PDB ?DestroySubFrames@SaleUI@@ 0x4615F0; callers '
                                    'are SaleUI methods')
        sm[key.lower()] = e
        moved.append((key, 'UpdateSkillPanel', 'SaleUI'))
    pal['methods'] = pal_methods

    # 3. known_members merge (20 non-conflicting; 0x0 __vftable wins; 0x4c bkHeight wins)
    skm = su.get('known_members') or {}
    conflicts = {'0': '__vftable wins (polymorphic, PDB vtable)', '76': 'bkHeight wins (pairs with bkWidth@72)'}
    merged = 0
    for k, v in (pm.get('known_members') or {}).items():
        o = int(k, 0) if not str(k).isdigit() else int(k)
        if o in (0, 76):
            continue
        skm[k.lower() if k.startswith('0x') else k] = v
        merged += 1

    su['methods'] = sm
    su['known_members'] = skm
    su['_naming_note'] = ('PDB-attested class (??0SaleUI@@QAE@XZ ctor, 12 mangled methods, vtable '
                          '0x56B5CC, size 0x19DB8 from CScreenMode::InitGameUI alloc). The former '
                          '"PlayerMgr" annotation was a phantom pseudo-name for this same class; '
                          'dissolved 2026-09-14 (see _round5_verdict.json).')
    su_p.write_text(json.dumps(su, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
    pal_p.write_text(json.dumps(pal, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
    print(f'moved {len(moved)} methods, merged {merged} known_members')

    # 4. functions.json flat renames
    fns = json.loads(FNS.read_text(encoding='utf-8'))
    ren = 0
    for k, v in fns.items():
        if isinstance(v, dict):
            n = str(v.get('name', ''))
            if 'PlayerMgr' in n:
                v['name'] = n.replace('PlayerMgr_', 'SaleUI_').replace('PlayerMgr', 'SaleUI')
                ren += 1
    FNS.write_text(json.dumps(fns, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
    print('functions.json PlayerMgr->SaleUI renames:', ren)

    # 5. tombstone: remove phantom class annotation
    pm_p.unlink()
    print('removed PlayerMgr.json (phantom class dissolved)')


if __name__ == '__main__':
    main()
