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

from ghidra.program.model.data import StructureDataType, CategoryPath, UnionDataType
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
    raw = (name or 'undefined').strip()
    is_ptr = raw.endswith('*')
    n = raw.rstrip(' *').strip()
    if n in _PRIM:
        base = _PRIM[n]()
    else:
        dt = dtm.getDataType('/annotations/' + n) or dtm.getDataType('/' + n) or dtm.getDataType(n)
        base = dt or ByteDataType()
    # [void* 修 2026-11-03] 指针类型必须包装 PointerDataType
    return PointerDataType(base) if is_ptr else base


def _sanitize_name(name):
    """清理符号名：反引号/空格/特殊字符→合法 Ghidra 标识符。"""
    import re as _re
    # 反引号特名 → _scalar_dtor / _vector_dtor 形
    n = (name or '')
    if n.startswith('`') and n.endswith("'"):
        if 'deleting' in n:
            n = '_vector_dtor' if 'vector' in n else '_scalar_dtor'
        else:
            n = n.strip('`').strip("'")
    # 非法字符 → _
    n = _re.sub(r'[^A-Za-z0-9_@?$:]', '_', n)
    # 确保不以数字开头
    if n and n[0].isdigit():
        n = '_' + n
    return n or '_unnamed'

def apply_plan(currentProgram, plan_path):
  plan = json.load(open(plan_path))
  fm = currentProgram.getFunctionManager()
  dtm = currentProgram.getDataTypeManager()
  af = currentProgram.getAddressFactory()

  def addr(s):
    return af.getAddress(s) if not s.startswith('0x') else af.getAddress(hex(int(s, 16)))

  # ---- 结构体两遍建 ----
  p1, p2 = partition_struct_passes([op for op in plan if op['kind'] == 'define_struct'])
  # union 建型（define_union 先于 pass2 引用）
  for op in plan:
      if op.get('kind') == 'define_union':
          if dtm.getDataType('/annotations/' + op['name']) is not None:
              continue
          u = dtm.addDataType(UnionDataType(CategoryPath('/annotations'), op['name']), None)
          for um in op.get('members') or []:
              u.add(resolve_dt(dtm, str(um.get('type') or 'int')), um.get('name') or 'u', None)
  created = {}
  for s in p1:
    st = StructureDataType(CategoryPath('/annotations'), s['name'], s.get('size') or 0)
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
    # [sizeof 对齐修 2026-11-03] 成员插入后强制设长度=declared size
    # （MSVC6 /Zp1 真实大小；Ghidra 默认会加尾部 padding）
    if s.get('size'):
        try:
            st.setLength(s['size'])
        except Exception:
            pass  # setLength 只能增长不能收缩，接受 Ghidra padding

  # ---- sizeof 对账（导入即校验）----
  obs = {n: created[n].getLength() for n in created}
  decl = {s['name']: s['size'] for s in p1 if s.get('size')}
  diffs = reconcile_sizes(decl, obs)
  _mismatch = {k: {'declared': v[0], 'observed': v[1]} for k, v in diffs.items()}
  if diffs:
    print('[apply_plan][SIZE-MISMATCH] %s' % diffs)
  else:
    print('[apply_plan][sizeof] reconcile OK (%d structs)' % len(decl))

  # ---- 符号/签名 ----
  named = sigd = 0
  for op in plan:
    if op['kind'] not in ('set_name', 'set_func_sig', '_meta', 'define_global', 'define_struct', 'define_union'):
        raise RuntimeError('未知 op 禁静默跳过: %r' % (op.get('kind'),))   # [G8]
    if op['kind'] == 'set_name':
        a = addr(op['addr'])
        if a:
            currentProgram.getSymbolTable().createLabel(a, _sanitize_name(op['name']), SourceType.USER_DEFINED)
            named += 1
    elif op['kind'] == 'set_func_sig':
        a = addr(op['addr'])
        f = fm.getFunctionAt(a) if a else None
        if not f:
            _nf = globals().setdefault('_nofunc', [])
            _nf.append(op.get('name'))
            continue
        params = ghidra_sig_params(op)
        try:
            from ghidra.program.model.listing import ParameterImpl, Function
            from ghidra.program.model.symbol import SourceType as _ST
            from java.util import ArrayList
            pd = []
            for nm, ty in params:
                base = resolve_dt(dtm, ty)
                d = PointerDataType(base) if ty.endswith('*') else base
                pd.append(ParameterImpl(nm or None, d, currentProgram))
            ret = resolve_dt(dtm, op.get('ret') or 'void')
            f.setReturnType(ret, _ST.USER_DEFINED)
            if pd:
                # [根因修 2026-11-02] varargs 形静默错绑（JPype）——ArrayList 结构形；
                # thiscall 的 this 变量独立于 formals ⇒ setThis 绑型
                # [T3 修] setThis 不存在（复核 L9）；this 以首 formal 保留
                # （剔除致 this 塌寄存器 in_RSI+偏移错位——新鲜会话 T3 实证）
                formals = pd
                if formals:
                    _lst = ArrayList()
                    for _v in formals:
                        _lst.add(_v)
                    f.replaceParameters(_lst, Function.FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS,
                                        False, _ST.USER_DEFINED)
            f.setCallingConvention('__thiscall' if op.get('cls') and op.get('conv') == '__thiscall' else '__stdcall' if op.get('conv') == '__stdcall' else '__cdecl')
            sigd += 1
        except Exception as e:
            print('[apply_plan][sig-skip] %s: %s' % (op.get('name'), e))
    elif op['kind'] == 'define_global':
        a = addr(op['addr'])
        if a:
            currentProgram.getSymbolTable().createLabel(a, _sanitize_name(op['name']), SourceType.USER_DEFINED)
            named += 1

  # 读回验证：成员命名/union 落型（探针级证据入报告）
  _verify = {}
  for _n, _st in created.items():
      try:
          _verify[_n] = [(c.getFieldName(), c.getOffset()) for c in _st.getComponents()]
      except Exception as _e:
          _verify[_n] = 'ERR:%s' % _e
  _u = dtm.getDataType('/annotations/UNION_Complex_16')
  print('[apply_plan] done: names=%d sigs=%d structs=%d union=%s nofunc=%s' % (named, sigd, len(created), bool(_u), globals().get('_nofunc')))
  print('[apply_plan][verify-comps] %s' % _verify)
  return _mismatch, _verify

def main(argv):
    """pyghidraRun 驱动：argv = <projdir> <projname> <progpath> <plan.json>"""
    import pyghidra
    pyghidra.start()
    from ghidra.base.project import GhidraProject
    projdir, projname, progpath, plan_path = argv[1], argv[2], argv[3], argv[4]
    proj = GhidraProject.openProject(projdir, projname)
    _fp = progpath.rsplit('/', 1)
    _folder, _name = (_fp[0] or '/'), _fp[1]
    prog = proj.openProgram(_folder, _name, False)   # readOnly=False（第三参=readOnly——True=DomainFileProxy 脱钩副本，持久化死根因）
    _tx = prog.startTransaction('apply_plan')
    try:
        _mismatch, _verify = apply_plan(prog, plan_path)
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
    rep = {'sizeof_mismatch': _mismatch, 'verify_comps': _verify, 'emitted_units': n, 'member_hits': [], 'verify_comps': _verify}
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
    proj.save(prog)   # 单通道（复核定谳：prog.save 回退双死，已删）
    proj.close()


if __name__ == '__main__':
    main(sys.argv)
