# fresh-session 渲染器（L-fresh 自动化）：独立进程重渲染全函数→<out>/slice_fresh/
# 用法: python3 render_fresh.py <projdir> <projname> <progpath> <out_dir>
import os, sys
os.environ.setdefault('GHIDRA_INSTALL_DIR', os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'tools', 'ghidra', 'ghidra_12.1.2_PUBLIC'))
import pyghidra
pyghidra.start()
from ghidra.base.project import GhidraProject
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
projdir, projname, progpath, outdir = sys.argv[1:5]
os.makedirs(outdir, exist_ok=True)
proj = GhidraProject.openProject(projdir, projname)
prog = proj.openProgram('/', progpath.lstrip('/'), False)
di = DecompInterface(); di.openProgram(prog)
n = 0
for f in prog.getFunctionManager().getFunctions(True):
    r = di.decompileFunction(f, 30, ConsoleTaskMonitor())
    if r and r.decompileCompleted() and r.getDecompiledFunction():
        fn = ''.join(ch if ch.isalnum() else '_' for ch in f.getName())[:60]
        open(os.path.join(outdir, fn + '.c'), 'w').write(r.getDecompiledFunction().getC())
        n += 1
proj.save(prog)
proj.close()
print('[render_fresh] %d units -> %s' % (n, outdir))
