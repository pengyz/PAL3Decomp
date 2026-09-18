#!/usr/bin/env python3
"""把**一批** annotation 修正一次性落到 JSON 上，然后（可选）只跑**一次**完整管线。

# 为什么要有它

完整管线（annotation → apply → export → codegen → probe → match）**成本很高**（IDA 全量重反编译）。
"改一处注解就跑一次"不可持续 ⇒ 修正应**攒成一批**，一次落盘、一次验证。

# 硬约束（来自项目规则与一次被撤销的教训）

1. **每条修正必须有证据**。`evidence` 字段为空 ⇒ **拒绝该条**（不写文件）。
   依据：`CLAUDE.md`「每一处 annotation 修改必须有二进制直接证据」，
   以及 `docs/knowledge/pattern_annotation_batch_rename_no_evidence.md`
   记载的**一次无证据批量改名被整体撤销**。
2. **重归属必须附成员访问证据**（函数内引用的成员在目标类存在、且不在原类存在）。
3. **改名必须同时复核语义**：`new_name` 若仍是"无语义名"（`_sdtor*`/`sub_*`/尾部十六进制等），
   必须给出 `name_evidence`（该名字依据什么：函数做了什么 / 与哪个已知函数同构）；
   给不出 ⇒ 用 `_todo_` 风格的**诚实占位名**，并在 `name_evidence` 里写明"含义未定"。

# 批次文件格式（data/status/annotation_fix_batch.json）

```json
[
  {"kind": "reattribute", "addr": "0x00411CA0",
   "from": "ScriptObj", "to": "PalScript",
   "new_name": "~PalScript",
   "evidence": "引用的成员 m_RoleArray/m_bCreated/... 全部属于 PalScript，且都不在 ScriptObj 里",
   "name_evidence": "成员族与 PalScript 的析构路径一致（释放 m_RoleArray/m_pDialogData）"},
  {"kind": "rename", "class": "CUtil", "addr": "0x005231F0",
   "new_name": "~CUtil", "evidence": "...", "name_evidence": "..."}
]
```

用法：
    python3 tools/apply_annotation_batch.py                 # 只落盘 + 校验（不动 IDB）
    python3 tools/apply_annotation_batch.py --run-pipeline  # 落盘后跑一次完整管线
"""
import argparse
import json
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN = os.path.join(ROOT, 'data', 'annotations', 'structs')
BATCH = os.path.join(ROOT, 'data', 'status', 'annotation_fix_batch.json')

NONSEM = ('_sdtor', '_scalar_dtor', '_vbase_dtor', 'sub_', 'unk_', 'loc_', '_todo', '_stub')


def _looks_nonsemantic(name):
    import re
    n = str(name or '')
    if n.startswith(NONSEM):
        return True
    return bool(re.search(r'_[0-9a-f]{3,}$', n)) or bool(re.search(r'_[0-9]{3,}$', n))


def load_ann(cls):
    p = os.path.join(ANN, '%s.json' % cls)
    return json.load(open(p, encoding='utf-8')), p


def save_ann(d, p):
    json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=2)
    open(p, 'a').write('\n')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--batch', default=BATCH)
    ap.add_argument('--run-pipeline', action='store_true')
    args = ap.parse_args()

    if not os.path.exists(args.batch):
        print('[ERROR] 批次文件不存在: %s' % args.batch)
        return 1
    items = json.load(open(args.batch, encoding='utf-8'))

    ok, rejected = [], []
    for it in items:
        ev = (it.get('evidence') or '').strip()
        nm = it.get('new_name') or ''
        ne = (it.get('name_evidence') or '').strip()
        if not ev:
            rejected.append((it, '缺少 evidence（硬约束 1）'))
            continue
        if nm and _looks_nonsemantic(nm) and not ne:
            rejected.append((it, '新名仍无语义且缺 name_evidence（硬约束 3）'))
            continue
        if it.get('kind') == 'reattribute' and not ne:
            rejected.append((it, '重归属缺 name_evidence（硬约束 2/3）'))
            continue
        ok.append(it)

    print('批次 %d 条：通过 %d，拒绝 %d' % (len(items), len(ok), len(rejected)))
    for it, why in rejected:
        print('   [拒绝] %s %s：%s' % (it.get('kind'), it.get('addr') or it.get('class'), why))
    if rejected:
        print('\n有被拒条目 ⇒ **不落盘**（宁可不做，也不写无据的改动）')
        return 1

    done = 0
    for it in ok:
        if it['kind'] == 'reattribute':
            src, sp = load_ann(it['from'])
            dst, dp = load_ann(it['to'])
            ent = (src.get('methods') or {}).pop(it['addr'], None)
            if ent is None:
                print('   [跳过] %s 不在 %s.methods' % (it['addr'], it['from']))
                continue
            ent['name'] = it['new_name']
            ent['note'] = 'reattribute: %s' % it['evidence']
            ent['name_evidence'] = it['name_evidence']
            dst.setdefault('methods', {})[it['addr']] = ent
            save_ann(src, sp)
            save_ann(dst, dp)
            print('   [重归属] %s: %s -> %s (%s)' % (it['addr'], it['from'], it['to'], it['new_name']))
            done += 1
        elif it['kind'] == 'rename':
            d, p = load_ann(it['class'])
            ent = (d.get('methods') or {}).get(it['addr'])
            if ent is None:
                print('   [跳过] %s 不在 %s.methods' % (it['addr'], it['class']))
                continue
            ent['name'] = it['new_name']
            ent['note'] = 'rename: %s' % it['evidence']
            ent['name_evidence'] = it['name_evidence']
            save_ann(d, p)
            print('   [改名] %s.%s -> %s' % (it['class'], it['addr'], it['new_name']))
            done += 1
        else:
            print('   [跳过] 未知 kind: %s' % it.get('kind'))
    print('\n落盘 %d 条' % done)

    rc = subprocess.call([sys.executable, 'pipeline/cli.py', 'check'], cwd=ROOT)
    if rc != 0:
        print('[ERROR] check 未通过')
        return rc
    if args.run_pipeline:
        print('\n=== 跑完整管线（一批只跑一次）===')
        for cmd in (['pipeline/cli.py', 'apply'], ['pipeline/cli.py', 'export'],
                    ['pipeline/gen/codegen.py', 'all'], ['pipeline/cli.py', 'probe', 'all']):
            print('-> %s' % ' '.join(cmd))
            rc = subprocess.call([sys.executable] + cmd, cwd=ROOT)
            if rc != 0:
                print('[ERROR] 管线在 %s 失败' % cmd)
                return rc
        print('管线完成。接着请自行跑 match（字节匹配裁判）并做对账。')
    return 0


if __name__ == '__main__':
    sys.exit(main())
