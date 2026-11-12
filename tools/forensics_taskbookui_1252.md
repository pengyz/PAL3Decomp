# TaskBookUI@1252 虚分派族取证报告(2026-11-12)

## 结论: 类身份未定谳

- 0x455790 RefreshElements 归属 TaskBookUI ✓(3 caller 全 TaskBookUI 族)
- 虚分派目标 = this+1252 内联子对象(25 个 call [vptr] 虚分派)
- 元素类候选 UIScene(344B + 虚槽0 ShowClipped 双吻合)
  **但** overlap gate 拒收(1244 落在 stp_State@1148 UIButton 344B 内部)
  **且** 1252 处有已定谳 m_fPathAngle(float)——两套布局矛盾未解
- RTTI 关闭(/GR-)实证: 类名通道不可用

## 待办
1. stp_State@1148 与 1252 的布局矛盾需 IDB vtable 交叉验证裁决
2. 60 错 C2664 虚分派族保持挂账
