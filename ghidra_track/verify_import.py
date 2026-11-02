# 导入验证：结构对账 + decompile 抽样验类型传播（this->member 渲染=导入成功判据）
import json, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(getSourceFile().getAbsolutePath())))
from import_annotation import reconcile_sizes
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

dtm = currentProgram.getDataTypeManager()
decl = json.load(open(getScriptArgs()[0])) if getScriptArgs() else {}
obs = {}
for n in ('UIWnd', 'UIListBox', 'UIScrollBar'):
    dt = dtm.getDataType('/annotations/' + n) or dtm.getDataType(n)
    if dt:
        obs[n] = dt.getLength()
print('[verify] struct sizes:', obs)
print('[verify] SIZE-MISMATCH:', reconcile_sizes({'UIWnd': decl.get('UIWnd'), 'UIListBox': decl.get('UIListBox')} if decl else {}, obs))

di = DecompInterface(); di.openProgram(currentProgram)
fm = currentProgram.getFunctionManager()
af = currentProgram.getAddressFactory()
hits = 0
for want in ('0x0043DE90', '0x0043E520', '0x00445B90'):
    a = af.getAddress(hex(int(want, 16)))
    f = fm.getFunctionAt(a)
    if not f:
        print('[verify] no func at', want); continue
    r = di.decompileFunction(f, 30, ConsoleTaskMonitor())
    if r and r.decompileCompleted():
        c = r.getDecompiledC()
        member_hits = c.count('->') + c.count('.')
        print('[verify] %s (%s): member-access marks=%d' % (want, f.getName(), member_hits))
        for line in c.splitlines():
            if 'this->' in line or 'm_' in line:
                print('   |', line.strip()[:90]); hits += 1
                if hits > 8: break
    else:
        print('[verify] decompile failed', want)
