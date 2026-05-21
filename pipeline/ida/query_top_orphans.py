"""
IDAPython: 查询高频orphan ordinal的类型信息

用途：诊断最常见的orphan ordinal，找出它们为什么无法解析
"""
import ida_auto, ida_typeinf, json, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))

# 从export log统计的高频ordinal
TOP_ORPHANS = [115, 821, 116, 133, 105, 114, 101, 123, 129, 127, 136, 138]

def main():
    ida_auto.auto_wait()
    print("[*] Querying top orphan ordinals...")

    til = ida_typeinf.get_idati()
    if not til:
        print("[!] No TIL available")
        return

    results = []
    for ordinal in TOP_ORPHANS:
        info = {'ordinal': ordinal}

        # Method 1: 尝试获取类型名
        type_name = ida_typeinf.get_numbered_type_name(til, ordinal)
        info['type_name'] = type_name if type_name else None

        # Method 2: 尝试获取类型信息
        tif = ida_typeinf.tinfo_t()
        if tif.get_numbered_type(til, ordinal):
            info['get_numbered_type'] = 'SUCCESS'
            info['dstr'] = tif.dstr()
            info['size'] = tif.get_size()
            info['is_ptr'] = tif.is_ptr()
            info['is_struct'] = tif.is_struct()
            info['is_decl_struct'] = tif.is_decl_struct()

            # 如果是指针，获取指向的类型
            if tif.is_ptr():
                pointed = tif.get_pointed_object()
                info['pointed_to'] = pointed.dstr()
                info['pointed_size'] = pointed.get_size()
        else:
            info['get_numbered_type'] = 'FAILED'

        results.append(info)

        # 打印诊断信息
        print(f"\n=== Ordinal #{ordinal} ===")
        if type_name:
            print(f"  Type name: {type_name}")
        else:
            print(f"  Type name: NONE (orphan!)")

        if info.get('dstr'):
            print(f"  dstr: {info['dstr'][:100]}")
            if info.get('is_decl_struct'):
                print(f"  Status: FORWARD DECLARATION ONLY")
            elif info.get('is_struct'):
                print(f"  Status: COMPLETE STRUCT")
                print(f"  Size: {info['size']} bytes")
        else:
            print(f"  Status: COMPLETELY UNRESOLVED")

    # 保存结果
    output_file = os.path.join(SCRIPT_DIR, "_logs", "top_orphans.json")
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump({
            'orphans': results,
            'total_checked': len(TOP_ORPHANS)
        }, f, indent=2, ensure_ascii=False)

    print(f"\n[*] Results saved to: {output_file}")

    # 统计
    with_names = sum(1 for r in results if r.get('type_name'))
    forward_only = sum(1 for r in results if r.get('is_decl_struct'))
    complete = sum(1 for r in results if r.get('is_struct') and not r.get('is_decl_struct'))

    print(f"\n[*] Summary:")
    print(f"  Total checked: {len(TOP_ORPHANS)}")
    print(f"  With type names: {with_names}")
    print(f"  Forward decl only: {forward_only}")
    print(f"  Complete definitions: {complete}")
    print(f"  Completely unresolved: {len(TOP_ORPHANS) - with_names}")

if __name__ == "__main__":
    main()
    import ida_pro
    ida_pro.qexit(0)
