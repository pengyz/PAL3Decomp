---
title: gbUI 窗口"vtable"实为 7 函数行表（状态表），不能用于继承推导
type: architecture
date: 2026-09-13
confidence: 85
---

# gbUI 窗口"vtable"实为 7 函数行表，不是 C++ vtable

## 现象

ida_structs.json 中 UI 家族（SceneObj/UIWnd/UIProgressBar/UIButton/UISceneFrm/
CGameData/UIListBox/SaleUI/LineupUI/EquipUI/StateUI/RenderTarget/UITitle…）
的 vtables[0] 槽位表全部截断为 7 项，且从 .rdata 完整读取后呈严格 7 行周期：

- slot 0 = `?ShowWindow@UIWnd@@QAEHH@Z`（0x445E70）在 0/7/14/21/28 行重复
- 0x445D10 在 6/13/20/27 行；0x445B90 在 4/11/18/25 行

即这些"vtable"是 **7 函数一行的状态/模块表数组**（gbUI 自研分发机制），
每行形如 {ShowWindow, X, Method2, Method3, Cleanup(0x445B90), X, 0x445D10}。
PalScriptMgr 的表首槽是 0x434D50（另一家族），CameraCtrl 的表首槽读出浮点
0x3C23D70A（vtable 地址本身漂移或非 vtable）。

## 推论（影响 ⑥c/继承重建工作流）

1. **不能用 vtable 前缀匹配推导 UI 类继承树**——行表不是 C++ vtable，
   前缀重合只反映行表结构，不反映类继承。继承边只能来自 ctor 调用链
   （反编译文本中 `Base::Base(this)` 形态，受寄存器折叠干扰，产率低）
   或逐类人工分析。
2. MISATTRIBUTED 账本中 SceneObj::Update(84x)/CGameData::OnMessage(46x)
   等"调用方横跨几十个 UI 类"的簇，解释大概率是**行表分派机制**：
   各窗口类的行表函数由统一入口（如 UIWnd::ShowWindow）按状态调用，
   反编译把这些行函数的调用归属到了包含它的窗口类。
3. 0x445E70 = UIWnd::ShowWindow 是行表通用首槽（几乎不被覆写），
   可作为"此类属于 gbUI 窗口家族"的指纹。

## 验证方法（复现）

```bash
# 用 IDA MCP 读完整行表（读到非代码段指针为止）
# pipeline: curl POST http://127.0.0.1:13337/mcp
# {"method":"read_memory_bytes","params":{"memory_address":"0x56AE2C","size":"800"}}
```

vtable 地址来自 asm/pal3/ida_structs.json 的 vtables[].addr
（data/status/_vtable_addrs.json 有全量 78 类）。
