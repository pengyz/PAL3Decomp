"""
IDAPython: 为已导入的类型补上基类字段定义

问题: PDB 导入的结构体只有子类自有字段，基类部分是 _gap_0[N]。
解决: 用已知的基类定义(UIWnd等)重新生成完整结构体。

影响的类:
  - 所有 UI* 类 (基类 UIWnd, 68B)
  - SceneObj (基类 76B，字段待完善)

用法:
  在 IDA 中 File -> Script File -> 选择此脚本
  前提: 已运行过 ida_import_all.py 或 ida_import_P*.py
"""

import idc
import ida_typeinf
import ida_hexrays
import ida_struct
import idautils

# UIWnd 基类字段定义 (来自 PAL3patch 精确逆向，总计 68 bytes)
UIWND_FIELDS = """
struct UIWnd {
    void *__vfptr;
    unsigned int m_fontcolor;
    unsigned int m_wndcolor;
    unsigned int m_id;
    int m_rect_left;
    int m_rect_top;
    int m_rect_right;
    int m_rect_bottom;
    void *m_pfather;
    void *m_childs_pData;
    int m_childs_nSize;
    int m_childs_nMaxSize;
    int m_childs_nGrowBy;
    int m_bcreateok;
    int m_bvisible;
    int m_benable;
    int m_bfocus;
};
"""

# UI 子类列表 (基类是 UIWnd, gap_0 = 68 bytes)
UI_CLASSES_68 = [
    'UIStatic', 'UIButton', 'UIPushButton', 'UIListBox',
    'UIDragBar', 'UIProgressBar', 'UIMap', 'UI3DCtrl',
    'UIScrollBar', 'UITitle_JDHY', 'UITitle_YXXX',
    'UICheckButton', 'UIEditBox', 'UIRadioButton',
]


def get_struct_id(name):
    """获取 IDA 中结构体的 ID"""
    sid = ida_struct.get_struc_id(name)
    return sid


def patch_struct_gap(struct_name, base_fields):
    """
    将结构体的 _gap_0 替换为基类字段。

    方案: 删除旧类型定义，重新创建包含基类字段的版本。
    """
    til = ida_typeinf.get_idati()
    tif = ida_typeinf.tinfo_t()

    if not tif.get_named_type(til, struct_name):
        return False, f"{struct_name} 不存在"

    # 获取当前定义的 C 字符串
    c_str = tif.dstr()
    size = tif.get_size()

    return True, f"size={size}"


def main():
    print("=" * 60)
    print("[*] 补全基类字段: UIWnd → UI* 类")
    print("=" * 60)
    print()

    # Step 1: 先确保 UIWnd 类型存在
    til = ida_typeinf.get_idati()

    tif = ida_typeinf.tinfo_t()
    if not tif.get_named_type(til, "UIWnd"):
        print("[*] 定义 UIWnd 类型...")
        nerrors = idc.parse_decls(UIWND_FIELDS, idc.PT_TYP)
        if nerrors != 0:
            print(f"  [!] UIWnd 定义失败 (errors={nerrors})")
            return
        print("  [+] UIWnd 定义成功 (68 bytes)")
    else:
        print("[*] UIWnd 已存在")

    # Step 2: 遍历 UI 类，用 set_member_type 方式修改 _gap_0
    # IDA 中更可靠的方式是用 idc.SetType 直接重新设置整个结构
    print()
    print("[*] 修补 UI 类的 _gap_0 为 UIWnd 子结构...")
    patched = 0
    for cls_name in UI_CLASSES_68:
        tif = ida_typeinf.tinfo_t()
        if not tif.get_named_type(til, cls_name):
            continue

        # 获取结构体详情
        si = ida_struct.get_struc_id(cls_name)
        if si == 0xFFFFFFFF or si == ida_struct.BADADDR:
            # 尝试通过 til ordinal
            # 另一种方式: 直接用 idc.SetType 修改
            # 获取完整 C 定义
            old_decl = idc.print_decls(cls_name, 0)
            if not old_decl:
                print(f"  [-] {cls_name}: 无法获取定义")
                continue

            # 替换 char _gap_0[68] 为 UIWnd __base
            if '_gap_0[68]' in old_decl or '_gap0[68]' in old_decl:
                new_decl = old_decl.replace('char _gap_0[68];', 'UIWnd __base;')
                new_decl = new_decl.replace('char _gap0[68];', 'UIWnd __base;')

                # 删除旧定义，导入新定义
                ida_typeinf.del_named_type(til, cls_name, ida_typeinf.NTF_TYPE)
                nerrors = idc.parse_decls(new_decl, idc.PT_TYP)
                if nerrors == 0:
                    print(f"  [+] {cls_name}: _gap_0[68] → UIWnd __base")
                    patched += 1
                else:
                    # 恢复旧定义
                    idc.parse_decls(old_decl, idc.PT_TYP)
                    print(f"  [!] {cls_name}: 替换失败，已恢复")
            else:
                print(f"  [-] {cls_name}: 无 _gap_0[68] (可能已修补)")
        else:
            print(f"  [-] {cls_name}: struct approach (sid={si:#x})")

    print()
    print(f"[+] 修补完成: {patched} 个 UI 类")

    # Step 3: 标记函数 dirty
    if patched > 0:
        print("[*] 标记 UI 相关函数...")
        dirty_count = 0
        for ea in idautils.Functions(0x00401000, 0x00558000):
            name = idc.get_func_name(ea)
            if name and ('UI' in name or 'Prop' in name or 'Equip' in name or
                         'Magic' in name or 'Deal' in name or 'CCB' in name):
                ida_hexrays.mark_cfunc_dirty(ea)
                dirty_count += 1
        print(f"  [+] {dirty_count} 个函数已标记")

    print()
    print("[+] 完成!")
    print("    效果预览: this->_gap_0[56] → this->__base.m_bvisible")
    print("    按 F5 重新反编译 UI 相关函数查看改进")


if __name__ == '__main__':
    main()
