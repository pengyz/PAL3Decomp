# R5 裁决：UIGameFrm 27,916B 是否为 g_gamefrm 内存第二视图

- 日期：2026-11-26
- 卡片：#8 `tsk_01M8BZ43BFACKBFT8GZKC2`
- 结论性质：**身份裁决**（本轮不改 annotation、不跑管线、不改基线）

---

## §0 结论（先给答案）

**判定：第二视图成立（同一存储的不同视图），处置 = 保留 UIGameFrm 现有成员（作为视图），删除清单为空。**

三条 A 级判据（下面 §2 给证据）：

1. **没有独立存储**：全 `.text` 搜索 `push $0x6e6c`（28,268）命中 **0**；`g_gamefrm`（0xDB9FD0）是**静态全局对象**，其 ctor `0x44f130` 只在启动初始化里被调 2 次（`0x404b22`、`0x404b7f`），**无 operator new 分配点**。
2. **UIGameFrm 自己构造/析构内嵌子对象**：ctor `0x44f130` / dtor `0x44f050` 用 `lea this+off, %ecx; call <子对象 ctor/dtor>` 直接构造/析构 5 个内嵌子对象 + 2 个定长数组（§2.2 表）。子对象 dtor 体内写各自 vtable（如 `0x44a7f0` 写 `0x56afb0`=UICaption、`0x44ace0` 写 `0x56afd4`=UITitle）。
3. **17/29/1 处「全局」引用地址 = 0xDB9FD0 + 偏移，精确算术相等**（§1、§2.1），且这些地址只被这一份存储覆盖（无其它分配点、无其它 `push $0x6e6c`）。写点样例：`0x436a2d mov %eax,0xdba240`，而 `0xDBA240 − 0xDB9FD0 = 0x270`，即写的是 `g_gamefrm` 的成员区。

⇒ 27,916B 洞区不是独立对象，而是这些**内嵌子对象/数组的未标注内部**。因此：
- **保留** UIGameFrm 成员（它们代表真实存储）；
- **不删**（删了洞区永远没有 owner，17/29/1 引用也失去基址锚）；
- 需要更正的是**既有注记**：`UIGameFrm.json` 的 `members_note`（line 619）写「独立对象实锤 … 零 UIGameFrm 方法内嵌构造证据」，与本节 A 级证据直接冲突，应由实施卡改写为「窗口切片」；
- `globals.json` 侧的 `overlaps_with: g_gamefrm` 已经是对的（2026-11-20 窗口切片定谳），保持；其中 `g_CCBEditorInst` 的 `CCBEditor` 型是「另一切片误型」（其注释已自记），`+0x1394` 实测是 UITitle（§2.2）。

---

## §1 引用面复核（17 / 29 / 1，逐条函数 + VA）

命令：`objdump -d original/PAL3.exe` 全量转储后，按绝对地址字面量匹配（`mov $0xADDR,%ecx` 为 receiver 取址形态）。函数归属用 `asm/pal3/decomp/*.json` 的 address/size 区间判定。

### 1.1 `0xDBA260`（= g_gamefrm+0x290，切片名 g_UIListBoxDlg）共 **17** 处

| 函数 | 站点 VA |
|---|---|
| 未入语料函数（0x428xxx 段） | 0x428e5c, 0x428e78, 0x428e94, 0x428eb0, 0x428ecc, 0x428ed6, 0x428ede |
| 未入语料函数（0x4290xx 段） | 0x4290b5, 0x4290db, 0x4290f7, 0x429101, 0x429109 |
| `PalScript::Op_RemoveItem(void)` | 0x43694c, 0x43696b, 0x436978, 0x436980, 0x436987 |

### 1.2 `0xDBAF10`（= g_gamefrm+0xF40，切片名 g_UISceneMapDlg）共 **29** 处

| 函数 | 站点 VA |
|---|---|
| `RoleSystem::UpdateFollowerMovement(float)` | 0x41a647, 0x41a651, 0x41a659, 0x41a660, 0x41a667, 0x41aab2, 0x41aabc, 0x41aac4, 0x41aacb, 0x41aad2（10） |
| `PalScript::Op_LK_Ghost(void)` | 0x43645d（1） |
| `PalScript::Op_FavorAdd(void)` | 0x43647c（1） |
| `PalScript::Op_Team(void)` | 0x43649f, 0x4364a9, 0x4364b1, 0x4364b8, 0x4364c1, 0x4364c9（6） |
| `PalScript::Op_GetMoney(void)` | 0x436b1e（1） |
| `PalScript::Op_LoadScene(void)` | 0x4374af, 0x4374b9, 0x4374c1, 0x4374c8（4） |
| `PalScript::Op_DlgHead(void)` | 0x4374ec（1） |
| `UITitle::OnMessage(int,uint,int)` | 0x44b781, 0x44b792, 0x44b79a, 0x44b7a1, 0x44b7aa（5） |

### 1.3 `0xDBB364`（= g_gamefrm+0x1394，切片名 g_CCBEditorInst）共 **1** 处

| 函数 | 站点 VA |
|---|---|
| `PalScript::Op_Movie(void)` | 0x4369fd |

> 计数与卡面 17/29/1 完全一致，可复跑（§8 命令 1）。

---

## §2 写者证据：这 27,916B 是不是同一存储的第二视图

### 2.1 地址算术（同一存储的直接判据）

| 切片全局 | VA | `VA − 0xDB9FD0` | UIGameFrm 内 dt/ctor 用的成员偏移 |
|---|---|---|---|
| g_UIListBoxDlg | 0xDBA260 | 0x290 | dtor `lea 0x290(%esi),%ecx; call 0x451900` |
| g_UISceneMapDlg | 0xDBAF10 | 0xF40 | dtor `lea 0xf40(%esi),%ecx; call 0x450eb0` |
| g_CCBEditorInst | 0xDBB364 | 0x1394 | dtor `lea 0x1394(%esi),%ecx; call 0x44ace0` |

写点样例（别名写入同一存储）：

- `0x436a2d  mov %eax,0xdba240` → `0xDBA240 − 0xDB9FD0 = 0x270`（g_gamefrm 内成员）
- `0x436c7d  mov %eax,0xdba244` → +0x274
- `0x436f27  mov %edx,0xdba24c` → +0x27C
- `0x44c742  mov %dl,0xdba250` → +0x280
- `0x4078f0  mov %ebx,0xdb9fd0(%eax)` → 以 g_gamefrm 为基址的索引写

### 2.2 UIGameFrm 自身构造/析构的内嵌子对象与数组（A 级）

`0x44f050`（UIGameFrm dtor）体：先 `movl $0x56b094,(%esi)`（自身 vtable），`call 0x44f430`，然后依次：

| 偏移 | 范围（含推断尺寸） | 子对象 dtor | dtor 写 vtable | 类（据 vtable 登记） |
|---|---|---|---|---|
| 0x38d0 | `+6×0x8e0` ⇒ 0x38d0–0x6e10 | `call 0x553549`（参数 `push $0x6`、`push $0x8e0`、elem dtor 0x44e5e0） | 元素级 | 定长数组 6×0x8e0 |
| 0x1394 | 0x1394–0x38c4（UITitle 9520=0x2530） | `call 0x44ace0` | `0x56afd4` | **UITitle** |
| 0xf40 | 0xf40–0x1334（切片声明 1012=0x3f4） | `call 0x450eb0` | `0x56b14c` + `0x56b140`(RoleAtt@+0x48) | 子对象存在=**A**；类身份逐案（vtbl `0x56b14c` 未登记，且 +0x48 是 RoleAtt 槽，与 UISceneMap 无 RoleAtt 基类不符） |
| 0x860 | `+5×0x160` ⇒ 0x860–0xf40 | `call 0x553549`（`push $0x5`、`push $0x160`、elem dtor 0x450390） | 元素级 | 定长数组 5×0x160 |
| 0x290 | 0x290–0x2d8（注解 UIListBox 72=0x48） | `call 0x451900` | `0x56b178` + `0x56b16c`(+0x48) | 子对象存在=**A**；类身份逐案（vtbl 未登记；globals 切片声明 1208B 与注解 72B 相互矛盾） |
| 0x164 | 0x164–0x1b0（RoleCameraCtrl 76=0x4c） | `call 0x450ad0` | `0x56b120` | **RoleCameraCtrl** |
| 0x104 | 0x104–0x164（UICaption 96=0x60） | `call 0x44a7f0` | `0x56afb0` + `0x56afa4`(+0x44) | **UICaption** |
| — | 最后 `call 0x445b40`（UIWnd 基类 dtor） | | | |

尺寸自洽：UICaption 96B 正好占满 0x104–0x164；UITitle 9520B 落 0x1394–0x38c4，与数组起点 0x38d0 只差 12B（对齐填充）；数组 6×0x8e0 正好收在 0x6e10（`m_pGameObj` 偏移）前。

### 2.3 「无独立分配」判据（否定独立实例的证据）

- `grep -c 'push $0x6e6c' 全量反汇编 = 0`；`$0x6E6C` 亦 0 ⇒ 没有 28,268B 的堆分配。
- `call 0x44f130`（UIGameFrm ctor）全树只有 2 处：`0x404b22`、`0x404b7f`（启动静态初始化路径），不是 `new` 后的构造。
- 因此 0xDB9FD0 起的 28,268B 是 PE 静态存储（.data/.bss），三个「切片全局」只是这份静态存储内部偏移的 IDA 锚名。

---

## §3 处置与门禁风险

**处置：保留视图（不删）**。具体：

1. **保留** `UIGameFrm` 现有 63 个成员（它们是真实存储的视图），删除清单为空。
2. **更正注记**（实施卡做，本卡不动）：`UIGameFrm.json` `members_note`(line 619) 的「独立对象实锤 / 零内嵌构造证据」与 §2.2 的 A 级证据冲突，应改写为「窗口切片：g_UISceneMapDlg@0xF40 / g_UIListBoxDlg@0x290 / g_CCBEditorInst@0x1394 是 g_gamefrm 内部子对象窗口，ctor/dtor 有 lea this+off 直证」。
3. **`g_CCBEditorInst` 的类型偏差**：其 `type=CCBEditor`、`binary_size=9624`（0x2598）会让 0x1394+9624=0x392C 越过数组起点 0x38D0，与 dtor 证据矛盾；实测 0x1394 是 **UITitle**（9520B，落点 0x38C4 刚好）。`globals.json` 的 source 已自记「CCBEditor型=另一切片误型」，保持记录、实施卡改型。
4. **门禁风险（删成员的反事实）**：
   - 若删成员：27,916B 洞区失去 owner，census 洞面只会更大，不会有任何收益；
   - 17/29/1 处引用地址（0xDBA260 等）将没有对应的声明锚点（只能退化成裸地址），后续 xref 归因会退化；
   - `UIGameFrm.cpp` **当前是 fail 单元**（`probe_census s2`：12 条错误，首条为 line 220 `C2664 unsigned char* → char*`），且 `s4_baseline` **没有任何 UIGameFrm 行**（0 行，故删/留都不改 L1 分子）；S2 现状 160/229。⇒ 本裁决对 L1 零影响；S2 若要变好，应走「修 UIGameFrm.cpp 的 12 条类型错」，而不是删成员。

---

## §4 洞区归属（37 洞 / 27,916B → 覆盖 25,997B，无证据 1,919B）

扫描口径：`data/status/struct_holes_20261125.json` 的 UIGameFrm 条目（`size 28268 / members 63 / holes 37 / hole_bytes 27916`）。归属范围取 §2.2 的子对象/数组。

| 洞区间 | 字节 | 归属（证据） |
|---|---|---|
| 0x108–0x148 / 0x14c–0x164 | 64 + 24 | UICaption@0x104（dtor 0x44a7f0，A） |
| 0x168–0x198 | 48 | RoleCameraCtrl@0x164（dtor 0x450ad0，A） |
| 0x19c–0x270 | 212 | 仅前 20B 属 RoleCameraCtrl（至 0x1b0）；其余 192B **无证据** |
| 0x290–0x2d8 | 72 | UIListBox 子对象区@0x290（dtor 0x451900，A；72B 恰等于 UIListBox.json 的 72B） |
| 0x734–0x8ac | 376 | 76B 属 array5 前导；300B **无证据** |
| 0x8e0–0x900 / 0x904–0x9b0 / 0x9b8–0xed4 / 0xed8–0xef5 | 32 + 172 + 1308 + 29 | array5×0x160@0x860（A） |
| 0xef8–0xf88 | 144 | 72B array5 尾 + 72B UISceneMap 头 |
| 0xf8c–0x1160 / 0x1168–0x13f0 | 468 + 648 | UISceneMap@0xF40（A；其中 0x1334–0x1394 的 96B 无证据） |
| 0x13f4–0x1680 … 0x32c4–0x38bc（共 9 段） | 652+648+648+648+652+2616+8+640+1976+1528 | UITitle@0x1394（dtor 0x44ace0，A） |
| 0x38d4–0x4028 / 0x402c–0x42d0 / 0x42d4–0x6e10 | 1876 + 676 + 11068 | array6×0x8e0@0x38d0（A） |

**明确「无证据」段（共 1,919B，不编造命名/类型）**：
0x4c–0xdc(144) · 0xe0–0xf4(20) · 0xf8–0x100(8) · 0x19c–0x270 的尾部(192) · 0x2dc–0x2e0(4) · 0x2e4–0x300(28) · 0x304–0x400(252) · 0x404–0x500(252) · 0x504–0x600(252) · 0x604–0x6d0(204) · 0x6d8–0x6fc(36) · 0x6fd–0x730(51) · 0x734–0x860(300) · 0x1334–0x1394(96) · 0x38c4–0x38d0(12) · 0x6e1c–0x6e6c(80)。

其中 0x304/0x404/0x504/0x604 四个 **252B 等长块**（步长 0x100，块间 4B 间隔）很像同一类的 4 个内嵌实例，但本轮**没有**找到它们的 ctor/dtor 调用点 ⇒ 按纪律标「无证据」，留待逐案取证（§5）。

---

## §5 下一步实施任务切分

**可批量（一条实施卡）**
1. 把 5 个子对象按 §2.2 落成带类型的成员：0x104 UICaption、0x164 RoleCameraCtrl、0x290 UIListBox 区、0xF40 UISceneMap 区、0x1394 UITitle；`evidence_level=verified`，source 写「ctor/dtor lea this+off + 子对象 vtable」。
2. 两个定长数组落成员：0x860 `?[5]`（stride 0x160，elem dtor 0x450390）、0x38d0 `?[6]`（stride 0x8e0，elem dtor 0x44e5e0）；元素类型待从 elem dtor 的 vtable 反推。
3. `globals.json` 的 `g_CCBEditorInst` 改型/改尺寸（→UITitle 语义），并确认 `overlaps_with` 三条仍在。

**需逐案取证（各一条小卡）**
4. 0x304/0x404/0x504/0x604 四个 252B 块：找 ctor/写者，判定是内嵌实例还是 UIGameFrm 自身字段。
5. 头部 0x4c–0x100（172B）：UIWnd 基类区之后的未标注段，需先对 UIWnd/UIFrameWnd 的 binary_size 复核。
6. 尾部 0x6e1c–0x6e6c（80B）：`m_pGameObjB` 之后，无引用点。
7. `UIGameFrm.cpp` 的 12 条 C2664（`unsigned char*` vs `char*`）——与洞区无关，但挡着该单元转 ok；建议单开修复卡。

**门禁**：以上都要过 `check_annotations` + `cli.py loop`；本卡不改 annotation（§6）。

---

## §6 本轮边界自证

- 未改任何 annotation：`git status --short data/annotations/` 中无 UIGameFrm.json / globals.json 的改动记录（并发成员对 SaleUI 等的改动不属本卡）。
- 未跑 apply/export/codegen/probe/loop；未写任何基线文件。
- 只读产物：`data/status/struct_holes_20261125.json`（19:06）、`data/status/probe_census.json`、`data/status/s4_baseline.json`、`original/PAL3.exe`（objdump）。

---

## §7 证据台账

- `ev_0009`（A，open）：UIGameFrm 27,916B = g_gamefrm 静态存储的第二视图；无 `push $0x6e6c`、ctor 仅启动 2 次、dtor `lea this+off` 析构 5 子对象 + 2 数组、切片地址=0xDB9FD0+off。
- `ev_0010`（A，open）：UIGameFrm 洞区归属 25,997/27,916B 有 A 级 owner（上述子对象/数组），余 1,919B 无证据（0x4c–0x100、0x304–0x730 四块、0x6e1c 尾）。

---

## §8 复现命令

```bash
cd /home/peng/workspace/PAL3Decomp
# 1) 17/29/1 引用面（全 .text 绝对地址匹配）
objdump -d original/PAL3.exe > /tmp/pal3_full_disasm.txt
grep -c '0xdba260' /tmp/pal3_full_disasm.txt   # 17
grep -c '0xdbaf10' /tmp/pal3_full_disasm.txt   # 29
grep -c '0xdbb364' /tmp/pal3_full_disasm.txt   # 1

# 2) 无独立分配
grep -c 'push   \$0x6e6c' /tmp/pal3_full_disasm.txt   # 0
grep -n 'call   0x44f130'  /tmp/pal3_full_disasm.txt   # 2 处：0x404b22 / 0x404b7f

# 3) UIGameFrm dtor 的子对象析构链
objdump -d --start-address=0x44f050 --stop-address=0x44f130 original/PAL3.exe

# 4) 子对象 dtor 写 vtable（类判定）
for a in 0x44a7f0 0x450ad0 0x451900 0x450eb0 0x44ace0; do
  objdump -d --start-address=$a --stop-address=$(printf '0x%x' $((a+0x30))) original/PAL3.exe | grep movl
done

# 5) 洞区归属
python3 - <<'PY'
import json
c=json.load(open('data/status/struct_holes_20261125.json'))
rows=c['classes'] if isinstance(c,dict) else c
u=[r for r in (rows if isinstance(rows,list) else rows.values()) if r['cls']=='UIGameFrm'][0]
print(u['size'],u['members'],u['hole_bytes'],len(u['holes']))
PY
```
