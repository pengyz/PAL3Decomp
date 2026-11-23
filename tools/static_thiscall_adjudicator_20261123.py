#!/usr/bin/env python3
"""[static+thiscall 矛盾裁决 2026-11-23] 26 条 static:true 且 cc=thiscall 注解条目逐案取证。

裁决判据(每案三证):
  ①方法体头窗是否缓存并使用 ecx(this)
  ②原始二进制全部调用点 ecx 纪律——**从宿主函数起点对齐反汇编**(语料地址表),
    取 call 前最后一次 ecx 写入形态:
      - mov/lea ecx, <真值>  = thiscall 形调用点(ecx 装载对象)
      - 窗内无 ecx 写        = 静态形调用点(ecx 值无关紧要, 未初始化即调)
  ③sig_model cc(注入 IDB 的 thiscall 类型, hexrays 渲染源)

判定: 调用点 ecx 纪律是 ABI 真值(L1 字节匹配的原始形), 体用 this 是强补强。
"""
import glob
import json
import struct
import capstone

EXE = '/home/peng/workspace/PAL3Decomp/original/PAL3.exe'
DECOMP = '/home/peng/workspace/PAL3Decomp/asm/pal3/decomp'
IMAGE_BASE = 0x400000

TARGETS = [
    (0x00538D20, 'Actor', 'CompareModelName'),
    (0x004AFD80, 'ArcLocaleRole', 'ParseLocaleData'),
    (0x004115C0, 'Array', 'PartialSort'),
    (0x0051D610, 'CCBLineupWindow', 'SetFaceLineup'),
    (0x004EA590, 'CCBStageCam', 'DlgProc'),
    (0x004E53C0, 'CCBUICtrl', 'SendWindowMessage'),
    (0x004E53E0, 'CCBUICtrl', 'FormatCombatBuffer'),
    (0x004CFD00, 'CEffModel', 'AllocEffect'),
    (0x0041E7D0, 'Camera', 'CheckCollision1'),
    (0x0041EA00, 'Camera', 'CheckCollision2'),
    (0x00410360, 'InputSystem', 'ProcessFrame'),
    (0x0053CE20, 'Logger', 'WriteRoleNames'),
    (0x00407180, 'PAL3', 'StartWolf'),
    (0x00433F90, 'PalScript', 'ProcessGBKString'),
    (0x0040DCD0, 'PtrArray', 'CompareValues'),
    (0x00433DC0, 'PtrArray', 'CopyRange'),
    (0x00410430, 'RoleSystem', 'RenderMainRole'),
    (0x004126D0, 'RoleSystem', 'GetAnimOffset'),
    (0x004161E0, 'RoleSystem', 'ScaleVector'),
    (0x00532960, 'RoleSystem', 'ScaleValue'),
    (0x00423500, 'SceneMgr', 'ClearInactiveRoles'),
    (0x0053EF60, 'SceneObj', 'LoadFromConfig'),
    (0x0040CBB0, 'ScriptSystem', 'GetScriptContext'),
    (0x0040CBD0, 'ScriptSystem', 'PassThrough'),
    (0x0040CC00, 'ScriptSystem', 'CheckEventType'),
    (0x004235B0, 'UIScene', 'ProcessInput'),
]


def load():
    d = open(EXE, 'rb').read()
    e = struct.unpack_from('<I', d, 0x3C)[0]
    opt = struct.unpack_from('<H', d, e + 20)[0]
    sec0 = e + 24 + opt
    nsec = struct.unpack_from('<H', d, e + 6)[0]
    secs = {}
    for i in range(nsec):
        s = sec0 + 40 * i
        nm = d[s:s + 8].rstrip(b'\0').decode()
        vs, va, rs, ra = struct.unpack_from('<IIII', d, s + 8)
        secs[nm] = (va + IMAGE_BASE, d[ra:ra + rs])
    return d, secs


def load_func_map():
    """语料地址表 → (start, size) 升序表(对齐反汇编锚点)。"""
    funcs = []
    for f in glob.glob(DECOMP + '/*.json'):
        try:
            d = json.load(open(f, encoding='utf-8'))
            a = d.get('address') or ''
            s = d.get('size_bytes') or 0
            if isinstance(a, str) and a.startswith('0x') and s:
                funcs.append((int(a, 16), int(s)))
        except Exception:
            pass
    return sorted(set(funcs))


def body_uses_this(md, text, text_va, tgt):
    off = tgt - text_va
    cached = None
    for ins in md.disasm(text[off:off + 0x60], tgt):
        if ins.mnemonic == 'mov' and ins.op_str.endswith(', ecx'):
            cached = ins.op_str.split(',')[0].strip()
            break
    if cached is None:
        return False, '头0x60B无ecx缓存'
    for ins in md.disasm(text[off + 0x10:off + 0x200], tgt + 0x10):
        m = ins.op_str
        if ('[%s+' % cached) in m or m == '[%s]' % cached:
            return True, '%s %s' % (ins.mnemonic, m)
        if ins.mnemonic == 'ret':
            break
    return False, 'ecx缓存%s但0x200B窗内未用' % cached


def caller_ecx_form(md, text, text_va, funcs, call_va):
    """宿主函数起点对齐反汇编到 call 处, 取最后一次 ecx 写入形态。"""
    start = None
    for s, sz in funcs:
        if s <= call_va < s + sz:
            start = s
            break
    if start is None:
        return None, 'no-host-func'
    off = start - text_va
    end_off = call_va - text_va
    last = None
    for ins in md.disasm(text[off:end_off], start):
        op0 = ins.op_str.split(',')[0].strip()
        if op0 == 'ecx' and ins.mnemonic in ('mov', 'lea', 'pop', 'xor', 'or'):
            last = '%s %s' % (ins.mnemonic, ins.op_str)
    if last is None:
        return False, 'carry-in(无ecx写)'
    if last.startswith('lea ecx, [ecx') or last == 'mov ecx, ecx':
        return None, 'decode-anchor?(nop形)'
    return True, last


def main():
    d, secs = load()
    text_va, text = secs['.text']
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    funcs = load_func_map()
    print('语料函数表: %d 条(对齐锚)' % len(funcs))

    out = {}
    for tgt, cls, fn in TARGETS:
        uses, why = body_uses_this(md, text, text_va, tgt)
        callers = []
        for o in range(len(text) - 5):
            if text[o] == 0xE8:
                rel = int.from_bytes(text[o + 1:o + 5], 'little', signed=True)
                if text_va + o + 5 + rel == tgt:
                    callers.append(text_va + o)
        real_ecx, carry, nopform, forms = 0, 0, 0, []
        for c in callers[:60]:
            ok, form = caller_ecx_form(md, text, text_va, funcs, c)
            if ok is True:
                real_ecx += 1
                if len(forms) < 4:
                    forms.append(form)
            elif ok is False:
                carry += 1
            else:
                nopform += 1
        n = len(callers)
        if uses:
            v = 'THISCALL(体用this)'
        elif n == 0:
            v = '无直调(待溯间接)'
        elif carry == n:
            v = 'STATIC形(全调用点无ecx写)'
        elif real_ecx and carry == 0:
            v = 'THISCALL(全调用点ecx装载)'
        elif real_ecx:
            v = 'MIXED thiscall%d/static%d/nop%d' % (real_ecx, carry, nopform)
        else:
            v = 'nop形%d待复核' % nopform
        out['%s.%s' % (cls, fn)] = {'addr': '0x%08X' % tgt, 'verdict': v,
                                    'body_uses_this': uses, 'body_why': why,
                                    'n_callers': n, 'real_ecx': real_ecx,
                                    'carry_in': carry, 'nop_form': nopform,
                                    'ecx_forms': forms}
        print('%-30s 0x%08X this=%-1s callers=%-3d real_ecx=%-2d carry=%-2d nop=%-2d %s' % (
            '%s.%s' % (cls, fn), tgt, 'Y' if uses else 'n', n, real_ecx, carry, nopform, v))
        for f in forms[:3]:
            print('      <%s>' % f)

    json.dump(out, open('data/status/static_thiscall_adjudication_20261123.json', 'w',
                        encoding='utf-8'), ensure_ascii=False, indent=1)
    print('\n落档 data/status/static_thiscall_adjudication_20261123.json')


if __name__ == '__main__':
    main()
