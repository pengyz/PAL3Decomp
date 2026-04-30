# PAL3.exe Phase 2: SCE 脚本引擎 - 实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 实现完整的 SCE 字节码虚拟机，能执行游戏脚本（140 个操作码）

**Architecture:** VM 核心 → 操作码实现 → 脚本加载 → CPK 集成

**Tech Stack:** C/C++, 自定义字节码格式, CPK 文件系统

**工期:** 1.5 个月  
**函数数:** 200-300 个  
**代码行数:** 5000-8000 行  
**重要性:** ⭐⭐⭐⭐⭐ (游戏逻辑核心)

---

## 前置条件

- ✅ Phase 1 已完成（程序框架）
- ✅ 游戏能启动到主循环
- ✅ 参考文档：`docs/sce_opcodes.md`（完整操作码表）
- ✅ OpenPAL3 源码参考（Rust 实现）

---

## 文件结构

```
src/pal3/script/
├── vm_core.h                   # VM 核心声明
├── vm_core.cpp                 # VM 核心实现
├── vm_stack.cpp                # 栈操作
├── opcodes.h                   # 操作码枚举
├── opcodes_basic.cpp           # 基本操作码（栈、算术、逻辑）
├── opcodes_control.cpp         # 流程控制操作码
├── opcodes_game.cpp            # 游戏特定操作码
├── script_loader.h             # 脚本加载
├── script_loader.cpp
├── script_manager.h            # 脚本管理器
├── script_manager.cpp
└── cpk_interface.cpp           # CPK 文件系统接口

include/pal3/
├── script_types.h              # 脚本相关类型
└── sce_format.h                # SCE 文件格式定义

docs/pal3/
└── sce_vm_architecture.md      # VM 架构文档
```

---

## SCE VM 架构概览

```
┌─────────────────────────────────────────┐
│         SCE Virtual Machine             │
├─────────────────────────────────────────┤
│  Program Counter (PC)                   │
│  Stack Pointer (SP)                     │
│  Stack[256]                             │
│  Registers[16]                          │
│  Code Memory                            │
│  String Table                           │
│  Running State                          │
└─────────────────────────────────────────┘
         ↓
    ┌────────┐
    │ Opcode │ → 解码 → 执行
    └────────┘
         ↓
    ┌──────────────────────────┐
    │ 操作码分类 (140 个)      │
    ├──────────────────────────┤
    │ 栈操作 (10)              │
    │ 算术运算 (15)            │
    │ 逻辑运算 (10)            │
    │ 比较运算 (8)             │
    │ 流程控制 (15)            │
    │ 内存操作 (12)            │
    │ 字符串操作 (8)           │
    │ 游戏特定 (60+)           │
    └──────────────────────────┘
```

---

## Task 1: VM 核心数据结构

**目标:** 定义 VM 的核心数据结构

**Files:**
- Create: `include/pal3/script_types.h`
- Create: `include/pal3/sce_format.h`

**关键结构:**

```cpp
// include/pal3/script_types.h

// VM 状态
enum VMState {
    VM_STATE_STOPPED = 0,
    VM_STATE_RUNNING,
    VM_STATE_PAUSED,
    VM_STATE_WAITING,
    VM_STATE_ERROR
};

// VM 结构
struct SCE_VM {
    // 代码和数据
    uint8_t*    code;           // 字节码
    uint32_t    codeSize;       // 代码大小
    char**      stringTable;    // 字符串表
    uint32_t    stringCount;    // 字符串数量
    
    // 执行状态
    uint32_t    pc;             // 程序计数器
    int32_t     sp;             // 栈指针
    uint32_t    stack[256];     // 栈
    uint32_t    registers[16];  // 寄存器
    
    // 运行状态
    VMState     state;          // VM 状态
    int32_t     waitFrames;     // 等待帧数
    uint32_t    errorCode;      // 错误代码
    
    // 用户数据
    void*       userData;       // 用户数据指针
};

// include/pal3/sce_format.h

// SCE 文件头
#pragma pack(push, 1)
struct SCE_Header {
    uint32_t    magic;          // 'SCE\0'
    uint32_t    version;        // 版本号
    uint32_t    codeOffset;     // 代码偏移
    uint32_t    codeSize;       // 代码大小
    uint32_t    stringOffset;   // 字符串表偏移
    uint32_t    stringSize;     // 字符串表大小
    uint32_t    reserved[4];    // 保留
};
#pragma pack(pop)

#define SCE_MAGIC 0x00454353  // 'SCE\0'
```

---

## Task 2: VM 核心实现（Week 1-2）

**目标:** 实现 VM 的创建、销毁和主执行循环

**Functions:** 8-12 个

**关键函数:**
```cpp
// src/pal3/script/vm_core.cpp

// 0x004XXXXX  SCE_VM_Create
SCE_VM* SCE_VM_Create();

// 0x004XXXXX  SCE_VM_Destroy
void SCE_VM_Destroy(SCE_VM* vm);

// 0x004XXXXX  SCE_VM_LoadBytecode
BOOL SCE_VM_LoadBytecode(SCE_VM* vm, const uint8_t* code, uint32_t size);

// 0x004XXXXX  SCE_VM_Execute
void SCE_VM_Execute(SCE_VM* vm);

// 0x004XXXXX  SCE_VM_Step
BOOL SCE_VM_Step(SCE_VM* vm);

// 0x004XXXXX  SCE_VM_Reset
void SCE_VM_Reset(SCE_VM* vm);

// 0x004XXXXX  SCE_VM_Error
void SCE_VM_Error(SCE_VM* vm, const char* format, ...);
```

**VM 主循环结构:**
```cpp
void SCE_VM_Execute(SCE_VM* vm) {
    vm->state = VM_STATE_RUNNING;
    
    while (vm->state == VM_STATE_RUNNING && vm->pc < vm->codeSize) {
        // 取指令
        uint8_t opcode = vm->code[vm->pc++];
        
        // 解码执行
        switch (opcode) {
            case OP_NOP:
                break;
            case OP_PUSH:
                SCE_OP_Push(vm);
                break;
            case OP_POP:
                SCE_OP_Pop(vm);
                break;
            // ... 其他 140 个操作码
            case OP_HALT:
                vm->state = VM_STATE_STOPPED;
                break;
            default:
                SCE_VM_Error(vm, "Unknown opcode: 0x%02X", opcode);
                vm->state = VM_STATE_ERROR;
                break;
        }
        
        // 检查暂停
        if (vm->state == VM_STATE_PAUSED) {
            break;
        }
    }
}
```

---

## Task 3: 栈操作实现（~20 个函数）

**目标:** 实现所有栈相关操作

**操作码 (10 个):**
- `OP_PUSH` - 压栈立即数
- `OP_POP` - 弹栈
- `OP_DUP` - 复制栈顶
- `OP_SWAP` - 交换栈顶两元素
- `OP_LOAD` - 从寄存器加载到栈
- `OP_STORE` - 从栈保存到寄存器
- `OP_LOADG` - 从全局变量加载
- `OP_STOREG` - 保存到全局变量
- `OP_LOADL` - 从局部变量加载
- `OP_STOREL` - 保存到局部变量

**实现示例:**
```cpp
// src/pal3/script/vm_stack.cpp

// 0x004XXXXX  SCE_Stack_Push
inline void SCE_Stack_Push(SCE_VM* vm, uint32_t value) {
    if (vm->sp >= 255) {
        SCE_VM_Error(vm, "Stack overflow");
        return;
    }
    vm->stack[++vm->sp] = value;
}

// 0x004XXXXX  SCE_Stack_Pop
inline uint32_t SCE_Stack_Pop(SCE_VM* vm) {
    if (vm->sp < 0) {
        SCE_VM_Error(vm, "Stack underflow");
        return 0;
    }
    return vm->stack[vm->sp--];
}

// 0x004XXXXX  SCE_OP_Push
void SCE_OP_Push(SCE_VM* vm) {
    // 读取 4 字节立即数
    uint32_t value = *(uint32_t*)(&vm->code[vm->pc]);
    vm->pc += 4;
    SCE_Stack_Push(vm, value);
}

// 0x004XXXXX  SCE_OP_Pop
void SCE_OP_Pop(SCE_VM* vm) {
    SCE_Stack_Pop(vm);
}

// 0x004XXXXX  SCE_OP_Dup
void SCE_OP_Dup(SCE_VM* vm) {
    if (vm->sp < 0) {
        SCE_VM_Error(vm, "Stack empty");
        return;
    }
    uint32_t value = vm->stack[vm->sp];
    SCE_Stack_Push(vm, value);
}

// 0x004XXXXX  SCE_OP_Swap
void SCE_OP_Swap(SCE_VM* vm) {
    if (vm->sp < 1) {
        SCE_VM_Error(vm, "Not enough elements on stack");
        return;
    }
    uint32_t temp = vm->stack[vm->sp];
    vm->stack[vm->sp] = vm->stack[vm->sp - 1];
    vm->stack[vm->sp - 1] = temp;
}
```

**字节匹配提示:**
- 使用 `inline` 或 `__forceinline` 标记热点函数
- 栈指针递增: `++vm->sp` 而不是 `vm->sp++; vm->sp`
- 边界检查使用 `>=` 而不是 `>`

---

## Task 4: 算术和逻辑运算（~30 个函数）

**目标:** 实现算术、逻辑、比较操作

**算术操作码 (15 个):**
- ADD, SUB, MUL, DIV, MOD, NEG, INC, DEC, ABS, MIN, MAX, CLAMP 等

**逻辑操作码 (10 个):**
- AND, OR, NOT, XOR, SHL, SHR, SAR 等

**比较操作码 (8 个):**
- EQ, NE, LT, LE, GT, GE, CMP 等

**实现示例:**
```cpp
// src/pal3/script/opcodes_basic.cpp

// 0x004XXXXX  SCE_OP_Add
void SCE_OP_Add(SCE_VM* vm) {
    uint32_t b = SCE_Stack_Pop(vm);
    uint32_t a = SCE_Stack_Pop(vm);
    SCE_Stack_Push(vm, a + b);
}

// 0x004XXXXX  SCE_OP_Sub
void SCE_OP_Sub(SCE_VM* vm) {
    uint32_t b = SCE_Stack_Pop(vm);
    uint32_t a = SCE_Stack_Pop(vm);
    SCE_Stack_Push(vm, a - b);
}

// 0x004XXXXX  SCE_OP_Mul
void SCE_OP_Mul(SCE_VM* vm) {
    uint32_t b = SCE_Stack_Pop(vm);
    uint32_t a = SCE_Stack_Pop(vm);
    SCE_Stack_Push(vm, a * b);
}

// 0x004XXXXX  SCE_OP_Div
void SCE_OP_Div(SCE_VM* vm) {
    uint32_t b = SCE_Stack_Pop(vm);
    uint32_t a = SCE_Stack_Pop(vm);
    if (b == 0) {
        SCE_VM_Error(vm, "Division by zero");
        SCE_Stack_Push(vm, 0);
        return;
    }
    SCE_Stack_Push(vm, a / b);
}

// 逻辑运算
// 0x004XXXXX  SCE_OP_And
void SCE_OP_And(SCE_VM* vm) {
    uint32_t b = SCE_Stack_Pop(vm);
    uint32_t a = SCE_Stack_Pop(vm);
    SCE_Stack_Push(vm, a & b);
}

// 比较运算
// 0x004XXXXX  SCE_OP_Equal
void SCE_OP_Equal(SCE_VM* vm) {
    uint32_t b = SCE_Stack_Pop(vm);
    uint32_t a = SCE_Stack_Pop(vm);
    SCE_Stack_Push(vm, (a == b) ? 1 : 0);
}
```

---

## Task 5: 流程控制操作码（~25 个函数）

**目标:** 实现跳转、调用、返回等流程控制

**流程控制操作码 (15 个):**
- JMP, JZ, JNZ, CALL, RET, IF, ELSE, ENDIF 等

**关键实现:**
```cpp
// src/pal3/script/opcodes_control.cpp

// 0x004XXXXX  SCE_OP_Jump
void SCE_OP_Jump(SCE_VM* vm) {
    // 读取跳转目标地址（4 字节）
    uint32_t target = *(uint32_t*)(&vm->code[vm->pc]);
    vm->pc = target;
}

// 0x004XXXXX  SCE_OP_JumpIfZero
void SCE_OP_JumpIfZero(SCE_VM* vm) {
    uint32_t target = *(uint32_t*)(&vm->code[vm->pc]);
    vm->pc += 4;
    
    uint32_t condition = SCE_Stack_Pop(vm);
    if (condition == 0) {
        vm->pc = target;
    }
}

// 0x004XXXXX  SCE_OP_Call
void SCE_OP_Call(SCE_VM* vm) {
    uint32_t target = *(uint32_t*)(&vm->code[vm->pc]);
    vm->pc += 4;
    
    // 保存返回地址到栈
    SCE_Stack_Push(vm, vm->pc);
    
    // 跳转到目标
    vm->pc = target;
}

// 0x004XXXXX  SCE_OP_Return
void SCE_OP_Return(SCE_VM* vm) {
    // 从栈恢复返回地址
    vm->pc = SCE_Stack_Pop(vm);
}
```

---

## Task 6: 游戏特定操作码（Week 3-5, ~80 个函数）

**目标:** 实现所有游戏相关的操作码（最大工作量）

**分类 (60+ 个操作码):**

### UI 相关 (15 个)
- `OP_SHOW_DIALOG` - 显示对话框
- `OP_SHOW_CHOICE` - 显示选择框
- `OP_SHOW_MESSAGE` - 显示消息
- `OP_HIDE_DIALOG` - 隐藏对话框
- `OP_SHOW_MENU` - 显示菜单
- 等等...

### 场景相关 (20 个)
- `OP_LOAD_SCENE` - 加载场景
- `OP_CHANGE_SCENE` - 切换场景
- `OP_CAMERA_MOVE` - 移动相机
- `OP_CAMERA_ZOOM` - 缩放相机
- `OP_CHARACTER_MOVE` - 移动角色
- `OP_CHARACTER_FACE` - 转向
- `OP_CHARACTER_ANIM` - 播放动画
- 等等...

### 战斗相关 (10 个)
- `OP_START_BATTLE` - 开始战斗
- `OP_END_BATTLE` - 结束战斗
- `OP_ADD_ENEMY` - 添加敌人
- 等等...

### 音频/视频 (10 个)
- `OP_PLAY_MUSIC` - 播放音乐
- `OP_STOP_MUSIC` - 停止音乐
- `OP_PLAY_SOUND` - 播放音效
- `OP_PLAY_VIDEO` - 播放视频
- 等等...

### 游戏状态 (15 个)
- `OP_SET_FLAG` - 设置标志
- `OP_GET_FLAG` - 获取标志
- `OP_ADD_ITEM` - 添加物品
- `OP_REMOVE_ITEM` - 移除物品
- `OP_ADD_MONEY` - 增加金钱
- `OP_SAVE_GAME` - 保存游戏
- `OP_LOAD_GAME` - 加载游戏
- 等等...

**实现示例:**
```cpp
// src/pal3/script/opcodes_game.cpp

// 0x004XXXXX  SCE_OP_ShowDialog
void SCE_OP_ShowDialog(SCE_VM* vm) {
    // 读取对话 ID
    uint32_t dialogID = SCE_Stack_Pop(vm);
    
    // 调用 UI 系统显示对话
    UI_ShowDialog(dialogID);
    
    // 暂停 VM，等待对话关闭
    vm->state = VM_STATE_PAUSED;
}

// 0x004XXXXX  SCE_OP_PlayMusic
void SCE_OP_PlayMusic(SCE_VM* vm) {
    // 读取音乐 ID
    uint32_t musicID = SCE_Stack_Pop(vm);
    
    // 获取音乐文件路径（从字符串表）
    if (musicID >= vm->stringCount) {
        SCE_VM_Error(vm, "Invalid music ID: %d", musicID);
        return;
    }
    
    const char* musicPath = vm->stringTable[musicID];
    
    // 调用音频系统
    gbengine::gbAudioManager_PlayMusic(g_pAudioManager, musicPath);
}

// 0x004XXXXX  SCE_OP_LoadScene
void SCE_OP_LoadScene(SCE_VM* vm) {
    uint32_t sceneID = SCE_Stack_Pop(vm);
    
    // 获取场景文件路径
    const char* scenePath = vm->stringTable[sceneID];
    
    // 加载场景
    Scene_Load(scenePath);
    
    // 暂停脚本，等待场景加载完成
    vm->state = VM_STATE_WAITING;
    vm->waitFrames = 1;  // 等待下一帧
}

// 0x004XXXXX  SCE_OP_SetFlag
void SCE_OP_SetFlag(SCE_VM* vm) {
    uint32_t value = SCE_Stack_Pop(vm);
    uint32_t flagID = SCE_Stack_Pop(vm);
    
    // 设置全局标志（保存在游戏存档中）
    GameState_SetFlag(flagID, value);
}
```

**实施策略:**
1. 先实现存根（stub）版本，返回成功但不执行实际逻辑
2. 按优先级实现：对话 → 场景切换 → 音乐 → 其他
3. 每实现 20 个操作码测试一次
4. 使用简单脚本测试（如开场对话）

---

## Task 7: 脚本加载和 CPK 集成（Week 6, ~15 个函数）

**目标:** 实现 SCE 文件加载和 CPK 文件系统集成

**Files:**
- `src/pal3/script/script_loader.cpp`
- `src/pal3/script/cpk_interface.cpp`

**关键函数:**
```cpp
// script_loader.cpp

// 0x004XXXXX  SCE_LoadFile
BOOL SCE_LoadFile(const char* filename, SCE_VM* vm);

// 0x004XXXXX  SCE_ParseHeader
BOOL SCE_ParseHeader(const uint8_t* data, SCE_Header* header);

// 0x004XXXXX  SCE_LoadStringTable
BOOL SCE_LoadStringTable(SCE_VM* vm, const uint8_t* data, uint32_t size);

// cpk_interface.cpp

// 0x004XXXXX  CPK_LoadFile
uint8_t* CPK_LoadFile(const char* filename, uint32_t* outSize);

// 0x004XXXXX  CPK_Initialize
BOOL CPK_Initialize();
```

**SCE 加载流程:**
```cpp
BOOL SCE_LoadFile(const char* filename, SCE_VM* vm) {
    // 1. 从 CPK 包加载文件
    uint32_t fileSize;
    uint8_t* data = CPK_LoadFile(filename, &fileSize);
    if (!data) {
        return FALSE;
    }
    
    // 2. 解析文件头
    SCE_Header header;
    if (!SCE_ParseHeader(data, &header)) {
        free(data);
        return FALSE;
    }
    
    // 3. 验证魔数和版本
    if (header.magic != SCE_MAGIC) {
        free(data);
        return FALSE;
    }
    
    // 4. 加载字节码
    SCE_VM_LoadBytecode(vm, 
                        data + header.codeOffset, 
                        header.codeSize);
    
    // 5. 加载字符串表
    SCE_LoadStringTable(vm,
                        data + header.stringOffset,
                        header.stringSize);
    
    free(data);
    return TRUE;
}
```

---

## Task 8: 脚本管理器（~10 个函数）

**目标:** 实现脚本缓存和管理

**Functions:**
```cpp
// script_manager.cpp

// 0x004XXXXX  ScriptManager_Initialize
BOOL ScriptManager_Initialize();

// 0x004XXXXX  ScriptManager_Shutdown
void ScriptManager_Shutdown();

// 0x004XXXXX  ScriptManager_LoadScript
SCE_VM* ScriptManager_LoadScript(const char* filename);

// 0x004XXXXX  ScriptManager_UnloadScript
void ScriptManager_UnloadScript(SCE_VM* vm);

// 0x004XXXXX  ScriptManager_UpdateAll
void ScriptManager_UpdateAll(float deltaTime);
```

**脚本缓存结构:**
```cpp
#define MAX_CACHED_SCRIPTS 32

struct ScriptCache {
    char        filename[256];
    SCE_VM*     vm;
    uint32_t    refCount;
    BOOL        active;
};

static ScriptCache g_scriptCache[MAX_CACHED_SCRIPTS];
static int g_scriptCacheCount = 0;
```

---

## Task 9: Phase 2 测试

**测试脚本集合:**

1. **基本测试** - `test_basic.sce`
   ```
   ; 测试栈操作
   PUSH 10
   PUSH 20
   ADD
   POP
   HALT
   ```

2. **对话测试** - `test_dialog.sce`
   ```
   ; 测试对话显示
   PUSH 0          ; 对话 ID
   SHOW_DIALOG
   HALT
   ```

3. **音乐测试** - `test_music.sce`
   ```
   ; 测试音乐播放
   PUSH 1          ; 音乐 ID
   PLAY_MUSIC
   PUSH 5000       ; 等待 5 秒
   WAIT
   STOP_MUSIC
   HALT
   ```

4. **场景测试** - `test_scene.sce`
   ```
   ; 测试场景切换
   PUSH 0          ; 场景 ID
   LOAD_SCENE
   HALT
   ```

---

## Phase 2 验收标准

### 功能验收
- [ ] VM 能加载和执行字节码
- [ ] 所有 140 个操作码实现完成
- [ ] 能执行简单测试脚本
- [ ] 能显示开场对话
- [ ] 能播放背景音乐
- [ ] 能切换场景
- [ ] 脚本缓存工作正常

### 代码验收
- [ ] 实现 200-300 个函数
- [ ] 代码结构清晰
- [ ] 注释完整
- [ ] 无内存泄漏

### 字节匹配验收
- [ ] VM 核心循环 100% 匹配
- [ ] 常用操作码（前 30 个）95%+ 匹配
- [ ] 整体匹配率 ≥ 80%

### 测试验收
- [ ] 所有 4 个测试脚本通过
- [ ] 能执行开场剧情脚本
- [ ] VM 错误处理正确
- [ ] 无崩溃运行 10 分钟

---

## 字节匹配技巧（Phase 2 特定）

**VM 主循环优化:**
- 使用跳转表而不是大 if-else 链
- 操作码解码使用位操作
- 热点函数标记 `__forceinline`

**示例:**
```cpp
// 跳转表方式（MSVC 7.1 会优化为跳转表）
switch (opcode) {
    case 0x00: SCE_OP_Nop(vm); break;
    case 0x01: SCE_OP_Push(vm); break;
    case 0x02: SCE_OP_Pop(vm); break;
    // ... 连续的 case，编译器生成跳转表
}

// 而不是：
if (opcode == 0x00) SCE_OP_Nop(vm);
else if (opcode == 0x01) SCE_OP_Push(vm);
else if (opcode == 0x02) SCE_OP_Pop(vm);
// ... (生成 if-else 链，性能差)
```

---

## 参考资源

- `docs/sce_opcodes.md` - 完整操作码表
- OpenPAL3: `yaobow/shared/src/scripting/sce/` - Rust 参考实现
- PAL3patch: `extra/PAL3patch/notes/pal3/script.txt` - 逆向笔记

---

**Phase 2 计划完成！准备进入 Phase 3：UI 系统**
