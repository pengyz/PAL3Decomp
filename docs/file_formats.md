# PAL3 文件格式文档

来源：OpenPAL3 (dontpanic92) + PAL3patch (zhangboyang)

## CPK 归档格式

CPK 是仙剑3使用的自定义压缩归档格式，类似于 ZIP 但使用 LZO 压缩和 CRC32 文件名哈希。

### CPK 文件头 (96 字节)

```c
struct CPKHeader {
    uint32_t dwLabel;         // 0x00: 魔数 0x1A545352 ("RST\x1A")
    uint32_t dwVersion;       // 0x04: 版本号
    uint32_t dwTableStart;    // 0x08: 文件表偏移
    uint32_t dwDataStart;     // 0x0C: 数据区偏移 (PAL4 = 0x00100080)
    uint32_t dwMaxFileNum;    // 0x10: 最大文件数
    uint32_t dwFileNum;       // 0x14: 实际文件数
    uint32_t dwIsFormatted;   // 0x18: 是否格式化
    uint32_t dwSizeOfHeader;  // 0x1C: 头部大小
    uint32_t dwValidTableNum; // 0x20: 有效表项数
    uint32_t dwMaxTableNum;   // 0x24: 最大表项数
    uint32_t dwFragmentNum;   // 0x28: 碎片数
    uint32_t dwPackageSize;   // 0x2C: 包总大小
    uint32_t dwReserved[20];  // 0x30: 保留 (80字节)
};
// sizeof = 0x60 (96)
```

### CPK 文件表项 (28 字节)

```c
struct CPKTable {
    uint32_t dwCRC;           // 0x00: 文件名 CRC32 哈希
    uint32_t dwFlag;          // 0x04: 标志位
    uint32_t dwFatherCRC;     // 0x08: 父目录 CRC32
    uint32_t dwStartPos;      // 0x0C: 数据起始位置
    uint32_t dwPackedSize;    // 0x10: 压缩后大小
    uint32_t dwOriginSize;    // 0x14: 原始大小
    uint32_t dwExtraInfoSize; // 0x18: 附加信息大小（文件名长度）
};
// sizeof = 0x1C (28)
```

### CPK 标志位

```c
#define CPK_FLAG_ISFILE         0x00000001  // 文件
#define CPK_FLAG_ISDIR          0x00000002  // 目录
#define CPK_FLAG_UNKNOWN1       0x00000004
#define CPK_FLAG_UNKNOWN2       0x00000008
#define CPK_FLAG_ISDELETED      0x00000010  // 已删除
#define CPK_FLAG_NOTCOMPRESSED  0x00010000  // 未压缩
```

### CPK 加密

部分 CPK 文件的前 4096 字节使用密钥加密：
```
密钥: "Vampire.C.J at Softstar Technology (ShangHai) Co., Ltd"
加密范围: 前 0x1000 (4096) 字节
```

### CPK 压缩

使用 mini-LZO 压缩算法。

---

## SCN 场景格式

SCN 文件描述游戏场景中的角色放置和交互物体。

### SCN 文件头 (126 字节)

```c
#pragma pack(push, 1)
struct SCNHeader {
    char     magic[4];            // 0x00: "SCN\0"
    uint16_t version;             // 0x04: 版本号 (1)
    uint16_t role_num;            // 0x06: 角色数量
    uint32_t role_offset;         // 0x08: 角色数据偏移
    uint16_t node_num;            // 0x0C: 节点数量
    uint32_t node_offset;         // 0x0E: 节点数据偏移
    char     cpk_name[32];        // 0x12: CPK 文件名 (GBK)
    char     scn_name[32];        // 0x32: 场景名 (GBK)
    char     scn_base_name[32];   // 0x52: 基础场景名 (GBK)
    uint32_t global_scene_index;  // 0x72: 全局场景索引
    uint32_t is_night;            // 0x76: 是否夜晚 (0/1)
    uint32_t skybox_id;           // 0x7A: 天空盒 ID
};
#pragma pack(pop)
// sizeof = 0x7E (126)
```

### SCN 角色项 (396 字节)

```c
#pragma pack(push, 1)
struct SCNRoleEntry {
    uint8_t  index;               // 0x00: 角色索引
    uint8_t  unknown1;            // 0x01
    char     name[64];            // 0x02: 角色名 (GBK)
    uint16_t unknown2;            // 0x42
    float    unknown_float;       // 0x44: 可能是朝向角度
    uint32_t unknown3;            // 0x48
    float    position_x;          // 0x4C: X 坐标
    float    position_z;          // 0x50: Z 坐标（注意：Z在Y前面）
    float    position_y;          // 0x54: Y 坐标
    uint32_t unknown4;            // 0x58
    uint32_t sce_proc_id;         // 0x5C: 关联的脚本过程 ID
    uint32_t unknown5;            // 0x60
    char     action_name[16];     // 0x64: 默认动作名 (GBK)
    uint32_t unknown6[3];         // 0x74
    uint8_t  reserved1[4];        // 0x80
    uint32_t unknown_array[49];   // 0x84
    uint32_t unknown7[3];         // 0x148
    uint32_t unknown_array2[29];  // 0x154
};
#pragma pack(pop)
// sizeof = 0x18C (396)
```

### SCN 节点项 (612 字节)

```c
#pragma pack(push, 1)
struct SCNNodeEntry {
    uint16_t index;               // 0x00: 节点索引
    uint16_t unknown1;            // 0x02
    char     name[32];            // 0x04: 节点名 (GBK)
    uint16_t unknown2;            // 0x24
    uint16_t unknown3;            // 0x26
    float    position_x;          // 0x28: X 坐标
    float    position_y;          // 0x2C: Y 坐标
    float    position_z;          // 0x30: Z 坐标
    float    rotation;            // 0x34: 旋转角度
    int32_t  nav_min_x;           // 0x38: 导航触发区域最小 X
    int32_t  nav_min_z;           // 0x3C: 导航触发区域最小 Z
    int32_t  nav_max_x;           // 0x40: 导航触发区域最大 X
    int32_t  nav_max_z;           // 0x44: 导航触发区域最大 Z
    uint16_t node_type;           // 0x48: 节点类型
    uint16_t nav_layer;           // 0x4A: 导航层
    int32_t  ladder_coord1_x;     // 0x4C: 梯子坐标1 X
    int32_t  ladder_coord1_z;     // 0x50: 梯子坐标1 Z
    int32_t  ladder_coord2_x;     // 0x54: 梯子坐标2 X
    int32_t  ladder_coord2_z;     // 0x58: 梯子坐标2 Z
    int32_t  ladder_switch_layer; // 0x5C: 梯子层切换
    uint8_t  reserved1[6];        // 0x60
    uint16_t unknown_words[4];    // 0x66
    uint8_t  reserved2[18];       // 0x6E
    uint32_t sce_proc_id;         // 0x80: 关联脚本过程 ID
    uint32_t unknown4;            // 0x84
    uint8_t  reserved3[192];      // 0x88
    uint16_t unknown5;            // 0x148
    uint8_t  reserved4[34];       // 0x14A
    float    aabb_min_x;          // 0x16C: AABB 触发区域
    float    aabb_min_y;          // 0x170
    float    aabb_min_z;          // 0x174
    float    aabb_max_x;          // 0x178
    float    aabb_max_y;          // 0x17C
    float    aabb_max_z;          // 0x180
    uint32_t unknown_array[6];    // 0x184
    uint8_t  reserved5[208];      // 0x19C
};
#pragma pack(pop)
// sizeof = 0x264 (612) -- 需验证 0x19C + 208 = 0x26C，实际以运行时为准
```

---

## SCE 脚本格式

SCE 文件包含场景脚本字节码。

### SCE 文件结构

```
+------------------+
| SCE Header       |
+------------------+
| Proc Header 表   |  (每个过程的入口信息)
+------------------+
| 字节码数据       |  (所有过程的指令流)
+------------------+
```

### SCE Proc Header

```c
struct SCEProcHeader {
    uint32_t id;       // 过程 ID
    uint32_t offset;   // 字节码偏移
    char     name[64]; // 过程名 (GBK)
};
```

### SCE 指令格式

```c
struct SCEInstruction {
    int16_t  opcode;           // 操作码
    int16_t  access_local_var; // 局部变量访问标志
    // 后跟可变长度参数
};
```

详细 opcode 列表见 [sce_opcodes.md](sce_opcodes.md)。

---

## 其他已知格式

### POL 模型格式
3D 模型文件，包含顶点、面、材质、骨骼信息。详细结构待逆向。

### CVD 动画格式
角色骨骼动画数据。详细结构待逆向。

### MV3 动画格式
另一种动画格式。详细结构待逆向。

### NAV 导航网格
场景寻路数据，定义可行走区域和层级关系。

---

## 字符编码

所有文本字段使用 **GBK** 编码（简体中文 Windows 默认编码）。
