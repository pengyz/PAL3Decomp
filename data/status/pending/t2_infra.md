# T2 基础架构设计

> 2026-10-22 · 只出设计 + TDD 清单，禁改产品文件。T2 = 语义等价（同输入 ⇒ 同行为，不要求同字节）。

## oracle 设计

- **运行**：原版 `original/PAL3.exe` + `Mss32.dll` 走 wine（`tools/wine_cl.sh` 同环境，`WINEDEBUG=-all`）；固定虚拟桌面 `explorer /desktop=pal3,1024x768`、固定 locale/时区、禁网络、RNG 种子化。
- **输入驱动**：脚本语料 ∪ 边界值 ∪ 覆盖率 fuzz 输入，统一 `input_id` 寻址。
- **四通道捕获**（每 run 落 `data/t2/oracle/<input_id>/<run_id>/`）：①返回值/退出码 ②stdout/stderr ③存档字节 ④截图（帧缓冲 dump，比对前屏蔽时间水印区）。
- **确定性门槛**：同输入连跑 2 次四通道 canonical hash 全等才准入语料；不稳定输入标 `flaky` 隔离，不进判据。

## T2-F 框架

- **双跑差分**：同一 harness/输入分别驱动原版函数与重建函数（`build/pal3_test`，见 tests/conftest.py），产出 `(返回值, 语义状态快照)` 二元组。
- **输入域** = 脚本语料 ∪ 边界值（0/±1/极值/NaN/空指针合法域）∪ 覆盖率引导 fuzz（以原版函数边覆盖为引导信号）。
- **比对对象**：返回值 + 语义状态字段（struct 语义成员、VM 栈/寄存器、相关全局）；padding/地址类非语义区不比。
- **normalize()**（单一纯函数，先测后写）：指针→对象 id（首见分配递增 id，别名同 id，确定性）· padding/未初始化字节归零 · 浮点 ULP≤2 视为相等（±0 统一 +0，NaN 归一 payload）。
- **差分判据**：`normalize(A) == normalize(B)` 逐字段相等；差异归类「语义差异」（必修）vs「噪声」；已知差异走 **ratchet 白名单**（理由+复核人，只减不增）。主 KPI = 行为覆盖率（被差分执行到的原函数占比）。

## TDD 清单（测试名 + assertion）

落点 `tests/t2/`（pytest，测试先于实现）：

**oracle（3）**
1. `test_oracle_runs` — wine 启动原版冒烟输入 ⇒ `assert returncode == 0`（或预期内集合）且日志非空；超时 ⇒ `assert False, "oracle_timeout"`（不静默 kill）。
2. `test_oracle_output_stable` — 同 `input_id` 连跑 2 次 ⇒ `assert sha256(run1_captures) == sha256(run2_captures)`（存档逐字节；截图 Δ≤1/255）。
3. `test_oracle_capture_channels` — ⇒ `assert 四通道文件均存在且非空` 且 schema 校验通过。

**T2-F（3）**
1. `test_normalize_ptr_to_objid` — 别名指针 ⇒ `assert id(p)==id(q)`；不同对象 ⇒ `assert id(r)!=id(p)`；重复 normalize ⇒ 结果全等（确定性）。
2. `test_normalize_padding_float` — padding ⇒ `assert 全 0`；`1.0` vs `1.0+2ulp` ⇒ `assert equal`；`1.0` vs `1.0+3ulp` ⇒ `assert not equal`；`+0.0` vs `-0.0` ⇒ `assert equal`。
3. `test_diff_criteria` — 同快照 ⇒ `assert diff == {}`；改一语义字段 ⇒ `assert diff == {field_path: (a,b)}`；仅改指针地址/padding ⇒ `assert diff == {}`。

## 实施顺序

① 上述 6 测试落盘（red）→ ② `normalize()` 纯函数（零 IO）→ ③ oracle runner（wine+四通道+确定性门槛）→ ④ T2-F diff runner（双跑+判据）→ ⑤ 语料入库 + ratchet 白名单。每步以对应测试转绿为完成判据；全程只加 `tests/t2/` 与 `data/t2/` 基建，不触碰 pipeline/annotation 产品文件。
