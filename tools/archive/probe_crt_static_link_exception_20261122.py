#!/usr/bin/env python3
"""[CRT 静态链接字节铁证 2026-11-22] exception.cpp 域归属裁决证据。

用户第一性质询: exception.cpp(0x408930 ??0exception@@QAE@XZ)需要反编译吗?
属于游戏逻辑吗?

验证: PAL3.exe 在 0x408930 的字节 == tools/vc6/Lib/libc.lib 的
??0exception@@QAE@XZ 成员字节 → 静态链接 CRT 产物(工具链可再生, 非游戏逻辑)。

方法:
  ① PE 头解析 .text 段 VA→raw 映射, 读 PAL3.exe @0x408930 前 64B
  ② 解析 libc.lib 归档: 遍历 COFF 成员符号表定位 ??0exception 所在成员 obj,
     提取 .text 节内函数体首 64B(经入口对齐)
  ③ 字节对比 + 反汇编抽样

用法: python3 tools/probe_crt_static_link_exception_20261122.py
"""
import struct
import sys

REPO = '/home/peng/workspace/PAL3Decomp'
EXE = REPO + '/original/PAL3.exe'
LIB = REPO + '/tools/vc6/Lib/libc.lib'
VA = 0x408930
SYM = '??0exception@@QAE@XZ'


def exe_bytes_at(va, n=64):
    """PE 头解析节表, VA→文件偏移。"""
    d = open(EXE, 'rb').read()
    e_lfanew = struct.unpack_from('<I', d, 0x3C)[0]
    nsec = struct.unpack_from('<H', d, e_lfanew + 6)[0]
    opt_size = struct.unpack_from('<H', d, e_lfanew + 20)[0]
    sec0 = e_lfanew + 24 + opt_size
    for i in range(nsec):
        s = sec0 + 40 * i
        name = d[s:s + 8].rstrip(b'\0').decode('ascii', 'replace')
        vsize, vaddr, rsize, raddr = struct.unpack_from('<IIII', d, s + 8)
        if vaddr <= va - 0x400000 < vaddr + max(vsize, rsize):
            off = raddr + (va - 0x400000 - vaddr)
            print('[exe] 段 %s VA=0x%X raw=0x%X → 0x%08X 前64B:' % (name, vaddr + 0x400000, raddr, va))
            b = d[off:off + n]
            print('  ', b.hex(' '))
            return b
    print('[exe] VA 0x%X 未落任何节' % va)
    return None


def lib_member_bytes():
    """解析 libc.lib 归档(Windows COFF archive), 定位含 SYM 的成员, 提取其代码节。"""
    d = open(LIB, 'rb').read()
    assert d[:8] == b'!<arch>\n', '非 COFF 归档'
    # 第一链接器成员(符号表): offset 8, "               " 名字
    off = 8
    hdr = d[off:off + 60]
    size = int(hdr[48:58].decode().strip())
    first = d[off + 60:off + 60 + size]
    nsyms = struct.unpack_from('<I', first, 0)[0]
    offs = struct.unpack_from('<%dI' % nsyms, first, 4)
    strs = first[4 + 4 * nsyms:]
    print('[lib] libc.lib 第一符号表: %d 符号' % nsyms)
    target_off = None
    idx = 0
    pos = 0
    for i in range(nsyms):
        end = strs.index(b'\0', pos)
        nm = strs[pos:end].decode('ascii', 'replace')
        if nm == SYM:
            target_off = offs[i]
            print('[lib] %s 找到于成员偏移 0x%X (符号序号 %d)' % (nm, target_off, i))
            break
        pos = end + 1
    if target_off is None:
        print('[lib] %s 不在 libc.lib!' % SYM)
        return None
    # 成员头: target_off-60 处
    mhdr = d[target_off - 60:target_off]
    mname = mhdr[0:16].decode('ascii', 'replace').strip()
    msize = int(mhdr[48:58].decode().strip())
    member = d[target_off:target_off + msize]
    print('[lib] 成员 obj: %s (%dB)' % (mname, msize))
    # COFF: 节表在文件头后
    nsec = struct.unpack_from('<H', member, 2)[0]
    opt = struct.unpack_from('<H', member, 16)[0]
    sec0 = 20 + opt
    text = None
    for i in range(nsec):
        s = sec0 + 40 * i
        nm = member[s:s + 8].rstrip(b'\0').decode('ascii', 'replace')
        rsize, raddr = struct.unpack_from('<II', member, s + 16)
        if nm == '.text':
            text = member[raddr:raddr + rsize]
            print('[lib] .text %dB' % rsize)
            break
    return text


def main():
    eb = exe_bytes_at(VA)
    tb = lib_member_bytes()
    if eb is None or tb is None:
        sys.exit(1)
    # 在 lib .text 里找 exe 前 16B 的出现(对齐函数入口)
    pat = eb[:16]
    i = tb.find(pat)
    if i >= 0:
        print('\n[判据] exe@0x%X 前16B 在 libc.lib .text @+0x%X 精确命中' % (VA, i))
        print('  exe 前64B:', eb.hex(' '))
        print('  lib 64B  :', tb[i:i + 64].hex(' '))
        m = sum(1 for a, b in zip(eb, tb[i:i + 64]) if a == b)
        print('  64B 一致度: %d/64' % m)
        print('\n结论: 0x%X %s —— 静态链接 CRT 产物, 工具链可再生, 非游戏逻辑'
              % (VA, '字节等同' if m == 64 else '部分一致(前16B等同)'))
    else:
        print('\n[判据] 前16B 未在 libc.lib .text 中命中——需人工复核(可能 ICF/编译差分)')


if __name__ == '__main__':
    main()
