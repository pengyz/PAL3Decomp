#!/usr/bin/env python3
"""[O3 数据层身份清单 2026-11-22] function_identity.json 生成器（单一真值源）。

架构定谳（对抗复核+架构审计双报告 2026-11-22，用户裁决路线）：
  ??_G/??1 等编译器特形符号的 match 配对，其地址绑定不应寄生在语料名快照
  （每 loop 重导出、名形漂移——18 个 L1 载体断裂实证），应由**数据层身份清单**
  定谳、match 消费层机械 join（O3 真值表 + O5 结构解码，互为表里）。
  本模块 = 清单的**单一构建源**：export_full（IDA 内，权威 size）与 CLI 自举
  （语料 size 兜底）都只调 build_identity()——无副本。

清单条目（覆盖全部注解 methods 地址，**含被抑制者**——抑制可挡语料正文，
不可挡身份数据）：
  {"va", "size", "ann_class", "ann_kind"(ctor|complete_dtor|deleting_dtor|method),
   "mangled"(list, deleting_dtor 形固定 ??_GCls@@UAEPAXI@Z), "virtual",
   "slot_verified", "owners", "data_suspect"}

用法:
  python3 pipeline/ida/function_identity.py            # CLI 自举(无 IDA)
  # export_full 内: from function_identity import build_identity; 同参注入
"""
import glob
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
STRUCTS_DIR = os.path.join(REPO, 'data', 'annotations', 'structs')
CORPUS_DIR = os.path.join(REPO, 'asm', 'pal3', 'decomp')
OUT_PATH = os.path.join(REPO, 'asm', 'pal3', 'function_identity.json')

_DTOR_FIXED_MANGLE = '??_G%s@@UAEPAXI@Z'


def _cls_chain(name):
    return '@'.join(reversed(name.split('::')))


def build_identity(structs_dir=STRUCTS_DIR, size_fn=None, mangler=None):
    """纯构建核心。size_fn(va:int)->int|None 注入（IDA=get_func().size()；
    CLI=语料 size_bytes 兜底）；mangler 注入 vc6_mangler（缺省延迟 import）。

    返回 (rows list, suspects list)。行按 va 升序。
    """
    if mangler is None:
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        import vc6_mangler as mangler
    # ① 全量注解 methods 扫描（含 rejected 过滤——与 export pre-pass 同守卫）
    claims = {}      # int va -> list of (cls, entry)
    vtables_slots = set()   # int va — 任意表槽（virtuality 裁决源）
    for sf in sorted(glob.glob(os.path.join(structs_dir, '*.json'))):
        try:
            sd = json.load(open(sf, encoding='utf-8'))
        except Exception:
            continue
        cls = sd.get('name') or os.path.basename(sf)[:-5]
        for vt in sd.get('vtables') or []:
            for slot in vt.get('slots') or []:
                sa = slot.get('addr')
                if sa:
                    try:
                        vtables_slots.add(int(sa, 16))
                    except (ValueError, TypeError):
                        pass
        for addr, info in (sd.get('methods') or {}).items():
            if not isinstance(info, dict):
                continue
            if info.get('adjudication') == 'rejected':
                continue   # [2026-11-03 复核安全前置] rejected 禁消费
            try:
                va = int(addr, 16)
            except (ValueError, TypeError):
                continue
            claims.setdefault(va, []).append((cls, info))
    # ② 行构建（owner 加权：owner==自身类者优先为主属主——与 export pre-pass 同律）
    rows, suspects = [], []
    for va in sorted(claims):
        entries = claims[va]
        owner_entries = [e for e in entries if e[1].get('owner') == e[0]]
        primary_cls, primary_info = (owner_entries or entries)[0]
        owners = sorted({c for c, _ in entries})
        flags = primary_info.get('flags') or []
        nm = str(primary_info.get('name') or '')
        suspect = ''
        # kind 判定（外类方法守卫——UIRoleDialog 内 ~UIWnd@0x4bef50 先例：
        # dtor 身份须 name=='~'+本类名，否则降级 method + 数据疑点）
        if 'dtor' in flags or nm.startswith('~'):
            if nm.lstrip('~') == primary_cls:
                kind = 'deleting_dtor' if 'deleting' in flags else 'complete_dtor'
            else:
                kind = 'method'
                suspect = ('dtor 形名 %s ≠ 本类 %s——外类条目不赋 dtor 身份'
                           % (nm, primary_cls))
        elif nm == primary_cls or 'ctor' in flags:
            kind = 'ctor'
        else:
            kind = 'method'
        row = {
            'va': '0x%08x' % va,
            'size': (size_fn(va) if size_fn else None),
            'ann_class': primary_cls,
            'ann_kind': kind,
            'flags': flags,
            'owners': owners,
            'slot_verified': va in vtables_slots,
            'data_suspect': suspect,
        }
        # deleting_dtor 固定形 mangle（obj 15/15 实证 UAEPAXI@Z；N18 已建成通道）
        if kind == 'deleting_dtor':
            row['mangled'] = [_DTOR_FIXED_MANGLE % _cls_chain(primary_cls)]
            if not row['slot_verified']:
                suspects.append({
                    'va': row['va'], 'class': primary_cls,
                    'note': 'flags deleting 但地址不在任何注解表槽——virtuality 无写表证据'
                            '（slot5 闭环战役欠账），键照发、字节比对裁决'})
        elif kind == 'complete_dtor':
            row['mangled'] = ['??1%s@@QAE@XZ' % _cls_chain(primary_cls),
                              '??1%s@@UAE@XZ' % _cls_chain(primary_cls)]
        rows.append(row)
    return rows, suspects


def load_corpus_sizes(corpus_dir=CORPUS_DIR):
    """CLI 自举的 size 兜底：语料 size_bytes（抑制地址无语料条目 → None）。"""
    sizes = {}
    for f in glob.glob(os.path.join(corpus_dir, '*.json')):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        try:
            va = int(d.get('address'), 16)
            sz = d.get('size_bytes')
            if sz:
                sizes[va] = int(sz)
        except (ValueError, TypeError):
            continue
    return sizes


def write_manifest(path, rows, suspects, size_source='corpus'):
    """统一信封写入（审计 C2 2026-11-22：export_full 与 CLI 双写点收敛——
    信封字段单源，防 _doc/_law 漂移）。"""
    kinds = {}
    for r in rows:
        kinds[r['ann_kind']] = kinds.get(r['ann_kind'], 0) + 1
    out = {
        '_doc': ('function_identity (O3 数据层身份清单)——?? 特形符号配对真值表；'
                 'export_full 每轮以 IDA size 权威重生成'
                 + ('' if size_source == 'ida' else '；本文件为 CLI 自举产物(语料 size 兜底)')),
        '_law': ('决策在数据层, match 只机械 join (O5 结构解码); 语料名=显示名非证据'
                 '(pipeline-data-flow-law); owners 多属主=ICF 共享(对齐 R6 多址聚合)'),
        'size_source': size_source,
        'count': len(rows),
        'rows': rows,
        'suspects': suspects,
    }
    with open(path, 'w', encoding='utf-8') as f:
        json.dump(out, f, ensure_ascii=False, indent=1)
    return kinds


def main():
    sizes = load_corpus_sizes()
    rows, suspects = build_identity(size_fn=lambda va: sizes.get(va))
    kinds = write_manifest(OUT_PATH, rows, suspects, size_source='corpus')
    print('[function_identity] %d 行 → %s' % (len(rows), OUT_PATH))
    print('  kinds:', kinds, '| suspects:', len(suspects))


if __name__ == '__main__':
    main()
