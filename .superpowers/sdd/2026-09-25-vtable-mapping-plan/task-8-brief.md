### Task 8: 端到端验证（L1 + .rdata 双裁判）
- **文件**: `tests/test_vtable_e2e.py`
- **TDD**: 先写测试（L1 函数体对比 + .rdata vtable 对比），再集成
- **验证**: 对 3 个已知断裂单元（CCBStageShadow/PalScriptWaitObj/UI3DCtrl）做端到端
