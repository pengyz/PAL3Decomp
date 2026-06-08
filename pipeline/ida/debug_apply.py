import os, sys
LOG = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_logs", "debug_apply.txt")
os.makedirs(os.path.dirname(LOG), exist_ok=True)
with open(LOG, "w") as f:
    f.write(f"__file__={__file__}\n")
    f.write(f"cwd={os.getcwd()}\n")
    f.write(f"sys.path={sys.path}\n")
import idc
idc.qexit(0)
