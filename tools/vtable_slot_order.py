#!/usr/bin/env python3
"""vtable 槽序**正向规则**（声明 → 槽序）—— MSVC 6.0 SP0 实测规则的可执行形式。

本模块回答一个问题：**给定类的 virtual 声明（和基类已知槽序），编译器会排出什么槽序？**
供 `vtable_decl_check`（Task 5 声明校验）等消费。反向（槽序→声明）**不**在本模块——
逆映射已被 ABI 证伪不可还原（attack README A-1/A-3）。

## 规则（每条都有真机实测金样本，见 tests/test_vtable_slot_order.py）

 1. **继承槽原位保留；覆写原位替换**。按 match_key=(kind, 参数, 方法 cv[, 名字]) 匹配，
    覆写者替换基类槽的**槽位**，不移动、不计数变化。
    （vt6/DO：4 槽逐位继承、仅 1 槽替换；D7/D8：析构覆写同样原位。）
 2. **本地新增段尾插**。未匹配到任何继承槽的声明进入本地新增段，接在继承段之后；
    MI 下**只进主视图**（首基链），次视图不含新增槽。（vt2：m 只在 ??_7D@@6BA@@@ 表尾。）
 3. **本地段内同名组逆序**。同名声明成组，**整组占据首现声明的组位**（连续区段），
    组内按声明序的**逆序**排放；组间按各组首现声明的先后排列。
    （T1：[o(),o(int),o(double)]→[o(double),o(int),o()]；T3：插队者 q 被挤到组后。）
 4. **合成槽（deleting_dtor 等）落声明位，不参与同名分组**。合成声明各自构成**单槽组**，
    组位=其声明序在各组首现序中的秩；既不与任何名字合并、也不逆序。
    （adv3：decl[~C3,o() const,o(int)]→[??_E,o(int),o() const]。）

### 打包细节（判别性实测，实现必须照做）

 * **本地段按全部本地声明打包（含覆写），打包后再把覆写者摘除**——摘除序 ≠ 重排序。
   判别样本 DA：decl[o(int)覆写,z,o(char*)]→[o(int)@DA,o(char*)@DA,z]；
   若"只按新增声明打包"会得 [o(int),z,o(char*)] ⇒ slot1/2 互换（实测证伪）。
 * 合成槽"落声明位"= **单槽组的组秩**，**不是字面声明下标**：P1 decl[o()(0),~(1),o(int)(2)]
   实测 → [o(int),o(),??_E]，dtor 落槽 2；钉死下标 1 会得 [o(int),??_E,o()]（实测证伪）。

## 边界（有意不做，防止静默错误）

 * **不用 mangling 识别合成槽**：真实二进制 531 槽仅 4 条带 mangled 符号；合成性由**声明**
   给出（kind 字段）——虚析构声明 ⇒ deleting_dtor。槽**内容**分类（adjustor_static/
   adjustor_vbase/purecall/composite…）属 `vtable_slot_classifier`（Task 2），本模块 kind 是
   **声明级**标记：KIND_FUNC（普通虚函数，纯虚也是）｜非 KIND_FUNC ⇒ 合成单槽组。
 * **虚继承视图合成拒绝执行**（NotImplementedError）：attack README B-1..B-4 实测缺口
   （1 声明↔多视图多槽、声明落异己视图、动态 delta）⇒ 归 Task 2/5/6，本模块不猜。
 * adjustor thunk 是同一声明在**其他视图**的槽内容，不新增槽、不改槽序（vt3：一函数两槽，
   两视图各 1 槽）。
 * 签名推断（Task 3）、槽数审计、双侧对比（Task 6）不在本模块。

用法：
    slots = compute_slot_order([], decls)             # 无基类
    slots = compute_slot_order(base_slots, decls)     # 单链继承
    views = compute_class_views(hierarchy, 'D')       # MI：[(视图标签, 槽序), ...]，主视图在前
"""
import re
from dataclasses import dataclass, replace

__all__ = [
    'KIND_FUNC', 'KIND_DELETING_DTOR', 'SYNTHETIC_KINDS',
    'ORIGIN_INHERITED', 'ORIGIN_OVERRIDE', 'ORIGIN_NEW',
    'VirtualDecl', 'SlotEntry', 'match_key',
    'layout_local_segment', 'compute_slot_order', 'compute_class_views',
]

KIND_FUNC = 'func'
KIND_DELETING_DTOR = 'deleting_dtor'
# 声明级合成槽种类。adjustor_* / composite 是槽内容种类（Task 2 词表），
# 若上游以声明形式传入同样按"合成单槽组"处理。
SYNTHETIC_KINDS = frozenset({
    KIND_DELETING_DTOR,
    'adjustor', 'adjustor_static', 'adjustor_vbase', 'adjustor_dynamic', 'composite',
})

ORIGIN_INHERITED = 'inherited'   # 继承槽原位未动
ORIGIN_OVERRIDE = 'override'     # 覆写原位替换
ORIGIN_NEW = 'new'               # 本地新增段尾插


@dataclass(frozen=True)
class VirtualDecl:
    """一条 virtual 声明（声明级信息，不含槽内容）。

    name: 不含类限定的名字；析构写 '~C3'（名字**不**参与合成槽匹配——~D 覆写 ~B）。
    sig:  声明级签名 = 参数表 + 方法 cv，如 '()' / '(int)' / '(char*,int)' / '() const'。
    kind: KIND_FUNC 或合成槽种类（见 SYNTHETIC_KINDS）。
    owner: 声明类（诊断/金样本键；不影响匹配）。
    """
    name: str
    sig: str
    kind: str = KIND_FUNC
    owner: str = ''

    @property
    def is_synthetic(self):
        return self.kind != KIND_FUNC


@dataclass(frozen=True)
class SlotEntry:
    """一个槽：声明 + **本类**对该槽的贡献（跨层传入的 origin 会被重置）。

    inherited = 本类未动的继承槽；override = 本类声明原位替换；new = 本类新增段尾插。
    """
    decl: VirtualDecl
    origin: str = ORIGIN_INHERITED


# ---------------- 匹配键（覆写判定） ----------------

def _split_sig(sig):
    """'(char*,int) const' → ('(char*,int)', 'const')。从最后一个 ')' 切，容忍函数指针参数。"""
    s = ' '.join(sig.strip().split())
    close = s.rfind(')')
    if s[:1] != '(' or close < 0:
        raise ValueError('sig 必须是 "(...)[ cv]" 形式：%r' % (sig,))
    return s[:close + 1], s[close + 1:].strip()


def _split_commas(text):
    """按顶层逗号切分（括号/尖括号内不切）。"""
    out, depth, cur = [], 0, []
    for ch in text:
        if ch in '(<[':
            depth += 1
        elif ch in ')>]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(''.join(cur)); cur = []
        else:
            cur.append(ch)
    out.append(''.join(cur))
    return out


def _canon_params(params):
    """参数表规范化：压空白、'char *'→'char*'、**去掉顶层** const/volatile。

    顶层参数 cv 不区分签名（C++：`o(const int)` 覆写 `o(int)`）；
    指针/引用参数的 const 在类型内部，**不动**（`o(const char*)` ≠ `o(char*)`）。
    """
    inner = params.strip()[1:-1].strip()
    if not inner:
        return '()'
    canon = []
    for p in _split_commas(inner):
        p = ' '.join(p.split())
        p = re.sub(r'\s+([*&])', r'\1', p)
        if '*' not in p and '&' not in p:
            p = re.sub(r'^((?:const|volatile)\s+)+', '', p)
            p = re.sub(r'\s+(?:const|volatile)$', '', p)
        canon.append(p)
    return '(' + ','.join(canon) + ')'


def match_key(decl):
    """覆写判定键。普通函数 = ('func', 名字, 参数, 方法 cv)；合成槽**名字不参与**。"""
    params, cv = _split_sig(decl.sig)
    params = _canon_params(params)
    if decl.is_synthetic:
        return (decl.kind, params, cv)
    return (KIND_FUNC, decl.name, params, cv)


# ---------------- 核心：本地段打包（规则 3 + 4 + 判别细节） ----------------

def _pack(decls):
    """本地段打包 → 声明下标序列。

    组 = 同名声明（合成槽各自为**单槽组**）；组位按**首现声明**排列；
    非合成组内按声明序**逆序**。含覆写的声明也参与打包（DA 判别样本），
    覆写者的摘除由调用方在打包后执行。
    """
    order = []            # 组键按首现排列
    members = {}          # 组键 → [声明下标...]（声明序）
    for i, d in enumerate(decls):
        key = ('syn', i) if d.is_synthetic else ('name', d.name)
        if key not in members:
            members[key] = []
            order.append(key)
        members[key].append(i)
    out = []
    for key in order:
        idxs = members[key]
        out.extend(reversed(idxs) if key[0] == 'name' else idxs)
    return out


def layout_local_segment(decls):
    """本地段槽序（VirtualDecl 列表）。见 _pack 的规则说明。"""
    return [decls[i] for i in _pack(decls)]


# ---------------- 单视图合成（规则 1 + 2） ----------------

def _as_entry(s):
    # 输入可以是 VirtualDecl 或下层算出的 SlotEntry；origin 描述**本类**的贡献，
    # 故跨层传递时统一重置为 inherited（本类未动的继承槽），避免下层的 new/override 泄漏。
    return SlotEntry(s.decl if isinstance(s, SlotEntry) else s, ORIGIN_INHERITED)


def _find_slot(slots, decl):
    k = match_key(decl)
    for i, s in enumerate(slots):
        if match_key(s.decl) == k:
            return i
    return None


def compute_slot_order(base_slots, local_decls):
    """单视图正向规则：继承原位（覆写替换）+ 本地段尾插。

    base_slots:  继承槽序列（VirtualDecl 或 SlotEntry）。
    local_decls: 本类声明（声明序）。
    返回 list[SlotEntry]。
    """
    slots = [_as_entry(s) for s in base_slots]
    matched = set()
    for i, d in enumerate(local_decls):
        j = _find_slot(slots, d)
        if j is not None:
            slots[j] = SlotEntry(d, ORIGIN_OVERRIDE)
            matched.add(i)
    for i in _pack(local_decls):          # 打包后摘除覆写者 ⇒ 摘除序 ≠ 重排序（DA）
        if i not in matched:
            slots.append(SlotEntry(local_decls[i], ORIGIN_NEW))
    return slots


# ---------------- MI 多视图（abi README #1/#3：vt2 / vt3） ----------------

def compute_class_views(hierarchy, cls, _stack=()):
    """按视图（基链）合成类的全部槽序。

    hierarchy: {类名: {'bases': [直接基类...], 'decls': [VirtualDecl...],
                       'virtual_bases': [...]（出现即拒绝）}}
    返回 [(视图标签, list[SlotEntry]), ...]——主视图（首基链）在前；
    视图标签 = 该视图链根类名（对应 ??_7D@@6B<根>@@@ 的 <根>，仅供诊断，不是符号身份）。

    MI 实测规则（vt2/vt3）：覆写在其出现的**每个**视图原位替换（一声明可占多视图多槽，
    次视图槽内容是 adjustor——属 Task 2/6，槽序不变）；本地新增段**只追加到主视图**。
    """
    spec = hierarchy[cls]
    if spec.get('virtual_bases'):
        raise NotImplementedError(
            '虚继承视图合成超出本任务范围（attack README B-1..B-4 缺口，归 Task 2/5/6）：%s' % cls)
    decls = [d if d.owner else replace(d, owner=cls) for d in spec.get('decls', [])]

    views = []
    for base in spec.get('bases', []):
        if base in _stack:
            raise ValueError('继承环：%s' % (' -> '.join(_stack + (cls, base)),))
        views.extend(compute_class_views(hierarchy, base, _stack + (cls,)))

    if not views:
        views = [(cls, [])]                     # 无基类 ⇒ 自身单视图

    for _label, slots in views:                 # origin 重置：只描述本类的贡献
        slots[:] = [_as_entry(s) for s in slots]

    matched = set()
    for i, d in enumerate(decls):
        for _label, slots in views:
            j = _find_slot(slots, d)
            if j is not None:
                slots[j] = SlotEntry(d, ORIGIN_OVERRIDE)
                matched.add(i)

    primary = views[0][1]                       # 新增段只进主视图（vt2：m 不入次表）
    for i in _pack(decls):
        if i not in matched:
            primary.append(SlotEntry(decls[i], ORIGIN_NEW))
    return views
