# vtable 映射实现计划

日期：2026-09-25
规格：docs/superpowers/specs/2026-09-25-vtable-mapping-design.md
方法：TDD（先写测试，再实现）

## 全局约束

1. vptr 由编译器生成——annotation 不声明 `__vftable`/`vfptr`/`vtable` 成员
2. `vtables[]` 数组是唯一声明点——有 = 多态，无 = 非多态
3. 工具生成候选，IDA 定性——工具不直接写真相源
4. 证据只来自原始指令字节——禁止 decomp JSON 作为签名证据输入
5. 棘轮制门禁——health 只升不降，不设硬门禁
6. 虚调用始终用直接方法调用——做不到的记账+证据，不降级
7. 布局断言默认开启——参数关闭，全反编译期持续

## 任务列表

### Task 1: vtable 槽序验证规则（正向规则 + 金样本测试）
- **文件**: `tools/vtable_slot_order.py` + `tests/test_vtable_slot_order.py`
- **TDD**: 先写测试（vt6/DO、adv2、adv4 金样本 + 合成槽用例），再实现正向规则
- **规则**: 继承槽原位保留（覆写原位替换）→ 本地新增段尾插 → 本地新增段内同名组逆序 → 合成槽落声明位不参与分组
- **测试**: 用 `_vtable_abi_probe_20260925/` + `_vtable_advprobe_20260925/` + `_vtable_attack_cases_20260925/` 的实测槽序做金样本

### Task 2: 合成槽分类器（二进制可观测形态）
- **文件**: `tools/vtable_slot_classifier.py` + `tests/test_vtable_slot_classifier.py`
- **TDD**: 先写测试（deleting_dtor/adjustor_static/adjustor_vbase/purecall/composite 各 ≥1 例），再实现分类器
- **识别**: 序言形态（add/sub imm;jmp 仅 ecx）、地址特征（与 ??_G 共享地址）、CRT stub 地址
- **不用 mangling**——真实二进制 531 条仅 4 条 mangled

### Task 3: 候选签名生成器（provenance + 序言分析）
- **文件**: `tools/vtable_sig_infer.py` + `tests/test_vtable_sig_infer.py`
- **TDD**: 先写测试（未用参数/this 入栈/fastcall/BOOL 物化/sret 用例），再实现推断器
- **证据**: 只用原始指令字节（disasm），输出 methods_pending 旁路
- **分级**: A 级候选（等价类确定）/ B 级（缺返回宽度）/ C 级（参数不确定）

### Task 4: 布局断言生成器（默认启用）
- **文件**: `tools/layout_assert_gen.py` + `tests/test_layout_assert_gen.py`
- **TDD**: 先写测试（单继承 4/MI 8/虚基 12 + offsetof 虚基跳过），再实现生成器
- **输出**: `_layout_asserts.h`（MSVC6 C_ASSERT 负数组技巧）
- **规则**: 有虚基⇒12，否则基>1⇒8，否则 4；虚基成员跳过 offsetof

### Task 5: 声明校验（棘轮制）
- **文件**: `tools/vtable_decl_check.py` + `tests/test_vtable_decl_check.py`
- **TDD**: 先写测试（health 上升放行/不变放行/下降阻塞），再实现棘轮制
- **校验**: 槽数数 + 槽序（用 Task 1 正向规则）+ 签名（编译产物实测）
- **门禁**: vtable_health[class] = 已验证槽数/总槽数，只升不降

### Task 6: 编译产物对比（vtable 数据最终裁判）
- **文件**: `tools/vtable_verify.py` + `tests/test_vtable_verify.py`
- **TDD**: 先写测试（符号重定位归约/thunk 归一/强制发射），再实现对比器
- **复用**: coff_vtable.py（读 .obj vtable）+ vtable_compare.py（双侧归约对比）
- **强制发射**: 普通类构造对象；抽象类 dummy ctor 用实体

### Task 7: 虚调用转换（三形态识别）
- **文件**: `pipeline/gen/stages/stage3_cleanup.py`（扩展）+ `tests/test_vtable_call_transform.py`
- **TDD**: 先写测试（inline/局部 vftable 变量/裸 vptr 读三形态），再实现转换
- **目标**: `obj->MethodName(args)` 直接虚调用
- **失败契约**: 保留 stub 语义 + 记账，不降级

### Task 8: 端到端验证（L1 + .rdata 双裁判）
- **文件**: `tests/test_vtable_e2e.py`
- **TDD**: 先写测试（L1 函数体对比 + .rdata vtable 对比），再集成
- **验证**: 对 3 个已知断裂单元（CCBStageShadow/PalScriptWaitObj/UI3DCtrl）做端到端
