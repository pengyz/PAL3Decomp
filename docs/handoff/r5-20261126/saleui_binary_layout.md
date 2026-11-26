# SaleUI 二进制布局（ctor/dtor 邻接分区）

来源：`??0SaleUI` 0x45A7B0–0x45ADC3（1555B）与 `??1SaleUI` 0x45AE60–0x45B200（928B）逐条反汇编；
方法：把每个 `lea ecx,[esi+OFF]` + 紧随构造/析构调用的位置记为分区起点，段长取「下一个起点 − 本起点」（末段取 class_size 0x19DB8）。
每个分区都同时有构造侧与拆除侧证据，故段长不是猜测；元素类尺寸（如 152/344/1368/180）与 IDB 尺寸交叉一致时才写成类名。

| 偏移 | 段长 | 构造侧 | 拆除侧 |
|---|---|---|---|
| 0x0178 | 13896 | ctor:? | — |
| 0x37c0 | 8 | ctor:? | — |
| 0x37c8 | 1600 | ctor:? | — |
| 0x3e08 | 1600 | ctor:? | — |
| 0x4448 | 404 | ctor:? | — |
| 0x45dc | 7056 | array:unknown1408[5x1408]; ctor:? | — |
| 0x616c | 152 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x6204 | 84 | ctor:UI3DCtrl::UI3DCtrl(void) | UIFrameWnd::__deleting_view(void) |
| 0x6258 | 152 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x62f0 | 164 | ctor:PalScript::PalScript(void) | PalScript::~PalScript(void) |
| 0x6394 | 864 | array:UIFrameContainer[5x152]; ctor:`eh vector constructor iterator'(void *,uint,int,void (*)(void *),void (*)(void *)) | `eh vector destructor iterator'(void *,uint,int,void (*)(void *)) |
| 0x66f4 | 40320 | array:UIFrameContainer[240x152]; ctor:`eh vector constructor iterator'(void *,uint,int,void (*)(void *),void (*)(void *)) | `eh vector destructor iterator'(void *,uint,int,void (*)(void *)) |
| 0x10474 | 244 | ctor:? | — |
| 0x10568 | 4080 | ctor:? | — |
| 0x11558 | 12480 | array:unknown52[240x52]; ctor:`eh vector constructor iterator'(void *,uint,int,void (*)(void *),void (*)(void *)) | `eh vector destructor iterator'(void *,uint,int,void (*)(void *)) |
| 0x14618 | 5400 | array:CCBResultWindow[30x180]; ctor:`eh vector constructor iterator'(void *,uint,int,void (*)(void *),void (*)(void *)) | `eh vector destructor iterator'(void *,uint,int,void (*)(void *)) |
| 0x15b30 | 4561 | array:UIFrameContainer[30x152]; ctor:`eh vector constructor iterator'(void *,uint,int,void (*)(void *),void (*)(void *)) | `eh vector destructor iterator'(void *,uint,int,void (*)(void *)) |
| 0x16d01 | 35 | ctor:? | — |
| 0x16d24 | 128 | ctor:? | — |
| 0x16da4 | 12 | ctor:? | — |
| 0x16db0 | 308 | ctor:UIProgressBar::ctor(void) | PalScript::Reset(void) |
| 0x16ee4 | 1368 | ctor:UIRoleDialog::UIRoleDialog(void) | UIRoleDialog::~UIRoleDialog(void) |
| 0x1743c | 152 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x174d4 | 152 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x1756c | 152 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x17604 | 168 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x176ac | 344 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x17804 | 344 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x1795c | 168 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x17a04 | 152 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x17a9c | 1976 | array:UIFrameContainer[13x152]; ctor:`eh vector constructor iterator'(void *,uint,int,void (*)(void *),void (*)(void *)) | `eh vector destructor iterator'(void *,uint,int,void (*)(void *)) |
| 0x18254 | 152 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x182ec | 152 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x18384 | 1224 | ctor:call    sub_43DFC0 | call    sub_43E120 |
| 0x1884c | 748 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x18b38 | 152 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x18bd0 | 168 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x18c78 | 168 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x18d20 | 168 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x18dc8 | 168 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x18e70 | 364 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x18fdc | 360 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x19144 | 360 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x192ac | 360 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x19414 | 344 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x1956c | 344 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x196c4 | 344 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x1981c | 344 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x19974 | 376 | ctor:NameSys::GetSys(void) | UICaption::Destroy2(void) |
| 0x19aec | 154 | ctor:call    ResetContainerState | UIFrameContainer::~UIFrameContainer(void) |
| 0x19b86 | 256 | ctor:? | — |
| 0x19c86 | 306 | ctor:lstrcpyA | — |

## 读法与注意

- `ResetContainerState` = `UIFrameContainer` 的构造入口（EquipUI R2 已用同一入口定谳 UIFrameContainer），拆除侧对应 `~UIFrameContainer`，两侧吻合的段类名可靠。
- `NameSys::GetSys` 侧的构造调用在 dtor 里对应 `UICaption::Destroy2` ⇒ 这些段实为 344B 的 UICaption 实例（名与类不符，命名时以拆除侧为准）。
- 0x6204 段 84B：构造侧 `??0UI3DCtrl`、拆除侧 `UIFrameWnd::__deleting_view`；IDB 的 UI3DCtrl=308B 与此不符 ⇒ 本类里该成员的真实占用按邻接 84B 记，IDB 尺寸不可直接用。
- 0x62F0 段 164B：构造侧 `??0PalScript`、拆除侧 `~PalScript`；IDB PalScript=2176B 与邻接 164B 矛盾（2176 会撞进 0x6394 的池）⇒ 同上，按邻接记。
- 0x10474 / 0x10568 两处各 240B 是 `rep stosd` 清零（0x3C dword），无构造调用 ⇒ 只能作「清零区」证据，不足以定成员类型。
- 0xF574–0x11558 之间除上述两处清零外没有构造证据，是真实缺口，不要在 R5 里填。
