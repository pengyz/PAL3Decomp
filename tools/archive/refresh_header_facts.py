#!/usr/bin/env python3
"""header_facts 缓存增量刷新（2026-11-09）。

背景：缓存由 pipeline/ida/export_full.py 全量 export 末尾物化。本轮 loop 跑的
增量 export 更新了 decomp JSON（新引用 dword_56F22C 等）但**没刷新缓存**
（缓存 10-10 vs decomp 11-09，差一个月）→ emit_headers 的 forced_global_names
缺新引用 → globals.h 不发 extern → C2065（SystemUI dword_56F22C 实证）。

本工具复用 emit_headers 的扫描 impl（纯 decomp 目录文件扫描，IDA 外可跑）
重算 4 字段并物化。与全量 export 的写入器同一代码路径（S0 语义保持）。
"""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'pipeline', 'gen'))

def main():
    from pipeline.gen.stages import emit_headers as eh
    # 扫描 impl 用模块级集合作累加器，先清零（与 export_full 的写入器同款）
    eh._scalar_dtor_classes = set()
    eh._underscore_aliases = {}
    facts = {
        'scalar_dtor_classes': set(eh._get_scalar_dtor_classes_scan_impl()),
        'underscore_aliases': dict(eh._get_underscore_aliases_scan_impl()),
        'forced_global_names': set(eh._referenced_identifiers()),
        'vptr_inject_classes': set(eh._get_scalar_dtor_classes_scan_impl()),
    }
    eh.save_header_facts(facts)
    print('header-facts cache refreshed: %d scalar_dtor / %d aliases / %d forced'
          % (len(facts['scalar_dtor_classes']), len(facts['underscore_aliases']),
             len(facts['forced_global_names'])))
    # 新引用抽查
    for probe in ('dword_56F22C', 'pszRoleDir', 'UIParticle'):
        print('  %s in forced: %s' % (probe, probe in facts['forced_global_names']))

if __name__ == '__main__':
    main()
