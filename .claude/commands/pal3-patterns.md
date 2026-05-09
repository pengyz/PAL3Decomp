IDA 反编译常见模式及其正确 C++ 还原参考。

在 /pal3-step 和 /pal3-iter 反编译时必须参考此文件，避免照搬 IDA 输出。

## 1. new 表达式

**IDA 输出（错误）：**
```c
v6 = operator new(0x162D8u);
if (v6)
    v7 = CCBSystem_ctor(v6);
else
    v7 = 0;
```

**正确 C++：**
```cpp
CCBSystem *pCBSystem = new CCBSystem();
```

编译器会自动生成：operator new → 判 NULL → 调构造函数 → 失败赋 0 的完整逻辑。

**注意**: 如果需要匹配字节，有时必须保留拆分形式（因为编译器可能内联不同）。此时写为：
```cpp
void *mem = operator new(sizeof(CCBSystem));
CCBSystem *pCBSystem = mem ? new(mem) CCBSystem() : NULL;
```

## 2. thiscall 调用约定

**IDA 输出（错误）：**
```c
unsigned long __thiscall CCBSystem::ProcUseItem(unsigned long hwnd)
```

**VC6 正确写法：**
```cpp
// VC6 不支持 __thiscall 关键字，成员函数默认就是 thiscall
unsigned long CCBSystem::ProcUseItem(unsigned long hwnd)
```

## 3. 虚函数调用

**IDA 输出（错误）：**
```c
(*(void (__stdcall **)(int, int))(*(DWORD *)obj + 28))(obj, arg);
```

**正确 C++：**
```cpp
obj->VirtualMethod(arg);  // vtable slot 7 (offset 28 = 7*4)
```

需要在类声明中按正确顺序声明虚函数。

## 4. dllimport 函数

**IDA 输出（错误）：**
```c
extern "C" void __cdecl sub_XXXXXX(void);  // 前向声明
```

**正确写法（gbengine 导出）：**
```cpp
#include "gbengine/gbTimeCounter.h"  // 包含头文件
// 函数通过头文件中的 __declspec(dllimport) 声明引入
```

## 5. 字符串常量

**IDA 输出（错误）：**
```c
extern "C" char aDatascriptComb[];  // 0x00609010
sub_4318B0(aDatascriptComb);
```

**正确 C++：**
```cpp
sub_4318B0("data\\script\\combat");  // 直接使用字符串字面量
```

**注意**: 字符串字面量 vs extern 声明可能影响字节匹配（地址引用方式不同）。
如果使用字面量导致不匹配，则保留 extern 形式但需注释说明原始字符串内容。

## 6. 结构体成员访问

**IDA 输出（错误）：**
```c
*(DWORD *)(this + 0x1C)
```

**正确 C++：**
```cpp
this->m_pStage  // 在类声明中用 _pad + 成员定义正确偏移
```

## 7. 类型转换与 reinterpret_cast

**IDA 输出（错误）：**
```c
dword_A3A6EC = (int)v21;
```

**正确 C++：**
```cpp
g_pCursorNode = pCursorNode;  // 使用正确类型的全局变量
```

## 8. EH (异常处理) 模式

**IDA 输出：**
```c
_Exception pExceptionObject;
memcpy(&pExceptionObject, sub_53CEF0(buf, msg, file, line), sizeof(_Exception));
// throw
```

**正确 C++：**
```cpp
throw _Exception(msg, file, line);
// 或如果需要匹配：
_Exception ex;
memcpy(&ex, MakeException(buf, msg, file, line), sizeof(ex));
throw ex;
```

## 9. 委托调用 (thiscall forward)

**原始汇编模式：**
```asm
mov eax, [esp+4]     ; 取参数
mov ecx, [ecx+0x1C]  ; 取成员作为新 this
push eax
call target
ret 4
```

**正确 C++：**
```cpp
unsigned long CCBSystem::ProcUseItem(unsigned long hwnd)
{
    return m_pStage->ProcUseItem(hwnd);
}
```

## 10. 条件 new (分配 + 条件构造)

**IDA 输出：**
```c
v30 = operator new(0xA930u);
if (v30) {
    v9 = SceneMgr_ctor(v30, arg1, arg2);
} else {
    v9 = 0;
}
```

**正确 C++ (如果构造函数无参)：**
```cpp
CSceneMgr *pSceneMgr = new CSceneMgr(arg1, arg2);
```

**保留拆分形式的条件：**
- 当 new 和构造函数之间有其他操作
- 当构造函数的参数需要额外计算
- 当需要精确匹配字节（placement new 形式）
