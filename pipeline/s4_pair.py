"""s4_pair — s4 双文件成对恢复（同源纪律·2026-11-05 病灶修）。

病灶（码证）：cli.py match 真退步分支恢复旧 baseline（prev_text 写回）时，
s4_diff_detail 已被本轮 compare 覆写 ⇒ 双文件代表不同 run（实证 161 vs 110·
状态相反 0x4420C0）。修：恢复必须成对；regressed detail 存档（诊断不丢）；
prev detail 缺则移除 cur detail（宁缺勿伪同源——match_progress 同源校验将响亮报缺）。
"""
import os
import time


def restore_pair(s4_path, detail_path, prev_s4_text, prev_detail_text,
                 cur_detail_text, archive_dir):
    """真退步成对回滚 → 摘要 dict（restored/archived）。cur==prev → 幂等不动。"""
    out = {'restored': False, 'archived': None}
    if cur_detail_text == prev_detail_text and prev_s4_text is not None:
        return out
    os.makedirs(archive_dir, exist_ok=True)
    if cur_detail_text is not None:
        arc = os.path.join(archive_dir, 's4_diff_detail_regressed_%s.json'
                           % time.strftime('%Y%m%dT%H%M%S'))
        with open(arc, 'w') as fh:
            fh.write(cur_detail_text)
        out['archived'] = arc
    if prev_s4_text is not None:
        with open(s4_path, 'w') as fh:
            fh.write(prev_s4_text)
        out['restored'] = True
    if prev_detail_text is not None:
        with open(detail_path, 'w') as fh:
            fh.write(prev_detail_text)
    elif os.path.exists(detail_path):
        os.remove(detail_path)   # 无 prev detail → 移除 cur（禁伪同源）
    return out
