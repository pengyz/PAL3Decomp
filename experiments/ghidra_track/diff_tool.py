"""双轨差分器（spec M1 判据件）：A 轨（Hex-Rays/codegen）与 B 轨（Ghidra/丑C）编译错误
三桶差分 + 逐条溯源。用法:
  python3 diff_tool.py <a_errors.txt> <b_errors.txt> <out.json> --slice <name>
输出 schema:
  {schema_version: 1, slice, generated_at,
   buckets: {A_only: [item], B_only: [item], intersection: [item]},
   item = {error_key, side, text, source_unit, trace: [归因链], class}}
A/B errors.txt 格式: 每行 "unit.cpp: error: TEXT"（gcc/MSVC 通用形，TEXT 归一化为 error_key）"""
import json, re, sys, datetime

def parse(path):
    out = {}
    for ln in open(path, encoding='utf-8', errors='replace'):
        m = re.match(r'^([^:]+):\s*(?:error\s*:\s*)?(.*)$', ln.strip())
        if not m:
            continue
        unit, text = m.group(1), m.group(2)
        key = re.sub(r'\b0x[0-9a-fA-F]+\b', '0xADDR', text)
        key = re.sub(r'\b\d+\b', 'N', key)
        key = re.sub(r'\s+', ' ', key).strip()
        out.setdefault(key, {'error_key': key, 'text': text[:200], 'source_unit': unit, 'count': 0})['count'] += 1
    return out

def main():
    a_path, b_path, out_path = sys.argv[1], sys.argv[2], sys.argv[3]
    sl = sys.argv[sys.argv.index('--slice') + 1] if '--slice' in sys.argv else 'unknown'
    A, B = parse(a_path), parse(b_path)
    ka, kb = set(A), set(B)
    def items(keys, side, src):
        r = []
        for k in sorted(keys):
            it = dict(src[k])
            it['side'] = side
            it['class'] = None       # 归因留待逐条裁定（不准确=不判定）
            it['trace'] = []
            r.append(it)
        return r
    doc = {'schema_version': 1, 'slice': sl,
           'generated_at': datetime.datetime.now().isoformat(timespec='seconds'),
           'buckets': {
               'A_only': items(ka - kb, 'A', A),          # 仅 A 有=Hex-Rays 约束候选（spec M1 归因对象）
               'B_only': items(kb - ka, 'B', B),          # 仅 B 有=验证轨伪影/转换层桶
               'intersection': items(ka & kb, 'AB', A)}}  # 交集=两侧共有=注解/共性问题
    json.dump(doc, open(out_path, 'w'), indent=1, ensure_ascii=False)
    print('diff: A_only=%d B_only=%d intersection=%d -> %s' % (
        len(doc['buckets']['A_only']), len(doc['buckets']['B_only']),
        len(doc['buckets']['intersection']), out_path))

if __name__ == '__main__':
    main()
