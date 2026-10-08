---
name: gotcha-fpu-double-locals-trigger-aligned-prologue-shape
description: 渲染源把 Hex-Rays 的 FPU 寄存器中间值物化成 double 局部变量时，VC6 会发 `and esp,-8` 动态对齐序言（orig 只有裸 `sub esp,N`）⇒ 整函数形状家族性漂移（栈槽全错位、数百字节 diff）；伴随"两个 bool 成员读取顺序对调"= 反编译器语句排序差异，不是布局错
type: gotcha
created: 2026-09-26
updated: 2026-09-26
status: active
sources: [session-2026-09-26, fdiff-CEffQuad-sub_4D1300]
---

# gotcha：FPU 中间值物化成 double 局部 ⇒ `and esp,-8` 对齐序言（形状家族）

## 现象（2026-09-26 fdiff 实测：CEffQuad::sub_4D1300，nd=903/1182，first_diff=0）

我们的 VC6 产物序言：
```asm
push ebp; mov ebp,esp; and esp,0xFFFFFFF8; sub esp,0x48   ; 动态 8 字节对齐
```
原始二进制序言：
```asm
sub esp,0x38; push ebx; push ebp; push esi; mov esi,ecx; push edi   ; 裸栈帧，无对齐
```

反编译伪码里有 `double fXSize; // st7`、`long double v11..v16; // st6/st5` 等
**FPU 寄存器伪变量**。渲染成 C 源时这些中间值落成真实 `double` 局部变量，
VC6 一旦判定函数需要跨调用溢出 double 就插入 `and esp,-8` 动态对齐——
原源码没有触发该路径 ⇒ 序言不同 ⇒ 帧形状不同 ⇒ **所有栈槽编号错位**
（orig `[esp+0x10]` vs 我们 `[esp+0x20]`），逐行 diff 全红。

## 伴随信号（易误诊为布局错，其实不是）

同函数里 orig 先读 `[esi+0x35]` 再读 `[esi+0x34]`，我们次序对调——
**两个 bool 成员偏移本身两侧一致**，这是反编译器**语句排序**差异，
改结构注解无用，只能靠源序/lvar 注解整形。

## 修复方向（未闭环，立账）

1. lvar 注解层把 FPU 中间值改声明为 `float`/寄存器糖或压成 `__int64`，
   避免触发 VC6 的 double 溢出对齐路径（需逐函数编译对照验证）。
2. 语句顺序类差异只能人肉按 orig asm 重排渲染源。
3. 判别公式：`first_diff=0 且 序言含 and esp,-8` ⇒ 形状家族（本 gotcha），
   不要往成员布局/结构注解方向查。

## 已知落点

- CEffQuad::sub_4D1300 (1182B, nd=903)、sub_4D17D0 (nd=945)——布局已正确
  （layout_probe drift=0），纯形状家族。
