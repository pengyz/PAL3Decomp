---
name: gotcha-verify-the-layer-before-patching
description: 修一个跨层缺陷前，必须先验证"病灶在哪一层"与"消费者实际读的是哪个文件/声明"——本会话 12 次假设驱动修补全部零效果，而每次只读验证都能一步定位
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：动手前先验证"病灶在哪一层 + 消费者实际读什么"

## 现象（同一族，本会话 12 次）

修一个 C2660（参数个数不符）家族时，我**连续 12 次**先猜机制、再动手，**全部零效果或净回归** ✗：

| 次 | 我的猜测 | 结果 |
|---|---|---|
| 1 | 级联"承重 bug" | 被**两路独立复核证伪** ✗ |
| 2–5 | 双调用约定 / 已解析分支归一 / stub 分支归一 / 最小归一 | 全部 **+13**（净亏）✗ |
| 6–7 | 槽位签名错 / 发射路径 | 零效果 ✗ |
| 8–9 | `gbTexture` 继承 `TextureLib` 撞名 / 某成员类型是 `TextureLib *` | grep **当场证伪** ✗ |
| 10–12 | 加 1 参重载（`gbImage2D*` → `int`）× 2 | 零效果 ✗ |

**而每次"只读验证"都能一步定位** ✓：
```bash
grep -rn "CreateFromMemory" pal3/src/ --include=*.h     # ⇒ 只找到另一个类 ✓
grep -rn '#include.*gbengine'  pal3/src/GameBase/PAL3.h # ⇒ 声明来自引擎头 ✓
sed -n '40,55p' pipeline/probe_compile.py               # ⇒ INCLUDE_DIRS 第一项=REPO/include ✓
# 临时在可疑头里放 #error ⇒ probe 立刻 610 行错误 ⇒ 确认它就是编译输入 ✓
```

## 坑

1. **跨层缺陷的"病灶"常在**消费者侧**，而不在"生成/数据侧"** ✗
   （本次：注解改了 3 次都无效 ✓，因为声明来自 `include/gbengine/*.h` —— **手工维护的引擎头** ✓）。
2. **"改了就零效果"时，先怀疑"我的改动是否参与编译"** ✗，而不是继续猜机制 ✓。
3. **报错文本携带的信息是有限的** ✗：`does not take N parameters` 只说**实参数目**，**不说类型** ✓
   ⇒ 据此推断"该加什么重载"必然失败 ✓（本次两次）。
4. **跨状态比对**是另一个静默失效源 ✗ —— 见
   [[page:gotcha-measure-state-before-not-after-change]] ✓（用行号去读"另一个状态"的生成物 ⇒ 读到的文本完全不对 ✓）。

## 规则

- **动手前，先回答三个只读问题** ✓：
 1. **病灶在哪一层**？（注解 / 生成器 / 手写头 / 编译器开关 / 数据 ✓）
 2. **消费者实际读的是哪个文件/声明**？（`#include` 链 + `-I` 顺序 + 是否存在**第二份**同名文件 ✓；
   最硬的证据 = **临时放 `#error`** 看是否触发 ✓）
 3. **报错还缺什么信息**？（若只给数目 ⇒ **必须去取类型/文本本身** ✓，不能推断 ✓）
- **改完必须有一次"单变量 + 基线断言"的测量** ✓（先断言 baseline 数值，否则会**自比** ✗ ——
 见 [[page:gotcha-interlocking-invariants-block-local-fixes]] 的同族教训 ✓）。
- **零效果 ≠ 机制错** ✗：也可能是**改动没进编译** ✓ ⇒ 先验证"是否参与编译" ✓。

## 追加实例（2026-10-29·T5 接线教训）：字符串 replace 接线须断言命中
stage5 接线 `strip_singleton_thunk_glue` 时 import 行 replace 因模式不合
（目标行含 `_strip_outer_parens, ` 前缀）**静默落空** ⇒ codegen 34s 速崩 NameError。
规则：任何 replace 接线后必须 `assert 新符号 in 源码`（或断言 replace 计数>0），
静默落空=延迟爆炸。同族：checkout 落暂存区坑（git checkout <file> 恢复的是
INDEX 态；须 `git checkout HEAD -- <file>` 才是 HEAD 态——T4 一版矫正落空根因）。
