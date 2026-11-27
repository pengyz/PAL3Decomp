#!/usr/bin/env python3
"""#151 落位：StateUI 尺寸 162000->171244 + #127 剩余 13 条归属迁移。
无参 = DRY-RUN（只打印）；--apply = 写盘。幂等：已迁过的条目不会二次处理。
"""
import json, sys

ROOT = '/home/peng/workspace/PAL3Decomp/'
S = ROOT + 'data/annotations/structs/'
APPLY = '--apply' in sys.argv
NEW_SIZE = 171244

SIZE_SRC = ("#151 A 级三证：alloc `original/PAL3.exe.asm:240476 push 29CECh` → "
            "`asm:240485 call sub_482ED0`（ctor 入口，前 `mov ecx,eax`）→ `asm:240496` 存 [2AFB8h]；"
            "写界 `asm:193686 mov [esi+29CE8h],ebx`（ctor 尾写 0，即末 4 字节）；"
            "自表 `asm:193688 mov [esi],offset off_56BA30`（表定义 `asm:536838`）。"
            "旧值 162000=0x278D0 为早期父边界估算，漏计尾段 9244B：`0x483650`(max 0x29CE8) 与 "
            "`0x485DF0`(max 0x29CE8) 的位移都无法落在 162000 内。")

M_STATE = {  # 迁 StateUI
    '0x00483650': ('CreatePreviewScene',
                   '#127/#141/#151: 调用点 `asm:240604 mov ecx,[esi+2AFB8h]`(StateUI 实例) → `asm:240606 call sub_483650`；max 位移 0x29CE8 需 171244'),
    '0x00483fa0': None,  # 以下四条从 LineupComp 整条搬迁，保留原条目
    '0x00484140': None,
    '0x004841b0': None,
    '0x00484e10': None,
    '0x00484e30': None,
    '0x004844a0': None,  # 从 MainEquipUI 搬
}
M_LINEUP = ['0x00480530', '0x004819a0', '0x00481ba0', '0x00481cb0', '0x00481eb0', '0x00482140']
FROM = {'0x00483fa0': 'LineupComp', '0x00484140': 'LineupComp', '0x004841b0': 'LineupComp',
        '0x00484e10': 'LineupComp', '0x00484e30': 'LineupComp', '0x004844a0': 'MainEquipUI'}


def load(n):
    return json.load(open(S + n + '.json'))


def dump(n, d):
    with open(S + n + '.json', 'w') as f:
        json.dump(d, f, ensure_ascii=False, indent=1)
        f.write('\n')


st, lu, lc, me = load('StateUI'), load('LineupUI'), load('LineupComp'), load('MainEquipUI')
cls = {'StateUI': st, 'LineupUI': lu, 'LineupComp': lc, 'MainEquipUI': me}


def cnt():
    return {k: len(v['methods']) for k, v in cls.items()}


before = cnt()
print('before methods', before, 'size', st.get('binary_size'))

# 阶段1：尺寸
if st.get('binary_size') != NEW_SIZE:
    print('[1] StateUI.binary_size %s -> %s' % (st.get('binary_size'), NEW_SIZE))
    st['binary_size'] = NEW_SIZE
    st['binary_size_source'] = SIZE_SRC
else:
    print('[1] size 已是 %s（幂等跳过）' % NEW_SIZE)

# 阶段2：迁移
for a in M_LINEUP:
    src = me
    if a in src['methods']:
        if a in lu['methods']:
            del src['methods'][a]
            print('[2] %s 已在 LineupUI，删 MainEquipUI 冗余' % a)
        else:
            lu['methods'][a] = src['methods'].pop(a)
            print('[2] %s MainEquipUI -> LineupUI' % a)
    elif a not in lu['methods']:
        print('[2] !! %s 既不在 MainEquipUI 也不在 LineupUI（异常）' % a)

for a, spec in M_STATE.items():
    if spec is not None:  # 无现存条目：新建
        if a in st['methods']:
            print('[2] %s 已在 StateUI' % a)
        else:
            st['methods'][a] = {'name': spec[0], 'evidence_level': 'A', 'source': spec[1]}
            print('[2] %s 新建 %s -> StateUI' % (a, spec[0]))
        continue
    src_name = FROM[a]
    src = cls[src_name]
    if a in src['methods']:
        if a in st['methods']:
            del src['methods'][a]
            print('[2] %s 已在 StateUI，删 %s 冗余' % (a, src_name))
        else:
            st['methods'][a] = src['methods'].pop(a)
            print('[2] %s %s -> StateUI' % (a, src_name))
    elif a not in st['methods']:
        print('[2] !! %s 不在 %s 也不在 StateUI（异常）' % (a, src_name))

after = cnt()
print('after  methods', after, '（预期 StateUI 38 / LineupUI 42 / LineupComp 2 / MainEquipUI 22）')

# 一致性断言
dup = [a for a in M_LINEUP + list(M_STATE) if sum(1 for v in cls.values() if a in v['methods']) != 1]
print('唯一性断言：', 'OK' if not dup else 'FAIL %s' % dup)

if APPLY:
    for n in cls:
        dump(n, cls[n])
    print('applied: StateUI/LineupUI/LineupComp/MainEquipUI')
else:
    print('DRY-RUN only（未写盘）')
