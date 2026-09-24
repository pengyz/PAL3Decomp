### Task 7: 虚调用转换（三形态识别）
- **文件**: `pipeline/gen/stages/stage3_cleanup.py`（扩展）+ `tests/test_vtable_call_transform.py`
- **TDD**: 先写测试（inline/局部 vftable 变量/裸 vptr 读三形态），再实现转换
- **目标**: `obj->MethodName(args)` 直接虚调用
- **失败契约**: 保留 stub 语义 + 记账，不降级

