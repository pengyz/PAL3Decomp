"""[D10 dtor 发射意图单点 2026-11-21] resolve_dtor_intent —— dtor 治理公共函数。

方案: docs/knowledge/plan_dtor_intent_reform_20261121.md（对抗复核定稿）
方法论: docs/knowledge/methodology_dtor_governance_20261121.md

模型（合成模型定谳）:
  ??_G 载体 = virtual ~Cls() 头声明（flags 通道） + TU 内 dtor 定义 → MSVC 合成 ??1/??_G
  唯一源律: 每类恰好一个 dtor 定义发射（完全形优先；无完全形时删除式经 N18 源级化承担）
  名律: 源码析构名=本类名(~Cls)——跨类槽链名(~Base)在发射域规范化（S0① 律）

分层纪律: 本模块=纯决策逻辑（零文件直读、零 IDA 依赖）；数据事实由调用方注入
（annotation_view 单一读点 / ida_structs flags 通道 / header_facts / decomp 目录在场）。
"""
import json
import re
from dataclasses import dataclass, field


@dataclass(frozen=True)
class DtorIntent:
    """单条 dtor 条目的发射意图（不可变，可审计）。"""
    role: str              # 'complete_def' | 'deleting_source' | 'declaration_only' |
                           # 'suppressed' | 'orphan'（无注解身份/拒发）
    body_emit: bool        # TU 内发射定义体
    decl_emit: bool        # 头发声明
    decl_virtual: bool     # 声明带 virtual
    decl_inline: bool      # 注入形 `virtual ~Cls() {}`（vs 槽循环 `;` 形）
    name: str              # 规范名 '~Cls'（跨类名在此规范化）
    definition_owner: str  # 拥有 TU 定义的条目地址（唯一源律仲裁结果；''=本条非owner）
    n18_strip: bool        # stage1 4c 织入物剥离（flags 形参/删尾/return this）
    reason: str            # 可审计判定理由
    data_suspect: str = field(default='' )


def _is_dtor_flags(entry):
    fl = entry.get('flags') or []
    return 'dtor' in fl


def _is_deleting(entry):
    return 'deleting' in (entry.get('flags') or [])


def _canon_name(cls, entry, flags_channel):
    """源码唯一析构律: 发射门名恒为 '~Cls'。跨类槽链名(~Base)规范化并留痕。"""
    nm = str(entry.get('name') or '')
    want = '~%s' % cls
    if nm == want:
        return want, ''
    if nm.startswith('~') and nm != want:
        # 跨类槽链名(~GameObject)/后缀变体(~Cls_adjthunk)——发射域一律 ~Cls
        return want, '跨类/变体名 %s 规范化为 %s(S0①源码唯一析构律)' % (nm, want)
    if nm and not nm.startswith('~'):
        # 非析构形名(_nearby_41cbc0/_scalar_dtor/adjthunk): 注解 flags 为 dtor 时本条
        # 身份=dtor → 名规范化; 否则疑似误标(交 data_suspect)
        if 'dtor' in (flags_channel or []) or _is_dtor_flags(entry):
            return want, '非析构形名 %s 规范化为 %s(flags dtor 通道)' % (nm, want)
        return want, 'data_suspect: 名 %s 非 ~ 形且 flags 无 dtor——疑 sig-vs-flags 失配' % nm
    return want, ''


def resolve_dtor_intent(*, cls, entry_addr, entry, siblings, unit_present,
                        unit_vintage, flags_channel, header_facts_scalar,
                        s4_symbols=None, vtable_slot_addrs=()):
    """单条 dtor 条目 → 发射意图。

    参数(全部注入, 本函数零文件读):
      cls: TU 类名
      entry_addr/entry: 本条地址与注解条目 dict
      siblings: 同类其他 dtor 条目 [{addr, entry, unit_present}]（不含本条）
      unit_present: 本条 decomp 单元在场
      unit_vintage: 'backtick'|'named'|'mangled'|'sub'|'none'
      flags_channel: ida_structs 侧 flags（TU 类条目; 通道缺失=None）
      header_facts_scalar: 类 ∈ header_facts.scalar_dtor_classes
      s4_symbols: {symbol: row} 冻结 S4 基线行（VA 级仲裁; 可 None）
      vtable_slot_addrs: 类的 vtables 槽地址集合（virtual 的唯一真证据——
        flags 不可用作 virtual 证据: 非虚 dtor 同样有 dtor flags，误标全类虚
        =vtable 布局灾难）
    """
    name, name_note = _canon_name(cls, entry, flags_channel)

    fl = entry.get('flags') or []
    deleting = 'deleting' in fl or 'deleting' in (flags_channel or [])
    is_dtor = _is_dtor_flags(entry) or 'dtor' in (flags_channel or [])
    suppressed = entry.get('type') == 'skip'
    decl_only = bool(entry.get('declaration_only'))

    # sig-vs-deleting 交叉核（T14/ParticleEffect 0x4bc790 形 + TextureLib 0x53f4d0 镜像）
    data_suspect = ''
    sm = entry.get('sig_model') or {}
    if sm and not sm.get('pending'):
        ps = sm.get('params') or []
        _nonthis_p = [p for p in ps
                      if 'this' not in json.dumps(p, ensure_ascii=False)]
        if deleting and not ps:
            data_suspect = 'sig-vs-deleting: flags=deleting 但 sig 0参(完全形 ABI 形)——形态矛盾待定谳'
        elif (not deleting) and _nonthis_p:
            # 镜像(TextureLib 0x53f4d0 案): flags 无 deleting 但 sig 带非 this 参
            # (删除式 ABI 形)——身份未定谳, 保守不发射(S2 定谳后解禁)
            data_suspect = ('sig-vs-non-deleting: flags 无 deleting 但 sig 带非 this 参'
                            '(删除式 ABI 形)——身份未定谳, 保守不发射')

    # ── 兄弟全集(含本条)与唯一源仲裁 ─────────────────────────────
    all_forms = [{'addr': entry_addr, 'entry': entry, 'unit_present': unit_present}] + list(siblings)

    def _sup(r):
        e = r['entry']
        return e.get('type') == 'skip' or bool(e.get('declaration_only'))

    def _del(r):
        return 'deleting' in (r['entry'].get('flags') or [])

    comp_emittable = [r for r in all_forms
                      if not _del(r) and not _sup(r) and r['unit_present']]
    if not comp_emittable:
        # 无可发射完全形 → 未压制的删除式承担定义源（N18 通路）
        del_emittable = [r for r in all_forms
                         if _del(r) and not _sup(r) and r['unit_present']]
    else:
        del_emittable = []
    owner = min((r['addr'] for r in (comp_emittable or del_emittable)),
                key=lambda a: int(a, 16)) if (comp_emittable or del_emittable) else ''

    # ── 角色判定 ─────────────────────────────────────────────────
    # [virtual 证据律 20261121] virtual 的唯一真证据=本址 ∈ vtable 槽地址
    #   （与 emit_headers 槽循环所有权同源语义）。flags 只证 dtor 身份不证虚性。
    _slot_set = {('0x%08X' % int(a, 16)) if isinstance(a, str) else '0x%08X' % a
                 for a in (vtable_slot_addrs or ())}
    decl_virtual = is_dtor and (
        ('0x%08X' % int(entry_addr, 16)) in _slot_set)

    if suppressed:
        role = 'suppressed'
        body_emit = False
        decl_emit = False          # type='skip' = 头抑制（N20a 守护 L1 载体）
        n18_strip = False
        reason = 'type=skip: 非函数目标/出语义域'
    elif decl_only:
        role = 'declaration_only'
        body_emit = False
        decl_emit = True           # decl_only=「真函数, 要声明」契约
        n18_strip = False
        reason = 'declaration_only: 体不发射, 声明照发'
    else:
        if owner and owner != entry_addr:
            role = 'declaration_only' if decl_only else 'declaration_only'
            body_emit = False
            decl_emit = True
            n18_strip = False
            reason = '唯一源律仲裁: 定义源=%s(本条=伴生形, 体抑制防C2084)' % owner
        elif not unit_present:
            role = 'declaration_only'
            body_emit = False
            decl_emit = True
            n18_strip = False
            reason = '单元不在场(decomp 无本条单元) → 无体可发, 声明照发'
        elif deleting:
            role = 'deleting_source'
            body_emit = True
            decl_emit = True
            n18_strip = True
            reason = '删除式=唯一形态(deleted-form ABI) → N18 源级化承担定义源'
        else:
            if data_suspect.startswith('sig-vs-non-deleting'):
                # [保守 20261121] 身份未定谳(flags/sig 矛盾) → 体不发射,
                # 声明照发——发射未定谳体=以错身份编译(TextureLib C2511 实证)
                role = 'declaration_only'
                body_emit = False
                decl_emit = True
                n18_strip = False
                reason = 'sig-vs-flags 矛盾未定谳 → 保守不发射(S2 定谳后解禁)'
            else:
                role = 'complete_def'
                body_emit = True
                decl_emit = True
                n18_strip = False
                reason = '完全形=定义源(4d 隐式析构剥离)'

    if name_note:
        reason = reason + '; ' + name_note
        if name_note.startswith('data_suspect:'):
            data_suspect = data_suspect or name_note[len('data_suspect:'):].strip()

    return DtorIntent(
        role=role, body_emit=body_emit, decl_emit=decl_emit,
        decl_virtual=decl_virtual, decl_inline=bool(header_facts_scalar),
        name=name, definition_owner=owner, n18_strip=n18_strip,
        reason=reason, data_suspect=data_suspect)
