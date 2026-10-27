# free_func_sigs 设计复核

## 设计问题验证

**① 机制归因证伪（实跑 DataStore）**：free_func_sigs 实测 394 条（R91 路由 pop 63 后）= decomp 自动 354 条（`data.py:467` 无 `::` 即自由）+ functions.json 补充 40 条（`data.py:528-575`，判据仅"无 `::`"且 cdecl/stdcall 可解析）。**两路均不读 `type` 字段**；全仓 `'free_function'` 字面量唯一消费者是 `tools/pal3_callgraph_comprehensive.py:336` 兜底标签。WinMain 实测已在 sigs（`int __stdcall WinMain(...)`）——标注是装饰，标不标结果相同。

**② "563 天然全局"口径虚高**：614−51（class 字段）=563 ✓，但内含 151 条 `::` 命名类方法（`apply_annotations.py:1359` 加载时自动补 class）+ 198 条 skip 墓碑 ⇒ 真候选 412（无 class 且无 `::`），非 skip 214。

**③ "非类函数天然全局"成立**：两条路径均以无 `::` 自动判自由——设计已自动识别，**无需额外标注**。

**④ 方向反转**：冗余真实但性质相反——非"必需而多余"，而是 `type: free_function` **零消费者死信道**；R121 今日写入 WinMain 恰证明维护者误以为该字段生效。

**⑤ 连带实证**：`type` 词表零校验（check_annotations 只认 skip）；skip 语义跨消费者不一致——190 个 skip 名全在 free_func_sigs（173 经 decomp + 17 经补充路径，后者无 skip 过滤，globals 补充 `data.py:354` 却有），且 190 名在生成代码全部有引用（1–49 处/名，Object3D_LoadActorModel 49 处）⇒ **声明承重**；另有 202 条占位签名 `int nVal`（184 条属墓碑名）。

## 完整修复方案

1. **死信道退役（主修）**：删 WinMain 的 `type: free_function`（信息移入 source 注记）；check_annotations 增 functions.json `type` 词表校验（合法值 skip/缺省）；文档明示"自由函数=无 `::` 自动识别，无需标注"。零 codegen 风险。
2. **或给字段消费者（不推荐）**：check_annotations 强校验 free_function ⇒ 无 `::` ∧ 非 skip ∧ 已入 sigs；否则维持退役。
3. **skip/声明面独立挂账**：190 条声明承重，禁加裸 skip 过滤（N1 教训 C2065 洪泛）；`int nVal` 占位签名须逐条 A 级证据正名，禁猜测、禁混批。
4. **识别机制不动**：无 `::` 自动识别已正确工作。

## 影响面评估

- **codegen**：方案1 零影响（无任何消费者读该字段），free_func_sigs 语义不变。
- **注解**：WinMain 1 条删字段，无批量改动。
- **测试**：`tests/codegen/test_free_functions_header_location.py` 用合成 sigs 不受影响；新增词表校验测试 1 个。
- **门禁**：annotation_diff 后 `loop --expect-errors` 断言不变即可；无签名/归属变更 ⇒ 无布局/字节影响面。
- **风险**：方案1 极低；方案3 高（触 190 承重声明），须独立轮 + match 当场读数。

## verdict

**PARTIAL：结论成立、机制证伪、方向反转**。设计冗余真实存在，但 free_func_sigs 无需 `type: free_function` 标注（实测 394 条零 type 过滤，无 `::` 自动识别）⇒ 病灶是**死信道**（标注写入无消费者、造成功效假象），而非"标注必需但多余"。修复=退役死信道+补词表校验；skip 声明面与 `int nVal` 占位签名属独立债。"563"口径应修正为 412/214。
