"""寄存器级 provenance 扫描器 —— 基对象归属的确定性工具。

对给定函数的 AT&T 指令流做过程内前向数据流分析：
  * 入口 %ecx = this（__thiscall）
  * 寄存器标签：('this', delta) / ('arg', k) / ('const', v) / None（未知）
  * call 后 %eax/%ecx/%edx 失效（调用方保存）✗；%ebx/%esi/%edi/%ebp 保持 ✓
输出：[('this'|'arg', off, 'r'|'w')] 访问三元组（按偏移排序去重）。

用途：
  ① CScreenMode::InitEquipScreen m_id 偏移裁定（Phase 2 队列 ①）
  ② SceneObj 复用槽批 ReleaseObject 矛盾裁定（队列 ②）
"""
import re

CALLER_SAVED = ('%eax', '%ecx', '%edx')
GP = ('%eax', '%ebx', '%ecx', '%edx', '%esi', '%edi', '%ebp')

_RM_E = re.compile(r'(?:0x([0-9a-f]+))?\(%(e[a-d]x|e[sd]i|e[bp])\)')
_MOV_RM_SRC = re.compile(r'^mov\s+\S+\s+(\S+)\s*,\s*%(\w+)$')
_MOV_REG_RM = re.compile(r'^mov\s+%(\w+)\s*,\s*(.+)$')
_LEA = re.compile(r'^lea\s+(.+),%(\w+)$')
_MOV_IMM_REG = re.compile(r'^mov[lbw]?\s+\$[^,]+,%(\w+)$')
_XOR_RR = re.compile(r'^xor\s+%(e\w+),%(\w+)$')


def _rm_base(text):
    """'(0xNN)%reg' / '(0xNN)(%reg)' / '(%reg)' → (base_reg, disp)"""
    m = re.search(r'(?:0x([0-9a-f]+))?\(%(e[a-d]x|e[sd]i|e[bp])\)\s*$', text.strip())
    if not m:
        return None, None
    disp = int(m.group(1), 16) if m.group(1) else 0
    return '%' + m.group(2), disp


def scan(insns, this_reg='%ecx', args_at_entry=None):
    """insns: [(va, at&t_text)]；this_reg: 入口 this 所在寄存器
    → {'accesses': [(owner, off, rw)], 'regs': 末态}"""
    regs = {this_reg: ('this', 0)}
    for r in GP:
        regs.setdefault(r, None)
    accesses = []

    def tag_of(reg):
        return regs.get(reg)

    def setreg(reg, tag):
        if reg in regs:
            regs[reg] = tag

    def note(owner, off, rw):
        if owner in ('this', 'arg'):
            accesses.append((owner, off, rw))

    for va, text in insns:
        t = ' '.join(text.split())
        # call：调用方保存寄存器失效
        if t.startswith('call'):
            for r in CALLER_SAVED:
                setreg(r, None)
            continue
        # xor %r,%r ⇒ 常量 0
        m = _XOR_RR.match(t)
        if m and m.group(1) == m.group(2):
            setreg(m.group(2), ('const', 0))
            continue
        # 寄存器复制（必须先于内存分支判定 ✓）
        m = re.match(r'^mov\s+%(e\w+)\s*,\s*%(e\w+)$', t)
        if m:
            setreg('%' + m.group(2), regs.get('%' + m.group(1)))
            continue
        # mov %reg,(disp)%esp —— 栈槽写（调用方栈参区）⇒ ('arg', disp) ✓
        m = re.match(r'^mov[lbw]?\s+%([re]\w+)\s*,\s*(0x[0-9a-f]+)?\(%esp\)$', t)
        if m:
            disp = int(m.group(2), 16) if m.group(2) else 0
            accesses.append(('arg', disp, 'w'))
            continue
        # mov %reg,(disp)%base —— 写内存（目的偏移恒可归属 ✓）
        m = re.match(r'^mov\s+%([re]\w+)\s*,\s*(.+\(%e[sd]i\)|.+\(%e[a-d]x\))$', t)
        if m:
            base, disp = _rm_base(m.group(2))
            tag = tag_of(base) if base else None
            if tag and tag[0] in ('this', 'arg'):
                note(tag[0], tag[1] + disp, 'w')
            continue
        # mov (disp)%esp,%reg —— 栈参读取 ⇒ ('arg', disp) ✓
        m = re.match(r'^mov[lbw]?\s+(0x[0-9a-f]+)?\(%esp\)\s*,\s*%([re]\w+)$', t)
        if m:
            disp = int(m.group(1), 16) if m.group(1) else 0
            setreg('%' + m.group(2), ('arg', disp))
            continue
        # mov (disp)%base,%reg —— 读内存到寄存器（读后 dst 携带 load 标签）
        m = re.match(r'^mov[lbw]?\s+(.+\(%e[sd]i\)|.+\(%e[a-d]x\))\s*,\s*%([re]\w+)$', t)
        if m:
            base, disp = _rm_base(m.group(1))
            dst = '%' + m.group(2)
            tag = tag_of(base) if base else None
            if tag and tag[0] in ('this', 'arg'):
                note(tag[0], tag[1] + disp, 'r')
                setreg(dst, ('load', tag[0], tag[1] + disp))
                continue
            if dst in regs:
                setreg(dst, None)
            continue
        # lea (disp)%base,%reg
        m = _LEA.match(t)
        if m:
            src, dst = m.group(1), '%' + m.group(2)
            base, disp = _rm_base(src)
            if base:
                tag = tag_of(base)
                if tag and tag[0] in ('this', 'arg'):
                    setreg(dst, (tag[0], tag[1] + disp))
                    continue
            setreg(dst, None)
            continue
        # mov $imm,%reg ⇒ 常量
        m = _MOV_IMM_REG.match(t)
        if m:
            setreg(m.group(1), None)
            continue
        # mov %r,%r（寄存器复制）
        m = re.match(r'^mov\s+%(e\w+)\s*,\s*%(\w+)$', t)
        if m:
            s, d = '%' + m.group(1), '%' + m.group(2)
            if d in regs:
                setreg(d, regs.get(s))
            continue
        # push/pop：不显式建模（MSVC6 常用 push 保存，不产生成员访问）
    out = []
    seen = set()
    for owner, off, rw in accesses:
        key = (owner, off)
        if key in seen:
            # 同偏移读写并存 ⇒ 记 'rw'
            for i, (o2, off2, rw2) in enumerate(out):
                if o2 == owner and off2 == off:
                    out[i] = (owner, off, 'rw')
            continue
        seen.add(key)
        out.append((owner, off, rw))
    out.sort(key=lambda x: x[1])
    return {'accesses': out, 'regs': dict(regs)}


if __name__ == '__main__':
    import json, sys
    print(__doc__)
