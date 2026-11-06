# 架构定谳：GBENGINE.DLL = PAL3.exe 第 7 导入 DLL（2026-11-06 晚）

**本文档作废此前三份交接中的以下结论**（均在 A 级一手证据下反转）：
- "PAL3.exe 未导入 GBENGINE.DLL，引擎静态链接进 .text"（progress_handoff_20261106 推论基础之一）
- "GBENGINE 函数体缺失 = extract isLibrary skip 管线缺陷"（session2 进度档 §五.3）
- "函数体回填 = B 面跑通的最大结构性欠账"（session2 复盘）

## 一、证据链（全部一手、可复现）

1. **IAT 定位**：PE Data Directory Entry c（IAT）RVA 0x16a000，373 槽 @ 0x56a000..0x56a5dc。
2. **调用形态**：DecideKeyStatus@0x404150 的三处间接调用 `call ds:0x56a52c/0x56a530/0x56a534`
   = IsColAABB / IsColTriangle / Length——全部走 IAT。
3. **名字串**：槽值是 RVA（0x17eaca 等），指向导入名 `?Length@gbVec3D@@QBEMXZ`
   （与 gbengine.dll 导出表逐字一致，亦与本仓 nsfix 签名库逐字一致）。
4. **描述符表**：标准导入描述符数组第 [6] 项 = `GBENGINE.DLL`，FirstThunk=0x16a1f4。
5. **反证前的错误**：早先 `objdump -p | grep -A3 "DLL Name" | head -30` **截断了自己的探针输出**，
   第 7 个 DLL 的名字行被剪掉 → 误判"无 GBENGINE 导入 → 静态链接"。
   **教训入档：探针输出截断可制造架构级误判，结论前必须全量枚举。**

## 二、认知反转清单

| 旧结论 | 新定谳 |
|---|---|
| 引擎静态链接，函数体须回填 | **引擎=运行期导入 DLL**；Ghidra EXTERNAL 建模正确 |
| extract `isLibrary skip` 是管线缺陷 | **完全正确**（与 BINKW32/ADVAPI32 同等待遇） |
| B 面需重跑 extract 拉 GBENGINE 函数体 | **取消**——函数体本来就不该在 PAL3.exe 里 |
| nsfix 成员声明是 adapt 层权宜 | **就是最终形态**（有声明无体，链接期由导入库解析） |
| "FID 把引擎函数标成库" | 无 FID 机制介入；isLibrary 标志来自 projectConfig.libraries（PAL3 无配置→从未生效） |

## 三、已落地（pal3-redivivus 8497e5e）

- `thirdparty/gbengine.def`：1019 条 C++ mangled 导出，名字原样（VC6 C++ 符号无前导下划线，
  archive 符号 = loader 导入名）。checked-in 同 binkw32.def 模式。
- `thirdparty/gen-implibs.sh` 扩展 GBENGINE 段：**VC6 lib.exe**（wine）原生生成导入库
  （MinGW dlltool 会加 `_` 前缀，不能用）。产物 `gbengine.lib`（313KB）构建期生成、gitignore。
- 验证：archive 内 thunk + `__imp_?Length@gbVec3D@@QBEMXZ` 双符号形态齐备。

## 四、与 A 面的对账

- A 面主线 `CMakeLists: topo.dll → gbengine.dll → PAL3.exe` 三级构建——**同构印证**导入模型。
- A 面 `gbengine/gbengine.def`（1019 导出 + 原始序号 @1..@1019）= 权威 def（ordinal 面对齐原 DLL）；
  B 面 thirdparty/gbengine.def = 同数据源的平名变体（ordinal 面暂未钉）。
- A 面 `pal3/CMakeLists: target_link_libraries(PAL3 PRIVATE gbengine)` = B 面 exe target 的接线模板。

## 五、B 面链接层新账（wine_link 建设清单）

1. `tools/wine_link.sh`（类比 wine_cl/wine_lib）包装 VC6 link.exe。
2. Reconstructed target 现状 = wine_lib 归档（`/out:Reconstructed.lib`）；需增 exe link 步骤：
   全部 .obj + `thirdparty/gbengine.lib` + kernel32/user32/(gdi32/ole32 等按 d2_platform 需求)。
3. 运行期：GBENGINE.DLL 须在 EXE 旁（original/gbengine.dll 可直接用）。
4. 枚举项：Mss32/ijl15 不在 PAL3 导入表（音频/图经由引擎封装）——列 PAL3 运行依赖清单时核实。

## 六、当前战场读数不变

编译 203（build57 @ 截断 8421；错误面=纯游戏层语法/数据问题，与引擎零牵连）：
C2143×50（globals.cpp 初始化器=数据层两源分裂）+ C2065×17 + C2440×34 + C2447×18 等族。
build58（nsfix pass3 cast 修复后）尚未跑，为 203 攻坚的下一读数。
