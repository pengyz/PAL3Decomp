# SaleUI 六池第二路径复核（IDA 文本清单，不依赖本卡探针）

本卡（#9）的池证据原本来自 idalib 逐指令跟踪探针。该探针对外不可直接复跑（要开 IDB）。
为了让复核者用**一条完全不同的路径**核对同一批事实，这里改用仓库里已有的 IDA 文本清单
`original/PAL3.exe.asm`（22.8 MB，纯文本，`grep`/`sed` 即可），不需要 IDA、不需要跑管线。

## 定位

```bash
grep -n "^sub_45A7B0 " original/PAL3.exe.asm      # ctor 140983–141339
grep -n "^sub_45AE60 " original/PAL3.exe.asm      # dtor 141431–141652
```

`??0SaleUI`/`??1SaleUI` 在这份清单里没有 demangle 名，按地址即 `sub_45A7B0`（ctor）/ `sub_45AE60`（dtor）。
ctor 的调用方在 `sub_4593C0`（= `CScreenMode::InitGameUI` 段）里：`:139310 push 19DB8h ; Size` → `call ??2@YAPAXI@Z` → `:139318 call sub_45A7B0`，与注解 `size_evidence`（operator new(0x19DB8)@0x459729 + ctor 0x45A7B0）一致。

## ctor 里的 6 个 `??_L`（`grep -n "??_L@YGXPAXIHP6EX0@Z1@Z"` 限定行号 140983–141339）

原文（`sed -n 141113,141200p original/PAL3.exe.asm`），cdecl 压栈序 **dtor → ctor → count → size → ptr**：

```asm
push offset sub_442390 / push offset sub_4422E0 / push 5    / lea ecx,[esi+6394h]  / push 98h / push ecx / call ??_L
push offset sub_442390 / push offset sub_4422E0 / push 0F0h / lea edx,[esi+66F4h]  / push 98h / push edx / call ??_L
push offset nullsub_1  / push offset sub_45ADD0 / push 0F0h / lea eax,[esi+11558h] / push 34h / push eax / call ??_L
push offset sub_444AC0 / push offset sub_444A20 / push 1Eh  / lea ecx,[esi+14618h] / push 0B4h/ push ecx / call ??_L
push offset sub_442390 / push offset sub_4422E0 / push 1Eh  / lea edx,[esi+15B30h]  / push 98h / push edx / call ??_L
push offset sub_442390 / push offset sub_4422E0 / push 0Dh  / lea eax,[esi+17A9Ch]  / push 98h / push eax / call ??_L
```

## dtor 里的 6 个 `??_M`（`sed -n 141600,141652p`）

```asm
push offset sub_442390 / push 5    / lea edx,[esi+6394h]  / push 98h / push edx / call ??_M
push offset sub_442390 / push 0F0h / lea ecx,[esi+66F4h]  / push 98h / push ecx / call ??_M
push offset nullsub_1  / push 0F0h / lea eax,[esi+11558h] / push 34h / push eax / call ??_M
push offset sub_444AC0 / push 1Eh  / lea edx,[esi+14618h] / push 0B4h/ push edx / call ??_M
push offset sub_442390 / push 1Eh  / lea ecx,[esi+15B30h] / push 98h / push ecx / call ??_M
push offset sub_442390 / push 0Dh  / lea eax,[esi+17A9Ch] / push 98h / push eax / call ??_M
```

## 对照表（两条路径一致）

| # | offset | stride | count | 跨度 | ctor 回调（ctor/dtor） | 注解类型 |
|---|---|---|---|---|---|---|
| 1 | 0x6394 | 0x98=152 | 5 | 760B | sub_4422E0 / sub_442390 | UIFrameContainer[5] |
| 2 | 0x66F4 | 0x98=152 | 0xF0=240 | 36,480B | sub_4422E0 / sub_442390 | UIFrameContainer[240] |
| 3 | 0x11558 | 0x34=52 | 0xF0=240 | 12,480B | sub_45ADD0 / nullsub_1 | 52B 未名元素（`unsigned char[12480]`） |
| 4 | 0x14618 | 0xB4=180 | 0x1E=30 | 5,400B | sub_444A20 / sub_444AC0 | CCBResultWindow[30] |
| 5 | 0x15B30 | 0x98=152 | 0x1E=30 | 4,560B | sub_4422E0 / sub_442390 | UIFrameContainer[30] |
| 6 | 0x17A9C | 0x98=152 | 0x0D=13 | 1,976B | sub_4422E0 / sub_442390 | UIFrameContainer[13] |

结论：6 个池的 `(offset, stride, count)` 在「文本清单」与「idalib 探针」两条路径上完全一致，
且 ctor/dtor 双向闭合（`??_L` 与 `??_M` 的 ptr/size/count 一一对应）。

## 顺带两条只有文本路径才看得到的东西

1. **`[esi+10564h]` 是一个索引标量，不是洞**。ctor 在池 3 调用前有 `mov [esi+10564h], ebx`（`:141144`）；
   另一个函数 `sub_4623A0`（`:150269` 起）读它：`mov eax,[esi+10564h]` → `cmp eax,edx` → 不等则清
   `0x10474` 与 `0x10568` 各 0xF0 字节后 `mov [esi+10564h],edx`。⇒ 该 4B 是「当前选中槽号」语义的标量。
   本卡注解把它留在残留洞里（7,684B 中的 4B），属于保守留白，可后续补为 `m_unk_0x10564 int`。
2. **`0x3E08`/`0x37C8` 是按索引取值的 int 数组基址**。同一函数 `mov ebp,[esi+edx*4+3E08h]`
   ⇒ stride 4、基址 0x3E08；这解释了 ctor 里 `rep stosd` 清 `0x37C8`/`0x3E08` 各 0x190 dword 的用途。
   本卡把这两段当作「ctor 清零跨度」证据使用（未落成员），与这一观察不冲突。
3. 残留段并非零访问：`esi+0F574h` 在清单里出现 20 次（含 `lea edx,[eax+0F574h]`、`mov [eax+esi+0F574h],edx` 这类基址+索引形态）；
   这已由 selfcheck §6 的「池尾基址 + 偏移」记录覆盖，属 R6 闭合卡的入口，不在本卡范围。

## 复跑成本

上面 4 条 `grep`/`sed` 在本机合计 < 1 秒，不占管线通道，不需要 IDB。
