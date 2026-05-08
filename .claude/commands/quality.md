对指定的 gbengine 源文件执行代码质量验收。

目标文件: $ARGUMENTS

## 质量门控（必须全部通过才算合格）

### 1. 禁止裸偏移访问

❌ 不允许:
```c
*(int*)(this + 0x58)
*(float*)((char*)ptr + 0x24)
((void**)vtable)[5]
```

✅ 必须:
```c
m_pActorDef              // 通过结构体成员名访问
action->weight           // 通过字段名
m_pActorDef->RenderDef() // 通过虚函数名
```

**例外**: 仅在以下情况允许偏移:
- 还未定义结构体的临时 stub（必须标记 `// TODO: define struct`）
- 联合体/变体类型的强制转换（必须注释说明原因）

### 2. 结构体布局正确性

- 所有被访问的结构体必须在 `include/` 下有定义
- 结构体的字段偏移必须通过注释标注验证
- 如果 IDA 数据显示新的偏移，必须更新头文件中的结构体定义
- sizeof 必须与原始二进制一致（在注释中标注）

验证方法:
```c
// 在头文件中标注偏移
struct gbActionState {
    int state;              // +0x00
    unsigned int actionCrc; // +0x04
    float weight;           // +0x08
    ...
};
```

### 3. 禁止魔数

❌ 不允许:
```c
action->currentFrame = (unsigned int)(time * 4800.0f);
if (state == 0x6f766572)
pCrc = (unsigned int*)((char*)pCrc + 0x24);
```

✅ 必须:
```c
action->currentFrame = (unsigned int)(time * GB_FRAMES_PER_SECOND);
if (state == GB_ACTION_TRANSITION_MAGIC)  // 'over' in ASCII
pCrc = (unsigned int*)((char*)pCrc + sizeof(gbActionState));
```

**允许的"魔数"**:
- 0, 1, -1（通用常量）
- 结构体 sizeof 值（如果直接用 `sizeof()` 表达式）
- NULL / 0x3f800000（已知为 1.0f 的 IEEE754 表示，用 `1.0f` 代替）

**常见常量定义位置**: `include/gbengine/gbengine_constants.h`（如不存在则创建）

### 4. 虚函数表必须有名字

❌ 不允许:
```c
void** vtable = *(void***)m_pActorDef;
typedef void (__thiscall *Fn)(void*, int);
Fn func = (Fn)vtable[5];
func(m_pActorDef, idx);
```

✅ 必须:
```c
m_pActorDef->RenderDef(this, renderInfo);
```

如果虚函数还没命名，先在头文件声明，用 `_vfXX` 占位。

## 检查流程

1. **扫描裸偏移**: 在目标文件中搜索 `this +`, `+ 0x`, `(char*)`, `*(int*)(` 等模式
2. **扫描魔数**: 搜索 `0x` 开头的十六进制常量（排除地址注释和 sizeof）
3. **扫描 vtable hack**: 搜索 `void**`, `(code*)`, `typedef.*Fn` 等模式
4. **验证结构体**: 确认所有被访问的结构体在 header 中有正确定义
5. **报告问题**: 列出所有违规项，按严重程度排序

## 输出格式

```
文件: XXX.cpp
质量检查: PASS / FAIL (N issues)

违规列表:
  Line 123: 裸偏移 *(int*)(this + 0x58) → 应使用 m_pActorDef
  Line 234: 魔数 0x24 → 应使用 sizeof(gbActionState)
  Line 345: vtable hack → 应在 gbActorDef 中声明虚函数

需要新增/修改的头文件:
  include/gbengine/gbActor.h: 添加 EnableActionTransMtlDef 声明
  include/gbengine/gbengine_constants.h: 添加 GB_FRAMES_PER_SECOND
```

## 修复指导

发现问题后:
1. 先修复头文件（添加结构体/常量/虚函数声明）
2. 再修改源文件（替换裸偏移/魔数/vtable hack）
3. 编译验证（确保修复后仍然编译通过）
4. 重新跑字节对比（确保匹配率没有下降）
5. 如果匹配率下降了，说明质量修复改变了代码语义——回退并分析原因
