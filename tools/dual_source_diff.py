#!/usr/bin/env python3
"""双源 diff 报表（只读）—— **往返保真**口径。

对比两侧成员表，产出 `data/status/dual_source_report.md`：

    IDA 侧: asm/pal3/ida_structs.json  →  struct.data_members（{name,type,offset}）
    注解侧: data/annotations/structs/*.json → known_members（{偏移键: {name,type,…}}）

# 口径（2026-10-23 step0 Task 1 · 对抗复核定谳）

**不是「IDA vs 注解」**。`ida_structs.json` 是 `annotation → apply → IDB → export`
的**下游产物**（`pipeline/ida/apply_annotations.py` 写 IDB，`export_full.py` 读 IDB），
两源不并列。本表任何差异只读作**往返保真缺口**：注解信息未在 apply→export 往返中
保真（丢失 / 降级 / 改写），或 export 侧引入了合成成员。
**禁止**把本表读成「IDA 反对注解」或反向「注解错误」。

# 陈旧拒报（stale gate）

报表是**时点读数**。export 早于注解最新改动 ⇒ `ida_structs.json` 是陈旧快照，
此时任何"差异"都可能是假差异（2026-10-19 fixer 陈旧验证致 S2 0/214 误判为改善的
同型坑）⇒ **拒报**：非零退出 + 不写报表 + 记录双侧时间戳供人工判断陈旧多久。
判据：`mtime(ida_structs.json) < max(mtime(ann-dir/*.json))` ⇒ stale。
（**不是**"导出超过 N 小时"的壁钟判据 —— 那会把隔周末的新鲜导出误判为陈旧，
也会把 24h 内的陈旧快照误判为新鲜。）

# dict 形态识别（位面复用 ≠ 偏移冲突）

`known_members` 的三形态是**位面复用声明**（同一存储的多解释视图），不是
「同偏移多成员冲突」（CLAUDE.md 2026-10-16 反向审计定谳：302 员抽样 9/9 全为位面复用）：

1. `type` 为 dict（`{"union": [...]}` / `{"struct": [...]}`，inline union/struct）；
2. `source` 带 `overlap`；
3. 同偏移 `_N` 变体键（如 `8` + `8_1`）。

三者单列「位面复用」账，**不计**成员缺失 / 类型差异 / 偏移冲突。
dict 形态的往返形是合成类型名 `_inline_<类>_<成员>`（`apply_annotations.py` 造名），
两侧按名对账即保真；同偏移多成员在 IDB 侧本就是多个重叠成员，属预期。

# 判据（成员配对）

按 **(基偏移, 成员名)** 配对（键 `12` / `12_1` 的基偏移都是 12；同偏移多视图靠名字
区分 —— 只按 offset 配对会互相顶掉，实测 tagNewItem@12 / scVARIANT_data@0 双视图）：

| 分类 | 判据 | 计入缺口？ |
|---|---|---|
| exact | 两侧 type 串全同 | 否 |
| spelling | 归一化后同型（DWORD/unsigned int、_BYTE/unsigned char、long/int…）| 否 |
| divergent | 归一化后仍不同 | **是**（类型差异）|
| 位面复用 | dict / overlap / `_N` 变体（见上）| 否 |
| base_region | 成员偏移 < base_size（基类区域，IDB 不在派生类重复声明）| 否 |
| relocated | `__vftable`/`baseclass*` → IDB 侧归位 `vtables`/`bases` 字段 | 否 |
| ann_missing | 其余「注解有 · 导出缺」 | **是**（往返丢失）|
| ida_extra | 「导出有 · 注解缺」（`_tail_*` 为 export 合成补尾，单列）| **是**（合成引入）|

类型拼写归一（MSVC6 x86 语义等价）：DWORD/UINT/uint→unsigned int、WORD→unsigned
__int16、BYTE/_BYTE→unsigned char、_DWORD→unsigned int、_QWORD→unsigned __int64、
short→signed __int16、__int64→signed __int64、long→int（32 位 long==int）、
BOOL→int、剥 `struct|union|class ` 前缀、空白归一。**只做等价变换**，不做信息取舍
（STL 折叠 `char[N]`、指针级变化、const 丢失等都留在「类型差异」）。

# 用法

    python3 tools/dual_source_diff.py                      # 仓库默认路径
    python3 tools/dual_source_diff.py --ida-structs I --ann-dir A --out O

stdout 打印 `[dual_source_diff] k=v …` 度量行；同值另发 `METRIC k=v` 兼容前缀
（早期草稿/外部脚本按 `METRIC` 抓取，双前缀同值不产生歧义）。
退出码：0=报表已写；2=拒报（陈旧 / 输入缺失）。
**只读**：除 `--out` 指定的报表外不写任何文件，不改两侧输入。

设计/测试：`tests/test_dual_source_diff.py`（生成 / 陈旧拒报 / dict 形态 / 检出力）。
"""
import argparse
import glob
import json
import os
import re
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEF_IDA = os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json')
DEF_ANN = os.path.join(ROOT, 'data', 'annotations', 'structs')
DEF_OUT = os.path.join(ROOT, 'data', 'status', 'dual_source_report.md')

_VFPT = ('__vftable', '_vftable')
_BASECLASS_RE = re.compile(r'^baseclass\d*$', re.I)
_OFFSET_KEY_RE = re.compile(r'^(\d+)(?:_(\d+))?$')
_INLINE_REF_RE = re.compile(r'_inline_[A-Za-z0-9_]+(?:::\$[0-9A-Fa-f]+)?')


# ---------------------------------------------------------------- 类型归一

def canon_type(t):
    """类型串归一（拼写等价判据；只做等价变换）。

    dict 形态（inline union/struct）返回 '<dict:…>' 占位 —— 位面复用不走类型比对。
    """
    if isinstance(t, dict):
        return '<dict:%s>' % json.dumps(t, sort_keys=True, ensure_ascii=False)
    s = str(t)
    s = s.replace('long long', 'signed __int64')
    s = re.sub(r'\bunsigned\s+short\b', 'unsigned __int16', s)
    s = re.sub(r'(?<![\w_])short\b', 'signed __int16', s)
    s = re.sub(r'(?<!unsigned )(?<!signed )\b__int16\b', 'signed __int16', s)
    s = re.sub(r'(?<!unsigned )(?<!signed )\b__int64\b', 'signed __int64', s)
    s = re.sub(r'\b(DWORD|UINT|uint|_DWORD)\b', 'unsigned int', s)
    s = re.sub(r'\b(WORD|_WORD)\b', 'unsigned __int16', s)
    s = re.sub(r'\b(BYTE|_BYTE)\b', 'unsigned char', s)
    s = re.sub(r'\b_QWORD\b', 'unsigned __int64', s)
    s = re.sub(r'\bBOOL\b', 'int', s)
    s = re.sub(r'\blong\b', 'int', s)
    s = re.sub(r'\b(struct|union|class)\s+', '', s)
    s = re.sub(r'\s*\*\s*', ' * ', s)
    s = re.sub(r'\s*\[\s*', '[', s)
    s = re.sub(r'\s*\]\s*', '] ', s)
    s = re.sub(r'\s*,\s*', ', ', s)
    return re.sub(r'\s+', ' ', s).strip()


def _ts(ts):
    """时间戳两读：epoch（可比较）+ 本地可读（可人工核对）。"""
    return '%.6f' % ts, time.strftime('%Y-%m-%d %H:%M:%S %z', time.localtime(ts))


def _rel(path):
    try:
        p = os.path.relpath(os.path.abspath(path), ROOT)
        return path if p.startswith('..') else p
    except ValueError:
        return path


# ---------------------------------------------------------------- 装载

def load_ann(ann_dir):
    """注解侧：{struct_name: 原始 dict}（无 name 的文件跳过并告警）。"""
    out, unnamed = {}, []
    for f in sorted(glob.glob(os.path.join(ann_dir, '*.json'))):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except (ValueError, OSError) as e:
            print('[WARN] 注解文件不可读，跳过: %s (%s)' % (f, e), file=sys.stderr)
            continue
        if not isinstance(d, dict):
            continue
        name = d.get('name')
        if not name:
            unnamed.append(os.path.basename(f))
            continue
        out[name] = d
    return out, unnamed


def _ann_offset_key(key):
    """偏移键 ⇒ (基偏移, 变体后缀)。`12_1` ⇒ (12, '1')；非法键 ⇒ (None, None)。"""
    m = _OFFSET_KEY_RE.match(str(key))
    if not m:
        return None, None
    return int(m.group(1)), m.group(2)


def _is_bitplane(member, key_suffix):
    """位面复用三形态判定 ⇒ (dict 形态, overlap 声明, 同偏移变体键)。"""
    t = member.get('type')
    src = str(member.get('source') or '')
    return (isinstance(t, dict),
            'overlap' in src,
            key_suffix is not None)


def _bp_kind(bp):
    dictish, ovl, suf = bp
    kinds = []
    if dictish:
        kinds.append('dict')
    if ovl:
        kinds.append('overlap')
    if suf:
        kinds.append('suffix')
    return '+'.join(kinds) or '—'


def _type_str(t):
    return t if isinstance(t, str) else json.dumps(t, sort_keys=True,
                                                   ensure_ascii=False)


def _bitplane_expected_inline(cls, member_name):
    """dict 形态的往返合成名（apply_annotations: `_inline_%s_%s`）。"""
    return '_inline_%s_%s' % (cls, member_name or '')


# ---------------------------------------------------------------- 对账

def classify(ida, ann):
    """逐结构对账 ⇒ 计数 + 明细（全部排序，保证同输入同输出）。"""
    r = {
        'structs': {'both': [], 'ida_only': [], 'ann_only': []},
        'size_mismatch': [],
        'exact': 0,
        'spelling': [],          # (cls, key, name, ann_type, ida_type)
        'divergent': [],         # 同上
        'bitplane': [],          # (cls, key, name, kind, ida_type, note)
        'ann_missing': [],       # 真缺口 (cls, key, name, type)
        'ann_base_region': [],
        'ann_relocated_vptr': [],
        'ann_relocated_base': [],
        'ida_extra': [],         # (cls, off, name, type, is_tail)
        'per_struct': [],        # 逐类差异行
    }

    for name in sorted(set(ida) & set(ann)):
        a, i = ann[name], ida[name]
        ak = a.get('known_members') or {}
        imembers = i.get('data_members') or []
        if (a.get('binary_size') is not None and i.get('size') is not None
                and int(a['binary_size']) != int(i['size'])):
            r['size_mismatch'].append((name, a.get('binary_size'), i.get('size')))

        imap = {}
        for m in imembers:
            try:
                off = int(m.get('offset'))
            except (TypeError, ValueError):
                continue
            imap.setdefault((off, m.get('name') or ''), []).append(m)

        base_size = int(a.get('base_size') or 0)
        n_exact = n_spell = n_div = n_bm = n_miss = n_extra = 0

        for key in sorted(ak, key=lambda k: str(k)):
            m = ak[key] or {}
            boff, suf = _ann_offset_key(key)
            nm = m.get('name') or ''
            at = m.get('type')
            bp = _is_bitplane(m, suf)
            cand = imap.get((boff, nm)) if boff is not None else None
            if cand:
                im0 = cand.pop(0)
                it = im0.get('type')
                if any(bp) or (isinstance(it, str) and it.startswith('_inline_')):
                    note = ''
                    if isinstance(at, dict):
                        exp = _bitplane_expected_inline(name, nm)
                        if not (isinstance(it, str)
                                and (it == exp or it.startswith(exp + '::$'))):
                            note = '合成名不对称：期望 %s 实得 %s' % (exp, it)
                    r['bitplane'].append((name, str(key), nm,
                                          _bp_kind(bp), str(it), note))
                    n_bm += 1
                elif at == it:
                    r['exact'] += 1
                    n_exact += 1
                elif canon_type(at) == canon_type(it):
                    r['spelling'].append((name, str(key), nm, str(at), str(it)))
                    n_spell += 1
                else:
                    r['divergent'].append((name, str(key), nm, str(at), str(it)))
                    n_div += 1
                continue
            # 未配对的注解成员
            nm_l = nm.lower()
            if nm_l in _VFPT and (i.get('vtables') or i.get('bases')):
                r['ann_relocated_vptr'].append((name, str(key), nm))
            elif _BASECLASS_RE.match(nm_l) and i.get('bases'):
                r['ann_relocated_base'].append((name, str(key), nm))
            elif base_size and boff is not None and boff < base_size:
                r['ann_base_region'].append((name, str(key), nm, boff))
            elif any(bp):
                r['bitplane'].append((name, str(key), nm, _bp_kind(bp),
                                      '（导出缺）', '位面复用成员未见于导出'))
                n_bm += 1
            else:
                r['ann_missing'].append((name, str(key), nm, _type_str(at)))
                n_miss += 1

        for (off, nm), lst in sorted(imap.items(), key=lambda kv: kv[0]):
            for im0 in lst:
                tail = str(im0.get('name') or '').startswith('_tail_')
                r['ida_extra'].append((name, off, nm, str(im0.get('type')), tail))
                n_extra += 1

        r['per_struct'].append((name, len(ak), len(imembers),
                                n_exact, n_spell, n_div, n_bm, n_miss, n_extra))

    r['structs']['both'] = sorted(set(ida) & set(ann))
    r['structs']['ida_only'] = sorted(set(ida) - set(ann))
    r['structs']['ann_only'] = sorted(set(ann) - set(ida))
    return r


def inline_symmetry(ida):
    """`_inline_*` 引用 vs 定义对称性（合成名对账）。"""
    defs = set(k for k in ida if str(k).startswith('_inline_'))
    refs = set()
    for s in ida.values():
        for m in (s.get('data_members') or []):
            for t in _INLINE_REF_RE.findall(str(m.get('type') or '')):
                refs.add(t)
    return {
        'defs': sorted(defs),
        'refs': sorted(refs),
        'missing_def': sorted(refs - defs),
        'unreferenced': sorted(defs - refs),
    }


# ---------------------------------------------------------------- 报表

def render(r, sym, meta):
    """渲染 markdown 报表（纯函数：同输入 ⇒ 同输出，无 wall-clock）。"""
    L = []
    A = L.append
    A('# 双源 diff 报表（只读）')
    A('')
    A('> **口径 = 往返保真**（非「IDA vs 注解」）：`asm/pal3/ida_structs.json` 是 '
      '`annotation → apply → IDB → export` 的**下游产物**，两源不并列。'
      '本表任何差异只读作**往返保真缺口**（注解未在 apply→export 往返中保真 / '
      'export 侧合成成员），不得读成「IDA 反对注解」或「注解错误」。')
    A('>')
    A('> **位面复用 ≠ 偏移冲突**：`known_members` 的 dict 形态（inline union/struct）、'
      '`source:overlap`、同偏移 `_N` 变体键是**同一存储的多解释视图声明**，'
      '单列「位面复用」账，不计缺失/冲突（CLAUDE.md 2026-10-16 反向审计定谳）。')
    A('>')
    A('> **陈旧拒报**：export 时间戳早于注解最新改动 ⇒ 本报表**不生成**（rc=2）。')
    A('')
    A('## 0. 输入与时间戳（陈旧拒报判据）')
    A('')
    A('| 项 | 值 |')
    A('|---|---|')
    A('| 导出产物 | `%s` |' % meta['ida_path'])
    A('| 注解目录 | `%s`（%d 个 JSON） |' % (meta['ann_path'], meta['ann_count']))
    A('| export 时间戳 | %s（epoch %s） |' % (meta['export_readable'],
                                              meta['export_ts']))
    A('| 注解最新改动 | %s（epoch %s） |' % (meta['ann_readable'], meta['ann_ts']))
    A('| 注解最新改动文件 | `%s` |' % meta['ann_newest'])
    A('| 陈旧判定 | %s |' % meta['stale_verdict'])
    A('')

    both = r['structs']['both']
    n_bad_struct = sum(1 for x in r['per_struct']
                       if x[4] or x[5] or x[6] or x[7] or x[8])
    A('## 1. 量化统计')
    A('')
    A('| 指标 | 值 |')
    A('|---|---|')
    A('| 结构：双侧共有 / 仅导出 / 仅注解 | %d / %d / %d |'
      % (len(both), len(r['structs']['ida_only']),
         len(r['structs']['ann_only'])))
    A('| 成员全同（type 串全同） | %d |' % r['exact'])
    A('| 成员拼写归一（语义等价，不计差异） | %d |' % len(r['spelling']))
    A('| **类型差异（语义不等）** | **%d** |' % len(r['divergent']))
    A('| **成员缺失（注解有 · 导出缺，真缺口）** | **%d** |'
      % len(r['ann_missing']))
    A('| **成员新增（导出有 · 注解缺）** | **%d** |' % len(r['ida_extra']))
    A('| └ 其中 export 合成补尾 `_tail_*` | %d |'
      % sum(1 for x in r['ida_extra'] if x[4]))
    A('| 位面复用声明（dict / overlap / 同偏移变体） | %d |'
      % len(r['bitplane']))
    A('| 已解释·基类区域成员（偏移 < base_size） | %d |'
      % len(r['ann_base_region']))
    A('| 已解释·vptr/base 声明迁移到 vtables/bases | %d |'
      % (len(r['ann_relocated_vptr']) + len(r['ann_relocated_base'])))
    A('| 结构 sizeof 不一致 | %d |' % len(r['size_mismatch']))
    A('| `_inline_*` 引用 / 定义 / 引用无定义 / 定义未引用 | %d / %d / %d / %d |'
      % (len(sym['refs']), len(sym['defs']), len(sym['missing_def']),
         len(sym['unreferenced'])))
    A('')
    A('**多少类不一致？** %d 个结构存在任一差异（成员数/偏移/类型），见 §8；'
      '**多少成员缺失？** 真缺口 %d 个，见 §2（另 %d 个已解释不计缺口）。'
      % (n_bad_struct, len(r['ann_missing']),
         len(r['ann_base_region']) + len(r['ann_relocated_vptr'])
         + len(r['ann_relocated_base'])))
    A('')

    A('## 2. 成员缺失（注解有 · 导出缺）')
    A('')
    A('往返丢失真缺口（**未**被基类区域 / vptr·base 归位解释的）：')
    A('')
    if r['ann_missing']:
        A('| 类 | 偏移键 | 成员 | 注解 type |')
        A('|---|---|---|---|')
        for cls, key, nm, t in r['ann_missing']:
            A('| %s | %s | %s | `%s` |' % (cls, key, nm, t))
    else:
        A('（无）')
    A('')
    A('### 已解释（不计缺口）')
    A('')
    A('| 解释类 | 数量 | 说明 |')
    A('|---|---|---|')
    A('| 基类区域成员 | %d | 偏移 < base_size：IDB 只在基类声明，派生类不重复 |'
      % len(r['ann_base_region']))
    A('| vptr 声明迁移 | %d | `__vftable`/`_vftable` 归位 IDB `vtables`/`bases` 字段 |'
      % len(r['ann_relocated_vptr']))
    A('| baseclass 声明迁移 | %d | `baseclass*` 归位 IDB `bases` 字段 |'
      % len(r['ann_relocated_base']))
    A('')
    for title, rows in (('基类区域成员', r['ann_base_region']),
                        ('vptr 声明迁移', r['ann_relocated_vptr']),
                        ('baseclass 声明迁移', r['ann_relocated_base'])):
        if not rows:
            continue
        A('### %s（%d）' % (title, len(rows)))
        A('')
        A('| 类 | 偏移键 | 成员 |')
        A('|---|---|---|')
        for row in rows:
            A('| %s | %s | %s |' % (row[0], row[1], row[2]))
        A('')

    A('## 3. 成员新增（导出有 · 注解缺）')
    A('')
    tails = [x for x in r['ida_extra'] if x[4]]
    others = [x for x in r['ida_extra'] if not x[4]]
    A('export 侧合成补尾 `_tail_*`（%d 个，合成填充非注解声明）：' % len(tails))
    A('')
    if tails:
        A('| 类 | 偏移 | 名 | type |')
        A('|---|---|---|---|')
        for cls, off, nm, t, _ in tails:
            A('| %s | %d | %s | `%s` |' % (cls, off, nm, t))
    else:
        A('（无）')
    A('')
    A('非合成补尾的新增（%d 个）：' % len(others))
    A('')
    if others:
        A('| 类 | 偏移 | 名 | type |')
        A('|---|---|---|---|')
        for cls, off, nm, t, _ in others:
            A('| %s | %d | %s | `%s` |' % (cls, off, nm, t))
    else:
        A('（无）')
    A('')

    A('## 4. 类型差异（语义不等）')
    A('')
    A('归一化后仍不同的类型对（往返降级 / 重解释，**真差异**）：')
    A('')
    if r['divergent']:
        A('| 类 | 偏移键 | 成员 | 注解 type | 导出 type |')
        A('|---|---|---|---|---|')
        for cls, key, nm, at, it in r['divergent']:
            A('| %s | %s | %s | `%s` | `%s` |' % (cls, key, nm, at, it))
    else:
        A('（无）')
    A('')

    A('## 5. 类型拼写归一（语义等价 · 不计差异）')
    A('')
    A('同型异拼（MSVC6 x86 等价：DWORD/UINT/uint=unsigned int、WORD=unsigned '
      '__int16、BYTE=_BYTE=unsigned char、long=int、short=signed __int16…），'
      '逐拼写族计数：')
    A('')
    fam = {}
    for cls, key, nm, at, it in r['spelling']:
        fam.setdefault((at, it), []).append((cls, key, nm))
    if fam:
        A('| 注解 type | 导出 type | 数量 | 样例 |')
        A('|---|---|---|---|')
        for (at, it), rows in sorted(fam.items(),
                                     key=lambda kv: (-len(kv[1]), kv[0])):
            ex = ', '.join('%s@%s' % (x[0], x[1]) for x in rows[:2])
            A('| `%s` | `%s` | %d | %s |' % (at, it, len(rows), ex))
    else:
        A('（无）')
    A('')

    A('## 6. 位面复用（非偏移冲突）')
    A('')
    A('**位面复用 ≠ 偏移冲突**：以下成员是同一存储的多解释视图（dict 形态 inline '
      'union/struct · `source:overlap` · 同偏移 `_N` 变体键），IDB 侧同偏移多成员'
      '属预期，**不计**缺失/类型差异/冲突。dict 形态的往返形是合成名 '
      '`_inline_<类>_<成员>`：')
    A('')
    kinds = {}
    for row in r['bitplane']:
        kinds[row[3]] = kinds.get(row[3], 0) + 1
    A('| 形态 | 数量 |')
    A('|---|---|')
    for k in sorted(kinds):
        A('| %s | %d |' % (k, kinds[k]))
    A('| 合计（条目） | %d |' % len(r['bitplane']))
    A('')
    if r['bitplane']:
        A('| 类 | 偏移键 | 成员 | 形态 | 导出 type | 备注 |')
        A('|---|---|---|---|---|---|')
        for cls, key, nm, kind, it, note in r['bitplane']:
            A('| %s | %s | %s | %s | `%s` | %s |'
              % (cls, key, nm, kind, it, note or '—'))
    else:
        A('（无）')
    A('')

    A('## 7. `_inline_*` 引用 vs 定义对称性')
    A('')
    A('| 项 | 数量 |')
    A('|---|---|')
    A('| 引用（成员 type 里的合成名） | %d |' % len(sym['refs']))
    A('| 定义（ida_structs 顶层 `_inline_*` 键） | %d |' % len(sym['defs']))
    A('| 引用无定义 | %d |' % len(sym['missing_def']))
    A('| 定义未被引用 | %d |' % len(sym['unreferenced']))
    A('')
    if sym['missing_def']:
        A('引用无定义（合成名不对称 ⇒ 下游 C2011 双产/漏产风险）：')
        A('')
        for t in sym['missing_def']:
            A('- `%s`' % t)
        A('')
    if sym['unreferenced']:
        A('定义未被引用：')
        A('')
        for t in sym['unreferenced']:
            A('- `%s`' % t)
        A('')

    A('## 8. 逐类差异（成员数 / 偏移 / 类型）')
    A('')
    A('每类一行：成员数（注解/导出）+ 差异计数（拼写/类型/位面/缺口/新增）。')
    A('')
    rows = [x for x in r['per_struct'] if x[4] or x[5] or x[6] or x[7] or x[8]]
    if rows:
        A('| 类 | 成员数(注解/导出) | 拼写归一 | 类型差异 | 位面复用 | 缺失 | 新增 |')
        A('|---|---|---|---|---|---|---|')
        for (cls, na, ni, ne, nsp, ndv, nbm, nms, nex) in rows:
            A('| %s | %d/%d | %d | %d | %d | %d | %d |'
              % (cls, na, ni, nsp, ndv, nbm, nms, nex))
    else:
        A('（无逐类差异）')
    A('')

    A('## 9. 结构覆盖（单侧独有）')
    A('')
    A('| 侧 | 数量 | 说明 |')
    A('|---|---|---|')
    A('| 仅导出（IDB 独有） | %d | 多为 CRT/系统类型（无注解属预期） |'
      % len(r['structs']['ida_only']))
    A('| 仅注解（导出缺） | %d | 注解结构未见于导出 ⇒ 整类往返缺口，须查 apply 是否跳过 |'
      % len(r['structs']['ann_only']))
    A('')
    if r['structs']['ann_only']:
        A('仅注解（导出缺）清单：')
        A('')
        for n in r['structs']['ann_only']:
            A('- `%s`' % n)
        A('')
    if r['size_mismatch']:
        A('sizeof 不一致：')
        A('')
        A('| 类 | 注解 binary_size | 导出 size |')
        A('|---|---|---|')
        for cls, bs, isz in r['size_mismatch']:
            A('| %s | %s | %s |' % (cls, bs, isz))
        A('')

    A('## 10. 口径附注')
    A('')
    A('- **只读**：本工具不改任何输入；只写本报表。')
    A('- **陈旧拒报**：export 时间戳早于注解最新改动 ⇒ 拒报（rc=2），'
      '避免拿过期快照当读数（2026-10-19 陈旧验证误判同型坑）。')
    A('- **dict 形态识别**：inline union/struct（dict `type`）、`source:overlap`、'
      '同偏移 `_N` 变体键 ⇒ 位面复用（非偏移冲突），见 §6。')
    A('- **拼写归一只做等价变换**（§5 判据），不抹真实差异（§4）：'
      'STL 折叠 `char[N]`、指针级变化、const 丢失等都留在 §4。')
    A('- 配对键是 **(基偏移, 成员名)**：同偏移多视图靠名字区分，'
      '`12` / `12_1` 同基偏移属位面复用变体。')
    A('- 同输入 ⇒ 同输出：全表排序输出，不含 wall-clock。')
    A('')
    return '\n'.join(L) + '\n'


# ---------------------------------------------------------------- main

def _emit_metrics(pairs):
    """双前缀打印度量：`[dual_source_diff]`（本工具主格式）+ `METRIC`（兼容旧抓取）。"""
    for key, val in pairs:
        print('[dual_source_diff] %s=%s' % (key, val))
    for key, val in pairs:
        print('METRIC %s=%s' % (key, val))


def main(argv=None):
    ap = argparse.ArgumentParser(description='双源 diff 报表（只读，往返保真口径）')
    ap.add_argument('--ida-structs', default=DEF_IDA,
                    help='IDA 导出产物（默认 asm/pal3/ida_structs.json）')
    ap.add_argument('--ann-dir', default=DEF_ANN,
                    help='注解结构目录（默认 data/annotations/structs）')
    ap.add_argument('--out', default=DEF_OUT,
                    help='报表输出（默认 data/status/dual_source_report.md）')
    args = ap.parse_args(argv)

    if not os.path.exists(args.ida_structs):
        print('[ERROR] 缺少导出产物 %s（先跑 pipeline/cli.py export）'
              % args.ida_structs, file=sys.stderr)
        return 2
    if not os.path.isdir(args.ann_dir):
        print('[ERROR] 缺少注解目录 %s' % args.ann_dir, file=sys.stderr)
        return 2

    export_ts = os.path.getmtime(args.ida_structs)
    ann_files = sorted(glob.glob(os.path.join(args.ann_dir, '*.json')))
    if not ann_files:
        print('[ERROR] 注解目录为空: %s' % args.ann_dir, file=sys.stderr)
        return 2
    ann_newest = max(ann_files, key=lambda p: os.path.getmtime(p))
    ann_ts = os.path.getmtime(ann_newest)

    e_epoch, e_readable = _ts(export_ts)
    a_epoch, a_readable = _ts(ann_ts)
    stale = export_ts < ann_ts
    if stale:
        _emit_metrics([('export_ts', e_epoch), ('ann_ts', a_epoch),
                       ('stale', 1)])
        print('[STALE] 拒报：export 时间戳 %s（epoch %s）早于注解最新改动 %s'
              '（epoch %s，%s）⇒ %s 是陈旧快照，差异读数不可信。'
              '请先重跑 apply→export（python pipeline/cli.py export）再出报表。'
              % (e_readable, e_epoch, a_readable, a_epoch,
                 _rel(ann_newest), _rel(args.ida_structs)), file=sys.stderr)
        return 2

    ida = json.load(open(args.ida_structs, encoding='utf-8'))
    ann, unnamed = load_ann(args.ann_dir)
    if unnamed:
        print('[WARN] %d 个注解文件缺 name，跳过: %s'
              % (len(unnamed), ', '.join(unnamed)), file=sys.stderr)

    r = classify(ida, ann)
    sym = inline_symmetry(ida)
    meta = {
        'ida_path': _rel(args.ida_structs),
        'ann_path': _rel(args.ann_dir),
        'ann_count': len(ann_files),
        'export_ts': e_epoch, 'export_readable': e_readable,
        'ann_ts': a_epoch, 'ann_readable': a_readable,
        'ann_newest': _rel(ann_newest),
        'stale_verdict': 'FRESH（export 不早于注解最新改动）',
    }

    n_bp = len(r['bitplane'])
    pairs = [
        ('export_ts', e_epoch), ('ann_ts', a_epoch), ('stale', 0),
        ('structs_both', len(r['structs']['both'])),
        ('ida_only', len(r['structs']['ida_only'])),
        ('ann_only', len(r['structs']['ann_only'])),
        ('exact', r['exact']),
        ('spelling', len(r['spelling'])),
        ('divergent', len(r['divergent'])),
        ('bitplane_dict',
         sum(1 for x in r['bitplane'] if 'dict' in x[3])),
        ('bitplane_suffix',
         sum(1 for x in r['bitplane'] if 'suffix' in x[3])),
        ('bitplane_overlap',
         sum(1 for x in r['bitplane'] if 'overlap' in x[3])),
        ('bitplane', n_bp),
        ('ann_missing', len(r['ann_missing'])),
        ('ida_extra', len(r['ida_extra'])),
        ('ida_extra_tail', sum(1 for x in r['ida_extra'] if x[4])),
        ('ann_base_region', len(r['ann_base_region'])),
        ('ann_relocated_vptr', len(r['ann_relocated_vptr'])),
        ('ann_relocated_base', len(r['ann_relocated_base'])),
        ('size_mismatch', len(r['size_mismatch'])),
        ('inline_defs', len(sym['defs'])),
        ('inline_refs', len(sym['refs'])),
        ('inline_missing_def', len(sym['missing_def'])),
        ('inline_unref', len(sym['unreferenced'])),
    ]

    text = render(r, sym, meta)
    out_dir = os.path.dirname(os.path.abspath(args.out))
    if out_dir and not os.path.isdir(out_dir):
        os.makedirs(out_dir, exist_ok=True)
    with open(args.out, 'w', encoding='utf-8') as fh:
        fh.write(text)
    _emit_metrics(pairs)
    print('report: %s' % _rel(args.out))
    return 0


if __name__ == '__main__':
    sys.exit(main())
