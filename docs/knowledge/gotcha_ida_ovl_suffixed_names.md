# `__ovl` 后缀名的来源与处理约定（2026-10-20 调研定谳）

## 结论

**IDA 原生支持函数重载**，靠 MSVC **修饰名**（mangled name，编码参数型）区分每个重载；
解码后显示 `Class::Name(参数型)`，签名在名字里 ⇒ 天然唯一，无需后缀。
`__ovl` / `__ovl_N` **不是** IDA 的重载机制，而是「二进制里**无 C++ 修饰符号**」时的
去重后缀（内部函数 / 符号被剥离 ⇒ IDA 解码不出签名，只能给唯一短名）。

## 决定性实证（本仓）

同一类 `CCCTData` 的两个 `Create` 真重载，两种名形并存：

| decomp name | signature | addr | 名形 |
|---|---|---|---|
| `Create__ovl_1_0` | `bool (CCCTData*, void  *param)` | 0x004A8770 | 无修饰名 ⇒ `__ovl` |
| `CCCTData::Create(float *)` | `bool (CCCTData*, float *pfVal)` | 0x00506020 | 有修饰名 ⇒ IDA 原生 |

同仓 IDA 原生形示例（带签名）：`NPC::Create(int)` · `CEffGrid::Create(tagEffObjType *)` ·
`CEffectSystem::CreateEffectChain(CCBUI *,int,uint,int,int)`。

## 规模

全仓约 **17 个不同 `__ovl` 名**：
`Create__ovl_1`（49 处引用最多）· `Create__ovl_1_0` · `ProcCommonTask__ovl` ·
以及 13 个带十六进制偏移的形（`ctor__ovl_BE80` / `Update__ovl_8260` /
`HandleInput__ovl_ff90` / `CreateEffect__ovl_f580` …）。

真重载（同类内同名多签名）仅 **3 组**：`CCCTData::Create` · `CEffCylinder::ProcCommonTask` ·
`ARC_PlayerAtt::Create`。

## 为什么暂不改（决策）

1. **不影响字节匹配** —— 函数名不进指令字节
2. 当前主线是 1290 条编译错误，改名是「忠实度收益」非「错误收益」
3. 改名前必须先留 `addr → 真名` 映射，否则 annotation 的回溯断链

## 若日后要改（约定）

- 有修饰名 ⇒ 用 IDA 原生形 `Class::Name(参数型)`
- 无修饰名 ⇒ 按类归属生成**真 C++ 重载**（同名不同参），如
  ```cpp
  class CCCTData {
      bool Create(void *param);    // 原 Create__ovl_1_0
      bool Create(float *pfVal);   // 原 CCCTData::Create(float *)
  };
  ```
- ⚠️ **带十六进制偏移的名字**（`HandleInput__ovl_ff90` 等）属 CLAUDE.md 禁止的
  **地址后缀伪语义命名**（`m_nState_4968` 同族）——这一条比 `__ovl` 本身更要紧，应优先正名。

## 参考

- [IDA 解码名称（显示参数型）](https://blog.csdn.net/u012206617/article/details/87796726)
- [Hex-Rays tip #35: Demangled names](https://hex-rays.com/blog/igors-tip-of-the-week-35-demangled-names)
- [IDA 文档：名字唯一性](https://hex-rays.gitbook.io/docs-dev/9.0/user-guide/user-interface/menu-bar/edit/give-name-to-the-location?fallback=true)
