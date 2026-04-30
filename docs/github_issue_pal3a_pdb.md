# GitHub Issue for PAL3patch - Request for PAL3A.PDB

## Issue Information

**Repository**: https://github.com/zhangboyang/PAL3patch
**Create Issue**: https://github.com/zhangboyang/PAL3patch/issues/new

---

## Issue Content (English Version)

### Title:
```
[Question] Where can I find PAL3A.PDB debugging symbols?
```

### Body:
```markdown
Hi @zhangboyang,

Thank you for your amazing work on PAL3patch! Your project has been incredibly helpful for understanding the PAL3 engine.

I'm working on a decompilation project for PAL3, and I noticed from your notes (`notes/pal3/notes20160711.txt`) that the retail version of PAL3A (问情篇) included `PAL3A.PDB` - the debugging symbols file.

> "而问情篇附带了主程序PAL3A.EXE的调试符号文件PAL3A.PDB（哇，一份大礼诶）"

Unfortunately, the Steam version of PAL3A has removed this file, and I haven't been able to locate it elsewhere.

**Would you be willing to:**
1. Share the PAL3A.PDB file, or
2. Point me to where I might find it?

The PDB would be extremely valuable for:
- Understanding gbengine.dll structure (as you mentioned, it's nearly identical between PAL3 and PAL3A)
- Extracting type definitions and function signatures
- Accelerating the reverse engineering process

I understand if there are licensing concerns. Any guidance would be greatly appreciated!

**My project details:**
- Goal: Matching decompilation of PAL3.exe, gbengine.dll, and topo.dll
- Current progress: PAL3.exe unpacked, topo.dll ~27% decompiled
- References: Your PAL3patch notes and the OpenPAL3 project

Thank you for considering this request!
```

---

## Issue Content (中文版本)

### 标题：
```
[问题] 请问在哪里可以获取 PAL3A.PDB 调试符号文件？
```

### 正文：
```markdown
你好 @zhangboyang，

非常感谢你在 PAL3patch 项目上的出色工作！这个项目对理解仙剑3引擎非常有帮助。

我正在进行仙剑3的反编译项目，从你的笔记（`notes/pal3/notes20160711.txt`）中了解到，问情篇的零售版本包含了 `PAL3A.PDB` 调试符号文件。

> "而问情篇附带了主程序PAL3A.EXE的调试符号文件PAL3A.PDB（哇，一份大礼诶）"

遗憾的是，Steam 版的 PAL3A 已经移除了这个文件，我在其他地方也没能找到。

**不知道您是否愿意：**
1. 分享 PAL3A.PDB 文件，或
2. 告诉我可能从哪里获取？

这个 PDB 文件对以下工作非常有价值：
- 理解 gbengine.dll 的结构（如您所说，PAL3 和 PAL3A 的 gbengine 几乎完全相同）
- 提取类型定义和函数签名
- 加速逆向工程过程

我理解可能存在授权方面的顾虑，任何指导都将不胜感激！

**我的项目详情：**
- 目标：PAL3.exe、gbengine.dll 和 topo.dll 的匹配反编译
- 当前进度：PAL3.exe 已脱壳，topo.dll 约 27% 完成
- 参考资料：您的 PAL3patch 笔记和 OpenPAL3 项目

感谢您考虑这个请求！
```

---

## How to Create the Issue

### Option 1: Direct Link (Recommended)
Click this link to create the issue (you'll need to be logged into GitHub):

**English version:**
```
https://github.com/zhangboyang/PAL3patch/issues/new?title=[Question]%20Where%20can%20I%20find%20PAL3A.PDB%20debugging%20symbols?
```

**中文版:**
```
https://github.com/zhangboyang/PAL3patch/issues/new?title=[问题]%20请问在哪里可以获取%20PAL3A.PDB%20调试符号文件？
```

### Option 2: Manual Steps

1. Go to https://github.com/zhangboyang/PAL3patch/issues
2. Click the green "New issue" button
3. Copy and paste the title and body from above
4. Click "Submit new issue"

### Option 3: Use gh CLI (if you install it later)

```bash
# Install gh CLI first
# Then create the issue:
gh issue create \
  --repo zhangboyang/PAL3patch \
  --title "[Question] Where can I find PAL3A.PDB debugging symbols?" \
  --body-file issue_body.txt
```

---

## Follow-up Actions

After creating the issue:

1. **Watch the repository** to get notifications when the author responds
2. **Be patient** - the author may be busy
3. **Check your GitHub notifications** regularly
4. **Meanwhile**, continue with the decompilation work using available resources

---

## Alternative Actions While Waiting

If the author doesn't respond immediately:

1. **Extract information from PAL3patch notes**
   ```bash
   cd extra/PAL3patch/notes/pal3
   grep -r "struct\|class" *.txt > extracted_types.txt
   ```

2. **Use RTTI from gbengine.dll**
   - Load in Ghidra with RTTI analysis enabled
   - Extract class names and vtables

3. **Continue topo.dll decompilation**
   - Already 27% complete
   - Good progress without needing PDB

4. **Reference OpenPAL3 project**
   - Many structure definitions available
   - Cross-reference with PAL3patch notes
