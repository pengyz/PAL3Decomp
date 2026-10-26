# PAL3 反编译项目

**目标**：从 PAL3.exe（MSVC 6.0 SP0 编译）生成可运行的 C++ 源码，逐步实现字节一致。

## ⚠️ 方向转向（2026-10-27）

**从"字节匹配优先"转向"逐步代换（可运行优先）"**：

```
原方向：codegen 全量输出 → 字节比对 → 修复 → 字节一致
新方向：主入口（WinMain）→ mock 解锁 → 可编译 → 调用链推进 → 可运行 → 函数迁移（字节一致）
```

**理由**：
1. **字节一致缺口大**（S2 135/209·L1 184/571）——信心不足
2. **游戏不可运行**（链接层盲区）——隐患
3. **增量可编译**（每步验证）——信心逐步建立

**策略**：逐步代换（codegen 成果吸收+增量验证+字节一致收敛）

## 迁移路径

### 阶段 1：可编译基（主入口+mock）
- [x] WinMain 定位（`_WinMain@16` @ 0x541900）
- [x] platform/windows/WinMain.cpp 建立（迁移起点）
- [ ] 关键接口 mock（窗口/消息/资源）
- [ ] 编译+链接（MSVC 6.0）

### 阶段 2：可运行（调用链推进）
- [ ] 游戏部署（编译产物→游戏目录替换 exe）
- [ ] 调用链迁移（WinMain→初始化→主循环）
- [ ] 运行验证（游戏启动→无崩溃）

### 阶段 3：字节一致（函数迁移）
- [ ] 函数级迁移（codegen→byte-identical）
- [ ] 字节比对（每函数 L1）
- [ ] 全量收敛（字节匹配）

## 平台分层

```
pal3/src/platform/
├── windows/    # Windows 入口（WinMain）——当前
├── linux/      # Linux 适配——后续
└── android/    # Android 适配——后续
pal3/src/core/  # 平台无关（游戏逻辑）
```

## 构建

```bash
# codegen（全量）
python pipeline/cli.py codegen all

# 部署（游戏目录）
python pipeline/cli.py deploy

# 字节比对
python pipeline/cli.py match
```

## 纪律

- **annotation=真值源**（git 版控）——IDB=派生物（可重建）
- **病灶层检查**（动手前）——消费者读哪个文件/声明
- **验证前全链**（apply→export→codegen→probe）
- **衰退分析**（先分析后回退）——修复优先
