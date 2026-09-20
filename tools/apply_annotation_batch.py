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
        kind = it.get('kind')
        if not ev:
            rejected.append((it, '缺少 evidence（硬约束 1）'))
            continue
        if nm and _looks_nonsemantic(nm) and not ne:
            rejected.append((it, '新名仍无语义且缺 name_evidence（硬约束 3）'))
            continue
        if kind == 'reattribute' and not ne:
            rejected.append((it, '重归属缺 name_evidence（硬约束 2/3）'))
            continue
        # set_size / skip_method（2026-09-19 新增，供 §49.4 尺寸与 thunk 类修正使用）
        if kind == 'set_size':
            if not it.get('class') or not isinstance(it.get('size'), int) or it['size'] <= 0:
                rejected.append((it, 'set_size 需要 class + 正整数 size'))
                continue
            if not (it.get('evidence') or '').strip():
                rejected.append((it, 'set_size 缺二进制证据'))
                continue
        if kind == 'skip_method':
            if not it.get('class') or not it.get('addr') or not (it.get('reason') or '').strip():
                rejected.append((it, 'skip_method 需要 class + addr + reason'))
                continue
        if kind == 'add_method':
            if not it.get('class') or not it.get('addr') or not it.get('new_name'):
                rejected.append((it, 'add_method 需要 class + addr + new_name'))
                continue
            sig = (it.get('signature') or '').strip()
            if not sig:
                rejected.append((it, 'add_method 需要 signature'))
                continue
            # 与 set_signature 同源护栏：__thiscall 必须带 "::"
            if '__thiscall' in sig and '::' not in sig:
                rejected.append((it, 'add_method 的 __thiscall 签名缺少 "::"（会被发射成 static free function）'))
                continue
        if kind == 'set_signature':
            sig = (it.get('new_signature') or '').strip()
            if not it.get('class') or not it.get('addr') or not sig:
                rejected.append((it, 'set_signature 需要 class + addr + new_signature'))
                continue
            # 与 check_annotations 同源的护栏：__thiscall 必须带 "::"，否则会退化成
            # "free function" 并被发射成 static（2026-09-19 实测：
            #  0x004C5B90 搬类后残留旧签名 ⇒ pal3/src/Effect/CEffectSystem.h:44
            #  出现 `static struct _Texture_uv & SetEffectVisible(_Texture_uv *);`）
            if '__thiscall' in sig and '::' not in sig:
                rejected.append((it, 'set_signature 的 __thiscall 签名缺少 "::"（会被发射成 static free function）'))
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
            # 2026-09-19 两次踩到：签名**不跟着搬**，旧类名留在 signature 里，
            # 生成头会把它发射成原类的静态自由函数（如
            # `static struct _Texture_uv & SetEffectVisible(_Texture_uv *)`）。
            old_sig = str(ent.get('signature') or '')
            if it['from'] in old_sig and not it.get('new_signature'):
                print('   [WARN] %s 的旧签名仍含原类名 %r：%s' % (it['addr'], it['from'], old_sig))
                print('          建议同时给 new_signature（否则生成头会用错类型/退化成 static）')
            if it.get('new_signature'):
                ent['signature'] = it['new_signature']
                ent['signature_note'] = 'reattribute 同时改签名 (was: %s)' % old_sig
            ent['name'] = it['new_name']
            ent['note'] = 'reattribute: %s' % it['evidence']
            ent['name_evidence'] = it['name_evidence']
            dst.setdefault('methods', {})[it['addr']] = ent
            save_ann(src, sp)
            save_ann(dst, dp)
            print('   [重归属] %s: %s -> %s (%s)' % (it['addr'], it['from'], it['to'], it['new_name']))
            done += 1
        elif it['kind'] == 'add_method':
            d, p2 = load_ann(it['class'])
            if it['addr'] in (d.get('methods') or {}):
                print('   [跳过] %s 已在 %s.methods' % (it['addr'], it['class']))
                continue
            d.setdefault('methods', {})[it['addr']] = {
                'name': it['new_name'],
                'signature': it['signature'],
                'note': 'add_method: %s' % it['evidence'],
                'name_evidence': it.get('name_evidence') or '',
            }
            save_ann(d, p2)
            print('   [新增方法] %s.%s = %s' % (it['class'], it['addr'], it['new_name']))
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
        elif it['kind'] == 'set_size':
            d, p = load_ann(it['class'])
            old = d.get('binary_size')
            d['binary_size'] = it['size']
            # 证据不写进 struct JSON（避免引入未知顶层键）；按 CLAUDE.md 的归属，
            # 单字段证据记 data/annotations/CHANGE_LOG.md。
            save_ann(d, p)
            print('   [尺寸] %s: %s -> %s  (evidence: %s)' % (it['class'], old, it['size'], it['evidence'][:80]))
            done += 1
        elif it['kind'] == 'skip_method':
            d, p = load_ann(it['class'])
            ent = (d.get('methods') or {}).get(it['addr'])
            if ent is None:
                print('   [跳过] %s 不在 %s.methods' % (it['addr'], it['class']))
                continue
            ent['type'] = 'skip'
            ent['reason'] = it['reason']
            ent['note'] = 'skip_method: %s' % it['evidence']
            if it.get('new_name'):
                ent['name'] = it['new_name']
            if it.get('name_evidence'):
                ent['name_evidence'] = it['name_evidence']
            save_ann(d, p)
            print('   [标 skip] %s.%s (%s)' % (it['class'], it['addr'], ent.get('name')))
            done += 1
        elif it['kind'] == 'set_signature':
            d, p = load_ann(it['class'])
            ent = (d.get('methods') or {}).get(it['addr'])
            if ent is None:
                print('   [跳过] %s 不在 %s.methods' % (it['addr'], it['class']))
                continue
            old = ent.get('signature')
            ent['signature'] = it['new_signature']
            ent['signature_note'] = 'set_signature: %s (was: %s)' % (it['evidence'], old)
            save_ann(d, p)
            print('   [签名] %s.%s: %s -> %s' % (it['class'], it['addr'], old, it['new_signature']))
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
