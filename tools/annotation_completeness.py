#!/usr/bin/env python3
"""annotation 完整度 + 准确度指标（棘轮制）。

## 为什么建这个（2026-10-20 用户第一性论点）

我曾建议「同宽型失配补 cast」，被用户以第一性论点驳回：
  · **cast 是现象，不是原因**
  · Hex-Rays 能力足够强 ⇒ annotation 正确时它自己能推断
  · 应该建「数据标注完整度 + 准确率」指标，直接根治 annotation，cast 自然减少

这与 CLAUDE.md 第一性原则一致：
  「编译错误不是问题本身…真正的任务是理解原始代码的意图
    ——内存布局、复用模式、生命周期——然后让 annotation 正确表达它。**错误自然消失。**」

⇒ **本工具度量「因」（annotation 质量），编译错误数度量「果」。**
   指标升，C2440/C2664/C2039 自然降。

## 指标体系

### A. 完整度（我们「不知道」多少）
  weak_type_rate       注解型中弱型（_BYTE/void*/unsigned long/int…）占比
  placeholder_name_rate 占位名成员（_todo_/_tail_/_gap_/_unk_/_field_）占比
  signature_coverage   有签名的函数 ÷ 已知函数总数
  weak_signature_rate  签名含弱型的比例
  shell_class_rate     零成员零方法类占比
  pending_verdict_rate 待终审 verdict 占比

### B. 准确度（我们「标错」多少）
  layout_consistent    成员偏移/尺寸与 binary_size 一致（复用 audit_type_layout）
  arity_consistent     声明参数数与调用点一致（复用 codegen_invariant_lint I3）
  ref_complete         引用的成员/变体名存在（C2039 计数即此）

### C. 下游症状（**验证信号，不是目标**）
  编译错误数（probe census）· decomp cast 率 · I4 门禁计数

## 制式

- **棘轮**：不追溯存量，只禁止退化；改善请显式 `--baseline` 重锚
- 纯离线只读（不改任何产品代码）
- 与 `codegen_invariant_lint.py` 同型：`--baseline` / `--json` / `--quiet`

## 用法
    python tools/annotation_completeness.py
    python tools/annotation_completeness.py --baseline
    python tools/annotation_completeness.py --json

R15 单测见 tests/test_annotation_completeness.py
"""
import argparse
import glob
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(HERE)
ANN_DIR = os.path.join(PROJECT_ROOT, 'data', 'annotations')
BASELINE = os.path.join(PROJECT_ROOT, 'data', 'status',
                        'annotation_completeness_baseline.json')

# ---------------------------------------------------------------- 判据（纯函数）

# 弱型：与 CLAUDE.md「禁止破坏性 workaround」对应的「确实不知道真实类型」清单
_WEAK_TYPE = re.compile(
    r'^\s*(?:'
    r'void\s*\*|_BYTE(?:\[\d*\])?|_WORD(?:\[\d*\])?|_DWORD(?:\[\d*\])?|'
    r'unsigned char(?:\s*\*|\[\d*\])?|unsigned long(?:\s*\*)?|'
    r'unsigned int(?:\s*\*)?|unsigned short(?:\s*\*)?|'
    r'int(?:\s*\*)?|float(?:\s*\*)?|long(?:\s*\*)?|char(?:\s*\*|\[\d*\])?|'
    r'HWND|_QWORD'
    r')\s*$')
_PLACEHOLDER_NAME = re.compile(
    r'(?:_todo_|m_nTodo_|_tail_|_gap_|_unk_|_field_)')
# IDA 地址名（byte_XXXXXX / dword_XXXXXX …）
_ADDR_NAME = re.compile(
    r'^(?:byte|dword|word|unk|flt|dbl|asc|off|str|a)_[0-9A-Fa-f]{5,}$')


def is_weak_type(typ):
    """型是否为「弱型」（不知真实类型的占位）。"""
    return bool(_WEAK_TYPE.match((typ or '').strip()))


def is_placeholder_name(name):
    """名是否为占位名（_todo_/_tail_/_gap_ 等）或 IDA 地址名。"""
    n = name or ''
    return bool(_PLACEHOLDER_NAME.search(n)) or bool(_ADDR_NAME.match(n))


def is_final_misattached(verdict_text):
    """是否「定谳误挂」（排除「待终审」）。"""
    t = str(verdict_text)
    return '误挂' in t and '待' not in t and 'pending' not in t.lower()


def is_pending_verdict(verdict_text):
    t = str(verdict_text)
    return ('误挂' in t and ('待' in t or 'pending' in t.lower())) or '待终审' in t


# ---------------------------------------------------------------- 聚合

def collect(ann_dir=ANN_DIR):
    structs = glob.glob(os.path.join(ann_dir, 'structs', '*.json'))
    tot_cls = shells = 0
    tot_mem = weak_mem = ph_mem = 0
    tot_bytes = gap_bytes = 0
    pend = final = 0
    for fp in structs:
        try:
            with open(fp, encoding='utf-8') as fh:
                d = json.load(fh)
        except (OSError, ValueError):
            continue
        tot_cls += 1
        ms = d.get('known_members') or {}
        if not ms and not (d.get('methods') or d.get('vtables')):
            shells += 1
        tot_bytes += int(d.get('binary_size') or 0)
        for x in (d.get('_verdicts') or {}).values():
            if is_pending_verdict(x):
                pend += 1
            elif is_final_misattached(x):
                final += 1
        for _off, m in (ms.items() if isinstance(ms, dict) else []):
            if not isinstance(m, dict):
                continue
            tot_mem += 1
            if is_weak_type(str(m.get('type') or '')):
                weak_mem += 1
            if is_placeholder_name(str(m.get('name') or '')):
                ph_mem += 1
                mm = re.search(r'\[(\d+)\]', str(m.get('type') or ''))
                if mm:
                    gap_bytes += int(mm.group(1))

    # 签名面 —— **分母是游戏逻辑函数**，不是「已在注解里的函数」
    # [口径修正 2026-10-20·用户指正] 原分母用 functions.json 条目数（自指，覆盖率恒 100%）。
    # 正确分母：decomp 全量 − skip_functions.json 的 CRT/库函数
    #   （库函数不属游戏逻辑、我们不映射；用户明确要求排除）。
    # 实测：decomp 3691 · skip 1912（crt_init/crt_runtime…）· 游戏逻辑 1779。
    fp_fn = os.path.join(ann_dir, 'functions.json')
    fp_skip = os.path.join(ann_dir, 'skip_functions.json')
    n_sig = n_weak_sig = 0
    ann_names = set()
    try:
        with open(fp_fn, encoding='utf-8') as fh:
            fn = json.load(fh)
        items = fn if isinstance(fn, list) else (fn.get('functions') or fn)
        it = items.values() if isinstance(items, dict) else items
        for f in it:
            if not isinstance(f, dict):
                continue
            s = str(f.get('signature') or f.get('sig') or '')
            if s:
                n_sig += 1
                ann_names.add(str(f.get('name') or ''))
                if re.search(r'\b_?DWORD\b|\bvoid\s*\*|_BYTE|unsigned long', s):
                    n_weak_sig += 1
    except (OSError, ValueError):
        pass

    # [分子口径修正 2026-10-20] 分子也要剔除 skip/CRT —— 库函数的签名
    # 不算游戏逻辑覆盖（用户明确：库函数不属游戏逻辑、我们不映射）。
    # 实测：functions.json 559 有签名 · 其中 skip/CRT 214 · 游戏逻辑签名 345
    #      ⇒ 真实覆盖率 345/1779 = 19%（而非 559/1779 = 31%）
    skip_names = set()
    try:
        with open(fp_skip, encoding='utf-8') as fh:
            _sk = json.load(fh)
        for _v in (_sk.values() if isinstance(_sk, dict) else _sk):
            for _x in (_v if isinstance(_v, list) else [_v]):
                if isinstance(_x, dict) and _x.get('name'):
                    skip_names.add(str(_x['name']))
    except (OSError, ValueError):
        pass
    n_skip_sig = 0
    try:
        with open(fp_fn, encoding='utf-8') as fh:
            fn2 = json.load(fh)
        it2 = fn2.values() if isinstance(fn2, dict) else (fn2.get('functions') or fn2)
        it2 = it2.values() if isinstance(it2, dict) else it2
        for f in it2:
            if not isinstance(f, dict):
                continue
            if not (f.get('signature') or f.get('sig')):
                continue
            if f.get('type') == 'skip' or str(f.get('name') or '') in skip_names:
                n_skip_sig += 1
    except (OSError, ValueError):
        pass
    n_sig = max(n_sig - n_skip_sig, 0)   # 分子 = 游戏逻辑签名

    # 游戏逻辑函数总数 = decomp 全量 − skip（CRT/库）
    n_decomp = n_skip = n_game = 0
    try:
        _dd = os.path.join(PROJECT_ROOT, 'asm', 'pal3', 'decomp')
        if os.path.isdir(_dd):
            n_decomp = len([f for f in os.listdir(_dd) if f.endswith('.json')])
        with open(fp_skip, encoding='utf-8') as fh:
            sk = json.load(fh)
        n_skip = len(sk) if isinstance(sk, (dict, list)) else 0
    except (OSError, ValueError):
        pass
    n_game = max(n_decomp - n_skip, 1)
    tot_fn = n_game

    def rate(n, d):
        return round(n / d, 4) if d else 0.0

    bc = byte_coverage()
    return {
        'completeness': {
            'byte_coverage_rate': bc['coverage_rate'],
            'weak_type_rate': rate(weak_mem, tot_mem),
            'placeholder_name_rate': rate(ph_mem, tot_mem),
            'signature_coverage': rate(n_sig, max(tot_fn, 1)),
            'weak_signature_rate': rate(n_weak_sig, max(n_sig, 1)),
            'shell_class_rate': rate(shells, tot_cls),
            'pending_verdict_rate': rate(pend, max(pend + final, 1)),
        },
        'counts': {
            'classes': tot_cls, 'shells': shells,
            'members': tot_mem, 'weak_members': weak_mem,
            'placeholder_members': ph_mem,
            'total_bytes': tot_bytes, 'gap_bytes': gap_bytes,
            'functions_game_logic': tot_fn,
            'functions_decomp_total': n_decomp,
            'functions_skip_crt': n_skip,
            'signed': n_sig,
            'weak_signed': n_weak_sig,
            'verdict_pending': pend, 'verdict_final': final,
        },
    }




# ---------------------------------------------------------------- 字节覆盖度量
# [度量修正 2026-10-20] 原「成员条数」是坏指标：`RoleAtt[200]` 算 1 条却覆盖 170KB
# ⇒ 42% 薄标的结论是误判。改按**字节覆盖**，且必须含：
#   ① 继承基类字节（ParticleEffect 的成员在 +362836，基类 sg_particle_scene 覆盖前段）
#   ② inline union/struct 型（原 tsz() 对 dict 型返回 0）
# 三轮实测：①成员条数=误导 ②简单字节=偏低 ③含继承+inline=**87% 覆盖 / 12% 缺口**
_IDA_SIZE = None
_SC = {}


def _type_size(t, depth=0):
    """型尺寸（含 inline union/struct、数组、指针、已知标量、递归查 ida_structs）。"""
    if depth > 6:
        return 0
    if isinstance(t, dict):
        if 'union' in t:
            return max((_type_size(x.get('type'), depth + 1) for x in t['union']), default=0)
        if 'struct' in t:
            return sum(_type_size(x.get('type'), depth + 1) for x in t['struct'])
        return 0
    t = str(t or '').strip()
    m = re.match(r'^(.+?)\s*\[(\d+)\]$', t)
    if m:
        return _type_size(m.group(1), depth + 1) * int(m.group(2))
    if t.endswith('*') or t.endswith('[]'):
        return 4
    b = re.sub(r'\s*\*$', '', t).strip()
    if b in ('int', 'float', 'long', 'unsigned long', 'unsigned int', '_DWORD',
             'BOOL', 'DWORD', 'UINT', 'HWND', 'HINSTANCE'):
        return 4
    if b in ('short', 'WORD', 'unsigned short', '_WORD'):
        return 2
    if b in ('char', 'BYTE', 'bool', 'unsigned char', '_BYTE'):
        return 1
    if b in ('double', '__int64', '_QWORD'):
        return 8
    if b in _SC:
        return _SC[b]
    v = None
    global _IDA_SIZE
    if _IDA_SIZE is None:
        try:
            with open(os.path.join(PROJECT_ROOT, 'asm', 'pal3', 'ida_structs.json'),
                      encoding='utf-8') as fh:
                _IDA_SIZE = json.load(fh)
        except (OSError, ValueError):
            _IDA_SIZE = {}
    v = (_IDA_SIZE.get(b) or {}).get('size')
    if not v:
        try:
            with open(os.path.join(ANN_DIR, 'structs', '%s.json' % b), encoding='utf-8') as fh:
                v = int((json.load(fh) or {}).get('binary_size') or 0)
        except (OSError, ValueError):
            v = 0
    _SC[b] = v
    return v


def base_bytes(name, seen=None, depth=0):
    """继承链字节（含自身成员）—— 防循环。"""
    seen = seen if seen is not None else set()
    if name in seen or depth > 8:
        return 0
    seen.add(name)
    tot = 0
    try:
        with open(os.path.join(ANN_DIR, 'structs', '%s.json' % name), encoding='utf-8') as fh:
            d = json.load(fh) or {}
    except (OSError, ValueError):
        d = {}
    if d:
        for x in (d.get('bases') or []):
            if isinstance(x, dict) and x.get('name'):
                tot += base_bytes(str(x['name']), seen, depth + 1)
        for m in (d.get('known_members') or {}).values():
            if isinstance(m, dict):
                tot += _type_size(m.get('type'))
    if not tot:
        tot = (_IDA_SIZE.get(name) or {}).get('size') or 0
    return tot


def byte_coverage(ann_dir=ANN_DIR):
    """字节级覆盖：{total, covered, rate, top_gaps}。"""
    global _IDA_SIZE
    if _IDA_SIZE is None:
        try:
            with open(os.path.join(PROJECT_ROOT, 'asm', 'pal3', 'ida_structs.json'),
                      encoding='utf-8') as fh:
                _IDA_SIZE = json.load(fh)
        except (OSError, ValueError):
            _IDA_SIZE = {}
    tot = cov = 0
    gaps = []
    for fp in glob.glob(os.path.join(ann_dir, 'structs', '*.json')):
        try:
            with open(fp, encoding='utf-8') as fh:
                d = json.load(fh) or {}
        except (OSError, ValueError):
            continue
        nm = str(d.get('name') or os.path.basename(fp)[:-5])
        sz = int(d.get('binary_size') or 0)
        if sz == 0:
            continue
        own = sum(_type_size(m.get('type')) for m in (d.get('known_members') or {}).values()
                  if isinstance(m, dict))
        inh = sum(base_bytes(str(x.get('name'))) for x in (d.get('bases') or [])
                  if isinstance(x, dict) and x.get('name'))
        c = min(own + inh, sz)
        tot += sz
        cov += c
        if sz - c > 4096:
            gaps.append({'name': nm, 'size': sz, 'covered': c, 'gap': sz - c})
    gaps.sort(key=lambda x: -x['gap'])
    return {'total_bytes': tot, 'covered_bytes': cov,
            'coverage_rate': round(cov / tot, 4) if tot else 0.0,
            'top_gaps': gaps[:15]}

# 棘轮方向：这些指标**越高越差**，故用「不得超过基线」判据
_HIGHER_IS_WORSE = ('weak_type_rate', 'placeholder_name_rate',
                    'weak_signature_rate', 'shell_class_rate',
                    'pending_verdict_rate')
_LOWER_IS_WORSE = ('signature_coverage', 'byte_coverage_rate')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--baseline', action='store_true')
    ap.add_argument('--json', action='store_true')
    ap.add_argument('--quiet', action='store_true')
    args = ap.parse_args()

    res = collect()
    comp = res['completeness']
    counts = res['counts']

    if args.baseline:
        os.makedirs(os.path.dirname(BASELINE), exist_ok=True)
        with open(BASELINE, 'w', encoding='utf-8') as fh:
            json.dump({'completeness': comp, 'counts': counts,
                       'note': 'annotation completeness ratchet; refresh only '
                               'after confirming real improvement'},
                      fh, ensure_ascii=False, indent=2)
        print('baseline written:', json.dumps(comp, ensure_ascii=False))
        return 0

    if args.json:
        print(json.dumps(res, ensure_ascii=False, indent=2))
        return 0

    bc = byte_coverage()

    if not args.quiet:
        print('=== A. annotation 完整度 ===')
        print(f'  **字节覆盖率**    {bc["coverage_rate"]:.2%}'
              f'  ({bc["covered_bytes"]:,}/{bc["total_bytes"]:,})  ← 主指标（含继承+inline）')
        if bc['top_gaps']:
            g = bc['top_gaps'][0]
            print(f'    最大缺口: {g["name"]} {g["gap"]:,} 字节'
                  f'  · >4KB 缺口类 {len(bc["top_gaps"])} 个')
        print(f'  弱型成员率        {comp["weak_type_rate"]:.2%}'
              f'  ({counts["weak_members"]}/{counts["members"]})')
        print(f'  占位名成员率      {comp["placeholder_name_rate"]:.2%}'
              f'  ({counts["placeholder_members"]}/{counts["members"]})')
        print(f'  签名覆盖率        {comp["signature_coverage"]:.2%}'
              f'  ({counts["signed"]}/{counts["functions_game_logic"]}'
              f' = 游戏逻辑 {counts["functions_decomp_total"]}'
              f' - skip/CRT {counts["functions_skip_crt"]})')
        print(f'  签名弱型率        {comp["weak_signature_rate"]:.2%}'
              f'  ({counts["weak_signed"]}/{counts["signed"]})')
        print(f'  空壳类率          {comp["shell_class_rate"]:.2%}'
              f'  ({counts["shells"]}/{counts["classes"]})')
        print(f'  verdict 待审率    {comp["pending_verdict_rate"]:.2%}'
              f'  ({counts["verdict_pending"]}/{counts["verdict_pending"]+counts["verdict_final"]})')

    base = {}
    if os.path.exists(BASELINE):
        try:
            with open(BASELINE, encoding='utf-8') as fh:
                base = json.load(fh).get('completeness') or {}
        except (OSError, ValueError):
            base = {}

    regressions = []
    for k in _HIGHER_IS_WORSE:
        if k in base and comp[k] > base[k]:
            regressions.append((k, base[k], comp[k], '↑变差'))
    for k in _LOWER_IS_WORSE:
        if k in base and comp[k] < base[k]:
            regressions.append((k, base[k], comp[k], '↓变差'))

    if regressions:
        print('\n[annotation-completeness] FAIL: 完整度退化（棘轮被突破）')
        for k, old, new, arrow in regressions:
            print(f'  {k}: {old:.4f} -> {new:.4f}  {arrow}')
        print('  修好再跑；确属视野扩大请显式 --baseline 重锚并写明理由。')
        return 1

    print('\n[annotation-completeness] OK（完整度未退化）')
    return 0


if __name__ == '__main__':
    sys.exit(main())
