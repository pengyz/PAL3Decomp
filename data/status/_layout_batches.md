# 布局冲突类 **闭环分批**（长期目标 `goal-22326891`，**每批 10 个**）

> ## 工作流（2026-09-22 使用者确立的**闭环** ✓，取代"预排批次" ✗）
> **测量 → DAG 选 10 → 修 → 重新测量 + 重建 DAG/问题规模 → 重新选目标**
> （布局更新有**传播效应** ✗：修一个类会顺带修好/改变别的类 ⇒ 旧清单会立刻失真 ✗
>  实测：旧清单里 SwordUI/PropUI/MainEquipUI 3 个"冲突"类已被此前的修复**顺带解决** ✗）

## 工具
* **测量**：`python3 tools/audit_type_layout.py --only <10 个类> --json`
* **重排**：`rank_targets(conflicts, embed, top=10)`（杠杆=被按值内嵌次数优先 ✓，冲突数次之 ✓，排除已解决 ✓）
* **门禁**：五阶段 `loop` + 四道门 + **新门（注解 vs 二进制）** ✓

## 当前基线（2026-09-22 晚）
S2 **76/205** ✓ · 总错误 **2140** ✓ · **L1 38** ✓ · matched 270/325 ✓ · 全链路**五阶段全绿** ✓

## 当前状态（2026-09-22 晚 · goal round 5 ✓）

### ✅ 已清零（布局审计 ✓ 一致）
UITextArea(192 ✓) · RoleCamera(✓) · CameraCtrl(✓) · PalScriptMgr(✓ 补 vptr) ·
UIListBox · SaleUI · EquipUI · UIRoleSelect · MagicUI · SwordUI · PropUI · MainEquipUI · UIAnimateCtrlEX ✓

### ⚠️ 级联待修（UITextArea 0x68→0xC0 的传播 ✗）
UIRoleDialog(720→需808 ✗ 未改注解) · UIRoleSelectDialog(2204→需2292 ✗ 未改) · Comp_DonateUI(46192→需46280 ✗ 未改) · UIGameFrm(28188→需28276 ✗ 未改)

### 🔧 可修（有方法 ⇒ O2 可扫 ✓）
SceneMgr(1/167 ✗ `_gap_C812` 尾部=级联尾巴 ✓)

### 🚫 不可修（无方法 ⇒ `manual_idb` ✗）
UIChatRest(47/48 ✗ · 0 个 IDB 方法) · CParticleSystem · HeadMsg 等数据/状态容器

### 📋 剩余冲突类
~75 个（去掉已清和不可修后 ✓）—— 按 DAG 序+杠杆选下一批 ✓

> ⚠️ 批次**不预排** ✗：每批修完 ⇒ 重新测量 ⇒ **重新确定问题规模与目标** ✓（按值内嵌的传播会改变清单 ✓）
