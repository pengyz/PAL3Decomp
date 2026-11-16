#!/usr/bin/env python3
"""[C9血统批量1 2026-11-16] CCBPanelSlot/CCBResultWindow 纯增量修复(无破坏性迁移)。

证据链(全部二进制+体级):
- 四表骨架对齐(0x56ae10/0x56ae2c/0x56ae84/0x56acb8): slot0=445e70(ShowClipped ICF折叠),
  slot4=445b90(Create继承), slot6=445d10(OnMessage继承) → 全UIWnd系
- CCBPanelSlot bases=None=标注缺口 → [UIWnd offset 0](最小主张, UIFrameWnd需ctor证据)
- CCBPanelSlot表3槽=截断, 二进制7槽 → 补slot3/4/5/6
- 0x442420: slot3位 + RET 0(0参ABI) + 体=Release纹理引用(面板隐藏即释放) → 链律名HideAll
- 0x444ad0: slot1位(Render) → RenderAll违每槽一名 → Render
- 0x444d30: slot2位(Update BOOL(int,int), 与0x442ff0同契约) → ProcessInput违链律 → Update
- 0x444ac0: 写0x56ae84(=CCBResultWindow表) → complete dtor归真 ~CCBResultWindow
  (UIFrameWnd.json冒领名~UIFrameWnd_Full待用户确认后移除, 挂账dossier)
- 0x4431b0: 0x56ae2c slot5值 → CCBPanelSlot deleting dtor(UIWnd.json冒领_sdtor_call_dtor待移除)
返回型漂移(void vs int)不在此修——L-TAILADDR队列, C9如实记账。
"""
import json

def load(fp):
    return json.load(open(fp, encoding='utf-8'))

def save(fp, d):
    json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

# ── CCBPanelSlot ──
fp = 'data/annotations/structs/CCBPanelSlot.json'
d = load(fp)
d['bases'] = [{'name': 'UIWnd', 'offset': 0}]
vt = d['vtables'][0]
slots = vt['slots']
assert len(slots) == 3, '前置漂移: %d槽' % len(slots)
slots += [
    {'addr': '0x00442420'},  # slot3 HideAll位(override, RET 0)
    {'addr': '0x00445B90'},  # slot4 Create继承(UIWnd slot4同值)
    {'addr': '0x004431B0'},  # slot5 删除式dtor位(声明序分配)
    {'addr': '0x00445D10'},  # slot6 OnMessage继承(UIWnd slot6同值)
]
vt['slots'] = slots
vt['note'] = ('7槽骨架20261116定谳: slot0/4/6与UIWnd同值(继承), slot1/2/3/5覆写; '
              'slot5=删除式dtor位(本二进制虚dtor按声明序分配非slot0)')
ms = d.setdefault('methods', {})
assert '0x00442420' not in ms and '0x004431b0' not in ms
ms['0x00442420'] = {
    'name': 'HideAll', 'ordinal': 4, 'evidence_level': 'verified',
    'semantic_name': 'CCBPanelSlot::HideAll(void)',
    'sig_model': {'return': 'void', 'cc': 'thiscall', 'params': [], 'varargs': False, 'pending': False},
    'signature': 'void __thiscall()',
    'name_note': ('C9血统修复20261116: slot3位(UIWnd骨架) + RET 0(0参ABI=census) + '
                  '体=Release纹理引用(m_pFace[1]/[5]置空, 面板隐藏即释放) → 链律名HideAll; '
                  '原名Destroy_2420=体读数命名(N12地址后缀); 返回型void vs 根int漂移→L-TAILADDR队列')
}
ms['0x004431b0'] = {
    'name': '~CCBPanelSlot', 'ordinal': 5, 'evidence_level': 'verified',
    'semantic_name': 'CCBPanelSlot::~CCBPanelSlot(del)',
    'sig_model': {'return': 'void *', 'cc': 'thiscall',
                  'params': [{'type': 'int', 'name': 'flags'}], 'varargs': False, 'pending': False},
    'signature': 'void * __thiscall(int)',
    'name_note': ('slot5删除式dtor位定谳20261116(??_G型, ABI RET 4=1参flags, 体=调complete dtor'
                  '+条件operator delete); 名取类dtor语义形(_scalar_dtor_XXXX为N12禁形不入新条目); '
                  'UIWnd.json冒领条目_sdtor_call_dtor待用户确认后移除')
}
save(fp, d)
print('CCBPanelSlot: bases=[UIWnd] 3→7槽 +0x442420(HideAll) +0x4431b0(~CCBPanelSlot)')

# ── CCBResultWindow ──
fp = 'data/annotations/structs/CCBResultWindow.json'
d = load(fp)
vt = d['vtables'][0]
slots = vt['slots']
assert len(slots) == 6 and slots[5]['addr'] == '0x00444AA0'
slots.append({'addr': '0x00445D10'})  # slot6 OnMessage继承
vt['slots'] = slots
ms = d.setdefault('methods', {})

e = ms['0x00444ad0']
assert e['name'] == 'RenderAll'
e['name'] = 'Render'
e['semantic_name'] = 'CCBResultWindow::Render(void)'
e['evidence_level'] = 'verified'
e['name_note'] = ('C9血统修复20261116: slot1位(Render, UIWnd骨架slot1=0x445cd0) → 链律名Render; '
                  '原名RenderAll=体读数; 返回型int vs 根void漂移→L-TAILADDR队列')

e = ms['0x00444d30']
assert e['name'] == 'ProcessInput'
e['name'] = 'Update'
e['semantic_name'] = 'CCBResultWindow::Update(int, int)'
e['evidence_level'] = 'verified'
e['name_note'] = ('C9血统修复20261116: slot2位(Update BOOL(int,int)契约, 同0x442ff0折叠载体契约) '
                  '→ 链律名Update; 原名ProcessInput=体读数')

e = ms['0x00442420']
assert e['name'] == 'Destroy_2420'
e['name'] = 'HideAll'
e['semantic_name'] = 'CCBResultWindow::HideAll(void)'
e['evidence_level'] = 'verified'
e['name_note'] = ('C9血统修复20261116: slot3位 + RET 0(0参ABI) + 体=Release纹理引用 '
                  '(与CCBPanelSlot/未知类0x56ae10三处同址=ICF折叠载体) → 链律名HideAll; '
                  '原名Destroy_2420=N12地址后缀形; 返回型void vs 根int漂移→L-TAILADDR队列')

assert '0x00444ac0' not in ms
ms['0x00444ac0'] = {
    'name': '~CCBResultWindow', 'ordinal': 35, 'evidence_level': 'verified',
    'semantic_name': 'CCBResultWindow::~CCBResultWindow(complete)',
    'sig_model': {'return': 'void', 'cc': 'thiscall', 'params': [], 'varargs': False, 'pending': False},
    'signature': 'void __thiscall()',
    'name_note': ('归真20261116: 写0x56AE84(=本类表, 机器码[esi]=imm实证) → 本类complete dtor; '
                  'UIFrameWnd.json冒领名~UIFrameWnd_Full待用户确认后移除(挂账dossier)')
}
save(fp, d)
print('CCBResultWindow: 6→7槽 +Render/Update/HideAll正名 +0x444ac0(~CCBResultWindow)')
