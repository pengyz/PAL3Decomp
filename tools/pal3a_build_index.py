#!/usr/bin/env python3
import argparse
import json
from pathlib import Path


def normalize_address(value):
    text = str(value).strip()
    if text.lower().startswith('0x'):
        text = text[2:]
    return f"0x{int(text, 16):08X}"


def build_index(payload):
    return {
        'image_base': normalize_address(payload['image_base']),
        'functions': {
            normalize_address(item['address']): {
                'name': item['name'],
                'source_file': item.get('source_file', ''),
                'return_type': item.get('return_type', ''),
                'parameters': item.get('parameters', []),
                'status': 'indexed',
            }
            for item in payload.get('functions', [])
        },
        'globals': {
            normalize_address(item['address']): {
                'name': item['name'],
                'datatype': item.get('datatype', ''),
            }
            for item in payload.get('globals', [])
        },
        'types': {
            item['name']: {
                'kind': item.get('kind', ''),
                'size': item.get('size', 0),
            }
            for item in payload.get('types', [])
        },
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', required=True)
    parser.add_argument('--output', required=True)
    args = parser.parse_args()

    payload = json.loads(Path(args.input).read_text(encoding='utf-8'))
    output = build_index(payload)
    out_path = Path(args.output)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(json.dumps(output, indent=2, ensure_ascii=False), encoding='utf-8')


if __name__ == '__main__':
    main()
