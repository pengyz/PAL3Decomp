#!/usr/bin/env python3
"""基于 xref 二进制证据，把 25 张明确归属的虚表写回 struct 文件。

用法: python3 pipeline/apply_vtable_evidence.py
"""
import json, os, sys, re

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STRUCTS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")

# 从 git 历史恢复的 vtable slot 数据
VTABLES_RESTORED = "/tmp/vtables_restored.json"

# 基于证据的决策: (vtable_addr, target_class, decision_type)
# decision_type: 'move' = 迁移到新类, 'add_back' = 加回原类二级表
DECISIONS = [
    ("0x005705D0", "CCBStage", "move"),         # CCBProtectWindow -> CCBStage
    ("0x0056B22C", "CCBUIPanel", "add_back"),
    ("0x0056FADC", "CEffect", "add_back"),
    ("0x0056F844", "CEffectSystem", "add_back"),
    ("0x0056AC4C", "PalScript", "add_back"),
    ("0x0056F5E4", "RenderTarget2", "add_back"),
    ("0x0056F674", "RenderTarget2", "add_back"),
    ("0x0056F6C8", "RenderTarget2", "add_back"),
    ("0x0056F71C", "RenderTarget2", "add_back"),
    ("0x0056F768", "RenderTarget2", "add_back"),
    ("0x0056F774", "RenderTarget2", "add_back"),
    ("0x0056AAD8", "RoleSystem", "add_back"),
    ("0x0056AAE4", "RoleSystem", "add_back"),
    ("0x0056AAF0", "RoleSystem", "add_back"),
    ("0x0056AE64", "UIFrameWnd", "add_back"),
    ("0x0056AD20", "UIListBox", "add_back"),
    ("0x0056B178", "UIListBox", "add_back"),
    ("0x0056B1BC", "UIListBox", "add_back"),
    ("0x005706EC", "UIListBox", "add_back"),
    ("0x0056AC70", "UICaption", "move"),          # UIScene -> UICaption
    ("0x0056AFFC", "UIScenePanel", "add_back"),
    ("0x0056AE48", "UIStatic", "add_back"),
    ("0x0056AFB0", "UIWnd", "move"),              # UIStatic -> UIWnd
    ("0x0056AEC8", "UIWnd", "add_back"),
]

def load_struct(cls_name):
    p = os.path.join(STRUCTS_DIR, "%s.json" % cls_name)
    if not os.path.exists(p):
        return None
    return json.load(open(p, encoding='utf-8'))

def save_struct(cls_name, data):
    p = os.path.join(STRUCTS_DIR, "%s.json" % cls_name)
    with open(p, 'w', encoding='utf-8') as f:
        json.dump(data, f, ensure_ascii=False, indent=2)

def main():
    vtables = json.load(open(VTABLES_RESTORED, encoding='utf-8'))
    functions = json.load(open(os.path.join(ANNOTATIONS_DIR, "functions.json"), encoding='utf-8'))
    
    # 按目标类聚合 vtable 地址
    by_target = {}
    for vaddr, target, dtype in DECISIONS:
        by_target.setdefault(target, []).append(vaddr)
    
    for target_cls, vaddrs in sorted(by_target.items()):
        sd = load_struct(target_cls)
        if sd is None:
            print("[!] %s.json not found, cannot apply vtables" % target_cls)
            continue
        
        # 从 restored vtables.json 找每个 vtable 的 slot 数据
        new_vtables = sd.get('vtables', [])
        existing_addrs = set(vt['addr'] for vt in new_vtables)
        methods = sd.setdefault('methods', {})
        
        for vaddr in vaddrs:
            if vaddr in existing_addrs:
                print("  %s @%s already has vtable, skip" % (target_cls, vaddr))
                continue
            
            # 在 restored vtables 里找这个地址
            vt_entry = None
            for sym, info in vtables.items():
                if info.get('address') == vaddr:
                    vt_entry = info
                    break
            
            if vt_entry is None:
                print("[!] vtable %s not found in restored data" % vaddr)
                continue
            
            slots = []
            for vm in vt_entry.get('methods', []):
                addr = vm.get('address', '')
                slot_name = vm.get('name', '')
                # 判继承关系
                owner = None
                if '::' in slot_name:
                    cls_part = slot_name.split('::')[0]
                    if cls_part != target_cls:
                        owner = cls_part
                
                # 确保该地址在 methods 里有条目
                if addr not in methods and owner is None and addr:
                    # 查 functions.json
                    fn_entry = functions.get(addr, {})
                    sig = fn_entry.get('signature', vm.get('signature', ''))
                    raw_name = fn_entry.get('name', slot_name)
                    short = raw_name.split('::')[-1] if '::' in raw_name else raw_name
                    if addr and short and not short.startswith('sub_') and not short.startswith('loc_'):
                        methods[addr] = {
                            'name': short,
                            'signature': sig,
                            'source': 'vtable_evidence',
                        }
                
                slots.append({"addr": addr, "from": owner})
            
            new_vtables.append({"addr": vaddr, "base": None, "slots": slots})
            print("  + %s @%s (%d slots)" % (target_cls, vaddr, len(slots)))
        
        sd['vtables'] = new_vtables
        save_struct(target_cls, sd)
    
    print("\n完成。已更新 %d 个 struct 文件。" % len(by_target))


if __name__ == '__main__':
    main()
