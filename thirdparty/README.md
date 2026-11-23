# thirdparty/ — 外部项目与工具子模块（git submodule）

| 子模块 | 上游 | 引入目的 | 状态 |
|---|---|---|---|
| `ghidra-mcp/` | jaenster/ghidra-mcp | Ghidra MCP 服务——ghidra_track 双轨验证实验线的 daemon 通道（annotate/写计划的活体通道） | 实验线依赖 |
| `ghidra-reconstruct/` | jaenster/ghidra-reconstruct | redivivus 方法论的 Ghidra 直出重建工作流（quick 预设=伪影清除=「可编译」铁律档） | 实验线依赖 |
| `pal3-redivivus/` | pengyz/redivivus（branch: pal3） | **B 面重建树**——用 redivivus 方法论对 PAL3A/B 的完整 Ghidra 重建（自含 CMake/build-*）；证明了「Ghidra 直出合法 C + 编译验证」路线可行，是 ghidra_track 双轨实验的方法论来源。2026-11-09 定调：A 面（字节轨）主攻，B 面冻结为研究线 | 冻结研究线 |
| `PAL3patch/` | zhangboyang/PAL3patch | 《仙剑奇侠传三》分辨率补丁源码（v5.1）——代理 DLL（ijl15）模式与多继承嵌入等源码级参考；annotation 出处标签 `PAL3patch:xxx` 即源于此 | 参考资料 |

> 注：`PAL3patch:multi_inheritance_as_embed` 等 annotation `source` 字段是**出处记号**（语义引用），
> 与本目录路径无关。历史文档（docs/ 2026-05~11）中的 `extra/PAL3patch`、根 `pal3-redivivus`
> 为迁移前路径（2026-11-23 目录组织迁入本目录）。
