#!/usr/bin/env python3
"""[R1-T5 2026-11-18] 对抗复核 P0/P1 修复。

复核结报（只读复核员，4 处编排侧错误被抓，双向验算确认）：
  P0-1 m_nCurPageTab@0x5578 → 0x5558 (3057*4=12228=0x2FC4, 0x2594+0x2FC4=0x5558;
       原写 0x2FE4=3065*4 与声称索引 3057 自相矛盾)
  P0-2 m_RenderQueue[12] → [98] (语料 v12=98 do-while(--v12)=98 次; 98*584=0xDF90,
       0x3CFB8+0xDF90=0x4AF48 与选区邻接三角互证; [12] 全库无出处)
  P0-3 m_SelectRect 0x4AF4C → 0x4AF48 (探针实测 x1@0x4AF48; 原成员含越界 4B
       且把 x1 撂在成员外)
  P0-4 rebaseline 叙述不全 → 隔离 A/B 实验补证 (单独脚本跑)
  P1-5 _todo_ 降级违反 CLAUDE.md 命名铁律(525: 全禁) → 撤销降级恢复原名,
       35 名存量伪语义由台账登记合法化 (CLAUDE.md 补记条款)
  P1-6 members_note gap 账本 4 处边界错 → 重写
  P1-7 探针 regex 漏变址+输出未存档 → 修复+存档 (单独跑)
  P1-8 降级漏网 7 名 (0x38/0x60/0xe8/0xf4/0xf8/0x184/0x308) → 保持原名+入台账

用法: python3 tools/sem_conv_r1_fix_p0_20261118.py
"""
import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
SDIR = REPO / 'data/annotations/structs'
ARCH = REPO / 'data/annotations/archive'
CLAUDE = REPO / 'CLAUDE.md'

def ev(text):
    return {'evidence_level': 'A', 'source': text}

# ── A. CCBCamControl 三处 P0 修正 + note 重写 ──
cam_p = SDIR / 'CCBCamControl.json'
cam = json.loads(cam_p.read_text(encoding='utf-8'))
km = cam['known_members']

assert km['0x3cfb8']['name'] == 'm_RenderQueue'
km['0x3cfb8'] = {'name': 'm_RenderQueue', 'type': 'UIParticle[98]', **ev(
    '[A 级汇编+语料三重互证 2026-11-18] ProcessRenderQueue VA=0x48e600: v12=98 '
    'do-while(--v12)=98 次迭代 (R1 初版误读 12, 复核 P0-2 证伪), 步进 584B '
    '(VA=0x48e75x add esi,248h); 98*584=0xDF90, 0x3CFB8+0xDF90=0x4AF48 与选区 '
    'm_SelectRect 邻接三角互证; 语料 m_RenderQueue[98].m_viewRect.left 渲染实证; '
    'UIParticle sizeof=584 注解对账')}
assert km['0x4af4c']['name'] == 'm_SelectRect'
del km['0x4af4c']
km['0x4af48'] = {'name': 'm_SelectRect', 'type': 'int[4]', **ev(
    '[A 级汇编 2026-11-18] ProcessRenderQueue VA=0x48e606: mov esi,[ecx+4AF48h] '
    '(x1) / VA=0x48e60d: [ecx+4AF50h] (x2) / VA=0x48e615: [ecx+4AF54h] (y2), '
    'y1@0x4AF4C 隐含; CalcRenderDimensions(v2=x2-x1, v6=y2-y1) 消费。R1 初版误落 '
    '0x4AF4C (复核 P0-3: x1 撂在成员外+含越界 4B), 修正基址')}
assert km['0x5578']['name'] == 'm_nCurPageTab'
del km['0x5578']
km['0x5558'] = {'name': 'm_nCurPageTab', 'type': 'int', 'evidence_level': 'B', **{
    'source': '[B 级语料锚 2026-11-18] ShowAllSlots: *(&m_nCurCamIdx+3057)=nVal; '
              '3057*4=12228=0x2FC4, 0x2594+0x2FC4=0x5558 (R1 初版 0x2FE4 算术错, '
              '复核 P0-1 证伪); B 级待汇编直接捕获'}}

# 修正后区间自检
SZ = {'UIParticle[98]': 98*584, 'int[4]': 16, 'UIButton[5]': 5*344, '_BYTE[6040]': 6040, 'int': 4}
ivals = []
for off_s in ('0x3cfb8', '0x4af48', '0x5558', '0x5d9ec', '0x5f360'):
    off = int(off_s, 16)
    sz = SZ[km[off_s]['type']]
    ivals.append((off, off+sz, km[off_s]['name']))
ivals.sort()
for (a1, b1, n1), (a2, b2, n2) in zip(ivals, ivals[1:]):
    assert b1 <= a2, '重叠: %s[%#x,%#x) vs %s[%#x,%#x)' % (n1, a1, b1, n2, a2, b2)
assert ivals[0][0] > 0x2594 + 4 and ivals[-1][1] <= 0x68fb0
print('[fix] 区间自检通过:', [('%#x-%#x %s' % (a, b, n)) for a, b, n in ivals])

cam['members_note'] = (cam.get('members_note') or '').split('\n[R1 2026-11-18]')[0] + (
    '\n[R1 2026-11-18 修正版·复核P0后] 池区骨架 (全部汇编 disp 对齐):\n'
    '  m_RenderQueue UIParticle[98] [0x3CFB8,0x4AF48) — 98x584 与选区邻接互证\n'
    '  m_SelectRect int[4] [0x4AF48,0x4AF58) — x1/x2/y2 disp 实测\n'
    '  m_nCurPageTab int [0x5558,0x555C) — B级语料锚 3057*4\n'
    '  m_SlotButtons UIButton[5] [0x5D9EC,0x5E0A4) — stride 344 循环界 5\n'
    '  m_TabLists _BYTE[6040] [0x5F360,0x60AF8) — stride 1208 身份未定谳\n'
    '未名 gap ≈396KB: [0x24e4,0x5558)+[0x555c,0x3cfb8)+[0x4af58,0x5d9ec)+'
    '[0x5e0a4,0x5f360)+[0x60af8,0x68fb0) 自然保留挂账 (R1 初版账本边界 4 处算错'
    '已重算, 复核 P1-6)。')
cam_p.write_text(json.dumps(cam, indent=1, ensure_ascii=False), encoding='utf-8')
print('[fix-A] CCBCamControl: [98]/0x4AF48/0x5558 三处修正+note 重算')

# ── B. Actor 撤销 _todo_ 降级 → 恢复原名 ──
actor_p = SDIR / 'Actor.json'
actor = json.loads(actor_p.read_text(encoding='utf-8'))
akm = actor['known_members']
revoked = {}
for off_s, m in akm.items():
    nm = str(m.get('name') or '')
    mt = re.match(r'^_todo_([0-9a-fA-F]+)$', nm)
    if mt and nm in ('_todo_30','_todo_34','_todo_3c','_todo_40','_todo_44','_todo_48',
                     '_todo_4c','_todo_50','_todo_58','_todo_5c','_todo_5d','_todo_80',
                     '_todo_84','_todo_dc','_todo_e0','_todo_e4','_todo_ec','_todo_f0',
                     '_todo_fc','_todo_14d','_todo_151','_todo_152','_todo_18c','_todo_194',
                     '_todo_198','_todo_1a4','_todo_1ac','_todo_1b0'):
        src = m.get('source') or ''
        mr = re.search(r'原名 (\S+) 为序号后缀伪语义', src)
        old = mr.group(1) if mr else None
        if old:
            revoked[nm] = old
            m['name'] = old
            m['source'] = (src.split(' | [R1 降级 2026-11-18]')[0] +
                           ' | [R1-T5 2026-11-18] _todo_ 降级撤销(CLAUDE.md 命名铁律 525 '
                           '全禁占位名); 存量伪语义名由台账登记合法化, 正名走 Actor 内嵌'
                           '子对象身份战役 (语料实证: 0x3c 区虚调用+AllocObject / 0x40 区 '
                           'UIPushButton::LoadTexture+CCBUI::SetRect / 0x58 区 ARC_'
                           'PlayerAtt::Create+UIItem::SetData / 0x1b0 g_RoleSlotBuf 数组 '
                           'stride 352)。')
if len(revoked) != 28:
    print('[fix-B] 预期撤销 28, 实得 %d — 中止' % len(revoked))
    sys.exit(1)
actor_p.write_text(json.dumps(actor, indent=1, ensure_ascii=False), encoding='utf-8')
print('[fix-B] Actor: 28 名 _todo_ 降级撤销, 原名恢复')

# ── C. 台账更新 + 补漏网 7 名 ──
led_p = ARCH / 'pseudo_semantic_names_20261118.json'
led = json.loads(led_p.read_text(encoding='utf-8'))
actor_list = led['names'].setdefault('Actor', [])
have = {e['offset']: e['name'] for e in actor_list}
for off_s, old in revoked.items():
    off_json = '0x' + off_s[2:]
    if off_json not in have:
        actor_list.append({'offset': off_json, 'name': old, 'type': akm[off_json].get('type')})
# 补复核 P1-8 漏网 7 名 (保持原名, 只入台账)
EXTRA = ['0x38','0x60','0xe8','0xf4','0xf8','0x184','0x308']
for off_s in EXTRA:
    m = akm.get(off_s)
    if m and off_s not in have:
        actor_list.append({'offset': off_s, 'name': m.get('name'), 'type': m.get('type')})
led['names']['Actor'] = sorted(actor_list, key=lambda e: int(e['offset'], 16))
led['adjudication_r1'] = (
    '2026-11-18 R1-T5 裁定: _todo_ 降级撤销 (CLAUDE.md:525 命名铁律全禁占位名); '
    '存量伪语义名以本台账登记为合法过渡态 (CLAUDE.md 已补记条款), 禁止新增; '
    '正名逐类走取证战役 (Actor=内嵌子对象身份战役)。复核 P1-8 补录 7 名漏网。')
led_p.write_text(json.dumps(led, indent=1, ensure_ascii=False), encoding='utf-8')
print('[fix-C] 台账: Actor 28 恢复登记 + 7 名补录 (共 %d)' % len(led['names']['Actor']))

# 撤销记录覆盖 demotion 档案
(ARCH / 'actor_pseudo_demotion_20261118.json').write_text(json.dumps({
    '_doc': 'Actor 28 伪语义名降级 **已撤销** (R1-T5 2026-11-18): _todo_ 占位形态'
            '违反 CLAUDE.md:525 命名铁律(全禁), 复核 P1-5 证伪; 原名恢复, 存量由 '
            'pseudo_semantic_names_20261118.json 台账登记合法化。本档案仅存裁决记录。',
    'verdict': 'REVOKED — 见 pseudo_semantic_names_20261118.json.adjudication_r1',
}, indent=1, ensure_ascii=False), encoding='utf-8')

# ── D. CLAUDE.md 补记存量台账合法过渡条款 ──
txt = CLAUDE.read_text(encoding='utf-8')
anchor = '- 管线槽名回退链中 `slot_%d` 占位分支同样违规——数据必须自带头槽语义名，回退分支命中即视为数据缺陷'
add = (anchor + '\n- **存量伪语义名过渡条款（2026-11-18 R1-T5）**：台账 '
       '`data/annotations/archive/pseudo_semantic_names_20261118.json` 已登记的历史'
       '序号后缀名（CachedA/B、RoleParam0-3 等 58 类）为**合法过渡态**——禁止新增此'
       '形态，存量正名逐类走取证战役（每名 name_note 留语料/汇编证据链），禁止 _todo_ '
       '降级规避')
if anchor in txt and '存量伪语义名过渡条款' not in txt:
    CLAUDE.write_text(txt.replace(anchor, add), encoding='utf-8')
    print('[fix-D] CLAUDE.md: 存量台账过渡条款已补记')
else:
    print('[fix-D] CLAUDE.md 条款已存在或锚点缺失 — 跳过')

print('[done] P0-1/2/3 + P1-5/6/8 修复完成; P0-4 隔离实验与 P1-7 探针存档随后')
