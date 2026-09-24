### Task 2: 合成槽分类器（二进制可观测形态）
- **文件**: `tools/vtable_slot_classifier.py` + `tests/test_vtable_slot_classifier.py`
- **TDD**: 先写测试（deleting_dtor/adjustor_static/adjustor_vbase/purecall/composite 各 ≥1 例），再实现分类器
- **识别**: 序言形态（add/sub imm;jmp 仅 ecx）、地址特征（与 ??_G 共享地址）、CRT stub 地址
- **不用 mangling**——真实二进制 531 条仅 4 条 mangled

