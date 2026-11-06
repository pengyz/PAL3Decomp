# B面战役交接 2026-11-06（接 progress_handoff_20261105.md）

## 一、现状一句话
B 面端到端已通（annotation→Ghidra 导入→proof→reconstruct extract→codegen→**真 VC6 编译**），
编译错误 **33,808(gcc smoke) → 203（vc6 真机·截断解锁深体层）**，全部修复已脚本化可重放。

## 二、编译战役权威读数
- 工具链：`wine_cl.sh` + `tools/compilers/msvc6.0`（CMake 识别 MSVC 12.00），`/Zm1000` 已配（C1076）。
- 轨迹：gcc-smoke 33,808 → vc6 349→152→64→28→12→105→203（fatal 解锁深层=进展非回潮，按 C1003 纪律看最大行号：2920→5769）。
- 当前 build：`/tmp/rvc6_build43.log`；**重建命令**：
  ```
  cd /home/peng/workspace/ghidra-reconstruct
  GHIDRA_PROJECT_PATH=/home/peng/workspace/PAL3Decomp/pal3-redivivus/ghidra_proj \
  GHIDRA_PROGRAM_PATH=/PAL3.exe GHIDRA_MCP_TOKEN=local-dev \
  GHIDRA_OUTPUT_DIR=/home/peng/workspace/PAL3Decomp/pal3-redivivus/reconstruct-out npx tsx run.ts
  cd ../pal3-redivivus && ./vc6_adapt_tree.sh && cmake --build /tmp/rvc6 -j4
  ```

## 三、适配链（全部幂等·在 pal3-redivivus/，已入库）
- `vc6_adapt_tree.sh`（主链 11+ 步）+ `vc6_d2platform_fix.py`（d2_platform 全套）+
  `vc6_postfix.py`（注释括号/SDK重复删/跨文件搬移）+ `vc6_gapfill.py`（缺口回填+unnamed-split·size>4096 SKIP=runaway 防爆）+
  `vc6_emit_missing.py`（v4：fwd 缺定义+全头字段闭包+按值 hoist·数据源=codegen-snapshot）+
  `vc6_deepfix.py`（六修：vfs::剥/TryExpand补参/FUN014b0返型/Dialog补声明/SQRT宏/this局部名）+
  `vc6_nested_ns.py`（C++17 嵌套命名空间展开）+ `vc6-shim/`（cstdint/cstring/wintrust/psapi/time64/typename/static_assert 等）。
- **铁律**：每修必落脚本，否则 regen 冲掉（实证×2：constexpr/extern 回潮）。

## 四、已定根因结论（一手证据在案）
1. 'constant' = VC6 对**裸数字记号**的类名（缺逗号后0x0）——非标识符（CreateDialog 案同源）。
2. init/def 两渲染器不一致：init 逐字节拆 unnamed run，def 无视 snapshot size 渲1字节 → C2078 级联（gapfill+unnamed-split 修）。
3. WINUSER 宏撞名（CreateDialog→CreateDialogA 链）→ FID_conflict 改名。
4. 点号命名空间（GBENGINE.DLL）= D2 无点假设被 PAL3 打穿 → 展开器。
5. C1001 自爆 = struct fwd 撞 d2_platform typedef（struct code）。
6. DialogResource = **Ghidra builtin size=-1**（"Dialog stored as a Resource"）非 struct。

## 五、数据层欠账（annotation 根修·按裁定不混管线）
- **76 条**导入失败=数据（48 未知型引用+19 STL+4 嵌套+4 非法字符+1 占位）。
- **47 plan 缺节点**（IDirect3D*/_GUID/gbFontType/_D3D* enums 漏注）+22 nested/STL。
- **runaway 结构族**（offset0 巨型 undefined·split SKIP 日志在案）：gbBinkVideo(1835912)、SoundMgr(918796)、ParticleEffect(362836)、CCBStage/CCBCamControl(400KB级)、gbSceneGraph、PAL3(4936)、Role(8704)、SceneMgr、CEffMgr、GRPinput 等。
- **签名矛盾待二进制裁定**：TryExpand(3vs5)、FUN_004014b0(void vs 赋值)、FUN_004b5d20(0vs4)。
- CScreenMode offset6/7 洞（快照 size5496/fields107 自证）。

## 六、字节匹配回访记账（改动有语义风险）
packed 属性删除、__thiscall 剥、FUN_004b5d20 调用剥参、extern struct 增词、SQRT→sqrt(sqrtss vs sqrtsd)、
FUN_014b0 void→int（**待回滚/取证**）、TryExpand 补参（**未取证选边**）、Dialog extern（**类型推断错·待重做**）。

## 七、下一步（优先级）
1. **纠正三修**：i) FUN_014b0 回滚（不补假 return）；j) Dialog 按 builtin 实证重做（查 Rsrc_Dialog_6a_804 引用面）；h) TryExpand 入待裁定账。
2. **通用 `Type::method`→自由函数解析**（gbVFileSystem 已修·gbEffectMgr::NewRenderEffect 等同族待清——勿逐族打地鼠）。
3. fnptr 初始化器族×15（成员 unsigned char* vs 值=函数址·疑数据签名）。
4. 未定位 C2447/C2143×18 解析断点；LAB_0055f02b 等符号遗漏族（reconstruct 漏发全局）。
5. → 0 错 → 链接层（wine_link·LNK 族）→ **B 字节率首数**（.cpp.map 地址映射在 reconstruct-out）。

## 八、导入面存档（本 arc 已完成）
- 导入 5673 ok / 2871 bad；structs 860/69、enums 68/0、unions 12/0、functions 5143/154。
- proof：match 924→1536、missing 453→19（`data/status/b_import_proof_20261106.json`）。
- 失败账本二分：`ghidra_track/out/import_standard_fails.jsonl`（527 = 291 dryRun剔环 +150 No-transaction +76 数据 +10杂）。
- 两遍建型 `partition_struct_passes`、C族 enums 进 plan（`41ee865dd`/`2909b77ec` 等已在主仓）。

## 九、质询纠正承诺（2026-11-06 用户质询后立规）
adapt 内一切"矛盾两侧选边/补型"必须附取证注释，否则不落；已违例三处（h/i/j）按第五节处理。
