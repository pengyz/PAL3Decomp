#!/usr/bin/env python3
import argparse
import json
from pathlib import Path

from pal3a_build_index import normalize_address


def build_signature(meta):
    params = ', '.join(meta.get('parameters', [])) or 'void'
    return_type = meta.get('return_type', 'void') or 'void'
    return f"{return_type} {meta['name']}({params})"


def build_body(meta):
    return (
        build_signature(meta)
        + "\n{\n"
        + "    /* UNCERTAIN */\n"
        + ("    return 0;\n" if meta.get('return_type') not in ('void', '', None) else "")
        + "}\n"
    )


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--index', required=True)
    parser.add_argument('--address', required=True)
    parser.add_argument('--output', required=True)
    args = parser.parse_args()

    index = json.loads(Path(args.index).read_text(encoding='utf-8'))
    meta = index['functions'][normalize_address(args.address)]
    out_path = Path(args.output)
    prefix = out_path.read_text(encoding='utf-8') if out_path.exists() else ''
    body = build_body(meta)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    if build_signature(meta) in prefix:
        return
    out_path.write_text(prefix + '\n' + body, encoding='utf-8')


if __name__ == '__main__':
    main()
