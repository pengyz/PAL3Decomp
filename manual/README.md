# 手动改写域（manual/）——独立于 codegen

## 目的
**手动改写版本**（迁移产物）——独立于 codegen（pal3/src=生成物·codegen 覆盖）。

## 目录设计
```
manual/pal3/
├── platform/
│   ├── windows/    # Windows 入口（WinMain）——当前
│   ├── linux/      # Linux 适配——后续
│   └── android/    # Android 适配——后续
├── core/           # 平台无关（游戏逻辑）——迁移
└── mock/           # 关键接口 mock（临时——代换替）
```

## 与 codegen 的关系
| 域 | 内容 | 覆盖 | 版控 |
|---|---|---|---|
| `pal3/src/` | codegen 生成物 | codegen 覆盖 | gitignore |
| `manual/pal3/` | 手动改写（迁移）| **不覆盖** | **git 跟踪** |

## 迁移流程
```
codegen 输出（pal3/src）→ 搬移（manual/pal3）→ 手动改写（byte-identical）→ 编译→运行
```

## 纪律
- **手动改写入 manual/**（禁直改 pal3/src——codegen 覆盖）
- **codegen 成果吸收**（pal3/src→manual/pal3 搬移）
- **字节一致验证**（每函数 L1——原 exe 比对）
