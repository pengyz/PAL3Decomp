#!/usr/bin/env python3
"""tools/thunk_scan.py — 跳板形态自动识别（research_thunk_mechanism §4.2 落地件 #7）。

字节签名 → 族标签（判据=分类学表 T1–T12 + 第 9 形，2026-10-31 勘误后 9 形齐）：
  FF 25 [IAT 0x56Axxx]        import_thunk                (T1/T2 链接器导入跳板)
  FF 25 [PSGP 0x6090A8-2F4]   psgp_dispatch               (T3 B 形 PSGP 分发)
  6A 01 E8.. FF 25 [PSGP]     psgp_lazy_init              (T3 A/C 形惰性初始化桩)
  B9 imm32 E9 rel32           singleton_thunk              (T5 单例/静态对象 this 装载)
  B9 imm32 FF 25 [IAT]        static_obj_ctor_thunk_to_import (第 9 形，12 件已入册)
  83 E9 imm8 E9 rel32         this_adjustor                (T6 多继承 this 调整)
  E8 rel32 E9 rel32           static_init_glue             (T8 10B 静态初始化胶水)
  E9 rel32                    tail_alias                   (T7 5B 直跳别名/ILT)
  其余                        real_body                    (真身——非跳板)

用法:
  python tools/thunk_scan.py --skip-unknown-libname [-o out.json]
  python tools/thunk_scan.py --addr 0x00401BC0 [--addr ...]
  python tools/thunk_scan.py --all-skip [-o out.json]

输出=纯计量 census（JSON）：每条 {addr, name, skip_reason, family, head_hex, ...}。
「不准确=不判定」：head_hex 随条目落盘，字节形证据可按地址复验。
"""
import argparse
import json
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
EXE = PROJECT_ROOT / 'original' / 'PAL3.exe'
SKIP_PATH = PROJECT_ROOT / 'data' / 'annotations' / 'skip_functions.json'

IAT_LO, IAT_HI = 0x0056A000, 0x00580000     # .rdata IAT 槽区（R2a-2 段界实测）
PSGP_LO, PSGP_HI = 0x006090A8, 0x006092F4   # PSGP 分发表 73 槽（review_dx 数字审计）


# ── 纯函数区（R15 单测点）─────────────────────────────────────────
def _u32(b, off):
    return struct.unpack_from('<I', b, off)[0]


def _s32(b, off):
    return struct.unpack_from('<i', b, off)[0]


def classify_shape(head, va=None):
    """head（>=16B 起始字节）→ 族标签。va 供 rel32 目标回算（可选）。

    判据按「前缀最小充分形」逐级短路；每级只看族签名所需字节。
    """
    if not head or len(head) < 1:
        return 'unknown'
    b = head
    # FF 25 imm32 —— 导入跳板(T1/T2) / PSGP 分发(T3 B 形)
    if len(b) >= 6 and b[0] == 0xFF and b[1] == 0x25:
        tgt = _u32(b, 2)
        if IAT_LO <= tgt < IAT_HI:
            return 'import_thunk'
        if PSGP_LO <= tgt <= PSGP_HI:
            return 'psgp_dispatch'
        return 'jmp_indirect_other'
    # 6A 01 E8 rel32 FF 25 …（A 形）/ 55 8B EC 6A 01 E8 rel32 5D FF 25 …（C 形）
    if len(b) >= 13 and b[0] == 0x6A and b[1] == 0x01 and b[2] == 0xE8 and b[7] == 0xFF and b[8] == 0x25:
        return 'psgp_lazy_init'
    if (len(b) >= 17 and b[0] == 0x55 and b[1] == 0x8B and b[2] == 0xEC
            and b[3] == 0x6A and b[4] == 0x01 and b[5] == 0xE8 and b[10] == 0x5D
            and b[11] == 0xFF and b[12] == 0x25):
        return 'psgp_lazy_init'
    # B9 imm32 … —— 单例跳板(T5: E9) / 第 9 形(FF 25 [IAT])
    if len(b) >= 5 and b[0] == 0xB9:
        if len(b) >= 11 and b[5] == 0xFF and b[6] == 0x25:
            tgt = _u32(b, 7)
            return 'static_obj_ctor_thunk_to_import' if IAT_LO <= tgt < IAT_HI else 'jmp_indirect_other'
        if b[5] == 0xE9:
            return 'singleton_thunk'
        return 'mov_ecx_imm_other'
    # 83 E9 imm8 E9 rel32 —— this-adjustor(T6)
    if len(b) >= 8 and b[0] == 0x83 and b[1] == 0xE9 and b[3] == 0xE9:
        return 'this_adjustor'
    # E8 rel32 E9 rel32 —— 10B 胶水(T8)
    if len(b) >= 10 and b[0] == 0xE8 and b[5] == 0xE9:
        return 'static_init_glue'
    # E9 rel32 —— 5B 直跳别名(T7)
    if b[0] == 0xE9:
        return 'tail_alias'
    return 'real_body'


FAMILY_NOTE = {
    'import_thunk': 'T1/T2 链接器导入跳板（(c) 链接期再生）',
    'psgp_dispatch': 'T3 B 形 PSGP 分发跳板',
    'psgp_lazy_init': 'T3 A/C 形 PSGP 惰性初始化桩',
    'singleton_thunk': 'T5 单例/静态对象 this 装载跳板',
    'static_obj_ctor_thunk_to_import': '第 9 形 静态对象 ctor/dtor 导入跳板',
    'this_adjustor': 'T6 多继承 this-adjustor',
    'static_init_glue': 'T8 10B 静态初始化胶水',
    'tail_alias': 'T7 5B 直跳别名（ILT/COMDAT/tail-jmp）',
    'real_body': '真身（非跳板）',
    'jmp_indirect_other': '间接跳（目标非 IAT/PSGP，待人工）',
    'mov_ecx_imm_other': 'mov ecx,imm 形变体（待人工）',
    'unknown': '空输入',
}


# ── PE 读数（只读）────────────────────────────────────────────────
class Exe:
    def __init__(self, path):
        self.data = path.read_bytes()
        pe = struct.unpack_from('<I', self.data, 0x3C)[0]
        nsec = struct.unpack_from('<H', self.data, pe + 6)[0]
        optsz = struct.unpack_from('<H', self.data, pe + 20)[0]
        self.image_base = struct.unpack_from('<I', self.data, pe + 24 + 28)[0]
        self.secs = []
        for i in range(nsec):
            off = pe + 24 + optsz + i * 40
            vsz, va, rsz, ptr = struct.unpack_from('<IIII', self.data, off + 8)
            self.secs.append((va, vsz, ptr, rsz))

    def va2off(self, v):
        rva = v - self.image_base
        for va, vsz, ptr, rsz in self.secs:
            if va <= rva < va + max(vsz, rsz):
                return ptr + (rva - va)
        return None

    def head(self, va, n=16):
        off = self.va2off(va)
        return self.data[off:off + n] if off is not None else b''


def scan(entries, exe):
    rows = []
    for addr, name, skip_reason in entries:
        va = int(addr, 16)
        h = exe.head(va)
        rows.append({
            'addr': '0x%08X' % va,
            'name': name,
            'skip_reason': skip_reason,
            'family': classify_shape(h, va),
            'head_hex': h[:11].hex(),
        })
    return rows


def main():
    ap = argparse.ArgumentParser(description='跳板形态自动识别（字节形 census）')
    ap.add_argument('--skip-unknown-libname', action='store_true',
                    help='扫描 skip_functions 的 unknown_libname_* 族')
    ap.add_argument('--all-skip', action='store_true', help='扫描 skip_functions 全量')
    ap.add_argument('--addr', action='append', default=[], help='指定地址（可重复）')
    ap.add_argument('-o', '--out', help='输出 JSON 路径（默认 stdout 摘要）')
    args = ap.parse_args()

    skip = json.loads(SKIP_PATH.read_text(encoding='utf-8'))
    entries = []
    if args.skip_unknown_libname:
        entries += [(a, e.get('name') or '', e.get('reason') or '')
                    for a, e in skip.items()
                    if (e.get('name') or '').startswith('unknown_libname_')]
    if args.all_skip:
        entries += [(a, e.get('name') or '', e.get('reason') or '')
                    for a, e in skip.items()
                    if not (e.get('name') or '').startswith('unknown_libname_')]
    for a in args.addr:
        e = skip.get('0x%08X' % int(a, 16), {})
        entries.append(('0x%08X' % int(a, 16), e.get('name') or '', e.get('reason') or ''))
    if not entries:
        ap.error('需要 --skip-unknown-libname / --all-skip / --addr')

    exe = Exe(EXE)
    rows = scan(entries, exe)
    rows.sort(key=lambda r: int(r['addr'], 16))

    dist = {}
    for r in rows:
        dist[r['family']] = dist.get(r['family'], 0) + 1
    out = {'_tool': 'tools/thunk_scan.py', '_criteria': 'T1-T12 + form9 byte-shape',
           'count': len(rows), 'family_dist': dist, 'rows': rows}
    if args.out:
        Path(args.out).write_text(json.dumps(out, ensure_ascii=False, indent=2) + '\n',
                                  encoding='utf-8')
        print('wrote %s (%d rows)' % (args.out, len(rows)))
    for k, v in sorted(dist.items(), key=lambda kv: -kv[1]):
        print('%-36s %4d  %s' % (k, v, FAMILY_NOTE.get(k, '')))
    print('total %d' % len(rows))


if __name__ == '__main__':
    main()
