### Task 6: 编译产物对比（vtable 数据最终裁判）
- **文件**: `tools/vtable_verify.py` + `tests/test_vtable_verify.py`
- **TDD**: 先写测试（符号重定位归约/thunk 归一/强制发射），再实现对比器
- **复用**: coff_vtable.py（读 .obj vtable）+ vtable_compare.py（双侧归约对比）
- **强制发射**: 普通类构造对象；抽象类 dummy ctor 用实体

