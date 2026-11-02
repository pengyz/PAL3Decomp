# ## [Ghidra headless postScript] 注解导入计划执行器（双轨 spec §4）
# 用法: analyzeHeadless <projdir> <projname> -import <PAL3.exe> \
#         -postScript ghidra_track/apply_plan.py ghidra_track/out/plan.json
# 两遍建结构 + thiscall 签名 + sizeof 对账（导入即校验）。纯逻辑在 import_annotation。
import json
import os
import sys

import pyghidra
pyghidra.start()   # JVM 先起，ghidra.* 方可 import（PyGhidra 契约）

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from import_annotation import partition_struct_passes, ghidra_sig_params, reconcile_sizes

from ghidra.program.model.data import StructureDataType, CategoryPath
from ghidra.program.model.symbol import SourceType
try:
    from ghidra.program.model.data import ParameterDefinitionImpl
except ImportError:
    from ghidra.program.model.listing import ParameterDefinitionImpl
from ghidra.program.model.data import (PointerDataType, VoidDataType, IntegerDataType,
    UnsignedIntegerDataType, FloatDataType, DoubleDataType, CharDataType, ByteDataType)

_PRIM = {'void': VoidDataType, 'int': IntegerDataType, 'unsigned int': UnsignedIntegerDataType,
         'float': FloatDataType, 'double': DoubleDataType, 'char': CharDataType,
         'byte': ByteDataType, 'undefined': ByteDataType}

def resolve_dt(dtm, name):
    n = (name or 'undefined').strip().rstrip(' *').strip()
    if n in _PRIM:
        return _PRIM[n]()
    dt = dtm.getDataType('/annotations/' + n) or dtm.getDataType('/' + n) or dtm.getDataType(n)
    return dt or ByteDataType()

def apply_plan(currentProgram, plan_path):
  plan = json.load(open(plan_path))
  fm = currentProgram.getFunctionManager()
  dtm = currentProgram.getDataTypeManager()
  af = currentProgram.getAddressFactory()

  def addr(s):
    return af.getAddress(s) if not s.startswith('0x') else af.getAddress(hex(int(s, 16)))

  # ---- 结构体两遍建 ----
  p1, p2 = partition_struct_passes([op for op in plan if op['kind'] == 'define_struct'])
  created = {}
  for s in p1:
    st = StructureDataType(CategoryPath('/annotations'), s['name'], 0)
    existing = dtm.getDataType('/annotations/' + s['name'])
    if existing is not None and hasattr(existing, 'deleteAll'):
        existing.deleteAll()          # 幂等：多轮重跑不得累积移位
        existing.setLength(s.get('size') or 0)
        created[s['name']] = existing
        continue
    if s.get('size'):
        st.setLength(s['size'])
    created[s['name']] = dtm.addDataType(st, None)
  for s in p2:
    st = created[s['name']]
    for m in s['members']:
        try:
            dt = dtm.getDataType('/annotations/' + str(m.get('type') or 'undefined'))
            if dt is None:
                dt = dtm.addDataType(StructureDataType(CategoryPath('/annotations'), str(m['type']), 4), None)
            st.replaceAtOffset(m['offset'], dt, dt.getLength(), m['name'], None)   # 覆盖式（insert=移位）
        except Exception as e:
            print('[apply_plan][member-skip] %s.%s @%d: %s' % (s['name'], m['name'], m['offset'], e))

  # ---- sizeof 对账（导入即校验）----
  obs = {n: created[n].getLength() for n in created}
  decl = {s['name']: s['size'] for s in p1 if s.get('size')}
  diffs = reconcile_sizes(decl, obs)
  if diffs:
    print('[apply_plan][SIZE-MISMATCH] %s' % diffs)
  else:
    print('[apply_plan][sizeof] reconcile OK (%d structs)' % len(decl))

  # ---- 符号/签名 ----
  named = sigd = 0
  for op in plan:
    if op['kind'] == 'set_name':
        a = addr(op['addr'])
        if a:
            currentProgram.getSymbolTable().createLabel(a, op['name'], SourceType.USER_DEFINED)
            named += 1
    elif op['kind'] == 'set_func_sig':
        a = addr(op['addr'])
        f = fm.getFunctionAt(a) if a else None
        if not f:
            continue
        params = ghidra_sig_params(op)
        try:
            from ghidra.program.model.listing import ParameterImpl
            pd = []
            for nm, ty in params:
                base = resolve_dt(dtm, ty)
                d = PointerDataType(base) if ty.endswith('*') else base
                pd.append(ParameterImpl(nm or None, d, prog if False else currentProgram))
            from ghidra.program.model.data import VoidDataType
            ret = resolve_dt(dtm, op.get('ret') or 'void')
            from ghidra.program.model.symbol import SourceType as _ST
            f.setReturnType(ret, _ST.USER_DEFINED)
            if pd:
                f.setArguments(pd)
            f.setCallingConvention('thiscall' if op.get('cls') and op.get('conv') == '__thiscall' else '__stdcall' if op.get('conv') == '__stdcall' else 'cdecl')
            sigd += 1
        except Exception as e:
            print('[apply_plan][sig-skip] %s: %s' % (op.get('name'), e))
    elif op['kind'] == 'define_global':
        a = addr(op['addr'])
        if a:
            currentProgram.getSymbolTable().createLabel(a, op['name'], SourceType.USER_DEFINED)
            named += 1

  print('[apply_plan] done: names=%d sigs=%d structs=%d' % (named, sigd, len(created)))

def main(argv):
    """pyghidraRun 驱动：argv = <projdir> <projname> <progpath> <plan.json>"""
    import pyghidra
    pyghidra.start()
    from ghidra.base.project import GhidraProject
    projdir, projname, progpath, plan_path = argv[1], argv[2], argv[3], argv[4]
    proj = GhidraProject.openProject(projdir, projname)
    _fp = progpath.rsplit('/', 1)
    _folder, _name = (_fp[0] or '/'), _fp[1]
    prog = proj.openProgram(_folder, _name, True)
    _tx = prog.startTransaction('apply_plan')
    try:
        _mismatch = apply_plan(prog, plan_path)
    finally:
        prog.endTransaction(_tx, True)
    # 验证合体：decompile 抽样验类型传播
    from ghidra.app.decompiler import DecompInterface
    from ghidra.util.task import ConsoleTaskMonitor
    di = DecompInterface(); di.openProgram(prog)
    af = prog.getAddressFactory(); fm = prog.getFunctionManager()
    import os as _os
    _out = (sys.argv[5] if len(sys.argv) > 5 else _os.path.join(_os.path.dirname(_os.path.abspath(__file__)), 'out', 'slice'))
    _os.makedirs(_out, exist_ok=True)
    n = 0
    fns = list(fm.getFunctions(True))
    for f in fns:
        r = di.decompileFunction(f, 30, ConsoleTaskMonitor())
        if r and r.decompileCompleted() and r.getDecompiledFunction().getC():
            c = r.getDecompiledFunction().getC()
            fn = ''.join(ch if ch.isalnum() else '_' for ch in f.getName())[:60]
            open(_os.path.join(_out, fn + '.c'), 'w').write(c)
            n += 1
    print('[verify] emitted %d decompiled units -> %s' % (n, _out))
    # 机读报告（e2e judge 消费）：sizeof 对账 + 出码计数 + 成员渲染抽样
    import json as _json
    rep = {'sizeof_mismatch': _mismatch, 'emitted_units': n, 'member_hits': []}
    for f in fns:
        try:
            r = di.decompileFunction(f, 30, ConsoleTaskMonitor())
            if r and r.decompileCompleted() and r.getDecompiledFunction():
                c = r.getDecompiledFunction().getC()
                if 'this->' in c or 'm_' in c:
                    rep['member_hits'].append({'fn': f.getName(), 'this_hits': c.count('this->')})
        except Exception:
            pass
    _json.dump(rep, open(_os.path.join(_out, '..', 'apply_report.json'), 'w'), indent=1)
    print('[verify] apply_report.json written')
    proj.save()
    proj.close()


if __name__ == '__main__':
    main(sys.argv)
