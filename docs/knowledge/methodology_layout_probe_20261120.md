# 布局排查方法论 v1（2026-11-20，CGameData 案提炼）

> 适用：巨型容器类（>10KB）、子对象区被拆散成伪标量的类、双档案类。
> 血统：CCBStage 三步法 + vtable-writer-evidence-law + X族三表偏移×bases对齐 + CGameData 四子对象案。

## 核心原则

**先锚点、后边界、再重划。** 子对象边界 = 「锚点成员偏移 + 子对象尺寸」推算；
锚点不足时不落任何 type 改动（CGameData 案教训：单 cast 落 type 被 C10 正确拦截）。

## 取证金字塔（每层产出锚点，逐层收紧）

### L0 边界基线
- 类尺寸 binary_size ↔ 分配边界（下一全局/对齐）双侧闭合律（tagStageRoleData 案）
- 产出：[base, base+size) 硬窗口

### L1 生命周期锚点（最强）
- **ctor 写表序**：`mov [reg+off], vtable_addr` 的 off 序 = vptr 布局全图
  （每张表一个直接基/虚基；X族判据：多表写偏移序 ↔ bases offset 列表逐字对齐）
- **ctor 子对象构造调用**：ctor 体对子对象 ctor 的 this 实参偏移 = 子对象锚点全集
- **dtor 子对象析构调用**：析构/Destroy 链（CGameData 案：UITitle::~UITitle(&this->m_UITitle)）
- ⚠️ ctor 可能未识别（CGameData 案：先找「写该 vtable 地址的函数」反推 ctor）

### L2 方法 this 锚点
- 类方法被调用的 this 实参 = 基址锚（`(Type *)&g_gamefrm`）
- **多调用点交叉**：单 cast 只标嫌疑；≥2 独立调用点同偏移才升锚

### L3 访问谱三层（成员踪迹）
1. 成员形 `obj.field`（封装类通常 0）
2. 偏移算术形 `base + off`
3. 绝对地址项 `dword_VA`（.data 实例直访）
- 三层全零 = 访问者不可达（寄存器中转基址/未导出函数）——**不是无访问**

### L4 尺寸矛盾判别（基座调用陷阱）
锚点+子对象注解尺寸 与 下一锚点间距 矛盾时，两种解释：
- **基座调用**：静态方法 cast 只保证基座可调（`RoleCameraCtrl::InitBaseWidget`
  若体只碰 UIWnd 基座 ⇒ 锚点处实际是 UIWnd 而非 RoleCameraCtrl）
  **判别法**：读该方法体，看 this 访问 disp 是否超出疑似基座尺寸
- **布局错**：现有散成员其实活在子对象内部（`UITitle 9236B 覆盖 0x1394-0x3744`
  ⇒ 之间所有"散成员"是 UITitle 内部）

### L5 交叉收口
- 全锚点一致性检查；type 落盘前**先算 C10 重叠**，冲突即回退或转专项
- 重划手术必须整块落（子对象内成员一并归并），禁止散改

## 锚点强度分级

| 证据 | 强度 |
|---|---|
| ctor 子对象构造调用（this 偏移） | A+（生命周期原生） |
| dtor 子对象析构调用 | A（清理原生） |
| ≥2 独立调用点 this 锚 | A |
| 单 cast 静态方法调用 | B（基座陷阱，需 L4 判别） |
| 访问谱踪迹 | B+（需三层齐全解读） |
| 名字语义猜测 | C（unverified，禁作锚） |

## 流程

1. L0 闭合窗口 → 2. 找 ctor（写表反推）→ 3. L1 双锚（ctor+dtor）→
4. L2 交叉 → 5. L4 逐锚判别 → 6. 锚点表+窗口矩阵 → 7. 重划方案
（先纸上全量计算 C10）→ 8. 整块落盘+门禁
