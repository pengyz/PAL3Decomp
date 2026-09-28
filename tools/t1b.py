"""T1b：this-relative disp32 census（type_evidence v3 的双信号合并核心）。

设计=复核 1239c52d【有条件通过】硬化版（data/status/_b_type_evidence_v3_design.md §2）：
- **播种门**：仅 signature 含 __thiscall 的方法播种 ECX=this+0（static/非 thiscall 不播种——
  459 方法 17 个非 thiscall，naive 播种 17 污染站点实证）；
- **写失效**：capstone `regs_access()` 的 writes（**含隐式写**——mul/cdq/pop/setcc 族全覆盖）
  + 寄存器别名归一（AL/AX/EAX 同族，部分写即整族失效）；
- call 后 EAX/ECX/EDX 失效；`mov dst,src`/`lea dst,[src+N]` 复制传播/派生指针（this+X 归并）；
- **载体收形**：仅 op.mem.index==0；**负 disp 一律不入**（MI adjustor 防线）；
  binary_size 只作提示（PAL3 91024→4936 实证 18 倍虚高）。

用法（只读）：python tools/t1b.py [--class Cls] [--report data/status/t1b_report.json]
测试：python tools/test_t1b.py
"""
import argparse
import collections
import hashlib
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN_STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')

_ALIAS = {
    'al': 'eax', 'ah': 'eax', 'ax': 'eax', 'eax': 'eax',
    'bl': 'ebx', 'bh': 'ebx', 'bx': 'ebx', 'ebx': 'ebx',
    'cl': 'ecx', 'ch': 'ecx', 'cx': 'ecx', 'ecx': 'ecx',
    'dl': 'edx', 'dh': 'edx', 'dx': 'edx', 'edx': 'edx',
    'sil': 'esi', 'si': 'esi', 'esi': 'esi',
    'dil': 'edi', 'di': 'edi', 'edi': 'edi',
    'bpl': 'ebp', 'bp': 'ebp', 'ebp': 'ebp',
}
_CALL_KILL = ('eax', 'ecx', 'edx')


def _norm(reg_name):
    return _ALIAS.get((reg_name or '').lower())


def this_track_step(mapping, ins):
    """单步状态机（纯函数）：mapping={reg: this_offset}。
    返回 (new_mapping, carriers)；carriers=[(offset, mnem, size, shape)]。
    顺序：先按旧映射收载体，后按 regs_access 更新（x86 语义）。"""
    out = dict(mapping)
    carriers = []
    mn = ins.mnemonic
    # 1) 载体：base∈映射 且 index==0 且 disp≥0
    for op in ins.operands:
        if op.type != 3:                        # X86_OP_MEM
            continue
        if op.mem.index:
            continue                            # index 形态排除（57 站点误归属实证）
        base = _norm(ins.reg_name(op.mem.base)) if op.mem.base else None
        if base in out:
            total = out[base] + op.mem.disp
            if total < 0:
                continue                        # 负 disp 拒（R6）
            shape = 'store' if ins.operands and ins.operands[0] is op else 'load'
            carriers.append((total, mn, op.size or 0, shape))
    # 2) 复制传播/派生指针（mov/lea 优先，避免被通用写失效误杀）
    if mn in ('mov', 'lea') and len(ins.operands) >= 2 and ins.operands[0].type == 1:
        dst = _norm(ins.reg_name(ins.operands[0].reg))
        if dst:
            if mn == 'mov' and ins.operands[1].type == 1:
                src = _norm(ins.reg_name(ins.operands[1].reg))
                if src in out:
                    out[dst] = out[src]
                else:
                    out.pop(dst, None)
            elif mn == 'lea' and ins.operands[1].type == 3 and not ins.operands[1].mem.index:
                src = _norm(ins.reg_name(ins.operands[1].mem.base)) if ins.operands[1].mem.base else None
                if src in out and out[src] + ins.operands[1].mem.disp >= 0:
                    out[dst] = out[src] + ins.operands[1].mem.disp
                else:
                    out.pop(dst, None)
            else:
                out.pop(dst, None)
        return out, carriers
    # 3) 通用写失效：regs_access writes（含隐式）+ 别名归一
    try:
        _reads, writes = ins.regs_access()
    except Exception:
        writes = [op.reg for op in ins.operands if op.type == 1 and op == ins.operands[0]]
    if mn == 'call':
        for r in _CALL_KILL:
            out.pop(r, None)
        return out, carriers
    for rid in writes:
        r = _norm(ins.reg_name(rid))
        if r in out:
            out.pop(r, None)
    return out, carriers


def to_refs(offset, hits):
    """T1b hits → type_evidence.Ref 列表（note='this+disp'；kind/sign 走 classify_insn 同源）。
    merge/propose 集成的输入适配层——type_evidence.py 的接线在 695bcbb4 收敛后做。"""
    from tools.type_evidence import Ref, classify_insn
    out = []
    for va, mnem, size, shape in hits:
        kind, sign = classify_insn(mnem, size or 0, False)
        out.append(Ref(offset, va, mnem, 'this+0x%X(%s)' % (offset, shape),
                       size or 0, kind, sign, note='this+disp'))
    return out


def merge_sources(t1_refs, t1b_refs, offset):
    """跨源合并前置（propose v3 §2.3）：宽度集对比 ⇒ cross-source-width 标签。
    返回 (merged_refs, extra_notes)。T1 4B + T1b 1B ⇒ 标签（真多宽度冲突由 propose 复判）。"""
    w1 = {r.op_size for r in t1_refs if getattr(r, 'op_size', 0)}
    w2 = {r.op_size for r in t1b_refs if getattr(r, 'op_size', 0)}
    notes = []
    if w1 and w2 and not (w1 & w2):
        notes.append('cross-source-width: T1%s vs T1b%s（T1b 假阳/方法误归属警报器）'
                     % (sorted(w1), sorted(w2)))
    return list(t1_refs) + list(t1b_refs), notes


def propose_v3(t1_refs, t1b_refs, t2=None):
    """合并分级（设计 §2.3）：同槽 T1+T1b 过现行 propose 规则 + 三处 v3 语义：
    ①cross-source-width 独立标签（T1b 假阳/方法误归属警报器，不与真多宽度冲突混装）；
    ②notes 增 `T1:%d T1b:%d` 溯源（不投票）；③单 float 站点 ⇒ B（现行 propose 已如此，
    契约锁在 test_t1b）；T1 addr + T1b double ⇒ double 提案（emit 禁填分支继承）。
    返回 (proposal, grade, notes)。type_evidence 管线接线待 695bcbb4 收敛后做。"""
    from tools.type_evidence import propose
    merged, xnotes = merge_sources(t1_refs, t1b_refs, 0)
    proposal, grade, notes = propose(merged, t2)
    out_notes = xnotes + ['T1:%d T1b:%d' % (len(t1_refs), len(t1b_refs))] + list(notes)
    return proposal, grade, out_notes


def collect_t1b_for_method(insns, seed_this=True):
    """单方法体 census → (hits, oob)。hits={offset: [(va, mnem, size, shape)]}。"""
    mapping = {'ecx': 0} if seed_this else {}
    hits = collections.defaultdict(list)
    for ins in insns:
        mapping, carriers = this_track_step(mapping, ins)
        for off, mn, size, shape in carriers:
            hits[off].append((ins.address, mn, size, shape))
    return hits, []


def method_seed_map():
    """播种门输入面（P1-e 钉死）：{(cls, addr): seed_this}。
    源=data/annotations/structs/*.json methods 的 signature。
    thiscall 判定=emit_headers 同源规则（:2394）：`__thiscall` 关键字 **或** 参数含 `*this`
    （IDA 有时漏写 __thiscall——RoleSystem 163 方法中大量 signature 无该关键字但首参是 this）。"""
    out = {}
    for f in sorted(os.listdir(ANN_STRUCTS)):
        if not f.endswith('.json'):
            continue
        try:
            d = json.load(open(os.path.join(ANN_STRUCTS, f), encoding='utf-8'))
        except Exception:
            continue
        cls = f[:-5]
        for k, v in (d.get('methods') or {}).items():
            try:
                addr = int(str(k), 16) if str(k).startswith('0x') else int(str(k))
            except Exception:
                continue
            sig = (v or {}).get('signature') or ''
            out[(cls, addr)] = ('__thiscall' in sig) or ('*this' in sig)
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description='T1b this-relative census（v3 核心）')
    ap.add_argument('--class', dest='cls')
    ap.add_argument('--report', default=os.path.join('data', 'status', 't1b_report.json'))
    args = ap.parse_args(argv)
    from tools.type_evidence import exe_text_image, load_func_ranges
    data, va2off, sections = exe_text_image()
    funcs = load_func_ranges()
    seeds = method_seed_map()
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    findex = dict(funcs)
    total_sites = 0
    methods_done = 0
    seeded = 0
    per_cls = collections.Counter()
    for (cls, addr), seed in sorted(seeds.items()):
        if args.cls and cls != args.cls:
            continue
        sz = findex.get(addr)
        if not sz:
            continue
        off = va2off(addr)
        insns = list(md.disasm(data[off:off + sz], addr))
        hits, _ = collect_t1b_for_method(insns, seed_this=seed)
        n = sum(len(v) for v in hits.values())
        total_sites += n
        methods_done += 1
        seeded += 1 if seed else 0
        per_cls[cls] += n
    print('T1b census：%d 方法（播种 %d）/ %d 站点' % (methods_done, seeded, total_sites))
    for c, n in per_cls.most_common(10):
        print('   %-18s %d' % (c, n))
    out = args.report if os.path.isabs(args.report) else os.path.join(ROOT, args.report)
    json.dump({'_meta': {'probe': 'tools/t1b.py',
                         'probe_md5': hashlib.md5(open(__file__, 'rb').read()).hexdigest(),
                         'methods': methods_done, 'seeded': seeded, 'sites': total_sites},
               'per_cls': dict(per_cls)},
              open(out, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('报告 -> %s' % out)
    return 0


if __name__ == '__main__':
    sys.exit(main())
