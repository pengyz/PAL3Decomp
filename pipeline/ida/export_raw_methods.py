"""
导出 raw IDB 中特定方法的反编译代码
用于对比 raw 和 work IDB 的字段偏移差异
"""
import idaapi
import idc
import ida_hexrays
import json
import sys

def export_method(ea, output_dict):
    """导出单个方法的反编译代码"""
    func = idaapi.get_func(ea)
    if not func:
        return

    func_name = idc.get_func_name(ea)

    # 尝试反编译
    try:
        cfunc = ida_hexrays.decompile(func)
        if cfunc:
            decompiled = str(cfunc)
            output_dict[func_name] = {
                'address': f'0x{ea:08X}',
                'decompiled': decompiled[:5000]  # 限制长度
            }
            print(f'✓ {func_name} @ 0x{ea:08X}')
    except Exception as e:
        print(f'✗ {func_name} @ 0x{ea:08X}: {e}')

def main():
    # 目标方法地址（从 work IDB 的 functions.json 中获取）
    target_methods = {
        # UIFrameWnd 构造函数（包含 m_nChildren 等字段的初始化）
        'UILoadingFrm_ctor': 0x0052DE00,
        # CCBStageScene 方法（包含向量运算字段）
        'CCBStageScene_method1': 0x004D4F60,
        'CCBStageScene_method2': 0x004D5480,
        # UIListBox 方法
        'UIListBox_UpdateKeyCtrl': 0x0043E210,
    }

    output = {}

    for name, ea in target_methods.items():
        export_method(ea, output)

    # 保存到文件
    output_path = 'pipeline/ida/_logs/raw_idb_methods.json'
    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(output, f, indent=2, ensure_ascii=False)

    print(f'\n导出完成: {len(output)} 个方法')
    print(f'输出: {output_path}')

    idc.qexit(0)

if __name__ == '__main__':
    idaapi.auto_wait()
    main()
