#!/usr/bin/env python3
"""[KEYCASE 归一 2026-11-23·用户裁定] 所有在用 JSON 十六进制字面量一律小写规范形。

起因: skip_functions.json 键 `0x004CB3A0`(大写) vs structs methods 键
`0x004cb3a0`(小写)——check 第5条 skip×methods 冲突门裸字符串比较被大小写
击败(0x4cb3a0 三类 ctor 的 skip 双注未检出)。用户裁定: 消费侧 int() 免疫
是使用侧的事, **检查是通用强制门禁**——所有在用 JSON 过大小写检查。

规范形: 键 `^0x[0-9a-f]+$`(十六进制字面量形状的键); 值=纯十六进制字面量
字符串(`^0x[0-9a-f]+$` 全串匹配, 非prose嵌入)。
范围: data/annotations/**.json(非 archive) + check 门禁消费的 status 台账。
幂等: 已规范内容零改动(重跑无副作用)。
"""
import glob
import json
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HEX = re.compile(r'^0[xX][0-9a-fA-F]+$')

STATUS_LEDGERS = [
    'bases_adjudications.json', 'bases_snapshot.json',
    'canonical_contract_baseline.json', 'check_baseline_errors.json',
    'dossier_pending.json', 'n12_grandfathered.json',
    'n22_pair_closure.json', 's4_baseline.json',
    'true_vtable_map_20261114.json',
]


def norm_value(s):
    if isinstance(s, str) and HEX.match(s):
        return s.lower()
    return s


def walk(o):
    """递归归一: dict 键(十六进制形状→小写, 保序重建)+纯hex字面量字符串值。"""
    if isinstance(o, dict):
        out = {}
        for k, v in o.items():
            nk = k.lower() if (isinstance(k, str) and HEX.match(k)) else k
            out[nk] = walk(v)
        return out
    if isinstance(o, list):
        return [walk(v) for v in o]
    return norm_value(o)


def main():
    files = [f for f in glob.glob(os.path.join(REPO, 'data', 'annotations', '**', '*.json'),
                                  recursive=True)
             if os.sep + 'archive' + os.sep not in f]
    for name in STATUS_LEDGERS:
        p = os.path.join(REPO, 'data', 'status', name)
        if os.path.exists(p):
            files.append(p)
    total_files, total_changes = 0, 0
    for fp in sorted(files):
        try:
            raw = open(fp, encoding='utf-8').read()
            d = json.loads(raw)
        except Exception as e:
            print('[SKIP-ERR] %s: %s' % (fp, e))
            continue
        nd = walk(d)
        new_text = json.dumps(nd, ensure_ascii=False, indent=1)
        if new_text != raw.strip():
            before = len(HEX.findall(raw))
            json.dump(nd, open(fp, 'w', encoding='utf-8'),
                      ensure_ascii=False, indent=1)
            total_files += 1
            total_changes += before
            print('[NORM] %s' % os.path.relpath(fp, REPO))
    print('归一 %d 文件(十六进制字面量位点约 %d)' % (total_files, total_changes))


if __name__ == '__main__':
    main()
