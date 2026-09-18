# 根因：**类名与自由函数同名**（`RoleCameraCtrl` / `FightInfo`）

**日期**：2026-09-17 · 来源：`UIDialog.cpp` 唯一错误 C2059 的最小复现 + include 二分

---

## 1. 现象与最小复现路径

`pal3/src/UI/UIDialog.cpp:57` 唯一错误：
```cpp
(((RoleCameraCtrl *)&this[1]))->RoleCameraCtrl::SetTargetDistance(2);   // C2059 syntax error : ')'
```

按"系统化调试"逐层收敛（每步都可复现）：

| 步骤 | 做法 | 结果 |
|---|---|---|
| 1 | 孤立 TU 只放这一句（`t(RoleCameraCtrl *p){ ... }`）| **编译通过** ⇒ 非语法本身问题 |
| 2 | 用 `UIDialog.cpp` 的 include 集 + 同一句 | **复现错误** ⇒ 是 include 集合引入的 |
| 3 | 逐个前缀二分 include | 前 8 个 ok，**加第 9 个 `free_functions.h` 立刻报错** |
| 4 | 看 `free_functions.h` | **`:226 void RoleCameraCtrl(void);`** |

⇒ `free_functions.h` 声明了一个**与类同名的自由函数**。于是在
`->RoleCameraCtrl::SetTargetDistance(2)` 中，`::` 前面的 `RoleCameraCtrl` 解析成
**函数**而非类，`函数::成员` 非法 ⇒ MSVC 报 `syntax error : ')'`。

## 2. 规模：语料里**正好 2 个**这种冲突

对 `free_functions.h` 的 **376** 个函数名与 881 个类名取交集：

| 冲突名 | 自由函数声明 | 自由函数定义 | 调用点 |
|---|---|---|---|
| `RoleCameraCtrl` | `free_functions.h:226` | `free_functions.cpp:4573 void RoleCameraCtrl()` | **0 个**（只有定义）|
| `FightInfo` | `free_functions.h:122` | `free_functions.cpp:2584 void FightInfo()` | **≥4 个**（`ScriptVM.cpp:443/963/1318/1494`）|

## 3. 这个冲突造成的错误（不只 UIDialog）

| 文件 | 错误数 | 与冲突相关的 |
|---|---|---|
| `pal3/src/UI/UIDialog.cpp` | **1** | C2059（§1）|
| `pal3/src/Misc/RoleCameraCtrl.cpp` | 16 | `C2501 'RoleCameraCtrl' : missing storage-class or type specifiers`、`C2373 redefinition; different type modifiers`、`C2556 overloaded function differs only by return type` |
| `pal3/src/free_functions.cpp` | 102 | `C2501 'FightInfo'`、`C2501 'm_pFightInfo'` |

⇒ **`UIDialog.cpp` 只差这一个 ⇒ 修掉即 `ok +1`**（本轮唯一可确定的 `ok` 收益）。

## 4. 两个候选修法与风险（**未实施，交下一轮**）

### 候选 A：改名自由函数（如 `RoleCameraCtrl` → `RoleCameraCtrl_fn`）
- ✅ `RoleCameraCtrl` **没有调用点** ⇒ 只改 `free_functions.h` 声明 + `free_functions.cpp` 定义即可。
- ⚠️ **风险**：`match` 用 mangled name 把源码函数与二进制符号配对（`symbols=218`）。
  若这个自由函数是 218 个符号之一，改名会**丢掉一个配对**，可能让 `matched` 下降。
  **实施前必须先确认它是否在 symbols 里**。
- ⚠️ `FightInfo` **有 ≥4 个调用点**，改名必须同时改 `ScriptVM.cpp` 的调用 ⇒ 需知道
  codegen 是否对自由函数名有统一的改名映射（若有则一处即可）。

> ❌ **更正（2026-09-17，对抗性复核实测）**：真正被误解析的是 **cast 里的类型名**
> （`(RoleCameraCtrl *)` 里的 `RoleCameraCtrl` 被当成函数），**不是"函数::成员"**。
> 合成 TU 实测：去掉限定符 `((RoleCameraCtrl*)&this[1])->SetTargetDistance(2)` **仍报 C2059**；
> 而 `((class RoleCameraCtrl *)&this[1])->...` **通过**。故**候选 B 无效**，
> 改用 **候选 B′：把 cast 写成 elaborated type specifier `(class RoleCameraCtrl *)`**。
> 详见 `_cleanup_erratum_adversarial_review_C1_C6.md` §4。

### 候选 B（**推荐**）：在**使用侧**避免 `->Cls::method` 形式
- 复用**上一轮刚加**的 `_qual` 机制（`pipeline/gen/ast_transform.py`）：
  当 `class_name` **与某个自由函数同名**（或含 `::`）时，省略限定符，发
  `((RoleCameraCtrl *)&this[1])->SetTargetDistance(2);`
- ✅ **不改任何名字** ⇒ 无符号/matching 风险；单点改动；语义等价（非虚调用 vs 虚调用
  的差别这里不涉及 —— 该限定符仅为保留"直接调用"形式）。
- ⚠️ 需要把"自由函数名集合"传给 transform。`free_functions.h` 由
  `emit_cpp.py:506` 写出，transform 在 `stage2_semantic.py` 阶段跑 ⇒ 需确认执行顺序，
  或改为从**注解/decomp 导出**取自由函数名集合。

## 5. 顺带发现：一个**通用的名冲突检测**值得做
"自由函数名 ∩ 类名"是个便宜的静态检查，目前语料里 2/376。
建议加进 `annotation_diff` 或 `check_annotations` 的门禁，避免以后再引入同类冲突
（本次若不是 `UIDialog.cpp` 恰好只有 1 个错误，这个根因会继续隐藏）。

## 6. 复现
```bash
# 最小复现（§1 步骤 2/3）
python3 - <<'EOF'
import sys,os; sys.path.insert(0,'.')
import pipeline.probe_compile as P
inc=open('pal3/src/UI/UIDialog.cpp',encoding='utf-8').read().split('// Forward declarations')[0]
open('pal3/src/UI/_repro.cpp','w').write(inc+'void UIDialog::Show(){ (((RoleCameraCtrl *)&this[1]))->RoleCameraCtrl::SetTargetDistance(2); }\n')
a=['/Fo'+P.wpath(os.path.join(P.OBJ_DIR,'r.obj')),P.wpath(os.path.join(P.REPO,'pal3/src/UI/_repro.cpp'))]+['/I'+P.wpath(d) for d in P.INCLUDE_DIRS]
print(P.parse_output(P.run_cl(a)[0])[0])   # -> C2059
os.remove('pal3/src/UI/_repro.cpp')
EOF
# 冲突检测
grep -n "void RoleCameraCtrl\|void FightInfo" pal3/src/free_functions.h
```