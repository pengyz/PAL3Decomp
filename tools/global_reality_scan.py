"""全局变量实况分类扫描（用户质疑驱动：2K+ 全局不合软件工程常识）。
判据复用 W1 体系：串指纹 / A 级锚对象区间包含 / static 块 / 访问形态 / 命名形态。
只读探针：python tools/global_reality_scan.py [--report data/status/global_reality_report.json]
"""
import argparse
import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN = os.path.join(ROOT, 'data', 'annotations', 'globals.json')
IDA = os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json')


def load_globals():
    """全集 = globals.json 注解 ∪ ida_structs._globals ∪ 生成头引用（三源并集）。"""
    out = {}
    g = json.load(open(ANN, encoding='utf-8'))
    items = g.get('globals') or g
    for k, v in items.items():
        try:
            va = int(str(k), 16)
        except Exception:
            continue
        out[va] = {'name': v.get('name'), 'type': v.get('type'),
                   'source': v.get('source', ''), 'src': 'annotation'}
    ida = json.load(open(IDA, encoding='utf-8'))
    for k, v in (ida.get('_globals') or {}).items():
        try:
            va = int(str(k), 16)
        except Exception:
            continue
        if va not in out:
            out[va] = {'name': v.get('name'), 'type': v.get('type'),
                       'source': '', 'src': 'ida'}
    return out


def build_fulltext_xref():
    """C3（75e5af3b）：全 .text 线性反汇编 xref（语料 build_xref_index 仅覆盖 83%——
    408 条全局有语料外隐藏引用 1326 站点；IAT 的 call [abs] 被判 other 等盲区一并覆盖）。"""
    import capstone
    from capstone import x86 as cs_x86
    from tools.type_evidence import exe_text_image
    data, va2off, sections = exe_text_image()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    md.skipdata = True        # .text 内数据岛（跳转表/对齐填充）——跳过续走而非停机
    xref = collections.defaultdict(list)
    text = None
    for s in sections:                       # sections 元组形：(name, va, size, ...)
        if isinstance(s, dict):
            if s.get('name') == '.text':
                text = {'va': s['va'], 'size': s['size']}
                break
        elif len(s) >= 3 and s[0] == '.text':
            text = {'va': s[1], 'size': s[2]}
            break
    if not text:
        return xref
    base, size = text['va'], text['size']
    off = va2off(base)
    for ins in md.disasm(data[off:off + size], base):
        mn = ins.mnemonic
        if mn == '.byte' or ins.id == 0:
            continue                        # skipdata 伪指令（数据岛）无 operands
        for op in ins.operands:
            if op.type == 2:      # IMM：call/jmp abs（IAT/跳转）+ push/mov 物化（W1 形态语义）
                tgt = op.imm & 0xFFFFFFFF
                if mn in ('call', 'jmp'):
                    xref[tgt].append((ins.address, mn, 'call_abs'))
                elif mn == 'push':
                    xref[tgt].append((ins.address, mn, 'push_arg'))
                elif mn == 'mov':
                    xref[tgt].append((ins.address, mn, 'addr'))
            elif op.type == 3 and op.mem.base == 0 and op.mem.index == 0:
                tgt = op.mem.disp & 0xFFFFFFFF
                if mn.startswith('f'):
                    shape = 'fpu'
                elif mn in ('cmp', 'test'):
                    shape = 'cmp'
                elif mn == 'lea':
                    shape = 'lea'
                elif mn.startswith('mov'):
                    shape = 'mov_store' if ins.operands[0] is op else 'mov_load'
                else:
                    shape = 'other'
                xref[tgt].append((ins.address, mn, shape))
            elif op.type == 3 and op.mem.disp:
                pass  # 基址/索引形不涉绝对地址
    return xref


def _is_mem_write(insn_va, mnem, shape):
    """C4（75e5af3b）：写点语义修正——addr=地址物化**不算写**（W1 模块明文）；
    fpu 按助记符分读写（fst/fist=写、fld=读、fadd 等 mem 形=RMW 写）；
    RMW（inc/dec/add/sub/and/or/xor/xchg 对 mem）计写。"""
    if shape in ('mov_store', 'mov_imm'):
        return True
    if shape == 'addr' or shape == 'push_arg' or shape == 'cmp' or shape == 'lea':
        return False
    m = mnem
    if m.startswith(('fst', 'fist')):
        return True
    if m in ('fld', 'fild'):
        return False
    if m.startswith(('fadd', 'fsub', 'fmul', 'fdiv', 'fcom', 'fxch')):
        return True                     # mem 形 RMW（保守计写）
    if m in ('inc', 'dec', 'neg', 'not', 'add', 'sub', 'and', 'or', 'xor',
             'xchg', 'setcc') or m.startswith('set'):
        return True
    return False


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument('--report', default=os.path.join('data', 'status', 'global_reality_report.json'))
    args = ap.parse_args(argv)
    from tools.type_evidence import exe_text_image
    from tools.member_existence_gate import build_static_blocks, string_fingerprint
    data, va2off, sections = exe_text_image()
    xref = build_fulltext_xref()          # C3：全 .text 线性超集（语料索引仅 83%）
    sblocks, swrites = build_static_blocks()
    glb = load_globals()
    print('全局全集（注解∪ida∪生成）: %d' % len(glb))

    # A 级锚对象 span（ctor+dtor thunk 对 + atexit 注册——W1 同法；75e5af3b C1：严格内部）
    from tools.member_existence_gate import build_ctor_anchors
    ctor = build_ctor_anchors()
    anchored_spans = [(b, b + 8, 'ctor-anchor@0x%X' % b) for b in sorted(ctor)]
    # 实证对象 span（台账裁定，A 级）：
    PROVEN = [(0xC043A0, 0xC05F20, 'g_RoleSlotBuf(1408x5 序列化闭合)'),
              (0xC10968, 0xC111E8, 'g_palScript(2176=PalScript.binary_size)'),
              (0xC11758, 0xC11B54, 'UIManager(0x95C ctor 槽循环)'),
              (0xC05F30, 0xC05F60, 'unk_C05F30 邻接区')]
    anchored_spans.extend(PROVEN)

    rows = []
    cat = collections.Counter()
    for va, info in sorted(glb.items()):
        nm = info.get('name') or ''
        off = va2off(va)
        # ① 串指纹（exe 字节——注意 string_fingerprint(buf, min_run) 取**字节切片**）
        is_str = False
        if off is not None and off + 8 < len(data):
            try:
                is_str = bool(string_fingerprint(data[off:off + 128]))
            except Exception:
                is_str = False
        # ② 锚对象区间包含——**严格内部**（va==base 是对象本体=真全局对象，不是"内部"！
        # 2026-09-28 G6 备料实证：<= 会把 g_PAL3/g_palScript/g_UIManager 等本体误判内部⇒误删）
        in_obj = None
        is_anchor_self = False
        for lo, hi, tag in anchored_spans:
            if va == lo:
                is_anchor_self = True
                in_obj = tag
                break
            if lo < va < hi:
                in_obj = tag
                break
        # ③ static 块
        in_static = any(lo <= va < hi for lo, hi in sblocks)
        # ④ 访问形态（W1 xref：站点形状）
        sites = xref.get(va, [])
        shapes = collections.Counter(s for _, _, s in sites)
        data_access = sum(n for s, n in shapes.items()
                          if s in ('mov_load', 'mov_store', 'mov_imm', 'fpu', 'cmp'))
        push_only = shapes.get('push_arg', 0) > 0 and data_access == 0
        # C4（75e5af3b）：写点语义修正——逐条按助记符判（addr 不算写/fpu 读写分/RMW 计写）
        has_write = any(_is_mem_write(ip, mn, sh) for ip, mn, sh in sites)
        # C4 附（75e5af3b）：串指纹从严——文本型名字或类型 + NUL 收尾 run + 引用仅指针实参
        is_str_strict = is_str and (
            bool(re.match(r'^a[A-Z]', nm)) or 'char' in str(info.get('type') or '')
        ) and (not sites or all(sh in ('push_arg', 'addr') for _, _, sh in sites))
        # ⑤ 命名形态
        name_form = ('g_*' if nm.startswith('g_') else
                     'a*串名' if re.match(r'^a[A-Z]', nm) else
                     'auto:' + nm.split('_')[0] if '_' in nm else 'other')
        # ⑥ 可变性（用户判据：游戏变量=可变状态；只读指针表/常量表不算）
        # [T77/F3] 死代码删除：原 L184-185 二次 has_write 赋值（addr/fpu 全计写、
        # 引用不存在的 mov_imm）覆盖 C4 逐条精判——影子树定量（bfd87ca0）：删后
        # 2720 条中 247 条改类、20 条假「真·可变全局」消除（g_pszSceneSlot1/2 等
        # 实为只读）。保留 C4 版（L174 _is_mem_write 逐条判）✓ 唯一权威。
        # 分类（负证优先——W1 结构性负证序；75e5af3b C4 严判据 + IAT 类目）
        if is_str_strict:
            c = '串字面（伪全局）'
        elif is_anchor_self:
            c = '锚对象本体（真全局对象）'
        elif in_obj:
            c = '对象内部（非独立）'
        elif in_static:
            c = '函数内 static'
        elif shapes.get('call_abs', 0) and not has_write:
            c = '导入表槽（IAT/call[abs]）'          # 75e5af3b 发现②：IAT 此前散落
        elif data_access == 0 and not sites:
            c = '零引用（未证实）'
        elif not has_write and nm.startswith('off_'):
            c = '只读指针表（vtable/跳转/导入槽）'
        elif not has_write:
            c = '只读数据（常量表/初值）'
        elif push_only and not data_access:
            c = '仅作指针实参（数据/表候选）'
        elif data_access > 0:
            c = '真·可变全局（游戏状态）'
        else:
            c = '待证'
        cat[c] += 1
        rows.append({'va': '0x%08X' % va, 'name': nm, 'type': info.get('type'),
                     'cls': c, 'name_form': name_form, 'sites': len(sites),
                     'data_access': data_access, 'str': is_str,
                     'in_obj': in_obj, 'in_static': in_static, 'src': info.get('src')})
    print('\n=== 全局实况分类 ===')
    for k, v in cat.most_common():
        print('  %-22s %d' % (k, v))
    # 交叉：真·可变全局 × 命名形态
    print('\n=== 真·可变全局（游戏状态）的命名构成 ===')
    nm2 = collections.Counter(r['name_form'] for r in rows if r['cls'].startswith('真·可变'))
    for k, v in nm2.most_common():
        print('  %-16s %d' % (k, v))
    out = args.report if os.path.isabs(args.report) else os.path.join(ROOT, args.report)
    json.dump({'_meta': {'probe': 'tools/global_reality_scan.py',
                         'total': len(glb), 'classes': dict(cat)},
               'rows': rows}, open(out, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('\n报告 -> %s' % out)
    # 派生类别图（ida-only 合成条目的类别源——发射分区回退查；status=派生件区）
    MAP = {'串字面（伪全局）': 'string_literal', '只读数据（常量表/初值）': 'const_data',
           '只读指针表（vtable/跳转/导入槽）': 'ptr_table', '真·可变全局（游戏状态）': 'game_state',
           '零引用（未证实）': 'unreferenced', '锚对象本体（真全局对象）': 'anchor_object',
           '对象内部（非独立）': 'object_interior', '函数内 static': 'function_static',
           '待证': 'pending', '仅作指针实参（数据/表候选）': 'pending'}
    cmap = {r['va']: MAP.get(r['cls'], 'pending') for r in rows}
    cout = os.path.join(ROOT, 'data', 'status', 'global_categories.json')
    json.dump(cmap, open(cout, 'w', encoding='utf-8'), ensure_ascii=False, indent=0)
    print('类别图 -> %s（%d 条）' % (cout, len(cmap)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
