### Task 4: 布局断言生成器（默认启用）
- **文件**: `tools/layout_assert_gen.py` + `tests/test_layout_assert_gen.py`
- **TDD**: 先写测试（单继承 4/MI 8/虚基 12 + offsetof 虚基跳过），再实现生成器
- **输出**: `_layout_asserts.h`（MSVC6 C_ASSERT 负数组技巧）
- **规则**: 有虚基⇒12，否则基>1⇒8，否则 4；虚基成员跳过 offsetof

