# experiments/ — 实验线（VERIFICATION-ONLY，不出现在字节轨）

- `ghidra_track/` — Ghidra 双轨验证轨：同一份 annotation JSON 喂 Ghidra 直出 vs Hex-Rays，
  编译错误差分 = 「annotation 真错 / Hex-Rays 硬约束」自动定量清单。
  铁律：零字节轨变更（不动 pal3/src 与 data/annotations）。详见其 README 与 docs/specs/2026-11-02-*。
- 状态（2026-11-23）：三证 gate 绿（mutation+fixture+matrix）；consume 环与差分首表待续。
- 测试经 conftest.py 把 experiments/ 加入 sys.path（`from ghidra_track.xxx import` 语义不变）。
