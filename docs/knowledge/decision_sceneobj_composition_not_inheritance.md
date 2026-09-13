---
title: SceneObj/UI 家族跨类调用是组合不是继承——base_size 钉死的终裁
type: decision
date: 2026-09-13
confidence: 90
---

# SceneObj::Update 的 84 处跨类调用 = 组合（has-a），非继承（is-a）

## 裁决过程（三方证据演进）

1. **v1（账本）**：`SceneObj::Update` 84 处调用方横跨 40+ 窗口类 → 猜"未记录继承树"。
2. **v2（对抗复核）**：vtable 槽 0/4/6 家族共享 → 裁 `UIWnd → SceneObj → CGameData(根)`，
   但自标 "base_size 待核"。
3. **v3（base_size + 安装点终裁，本文）**：**复核链被否决**——
   - 尺寸硬约束：CGameData(28268B) > SceneObj(1784B)，链不可能成立；
   - SceneObj ctor 0x452AA0（7KB）只安装自己的 vtable 0x56B200，零基类表安装；
     对照 UIWnd ctor 0x4427C0 实装 UIFrameWnd+UIWnd 两表（该边为真）；
   - vtable 槽重合率 3/7 = 兄弟关系（共同基在别处），非父子覆写；
   - **75 个直接 call 0x445C60 调用点的机器码**：`mov ecx, <各类自己的指针来源>` 后
     直接 call——各窗口类持有 SceneObj 指针（成员/全局），是教科书组合调用。
   - SceneObj 注解既有三基（PalScriptWaitObj/GlowObj/TaskMgr_SceneObjParam_SceneObj）
     与此自洽：它是脚本侧多继承节点，不属于 UI 窗口继承树。

## 对 1044 处 MISATTRIBUTED 的最终解释

UI 大簇（SceneObj/StateUI/UIListBox/…）的跨类调用 = **组合调用被 Hex-Rays
渲染成限定形式**（Hex-Rays 只知道被调函数归属 SceneObj，把调用方持有的
指针显示为调用方 this——因为局部/成员变量类型未被标注，寄存器折叠后
Hex-Rays 用当前函数的 this 兜底渲染）。

## 修复方向（替代 base_class 方案）

transform 侧识别"成员/全局持有的跨类调用"：
- 已知类 X 的方法内出现 `SceneObj::M(ptr)` 且 ptr ≠ this → 发射
  `((SceneObj *)ptr)->SceneObj::M(...)`（保真形式，cast+限定）；
- `SceneObj::M(this)` 且 X 不继承 SceneObj → 维持 [MISATTRIBUTED] 标记
  （可能真错或指针别名，需逐案）。

这条修复不触碰 IDB 结构（无派生化连锁），风险远低于 base_class 方案。

## 教训

- vtable 槽共享 ≠ 继承（兄弟类共享根类未覆写槽是常态）；
- **base_size/尺寸约束是继承裁决的第一道闸**，槽分析只能做辅助；
- 对抗复核也要被复核：复核员自己标了 "base_size 待核" 的结论，
  核完就翻。
