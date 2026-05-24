"""Decomp quality metrics: field coverage + type correctness.

Measures Hex-Rays decompilation quality based on struct annotation effectiveness.
Designed to run after export (on decomp JSON), independent of compile results.

Usage:
    python pipeline/decomp_quality.py              # full scan
    python pipeline/decomp_quality.py --brief      # one-line summary
    python pipeline/decomp_quality.py --threshold  # exit 1 if regression detected
"""
import json
import glob
import os
import re
import sys

DECOMP_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'asm', 'pal3', 'decomp')
SNAPSHOT_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'pipeline', '_logs', 'quality_baseline.json')


def _load_struct_sizes():
    """Load binary_size for all structs (for attribution check)."""
    sizes = {}
    structs_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'data', 'annotations', 'structs')
    for f in glob.glob(os.path.join(structs_dir, '*.json')):
        sname = os.path.basename(f).replace('.json', '')
        try:
            ann = json.load(open(f, encoding='utf-8'))
            bs = ann.get('binary_size', 0)
            if bs:
                sizes[sname] = bs
        except:
            pass
    return sizes


def measure():
    """Scan all decomp JSONs and compute quality metrics."""
    _struct_sizes = _load_struct_sizes()
    total_funcs = 0
    thiscall_funcs = 0
    typed_this = 0       # ClassName *this (good)
    untyped_this = 0     # int this / void *this (bad)

    field_accesses = 0   # this->m_name pattern
    raw_offsets = 0      # *(this+N), *(_TYPE*)(this+N) pattern
    named_globals = 0    # g_XXX named globals
    raw_globals = 0      # dword_/byte_/off_ unnamed globals
    misattrib_funcs = 0  # functions accessing offsets >> class size

    for f in glob.glob(os.path.join(DECOMP_DIR, '*.json')):
        try:
            d = json.load(open(f, encoding='utf-8'))
            code = d.get('decompiled_c', '')
            if not code:
                continue
            total_funcs += 1

            first_line = code.split('\n')[0]

            # Type correctness: check this parameter type
            if '__thiscall' in first_line:
                thiscall_funcs += 1
                m = re.search(r'__thiscall\s+\w+::\w+\((.+?)\s+\*?\s*this[,)]', first_line)
                if m:
                    this_type = m.group(1).strip().rstrip('*').strip()
                    if this_type in ('int', 'void', '_DWORD', 'unsigned int'):
                        untyped_this += 1
                    else:
                        typed_this += 1
                else:
                    untyped_this += 1

            # Field coverage: count named field access vs raw offset
            field_accesses += len(re.findall(r'this->\w+', code))

            # Raw offset patterns (various Hex-Rays output forms)
            raw_offsets += len(re.findall(r'\*\(\s*\(_[A-Z]+\s*\*\s*\)\s*this\s*\+', code))
            raw_offsets += len(re.findall(r'\*\(\s*\(\s*_[A-Z]+\s*\*\s*\)\s*this\s*\+', code))
            raw_offsets += len(re.findall(r'\*\(\s*this\s*\+\s*\d+\s*\)', code))
            raw_offsets += len(re.findall(r'\*\(\(_[A-Z]+\s*\*\)this\s*\+\s*\d+\)', code))

            # Global variable coverage
            named_globals += len(re.findall(r'\bg_\w+', code))
            raw_globals += len(re.findall(r'\b(?:dword|byte|word|off|qword|unk)_[0-9A-Fa-f]+', code))

            # Misattribution detection: function accesses offsets far beyond class size
            if '__thiscall' in first_line:
                cls_match = re.match(r'.*__thiscall\s+(\w+)::', first_line)
                if cls_match:
                    cls_name = cls_match.group(1)
                    cls_size = _struct_sizes.get(cls_name, 0)
                    if cls_size > 0:
                        offsets = [int(x) for x in re.findall(r'this\s*\+\s*(\d+)', code)]
                        if offsets and max(offsets) > cls_size * 2:
                            misattrib_funcs += 1

        except (json.JSONDecodeError, KeyError):
            continue

    type_rate = typed_this / max(thiscall_funcs, 1)
    field_rate = field_accesses / max(field_accesses + raw_offsets, 1)
    global_rate = named_globals / max(named_globals + raw_globals, 1)
    attrib_rate = 1.0 - (misattrib_funcs / max(thiscall_funcs, 1))

    return {
        'total_funcs': total_funcs,
        'thiscall_funcs': thiscall_funcs,
        'typed_this': typed_this,
        'untyped_this': untyped_this,
        'type_correctness': round(type_rate, 4),
        'field_accesses': field_accesses,
        'raw_offsets': raw_offsets,
        'field_coverage': round(field_rate, 4),
        'named_globals': named_globals,
        'raw_globals': raw_globals,
        'global_coverage': round(global_rate, 4),
        'misattrib_funcs': misattrib_funcs,
        'attribution_accuracy': round(attrib_rate, 4),
    }


def load_baseline():
    if os.path.exists(SNAPSHOT_FILE):
        return json.load(open(SNAPSHOT_FILE, encoding='utf-8'))
    return None


def save_baseline(metrics):
    os.makedirs(os.path.dirname(SNAPSHOT_FILE), exist_ok=True)
    json.dump(metrics, open(SNAPSHOT_FILE, 'w', encoding='utf-8'), indent=2)


def check_regression(metrics, baseline):
    """Return list of regression warnings."""
    warnings = []
    if baseline is None:
        return warnings

    # Type correctness: alert if drops > 5%
    if metrics['type_correctness'] < baseline['type_correctness'] - 0.05:
        warnings.append(
            'type_correctness REGRESSED: %.1f%% -> %.1f%%' % (
                baseline['type_correctness'] * 100, metrics['type_correctness'] * 100))

    # Field coverage: alert if drops > 5%
    if metrics['field_coverage'] < baseline['field_coverage'] - 0.05:
        warnings.append(
            'field_coverage REGRESSED: %.1f%% -> %.1f%%' % (
                baseline['field_coverage'] * 100, metrics['field_coverage'] * 100))

    # Global coverage: alert if drops > 5%
    if metrics['global_coverage'] < baseline.get('global_coverage', 0) - 0.05:
        warnings.append(
            'global_coverage REGRESSED: %.1f%% -> %.1f%%' % (
                baseline.get('global_coverage', 0) * 100, metrics['global_coverage'] * 100))

    # Attribution accuracy: alert if drops > 5%
    if metrics['attribution_accuracy'] < baseline.get('attribution_accuracy', 0) - 0.05:
        warnings.append(
            'attribution_accuracy REGRESSED: %.1f%% -> %.1f%%' % (
                baseline.get('attribution_accuracy', 0) * 100, metrics['attribution_accuracy'] * 100))

    return warnings


def main():
    brief = '--brief' in sys.argv
    threshold = '--threshold' in sys.argv
    save = '--save' in sys.argv

    metrics = measure()

    if brief:
        print('quality: type=%.1f%% field=%.1f%% (typed=%d/%d, field=%d raw=%d)' % (
            metrics['type_correctness'] * 100,
            metrics['field_coverage'] * 100,
            metrics['typed_this'], metrics['thiscall_funcs'],
            metrics['field_accesses'], metrics['raw_offsets']))
        return

    print('Decomp Quality Report')
    print('=' * 50)
    print(f'  Total functions:     {metrics["total_funcs"]}')
    print(f'  Thiscall functions:  {metrics["thiscall_funcs"]}')
    print()
    print(f'  TYPE CORRECTNESS:    {metrics["type_correctness"]*100:.1f}%')
    print(f'    Typed this:        {metrics["typed_this"]}')
    print(f'    Untyped this:      {metrics["untyped_this"]}')
    print()
    print(f'  FIELD COVERAGE:      {metrics["field_coverage"]*100:.1f}%')
    print(f'    Named accesses:    {metrics["field_accesses"]}')
    print(f'    Raw offsets:       {metrics["raw_offsets"]}')
    print()
    print(f'  GLOBAL COVERAGE:     {metrics["global_coverage"]*100:.1f}%')
    print(f'    Named globals:     {metrics["named_globals"]}')
    print(f'    Raw globals:       {metrics["raw_globals"]}')
    print()
    print(f'  ATTRIBUTION:         {metrics["attribution_accuracy"]*100:.1f}%')
    print(f'    Misattributed:     {metrics["misattrib_funcs"]}/{metrics["thiscall_funcs"]}')

    baseline = load_baseline()
    if baseline:
        print()
        print('  vs Baseline:')
        dt = metrics['type_correctness'] - baseline.get('type_correctness', 0)
        df = metrics['field_coverage'] - baseline.get('field_coverage', 0)
        dg = metrics['global_coverage'] - baseline.get('global_coverage', 0)
        da = metrics['attribution_accuracy'] - baseline.get('attribution_accuracy', 0)
        print(f'    type_correctness:  {dt*100:+.1f}%')
        print(f'    field_coverage:    {df*100:+.1f}%')
        print(f'    global_coverage:   {dg*100:+.1f}%')
        print(f'    attribution:       {da*100:+.1f}%')

    warnings = check_regression(metrics, baseline)
    if warnings:
        print()
        for w in warnings:
            print(f'  [REGRESSION] {w}')

    if save:
        save_baseline(metrics)
        print(f'\n  Baseline saved to {SNAPSHOT_FILE}')

    if threshold and warnings:
        sys.exit(1)


if __name__ == '__main__':
    main()
