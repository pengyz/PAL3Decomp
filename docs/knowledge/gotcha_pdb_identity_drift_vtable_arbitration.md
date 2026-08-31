---
name: pdb-identity-drift-vtable-arbitration
description: PDB（PAL3A）类型/函数名在 PAL3 上会漂移；类身份的最终裁决是 ctor 安装的 vtable 值 + EH 展开目标，不是名字
type: gotcha
created: 2026-08-31
updated: 2026-08-31
status: active
sources: [session-2026-08-31]
---

**现象**：同一数据地址（0xC10968）出现三种矛盾的身份主张——PDB 布局说它是 `SceneMgrCamBlock+92 m_pUIScript: PalScript *`（指针），反编译正文把它当嵌入对象成员访问（47 个文件），InitSubsystems 又对它调 Create/LoadResource/ShowWindow（UI 窗口语义）。期间还发现 PDB 函数名映射系统性漂移：`PalScript::OffsetRect((PalScript*)&this->m_rect)` 实为矩形 helper，`UINote::Create(this=1)` 参数完全错位。

**为什么**：PDB 来自 PAL3A。两个游戏的函数体大部分相同（函数名映射大体可用），但**数据布局与类职责会漂移**——PAL3A 在该地址放了指针，PAL3 放了完整实例；部分辅助函数名被错误映射到 PAL3 地址。名字（无论类型名还是函数名）都是"PAL3A 说的"，不是本二进制说的。

**裁决方法（实测有效，按证据强度排序）**：
1. **ctor 安装的 vtable 值 = 类的身份证**：`mov dword ptr [esi], offset stru_XXXX` 写进对象的 vtable 是唯一不可伪造的身份证据。两个候选类各自"会安装什么 vtable"一对照，身份立判。
2. **ctor 的 EH 展开目标暴露基类**：ctor 的 SEH scope unwind 调 `UIWnd::_UIWnd` ⇒ 该类继承 UIWnd——一行汇编解释了"为什么脚本类会被当窗口 Create"（它本来就是窗口类）。
3. **动态初始化 thunk**（`mov ecx, offset X; jmp Ctor`，通常 10 字节、成对出现 ctor/dtor）证明对象是就地构造的全局实例而非指针槽。
4. **偏移直方图验证布局迁移**：IDA python 扫全部代码段 `DataRefsFrom`，对落入 [addr, addr+size) 的引用做偏移直方图；最大命中偏移 > 标注 binary_size ⇒ 尺寸错；ctor 写入的偏移逐一对照 struct JSON 成员 ⇒ 布局迁移成功与否立判。

**何时使用**：任何"PDB 说 A、反编译正文说 B"的标注争议；任何要用 PDB 布局/函数名做 struct_instances 推断之前；看到 `某类::OffsetRect` 之类"语义违和"的函数名时（名字漂移的标志症状——语义违和 = 名字错，不是代码怪）。

**反面教训**：本轮最初差点按名字采信"PalScript 指针"或反向采信"UI 窗口"推翻 PDB 类型——两边都是名字。最后 vtable + EH 裁决：两边都对（PalScript 本就是 UIWnd 派生窗口类），错的只是 PDB 把实例说成了指针。
