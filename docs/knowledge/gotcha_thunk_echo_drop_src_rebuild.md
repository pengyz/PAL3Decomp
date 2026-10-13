# gotcha · thunk 形回波剔除需先闭合 echo-drop 通路 + 17 函数源形重建判定

**type**: gotcha
**created**: 2026-10-13（T50 实验/T51 闭合/T53 复核修正）
**confidence**: high（双向探针实证 + R15 单测 6/6）

## 一句话
**thunk/尾调用形的源形重建（`f(this)` 回波剔除）需先闭合 echo-drop 通路**——
且证据门必须锚定 thunk 属性注记（裸子串会误放行字面量撞码）。

## T50 实验（诚实回退第 5 次）
```
thunk 形实验（compiler_init_005090A0：sig 变参→0 参 + echo-drop 门补方法隐式 this）
  ⇒ 当场读抓到净负：CCBStageEffect 翻红（回波未剔）· L1 134→131（−3）
  ⇒ 立即全回退，1337/127/134 精确复位 ✓ 零翻红（4150463bf 空提交=无残留实证）
```
**教训**：「当场读抓到误判立即回退」第 5 次（T11/T14/T19/T26/T50）。

## F-echo-drop-this-gap（T51 闭合，T53 修正）
双缺口：①「真定义头形参集」不含方法隐式 this（this-strip 后 def-head 无 this）
②调用 pattern 的 `,\s*` 尾要求多实参——单实参 `f(this)` 形根本不入匹配。
**证据门**：decomp `// attributes: thunk` **行首注释形锚定**
（`re.search(r'^\s*//\s*attributes:\s*thunk', code, re.M)`——T53-F2：
裸子串 `in code` 会被字面量撞码误放行）。
**负形保护**（T53②）：无注记 `f(this)` **不剔**（UI3DModelNode/_Console 真实参案
——2026-09-29 SetVideoRect/LayoutSlot 族同类）。

## R15/R11 教训（T52-F1）
**测试与最终政策必须对齐**：证据门收窄后**未复跑** ⇒ 「4/4 passed」仅成立于
中间态（交付态 2 failed）——**R11 违例**（改工具必须跑其测试）。
单测：`tests/test_drop_call_echo_arg.py` **6/6**（正形/负形/非回波/幂等/字面量/
字面量撞码不计证据）—— 改动 echo-drop 后**强制复跑**（R11）。

## 17 函数源形重建判定（T44/T47 挂账，T50 裁决）
| 类 | 数量 | 判定 |
|---|---|---|
| 指令移位族 | ×10 | 需源形重建（编码长度差传播，等价改写不够）|
| COMDAT 别名 thunk | ×3 | 需 sig 0 参化（data/annotations）+ 本通路（已闭合）|
| 寄存器分配差 | ×2 | 需活区间重建（FindIn*：编译器仍选 eax）|
| 尾调用形差 | ×1 | 需签名/返回型对齐（Destroy 案）|
| 删除析构形 | ×1 | _sdtor_call_dtor 通道已立（T23）待对齐 |
**逐字节 objdump 证据**入档 T44/T47（双侧指令序列）。

## 相关
- 单测：`tests/test_drop_call_echo_arg.py`（R11 强制复跑）
- 「测试绿证据力为 0」：`gotcha_wiring_type_changes_test_green_is_zero_evidence.md`
