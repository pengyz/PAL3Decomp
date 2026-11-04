# B 面现状重看（T10 终读数·2026-11-04）

## 证明链状态：全活
- mutation 6/6 抓红（硬闸过）· case-01/02 手写 oracle 双零差 · matrix 135 键全覆盖
- 活体 proof 真差分面（结构）：functions exp3804/act6793 · structs exp925/**act1250**（表解析修后）
  · globals exp1355/act9619 · 桶 match11/missing518/changed11062/extra325(结构)/coverage_extra6216
- verdict=BROKEN（按设计报红=缺口显形）

## 头条发现（proof 抓获的导入机制缺口——B 面价值实证）
**changeset 改名从未落 B**（`0x401000: ~AStarPathFinder → FUN_00401000`）——dryRun 单 op 探明双根因：
1. **`expect` 必填**（乐观锁「name as you saw it」）——plan 级转换器未发 expect ⇒ 全数拒
2. **名字校验=严格 C 标识符**（`~AStarPathFinder`/`?mangled` 被拒）——注解的 dtor/mangled 名
   （铁律：已 mangled 直通）与 daemon rename_function 校验冲突；旧旁路 create_label 可收任意名
3. **import_standard ok 计数错**：apply_changeset 的 `ok:false` 在 text 内（isError=None）
   ⇒ 10319「ok」实为全拒（工具级信号误读）——统计面修缮项

## 编译读数
- 证明后重灌轮出码=21361（零标注同值）——**双重因**：①改名未落（本报告头条）②该轮 generate
  拾错会话（session 清场前跑的，Types382 零标注签名）——**待重跑**（会话已独留 bf3837cd）

## 悬案移交（B 面下轮）
1. 两阶段导入：read 当前名 → rename 带 expect（标准通路内）
2. 非标识符名（dtor/mangled）的命名通路（create_label 标准面 or daemon 校验豁免调研）
3. import_standard ok 计数改读 text 内 ok 字段
4. 函数改名落地后重跑 generate+整编（真·修后读数）
