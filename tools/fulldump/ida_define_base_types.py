"""
IDAPython: 定义 PAL3A 关键基类和缺失嵌套类型

定义以下类型:
  - UIWnd (68B) - 所有 UI 类的基类 (来自 PAL3patch 精确逆向)
  - NPCInfo (456B) - Role::m_npcinfo 的类型 (从反编译访问模式推断)
  - SaveTask (12B) - SceneObj::_SaveTaskInfo 的类型
  - PtrArray (16B) - 通用指针数组容器 (来自 PAL3patch)

效果:
  - UI类 (UIStatic,UIButton,UIListBox等): _gap_0[68] → UIWnd 字段
  - Role: m_npcinfo[N] → NPCInfo.field_XXX
  - 总计影响 500+ 个函数的反编译质量

用法:
  在 IDA 中 File -> Script File -> 选择此脚本

注意:
  此脚本定义独立类型。要让 UIStatic 等类使用 UIWnd 基类,
  需要在 IDA 中手动编辑类型: 将 _gap_0[68] 改为 UIWnd __base;
  或重新运行 gen_ida_struct_import.py --with-base-classes
"""

import idc
import ida_typeinf
import ida_hexrays
import idautils

# === 来自 PAL3patch 社区逆向的精确定义 ===
TYPES_HEADER = r"""
#pragma pack(push, 1)

typedef unsigned int UINT;
typedef int BOOL;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef long LONG;

struct gbColorQuad {
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    unsigned char Alpha;
};

struct PtrArray {
    void *m_pData;
    int m_nSize;
    int m_nMaxSize;
    int m_nGrowBy;
};

struct UIWnd {
    void *vfptr;
    struct gbColorQuad m_fontcolor;
    struct gbColorQuad m_wndcolor;
    unsigned int m_id;
    int m_rect_left;
    int m_rect_top;
    int m_rect_right;
    int m_rect_bottom;
    struct UIWnd *m_pfather;
    struct PtrArray m_childs;
    int m_bcreateok;
    int m_bvisible;
    int m_benable;
    int m_bfocus;
};

struct NPCInfo {
    int field_000;
    int field_004;
    int field_008;
    int field_00C;
    int field_010;
    int field_014;
    int field_018;
    int field_01C;
    int field_020;
    int field_024;
    int field_028;
    int _pad_02C;
    int field_030;
    int field_034;
    int field_038;
    int field_03C;
    int field_040;
    char field_041;
    short field_042;
    int field_044;
    int field_048;
    int field_04C;
    int field_050;
    int field_054;
    int field_058;
    int field_05C;
    int field_060;
    int field_064;
    int field_068;
    int field_06C;
    int field_070;
    int field_074;
    int field_078;
    int field_07C;
    int field_080;
    int field_084;
    int field_088;
    char _gap_08C[8];
    int field_094;
    int field_098;
    int field_09C;
    int field_0A0;
    int field_0A4;
    int field_0A8;
    int field_0AC;
    int field_0B0;
    int field_0B4;
    int field_0B8;
    int field_0BC;
    int field_0C0;
    char _gap_0C4[28];
    int field_0E0;
    int _pad_0E4;
    int field_0E8;
    int _pad_0EC;
    int field_0F0;
    int _pad_0F4;
    int field_0F8;
    int _pad_0FC;
    int field_100;
    char _gap_104[8];
    int field_10C;
    int _pad_110;
    int nCount;
    int field_118;
    char _gap_11C[28];
    int field_138;
    char _gap_13C[16];
    int field_14C;
    char _gap_150[8];
    int field_158;
    int field_15C;
    int field_160;
    int field_164;
    int field_168;
    int field_16C;
    int field_170;
    int field_174;
    int field_178;
    int field_17C;
    int field_180;
    int field_184;
    int field_188;
    int field_18C;
    int field_190;
    int field_194;
    int field_198;
    char _gap_19C[24];
    int field_1B4;
    int _pad_1B8;
    int field_1BC;
    char _gap_1C0[8];
};

struct SaveTask {
    int taskid;
    int param1;
    int param2;
};

#pragma pack(pop)
"""


def delete_type_if_exists(til, name):
    """删除已有的类型定义"""
    tif = ida_typeinf.tinfo_t()
    if tif.get_named_type(til, name):
        ida_typeinf.del_named_type(til, name, ida_typeinf.NTF_TYPE)
        return True
    return False


def main():
    print("=" * 60)
    print("[*] PAL3A 关键基类/嵌套类型定义")
    print("=" * 60)

    til = ida_typeinf.get_idati()

    # 删除旧定义
    types_to_define = ['gbColorQuad', 'PtrArray', 'UIWnd', 'NPCInfo', 'SaveTask']
    for t in types_to_define:
        if delete_type_if_exists(til, t):
            print(f"  [*] 删除旧定义: {t}")

    # 导入
    print("[*] 导入类型定义...")
    nerrors = idc.parse_decls(TYPES_HEADER, idc.PT_TYP)
    if nerrors != 0:
        print(f"  [!] parse_decls 返回 {nerrors} 个错误")
    else:
        print("  [+] 所有类型导入成功")

    # 验证
    print("[*] 验证类型大小...")
    expected_sizes = {
        'gbColorQuad': 4,
        'PtrArray': 16,
        'UIWnd': 68,
        'NPCInfo': 456,
        'SaveTask': 12,
    }
    all_ok = True
    for name, expected in expected_sizes.items():
        tif = ida_typeinf.tinfo_t()
        if tif.get_named_type(til, name):
            actual = tif.get_size()
            status = "OK" if actual == expected else f"MISMATCH (got {actual})"
            if actual != expected:
                all_ok = False
            print(f"  {name:20s}  sizeof={actual:4d}  expected={expected:4d}  {status}")
        else:
            print(f"  {name:20s}  NOT FOUND")
            all_ok = False

    if not all_ok:
        print("[!] 部分类型大小不匹配，请检查!")
        return

    # 标记受影响函数为 dirty
    print("[*] 标记受影响函数...")
    dirty_count = 0
    keywords = ['Role', 'SceneObj', 'UI', 'PropUI', 'Equip', 'Magic', 'Deal',
                'CCB', 'State', 'Main']
    for ea in idautils.Functions(0x00401000, 0x00558000):
        name = idc.get_func_name(ea)
        if name:
            for kw in keywords:
                if kw in name:
                    ida_hexrays.mark_cfunc_dirty(ea)
                    dirty_count += 1
                    break

    print(f"  [+] 已标记 {dirty_count} 个函数")
    print()
    print("[+] 完成! 按 F5 重新反编译函数查看改进效果")
    print("    预期改进:")
    print("    - UI类: _gap_0[N] → UIWnd 基类字段 (m_bvisible, m_rect 等)")
    print("    - Role: m_npcinfo[276] → m_npcinfo.nCount")
    print("    - SceneObj: _SaveTaskInfo 使用 SaveTask 字段")


if __name__ == '__main__':
    main()
