# P0' ref_params 括号修 Spec（2026-11-02）

## 根因

`pipeline/gen/ref_params.py` `_fix_single_ref_arg` 两个 Case 的操作数括号/覆盖面缺陷：

### Case 2（L197）：`*` 绑定范围不足
- **病灶**：`return '*' + arg` 只把 `*` 绑到 cast 前缀，二元 `+` 落在解引用外面
- **实证**：decomp `Translate(pStack, (struct gbVec3D *)this + 14)` → 生成 `*(gbVec3D *)this + 14`（`*` 绑到 `(gbVec3D*)this`，`+14` 在外面）
- **效果**：`gbVec3D + int` 无 `operator+` → C2676 → C2784

### Case 1（L192）：`&` 剥离未验证覆盖面
- **病灶**：`if arg_stripped.startswith('&')` 剥 `&` 不校验 `&` 是否覆盖整个实参
- **实证**：decomp `&g_pCameraCtrl->m_vecLookAt + 1` → 生成 `m_vecLookAt + 1`（`&` 只覆盖 `m_vecLookAt`，`+1` 在外面）
- **效果**：`gbVec3D + int` → C2676 → C2784

## 修法

| Case | 修法 | 变换类型 |
|---|---|---|
| Case 2 | `'*' + arg` → `'*(' + arg + ')'`（整操作数加括号） | 等价（括号显式化优先级） |
| Case 1 | 仅 `&` 覆盖整个实参才剥；`&X + N` 形改为 `*(&X + N)`（整体解引用） | 等价（引用绑定=解引用） |

## TDD 测试

1. `Case 2: (T*)x + N → *((T*)x + N)`（括号修复）
2. `Case 1: &x + N → *(&x + N)`（覆盖面修复）
3. `Case 2: (T*)x → *(T*)x`（简单形不变）
4. `Case 1: &x → x`（全覆盖剥 & 不变）
5. 负例：无引用参数的实参不变

## 验证面

1. TDD 测试绿
2. C2784 降 12/42
3. S2 不降（+0~1）
4. `cli check` 0 errors
5. `match/L1` 不降（对抗复核 F8② 要求）

## 预期效果

- C2784: 42 → 30（降 12）
- S2: 130 → 130~131（+0~1）
- C2676: 降 7（gbVec3D + int 消除）
