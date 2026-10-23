# Task 1 复核（0d26dcb32）

## 实施正确性
真走 `_annview` ✓ 非形式伪（运行时取证：改 `annotation_view.structs_dir` 指沙箱，返回值随之变；路径与旧实现逐字同）。语义等价 ✓：新旧函数体全域 46320 例（全 struct×全槽×5 形×2 obj）+ 边角 16 例，仅 1 差异（JSON 顶为 `null`：旧抛 AttributeError、新返 None，现实不存在）。
⚠️ **改的是死代码**：`_try_resolve_vftable` 全仓 AST 零调用点（唯一引用=本测试）；死代码探针（入口插 `raise` 跑全量 codegen）exit 0、触发 0 次。`docs/specs/2026-09-21-vtable-resolver-refactor-design.md:71` 已定谳「死代码⇒直接删」。活路径 `_resolve_vftable_calls_ast`/`_try_resolve_vtable` 读 `store.struct_vtables`，本就无直读。

## 测试有效性
真测试但判别力窄（6 变异体实测）：M1 整体回退→FAIL ✓；**M2 形式伪（真调用但丢弃结果+改名直读）/ M3 读点只在注释 / M4 直读加回别的函数 → 均 PASS ✗**（模块断言 `'structs/' not in src or '_annview' in src` 是析取式，无牙）。反向误伤：实现正确、仅注释出现 `ann_path` → 误报 FAIL（断言绑变量名）。

## P1-5 验证
commit「S2 128/207→129/214」**无效对比**：分母 207→214＝单元集漂移非同树（同 class_review_progress.json 独立复核）。自跑同树 A/B（沙箱仅换此函数）：**1141 文件 sha256 逐字节相同**（含 new1=new2 确定性对照）⇒ S2/总错误/L1 必然不变，"+1" 为噪声。commit 缺总错误数字、L1 读数、字节 diff（P1-5 四项只证 2 项，`refactor_unify_data_source.md:26`）。未跑真树 probe（防污染并发者的 census）。

## 自构造 case
①全域新旧等价 ②死代码探针 ③6 变异体矩阵 ④边角矩阵（缺类/坏 JSON/顶层数组/null/空 vtables/无 `::`/槽越界/参数剥离）。

## verdict
**有条件通过**（改动正确、字节中性，但改的是死代码）。must-fix：①按既有定谳**删除**该死函数而非重构，CLAUDE.md「3 处直读」改实测口径（姊妹复核：≥11 处/5 文件）；②测试补形式伪负例（M2/M3 至少其一）或改行为级；③P1-5 改「同树 A/B 字节 diff」口径，禁跨单元集比 S2。旁证：`annotation_view` 双模块实例（`pipeline.gen.annotation_view`≠`annotation_view`，缓存实测分裂）应统一导入；Task 2 commit 声称的 `test_ast_transform_no_direct_read` **不存在**。
