import ida_auto, ida_typeinf, idc, os
ida_auto.auto_wait()
sd = os.path.dirname(os.path.abspath(__file__))
til = ida_typeinf.get_idati()
results = []
for name in ['ARC_PlayerAtt', 'RoleSystem', 'SceneMgrCamBlock', 'SceneMgr']:
    tinfo = ida_typeinf.tinfo_t()
    if tinfo.get_named_type(til, name):
        results.append('%s: size=%d (0x%X)' % (name, tinfo.get_size(), tinfo.get_size()))
    else:
        results.append('%s: NOT FOUND' % name)
with open(os.path.join(sd, chr(95) + 'logs', 'struct_sizes.txt'), 'w') as f:
    f.write(chr(10).join(results))
idc.qexit(0)
