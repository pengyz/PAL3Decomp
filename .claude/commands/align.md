对指定的 gbengine 源文件执行一次二进制对齐迭代。

目标文件: $ARGUMENTS

## 核心原则: 先 match，再质量，再验证 match

不允许为了 match 破坏代码质量。流程是:
1. 先让函数字节匹配（可以临时用偏移/魔数）
2. 替换偏移为结构体访问、魔数为常量、vtable hack 为虚函数调用
3. 重新验证匹配率没有下降
4. 如果质量优化导致匹配下降 → 回退质量修改，保留 match 版本并标注 TODO

## 完整流程

### Phase 1: 字节匹配

1. 运行字节对比: `python tools/gbengine_compare.py --compile src/gbengine/$ARGUMENTS --all`
2. 记录当前匹配数
3. 对每个不匹配函数:
   - Size MISMATCH（stub）: 查找 `asm/gbengine/` 下 IDA JSON，实现函数
   - Size OK 但不匹配: 读 IDA 反编译，判断差异类型:
     - 逻辑错误 → 修正
     - 寄存器/布局差异 → 跳过（等价匹配）
4. 编译验证通过

### Phase 2: 质量验收

执行 `/quality $ARGUMENTS` 的逻辑:
- 消除所有裸偏移访问（必须用结构体成员）
- 消除魔数（用宏/sizeof/命名常量）
- 消除 vtable hack（在头文件声明虚函数）
- 确保结构体布局正确（偏移注释）
- **禁止照搬 IDA 变量名** — `v3`, `v4`, `v5` 等必须替换为有语义的名称（如 `prev`, `next`, `count`, `oldHead`）。IDA 临时变量名是反编译器产物，不代表源码风格。改名不影响字节匹配（同类型同作用域）。

### Phase 3: 回归验证

1. 重新编译: `python tools/gbengine_compare.py --compile src/gbengine/$ARGUMENTS --all`
2. 确认匹配率 >= Phase 1 结束时的匹配率
3. 如果下降: 定位哪个质量修改导致下降，回退该修改
4. 编译通过 + 匹配不降 = 本次迭代成功

### Phase 4: 提交推送

1. `git add` 所有修改的文件（src/ 和 include/）
2. `git commit` 使用格式: `feat(gbengine): align <文件名> — X/N exact match`
3. `git push`

## 匹配判定

可接受为等价（不需修正）:
- 寄存器选择不同
- push/mov 顺序差异
- lea vs add 等价指令
- 栈偏移不同
- 循环方向差异（编译器布局）

必须修正:
- Size MISMATCH
- 调用了不同函数
- 控制流逻辑不同
- 常量值不同

## 输出

```
文件: $ARGUMENTS
Phase 1 (match):  X/N → X'/N exact
Phase 2 (quality): PASS / N issues fixed
Phase 3 (verify):  X'/N confirmed (no regression)
Phase 4 (commit):  <hash> pushed
```
