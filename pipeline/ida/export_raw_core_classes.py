"""
从 raw IDB 导出核心类的构造函数和关键方法
用于验证字段偏移和类型
"""
import idaapi
import idc
import ida_hexrays
import json
import sys

def export_method(ea, method_name, output_dict):
    """导出单个方法的反编译代码"""
    func = idaapi.get_func(ea)
    if not func:
        print(f'✗ {method_name} @ 0x{ea:08X}: 未找到函数')
        return False

    try:
        cfunc = ida_hexrays.decompile(func)
        if cfunc:
            decompiled = str(cfunc)
            output_dict[method_name] = {
                'address': f'0x{ea:08X}',
                'decompiled': decompiled[:10000]  # 增加长度限制
            }
            print(f'✓ {method_name} @ 0x{ea:08X}')
            return True
    except Exception as e:
        print(f'✗ {method_name} @ 0x{ea:08X}: {e}')

    return False

def main():
    # 核心类的构造函数和关键方法
    # 地址从 work IDB 的 functions.json 或 vtables.json 获取
    target_methods = {
        # Camera 类
        'Camera_ctor': 0x0041AF30,
        'Camera_Init': 0x0041B370,
        'Camera_Update': 0x0041BEC0,

        # SceneMgr 类（需要先找到全局实例，然后找方法）
        # 'SceneMgr_ctor': 0x00000000,  # TODO: 找到地址

        # CCBStage 类
        'CCBStage_ctor': 0x004D1FE0,
        'CCBStage_Init': 0x004D3540,

        # CCBStageScene 类
        'CCBStageScene_ctor': 0x004D4F60,
        'CCBStageScene_method1': 0x004D6D70,
        'CCBStageScene_method2': 0x004D7340,

        # CCBCamControl 类
        'CCBCamControl_ctor': 0x00507DF0,
        'CCBCamControl_Update': 0x00508140,

        # UIWnd 类
        'UIWnd_ctor': 0x00441C90,

        # UIListBox 类
        'UIListBox_ctor': 0x0043DCE0,
        'UIListBox_SetSelTexture': 0x0043E050,

        # UIFrameWnd 类（已导出，但再导出一个方法作为补充）
        'UIFrameWnd_Create': 0x00442370,
    }

    output = {}
    success_count = 0

    print(f'开始导出 {len(target_methods)} 个方法...\n')

    for name, ea in target_methods.items():
        if ea == 0:
            print(f'⊘ {name}: 地址未知，跳过')
            continue

        if export_method(ea, name, output):
            success_count += 1

    # 保存到文件
    output_path = 'pipeline/ida/_logs/raw_core_classes.json'
    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(output, f, indent=2, ensure_ascii=False)

    print(f'\n导出完成: {success_count}/{len(target_methods)} 个方法')
    print(f'输出: {output_path}')

    idc.qexit(0)

if __name__ == '__main__':
    idaapi.auto_wait()
    main()
