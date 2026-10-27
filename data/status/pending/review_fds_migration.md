# FDS 迁移复核

复核对象：lead N=0-N=2（Logger WinProc / CUtil 骨架 / N=2 统一 Mock）。自查、只读、未改产品文件。

## 编译验证
`bash manual/pal3/build.sh` 清树重建 **EXIT=0** ✓（6 源编译 + 链接 PAL3_manual.exe）。但编译报警暴露真 bug：
- **C4700 未初始化 `result`** ×2：`PAL3.cpp:26` `InitVFileSystem` / `:33` `InitVFileSystem2`，`void *result;` 从不赋值却 `return result` ⇒ UB/返回垃圾。系 Hex-Rays `// eax` 占位被照抄未修。证据：build 输出 `warning C4700 ... 'result' used without having been initialized`。

## L1 对拍
`python3 tools/manual_l1_match.py` 报 "12 匹配"，**但这是符号名命中，不是字节比对**：
- 工具只做 `if sym_name in orig_addrs: matched.append(...)`（纯名表求交 + 打印两侧地址），**全程无任何字节/code 比对**，尽管 docstring 自称"取地址 => 字节比对"。
- ⇒ "12 匹配" ≠ 本项目 L1（字节全同函数数）。把它当"L1 对拍 ✓"是**度量名不副实**。真正字节 L1 在 `pipeline/compare_pal3.py`，而 manual/pal3 无字节比对。
- 另：`get_manual_symbols` 中 objdump 分支是 `return` 后死代码；只打印前 10 条（12 有 2 条不显示）。

## 语义一致性
WinProc_HWND_InputLine（N=0）逐 case 对齐 codegen（`pal3/src/GameBase/Logger.cpp`）✓：退格 `szCmdBuf2+v6+3=0 / +2=95`、回车 `Write((char*)this)+ExecCommand+memset(0x64)+'_'`、Esc、默认键入 `v4<0x63` 均逐字一致，含 `Write((char*)this)`（把 this 当 fmt 传）技巧正确。**偏差**：
- return 值：pData==96 分支 manual 恒 `return 0`，codegen 返回翻转后的 mode 值（调用方若读返回值则不等价）。
- **Logger 布局与注释不符**：注释称 `m_szCmdBuf2 @ +0x122C / m_szCmdBuf @ +0x1230`（原布局），但 as-declared 只有 3×int+数组 ⇒ 实际落在 **+0xC / +0x74**。偏移差 0x1220，将来做字节匹配必错位（当前自标"semantic target"，暂不致命）。

## 挑刺
1. **obj 输出路径 bug**：`build.py` 里 `rel` 基算成 `gbengine_dir/../../manual/pal3` = `manual/manual/pal3`（多一层 `manual`）⇒ `/Fo` 与 obj 全落**源码树** `manual/pal3/core/*.obj` 等，非 `build/`。与注释"out-of-tree build"矛盾。证据：`find build -name '*.obj'` 空、obj 在 core/mock/platform。
2. **4 个孤儿 .obj**（`mocks/mocks_batch3/mocks_batch4/mocks_simple.obj`）留源码树，对应源已删/不存在（batch4 无 cpp）。
3. **N=2 去重无丢失 ✓**：旧 3 文件并集 50 名 → 新 87 名，`comm` 无一丢失、无重复名。但 mock 全是 `void X() {}` 空签名，真实调用者迁入即签名不匹配（latent）。

## verdict
编译 ✓、N=2 去重无损 ✓、WinProc 逐 case 语义对齐 ✓。**但 3 处须修**：① C4700 未初始化 `result`（PAL3.cpp:26,33）真 bug；② "12 匹配"是符号名命中非字节 L1，不得充数；③ obj 落源码树 + 4 孤儿 obj（build.py base 算错）。建议先修 ①③、L1 换真字节比对再宣称通过。
