# 全容器锚定实况普查（2026-09-27，W1 裁定门判据数据集；c34f38aa 点名的 E/D 全扫）

## 方法
复用 `tools/global_region_audit.py` 既有锚机构（无需重建 W1 的检测器核心）：
`collect_anchor_containers`（注解型容器 38）+ `collect_evidence_anchors`（E/D 证据链 34）
+ `merge_anchors` ⇒ 65 条。证据锚三类：D:xcu（dynamic-init ctor thunk→析构 thunk→对象）、
E:singleton（guard+self-ctor+atexit 三元组）、atexit 注册桩字节级（detect_atexit_helper=0x553041 ✓）。

## 1. 证据锚实况范围（正证 = 对象真实存在的下界/整界）
| 对象 | 实况范围 | 大小 | 链 |
|---|---|---|---|
| g_ScreenMode | 0xA3A7D8..0xB1A994 | 917948B | D:xcu:target_53C2D0（=CPK 归属 A1 案）|
| g_gamefrm | 0xDB9FD0..0xDC0E3C | 28268B | D:xcu:target_44F050（与 binary_size 28268 吻合 ✓）|
| g_palScript | 0xC10968..0xC111E8 | 2176B | D:xcu:target_43A1F0（与 SceneMgr+0xC5D8 争端直接相关）|
| stru_1894B78 | 0x1894B78..0x1894D8C | 532B | D:xcu:target_53F5E0（TextureLib）|
| stru_17AB828 | 0x17AB828..0x17AB868 | 64B | E:singleton（CCBStage::DoTask gbMatrix4 static）|
| dword_BFDAB0 | 0xBFDAB0..0xBFDB70 | 192B | D:xcu:target_445010（UITextArea）|
| g_PAL3_Instance 等 | 4B 标量锚 ×20 | 4B | D:xcu（首 4B 有动态初始化 ≠ 全对象锚）|

## 2. 无锚声称（ev=None ⇒ **风险指示**，非定罪——POD 大对象本就无 ctor）
| 容器 | 声称 size | 状态 |
|---|---|---|
| g_PAL3 / g_PAL3_Instance | 91024 | 无锚；**已被 statics 侵入证伪尾部**（真界 ≤0x1358 待证）|
| g_EffMgr | 43312 | 无锚；**已被串字面量证伪整体** |
| g_SceneMgr | 58692 | 无锚；尾区 [0xC5D8,…) 已被 g_palScript A 级锚侵入 |
| g_ScriptSystemData | 12624 | 无锚 |
| g_RoleSystemCombat/Main/SlotBuf | 4868×3 | 无锚（多实例同型，证据须逐实例核）|
| g_DrvInfo | 184 | 无锚（区内 11 个独立全局）|
| g_EffMgrData | 1500 | 无锚（B 批 tagEffMgrData 225/225 T1 全 addr-only 同源疑点）|

## 3. 判据合成（W1 采纳，回应方案复核 Q4）
- **正证**（存在+范围）：D:xcu/E:singleton/atexit 桩/GetInstance 返回/ctor 多调用点同 N（alloc_sizeof v2）；
- **负证**（幻影）：函数内 static 侵入（guard 三元组）/池化串字面量/独立符号名（g_ 前缀 global_analysis）/
  多函数非 this 访问模式；
- **下界**：成员 disp32 访问最大偏移；**上界**：相邻符号/锚边界；
- 单证据不定罪：无锚=风险，负证=定罪，正证+负证冲突=分区争端（走 §3.3 裁定）。
- 已知三组定案在本数据下全部判对：PAL3 statics（负证✓）、CEffMgr 串表（负证✓）、
  g_palScript（正证 2176B✓ 且与声称成员冲突 ⇒ 争端✓）。

## 5. this 物化锚全量实测（2026-09-27 补，W1"this 物化点"检测器实证）
方法：CEffMgr/SceneMgr/RoleSystem/CGameData/PAL3 的注解方法入口 × 全函数体（3608）反汇编，
call 方法入口前 14 条内 `mov ecx,0x…`/`lea ecx,[0x…]` 聚类。

| 类 | 方法 | 调用点 | this 物化 Top | 判读 |
|---|---|---|---|---|
| CEffMgr | 31 | 208 | **0x1895580×146**（70%） | **真身 = 0x1895580**（非幻影串表 0x5D5484！）|
| CGameData | 12 | 114 | **0xDB9FD0×62** | 真身 = g_gamefrm（与 D:xcu 锚 28268B 吻合 ✓ 双源互证）|
| PAL3 | 57 | 154 | 0xDB9FD0×10、0xDE7AA0×1 | ⚠️ PAL3 方法的 this 多为 g_gamefrm（跨类归属异常，"全局归属工程"核心疑点）|
| RoleSystem | 163 | 646 | 0xC020F8×7（Main ✓）、0xC10DF0×7、0xBFFDB0×6、0x975ED8×5 | 多实例分散；g_RoleSystemCombat@0x17A8AE8 **未进 Top5** |
| SceneMgr | 15 | 22 | 0xC11758×1 | 调用点多经寄存器传 this（需数据流扩展）|
| SSD/tagEffMgrData | — | — | 无方法表 | 走绝对地址 T1 路线 |

- **W1 检测器实证有效**：CEffMgr 真身定位 = c34f38aa 判"超出复核范围未定位"项已解决；
- PAL3↔g_gamefrm 的 this 混用 = 新增 P0 级归属疑点（方法表归属 vs 实际调用对象），
  须进 W2 的逐条裁定（可能一批 PAL3 方法实为 CGameData 方法）。

## 6. 对修复方案的增量
- W1 的检测器**大部分已有实现**（global_region_audit.py E/D/atexit/partition + alloc_sizeof ctor-anchored）：
  工项改为"合成裁定器 + 逐成员落判"，工作量大降；
- W2 的范围收缩证据链：PAL3 用 statics 负证 + 成员访问下界；Array 件用邻接全局负证；
  RoleSystem×3 须逐实例（g_RoleSlotBuf 已被 c34f38aa 判"无锚源=decomp 建模"）；
- W3 重放时并入本表（退役进无锚声称区间的成员优先复核）。
