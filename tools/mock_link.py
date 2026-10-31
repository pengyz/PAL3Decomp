#!/usr/bin/env python3
"""tools/mock_link.py — link-build harness（codegen+stub overlay 设计 §3.3）。

装配契约（设计 §1）：gbengine.dll/binkw32/mss32/win32 全部由真实 DLL 提供；
exe 自身代码 = 唯一重写对象。本工具做「空壳但真闭合」的链接装配：
  - S2-ok 单元 ⇒ 编真身（pal3/src/...cpp）
  - S2-fail 单元 ⇒ 编 stub（phase2/stubs/..._stub.cpp；缺 stub ⇒ fail-loud）
  - 链接 gbengine.lib（gbengine.def 生成）+ win32 系 ⇒ 可执行产物
  - 输出**真身覆盖率**（真编单元/总单元）——不用「编译通过」措辞（设计 §4）。

编译面与 S2 普查同源（pipeline/probe_compile.INCLUDE_DIRS + run_cl），
链接机制吸收 manual/pal3/build.py（LIB.EXE /DEF + LINK.EXE + 环境）。

用法:
  python tools/mock_link.py [--skip-compile] [--keep-going]
"""
import argparse
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))
import probe_compile as pc  # noqa: E402

CENSUS = PROJECT_ROOT / 'data' / 'status' / 'probe_census.json'
SRC_ROOT = PROJECT_ROOT / 'pal3' / 'src'
STUB_ROOT = PROJECT_ROOT / 'phase2' / 'stubs'
BUILD = PROJECT_ROOT / 'build' / 'mock_link'
VC6 = PROJECT_ROOT / 'tools' / 'compilers' / 'msvc6.0'
VC6_LIB = PROJECT_ROOT / 'tools' / 'vc6' / 'Lib'
GBENGINE_DEF = PROJECT_ROOT / 'gbengine' / 'gbengine.def'
TARGET = BUILD / 'PAL3_mocklink.exe'

LIBS = ['gbengine.lib', 'user32.lib', 'gdi32.lib', 'winmm.lib', 'uuid.lib',
        'ole32.lib', 'oleaut32.lib', 'advapi32.lib', 'shell32.lib',
        'libc.lib', 'oldnames.lib', 'kernel32.lib']


def plan_units():
    """probe_census → [(unit, kind, src_path)]；缺 stub ⇒ fail-loud。"""
    c = json.loads(CENSUS.read_text(encoding='utf-8'))
    plan, missing = [], []
    for x in c['s2']['results']:
        u = x['unit']
        if x.get('status') == 'ok':
            plan.append((u, 'real', PROJECT_ROOT / u))
        else:
            rel = u.replace('\\', '/')
            stem = rel[len('pal3/src/'):] if rel.startswith('pal3/src/') else rel
            stub = STUB_ROOT / (stem[:-4] + '_stub.cpp')
            if stub.exists():
                plan.append((u, 'stub', stub))
            else:
                missing.append((u, str(stub)))
    return plan, missing


def compile_units(plan, keep_going=False):
    """逐单元编译（真身/stub 同源 include 面 + 单元目录 /I）。"""
    incs_base = ['/I' + pc.wpath(d) for d in pc.INCLUDE_DIRS]
    BUILD.mkdir(parents=True, exist_ok=True)
    objs, failed = [], []
    # EH 元数据胶水 + 虚槽批量供给（(d) 手工合成，非单元——恒编）
    extras = [PROJECT_ROOT / 'phase2/stubs/_eh_metadata_stub.cpp']
    for sub in ('_slots', '_supply'):
        d = PROJECT_ROOT / 'phase2/stubs' / sub
        if d.exists():
            extras += sorted(d.glob('*.cpp'))
    plan = [(str(e.relative_to(PROJECT_ROOT)), 'glue', e) for e in extras] + list(plan)
    for u, kind, src in plan:
        obj = BUILD / (u.replace('/', '_').replace('\\', '_') + '.obj')
        unit_dir = str((PROJECT_ROOT / u).parent)
        incs = incs_base + ['/I' + pc.wpath(unit_dir)]
        out, err = pc.run_cl(incs + ['/Fo' + pc.wpath(str(obj)), '/c', pc.wpath(str(src))],
                             timeout=120, flags=('/nologo', '/TP', '/c', '/W3', '/GX'))
        errs = [l for l in out.splitlines() if ' error ' in l]
        if errs or err:
            failed.append((u, kind, errs[:2] or [str(err)]))
            if not keep_going:
                break
        else:
            objs.append(obj)
    return objs, failed


def make_gbengine_lib():
    """gbengine.def → gbengine.lib（LIB.EXE；build.py 同机制）。"""
    def_dst = BUILD / 'gbengine.def'
    shutil.copy2(GBENGINE_DEF, def_dst)
    lib_exe = str(VC6 / 'Bin' / 'LIB.EXE')
    if os.name != 'nt':
        cmd = ['wine', pc.wpath(lib_exe)]
    else:
        cmd = [pc.wpath(lib_exe)]
    cmd += ['/DEF:' + pc.wpath(str(def_dst)), '/OUT:' + pc.wpath(str(BUILD / 'gbengine.lib')),
            '/MACHINE:IX86']
    proc = subprocess.run(cmd, capture_output=True, text=True, errors='replace', cwd=str(BUILD))
    return (BUILD / 'gbengine.lib').exists(), proc.stdout + proc.stderr


def link(objs):
    """LINK.EXE 装配（build.py 同机制：/SUBSYSTEM:WINDOWS /OPT:NOREF）。"""
    link_exe = str(VC6 / 'Bin' / 'LINK.EXE')
    cmd = [pc.wpath(link_exe)] if os.name == 'nt' else ['wine', pc.wpath(link_exe)]
    cmd += ['/NOLOGO', '/SUBSYSTEM:WINDOWS', '/OPT:NOREF', '/OUT:' + pc.wpath(str(TARGET))]
    cmd += [pc.wpath(str(o)) for o in objs]
    cmd += [pc.wpath(str(BUILD / 'gbengine.lib'))]
    cmd += [pc.wpath(str(VC6_LIB / l)) for l in LIBS if l != 'gbengine.lib']
    env = os.environ.copy()
    env['LIB'] = ';'.join([pc.wpath(str(VC6 / 'lib')), pc.wpath(str(VC6_LIB)),
                          pc.wpath(str(BUILD))])
    proc = subprocess.run(cmd, capture_output=True, text=True, errors='replace',
                          env=env, cwd=str(BUILD))
    return proc.returncode, proc.stdout + proc.stderr


def main():
    ap = argparse.ArgumentParser(description='link-build harness（真身+stub 装配）')
    ap.add_argument('--keep-going', action='store_true', help='编译失败继续收集')
    args = ap.parse_args()

    plan, missing = plan_units()
    n_real = sum(1 for _, k, _ in plan if k == 'real')
    n_stub = sum(1 for _, k, _ in plan if k == 'stub')
    total = n_real + n_stub + len(missing)
    print('[mock_link] 真身覆盖率 %d/%d = %.0f%%（真编 %d · stub %d · 缺 %d）'
          % (n_real, total, 100.0 * n_real / max(total, 1), n_real, n_stub, len(missing)))
    if missing:
        print('[mock_link] FAIL-LOUD: %d 个 S2-fail 单元缺 stub（催生成）:' % len(missing))
        for u, s in missing[:10]:
            print('   %s -> %s' % (u, s))
        return 2

    objs, failed = compile_units(plan, keep_going=args.keep_going)
    if failed:
        print('[mock_link] 编译失败 %d 单元:' % len(failed))
        for u, k, errs in failed[:10]:
            print('   [%s] %s' % (k, u))
            for e in errs:
                print('      %s' % e[:110])
        return 3
    print('[mock_link] 编译面 %d/%d 单元就位' % (len(objs), len(plan)))

    ok, log = make_gbengine_lib()
    if not ok:
        print('[mock_link] gbengine.lib 生成失败:\n%s' % log[-500:])
        return 4

    rc, log = link(objs)
    (BUILD / 'link.log').write_text(log, encoding='utf-8')   # 全量日志（分析面）
    # [2026-10-31] 需求台账累积——供给按 ledger 并集生成，防迭代振荡
    # （只看当轮日志会丢已供给符号：上轮满足⇒当轮缺名⇒下轮丢定义⇒再现）。
    seen = set()
    ledger = BUILD / 'demand_ledger.txt'
    if ledger.exists():
        seen.update(l.strip() for l in ledger.read_text(encoding='utf-8').splitlines() if l.strip())
    for l in log.splitlines():
        if 'LNK2001' not in l and 'LNK2019' not in l:
            continue
        i = l.find('symbol "')
        if i >= 0:
            j = l.find('"', i + 8)
            seen.add(l[i + 8:j])
        else:
            m = re.search(r'symbol\s+([A-Za-z_][\w$?@]*)\s*$', l)
            if m:
                seen.add(m.group(1))
    ledger.write_text('\n'.join(sorted(seen)) + '\n', encoding='utf-8')
    if rc == 0:
        size = TARGET.stat().st_size
        print('[mock_link] 链接闭合 ✓ %s (%d bytes)' % (TARGET, size))
        print('[mock_link] 真身覆盖率 %d/%d = %.0f%%' % (n_real, total, 100.0 * n_real / total))
        return 0
    unresolved = [l for l in log.splitlines() if 'LNK2001' in l or 'LNK2019' in l]
    print('[mock_link] 链接未闭合: unresolved %d（截前 15）:' % len(unresolved))
    for l in unresolved[:15]:
        print('   %s' % l.strip()[:120])
    dup = [l for l in log.splitlines() if 'LNK2005' in l]
    if dup:
        print('[mock_link] LNK2005 重复符号 %d（截前 5）:' % len(dup))
        for l in dup[:5]:
            print('   %s' % l.strip()[:120])
    return 5


if __name__ == '__main__':
    sys.exit(main())
