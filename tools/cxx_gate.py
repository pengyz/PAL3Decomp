"""强检测闸（2026-11-02）——重名必被查出（用户铁律）。
三门：①same_addr 同址大小写双录 ②same_name 同(类)全同名双址
③cxx_rule C++ 铁律(类,归一名,严格签名)双址（合成物豁免）。
棘轮形：存量 grandfather 基线冻结 · 新增=硬红 · 清理后基线刷新。
用法: python3 tools/cxx_gate.py [--bootstrap]
"""
# ── stdio UTF-8 单源引导：Windows GBK 控制台 print ⚠/⇒ 即崩（UnicodeEncodeError）──
# 单源: pipeline/utf8_stdio.py · gotcha: docs/knowledge/gotcha_windows_gbk_stdio_unicode_crash.md
import os as _os8, sys as _sys8
_sys8.path.append(_os8.path.dirname(_os8.path.dirname(_os8.path.abspath(__file__))))
from pipeline.utf8_stdio import force_utf8_stdio as _force_utf8_stdio
_force_utf8_stdio()
import glob
import json
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / 'data/status/cxx_gate_baseline.json'


def evaluate_cxx_gate(violations, baseline, resolved):
    errs, warns = [], []
    for k in sorted(set(violations) - set(baseline)):
        errs.append('CXX_GATE:new_violation:%s' % k)
    for k in sorted(set(baseline) & set(resolved or ())):
        warns.append('CXX_GATE:baseline_stale:%s' % k)
    return errs, warns


def collect_violations(entries):
    """entries=[{addr,class,name,sig}] → 违规键集（三门）。"""
    import re
    import importlib.util
    _sp = importlib.util.spec_from_file_location(
        'ccd', str(ROOT / 'tools' / 'cxx_collision_detector.py'))
    ccd = importlib.util.module_from_spec(_sp); _sp.loader.exec_module(ccd)
    v = set()
    by_addr = defaultdict(list)
    by_name = defaultdict(list)
    by_rule = defaultdict(list)
    for e in entries:
        by_addr[int(str(e['addr']), 16)].append(e)
        by_name[(e.get('class') or '', e.get('name'))].append(e)
        if not ccd.SYNTH.search(e.get('name') or ''):
            k = (e.get('class') or '', ccd.canon_name(e.get('name')),
                 ccd.cxx_sig_key(e.get('sig') or ''))
            by_rule[k].append(e)
    for a, es in by_addr.items():
        if len(es) > 1:
            v.add('same_addr:0x%X:%s' % (a, '|'.join(sorted(x['name'] for x in es))))
    for (cls, nm), es in by_name.items():
        if len(es) > 1:
            # [2026-11-02 G2] 同名异签=合法重载 ⇒ 闸②签名感知（仅同签双址=违规）
            _sk = {ccd.cxx_sig_key(e.get('sig') or '') for e in es}
            if len(_sk) < len(es):
                v.add('same_name:%s:%s:x%d' % (cls or 'global', nm, len(es)))
    for k, es in by_rule.items():
        if len(es) > 1:
            v.add('cxx_rule:%s:%s:%s:x%d' % (k[0] or 'global', k[1], k[2], len(es)))
    return v


def load_entries():
    entries = []
    for f in glob.glob(str(ROOT / 'data/annotations/structs/*.json')):
        d = json.load(open(f, encoding='utf-8'))
        cls = d.get('name') or ''
        for addr, m in (d.get('methods') or {}).items():
            if isinstance(m, dict) and m.get('name'):
                entries.append({'addr': addr, 'class': cls, 'name': m['name'],
                                'sig': m.get('signature') or ''})
    for addr, m in json.load(open(ROOT / 'data/annotations/functions.json', encoding='utf-8')).items():
        if isinstance(m, dict) and m.get('name'):
            entries.append({'addr': addr, 'class': '', 'name': m['name'],
                            'sig': m.get('signature') or ''})
    return entries


def main(bootstrap=False):
    v = collect_violations(load_entries())
    if bootstrap:
        BASELINE.write_text(json.dumps({'baseline': sorted(v)}, ensure_ascii=False, indent=2),
                            encoding='utf-8')
        print('基线自举: %d 违规键冻结' % len(v))
        return [], []
    b = json.load(open(BASELINE, encoding='utf-8')) if BASELINE.exists() else {'ERROR': 'baseline_missing'}
    if 'ERROR' in b:
        return ['CXX_GATE:baseline_missing (fail-loud 禁自举)'], []
    baseline = set(b.get('baseline', []))
    resolved = baseline - v
    return evaluate_cxx_gate(v, baseline, resolved)


if __name__ == '__main__':
    import sys
    if '--bootstrap' in sys.argv:
        main(bootstrap=True)
    else:
        errs, warns = main()
        print('errs=%d warns=%d' % (len(errs), len(warns)))
        for e in errs[:8]:
            print(' ', e)
        for w in warns[:4]:
            print('  warn:', w)
        # 新增违规=硬红须有出口码（2026-11-04 修：此前只打印不退出 ⇒ "硬红"无牙齿）
        sys.exit(1 if errs else 0)
