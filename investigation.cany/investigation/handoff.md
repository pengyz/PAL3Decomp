# Handoff

状态(2026-11-11 15:47)：HEAD=a88c9de42（串池命名冲突修正）。全链已跑：apply→export→codegen→probe，census 2026-11-11T15:44:16 = S2 141/215 · 800 错（本轮起点 131/215 · 1079 错，批E前 140/858）。dir_0 C2065 33→0，C2109 188→30，C2102 166→0。

已定谳：0x583A9C 串池首串 "fivemagic"，旧名 dir 与 0x58B44C("role") 的 IDB 名 dir 撞名 ⇒ IDA 落 dir_0、globals.h 发 dir ⇒ 33 单元级联。改唯一名 aFivemagic（type char[256] 不变），decomp 82 文件引用一致。证据 ev_3ff7b3b6(0x583A9C)/ev_6ee7f472(0x58B44C)，finding fnd_1。

待办：1) 本轮没跑 match（S4/L1 未刷新，L1 棘轮 94 待测）；2) 剩余大头 C2440 206 / C2664 152 / C2660 64；3) unk_1a6229b6（0x58B44C 名字何时从 aRole 漂成 dir）低优先。

坑（重要）：本环境存在另一个 builder 进程会并发跑同一管线（15:21/15:41 两次实测）。并发 codegen 会互相 cmd_clean 掉树（我 15:38 的 codegen 就因 FileNotFoundError 崩在 UIPoCushButton.cpp，随后对方完整跑完）。动手前先看 pal3/src 的 cpp 计数是否在涨、census mtime 是否在变；涨就等。

IDA 在沙箱里跑不起来的原因：$HOME 只读，IDA 启动即退。解法：同一 bash 调用内 mkdir /tmp/ida-home/.idapro + 复制 ~/.idapro/{ida.reg,ida-config.json,license_accepted}，然后 IDAUSR=/tmp/ida-home/.idapro TVHEADLESS=1 跑（保留原 HOME，否则 Python 丢 ~/.local 的 tree_sitter_cpp）。/tmp 每次调用全新，必须同命令内建。不要复制 plugins（HappyIDA 依赖缺失会中止脚本）。

构建检查修复（2026-11-11 15:5x，与上面管线工作无关）：Craft Anything 把本项目识别成 Python 工具链，build=`python3 -m compileall .` 会扫到 tools/ghidra 两个发行包（约 1.5G，内含 Python 2/Jython 源码），报数百条 print/except 语法错。修法：两个发行包实体移到 tools/ghidra/venv/（compileall 的 -x 与 pytest 默认都跳过 venv），原路径 tools/ghidra/ghidra_{11.2.1,12.1.2}_PUBLIC 改为相对符号链接；.gitignore 补 venv/ 与两个链接；tools/ghidra/README.md 记布局。build 检查现 exit 0（1.2s）。pytest.ini 增加 --ignore=tools/ghidra（第三方）、pipeline/ida/_archive（IDA 专用归档脚本）、tests/tools/test_audit_callsite_evidence.py（针对已删除 API 的陈旧用例）。注意 own-tests 检查仍红：全套 pytest 48 failed / 1501 passed（数据漂移、apply_annotation_batch 已删、global_region_audit 等既有红），未用跳过掩盖；这是独立于构建的既有债。
