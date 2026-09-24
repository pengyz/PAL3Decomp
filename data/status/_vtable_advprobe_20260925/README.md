# vtable ABI 对抗性探针（2026-09-25，对抗性复核证据）

针对 `docs/superpowers/specs/2026-09-25-vtable-mapping-design.md`（v2）的对抗性复核实测。
工具链与 `_vtable_abi_probe_20260925/` 相同（cl 12.00.8168 + `tools/coff_vtable.py`）。
除 vt6_repro 用 `/Od /GR`（原探针同参）外均 `/Od /GR`；adv1–adv3 首轮 `/O2` 系。
**未跟踪草稿**，可整目录删除。

| 用例 | 场景 | 实测结论 | 打击的设计条款 |
|---|---|---|---|
| adv1 | 协变返回覆写（MI） | **C2555 编译拒绝**——MSVC6 不支持协变返回 ⇒ 二进制无协变返回 thunk | §2.1 枚举（该缺口**证伪**，不成立）|
| adv2 | 派生类新增**同名**新重载 `o(char)` | 尾插主表末（槽 3），同名组跨区段**不连续** | §2.2"组位置=首现位置连续区段"**证伪** |
| adv3 | 析构 + const 限定重载 | deleting dtor 落声明位（槽 0）；`o() const` 与 `o(int)` 同名成组逆序 ✓ | §2.2 缺失维度补充 |
| adv4 | 尾插段两个同名重载 | 尾插段内部仍同名组逆序（y(double), y(int)）；真实规则=基类槽位原位保留 ++ 新增段组内逆序 | §2.2 平坦反演算法**证伪** |
| adv5 | 抽象类 + out-of-line 非纯虚函数 | **0 个 vtable 符号**——无法用"构造对象"强制发射 | §3.6 强制发射**无解** |
| adv6 | 抽象类 + 虚析构 | `??_7AB2` 出现（槽=[??_E, __purecall]）⇒ 虚析构才是发射锚点 | §3.6 修复路径（文档未写）|
| adv7 | 虚继承 + 虚析构 + ctor 虚调用 | 槽 `??_EDV@@$4PPPPPPPM@A@AEPAXI@Z` = **deleting_dtor × vbase adjustor 复合槽** | §2.1 单值 kind **不可表达** |
| vt6_repro | 原探针 vt6.cpp 的 `DO : O`（README 编了未报结果） | DO 只声明 1 个覆写，槽序逐位继承 O 的 4 槽；平坦反演会造出 3 个幽灵覆写 | §2.2 反演算法**证伪** |

复现：
```sh
INC=tools/compilers/msvc6.0/Include
tools/wine_cl.sh /c /nologo /Od /GR /I$INC /Fo/tmp/advN.obj data/status/_vtable_advprobe_20260925/advN.cpp
python3 tools/coff_vtable.py /tmp/advN.obj
```
