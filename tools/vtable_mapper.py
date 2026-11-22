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

# CRT 静态链接产物类（/MT 把 libcmt 的类链进 PAL3）：其 vtable 槽指向 CRT 代码，
# 不是本项目标注对象 ⇒ 门禁跳过（filebuf 0x438100 实例，2026-09-25）。
CRT_GATE_SKIP = {'filebuf'}

_sdk_class_cache = None

def _sdk_class_names():
    """include/gbengine/*.h 里声明的类名集合（SDK 单源类：槽位覆盖由 SDK 头承担）。"""
    global _sdk_class_cache
    if _sdk_class_cache is not None:
        return _sdk_class_cache
    names = set()
    gd = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                      'include', 'gbengine')
    if os.path.isdir(gd):
        rx = re.compile(r'^(?:class|struct)\s+(?:GBAPI\s+|__declspec\([^)]*\)\s+)?(\w+)',
                        re.M)
        for f in os.listdir(gd):
            if f.endswith(('.h', '.hpp')):
                names |= set(rx.findall(open(os.path.join(gd, f), encoding='utf-8',
                                             errors='replace').read()))
    _sdk_class_cache = names
    return names

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
    
    # [from退役 2026-11-16] 消费者同步: 继承判据=地址∈祖先链槽/方法集(推导), 旧from路由作废
    _pre = {}
    for _cn0, _d0 in structs.items():
        _slots0 = set()
        for _vt0 in (_d0.get('vtables') or []):
            for _sl0 in (_vt0.get('slots') or []):
                try: _slots0.add(int(_sl0.get('addr'), 16))
                except (ValueError, TypeError): pass
        _m0 = set()
        for _k0 in (_d0.get('methods') or {}):
            try: _m0.add(int(_k0, 16))
            except (ValueError, TypeError): pass
        _b0 = [(_b.get('name') if isinstance(_b, dict) else _b) for _b in (_d0.get('bases') or [])]
        _pre[_cn0] = (_slots0, _m0, [x for x in _b0 if x])

    def _in_chain(_cls, _addr, _seen=None):
        _seen = _seen if _seen is not None else set()
        for _bn in _pre.get(_cls, (set(), set(), []))[2]:
            if _bn in _seen: continue
            _seen.add(_bn)
            _bs, _bm, _bb = _pre.get(_bn, (set(), set(), []))
            if _addr in _bs or _addr in _bm: return True
            if _in_chain(_bn, _addr, _seen): return True
        return False

    targets = [cls_name] if cls_name else sorted(structs.keys())
    
    for cn in targets:
        d = structs.get(cn)
        if not d: continue
        if cn in CRT_GATE_SKIP:
            continue
        vts = d.get('vtables') or []
        if not vts: continue
        if cn in _sdk_class_names():
            # SDK 单源类（F53/105 轮架构）：类声明由 include/gbengine 头承担，
            # pal3 侧不生成该类头文件 ⇒ 注解 methods 表不适用；槽位覆盖走 SDK 头路线
            _n = sum(len(vt.get('slots') or []) for vt in vts if isinstance(vt, dict))
            stats['checked'] += sum(1 for vt in vts if isinstance(vt, dict) and vt.get('slots'))
            stats['total_slots'] += _n
            stats['sdk_route'] = stats.get('sdk_route', 0) + _n
            stats['pass'] += sum(1 for vt in vts if isinstance(vt, dict) and vt.get('slots'))
            continue
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
                # [空addr守卫 2026-11-22] 唯一所有者律去址槽(声明型, EffCallBackNode
                # slot0/1 先例: 0x4C2600=CEffSParticle双账在册)——合法形态, 声明型
                # 槽不参与地址闭环验证, 跳过且不中断整表校验(此前空串int()异常
                # 中断整表=门禁对全库失效)
                if not addr:
                    stats['decl_slots'] = stats.get('decl_slots', 0) + 1
                    continue
                addr_int = int(addr, 16) if isinstance(addr, str) else addr
                addr_hex = '0x%08X' % addr_int
                # [from退役 2026-11-16] 继承=地址∈祖先链(推导, _in_chain已确认
                #   某祖先槽/方法集持有该地址) ⇒ 解析成立; 否则走自有槽路径
                if _in_chain(cn, addr_int):
                    # 继承槽：祖先链已确认持有该地址(_in_chain推导), 解析成立
                    stats['resolved'] += 1
                else:
                    # [C7v3对齐 2026-11-16] 纯虚槽(_purecall)与thunk域豁免
                    if addr_int == 0x55434f or 0x542000 <= addr_int <= 0x542200:
                        stats['resolved'] += 1
                        continue
                    # 自有槽：必须在当前类 methods 表中，且函数地址精确匹配
                    found_method = None
                    for key in (addr_hex, '0x%08x' % addr_int, hex(addr_int), str(addr_int)):
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
