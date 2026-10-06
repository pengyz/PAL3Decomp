
#!/usr/bin/env python3
"""把**一批** annotation 修正一次性落到 JSON 上，然后（可选）只跑**一次**完整管线。

# 为什么要有它

完整管线（annotation → apply → export → codegen → probe → match）**成本很高**（IDA 全量重反编译）。
"改一处注解就跑一次"不可持续 ⇒ 修正应**攒成一批**，一次落盘、一次验证。

# 硬约束（来自项目规则与一次被撤销的教训）

1. **每条修正必须有证据**。`evidence` 字段为空 ⇒ **拒绝该条**（不写文件）。
   依据：`CLAUDE.md`「每一处 annotation 修改必须有二进制直接证据」，
   以及 `docs/knowledge/pattern_annotation_batch_rename_no_evidence.md`
   记载的**一次无证据批量改名被整体撤销**。
2. **重归属必须附成员访问证据**（函数内引用的成员在目标类存在、且不在原类存在）。
3. **改名必须同时复核语义**：`new_name` 若仍是"无语义名"（`_sdtor*`/`sub_*`/尾部十六进制等），
   必须给出 `name_evidence`（该名字依据什么：函数做了什么 / 与哪个已知函数同构）；
   给不出 ⇒ 用 `_todo_` 风格的**诚实占位名**，并在 `name_evidence` 里写明"含义未定"。

# 批次文件格式（data/status/annotation_fix_batch.json）

```json
[
  {"kind": "reattribute", "addr": "0x00411CA0",
   "from": "ScriptObj", "to": "PalScript",
   "new_name": "~PalScript",
   "evidence": "引用的成员 m_RoleArray/m_bCreated/... 全部属于 PalScript，且都不在 ScriptObj 里",
   "name_evidence": "成员族与 PalScript 的析构路径一致（释放 m_RoleArray/m_pDialogData）"},
  {"kind": "rename", "class": "CUtil", "addr": "0x005231F0",
   "new_name": "~CUtil", "evidence": "...", "name_evidence": "..."}
]
```

用法：
    python3 tools/apply_annotation_batch.py                 # 只落盘 + 校验（不动 IDB）
    python3 tools/apply_annotation_batch.py --run-pipeline  # 落盘后跑一次完整管线
"""
import argparse
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN = os.path.join(ROOT, 'data', 'annotations', 'structs')
BATCH = os.path.join(ROOT, 'data', 'status', 'annotation_fix_batch.json')

NONSEM = ('_sdtor', '_scalar_dtor', '_vbase_dtor', 'sub_', 'unk_', 'loc_', '_todo', '_stub')


def _norm_off_try(k):
    """offset 键归一（十进制 / 0x… / NNN_N 后缀）。**禁用 int(k,0)** ✗（'50814_0' 会变 508140）。"""
    ks = str(k)
    if ks[:2].lower() == '0x':
        try:
            return int(ks, 16)
        except ValueError:
            return None
    if '_' in ks:
        ks = ks.split('_')[0]
    return int(ks, 10) if ks.isdigit() else None


def _looks_nonsemantic(name):
    import re
    n = str(name or '')
    if n.startswith(NONSEM):
        return True
    return bool(re.search(r'_[0-9a-f]{3,}$', n)) or bool(re.search(r'_[0-9]{3,}$', n))


def load_ann(cls, path=None):
    p = path or os.path.join(ANN, '%s.json' % cls)
    # P0（2026-09-27 复核 5560c6c5）：同文件多条目必须**链式施加** ——
    # 缓冲命中时返回缓冲版（含此前条目的改动），否则第 2 条重读原盘会覆盖第 1 条
    # ⇒ 静默丢改 + exit 0（沙箱 4 形态实证）。B 批天然同文件多条目（25/26 类多候选）。
    if _BUFFER is not None and p in _BUFFER:
        return _BUFFER[p], p
    # newline=''：通用换行会把 CRLF 折叠成 \n ⇒ _detect_style 探不到真实风格（F8 首跑即踩）
    text = open(p, encoding='utf-8', newline='').read()
    _STYLE[p] = _detect_style(text)      # F8：记原风格，落盘按原字节风格回写（diff 可审）
    return json.loads(text), p


def _detect_style(text):
    """(换行符, 尾换行, indent)。仓内现状混杂（实测 CRLF 886/LF 12、indent2 833/indent1 49、
    尾换行 122 有/776 无）⇒ 逐文件保持原样，避免整文件重排版淹没 annotation_diff 门禁。"""
    nl = '\r\n' if '\r\n' in text else '\n'
    trailing = text.endswith('\n')
    m = re.search(r'\n([ \t]+)"', text)
    indent = len(m.group(1)) if m else 2
    return {'nl': nl, 'trailing': trailing, 'indent': indent}


def _render_like(d, p):
    """按 _STYLE 记录的原风格序列化为**文本**（纯函数，不写盘）。"""
    st = _STYLE.get(p) or {'nl': '\r\n', 'trailing': False, 'indent': 2}
    text = json.dumps(d, ensure_ascii=False, indent=st['indent'])
    if st['trailing']:
        text += '\n'
    if st['nl'] != '\n':
        text = text.replace('\n', st['nl'])
    return text


def _dump_like(d, p):
    """按 _STYLE 记录的原风格回写（无记录则仓内多数派：indent=2/CRLF/无尾换行）。
    P2（复核 5560c6c5 Q1b）：临时文件 + os.replace 原子替换，中途被杀不留半写文件。"""
    tmp = p + '.__tmp__'
    with open(tmp, 'w', encoding='utf-8', newline='') as f:
        f.write(_render_like(d, p))
    os.replace(tmp, p)


# type_change 允许的新类型（F3/D4 裁决）：double 布局高危 v1 禁填；指针需数据流证明 v1 不做。
_TYPE_CHANGE_ALLOWED = {'float', 'char', 'unsigned char', 'short', 'unsigned short'}
_TYPE_CHANGE_PLACEHOLDERS = {'int', 'unsigned int', '_DWORD', '__int32', 'unsigned __int32'}


# 2026-09-21：**全局 dry-run 闸** —— 起因：我最初只在新增分支里检查 args.dry_run，
# 而既有的 set_size 分支不知道它 ⇒ 一次 --dry-run 竟然真落了 1453 条 ✗✗（已逐个 git show 回退 ✓）。
# ⇒ 把守卫放到**唯一的落盘出口** save_ann 上，任何分支都无法绕过 ✓。
_DRY_RUN = False
# 2026-09-21（复核 7f6a52cd Q5 / 阶段一 ③b）：**两阶段落盘** —— 原实现循环内逐条 save_ann ✗
# 且 `[拒绝]` 只 continue ✗ ⇒ "1507/1507 通过"**不等于原子** ✗。
# 现改为：**先在内存缓冲**（同一单点 save_ann ✓），末尾若无拒绝才**统一 flush** ✓；
# 任一拒绝 ⇒ **整批不写 + 非零退出** ✓。
_BUFFER = None          # None = 直写（兼容旧行为）；dict = 缓冲模式（path -> data）
_STYLE = {}             # path -> 原文件风格（load_ann 记录，save_ann/flush 回写）——F8


def save_ann(d, p):
    if _DRY_RUN:
        return                      # dry-run：**绝不写盘** ✓（单点守卫，不可绕过 ✓）
    if _BUFFER is not None:
        _BUFFER[p] = d              # 两阶段：先缓冲 ✓（校验通过后才 flush ✓）
        return
    _dump_like(d, p)                # F8：按原风格回写，不整文件重排版


def main():
    _write_rejected = 0
    ap = argparse.ArgumentParser()
    ap.add_argument('--batch', default=BATCH)
    ap.add_argument('--run-pipeline', action='store_true')
    ap.add_argument('--dry-run', action='store_true', help='只计算并打印将做的修改，**不落盘**')
    args = ap.parse_args()

    global _DRY_RUN, _BUFFER      # **B4 修复**：原缺 _BUFFER ⇒ 赋值只建局部名 ⇒ save_ann 读到模块级 None
                                  # ⇒ 逐条直写，"两阶段全或无"是假的 ✗（独立复核 bd0abcc1 反汇编实证：1×STORE_FAST/0×STORE_GLOBAL）

    _DRY_RUN = bool(getattr(args, 'dry_run', False))

    _BUFFER = {} if not _DRY_RUN else None      # 非 dry-run ⇒ 启用两阶段缓冲 ✓（现为真全局 ✓）

    if not os.path.exists(args.batch):
        print('[ERROR] 批次文件不存在: %s' % args.batch)
        return 1
    items = json.load(open(args.batch, encoding='utf-8'))

    ok, rejected = [], []
    for it in items:
        ev = (it.get('evidence') or '').strip()
        nm = it.get('new_name') or it.get('name') or ''   # 缺口2（复核 c34f38aa）：add_member 的 name 同样受硬约束 3
        ne = (it.get('name_evidence') or '').strip()
        kind = it.get('kind')
        if not ev:
            rejected.append((it, '缺少 evidence（硬约束 1）'))
            continue
        if nm and _looks_nonsemantic(nm) and not ne:
            rejected.append((it, '新名仍无语义且缺 name_evidence（硬约束 3）'))
            continue
        if kind == 'reattribute' and not ne:
            rejected.append((it, '重归属缺 name_evidence（硬约束 2/3）'))
            continue
        # 复核 5560c6c5 Q7a/b：rename/reattribute 写盘字段是 new_name —— 缺失会写入期
        # KeyError 崩溃，空串会绕过硬约束 3 落空名 ⇒ 校验与写盘同源（按"将被写的字段"查）。
        if kind in ('rename', 'reattribute') and not (it.get('new_name') or '').strip():
            rejected.append((it, '%s 需要非空 new_name（写盘字段）' % kind))
            continue
        # 2026-09-19 补：reattribute 也必须校验 new_signature（此前只管 add_method/set_signature，
        # 结果 3 条迁移条目带着"__thiscall 但无 ::"的签名落盘，会被发射成 static 自由函数）
        if kind == 'reattribute' and it.get('new_signature'):
            _ns = it['new_signature']
            if '__thiscall' in _ns and '::' not in _ns:
                rejected.append((it, 'reattribute 的 new_signature 是 __thiscall 却缺 "::"（会被发射成 static free function）'))
                continue
        # set_size / skip_method（2026-09-19 新增，供 §49.4 尺寸与 thunk 类修正使用）
        if kind == 'set_size':
            if not it.get('class') or not isinstance(it.get('size'), int) or it['size'] <= 0:
                rejected.append((it, 'set_size 需要 class + 正整数 size'))
                continue
            if not (it.get('evidence') or '').strip():
                rejected.append((it, 'set_size 缺二进制证据'))
                continue
        if kind == 'skip_method':
            if not it.get('class') or not it.get('addr') or not (it.get('reason') or '').strip():
                rejected.append((it, 'skip_method 需要 class + addr + reason'))
                continue
        if kind == 'add_method':
            if not it.get('class') or not it.get('addr') or not it.get('new_name'):
                rejected.append((it, 'add_method 需要 class + addr + new_name'))
                continue
            sig = (it.get('signature') or '').strip()
            if not sig:
                rejected.append((it, 'add_method 需要 signature'))
                continue
            # 与 set_signature 同源护栏：__thiscall 必须带 "::"
            if '__thiscall' in sig and '::' not in sig:
                rejected.append((it, 'add_method 的 __thiscall 签名缺少 "::"（会被发射成 static free function）'))
                continue
        if kind == 'set_signature':
            sig = (it.get('new_signature') or '').strip()
            if not it.get('class') or not it.get('addr') or not sig:
                rejected.append((it, 'set_signature 需要 class + addr + new_signature'))
                continue
            # 与 check_annotations 同源的护栏：__thiscall 必须带 "::"，否则会退化成
            # "free function" 并被发射成 static（2026-09-19 实测：
            #  0x004C5B90 搬类后残留旧签名 ⇒ pal3/src/Effect/CEffectSystem.h:44
            #  出现 `static struct _Texture_uv & SetEffectVisible(_Texture_uv *);`）
            if '__thiscall' in sig and '::' not in sig:
                rejected.append((it, 'set_signature 的 __thiscall 签名缺少 "::"（会被发射成 static free function）'))
                continue
        if kind == 'global_retype':
            # B 批填充重定向（W2 后）：globals.json 条目类型修正。
            # 允许型=type_change 表 + 'int'（un-skip 场景：skip→int 是真实修正，
            # 而 type_change 的 int 排除是"占位起点"语义不适用于此）；指针仍禁（D4 裁决）。
            if not it.get('addr') or it.get('new_type') not in (_TYPE_CHANGE_ALLOWED | {'int'}):
                rejected.append((it, 'global_retype 需要 addr + new_type∈%s'
                                 % sorted(_TYPE_CHANGE_ALLOWED | {'int'})))
                continue
        if kind == 'global_add':
            # W2-④ 独立全局正名（globals.json 注册）。防重：地址已存在 ⇒ 写入期拒。
            if not it.get('addr') or not it.get('name') or not it.get('type'):
                rejected.append((it, 'global_add 需要 addr + name + type'))
                continue
            if not re.fullmatch(r'0[xX][0-9a-fA-F]{5,8}', str(it['addr'])):
                rejected.append((it, 'global_add 的 addr %r 非法（需 0xXXXXXXX）' % it['addr']))
                continue
        if kind == 'delete_member':
            # W2 幻影清理（复核 c34f38aa A7 / 方案 v2 §5）：删除幻影成员。
            # 防陈旧：写入期 key 必须存在，否则整批拒（A7 明确要求）；证据硬约束 1 统一查。
            if not it.get('class') or it.get('key') is None:
                rejected.append((it, 'delete_member 需要 class + key'))
                continue
            _k = str(it['key'])
            if not re.fullmatch(r'(0[xX][0-9a-fA-F]+|\d+)(_\d+)*', _k):
                rejected.append((it, 'delete_member 的 key %r 非法（允许十进制/hex + N_N 后缀）' % _k))
                continue
        if kind == 'global_categorize':
            # 全局实况清理 G1：分类标注（非破坏——只写 category/storage 字段）。
            # category 白名单=摸底九类规范形。
            _CATS = ('string_literal', 'const_data', 'ptr_table', 'game_state',
                     'unreferenced', 'anchor_object', 'object_interior',
                     'function_static', 'pending')
            if not it.get('addr') or it.get('category') not in _CATS:
                rejected.append((it, 'global_categorize 需要 addr + category∈%s' % (_CATS,)))
                continue
            if not re.fullmatch(r'0[xX][0-9a-fA-F]{5,8}', str(it['addr'])):
                rejected.append((it, 'global_categorize addr 形非法'))
                continue
        if kind == 'delete_global':
            # 全局实况清理 G6/G7：globals.json 删条（防陈旧 + 处置闭合必填）。
            if not it.get('addr'):
                rejected.append((it, 'delete_global 需要 addr'))
                continue
            if not re.fullmatch(r'0[xX][0-9a-fA-F]{5,8}', str(it['addr'])):
                rejected.append((it, 'delete_global addr 形非法'))
                continue
            if not it.get('disposal'):
                rejected.append((it, 'delete_global 需要 disposal（地址处置闭合）'))
                continue
        if kind == 'global_tombstone':
            # C2（75e5af3b 硬条件）：删除=**墓碑化**——写 type=skip 墓碑而非移除条目。
            # 移除条目会撤掉 skip 抑制 ⇒ ida 侧条目发射复活（N1：extern +197 合同破同根）。
            if not it.get('addr'):
                rejected.append((it, 'global_tombstone 需要 addr'))
                continue
            if not re.fullmatch(r'0[xX][0-9a-fA-F]{5,8}', str(it['addr'])):
                rejected.append((it, 'global_tombstone addr 形非法'))
                continue
            if not it.get('disposal'):
                rejected.append((it, 'global_tombstone 需要 disposal（处置闭合）'))
                continue
        if kind == 'global_rename':
            # W2-SceneMgr 弱承接方改名（复核 84fd2ef7 Q2/Q8：m_ 前缀伪成员名/IDA 自动名
            # 当全局名=可追溯性不合格）——只改 name 字段，type/键不动。
            if not it.get('addr') or not it.get('new_name'):
                rejected.append((it, 'global_rename 需要 addr + new_name'))
                continue
        if kind == 'delete_method':
            # C-② 方法误归属清理（1239c52d R4 实证：FormatStatusCaption 是 cdecl 自由函数，
            # 被 SceneMgr_ 前缀误收进 methods 表 ⇒ ECX 跟踪垃圾造 205KB 假偏移）。
            if not it.get('class') or it.get('key') is None:
                rejected.append((it, 'delete_method 需要 class + key(addr)'))
                continue
            if not re.fullmatch(r'(0[xX][0-9a-fA-F]+|\d+)(_\d+)*', str(it['key'])):
                rejected.append((it, 'delete_method 键形非法'))
                continue
        if kind == 'normalize_key':
            # W5 键纪律：known_members 键形态归一（hex/N_N → 纯十进制规范形）。
            # 防陈旧：旧键必须存在、新键不得撞（写入期双查）。
            if not it.get('class') or it.get('from_key') is None or it.get('to_key') is None:
                rejected.append((it, 'normalize_key 需要 class + from_key + to_key'))
                continue
            if not re.fullmatch(r'(0[xX][0-9a-fA-F]+|\d+)(_\d+)*', str(it['from_key'])) \
                    or not re.fullmatch(r'\d+(_\d+)*', str(it['to_key'])):
                rejected.append((it, 'normalize_key 键形非法（from 收全形态，to 须纯十进制）'))
                continue
        if kind == 'type_change':
            # B 批 type-evidence 的落盘条目（2026-09-27）：只动 known_members 的 type，
            # evidence 必须指到具体 insn（硬约束 1 已在上面统一查）。
            if not it.get('class') or it.get('key') is None \
                    or it.get('new_type') not in _TYPE_CHANGE_ALLOWED:
                rejected.append((it, 'type_change 需要 class + key + new_type∈%s（double/指针 v1 禁填）'
                                 % sorted(_TYPE_CHANGE_ALLOWED)))
                continue
            # P1（复核 5560c6c5 纠向）：key 允许**全部真实键形态**——纯十进制/hex + N_N 数组
            # 后缀（实测键谱系 dec 9745/hex 51/N_N 4）。旧规则"放 N_N 拒 hex"方向反了：
            # int('50814_0',0)=508140 是 N_N 被误读（apply_annotations.py:447 已同批修复），
            # 而 int('0x6C',0) 本就正确。hex 键在 B 批工作集真实存在（14 个），拒之会整批卡死。
            _k = str(it['key'])
            if not re.fullmatch(r'(0[xX][0-9a-fA-F]+|\d+)(_\d+)*', _k):
                rejected.append((it, 'type_change 的 key %r 非法（允许十进制/hex + N_N 后缀）' % _k))
                continue
        ok.append(it)

    print('批次 %d 条：通过 %d，拒绝 %d' % (len(items), len(ok), len(rejected)))
    for it, why in rejected:
        print('   [拒绝] %s %s：%s' % (it.get('kind'), it.get('addr') or it.get('class'), why))
    if rejected:
        print('\n有被拒条目 ⇒ **不落盘**（宁可不做，也不写无据的改动）')
        return 1

    done = 0
    for it in ok:
        if it['kind'] == 'reattribute':
            src, sp = load_ann(it['from'])
            dst, dp = load_ann(it['to'])
            ent = (src.get('methods') or {}).pop(it['addr'], None)
            if ent is None:
                # P1-2（2026-09-27 复核 ff86c62f）：跳过即拒绝 ⇒ 静默丢条目却 flush 是原子性漏洞
                _write_rejected += 1
                print('   [拒绝] %s 不在 %s.methods' % (it['addr'], it['from']))
                continue
            # 2026-09-19 两次踩到：签名**不跟着搬**，旧类名留在 signature 里，
            # 生成头会把它发射成原类的静态自由函数（如
            # `static struct _Texture_uv & SetEffectVisible(_Texture_uv *)`）。
            old_sig = str(ent.get('signature') or '')
            if it['from'] in old_sig and not it.get('new_signature'):
                print('   [WARN] %s 的旧签名仍含原类名 %r：%s' % (it['addr'], it['from'], old_sig))
                print('          建议同时给 new_signature（否则生成头会用错类型/退化成 static）')
            if it.get('new_signature'):
                ent['signature'] = it['new_signature']
                ent['signature_note'] = 'reattribute 同时改签名 (was: %s)' % old_sig
            ent['name'] = it['new_name']
            ent['note'] = 'reattribute: %s' % it['evidence']
            ent['name_evidence'] = it['name_evidence']
            dst.setdefault('methods', {})[it['addr']] = ent
            save_ann(src, sp)
            save_ann(dst, dp)
            print('   [重归属] %s: %s -> %s (%s)' % (it['addr'], it['from'], it['to'], it['new_name']))
            done += 1
        elif it['kind'] == 'add_method':
            d, p2 = load_ann(it['class'])
            _exist = (d.get('methods') or {}).get(it['addr'])
            if _exist is not None:
                # 复核 5560c6c5 Q3：内容完全一致 ⇒ 幂等重跑视为 no-op 成功；
                # 内容不一致 ⇒ 批次意图未达成，整批拒。
                if _exist.get('name') == it['new_name'] and _exist.get('signature') == it['signature']:
                    print('   [no-op] %s 已在 %s.methods 且内容一致（幂等重跑 ✓）' % (it['addr'], it['class']))
                    done += 1
                    continue
                _write_rejected += 1
                print('   [拒绝] %s 已在 %s.methods 且内容不一致（批次意图未达成 ⇒ 整批不写）' % (it['addr'], it['class']))
                continue
            d.setdefault('methods', {})[it['addr']] = {
                'name': it['new_name'],
                'signature': it['signature'],
                'note': 'add_method: %s' % it['evidence'],
                'name_evidence': it.get('name_evidence') or '',
            }
            save_ann(d, p2)
            print('   [新增方法] %s.%s = %s' % (it['class'], it['addr'], it['new_name']))
            done += 1
        elif it['kind'] == 'rename':
            d, p = load_ann(it['class'])
            ent = (d.get('methods') or {}).get(it['addr'])
            if ent is None:
                _write_rejected += 1      # P1-2（2026-09-27 复核 ff86c62f）：跳过即拒绝
                print('   [拒绝] %s 不在 %s.methods' % (it['addr'], it['class']))
                continue
            ent['name'] = it['new_name']
            ent['note'] = 'rename: %s' % it['evidence']
            ent['name_evidence'] = it['name_evidence']
            save_ann(d, p)
            print('   [改名] %s.%s -> %s' % (it['class'], it['addr'], it['new_name']))
            done += 1
        elif it['kind'] == 'global_categorize':
            d, p = load_ann('globals',
                            os.path.join(os.path.dirname(ANN), 'globals.json'))
            # 键形无关定位（大小写/前导零形实测混存——0xDC333C 案）：按整数值匹配实际键
            _want = int(str(it['addr']), 16)
            k = next((kk for kk in d
                      if str(kk).startswith('0x') and int(str(kk), 16) == _want), None)
            ent = d.get(k) if k else None
            if ent is None:
                _write_rejected += 1
                print('   [拒绝] global_categorize 地址未注册 %s（防陈旧 ⇒ 整批不写）' % k)
                continue
            old_c = ent.get('category')
            if old_c == it['category']:
                print('   [no-op] %s category 已一致（%s）' % (k, old_c))
                done += 1
                continue
            ent['category'] = it['category']
            ent['source'] = (ent.get('source') or '') + ' | categorize: %s' % it['evidence'][:40]
            save_ann(d, p)
            print('   [分类] %s: %s -> %s' % (k, old_c, it['category']))
            done += 1
        elif it['kind'] == 'delete_global':
            d, p = load_ann('globals',
                            os.path.join(os.path.dirname(ANN), 'globals.json'))
            k = str(it['addr'])
            if k not in d:
                _write_rejected += 1
                print('   [拒绝] delete_global 无此条 %s（防陈旧 ⇒ 整批不写）' % k)
                continue
            ent = d.pop(k)
            save_ann(d, p)
            print('   [全局删除] %s (%s)  处置=%s' % (k, ent.get('name'), it['disposal'][:52]))
            done += 1
        elif it['kind'] == 'global_tombstone':
            d, p = load_ann('globals',
                            os.path.join(os.path.dirname(ANN), 'globals.json'))
            _want = int(str(it['addr']), 16)
            k = next((kk for kk in d
                      if str(kk).startswith('0x') and int(str(kk), 16) == _want), None)
            if k is None:
                k = '0x%08X' % _want          # 墓碑可创建（复活抑制载体）
            ent = d.get(k) or {}
            if ent.get('type') == 'skip' and ent.get('deleted'):
                if it.get('orig_type') and not ent.get('orig_type'):
                    ent['orig_type'] = it['orig_type']   # 回填原类型（复活型解析用）
                    save_ann(d, p)
                    print('   [墓碑补型] %s orig_type=%s' % (k, it['orig_type']))
                    done += 1
                    continue
                print('   [no-op] %s 墓碑已立' % k)
                done += 1
                continue
            _old = ent.get('name')
            ent['orig_type'] = it.get('orig_type') or ent.get('type')   # 原型保存（复活型解析源）
            ent['type'] = 'skip'               # 抑制载体（skip=改名治理不静音语义的反向利用）
            ent['deleted'] = it['disposal']
            ent['category'] = ent.get('category') or 'object_interior'
            ent['source'] = ((ent.get('source') or '') +
                             ' | tombstone(%s): %s' % (_old or '无名', it['evidence'][:40]))
            d[k] = ent
            save_ann(d, p)
            print('   [墓碑] %s (%s) 处置=%s' % (k, _old, it['disposal'][:44]))
            done += 1
        elif it['kind'] == 'global_rename':
            d, p = load_ann('globals',
                            os.path.join(os.path.dirname(ANN), 'globals.json'))
            k = str(it['addr'])
            ent = d.get(k)
            if ent is None:
                _write_rejected += 1
                print('   [拒绝] global_rename 地址未注册 %s（防陈旧 ⇒ 整批不写）' % k)
                continue
            old = ent.get('name')
            if old == it['new_name']:
                print('   [no-op] %s 名已一致（%s）' % (k, old))
                done += 1
                continue
            ent['name'] = it['new_name']
            ent['source'] = (ent.get('source') or '') + ' | global_rename: %s -> %s (%s)' % (
                old, it['new_name'], it['evidence'][:40])
            save_ann(d, p)
            print('   [全局改名] %s: %s -> %s' % (k, old, it['new_name']))
            done += 1
        elif it['kind'] == 'global_retype':
            d, p = load_ann('globals',
                            os.path.join(os.path.dirname(ANN), 'globals.json'))
            k = str(it['addr'])
            ent = d.get(k)
            if ent is None:
                _write_rejected += 1
                print('   [拒绝] global_retype 地址未注册 %s（防陈旧 ⇒ 整批不写）' % k)
                continue
            old = ent.get('type')
            if old == it['new_type']:
                print('   [no-op] %s 类型已一致（%s）' % (k, old))
                done += 1
                continue
            ent['type'] = it['new_type']
            ent['source'] = (ent.get('source') or '') + ' | global_retype: %s' % it['evidence']
            save_ann(d, p)
            print('   [全局定型] %s: %s -> %s  (%s)' % (k, old, it['new_type'], it['evidence'][:50]))
            done += 1
        elif it['kind'] == 'global_add':
            # globals.json 在注解根目录（非 structs/）——W2-④ 实测踩点
            d, p = load_ann('globals',
                            os.path.join(os.path.dirname(ANN), 'globals.json'))
            k = str(it['addr'])
            if k in d:
                _write_rejected += 1
                print('   [拒绝] global_add 地址已注册 %s（防重 ⇒ 整批不写）' % k)
                continue
            d[k] = {'name': it['name'], 'type': it['type'],
                    'source': 'global_add: %s' % it['evidence']}
            save_ann(d, p)
            print('   [全局正名] %s = %s (%s)' % (k, it['name'], it['type']))
            done += 1
        elif it['kind'] == 'delete_method':
            d, p = load_ann(it['class'])
            k = str(it['key'])
            meth = d.get('methods') or {}
            if k not in meth:
                _write_rejected += 1
                print('   [拒绝] delete_method 无此方法 %s.%s（防陈旧 ⇒ 整批不写）' % (it['class'], k))
                continue
            meth.pop(k, None)
            d['methods'] = meth
            save_ann(d, p)
            print('   [方法删除] %s.%s  (%s)' % (it['class'], k, it['evidence'][:52]))
            done += 1
        elif it['kind'] == 'normalize_key':
            d, p = load_ann(it['class'])
            km = d.get('known_members') or {}
            fk, tk = str(it['from_key']), str(it['to_key'])
            if fk not in km:
                _write_rejected += 1
                print('   [拒绝] normalize_key 无旧键 %s.%s（防陈旧 ⇒ 整批不写）' % (it['class'], fk))
                continue
            if tk in km and tk != fk:
                _write_rejected += 1
                print('   [拒绝] normalize_key 新键已存在 %s.%s（防撞 ⇒ 整批不写）' % (it['class'], tk))
                continue
            ent = km[fk]
            ent['source'] = (ent.get('source') or '') + ' | normalize_key: %s -> %s' % (fk, tk)
            # 保序重建（pop/排序都会整文件重排——P1-3 diff 最小化纪律）
            d['known_members'] = {((tk if k == fk else k)): v for k, v in km.items()}
            save_ann(d, p)
            print('   [键归一] %s: %s -> %s' % (it['class'], fk, tk))
            done += 1
        elif it['kind'] == 'delete_member':
            d, p = load_ann(it['class'])
            km = d.get('known_members') or {}
            k = str(it['key'])
            if k not in km:
                _write_rejected += 1
                print('   [拒绝] delete_member 无成员键 %s.%s（防陈旧 ⇒ 整批不写）' % (it['class'], k))
                continue
            gone = km.pop(k)
            save_ann(d, p)
            print('   [删成员] %s.%s (%s) — %s' % (it['class'], k, gone.get('name'),
                                                  it['evidence'][:60]))
            done += 1
        elif it['kind'] == 'type_change':
            # B 批 type-evidence 落盘（2026-09-27）：只动 known_members 的 type，防陈旧批次：
            # 目标键必须存在、当前类型必须仍是占位（不得覆盖已验证类型）。
            d, p = load_ann(it['class'])
            m = (d.get('known_members') or {}).get(str(it['key']))
            if not isinstance(m, dict):
                _write_rejected += 1
                print('   [拒绝] type_change %s 无成员键 %s（防陈旧批次 ✗）' % (it['class'], it['key']))
                continue
            if str(m.get('type')) not in _TYPE_CHANGE_PLACEHOLDERS:
                _write_rejected += 1
                print('   [拒绝] type_change %s.%s 当前类型 %r 非占位（防覆盖已验证类型 ✗）'
                      % (it['class'], it['key'], m.get('type')))
                continue
            old = m.get('type')
            m['type'] = it['new_type']
            m['source'] = (m.get('source') or '') + ' | type_change: %s' % it['evidence']
            save_ann(d, p)
            print('   [类型] %s.%s: %s -> %s  (%s)'
                  % (it['class'], it['key'], old, it['new_type'], it['evidence'][:60]))
            done += 1
        elif it['kind'] in ('set_base_size', 'shift_offset'):
            # A 窄核新增（2026-09-21）：set_base_size 与 shift_offset（含 mult 倍数）
            # 依据：cascade_plan 的精确计划 —— 平移量**非常数**（第 k 个内嵌对象之后 +Δ×k ✓）
            cls = it.get('class')
            if not cls:
                _write_rejected += 1
                print('   [跳过] %s 缺 class' % kind); continue
            p2 = os.path.join(ANN, '%s.json' % cls)
            if not os.path.exists(p2):
                _write_rejected += 1
                print('   [跳过] %s 无注解: %s' % (it['kind'], cls)); continue
            d, p2 = load_ann(cls)      # load_ann 返回 (dict, path) ✓
            if it['kind'] == 'set_base_size':
                frm, to = it.get('from'), it.get('to')
                if d.get('base_size') != frm:
                    _write_rejected += 1
                    print('   [拒绝] %s base_size 期望 %s 实得 %s（防陈旧计划 ✗）' % (cls, frm, d.get('base_size'))); continue
                if not args.dry_run:
                    d['base_size'] = to; save_ann(d, p2)
                print('   [%s] %s base_size %s -> %s' % ('dry-run' if args.dry_run else '落盘', cls, frm, to))
                done += 1
            else:
                key, frm, to = str(it.get('key')), it.get('from'), it.get('to')
                km = d.get('known_members') or {}
                if key not in km:
                    _write_rejected += 1
                    print('   [拒绝] %s 无成员键 %s（防陈旧计划 ✗）' % (cls, key)); continue
                newkm = {}
                _shifted = 0
                for k, v in km.items():
                    o = _norm_off_try(k)
                    if o is not None and frm is not None and o == frm:
                        newkm[str(to)] = v
                        _shifted += 1
                    else:
                        newkm[k] = v
                if frm is not None and _shifted == 0:
                    # 复核 5560c6c5 Q1(a)：from 不命中任何键 = 意图未达成，不得报成功
                    _write_rejected += 1
                    print('   [拒绝] %s shift_offset 的 from=%s 未命中任何成员键（空转 ⇒ 整批不写）' % (cls, frm))
                    continue
                if not args.dry_run:
                    d['known_members'] = newkm; save_ann(d, p2)
                print('   [%s] %s offset %s -> %s (mult=%s)' % ('dry-run' if args.dry_run else '落盘', cls, frm, to, it.get('mult')))
                done += 1
        elif it['kind'] == 'set_size':
            d, p = load_ann(it['class'])
            old = d.get('binary_size')
            d['binary_size'] = it['size']
            # 证据不写进 struct JSON（避免引入未知顶层键）；按 CLAUDE.md 的归属，
            # 单字段证据记 data/annotations/CHANGE_LOG.md。
            save_ann(d, p)
            print('   [尺寸] %s: %s -> %s  (evidence: %s)' % (it['class'], old, it['size'], it['evidence'][:80]))
            done += 1
        elif it['kind'] == 'skip_method':
            d, p = load_ann(it['class'])
            ent = (d.get('methods') or {}).get(it['addr'])
            if ent is None:
                _write_rejected += 1      # P1-2（2026-09-27 复核 ff86c62f）：跳过即拒绝
                print('   [拒绝] %s 不在 %s.methods' % (it['addr'], it['class']))
                continue
            ent['type'] = 'skip'
            ent['reason'] = it['reason']
            ent['note'] = 'skip_method: %s' % it['evidence']
            if it.get('new_name'):
                ent['name'] = it['new_name']
            if it.get('name_evidence'):
                ent['name_evidence'] = it['name_evidence']
            save_ann(d, p)
            print('   [标 skip] %s.%s (%s)' % (it['class'], it['addr'], ent.get('name')))
            done += 1
        elif it['kind'] == 'unskip':
            # 【挂账④ checklist 5】unskip（skip_functions 体排除解除）+单源双向校验
            sk_p = os.path.join(ROOT, 'data', 'annotations', 'skip_functions.json')
            sk = json.load(open(sk_p, encoding='utf-8'))
            if it['addr'] not in sk:
                _write_rejected += 1
                print('   [拒绝] %s 不在 skip_functions' % it['addr'])
                continue
            ent = sk.pop(it['addr'])
            ent['unskipped'] = '2026-10-06'
            ent['unskip_evidence'] = it.get('evidence', '')
            # 单源校验：解禁后不得同时在 functions.json/struct methods 有定义意图注册
            # 【同批配对放行】register_func+unskip 同批=原子解禁（签名源+体收）——合法组合
            _paired = any(x.get('kind') == 'register_func' and x.get('addr') == it['addr']
                          for x in items)
            _fj_p = os.path.join(ROOT, 'data', 'annotations', 'functions.json')
            _fj = json.load(open(_fj_p, encoding='utf-8'))
            _reg = _fj.get(it['addr'])
            if _reg and not _paired and not (_reg.get('declaration_only') or
                             str(_reg.get('signature', '')).rstrip().endswith('(...)')):
                print('   [拒绝] %s 解禁后与 functions.json 定义意图双注（单源）' % it['addr'])
                sk[it['addr']] = ent
                continue
            json.dump(sk, open(sk_p, 'w', encoding='utf-8'), ensure_ascii=False, indent=2)
            print('   [解禁] %s %s（原 reason=%s）' % (it['addr'], ent.get('name'), ent.get('reason')))
            done += 1
        elif it['kind'] == 'register_func':
            # 【挂账④ checklist 5】functions.json 注册（声明收编形——变参/实参形）
            _fj_p = os.path.join(ROOT, 'data', 'annotations', 'functions.json')
            _fj = json.load(open(_fj_p, encoding='utf-8'))
            _fj[it['addr']] = {
                'name': it['name'], 'signature': it['signature'],
                'source': 'register_func: %s' % it.get('evidence', ''),
                'declaration_only': bool(it.get('declaration_only')),
            }
            json.dump(_fj, open(_fj_p, 'w', encoding='utf-8'), ensure_ascii=False, indent=2)
            print('   [注册] %s %s %s' % (it['addr'], it['name'], it['signature'][:40]))
            done += 1
        elif it['kind'] == 'set_signature':
            d, p = load_ann(it['class'])
            ent = (d.get('methods') or {}).get(it['addr'])
            if ent is None:
                _write_rejected += 1      # P1-2（2026-09-27 复核 ff86c62f）：跳过即拒绝
                print('   [拒绝] %s 不在 %s.methods' % (it['addr'], it['class']))
                continue
            old = ent.get('signature')
            ent['signature'] = it['new_signature']
            ent['signature_note'] = 'set_signature: %s (was: %s)' % (it['evidence'], old)
            save_ann(d, p)
            print('   [签名] %s.%s: %s -> %s' % (it['class'], it['addr'], old, it['new_signature']))
            done += 1
        else:
            _write_rejected += 1
            print('   [跳过] 未知 kind: %s' % it.get('kind'))
    # **两阶段**：有拒绝 ⇒ 整批不写 + 非零退出 ✓（复核要求"先全量校验再统一落盘" ✓）
    if rejected:
        print('\n[ABORT] 有 %d 条被拒 ⇒ **整批不写** ✓（两阶段：校验未全过）' % len(rejected))
        return 1
    # **B4 真正的全或无**：任一拒绝（校验阶段或写入阶段）⇒ **flush 之前就中止** ✓
    # （前一版是"先 flush 再报失败" ✗ ⇒ 部分写入仍会发生 ✗，独立复核 bd0abcc1 指出的正是这一点）
    if _write_rejected:
        print('\n[ABORT] 写入阶段有 %d 条被拒 ⇒ **整批不写** ✓（缓冲丢弃，未 flush ✓）' % _write_rejected)
        return 1
    if _BUFFER is not None and not _DRY_RUN:
        # P1-3（2026-09-27 复核 ff86c62f）：**重序列化等价探测** —— 原文件若不能被本序列化器
        # 字节级 round-trip（实测 4/894：Logger.json 的 \uXXXX 转义、tagCam/tagCmdData/
        # tagRoleTask 的 inline 对象），任何落盘都会整文件重排版、淹没 annotation_diff 门禁
        # ⇒ **整批不写**（先全量探测后统一写，探测失败时零落盘 ✓）。
        unpreserved = []
        for path in sorted(_BUFFER):
            orig = open(path, encoding='utf-8', newline='').read()
            if _render_like(json.loads(orig), path) != orig:
                unpreserved.append(os.path.basename(path))
        if unpreserved:
            print('\n[ABORT] 重序列化不等价（原风格保不住，落盘=整文件重排版）: %s'
                  % ', '.join(unpreserved))
            print('        ⇒ **整批不写**（P1-3 探测拦截）')
            return 1
        for path, data in sorted(_BUFFER.items()):
            _dump_like(data, path)     # F8：按原风格回写（indent/换行/尾换行逐文件保持）
        print('\n[flush] 统一落盘 %d 个文件（两阶段 ✓ 全或无 ✓）' % len(_BUFFER))
    print('\n%s %d 条' % ('[dry-run] 计算' if _DRY_RUN else '落盘', done))

    if _DRY_RUN:
        print('[dry-run] **未写任何文件** ✓ —— 确认无误后去掉 --dry-run 再执行 ✓')
        return 0
    rc = subprocess.call([sys.executable, 'pipeline/cli.py', 'check'], cwd=ROOT)
    if rc != 0:
        print('[ERROR] check 未通过')
        return rc
    if args.run_pipeline:
        print('\n=== 跑完整管线（一批只跑一次）===')
        for cmd in (['pipeline/cli.py', 'apply'], ['pipeline/cli.py', 'export'],
                    ['pipeline/gen/codegen.py', 'all'], ['pipeline/cli.py', 'probe', 'all']):
            print('-> %s' % ' '.join(cmd))
            rc = subprocess.call([sys.executable] + cmd, cwd=ROOT)
            if rc != 0:
                print('[ERROR] 管线在 %s 失败' % cmd)
                return rc
        print('管线完成。接着请自行跑 match（字节匹配裁判）并做对账。')
    return 0


if __name__ == '__main__':
    sys.exit(main())
