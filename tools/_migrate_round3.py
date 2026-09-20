"""MCP round 3 annotation surgery (2026-09-14).

- UpdatePanel 0x4DC250: CCBUI -> CCBRoleState (this=CCBRoleState proven by
  mov ecx,esi chains; +0xC/+0x20 = CCBRoleState known_members; sole caller
  CCBRoleState x12)
- AddCommand 0x4F2C70: CCBSystem -> CCBRoleState (this used as CCBRoleState:
  GetRoleField/GetTotalRounds/CheckBuff all on own this; sole caller x12)
- ExecuteBlock 0x424C20: PalScriptMgr -> ScriptVM (2,353-line interpreter
  loop; calls ScriptVM::CallFunction/SetRolePosition on own this x6+;
  IsRunning callers all inside it) -> IsRunning's 13 marker sites resolve
  intra-class.
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

MOVES = {
    '0x004DC250': ('CCBUI', 'CCBRoleState', 'UpdatePanel',
                   'this=CCBRoleState (mov ecx,esi -> GetRoleField family); '
                   '+0xC/+0x20 are CCBRoleState known_members; sole caller x12'),
    '0x004F2C70': ('CCBSystem', 'CCBRoleState', 'AddCommand',
                   'this=CCBRoleState: GetRoleField/GetTotalRounds/CheckBuff all on own this; '
                   'CCBSystem only reached via other objects; sole caller x12'),
    '0x00424C20': ('PalScriptMgr', 'ScriptVM', 'ExecuteBlock',
                   'interpreter loop; ScriptVM::CallFunction/SetRolePosition on own this (mov ecx,esi); '
                   'IsRunning(0x42C1A0) callers all inside this function'),
}


def main():
    moved = 0
    for al_raw, (src_cls, dst_cls, name, evidence) in MOVES.items():
        al = al_raw.lower()
        src_p = SDIR / f'{src_cls}.json'
        dst_p = SDIR / f'{dst_cls}.json'
        src = json.loads(src_p.read_text(encoding='utf-8'))
        dst = json.loads(dst_p.read_text(encoding='utf-8'))
        sm = src.get('methods') or {}
        key = next((k for k in sm if k.lower() == al), None)
        if key is None:
            print('missing in', src_cls, al)
            continue
        entry = dict(sm.pop(key))
        entry['name'] = name
        entry['_misattrib_evidence'] = 'round3: %s' % evidence
        dm = dst.get('methods') or {}
        dm[al] = entry
        dst['methods'] = dm
        src['methods'] = sm
        src_p.write_text(json.dumps(src, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
        dst_p.write_text(json.dumps(dst, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
        moved += 1
        print(f'{al} {src_cls} -> {dst_cls}::{name}')
    print('moved:', moved)


if __name__ == '__main__':
    main()
