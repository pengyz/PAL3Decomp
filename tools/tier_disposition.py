"""③ 低置信档档化：adjudication_v2 行批量处置标注（判据+理由入表——不硬解禁）。
处置形：clue_game_candidate（线索指向 game·深证批作业池）/clue_lib（库/CRT 族）/
thin_stub（薄体/桩）/undecided_deep（深度体征待证）。"""
import json

p = r"D:\workspace\PAL3Decomp\data\status\adjudication_v2.json"
d = json.load(open(p, encoding="utf-8"))

counts = {}
for r in d["rows"]:
    if r["tier"] != "clue_only":
        continue
    cl = r.get("clues") or {}
    pro = cl.get("prologue", "")
    this_refs = cl.get("this_refs") or 0
    gc = cl.get("game_calls") or 0
    lc = cl.get("lib_calls") or 0
    if pro == "thiscall" and this_refs >= 2 and gc >= 1:
        disp = "clue_game_candidate"     # 线索指向 game（深证池）
    elif lc > gc and lc >= 2:
        disp = "clue_lib"                # 库调用占优
    elif this_refs == 0 and gc == 0 and lc == 0:
        disp = "thin_stub"               # 薄体/桩
    else:
        disp = "undecided_deep"
    r["disposition"] = disp
    r["disposition_reason"] = "档化 2026-10-06：prologue=%s this_refs=%d game=%d lib=%d" % (
        pro, this_refs, gc, lc)
    counts[disp] = counts.get(disp, 0) + 1

d["_meta"]["dispositions"] = counts
json.dump(d, open(p, "w", encoding="utf-8"), ensure_ascii=False, indent=2)
print("③ 档化：%s" % counts)
