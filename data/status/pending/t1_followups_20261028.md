# T1 复核 follow-up 挂账（f814bc0b ACCEPT-WITH-FIXES）

- [D3 叙事勘误] 实效口径=**14 处 C2065 全清 / 9 单元转绿**（非「9 处」）——本文件为准
- [D5 叙事补记] 附带新增 decl 4 个（IsAnimDone/IsFadeDone/ResetIdle/ResetContainerState，thiscall 条目经 free_sig_decl 双形面顺带接通，decl 456→461 增 5 损 0）
- [D6 欠账] **T1 Step 5 未做**：overlay 47 条中 Destroy__ovl_03 注释块 10 处/9 文件待回收（须纯态 probe 该单元 ok 后逐条撤）
- [D7 挂账] **PropUI deleting_view 解除动作**独立立项（身份已定谳：0x43D880 纯析构 thunk，源写 ~UIFrameWnd() 即再生）——归 PlanA-T4 合成物清理或独立
- [D4 状态] 源形态（同体 override 簇 vs 单一中间类）**二进制不可判定**，解除时勿按「已定谳簇」处理

## (ii) 对象定义进展（2026-10-29）
- ✅ 0xD8C2E8/0xD8C2C8 存储注册（char[32] 保守型+_todo_ 名，布局证据入 source）
- ✅ 0xD8C338=Iostream CRT 对象（<iostream> 再生路径，Site1 已闭）
- ⏳ 0xDE8B40：尺寸未定（邻界取证待）——注册挂账
- ✅ g_RenderTarget3 既有注册（RenderTarget3 型）
- ✅ 0xDE8B40 存储注册（char[696] 几何定界+双生胶水形；RT2 直挂已证伪；真名真型待裁 confidence:low）
- ⏳ P6 挂账升级：crt_sub_00541590 调用形修复=字节匹配阶段项（真形 push 0+ecx 双参 thiscall，
  自由函数载体不可等价（fastcall 双参走 ecx/edx≠栈参）⇒ 留待调用形转写基建（D2b 反方向）
