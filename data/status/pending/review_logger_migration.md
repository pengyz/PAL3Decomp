# Logger 迁移复核（N=0 WinProc）

对象 `manual/pal3/core/Logger.cpp` vs codegen + IDA `0x53CB10`。纯复核，未改产品文件，均自跑。

## 编译验证
`bash manual/pal3/build.sh` **PASS**(EXIT 0)：Logger.cpp 干净编译(无 err/warn)，链接 `PAL3_manual.exe`。map 实证 `WinProc_HWND_InputLine→0x004014b0`。✅

## 语义一致性
✅ `96` 切换 `m_nRenderMode=(m_nRenderMode==0)` 等价；`else if(m_nRenderMode)` 等价；case27 全等；case13 尾段 memset+`='_'` 等价。
❌/⚠️ 缺口（逐行比 Hex-Rays）：
1. **case8 退格=TODO 空壳**：原 `if(v6>=2){*(szCmdBuf2+v6+3)=0;*(+v6+2)=95;}` 未实现。
2. **default 键入=TODO 空壳**：原 `if(v4<0x63){*(szCmdBuf2+v4+3)=pData;szCmdBuf[v4]=95;}` 未实现。
3. **case13 漏副作用**：原 Write 前 `*(szCmdBuf2+strlen(szCmdBuf)+3)=0`（null-term）被省略——对象状态写入，不在 Mock Write 内，真实语义缺口。
4. Write 实参 `Write("")` vs 原 `Write((char*)this)`(this=`&g_InputState`)；已 Mock 故低危但入参偏。
5. **返回值**恒 `0`，原 96 分支返回新 mode(0/1)。低危：唯一调用者 `WinProc`(Msg==258) 丢弃返回值(IDA 0x404D60)；但非"寄存器分配"，严格语义仍不符。

## L1 对拍
`python3 tools/manual_l1_match.py` **EXIT 0**，符号名匹配 11 项，含 `WinProc_HWND_InputLine manual=0x4014b0 orig=0x53CB10`。
⚠️**只做符号名匹配+打印地址，不读字节不比对**（139 行无字节比对逻辑；唯一 objdump 在 `get_manual_symbols` 的 `return` 后死代码）。名为 L1 实为 name-matcher，**字节恒等门禁未生效**。map 解析脆弱。

## 挑刺
1. **核心函数仅落约一半**：4 switch 臂 2 个 TODO 空壳，称"已迁移"偏乐观。
2. **结构体布局潜伏 bug**：manual 顺序 `szCmdBuf[100];szCmdBuf2[100]`(连续)≠真实 `Logger.h` `szCmdBuf2[104]@+0x122C`、`szCmdBuf[100]@+0x1230`(**重叠**，`szCmdBuf==&szCmdBuf2+4`)，且 size 104 vs 100。case8/default 的 `*(szCmdBuf2+v+3)`/`szCmdBuf[v]` 依赖真实重叠布局，按 manual 解析到错偏移；TODO 补全前必须先修布局。
3. 更好方案：L1 工具补真字节比对(orig@0x53CB10 vs 编译@0x4014b0，截长+重定位4B don't-care)；结构体直接对齐 `pal3/src/GameBase/Logger.h`。

## verdict
**编译✅；语义⚠️PARTIAL(case8/default 未实现+case13 漏 null-term)；L1 门禁❌未生效(仅符号匹配)。迁移未完成**。补完：①case8/default(先修重叠布局)②case13 null-term ③字节匹配阶段返回值+Write 实参 ④L1 补真比对。
