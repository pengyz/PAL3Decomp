# modules/ — PAL3 姊妹 DLL 模块（手动维护源码）

与 PAL3.exe 并列的游戏模块构建目标，依赖链：`topo.dll → gbengine.dll → PAL3.exe`。

- `topo/` — 数学库（纯数学，仅依赖 libc；src/ + topo.def）
- `gbengine/` — 引擎核心（依赖 topo + d3d9/d3dx9/dinput8/mss32/ijl15；src/ + gbengine.def + lzo/）
- 声明面在 `include/gbengine/`（与模块 src 分离——头=管线共享类型域）
- 构建：根 `cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake -G Ninja` → `cmake --build build`
- 已知存量：gbengine 源级编译错（gbPlane 族 vs include 头的 inline/out-of-line 分裂）待修
