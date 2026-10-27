# WinMain 归因复核

## 归因验证
「export 排除自由函数」**不成立**。
- export_full.py:413-421 仅排 nullsub_/j_ 名、skip_functions.json、size≤1；decomp 实测 439 个自由函数（ActVecReallocate 等）+ free_functions.cpp 337 体，照常导出。
- 「2243 个全局函数」无法复现（实测 337 体/394 声明/439 decomp）。
- WinMain 是点名排除：skip_functions.json["0x00541900"]={name:"_WinMain@16",reason:"crt_runtime"}，export:417 及补录 :436-438 均跳过。functions.json∩skip 双注册 19 条，余 18 条真 CRT/thunk，唯 WinMain 定性错。

## 根因定性
skip_functions.json 误分类（1837cc6e9 连带判 CRT）。IDA 实证（b2b23162）：0x00541900 体=游戏代码（FindWindowA→Disc4 检查→PAL3::Create→消息循环→Update/Render/Destroy），caller=start@0x55507c（CRT 调用户入口=MSVC 契约）。声明侧已就绪（functions.json R121/R122 + free_functions.h:373）⇒ 病灶单点=skip_functions.json。

## 修复方案
1. 删 skip_functions.json["0x00541900"]；
2. 全链 apply→export→codegen→probe，验证 decomp/WinMain_00541900.json；
3. check_annotations 加规则：functions.json 真实签名非 declaration_only 者禁留 skip；
4. free_functions.cpp 是 C1003 截断单元，以最大行号判进展。

## verdict
归因推翻 ✓：export 不排自由函数；WinMain 缺失=skip 误分类单点，「特殊」是误判。删条+全链重导，低风险。