# PAL3 反编译 - 渐进式工作流程

## 🎯 核心原则

**永远保持代码可编译** - 每次添加新代码后，必须验证编译通过。

---

## 📋 工作流程（迭代循环）

```
┌─────────────────────────────────────────────────────────┐
│                                                         │
│  1. 选择1-3个简单函数                                   │
│     ↓                                                   │
│  2. 添加到源文件                                        │
│     ↓                                                   │
│  3. 编译验证         ← 必须通过                         │
│     ↓                                                   │
│  4. 提交到 Git                                          │
│     ↓                                                   │
│  5. 继续下一批 ────────┘                                │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

### 关键点：
- ✅ **小步迭代** - 每次只添加 1-3 个函数
- ✅ **立即验证** - 添加后马上编译
- ✅ **频繁提交** - 每次验证通过后提交 Git
- ❌ **不要堆积** - 不要写完一大堆代码再编译

---

## 🔧 使用的工具

### 1. 持续验证脚本

```batch
# 验证当前代码可编译
python verify_build.py
```

这个脚本会：
- 清理旧构建
- 重新编译所有源文件
- 检查是否有编译错误
- 生成构建报告

### 2. 快速编译检查

```batch
# 只编译，不清理
cmake --build build/verify
```

### 3. 增量添加函数

```batch
# 第1步：选择函数
# 查看 asm/gbengine/SimpleFunctionName.json

# 第2步：添加到源文件
notepad src/gbengine/module_name.cpp

# 第3步：验证编译
python verify_build.py

# 第4步：如果通过，提交
git add src/gbengine/module_name.cpp
git commit -m "Add SimpleFunctionName to gbengine"
```

---

## 📊 项目阶段

### 阶段 0: 验证基础（当前）✅

**目标**: 确认已有代码可编译

```batch
python verify_build.py
```

**期望结果**:
- ✅ topo.dll 编译成功
- ✅ 7个文件，2,340行代码
- ✅ 无编译错误

---

### 阶段 1: topo.dll 完善（如需二进制匹配）

**目标**: 完成 topo.dll 剩余函数，验证二进制匹配

**工作量**: 414 个函数，已完成 ~100 个，剩余 ~314 个

**流程**:
```batch
# 每次迭代
1. 选择 2-3 个函数
2. 添加到 src/topo/
3. python verify_build.py
4. git commit
5. 重复
```

**里程碑**:
- [ ] 100% 函数反编译完成
- [ ] 使用 VC6 编译通过
- [ ] 二进制字节级匹配（可选）

---

### 阶段 2: gbengine.dll 启动

**目标**: 创建 gbengine.dll 基础框架

**第一批目标**（10个最简单的函数）:
1. 构造函数/析构函数
2. 简单的 getter/setter
3. 内联函数

**流程**:
```batch
# 1. 创建目录结构
mkdir src/gbengine

# 2. 创建第一个源文件
notepad src/gbengine/gbRefObject.cpp

# 3. 添加 2-3 个最简单的函数
# - 构造函数
# - 析构函数
# - AddRef/Release

# 4. 验证编译
python verify_build.py

# 5. 提交
git add src/gbengine/gbRefObject.cpp
git commit -m "Add gbRefObject basic methods"
```

**里程碑**:
- [ ] 创建基础类框架（10个类）
- [ ] 每个类 2-5 个简单函数
- [ ] gbengine.dll 可编译（即使不完整）

---

### 阶段 3: gbengine.dll 模块化反编译

**目标**: 按模块逐步完成

**模块划分**:
```
src/gbengine/
  ├── core/          # 核心类（gbRefObject, gbChain1D）
  ├── render/        # 渲染系统
  ├── input/         # 输入系统
  ├── audio/         # 音频系统
  ├── resource/      # 资源管理
  └── scene/         # 场景管理
```

**每个模块**:
1. 先反编译 10-20 个最简单的函数
2. 验证编译
3. 提交
4. 逐步增加复杂度

---

### 阶段 4: PAL3.exe（最终目标）

需要先脱壳，流程与 gbengine.dll 类似。

---

## 🔍 持续验证检查清单

### 每次添加代码前
- [ ] 当前代码可编译
- [ ] 理解要添加的函数逻辑
- [ ] 准备好头文件和依赖

### 每次添加代码后
- [ ] 运行 `python verify_build.py`
- [ ] 检查编译错误
- [ ] 修复错误（如有）
- [ ] 提交到 Git

### 每天结束时
- [ ] 确保主分支可编译
- [ ] 更新进度文档
- [ ] 备份工作

---

## 📈 进度追踪

### 当前状态（2026-05-01）

```
topo.dll:       ████████░░░░░░░░░░░░  24% (100/414)
gbengine.dll:   ░░░░░░░░░░░░░░░░░░░░   0% (0/3213)
PAL3.exe:       ░░░░░░░░░░░░░░░░░░░░   0% (需脱壳)
```

### 目标（下一个里程碑）

```
topo.dll:       ████████████████████ 100% (414/414) ✅
gbengine.dll:   ██░░░░░░░░░░░░░░░░░░   5% (160/3213)
PAL3.exe:       ░░░░░░░░░░░░░░░░░░░░   0%
```

---

## 🎯 本周目标（建议）

### 立即执行（今天）

1. **验证基础**
   ```batch
   python verify_build.py
   ```
   确认 topo.dll 可编译。

2. **提交当前状态**
   ```batch
   git add -A
   git commit -m "Initial toolchain setup complete"
   ```

### 短期目标（本周）

选择以下之一：

**选项 A: 完善 topo.dll**（如需二进制匹配）
- 每天反编译 10-20 个函数
- 每天提交 2-3 次
- 本周完成 50-100 个函数

**选项 B: 启动 gbengine.dll**（快速推进）
- 创建 5-10 个基础类
- 每个类 2-5 个简单函数
- 建立模块框架

---

## 🚨 避免的陷阱

❌ **不要做**:
- 一次写几百行代码再编译
- 长时间不提交 Git
- 跳过编译验证步骤
- 堆积大量未测试的代码

✅ **正确做法**:
- 小步快跑，频繁验证
- 遇到编译错误立即修复
- 每个工作单元都提交
- 保持主分支随时可编译

---

## 📝 提交消息规范

```bash
# 好的提交消息
git commit -m "Add gbVec3D::Length and IsValid methods"
git commit -m "Add gbMatrix4 constructor and destructor"
git commit -m "Fix compilation error in gbQuaternion.cpp"

# 不好的提交消息
git commit -m "update"
git commit -m "wip"
git commit -m "fix bug"
```

---

## 🔄 每日工作循环

```bash
# 早上：同步和验证
git pull
python verify_build.py

# 工作：小步迭代
# 1. 选择 2-3 个函数
# 2. 添加代码
# 3. python verify_build.py
# 4. git commit
# 5. 重复 3-5 次

# 晚上：总结和推送
git log --oneline -10  # 查看今天的进度
git push
```

---

## 📊 成功指标

### 每天
- ✅ 至少 2 次成功的编译+提交循环
- ✅ 添加 5-10 个函数
- ✅ 0 个未修复的编译错误

### 每周
- ✅ 30-50 个新函数
- ✅ 10-20 次 Git 提交
- ✅ 1 个模块基本完成

---

## 🎉 下一步行动

**立即执行**（10分钟）:
```batch
# 1. 验证当前状态
python verify_build.py

# 2. 如果通过，提交
git add -A
git commit -m "Setup complete: topo.dll compiles successfully"
git log --oneline -5
```

**今天的目标**（1-2小时）:
- 验证 topo.dll 编译通过 ✅
- 提交当前状态
- 决定下一步方向（完善 topo 或启动 gbengine）

**本周目标**:
- 建立稳定的工作节奏
- 完成 50+ 个函数
- 保持代码库随时可编译
