# manual/pal3 编译复核

复核方式：本地实跑 `python build.py`（Linux/wine：nmake 6.00.8168 + cl 12.00.8168 + link 6.00.8168），含 clean 重建 + 破坏性实验。仅只读复核，未改任何产品源文件。

## Windows/Linux 兼容
- Linux/wine：**实测通过**。删 *.obj/exe 后 clean 重跑，4 源全编译 + 链接，产 `PAL3_manual.exe` 40960 B（PE32 GUI），exit 0，仅 C4251/C4700 警告。⚠️ 增量构建是 no-op（nmake 判 up-to-date）⇒ 单跑 exit 0 ≠ 真编译过。
- Windows/非 wine：**本次无法实测**（无 Windows）。静态看 to_wine_path(非 Linux) 返原生路径、nmake 直调，逻辑成立。
- 残留瑕疵：`os.pathsep` 拼 INCLUDE/LIB（build.py:105-111）。Linux pathsep=':'，而 MSVC 的 INCLUDE/LIB 恒用 ';' ⇒ Linux 下 env 变量是错的（`Z:\a:Z:\b` 被当盘符冒号误析）。当前**侥幸**不炸：编译靠 /I（Makefile:14）、链接靠显式 lib 全路径覆盖，两 env 实为死码；Windows 下 pathsep=';' 恰好对。属真隐患非现症。

## 硬编码检查
- ❌ **有硬编码游戏路径**：
  - build.py:74 `gbengine_dir = r'Z:\home\peng\.steam\debian-installation\steamapps\common\PAL3'` —— 绝对路径 + 用户名 `peng` + steam 布局，且已是 Z: wine 形（native Windows 上此路径无效）。
  - deploy.py:11 `game_dir = r'E:\Program Files (x86)\Steam\...'` —— 另一处硬编码。
- 与 build.py:72 注释「Relative paths (no hardcoded absolute)」**自相矛盾**。建议走 env/pipeline.toml [game] install_dir（deploy.py 已留 TODO）。

## lib 生成
- ❌ **gbengine.lib 不会每次生成**。实证：① build.py/Makefile 无任何 lib.exe//DEF 规则（全仓 grep 无）；② 增量+clean 两次构建，gbengine.lib mtime 恒 10:49:12、sha 恒 `88117280…`，从未被触碰；③ 破坏实验：删 gbengine.lib 重跑 → `LNK1181: cannot open input file gbengine.lib`，exit 2。⇒ 它是**手工预置**进 build/ 的 import lib（gbengine.dll 导入库，1019 导出）。build/ 被 .gitignore ⇒ **fresh clone 必编不过**。
- ✅ 可再生且低风险：`lib.exe /DEF:gbengine/gbengine.def /MACHINE:IX86 /OUT:build/gbengine.lib`（实测产 313354 B，与现有仅第 30 字节 COFF 时间戳不同，符号内容 8572 处一致）。建议在 link 前加此规则，从 gbengine.def（源头 1019 EXPORTS）生成。

## 挑刺
1. **R104 修复是 no-op（注释与代码矛盾）**：build.py:73 称「统一用游戏路径（与 L25 GBENGINE_DIR 一致）」，但 Makefile:25 `GBENGINE_DIR = {to_wine_path(build_dir)}` 用的是 **build_dir** 非游戏路径；generate_makefile 的 `gbengine_dir` 形参在函数体内**从未被用**（仅进 env['LIB']）。⇒ 改 line 74 的值对 GBENGINE_DIR 解析零影响，游戏路径是死码。实际链接吃的是 build/gbengine.lib。
2. **大小写不一致（item① 残留）**：真目录/可执行是 `Bin/CL.EXE`（大写），Makefile:31-32 写 `\bin\cl.exe`（小写），靠 wine/NTFS 大小写不敏感才通；build.py:99 又用 'Bin'。脆，建议统一。
3. **增量 no-op 误导**：exit 0 不代表编译过，验证须删产物或 /A。
4. 游戏目录 gbengine.dll 旁并无 gbengine.lib ⇒ line 74 那条 env['LIB'] 指向的游戏路径根本找不到 gbengine.lib，佐证其为死码。

## verdict
功能达成但 3 处实质问题：① **gbengine.lib 不自动生成**（fresh clone 断链，最高优先）；② **游戏路径硬编码 + Z: wine 形**（破坏 Windows 通用性与注释承诺）；③ **R104 修复实为 no-op**（注释误导、死码）。Linux/wine 编译链**实测可用**（40960 B exe）；Windows 静态可信但未实测，line 74 的 Z: 硬编码在 Windows 上无效。建议：lib 生成入 Makefile + 游戏路径改 env/toml + 修正 R104 注释/删死码。不阻断当前 Linux 构建，但 fresh clone / Windows 场景会踩坑。
