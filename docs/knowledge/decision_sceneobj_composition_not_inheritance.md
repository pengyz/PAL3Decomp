---
title: gbUI 跨类调用终裁：7 槽行表注册制（非继承非组合）
type: decision
date: 2026-09-13
confidence: 80
---

# SceneObj::Update 84 处跨类调用 = gbUI 行表注册制调用

## 三轮裁决史（每轮都被下一轮修正——保留全过程作为方法论样本）

1. **v1 账本**：84 处调用方横跨 40+ 类 → 猜未记录继承树。
2. **v2 对抗复核**：vtable 槽共享 → 裁 UIWnd→SceneObj→CGameData 链（base_size 未核）。
3. **v3 组合**：base_size 否决 v2 链 + 75 个调用点 mov ecx,各类指针 → 裁组合。
4. **v4 终裁（本文）**：slot2 覆写证据（CCBResultWindow::IsImbibeNimbusNotFinish 覆写
   SceneObj::Update 槽位）推翻 v3 纯组合说；而 UIWnd.slot2 访问半径 0x94BE(38KB)
   证明 0x4427C0 是管理器而非窗口 ctor → **槽共享的真身是 gbUI 行表注册制**：
   每个窗口类在 .rdata 注册一张 7 函数行表（slot0/4/6 为框架通用入口
   ShowWindow/Cleanup 等，slot1/2/3/5 是各类自实现的消息处理 Update/OnMessage），
   框架（管理器）按表调度。Hex-Rays 把行表函数归属到注解类名，调用点渲染成
   `SceneObj::Update((SceneObj*)this)` 限定形式。

## 证据链（v4）

- 0x445E70（slot0 通用入口）访问半径仅 0x3C，被 68 个类的表共享——框架级小函数；
- UIWnd 表的 slot2（0x442FF0）访问半径 0x94BE——管理器级巨型函数（0x4427C0 区）；
- SceneObj 表 slot2=0x445C60（Update），CCBResultWindow 表 slot2=0x519660
  （IsImbibeNimbusNotFinish）——各类自实现消息处理器；
- ctor 证据：SceneObj ctor 0x452AA0 只装自己表；管理器 ctor 0x4427C0 装多表；
- 注解层 CCBResultWindow size=180 是扫描截断（ctor 访问 this+0xA44，已修正 2628）。

## 修复方案（终版）

**不是 base_class（行表不是继承），不是成员组合**。正确形态：
`((SceneObj *)this)->SceneObj::Update(...)`——但 this 兼任行表所有者的语义
无法在注解层表达。务实路径：
1. transform 增加"行表类白名单"：被调类属于行表注册族（SceneObj/CGameData/
   StateUI/UIListBox 等出现在多类表中的函数）时，`X::M((X*)this)` 发射
   `((X*)this)->X::M(...)` 保真形式（cast+限定），标记改为 [ROWTABLE]；
2. IDB 层长期：给行表函数命名加 `_rowtable` 后缀区分归属语义；
3. 语义校验：编译后比对调用目标地址不变（is-GA）。

## 教训

- 槽共享、槽覆写都不是继承的充分证据——先看函数访问半径（0x3C vs 0x94BE
  立刻区分框架函数与管理器）；
- 尺寸约束（base_size）是否决性检验但不是充分性检验；
- 四轮裁决每轮都有新证据推翻前轮：对抗复核本身也要被对抗复核。
