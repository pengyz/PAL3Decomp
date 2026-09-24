### Task 3: 候选签名生成器（provenance + 序言分析）
- **文件**: `tools/vtable_sig_infer.py` + `tests/test_vtable_sig_infer.py`
- **TDD**: 先写测试（未用参数/this 入栈/fastcall/BOOL 物化/sret 用例），再实现推断器
- **证据**: 只用原始指令字节（disasm），输出 methods_pending 旁路
- **分级**: A 级候选（等价类确定）/ B 级（缺返回宽度）/ C 级（参数不确定）

