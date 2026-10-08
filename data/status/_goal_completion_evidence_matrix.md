# Goal 完成证据矩阵（终版 2026-09-28 round 52；loop 门禁读数待回填 §四）

对照 goal 目标（W 序列 + B/C/D 三批 + 全程纪律）逐项收证。

## 一、W 序列（7 项）
| 项 | 主张 | 证据 | 状态 |
|---|---|---|---|
| W1 裁定门 | 6 判据+分类+聚合，37/37 | tools/member_existence_gate.py 自测（G1-G18/C1-C18）+ 3 轮复核收口（5eb371d4/fbe198d4/63ce3392）| ✅（判据④尺寸锚未实现=如实标注）|
| W4-C0b | 打包尺寸 oracle 21 表；inline 0/167 | test_pipeline TestPackedInlineSize 6 测硬判 + 6dc45d18 复核 | ✅ |
| W2 幻影清理 | PAL3 20 删+7 正名+收缩 91024→4936；SceneMgr 22 删+4 处置 | 守卫批次 5 份 + beb91db4/695bcbb4/84fd2ef7 三复核；**0/323 字节全等**（零字节回退铁证）| ✅ |
| W3 退役审计 | 类型源统一灭双声明族 ≈−34 错 | C2040 +25→**0**、C2371 +3→−1、C2440 +5→1（codegen 实测）| ✅（C2372×1 尾账挂 W5）|
| W5 键纪律 | hex→dec 归一 + 双拼裁决 | **47 normalize_key + 2 delete_member**（双拼占位裁决）落地（原"49 条键归一"措辞经 b827549e 订正）；全库 hex 键残留=2=留裁对 ⚠️ C2DSpark 0x1c/0x1C **双条目并存——重裁前勿 codegen 该类**（同偏移双条目会双发射）| ✅（data.py:151 变体匹配修=尾账）|
| W6 AST 显式 this | C2660 −43~52 | ast_transform 修复 + 验收（2921 处 0 污染）+ C2660 **−52** 实测 | ✅（CreateEff 净新增=尾账）|
| W7 基线收官 | loop 门禁+对账+知识回写 | 知识 5 则 ✅；台账索引 90 篇 ✅；**棘轮 4 项待用户确认**；loop 门禁在跑 | 🔄 |

## 二、主线三批
| 项 | 主张 | 证据 | 状态 |
|---|---|---|---|
| **B** | W 重编目 697 + 真实成员分级填充 | v3 全链（13 契约）；**11 真填充**（2 A 级 float RoleSystem +0x508/+0x51c + 9 重定向）=终版期望 ≤11 ✓；W4M 340 诚实终态 | ✅ |
| **C** | SceneMgr 缺口 + CEffMgr 重定基 | SceneMgr 22+8+66 条归属清理全落地（beb91db4/84fd2ef7/21984786 三裁定全条件实施）；**(甲) 裁决伪命题→C-② 成分拆分兑现**（争端A：RoleSlot 50 条 g_RoleSlotBuf 面承接；争端B：相机块 +0x60 错位 4 迁/11 删/2 留裁；A4 m_pAddEffect 基字）；终态 SceneMgr 23 成员全有据；C0b 0/167 ✅；CEffMgr 串表证伪 ✅ | ✅ |
| **D** | loop 门禁+基线对账+知识回写 | 读数 S2 **95/208**·总错 **1657**·悬空 **0**·35 单元收敛·6 转绿；知识 5 则 ✅；loop 门禁在跑 | 🔄 |

## 三、全程纪律
- annotation 证据规则：全批次 evidence 逐条 VA 级（空 evidence 整批拒）✅
- 四道门：布局等价/错误不增/L1 不降/证据自校验——每批同运行读 ✅
- 每步对抗复核：**19 次派发、17 份有效结报**（条件全实施）；**2 次技术失败**（b6ed6ed5 崩溃、
  b827549e 空转 6 轮+引导未果已中断）⇒ 波次验证复核**缺独立结报**——其七问主张均备编排侧
  自测证据链（悬空 0/落点 7/7/键谱系/错误码逐条），独立确认层缺失如实记账；
- 零回归：新失败 **0**；共享行字节 0/323 变化 ✅。

### 附：2 条待归因新形态结案（round 61 自查）
1. PAL3.cpp L2994/3048 `gbVec3D* vs int`：`if (v123 != pEnd)` 的 pEnd 局部变量被 decomp 定型
   int 而实为指针（`(gbVec3D*)pEnd` 后文实证）= **Hex-Rays 局部定型残余**（非批次产物，错误数
   下降揭出的存量）——归 hexlimits/manual 类；
2. CCBRoleState L6329 `bDestRole`：`force->bDestRole[v3]` 渲染实证 **IDA 结构有字段而注解无**
   （tagCmdData=W4-C0b 11 inline union 点族）= 注解缺口——补成员需守卫 `add_member` kind（未有），
   挂尾账。

## 四、loop 门禁终读数（round 55 实测，三断言全过 ✓）
| 断言 | 期望 | 实得 | 判 |
|---|---|---|---|
| --expect-s2 | 95/208 | **95/208** | ✅ |
| --expect-errors | 1657 | **1657** | ✅ |
| --expect-l1 | 68 | **68**（棘轮 68→68 稳）| ✅ |

loop 流水实测：apply 21.5s ✓ · export 306.5s ✓ · codegen 301.7s（含内嵌 probe 读数）→
**中止于容错分类瑕疵**：codegen 内嵌 probe-s2 因陈旧基线 exit 1 被判"非容错"（容错表条目是
"compile_regression"、实际红门是 probe 内 regression_detector——名字错位）⇒ match 段由手动
补跑取数。**根因=棘轮陈旧**（4 项用户决策即根治）。
## 五、结论待定项（用户）
1. W7 棘轮 4 项（compile_baseline/baselines/L1 rebaseline/归档）——备忘 §一；
2. C-② 成分拆分批（首批误归属清理已备）是否作为下一段主项推进；
3. goal 是否在 loop 门禁绿+棘轮确认后 mark complete（C-② 与尾账按"目标保持活跃"处置）。
