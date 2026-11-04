# 名字撞名裁决队列（2026-11-04）

> 设计定案：戳归一下沉 annotation 层、让隐性撞名变真撞名（用户裁定）。本队列 = 显形后的裁决工作单。
> 棘轮处置（用户裁定）：cxx_gate 基线已重冻（491 键，2026-11-04），撞名逐条在此登记裁决，不阻塞提交。

## §1 A 真撞组（同 TU 同名同签双正文 = 现实 C2084，逐对二进制取证正名）

| # | 组 | 双址 | 现状 | 裁决状态 |
|---|---|---|---|---|
| 1 | UIListBox::Destroy | 0x43DE90 / 0x43E520 | C2084 @UIListBox.cpp L423 | 待裁决 |
| 2 | CCBProtectWindow::Destroy | 0x43D920 / 0x5164D0 | C2084 @CCBProtectWindow.cpp L43 | 待裁决 |
| 3 | CCBFiveNimbusWindow::Destroy | 0x4438F0 / 0x519F50 | C2084 @CCBFiveNimbusWindow.cpp L251 | 待裁决 |
| 4 | UILoadingFrm::OnMessage | 0x450990 / 0x451AA0 | C2084 @UILoadingFrm.cpp L104 | 待裁决 |
| 5 | ArraySort（free_functions） | 双址 | C2084 埋在 C1003 截断单元 | 待裁决 |

裁决方法：per-pair 二进制取证（调用簇/成员访问/vtable 槽/ctor vptr）→ 真名正名或归属迁移。
参考：out/_adversarial_review_verdict.md（全库扫描：A 真撞仅此 5 组；UIScene::Destroy 为注解认领粒度假阳性，0x43AB00 真名 UICaption::Destroy 入他 TU）。

## §2 `_xx` 尾戳名族（下一步进攻点：统计 + 正确语义化，用户裁定 2026-11-04）

弹药清单：**data/status/tail_name_census_20261104.md**
- 真撞 26 组（剥尾即撞，语义正名优先队列：UIWnd::HideAll / UIFrameWnd::Destroy,Render,Update / CCBUI::Destroy,InitUI,Update / PAL3::Render / CCBSystem::Initialize / Actor::Method / UIListBox::Render / UIScene::Render …）
- 重载候选 19 组（异签，剥尾安全）· 单例 8 · 合成物/CRT 另账 142（crt_sub/_sdtor/SingletonThunk 族地址尾=身份，不剥不算进攻面——D7 教训）

## §3 门禁修复记录（2026-11-04）

- cxx_sig_key 末参名泄漏修复 + 类型词防护（tests/test_cxx_collision_detector.py 锁）
- cxx_gate 退出码接通（新增=exit 1 硬红）
- test_ovl_suffixed_exempt → test_ovl_suffixed_stripped_and_judged（契约翻转：戳名剥后撞名必须报）
- 防回流锁 tests/test_ovl_migration_lock.py（管线禁剥戳副本 + annotation 活数据禁戳名）
