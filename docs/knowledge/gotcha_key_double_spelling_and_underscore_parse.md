# 键双拼与十进制下划线——成员键解析双陷阱

事实：known_members 的键形态谱系实测 dec 9745 / hex 51 / N_N 4，其中存在**同偏移双拼键**
（C2DSpark_tagSpark 同时有 '0x8' 与 '0x08'、'0xc' 与 '0x0C'——大小写+前导零变体各持一条
且内容不同）；且 `int('50814_0', 0)` 在 Python 3.6+ = **508140**（下划线是数字分隔符），
N_N 数组后缀键会被整体误读。

**为什么：** ①历史批注工具按字符串拼 hex 键无规范形，同偏移异拼键静默并存（且 dict 按
字符串键各存一条）；②`int(x, 0)` 的下划线语义与"offset_index"键形天然冲突——
apply_annotations 曾一处 `int(off,0)` 无 split('_')[0]（790/986 行其余处都有）。
后果：归一化/查表/防重叠全部偏移一位，且"新键已存在"式防撞才是发现双拼的第一现场。

**何时使用：** 键解析统一 `int(str(k).split('_')[0], 0)`（split 后缀 + base 0 认 hex）；
守卫（tools/apply_annotation_batch.py）键形白名单 `(0x[0-9a-fA-F]+|\d+)(_\d+)*`、
normalize_key 保序重建（pop/排序会整文件重排淹 diff）；批量改键前先查双拼
（同偏移多键=type_evidence 的 dups 诊断），双拼对按证据删弱留强、双有证留裁。
