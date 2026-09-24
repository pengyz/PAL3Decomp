#!/usr/bin/env python3
"""金样本夹具 ↔ 真机 objdump 输出**逐指令比对**（Task 3 的出处自证）。

用途：`tests/test_vtable_sig_infer.py` 里的反汇编夹具全部是手抄的逐字输出 —— 本脚本
用真机 MSVC6 重新编译探针、重新反汇编，并与夹具的**解析结果**（mnem + 操作数）逐条比对，
只有对不齐就非零退出。地址操作数（跳转/call 目标文本）不参与比较（夹具里地址被重写过）。

用法：
    python3 data/status/_vtable_sig_probe_20260925/verify_fixtures.py [--keep]

依赖：wine + tools/wine_cl.sh + objdump（缺失时非零退出，不静默通过）。
"""
import argparse
import importlib.util
import os
import re
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(os.path.dirname(HERE)))  # <repo>/data/status/<dir>
sys.path.insert(0, os.path.join(REPO, 'tools'))
from vtable_slot_classifier import parse_disasm_report as P            # noqa: E402
from vtable_sig_infer import sanitize_pe_relocs                        # noqa: E402

#: 探针 → 编译开关（与 README 逐字一致）
PROBES = {
    'rw1': ['/Od', '/GR'],
    'rw2': ['/Od', '/GR'],
    'rw3': ['/Od', '/GR'],
    'rw4': ['/Od', '/GR'],
    'opt1': ['/O2', '/Ob2', '/Oi', '/Ot', '/Oy', '/GR'],
    'opt2': ['/O2', '/Ob2', '/Oi', '/Ot', '/Oy', '/GR'],
    # R=1/R=2 新增探针（源入库于 0a2f8bdc4）
    'deref_form': ['/O2', '/Ob2', '/Oi', '/Ot', '/Oy', '/GR'],
    'rw5': ['/Od', '/GR'],
    'rw6': ['/Od', '/GR'],
    # R=2 新增探针（源入库于本轮）
    'rw7': ['/Od', '/GR'],
}
#: 攻击用例（Task 1/2 目录，本任务复用）
ATTACK = os.path.join(REPO, 'data', 'status', '_vtable_attack_cases_20260925')
ATTACK_PROBES = {'s1': ['/Od', '/GR'], 's3': ['/Od', '/GR'], 'r2': ['/Od', '/GR'],
                 'e1': ['/Od', '/GR'], 'b1': ['/Od', '/GR']}

#: 夹具名 → (obj 键, 符号)
FIXTURES = {
    'C1_UNUSED': ('attack:s1', '?unused@S@@UAEXHH@Z'),
    'C2_FREG': ('attack:s1', '?freg@S@@UAIXHH@Z'),
    'C4_LOG': ('attack:s1', '?log@S@@UAAXPBDZZ'),
    'S1_IDI': ('attack:s1', '?idi@S@@UAEHH@Z'),
    'C3_CF': ('attack:r2', '?cf@Xc@@UAAXH@Z'),
    'C3_CF2': ('attack:r2', '?cf2@Xc@@UAAXHH@Z'),
    'C5_O_INT': ('attack:e1', '?o@E@@UAEXH@Z'),
    'C6_FB': ('attack:b1', '?fb@SB@@UAEX_N@Z'),
    'C6_FI': ('attack:b1', '?fi@SB@@UAEXH@Z'),
    'S3_TWO': ('attack:s3', '?two@SC@@UAEXHN@Z'),
    'RW1_RI': ('rw1', '?ri@Rn@@UAEHH@Z'),
    'C1_R2_MULTI_BASE_GAP': ('rw7', '?mwp@Rn7@@UAEHPAUInnerV@@@Z'),
    'RW1_RC': ('rw1', '?rc@Rn@@UAEDH@Z'),
    'RW1_RS': ('rw1', '?rs@Rn@@UAEFH@Z'),
    'RW1_RF': ('rw1', '?rf@Rn@@UAEMH@Z'),
    'RW1_RV': ('rw1', '?rv@Rn@@UAEXH@Z'),
    'RW1_RB': ('rw1', '?rb@Rn@@UAE?AUBig@@H@Z'),
    'RW1_CV': ('rw1', '?cv@Rn@@UAAXH@Z'),
    'RW1_F1': ('rw1', '?f1@Rn@@UAIXH@Z'),
    'RW1_F0U': ('rw1', '?f0u@Rn@@UAEXXZ'),
    'RW2_RFQ': ('rw2', '?rfq@Rf@@UAEMN@Z'),
    'RW3_RBOOL': ('rw3', '?rbool@Rb@@UAE_NH@Z'),
    'RW3_RCHAR': ('rw3', '?rchar@Rb@@UAEDH@Z'),
    'RW3_R64': ('rw3', '?r64@Rb@@UAE_JH@Z'),
    'RW4_RETP': ('rw4', '?retp@Rn2@@UAEHPAUInner@@@Z'),
    'RW4_RETP2': ('rw4', '?retp2@Rn2@@UAEHPAH@Z'),
    'RW4_WR': ('rw4', '?wr@Rn2@@UAEXPAUInner@@@Z'),
    'RW4_MK': ('rw4', '?mk@Rn2@@UAE?AUInner@@H@Z'),
    'RW4_MK0': ('rw4', '?mk0@Rn3@@UAE?AUInner@@XZ'),
    'RW4_MK0B': ('rw4', '?mk0b@Rn3@@UAE?AUBig16@@XZ'),
    'OPT1_ZERO': ('opt1', '?zero@Op@@UAEXH@Z'),
    'OPT1_ADD1': ('opt1', '?add1@Op@@UAEHH@Z'),
    'OPT2_SD': ('opt2', '?sd@Os@@UAGXH@Z'),
    'OPT2_CD': ('opt2', '?cd@Os@@UAAXH@Z'),
    'OPT2_FE': ('opt2', '?fe@Os@@UAIXH@Z'),
    'OPT2_FU': ('opt2', '?fu@Os@@UAIXH@Z'),
    'OPT2_T2': ('opt2', '?t2@Os@@UAEHHH@Z'),
    # ---- R=1 新夹具（deref_form.cpp / rw5.cpp / rw6.cpp） ----
    'C1_R1_DEREF_SAME_BYTES': ('deref_form', '?wr2@Rn6@@UAEHPAUInnerV@@@Z'),
    'C1_R1_POFF_GAP': ('rw5', '?poff@RnA@@UAEHPAH@Z'),
    'C1_R1_PAD_SRET': ('rw6', '?mkp@Rn11@@UAE?AUPad16@@XZ'),
    'C1_R1_PWRITE_NOT_SRET': ('rw6', '?pwrite@Rn11@@UAEHPAUPad16@@@Z'),
}
#: 调用点片段 → (obj 键, 所在函数)
CALL_FIXTURES = {
    'C2_FREG_CALL': ('attack:s1', '_main'),
    'C3_CCALL': ('attack:r2', '?ccall@@YAXPAUXc@@@Z'),
    'C6_C2_CALLS': ('attack:b1', '?c2@@YAXPAUSB@@H@Z'),
}


def _key(text):
    """指令序列键（target 操作数不参与：夹具里地址被重写）。"""
    text = sanitize_pe_relocs(text)[0]
    return tuple((i.mnem, tuple((o.kind, o.reg, o.base, o.index, o.scale, o.disp)
                                for o in i.ops if o.kind != 'target'))
                 for i in P(text).insns)


def _funcs(obj):
    """objdump -dr 输出 → {符号: [函数体文本, ...]}（同名 COMDAT 多个）。"""
    txt = subprocess.run(['objdump', '-dr', obj], capture_output=True, text=True).stdout
    out, cur, buf = {}, None, []

    def flush():
        if cur:
            out.setdefault(cur, []).append('\n'.join(buf))

    for line in txt.splitlines():
        m = re.match(r'^[0-9A-Fa-f]{8} <([^>]+)>:', line)
        if m:
            flush()
            cur, buf = m.group(1), []
            continue
        if cur is None:
            continue
        if re.match(r'^\s*[0-9A-Fa-f]+:', line):
            buf.append(line)
        elif line.strip() == '' or 'DISP32' in line or 'dir32' in line:
            pass
        else:
            flush()
            cur, buf = None, []
    flush()
    return out


def _compile(name, flags, outdir, tmp):
    if name.startswith('attack:'):
        src = os.path.join(ATTACK, name.split(':', 1)[1] + '.cpp')
    else:
        src = os.path.join(HERE, name + '.cpp')
    obj = os.path.join(outdir, name.replace(':', '_') + '.obj')
    cmd = [os.path.join(REPO, 'tools', 'wine_cl.sh'), '/c'] + flags + \
          ['/Itools/compilers/msvc6.0/Include', '/Fo' + obj, src]
    r = subprocess.run(cmd, cwd=REPO, capture_output=True, text=True)
    if r.returncode != 0 or not os.path.exists(obj):
        sys.stderr.write(r.stdout[-2000:] + r.stderr[-2000:])
        raise SystemExit('编译失败: %s（exit=%d）' % (src, r.returncode))
    return obj


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--keep', action='store_true', help='保留临时 .obj')
    args = ap.parse_args()
    if not os.path.exists(os.path.join(REPO, 'tools', 'wine_cl.sh')):
        raise SystemExit('缺少 tools/wine_cl.sh')
    if not shutil.which('wine') or not shutil.which('objdump'):
        raise SystemExit('需要 wine 与 objdump')

    spec = importlib.util.spec_from_file_location(
        'fixtures', os.path.join(REPO, 'tests', 'test_vtable_sig_infer.py'))
    fx = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(fx)

    tmp = tempfile.mkdtemp(prefix='sigprobe_')
    objs = {}
    try:
        for name, flags in list(PROBES.items()) + list(ATTACK_PROBES.items()):
            key = ('attack:' + name) if name in ATTACK_PROBES else name
            objs[key] = _funcs(_compile(key, flags, tmp, tmp))
        bad = 0
        for fname, (objkey, sym) in sorted(FIXTURES.items()):
            want = _key(getattr(fx, fname))
            got = [_key(v) for v in objs[objkey].get(sym, [])]
            if not got:
                print('  NO SYMBOL %-34s %s' % (sym, objkey))
                bad += 1
            elif not any(g[:len(want)] == want for g in got):
                print('  MISMATCH  %-12s %s' % (fname, sym))
                bad += 1
            else:
                print('  OK        %-12s %s' % (fname, sym))

        def subseq(sub, full):
            return any(full[i:i + len(sub)] == sub for i in range(len(full) - len(sub) + 1))

        for fname, (objkey, sym) in sorted(CALL_FIXTURES.items()):
            got = [_key(v) for v in objs[objkey].get(sym, [])]
            if not got or not subseq(_key(getattr(fx, fname)), got[0]):
                print('  MISMATCH  %-12s (调用点片段 %s)' % (fname, sym))
                bad += 1
            else:
                print('  OK        %-12s (调用点片段 %s)' % (fname, sym))
        print('夹具 %d 条（函数 %d + 调用点 %d）；不一致 %d'
              % (len(FIXTURES) + len(CALL_FIXTURES), len(FIXTURES),
                 len(CALL_FIXTURES), bad))
        return 1 if bad else 0
    finally:
        if not args.keep:
            shutil.rmtree(tmp, ignore_errors=True)
        else:
            print('临时目录保留: %s' % tmp)


if __name__ == '__main__':
    sys.exit(main())