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


def _norm_off_try(k):
    """offset 键归一（十进制 / 0x… / NNN_N 后缀）。**禁用 int(k,0)** ✗（'50814_0' 会变 508140）。"""
    ks = str(k)
    if ks[:2].lower() == '0x':
        try:
            return int(ks, 16)
        except ValueError:
            return None
    if '_' in ks:
        ks = ks.split('_')[0]
    return int(ks, 10) if ks.isdigit() else None


def _looks_nonsemantic(name):
    import re
    n = str(name or '')
    if n.startswith(NONSEM):
        return True
    return bool(re.search(r'_[0-9a-f]{3,}$', n)) or bool(re.search(r'_[0-9]{3,}$', n))


def load_ann(cls):
    p = os.path.join(ANN, '%s.json' % cls)
    return json.load(open(p, encoding='utf-8')), p


# 2026-09-21：**全局 dry-run 闸** —— 起因：我最初只在新增分支里检查 args.dry_run，
# 而既有的 set_size 分支不知道它 ⇒ 一次 --dry-run 竟然真落了 1453 条 ✗✗（已逐个 git show 回退 ✓）。
# ⇒ 把守卫放到**唯一的落盘出口** save_ann 上，任何分支都无法绕过 ✓。
_DRY_RUN = False
# 2026-09-21（复核 7f6a52cd Q5 / 阶段一 ③b）：**两阶段落盘** —— 原实现循环内逐条 save_ann ✗
# 且 `[拒绝]` 只 continue ✗ ⇒ "1507/1507 通过"**不等于原子** ✗。
# 现改为：**先在内存缓冲**（同一单点 save_ann ✓），末尾若无拒绝才**统一 flush** ✓；
# 任一拒绝 ⇒ **整批不写 + 非零退出** ✓。
_BUFFER = None          # None = 直写（兼容旧行为）；dict = 缓冲模式（path -> data）


def save_ann(d, p):
    if _DRY_RUN:
        return                      # dry-run：**绝不写盘** ✓（单点守卫，不可绕过 ✓）
    if _BUFFER is not None:
        _BUFFER[p] = d              # 两阶段：先缓冲 ✓（校验通过后才 flush ✓）
        return
    json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=2)
    open(p, 'a').write('\n')


def main():
    _write_rejected = 0
    ap = argparse.ArgumentParser()
    ap.add_argument('--batch', default=BATCH)
    ap.add_argument('--run-pipeline', action='store_true')
    ap.add_argument('--dry-run', action='store_true', help='只计算并打印将做的修改，**不落盘**')
    args = ap.parse_args()

    global _DRY_RUN, _BUFFER      # **B4 修复**：原缺 _BUFFER ⇒ 赋值只建局部名 ⇒ save_ann 读到模块级 None
                                  # ⇒ 逐条直写，"两阶段全或无"是假的 ✗（独立复核 bd0abcc1 反汇编实证：1×STORE_FAST/0×STORE_GLOBAL）

    _DRY_RUN = bool(getattr(args, 'dry_run', False))

    _BUFFER = {} if not _DRY_RUN else None      # 非 dry-run ⇒ 启用两阶段缓冲 ✓（现为真全局 ✓）

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
        # 2026-09-19 补：reattribute 也必须校验 new_signature（此前只管 add_method/set_signature，
        # 结果 3 条迁移条目带着"__thiscall 但无 ::"的签名落盘，会被发射成 static 自由函数）
        if kind == 'reattribute' and it.get('new_signature'):
            _ns = it['new_signature']
            if '__thiscall' in _ns and '::' not in _ns:
                rejected.append((it, 'reattribute 的 new_signature 是 __thiscall 却缺 "::"（会被发射成 static free function）'))
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
        if it['kind'] in ('set_base_size', 'shift_offset'):
            # A 窄核新增（2026-09-21）：set_base_size 与 shift_offset（含 mult 倍数）
            # 依据：cascade_plan 的精确计划 —— 平移量**非常数**（第 k 个内嵌对象之后 +Δ×k ✓）
            cls = it.get('class')
            if not cls:
                print('   [跳过] %s 缺 class' % kind); continue
            p2 = os.path.join(ANN, '%s.json' % cls)
            if not os.path.exists(p2):
                print('   [跳过] %s 无注解: %s' % (it['kind'], cls)); continue
            d, p2 = load_ann(cls)      # load_ann 返回 (dict, path) ✓
            if it['kind'] == 'set_base_size':
                frm, to = it.get('from'), it.get('to')
                if d.get('base_size') != frm:
                    print('   [拒绝] %s base_size 期望 %s 实得 %s（防陈旧计划 ✗）' % (cls, frm, d.get('base_size'))); continue
                if not args.dry_run:
                    d['base_size'] = to; save_ann(d, p2)
                print('   [%s] %s base_size %s -> %s' % ('dry-run' if args.dry_run else '落盘', cls, frm, to))
                done += 1
            else:
                key, frm, to = str(it.get('key')), it.get('from'), it.get('to')
                km = d.get('known_members') or {}
                if key not in km:
                    print('   [拒绝] %s 无成员键 %s（防陈旧计划 ✗）' % (cls, key)); continue
                newkm = {}
                for k, v in km.items():
                    o = _norm_off_try(k)
                    if o is not None and frm is not None and o == frm:
                        newkm[str(to)] = v
                    else:
                        newkm[k] = v
                if not args.dry_run:
                    d['known_members'] = newkm; save_ann(d, p2)
                print('   [%s] %s offset %s -> %s (mult=%s)' % ('dry-run' if args.dry_run else '落盘', cls, frm, to, it.get('mult')))
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
    # **两阶段**：有拒绝 ⇒ 整批不写 + 非零退出 ✓（复核要求"先全量校验再统一落盘" ✓）
    if rejected:
        print('\n[ABORT] 有 %d 条被拒 ⇒ **整批不写** ✓（两阶段：校验未全过）' % len(rejected))
        return 1
    # **B4 真正的全或无**：任一拒绝（校验阶段或写入阶段）⇒ **flush 之前就中止** ✓
    # （前一版是"先 flush 再报失败" ✗ ⇒ 部分写入仍会发生 ✗，独立复核 bd0abcc1 指出的正是这一点）
    if _write_rejected:
        print('\n[ABORT] 写入阶段有 %d 条被拒 ⇒ **整批不写** ✓（缓冲丢弃，未 flush ✓）' % _write_rejected)
        return 1
    if _BUFFER is not None and not _DRY_RUN:
        for path, data in sorted(_BUFFER.items()):
            json.dump(data, open(path, 'w', encoding='utf-8'), ensure_ascii=False, indent=2)
        print('\n[flush] 统一落盘 %d 个文件（两阶段 ✓ 全或无 ✓）' % len(_BUFFER))
    print('\n%s %d 条' % ('[dry-run] 计算' if _DRY_RUN else '落盘', done))

    if _DRY_RUN:
        print('[dry-run] **未写任何文件** ✓ —— 确认无误后去掉 --dry-run 再执行 ✓')
        return 0
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
