---
name: gotcha-emitted-layout-drifts-from-annotated-offsets
description: 生成头的**实际 C++ 布局**会与它自己的 `// +0x...` 注释（=注解偏移）不一致——实测 SceneMgr 169 个成员里 101 个不匹配(60%)、Scene 7/21、RoleSystem 22/192；漂移点之后的每个成员访问都被编译成错误位移 ⇒ 该类的函数**永远不可能字节一致**；而当前无任何门禁能发现
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：生成头的实际布局 ≠ 注解偏移（编译器为唯一裁判）

## 现象（2026-09-21 实测，用**编译器**当裁判）

`Scene`/`SceneMgr`/`RoleSystem` 等生成头里，成员都带 `// +0xNNN` 注释（其值就是注解偏移），
但**把类交给编译器后，`offsetof` 得到的实际偏移与注释不符**：

| 类 | 成员数 | `offsetof ≠ 注释` | 首个不匹配 |
|---|---|---|---|
| `SceneMgr` | 169 | **101（60%）** | `m_pGfxMgr`（注释 +0x0）⇒ **从第一个成员就偏** |
| `Scene` | 21 | 7（33%） | `_gap_784E4` |
| `RoleSystem` | 192 | 22（11%） | `_gap_F20` |
| `CGameData` | 177 | **0 ✓** | — |
| `UIWnd` | 10 | **0 ✓** | — |

**判定手段（可复用，纯编译器、无需 IDA）**：为每个成员生成一行

```cpp
char c<N>[offsetof(Cls, member) == 0x<注解偏移> ? 1 : -1];
```

编译 ⇒ **只有不匹配的成员会报 `error C2118: negative subscript`** ✓（一次编译即可列出全部不匹配）。
注意：生成 TU 时前几行是 `#include`，第 N 个检查在第 `4+N` 行（**行号映射差 1 是最容易犯的错**）。

## 已发现的两个具体成因

1. **注入 `virtual ~Cls() {}` 带来非预期 vptr**：32 个类的生成头含注入的虚析构，
   其中 **`SceneMgr` 的注解 `vtables: null`**（布局模型假设无 vptr）⇒ 编译器插 vptr ⇒ 全部成员 +4 ✗
   （另 30 个类注解本就有 `vtables`，vptr 可能本就该有，需逐个核对）
2. **至少还有一个成员被"发小了"**：`SceneMgr::m_nRoleCount` 注解 `0xE0E0`（`source: binary:*((_DWORD*)this+14392)` ✓ 正确），
   而实际编译出 **0xE0BC**（−0x24）⇒ 除 vptr(+4) 外还有 **−0x28** 的累积亏空 ⇒
   即有成员的**发射尺寸小于注解尺寸** ✗

## **为什么**这很严重

* 漂移点之后的**每个成员访问**都编译成**错误位移** ⇒ 该类的函数**不可能字节一致**（L1 永远拿不到）✗
* 而**聚合指标与现有门禁都看不见**：`codegen_invariants` 的 [D] 只检查"注解有 vtables 但 +0x0 不是 vptr"，
  `check_member_extent` 只看"成员末端 < binary_size" ⇒ **没有任何门禁校验"发射布局 == 注解偏移"** ✗

## **何时使用 / 下一步**

* 看到某类的函数普遍 partial（哪怕匹配度不低）时：**先跑上面的 `offsetof` 检查**，
  确认该类的布局是否已经漂移——漂移了就先修布局，不要在该类的函数上做逐处修补（做了也不会有字节收益）✗
* **应建门禁**：`tools/check_layout_invariants.py`（编译器 oracle，逐类逐成员，advisory → hard），
  否则漂移会继续静默累积 ✓
* ⚠️ **验证因果再投资**（本会话教训）：先取一个漂移类（如 `SceneMgr`），
  只修布局、跑 `loop`、看该类的 partial 是否有字节改善；**改善了才铺开** ✓

## ✅ 因果已用**字节**证明（2026-09-21，只改生成物、不动 codegen）

删掉 `SceneMgr.h` 里注入的那一行 `virtual ~SceneMgr() {}`（⇒ 去掉非预期 vptr），跑 `probe`+`match`：

| 函数 | before | **after** |
|---|---|---|
| **`SceneMgr::Create(int,int,int)`** | 25.5% | **80.6%**（**+55.1pp**）✓✓ |
| `SceneMgr::RenderAll(void)` | 52.8% | 55.6%（+2.8）|
| `SceneMgr::RenderUpdate(void)` | 52.8% | 55.6%（+2.8）|
| `SceneMgr::GetCurrentNode(void)` | 4.3% | 2.9%（−1.4）|
| 其余 6 个 | 不变 | 不变 |

⇒ **漂移不只是理论问题**：单修 vptr 一项即带来 **+55 个百分点**的字节改善 ✓
⇒ L1 未动，因为**第二个 bug（+0x124 → +0xE0E0 之间丢 0x28）**仍在 ⇒ 需继续定位（同一 `offsetof` 探测法可二分）

**漂移曲线（实测）**：`SceneMgr` 从 class 起始到 `_gap_120`(+0x120) 漂移**恒 +4**（vptr）；
到 `m_nRoleCount`(+0xE0E0) 变成 **−36** ⇒ 期间**丢了 0x28(40) 字节** ⇒ 至少两个独立成因 ✓
