#!/usr/bin/env python3
"""[C9试点修复 2026-11-16] CCBControlWindow slot2/slot3 名字+签名链律对齐。

证据链(全部二进制/体级, 无一处臆测):
- 表序: original/PAL3.exe .rdata 0x57051C 指针序与标注逐一吻合(8槽)
- slot2=0x51b0b0: RET 8(2参) + 体尾直调 UIWnd::Update(this,nVal,nVal2)
  + 根契约 slot2=Update(int,int)=BOOL(UIWnd::Update体0x445c60向子物件slot2推2参)
  → 现名MoveButtons违每槽一名override律 → 正名 Update
- slot3=0x51afe0: RET 0(**0参ABI真相**) + 体不读a2/a3(Hex-Rays伪影) + 体形态
  (ReleaseTempStorage+释放子控件)与HideAll族同构
  + 根契约 slot3=HideAll() 0参(UIWnd::HideAll体0x445c10向子物件slot3推0参;
    __thiscall被调方清栈, 参个数跨槽不一致=栈腐蚀, 原版不可能)
  → 现名Update(float,int)名+参双伪 → 正名 HideAll, 签名修 int __thiscall()
- C8预检: 类内无既有HideAll, 改名后无同名双地址
普查佐证: data/status/ret_param_census_20261116.json (锚自检7/7 PASS)
"""
import json

FP = 'data/annotations/structs/CCBControlWindow.json'


def main():
    d = json.load(open(FP, encoding='utf-8'))
    ms = d['methods']

    # C8预检: 目标名不得已被类内其他地址占用
    names_now = {}
    for a, e in ms.items():
        names_now.setdefault(e.get('name'), []).append(a)
    for tgt in ('Update', 'HideAll'):
        holders = [a for a in names_now.get(tgt, []) if a not in ('0x0051b0b0', '0x0051afe0')]
        assert not holders, 'C8守卫: %s 已被 %s 占用' % (tgt, holders)

    e2 = ms['0x0051b0b0']
    assert e2['name'] == 'MoveButtons', '前置漂移: %s' % e2['name']
    e2['name'] = 'Update'
    e2['semantic_name'] = 'CCBControlWindow::Update(int, int)'
    e2['evidence_level'] = 'verified'
    e2['name_note'] = ('C9链律正名20261116: slot2二进制位(0x57051C+8) + RET 8(2参) '
                       '+ 体尾直调UIWnd::Update(this,nVal,nVal2) + 根契约Update(int,int)=BOOL; '
                       '原名MoveButtons=体读数命名, 违每槽一名override律')

    e3 = ms['0x0051afe0']
    assert e3['name'] == 'Update' and e3['sig_model']['params'], '前置漂移'
    e3['name'] = 'HideAll'
    e3['semantic_name'] = 'CCBControlWindow::HideAll(void)'
    e3['evidence_level'] = 'verified'
    e3['semantic_sig'] = 'int'
    e3['sig_model'] = {'return': 'int', 'cc': 'thiscall', 'params': [],
                       'varargs': False, 'pending': False}
    e3['signature'] = 'int __thiscall()'
    e3['name_note'] = ('C9链律正名20261116: slot3二进制位 + RET 0(0参ABI真相, '
                       'census锚PASS) + 体不读a2/a3(hexrays伪影) + 体形态与HideAll族同构 '
                       '(ReleaseTempStorage+释放3子控件经slot5(child,1)) + '
                       '根契约slot3=HideAll() 0参(UIWnd::HideAll体0参虚调子物件slot3); '
                       '原名Update(float,int)=调用点推测伪影')

    json.dump(d, open(FP, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('已修: 0x0051b0b0 MoveButtons→Update; 0x0051afe0 Update(float,int)→HideAll()')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
