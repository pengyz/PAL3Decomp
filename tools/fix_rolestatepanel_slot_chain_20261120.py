#!/usr/bin/env python3
"""[P1 手术 2026-11-20] RoleStatePanel 槽链签名对齐家族契约 + 0x4a4820 降级占位。

本案推翻 6c9eab149 (RoleStatePanel C9 六条) 的两个前提:
  ① "sig return→int (decomp 渲染直证 virtual int)" —— 伪影非直证:
     - 0x4a5930 body `LOBYTE(result)=IsVisible(...)` = eax scratch 存储,
       hexrays 由 scratch eax 误推 int 原型 (12 族旁证类 body 全是干净 return;/无 return)
     - body 首行 `RoleStatePanel::Render(this)` 自递归 = 名字遮蔽伪影
       (0x4a4820 撞名 Render, CXX_GATE same_name:x2 当轮已报)
  ② "基类签名不一致冻结 5 条=原源码真实状态(MSVC6 容忍返回型不协变)" —— 证伪:
     MSVC6 虚覆盖返回型不一致 = C2555 硬错误(非协变指针不容忍),
     原源码不可能以 UIWnd::Render void + 派生 override int 编译通过。

裁决证据 (本轮三重 A 级):
  A. 表字节直证: original/PAL3.exe .rdata VA 0x56f040 =
     [0x445e70, 0x4a5930, 0x4a5b30, 0x4a6600, 0x445b90, 0x4a2150, 0x4a6120]
     —— slot1/2/3 override 契约=二进制事实 (VC6 vtable 布局即 override 契约)
  B. 12 族共识: CCBUIPanel/PalScript/UIButton/UIGameFrm/UIMap/UIProgressBar/
     UIPushButton/UITextArea/UISceneMap/UIListBox/UI3DCtrl/UIAnimateCtrlEX
     slot1 Render=void() / slot2 Update=BOOL(CCBUI**,int) / slot3 HideAll=void()
     —— RoleStatePanel 唯一离群 ⇒ 基锚 UIWnd 签名即家族契约
  C. 0x4a4820 全二进制零表出现(4字节对齐扫描)=非虚函数;
     其前判 "was MainEquipUI.Render_4a4820" 同伪 (MainEquipUI::Render override
     必坐其表槽, 而该址不在任何表) ⇒ 退赔(条目删除; N12 非语义名禁入现役律,
     知识留档挂账)

手术:
  1. methods 签名对齐家族契约: 0x4a5930 Render int→void /
     0x4a5b30 Update int→BOOL + params[]→[CCBUI **, int] /
     0x4a6600 HideAll int→void
  2. 0x4a4820 退赔(条目删除, 撞名消解; 首调直证 e8→0x4a4820 已留档)
  3. vtables slots 正名同步 (每槽一名律): RenderThrottled→Render /
     UpdateCaptions→Update / Destroy→HideAll; note "slot ownership unverified"
     → 表字节已验
  4. 类 note 追加本轮裁定史 (裁定字段与裁定史同步律)

用法: python3 tools/fix_rolestatepanel_slot_chain_20261120.py [--dry]
归档: data/annotations/archive/rolestatepanel_slot_chain_20261120.json
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv

FP = REPO / 'data/annotations/structs/RoleStatePanel.json'
d = json.loads(FP.read_text(encoding='utf-8'))
ms = d['methods']
archive = {'_doc': 'RoleStatePanel 槽链手术 2026-11-20 (C2555案)', 'ops': []}

FAMILY_SIG = json.loads(json.dumps(
    json.loads((REPO / 'data/annotations/structs/UIWnd.json')
               .read_text(encoding='utf-8'))['methods']['0x00445c60']['sig_model']))

# --- 1. 三槽方法签名对齐 ---
ALIGN = [
    ('0x004a5930', 'Render',  {'return': 'void',  'params': []}),
    ('0x004a5b30', 'Update',  {'return': 'BOOL',  'params': FAMILY_SIG['params']}),
    ('0x004a6600', 'HideAll', {'return': 'void',  'params': []}),
]
for addr, name, sig in ALIGN:
    m = ms.get(addr)
    assert m is not None and m.get('name') == name, (addr, m and m.get('name'))
    old = {'return': m['sig_model'].get('return'),
           'params': [p.get('type') for p in (m['sig_model'].get('params') or [])]}
    if '槽链契约定谳20261120' in (m.get('name_note') or ''):
        continue  # 幂等护栏: 已裁定过, 不重复落注记
    m['sig_model']['return'] = sig['return']
    m['sig_model']['params'] = json.loads(json.dumps(sig['params']))
    m['sig_model']['pending'] = False
    m['name_note'] = (m.get('name_note') or '') + (
        ' | 槽链契约定谳20261120: %s→%s (表字节0x56f040直证+12族共识'
        '+C2555硬错证伪容忍说+hexrays scratch-eax伪影双证)' % (old, sig['return']))
    archive['ops'].append('%s %s sig %s -> return=%s params=%s' % (
        addr, name, old, sig['return'],
        [p.get('type') for p in sig['params']]))

# --- 2. 0x4a4820 退赔(删条目) ---
# N12 铁律: 非语义名禁入现役(_todo_ 占位=新增硬错)。该址证据链本就断裂
# (改判自 MainEquipUI+零表出现), 退赔=唯一正当态; 知识留本归档。
m = ms.pop('0x004a4820', None)
assert m is not None and m.get('name') in ('Render', '_todo_4a4820'), m
archive['ops'].append('0x004a4820 %s -> 退赔(条目删除, 知识留档: '
                      '0x4a5930 首调直证 e8→0x4a4820; 非虚函数(全二进制零表出现); '
                      '前判 MainEquipUI.Render 同伪; body=if(flag)调0x540d20; '
                      '真语义待调用方普查定谳挂账)' % m.get('name'))

# --- 3. vtable slots 正名同步 ---
RENAME = {'RenderThrottled': 'Render', 'UpdateCaptions': 'Update',
          'Destroy': 'HideAll'}
for vt in d.get('vtables') or []:
    if vt.get('addr') != '0x0056f040':
        continue
    for s in vt.get('slots') or []:
        if s.get('name') in RENAME:
            archive['ops'].append('slot %s %s -> %s' % (
                s.get('addr'), s['name'], RENAME[s['name']]))
            s['name'] = RENAME[s['name']]
    vt['note'] = ('表字节已验20261120: original/PAL3.exe .rdata VA 0x56f040 七槽'
                  '逐字直读=[0x445e70,0x4a5930,0x4a5b30,0x4a6600,0x445b90,0x4a2150,'
                  '0x4a6120] 与本注解一致; slot0/4 坐 UIWnd 原址=继承槽直证; '
                  'installed by InitUI@0x4A1E40')

# --- 4. 类 note 裁定史 ---
if '槽链契约定谳20261120' not in (d.get('note') or ''):
    d['note'] = (d.get('note') or '') + (
    ' | 槽链契约定谳20261120: C9轮"基类不一致冻结=MSVC6容忍返回型不协变"前提'
    '被C2555硬错证伪, "decomp int直证"实为hexrays scratch-eax伪影'
    '(LOBYTE(result)=IsVisible)+撞名自递归伪影; 真签名=家族契约'
    '(Render void()/Update BOOL(CCBUI**,int)/HideAll void()), 三重A级: '
    '表字节+12族共识+C2555编译 verdict; 0x4a4820双Render退赔(条目删除)')
elif '降级_todo_占位' in d.get('note') or '':
    d['note'] = d['note'].replace(
        '0x4a4820双Render降级_todo_占位', '0x4a4820双Render退赔(条目删除, N12铁律)')

if not DRY:
    FP.write_text(json.dumps(d, ensure_ascii=False, indent=1), encoding='utf-8')
    outp = REPO / 'data/annotations/archive/rolestatepanel_slot_chain_20261120.json'
    outp.write_text(json.dumps(archive, ensure_ascii=False, indent=1), encoding='utf-8')
    print('归档 ->', outp.name)
for op in archive['ops']:
    print(' ', op)
print('done (dry=%s)' % DRY)
