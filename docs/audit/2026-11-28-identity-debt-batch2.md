# 身份债定谳（batch2）：C7 定义路由断链 8 条 · N15 五类 · C9 折叠载体名 4 条

- 日期：2026-11-27
- 性质：**只读定谳**（未改任何注解/JSON/基线，未跑 apply/export/codegen/probe/match）
- 输入：`python3 pipeline/cli.py check`（RC=0）的冻结输出
  - C7：`/tmp/qa73_check.log:134-141` 八行
  - N15：`/tmp/qa73_check.log:15`
  - C9：`/tmp/qa73_check.log:142-145` 四行
- 证据源：`asm/pal3/ida_structs.json`（结构体/槽值）、`data/status/_disasm_cache.txt`（objdump 反汇编副本）、`data/annotations/structs/*.json`、`data/status/ctor_evidence_registry.json`
- 台账：结论已逐条登记 `data/status/evidence_ledger.json`（ev_0065–ev_0081），本文引用 ev id。

> 说明：卡面写「C7 七条」，实际 check 冻结 **8 行**（gbBinkVideo 有 4 个自有槽：0x43de40 / 0x445b90 / 0x445e70 / 0x524970）。本文件按 8 行逐条定谳。

---

## 0. 一句话结论

| 族 | 条数 | 真身份错 | 折叠载体合法 | 证据不足 |
|---|---|---|---|---|
| C7 | 8 | 5（2×bases 缺失、1×methods 缺条目 + 2×同族） | 1（0x43de40 四类同体） | 2（并入 bases 缺失判定，见 §1.1/1.2） |
| N15 | 5 | 0 | 5（4 个登记缺口 + 1 个子对象副表） | 0 |
| C9 | 4 | 2（RoleSystem 表定界、UIEmote slot0 名错） | 2（UIEmote 副表被主链误比） | 0 |

**根因不是「名字没起」，而是三处建模缺口**：(a) UIWnd 族三个类的 `bases` 为空，继承槽被当成自有槽；(b) ctor 证据登记表漏录（N15 全族）；(c) 多继承副表与表农场定界没有进入 check 的比较口径。

---

## 1. C7：定义路由断链 8 条

### 1.1 CCBPanelSlot 0x00445b90（slot4）/ 0x00445d10（slot6）— 真身份错：bases 缺失

- **现象**：`vtable 0x56ae2c` 的 slot4/slot6 指向 0x445b90 / 0x445d10，本类 methods 只有 4 条（0x442420 HideAll、0x442ff0 Update_2ff0、0x4431b0 ~CCBPanelSlot、0x443200 Render），槽地址无条目。
- **二进制证据**：
  - 0x445b90 体（`_disasm_cache.txt:93660`）：`mov eax,[esp+4]; mov [esi+0xc],eax; ... lea edi,[esi+0x10]` —— 写成员 +0xc/+0x10 的 Create 形；`UIWnd` 表 `0x56aec8` slot4 正是 0x445b90 `Create`。
  - 0x445d10 体（`:93856`）：`xor eax,eax; ret 0xc` —— 返回 0 的 12 字节参数空实现；`UIWnd` 表 slot6 正是 0x445d10 `OnMessage`。
  - 本类 ctor 0x443190（`:89705` 起）：`push esi; mov esi,ecx; call 0x442e10; mov [esi],0x56ae2c`（`:89708`）——先调基类 ctor、再写本类表；`ida_structs.json` 中 `CCBPanelSlot` size=476、`bases=[]`。
- **裁决**：**真身份错（bases 缺失，不是 methods 缺条目）**。该表 7 槽与 UIWnd 表同形（slot0/1/2/3/5 是自有覆盖，slot4/6 继承 0x445b90/0x445d10），`bases=[]` 使 check 把所有槽当「自有」。补 bases 后两条 C7 自然消失，无需给这两个地址在 CCBPanelSlot 下造条目。
- **该谁修、在哪层**：annotation 层（`data/annotations/structs/CCBPanelSlot.json` 的 `bases`），owner=拆骨。证据写法：ctor 0x443198 写表 + 0x443193 基类 ctor 调用；若 0x442e10 是中间类，则填中间类而非直接 UIWnd（需一条 ctor 链确认）。
- 台账：ev_0065（0x445b90）、ev_0066（0x445d10）

### 1.2 RenderTarget 0x00445b90（slot4）/ 0x00445e70（slot0）— 真身份错：bases 缺失

- **现象**：`vtable 0x56c590` slot4=0x445b90、slot0=0x445e70，本类 41 条 methods 无这两个地址。
- **二进制证据**：
  - 0x445e70 体（`:94034`）：`mov eax,[ecx+0x34]; test eax,eax; ... mov edx,[ecx]; push 0; push eax; push 0x3e8; ...` —— 读成员 +0x34/+0x38、按可见性调虚槽 0；`UIWnd` 表 slot0 正是 0x445e70 `ShowClipped`。
  - 0x445b90 同上（UIWnd slot4 Create）。
  - ctor 区写表：0x486c6f（`:171254`）`mov [esi],0x56c590`；类 size=200、`bases=[]`；表 7 槽与 UIWnd 同形。
- **裁决**：**真身份错（bases 缺失）**。与 1.1 同型；补 `bases:[UIWnd@0]` 后两条消失。注意 slot3 是 0x43de40（见 1.3）、slot6 是 0x48f3a0（见 §4.1 新发现）。
- **该谁修、在哪层**：annotation 层 bases（`RenderTarget.json`），owner=拆骨。
- 台账：ev_0067（0x445b90）、ev_0068（0x445e70）

### 1.3 gbBinkVideo 0x0043de40（slot3）— 折叠载体合法（ICF 四类同体）

- **现象**：slot3 指向 0x43de40，本类 methods 无条目；check 报「自有槽无条目」。
- **二进制证据**：
  - 0x43de40 体（`:82523`）：`push esi; mov esi,ecx; mov ecx,[esi+0x44]; test ecx,ecx; je; call dword ptr ds:0x56a58c`（operator delete）；`mov [esi+0x44],0`；`mov ecx,esi; call 0x445c10`（UIWnd::HideAll）；`ret` —— 释放成员 +0x44 后尾调基类 HideAll。
  - 同一地址同时出现在：`RenderTarget` slot3（名 HideAll）、`gbBinkVideo` slot3（HideAll）、`SkillUI` slot3（Destroy）、`SwordUI` slot3（HideAll）四张表。
- **裁决**：**折叠载体合法**。这是四个类各自「释放纹理后调基类 HideAll」的同一实现被 ICF 折叠到一个地址；给每个类各造一条 methods 会造成同址多录（C8 债），不给条目又被 C7 判断链。正确形态是「同址多类同槽」的显式载体建模。
- **该谁修、在哪层**：门禁层（`pipeline/check_annotations.py` C7 增加「同址被 ≥2 个类的同一 slot 位引用 ⇒ 折叠载体豁免，但需至少 1 条 canonical 登记 + name_note」），owner=门禁 owner；canonical 登记可放 `gbBinkVideo.json` 或独立 stub 账（拆骨）。
- 台账：ev_0069

### 1.4 gbBinkVideo 0x00445b90（slot4）/ 0x00445e70（slot0）— 真身份错：bases 缺失

- **现象**：slot4=0x445b90、slot0=0x445e70，methods 57 条无条目。
- **二进制证据**：两地址体同 1.1/1.2（UIWnd Create / ShowClipped）；本类 ctor 0x523f30（`:378251` 起）`call 0x43dcd0`，而 0x43dcd0（`:82386`）`call 0x445aa0`（UIWnd ctor）后 `mov [esi],0x56ad20`、`mov [esi+0x44],0` —— 即 gbBinkVideo 的基类 0x43dcd0 本身就是 UIWnd 派生，ctor 链成立；`bases=[]` 是缺口。
- **裁决**：**真身份错（bases 缺失）**。补 bases 后两条消失（注意填 0x43dcd0 对应类，而不是直接 UIWnd，chain 才与 ctor 调用一致）。
- **该谁修、在哪层**：annotation 层 bases（`gbBinkVideo.json`），owner=拆骨；填之前先用 0x43dcd0 的 `[esi]=0x56ad20` 找该类名。
- 台账：ev_0070（0x445b90）、ev_0071（0x445e70）

### 1.5 gbBinkVideo 0x00524970（slot1）— 真身份错：methods 缺条目

- **现象**：slot1 指向 0x524970，槽名 `Render`，methods 无条目；而同类 slot2 Update / slot6 OnMessage 都有条目并有 `override` 标记。
- **二进制证据**：
  - 0x524970 体（`:378970`）：`jmp 0x43ddf0` —— 纯尾跳 thunk。
  - 目标 0x43ddf0 体（`:82386+` 区）：`sub esp,0x44; mov eax,[esi+0x38]; test eax,eax; je; mov eax,[esi+0x44] ...` —— 按视频源状态绘制（与 UIWnd::Render 0x445cd0 不同体）。
  - 本类表 `0x570630` slot1=0x524970；UIWnd 表 slot1=0x445cd0 Render ⇒ 合法覆盖。
- **裁决**：**真身份错（methods 缺条目）**。这是真正的「定义路由断链」：调用点写 `gbBinkVideo::Render` 会 C2039。修法=补 methods 条目（名 Render，flags override，override_of 0x445cd0，sig 从 thunk 目标 0x43ddf0 的 ret 字节定）。
- **该谁修、在哪层**：annotation 层（`gbBinkVideo.json` methods），owner=拆骨。
- 台账：ev_0072

---

## 2. N15：五类「无 ctor 证据」— 全为登记/建模缺口

check 的 N15 只读 `data/status/ctor_evidence_registry.json` 的 `classes` 集合（不读 ida_structs、不读注解 flags），未登记者一律进 advisory 普查。逐类二进制核实：

| 类 | 二进制 ctor 证据 | 裁决 | 修法 |
|---|---|---|---|
| CCBUICtrl | ctor 0x519310（注解名 CCBUI，flags ctor）；0x51933c（`:364702`）`mov [esi],0x5704c8` 写本类表 | 非伪造，登记缺口 | 注册表补 CCBUICtrl（ref: 0x51933c） |
| PalScriptWaitObj | 无自有 ctor；表 0x56afa4 只由宿主 UICaption ctor 0x44a7b0（`:99002` `mov [esi+0x44],0x56afa4`）与 dtor 0x44a801（`:99040`）写 ⇒ 子对象副表 | 建模合法（base-subobject 副表） | 注册表按「宿主 ctor 0x44a7b0」登记 + N15 支持副表豁免 |
| ScreenEffectRingNode | ctor 0x4bee60（`:241464`）`call 0x4b6f70`（PAL3VisNode ctor）；表 0x56f580 | 非伪造，登记缺口 | 注册表补（ref: 0x4bee60） |
| SkillUI | ctor 0x525120；0x52543b（`:379765`）`mov [esi],0x5706cc` 写本类表 | 非伪造，登记缺口 | 注册表补（ref: 0x52543b） |
| SwordUI | ctor 0x4a6f10；0x4a75a7（`:211091`）`mov [esi],0x56f29c` 写本类表 | 非伪造，登记缺口 | 注册表补（ref: 0x4a75a7） |

- **裁决汇总**：五类都不是「伪造候选」，N15 当前是「登记表为空导致的普查噪音」。其中四类补登记即可清零；PalScriptWaitObj 需要 N15 增加「子对象副表（表地址由宿主 ctor 在 +offset 写入）」的合法形态，否则它永远无法自证。
- **该谁修、在哪层**：数据层 `data/status/ctor_evidence_registry.json`（owner=拆骨）+ 门禁层 N15 副表豁免（owner=门禁 owner）。
- 台账：ev_0073（CCBUICtrl）、ev_0074（PSWO）、ev_0075（ScreenEffectRingNode）、ev_0076（SkillUI）、ev_0077（SwordUI）

---

## 3. C9：折叠载体名冲突 4 条

### 3.1 RoleSystem 0x004209e0 slot6「ResetState」vs 基 OnMessage 0x445d10 — 真身份错（表定界/归属层）

- **现象**：slot6=0x4209e0 名 ResetState，UIWnd slot6=0x445d10 OnMessage（空 stub），链律名冲突。
- **二进制证据**：
  - 0x4209e0 体（`:42142`）：`mov [ecx+0x10],0; jmp 0x4202f0` —— 清成员 +0x10 后尾跳。
  - 0x4202f0（slot0，名 ~RoleSystem）体（`:414xx`）：`push esi; mov esi,ecx; mov eax,[esi+0xc]; test; je; push eax; call 0x552f55`（free）—— 释放缓冲区的析构形。
  - RoleSystem 表 0x56aad8 有 **9 槽**，且 slot0/2/5/8 四个 dtor 形（~RoleSystem、_scalar_dtor_0270、_scalar_dtor_0430、_scalar_dtor_0910），与 UIWnd 族 7 槽形状（slot0=ShowClipped 0x445e70）不符；表由 0x420254 / 0x420290（`:41412`/`:41442`）写。
- **裁决**：**真身份错，但错在表定界/归属层（G2），不在名字层**。9 槽 4 dtor 是「表农场被合并读成一张表」的典型形态；slot6 的 ResetState 与 UIWnd OnMessage 不可比，因为这张表很可能不是 RoleSystem 的 UIWnd 主表。在表定界厘清前，`ResetState` 名**不定谳**。
- **该谁修、在哪层**：表定义层（raw .rdata 直读定界 0x56aad8 前后表、7 槽周期识别），owner=表定义/审计 owner；定界后若确属 RoleSystem 主表，再按 UIWnd 链律改名。
- 台账：ev_0078

### 3.2 UIEmote 0x0044ab00 slot1「GetType」vs 基 Render 0x445cd0 — 折叠载体合法（副表被主链误比）

- **现象**：UIEmote 表 0x56b044 slot1=0x44ab00 GetType，基槽 Render=0x445cd0。
- **二进制证据**：
  - 0x44ab00 体（`:99321`）：`mov eax,[ecx-0xc]; ret` —— 读「本对象前 0xc 字节」的宿主字段，是子对象视角的 getter；同址也是 PalScriptWaitObj 表 0x56afa4 的 slot1。
  - 表 0x56b044 的写入点：ctor 0x44e595（`:103933`）`mov [esi+0x44],0x56b044`；完全 dtor 0x44e607（`:103978`）`mov [edi],0x56b044`（edi=ecx+0x44）⇒ **这是 UIEmote 在 +0x44（GameObject 基）处的副表**，不是主表。
  - 主基链 scScriptInstance 表 0x56b050 slot1=0x445cd0；check 却拿 UIWnd 链（Render）比较副表 slot1。
- **裁决**：**折叠载体合法 + check 比较口径错**。GetType 是副表自己的语义（读宿主类型字段），与 Render 不是同一契约；冲突来自「用主基链比副表」。
- **该谁修、在哪层**：annotation 层补 `bases` 的次基（GameObject@0x44）表对应关系；门禁层 C9 的 `_anc_slot_chain` 次表分派（已有 `_first` 机制，但 bases 缺表条目导致落到主链）。owner=拆骨 + 门禁 owner。
- 台账：ev_0079

### 3.3 UIEmote 0x0044e980 slot5「OnVisible」vs 基 ~UIWnd 0x445b20 — 折叠载体合法（同一副表误比）

- **现象**：slot5=0x44e980 OnVisible，基 ~UIWnd=0x445b20（deleting dtor），名冲突。
- **二进制证据**：0x44e980 体（`:104239`）：`push esi; mov esi,ecx; mov eax,[esi+0x38]; test; je → xor eax,eax; ret 8`；否则读 [esi+0x4c]、[esi+0x8a4] 继续 —— 可见性判定，`ret 8` 双参，明确不是析构器。
- **裁决**：**折叠载体名合法 + check 误比**（与 3.2 同一张副表 0x56b044、同一根因）。
- **该谁修、在哪层**：同 3.2。
- 台账：ev_0080

### 3.4 UIEmote 0x0044eb40 slot0「Reset」vs 基 ShowClipped 0x445e70 — 真身份错（名 + flags）

- **现象**：slot0=0x44eb40 名 Reset。
- **二进制证据**：0x44eb40 体（`:104408`）：`sub ecx,0x44; jmp 0x44e5c0` —— 8 字节 adjustor thunk；0x44e5c0（`:103953`）是 UIEmote 标量删除 dtor（`call 0x44e5e0; test byte[esp+8],1; je; push esi; call 0x541d10; ... ret 4`）。⇒ 0x44eb40 = **副表（+0x44 子对象）视角的 deleting-dtor adjustor thunk**，不是 Reset。
- **裁决**：**真身份错（名错 + 缺 declaration_only/adjustor 标记）**。应命名为 `UIEmote_dtor_adjthunk` 形（先例：#59/#64 的 `UICaption_dtor_adjthunk`），并写 name_note 记录 `sub ecx,0x44; jmp 0x44e5c0`。
- **该谁修、在哪层**：annotation 层（`UIEmote.json` methods 0x44eb40 改名 + name_note；vtable slot0 名同步），owner=拆骨。
- 台账：ev_0081

---

## 4. 定谳中新发现（不在冻结清单，建议单开卡）

### 4.1 RenderTarget slot6 0x0048f3a0 名为 `OnRender`，体是消息处理器

- 0x48f3a0 体（`:181556`）：`sub esp,0x108; ... mov ecx,[esp+0x118]; lea eax,[ecx-0x3e8]; cmp eax,0x14; ja 0x49082a; ... mov dl,[eax+0x490878]` —— 按消息号 0x3e8..0x3fc 查表跳转，是 `OnMessage` 形态，不是渲染函数。
- 影响：一旦补上 RenderTarget 的 bases（§1.2），C9 会在 slot6 报 `OnRender` vs `OnMessage`；现在只是被 bases=[] 掩盖。建议单卡：核 0x490878 跳转表的目标族，定 slot6 名。

### 4.2 UIEmote 副表缺 GameObject 次基建模

- 3.2/3.3 的根因是 `bases` 只有 scScriptInstance@0、GameObject@0x44 没有对应 vtable 条目（`GameObject` size=4、`vtables=[]`）。要么给 GameObject 建档 vtable 0x56b044 的归属，要么在 UIEmote 的 vtable 列表里加第二张表并标 `bases[1]`，否则 C9 的次表分派永远落回主链。

### 4.3 RoleSystem 表 0x56aad8 需重新定界

- 见 3.1：9 槽 4 dtor，疑似表农场合并。在定界前，RoleSystem 的所有 C9/C7 结论都不应作为改名依据。

---

## 5. 修法汇总（谁修、哪层）

| 序 | 项 | 修法 | 层 | owner |
|---|---|---|---|---|
| 1 | CCBPanelSlot bases | 补 `bases`（0x442e10 链确认后填） | annotation | 拆骨 |
| 2 | RenderTarget bases | 补 `bases:[UIWnd@0]` | annotation | 拆骨 |
| 3 | gbBinkVideo bases | 补 `bases`（0x43dcd0 对应类） | annotation | 拆骨 |
| 4 | gbBinkVideo 0x524970 | 补 methods Render(override_of 0x445cd0) | annotation | 拆骨 |
| 5 | 0x43de40 四类同体 | C7 增「同址多类同槽」折叠载体豁免 + canonical 登记 | 门禁 + annotation | 门禁 owner / 拆骨 |
| 6 | N15 四类 | 补 `ctor_evidence_registry.json`（ref: ctor 写表指令） | data | 拆骨 |
| 7 | N15 PSWO | N15 增子对象副表豁免 + 按宿主 ctor 登记 | 门禁 + data | 门禁 owner |
| 8 | C9 RoleSystem | 0x56aad8 raw .rdata 重新定界（表农场识别） | 表定义 | 表审计 owner |
| 9 | C9 UIEmote 3.2/3.3 | 补 GameObject 次基/副表建模 + C9 次表分派修正 | annotation + 门禁 | 拆骨 / 门禁 owner |
| 10 | C9 UIEmote 3.4 | 0x44eb40 改名 `UIEmote_dtor_adjthunk` + declaration_only + name_note | annotation | 拆骨 |
| 11 | 新发现 4.1 | RenderTarget slot6 名定谳（跳转表 0x490878 核目标族） | annotation | 拆骨（单卡） |

> 注：以上修法**均不在本卡写域**（本卡只写审计 md + evidence ledger），需由 lead 按上表分派；本卡不替修。

---

## 6. 复现命令

```bash
cd /home/peng/workspace/PAL3Decomp
python3 pipeline/cli.py check            # 冻结输出来源（RC=0）
grep -n '445b90\|445e70\|445d10\|43de40\|524970\|4209e0\|44ab00\|44e980\|44eb40' data/status/_disasm_cache.txt
python3 tools/evidence_ledger.py query --subject 'C7' --full
```

证据行号以 `data/status/_disasm_cache.txt` 当前版本为准（本文件引用行号已逐条核对）。
