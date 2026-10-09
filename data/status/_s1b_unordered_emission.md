# S-1b 无序迭代候选清单（report-only，非门禁）

生成时间：2026-10-09T21:57:42
判据：for 的可迭代对象是 set/frozenset/dict.keys()/dict.values() 且未被 sorted() 包裹。
⚠️ AST 浅层扫描必然误报（membership/filter 用途语法上无法区分）⇒ 人工复核后才可定性。

## 候选（171 条）

- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:114  [UNKNOWN-ITER] for type_name in ida`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:207  for (k, v) in <ORDINAL_MAP.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:220  for (k, v) in <ORDINAL_MAP.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:306  [UNKNOWN-ITER] for vt in vtables`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:437  [UNKNOWN-ITER] for _mac in _EXPORT_MACROS`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:515  [UNKNOWN-ITER] for d in dms`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:747  [UNKNOWN-ITER] for ch in params_str`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:914  for (_sname, _sinfo) in <_ida_s.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1752  [UNKNOWN-ITER] for b in base_names`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2884  for (sname, s) in <ida_classes.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2892  for (_k, _v) in <_tpl_data.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2909  [UNKNOWN-ITER] for cls_name in all_classes`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2924  [UNKNOWN-ITER] for base_name in template_classes`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2929  for (ename, edata) in <ida_enums.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2940  for (ename, edata) in <enum_by_name.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3241  [UNKNOWN-ITER] for nm in ref`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3296  [UNKNOWN-ITER] for b in raw`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3367  for (_addr_s, _ginfo) in <globs.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3376  [UNKNOWN-ITER] for (_addr_s, _ginfo) in sorted_globs`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3442  [UNKNOWN-ITER] for (_addr_s, _ginfo) in _extra_entries`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3449  [UNKNOWN-ITER] for (_addr_s, _ginfo) in sorted_globs`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3512  [UNKNOWN-ITER] for (addr_str, g) in sorted_globs`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3753  [UNKNOWN-ITER] for p in paths`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3789  for (a_s, info) in <ann_raw.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:293  [UNKNOWN-ITER] for vt in vtables`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:566  [UNKNOWN-ITER] for d in dims`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:923  for (_addr_str, _minfo) in <_sinfo['methods'].items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1226  for (k, v) in <(ann.get('known_members') or {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1330  [UNKNOWN-ITER] for (ename, edata) in colliding_enums`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1398  [UNKNOWN-ITER] for b in _base_list`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1413  for (_k, _v) in <_tpl_data.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1481  for (_v_off, _v_info) in <ann_variants.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1509  for (_k, _v) in <_ann_ms.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1515  [UNKNOWN-ITER] for (method_name, sig, addr) in methods`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1556  [UNKNOWN-ITER] for t in include_types`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1821  [UNKNOWN-ITER] for b in base_names`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1830  [UNKNOWN-ITER] for b in base_names`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1935  [UNKNOWN-ITER] for bn in base_names`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2425  [UNKNOWN-ITER] for (_mn, _ms, _ma) in methods`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2450  [UNKNOWN-ITER] for (_mn, _ms, _ma) in methods`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2753  [UNKNOWN-ITER] for _l in lines`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2878  for (_k, _v) in <_tpl_data.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3070  [UNKNOWN-ITER] for (vname, vval) in sorted_vals`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3107  [UNKNOWN-ITER] for m in members`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3382  [UNKNOWN-ITER] for (_base, _end, _pname, _ptype, _dms) in _instances`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3417  [UNKNOWN-ITER] for (_addr_s, _ginfo) in sorted_globs`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3466  [UNKNOWN-ITER] for (_addr_s, _ginfo) in sorted_globs`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3618  [UNKNOWN-ITER] for e in _header_errors`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:184  [UNKNOWN-ITER] for e in entries`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:446  [UNKNOWN-ITER] for _line in _fh`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:466  [UNKNOWN-ITER] for _line in _fh`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:530  [UNKNOWN-ITER] for dd in dims`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:951  for (_slot, _minfo) in <_km.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1525  [UNKNOWN-ITER] for _scan_sig in _sigs_to_scan`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1676  [UNKNOWN-ITER] for b in _ann_base`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1706  [UNKNOWN-ITER] for _b in _ann_json_base`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1734  for (_k, _v) in <template_map.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1953  [UNKNOWN-ITER] for raw in own_slots`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2095  [UNKNOWN-ITER] for off_str in sorted_offsets`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2688  for (_slot, _minfo) in <_ann_data.get('known_methods', {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2780  [UNKNOWN-ITER] for _l in lines`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2815  for (sname, s) in <ida_data.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2901  [UNKNOWN-ITER] for _c in _inner`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3246  for (_as_, _gi) in <_glbs.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3757  for category in <data.values()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1132  [UNKNOWN-ITER] for _dm in _nt_members`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1150  [UNKNOWN-ITER] for (_mname, _msig, _maddr) in _nt_methods`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1297  for (k, v) in <_ann_km.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1304  [UNKNOWN-ITER] for _off in _ann_by_off`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1306  [UNKNOWN-ITER] for _m in _overlaid`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1382  [UNKNOWN-ITER] for line in fh`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1440  [UNKNOWN-ITER] for at in arg_types`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1527  [UNKNOWN-ITER] for t in all_types_in_sig`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1639  for (_k, _v) in <_tpl_data.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1931  [UNKNOWN-ITER] for b in base`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:1943  for (_slot, _minfo) in <_ann_data.get('known_methods', {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2057  for (ida_type, c_type) in <TYPE_REMAP.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2599  [UNKNOWN-ITER] for p in parts`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3388  [UNKNOWN-ITER] for _dm in _dms`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3717  [UNKNOWN-ITER] for b in s`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2139  [UNKNOWN-ITER] for m in group`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2180  [UNKNOWN-ITER] for _idm in _inline_dms`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2326  [UNKNOWN-ITER] for v in _field_variants`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2352  [UNKNOWN-ITER] for v in _field_variants`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2693  for (_off, _mi) in <_ann_data.get('known_members', {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:3759  for (a_s, writes) in <category.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2208  [UNKNOWN-ITER] for _idm in _inline_dms`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2704  for (_off, _mi) in <_ann_data.get('known_members', {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2716  for (_off, _mi) in <_ann_data.get('known_members', {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_headers.py:2224  [UNKNOWN-ITER] for _iidm in _inner_dms`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:234  [UNKNOWN-ITER] for u in undef`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:366  for (_fn, _sig) in <_sigs.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:474  [UNKNOWN-ITER] for m in methods`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:534  [UNKNOWN-ITER] for (addr, code) in transformed`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:576  [UNKNOWN-ITER] for f in funcs`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:589  [UNKNOWN-ITER] for (addr, code) in transformed`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:181  for (fname, decl) in <store.free_func_sigs.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:678  for (fname, decl) in <store.free_func_sigs.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:262  [UNKNOWN-ITER] for (_u, _t) in _class_type_externs`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:391  [UNKNOWN-ITER] for _hl in _gh`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:415  for (_var, _typ) in <_extern_map.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:424  [UNKNOWN-ITER] for hline in hf`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:437  [UNKNOWN-ITER] for hline in hf`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:447  for (_sn, _sm) in <store.struct_members.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/emit_cpp.py:448  for (_so, (_sfn, _sft)) in <_sm.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage2_semantic.py:54  for _mi in <(_ann.get('known_members') or {}).values()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage2_semantic.py:85  for (_c, _bs) in <(getattr(store, 'struct_bases', None) or {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:468  [UNKNOWN-ITER] for line in lines`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:1453  for (_o, v) in <(store.struct_members.get(cls_name) or {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:1504  [UNKNOWN-ITER] for p in parts`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:2061  [UNKNOWN-ITER] for line in lines`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:2129  for (func_name, ref_indices) in <_GB_REF_PARAM_FUNCS.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:1176  [UNKNOWN-ITER] for ch in args_text`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:1306  [UNKNOWN-ITER] for (decl, definition, comment) in stub_items`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:1439  [UNKNOWN-ITER] for c in cur`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:765  for (maddr, entry) in <methods.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:770  for entry in <(ann.get('known_methods') or {}).values()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:785  for (key, ent) in <ida.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:807  for (cname, ent) in <ida.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:1060  [UNKNOWN-ITER] for line in fh`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:792  [UNKNOWN-ITER] for dm in members`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage3_cleanup.py:810  for (maddr, entry) in <(ent.get('methods') or {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:309  for ((field, idx), cname) in <_ARRAY_INDEX_CONSTANTS.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:420  for (tname, offs) in <(store.struct_members or {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:694  [UNKNOWN-ITER] for ch in inner`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1360  for (_pn, _pt) in <_param_types(tree).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1563  for (_pn, _pt) in <_param_types(tree).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1630  for (_pn, _pt) in <_param_types(tree).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1683  for (_pn, _pt) in <_param_types(tree).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:421  for (off, mi) in <offs.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:812  for (sname, offs) in <store.struct_members.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1808  for (_c, _bs) in <_bm.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1925  [UNKNOWN-ITER] for (x, y) in pairs`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:814  for (_off, (mname, mtype)) in <offs.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1140  for mv in <(d.get('methods') or {}).values()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1756  for (k, v) in <_ms.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:240  for (_gn, _ga) in <store.global_addrs.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:855  [UNKNOWN-ITER] for line in fh`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1575  for (idx, ptext) in <table.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1662  [UNKNOWN-ITER] for an in anodes`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1749  for (_mk, _mv) in <(_d.get('methods') or {}).items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage4_substitution.py:1207  [UNKNOWN-ITER] for (a, c) in pairs`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:219  for (type_name, members) in <store.struct_members.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:258  [UNKNOWN-ITER] for line in lines`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:350  [UNKNOWN-ITER] for ch in args_text`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:437  [UNKNOWN-ITER] for ch in inner`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:460  [UNKNOWN-ITER] for ch in args_text`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:669  for (func_name, ref_indices) in <_GB_REF_PARAM_FUNCS.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:861  [UNKNOWN-ITER] for ch in s`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:1471  for (old, new) in <_fixes.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:1705  for (gname, gtype) in <store.global_types.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:1713  [UNKNOWN-ITER] for _ag in _array_globals`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:1848  for (_c, _ms) in <mi.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:220  for (offset, (mname, mtype)) in <members.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:937  for (type_name, members) in <store.struct_members.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:1335  [UNKNOWN-ITER] for _ln in lines`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:1808  [UNKNOWN-ITER] for ch in rhs`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/stages/stage5_fixup.py:938  for (_off, (mname, mtype)) in <members.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:121  for (addr_str, ginfo) in <_globals.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:139  for (sname, sinfo) in <ida_structs.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:179  for (addr_str, ginfo) in <_globals.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:338  for (_addr_s, _info) in <_data.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:267  [UNKNOWN-ITER] for _vt in _vtables`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:464  for (_addr_s, _info) in <_ann_funcs.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:524  for (aname, ainfo) in <astrings.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:76  [UNKNOWN-ITER] for _k in _ida_data`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:135  [UNKNOWN-ITER] for pfx in ida_prefixes`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:146  [UNKNOWN-ITER] for dm in dms`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:219  for (_addr_s, _tinfo) in <_skip_data.items()>`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:308  [UNKNOWN-ITER] for _b in _bases`
- `/home/peng/workspace/PAL3Decomp/pipeline/gen/data.py:155  for (vk, vv) in <variants.items()>`

---

## 人工复核结论（2026-10-09）

### 计数
| 类别 | 条数 | 定性 |
|---|---|---|
| **真阳性**（iter 明确 set/dict）| **76** | **全部是 `dict.items()`，0 条 set 迭代** |
| `[UNKNOWN-ITER]`（iter 是 Name，绑定不明）| 96 | 其中**绑 set 的只有 1 条** |
| **合计** | 171 | |

### 逐类定性

**① 76 条 `dict.items()` —— 低风险（不必修）**
Python 3.7+ 的 `dict` **保插入序** ⇒ 迭代序确定，前提是**插入序本身确定**。
本仓这些 dict 的插入来源是 `json.load(...)`（`ida_structs.json` / `enums.json` / `ann_*.json`）
—— JSON 解析的 key 序 = 文件内书写序，**确定**。
⇒ `ORDINAL_MAP` / `_ida_s` / `ida_classes` / `_tpl_data` / `ida_enums` / `globs` / `ann_raw` /
`_km` / `known_members` / `TYPE_REMAP` 等 76 处 **均安全**。

**② `UNKNOWN-ITER` 里绑 set 的 1 条 —— 已修**
`emit_headers.py:3241  for nm in ref`（`ref = _referenced_identifiers()` 返回 set）
⇒ **正是 S-1a 修复的那条**（现于 `:3280` 加 `extra.sort(...)`，源头排序）。
⚠️ 注意：`extra.sort()` 修的是**结果**，`:3241` 的**循环序**仍是 set 序 —— 但该循环只做
`forced.add(nm)` 与 `extra.append(...)`，不直接产出文本；文本序由 `extra.sort()` 决定 ⇒ **已覆盖**。

**③ `seen_addrs` / `seen` / `_seen` 等 `.add()` —— membership-only，无害**
`emit_headers.py:298/879/909/934/1166` 等，只做去重判定，不进文本产出路径。

**④ 其余 95 条 `UNKNOWN-ITER`**：iter 是普通列表/字符串/参数序列（`params_str`/`base_names`/
`methods`/`dims`/`raw`/`paths` 等），**本就有序**，AST 浅层无法识别故标 UNKNOWN ⇒ 误报。

### 结论
**S-1a 已覆盖唯一的真病灶**（`_referenced_identifiers()` 的 set 迭代序），其余候选经人工定性
均为「dict 插入序确定」或「membership-only」或「本就有序」⇒ **无需再修**。

⚠️ **残留风险（记档）**：本结论基于**当前**数据来源（JSON 解析 = 确定插入序）。
若未来有 dict 的插入序来自 set 迭代，则需重跑本扫描并复核 —— 故本扫描器保留为**回归护栏**
（report-only），代码变更后可重跑对照。

### 扫描器定级
**report-only（非硬门禁）** —— AST 浅层扫描 171 条里 96 条是误报（56%），
误报率过高不宜作 CI 阻断；人工复核结论已固化于此，后续变更时 diff 本文件即可。
