# `m.get('name', default)` 不拦空串——匿名成员空名双层悬空案

事实：Python dict.get 的默认值只拦"键缺失"，**拦不住键存在值为空串**——导出数据里
`{"name": ""}` 的匿名 union 成员让 `m.get('name', '_field_%04X' % off)` 返回 `''`，
生成头出现 `} ;` 空成员名，且渲染层 `'.%s' % ''` 产出 `g_SceneMgr.` 悬空调用点。

**为什么：** 编译产物的空成员名是**两层独立病灶**（头文件发射层 + stage4 渲染解析层
`_resolve_offset`），修一层只好一层——上轮只修发射层后终验仍见 3 处悬空 + 8 条级联
C2039/C2059/C2653（`'Camera' is not a member of 'SceneMgr'` 等解析崩溃假象）。
IDB 导出的匿名 union/struct 天然带空串 name，任何消费侧的 `get(name, default)` 都会被绕过。

**何时使用：** 凡从 asm/pal3/ida_structs.json 的 data_members/_variants 读 name 的代码
（emit_headers 各发射分支、stage4_substitution._resolve_offset、annotation_view.member_names），
一律 `m.get('name') or 合成名`；合成公式必须**跨层一致**（本案统一
`_field_%04X % offset`）——头文件成员名与渲染路径名不同步即产生悬空或错名。
验证悬空的快速扫描：`g_SceneMgr\.\s*(?![A-Za-z_])` 类正则全 .cpp 一遍。

⚠️ **合成必须豁免匿名 union/struct**（2026-09-28 自查回归实证）：空名的 **dict 型（union/struct）
成员是故意匿名的**——C++ 匿名成员的内层名提升到外层类作用域（tagCmdData `+29` 空名 union 的
内层 `bDestRole` 即 `force->bDestRole[v3]` 的来源）。给它合成 `_field_%04X` 名会**切断提升** ⇒
C2039 "'X' is not a member" 族。规则：`or ('' if isinstance(type, dict) else 合成名)`——
合成只救**标量**空名（悬空渲染的真病灶），匿名聚合体保持匿名。
