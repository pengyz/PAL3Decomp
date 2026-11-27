# 身份错误索引（首批 5 条，2026-11-27）

本页是**人读索引 + 人工裁决记录**，每条结论都已在 `data/status/evidence_ledger.json` 登记 ev id，
可用 `python3 tools/evidence_ledger.py query --subject <VA>` 复现。

## 与 `data/status/misattribution_ledger.json` 的分工

| | 本页 / evidence_ledger | `data/status/misattribution_ledger.json` |
|---|---|---|
| 数据来源 | 人工裁决（逐条读体、读 PDB、读反汇编） | `tools/misattribution_ledger.py` 自动扫描注解产物 |
| 内容 | VA、当前名、裁决名、证据等级、证据指针、状态、后续卡 | 自动分桶（A/B/C）与机检标签 |
| 使用方式 | 结论引用入口（带 ev id） | 找候选错例的起点 |
| 关系 | **只互相指向，不互相复制**（防双副本分叉，见 `docs/knowledge/gotcha_dual_copy_table_divergence.md`） | 同左 |

## 首批 5 条

| VA | 当前名（注解/IDB） | 裁决名 | 等级 | 证据指针 | 状态 | ev id | 后续卡 |
|---|---|---|---|---|---|---|---|
| `0x005052C0` | `CCBStageCam::IsCamValid`（`asm/pal3/ida_structs.json` methods 实测仍是此名） | `CCCTData::GetFreeSpaceInPool(void) int`（待定：缺一处交叉证据） | B | `data/status/_disasm_cache.txt` 0x5052c0 体：`5052c6: mov bl,BYTE PTR [ecx+eax*1+0x639c0]` 循环到 2000，满则返回 -1 ⇒ 扫 `m_bPoolInUse[2000]` 取首个空位；`CCBStageCam` size 6272B 不可能含 `+0x639c0` 成员；PDB `CCCTData::GetFreeSpaceInPool(void) int` 形态一致 | 待定（open） | `ev_0056` | #62 |
| `0x005058F0` | 无类归属（#58 已删 CCCTData methods；decomp 文件仍名 `CCCTData_…_005058f0`） | `CCBCamControl::SetCircle(gbVec3D*, gbVec3D*)` | A | `_disasm_cache.txt` 0x5058f0 体：写 `[ecx+0x69094..0x6909C]`、`[ecx+0x690A0..0x690A8]` 后 `ret 8`（两个 vec3 形参）；PDB 同名同型 | 已定谳（resolved） | `ev_0057` | #62 |
| `0x00505930` | 无类归属（同上，decomp 名 `CCCTData_…00505930`） | `CCBCamControl::UpdateCircleSet` | A | `_disasm_cache.txt` 0x505930 体：1746B，`sub esp,0x88` 后读 `[edi+0x690AC]`(m_bShowCircleSet)、`[edi+0x69090]`(m_pPointer)、`lea [edi+0x69094]`(circle center)；PDB `UpdateCircleSet` 同名同域；**不是 19B 的 `??1CCCTData`** | 已定谳（resolved） | `ev_0058` | #62 |
| `0x00506020` | 无类归属（decomp 名 `CCCTData_Create_00506020`） | `CCBCamControl::IsPointerUnderMouse(gbVec3D*)` | A | `asm/pal3/decomp/CCCTData_Create_00506020.json`：读 `[this+430224]`(m_pPointer) → `gbGeomNode::GetTotalOBBox` → 相机 view target → `gbRay::IsColOBB`，返回鼠标射线是否命中指针 OBB | 已定谳（resolved） | `ev_0059` | #62 |
| `0x005060D0` | 无类归属（decomp 名 `CCCTData_Destroy_005060d0`） | `CCBCamControl::LoadPointer` | A | `asm/pal3/decomp/CCCTData_Destroy_005060d0.json`：`operator new(0x118)` → `gbGeomNode` → 存 `[this+430224]` → `LoadFromFile(aUiCombatPointe…)` → `return 1`；Destroy 语义相反 | 已定谳（resolved） | `ev_0060` | #62 |

## 复现命令

```bash
# 台账查询（summary-first；--full 展开证据指针）
for va in 0x005052C0 0x005058F0 0x00505930 0x00506020 0x005060D0; do
  python3 tools/evidence_ledger.py query --subject $va
done

# 当前注解名（0x5052C0 仍挂 CCBStageCam）
python3 -c "import json;d=json.load(open('asm/pal3/ida_structs.json'));print(d['CCBStageCam']['methods']['0x005052c0']['name'])"

# 0x5058F0 体（写 0x69094/98/9C + 0x690A0/A4/A8，ret 8）
grep -n -A9 '^  5058f0:' data/status/_disasm_cache.txt | head -12

# 0x5052C0 体（扫 2000 字节池）
grep -n '0x639c0' data/status/_disasm_cache.txt | sed -n '1,6p'
```

## 明确不做

不新建 JSON、不改 `tools/`、不跑 `misattribution_ledger.py`、不开 IDA 探针、不改任何注解；
回填（把裁决名写进 structs）统一由 #62 承接。
