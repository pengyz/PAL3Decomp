"""
IDAPython: 批量重命名高频调用的未命名函数

这些函数通过反编译代码分析推断身份。
命名后将大幅改善调用方的反编译可读性。

影响: Top 15 函数合计被 ~8000 个函数引用。

用法:
  在 IDA 中 File -> Script File -> 选择此脚本
"""

import idc
import ida_name
import ida_hexrays
import idautils

# (地址, 新名称, 推断依据)
RENAME_TABLE = [
    # === UIWnd 系统 (来自 PAL3patch 验证) ===
    (0x0044D2A6, "UIWnd::SetRect",
     "拷贝RECT到this+4..+7, 调vtable[6](OnMessage) msg=1023"),

    (0x0044ACE9, "UIStatic::SetText",
     "strlen+string::assign到this+96(=UIStatic::m_text), 设flag"),

    (0x0044ABF3, "UIWnd::LoadImage",
     "接收LPCSTR路径, 操作gbTexture/gbVFileSystem"),

    (0x004307C0, "UIWnd::DestroyChildren",
     "遍历this+7(PtrArray.nSize)个子控件并清理"),

    # === UI 消息系统 ===
    (0x00430E73, "UIWnd::PostMsg_Show",
     "构造消息type=8, 调SendMessage"),

    (0x00430EA3, "UIWnd::PostMsg_Hide",
     "构造消息type=9, 调SendMessage"),

    (0x00431053, "UIWnd::PostMsg_Enable",
     "构造消息type=18, 调SendMessage"),

    # === 数学/工具 ===
    (0x00406402, "gbVec3D_Distance",
     "计算两float[3]差向量并求Length, __cdecl"),

    # === 全局访问器 ===
    (0x00528901, "GetGlobalInstance",
     "仅return全局stru_21AE020, 6字节thunk"),

    (0x004D8009, "UIBigMap_UpdateSpirit_Thunk",
     "直接转发到UIBigMap::UpdateSpirit, 6字节thunk"),

    # === 战斗系统偏移访问器 ===
    (0x004E0523, "CCBStageRole::GetRolePtr",
     "return this + 1040*index + 552, 角色数据指针计算"),

    (0x004E5924, "CCBStageRole::GetRoleByte",
     "return *(this + 1040*a2 + a3 + 1257), 读取角色字节属性"),

    # === PlayerMgr ===
    (0x00439686, "PlayerMgr::CalcRoleStat",
     "192字节步长访问, 调PlayerMgr::CalRoleFull_DEF"),

    (0x00430829, "PlayerMgr::SetActionState",
     "设置740字节步长数组状态=3"),

    (0x00434523, "PlayerMgr::UpdateRolePosition",
     "复杂位置计算, 访问浮点坐标和1140偏移"),

    # === 第二批: 高频 UI 系统函数 ===
    (0x0044D15D, "UIWnd::Enable",
     "if(this+13=bcreateok) this+15=benable=a2"),

    (0x0044ACCF, "UIStatic::SetShowMode",
     "根据bool设this+23为2或1, 影响显示模式"),

    (0x0044D2DE, "UIWnd::SetFontColor",
     "this+1 = *a2, 拷贝gbColorQuad到fontcolor"),

    (0x0044D2EA, "UIWnd::SetWndColor",
     "this+2 = a2, 设置wndcolor字段"),

    (0x0044D075, "UIWnd::ScreenToClient",
     "x - rect_left, y - rect_top, 屏幕坐标转客户区"),

    (0x0044CF8C, "UIWnd::FrameMove",
     "遍历childs.pData调vtable[2], 帧刷新"),

    (0x00442BA0, "UIFrameWnd::UIFrameWnd",
     "设vtable off_558C58, 初始化各字段, 构造函数"),

    (0x00442C38, "UIFrameWnd::dtor",
     "设vtable off_558C58, 调析构链, 析构函数"),

    (0x00442DDF, "UIWnd::LoadTexture",
     "操作gbTexture + gbVFileSystem加载纹理"),

    # === 全局/工具函数 ===
    (0x004B1618, "GetGameInstance",
     "单例模式 Construct_18 + atexit, 返回全局对象"),

    (0x004D80F1, "GetEditCtrlFloat",
     "SendMessage(WM_GETTEXT) + atof, 从编辑框取浮点值"),

    (0x00430DA7, "UIWnd::PostMsg_Cmd",
     "构造消息结构调用SendMessage, type=3"),

    # === 场景/角色搜索 ===
    (0x0047ADA6, "Scene::FindRoleByID",
     "200*步长遍历37个slot搜索匹配ID"),

    (0x0047ACF4, "Scene::FindNPCByID",
     "190*步长遍历35个slot搜索匹配ID"),

    (0x004DF033, "CCBStageRole::IsRoleAlive",
     "1040*a2步长读取字节flag, 判断存活"),

    # === PlayerMgr/Inventory ===
    (0x00439D3D, "PlayerMgr::SetRoleString",
     "strlen + string::assign设置字符串属性"),

    (0x004326CB, "Inventory::RefreshCount",
     "调GetTotalNum刷新物品数量"),

    (0x00446367, "PlayerMgr::SetSkillSlot",
     "92*步长设置技能名+参数到角色数据"),

    # === 战斗系统 ===
    (0x004EDF46, "CCBStage::SetRoleDead",
     "2632*步长设状态=3, 标记角色死亡"),

    (0x0052BBAE, "ChoseCompose_OnMessage_Thunk",
     "直接转发到ChoseCompose::OnMessage"),

    # === sub_447F0F ===
    (0x00447F0F, "UIStatic::LoadFromPath",
     "lstrlenA + sprintf构造路径加载图片资源"),
]


def main():
    print("=" * 60)
    print("[*] 批量重命名高频 sub_ 函数")
    print(f"    共 {len(RENAME_TABLE)} 个函数")
    print("=" * 60)

    renamed = 0
    skipped = 0
    failed = 0

    for addr, new_name, reason in RENAME_TABLE:
        old_name = idc.get_func_name(addr)
        if not old_name:
            print(f"  [!] 0x{addr:08X}: 该地址无函数")
            failed += 1
            continue

        if not old_name.startswith("sub_"):
            print(f"  [-] 0x{addr:08X}: 已命名为 {old_name}, 跳过")
            skipped += 1
            continue

        # IDA 不允许 :: 在函数名中（除非是类方法）
        # 用 MakeName 设置
        safe_name = new_name.replace("::", "_")
        if ida_name.set_name(addr, safe_name, ida_name.SN_NOWARN):
            print(f"  [+] 0x{addr:08X}: {old_name} -> {safe_name}")
            renamed += 1
            # 标记调用者为 dirty
            for xref in idautils.CodeRefsTo(addr, 0):
                ida_hexrays.mark_cfunc_dirty(xref)
        else:
            print(f"  [!] 0x{addr:08X}: 重命名失败 ({new_name})")
            failed += 1

    print()
    print(f"[+] 完成: {renamed} 重命名, {skipped} 已有名, {failed} 失败")
    print()
    print("[*] 提示: 重命名后按 F5 刷新反编译即可看到效果")
    print("    例: sub_44D2A6(...) -> UIWnd_SetRect(...)")


if __name__ == '__main__':
    main()
