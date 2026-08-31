# char-vs-int 返回家族证据状态（2026-08-31）

5 条 pdb_ret 来源的 char 返回标注 vs Hex-Rays int。逐出口块分析（IDA 9.1 FlowChart）：

| 地址 | 函数 | AL 写出 | EAX 写出 | 直接调用点 | 出口 |
|------|------|---------|----------|------------|------|
| 0x004FCE70 | CCBStage::IsSubTaskFinished | 0 | 1 | 0（间接） | xor eax,eax; retn 4 |
| 0x004FD1A0 | CCBStage::IsSubTaskValid | 0 | 1 | 0（间接） | xor eax,eax; retn 4 |
| 0x0050A180 | CCBStageRole::Grab | 0 | 1 | 1（样本无关） | xor eax,eax; retn 4 |
| 0x005155D0 | CCBSystem::PassCmdToTask | 0 | 1 | 0（间接） | xor eax,eax; retn 4 |
| 0x00515760 | CCBSystem::PassCmdViaThread | 0 | 1 | 0（间接） | xor eax,eax; retn 4 |

## 解读

- 指向 int：所有出口写 EAX，全函数无 `mov al, x` / `setcc al` 模式
- 但不确定谳：`xor eax,eax` 对 char 的 0 返回同样合法（等长 2 字节）；
  **须确认这些函数存在非零返回路径且该路径也走 EAX**，才能推翻 PDB 参考
- 4 条无直接调用点 = 经函数指针表间接调用（编辑器/命令表代码路径），
  调用点 AL/EAX 读取证据不可得，除非找到间接表

## 下一步（定谳流程）

1. 全函数体指令清单人工复核每条（找非零返回路径的宽度）
2. 找间接调用表（谁的函数指针字段指向这些地址——data xref 扫描）
3. 若确认 EAX 非零返回 → 修标注 char→int（证据：VA=出口指令，A 级）
4. 若全零返回 → 字节不可分辨，保留 PDB char（参考级），标记 AMBIG-COSMETIC

教训：`xor eax,eax` 与 `xor al,al` 等长，0 返回路径无宽度信息——
宽度证据只存在于非零返回路径与调用点消费。
