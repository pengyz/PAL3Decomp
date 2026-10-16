# union:true 仅限 POD 成员（2026-10-16 新增）

## 现象
**C2620 全树崩**（S2 0/205）—— `union '__unnamed'：member 'm_WaitObjList' has user-defined constructor`
击中**每个 TU L84**（PalScript.h 经 globals 链全树可见）

## 为什么
**MSVC6 union 禁非平凡成员**（带 ctor 的 class 如 `PtrArray`）
**经 globals 链放大为 205/205 崩**（PalScript.h 全树可见）

## 何时使用
**所有 repr 改型前必须先查成员型平凡性**：
- ✅ **POD 成员**（float/int/void*）⇒ `union:true` 安全
- ❌ **非平凡型**（带 ctor 的 class）⇒ **禁入匿名 union**（用 overlap 标注 / POD 替身）

## 复算命令
```bash
python pipeline/cli.py check  # C2620 报文
grep -n "user-defined constructor" <census>  # 全树崩证据
```

## 本仓实证
**verifier 31 站修法·C1 项**（2026-10-16）：`PalScript.m_WaitObjList@260` = `PtrArray`（带 ctor）塞进匿名 union
⇒ C2620 全树崩 ⇒ **C1 已撤**（回单型 `PtrArray`）
**B/D 族保留**（POD/单型安全 ✓）

## 教训
**机械类比误伤**（T56 族教训新证）—— B 族 POD union 安全，C 族照抄同惯例**未查平凡性** ✗
**⇒ repr 改型前先查平凡性**
