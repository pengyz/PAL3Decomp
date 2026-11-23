#!/usr/bin/env python3
"""[S5 signature字段退役 2026-11-16 用户裁定"只允许有一个权威源"]
删除 methods[].signature 字符串键——唯一权威源 = sig_model(结构节点)。
前置: apply_annotations 已切 _sig_str_of(sig_model优先渲染); 消费端审计完成(见会话记录)。
幂等: 重跑无变化。"""
import json, glob, sys, os
sys.path.insert(0, os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')))

def main(dry=False):
    n_ent, n_files = 0, 0
    for p in sorted(glob.glob('data/annotations/structs/*.json')):
        d = json.load(open(p, encoding='utf-8'))
        ch = False
        for k, v in (d.get('methods') or {}).items():
            if 'signature' in v:
                if not dry:
                    del v['signature']
                n_ent += 1; ch = True
        if ch and not dry:
            json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
            n_files += 1
    mode = 'DRY' if dry else 'APPLIED'
    print('[%s] signature键删除: %d 条 / %d 文件' % (mode, n_ent, n_files))
    return 0

if __name__ == '__main__':
    sys.exit(main(dry=('--dry' in sys.argv)))
