# crt_runtime skip 条目普查（2026-10-28）

> 只读普查。触发：free_functions.cpp 中 `crt_sub_xxxx` 被游戏逻辑调用，疑 crt_runtime 误标（WinMain 冤案同族）。

## 一、crt_sub_* 家族（用户关注面）：61 个

| 分类 | 数 | 明细 |
|---|---|---|
| **游戏可达且仍被 skip（冤户）** | **4** | `crt_sub_00541490`←InitUIQuadManagerSingleton · `crt_sub_005414A0`←sub_404800 · `crt_sub_00541860`←WinMain · `crt_sub_00541C40`←WinMain（注册表读 "software\\softstar\\pal3"/"CDriver"）|
| 游戏可达但已解禁（functions.json 有 decl） | 7 | `00540070`(13 个 decomp 引用) · `00540D20`(7) · `00541590`(6) · `00540FD0`(4) · `00540DC0`(3) · `00541210`(3) · `005415C0`(1，**skip 表仍有同址条目=双注**) |
| 孤立（0 引用） | 50 | 真 CRT 段（0x55xxxx：_malloc/_sprintf/__ftol/EH runtime/stdio…）+ 微跳板簇（0x5424xx-0x543Axx 间距 5-10B）+ `__m64/__m128::_static_*` 簇 ⇒ 保持 skip 正确 |

⚠️ 7 个已解禁件的签名全是占位 `int __cdecl()`（仅 005415C0 有真签名 `void __cdecl(gbRefObject **p)`）——待签名补真。

## 二、大发现：`crt_runtime` 是筐（512 个具名条目全量扫）

**22 个游戏可达**（被非自身 decomp 引用），其中真 CRT 调用属正常（`_strcmp` ×39 引用、`_exit`、`CRT_set_new_handler`——游戏调 CRT 库函数天经地义，skip 正确：链接期由 CRT 库供给）。**真正冤的是游戏代码被塞进筐**：

| 条目 | 引用 | 性质 |
|---|---|---|
| `fn` | **21** | WinMain 传给 `SetWindowsHookExA` 的钩子回调 + ScriptVM/PAL_GDB 调用 ⇒ **游戏代码** |
| `PushMatrixStacks`/`PopMatrixStacks` | 11+11 | 渲染栈 helper（RenderTarget*.Resolve 等）⇒ **游戏代码**（source 自述「批0 复位……skip 挡 C2556 ×144 爆」= 双定义 workaround，非 CRT 判断）|
| `j_D3DXVec3TransformCoord` | 1 | D3DX 导入跳板——**正对应 sg_emission_control 里被我们 overlay 注释掉的 C2065 `j_D3DXVec3TransformCoord_0`**！注释债的根因之一 |
| `DirectInput8Create` | 1 | 导入跳板（GRPinput_Create 调用）|
| `SingletonThunk_*` ×7 | 各 1 | `mov ecx,[global]; jmp target` 编译器产物——**链接期需供给**，现无定义体 |
| `crt_sub_00541490/005414A0/005415C0/00541860/00541C40` | 各 1 | 见上表冤户 |

## 三、裁决建议

1. **立即可办（WinMain 流程）**：`crt_sub_00541490/005414A0/00541860/00541C40` 复核无双源声明后 unskip ⇒ export 得 decomp ⇒ codegen 补函数体。
2. **正名批**：`fn`（建议语义名 WinHookProc）、`PushMatrixStacks`/`PopMatrixStacks` 摘掉 crt_runtime 伪装，按真实类别处理（skip 原因如实记录）。
3. **对应 overlay 回收**：`j_D3DXVec3TransformCoord(_0)` 解决后，sg_emission_control 的 `[overlay-fix]` 注释可回收。
4. **保持 skip**：0x55xxxx 真 CRT（链接期 CRT 库供给，字节等同由 MSVC6 同版库保证）、`__m64/__m128` 静态簇、微跳板孤立件、`unknown_libname_*`（另行审计）。
5. **风险闸**（批0 教训 data/annotations/CHANGE_LOG 有案）：unskip 必须先查 functions.json/methods 是否已有同址声明收编 ⇒ 否则 C2556/2373 双定义爆炸（×144 实录）。逐个来，不批量。

## 四、方法

- 可达性判据：`asm/pal3/decomp/*.json`（3695 个）文本出现该名字且非自名 decomp 文件 ⇒ 游戏可达。
- 局限：间接调用（函数指针/虚槽）不可见 ⇒「孤立」≠ 永不被调，仅=无静态直调。
