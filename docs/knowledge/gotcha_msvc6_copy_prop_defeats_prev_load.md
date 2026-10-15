# MSVC6 对 `Y = i` 复制对必前向传播——「经 prev 寻址」的双变量改写不翻字节

**现象**：A 级 objdump 显示原函数 `mov ecx,eax / mov eax,[ecx+0x3c]`（载入经 prev=Y），
我方编出 `mov ecx,eax / mov eax,[eax+0x3c]`（经 cur=i）。把 Hex-Rays 双变量循环的
增量从 `i = i->next` 改写成 `i = Y->next`（T44 规则，stage4_substitution）后，
编出字节**零变化**——MSVC6 仍前向传播 Y=i 的值用 eax 载入。

**为什么**：MSVC6 /O2 的复制传播发生在语句形状层面：只要载入基址变量的到达定义是
一个紧邻的寄存器复制（`Y = i`），它就用复制源寄存器。9 种双变量形（for/while/
do-while/逗号增量/字节偏移 cast/while 体末载入等）**全部**编出同一字节 ✗。
唯有**单循环变量形**让载入的基址成为循环携带变量（循环头多个到达定义 ⇒ 绑 home
寄存器 ecx）：

```c
// 双变量形（编出 8b 40 3c ✗）        // 单变量形（编出 8b 41 3c ✓ 34 字节全同）
for ( i = Y->next; i; i = i->next )   for ( ; Y->next; Y = Y->next )
{                                     {
    if ( i->key == K ) break;             if ( Y->next->key == K ) break;
    Y = i;                            }
}                                     return (int)Y->next;
return (int)Y->next;
```

等价性：循环头不变量 `i == Y->next`；`Y = i` 吸收进增量 `Y = Y->next`；break 在
`Y = i` 前离场 ⇒ 两侧都停在「Y = 命中点前」。守卫：体仅 2 句（if-break + `Y = i`）
⇒ 无 continue；函数内 i 无其它引用。实现：`stage4_substitution._try_loop_carry_rewrite`
（单测 `tests/test_stage4_loop_carry.py`）。

**何时使用**：凡「原函数载入经 prev、我方经 cur」的 1-字节 ModRM 差（0x41 vs 0x40 族），
先做单变量形受控实验（/tmp 独立 TU + 同 S4 flags 编译 + objdump 逐字节），**不要**再试
双变量改写或字节偏移 cast——实测全部无效。受控实验是判据（字节比对即裁判），别靠推理。
