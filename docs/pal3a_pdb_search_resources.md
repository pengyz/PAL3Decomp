# PAL3A.PDB 搜索资源清单

## 确认信息

根据 PAL3patch 笔记（notes20160711.txt）：
> "而问情篇附带了主程序PAL3A.EXE的调试符号文件PAL3A.PDB（哇，一份大礼诶）"

**结论**: PAL3A.PDB 是问情篇的官方调试符号文件，但 Steam 版已移除。

## 手动搜索清单

### GitHub 项目搜索

访问以下链接手动搜索：

1. **OpenPAL3 项目**
   - 主仓库: https://github.com/dontpanic92/OpenPAL3
   - Issues: https://github.com/dontpanic92/OpenPAL3/issues?q=PDB
   - Discussions: https://github.com/dontpanic92/OpenPAL3/discussions

2. **PAL3patch 项目**
   - Issues: https://github.com/zhangboyang/PAL3patch/issues?q=PDB
   - 作者主页: https://github.com/zhangboyang

3. **其他相关项目**
   ```
   https://github.com/search?q=PAL3A+PDB
   https://github.com/search?q=chinese+paladin+symbols
   https://github.com/search?q=仙剑3+PDB
   ```

### Gitee (中国镜像)

```
https://gitee.com/search?q=PAL3A
https://gitee.com/search?q=仙剑3外传
```

### 游戏社区论坛

1. **游侠网** (ali213.net)
   - 仙剑奇侠传系列讨论区
   - MOD 制作区
   搜索关键词: "PAL3A.PDB", "问情篇 调试符号", "仙剑3外传 开发版"

2. **3DM 论坛** (bbs.3dmgame.com)
   - 仙剑系列专区
   搜索: "PAL3A PDB", "问情篇 反编译"

3. **游民星空** (gamersky.com)
   - 下载/工具区

4. **仙剑贴吧**
   - 百度贴吧: 仙剑奇侠传吧
   - 搜索: "PAL3A.PDB"

### 文件分享站点

**警告**: 从非官方来源下载时要验证文件完整性

搜索关键词：
```
PAL3A.PDB
仙剑奇侠传3外传 PDB
问情篇 调试符号
PAL3A debugging symbols
```

可能的站点：
- 百度网盘（搜索分享链接）
- 城通网盘
- 蓝奏云

### 专业反编译论坛

1. **看雪论坛** (pediy.com)
   - 逆向工程区
   - 搜索: "PAL3A", "仙剑3"

2. **吾爱破解** (52pojie.cn)
   - 脱壳破解区
   - 搜索: "仙剑3外传"

3. **腾讯Bugly** - 可能有人讨论过

## 已知的 PDB 工具

如果找到 PDB，使用这些工具：

1. **PDB Explorer**
   - 下载: http://blog.titilima.com/pdbexp.html
   - 用途: 导出 C/C++ 结构体定义

2. **Microsoft DBH**
   - 内置于 Windows SDK
   - 命令: `dbh -v PAL3A.pdb enum > symbols.txt`

3. **cvdump**
   - 官方: https://github.com/Microsoft/microsoft-pdb

## 验证 PDB 的方法

找到文件后，验证其真实性：

```bash
# 检查文件大小（应该在 10-30 MB 之间）
ls -lh PAL3A.pdb

# 使用 file 命令
file PAL3A.pdb
# 应该显示: Microsoft Program Database

# 使用 DBH 验证
dbh -v PAL3A.pdb
# 应该列出大量符号

# 检查是否包含 gbengine 符号
dbh -v PAL3A.pdb enum | grep -i gbengine
```

## 替代方案（如果找不到 PDB）

### 1. 使用已提取的信息

PAL3patch 笔记中已经包含很多从 PDB 提取的信息：

```bash
# 搜索笔记中的结构体定义
cd extra/PAL3patch/notes/pal3
grep -r "struct\|class" *.txt

# 已知类列表
cat known_classes.txt
```

### 2. 使用 RTTI 恢复类信息

PAL3A.exe 和 gbengine.dll 包含 RTTI，可以恢复：
- 类名
- 虚函数表
- 继承关系

在 Ghidra 中启用 RTTI 分析。

### 3. 参考 OpenPAL3 项目

OpenPAL3 是完整的重新实现，包含了很多结构定义：
```
https://github.com/dontpanic92/OpenPAL3/tree/master/yaobow
```

### 4. 继续使用现有资源

即使没有 PDB：
- ✅ PAL3.exe 已脱壳
- ✅ topo.dll 27% 完成
- ✅ gbengine.dll 有导出函数名
- ✅ RTTI 信息可用

## 社区求助模板

如果在论坛发帖询问，可以使用：

```
标题：寻求 PAL3A.PDB 调试符号文件

正文：
各位好，我在进行仙剑奇侠传3外传·问情篇的逆向研究。
根据 PAL3patch 项目笔记，原版问情篇应该附带 PAL3A.PDB 调试符号文件。
但 Steam 版已移除此文件。

请问有人保存了这个文件吗？或者知道从哪里可以获取？

用途：用于游戏引擎研究和开源重制项目
项目：https://github.com/zhangboyang/PAL3patch
```

## 联系作者

PAL3patch 作者可能愿意分享：

- GitHub: @zhangboyang
- 通过 PAL3patch Issues: https://github.com/zhangboyang/PAL3patch/issues/new

建议的问题：
```
Hi, I'm working on reverse engineering PAL3/PAL3A based on your excellent work.
I noticed from your notes that PAL3A retail version included PAL3A.PDB.
Unfortunately, the Steam version has removed it.

Would you be willing to share the PDB file, or let me know where I might find it?
Thank you for your amazing work on PAL3patch!
```

## 下一步行动

1. ⬜ 在 GitHub 搜索 PAL3A PDB
2. ⬜ 访问游侠网/3DM 论坛搜索
3. ⬜ 在 PAL3patch 创建 Issue 询问作者
4. ⬜ 检查 OpenPAL3 项目是否有相关信息
5. ⬜ 如果找不到，使用替代方案继续反编译

## 更新日志

- 2026-05-01: 创建搜索资源清单
- 确认 Steam 版不含 PDB
- 待行动：社区搜索和作者联系
