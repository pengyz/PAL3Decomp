#!/usr/bin/env python3
import argparse
import json
from pathlib import Path


def score_function(meta):
    source_file = meta.get('source_file', '').lower()
    name = meta.get('name', '').lower()
    score = 0
    if 'script' in source_file or 'sce' in source_file:
        score += 10
    if name.startswith('sce_') or name.startswith('script'):
        score += 10
    return score


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--index', required=True)
    parser.add_argument('--output', required=True)
    parser.add_argument('--limit', type=int, default=12)
    args = parser.parse_args()

    index = json.loads(Path(args.index).read_text(encoding='utf-8'))
    ranked = sorted(index['functions'].items(), key=lambda item: score_function(item[1]), reverse=True)
    payload = {
        'anchors': [
            {'address': address, 'name': meta['name'], 'source_file': meta.get('source_file', '')}
            for address, meta in ranked[:args.limit]
            if score_function(meta) > 0
        ]
    }
    Path(args.output).write_text(json.dumps(payload, indent=2, ensure_ascii=False), encoding='utf-8')


if __name__ == '__main__':
    main()
