#!/usr/bin/env python3
"""Phase 2 手工 fix 留存机制（overlay + base-hash 漂移门）。

## 背景：pal3/src 的三重灭失（Phase 2 fix 零留存根因，verifier 2026-10-15 复核）

1. **射程生成逐文件覆盖**：`pipeline/gen/stages/emit_cpp.py` 对每个 .cpp
   `open(out_path, 'w')` ⇒ codegen 一次即覆盖手改。
2. **`codegen all` rmtree 全树**：`pipeline/gen/codegen.py:cmd_clean` 整树删除重建。
3. **git 不跟踪**：`.gitignore` 目录级排除 `pal3/src/`（re-include 不可行）。
⇒ 手改 pal3/src = 三重灭失，零留存。

## 方案 A'（verifier 已批准）：git 托管 overlay + base-hash 漂移门

```
phase2/
  manifest.json          # 源真值（tracked）——每条 fix 的模式/基准 hash/备注
  overlay/<相对路径>      # fix 副本，镜像 pal3/src 的相对路径（tracked）
  base_census.json       # 派生物：最近一次 apply 时的 codegen 产物全量 hash（gitignore）
```

- **零管线侵入**：只在 `codegen.py` 三分支（headers/cpp/all）末尾挂 retain apply，
  emit_cpp/cmd_clean 一行不动。
- **git 即独立基线**：overlay 在 gitignored 树外 ⇒ 天然 tracked、可回溯。
- **漂移显式化**：codegen 该文件输出变化（hash ≠ manifest.base_sha256）时
  `override` 条目 **fail-loud（exit 2）**，`pin` 条目跳过并告警——「旧 fix 过期」
  从静默风险变成显式失败。

## 条目模式

| mode | 漂移时 | 用途 |
|---|---|---|
| `override` | **exit 2**（fail-loud，逼人工 rebase） | 常规手工 fix |
| `pin`   | 跳过 + 告警 | 明知基座会动的挂账条目 |

`new_unit: true`：fix 产出 codegen **不生成**的新单元（改 S2 分母！）
⇒ 无 base 可漂移，apply 直接拷贝；**必须显式声明**并走门禁数字刷新流程。

## 子命令

    apply  [--root DIR] [--phase2 DIR]   # codegen 后：漂移门 → overlay 覆盖 → 写 census
    check  [...]                         # 后置自校验：逐条目 sha256(pal3/src)==sha256(overlay)
    adopt  <relpath> [...]               # 收编当前 pal3/src 文件为 fix 基底（拷入 overlay + 记 base hash）
    diff   [<relpath>] [...]             # overlay vs 当前 pal3/src 的 unified diff
    rebase [<relpath>] [...]             # 人工复核后把 base_sha256 刷新为 census 里的新 hash

退出码：0 成功 · 1 check 失败/用法错 · 2 override 漂移（fail-loud）。

R15：纯函数（hash/manifest/plan）单测见 tests/test_phase2_retain.py（fixture 树，
不碰真 pal3/src）。
"""
import argparse
import difflib
import hashlib
import json
import os
import shutil
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_ROOT = os.path.join(REPO, 'pal3', 'src')
DEFAULT_PHASE2 = os.path.join(REPO, 'phase2')

EXIT_OK = 0
EXIT_FAIL = 1
EXIT_DRIFT = 2

# 派生物（gitignore）：最近一次 apply 时 codegen 产物的全量 hash
CENSUS_NAME = 'base_census.json'
MANIFEST_NAME = 'manifest.json'
OVERLAY_DIR = 'overlay'


# ─────────────────────────── 纯函数层 ───────────────────────────

def sha256_bytes(data):
    return hashlib.sha256(data).hexdigest()


def sha256_file(path):
    with open(path, 'rb') as f:
        return sha256_bytes(f.read())


def load_manifest(path):
    """读 manifest；不存在 ⇒ 空骨架。结构非法 ⇒ ValueError（fail-loud，不猜）。"""
    if not os.path.exists(path):
        return {'version': 1, 'entries': {}}
    with open(path, encoding='utf-8') as f:
        data = json.load(f)
    if not isinstance(data, dict) or not isinstance(data.get('entries'), dict):
        raise ValueError('manifest 结构非法：需 {"version":…, "entries": {...}}')
    for rel, e in data['entries'].items():
        if not isinstance(e, dict):
            raise ValueError('manifest 条目非法（%s）：需对象' % rel)
        if e.get('mode', 'override') not in ('override', 'pin'):
            raise ValueError('manifest 条目 %s：mode 只能 override|pin' % rel)
    return data


def save_manifest(path, manifest):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w', encoding='utf-8') as f:
        json.dump(manifest, f, ensure_ascii=False, indent=2, sort_keys=True)
        f.write('\n')


def compute_census(root):
    """root 下全部**文件**的 {相对路径: sha256}（字典序，确定性）。
    跳过点文件（.gitkeep 等占位符不是 fix 副本）。"""
    out = {}
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames.sort()
        for fn in sorted(filenames):
            if fn.startswith('.'):
                continue
            full = os.path.join(dirpath, fn)
            rel = os.path.relpath(full, root).replace(os.sep, '/')
            out[rel] = sha256_file(full)
    return out


def load_census(path):
    if not os.path.exists(path):
        return {}
    with open(path, encoding='utf-8') as f:
        data = json.load(f)
    return data.get('files', {}) if isinstance(data, dict) else {}


def save_census(path, census, note=''):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w', encoding='utf-8') as f:
        json.dump({'note': note, 'files': census}, f, ensure_ascii=False,
                  indent=2, sort_keys=True)
        f.write('\n')


def plan_apply(manifest, census, overlay_hashes):
    """纯函数：给定 manifest、**当前 pal3/src 产物 census** 与 overlay hash，算执行计划。

    逐条目三分判据（射程/重复 apply 安全）：
      ① root == overlay          ⇒ fix 在位 ⇒ no-op（幂等；射程 codegen 后重复
                                   apply 不得误报漂移——root 里是 overlay 内容）
      ② root == base_sha256      ⇒ codegen 重生成了基座 ⇒ action（拷 overlay）
      ③ 其它（root 是新产出）    ⇒ **漂移**：override→drift（exit 2 fail-loud）·
                                   pin→skips（跳过 + 告警）
    另：root 缺失（被手删/codegen 未产出）⇒ action 自愈拷回（overlay 是真值）；
    new_unit 无 base ⇒ 仅 ① no-op，否则 action（同名新产出=声明内接管，WARN 由
    调用方在 census 里发现双源时打）。

    返回 dict: actions [(rel, base_sha256|None)] · drift [(rel, expected, actual, mode)]
              · skips [(rel, reason)] · inplace [rel]
    """
    actions, drift, skips, inplace = [], [], [], []
    for rel in sorted(manifest.get('entries', {})):
        e = manifest['entries'][rel]
        mode = e.get('mode', 'override')
        ov = overlay_hashes.get(rel)
        if ov is None:
            skips.append((rel, 'overlay 副本缺失 ⇒ 跳过（check 会 FAIL-loud）'))
            continue
        actual = census.get(rel)
        if actual == ov:
            inplace.append(rel)
            continue
        if e.get('new_unit'):
            actions.append((rel, None))
            continue
        expected = e.get('base_sha256')
        if actual is None:
            actions.append((rel, expected))   # 自愈：root 被删 ⇒ 拷回
        elif expected is None:
            skips.append((rel, '条目缺 base_sha256 ⇒ 跳过（先 adopt/rebase 补基准）'))
        elif actual == expected:
            actions.append((rel, expected))
        elif mode == 'override':
            drift.append((rel, expected, actual, mode))
        else:
            skips.append((rel, 'pin 漂移：codegen 输出已变（%s…→%s…）⇒ 跳过并告警'
                          % (expected[:8], actual[:8])))
    return {'actions': actions, 'drift': drift, 'skips': skips,
            'inplace': inplace}


def plan_check(manifest, root_hashes, overlay_hashes):
    """纯函数：后置自校验计划（防回退断言 ①）。

    返回 dict:
      ok:      [rel]   sha256(pal3/src) == sha256(overlay) 的条目
      missing: [rel]   pal3/src 侧缺失（被 codegen 冲掉/手删）
      mismatch:[(rel, want, got)] 两侧 hash 不等（fix 未应用或被改）
      orphans: [rel]   overlay 有文件但 manifest 无条目（脏副本）
      no_overlay:[rel] manifest 有条目但 overlay 缺文件（记录损坏）
    """
    ok, missing, mismatch = [], [], []
    entries = manifest.get('entries', {})
    for rel in sorted(entries):
        want = overlay_hashes.get(rel)
        got = root_hashes.get(rel)
        if want is None:
            missing.append(rel)   # 占位：overlay 缺 → no_overlay 更精确（下面统一）
        elif got is None:
            missing.append(rel)
        elif got == want:
            ok.append(rel)
        else:
            mismatch.append((rel, want, got))
    no_overlay = [r for r in sorted(entries) if r not in overlay_hashes]
    orphans = [r for r in sorted(overlay_hashes) if r not in entries]
    missing = [r for r in missing if r not in no_overlay]
    return {'ok': ok, 'missing': missing, 'mismatch': mismatch,
            'orphans': orphans, 'no_overlay': no_overlay}


def normalize_rel(rel):
    """相对路径归一：反斜杠→正斜杠、去前导 ./ 与 /、剥仓库级 `pal3/src/` 前缀
    （root 即 pal3/src，接受两种口径——防手滑拼成双路径）。"""
    r = rel.replace('\\', '/').strip()
    while r.startswith('./'):
        r = r[2:]
    r = r.lstrip('/')
    for prefix in ('pal3/src/', 'src/'):
        if r.startswith(prefix):
            r = r[len(prefix):]
    return r


# ─────────────────────────── 执行层 ───────────────────────────

class Ctx(object):
    def __init__(self, root, phase2):
        self.root = root
        self.phase2 = phase2
        self.overlay = os.path.join(phase2, OVERLAY_DIR)
        self.manifest_path = os.path.join(phase2, MANIFEST_NAME)
        self.census_path = os.path.join(phase2, CENSUS_NAME)

    def overlay_hashes(self):
        return compute_census(self.overlay) if os.path.isdir(self.overlay) else {}

    def root_hashes(self):
        return compute_census(self.root) if os.path.isdir(self.root) else {}


def cmd_apply(ctx, note=''):
    manifest = load_manifest(ctx.manifest_path)
    if not manifest['entries']:
        print('[phase2-retain] manifest 空 ⇒ no-op')
        return EXIT_OK
    if not os.path.isdir(ctx.root):
        print('[phase2-retain] root 不存在：%s ⇒ no-op' % ctx.root)
        return EXIT_OK
    census = ctx.root_hashes()
    save_census(ctx.census_path, census, note=note or 'codegen 产物快照（apply 时点）')
    plan = plan_apply(manifest, census, ctx.overlay_hashes())
    for rel, reason in plan['skips']:
        print('[phase2-retain][SKIP] %s — %s' % (rel, reason))
    for rel in plan['inplace']:
        print('[phase2-retain][in-place] %s — fix 已在位（幂等 no-op）' % rel)
    if plan['drift']:
        for rel, expected, actual, mode in plan['drift']:
            print('[phase2-retain][DRIFT] %s — codegen 输出已变 '
                  '（base %s… → %s…）；override 条目 fail-loud ⇒ 先人工复核再 '
                  '`rebase`' % (rel, expected[:12], actual[:12]))
        print('[phase2-retain] 漂移 %d 条 ⇒ exit 2（fail-loud）'
              % len(plan['drift']))
        return EXIT_DRIFT
    for rel, _base in plan['actions']:
        src = os.path.join(ctx.overlay, rel)
        if not os.path.exists(src):
            print('[phase2-retain][FAIL] %s — overlay 副本缺失' % rel)
            return EXIT_FAIL
        dst = os.path.join(ctx.root, rel)
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        shutil.copyfile(src, dst)
        print('[phase2-retain] applied %s' % rel)
    print('[phase2-retain] apply 完成：%d 条' % len(plan['actions']))
    return EXIT_OK


def cmd_check(ctx):
    manifest = load_manifest(ctx.manifest_path)
    if not manifest['entries']:
        print('[phase2-retain] manifest 空 ⇒ check PASS（无可校验）')
        return EXIT_OK
    plan = plan_check(manifest, ctx.root_hashes(), ctx.overlay_hashes())
    bad = False
    for rel in plan['ok']:
        print('[phase2-retain][OK] %s' % rel)
    for rel in plan['missing']:
        bad = True
        print('[phase2-retain][FAIL] %s — pal3/src 侧缺失（被 codegen 冲掉/手删？）' % rel)
    for rel, want, got in plan['mismatch']:
        bad = True
        print('[phase2-retain][FAIL] %s — 内容不符（want %s… got %s…）'
              % (rel, want[:12], got[:12]))
    for rel in plan['no_overlay']:
        bad = True
        print('[phase2-retain][FAIL] %s — manifest 有条目但 overlay 缺文件' % rel)
    for rel in plan['orphans']:
        bad = True
        print('[phase2-retain][FAIL] %s — overlay 游离文件（manifest 无条目）' % rel)
    print('[phase2-retain] check %s（ok %d · missing %d · mismatch %d · '
          'no_overlay %d · orphan %d）'
          % ('FAIL' if bad else 'PASS', len(plan['ok']), len(plan['missing']),
             len(plan['mismatch']), len(plan['no_overlay']), len(plan['orphans'])))
    return EXIT_FAIL if bad else EXIT_OK


def cmd_adopt(ctx, rel):
    rel = normalize_rel(rel)
    src = os.path.join(ctx.root, rel)
    if not os.path.exists(src):
        print('[phase2-retain] adopt 失败：%s 不在 pal3/src' % rel)
        return EXIT_FAIL
    digest = sha256_file(src)
    dst = os.path.join(ctx.overlay, rel)
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    shutil.copyfile(src, dst)
    manifest = load_manifest(ctx.manifest_path)
    entry = manifest['entries'].get(rel, {})
    entry.update({'mode': entry.get('mode', 'override'), 'base_sha256': digest})
    manifest['entries'][rel] = entry
    save_manifest(ctx.manifest_path, manifest)
    print('[phase2-retain] adopt %s（base %s…）⇒ 请编辑 overlay 副本，'
          '随后 `apply` 落盘' % (rel, digest[:12]))
    return EXIT_OK


def cmd_diff(ctx, rel=None):
    o_hashes = ctx.overlay_hashes()
    rels = [normalize_rel(rel)] if rel else sorted(o_hashes)
    shown = 0
    for r in rels:
        op = os.path.join(ctx.overlay, r)
        rp = os.path.join(ctx.root, r)
        if not os.path.exists(op):
            print('[phase2-retain] %s — overlay 无此文件' % r)
            continue
        a = open(op, encoding='utf-8', errors='replace').read().splitlines(True)
        b = (open(rp, encoding='utf-8', errors='replace').read().splitlines(True)
             if os.path.exists(rp) else [])
        if a == b:
            print('[phase2-retain] %s — 与 pal3/src 一致（已应用）' % r)
            continue
        shown += 1
        for line in difflib.unified_diff(b, a, fromfile='pal3/src/' + r,
                                         tofile='phase2/overlay/' + r):
            sys.stdout.write(line)
    if not shown:
        print('[phase2-retain] 无差异（全部已应用）')
    return EXIT_OK


def cmd_rebase(ctx, rel=None):
    manifest = load_manifest(ctx.manifest_path)
    census = load_census(ctx.census_path)
    if not census:
        print('[phase2-retain] rebase 需要 %s（先跑一次 apply 产出 census）'
              % CENSUS_NAME)
        return EXIT_FAIL
    rels = [normalize_rel(rel)] if rel else sorted(manifest.get('entries', {}))
    n = 0
    for r in rels:
        e = manifest['entries'].get(r)
        if e is None:
            print('[phase2-retain] %s — manifest 无条目' % r)
            continue
        if e.get('new_unit'):
            print('[phase2-retain] %s — new_unit 无 base，跳过' % r)
            continue
        new = census.get(r)
        if not new:
            print('[phase2-retain] %s — census 无该文件（codegen 未产出？）' % r)
            continue
        old = e.get('base_sha256')
        e['base_sha256'] = new
        if old != new:
            n += 1
            print('[phase2-retain] rebase %s：%s… → %s…（请复核 overlay 是否仍适用）'
                  % (r, (old or 'None')[:12], new[:12]))
    save_manifest(ctx.manifest_path, manifest)
    print('[phase2-retain] rebase 完成：%d 条更新' % n)
    return EXIT_OK


def main(argv=None):
    ap = argparse.ArgumentParser(description='Phase 2 手工 fix 留存（overlay + 漂移门）')
    ap.add_argument('--root', default=DEFAULT_ROOT)
    ap.add_argument('--phase2', default=DEFAULT_PHASE2)
    sub = ap.add_subparsers(dest='cmd')
    sub.add_parser('apply')
    sub.add_parser('check')
    p = sub.add_parser('adopt')
    p.add_argument('relpath')
    p = sub.add_parser('diff')
    p.add_argument('relpath', nargs='?')
    p = sub.add_parser('rebase')
    p.add_argument('relpath', nargs='?')
    args = ap.parse_args(argv)
    ctx = Ctx(os.path.abspath(args.root), os.path.abspath(args.phase2))
    if args.cmd == 'apply':
        return cmd_apply(ctx)
    if args.cmd == 'check':
        return cmd_check(ctx)
    if args.cmd == 'adopt':
        return cmd_adopt(ctx, args.relpath)
    if args.cmd == 'diff':
        return cmd_diff(ctx, args.relpath)
    if args.cmd == 'rebase':
        return cmd_rebase(ctx, args.relpath)
    ap.print_help()
    return EXIT_FAIL


if __name__ == '__main__':
    sys.exit(main())
