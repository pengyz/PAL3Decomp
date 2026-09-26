---
name: gotcha-msvc6-spurious-c2512-on-lf-only-headers
description: 本仓库 MSVC6 cl.exe 对 **LF-only 行尾的头文件**会发出成批假 C2512（"no appropriate default constructor available"，指名 gbVec3D 等无关类）——同一文件 CRLF 则编译通过；任何脚本改头文件必须二进制模式写回保 CRLF
type: gotcha
created: 2026-09-26
updated: 2026-09-26
status: active
sources: [session-2026-09-26, SDK虚构构造批次]
---

# gotcha：LF-only 头文件触发 MSVC6 假 C2512（行尾幽灵）

## 现象（2026-09-26 SDK 虚构构造批次实测）

Python 文本模式读改 gbengine 头（`open(encoding='utf-8')` 读 + `newline=''` 写）
会把 CRLF 无声转成 LF。随后 cl.exe 在**与修改内容毫无关系的 TU**（如
Scene.cpp:34 的 `struct gbVec3D pOut;`）报成批：

```
error C2512: 'gbVec3D' : no appropriate default constructor available
```

指名的类/构造**完好无损**。删除 gbengine_types.h 里**任意一行**（哪怕
`gbColorFlt(float,float,float,float);`）都触发；恢复任意一行都消失。

## 判别与修复

- 同一内容以 CRLF 写回（`open(path,'rb')` 二进制读写、正则用 `\r?\n`）→ 全绿。
- 因此曾误推出"GBAPI struct 内联构造 + 类类型成员 ⇒ C2512"的机制——**全是 LF 幽灵**，
  内联空构造本身在 GBAPI struct 里编译正常（gbColorQuad 已有先例）。

## 规则

1. 凡脚本改 include/ 头：**必须 `'rb'` 读 `'wb'` 写**（或读后显式 `'\r\n'` 归一）。
2. 遇到"删除任意行都红"的对称性怪象，先 diff 行尾（`file` / grep `\r`）再查语义。
3. git 的 "LF will be replaced by CRLF" warning 是本坑的前兆信号。
