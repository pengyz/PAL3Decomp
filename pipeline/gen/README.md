# Codegen Pipeline

从 IDA 反编译 JSON 生成 MSVC 6.0 兼容的 C++ 源码。

## 架构

```
codegen.py              入口（子命令: headers / cpp / all）
data.py                 DataStore 单例（一次性加载 annotations + binary）
stages/
  collect.py            从 decomp JSON 收集函数，按类分组
  transform.py          Transform pipeline runner
  emit_headers.py       生成 include/pal3/gen/*.h
  emit_cpp.py           生成 src/pal3/**/*.cpp
transforms/             可插拔代码变换模块
  ida_cleanup.py        IDA 无效代码清理 (order 0-99)
  type_fixes.py         类型修复 (order 100-199)
  oop.py                OOP 调用变换 (order 200-299)
  names.py              名称解析替换 (order 300-399)
  compat.py             VC6 兼容性修复 (order 400-499)
```

## 用法

```bash
# 全量生成
python pipeline/gen/codegen.py all

# 只生成 headers
python pipeline/gen/codegen.py headers

# 只生成 cpp
python pipeline/gen/codegen.py cpp

# 只生成特定类
python pipeline/gen/codegen.py cpp CameraCtrl
```

## 添加新的 Transform

在 `transforms/` 目录下创建或修改 `.py` 文件：

```python
# transforms/my_fix.py
import re
from . import register

@register(order=150)  # 100-199 = type_fixes 区间
def fix_something(code, ctx):
    """修复某个 Hex-Rays 输出问题。"""
    return re.sub(r'broken_pattern', 'fixed', code)
```

Transform 签名：`(code: str, ctx: TransformContext) -> str`

- `ctx.cls_name` — 类名（free function 时为空）
- `ctx.method_name` — 方法名
- `ctx.is_ctor` / `ctx.is_dtor` — 是否构造/析构函数
- `ctx.is_free_function` — 是否自由函数
- `ctx.sig` — IDA 函数签名

全局数据通过 `from ..data import store` 访问。

## Order 约定

| 范围 | 模块 | 职责 |
|------|------|------|
| 0-99 | ida_cleanup | 删除 IDA 无效代码 |
| 100-199 | type_fixes | 类型转换修复 |
| 200-299 | oop | OOP 方法调用变换 |
| 300-399 | names | 名称解析（thunk/global/literal） |
| 400-499 | compat | VC6 编译器兼容性 |

低 order 先执行。同一模块内按定义顺序。

## 设计原则

- 每个 transform 是纯函数（输入 code → 输出 code）
- Transform 不依赖执行顺序外的隐式状态
- 全局数据集中在 DataStore，transform 只读访问
- 全量生成，无增量缓存——简单可靠
