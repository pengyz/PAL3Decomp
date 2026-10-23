# union 根因确认

## 根因链验证
- L2266 `ann_data=_get_ida_structs()` 语句真但定位错：ann_data 只喂 base_size（L2269-2280），成员构造源是 L2307 `ann_data_fb`+L2318。
- L2316 ✓：实测 data_members 两员 type 均 `_inline_*` 字符串。
- "known_members dict-union 未用"半对：L1487 overlay 读了注解，但 dict 型 type 按设计跳过（L1513）；dict-union 亦在导出 `_variants['396'/'1300'].type` ⇒ 三处有信息，发射器只吃 `_inline_*` 解析。
- 修 6 证据断裂：e272e56bb diff 仅 DEBUG_MERGE 钩子、无数据源改动（L2266 现仍 `_get_ida_structs()`）；该钩子在无基类类上 UnboundLocalError（L2318，PalScript 实测炸）⇒ 其 DEBUG 读数不可信。字面改 L2266 亦零效果（不喂成员；struct_by_class 无 bases/size）。"部分生效"=既有路径分叉：当前树零改动即复现 m_szDialog1 ✓ / m_RoleSlotArray ✗。

## 差异归因
type:str 非真因：① dict 分支 L2366 对 str 变体正常 `%s %s` 发射；② 家用 DEBUG_UNION 无输出已证 dict 分支没进——分支内失败不可能为因（自相矛盾）；③ trace 实证 m_szDialog1 走 L2505 `_inline_` UDT+L2604 hoist（`_inline_PalScript_m_szDialog1` 存在·kind:union·带偏移 gap），m_RoleSlotArray 走 L2741 字符串路（`_inline_PalScript_m_RoleSlotArray` 在 ida_structs.json 缺失→supersede 成 `PalScriptRoleSlotOverlay` 单型）。真因=两员 `_inline_*` 类型在导出一有一无。

## 修法评估
"改数据源+修 type:str"不成立：type:str 空操作；成员源改 known_members 我实测（注入 dict 型）直接崩 L2499 `dict.startswith`，被 L2775 捕获 ⇒ 该员后全体数据成员不发射（头截断于 _gap_180）。绕过后 dict 分支仍：(a) `return '\n'.join(_out)` 文本被 L2741 当尺寸（再 TypeError）、L2706 直接丢弃，均不入 lines（码读）；(b) L2358 嵌套成员无视 offset 无补隙 ⇒ 稀疏 overlay（1..892 / 140..160）静默布局错，违字节匹配红线。可行：① L2499 前 dict 早分派+文本入 lines+返回尺寸+offset 补隙；② 导出补 `_inline_PalScript_m_RoleSlotArray`（union）走已 work 的 hoist 路；③ L2686 改读 dict 形 `_variants[off].type`（现读 `['_variants']` 列表=死分支）。

## 挑刺
三源两汇（known_members / `_variants.type` / `_inline_*` × overlay·L2686·L2505）链上只提一源；supersede 坍成具名单型是"单型"观感的直接机制；L1487 浅拷贝原地改 ida 缓存成员 dict（跨调用顺序敏感）；导出一有一无的不对称（合成名跳过规则）未解释、②须先答；e272e56bb message 描述 diff 不存在的改动（违 R13 补丁落地 grep 核实）。

## verdict
方向对（dict-union 未被消费、成员源自 IDA 字符串 data_members），但 L2266 定位偏、步骤 4 证据无效、步骤 5 归因错（type:str 非因；真因=RoleSlotArray 的 `_inline_` 型导出缺失）。修法不足且引入截断崩溃/静默布局错；建议走 ② 或 ①，勿动 type:str。
