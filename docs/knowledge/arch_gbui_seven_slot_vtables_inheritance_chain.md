---
title: gbUI 窗口类为 7 槽紧凑 vtable（非行表），继承树断裂是 MISATTRIBUTED 主因
type: architecture
date: 2026-09-13
confidence: 85
---

# gbUI 窗口类 = 7 槽紧凑 C++ vtable；继承链断裂 → MISATTRIBUTED 主因

> 勘误史：本文第一版误判为"7 函数行表（状态表）"——把相邻类 vtable 背靠背
> 排列误读成单表周期行。第二版修正为"紧凑 vtable 背靠背"但措辞仍不精确
> （槽间距 0x1C~0x24 不等距，夹 4~8 字节伴随数据）。本版为对抗复核后的定稿。

## 结构事实（IDA MCP 实测）

1. UI 家族（SceneObj/UIWnd/UIProgressBar/UIButton/UISceneFrm/CGameData/
   UIListBox/SaleUI/LineupUI/EquipUI/StateUI/RenderTarget/UITitle…）每类
   一个 **7 槽紧凑 vtable**，在 .rdata 0x56A9xx–0x5709xx 不等距紧密排列
   （间距 0x1C~0x24，夹伴随数据——早期读取跨类连线造成"7 周期行表"假象）。
2. 共享未覆写槽：slot0=0x445E70（68 个 data xref；IDA 名 `UIWnd::ShowWindow`
   系漂移命名，实为根类函数）、slot4=0x445B90（IDA 名 `CCBItemWindow::Create`
   ——同为漂移命名：被 68+ 类共享的槽不可能属于单一窗口类）、slot6=0x445D10。
3. **继承链（vtable 仲裁 + ctor/dtor 安装顺序互证）**：
   `CCBResultWindow → UIFrameWnd → UIWnd → SceneObj → CGameData(根)`。
   OnMessage 位于 CGameData 槽6——UI 窗口的 OnMessage 虚调用最终落在
   CGameData 层实现。
4. Role : ScriptObj（ctor 0x411965 先装 ScriptObj 1 槽表、0x411B30 装 Role
   4 槽表覆盖；dtor 反向互证），且 Role 有**多继承第二基 @+0x40**
   （vtable 0x56A9A4 slot2 含 `sub ecx,40h; jmp` this 调整 thunk——成员对象
   的表不会含指向外部类 dtor 的 thunk）。0x56A9A4 被 IDA 名为 RenderTarget3。

## 对 MISATTRIBUTED 的解释

`SceneObj::Update` 84 处调用方横跨 40+ 窗口类、`CGameData::OnMessage` 46 处
横跨 33 类：这些窗口类经上述继承链都是 SceneObj/CGameData 的派生类，
派生类方法调用基类虚方法（Hex-Rays 输出限定名 + this 强转），而注解层
base_class 链断裂（UIWnd.base_class: None 等）导致 codegen 无法判定合法，
发射 MISATTRIBUTED 标记。**修复 = 按 base_class 补全继承链**（带三条硬裁决：
thunk 检查 / ctor-dtor 顺序互证 / 槽兼容），预期消化 ~500±50 处（约 50%）。
剩余（PAL3/PAL_GDB/RoleSystem/CCBSystem/Array 等 ~180+ 处）是全局单例/
成员对象/命名错位簇，不适用继承解释。

## 陷阱

- IDA 对槽函数的类归属命名系统性偏向"最后触碰的成员类"，共享槽的名字
  不可信（0x445E70/0x445B90 两例）；仓库 original/PAL3.exe.i64.polluted.bak
  与 0x411CA0（~Role 被名 ScriptObj__ScriptObj）为 IDB 名字污染实证。
- base_class 写错 → codegen 发射"合法编译但 this 调整错误"的调用 →
  运行时崩溃，S2 编译探针查不出。写入前必须过三条硬裁决，且 probe
  需补语义级校验。
