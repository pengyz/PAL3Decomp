#!/usr/bin/env python3
"""[status 清债 2026-11-23·用户裁定四项之四] data/status 定性调研结论执行。

调研结论(agent 全量定性): status=运行状态对账层——
  活基线/裁决台账/pending/ = 绝不能删(L1 棘轮/编译门/annotation 门/25 测试消费)
  baselines/ 时间戳快照 696个/195MB = 只被 latest.json 消费, 快照纯死重
  c 类一次性调查产物 ≈262个/25MB = 抽样20/20零引用
整体删除=NO; 可安全清理 ≈970文件/222MB(75%)。

清理规则(保守三闸):
  ①baselines/: 保 latest.json + 最近5个时间戳快照 + 显式点名, 其余删
  ②顶层文件: basename 全仓引用扫(pipeline/tools/tests/docs/CLAUDE.md/.zcode),
    零命中才删; 治理文档(gate_registry/baseline_authority/G0_BASELINE等)白名单保
  ③_tmp/ __pycache__ 直接删
git 历史=归档(HEAD 删除不丢数据)。
"""
import glob
import json
import os
import subprocess
import sys

REPO = '/home/peng/workspace/PAL3Decomp'
STATUS = os.path.join(REPO, 'data', 'status')

# 治理/台账白名单(basename 精确保)
KEEP_EXACT = {
    # 活 gate/基线(agent 尽调活消费清单)
    's4_baseline.json', 's4_diff_detail.json', 's4_l1_identity_cur.json',
    'compile_baseline.json', 'probe_census.json', 'check_baseline_errors.json',
    'canonical_contract_baseline.json', 'claim_gate_baseline.json',
    'quality_baseline.json', 'quality_equiv_baseline.json',
    'vtable_ratchet_baseline.json', 'vtable_baseline.json',
    'codegen_invariant_baseline.json', 'incremental_state.json',
    'link_census.json', 'expected_symbols.json', 'flags_matrix.json',
    'ctor_evidence_registry_20261117.json', 'true_vtable_map_20261114.json',
    'bases_adjudications.json', 'bases_snapshot.json', 'dossier_pending.json',
    'n12_grandfathered.json', 'n22_pair_closure.json',
    'global_categories.json', '_decomp_derived_header_facts.json',
    'globals_partition.json', 'audit_proposal.json',
    'annotation_completeness_baseline.json', 'annotation_quality_ledger.md',
    'evidence_ledger.json', '_loop_last.json', 'latest.json',
    # 治理文档(历史裁决记录, 保留成本可忽略)
    'G0_BASELINE.md', 'gate_registry.md', 'baseline_authority.md',
    '_d1_ledger.md', '_layout_gate_adjudications.md',
}


def referenced(basename):
    """basename 全仓引用扫(git grep 快), 命中即保留。"""
    r = subprocess.run(['git', 'grep', '-l', '-F', basename, '--',
                        'pipeline', 'tools', 'tests', 'docs', 'CLAUDE.md',
                        '.zcode', 'README.md'],
                       cwd=REPO, capture_output=True, text=True)
    return bool(r.stdout.strip())


def main():
    dry = '--apply' not in sys.argv
    removed_f, removed_b = 0, 0

    # ①baselines/: 保 latest + 最近5快照
    bl = sorted(glob.glob(os.path.join(STATUS, 'baselines', '2*.json')))
    keep_bl = set(bl[-5:]) | {os.path.join(STATUS, 'baselines', 'latest.json')}
    for f in bl:
        if f not in keep_bl:
            removed_b += 1
            if not dry:
                os.remove(f)
    print('baselines/ 时间戳快照: 删 %d / 留 %d' % (removed_b, len(keep_bl)))

    # ②顶层文件: 引用扫
    tops = [f for f in glob.glob(os.path.join(STATUS, '*')) if os.path.isfile(f)]
    keep_names = set()
    for f in tops:
        b = os.path.basename(f)
        if b in KEEP_EXACT or referenced(b):
            keep_names.add(b)
        else:
            removed_f += 1
            if not dry:
                os.remove(f)
    print('顶层文件: 删 %d / 留 %d (白名单+引用命中)' % (removed_f, len(keep_names)))

    # ③_tmp/ __pycache__
    import shutil
    for d in ('_tmp', '__pycache__'):
        p = os.path.join(STATUS, d)
        if os.path.isdir(p):
            shutil.rmtree(p, ignore_errors=True)
            print('删目录:', d)

    if dry:
        print('== DRY RUN(加 --apply 执行) ==')
    else:
        print('== 已执行 ==')


if __name__ == '__main__':
    main()
