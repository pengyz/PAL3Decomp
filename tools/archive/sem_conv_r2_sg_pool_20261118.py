#!/usr/bin/env python3
"""[R2-T2 2026-11-18] 语义收敛 R2 落地：ParticleEffect 池 + sg 系注解补建 +
RoleStatePanel UIStatic[5] + tagCombatTaskData 强证据正名 2 名。

== A. ParticleEffect 池落地 (三段收口, T1 已定谳) ==
  UpdateParticles(0x4bc7f0): v9=&this->econtrol[0].name[4]; v9+=36952; 循环界
  particle_num — stride 36952B = sg_emission_control sizeof (IDA 对账)。
  econtrol[0]@0x763C: 0x763C + 9*36952 = 0x58954 与 active_parnum 精确衔接
  (9 = 362860-0x763C 差整除验证)。头区 [0x0,0x763C) = TextureLib(532B) cast
  视图 + 解析区 (disp 0x100..0x424) + 28KB 深区零直接访问挂账。

== B. sg 系注解文件补建 (IDA 类型实名 + 语料互证) ==
  sg_emission_control(36952B/14名): Update(0x4b8890)/Emit(0x4ba800)/
    RenderToTexture/LoadTextures 真实访问 particle_array/curpos/curdir/
    elerandvel_*/emissionrate_* 等成员 — decomp/registry 证据名 (铁律第一优先级)。
  sg_particle_data(92B/14名) / sg_emitter_data(44B/9名): 同上互证。

== C. RoleStatePanel UIStatic[5] @0x210 ==
  InitUI(0x4a1e40)/~RoleStatePanel(0x4a2450) ctor/dtor 配对 disp 序列
  0x210/2a8/340/3d8/470 stride 152B; UIStatic sizeof=152 (IDA 对账);
  体语义: 5 角色状态静态框 (对齐 m_roles s_RoleState[5]@0x25E04 的 5 角色)。

== D. tagCombatTaskData 强证据正名 2 名 ==
  0x0C int m_nEffParam0 → float m_fEffDirX
  0x14 int m_nEffParam14 → float m_fEffDirZ
  证据: CreateOne sin(v6)*xa / cos(v6)*xa (特效初始方向分量);
        ~CCCTData *(float *)&g_CombatTaskData.m_nEffParam0 = v37 (float 双证)。
  其余 15 名证据弱 (级联拷贝/类型存疑) — 保持台账过渡态。

用法: python3 tools/sem_conv_r2_sg_pool_20261118.py
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
SDIR = REPO / 'data/annotations/structs'
ARCH = REPO / 'data/annotations/archive'

def ev(text):
    return {'evidence_level': 'A', 'source': text}

# ── A+B. sg 系注解文件 ──
ida = json.load(open(REPO / 'asm/pal3/ida_structs.json'))
SG_CORPUS = {
    'sg_emission_control': (
        'sg_emission_control::Update VA=0x4b8890 (tval/curdir/elerandvel_max/min/'
        'emissionrate_max/elelifetime_max/min x30) / sg_emission_control::Emit '
        'VA=0x4ba800 (particle_array[a2].curpos x8) / RenderTarget::RenderToTexture '
        '(pemitter x27/particle_array x9/emitter_pointer) / ParticleEffect::'
        'LoadTextures (emitter x24/elapsetime) — decomp/registry 证据名'),
    'sg_particle_data': (
        'sg_emission_control::Emit VA=0x4ba800: particle_array[a2].curpos.y '
        '浮点累加 x8 — 元素 92B/14 实名, IDA 类型+语料互证'),
    'sg_emitter_data': (
        'sg_emission_control::Update VA=0x4b8890: curdir/elerandvel_max/min '
        '真实读写 — 元素 44B/9 实名, IDA 类型+语料互证'),
}
created = []
for name, corpus_ev in SG_CORPUS.items():
    s = ida.get(name) or {}
    mems = s.get('data_members') or []
    size = s.get('size')
    assert size, name
    km = {}
    for m in mems:
        off_hex = '0x%x' % m['offset']
        km[off_hex] = {
            'name': m['name'], 'type': m['type'],
            'evidence_level': 'A',
            'source': '[IDA 类型实名+语料互证 2026-11-18] %s' % corpus_ev,
        }
    # [复核P0-1改] 合并式: 保留既有 methods/其他键, 只更新 known_members/evidence
    doc = {}
    fp0 = SDIR / ('%s.json' % name)
    if fp0.exists():
        doc = json.loads(fp0.read_text(encoding='utf-8'))
    doc['name'] = name
    doc['binary_size'] = size
    doc['known_members'] = km
    doc['members_note'] = '[R2 2026-11-18] IDA 侧已实名结构补建注解文件 (语料互证: %s)' % corpus_ev[:60]
    fp = SDIR / ('%s.json' % name)
    fp.write_text(json.dumps(doc, indent=1, ensure_ascii=False), encoding='utf-8')
    created.append('%s(%dB/%d名)' % (name, size, len(km)))
print('[R2-B] sg 系注解补建:', ', '.join(created))

# ── A. ParticleEffect 池落地 [已撤销·复核P0] econtrol[9]@0x763C 为余数凑数
#    误落 (实落基类 sg_particle_scene.econtrol[4] 区内), C10 拦截后撤销;
#    布局叙事见 ParticleEffect.json members_note。此段已移除防止重跑复活。
# ── C. RoleStatePanel UIStatic[5] ──
rp_p = SDIR / 'RoleStatePanel.json'
rp = json.loads(rp_p.read_text(encoding='utf-8'))
rkm = rp.setdefault('known_members', {})
rkm['0x210'] = {'name': 'm_RoleStatics', 'type': 'UIStatic[5]', **ev(
    '[A 级汇编 2026-11-19] InitUI VA=0x4a1e40 / ~RoleStatePanel VA=0x4a2450 '
    'ctor/dtor 配对 disp 序列 0x210/2a8/340/3d8/470 stride 152B; UIStatic '
    'sizeof=152 (IDA 对账, UIWnd 派生); 体语义: 5 角色状态静态框 (对齐 '
    'm_roles s_RoleState[5]@0x25E04 的 5 角色分组)')}
rp['members_note'] = (rp.get('members_note') or '') + (
    '\n[R2 2026-11-19] 骨架: m_RoleStatics UIStatic[5] [0x210,0x4F8)。'
    '未定谳挂账: 0x508 起 stride-344 序列(UIButton 尺寸候选, N 未定)/'
    'RenderThrottled 深区 disp 0x12F8/0x136F8/0x25B80/池区主体。')
rp_p.write_text(json.dumps(rp, indent=1, ensure_ascii=False), encoding='utf-8')
print('[R2-C] RoleStatePanel: m_RoleStatics UIStatic[5] @0x210 落地')

# ── D. tagCombatTaskData 强证据正名 2 名 ──
ct_p = SDIR / 'tagCombatTaskData.json'
ct = json.loads(ct_p.read_text(encoding='utf-8'))
ckm = ct['known_members']
RENAME = {
    '0xc': ('m_nEffParam0', 'm_fEffDirX', 'float'),
    '0x14': ('m_nEffParam14', 'm_fEffDirZ', 'float'),
}
for off, (old, new, newtype) in RENAME.items():
    m = ckm[off]
    assert m.get('name') == old, (off, m.get('name'))
    m['name'] = new
    m['type'] = newtype
    m['source'] = (m.get('source') or '') + (
        ' | [R2 正名 2026-11-18] CreateOne: g_17A8Data.%s = sin(v6)*xa / cos(v6)*xa '
        '(特效初始方向分量, VA 语料 0x4d8xxx 簇); ~CCCTData: *(float *)&g_CombatTaskData.'
        '%s = v37 float 双证; 类型 int→float (浮点指针写实证)。' % (new, off))
ct_p.write_text(json.dumps(ct, indent=1, ensure_ascii=False), encoding='utf-8')
print('[R2-D] tagCombatTaskData: 0xC→m_fEffDirX / 0x14→m_fEffDirZ (float 双证)')

# 台账消账
led_p = ARCH / 'pseudo_semantic_names_20261118.json'
led = json.loads(led_p.read_text(encoding='utf-8'))
lst = led['names'].get('tagCombatTaskData', [])
led['names']['tagCombatTaskData'] = [e for e in lst if e['name'] not in ('m_nEffParam0', 'm_nEffParam14')]
led.setdefault('progress', {})['R2'] = 'tagCombatTaskData 2 名正名(m_fEffDirX/Z); ScriptSystemData 31/34 零语料引用→保持台账'
led_p.write_text(json.dumps(led, indent=1, ensure_ascii=False), encoding='utf-8')
print('[R2-D] 台账消账: tagCombatTaskData 剩 %d 名' % len(led['names']['tagCombatTaskData']))
print('[done]')
