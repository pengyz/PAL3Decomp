# ## [Ghidra headless postScript] 注解导入计划执行器（双轨 spec §4）
# 用法: analyzeHeadless <projdir> <projname> -import <PAL3.exe> \
#         -postScript ghidra_track/apply_plan.py ghidra_track/out/plan.json
# 两遍建结构 + thiscall 签名 + sizeof 对账（导入即校验）。纯逻辑在 import_annotation。
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(getSourceFile().getAbsolutePath())))
from import_annotation import partition_struct_passes, ghidra_sig_params, reconcile_sizes

from ghidra.program.model.data import StructureDataType, CategoryPath
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.listing import ParameterDefinitionImpl
from ghidra.program.model.data import PointerDataType

plan_path = getScriptArgs()[0]
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
            st.insertAtOffset(m['offset'], dt, dt.getLength())
            mem = st.getMemberAt(m['offset'])
            if mem:
                mem.setName(m['name'])
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
            pd = []
            for nm, ty in params:
                base = dtm.getDataType('/annotations/' + ty.rstrip(' *').strip()) or dtm.getDataType(ty.rstrip(' *').strip()) or dtm.getDataType('int')
                d = PointerDataType(base) if ty.endswith('*') else base
                pd.append(ParameterDefinitionImpl(nm or None, d, None))
            ret = dtm.getDataType(op.get('ret') or 'void') or dtm.getDataType('void')
            f.setSignature(ret, f.getCallingConventionName(), pd, SourceType.USER_DEFINED)
            sigd += 1
        except Exception as e:
            print('[apply_plan][sig-skip] %s: %s' % (op.get('name'), e))
    elif op['kind'] == 'define_global':
        a = addr(op['addr'])
        if a:
            currentProgram.getSymbolTable().createLabel(a, op['name'], SourceType.USER_DEFINED)
            named += 1

print('[apply_plan] done: names=%d sigs=%d structs=%d' % (named, sigd, len(created)))
