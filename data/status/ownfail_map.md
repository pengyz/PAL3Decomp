# Own-fail 166 文件错误码战役地图（2026-08-31）

聚类基线：S2 39/205，own-fail 166，错误总数 ~3500+。

## 家族分类（按修复杠杆）

### A. 标注杠杆（上游修，符合 Phase 1 纪律）
| 家族 | 文件数 | 典型 | 修法 |
|------|--------|------|------|
| C2039 not-a-member | 61 | `m_szLogPath` ∉ CCBControlWindow、`m_pModObj` ∉ gbVolModNode | 找 A 级证据补结构体成员 |
| C2227/C2228 left-of | 46+24 | `->ShowWindow` 左值 void* | 变量/参数类型标注 |
| C2664-memset 型 | 部分 | memset 参数1 `unsigned int` | 全局变量类型标注（应为缓冲区指针）|

### B. codegen 杠杆（等价变换补丁）
| 家族 | 文件数 | 典型 | 修法 |
|------|--------|------|------|
| C2065 字符串 extern | 6 | `aDProjectPal3Co_7` 未声明 | codegen 字符串常量就地 extern 补全 |
| C2440 enum-cast | 5 | `(ECBRoleSpecState)int` MSVC6 需完整枚举定义 | 枚举定义补全/引入 |
| C2143/C2059 语法 | 74+41 | Hex-Rays 语法缺口 | 逐个判：可等价变换 vs Phase 2 |

### C. Phase 2 手工（Hex-Rays 上限）
- C2440 成员函数指针转换（`bool(__cdecl*)(int,int)` → `int (__thiscall CCBSystem::*)(int)`）
- C2660 尾态（如 Destroy 调用点参数残留——调用方 decomp 缓存旧类型）
- C2679/C2226 运算符与声明缺失族

## 下一步排序
1. m_szLogPath / m_pModObj 成员证据猎取（A 族试点，量化单成员收益）
2. C2660 Destroy 调用点残留排查（可能是 vtable 槽类型不同步）
3. codegen 字符串 extern 补全（小而确定）
4. C2039 全量盘点：按类聚合缺员清单，批量证据猎取

## 纪律提醒
编译错误是表象（CLAUDE.md）——A 族每个成员必须 IDA 访问点证据，
禁止从错误码反推偏移。
