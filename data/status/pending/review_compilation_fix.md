# 编译修复复核

## Windows/Linux 兼容
- Linux/wine 实测：clean 重建 exit 0 → PAL3_manual.exe 40960 B，PE32 GUI ✓；增量 no-op；删 obj/删 lib/改 def 均触发重建 ✓。
- Windows/非 wine 未实测，静态成立（ntpath/';'/直调 NMAKE）；隐患：LIBCMT.LIB↔lib 大小写重名对（clone 碰撞）、路径含空格即断。

## 硬编码检查
- ✓ build.py 已清（R107）：grep 硬编码模式零命中；Makefile 路径由 __file__ 派生，异路径(/tmp/pal3rev_fresh)构建成功。
- ⚠️ deploy.py:10 仍硬编码 E:\...\Steam\...\PAL3（范围外未修）。

## lib 自动生成
- ✓ 实证：LIB.EXE 自 gbengine.def 产 gbengine.lib(313354 B)；删 lib 再生✓；touch def 触发✓（copy2 保 mtime）；def 已 git 跟踪(1021 行)⇒ fresh clone 可编。

## 挑刺
1. [bug·实证] `'build' in root` 子串匹配（build.py:123）：路径含 "build" 即 0 源→LNK2001 _WinMain@16→exit 2。应改 dirs 剪枝。
2. [bug·实证] obj 按 basename 碰撞（build.py:48）：同名双源→U4004+LNK4042，exit 0 静默丢一源。建议 obj 镜像源相对路径。
3. 次要：clean 留 lib/.exp(:97)；env 大小写残留(:155,162)；CMakeLists 指不存在的 gbengine.lib（双路线分叉）。

## verdict
4 项修复属实、逐项实测（recipe/lib 自动化/消 ../GUI）；wine clean+fresh clone 异路径均过。遗留 2 实证 latent bug（'build' 子串、basename 碰撞）+ deploy.py 硬编码；建议修 1/2 再收，不阻断当前构建。
