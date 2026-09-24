### Task 5: 声明校验（棘轮制）
- **文件**: `tools/vtable_decl_check.py` + `tests/test_vtable_decl_check.py`
- **TDD**: 先写测试（health 上升放行/不变放行/下降阻塞），再实现棘轮制
- **校验**: 槽数数 + 槽序（用 Task 1 正向规则）+ 签名（编译产物实测）
- **门禁**: vtable_health[class] = 已验证槽数/总槽数，只升不降

