# SwordUI 归属补证：RenderSword 调用点与实例前提（R7 灰区收口）

日期：2026-11-27 · 卡号：tsk_01M8CH9CS7MD7WGDY455JM（#45）· 只读

## 0. 结论摘要（先给判断）

1. `RenderSword@0x4AAD90` **是 thiscall 成员**：`mov esi, ecx`，体内 25 处 `[esi+disp]`，最大位移 `0x5D718`，小于 SwordUI 的 `0x5EF58`，也小于调用方对象的 `0x62588`。
2. 唯一调用点 `original/PAL3.exe.asm:252813`（`call sub_4AAD90`）位于 `sub_4AD540`；该函数是 `.rdata:0056F2A4` 槽（表 `0x56F29C` 第 2 槽）指向的虚函数，即 **402,824B 对象（`push 62588h` → ctor `sub_4A6F10` → 表 `0x56F29C`）的成员方法**，不是「另一个类误调」。
3. 卡面提到的 `[esi+62028h] > 0x5EF58` 不是一条比较指令，而是**地址算术事实**：`lea ecx,[esi+62028h]` 后 `call sub_4A1CF0`（读并复位 `[ecx+530h]`，即对象内 `+0x62558` 的 dword），返回值非 0 就跳过 `RenderSword`。这条说明 **`esi` 指向的对象至少 0x62558 字节**，因此它不可能是 388,952B 的 SwordUI 独立实例。
4. 实例前提五项（alloc 立即数 / ctor / 写 vtable / 槽位存储 / 尺寸闭合）**全部零命中**：全库 `grep -i "5ef58"` = 0 次。
5. 三档结论：**不可证（作为独立类）**。可证的替代解释是 **SwordUI 是 402,824B 对象的头部视图/切片**（`RoleStatePanel+0x2AFC8` 持有的那个对象），`RenderSword` 的真实 owner 是这个 402,824B 类。剩余的「一条证据」是表 `0x56F29C` 的类归属（与 #29 挂账的 402,824 类身份同一件事），不是 SwordUI 自己的 ctor。

## 1. 只读声明与复现命令

未运行任何 `pipeline/cli.py` 子命令，未改 annotation / 生成树 / 基线。全部证据来自 `original/PAL3.exe.asm` 文本与 `data/annotations/`、`data/status/` 的只读读取。

```bash
cd /home/peng/workspace/PAL3Decomp
grep -ic "5ef58" original/PAL3.exe.asm                      # 0
grep -n "62588h" original/PAL3.exe.asm                      # 240548 push 62588h
grep -n "56F29C" original/PAL3.exe.asm                      # 245101 写表 / 537911 表定义
nl -ba original/PAL3.exe.asm | sed -n '252808,252813p'      # 守卫 + 调用
nl -ba original/PAL3.exe.asm | sed -n '249383,249868p'      # RenderSword 全体
python3 - <<'EOF'
import json
d=json.load(open('data/annotations/structs/SwordUI.json'))
print(d['binary_size'], hex(d['binary_size']), len(d['known_members']), d.get('methods'), d.get('vtables'))
EOF
```

## 2. RenderSword@0x4AAD90 函数体取证

- 定义：`original/PAL3.exe.asm:249383`，`endp` 在 `249868`（485 行）；XREF 只有一条：`sub_4AD540+EC↓p`。
- 调用约定：`249383` 起 `push ebp; mov ebp,esp; sub esp,0D4h; push ebx; push esi; mov esi, ecx` ⇒ **thiscall**，`this` 在 `esi`。
- this 位移：脚本统计体内 `[esi+disp]` 共 25 处、16 个不同偏移，范围 `0x68`–`0x5D718`：
  - 头部：`0x68`（sprintf 缓冲，SwordUI 注解 `m_szSwordBuf char[64]` 同位）、`0x168`（计数递减）、`0x204`–`0x230`（一组 dword 读取/比较）。
  - 中部：`0x5544`、`0x5553`（两处 string 比较）、`0x5B98`（`mov eax,[esi+5B98h]; test eax,eax; jle` 入口守卫）、`0x2B514`、`0x2B5AC`（`sub_4426B0` 换图，正是 SwordUI 注解里 `m_*` UIStatic 区域）、`0x5D718`（`sub_4A6CA0` 参数基址）。
  - **无任何 ≥0x5EF58 的 this 位移** ⇒ 函数体的对象视图完全落在 SwordUI 声明的 388,952B 内。
- 语义：体内按 `dword_5D0750` switch 选 `UI\GameMainUI\Sword\Sword_Shui.tga / Sword_Huo.tga / Sword_Lei.tga…`，并做颜色四元组与 `sprintf` 文本渲染 ⇒ 确实是「剑（五行属性）UI」的渲染函数。
- 因此第①问：**是 thiscall 成员，位移起点 0x68，最大 0x5D718，落在 SwordUI 尺寸内**；但这条只证明「它按 SwordUI 布局访问对象」，**不能单独证明该布局有独立实例**（大对象的前 388,952B 同样满足）。

## 3. 调用点上下文：sub_4AD540 与 `[esi+62028h]`

- `sub_4AD540` 定义在 `original/PAL3.exe.asm:252714`，`endp` 在 `253240`，数据 XREF `.rdata:0056F2A4`。
- `0056F2A4` = 表 `0x56F29C` 的第 2 槽（`537911`–`537918`：`0x445E70 / 0x4AD140 / 0x4AD540 / 0x43DE40 / 0x445B90 / 0x4A7670 / 0x4ADC30`）。写这张表的是 `sub_4A6F10+697`（`245101: mov dword ptr [esi], offset off_56F29C`），而 `sub_4A6F10` 正是 `push 62588h`（`240548`）后的 ctor（`240558 call sub_4A6F10`）⇒ **`sub_4AD540` 是 402,824B 对象的虚方法**。
- `sub_4AD540` 开头 `mov esi, ecx`（`252726` 附近），随后直接以 `esi` 为对象基址访问：`[esi+5D718h]`（`252733`）、`[esi+2B7CCh]`（ReplaceTexture）、`[esi+68h]`（sprintf 时间串）、`[esi+6B58h]`/`[esi+6BF0h]`（`sub_4427C0` 两次文本刷新）、`[esi+168h]`（递减）——**这些偏移与 RenderSword / SwordUI 注解的头部布局一致**，说明调用方在同一个对象上操作 SwordUI 视图。
- 守卫段（`252808`–`252813`）：

```
252808  lea  ecx, [esi+62028h]
252809  call sub_4A1CF0        ; eax = [ecx+530h]; [ecx+530h] = -1  (读并复位 +0x62558 的 dword)
252810  test eax, eax
252811  jnz  loc_4AD9E8        ; 非 0 ⇒ 跳过 RenderSword
252812  mov  ecx, esi          ; this = 对象基址
252813  call sub_4AAD90        ; RenderSword
```

  `sub_4A1CF0` 本体（`237240`）：`mov eax,[ecx+530h]; mov dword ptr [ecx+530h],-1; retn` —— 一个「取出并复位」的 getter。
- 语义：`+0x62028` 是对象尾部的一个子对象（ctor 在 `245097` 用 `call sub_4A12F0` 构造它，`sub_4A12F0` 是 1,368B 的 UIRoleDialog；紧邻的 `245094` 还构造了 `+0x61AD0` 的另一个同型对象）。`+0x62028+0x530 = +0x62558` 距类尾 `0x62588` 还有 0x30 ⇒ 这是一个「待播动画/对话 id」字段：有值时这一帧不渲染剑，无值时调 RenderSword。
- 能否证否 SwordUI 归属：**能证否「独立实例」**。`esi` 指向的对象至少含 `+0x62558`，而 SwordUI 的 `binary_size=0x5EF58`；一个 388,952B 的对象不可能有 `+0x62028` 的子对象。因此 `RenderSword` 的 this 对象不是独立 SwordUI，而是 402,824B 对象；SwordUI 布局只能作为该对象的头部切片存在。

## 4. 实例前提五项（逐项命中/零命中）

| 前提 | 检查 | 结果 |
|---|---|---|
| alloc 立即数 | `grep -ic "5ef58" original/PAL3.exe.asm` | **0**（全库没有任何 `5EF58` 字面量；`62588h` 仅 1 处 `240548`） |
| ctor | `functions.json` / asm 中无 SwordUI ctor；唯一方法登记为 `0x004aad90` | **零命中** |
| 写 vtable | `SwordUI.json` 的 `vtables` 为 null；全库无 `off_56F...` 写点对应 SwordUI | **零命中** |
| 槽位存储点 | 无 `[reg]=SwordUI*` 型存储；402,824 对象的存储点是 `RoleStatePanel+0x2AFC8` | **零命中（SwordUI 自身）** |
| 尺寸 388,952 构造闭合 | 无 ctor 建链记录；成员最大 `0x5EF54`（`m_bHasWeapon uchar`）+ pad 恰好 `0x5EF58` | 只能说明注解自洽，**不能证明独立对象** |

补充：`SwordUI.json` 现状 `binary_size=388952`、`members=134`、`methods` 仅 `0x004aad90`、`vtables` 空；`data/status/struct_holes_20261125.json` 记 `size=388952 / hole_bytes=12700 / total_holes=46 / members=134 / bases=1`。

## 5. 归属解释（可证部分）

- 402,824B 对象的完整链：`RoleStatePanel::InitUI`（`sub_4A4220`）→ `push 62588h`（`240548`）→ `??2` → `sub_4A6F10`（ctor，写表 `0x56F29C`，并在 `+0x61AD0`/`+0x62028` 构造两个 UIRoleDialog）→ 存 `[RoleStatePanel+0x2AFC8]`。
- 该对象的虚方法 `sub_4AD540`（表第 2 槽）维护 SwordUI 头部字段（`0x68`/`0x168`/`0x6B58`/`0x6BF0`/`0x2B7CC`/`0x5D718`）并调 `RenderSword`。
- 因此 **SwordUI 更像「402,824B 类的前 0x5EF58 字节视图」**：与 `g_UISceneMapDlg` 的窗口切片同类处理，宜写成「某 402,824B 类对象的 Sword UI 切片」，而不是独立可分配类。注解里 `head_template 子对象基座锚` / `双视图共享头` 的既有注记与此一致。

## 6. 结论档位与 R7 清单更新

- 档位：**不可证（作为独立类）**。不是「需再补一条就能开」的独立类；缺的那条证据是 **表 `0x56F29C` / 402,824B 类的身份**（#29 已挂账「表归属裁决」），不是 SwordUI 自己的 ctor。
- 若后续要落 SwordUI：建议按「视图/切片」建档（`bases` 与 owner 指向 402,824B 类），并在 `note` 写明 `RenderSword` 的真实 this 是 402,824B 对象；**不要**按独立类开实现卡（会造出一个没有分配点的 388,952B 类）。
- R7 待开类清单（截至本卡）：

| 类 | 尺寸 | census 洞 | 真未闭合 | 档位 |
|---|---:|---:|---:|---|
| PropUI | 28,892 | 18,652 | 3B | 可开 |
| MainPropUI | 219,984 | 16,896 | 0 | 可开 |
| EquipUI | 266,260 | 15,960 | 80B | 可开 |
| LineupUI | 162,772 | 13,928 | 0 | 可开 |
| **SwordUI** | **388,952** | **12,700** | **不可定（视图型）** | **不可证独立类；等表 0x56F29C 归属（#29）** |

## 7. 未决

1. 表 `0x56F29C` 的类名与 15/22 个方法的归属（#29 挂账「表归属裁决」；本卡不重复考古）。
2. `+0x62028` 两个 UIRoleDialog（`+0x61AD0`、`+0x62028`）的语义（对话/动画 id 值域来自 `dword_5D0750` 与 `+0x62558`）。
3. SwordUI 注解 134 员的来源证据（多数 `annotation`，非本卡的否证范围；若要按切片建档，需要逐段对 402,824B 类的 head 布局重取）。
4. 402,824B 类与 `CCCTData`（注解 size 430,256、members 0）的关系仍是 #29 的 chimera 待重铸项，本卡未动。

## 8. 只读自证

```bash
git status --short            # 本卡仅 ?? docs/audit/2026-11-27-swordui-attribution-evidence.md
git diff data/annotations/structs/SwordUI.json pal3/src   # 空
```
