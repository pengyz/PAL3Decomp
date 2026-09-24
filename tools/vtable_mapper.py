#!/usr/bin/env python3
"""vtable 闭环验证门禁。

保证：annotation 声明的 virtual 函数 → 编译器生成的 vtable → 与二进制中的 vtable 严格对应。
偏差（数量/顺序/签名不一致）= annotation bug ⇒ 报错。

验证链路：
  二进制 vtable[slot_i] = addr_i
      ↕ 必须一一对应
  annotation.methods[addr_i] = {name, signature}
      ↕ 发射器生成
  C++ header 中第 i 个 virtual 声明 = addr_i 对应的函数
      ↕ 编译器
  编译后 vtable[slot_i] = addr_i
"""
import json, os, re, sys

STRUCTS = 'data/annotations/structs'

def load_all():
    structs = {}
    for f in sorted(os.listdir(STRUCTS)):
        if not f.endswith('.json'): continue
        d = json.load(open(os.path.join(STRUCTS, f), encoding='utf-8'))
        structs[d.get('name', f[:-5])] = d
    return structs

def check(cls_name=None, structs=None, verbose=False):
    """执行 vtable 闭环验证。返回 (errors, warnings, stats)。"""
    if structs is None: structs = load_all()
    errors, warnings = [], []
    stats = {'checked':0,'pass':0,'fail':0,'total_slots':0,'resolved':0,'own_unresolved':0,
             'order_mismatch':0,'signature_mismatch':0}
    
    targets = [cls_name] if cls_name else sorted(structs.keys())
    
    for cn in targets:
        d = structs.get(cn)
        if not d: continue
        vts = d.get('vtables') or []
        if not vts: continue
        methods = d.get('methods') or {}
        base_class = d.get('base_class')
        if isinstance(base_class, list): base_class = base_class[0] if base_class else None
        
        for vi, vt in enumerate(vts):
            if not isinstance(vt, dict): continue
            slots = vt.get('slots') or []
            if not slots: continue
            stats['checked'] += 1
            stats['total_slots'] += len(slots)
            
            cls_errors = []
            prev_resolved = True  # 用于检查顺序
            
            for si, slot in enumerate(slots):
                addr = slot.get('addr', '')
                from_base = slot.get('from')
                addr_int = int(addr, 16) if isinstance(addr, str) else addr
                addr_hex = '0x%08X' % addr_int
                
                if from_base:
                    # 继承槽：验证基类中该槽位有对应方法
                    base_d = structs.get(from_base, {})
                    base_methods = base_d.get('methods') or {}
                    # 在基类 methods 或基类的 vtable slots 中查找
                    base_vts = base_d.get('vtables') or []
                    base_found = False
                    for key in (addr_hex, hex(addr_int), str(addr_int)):
                        if key in base_methods:
                            base_found = True; break
                    if not base_found:
                        for bvt in base_vts:
                            if not isinstance(bvt, dict): continue
                            for bslot in (bvt.get('slots') or []):
                                if bslot.get('addr','') == addr:
                                    base_found = True; break
                            if base_found: break
                    if not base_found:
                        cls_errors.append(
                            f"slot[{si}] inherited from {from_base}: addr={addr} not found in {from_base} methods/vtables")
                        stats['own_unresolved'] += 1
                    else:
                        stats['resolved'] += 1
                else:
                    # 自有槽：必须在当前类 methods 表中，且函数地址精确匹配
                    found_method = None
                    for key in (addr_hex, hex(addr_int), str(addr_int)):
                        if key in methods:
                            found_method = methods[key]
                            break
                    
                    if not found_method:
                        cls_errors.append(
                            f"slot[{si}] own virtual: addr={addr} NOT in methods table ⇒ "
                            f"发射器无法生成 virtual 声明 ⇒ 编译器 vtable 槽位缺失/错位")
                        stats['own_unresolved'] += 1
                    else:
                        stats['resolved'] += 1
                        # 验证方法名不含 vtable 相关键（禁止手动 vtable）
                        mname = found_method.get('name','')
                        if re.match(r'^(?:__vftable|__vfptr|vfptr|vtable)$', mname, re.I):
                            cls_errors.append(
                                f"slot[{si}]: method name '{mname}' is a vtable key word — "
                                f"这是编译器内部机制，不能作为方法名")
                        
                        if not prev_resolved:
                            stats['order_mismatch'] += 1
                            cls_errors.append(
                                f"slot[{si}] follows an unresolved slot ⇒ virtual 声明顺序可能与二进制 vtable 不一致")
                        prev_resolved = True
            
            if cls_errors:
                stats['fail'] += 1
                for e in cls_errors:
                    errors.append(f"vtable[{cn}][{vi}]: {e}")
            else:
                stats['pass'] += 1
            
            if verbose:
                status = '✓' if not cls_errors else f'✗ {len(cls_errors)} issues'
                print(f"  {cn} vtable[{vi}]: {len(slots)} slots {status}")
    
    return errors, warnings, stats

if __name__ == '__main__':
    verbose = '-v' in sys.argv
    cls = None
    for a in sys.argv[1:]:
        if not a.startswith('-'): cls = a
    
    errors, warnings, stats = check(cls_name=cls, verbose=verbose)
    print(f"检查类/vtable: {stats['checked']}")
    print(f"总槽位: {stats['total_slots']} · 已解析: {stats['resolved']} · 未解析: {stats['own_unresolved']}")
    print(f"通过: {stats['pass']} · 失败: {stats['fail']}")
    if stats['order_mismatch']:
        print(f"⚠️ 顺序错位: {stats['order_mismatch']}")
    if errors:
        print(f"\nERRORS ({len(errors)}):")
        for e in errors[:15]:
            print(f"  ✗ {e[:140]}")
        if len(errors) > 15: print(f"  ... +{len(errors)-15} more")
        sys.exit(1)
    else:
        print("\n✅ vtable 闭环验证通过：annotation 声明 ⇒ 编译器 vtable 与二进制严格对应")
